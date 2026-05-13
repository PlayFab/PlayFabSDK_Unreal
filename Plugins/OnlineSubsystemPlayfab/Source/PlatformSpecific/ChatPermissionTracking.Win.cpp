//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include "HAL/Platform.h"
PRAGMA_DISABLE_UNDEFINED_IDENTIFIER_WARNINGS

#if OSS_PLAYFAB_WIN64
#include "OnlineSessionSettings.h"
#include "PlatformDefines.h"
#include "PlayFabHelpers.h"

#include "OnlineVoiceInterfacePlayFab.h"
#include "OnlineSessionInterfacePlayFab.h"
#include "OnlineSubsystemPlayFab.h"


using namespace Party;

namespace
{
	struct RemoteTalkerOptionsWin
	{
		ECrossNetworkType Type = ECrossNetworkType::DISABLED;
		TMap<FString /*User ID*/, PartyChatPermissionOptions> OptionsMap;
	};

	TMap<FString /*User ID*/, RemoteTalkerOptionsWin> TalkersOptionsWin;
	TMap<FString /*Entity ID*/, FString /*User ID*/> TalkerIdMappingWin;

	FString LocalTalkerUserId;
	bool bLoggedLocalUserIdNotSet = false;

	TArray<FCrossNetworkTalkerPlayFab> CrossNetworkTalkersWin;
	
	bool UpdateTalkerCrossNetworkPermissionWin()
	{
		if (CrossNetworkTalkersWin.Num() == 0)
		{
			return false;
		}

		if (LocalTalkerUserId.IsEmpty())
		{
			if (!bLoggedLocalUserIdNotSet)
			{
				UE_LOG_ONLINE(Verbose, TEXT("Local user id isn't set yet"));
				bLoggedLocalUserIdNotSet = true;
			}
			return false;
		}

		auto CrossNetwork = CrossNetworkTalkersWin[0];

		Party::PartyChatPermissionOptions ChatPermissionMask = PartyChatPermissionOptions::None;
		RemoteTalkerOptionsWin* LocalTalker = TalkersOptionsWin.Find(LocalTalkerUserId);
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
			TalkersOptionsWin.Emplace(LocalTalkerUserId, RemoteTalkerOptionsWin());
			LocalTalker = TalkersOptionsWin.Find(LocalTalkerUserId);
		}

		if (CrossNetwork.Type != ECrossNetworkType::DISABLED)
		{
			ChatPermissionMask = Party::PartyChatPermissionOptions::SendAudio | Party::PartyChatPermissionOptions::ReceiveAudio | Party::PartyChatPermissionOptions::ReceiveText;
		}

		LocalTalker->Type = CrossNetwork.Type;
		LocalTalker->OptionsMap.Emplace(CrossNetwork.RemoteUserId, ChatPermissionMask);

		UE_LOG_ONLINE(Verbose, TEXT("Set voice chat permission %s vs %s as %d, Type %d"), *LocalTalkerUserId, *CrossNetwork.RemoteUserId, ChatPermissionMask, CrossNetwork.Type);

		CrossNetworkTalkersWin.RemoveAt(0, 1);
		return true;
	}
}

void FOnlineVoicePlayFab::AddTalkerIdMapping(const FString& EntityId, const FString& UserId)
{
#if defined(OSS_PLAYFAB_GDK_SUPPORT)
	if (IsNativePlatformSubsystemGDK())
	{
		AddTalkerIdMappingGDK(EntityId, UserId);
		return;
	}
#endif

	TalkerIdMappingWin.Add(EntityId, UserId);
	UE_LOG_ONLINE(Verbose, TEXT("Talker ID Mapping %s to %s"), *UserId, *EntityId);
}

void FOnlineVoicePlayFab::SetTalkerCrossNetworkPermission(ECrossNetworkType VoiceChatType, const FString& RemoteUserId, const FString& PlatformModel)
{
#if defined(OSS_PLAYFAB_GDK_SUPPORT)
	if (IsNativePlatformSubsystemGDK())
	{
		SetTalkerCrossNetworkPermissionGDK(VoiceChatType, RemoteUserId, PlatformModel);
		return;
	}
#endif

	FCrossNetworkTalkerPlayFab CrossNetwork = {VoiceChatType, RemoteUserId, PlatformModel};
	CrossNetworkTalkersWin.Emplace(CrossNetwork);
}

PartyChatPermissionOptions FOnlineVoicePlayFab::GetChatPermissionsForTalker(const FString& LocalId, const FString& RemoteId)
{
#if defined(OSS_PLAYFAB_GDK_SUPPORT)
	if (IsNativePlatformSubsystemGDK())
	{
		return GetChatPermissionsForTalkerGDK(LocalId, RemoteId);
	}
#endif

	RemoteTalkerOptionsWin* AllOptions = nullptr;
	PartyChatPermissionOptions* Options = nullptr;

	UE_LOG_ONLINE(Verbose, TEXT("GetChatPermissionsForTalker %s vs. %s"), *LocalId, *RemoteId);

	AllOptions = TalkersOptionsWin.Find(LocalId);
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

FString FOnlineVoicePlayFab::GetPlatformIdFromEntityId(const FString& EntityId)
{
#if defined(OSS_PLAYFAB_GDK_SUPPORT)
	if (IsNativePlatformSubsystemGDK())
	{
		return GetPlatformIdFromEntityIdGDK(EntityId);
	}
#endif

	UE_LOG_ONLINE(Verbose, TEXT("GetPlatformIdFromEntityId %s"), *EntityId);

	FString* Xuid = TalkerIdMappingWin.Find(EntityId);
	if (Xuid != nullptr)
	{
		return *Xuid;
	}

	UE_LOG_ONLINE(Error, TEXT("Failed to find xuid mapping for %s"), *EntityId);

	return FString();
}

void FOnlineVoicePlayFab::StartTrackingPermissionForTalker(const FString& UserId, bool IsRemote)
{
#if defined(OSS_PLAYFAB_GDK_SUPPORT)
	if (IsNativePlatformSubsystemGDK())
	{
		StartTrackingPermissionForTalkerGDK(UserId, IsRemote);
		return;
	}
#endif

	UE_LOG_ONLINE(Verbose, TEXT("StartTrackingPermissionForTalker %s %s"), *UserId, IsRemote ? TEXT("remote") : TEXT("local"));

	if (!IsRemote)
	{
		LocalTalkerUserId = UserId;
	}
}

void FOnlineVoicePlayFab::StopTrackingPermissionForTalker(const FString& UserId)
{
#if defined(OSS_PLAYFAB_GDK_SUPPORT)
	if (IsNativePlatformSubsystemGDK())
	{
		StopTrackingPermissionForTalkerGDK(UserId);
		return;
	}
#endif

	UE_LOG_ONLINE(Verbose, TEXT("StopTrackingPermissionForTalker %s"), *UserId);

	for (auto& TalkerIdKvPair : TalkerIdMappingWin)
	{
		if (TalkerIdKvPair.Value == UserId)
		{
			TalkerIdMappingWin.Remove(TalkerIdKvPair.Key);
			break;
		}
	}
}

void FOnlineVoicePlayFab::TickTalkerPermissionTracking()
{
#if defined(OSS_PLAYFAB_GDK_SUPPORT)
	if (IsNativePlatformSubsystemGDK())
	{
		TickTalkerPermissionTrackingGDK();
		return;
	}
#endif

	if (UpdateTalkerCrossNetworkPermissionWin())
	{
		UpdatePermissionsForAllControls();
	}
}

#endif // OSS_PLAYFAB_WIN64