//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "PlayFabLobbyCompletion.h"

namespace PlayFabLobbyCompletion
{
	FReadResult TryReadCreatedLobby(
		HRESULT CompletionResult,
		PFLobbyHandle Lobby,
		FLobbyStringGetter GetLobbyId,
		FLobbyStringGetter GetConnectionString)
	{
		FReadResult ReadResult;

		if (FAILED(CompletionResult))
		{
			ReadResult.Error = CompletionResult;
			return ReadResult;
		}

		const char* LobbyId = nullptr;
		HRESULT Hr = GetLobbyId(Lobby, &LobbyId);
		if (FAILED(Hr))
		{
			ReadResult.Result = Hr == LobbyObjectPending ? EReadResult::Pending : EReadResult::Failed;
			ReadResult.Error = Hr;
			return ReadResult;
		}

		const char* ConnectionString = nullptr;
		Hr = GetConnectionString(Lobby, &ConnectionString);
		if (FAILED(Hr))
		{
			ReadResult.Result = Hr == LobbyObjectPending ? EReadResult::Pending : EReadResult::Failed;
			ReadResult.Error = Hr;
			return ReadResult;
		}

		ReadResult.Result = EReadResult::Success;
		ReadResult.LobbyId = UTF8_TO_TCHAR(LobbyId);
		ReadResult.ConnectionString = UTF8_TO_TCHAR(ConnectionString);
		return ReadResult;
	}
}
