//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "OnlineSessionInterfacePlayFab.h"
#include "OnlineSubsystemSessionSettings.h"
#include "OnlineSessionSettings.h"
#include "PlayFabSocketSubsystem.h"
#include "../PlatformSpecific/PlatformDefines.h"
#include "PlayFabHelpers.h"

#include "OnlineSubsystemPlayFab.h"
#include "PlayFabPartyNetwork.h"
#include "OnlineSubsystemPlayFabPrivate.h"

#include "GenericPlatform/GenericPlatformHttp.h"

#define OSS_PLAYFAB_GET_NATIVE_SESSION_INTERFACE IOnlineSubsystem* NativeSubsystem = GetNativeOnlineSubsystem(OSSPlayFab);  IOnlineSessionPtr NativeSessionInterface = NativeSubsystem ? NativeSubsystem->GetSessionInterface() : nullptr; if (NativeSessionInterface)

FPlayFabSessionState::FPlayFabSessionState(FName InSessionName, FNamedOnlineSessionRef InNamedSession, bool bInUsesNativeSession, FOnlineSubsystemPlayFab* InSubsystem)
	: SessionName(InSessionName)
	, NamedSession(InNamedSession)
	, bUsesNativeSession(bInUsesNativeSession)
	, OSSPlayFab(InSubsystem)
{
	check(InSubsystem);
}

FPlayFabSessionState::~FPlayFabSessionState()
{
	OSS_PLAYFAB_GET_NATIVE_SESSION_INTERFACE
	{
		if (OnNativeCreateSessionCompleteDelegateHandle.IsValid())
		{
			NativeSessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(OnNativeCreateSessionCompleteDelegateHandle);
		}
		if (OnNativeUpdateSessionCompleteDelegateHandle.IsValid())
		{
			NativeSessionInterface->ClearOnUpdateSessionCompleteDelegate_Handle(OnNativeUpdateSessionCompleteDelegateHandle);
		}
		if (OnNativeJoinSessionCompleteDelegateHandle.IsValid())
		{
			NativeSessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(OnNativeJoinSessionCompleteDelegateHandle);
		}
	}

	FPlayFabLobbyPtr LobbyInterface = OSSPlayFab->GetPlayFabLobbyInterface();
	if (LobbyInterface.IsValid())
	{
		if (OnUpdateLobbyCompleteDelegate.IsValid())
		{
			LobbyInterface->ClearOnUpdateLobbyCompletedDelegate_Handle(OnUpdateLobbyCompleteDelegate);
		}
		if (OnUpdateSession_MatchmakingDelegateHandle.IsValid())
		{
			LobbyInterface->ClearOnUpdateLobbyCompletedDelegate_Handle(OnUpdateSession_MatchmakingDelegateHandle);
		}
	}

	OSSPlayFab->RemovePartyNetwork(SessionName);
}

FOnlineSessionPlayFab::FOnlineSessionPlayFab(class FOnlineSubsystemPlayFab* InSubsystem) :
	OSSPlayFab(InSubsystem)
{
	check(OSSPlayFab);

	bPlatformUsesNativeSession = ShouldSubsystemUseNativeSession();
#if defined(OSS_PLAYFAB_PLAYSTATION)
	UpdateNativeSessionName();
#endif
#if defined(OSS_PLAYFAB_GDK_SUPPORT)
	if (IsNativePlatformSubsystemGDK())
	{
		RegisterForInvites();
	}
#endif
#if defined(OSS_PLAYFAB_STEAM)
	if (IsNativePlatformSubsystemSteam())
	{
		RegisterForSteamInvites();
	}
#endif
	RegisterForUpdates();
	GenerateCrossNetworkVoiceChatPlatformPermissions();
}

FOnlineSessionPlayFab::~FOnlineSessionPlayFab()
{
#if defined(OSS_PLAYFAB_GDK_SUPPORT)
	if (IsNativePlatformSubsystemGDK())
	{
		UnregisterForInvites();
	}
#endif
#if defined(OSS_PLAYFAB_STEAM)
	if (IsNativePlatformSubsystemSteam())
	{
		UnregisterForSteamInvites();
	}
#endif

	UnregisterForUpdates();
}

TSharedPtr<const FUniqueNetId> FOnlineSessionPlayFab::CreateSessionIdFromString(const FString& SessionIdStr)
{
	if (!SessionIdStr.IsEmpty())
	{
		return FUniqueNetIdPlayFab::Create(SessionIdStr);
	}
	return nullptr;
}

FNamedOnlineSession* FOnlineSessionPlayFab::GetNamedSession(FName SessionName)
{
	FPlayFabSessionStatePtr SessionStatePtr = GetSessionStatePtr(SessionName);
	if (SessionStatePtr.IsValid())
	{
		return &SessionStatePtr->NamedSession.Get();
	}

	return nullptr;
}

void FOnlineSessionPlayFab::RemoveNamedSession(FName SessionName)
{
	FScopeLock ScopeLock(&SessionLock);
	SessionStates.RemoveAll([SessionName](const FPlayFabSessionStateRef& State)
	{
		return State->SessionName == SessionName;
	});
}

bool FOnlineSessionPlayFab::HasPresenceSession()
{
	FScopeLock ScopeLock(&SessionLock);
	for (const FPlayFabSessionStateRef& State : SessionStates)
	{
		if (State->NamedSession->SessionSettings.bUsesPresence)
		{
			return true;
		}
	}

	return false;
}

EOnlineSessionState::Type FOnlineSessionPlayFab::GetSessionState(FName SessionName) const
{
	FPlayFabSessionStatePtr SessionStatePtr = GetSessionStatePtr(SessionName);
	if (SessionStatePtr.IsValid())
	{
		return SessionStatePtr->NamedSession->SessionState;
	}

	return EOnlineSessionState::NoSession;
}

bool FOnlineSessionPlayFab::CreateSession(int32 HostingPlayerControllerIndex, FName SessionName, const FOnlineSessionSettings& NewSessionSettings)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::CreateSession()"));

	bool bSuccess = false;

	if (!IsRunningDedicatedServer())
	{
		IOnlineIdentityPtr Identity = OSSPlayFab->GetIdentityInterface();
		TSharedPtr<const FUniqueNetId> HostingPlayerId = Identity.IsValid()
			? Identity->GetUniquePlayerId(HostingPlayerControllerIndex)
			: nullptr;
		if (!HostingPlayerId.IsValid())
		{
			UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::CreateSession: No unique player ID for controller index %i"), HostingPlayerControllerIndex);
			OnCreateSessionCompleted(SessionName, false, true);
			return false;
		}

		return CreateSession(*HostingPlayerId, SessionName, NewSessionSettings);
	}

	if (NewSessionSettings.bIsLANMatch)
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::CreateSession: OnlineSubsystemPlayFab doe not support LAN sessions"));
		OnCreateSessionCompleted(SessionName, false, true);
		return false;
	}
	
	// Create the NamedSession immediately so it is visible for the duration of the async create flow
	FNamedOnlineSessionRef Session = MakeShared<FNamedOnlineSession, ESPMode::ThreadSafe>(SessionName, NewSessionSettings);
	Session->SessionState = EOnlineSessionState::Creating;
	Session->bHosting = true;
	Session->SessionSettings.BuildUniqueId = GetBuildUniqueId();

	TSharedRef<FOnlineSessionInfoPlayFab> NewSessionInfo = MakeShared<FOnlineSessionInfoPlayFab>();
	NewSessionInfo->SessionName = SessionName;
	Session->SessionInfo = NewSessionInfo;

	// Check for an existing session
	FPlayFabSessionStatePtr SessionStatePtr = TryAddSessionState(SessionName, Session);
	if (!SessionStatePtr.IsValid())
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::CreateSession: Cannot create session '%s': session already exists."), *SessionName.ToString());
		OnCreateSessionCompleted(SessionName, false, true);
		return false;
	}

	// Dedicated servers always use the PlayFab server entity (secret key auth),
	// even if native GDK users are logged in on the same machine
	FOnlineIdentityPlayFabPtr PlayFabIdentity = OSSPlayFab->GetIdentityInterfacePlayFab();
	if (PlayFabIdentity)
	{
		TSharedPtr<FPlayFabUser> Server = PlayFabIdentity->GetServerEntity();
		if (Server.IsValid())
		{
			Session->OwningUserId = FUniqueNetIdPlayFab::Create(Server->GetPlatformUserId());
			Session->LocalOwnerId = Session->OwningUserId;
			UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::CreateSession: Using server entity '%s' as hosting player"), *Server->GetPlatformUserId());
		}
	}

	TSharedPtr<FPlayFabPartyNetwork> SessionNetwork = OSSPlayFab->CreateAndConnectToNetwork(SessionName);
	bSuccess = SessionNetwork.IsValid();

	if (bSuccess)
	{
		SessionStatePtr->NetworkId = SessionNetwork->NetworkId;
		SessionStatePtr->NetworkFlowType = ENetworkFlowType::CreateSession;
	}
	else
	{
		OnCreateSessionCompleted(SessionName, false, false);
	}

	return bSuccess;
}

bool FOnlineSessionPlayFab::CreateSession(const FUniqueNetId& HostingPlayerId, FName SessionName, const FOnlineSessionSettings& NewSessionSettings)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::CreateSession()"));

	bool bSuccess = false;

	if (NewSessionSettings.bIsLANMatch)
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::CreateSession: OnlineSubsystemPlayFab doe not support LAN sessions"));
		OnCreateSessionCompleted(SessionName, false, true);
		return false;
	}

	// Create the NamedSession immediately so it is visible for the duration of the async create flow
	FNamedOnlineSessionRef Session = MakeShared<FNamedOnlineSession, ESPMode::ThreadSafe>(SessionName, NewSessionSettings);
	Session->SessionState = EOnlineSessionState::Creating;
	Session->bHosting = true;
	Session->OwningUserId = HostingPlayerId.AsShared();
	Session->LocalOwnerId = HostingPlayerId.AsShared();
	Session->SessionSettings.BuildUniqueId = GetBuildUniqueId();

	TSharedRef<FOnlineSessionInfoPlayFab> NewSessionInfo = MakeShared<FOnlineSessionInfoPlayFab>();
	NewSessionInfo->SessionName = SessionName;
	Session->SessionInfo = NewSessionInfo;

	// Check for an existing session
	FPlayFabSessionStatePtr SessionStatePtr = TryAddSessionState(SessionName, Session);
	if (!SessionStatePtr.IsValid())
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::CreateSession: Cannot create session '%s': session already exists."), *SessionName.ToString());
		OnCreateSessionCompleted(SessionName, false, true);
		return false;
	}

	TSharedPtr<FPlayFabPartyNetwork> SessionNetwork = OSSPlayFab->CreateAndConnectToNetwork(SessionName);
	bSuccess = SessionNetwork.IsValid();

	if (bSuccess)
	{
		SessionStatePtr->NetworkId = SessionNetwork->NetworkId;
		SessionStatePtr->NetworkFlowType = ENetworkFlowType::CreateSession;
	}
	else
	{
		OnCreateSessionCompleted(SessionName, false, false);
	}

	return bSuccess;
}

void FOnlineSessionPlayFab::OnPartyEndpointCreated(bool bSuccess, const FString& NetworkId, uint16 EndpointID, bool bIsHosting)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnPartyEndpointCreated()"));

    // Find session state for the network ID call the appropriate callback outside of the lock scope.
	FPlayFabSessionStatePtr PlayFabSessionState = nullptr;
	{
		FScopeLock ScopeLock(&SessionLock);
		for (auto& SessionState : SessionStates)
		{
			if (NetworkId == SessionState->NetworkId)
			{
				PlayFabSessionState = SessionState;
				break;
			}
		}
	}

	if (PlayFabSessionState.IsValid())
	{
		switch (PlayFabSessionState->NetworkFlowType)
		{
		case ENetworkFlowType::CreateSession:
			OnCreatePartyEndpoint(bSuccess, bIsHosting, PlayFabSessionState.ToSharedRef());
			break;
		case ENetworkFlowType::Matchmaking:
			OnCreatePartyEndpoint_Matchmaking(bSuccess, bIsHosting, PlayFabSessionState->SessionName, PlayFabSessionState.ToSharedRef());
			break;
		case ENetworkFlowType::JoinSession:
			OnCreatePartyEndpoint_JoinSession(bSuccess, PlayFabSessionState->SessionName);
			break;
		default:
			UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnPartyEndpointCreated: Unexpected flow type for NetworkId '%s'"), *NetworkId);
			break;
		}
	}
	else
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnPartyEndpointCreated: No matching flow for NetworkId '%s'"), *NetworkId);
	}
}

void FOnlineSessionPlayFab::OnCreatePartyEndpoint(bool bSuccess, bool bIsHosting, FPlayFabSessionStateRef SessionState)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnCreatePartyEndpoint()"));

	if (bIsHosting)
	{
		ISocketSubsystem* PlayFabSocketSubsystem = ISocketSubsystem::Get(PLAYFAB_SOCKET_SUBSYSTEM);
		if (bSuccess && OSSPlayFab && PlayFabSocketSubsystem)
		{
			TSharedRef<FInternetAddr> LocalIp = static_cast<FPlayFabSocketSubsystem*>(PlayFabSocketSubsystem)->GetLocalBindAddr(SessionState->SessionName, *GLog);
			if (LocalIp->IsValid())
			{
				TSharedPtr<FPlayFabPartyNetwork> SessionNetwork = OSSPlayFab->GetPartyNetwork(SessionState->SessionName);
				if (SessionNetwork.IsValid())
				{
					FString NetworkIdStr = SessionNetwork->NetworkId;
					FString NetworkDescriptorStr = SessionNetwork->SerializeNetworkDescriptor(SessionNetwork->NetworkDescriptor);
					FString HostConnectInfo = LocalIp->ToString(false);

					SessionState->NamedSession->SessionSettings.Set(SETTING_NETWORK_ID, NetworkIdStr, EOnlineDataAdvertisementType::ViaOnlineService);
					SessionState->NamedSession->SessionSettings.Set(SETTING_NETWORK_DESCRIPTOR, NetworkDescriptorStr, EOnlineDataAdvertisementType::ViaOnlineService);
					SessionState->NamedSession->SessionSettings.Set(SETTING_HOST_CONNECT_INFO, HostConnectInfo, EOnlineDataAdvertisementType::ViaOnlineService);
				}
				else
				{
					UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnCreatePartyEndpoint: Could not find PartyNetwork for NetworkId %s"), *SessionState->NetworkId);
					OnCreateSessionCompleted(SessionState->SessionName, false, false);
                    return;
				}
			}
			else
			{
				UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnCreatePartyEndpoint: LocalHostAddr was invalid"));
			}

			if (!SessionState->NamedSession->OwningUserId.IsValid())
			{
				UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnCreatePartyEndpoint: PlayerId is null, cannot create session"));
				OnCreateSessionCompleted(SessionState->SessionName, false, false);
			}
			else if (!OSSPlayFab->GetPlayFabLobbyInterface()->CreatePlayFabLobby(*SessionState->NamedSession->OwningUserId, SessionState->SessionName, SessionState->NamedSession->SessionSettings))
			{
				UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnCreatePartyEndpoint: Failed to create lobby operation"));
				RemoveNamedSession(SessionState->SessionName);
				OnCreateSessionCompleted(SessionState->SessionName, false, false);
			}
		}
		else
		{
			OnCreateSessionCompleted(SessionState->SessionName, false, false);
		}
	}
}

void FOnlineSessionPlayFab::OnLobbyCreatedAndJoinCompleted(bool fSuccess, FName SessionName)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnLobbyCreatedAndJoinCompleted()"));
	if (fSuccess)
	{
		TryClaimVoiceForSession(SessionName);
	}
	OnCreateSessionCompleted(SessionName, fSuccess, false);
}

