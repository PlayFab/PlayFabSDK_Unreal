//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "PlayFabSocketSelection.h"

namespace
{
	struct FTestSocket
	{
		const void* Network = nullptr;
	};

	const void* GetTestNetwork(FTestSocket* Socket)
	{
		return Socket->Network;
	}
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FPlayFabSocketSelectionLinkedSocketTest,
	"PlayFab.OSS.SocketSelection.LinkedSocketIsPreferred",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabSocketSelectionLinkedSocketTest::RunTest(const FString&)
{
	FTestSocket Network;
	FTestSocket Linked{ &Network };
	FTestSocket Newer{ &Network };
	TArray<FTestSocket*> ActiveSockets{ &Linked, &Newer };

	FTestSocket* Selected = PlayFabSocketSelection::SelectSocket(
		ActiveSockets, &Linked, static_cast<const void*>(nullptr), GetTestNetwork);

	TestEqual(TEXT("The linked socket is selected"), Selected, &Linked);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FPlayFabSocketSelectionNewestFallbackTest,
	"PlayFab.OSS.SocketSelection.NewestSocketIsFallback",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabSocketSelectionNewestFallbackTest::RunTest(const FString&)
{
	FTestSocket Older;
	FTestSocket Newer;
	TArray<FTestSocket*> ActiveSockets{ &Older, nullptr, &Newer };

	FTestSocket* Selected = PlayFabSocketSelection::SelectSocket(
		ActiveSockets, static_cast<FTestSocket*>(nullptr), static_cast<const void*>(nullptr), GetTestNetwork);

	TestEqual(TEXT("The newest active socket is selected"), Selected, &Newer);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FPlayFabSocketSelectionStaleLinkedSocketTest,
	"PlayFab.OSS.SocketSelection.StaleLinkedSocketIsIgnored",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabSocketSelectionStaleLinkedSocketTest::RunTest(const FString&)
{
	FTestSocket Stale;
	FTestSocket Older;
	FTestSocket Newer;
	TArray<FTestSocket*> ActiveSockets{ &Older, &Newer };

	FTestSocket* Selected = PlayFabSocketSelection::SelectSocket(
		ActiveSockets, &Stale, static_cast<const void*>(nullptr), GetTestNetwork);

	TestEqual(TEXT("A stale linked socket falls back to the newest active socket"), Selected, &Newer);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FPlayFabSocketSelectionMatchingNetworkTest,
	"PlayFab.OSS.SocketSelection.MessageRoutesToMatchingNetwork",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabSocketSelectionMatchingNetworkTest::RunTest(const FString&)
{
	int32 FirstNetwork;
	int32 SecondNetwork;
	int32 UnknownNetwork;
	FTestSocket First{ &FirstNetwork };
	FTestSocket Matching{ &SecondNetwork };
	FTestSocket Linked{ &FirstNetwork };
	TArray<FTestSocket*> ActiveSockets{ &First, &Matching, &Linked };

	FTestSocket* Selected = PlayFabSocketSelection::SelectSocket(
		ActiveSockets, &Linked, static_cast<const void*>(&SecondNetwork), GetTestNetwork);
	FTestSocket* Missing = PlayFabSocketSelection::SelectSocket(
		ActiveSockets, &Linked, static_cast<const void*>(&UnknownNetwork), GetTestNetwork);

	TestEqual(TEXT("The socket bound to the message network is selected"), Selected, &Matching);
	TestNull(TEXT("An unmatched network is not routed to another socket"), Missing);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FPlayFabSocketSelectionReconnectFallbackTest,
	"PlayFab.OSS.SocketSelection.NewestMatchingSocketIsReconnectFallback",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabSocketSelectionReconnectFallbackTest::RunTest(const FString&)
{
	int32 TargetNetwork;
	int32 OtherNetwork;
	FTestSocket OlderMatch{ &TargetNetwork };
	FTestSocket Linked{ &OtherNetwork };
	FTestSocket NewerMatch{ &TargetNetwork };
	TArray<FTestSocket*> ActiveSockets{ &OlderMatch, &Linked, &NewerMatch };

	FTestSocket* Selected = PlayFabSocketSelection::SelectSocket(
		ActiveSockets, &Linked, static_cast<const void*>(&TargetNetwork), GetTestNetwork);

	TestEqual(TEXT("Reconnect routing selects the newest socket for the target network"), Selected, &NewerMatch);
	return true;
}

#endif