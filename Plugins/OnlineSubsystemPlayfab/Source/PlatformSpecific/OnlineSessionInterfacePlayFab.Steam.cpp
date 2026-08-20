//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#if defined(OSS_PLAYFAB_STEAM)
#include "OnlineSessionInterfacePlayFab.h"
#include "OnlineSubsystemPlayFab.h"
#include "PlayFabHelpers.h"
#include "Misc/CommandLine.h"

THIRD_PARTY_INCLUDES_START
#include "steam/steam_api.h"
THIRD_PARTY_INCLUDES_END

// File-scoped Steam callback handler for GameRichPresenceJoinRequested_t.
// This bridges the Steamworks C++ callback mechanism to the FOnlineSessionPlayFab instance.
class FSteamRichPresenceJoinHandler
{
public:
	FSteamRichPresenceJoinHandler()
		: SessionInterface(nullptr)
	{
	}

	void SetSessionInterface(FOnlineSessionPlayFab* InSessionInterface)
	{
		SessionInterface = InSessionInterface;
	}

	void ClearSessionInterface()
	{
		SessionInterface = nullptr;
	}

private:
	STEAM_CALLBACK(FSteamRichPresenceJoinHandler, OnGameRichPresenceJoinRequested, GameRichPresenceJoinRequested_t);
	FOnlineSessionPlayFab* SessionInterface;
};

void FSteamRichPresenceJoinHandler::OnGameRichPresenceJoinRequested(GameRichPresenceJoinRequested_t* pParam)
{
	if (SessionInterface != nullptr && pParam != nullptr)
	{
		FString ConnectString(UTF8_TO_TCHAR(pParam->m_rgchConnect));
		SessionInterface->OnSteamRichPresenceJoinRequested(ConnectString);
	}
}

static TUniquePtr<FSteamRichPresenceJoinHandler> GSteamRichPresenceJoinHandler;

// Prefix added to PlayFab connection strings when published via Steam Rich Presence or InviteUserToGame.
// This distinguishes PlayFab invites from native Steam invites (which use SteamConnectIP= format),
// allowing OnSteamRichPresenceJoinRequested to handle only PlayFab-originated connection strings.
static const TCHAR* PlayFabConnectPrefix = TEXT("playfab:");
static const char* PlayFabConnectPrefixAnsi = "playfab:";
static const int32 PlayFabConnectPrefixLen = 8; // FCString::Strlen(PlayFabConnectPrefix)

bool FOnlineSessionPlayFab::SendInviteSteam(const FUniqueNetId& SenderId, FName SessionName, const TArray< TSharedRef<const FUniqueNetId> >& RemoteUserNetIds)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::SendInviteSteam()"));

	if (!ValidateSessionForInvite(SessionName))
	{
		return false;
	}

	// No native Steam session (e.g. server-created lobby).
	// Use ISteamFriends::InviteUserToGame with the PlayFab lobby connection string directly.
	ISteamFriends* SteamFriendsPtr = SteamFriends();
	if (SteamFriendsPtr == nullptr)
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::SendInviteSteam: SteamFriends API not available"));
		return false;
	}

	PFLobbyHandle LobbyHandle{};
	if (!GetLobbyHandleBySessionName(SessionName, LobbyHandle))
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::SendInviteSteam: No lobby found for session %s"), *SessionName.ToString());
		return false;
	}

	const char* ConnectionStr = nullptr;
	HRESULT Hr = PFLobbyGetConnectionString(LobbyHandle, &ConnectionStr);
	if (FAILED(Hr) || ConnectionStr == nullptr)
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::SendInviteSteam: Failed to get lobby connection string"));
		return false;
	}

	// Prepend the PlayFab prefix so receivers can distinguish PlayFab invites from native Steam invites.
	int32 ConnectionStrLen = FCStringAnsi::Strlen(ConnectionStr);
	int32 PrefixedLen = PlayFabConnectPrefixLen + ConnectionStrLen;
	if (PrefixedLen > 256)
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::SendInviteSteam: Prefixed connection string exceeds Steam's 256 char limit (%d chars)"), PrefixedLen);
		return false;
	}

	TArray<char> PrefixedConnectionStr;
	PrefixedConnectionStr.SetNumUninitialized(PrefixedLen + 1);
	FCStringAnsi::Snprintf(PrefixedConnectionStr.GetData(), PrefixedLen + 1, "%s%s", PlayFabConnectPrefixAnsi, ConnectionStr);

	bool bAllSucceeded = true;
	for (const TSharedRef<const FUniqueNetId>& RemoteId : RemoteUserNetIds)
	{
		// Resolve to native Steam ID
		FUniqueNetIdPtr NativeNetId = OSSPlayFab->GetNativeNetId(RemoteId);
		if (!NativeNetId.IsValid())
		{
			UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::SendInviteSteam: Failed to resolve native Steam ID for %s"), *RemoteId->ToString());
			bAllSucceeded = false;
			continue;
		}

		uint64 SteamId64 = FCString::Strtoui64(*NativeNetId->ToString(), nullptr, 10);
		CSteamID SteamId(SteamId64);

		if (!SteamFriendsPtr->InviteUserToGame(SteamId, PrefixedConnectionStr.GetData()))
		{
			UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::SendInviteSteam: InviteUserToGame failed for Steam ID %llu"), SteamId64);
			bAllSucceeded = false;
		}
		else
		{
			UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::SendInviteSteam: Successfully invited Steam ID %llu"), SteamId64);
		}
	}

	return bAllSucceeded;
}

