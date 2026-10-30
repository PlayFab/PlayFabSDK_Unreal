//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "PlayFabLobbyUpdate.h"

namespace PlayFabLobbyUpdate
{
	void ApplyServerPropertyUpdate(FOnlineSessionSettings& SessionSettings, const char* Key, const char* Value)
	{
		const FName SettingName(UTF8_TO_TCHAR(Key));
		if (Value == nullptr)
		{
			SessionSettings.Remove(SettingName);
			return;
		}

		SessionSettings.Set(SettingName, FString(UTF8_TO_TCHAR(Value)), EOnlineDataAdvertisementType::ViaOnlineService);
	}

	void ApplyServerUpdate(FOnlineSessionSettings& SessionSettings, const PFEntityKey* ServerEntity)
	{
		if (ServerEntity == nullptr)
		{
			SessionSettings.Remove(FName(TEXT("_server_entity")));
			SessionSettings.Remove(FName(TEXT("_server_connection_status")));
			return;
		}

		SessionSettings.Set(
			FName(TEXT("_server_entity")),
			FString(UTF8_TO_TCHAR(ServerEntity->id)),
			EOnlineDataAdvertisementType::ViaOnlineService);
	}

	void ApplyServerConnectionStatusUpdate(FOnlineSessionSettings& SessionSettings, PFLobbyServerConnectionStatus Status)
	{
		if (!SessionSettings.Settings.Contains(FName(TEXT("_server_entity"))))
		{
			return;
		}

		const FString StatusString = Status == PFLobbyServerConnectionStatus::Connected ? TEXT("Connected") : TEXT("NotConnected");
		SessionSettings.Set(FName(TEXT("_server_connection_status")), StatusString, EOnlineDataAdvertisementType::ViaOnlineService);
	}
}