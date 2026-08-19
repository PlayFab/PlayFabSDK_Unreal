//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSubsystemPlayFabDefines.h"
#include "OnlineSubsystemPlayFabPackage.h"
#include "OnlineSubsystemPlayFabTypes.h"
#include "PlayFabLobby.h"
#include "MatchmakingInterfacePlayFab.h"

#if defined(OSS_PLAYFAB_GDK_SUPPORT)
#include "OnlineSubsystemGDKTypes.h"
#endif // OSS_PLAYFAB_GDK_SUPPORT

using FNamedOnlineSessionRef = TSharedRef<FNamedOnlineSession, ESPMode::ThreadSafe>;
using FNamedOnlineSessionPtr = TSharedPtr<FNamedOnlineSession, ESPMode::ThreadSafe>;

class FInternetAddr;
class FOnlineSettings;
class FUniqueNetIdPlayFab;
class FOnlineSubsystemPlayFab;
enum class ECrossNetworkType : int;

// Identifies which async flow initiated the Party network connection.
enum class ENetworkFlowType : uint8
{
	None,
	CreateSession,
	Matchmaking,
	JoinSession
};

// Encapsulates all per-session state for a PlayFab session. This bundles PlayFab-specific async
// operation state (retry counters, pending info).
struct FPlayFabSessionState
{
	FPlayFabSessionState(FName InSessionName, FNamedOnlineSessionRef InNamedSession, bool bInUsesNativeSession, FOnlineSubsystemPlayFab* InSubsystem);
	~FPlayFabSessionState();

	FName SessionName;

	// The Unreal named session associated with this state
	FNamedOnlineSessionRef NamedSession;

	// Per-session connection info
	FString ConnectionString;

	// Retry state for joining Party network (used by both matchmaking and lobby join flows)
	float RetryJoinNetwork_RetryTime = 2.0f;
	float RetryJoinNetwork_TimeSinceLastRetry = 0.0f;
	int32 RetryJoinNetwork_Count = 0;
	int32 RetryJoinNetwork_MaxCount = 15;

	// Per-session operation state
	FString NetworkId;
	ENetworkFlowType NetworkFlowType = ENetworkFlowType::None;

	// Maps PlayFab entity IDs to platform-specific user IDs for this session's members
	TMap<FString, FString> EntityPlatformIdMapping;

	// Lobby operation delegate handles
	FDelegateHandle OnUpdateLobbyCompleteDelegate;
	FDelegateHandle OnUpdateSession_MatchmakingDelegateHandle;

	// Lobby delegate callbacks
	void OnUpdateLobbyCompleted(FName InSessionName, bool bWasSuccessful);
	void OnUpdateSession_Matchmaking(FName InSessionName, bool bWasSuccessful);

	// Native platform operation delegate handles
	FDelegateHandle OnNativeCreateSessionCompleteDelegateHandle;
	FDelegateHandle OnNativeUpdateSessionCompleteDelegateHandle;
	FDelegateHandle OnNativeJoinSessionCompleteDelegateHandle;

	bool bUsesNativeSession;

	FOnlineSubsystemPlayFab* OSSPlayFab;
};

using FPlayFabSessionStateRef = TSharedRef<FPlayFabSessionState>;
using FPlayFabSessionStatePtr = TSharedPtr<FPlayFabSessionState>;

struct FPendingInviteData
{
	FPendingInviteData() = default;
	FPendingInviteData(const int32 ControllerIndex,
		const FOnlineSessionSearchResult& SearchResult)
		: bControllerIndex(ControllerIndex),
		bSearchResult(SearchResult)
	{}

	int32 bControllerIndex;
	FOnlineSessionSearchResult bSearchResult;
	bool bHasActiveInvite = false;
};

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnPlayFabMultiplayerInviteReceived, const PFEntityKey /*ListingEntityKey*/, const PFEntityKey /*InvitingEntityKey*/, const FString /*ConnectionString*/);
typedef FOnPlayFabMultiplayerInviteReceived::FDelegate FOnPlayFabMultiplayerInviteReceivedDelegate;

