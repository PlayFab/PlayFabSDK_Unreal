//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "HAL/Platform.h"
PRAGMA_DISABLE_UNDEFINED_IDENTIFIER_WARNINGS

#if defined(OSS_PLAYFAB_GDK_SUPPORT)
#include "PlatformDefines.h"

#include "OnlineVoiceInterfacePlayFab.h"
#include "OnlineSessionInterfacePlayFab.h"
#include "Misc/ConfigCacheIni.h"

namespace
{
	bool bPartyXblManagerInitialized = false;

	struct RemoteTalkerOptionsGDK
	{
		ECrossNetworkType Type = ECrossNetworkType::DISABLED;
		TMap<FString /*User ID*/, PartyChatPermissionOptions> OptionsMap;
	};

	TMap<FString /*User ID*/, PartyXblChatUser*> TalkersMap;
	TMap<FString /*User ID*/, RemoteTalkerOptionsGDK> TalkersOptionsGDK;
	TMap<FString /*Entity ID*/, FString /*User ID*/> TalkerIdMappingGDK;

	PartyXblLocalChatUser* LocalChatUser = nullptr;

	TArray<FCrossNetworkTalkerPlayFab> CrossNetworkTalkersGDK;

	PartyString GetXblErrorMessage(PartyError error)
	{
		PartyString errString = nullptr;

		PartyError err = PartyXblManager::GetErrorMessage(error, &errString);
		if (PARTY_FAILED(err))
		{
			UE_LOG_ONLINE(Error, TEXT("Failed to get error message %lu."), err);
			return "[ERROR]";
		}

		return errString;
	}

	bool UpdateTalkerCrossNetworkPermissionGDK()
	{
		if (CrossNetworkTalkersGDK.Num() == 0)
		{
			return false;
		}

		if (LocalChatUser)
		{
			uint64_t LocalUserId;
			PartyError err = LocalChatUser->GetXboxUserId(&LocalUserId);
			if (PARTY_FAILED(err))
			{
				UE_LOG_ONLINE(Verbose, TEXT("Getting local user id failed: %hs"), GetXblErrorMessage(err));
				return false;
			}
			
			FString LocalTalkerUserId = FString::Printf(TEXT("%llu"), LocalUserId);

			auto CrossNetwork = CrossNetworkTalkersGDK[0];
			
			Party::PartyChatPermissionOptions ChatPermissionMask = PartyChatPermissionOptions::None;
			RemoteTalkerOptionsGDK* LocalTalker = TalkersOptionsGDK.Find(LocalTalkerUserId);
			if (LocalTalker)
			{
				Party::PartyChatPermissionOptions* PermissionOptions = LocalTalker->OptionsMap.Find(CrossNetwork.RemoteUserId);
				if (PermissionOptions)
				{
					ChatPermissionMask = *PermissionOptions;
				}
			}
			else
			{
				TalkersOptionsGDK.Emplace(LocalTalkerUserId, RemoteTalkerOptionsGDK());
				LocalTalker = TalkersOptionsGDK.Find(LocalTalkerUserId);
			}

			switch(CrossNetwork.Type)
			{
			case ECrossNetworkType::DISABLED:
			case ECrossNetworkType::GDK:
				break;
			case ECrossNetworkType::NONGDK:
			{
				PartyXblCrossNetworkCommunicationPrivacySetting	Permission;
				err = LocalChatUser->GetCrossNetworkCommunicationPrivacySetting(&Permission);
				if (PARTY_FAILED(err))
				{
					UE_LOG_ONLINE(Error, TEXT("Getting cross-network permission failed: %hs"), GetXblErrorMessage(err));
					return false;
				}

				switch (Permission)
				{
				case PartyXblCrossNetworkCommunicationPrivacySetting::Allowed:
					ChatPermissionMask = Party::PartyChatPermissionOptions::SendAudio | Party::PartyChatPermissionOptions::ReceiveAudio | Party::PartyChatPermissionOptions::ReceiveText;
					break;
				case PartyXblCrossNetworkCommunicationPrivacySetting::FriendsOnly:
				case PartyXblCrossNetworkCommunicationPrivacySetting::Disallowed:
					break;
				}
				break;
			}
			}

			LocalTalker->Type = CrossNetwork.Type;
			LocalTalker->OptionsMap.Emplace(CrossNetwork.RemoteUserId, ChatPermissionMask);

			UE_LOG_ONLINE(Verbose, TEXT("Set voice chat permission %s vs %s as %d, Type %d"), *LocalTalkerUserId, *CrossNetwork.RemoteUserId, ChatPermissionMask, CrossNetwork.Type);

			CrossNetworkTalkersGDK.RemoveAt(0, 1);
			return true;
		}
		else
		{
			if (IsRunningDedicatedServer())
			{
				UE_LOG_ONLINE(Verbose, TEXT("LocalChatUser is nullptr on dedicated server, clearing %d pending cross-network talkers"), CrossNetworkTalkersGDK.Num());
				CrossNetworkTalkersGDK.Empty();
			}
			else
			{
				UE_LOG_ONLINE(Verbose, TEXT("LocalChatUser is nullptr, deferring %d pending cross-network talkers until local user is created"), CrossNetworkTalkersGDK.Num());
			}
		}
		return false;
	}
}

