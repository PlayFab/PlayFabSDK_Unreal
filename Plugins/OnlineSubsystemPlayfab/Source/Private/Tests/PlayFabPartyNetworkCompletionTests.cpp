//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "PlayFabPartyNetworkCompletion.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FPlayFabPartyNetworkFailureNotificationTest,
	"PlayFab.OSS.Party.NetworkCompletion.FailureRoutesToEndpoint",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabPartyNetworkFailureNotificationTest::RunTest(const FString&)
{
	const TOptional<PlayFabPartyNetworkCompletion::FEndpointFailure> HostFailure = PlayFabPartyNetworkCompletion::GetEndpointFailure(
		PartyStateChangeResult::InternetConnectivityError,
		TEXT("host-network"),
		EPlayFabPartyNetworkState::JoiningNetwork_Host);
	TestTrue(TEXT("Host failure emits endpoint completion"), HostFailure.IsSet());
	if (HostFailure.IsSet())
	{
		TestEqual(TEXT("Host network ID is preserved"), HostFailure->NetworkId, FString(TEXT("host-network")));
		TestTrue(TEXT("Host failure is marked hosting"), HostFailure->bIsHosting);
	}
	const TOptional<PlayFabPartyNetworkCompletion::FEndpointFailure> PendingHostFailure = PlayFabPartyNetworkCompletion::GetEndpointFailure(
		PartyStateChangeResult::PartyServiceError,
		TEXT("pending-host-network"),
		EPlayFabPartyNetworkState::JoiningNetwork_Host_PendingEndpointCreation);
	TestTrue(TEXT("Pending host failure emits endpoint completion"), PendingHostFailure.IsSet());
	if (PendingHostFailure.IsSet())
	{
		TestTrue(TEXT("Pending host failure is marked hosting"), PendingHostFailure->bIsHosting);
	}

	const TOptional<PlayFabPartyNetworkCompletion::FEndpointFailure> ClientFailure = PlayFabPartyNetworkCompletion::GetEndpointFailure(
		PartyStateChangeResult::PartyServiceError,
		TEXT("client-network"),
		EPlayFabPartyNetworkState::JoiningNetwork_Client);
	TestTrue(TEXT("Client failure emits endpoint completion"), ClientFailure.IsSet());
	if (ClientFailure.IsSet())
	{
		TestEqual(TEXT("Client network ID is preserved"), ClientFailure->NetworkId, FString(TEXT("client-network")));
		TestFalse(TEXT("Client failure is not marked hosting"), ClientFailure->bIsHosting);
	}

	const TOptional<PlayFabPartyNetworkCompletion::FEndpointFailure> Success = PlayFabPartyNetworkCompletion::GetEndpointFailure(
		PartyStateChangeResult::Succeeded,
		TEXT("successful-network"),
		EPlayFabPartyNetworkState::JoiningNetwork_Host);
	TestFalse(TEXT("Successful network operation waits for endpoint creation"), Success.IsSet());

	const TOptional<PlayFabPartyNetworkCompletion::FEndpointFailure> CustomEndpointFailure =
		PlayFabPartyNetworkCompletion::GetEndpointCreationFailure(
			PartyStateChangeResult::PartyServiceError,
			TEXT("custom-endpoint-network"),
			EPlayFabPartyNetworkState::JoiningNetwork_Host_PendingEndpointCreation,
			true);
	TestFalse(TEXT("Optional custom endpoint failure does not fail the session"), CustomEndpointFailure.IsSet());

	const TOptional<PlayFabPartyNetworkCompletion::FEndpointFailure> NormalEndpointFailure =
		PlayFabPartyNetworkCompletion::GetEndpointCreationFailure(
			PartyStateChangeResult::PartyServiceError,
			TEXT("normal-endpoint-network"),
			EPlayFabPartyNetworkState::JoiningNetwork_Host_PendingEndpointCreation,
			false);
	TestTrue(TEXT("Normal endpoint failure still fails the session"), NormalEndpointFailure.IsSet());

	const TOptional<PlayFabPartyNetworkCompletion::FEndpointFailure> DestroyedWhileJoining =
		PlayFabPartyNetworkCompletion::GetEndpointFailureForNetworkState(
			TEXT("destroyed-host-network"),
			EPlayFabPartyNetworkState::JoiningNetwork_Host);
	TestTrue(TEXT("Network destruction while joining emits endpoint failure"), DestroyedWhileJoining.IsSet());
	if (DestroyedWhileJoining.IsSet())
	{
		TestEqual(TEXT("Destroyed network ID is preserved"), DestroyedWhileJoining->NetworkId, FString(TEXT("destroyed-host-network")));
		TestTrue(TEXT("Destroyed joining host is marked hosting"), DestroyedWhileJoining->bIsHosting);
	}

	const TOptional<PlayFabPartyNetworkCompletion::FEndpointFailure> DestroyedReadyNetwork =
		PlayFabPartyNetworkCompletion::GetEndpointFailureForNetworkState(
			TEXT("ready-network"),
			EPlayFabPartyNetworkState::NetworkReady);
	TestFalse(TEXT("Network destruction after setup does not complete a setup flow"), DestroyedReadyNetwork.IsSet());

	TArray<FString> Actions;
	int32 NetworkGeneration = 1;
	PlayFabPartyNetworkCompletion::CompleteFailure(
		ClientFailure,
		[&Actions, &NetworkGeneration]()
		{
			Actions.Add(TEXT("cleanup"));
			NetworkGeneration = 0;
		},
		[&Actions, &NetworkGeneration](const PlayFabPartyNetworkCompletion::FEndpointFailure&)
		{
			Actions.Add(TEXT("endpoint"));
			NetworkGeneration = 2;
		},
		[&Actions]() { Actions.Add(TEXT("operation")); });
	TestEqual(TEXT("All failure actions run"), Actions.Num(), 3);
	if (Actions.Num() == 3)
	{
		TestEqual(TEXT("Failure cleanup runs before endpoint completion"), Actions[0], FString(TEXT("cleanup")));
		TestEqual(TEXT("Endpoint completion runs before operation completion"), Actions[1], FString(TEXT("endpoint")));
		TestEqual(TEXT("Operation completion runs last"), Actions[2], FString(TEXT("operation")));
	}
	TestEqual(TEXT("Replacement network created by completion remains"), NetworkGeneration, 2);
	return true;
}

#endif