DECLARE_MULTICAST_DELEGATE(FOnSessionsRemoved);
typedef FOnSessionsRemoved::FDelegate FOnSessionsRemovedDelegate;

class FOnlineSessionPlayFab : public IOnlineSession
{
public:
	FOnlineSessionPlayFab(FOnlineSubsystemPlayFab* InSubsystem);
	virtual ~FOnlineSessionPlayFab();

	/** Performs common constructor operations. */
	void Initialize();

	// IOnlineSession interface
	virtual TSharedPtr<const FUniqueNetId> CreateSessionIdFromString(const FString& SessionIdStr) override;
	virtual FNamedOnlineSession* GetNamedSession(FName SessionName) override;

	virtual void RemoveNamedSession(FName SessionName) override;
	virtual bool HasPresenceSession() override;
	virtual EOnlineSessionState::Type GetSessionState(FName SessionName) const override;
	virtual bool CreateSession(int32 HostingPlayerControllerIndex, FName SessionName, const FOnlineSessionSettings& NewSessionSettings) override;
	virtual bool CreateSession(const FUniqueNetId& HostingPlayerId, FName SessionName, const FOnlineSessionSettings& NewSessionSettings) override;
	virtual bool StartSession(FName SessionName) override;
	virtual bool UpdateSession(FName SessionName, FOnlineSessionSettings& UpdatedSessionSettings, bool bShouldRefreshOnlineData = false)  override;
	virtual bool EndSession(FName SessionName) override;
	virtual bool DestroySession(FName SessionName, const FOnDestroySessionCompleteDelegate& CompletionDelegate = FOnDestroySessionCompleteDelegate()) override;
	virtual bool IsPlayerInSession(FName SessionName, const FUniqueNetId& UniqueId) override;
	virtual bool StartMatchmaking(const TArray< TSharedRef<const FUniqueNetId> >& LocalPlayers, FName SessionName, const FOnlineSessionSettings& NewSessionSettings, TSharedRef<FOnlineSessionSearch>& SearchSettings) override;
	virtual bool CancelMatchmaking(int32 SearchingPlayerNum, FName SessionName) override;
	virtual bool CancelMatchmaking(const FUniqueNetId& SearchingPlayerId, FName SessionName) override;
	virtual bool FindSessions(int32 SearchingPlayerNum, const TSharedRef<FOnlineSessionSearch>& SearchSettings) override;
	virtual bool FindSessions(const FUniqueNetId& SearchingPlayerId, const TSharedRef<FOnlineSessionSearch>& SearchSettings) override;
	virtual bool FindSessionById(const FUniqueNetId& SearchingUserId, const FUniqueNetId& SessionId, const FUniqueNetId& FriendId, const FOnSingleSessionResultCompleteDelegate& CompletionDelegate) override;
	virtual bool CancelFindSessions() override;
	virtual bool PingSearchResults(const FOnlineSessionSearchResult& SearchResult) override;
	virtual bool JoinSession(int32 ControllerIndex, FName SessionName, const FOnlineSessionSearchResult& DesiredSession) override;
	virtual bool JoinSession(const FUniqueNetId& UserId, FName SessionName, const FOnlineSessionSearchResult& DesiredSession) override;
	virtual bool FindFriendSession(int32 LocalUserNum, const FUniqueNetId& Friend) override;
	virtual bool FindFriendSession(const FUniqueNetId& LocalUserId, const FUniqueNetId& Friend) override;
	virtual bool FindFriendSession(const FUniqueNetId& LocalUserId, const TArray<TSharedRef<const FUniqueNetId>>& FriendList) override;
	virtual bool SendSessionInviteToFriend(int32 LocalUserNum, FName SessionName, const FUniqueNetId& Friend) override;
	virtual bool SendSessionInviteToFriend(const FUniqueNetId& LocalUserId, FName SessionName, const FUniqueNetId& Friend) override;
	virtual bool SendSessionInviteToFriends(int32 LocalUserNum, FName SessionName, const TArray< TSharedRef<const FUniqueNetId> >& Friends) override;
	virtual bool SendSessionInviteToFriends(const FUniqueNetId& LocalUserId, FName SessionName, const TArray< TSharedRef<const FUniqueNetId> >& Friends) override;
	virtual bool GetResolvedConnectString(FName SessionName, FString& ConnectInfo, FName PortType)  override;
	virtual bool GetResolvedConnectString(const class FOnlineSessionSearchResult& SearchResult, FName PortType, FString& ConnectInfo)  override;
	virtual FOnlineSessionSettings* GetSessionSettings(FName SessionName) override;
	virtual bool RegisterPlayer(FName SessionName, const FUniqueNetId& PlayerId, bool bWasInvited)  override;
	virtual bool RegisterPlayers(FName SessionName, const TArray< TSharedRef<const FUniqueNetId> >& Players, bool bWasInvited = false)  override;
	virtual bool UnregisterPlayer(FName SessionName, const FUniqueNetId& PlayerId)  override;
	virtual bool UnregisterPlayers(FName SessionName, const TArray< TSharedRef<const FUniqueNetId> >& Players)  override;
	virtual void RegisterLocalPlayer(const FUniqueNetId& PlayerId, FName SessionName, const FOnRegisterLocalPlayerCompleteDelegate& Delegate) override;
	virtual void UnregisterLocalPlayer(const FUniqueNetId& PlayerId, FName SessionName, const FOnUnregisterLocalPlayerCompleteDelegate& Delegate) override;
	virtual int32 GetNumSessions() override;
	virtual void DumpSessionState() override;

