//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "PlayFabDestroySessionCompletion.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FPlayFabDestroySessionCompletionTest,
	"PlayFab.OSS.Session.DestroyCompletion.WaitsForLobbyAndParty",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabDestroySessionCompletionTest::RunTest(const FString&)
{
	PlayFabDestroySessionCompletion::FState LobbyFirst;
	TestTrue(TEXT("Destroy operation begins"), LobbyFirst.Begin(false, false));
	TestFalse(TEXT("A second destroy cannot overwrite pending state"), LobbyFirst.Begin(false, false));
	TestFalse(TEXT("Lobby-first completion waits for Party"), LobbyFirst.CompleteLobby(true).IsSet());
	const TOptional<bool> LobbyFirstResult = LobbyFirst.CompletePartyLeave(true);
	TestTrue(TEXT("Party completion releases lobby-first destroy"), LobbyFirstResult.IsSet());
	TestTrue(TEXT("Lobby-first destroy succeeds"), LobbyFirstResult.Get(false));
	TestFalse(TEXT("Duplicate Party completion is ignored"), LobbyFirst.CompletePartyLeave(true).IsSet());

	PlayFabDestroySessionCompletion::FState NetworkDestroyedGate;
	TestTrue(TEXT("Network-destroy-gated operation begins"), NetworkDestroyedGate.Begin(false, false));
	TestFalse(TEXT("Lobby completion waits through successful leave callback"), NetworkDestroyedGate.CompleteLobby(true).IsSet());
	TestTrue(TEXT("Destroy remains pending until network destruction"), NetworkDestroyedGate.IsInProgress());
	const TOptional<bool> NetworkDestroyedResult = NetworkDestroyedGate.CompletePartyLeave(true);
	TestTrue(TEXT("Network destruction completes the Party gate"), NetworkDestroyedResult.IsSet());
	TestTrue(TEXT("Network-destroy-gated operation succeeds"), NetworkDestroyedResult.Get(false));

	PlayFabDestroySessionCompletion::FState PartyFirst;
	TestTrue(TEXT("Party-first destroy begins"), PartyFirst.Begin(false, false));
	TestFalse(TEXT("Party-first completion waits for lobby"), PartyFirst.CompletePartyLeave(true).IsSet());
	const TOptional<bool> PartyFirstResult = PartyFirst.CompleteLobby(true);
	TestTrue(TEXT("Lobby completion releases Party-first destroy"), PartyFirstResult.IsSet());
	TestTrue(TEXT("Party-first destroy succeeds"), PartyFirstResult.Get(false));

	PlayFabDestroySessionCompletion::FState FailedParty;
	TestTrue(TEXT("Failed-Party destroy begins"), FailedParty.Begin(false, false));
	TestFalse(TEXT("Failed Party still waits for lobby"), FailedParty.CompletePartyLeave(false).IsSet());
	const TOptional<bool> FailedPartyResult = FailedParty.CompleteLobby(true);
	TestTrue(TEXT("Failed Party destroy completes after lobby"), FailedPartyResult.IsSet());
	TestFalse(TEXT("Failed Party result is merged"), FailedPartyResult.Get(true));

	PlayFabDestroySessionCompletion::FState NoParty;
	TestTrue(TEXT("No-Party destroy begins with Party gate complete"), NoParty.Begin(true, true));
	const TOptional<bool> NoPartyResult = NoParty.CompleteLobby(true);
	TestTrue(TEXT("No-Party destroy completes with lobby"), NoPartyResult.IsSet());
	TestTrue(TEXT("No-Party destroy succeeds"), NoPartyResult.Get(false));
	return true;
}

#endif