//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"

namespace PlayFabDestroySessionCompletion
{
	class FState
	{
	public:
		bool Begin(bool bPartyLeaveComplete, bool bPartyLeaveResult);
		TOptional<bool> CompleteLobby(bool bSuccess);
		TOptional<bool> CompletePartyLeave(bool bSuccess);
		bool IsInProgress() const { return bInProgress; }

	private:
		TOptional<bool> TryComplete();

		bool bInProgress = false;
		bool bLobbyComplete = false;
		bool bLobbyResult = false;
		bool bPartyComplete = false;
		bool bPartyResult = false;
	};
}