bool FOnlineSessionPlayFab::StartSession(FName SessionName)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::StartSession()"));

	FPlayFabSessionStatePtr SessionStatePtr = GetSessionStatePtr(SessionName);
	FNamedOnlineSessionPtr Session = SessionStatePtr.IsValid() ? SessionStatePtr->NamedSession.ToSharedPtr() : nullptr;
	if (!Session.IsValid())
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::StartSession: Can't start an online game for session (%s) that hasn't been created"), *SessionName.ToString());
		TriggerOnStartSessionCompleteDelegates(SessionName, false);
		return false;
	}

	if (Session->SessionState != EOnlineSessionState::Pending &&
		Session->SessionState != EOnlineSessionState::Ended)
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::StartSession: Can't start an online session (%s) in state %s"), *SessionName.ToString(), EOnlineSessionState::ToString(Session->SessionState));
		TriggerOnStartSessionCompleteDelegates(SessionName, false);
		return false;
	}

	Session->SessionState = EOnlineSessionState::InProgress;

	if (SessionStatePtr->bUsesNativeSession)
	{
		OSS_PLAYFAB_GET_NATIVE_SESSION_INTERFACE
		{
			if (NativeSessionInterface->StartSession(ResolveNativeSessionName(SessionName)))
			{
				TriggerOnStartSessionCompleteDelegates(SessionName, true);
				return true;
			}
			else
			{
				UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::StartSession: Start native session (%s) failed"), *ResolveNativeSessionName(SessionName).ToString());
			}
		}
		else
		{
			UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::StartSession: Failed to get native session (%s) interface"), *ResolveNativeSessionName(SessionName).ToString());
		}
	
		TriggerOnStartSessionCompleteDelegates(SessionName, false);
		return false;
	}

	TriggerOnStartSessionCompleteDelegates(SessionName, true);
	return true;
}

bool FOnlineSessionPlayFab::UpdateSession(FName SessionName, FOnlineSessionSettings& UpdatedSessionSettings, bool bShouldRefreshOnlineData /*= false*/)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::UpdateSession()"));

	FPlayFabSessionStatePtr SessionStatePtr = GetSessionStatePtr(SessionName);
	if (!SessionStatePtr.IsValid())
	{
		OSSPlayFab->ExecuteNextTick([this, SessionName]()
		{
			UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::UpdateSession: Unable to update session %s, no session state found"), *SessionName.ToString());
			TriggerOnUpdateSessionCompleteDelegates(SessionName, false);
		});
		return false;
	}

	FPlayFabSessionState& PlayFabSessionState = *SessionStatePtr;
	EOnlineSessionState::Type SessionState = PlayFabSessionState.NamedSession->SessionState;
	if (SessionState <= EOnlineSessionState::Creating || SessionState >= EOnlineSessionState::Destroying)
	{
		OSSPlayFab->ExecuteNextTick([this, SessionName, SessionState]()
		{
			UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::UpdateSession: Unable to update session %s, it is state %s, which may not be updated"), *SessionName.ToString(), EOnlineSessionState::ToString(SessionState));
			TriggerOnUpdateSessionCompleteDelegates(SessionName, false);
		});
		return false;
	}

	if (PlayFabSessionState.OnUpdateLobbyCompleteDelegate.IsValid())
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::UpdateSession: UpdateSession is already in progress. Call UpdateSession again after the current operation is completed."));
		return false;
	}

	PlayFabSessionState.OnUpdateLobbyCompleteDelegate = OSSPlayFab->GetPlayFabLobbyInterface()->AddOnUpdateLobbyCompletedDelegate_Handle(FOnUpdateLobbyCompletedDelegate::CreateRaw(&PlayFabSessionState, &FPlayFabSessionState::OnUpdateLobbyCompleted));
	if (!OSSPlayFab->GetPlayFabLobbyInterface()->UpdateLobby(SessionName, UpdatedSessionSettings))
	{
		UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::UpdateSession: Failed to update session %s"), *SessionName.ToString());
		OSSPlayFab->GetPlayFabLobbyInterface()->ClearOnUpdateLobbyCompletedDelegate_Handle(PlayFabSessionState.OnUpdateLobbyCompleteDelegate);
		return false;
	}

	if (PlayFabSessionState.bUsesNativeSession)
	{
		OSS_PLAYFAB_GET_NATIVE_SESSION_INTERFACE
		{
			FOnlineSessionSettings SessionSettings = UpdatedSessionSettings;
			SessionSettings.Set(SETTING_CONNECTION_STRING, PlayFabSessionState.ConnectionString, EOnlineDataAdvertisementType::ViaOnlineService);
			PlayFabSessionState.OnNativeUpdateSessionCompleteDelegateHandle = NativeSessionInterface->AddOnUpdateSessionCompleteDelegate_Handle(
				FOnUpdateSessionCompleteDelegate::CreateLambda([this, NativeSessionInterface, SessionName](FName CallbackSessionName, bool bNativeSessionUpdated)
					{
						// Each session registers with the same delegate so check that the callback is for the current session first
						if (ResolveNativeSessionName(SessionName) != CallbackSessionName)
						{
							return;
						}
						if (bNativeSessionUpdated == false)
						{
							UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnNativeUpdateSessionComplete: Failed to update native session"));
						}

						FPlayFabSessionStatePtr State = GetSessionStatePtr(SessionName);
						if (State.IsValid())
						{
							NativeSessionInterface->ClearOnUpdateSessionCompleteDelegate_Handle(State->OnNativeUpdateSessionCompleteDelegateHandle);
						}
					}));
			return NativeSessionInterface->UpdateSession(ResolveNativeSessionName(SessionName), SessionSettings, bShouldRefreshOnlineData);
		}
		else
		{
			UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::UpdateSession: Failed to to get native session inteface %s"), *ResolveNativeSessionName(SessionName).ToString());
			return false;
		}
	}

	return true;
}

bool FOnlineSessionPlayFab::EndSession(FName SessionName)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::EndSession()"));

	FPlayFabSessionStatePtr SessionStatePtr = GetSessionStatePtr(SessionName);
	if (SessionStatePtr.IsValid() && SessionStatePtr->bUsesNativeSession)
	{
		OSS_PLAYFAB_GET_NATIVE_SESSION_INTERFACE
		{
			SessionStatePtr->ConnectionString = TEXT("");
			NativeSessionInterface->EndSession(ResolveNativeSessionName(SessionName));
		}
	}

	if (!SessionStatePtr.IsValid())
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::EndSession: Can't end an online game for session (%s) that hasn't been created"), *SessionName.ToString());
		TriggerOnEndSessionCompleteDelegates(SessionName, false);
		return false;
	}

#if defined(OSS_PLAYFAB_STEAM)
	if (IsNativePlatformSubsystemSteam() && !SessionStatePtr->bUsesNativeSession && SessionStatePtr->NamedSession->SessionSettings.bUsesPresence)
	{
		ClearSteamRichPresenceConnect();
	}
#endif

	FNamedOnlineSessionRef Session = SessionStatePtr->NamedSession;
	if (Session->SessionState != EOnlineSessionState::InProgress)
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::EndSession: Can't end session (%s) in state %s"), *SessionName.ToString(), EOnlineSessionState::ToString(Session->SessionState));
		TriggerOnEndSessionCompleteDelegates(SessionName, false);
		return false;
	}

	Session->SessionState = EOnlineSessionState::Ended;
	TriggerOnEndSessionCompleteDelegates(SessionName, true);
	return true;
}

bool FOnlineSessionPlayFab::DestroySession(FName SessionName, const FOnDestroySessionCompleteDelegate& CompletionDelegate /*= FOnDestroySessionCompleteDelegate()*/)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::DestroySession: SessionName:%s"), *SessionName.ToString());

	FPlayFabSessionStatePtr SessionStatePtr = GetSessionStatePtr(SessionName);
	if (SessionStatePtr.IsValid() && SessionStatePtr->bUsesNativeSession)
	{
		OSS_PLAYFAB_GET_NATIVE_SESSION_INTERFACE
		{
			SessionStatePtr->ConnectionString = TEXT("");
			NativeSessionInterface->DestroySession(ResolveNativeSessionName(SessionName));
		}
	}

	if (!SessionStatePtr.IsValid())
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::DestroySession: Can't destroy a null online session (%s)"), *SessionName.ToString());
		OSSPlayFab->ExecuteNextTick([this, SessionName, CompletionDelegate]()
		{
			CompletionDelegate.ExecuteIfBound(SessionName, false);
			TriggerOnDestroySessionCompleteDelegates(SessionName, false);
		});
		return false;
	}

#if defined(OSS_PLAYFAB_STEAM)
	if (IsNativePlatformSubsystemSteam() && !SessionStatePtr->bUsesNativeSession && SessionStatePtr->NamedSession->SessionSettings.bUsesPresence)
	{
		ClearSteamRichPresenceConnect();
	}
#endif

	// Leave the PlayFab Party network for this session
	TeardownSessionNetwork(SessionName);

	SessionStatePtr->NetworkId.Empty();
	SessionStatePtr->NetworkFlowType = ENetworkFlowType::None;

	FNamedOnlineSessionRef Session = SessionStatePtr->NamedSession;
	if (Session->SessionState == EOnlineSessionState::Destroying)
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::DestroySession: Already in process of destroying session (%s)"), *SessionName.ToString());
		OSSPlayFab->ExecuteNextTick([this, SessionName, CompletionDelegate]()
		{
			CompletionDelegate.ExecuteIfBound(SessionName, false);
			TriggerOnDestroySessionCompleteDelegates(SessionName, false);
		});
		return false;
	}

	Session->SessionState = EOnlineSessionState::Destroying;

	// TODO GDK OSS will leave the session in next tick? should PF OSS also use ExecuteNextTick?
	if (!OSSPlayFab->GetPlayFabLobbyInterface()->LeaveLobby(*FUniqueNetIdPlayFab::EmptyId(), SessionName, CompletionDelegate, FOnUnregisterLocalPlayerCompleteDelegate(), true))
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::DestroySession: Failed to destroy the session %s"), *SessionName.ToString());

		OSSPlayFab->ExecuteNextTick([this, SessionName, CompletionDelegate]()
			{
				CompletionDelegate.ExecuteIfBound(SessionName, false);
				TriggerOnDestroySessionCompleteDelegates(SessionName, false);
			});
		return false;
	}

	return true;
}

void FOnlineSessionPlayFab::OnLeaveLobbyCompleted(FName SessionName, bool bSuccess)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnLeaveLobbyCompleted()"));
	
	RemoveNamedSession(SessionName);
	TriggerOnDestroySessionCompleteDelegates(SessionName, bSuccess);
}

void FOnlineSessionPlayFab::OnFindLobbiesCompleted(int32 LocalUserNum, bool bSuccess, TSharedPtr<FOnlineSessionSearch> SearchResults)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnFindLobbiesCompleted()"));

	OSSPlayFab->GetPlayFabLobbyInterface()->ClearOnFindLobbiesCompletedDelegate_Handle(OnFindLobbiesCompletedHandle);
	TriggerOnFindSessionsCompleteDelegates(bSuccess);
}

bool FOnlineSessionPlayFab::IsPlayerInSession(FName SessionName, const FUniqueNetId& UniqueId)
{
	return IsPlayerInSessionImpl(this, SessionName, UniqueId);
}

bool FOnlineSessionPlayFab::StartMatchmaking(const TArray< TSharedRef<const FUniqueNetId> >& LocalPlayers, FName SessionName, const FOnlineSessionSettings& NewSessionSettings, TSharedRef<FOnlineSessionSearch>& SearchSettings)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::StartMatchmaking()"));
	
	if (LocalPlayers.Num() == 0)
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::StartMatchmaking: LocalPlayers was empty. At least one player is required for matchmaking."));
		TriggerOnMatchmakingCompleteDelegates(SessionName, false);
		return false;
	}

	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::StartMatchmaking:CreateMatchMakingTicket()"));

	FNamedOnlineSessionRef NamedSession = MakeShared<FNamedOnlineSession, ESPMode::ThreadSafe>(SessionName, NewSessionSettings);
	NamedSession->HostingPlayerNum = INDEX_NONE;
	FUniqueNetIdPlayFabRef SearchingPlayerNetId = FUniqueNetIdPlayFab::Create(LocalPlayers[0].Get());
	NamedSession->OwningUserId = SearchingPlayerNetId;
	NamedSession->LocalOwnerId = SearchingPlayerNetId;

	FPlayFabSessionStatePtr SessionState = TryAddSessionState(SessionName, NamedSession);
	if (!SessionState.IsValid())
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::StartMatchmaking: Session '%s' already exists."), *SessionName.ToString());
		TriggerOnMatchmakingCompleteDelegates(SessionName, false);
		return false;
	}

	SessionState->bUsesNativeSession = false;
	SessionState->NetworkFlowType = ENetworkFlowType::Matchmaking;

	if (!OSSPlayFab->GetMatchmakingInterface()->CreateMatchMakingTicket(LocalPlayers, SessionName, NewSessionSettings, SearchSettings))
	{
		UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::StartMatchmaking: Failed to CreateMatchMakingTicket"));
		RemoveNamedSession(SessionName);
		TriggerOnMatchmakingCompleteDelegates(SessionName, false);
		return false;
	}

	return true;
}

void FOnlineSessionPlayFab::OnMatchmakingTicketCompleted(bool fSuccess, FName SessionName)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnMatchmakingTicketCompleted()"));
	OnMatchmakingComplete(SessionName, fSuccess);
}

void FOnlineSessionPlayFab::OnCancelMatchmakingComplete(FName SessionName, bool fSuccess)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnCancelMatchmakingComplete()"));
	if (fSuccess)
	{
		RemoveNamedSession(SessionName);
	}
	TriggerOnCancelMatchmakingCompleteDelegates(SessionName, fSuccess);
}

void FOnlineSessionPlayFab::OnMatchmakingComplete(FName SessionName, bool bWasSuccessful)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnMatchmakingComplete()"));

	if (OSSPlayFab == nullptr)
	{
		UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnMatchmakingComplete: OSSPlayFab was null"));
		RemoveNamedSession(SessionName);
		TriggerOnMatchmakingCompleteDelegates(SessionName, false);
		return;
	}

	if (bWasSuccessful == false)
	{
		UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnMatchmakingComplete: Matchmaking was not successful"));
		RemoveNamedSession(SessionName);
		TriggerOnMatchmakingCompleteDelegates(SessionName, false);
		return;
	}

	FPlayFabSessionStatePtr SessionStatePtr = GetSessionStatePtr(SessionName);
	if (SessionStatePtr.IsValid())
	{
		FPlayFabSessionState& PlayFabSessionState = *SessionStatePtr;
		if (PlayFabSessionState.NamedSession->bHosting)
		{
			TSharedPtr<FPlayFabPartyNetwork> SessionNetwork = OSSPlayFab->CreateAndConnectToNetwork(SessionName);

			if (SessionNetwork.IsValid())
			{
				PlayFabSessionState.NetworkId = SessionNetwork->NetworkId;
			}
			else
			{
				UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnMatchmakingComplete: CreateAndConnectToPlayFabPartyNetwork failed"));
				RemoveNamedSession(SessionName);
				TriggerOnMatchmakingCompleteDelegates(SessionName, false);
			}
		}
		else
		{
			//kick off the join logic and give time for the session update
			PlayFabSessionState.RetryJoinNetwork_Count = PlayFabSessionState.RetryJoinNetwork_MaxCount;
		}

		// Matchmaking does not use native interface
		PlayFabSessionState.bUsesNativeSession = false;
	}
	else
	{
		UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnMatchmakingComplete: Session was null"));
		RemoveNamedSession(SessionName);
		TriggerOnMatchmakingCompleteDelegates(SessionName, false);
	}
}

