//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "OnlineSessionSettings.h"

namespace PlayFabLobbyInvite
{
	struct FStandardInvite
	{
		bool bWasSuccessful = false;
		int32 ControllerIndex = INDEX_NONE;
		FUniqueNetIdPtr LocalUserId;
		FOnlineSessionSearchResult SearchResult;
	};

	/** Creates the session search result exposed through Unreal's standard invite-accepted delegate. */
	FOnlineSessionSearchResult CreateSearchResult(const FString& ConnectionString);
	FOnlineSessionSearchResult CreateSearchResult(const char* ConnectionString);

	/** Builds the standard delegate arguments. A missing local user reports an unsuccessful acceptance. */
	FStandardInvite CreateStandardInvite(const FString& ConnectionString, int32 ControllerIndex, FUniqueNetIdPtr LocalUserId);
}