	// IOnlineSession interface
	FNamedOnlineSession* AddNamedSession(FName SessionName, const FOnlineSessionSettings& SessionSettings) override;
	FNamedOnlineSessionRef AddNamedSessionRef(FName SessionName, const FOnlineSessionSettings& SessionSettings);
	FNamedOnlineSession* AddNamedSession(FName SessionName, const FOnlineSession& Session) override;
	FNamedOnlineSessionRef AddNamedSessionRef(FName SessionName, const FOnlineSession& Session);

	FNamedOnlineSessionPtr GetNamedSessionPtr(FName SessionName) const;

	void RegisterForUpdates();
	void UnregisterForUpdates();

	void OnLobbyUpdate(FName SessionName, const PFLobbyUpdatedStateChange& StateChange);
	void OnLobbyMemberAdded(FName SessionName, const PFLobbyMemberAddedStateChange& StateChange);
	void OnLobbyMemberRemoved(FName SessionName, const PFLobbyMemberRemovedStateChange& StateChange);
	void OnLobbyDisconnected(FName SessionName);
	bool SetHostOnSession(FName SessionName, const PFEntityKey& HostEntityKey);
	void OnAppResume(FOnSessionsRemovedDelegate& CompletionDelegate);

PACKAGE_SCOPE:
	/** Critical sections for thread safe operation of session lists */
	mutable FCriticalSection SessionLock;

	/** Current search object */
	TSharedPtr<FOnlineSessionSearch> CurrentSessionSearch;

	/** Current session settings */
	TArray<FPlayFabSessionStateRef> SessionStates;
	FPlayFabSessionStatePtr TryAddSessionState(FName SessionName, FNamedOnlineSessionRef InNamedSession);
	FPlayFabSessionStatePtr GetSessionStatePtr(FName SessionName) const;

protected:
	bool JoinSession_PlayFabInternal(int32 ControllerIndex, TSharedPtr<const FUniqueNetId> UserId, FName SessionName, const FOnlineSessionSearchResult& DesiredSession);

	void OnPartyEndpointCreated(bool bSuccess, const FString& NetworkId, uint16 EndpointID, bool bIsHosting);
	void OnCreatePartyEndpoint(bool bSuccess, bool bIsHosting, FPlayFabSessionStateRef SessionState);

	FOnlineSubsystemPlayFab* OSSPlayFab = nullptr;

	void OnJoinLobbyCompleted(FName InSessionName, EOnJoinSessionCompleteResult::Type Result);
	void OnMatchmakingComplete(FName SessionName, bool bWasSuccessful);

#if defined(OSS_PLAYFAB_PLAYSTATION)
	FName NativeSessionName = NAME_GameSession;
	void UpdateNativeSessionName();
	const FUniqueNetIdPtr CreateNativeNetIdPtr();
	FName ResolveNativeSessionName(FName) const { return NativeSessionName; }
#else
	static FName ResolveNativeSessionName(FName SessionName) { return SessionName; }
#endif