void FOnlineSessionPlayFab::OnOperationComplete_TryJoinNetwork(FPlayFabSessionStateRef SessionState)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnOperationComplete_TryJoinNetwork()"));

	const FName SessionName = SessionState->SessionName;
	const bool bJoinLobbyOperation = (SessionState->NetworkFlowType == ENetworkFlowType::JoinSession);

	if (OSSPlayFab == nullptr)
	{
		UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnOperationComplete_TryJoinNetwork: OSSPlayFab was null"));
		RemoveNamedSession(SessionName);
		if (bJoinLobbyOperation)
		{
			TriggerOnJoinSessionCompleteDelegates(SessionName, EOnJoinSessionCompleteResult::UnknownError);
		}
		else
		{
			TriggerOnMatchmakingCompleteDelegates(SessionName, false);
		}

		return;
	}

	if (FOnlineSessionSettings* SessionSettings = GetSessionSettings(SessionName))
	{
		FString NetworkIdStr;
		FString NetworkDescriptorStr;
		FString HostConnectInfo;
		if (SessionSettings->Get(SETTING_NETWORK_ID, NetworkIdStr) &&
			SessionSettings->Get(SETTING_NETWORK_DESCRIPTOR, NetworkDescriptorStr) &&
			SessionSettings->Get(SETTING_HOST_CONNECT_INFO, HostConnectInfo))
		{
			TSharedPtr<FPlayFabPartyNetwork> SessionNetwork = OSSPlayFab->ConnectToNetwork(SessionName, NetworkIdStr, NetworkDescriptorStr);
			if (!SessionNetwork.IsValid())
			{
				UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnOperationComplete_TryJoinNetwork: ConnectToPlayFabPartyNetwork failed"));
				RemoveNamedSession(SessionName);
				if (bJoinLobbyOperation)
				{
					TriggerOnJoinSessionCompleteDelegates(SessionName, EOnJoinSessionCompleteResult::UnknownError);
				}
				else
				{
					TriggerOnMatchmakingCompleteDelegates(SessionName, false);
				}
			}
			else
			{
				//prevent any retry attempts
				SessionState->RetryJoinNetwork_Count = 0;

				SessionState->NetworkId = SessionNetwork->NetworkId;
				if (bJoinLobbyOperation)
				{
					SessionState->NetworkFlowType = ENetworkFlowType::JoinSession;
				}
				else
				{
					SessionState->NetworkFlowType = ENetworkFlowType::Matchmaking;
				}
			}
		}
		else
		{
			//stop retrying if we are out of attempts
			if (SessionState->RetryJoinNetwork_Count == 0)
			{
				UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnOperationComplete_TryJoinNetwork: Missing required session settings"));
				RemoveNamedSession(SessionName);
				if (bJoinLobbyOperation)
				{
					TriggerOnJoinSessionCompleteDelegates(SessionName, EOnJoinSessionCompleteResult::UnknownError);
				}
				else
				{
					TriggerOnMatchmakingCompleteDelegates(SessionName, false);
				}
			}
		}
	}
	else
	{
		UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnOperationComplete_TryJoinNetwork: SessionSettings was null"));
		RemoveNamedSession(SessionName);
		if (bJoinLobbyOperation)
		{
			TriggerOnJoinSessionCompleteDelegates(SessionName, EOnJoinSessionCompleteResult::UnknownError);
		}
		else
		{
			TriggerOnMatchmakingCompleteDelegates(SessionName, false);
		}
	}
}

void FOnlineSessionPlayFab::OnCreatePartyEndpoint_Matchmaking(bool bSuccess, bool bIsHosting, FName SessionName, FPlayFabSessionStateRef SessionState)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnCreatePartyEndpoint_Matchmaking()"));

	if (bIsHosting)
	{
		bool bHostingSucceeded = false;
		if (FOnlineSessionSettings* SessionSettings = GetSessionSettings(SessionName))
		{
			if (ISocketSubsystem* PlayFabSocketSubsystem = ISocketSubsystem::Get(PLAYFAB_SOCKET_SUBSYSTEM))
			{
				TSharedRef<FInternetAddr> LocalIp = static_cast<FPlayFabSocketSubsystem*>(PlayFabSocketSubsystem)->GetLocalBindAddr(SessionName, *GLog);
				if (LocalIp->IsValid())
				{
					TSharedPtr<FPlayFabPartyNetwork> SessionNetwork = OSSPlayFab->GetPartyNetwork(SessionName);
					if (SessionNetwork.IsValid())
					{
						FString NetworkIdStr = SessionNetwork->NetworkId;
						FString NetworkDescriptorStr = SessionNetwork->SerializeNetworkDescriptor(SessionNetwork->NetworkDescriptor);
						FString HostConnectInfo = LocalIp->ToString(false);

						SessionSettings->Set(SETTING_NETWORK_ID, NetworkIdStr, EOnlineDataAdvertisementType::ViaOnlineService);
						SessionSettings->Set(SETTING_NETWORK_DESCRIPTOR, NetworkDescriptorStr, EOnlineDataAdvertisementType::ViaOnlineService);
						SessionSettings->Set(SETTING_HOST_CONNECT_INFO, HostConnectInfo, EOnlineDataAdvertisementType::ViaOnlineService);

						SessionState->OnUpdateSession_MatchmakingDelegateHandle = OSSPlayFab->GetPlayFabLobbyInterface()->AddOnUpdateLobbyCompletedDelegate_Handle(FOnUpdateLobbyCompletedDelegate::CreateRaw(&SessionState.Get(), &FPlayFabSessionState::OnUpdateSession_Matchmaking));
						if (!OSSPlayFab->GetPlayFabLobbyInterface()->UpdateLobby(SessionName, *SessionSettings))
						{
							UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnCreatePartyEndpoint_Matchmaking: Failed to update Lobby with network descriptor %s"), *SessionName.ToString());
						}
						else
						{
							bHostingSucceeded = true;
						}
					}
					else
					{
						UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnCreatePartyEndpoint_Matchmaking: Could not find PartyNetwork for MatchmakingNetworkId %s"), *SessionState->NetworkId);
					}
				}
				else
				{
					UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnCreatePartyEndpoint_Matchmaking: LocalIp was invalid"));
				}
			}
			else
			{
				UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnCreatePartyEndpoint_Matchmaking: PlayFabSocketSubsystem was null"));
			}
		}
		else
		{
			UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnCreatePartyEndpoint_Matchmaking: SessionSettings was null"));
		}

		if (!bHostingSucceeded)
		{
			RemoveNamedSession(SessionName);
			TriggerOnMatchmakingCompleteDelegates(SessionName, false);
		}
	}
	else
	{
		if (!bSuccess)
		{
			RemoveNamedSession(SessionName);
		}
		else
		{
			TryClaimVoiceForSession(SessionName);
		}

		TriggerOnMatchmakingCompleteDelegates(SessionName, bSuccess);
	}
}

void FOnlineSessionPlayFab::OnCreatePartyEndpoint_JoinSession(bool bSuccess, FName SessionName)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnCreatePartyEndpoint_JoinSession()"));

#if defined(OSS_PLAYFAB_STEAM)
	// Set Steam Rich Presence so friends can join via "Join Game" on Steam overlay.
	// Only set when no native session exists — the native Steam OSS handles its own invite flow.
	FPlayFabSessionStatePtr SessionStatePtr = GetSessionStatePtr(SessionName);
	if (SessionStatePtr.IsValid())
	{
		if (bSuccess && IsNativePlatformSubsystemSteam() && !SessionStatePtr->bUsesNativeSession && SessionStatePtr->NamedSession->SessionSettings.bUsesPresence)
		{
			FOnlineSessionInfoPlayFabPtr SessionInfo = StaticCastSharedPtr<FOnlineSessionInfoPlayFab>(SessionStatePtr->NamedSession->SessionInfo);
			if (SessionInfo.IsValid() && !SessionInfo->ConnectionString.IsEmpty())
			{
				SetSteamRichPresenceConnect(SessionInfo->ConnectionString);
			}
		}
	}
#endif

	if (!bSuccess)
	{
		RemoveNamedSession(SessionName);
	}
	else
	{
		TryClaimVoiceForSession(SessionName);
	}
	
	TriggerOnJoinSessionCompleteDelegates(SessionName, bSuccess ? EOnJoinSessionCompleteResult::Success : EOnJoinSessionCompleteResult::UnknownError);
}

void FPlayFabSessionState::OnUpdateLobbyCompleted(FName InSessionName, bool bWasSuccessful)
{
	if (InSessionName != SessionName)
	{
		return;
	}

	OSSPlayFab->GetPlayFabLobbyInterface()->ClearOnUpdateLobbyCompletedDelegate_Handle(OnUpdateLobbyCompleteDelegate);
	OnUpdateLobbyCompleteDelegate.Reset();

	OSSPlayFab->GetSessionInterfacePlayFab()->TriggerOnUpdateSessionCompleteDelegates(SessionName, bWasSuccessful);
}

void FPlayFabSessionState::OnUpdateSession_Matchmaking(FName InSessionName, bool bWasSuccessful)
{
	if (InSessionName != SessionName)
	{
		return;
	}

	OSSPlayFab->GetPlayFabLobbyInterface()->ClearOnUpdateLobbyCompletedDelegate_Handle(OnUpdateSession_MatchmakingDelegateHandle);
	OnUpdateSession_MatchmakingDelegateHandle.Reset();

	if (bWasSuccessful)
	{
		OSSPlayFab->GetSessionInterfacePlayFab()->TryClaimVoiceForSession(SessionName);
	}

	OSSPlayFab->GetSessionInterfacePlayFab()->TriggerOnMatchmakingCompleteDelegates(SessionName, bWasSuccessful);
}

bool FOnlineSessionPlayFab::CancelMatchmaking(int32 SearchingPlayerNum, FName SessionName)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::CancelMatchmaking(index)"));

	IOnlineIdentityPtr Identity = OSSPlayFab->GetIdentityInterface();
	TSharedPtr<const FUniqueNetId> SearchingPlayerId = Identity.IsValid()
		? Identity->GetUniquePlayerId(SearchingPlayerNum)
		: nullptr;
	if (SearchingPlayerId.IsValid())
	{
		return CancelMatchmaking(*SearchingPlayerId, SessionName);
	}

	UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::CancelMatchmaking: No unique player ID for local user index %i"), SearchingPlayerNum);
	return false;
}

bool FOnlineSessionPlayFab::CancelMatchmaking(const FUniqueNetId& SearchingPlayerId, FName SessionName)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::CancelMatchmaking()"));

	return OSSPlayFab->GetMatchmakingInterface()->CancelMatchmakingTicket(SessionName);
}

bool FOnlineSessionPlayFab::FindSessions(int32 SearchingPlayerNum, const TSharedRef<FOnlineSessionSearch>& SearchSettings)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::FindSessions()"));

	TSharedPtr<const FUniqueNetId> PlayerId;
	IOnlineIdentityPtr IdentityIntPtr = OSSPlayFab->GetIdentityInterface();
	if (!IdentityIntPtr.IsValid())
	{
		return false;
	}

	PlayerId = IdentityIntPtr->GetUniquePlayerId(SearchingPlayerNum);

	if (!PlayerId.IsValid())
	{
		return false;
	}

	return FindSessions(*PlayerId, SearchSettings);
}

bool FOnlineSessionPlayFab::FindSessions(const FUniqueNetId& SearchingPlayerId, const TSharedRef<FOnlineSessionSearch>& SearchSettings)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::FindSessions()"));

	OnFindLobbiesCompletedDelegateHandle = FOnFindLobbiesCompletedDelegate::CreateRaw(this, &FOnlineSessionPlayFab::OnFindLobbiesCompleted);
	OnFindLobbiesCompletedHandle = OSSPlayFab->GetPlayFabLobbyInterface()->AddOnFindLobbiesCompletedDelegate_Handle(OnFindLobbiesCompletedDelegateHandle);

	if (!OSSPlayFab->GetPlayFabLobbyInterface()->FindLobbies(SearchingPlayerId, SearchSettings))
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::FindSessions: Failed to FindLobbies"));
		OSSPlayFab->GetPlayFabLobbyInterface()->ClearOnFindLobbiesCompletedDelegate_Handle(OnFindLobbiesCompletedHandle);
		TriggerOnFindSessionsCompleteDelegates(false);
		return false;
	}

#if defined(OSS_PLAYFAB_WIN64)
	if (!IsNativePlatformSubsystemGDK())
	{
		CachedSearchSettings = MakeShared<FOnlineSessionSearch>(*SearchSettings);
		CachedSearchSettings->SearchState = EOnlineAsyncTaskState::NotStarted;
		if (bPlatformUsesNativeSession)
		{
			OSS_PLAYFAB_GET_NATIVE_SESSION_INTERFACE
			{
				OnNativeFindSessionsCompleteDelegateHandle = NativeSessionInterface->AddOnFindSessionsCompleteDelegate_Handle(
					FOnFindSessionsCompleteDelegate::CreateLambda([this, NativeSessionInterface](bool NativeSessionFindResult)
						{
							if (!NativeSessionFindResult)
							{
								UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnNativeFindSessionComplete: Find Steam native sessions has failure"));
							}
							UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnNativeFindSessionComplete: Num of Search Results: %d"), CachedSearchSettings->SearchResults.Num());
							NativeSessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(OnNativeFindSessionsCompleteDelegateHandle);
						}));
			return NativeSessionInterface->FindSessions(SearchingPlayerId, CachedSearchSettings.ToSharedRef());
			}
		}
	}
#endif

	return true;
}

bool FOnlineSessionPlayFab::FindSessionById(const FUniqueNetId& SearchingUserId, const FUniqueNetId& SessionId, const FUniqueNetId& FriendId, const FOnSingleSessionResultCompleteDelegate& CompletionDelegate)
{
	// Unsupported
	CompletionDelegate.ExecuteIfBound(0, false, FOnlineSessionSearchResult());
	return false;
}

bool FOnlineSessionPlayFab::CancelFindSessions()
{
	// Unsupported
	OSSPlayFab->ExecuteNextTick([this]()
	{
		TriggerOnCancelFindSessionsCompleteDelegates(false);
	});

	return false;
}

bool FOnlineSessionPlayFab::PingSearchResults(const FOnlineSessionSearchResult& SearchResult)
{
	UE_LOG_ONLINE_SESSION(Display, TEXT("FOnlineSessionPlayFab::PingSearchResults: Not implemented"));
	return false;
}

void FOnlineSessionPlayFab::RegisterForUpdates()
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::RegisterForUpdates()"));

	// Register for changes across multiple sessions
	OSSPlayFab->GetPlayFabLobbyInterface()->AddOnLobbyUpdateDelegate_Handle(FOnLobbyUpdateDelegate::CreateRaw(this, &FOnlineSessionPlayFab::OnLobbyUpdate));
	OSSPlayFab->GetPlayFabLobbyInterface()->AddOnLobbyMemberAddedDelegate_Handle(FOnLobbyMemberAddedDelegate::CreateRaw(this, &FOnlineSessionPlayFab::OnLobbyMemberAdded));
	OSSPlayFab->GetPlayFabLobbyInterface()->AddOnLobbyMemberRemovedDelegate_Handle(FOnLobbyMemberRemovedDelegate::CreateRaw(this, &FOnlineSessionPlayFab::OnLobbyMemberRemoved));
	OSSPlayFab->GetPlayFabLobbyInterface()->AddOnLobbyDisconnectedDelegate_Handle(FOnLobbyDisconnectedDelegate::CreateRaw(this, &FOnlineSessionPlayFab::OnLobbyDisconnected));
	OSSPlayFab->GetPlayFabLobbyInterface()->AddOnLobbyCreatedAndJoinCompletedDelegate_Handle(FOnLobbyCreatedAndJoinCompletedDelegate::CreateRaw(this, &FOnlineSessionPlayFab::OnLobbyCreatedAndJoinCompleted));
	OSSPlayFab->GetPlayFabLobbyInterface()->AddOnJoinLobbyCompletedDelegate_Handle(FOnJoinLobbyCompletedDelegate::CreateRaw(this, &FOnlineSessionPlayFab::OnJoinLobbyCompleted));
	OSSPlayFab->GetPlayFabLobbyInterface()->AddOnLeaveLobbyCompletedDelegate_Handle(FOnLeaveLobbyCompletedDelegate::CreateRaw(this, &FOnlineSessionPlayFab::OnLeaveLobbyCompleted));
	OSSPlayFab->GetMatchmakingInterface()->AddOnMatchmakingTicketCompletedDelegate_Handle(FOnMatchmakingTicketCompletedDelegate::CreateRaw(this, &FOnlineSessionPlayFab::OnMatchmakingTicketCompleted));
	OSSPlayFab->GetMatchmakingInterface()->AddOnCancelMatchmakingCompleteDelegate_Handle(FOnCancelMatchmakingCompleteDelegate::CreateRaw(this, &FOnlineSessionPlayFab::OnCancelMatchmakingComplete));
	OSSPlayFab->AddOnPartyEndpointCreatedDelegate_Handle(FOnPartyEndpointCreatedDelegate::CreateRaw(this, &FOnlineSessionPlayFab::OnPartyEndpointCreated));

	if (bPlatformUsesNativeSession)
	{
		OnNativeSessionUserInviteAcceptedDelegate = FOnSessionUserInviteAcceptedDelegate::CreateRaw(this, &FOnlineSessionPlayFab::OnNativeSessionUserInviteAccepted);
	}
}

