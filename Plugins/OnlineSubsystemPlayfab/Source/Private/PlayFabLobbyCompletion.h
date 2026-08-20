//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystemPlayFabPackage.h"
#include "PlayFabSDKIncludes.h"

namespace PlayFabLobbyCompletion
{
	// The Lobby SDK does not currently expose a named constant for this HRESULT.
	constexpr HRESULT LobbyObjectPending = static_cast<HRESULT>(static_cast<int32>(0x89236205u));
	static_assert(FAILED(LobbyObjectPending), "LobbyObjectPending must remain a failing HRESULT.");

	using FLobbyStringGetter = HRESULT (*)(PFLobbyHandle Lobby, const char** Value);

	enum class EReadResult
	{
		Success,
		Pending,
		Failed,
	};

	struct FReadResult
	{
		EReadResult Result = EReadResult::Failed;
		HRESULT Error = S_OK;
		FString LobbyId;
		FString ConnectionString;
	};

	FReadResult TryReadCreatedLobby(
		HRESULT CompletionResult,
		PFLobbyHandle Lobby,
		FLobbyStringGetter GetLobbyId,
		FLobbyStringGetter GetConnectionString);
}