#if defined(OSS_PLAYFAB_GDK)
void FOnlineVoicePlayFab::AddTalkerIdMapping(const FString& EntityId, const FString& UserId)
{
	AddTalkerIdMappingGDK(EntityId, UserId);
}

void FOnlineVoicePlayFab::SetTalkerCrossNetworkPermission(ECrossNetworkType VoiceChatType, const FString& RemoteUserId, const FString& PlatformModel)
{
	SetTalkerCrossNetworkPermissionGDK(VoiceChatType, RemoteUserId, PlatformModel);
}

PartyChatPermissionOptions FOnlineVoicePlayFab::GetChatPermissionsForTalker(const FString& LocalId, const FString& RemoteId)
{
	return GetChatPermissionsForTalkerGDK(LocalId, RemoteId);
}

FString FOnlineVoicePlayFab::GetPlatformIdFromEntityId(const FString& EntityId)
{
	return GetPlatformIdFromEntityIdGDK(EntityId);
}

void FOnlineVoicePlayFab::StartTrackingPermissionForTalker(const FString& UserId, bool IsRemote)
{
	StartTrackingPermissionForTalkerGDK(UserId, IsRemote);
}

void FOnlineVoicePlayFab::StopTrackingPermissionForTalker(const FString& UserId)
{
	StopTrackingPermissionForTalkerGDK(UserId);
}

void FOnlineVoicePlayFab::TickTalkerPermissionTracking()
{
	TickTalkerPermissionTrackingGDK();
}
#endif // OSS_PLAYFAB_GDK

void FOnlineVoicePlayFab::AddTalkerIdMappingGDK(const FString& EntityId, const FString& UserId)
{
	TalkerIdMappingGDK.Add(EntityId, UserId);
	UE_LOG_ONLINE(Verbose, TEXT("Talker ID Mapping %s to %s"), *UserId, *EntityId);
}

void FOnlineVoicePlayFab::SetTalkerCrossNetworkPermissionGDK(ECrossNetworkType VoiceChatType, const FString& RemoteUserId, const FString& PlatformModel)
{
	FCrossNetworkTalkerPlayFab CrossNetwork = {VoiceChatType, RemoteUserId, PlatformModel};
	CrossNetworkTalkersGDK.Emplace(CrossNetwork);
}

PartyChatPermissionOptions FOnlineVoicePlayFab::GetChatPermissionsForTalkerGDK(const FString& LocalId, const FString& RemoteId)
{
	RemoteTalkerOptionsGDK* AllOptions = nullptr;
	PartyChatPermissionOptions* Options = nullptr;

	UE_LOG_ONLINE(Verbose, TEXT("GetChatPermissionsForTalker %s vs. %s"), *LocalId, *RemoteId);

	AllOptions = TalkersOptionsGDK.Find(LocalId);
	if (AllOptions != nullptr)
	{
		Options = (*AllOptions).OptionsMap.Find(RemoteId);
		if (Options != nullptr)
		{
			return *Options;
		}
	}

	UE_LOG_ONLINE(Verbose, TEXT("No options found"));

	return PartyChatPermissionOptions::None;
}