void FOnlineSessionPlayFab::UnregisterForUpdates()
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::UnregisterForUpdates()"));

	// Clear registered delegates
	OSSPlayFab->GetPlayFabLobbyInterface()->ClearOnLobbyUpdateDelegates(this);
	OSSPlayFab->GetPlayFabLobbyInterface()->ClearOnLobbyMemberAddedDelegates(this);
	OSSPlayFab->GetPlayFabLobbyInterface()->ClearOnLobbyMemberRemovedDelegates(this);
	OSSPlayFab->GetPlayFabLobbyInterface()->ClearOnLobbyDisconnectedDelegates(this);
	OSSPlayFab->GetPlayFabLobbyInterface()->ClearOnLobbyCreatedAndJoinCompletedDelegates(this);
	OSSPlayFab->GetPlayFabLobbyInterface()->ClearOnJoinLobbyCompletedDelegates(this);
	OSSPlayFab->GetPlayFabLobbyInterface()->ClearOnLeaveLobbyCompletedDelegates(this);
	OSSPlayFab->GetMatchmakingInterface()->ClearOnMatchmakingTicketCompletedDelegates(this);
	OSSPlayFab->GetMatchmakingInterface()->ClearOnCancelMatchmakingCompleteDelegates(this);
	OSSPlayFab->ClearOnPartyEndpointCreatedDelegates(this);

	if (bPlatformUsesNativeSession)
	{
		OSS_PLAYFAB_GET_NATIVE_SESSION_INTERFACE
		{
			NativeSessionInterface->ClearOnSessionUserInviteAcceptedDelegates(this);
		}
	}
}

void FOnlineSessionPlayFab::OnLobbyUpdate(FName SessionName, const PFLobbyUpdatedStateChange& StateChange)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnLobbyUpdate()"));

	HRESULT Hr;
	FPlayFabSessionStatePtr SessionStatePtr = GetSessionStatePtr(SessionName);
	if (!SessionStatePtr.IsValid())
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnLobbyUpdate No session found with SessionName:%s!"), *(SessionName.ToString()));
		return;
	}
	
	FNamedOnlineSessionRef ExistingNamedSession = SessionStatePtr->NamedSession;

	bool UpdateHostSetting = false;
	for (uint32 i = 0; i < StateChange.updatedLobbyPropertyCount; ++i)
	{
		const char* updatedLobbyKey = StateChange.updatedLobbyPropertyKeys[i];
		const char* updatedLobbyPropertyValue = nullptr;
		Hr = PFLobbyGetLobbyProperty(StateChange.lobby, updatedLobbyKey, &updatedLobbyPropertyValue);
		if (FAILED(Hr))
		{
			LogMultiplayerErrorWithMessage("PFLobbyGetLobbyProperty", Hr);
			continue;
		}

		const FString UpdatedLobbyKey(UTF8_TO_TCHAR(updatedLobbyKey));

		if (updatedLobbyPropertyValue == nullptr)
		{
			UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnLobbyUpdate Remove Key:%s"), *UpdatedLobbyKey);
			ExistingNamedSession->SessionSettings.Remove(FName(UpdatedLobbyKey));
		}
		else
		{
			const FString UpdatedLobbyPropertyValue(UTF8_TO_TCHAR(updatedLobbyPropertyValue));

			if (UpdatedLobbyKey == TEXT("_flags"))
			{
				int16 SessionSettingsFlags = 0;
				LexFromString(SessionSettingsFlags, *UpdatedLobbyPropertyValue);

				int32 BitShift = 0;
				ExistingNamedSession->SessionSettings.bShouldAdvertise = (SessionSettingsFlags & (1 << BitShift++)) ? true : false;
				ExistingNamedSession->SessionSettings.bAllowJoinInProgress = (SessionSettingsFlags & (1 << BitShift++)) ? true : false;
				ExistingNamedSession->SessionSettings.bIsLANMatch = (SessionSettingsFlags & (1 << BitShift++)) ? true : false;
				ExistingNamedSession->SessionSettings.bIsDedicated = (SessionSettingsFlags & (1 << BitShift++)) ? true : false;
				ExistingNamedSession->SessionSettings.bUsesStats = (SessionSettingsFlags & (1 << BitShift++)) ? true : false;
				ExistingNamedSession->SessionSettings.bAllowInvites = (SessionSettingsFlags & (1 << BitShift++)) ? true : false;
				ExistingNamedSession->SessionSettings.bUsesPresence = (SessionSettingsFlags & (1 << BitShift++)) ? true : false;
				ExistingNamedSession->SessionSettings.bAllowJoinViaPresence = (SessionSettingsFlags & (1 << BitShift++)) ? true : false;
				ExistingNamedSession->SessionSettings.bAllowJoinViaPresenceFriendsOnly = (SessionSettingsFlags & (1 << BitShift++)) ? true : false;
				ExistingNamedSession->SessionSettings.bAntiCheatProtected = (SessionSettingsFlags & (1 << BitShift++)) ? true : false;
				ExistingNamedSession->SessionSettings.bUseLobbiesVoiceChatIfAvailable = (SessionSettingsFlags & (1 << BitShift++)) ? true : false;
			}
			else
			{
				UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnLobbyUpdate Lobby Key:%s, value:%s"), *UpdatedLobbyKey, *UpdatedLobbyPropertyValue);
				ExistingNamedSession->SessionSettings.Set(FName(UpdatedLobbyKey), UpdatedLobbyPropertyValue, EOnlineDataAdvertisementType::ViaOnlineService);
				if (IsHostSetting(FName(UpdatedLobbyKey)))
				{
					UpdateHostSetting = true;
				}
			}
		}
	}

	for (uint32 i = 0; i < StateChange.updatedSearchPropertyCount; ++i)
	{
		const char* updatedSearchKey = StateChange.updatedSearchPropertyKeys[i];
		const char* updatedSearchPropertyValue = nullptr;
		Hr = PFLobbyGetSearchProperty(StateChange.lobby, updatedSearchKey, &updatedSearchPropertyValue);
		if (FAILED(Hr))
		{
			LogMultiplayerErrorWithMessage("PFLobbyGetSearchProperty", Hr);
			continue;
		}

		const FString UpdatedSearchKey(UTF8_TO_TCHAR(updatedSearchKey));

		if (updatedSearchPropertyValue == nullptr)
		{
			UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnLobbyUpdate Remove Key:%s"), *UpdatedSearchKey);
			ExistingNamedSession->SessionSettings.Remove(FName(UpdatedSearchKey));
		}
		else
		{
			const FString UpdatedSearchPropertyValue(UTF8_TO_TCHAR(updatedSearchPropertyValue));

			// return search properties back to session settings
			auto SettingKey = OSSPlayFab->GetPlayFabLobbyInterface()->FindSearchKey(UpdatedSearchKey);
			if (SettingKey)
			{
				UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnLobbyUpdate Search Key:%s, value:%s"), *FString(SettingKey->SettingName), *UpdatedSearchPropertyValue);
				switch (SettingKey->Type)
				{
					case EOnlineKeyValuePairDataType::Bool:
						ExistingNamedSession->SessionSettings.Set(FName(SettingKey->SettingName), *updatedSearchPropertyValue == '1' ? true : false, EOnlineDataAdvertisementType::ViaOnlineService);
						break;
					case EOnlineKeyValuePairDataType::Int32:
						ExistingNamedSession->SessionSettings.Set(FName(SettingKey->SettingName), FCString::Atoi(*UpdatedSearchPropertyValue), EOnlineDataAdvertisementType::ViaOnlineService);
						break;
					case EOnlineKeyValuePairDataType::String:
						ExistingNamedSession->SessionSettings.Set(FName(SettingKey->SettingName), UpdatedSearchPropertyValue, EOnlineDataAdvertisementType::ViaOnlineService);
						break;
				}
				if (IsHostSetting(FName(SettingKey->SettingName)))
				{
					UpdateHostSetting = true;
				}
			}
			else
			{
				UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnLobbyUpdate Search Key:%s, value:%s"), *UpdatedSearchKey, *UpdatedSearchPropertyValue);
				ExistingNamedSession->SessionSettings.Set(FName(UpdatedSearchKey), UpdatedSearchPropertyValue, EOnlineDataAdvertisementType::ViaOnlineService);
			}
		}
	}

	if (StateChange.ownerUpdated || UpdateHostSetting)
	{
		const PFEntityKey* OwnerEntityKeyPtr;
		Hr = PFLobbyGetOwner(StateChange.lobby, &OwnerEntityKeyPtr);
		if (SUCCEEDED(Hr))
		{
			if (OwnerEntityKeyPtr != nullptr)
			{
				if (!SetHostOnSession(SessionName, *OwnerEntityKeyPtr))
				{
					UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnLobbyUpdate invalid owner!"));
				}
			}
			else
			{
				UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnLobbyUpdate owner is removed from the session!"));
			}
		}
		else
		{
			UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnLobbyUpdate failed to GetOwner for the lobby. ErrorCode=[0x%08x], Warning message:%s"), Hr, *GetMultiplayerErrorMessage(Hr));
		}
	}

	if (StateChange.maxMembersUpdated)
	{
		uint32 NewMemberCount;
		Hr = PFLobbyGetMaxMemberCount(StateChange.lobby, &NewMemberCount);
		if (SUCCEEDED(Hr))
		{
			UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnLobbyUpdate max member count updated to :%u"), NewMemberCount);
			ExistingNamedSession->SessionSettings.NumPublicConnections = NewMemberCount;
		}
		else
		{
			UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnLobbyUpdate failed to GetMaxMemberCount for the lobby. ErrorCode=[0x%08x], Warning message:%s"), Hr, *GetMultiplayerErrorMessage(Hr));
		}
	}

	if (StateChange.accessPolicyUpdated)
	{
		PFLobbyAccessPolicy NewAccessPolicy;
		Hr = PFLobbyGetAccessPolicy(StateChange.lobby, &NewAccessPolicy);
		if (SUCCEEDED(Hr))
		{
			UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnLobbyUpdate access policy updated to :%u"), NewAccessPolicy);
			ExistingNamedSession->SessionSettings.bShouldAdvertise = (NewAccessPolicy != PFLobbyAccessPolicy::Private);
		}
		else
		{
			UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnLobbyUpdate failed to GetAccessPolicy for the lobby. ErrorCode=[0x%08x], Warning message:%s"), Hr, *GetMultiplayerErrorMessage(Hr));
		}
	}

	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnLobbyUpdate member update count:%u"), StateChange.memberUpdateCount);
	for (uint32_t i = 0; i < StateChange.memberUpdateCount; ++i)
	{
		const PFLobbyMemberUpdateSummary& MemberUpdate = StateChange.memberUpdates[i];
		const PFEntityKey* MemberEntity = &MemberUpdate.member;		
		const FString* PlatformId = SessionStatePtr->EntityPlatformIdMapping.Find(FString(MemberEntity->id));

		if ((PlatformId != nullptr) && (!PlatformId->IsEmpty()))
		{
			FSessionSettings* MemberSettings = ExistingNamedSession->SessionSettings.MemberSettings.Find(FUniqueNetIdPlayFab::Create(*PlatformId));
			if (!MemberSettings)
			{
				MemberSettings = &ExistingNamedSession->SessionSettings.MemberSettings.Add(FUniqueNetIdPlayFab::Create(*PlatformId), FSessionSettings());
			}

			for (uint32_t j = 0; j < MemberUpdate.updatedMemberPropertyCount; ++j)
			{
				const char* Key = MemberUpdate.updatedMemberPropertyKeys[j];
				const char* Value = nullptr;
				Hr = PFLobbyGetMemberProperty(StateChange.lobby, MemberEntity, Key, &Value);
				if (SUCCEEDED(Hr))
				{
					MemberSettings->Add(FName(Key), FOnlineSessionSetting(Value != nullptr ? FString(UTF8_TO_TCHAR(Value)) : FString(), EOnlineDataAdvertisementType::ViaOnlineService));
					UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnLobbyUpdate Update member property for:%s, Key:%s Value:%s"), *FString(MemberEntity->id), *FString(UTF8_TO_TCHAR(Key)), *FString(UTF8_TO_TCHAR(Value)));
				}
			}
		}
		else
		{
			UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnLobbyUpdate PlatformId not found for Entity:%s!"), *FString(MemberEntity->id));
		}

		// Check if this member's connection status changed and remove them if disconnected
		if (MemberUpdate.connectionStatusUpdated)
		{
			PFLobbyMemberConnectionStatus ConnectionStatus;
			Hr = PFLobbyGetMemberConnectionStatus(StateChange.lobby, MemberEntity, &ConnectionStatus);
			if (SUCCEEDED(Hr) && ConnectionStatus == PFLobbyMemberConnectionStatus::NotConnected)
			{
				UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnLobbyUpdate Member %s is NotConnected, checking if we should force remove."), *FString(MemberEntity->id));

				// Only the lobby owner can force-remove members
				const PFEntityKey* OwnerEntityKeyPtr = nullptr;
				Hr = PFLobbyGetOwner(StateChange.lobby, &OwnerEntityKeyPtr);
				if (SUCCEEDED(Hr) && OwnerEntityKeyPtr != nullptr)
				{
					FOnlineIdentityPlayFabPtr PlayFabIdentityInt = OSSPlayFab->GetIdentityInterfacePlayFab();
					if (PlayFabIdentityInt.IsValid())
					{
						const TArray<PFEntityKey> LocalEntityKeys = PlayFabIdentityInt->GetLocalUserEntityKeys();
						for (const PFEntityKey& LocalEntity : LocalEntityKeys)
						{
							if (FCString::Strcmp(UTF8_TO_TCHAR(LocalEntity.id), UTF8_TO_TCHAR(OwnerEntityKeyPtr->id)) == 0)
							{
								UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnLobbyUpdate Local user is lobby owner, force removing disconnected member %s."), *FString(MemberEntity->id));
								HRESULT ForceRemoveHr = PFLobbyForceRemoveMember(StateChange.lobby, MemberEntity, false, nullptr);
								if (FAILED(ForceRemoveHr))
								{
									UE_LOG_ONLINE_SESSION(Error, TEXT("FOnlineSessionPlayFab::OnLobbyUpdate PFLobbyForceRemoveMember failed. ErrorCode=[0x%08x], Error message:%s"), ForceRemoveHr, *GetMultiplayerErrorMessage(ForceRemoveHr));
								}
								break;
							}
						}
					}
				}
			}
			else if (FAILED(Hr))
			{
				UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnLobbyUpdate PFLobbyGetMemberConnectionStatus failed. ErrorCode=[0x%08x], Error message:%s"), Hr, *GetMultiplayerErrorMessage(Hr));
			}
		}
	}

#if defined(OSS_PLAYFAB_GDK_SUPPORT)
	if (IsNativePlatformSubsystemGDK())
	{
		SetMultiplayerActivityForSession(ExistingNamedSession);
	}
#endif

	TriggerOnSessionSettingsUpdatedDelegates(SessionName, ExistingNamedSession->SessionSettings);
}