	void OnOperationComplete_TryJoinNetwork(FPlayFabSessionStateRef SessionState);

	void OnCreatePartyEndpoint_Matchmaking(bool bSuccess, bool bIsHosting, FName SessionName, FPlayFabSessionStateRef SessionState);
	void OnCreatePartyEndpoint_JoinSession(bool bSuccess, FName SessionName);

public:
	void Tick(float DeltaTime);

	void OnCreateSessionCompleted(FName SessionName, bool bWasSuccessful, bool bSkipCleanup);

	void OnLobbyCreatedAndJoinCompleted(bool bSuccess, FName SessionName);

	void OnMatchmakingTicketCompleted(bool bSuccess, FName SessionName);

	void OnCancelMatchmakingComplete(FName SessionName, bool bSuccess);

	void OnLeaveLobbyCompleted(FName SessionName, bool bSuccess);

	void OnFindLobbiesCompleted(int32 LocalUserNum, bool bSuccess, TSharedPtr<FOnlineSessionSearch> SearchResults);
	FOnFindLobbiesCompletedDelegate OnFindLobbiesCompletedDelegateHandle;
	FDelegateHandle OnFindLobbiesCompletedHandle;

	void OnFindFriendLobbiesCompleted(int32 LocalUserNum, bool bSuccess, TSharedPtr<FOnlineSessionSearch> SearchResults);
	FDelegateHandle OnFindFriendLobbiesCompletedHandle;

private:
	void TeardownSessionNetwork(FName SessionName);
	void TryClaimVoiceForSession(FName SessionName);
	bool IsVoiceSession(FName SessionName) const;
	void RegisterVoice(const FUniqueNetId& PlayerId);
	void UnregisterVoice(const FUniqueNetId& PlayerId);
	FString GetPlatformIdFromEntityId(const FString& EntityId);
	FOnlineSessionSearchResult CreateSearchResultFromInvite(const PFLobbyInviteReceivedStateChange& StateChange);

#if defined(OSS_PLAYFAB_GDK_SUPPORT)
	XTaskQueueRegistrationToken ActivationHandler = { 0 };
	bool bActivationHandlerRegistered = false;
#endif // OSS_PLAYFAB_GDK_SUPPORT
#if defined(OSS_PLAYFAB_WIN64)
	TSharedPtr<FOnlineSessionSearch> CachedSearchSettings;
#endif // OSS_PLAYFAB_WIN64

	FPendingInviteData PendingInviteData;

	TMap<FString, ECrossNetworkType> VoiceChatPlatforms;
	void GenerateCrossNetworkVoiceChatPlatformPermissions();
	bool IsHostSetting(const FName& Name);

	// Flag for whether the current platform should call into the platform's native session interface
	bool bPlatformUsesNativeSession = false;

	FDelegateHandle OnNativeFindSessionsCompleteDelegateHandle;

	FDelegateHandle OnNativeSessionUserInviteAcceptedDelegateHandle;
	FOnSessionUserInviteAcceptedDelegate OnNativeSessionUserInviteAcceptedDelegate;
	void OnNativeSessionUserInviteAccepted(const bool bWasSuccessful, const int32 ControllerId, FUniqueNetIdPtr UserId, const FOnlineSessionSearchResult& InviteResult);

