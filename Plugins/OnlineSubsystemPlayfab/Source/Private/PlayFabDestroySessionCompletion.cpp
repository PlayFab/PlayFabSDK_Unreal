//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "PlayFabDestroySessionCompletion.h"

namespace PlayFabDestroySessionCompletion
{
	bool FState::Begin(bool bPartyLeaveComplete, bool bPartyLeaveResult)
	{
		if (bInProgress)
		{
			return false;
		}

		bInProgress = true;
		bLobbyComplete = false;
		bLobbyResult = false;
		bPartyComplete = bPartyLeaveComplete;
		bPartyResult = bPartyLeaveResult;
		return true;
	}

	TOptional<bool> FState::CompleteLobby(bool bSuccess)
	{
		if (!bInProgress || bLobbyComplete)
		{
			return {};
		}

		bLobbyComplete = true;
		bLobbyResult = bSuccess;
		return TryComplete();
	}

	TOptional<bool> FState::CompletePartyLeave(bool bSuccess)
	{
		if (!bInProgress || bPartyComplete)
		{
			return {};
		}

		bPartyComplete = true;
		bPartyResult = bSuccess;
		return TryComplete();
	}

	TOptional<bool> FState::TryComplete()
	{
		if (!bLobbyComplete || !bPartyComplete)
		{
			return {};
		}

		bInProgress = false;
		return bLobbyResult && bPartyResult;
	}
}