void FOnlineSessionPlayFab::OnLobbyMemberAdded(FName SessionName, const PFLobbyMemberAddedStateChange& StateChange)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnLobbyMemberAdded()"));

	FPlayFabSessionStatePtr SessionStatePtr = GetSessionStatePtr(SessionName);
	if (!SessionStatePtr.IsValid())
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnLobbyMemberAdded: No session found with SessionName:%s!"), *(SessionName.ToString()));
		return;
	}
	FNamedOnlineSessionRef ExistingNamedSession = SessionStatePtr->NamedSession;

	const PFEntityKey& EntityKey = StateChange.member;
	
	const char* PlatformIdValue = nullptr;
	HRESULT Hr = PFLobbyGetMemberProperty(StateChange.lobby, &EntityKey, TCHAR_TO_UTF8(*SETTING_PLATFORM_ID), &PlatformIdValue);
	if (FAILED(Hr))
	{
		LogMultiplayerErrorWithMessage("PFLobbyGetMemberProperty", Hr);
		return;
	}

	if (PlatformIdValue == nullptr)
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnLobbyMemberAdded: PlatformIdValue was null"));
		return;
	}

	const char* PlatformModelValue = nullptr;
	Hr = PFLobbyGetMemberProperty(StateChange.lobby, &EntityKey, TCHAR_TO_UTF8(*SETTING_PLATFORM_MODEL), &PlatformModelValue);
	if (FAILED(Hr))
	{
		LogMultiplayerErrorWithMessage("PFLobbyGetMemberProperty", Hr);
		return;
	}

	if (PlatformModelValue == nullptr)
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnLobbyMemberAdded: PlatformModelValue was null"));
		return;
	}
	
	const FString EntityIdStr(UTF8_TO_TCHAR(EntityKey.id));
	const FString PlatformIdStr(UTF8_TO_TCHAR(PlatformIdValue));
	const FString PlatformModelStr(UTF8_TO_TCHAR(PlatformModelValue));

	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnLobbyMemberAdded Id:%s, PlatformId:%s, PlatformModel:%s"), *EntityIdStr, *PlatformIdStr, *PlatformModelStr);
	SessionStatePtr->EntityPlatformIdMapping.Add(EntityIdStr, PlatformIdStr);

	auto VoicePlayFab = StaticCastSharedPtr<FOnlineVoicePlayFab>(OSSPlayFab->GetVoiceInterface());
	if (VoicePlayFab.IsValid())
	{
		VoicePlayFab->AddTalkerIdMapping(EntityIdStr, PlatformIdStr);

		if (ECrossNetworkType* ChatType = VoiceChatPlatforms.Find(PlatformModelStr))
		{
			VoicePlayFab->SetTalkerCrossNetworkPermission(*ChatType, PlatformIdStr, PlatformModelStr);
		}
	}

#if defined(OSS_PLAYFAB_GDK_SUPPORT)
	if (IsNativePlatformSubsystemGDK())
	{
		FOnlineIdentityPlayFabPtr PlayFabIdentityInt = OSSPlayFab ? OSSPlayFab->GetIdentityInterfacePlayFab() : nullptr;
		if (PlayFabIdentityInt.IsValid())
		{
			RecordRecentlyMetPlayer(StateChange.lobby, PlayFabIdentityInt->GetLocalUserEntityKeys(), EntityKey, PlatformIdStr);
		}
		else
		{
			UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnLobbyMemberAdded: Identity Interface is invalid"));
		}

		SetMultiplayerActivityForSession(ExistingNamedSession);
	}
#endif

	const TSharedRef<const FUniqueNetId> MemberAddedNetId = FUniqueNetIdPlayFab::Create(PlatformIdStr);

	if (!IsRunningDedicatedServer() && IsVoiceSession(SessionName))
	{
		RegisterVoice(*MemberAddedNetId);
	}

	TriggerOnSessionParticipantJoinedDelegates(SessionName, *MemberAddedNetId);
}

void FOnlineSessionPlayFab::OnLobbyMemberRemoved(FName SessionName, const PFLobbyMemberRemovedStateChange& StateChange)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnLobbyMemberRemoved()"));

	FPlayFabSessionStatePtr SessionStatePtr = GetSessionStatePtr(SessionName);
	if (!SessionStatePtr.IsValid())
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnLobbyMemberRemoved: No session found with SessionName:%s!"), *(SessionName.ToString()));
		return;
	}
	FNamedOnlineSessionRef ExistingNamedSession = SessionStatePtr->NamedSession;
	
	const PFEntityKey& MemberRemovedEntity = StateChange.member;
	const FString MemberRemovedEntityIdStr(UTF8_TO_TCHAR(MemberRemovedEntity.id));
	const FString MemberRemovedEntityTypeStr(UTF8_TO_TCHAR(MemberRemovedEntity.type));
	const FString* PlatformId = SessionStatePtr->EntityPlatformIdMapping.Find(MemberRemovedEntityIdStr);
	if (PlatformId != nullptr && !PlatformId->IsEmpty())
	{
		UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnLobbyMemberRemoved Id:%s, Type:%s PlatformId:%s"), *MemberRemovedEntityIdStr, *MemberRemovedEntityTypeStr, **PlatformId);
		const TSharedRef<const FUniqueNetId> MemberRemovedNetId = FUniqueNetIdPlayFab::Create(**PlatformId);
		SessionStatePtr->EntityPlatformIdMapping.Remove(MemberRemovedEntityIdStr);

		if (!IsRunningDedicatedServer() && IsVoiceSession(SessionName))
		{
			UnregisterVoice(*MemberRemovedNetId);
		}

		TriggerOnSessionParticipantLeftDelegates(SessionName, *MemberRemovedNetId, EOnSessionParticipantLeftReason::Left);
	}
	else
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnLobbyMemberRemoved failed to get PlatformId for Entity:%s!"), *MemberRemovedEntityIdStr);
	}

#if defined(OSS_PLAYFAB_GDK_SUPPORT)
	if (IsNativePlatformSubsystemGDK())
	{
		SetMultiplayerActivityForSession(ExistingNamedSession);
	}
#endif
}

void FOnlineSessionPlayFab::OnLobbyDisconnected(FName SessionName)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnLobbyDisconnected SessionName:%s"), *(SessionName.ToString()));

	FPlayFabSessionStatePtr SessionStatePtr = GetSessionStatePtr(SessionName);
	if (SessionStatePtr.IsValid())
	{
#if defined(OSS_PLAYFAB_STEAM)
		if (IsNativePlatformSubsystemSteam() && !SessionStatePtr->bUsesNativeSession && SessionStatePtr->NamedSession->SessionSettings.bUsesPresence)
		{
			ClearSteamRichPresenceConnect();
		}
#endif

		// Disconnect from the network and remove the session state then notify the game that the connection was lost.
		TeardownSessionNetwork(SessionName);

		RemoveNamedSession(SessionName);
		TriggerOnSessionFailureDelegates(*FUniqueNetIdPlayFab::EmptyId(), ESessionFailure::ServiceConnectionLost);
		UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnLobbyDisconnected SessionName:%s disconnected due to ServiceConnectionLost"), *(SessionName.ToString()));
	}


	// NOTE: This implmentation is based on the assumption that we only have one lobby.
	if (OnSessionsRemovedDelegate.IsBound())
	{
		OnSessionsRemovedDelegate.Execute();
		OnSessionsRemovedDelegate.Unbind();
	}
}

bool FOnlineSessionPlayFab::SetHostOnSession(FName SessionName, const PFEntityKey& HostEntityKey)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::SetHostOnSession()"));

	FPlayFabSessionStatePtr SessionStatePtr = GetSessionStatePtr(SessionName);
	if (!SessionStatePtr.IsValid())
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::SetHostOnSession No session found with SessionName: %s!"), *(SessionName.ToString()));
		return false;
	}
	FNamedOnlineSessionRef ExistingNamedSession = SessionStatePtr->NamedSession;

	if (FCString::Strcmp(UTF8_TO_TCHAR(HostEntityKey.type), UTF8_TO_TCHAR(ENTITY_TYPE_TITLE_PLAYER)) != 0)
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::SetHostOnSession owner type is not title_player_account: %s!"), UTF8_TO_TCHAR(HostEntityKey.type));
	}

	IOnlineIdentityPtr IdentityIntPtr = OSSPlayFab->GetIdentityInterface();
	if (!IdentityIntPtr.IsValid())
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::SetHostOnSession Identity Interface is invalid"));
		return false;
	}	

	FString* HostPlatformId = SessionStatePtr->EntityPlatformIdMapping.Find(FString(HostEntityKey.id));
	if (HostPlatformId == nullptr)
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::SetHostOnSession couldn't find a new lobby owner in the entity mapping cache!"));
		return false;
	}

	FString PlayerNickname;
	ExistingNamedSession->SessionSettings.Get(SETTING_HOST_NICKNAME, PlayerNickname);
	if (PlayerNickname.IsEmpty())
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::SetHostOnSession: session owner nickname is not found in session %s for player with ID %s"), *SessionName.ToString(), *(*HostPlatformId));
	}
	else
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::SetHostOnSession: session owner nickname is %s"), *PlayerNickname);
	}

	FUniqueNetIdPtr NativePlatformId;
	for (int32 i = 0; i < MAX_LOCAL_PLAYERS; ++i)
	{
		TSharedPtr<const FUniqueNetId> NativeId = IdentityIntPtr->GetUniquePlayerId(i);
		if (NativeId.IsValid() && NativeId->ToString() == *HostPlatformId)
		{
			NativePlatformId = NativeId;
			break;
		}
	}

	if (NativePlatformId.IsValid())
	{
		ExistingNamedSession->OwningUserId = NativePlatformId;
		ExistingNamedSession->LocalOwnerId = NativePlatformId;
	}
	else
	{
		ExistingNamedSession->OwningUserId = FUniqueNetIdPlayFab::Create(*HostPlatformId);
		ExistingNamedSession->LocalOwnerId = ExistingNamedSession->OwningUserId->AsShared();
	}
	ExistingNamedSession->OwningUserName = PlayerNickname;

	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::SetHostOnSession set host updated:%s"), *ExistingNamedSession->OwningUserId->ToString());

	FOnlineIdentityPlayFab* PlayFabIdentityInt = static_cast<FOnlineIdentityPlayFab*>(IdentityIntPtr.Get());
	TSharedPtr<FPlayFabUser> LocalUser = PlayFabIdentityInt->GetPartyLocalUserFromPlatformIdString(*HostPlatformId);

	if (LocalUser == nullptr)
	{
		UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::SetHostOnSession Identity Interface's GetPartyLocalUserFromPlatformId returned empty user. Local user is not the host."));
	}
	else
	{
		ExistingNamedSession->bHosting = true;
	}

	return true;
}

bool FOnlineSessionPlayFab::JoinSession_PlayFabInternal(int32 ControllerIndex, TSharedPtr<const FUniqueNetId> UserId, FName SessionName, const FOnlineSessionSearchResult& DesiredSession)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::JoinSession_PlayFabInternal()"));

	TSharedPtr<const FUniqueNetId> PlayerId;
	if (ControllerIndex != INDEX_NONE)
	{
		IOnlineIdentityPtr IdentityIntPtr = OSSPlayFab->GetIdentityInterface();
		if (IdentityIntPtr.IsValid())
		{
			PlayerId = IdentityIntPtr->GetUniquePlayerId(ControllerIndex);
			if (!PlayerId.IsValid())
			{
				TriggerOnJoinSessionCompleteDelegates(SessionName, EOnJoinSessionCompleteResult::UnknownError);
				return false;
			}
		}
	}
	else if (UserId.IsValid())
	{
		PlayerId = UserId;
	}
	else
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::JoinSession_PlayFabInternal: invalid data to join the session"));
		TriggerOnJoinSessionCompleteDelegates(SessionName, EOnJoinSessionCompleteResult::UnknownError);
		return false;
	}

	FNamedOnlineSessionRef NamedSession = MakeShared<FNamedOnlineSession, ESPMode::ThreadSafe>(SessionName, DesiredSession.Session);
	NamedSession->HostingPlayerNum = INDEX_NONE;
	NamedSession->OwningUserId = PlayerId;
	NamedSession->LocalOwnerId = PlayerId;

	// work out if we're already in the session of this name or not
	FPlayFabSessionStatePtr SessionStatePtr = TryAddSessionState(SessionName, NamedSession);
	if (!SessionStatePtr.IsValid())
	{
		FPlayFabSessionStatePtr ExistingState = GetSessionStatePtr(SessionName);
		if (ExistingState.IsValid())
		{
			// Check if we're trying to join a different session of this same type while in a different session (different than joining the same session multiple times)
			const FString ExistingSessionId(ExistingState->NamedSession->GetSessionIdStr());
			const FString NewSessionId(DesiredSession.GetSessionIdStr());

			if (ExistingSessionId == NewSessionId)
			{
				UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::JoinSession_PlayFabInternal: Join session failed; session (%s) already exists, can't join twice"), *SessionName.ToString());
			}
			else
			{
				UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::JoinSession_PlayFabInternal: Join session failed; already in session of type %s, you must leave session %s before joining %s"), *SessionName.ToString(), *ExistingSessionId, *NewSessionId);
			}
		}

		TriggerOnJoinSessionCompleteDelegates(SessionName, EOnJoinSessionCompleteResult::AlreadyInSession);
		return false;
	}

	if (!OSSPlayFab->GetPlayFabLobbyInterface()->JoinLobby(*PlayerId, SessionName, DesiredSession))
	{
		UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::JoinSession_PlayFabInternal: Failed to JoinLobby"));
		RemoveNamedSession(SessionName);
		TriggerOnJoinSessionCompleteDelegates(SessionName, EOnJoinSessionCompleteResult::UnknownError);
		return false;
	}

	return true;
}

bool FOnlineSessionPlayFab::JoinSession(int32 ControllerIndex, FName SessionName, const FOnlineSessionSearchResult& DesiredSession)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::JoinSession()"));

	bool bSuccess = JoinSession_PlayFabInternal(ControllerIndex, nullptr, SessionName, DesiredSession);
	if (bSuccess == false)
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::JoinSession: Failed to join session"));
		TriggerOnJoinSessionCompleteDelegates(SessionName, EOnJoinSessionCompleteResult::UnknownError);
		return false;
	}

	FPlayFabSessionStatePtr SessionStatePtr = GetSessionStatePtr(SessionName);
	if (SessionStatePtr.IsValid() && SessionStatePtr->bUsesNativeSession)
	{
		OSS_PLAYFAB_GET_NATIVE_SESSION_INTERFACE
		{
			// Check if the session has native session info before trying to join the native session.
			// Server lobbies (e.g., created via PFMultiplayerCreateAndClaimServerLobby) won't have
			// native session properties, so we skip the native join for dedicated servers.
			// For clients, a missing native session ID is unexpected and treated as an error.
			bool bHasNativeSession = false;
			if (DesiredSession.Session.SessionInfo.IsValid() &&
				DesiredSession.Session.SessionInfo->GetSessionId().GetType() == PLAYFAB_SUBSYSTEM)
			{
				FOnlineSessionInfoPlayFabPtr PlayFabSessionInfo = StaticCastSharedPtr<FOnlineSessionInfoPlayFab>(DesiredSession.Session.SessionInfo);
				if (PlayFabSessionInfo.IsValid())
				{
					const FString NativeSessionIdStr = PlayFabSessionInfo->GetNativeSessionIdString();
					bHasNativeSession = !NativeSessionIdStr.IsEmpty();
				}
			}

			if (!bHasNativeSession)
			{
				if (IsRunningDedicatedServer())
				{
					UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::JoinSession: No native session ID in lobby properties, skipping native session join (dedicated server)"));
				}
				else
				{
					// No native session exists (e.g. server-created lobby). Proceed with PlayFab-only join.
					UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::JoinSession: No native session ID found, proceeding without native session (server lobby)"));
					SessionStatePtr->bUsesNativeSession = false;
				}
			}

			if (bHasNativeSession)
			{
				FPlayFabSessionState& PlayFabSessionState = *SessionStatePtr;
				PlayFabSessionState.OnNativeJoinSessionCompleteDelegateHandle = NativeSessionInterface->AddOnJoinSessionCompleteDelegate_Handle(
					FOnJoinSessionCompleteDelegate::CreateLambda([this, NativeSessionInterface, SessionName](FName CallbackSessionName, EOnJoinSessionCompleteResult::Type NativeSessionJoinedResult)
						{
							// Each session registers with the same delegate so check that the callback is for the current session first
							if (ResolveNativeSessionName(SessionName) != CallbackSessionName)
							{
								return;
							}
							if (NativeSessionJoinedResult != EOnJoinSessionCompleteResult::Success)
							{
								UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnNativeJoinSessionComplete: Failed to join native session due to %s"), LexToString(NativeSessionJoinedResult));
							}

							FPlayFabSessionStatePtr State = GetSessionStatePtr(SessionName);
							if (State.IsValid())
							{
								NativeSessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(State->OnNativeJoinSessionCompleteDelegateHandle);
							}
						}));
				bool bNativeJoinSuccess = NativeSessionInterface->JoinSession(ControllerIndex, ResolveNativeSessionName(SessionName), DesiredSession);
				if (!bNativeJoinSuccess)
				{
					RemoveNamedSession(SessionName);
				}
				return bNativeJoinSuccess;
			}
		}
		else
		{
			UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::JoinSession: Failed to get native session (%s) interface"), *ResolveNativeSessionName(SessionName).ToString());
			RemoveNamedSession(SessionName);
			return false;
		}
	}

	return true;
}

