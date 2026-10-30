//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "OnlineSubsystemPlayFabPrivate.h"
#include "OnlineSubsystemPlayFabTypes.h"
#include "PlayFabLobbyInvite.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FPlayFabStandardLobbyInviteTest,
	"PlayFab.OSS.Lobby.Invites.StandardDelegatePayload",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabStandardLobbyInviteTest::RunTest(const FString&)
{
	const FUniqueNetIdPtr LocalUserId = FUniqueNetIdPlayFab::Create(TEXT("local-user"));
	const PlayFabLobbyInvite::FStandardInvite Invite = PlayFabLobbyInvite::CreateStandardInvite(
		TEXT("invite-connection-string"),
		0,
		LocalUserId);

	TestTrue(TEXT("Invite is successful when the local user is valid"), Invite.bWasSuccessful);
	TestEqual(TEXT("Controller index is preserved"), Invite.ControllerIndex, 0);
	TestTrue(TEXT("Local user is preserved"), Invite.LocalUserId == LocalUserId);
	TestTrue(TEXT("Search result is valid"), Invite.SearchResult.IsValid());

	const FOnlineSessionInfoPlayFabPtr SessionInfo = StaticCastSharedPtr<FOnlineSessionInfoPlayFab>(Invite.SearchResult.Session.SessionInfo);
	TestTrue(TEXT("PlayFab session info is present"), SessionInfo.IsValid());
	if (SessionInfo.IsValid())
	{
		TestEqual(TEXT("Session info contains the invite connection string"), SessionInfo->ConnectionString, FString(TEXT("invite-connection-string")));
	}

	FString ConnectionString;
	TestTrue(
		TEXT("Session settings contain the invite connection string"),
		Invite.SearchResult.Session.SessionSettings.Get(SETTING_CONNECTION_STRING, ConnectionString));
	TestEqual(TEXT("Session setting value is preserved"), ConnectionString, FString(TEXT("invite-connection-string")));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FPlayFabStandardLobbyInviteMissingUserTest,
	"PlayFab.OSS.Lobby.Invites.MissingLocalUserReportsFailure",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabStandardLobbyInviteMissingUserTest::RunTest(const FString&)
{
	const PlayFabLobbyInvite::FStandardInvite Invite = PlayFabLobbyInvite::CreateStandardInvite(
		TEXT("invite-connection-string"),
		0,
		nullptr);

	TestFalse(TEXT("Invite reports failure without a local user"), Invite.bWasSuccessful);
	TestFalse(TEXT("Missing local user remains null"), Invite.LocalUserId.IsValid());
	TestTrue(TEXT("Invite search result remains available"), Invite.SearchResult.IsValid());

	const PlayFabLobbyInvite::FStandardInvite MissingConnectionString = PlayFabLobbyInvite::CreateStandardInvite(
		FString(),
		0,
		FUniqueNetIdPlayFab::Create(TEXT("local-user")));
	TestFalse(TEXT("Invite reports failure without a connection string"), MissingConnectionString.bWasSuccessful);

	const FOnlineSessionSearchResult NullConnectionSearchResult = PlayFabLobbyInvite::CreateSearchResult(static_cast<const char*>(nullptr));
	const FOnlineSessionInfoPlayFabPtr NullConnectionSessionInfo = StaticCastSharedPtr<FOnlineSessionInfoPlayFab>(NullConnectionSearchResult.Session.SessionInfo);
	TestTrue(TEXT("Null connection string still produces session info"), NullConnectionSessionInfo.IsValid());
	if (NullConnectionSessionInfo.IsValid())
	{
		TestTrue(TEXT("Null connection string becomes empty"), NullConnectionSessionInfo->ConnectionString.IsEmpty());
	}
	return true;
}

#endif