	FOnSessionsRemovedDelegate OnSessionsRemovedDelegate;
	FOnSessionsRemovedDelegate OnAppResumeDelegate;

private:
	//Invites
#if defined(OSS_PLAYFAB_GDK_SUPPORT)
	void RegisterForInvites();
	void UnregisterForInvites();
#endif // OSS_PLAYFAB_GDK_SUPPORT
#if defined(OSS_PLAYFAB_STEAM)
	// Steam invite support — registers for Steam overlay "Join Game" callbacks
	// and Rich Presence. Runtime check IsNativePlatformSubsystemGDK() selects the active path.
	void RegisterForSteamInvites();
	void UnregisterForSteamInvites();
	void SetSteamRichPresenceConnect(const FString& InPlayFabConnectionString);
	void ClearSteamRichPresenceConnect();
	void CheckSteamCommandLineLaunch();
	void TickPendingSteamInvite();
	bool bSteamInviteCallbackRegistered = false;
	FString PendingSteamInviteConnectionString;
public:
	// Public so the file-scoped Steam callback handler can invoke it
	void OnSteamRichPresenceJoinRequested(const FString& InConnectionString);
private:
	bool SendInviteSteam(const FUniqueNetId& SenderId, FName SessionName, const TArray< TSharedRef<const FUniqueNetId> >& RemoteUserNetIds);
#endif // OSS_PLAYFAB_STEAM
	bool SendInvite(const FUniqueNetId& SenderId, FName SessionName, const TArray< TSharedRef<const FUniqueNetId> >& RemoteUserNetIds);
	void SaveInviteFromEvent(void* Context, const FString& ActivationUri);

#if defined(OSS_PLAYFAB_GDK_SUPPORT)
public:
	//Activity
	void SetMultiplayerActivityForSession(const FNamedOnlineSessionPtr& ExistingNamedSession);
	void SetMultiplayerActivity(PFLobbyHandle LobbyHandle, const PFEntityKey& EntityKey, const FOnlineSessionSettings& OnlineSessionSettings) const;
	void SetMultiplayerActivity(PFLobbyHandle LobbyHandle, const TArray<PFEntityKey>& EntityKeys, const FOnlineSessionSettings& OnlineSessionSettings) const;
	void DeleteMultiplayerActivity(PFLobbyHandle LobbyHandle, const PFEntityKey& EntityKey, const FOnlineSessionSettings& OnlineSessionSettings) const;
	void DeleteMultiplayerActivity(PFLobbyHandle LobbyHandle, const TArray<PFEntityKey>& EntityKeys, const FOnlineSessionSettings& OnlineSessionSettings) const;
	void RecordRecentlyMetPlayer(PFLobbyHandle LobbyHandle, const PFEntityKey& EntityKey, const PFEntityKey& RecentPlayerEntityKey, const FString& RecentPlayerPlatformIdStr) const;
	void RecordRecentlyMetPlayer(PFLobbyHandle LobbyHandle, const TArray<PFEntityKey>& EntityKeys, const PFEntityKey& RecentPlayerEntityKey, const FString& RecentPlayerPlatformIdStr) const;

private:
	bool SendInviteGDK(const FUniqueNetId& SenderId, FName SessionName, const TArray< TSharedRef<const FUniqueNetId> >& RemoteUserNetIds);
	void TickPendingInvites();
#endif // OSS_PLAYFAB_GDK_SUPPORT

private:
	//Helpers
	bool GetLobbyHandleBySessionName(const FName SessionName, PFLobbyHandle& LobbyHandle);
	FNamedOnlineSession* GetNamedSessionByLobbyHandle(const PFLobbyHandle& LobbyHandle);
	bool ValidateSessionForInvite(const FName SessionName);

public:
	//PlayFab Invites
	DEFINE_ONLINE_DELEGATE_THREE_PARAM(OnPlayFabMultiplayerInviteReceived, const PFEntityKey /*ListingEntityKey*/, const PFEntityKey /*InvitingEntityKey*/, const FString /*ConnectionString*/);

	bool SendSessionInviteToFriend_PlayFabMultiplayer(const PFEntityKey& LocalUserEntityKey, FName SessionName, const PFEntityKey& FriendEntityKey);
	bool SendSessionInviteToFriends_PlayFabMultiplayer(const PFEntityKey& LocalUserEntityKey, FName SessionName, const TArray<PFEntityKey>& RemoteUserEntityKeys);
	void OnInvitationReceived_PlayFabMultiplayer(const PFEntityKey& ListeningEntityKey, const PFEntityKey& InvitingEntityKey, const FString& InConnectionString);

private:
	friend struct FPlayFabSessionState;
};

typedef TSharedPtr<FOnlineSessionPlayFab, ESPMode::ThreadSafe> FOnlineSessionPlayFabPtr;