bool FOnlineSessionPlayFab::JoinSession(const FUniqueNetId& UserId, FName SessionName, const FOnlineSessionSearchResult& DesiredSession)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::JoinSession()"));

	bool bSuccess = JoinSession_PlayFabInternal(INDEX_NONE, UserId.AsShared(), SessionName, DesiredSession);
	if (bSuccess == false)
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::JoinSession: Failed to join session"));
		TriggerOnJoinSessionCompleteDelegates(SessionName, EOnJoinSessionCompleteResult::UnknownError);
		return false;
	}

	FPlayFabSessionStatePtr SessionStatePtr = GetSessionStatePtr(SessionName);
	if (SessionStatePtr.IsValid() && SessionStatePtr->bUsesNativeSession)
	{
		FPlayFabSessionState& PlayFabSessionState = *SessionStatePtr;
		OSS_PLAYFAB_GET_NATIVE_SESSION_INTERFACE
		{
			// Determine if DesiredSession.Session.SessionInfo is type of FOnlineSessionInfoPlayfab.
			// If yes, meaning this call triggered after FindSessions(), othewise, this call is triggered
			// by invitation from native layer.
			if (DesiredSession.Session.SessionInfo->GetSessionId().GetType() == PLAYFAB_SUBSYSTEM)
			{
				FOnlineSessionInfoPlayFabPtr PlayFabSessionInfo = StaticCastSharedPtr<FOnlineSessionInfoPlayFab>(DesiredSession.Session.SessionInfo);
				if (PlayFabSessionInfo.IsValid())
				{
#if defined(OSS_PLAYFAB_PLAYSTATION)
					if (PlayFabSessionInfo->GetNativePlatform() != PLATFORM_MODEL_SONY)
					{
						// The host is a not a PlayStation player and not joining host's native session is expected.
						UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::JoinSession: Won't join a native session which is hosted by the player from different platform."));
						PlayFabSessionState.bUsesNativeSession = false;
						return true;
					}
					const FString SessionIdString(PlayFabSessionInfo->GetNativeSessionIdString());
					if (!SessionIdString.IsEmpty())
					{
						if (FUniqueNetIdPtr SessionId = NativeSessionInterface->CreateSessionIdFromString(SessionIdString))
						{
							bSuccess = NativeSessionInterface->FindSessionById(UserId, *SessionId, *CreateNativeNetIdPtr(), TEXT(""), FOnSingleSessionResultCompleteDelegate::CreateLambda([this, &UserId, SessionName, NativeSessionInterface, &bSuccess](int32, bool bWasSuccessful, const FOnlineSessionSearchResult& SearchResult)
								{
									if (bWasSuccessful)
									{
										bSuccess = NativeSessionInterface->JoinSession(UserId, NativeSessionName, SearchResult);
										if (!bSuccess)
										{
											UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::JoinSession: Found Playstation native session but failed to join it"));
										}
									}
									else
									{
										UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::JoinSession: Failed to find native session"));
										bSuccess = false;
									}
								}));
						}
						else
						{
							UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::JoinSession: Failed to create Playstation session from string %s"), SessionIdString.IsEmpty() ? TEXT("nullptr") : *SessionIdString);
							bSuccess = false;
						}
					}
					else
					{
						UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::JoinSession: SessionIdString is empty"));
						bSuccess = false;
					}
#elif defined(OSS_PLAYFAB_WIN64)
					if (!IsNativePlatformSubsystemGDK())
					{
						if (PlayFabSessionInfo->GetNativePlatform() != PLATFORM_MODEL_WIN64)
						{
							// The host is a not a Steam player and not joining host's native session is expected.
							UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::JoinSession: Won't join a native session which is hosted by the player from different platform."));
							PlayFabSessionState.bUsesNativeSession = false;
							return true;
						}
						const FString SessionIdString(PlayFabSessionInfo->GetNativeSessionIdString());
						if (!SessionIdString.IsEmpty())
						{
							const FOnlineSessionSearchResult* NativeDesiredSession = nullptr;
							for (auto SearchResult : CachedSearchSettings->SearchResults)
							{
								if (SearchResult.Session.GetSessionIdStr() == SessionIdString)
								{
									NativeDesiredSession = &SearchResult;
									break;
								}
							}
							if (!NativeDesiredSession)
							{
								UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::JoinSession: Failed to find Steam session with sessionId=%s"), *SessionIdString);
								bSuccess = false;
							}
							else
							{
								PlayFabSessionState.OnNativeJoinSessionCompleteDelegateHandle = NativeSessionInterface->AddOnJoinSessionCompleteDelegate_Handle(
									FOnJoinSessionCompleteDelegate::CreateLambda([this, NativeSessionInterface, SessionName](FName CallbackSessionName, EOnJoinSessionCompleteResult::Type NativeSessionJoinedResult)
										{
											// Each session registers with the same delegate so check that the callback is for the current session first
											if (ResolveNativeSessionName(SessionName) != CallbackSessionName)
											{
												return;
											}

											if (NativeSessionJoinedResult != EOnJoinSessionCompleteResult::Success)
											{
												UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnNativeJoinSessionComplete: Failed to join native session due to %s"), LexToString(NativeSessionJoinedResult));
											}
											FPlayFabSessionStatePtr State = GetSessionStatePtr(SessionName);
											if (State.IsValid())
											{
												NativeSessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(State->OnNativeJoinSessionCompleteDelegateHandle);
											}
										}));
								bSuccess = NativeSessionInterface->JoinSession(UserId, ResolveNativeSessionName(SessionName), *NativeDesiredSession);
							}
						}
						else
						{
							UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::JoinSession: SessionIdString is empty"));
							bSuccess = false;
						}
					}
#endif // !OSS_PLAYFAB_PLAYSTATION
				}
				else
				{
					UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::JoinSession: PlayFabSessionInfo was invalid"));
					bSuccess = false;
				}
				if (!bSuccess)
				{
					RemoveNamedSession(SessionName);
				}
				return bSuccess;
			}
			else
			{
				// This call is triggered by invitation from native layer.
				PlayFabSessionState.OnNativeJoinSessionCompleteDelegateHandle = NativeSessionInterface->AddOnJoinSessionCompleteDelegate_Handle(
					FOnJoinSessionCompleteDelegate::CreateLambda([this, NativeSessionInterface, SessionName](FName CallbackSessionName, EOnJoinSessionCompleteResult::Type NativeSessionJoinedResult)
						{
							// Each session registers with the same delegate so check that the callback is for the current session first
							if (ResolveNativeSessionName(SessionName) != CallbackSessionName)
							{
								return;
							}
							if (NativeSessionJoinedResult != EOnJoinSessionCompleteResult::Success)
							{
								UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnNativeJoinSessionComplete: Failed to join native session due to %s"), LexToString(NativeSessionJoinedResult));
							}

							FPlayFabSessionStatePtr State = GetSessionStatePtr(SessionName);
							if (State.IsValid())
							{
								NativeSessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(State->OnNativeJoinSessionCompleteDelegateHandle);
							}
						}));
				bool bNativeJoinSuccess = NativeSessionInterface->JoinSession(UserId, ResolveNativeSessionName(SessionName), DesiredSession);
				if (!bNativeJoinSuccess)
				{
					RemoveNamedSession(SessionName);
				}
				return bNativeJoinSuccess;
			}
		}
		else
		{
			UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::JoinSession: Failed to get native session (%s) interface"), *ResolveNativeSessionName(SessionName).ToString());
			RemoveNamedSession(SessionName);
			return false;
		}

	}

	return true;
}

void FOnlineSessionPlayFab::OnJoinLobbyCompleted(FName InSessionName, EOnJoinSessionCompleteResult::Type Result)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnJoinLobbyCompleted()"));

	FPlayFabSessionStatePtr PlayFabSessionState = GetSessionStatePtr(InSessionName);
	if (!PlayFabSessionState.IsValid())
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnJoinLobbyCompleted: No session state found for session %s"), *InSessionName.ToString());
		TriggerOnJoinSessionCompleteDelegates(InSessionName, EOnJoinSessionCompleteResult::UnknownError);
		return;
	}

	//kick off the join logic and give time for the session update
	PlayFabSessionState->NetworkFlowType = ENetworkFlowType::JoinSession;
	PlayFabSessionState->RetryJoinNetwork_Count = PlayFabSessionState->RetryJoinNetwork_MaxCount;

	if (Result != EOnJoinSessionCompleteResult::Success && Result != EOnJoinSessionCompleteResult::AlreadyInSession)
	{
		// Leave the PlayFab Party network for this session
		TeardownSessionNetwork(InSessionName);
		
		RemoveNamedSession(InSessionName);
		TriggerOnJoinSessionCompleteDelegates(InSessionName, Result);
	}
}

bool FOnlineSessionPlayFab::FindFriendSession(int32 LocalUserNum, const FUniqueNetId& Friend)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::FindFriendSession()"));

	TSharedPtr<const FUniqueNetId> PlayerId;
	IOnlineIdentityPtr IdentityIntPtr = OSSPlayFab->GetIdentityInterface();
	if (!IdentityIntPtr.IsValid())
	{
		return false;
	}

	PlayerId = IdentityIntPtr->GetUniquePlayerId(LocalUserNum);
	if (!PlayerId.IsValid())
	{
		return false;
	}

	return FindFriendSession(*PlayerId, Friend);
}

bool FOnlineSessionPlayFab::FindFriendSession(const FUniqueNetId& LocalUserId, const FUniqueNetId& Friend)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::FindFriendSession()"));

	OnFindFriendLobbiesCompletedHandle = OSSPlayFab->GetPlayFabLobbyInterface()->AddOnFindLobbiesCompletedDelegate_Handle(FOnFindLobbiesCompletedDelegate::CreateRaw(this, &FOnlineSessionPlayFab::OnFindFriendLobbiesCompleted));

	if (!OSSPlayFab->GetPlayFabLobbyInterface()->FindFriendLobbies(LocalUserId))
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::FindFriendSession: Failed!"));
		OSSPlayFab->GetPlayFabLobbyInterface()->ClearOnFindLobbiesCompletedDelegate_Handle(OnFindFriendLobbiesCompletedHandle);
		TriggerOnFindFriendSessionCompleteDelegates(-1, false, TArray<FOnlineSessionSearchResult>());
		return false;
	}

	return true;
}

bool FOnlineSessionPlayFab::FindFriendSession(const FUniqueNetId& LocalUserId, const TArray<TSharedRef<const FUniqueNetId>>& FriendList)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::FindFriendSession()"));

	IOnlineIdentityPtr IdentityIntPtr = OSSPlayFab->GetIdentityInterface();
	if (!IdentityIntPtr.IsValid())
	{
		return false;
	}
	int32 LocalUserNum = IdentityIntPtr->GetPlatformUserIdFromUniqueNetId(LocalUserId);
	TriggerOnFindFriendSessionCompleteDelegates(LocalUserNum, false, TArray<FOnlineSessionSearchResult>());

	return false;
}

void FOnlineSessionPlayFab::OnFindFriendLobbiesCompleted(int32 LocalUserNum, bool bSuccess, TSharedPtr<FOnlineSessionSearch> SearchResults)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnFindFriendLobbiesCompleted()"));

	OSSPlayFab->GetPlayFabLobbyInterface()->ClearOnFindLobbiesCompletedDelegate_Handle(OnFindFriendLobbiesCompletedHandle);
	TriggerOnFindFriendSessionCompleteDelegates(LocalUserNum, bSuccess, SearchResults->SearchResults);
}

bool FOnlineSessionPlayFab::SendSessionInviteToFriend(int32 LocalUserNum, FName SessionName, const FUniqueNetId& Friend)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::SendSessionInviteToFriend()"));

	FOnlineIdentityPlayFabPtr PlayFabIdentityInt = OSSPlayFab ? OSSPlayFab->GetIdentityInterfacePlayFab() : nullptr;
	if (PlayFabIdentityInt.IsValid())
	{
		TSharedPtr<const FUniqueNetId> PlayerId = PlayFabIdentityInt->GetUniquePlayerId(LocalUserNum);
		if (PlayerId.IsValid())
		{
			return SendSessionInviteToFriend(*PlayerId, SessionName, Friend);
		}
	}

	return false;
}

bool FOnlineSessionPlayFab::SendSessionInviteToFriend(const FUniqueNetId& LocalUserId, FName SessionName, const FUniqueNetId& Friend)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::SendSessionInviteToFriend()"));

	if (Friend.IsValid())
	{
		TArray< TSharedRef<const FUniqueNetId> > Friends;
		Friends.Add(Friend.AsShared());
		return SendInvite(LocalUserId, SessionName, Friends);
	}

	return false;
}

bool FOnlineSessionPlayFab::SendSessionInviteToFriends(int32 LocalUserNum, FName SessionName, const TArray< TSharedRef<const FUniqueNetId> >& Friends)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::SendSessionInviteToFriends()"));

	FOnlineIdentityPlayFabPtr PlayFabIdentityInt = OSSPlayFab ? OSSPlayFab->GetIdentityInterfacePlayFab() : nullptr;
	if (PlayFabIdentityInt.IsValid())
	{
		TSharedPtr<const FUniqueNetId> PlayerId = PlayFabIdentityInt->GetUniquePlayerId(LocalUserNum);
		if (PlayerId.IsValid())
		{
			return SendInvite(*PlayerId, SessionName, Friends);
		}
	}

	return false;
}

bool FOnlineSessionPlayFab::SendSessionInviteToFriends(const FUniqueNetId& LocalUserId, FName SessionName, const TArray< TSharedRef<const FUniqueNetId> >& Friends)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::SendSessionInviteToFriends()"));

	return SendInvite(LocalUserId, SessionName, Friends);
}

bool FOnlineSessionPlayFab::GetResolvedConnectString(FName SessionName, FString& ConnectInfo, FName PortType)
{
	ConnectInfo = FString::Printf(TEXT("0.0.0.0:5000?SessionName=%s"), *SessionName.ToString());
	return true;
}

bool FOnlineSessionPlayFab::GetResolvedConnectString(const class FOnlineSessionSearchResult& SearchResult, FName PortType, FString& ConnectInfo)
{
	// NOTE: We don't care about the IP addr since PlayFab Party does not use them. Return empty IP instead of an actual IP or SDA. Don't call the base OSS.
	ConnectInfo = "0.0.0.0:5000";
	return true;
}

FOnlineSessionSettings* FOnlineSessionPlayFab::GetSessionSettings(FName SessionName)
{
	FNamedOnlineSessionPtr MySession = GetNamedSessionPtr(SessionName);
	return MySession.IsValid() ? &MySession->SessionSettings : nullptr;
}

bool FOnlineSessionPlayFab::RegisterPlayer(FName SessionName, const FUniqueNetId& PlayerId, bool bWasInvited)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::RegisterPlayer()"));

	TArray<TSharedRef<const FUniqueNetId>> Players;
	Players.Add(FUniqueNetIdPlayFab::Create(PlayerId));
	return RegisterPlayers(SessionName, Players, bWasInvited);	
}