FString FOnlineVoicePlayFab::GetPlatformIdFromEntityIdGDK(const FString& EntityId)
{
	UE_LOG_ONLINE(Verbose, TEXT("GetPlatformIdFromEntityId %s"), *EntityId);

	FString* Xuid = TalkerIdMappingGDK.Find(EntityId);
	if (Xuid != nullptr)
	{
		return *Xuid;
	}

	UE_LOG_ONLINE(Error, TEXT("Failed to find xuid mapping for %s"), *EntityId);

	return FString();
}

void FOnlineVoicePlayFab::StartTrackingPermissionForTalkerGDK(const FString& UserId, bool IsRemote)
{
	UE_LOG_ONLINE(Verbose, TEXT("StartTrackingPermissionForTalker %s %s"), *UserId, IsRemote ? TEXT("remote") : TEXT("local"));

	if (bPartyXblManagerInitialized == false)
	{
		FString TitleID;
		GConfig->GetString(TEXT("OnlineSubsystemPlayFab"), TEXT("PlayFabTitleID"), TitleID, GEngineIni);

		PartyError err = PartyXblManager::GetSingleton().Initialize(TCHAR_TO_UTF8(*TitleID));
		if (PARTY_FAILED(err))
		{
			UE_LOG_ONLINE(Error, TEXT("Party XboxLive Initialize failed: %hs"), GetXblErrorMessage(err));
			return;
		}

		bPartyXblManagerInitialized = true;
	}

	uint64_t XboxId = FCString::Atoi64(*UserId);

	if (IsRemote)
	{
		PartyXblChatUser* NewUser = nullptr;
		PartyError err = PartyXblManager::GetSingleton().CreateRemoteChatUser(XboxId, &NewUser);
		if (PARTY_SUCCEEDED(err))
		{
			TalkersMap.Emplace(UserId, NewUser);
		}
		else
		{
			UE_LOG_ONLINE(Error, TEXT("CreateRemoteChatUser failed: %hs"), GetXblErrorMessage(err));
		}
	}
	else
	{
		PartyXblLocalChatUser* NewUser = nullptr;
		PartyError err = PartyXblManager::GetSingleton().CreateLocalChatUser(XboxId, nullptr, &NewUser);
		if (PARTY_SUCCEEDED(err))
		{
			TalkersMap.Emplace(UserId, NewUser);
			LocalChatUser = NewUser;
		}
		else
		{
			UE_LOG_ONLINE(Error, TEXT("CreateLocalChatUser failed: %hs"), GetXblErrorMessage(err));
		}
	}

	if (TalkersOptionsGDK.Find(UserId) == nullptr)
	{
		TalkersOptionsGDK.Emplace(UserId, RemoteTalkerOptionsGDK());
	}

	PartyError err = PartyXblManager::GetSingleton().GetEntityIdsFromXboxLiveUserIds(1, &XboxId, LocalChatUser, nullptr);
	if (PARTY_FAILED(err))
	{
		UE_LOG_ONLINE(Error, TEXT("GetEntityIdsFromXboxLiveUserIds failed: %hs"), GetXblErrorMessage(err));
	}
}

void FOnlineVoicePlayFab::StopTrackingPermissionForTalkerGDK(const FString& UserId)
{
	UE_LOG_ONLINE(Verbose, TEXT("StopTrackingPermissionForTalker %s"), *UserId);

	PartyXblChatUser** User = TalkersMap.Find(UserId);
	if (User != nullptr)
	{
		PartyError err = PartyXblManager::GetSingleton().DestroyChatUser(*User);
		if (PARTY_FAILED(err))
		{
			UE_LOG_ONLINE(Error, TEXT("DestroyChatUser failed: %hs"), GetXblErrorMessage(err));
		}

		TalkersMap.Remove(UserId);
		TalkersOptionsGDK.Remove(UserId);

		for (auto& TalkerIdKvPair : TalkerIdMappingGDK)
		{
			if (TalkerIdKvPair.Value == UserId)
			{
				TalkerIdMappingGDK.Remove(TalkerIdKvPair.Key);
				break;
			}
		}
	}

	if (TalkersMap.Num() == 0)
	{
		PartyError err = PartyXblManager::GetSingleton().Cleanup();
		if (PARTY_FAILED(err))
		{
			UE_LOG_ONLINE(Error, TEXT("PartyXblManager::Cleanup() failed: %hs"), GetXblErrorMessage(err));
		}

		bPartyXblManagerInitialized = false;
	}
}