void FOnlineSessionPlayFab::RegisterForSteamInvites()
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::RegisterForSteamInvites()"));

	// Steam invite callbacks are client-only; SteamFriends() is not available on dedicated servers
	if (IsRunningDedicatedServer())
	{
		bSteamInviteCallbackRegistered = true; // Prevent Tick from retrying
		return;
	}

	if (bSteamInviteCallbackRegistered)
	{
		return;
	}

	ISteamFriends* SteamFriendsPtr = SteamFriends();
	if (SteamFriendsPtr == nullptr)
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::RegisterForSteamInvites: SteamFriends API not available, will retry in Tick"));
		return;
	}

	bSteamInviteCallbackRegistered = true;

	// Create the callback handler for GameRichPresenceJoinRequested_t.
	// This fires when a friend clicks "Join Game" on our profile or accepts an invite via InviteUserToGame.
	if (!GSteamRichPresenceJoinHandler.IsValid())
	{
		GSteamRichPresenceJoinHandler = MakeUnique<FSteamRichPresenceJoinHandler>();
	}
	GSteamRichPresenceJoinHandler->SetSessionInterface(this);

	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::RegisterForSteamInvites: Steam invite callback registered"));

	CheckSteamCommandLineLaunch();
}

void FOnlineSessionPlayFab::UnregisterForSteamInvites()
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::UnregisterForSteamInvites()"));

	if (bSteamInviteCallbackRegistered)
	{
		ClearSteamRichPresenceConnect();

		if (GSteamRichPresenceJoinHandler.IsValid())
		{
			GSteamRichPresenceJoinHandler->ClearSessionInterface();
			GSteamRichPresenceJoinHandler.Reset();
		}

		bSteamInviteCallbackRegistered = false;
	}
}

void FOnlineSessionPlayFab::SetSteamRichPresenceConnect(const FString& InPlayFabConnectionString)
{
	ISteamFriends* SteamFriendsPtr = SteamFriends();
	if (SteamFriendsPtr == nullptr)
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::SetSteamRichPresenceConnect: SteamFriends API not available"));
		return;
	}

	if (InPlayFabConnectionString.IsEmpty())
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::SetSteamRichPresenceConnect: Connection string is empty"));
		return;
	}

	// Prepend the PlayFab prefix so receivers can distinguish PlayFab invites from native Steam invites.
	FString ConnectValue = FString::Printf(TEXT("%s%s"), PlayFabConnectPrefix, *InPlayFabConnectionString);
	if (ConnectValue.Len() > 256)
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::SetSteamRichPresenceConnect: Prefixed connection string exceeds 256 char limit (%d chars)"), ConnectValue.Len());
		return;
	}

	SteamFriendsPtr->SetRichPresence("connect", TCHAR_TO_UTF8(*ConnectValue));
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::SetSteamRichPresenceConnect: Set Rich Presence connect key"));
}