bool FOnlineSessionPlayFab::RegisterPlayers(FName SessionName, const TArray< TSharedRef<const FUniqueNetId> >& Players, bool bWasInvited /*= false*/)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::RegisterPlayers()"));

	bool bSuccess = false;
	FNamedOnlineSessionPtr Session = GetNamedSessionPtr(SessionName);
	if (Session.IsValid())
	{
		if (Session->SessionInfo.IsValid())
		{
			for (int32 PlayerIdx = 0; PlayerIdx < Players.Num(); PlayerIdx++)
			{
				const TSharedRef<const FUniqueNetId>& PlayerId = Players[PlayerIdx];

				FUniqueNetIdMatcher PlayerMatch(*PlayerId);
				if (Session->RegisteredPlayers.IndexOfByPredicate(PlayerMatch) == INDEX_NONE)
				{
					Session->RegisteredPlayers.Add(PlayerId);
					if (OSSPlayFab->IsLocalPlayer(*PlayerId))
					{
						FSessionSettings* MemberSettings = Session->SessionSettings.MemberSettings.Find(PlayerId);
						if (MemberSettings)
						{
							if (!MemberSettings->Find(FName("Registered")))
							{
								MemberSettings->Add(FName("Registered"), FOnlineSessionSetting(true, EOnlineDataAdvertisementType::ViaOnlineService));
								UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::RegisterPlayers: Marking Player %s as registered in session %s"), *Players[PlayerIdx]->ToDebugString(), *SessionName.ToString());
							}
						}
					}
				}
				else
				{
					UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::RegisterPlayers: Player %s already registered in session %s"), *Players[PlayerIdx]->ToDebugString(), *SessionName.ToString());
				}
			}
			bSuccess = true;
		}
		else
		{
			UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::RegisterPlayers: No session info to join for session (%s)"), *SessionName.ToString());
		}
	}
	else
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::RegisterPlayers: No game present to join for session (%s)"), *SessionName.ToString());
	}

	TriggerOnRegisterPlayersCompleteDelegates(SessionName, Players, bSuccess);
	return bSuccess;
}

void FOnlineSessionPlayFab::TeardownSessionNetwork(FName SessionName)
{
	TSharedPtr<FPlayFabPartyNetwork> SessionNetwork = OSSPlayFab ? OSSPlayFab->GetPartyNetwork(SessionName) : nullptr;
	if (!SessionNetwork.IsValid())
	{
		return;
	}

	SessionNetwork->LeaveNetwork();

	if (IsRunningDedicatedServer())
	{
		return;
	}

	IOnlineVoicePtr VoiceIntPtr = OSSPlayFab ? OSSPlayFab->GetVoiceInterface() : nullptr;
	if (!VoiceIntPtr.IsValid())
	{
		return;
	}

	static_cast<FOnlineVoicePlayFab*>(VoiceIntPtr.Get())->ReleaseVoiceOwnership(SessionName);
}

void FOnlineSessionPlayFab::TryClaimVoiceForSession(FName SessionName)
{
	if (IsRunningDedicatedServer())
	{
		return;
	}

	FPlayFabSessionStatePtr SessionStatePtr = GetSessionStatePtr(SessionName);
	if (!SessionStatePtr.IsValid() || !SessionStatePtr->NamedSession->SessionSettings.bUseLobbiesVoiceChatIfAvailable)
	{
		return;
	}

	IOnlineVoicePtr VoiceIntPtr = OSSPlayFab ? OSSPlayFab->GetVoiceInterface() : nullptr;
	if (!VoiceIntPtr.IsValid())
	{
		return;
	}

	FOnlineVoicePlayFab* PlayFabVoiceInt = static_cast<FOnlineVoicePlayFab*>(VoiceIntPtr.Get());
	if (!PlayFabVoiceInt->TryClaimVoiceOwnership(SessionName))
	{
		return;
	}

	// Add any existing session members to the voice session
	TSharedPtr<FPlayFabPartyNetwork> SessionNetwork = OSSPlayFab->GetPartyNetwork(SessionName);
	if (!SessionNetwork.IsValid() || SessionNetwork->NetworkState != EPlayFabPartyNetworkState::NetworkReady)
	{
		return;
	}

	for (const TPair<FString, FString>& EntityToPlatform : SessionStatePtr->EntityPlatformIdMapping)
	{
		const FString& PlatformId = EntityToPlatform.Value;
		if (PlatformId.IsEmpty())
		{
			continue;
		}
		const TSharedRef<const FUniqueNetId> MemberNetId = FUniqueNetIdPlayFab::Create(PlatformId);
		RegisterVoice(*MemberNetId);
	}
}

bool FOnlineSessionPlayFab::IsVoiceSession(FName SessionName) const
{
	if (!OSSPlayFab)
	{
		return false;
	}

	IOnlineVoicePtr VoiceIntPtr = OSSPlayFab->GetVoiceInterface();
	if (!VoiceIntPtr.IsValid())
	{
		return false;
	}

	return static_cast<FOnlineVoicePlayFab*>(VoiceIntPtr.Get())->IsVoiceOwner(SessionName);
}

void FOnlineSessionPlayFab::RegisterVoice(const FUniqueNetId& PlayerId)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::RegisterVoice()"));

	// Register the player as a local talker with our own voice interface
	IOnlineVoicePtr VoiceIntPtr = OSSPlayFab->GetVoiceInterface();
	if (VoiceIntPtr.IsValid())
	{
		FOnlineVoicePlayFab* PlayFabVoiceInt = static_cast<FOnlineVoicePlayFab*>(VoiceIntPtr.Get());

		IOnlineIdentityPtr IdentityIntPtr = OSSPlayFab->GetIdentityInterface();
		if (IdentityIntPtr.IsValid())
		{
			FOnlineIdentityPlayFab* PlayFabIdentityInt = static_cast<FOnlineIdentityPlayFab*>(IdentityIntPtr.Get());

			TSharedPtr<FPlayFabUser> LocalUser = PlayFabIdentityInt->GetPartyLocalUserFromPlatformId(PlayerId);
			if (LocalUser != nullptr)
			{
				PlayFabVoiceInt->RegisterLocalTalker(PlayerId);
			}
			else
			{
				PlayFabVoiceInt->RegisterRemoteTalker(PlayerId);
			}
		}
	}
}

bool FOnlineSessionPlayFab::UnregisterPlayer(FName SessionName, const FUniqueNetId& PlayerId)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::UnregisterPlayer()"));

	TArray<TSharedRef<const FUniqueNetId>> Players;
	Players.Add(FUniqueNetIdPlayFab::Create(PlayerId));
	return UnregisterPlayers(SessionName, Players);
}

bool FOnlineSessionPlayFab::UnregisterPlayers(FName SessionName, const TArray< TSharedRef<const FUniqueNetId> >& Players)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::UnregisterPlayers()"));

	bool bSuccess = false;

	FNamedOnlineSessionPtr Session = GetNamedSessionPtr(SessionName);
	if (Session.IsValid())
	{
		if (Session->SessionInfo.IsValid())
		{
			for (int32 PlayerIdx = 0; PlayerIdx < Players.Num(); PlayerIdx++)
			{
				const TSharedRef<const FUniqueNetId>& PlayerId = Players[PlayerIdx];

				FUniqueNetIdMatcher PlayerMatch(*PlayerId);
				int32 RegistrantIndex = Session->RegisteredPlayers.IndexOfByPredicate(PlayerMatch);
				if (RegistrantIndex != INDEX_NONE)
				{
					Session->RegisteredPlayers.RemoveAtSwap(RegistrantIndex);

					// The unetdriver cleanup triggers this unregister before the OnSessionChanged event so trigger this delegate here.
					// the test in OnSessionChanged will remain as different underlying net systems will rely on it.
					TriggerOnSessionParticipantLeftDelegates(SessionName, *PlayerId, EOnSessionParticipantLeftReason::Left);
				}
				else
				{
					UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::UnregisterPlayers: Player %s is not part of session (%s)"), *PlayerId->ToDebugString(), *SessionName.ToString());
				}
			}

			bSuccess = true;
		}
		else
		{
			UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::UnregisterPlayers: No session info to leave for session (%s)"), *SessionName.ToString());
		}
	}
	else
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::UnregisterPlayers: No game present to leave for session (%s)"), *SessionName.ToString());
	}

	TriggerOnUnregisterPlayersCompleteDelegates(SessionName, Players, bSuccess);
	return bSuccess;
}

void FOnlineSessionPlayFab::UnregisterVoice(const FUniqueNetId& PlayerId)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::UnregisterVoice()"));

	IOnlineVoicePtr VoiceIntPtr = OSSPlayFab->GetVoiceInterface();
	if (VoiceIntPtr.IsValid())
	{
		FOnlineVoicePlayFab* PlayFabVoiceInt = static_cast<FOnlineVoicePlayFab*>(VoiceIntPtr.Get());

		IOnlineIdentityPtr IdentityIntPtr = OSSPlayFab->GetIdentityInterface();
		if (IdentityIntPtr.IsValid())
		{
			FOnlineIdentityPlayFab* PlayFabIdentityInt = static_cast<FOnlineIdentityPlayFab*>(IdentityIntPtr.Get());
			TSharedPtr<FPlayFabUser> pLocalPartyUser = PlayFabIdentityInt->GetPartyLocalUserFromPlatformId(PlayerId);
			if (pLocalPartyUser != nullptr)
			{
				PlayFabVoiceInt->UnregisterLocalTalker(PlayerId);
			}
			else
			{
				PlayFabVoiceInt->UnregisterRemoteTalker(PlayerId);
			}
		}
	}
}

void FOnlineSessionPlayFab::RegisterLocalPlayer(const FUniqueNetId& PlayerId, FName SessionName, const FOnRegisterLocalPlayerCompleteDelegate& Delegate)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::RegisterLocalPlayer()"));

	if (!OSSPlayFab->GetPlayFabLobbyInterface()->AddLocalPlayer(PlayerId, SessionName, Delegate))
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::RegisterLocalPlayer: Failed to add player to session"));
		Delegate.ExecuteIfBound(PlayerId, EOnJoinSessionCompleteResult::UnknownError);
		return;
	}

	FPlayFabSessionStatePtr SessionStatePtr = GetSessionStatePtr(SessionName);
	if (SessionStatePtr.IsValid() && SessionStatePtr->bUsesNativeSession)
	{
		OSS_PLAYFAB_GET_NATIVE_SESSION_INTERFACE
		{
			NativeSessionInterface->RegisterLocalPlayer(PlayerId, ResolveNativeSessionName(SessionName), Delegate);
		}
	}
}

void FOnlineSessionPlayFab::UnregisterLocalPlayer(const FUniqueNetId& PlayerId, FName SessionName, const FOnUnregisterLocalPlayerCompleteDelegate& Delegate)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::UnregisterLocalPlayer()"));

	if (!OSSPlayFab->GetPlayFabLobbyInterface()->LeaveLobby(PlayerId, SessionName, FOnDestroySessionCompleteDelegate(), Delegate, false))
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::UnregisterLocalPlayer: Failed to unregister player from the session"));
		Delegate.ExecuteIfBound(PlayerId, false);
		return;
	}

	FPlayFabSessionStatePtr SessionStatePtr = GetSessionStatePtr(SessionName);
	if (SessionStatePtr.IsValid() && SessionStatePtr->bUsesNativeSession)
	{
		OSS_PLAYFAB_GET_NATIVE_SESSION_INTERFACE
		{
			NativeSessionInterface->UnregisterLocalPlayer(PlayerId, ResolveNativeSessionName(SessionName), Delegate);
		}
	}
}

int32 FOnlineSessionPlayFab::GetNumSessions()
{
	FScopeLock ScopeLock(&SessionLock);
	return SessionStates.Num();
}

void FOnlineSessionPlayFab::DumpSessionState()
{
	FScopeLock ScopeLock(&SessionLock);

	for (const auto& State : SessionStates)
	{
		DumpNamedSession(&State->NamedSession.Get());
	}
}

FPlayFabSessionStatePtr FOnlineSessionPlayFab::TryAddSessionState(FName SessionName, FNamedOnlineSessionRef InNamedSession)
{
	FScopeLock ScopeLock(&SessionLock);
	if (GetSessionStatePtr(SessionName).IsValid())
	{
		return nullptr;
	}

	return SessionStates.Add_GetRef(MakeShared<FPlayFabSessionState>(SessionName, InNamedSession, bPlatformUsesNativeSession, OSSPlayFab));
}

FPlayFabSessionStatePtr FOnlineSessionPlayFab::GetSessionStatePtr(FName SessionName) const
{
	FScopeLock ScopeLock(&SessionLock);
	const FPlayFabSessionStateRef* StateRef = SessionStates.FindByPredicate([SessionName](const FPlayFabSessionStateRef& State)
	{
		return State->SessionName == SessionName;
	});

	if (StateRef)
	{
		return *StateRef;
	}
	
	return nullptr;
}

FNamedOnlineSession* FOnlineSessionPlayFab::AddNamedSession(FName SessionName, const FOnlineSessionSettings& SessionSettings)
{
	FNamedOnlineSessionRef NewSession = MakeShared<FNamedOnlineSession, ESPMode::ThreadSafe>(SessionName, SessionSettings);
	FScopeLock ScopeLock(&SessionLock);
	if (!TryAddSessionState(SessionName, NewSession).IsValid())
	{
		GetSessionStatePtr(SessionName)->NamedSession = NewSession;
	}
	return &NewSession.Get();
}


FNamedOnlineSessionRef FOnlineSessionPlayFab::AddNamedSessionRef(FName SessionName, const FOnlineSessionSettings& SessionSettings)
{
	FNamedOnlineSessionRef NewSession = MakeShared<FNamedOnlineSession, ESPMode::ThreadSafe>(SessionName, SessionSettings);
	FScopeLock ScopeLock(&SessionLock);
	if (!TryAddSessionState(SessionName, NewSession).IsValid())
	{
		GetSessionStatePtr(SessionName)->NamedSession = NewSession;
	}
	return NewSession;
}

FNamedOnlineSession* FOnlineSessionPlayFab::AddNamedSession(FName SessionName, const FOnlineSession& Session)
{
	FNamedOnlineSessionRef NewSession = MakeShared<FNamedOnlineSession, ESPMode::ThreadSafe>(SessionName, Session);
	FScopeLock ScopeLock(&SessionLock);
	if (!TryAddSessionState(SessionName, NewSession).IsValid())
	{
		GetSessionStatePtr(SessionName)->NamedSession = NewSession;
	}
	return &NewSession.Get();
}

FNamedOnlineSessionRef FOnlineSessionPlayFab::AddNamedSessionRef(FName SessionName, const FOnlineSession& Session)
{
	FNamedOnlineSessionRef NewSession = MakeShared<FNamedOnlineSession, ESPMode::ThreadSafe>(SessionName, Session);
	FScopeLock ScopeLock(&SessionLock);
	if (!TryAddSessionState(SessionName, NewSession).IsValid())
	{
		GetSessionStatePtr(SessionName)->NamedSession = NewSession;
	}
	return NewSession;
}

FNamedOnlineSessionPtr FOnlineSessionPlayFab::GetNamedSessionPtr(FName SessionName) const
{
	FPlayFabSessionStatePtr State = GetSessionStatePtr(SessionName);
	if (State.IsValid())
	{
		return State->NamedSession;
	}
	return nullptr;
}