void FOnlineVoicePlayFab::TickTalkerPermissionTrackingGDK()
{
	if (bPartyXblManagerInitialized == false)
	{
		return;
	}
	
	if (TalkersMap.Num() == 0)
	{
		return;
	}

	uint32_t count;
	PartyXblStateChangeArray xblChanges;

	// Process Xbl messages
	PartyError err = PartyXblManager::GetSingleton().StartProcessingStateChanges(
		&count,
		&xblChanges
	);

	if (PARTY_FAILED(err))
	{
		UE_LOG_ONLINE(Error, TEXT("FOnlineVoicePlayFab::TickTalkerPermissionTracking: StartProcessingStateChanges failed: %hs"), GetXblErrorMessage(err));
		return;
	}

	for (uint32_t i = 0; i < count; i++)
	{
		auto change = xblChanges[i];

		switch (change->stateChangeType)
		{
		case PartyXblStateChangeType::CreateLocalChatUserCompleted:
			UE_LOG_ONLINE(Verbose, TEXT("PartyXblStateChangeType: CreateLocalChatUserCompleted"));
			break;

		case PartyXblStateChangeType::LocalChatUserDestroyed:
			UE_LOG_ONLINE(Verbose, TEXT("PartyXblStateChangeType: LocalChatUserDestroyed"));
			break;

		case PartyXblStateChangeType::LoginToPlayFabCompleted:
			UE_LOG_ONLINE(Verbose, TEXT("PartyXblStateChangeType: LoginToPlayFabCompleted"));
			break;

		case PartyXblStateChangeType::GetEntityIdsFromXboxLiveUserIdsCompleted:
		{
			UE_LOG_ONLINE(Verbose, TEXT("PartyXblStateChangeType: PartyXblGetEntityIdsFromXboxLiveUserIdsCompletedStateChange"));
			auto userStateChange = static_cast<const PartyXblGetEntityIdsFromXboxLiveUserIdsCompletedStateChange*>(change);

			if (userStateChange->result != PartyXblStateChangeResult::Succeeded)
			{
				check(userStateChange->result == PartyXblStateChangeResult::Succeeded);
				// This should not fail because users are required to be signed in to PlayFab with their XUID before
				// we attempt to get the EntityIds.
				break;
			}

			for (uint32_t j = 0; j < userStateChange->entityIdMappingCount; j++)
			{
				if (strlen(userStateChange->entityIdMappings[j].playfabEntityId) > 0)
				{
					FString XboxLiveUserId = FString::Printf(TEXT("%llu"), userStateChange->entityIdMappings[j].xboxLiveUserId);
					FString EntityId(userStateChange->entityIdMappings[j].playfabEntityId);
					TalkerIdMappingGDK.Add(EntityId, XboxLiveUserId);
					UE_LOG_ONLINE(Verbose, TEXT("TalkerIdMapping: %s to %s"), *XboxLiveUserId, *EntityId);
				}
				else
				{
					UE_LOG_ONLINE(Verbose, TEXT("TalkerIdMapping: can't find Entity ID for %llu."), userStateChange->entityIdMappings[j].xboxLiveUserId);
				}
			}

			// update chat permissions for all, this can arrive after remote chat controls are created
			UpdatePermissionsForAllControls();

			break;
		}

		case PartyXblStateChangeType::RequiredChatPermissionInfoChanged:
		{
			UE_LOG_ONLINE(Verbose, TEXT("PartyXblStateChangeType: RequiredChatPermissionInfoChanged"));
			auto chatPermissionChanged = static_cast<const PartyXblRequiredChatPermissionInfoChangedStateChange*>(change);

			PartyXblLocalChatUser* localChatUser = chatPermissionChanged->localChatUser;
			PartyXblChatUser* targetChatUser = chatPermissionChanged->targetChatUser;

			PartyXblChatPermissionInfo chatPermissionInfo;
			err = localChatUser->GetRequiredChatPermissionInfo(targetChatUser, &chatPermissionInfo);
			if (PARTY_FAILED(err))
			{
				UE_LOG_ONLINE(Error, TEXT("GetRequiredChatPermissionInfo failed: %hs"), GetXblErrorMessage(err));
				break;
			}

			uint64_t userXuid = 0;
			err = localChatUser->GetXboxUserId(&userXuid);
			if (PARTY_FAILED(err))
			{
				UE_LOG_ONLINE(Error, TEXT("GetXboxUserId on local failed: %hs"), GetXblErrorMessage(err));
				break;
			}

			FString UserXuid = FString::Printf(TEXT("%llu"), userXuid);

			RemoteTalkerOptionsGDK* LocalTalker = TalkersOptionsGDK.Find(UserXuid);
			if (LocalTalker == nullptr)
			{
				UE_LOG_ONLINE(Error, TEXT("Can't find TalkersOptions entry for %s!"), *UserXuid);
				break;
			}

			uint64_t remoteXuid = 0;
			err = targetChatUser->GetXboxUserId(&remoteXuid);
			if (PARTY_FAILED(err))
			{
				UE_LOG_ONLINE(Error, TEXT("GetXboxUserId on remote failed: %hs"), GetXblErrorMessage(err));
				break;
			}

			FString RemoteXuid = FString::Printf(TEXT("%llu"), remoteXuid);

			if (LocalTalker->Type == ECrossNetworkType::GDK)
			{
				LocalTalker->OptionsMap.Emplace(RemoteXuid, chatPermissionInfo.chatPermissionMask);
			}
			else
			{
				UE_LOG_ONLINE(Verbose, TEXT("Skip voice chat permission setting for %s vs %s, permission: %x."), *UserXuid, *RemoteXuid, chatPermissionInfo.chatPermissionMask);
			}

			OnChatPermissionsChanged(FString::Printf(TEXT("%s"), *UserXuid), FString::Printf(TEXT("%s"), *RemoteXuid), chatPermissionInfo.chatPermissionMask);
			break;
		}

		case PartyXblStateChangeType::TokenAndSignatureRequested:
		{
			UE_LOG_ONLINE(Verbose, TEXT("PartyXblStateChangeType: TokenAndSignatureRequested"));

			auto tokenAndSignatureRequested = static_cast<const PartyXblTokenAndSignatureRequestedStateChange*>(change);

			// Setup the options flags
			XUserGetTokenAndSignatureOptions tnsOptions = tokenAndSignatureRequested->forceRefresh ?
				XUserGetTokenAndSignatureOptions::ForceRefresh : XUserGetTokenAndSignatureOptions::None;

			if (tokenAndSignatureRequested->allUsers)
			{
				tnsOptions |= XUserGetTokenAndSignatureOptions::AllUsers;
			}

			// Format the headers
			std::vector<XUserGetTokenAndSignatureHttpHeader> headers;
			for (uint32_t j = 0; j < tokenAndSignatureRequested->headerCount; j++)
			{
				headers.push_back({ tokenAndSignatureRequested->headers[j].name, tokenAndSignatureRequested->headers[j].value });
			}

			XAsyncBlock* async = new XAsyncBlock{};

			async->context = (void*)(UINT_PTR)tokenAndSignatureRequested->correlationId;
			async->callback = [](XAsyncBlock* async)
			{
				size_t bufferSize;
				HRESULT hr = XUserGetTokenAndSignatureResultSize(async, &bufferSize);

				if (FAILED(hr))
				{
					UE_LOG_ONLINE(Error, TEXT("XUserGetTokenAndSignatureResultSize failed: 0x%08X"), static_cast<unsigned int>(hr));
				}

				std::vector<uint8_t> buffer(bufferSize);
				XUserGetTokenAndSignatureData* data = nullptr;

				if (SUCCEEDED(hr))
				{
					hr = XUserGetTokenAndSignatureResult(async, buffer.size(), buffer.data(), &data, nullptr /*bufferUsed*/);

					if (FAILED(hr))
					{
						UE_LOG_ONLINE(Error, TEXT("XUserGetTokenAndSignatureResult failed: 0x%08X"), static_cast<unsigned int>(hr));
					}
				}

				// Tell the party manager we're done
				PartyError err = PartyXblManager::GetSingleton().CompleteGetTokenAndSignatureRequest(
					(UINT_PTR)(async->context),
					SUCCEEDED(hr),
					data ? data->token : nullptr,
					data ? data->signature : nullptr
				);

				if (PARTY_SUCCEEDED(err))
				{
					UE_LOG_ONLINE(Verbose, TEXT("CompleteGetTokenAndSignatureRequest succeeded.\n\tToken: %s\n\tSignature: %s"),
						data && data->token ? *FString(UTF8_TO_TCHAR(data->token)) : TEXT("nullptr"),
						data && data->signature ? *FString(UTF8_TO_TCHAR(data->signature)) : TEXT("nullptr"));
				}
				else
				{
					UE_LOG_ONLINE(Error, TEXT("CompleteGetTokenAndSignatureRequest failed: %hs"), GetXblErrorMessage(err));
				}

				delete async;
			};

			uint64_t xuid = 0;
			err = tokenAndSignatureRequested->localChatUser->GetXboxUserId(&xuid);
			if (PARTY_FAILED(err))
			{
				UE_LOG_ONLINE(Error, TEXT("GetXboxUserId failed: %hs"), GetXblErrorMessage(err));
				break;
			}

			auto& GDKUserMgr = IGDKRuntimeModule::Get();
			const FGDKUserHandle userHandle = GDKUserMgr.GetUserHandleByXUserId(xuid);

			// Start the auth call
			HRESULT hr = XUserGetTokenAndSignatureAsync(
				userHandle,                                             // XUser to query
				tnsOptions,                                             // Option flags
				tokenAndSignatureRequested->method,                     // HTTP method ("GET", "POST")
				tokenAndSignatureRequested->url,                        // Auth url
				static_cast<uint32_t>(headers.size()),                  // Additional header count
				headers.data(),                                         // Additional headers
				tokenAndSignatureRequested->bodySize,                   // Query body size
				tokenAndSignatureRequested->body,                       // Query body
				async
			);

			if (FAILED(hr))
			{
				UE_LOG_ONLINE(Error, TEXT("XUserGetTokenAndSignatureAsync failed: 0x%x"), hr);

				PartyXblManager::GetSingleton().CompleteGetTokenAndSignatureRequest(
					tokenAndSignatureRequested->correlationId,
					false,
					nullptr,
					nullptr
				);

				delete async;
			}
			break;
		}
		}
	}

	err = PartyXblManager::GetSingleton().FinishProcessingStateChanges(count, xblChanges);

	if (UpdateTalkerCrossNetworkPermissionGDK())
	{
		UpdatePermissionsForAllControls();
	}

	if (PARTY_FAILED(err))
	{
		UE_LOG_ONLINE(Error, TEXT("FOnlineVoicePlayFab::TickTalkerPermissionTracking: FinishProcessingStateChanges failed: %hs"), GetXblErrorMessage(err));
	}
}

void FOnlineVoicePlayFab::CleanUpPartyXblManager()
{
	UE_LOG_ONLINE(Verbose, TEXT("FOnlineVoicePlayFab::CleanUpPartyXblManager"));

	if (bPartyXblManagerInitialized)
	{
		PartyError err = PartyXblManager::GetSingleton().Cleanup();
		if (PARTY_FAILED(err))
		{
			UE_LOG_ONLINE(Error, TEXT("PartyXblManager::Cleanup() failed: %hs"), GetXblErrorMessage(err));
		}

		bPartyXblManagerInitialized = false;
	}
}

#endif // OSS_PLAYFAB_GDK_SUPPORT