void FOnlineSessionPlayFab::ClearSteamRichPresenceConnect()
{
	ISteamFriends* SteamFriendsPtr = SteamFriends();
	if (SteamFriendsPtr == nullptr)
	{
		return;
	}

	SteamFriendsPtr->SetRichPresence("connect", "");
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::ClearSteamRichPresenceConnect: Cleared Rich Presence connect key"));
}

void FOnlineSessionPlayFab::OnSteamRichPresenceJoinRequested(const FString& InConnectionString)
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnSteamRichPresenceJoinRequested: ConnectionString=%s"), *InConnectionString);

	if (InConnectionString.IsEmpty())
	{
		UE_LOG_ONLINE_SESSION(Warning, TEXT("FOnlineSessionPlayFab::OnSteamRichPresenceJoinRequested: Empty connection string"));
		return;
	}

	// Only handle connection strings with the PlayFab prefix. The native Steam OSS also registers
	// for GameRichPresenceJoinRequested_t and handles its own SteamConnectIP= format strings.
	// Without this check, both OSS layers would attempt to handle every callback.
	if (!InConnectionString.StartsWith(PlayFabConnectPrefix))
	{
		UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnSteamRichPresenceJoinRequested: Connection string does not have PlayFab prefix, deferring to native OSS"));
		return;
	}

	// Strip the prefix to recover the original PlayFab lobby connection string.
	FString ConnectionString = InConnectionString.Mid(PlayFabConnectPrefixLen);

	// Check if the local user identity is ready. If not, defer the invite to be processed in Tick.
	IOnlineIdentityPtr IdentityIntPtr = OSSPlayFab->GetIdentityInterface();
	FUniqueNetIdPtr UserId;
	if (IdentityIntPtr.IsValid())
	{
		UserId = IdentityIntPtr->GetUniquePlayerId(0);
	}

	if (!UserId.IsValid())
	{
		UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::OnSteamRichPresenceJoinRequested: User identity not ready, deferring invite"));
		PendingSteamInviteConnectionString = InConnectionString;
		return;
	}

	FOnlineSessionSearchResult SearchResult;
	SearchResult.Session.SessionSettings.Set(SETTING_CONNECTION_STRING, ConnectionString, EOnlineDataAdvertisementType::ViaOnlineService);

	TSharedRef<FOnlineSessionInfoPlayFab> NewSessionInfo = MakeShared<FOnlineSessionInfoPlayFab>();
	NewSessionInfo->ConnectionString = ConnectionString;
	SearchResult.Session.SessionInfo = NewSessionInfo;
	SearchResult.Session.OwningUserId = FUniqueNetIdPlayFab::EmptyId();

	const int32 ControllerId = 0;
	OSSPlayFab->ExecuteNextTick([this, ControllerId, UserId, SearchResult]()
	{
		TriggerOnSessionUserInviteAcceptedDelegates(true, ControllerId, UserId, SearchResult);
	});
}

void FOnlineSessionPlayFab::TickPendingSteamInvite()
{
	if (PendingSteamInviteConnectionString.IsEmpty())
	{
		return;
	}

	IOnlineIdentityPtr IdentityIntPtr = OSSPlayFab->GetIdentityInterface();
	FUniqueNetIdPtr UserId;
	if (IdentityIntPtr.IsValid())
	{
		UserId = IdentityIntPtr->GetUniquePlayerId(0);
	}

	if (!UserId.IsValid())
	{
		return;
	}

	FString ConnectionStr = MoveTemp(PendingSteamInviteConnectionString);
	PendingSteamInviteConnectionString.Empty();

	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::TickPendingSteamInvite: Processing deferred invite"));
	OnSteamRichPresenceJoinRequested(ConnectionStr);
}

void FOnlineSessionPlayFab::CheckSteamCommandLineLaunch()
{
	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::CheckSteamCommandLineLaunch()"));

	FString ConnectString;
	if (FParse::Value(FCommandLine::Get(), TEXT("+connect "), ConnectString))
	{
		ConnectString.TrimStartAndEndInline();
		if (!ConnectString.IsEmpty())
		{
			UE_LOG_ONLINE_SESSION(Log, TEXT("FOnlineSessionPlayFab::CheckSteamCommandLineLaunch: Found +connect command line arg: %s"), *ConnectString);
			OnSteamRichPresenceJoinRequested(ConnectString);
		}
	}
}

#endif // OSS_PLAYFAB_STEAM