void FOnlineSessionPlayFab::Tick(float DeltaTime)
{
	// Snapshot session states to avoid iterator invalidation if callbacks modify the array
	TArray<FPlayFabSessionStateRef> PendingRetries;

	{
		FScopeLock ScopeLock(&SessionLock);
		for (auto& PlayFabSessionState : SessionStates)
		{
			PlayFabSessionState->RetryJoinNetwork_TimeSinceLastRetry += DeltaTime;

			if (PlayFabSessionState->RetryJoinNetwork_Count > 0)
			{
				if (PlayFabSessionState->RetryJoinNetwork_TimeSinceLastRetry > PlayFabSessionState->RetryJoinNetwork_RetryTime)
				{
					PlayFabSessionState->RetryJoinNetwork_TimeSinceLastRetry = 0.0f;
					PlayFabSessionState->RetryJoinNetwork_Count -= 1;
					PendingRetries.Add(PlayFabSessionState);
				}
			}
		}
	}

	for (const FPlayFabSessionStateRef& SessionState : PendingRetries)
	{
		OnOperationComplete_TryJoinNetwork(SessionState);
	}

	OSSPlayFab->GetPlayFabLobbyInterface()->DoWork();

	OSSPlayFab->GetMatchmakingInterface()->DoWork();

	if (bPlatformUsesNativeSession)
	{
		OSS_PLAYFAB_GET_NATIVE_SESSION_INTERFACE
		{
			if (!OnNativeSessionUserInviteAcceptedDelegateHandle.IsValid())
			{
				OnNativeSessionUserInviteAcceptedDelegateHandle = NativeSessionInterface->AddOnSessionUserInviteAcceptedDelegate_Handle(OnNativeSessionUserInviteAcceptedDelegate);
			}
		}
	}

#if defined(OSS_PLAYFAB_GDK_SUPPORT)
	if (IsNativePlatformSubsystemGDK())
	{
		TickPendingInvites();
	}
#endif
#if defined(OSS_PLAYFAB_STEAM)
	if (IsNativePlatformSubsystemSteam())
	{
		// Retry Steam invite callback registration if it wasn't ready at construction time
		if (!bSteamInviteCallbackRegistered)
		{
			RegisterForSteamInvites();
		}
		// Process deferred Steam invites once identity is ready
		TickPendingSteamInvite();
	}
#endif
}

FOnlineSessionSearchResult FOnlineSessionPlayFab::CreateSearchResultFromInvite(const PFLobbyInviteReceivedStateChange& StateChange)
{
	const FString LobbyConnectionString(UTF8_TO_TCHAR(StateChange.connectionString));

	TSharedRef<FOnlineSessionInfoPlayFab> NewSessionInfo = MakeShared<FOnlineSessionInfoPlayFab>();
	NewSessionInfo->ConnectionString = LobbyConnectionString;

	FOnlineSessionSearchResult NewSearchResult;
	NewSearchResult.Session.SessionInfo = NewSessionInfo;
	NewSearchResult.Session.OwningUserId = FUniqueNetIdPlayFab::EmptyId(); // TODO we do not receive the owner, but only the inviting Entity.

	NewSearchResult.Session.SessionSettings.Set(SETTING_CONNECTION_STRING, LobbyConnectionString, EOnlineDataAdvertisementType::ViaOnlineService);

	return NewSearchResult;
}

// TODO remove this function as a part of cleanup
FString FOnlineSessionPlayFab::GetPlatformIdFromEntityId(const FString& EntityId)
{
	FString PlatformUserId;

	IOnlineVoicePtr VoiceIntPtr = OSSPlayFab->GetVoiceInterface();
	if (VoiceIntPtr.IsValid())
	{
		FOnlineVoicePlayFab* PlayFabVoiceInt = static_cast<FOnlineVoicePlayFab*>(VoiceIntPtr.Get());
		if (PlayFabVoiceInt)
		{
			PlatformUserId = PlayFabVoiceInt->GetPlatformIdFromEntityId(EntityId);
		}
	}

	return PlatformUserId;
}

void FOnlineSessionPlayFab::OnCreateSessionCompleted(FName SessionName, bool bPlayFabSessionCreated, bool bSkipCleanup)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnCreateSessionCompleted()"));

	bool bSuccess = false;
	FPlayFabSessionStatePtr SessionStatePtr = GetSessionStatePtr(SessionName);

	if (bPlayFabSessionCreated && SessionStatePtr.IsValid())
	{
		FPlayFabSessionState& PlayFabSessionState = *SessionStatePtr;
		FNamedOnlineSessionRef ExistingNamedSession = PlayFabSessionState.NamedSession;
		if (ExistingNamedSession->OwningUserId.IsValid())
		{
			FUniqueNetIdPtr NativeNetId;
			if (!IsRunningDedicatedServer())
			{
				NativeNetId = OSSPlayFab->GetNativeNetId(ExistingNamedSession->OwningUserId.ToSharedRef());
			}
			if (NativeNetId.IsValid() || ExistingNamedSession->OwningUserId->GetType() == PLAYFAB_SUBSYSTEM)
			{
				FOnlineSessionInfoPlayFabPtr PlayFabSessionInfo = StaticCastSharedPtr<FOnlineSessionInfoPlayFab>(ExistingNamedSession->SessionInfo);
				if (PlayFabSessionInfo.IsValid())
				{
					PlayFabSessionState.ConnectionString = PlayFabSessionInfo->ConnectionString;
					if (PlayFabSessionState.ConnectionString.IsEmpty() == false)
					{
						if (PlayFabSessionState.bUsesNativeSession && NativeNetId.IsValid())
						{
							OSS_PLAYFAB_GET_NATIVE_SESSION_INTERFACE
							{
								PlayFabSessionState.OnNativeCreateSessionCompleteDelegateHandle = NativeSessionInterface->AddOnCreateSessionCompleteDelegate_Handle(
									FOnCreateSessionCompleteDelegate::CreateLambda([this, NativeSessionInterface, ExistingNamedSession, SessionName](FName CallbackNativeSessionName, bool bNativeSessionCreated)
									{
										if (ResolveNativeSessionName(SessionName) != CallbackNativeSessionName)
										{
											return;
										}
										if (bNativeSessionCreated == false)
										{
											TeardownSessionNetwork(SessionName);
											RemoveNamedSession(SessionName);
											OSSPlayFab->GetPlayFabLobbyInterface()->LeaveLobby(*FUniqueNetIdPlayFab::EmptyId(), SessionName, FOnDestroySessionCompleteDelegate(), FOnUnregisterLocalPlayerCompleteDelegate(), true);

											UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnNativeCreateSessionComplete: Failed to create native session, leaving Playfab Party network"));
											TriggerOnCreateSessionCompleteDelegates(SessionName, false);
											return;
										}
										else
										{
											FNamedOnlineSession* ExistingNativeNamedSession = NativeSessionInterface->GetNamedSession(CallbackNativeSessionName);
											if (ExistingNativeNamedSession)
											{
												FUniqueNetIdRef NativeSessionId = ExistingNativeNamedSession->SessionInfo->GetSessionId().AsShared();
												if (NativeSessionId->IsValid())
												{
													ExistingNamedSession->SessionSettings.Set(FName(SEARCH_KEY_NATIVE_SESSIONID), NativeSessionId->ToString(), EOnlineDataAdvertisementType::ViaOnlineService);
#if defined(OSS_PLAYFAB_WIN64)
													if (!IsNativePlatformSubsystemGDK())
													{
														ExistingNamedSession->SessionSettings.Set(FName(SEARCH_KEY_NATIVE_PLATFORM), PLATFORM_MODEL_WIN64, EOnlineDataAdvertisementType::ViaOnlineService);
													}
#elif defined(OSS_PLAYFAB_PLAYSTATION)
													ExistingNamedSession->SessionSettings.Set(FName(SEARCH_KEY_NATIVE_PLATFORM), PLATFORM_MODEL_SONY, EOnlineDataAdvertisementType::ViaOnlineService);
#endif
													if (!UpdateSession(SessionName, ExistingNamedSession->SessionSettings, true))
													{
														UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnNativeCreateSessionComplete: UpdateSession failed"));
													}
												}

												else
												{
													UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnNativeCreateSessionComplete: NativeSessionId was invalid"));
												}
											}
											else
											{
												UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnNativeCreateSessionComplete: ExistingNativeNamedSession was null"));
											}
										}
										TriggerOnCreateSessionCompleteDelegates(SessionName, bNativeSessionCreated);
										FPlayFabSessionStatePtr State = GetSessionStatePtr(SessionName);
										if (State.IsValid())
										{
											NativeSessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(State->OnNativeCreateSessionCompleteDelegateHandle);
										}
									}));

								FOnlineSessionSettings SessionSettings = ExistingNamedSession->SessionSettings;
								SessionSettings.Set(SETTING_CONNECTION_STRING, PlayFabSessionState.ConnectionString, EOnlineDataAdvertisementType::ViaOnlineService);
								bSuccess = NativeSessionInterface->CreateSession(*NativeNetId, ResolveNativeSessionName(SessionName), SessionSettings);
							}
						}
						else
						{
							bSuccess = true;

#if defined(OSS_PLAYFAB_STEAM)
								// No native session was created (e.g. server-created lobby).
								// Set Steam Rich Presence so friends can join via "Join Game" on Steam overlay.
								if (IsNativePlatformSubsystemSteam() && ExistingNamedSession->SessionSettings.bUsesPresence)
								{
									SetSteamRichPresenceConnect(PlayFabSessionState.ConnectionString);
								}
#endif

							TriggerOnCreateSessionCompleteDelegates(SessionName, bSuccess);
						}
					}
					else
					{
						UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnCreateSessionCompleted: ConnectionString was invalid"));
					}
				}
				else
				{
					UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnCreateSessionCompleted: PlayFabSessionInfo was invalid"));
				}
			}
			else
			{
				UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnCreateSessionCompleted: NativeNetId was invalid"));
			}
		}
		else
		{
			UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnCreateSessionCompleted: ExistingNamedSession or PlayerId was invalid"));
		}
	}
	
	if (bSuccess == false)
	{
		if (!bSkipCleanup)
		{
			UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnCreateSessionCompleted: failed to create session, leaving Playfab Party network"));
			TeardownSessionNetwork(SessionName);
			RemoveNamedSession(SessionName);
		}
		TriggerOnCreateSessionCompleteDelegates(SessionName, false);
	}
}

void FOnlineSessionPlayFab::GenerateCrossNetworkVoiceChatPlatformPermissions()
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::GenerateCrossNetworkVoiceChatPlatformPermissions()"));

	VoiceChatPlatforms.Emplace(PLATFORM_MODEL_WINGDK, ECrossNetworkType::GDK);
	VoiceChatPlatforms.Emplace(PLATFORM_MODEL_XSX, ECrossNetworkType::GDK);
	VoiceChatPlatforms.Emplace(PLATFORM_MODEL_XB1, ECrossNetworkType::GDK);
	VoiceChatPlatforms.Emplace(PLATFORM_MODEL_WIN64, ECrossNetworkType::NONGDK);
	VoiceChatPlatforms.Emplace(PLATFORM_MODEL_SWITCH, ECrossNetworkType::NONGDK);
	VoiceChatPlatforms.Emplace(PLATFORM_MODEL_PS4, ECrossNetworkType::NONGDK);
	VoiceChatPlatforms.Emplace(PLATFORM_MODEL_PS5, ECrossNetworkType::NONGDK);
	
	// load all voice chat disabled platforms
	TArray<FString> DisabledPlatforms;
	GConfig->GetArray(TEXT("OnlineSubsystemPlayFabVoiceChatDisabledPlatforms"), TEXT("Platforms"), DisabledPlatforms, GEngineIni);

	for (auto& DisabledPlatform : DisabledPlatforms)
	{
		VoiceChatPlatforms.Emplace(DisabledPlatform, ECrossNetworkType::DISABLED);
	}
}

bool FOnlineSessionPlayFab::IsHostSetting(const FName& Name)
{
	return Name == SETTING_HOST_NICKNAME;
}

void FOnlineSessionPlayFab::OnNativeSessionUserInviteAccepted(const bool bWasSuccessful, const int32 ControllerId, FUniqueNetIdPtr UserId, const FOnlineSessionSearchResult& InviteResult)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnNativeSessionUserInviteAccepted()"));
	TriggerOnSessionUserInviteAcceptedDelegates(bWasSuccessful, ControllerId, UserId, InviteResult);
}

#pragma region Helpers
bool FOnlineSessionPlayFab::GetLobbyHandleBySessionName(const FName SessionName, PFLobbyHandle& LobbyHandle)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::GetLobbyHandleBySessionName()"));

	FNamedOnlineSessionPtr SessionPtr = GetNamedSessionPtr(SessionName);
	if (SessionPtr.IsValid())
	{
		FOnlineSessionInfoPlayFabPtr SessionInfo = StaticCastSharedPtr<FOnlineSessionInfoPlayFab>(SessionPtr->SessionInfo);
		if (SessionInfo.IsValid())
		{
			LobbyHandle = SessionInfo->LobbyHandle;
			return true;
		}
		else
		{
			UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::GetLobbyHandleBySessionName: SessionInfo was null"));
		}
	}
	else
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::GetLobbyHandleBySessionName: failed to find the lobby for session %s!"), *SessionName.ToString());
	}

	return false;
}

bool FOnlineSessionPlayFab::ValidateSessionForInvite(const FName SessionName)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::ValidateSessionForInvite()"));

	FNamedOnlineSessionPtr SessionPtr = GetNamedSessionPtr(SessionName);
	if (!SessionPtr.IsValid())
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::ValidateSessionForInvite: Cannot Invite Friends to session %s, that session does not exist"), *SessionName.ToString());
		return false;
	}

	if (SessionPtr->SessionState < EOnlineSessionState::Pending || SessionPtr->SessionState > EOnlineSessionState::InProgress)
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::ValidateSessionForInvite: Cannot Invite Friends to session %s, that session is in state %d"), *SessionName.ToString(), SessionPtr->SessionState);
		return false;
	}

	FOnlineSessionInfoPlayFabPtr SessionInfo = StaticCastSharedPtr<FOnlineSessionInfoPlayFab>(SessionPtr->SessionInfo);
	if (!SessionInfo.IsValid())
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::ValidateSessionForInvite: Cannot Invite Friends to session %s, that session has invalid info"), *SessionName.ToString());
		return false;
	}

	return true;
}

#pragma endregion

#pragma region PlayFab Multiplayer Invites
bool FOnlineSessionPlayFab::SendSessionInviteToFriend_PlayFabMultiplayer(const PFEntityKey& LocalUserEntityKey, FName SessionName, const PFEntityKey& RemoteUserEntityKey)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::SendSessionInviteToFriend_PlayFabMultiplayer()"));

	TArray<PFEntityKey> RemoteUserEntityKeys;
	RemoteUserEntityKeys.Add(RemoteUserEntityKey);

	return SendSessionInviteToFriends_PlayFabMultiplayer(LocalUserEntityKey, SessionName, RemoteUserEntityKeys);
}

bool FOnlineSessionPlayFab::SendSessionInviteToFriends_PlayFabMultiplayer(const PFEntityKey& LocalUserEntityKey, FName SessionName, const TArray<PFEntityKey>& RemoteUserEntityKeys)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::SendSessionInviteToFriends_PlayFabMultiplayer()"));

	if (RemoteUserEntityKeys.Num() < 1)
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::SendInvite_PlayFabMultiplayer: RemoteUserEntityKeys was empty"));
		return true;
	}

	if (!ValidateSessionForInvite(SessionName))
	{
		return false;
	}

	PFLobbyHandle LobbyHandle{};
	if (!GetLobbyHandleBySessionName(SessionName, LobbyHandle))
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::SendInvite_PlayFabMultiplayer: No lobby found for session %s!"), *SessionName.ToString());
		return false;
	}

	for (const PFEntityKey& RemoteUserEntityKey : RemoteUserEntityKeys)
	{
		HRESULT Hr = PFLobbySendInvite(LobbyHandle, &LocalUserEntityKey, &RemoteUserEntityKey, nullptr);
		if (FAILED(Hr))
		{
			LogMultiplayerErrorWithMessage("PFLobbySendInvite", Hr);
			return false;
		}
	}

	return true;
}

void FOnlineSessionPlayFab::OnInvitationReceived_PlayFabMultiplayer(const PFEntityKey& ListeningEntityKey, const PFEntityKey& InvitingEntityKey, const FString& InConnectionString)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnInvitationReceived_PlayFabMultiplayer()"));

	TriggerOnPlayFabMultiplayerInviteReceivedDelegates(ListeningEntityKey, InvitingEntityKey, InConnectionString);
}

void FOnlineSessionPlayFab::OnAppResume(FOnSessionsRemovedDelegate& CompletionDelegate)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnAppResume()"));

	if (SessionStates.Num() == 0)
	{
		CompletionDelegate.ExecuteIfBound();
		return;
	}

	OnAppResumeDelegate = CompletionDelegate;

	auto OnSessionsRemoved = [&]() {
		OnAppResumeDelegate.ExecuteIfBound();
	};
	OnSessionsRemovedDelegate.BindLambda(OnSessionsRemoved);
}

#pragma endregion
