//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "PlayFabLobbyCompletion.h"

namespace
{
	int32 LobbyIdCallCount = 0;
	int32 ConnectionStringCallCount = 0;
	bool bReturnPendingLobbyId = false;
	bool bReturnPendingConnectionString = false;

	HRESULT GetTestLobbyId(PFLobbyHandle, const char** Value)
	{
		++LobbyIdCallCount;
		if (bReturnPendingLobbyId)
		{
			return PlayFabLobbyCompletion::LobbyObjectPending;
		}

		*Value = "test-lobby";
		return S_OK;
	}

	HRESULT GetTestConnectionString(PFLobbyHandle, const char** Value)
	{
		++ConnectionStringCallCount;
		if (bReturnPendingConnectionString)
		{
			return PlayFabLobbyCompletion::LobbyObjectPending;
		}

		*Value = "test-connection";
		return S_OK;
	}

	void ResetTestGetters()
	{
		LobbyIdCallCount = 0;
		ConnectionStringCallCount = 0;
		bReturnPendingLobbyId = false;
		bReturnPendingConnectionString = false;
	}
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FPlayFabLobbyFailedCompletionTest,
	"PlayFab.OSS.Lobby.CreateCompletion.FailedResultSkipsLobbyAccess",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabLobbyFailedCompletionTest::RunTest(const FString&)
{
	ResetTestGetters();
	const HRESULT CompletionFailure = E_FAIL;

	const PlayFabLobbyCompletion::FReadResult Result = PlayFabLobbyCompletion::TryReadCreatedLobby(
		CompletionFailure,
		nullptr,
		GetTestLobbyId,
		GetTestConnectionString);

	TestEqual(TEXT("Failed completion is preserved"), Result.Error, CompletionFailure);
	TestEqual(TEXT("Result is failed"), Result.Result, PlayFabLobbyCompletion::EReadResult::Failed);
	TestEqual(TEXT("Lobby ID is not read"), LobbyIdCallCount, 0);
	TestEqual(TEXT("Connection string is not read"), ConnectionStringCallCount, 0);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FPlayFabLobbyPendingIdTest,
	"PlayFab.OSS.Lobby.CreateCompletion.PendingLobbyIdIsDeferred",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabLobbyPendingIdTest::RunTest(const FString&)
{
	ResetTestGetters();
	bReturnPendingLobbyId = true;

	const PlayFabLobbyCompletion::FReadResult Result = PlayFabLobbyCompletion::TryReadCreatedLobby(
		S_OK,
		nullptr,
		GetTestLobbyId,
		GetTestConnectionString);

	TestEqual(TEXT("Result is pending"), Result.Result, PlayFabLobbyCompletion::EReadResult::Pending);
	TestEqual(TEXT("Pending error is preserved"), Result.Error, PlayFabLobbyCompletion::LobbyObjectPending);
	TestEqual(TEXT("Lobby ID is read once"), LobbyIdCallCount, 1);
	TestEqual(TEXT("Connection string is not read"), ConnectionStringCallCount, 0);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FPlayFabLobbyPendingConnectionTest,
	"PlayFab.OSS.Lobby.CreateCompletion.PendingConnectionIsDeferredThenSucceeds",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabLobbyPendingConnectionTest::RunTest(const FString&)
{
	ResetTestGetters();
	bReturnPendingConnectionString = true;

	const PlayFabLobbyCompletion::FReadResult PendingResult = PlayFabLobbyCompletion::TryReadCreatedLobby(
		S_OK,
		nullptr,
		GetTestLobbyId,
		GetTestConnectionString);

	TestEqual(TEXT("First result is pending"), PendingResult.Result, PlayFabLobbyCompletion::EReadResult::Pending);
	TestEqual(TEXT("Pending error is preserved"), PendingResult.Error, PlayFabLobbyCompletion::LobbyObjectPending);

	bReturnPendingConnectionString = false;
	const PlayFabLobbyCompletion::FReadResult SuccessResult = PlayFabLobbyCompletion::TryReadCreatedLobby(
		S_OK,
		nullptr,
		GetTestLobbyId,
		GetTestConnectionString);

	TestEqual(TEXT("Retry succeeds"), SuccessResult.Result, PlayFabLobbyCompletion::EReadResult::Success);
	TestEqual(TEXT("Lobby ID is populated"), SuccessResult.LobbyId, FString(TEXT("test-lobby")));
	TestEqual(TEXT("Connection string is populated"), SuccessResult.ConnectionString, FString(TEXT("test-connection")));
	return true;
}

#endif
