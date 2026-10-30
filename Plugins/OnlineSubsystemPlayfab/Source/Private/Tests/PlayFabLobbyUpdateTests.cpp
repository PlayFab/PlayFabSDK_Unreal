//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "PlayFabLobbyUpdate.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FPlayFabServerPropertyUpdateTest,
	"PlayFab.OSS.Lobby.ServerUpdates.PropertySetAndRemove",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabServerPropertyUpdateTest::RunTest(const FString&)
{
	FOnlineSessionSettings SessionSettings;
	const FName SettingName(TEXT("server_map"));

	PlayFabLobbyUpdate::ApplyServerPropertyUpdate(SessionSettings, "server_map", "arena");

	FString Value;
	TestTrue(TEXT("Server property is added"), SessionSettings.Get(SettingName, Value));
	TestEqual(TEXT("Server property value is preserved"), Value, FString(TEXT("arena")));
	TestEqual(
		TEXT("Server property is advertised through the online service"),
		SessionSettings.Settings.FindChecked(SettingName).AdvertisementType,
		EOnlineDataAdvertisementType::ViaOnlineService);

	PlayFabLobbyUpdate::ApplyServerPropertyUpdate(SessionSettings, "server_map", "");
	TestTrue(TEXT("Empty server property remains present"), SessionSettings.Get(SettingName, Value));
	TestTrue(TEXT("Empty server property remains empty"), Value.IsEmpty());

	PlayFabLobbyUpdate::ApplyServerPropertyUpdate(SessionSettings, "server_map", nullptr);
	TestFalse(TEXT("Removed server property is absent"), SessionSettings.Settings.Contains(SettingName));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FPlayFabServerEntityUpdateTest,
	"PlayFab.OSS.Lobby.ServerUpdates.EntityJoinAndLeave",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabServerEntityUpdateTest::RunTest(const FString&)
{
	FOnlineSessionSettings SessionSettings;
	PFEntityKey ServerEntity{};
	ServerEntity.id = "server-entity-id";
	ServerEntity.type = "game_server";

	PlayFabLobbyUpdate::ApplyServerUpdate(SessionSettings, &ServerEntity);

	FString EntityId;
	TestTrue(TEXT("Server entity is added"), SessionSettings.Get(FName(TEXT("_server_entity")), EntityId));
	TestEqual(TEXT("Server entity ID is preserved"), EntityId, FString(TEXT("server-entity-id")));
	TestEqual(
		TEXT("Server entity is advertised through the online service"),
		SessionSettings.Settings.FindChecked(FName(TEXT("_server_entity"))).AdvertisementType,
		EOnlineDataAdvertisementType::ViaOnlineService);

	PlayFabLobbyUpdate::ApplyServerConnectionStatusUpdate(SessionSettings, PFLobbyServerConnectionStatus::Connected);
	PlayFabLobbyUpdate::ApplyServerUpdate(SessionSettings, nullptr);
	PlayFabLobbyUpdate::ApplyServerConnectionStatusUpdate(SessionSettings, PFLobbyServerConnectionStatus::NotConnected);

	TestFalse(TEXT("Departed server entity is removed"), SessionSettings.Settings.Contains(FName(TEXT("_server_entity"))));
	TestFalse(TEXT("Departed server status remains removed when both updates arrive together"), SessionSettings.Settings.Contains(FName(TEXT("_server_connection_status"))));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FPlayFabServerConnectionStatusUpdateTest,
	"PlayFab.OSS.Lobby.ServerUpdates.ConnectionStatus",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabServerConnectionStatusUpdateTest::RunTest(const FString&)
{
	FOnlineSessionSettings SessionSettings;
	const FName SettingName(TEXT("_server_connection_status"));
	PFEntityKey ServerEntity{};
	ServerEntity.id = "server-entity-id";
	ServerEntity.type = "game_server";
	PlayFabLobbyUpdate::ApplyServerUpdate(SessionSettings, &ServerEntity);

	PlayFabLobbyUpdate::ApplyServerConnectionStatusUpdate(SessionSettings, PFLobbyServerConnectionStatus::Connected);
	FString Value;
	TestTrue(TEXT("Connected status is added"), SessionSettings.Get(SettingName, Value));
	TestEqual(TEXT("Connected status is surfaced"), Value, FString(TEXT("Connected")));
	TestEqual(
		TEXT("Connection status is advertised through the online service"),
		SessionSettings.Settings.FindChecked(SettingName).AdvertisementType,
		EOnlineDataAdvertisementType::ViaOnlineService);

	PlayFabLobbyUpdate::ApplyServerConnectionStatusUpdate(SessionSettings, PFLobbyServerConnectionStatus::NotConnected);
	TestTrue(TEXT("Not-connected status remains available"), SessionSettings.Get(SettingName, Value));
	TestEqual(TEXT("Not-connected status is surfaced"), Value, FString(TEXT("NotConnected")));
	return true;
}

#endif