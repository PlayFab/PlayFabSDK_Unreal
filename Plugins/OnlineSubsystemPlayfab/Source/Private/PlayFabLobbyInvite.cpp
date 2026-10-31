//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "PlayFabLobbyInvite.h"
#include "OnlineSubsystemPlayFabPrivate.h"
#include "OnlineSubsystemPlayFabTypes.h"

namespace PlayFabLobbyInvite
{
	FOnlineSessionSearchResult CreateSearchResult(const FString& ConnectionString)
	{
		TSharedRef<FOnlineSessionInfoPlayFab> SessionInfo = MakeShared<FOnlineSessionInfoPlayFab>();
		SessionInfo->ConnectionString = ConnectionString;

		FOnlineSessionSearchResult SearchResult;
		SearchResult.Session.SessionInfo = SessionInfo;
		SearchResult.Session.OwningUserId = FUniqueNetIdPlayFab::EmptyId();
		SearchResult.Session.SessionSettings.Set(SETTING_CONNECTION_STRING, ConnectionString, EOnlineDataAdvertisementType::ViaOnlineService);
		return SearchResult;
	}

	FOnlineSessionSearchResult CreateSearchResult(const char* ConnectionString)
	{
		return CreateSearchResult(ConnectionString != nullptr ? UTF8_TO_TCHAR(ConnectionString) : FString());
	}

	FStandardInvite CreateStandardInvite(const FString& ConnectionString, int32 ControllerIndex, FUniqueNetIdPtr LocalUserId)
	{
		FStandardInvite Invite;
		Invite.bWasSuccessful = LocalUserId.IsValid() && !ConnectionString.IsEmpty();
		Invite.ControllerIndex = ControllerIndex;
		Invite.LocalUserId = MoveTemp(LocalUserId);
		Invite.SearchResult = CreateSearchResult(ConnectionString);
		return Invite;
	}
}