//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "OnlineSessionSettings.h"
#include "PlayFabSDKIncludes.h"

namespace PlayFabLobbyUpdate
{
	/** Mirrors one server-owned lobby property into session settings. A null value removes the setting. */
	void ApplyServerPropertyUpdate(FOnlineSessionSettings& SessionSettings, const char* Key, const char* Value);

	/** Mirrors server presence under _server_entity. A null entity clears both reserved server settings. */
	void ApplyServerUpdate(FOnlineSessionSettings& SessionSettings, const PFEntityKey* ServerEntity);

	/** Mirrors the lobby-service connection state under _server_connection_status. */
	void ApplyServerConnectionStatusUpdate(FOnlineSessionSettings& SessionSettings, PFLobbyServerConnectionStatus Status);
}