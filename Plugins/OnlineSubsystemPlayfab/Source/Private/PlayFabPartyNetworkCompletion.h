//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "PlayFabPartyNetwork.h"

namespace PlayFabPartyNetworkCompletion
{
	struct FEndpointFailure
	{
		FString NetworkId;
		bool bIsHosting = false;
	};

	/** Returns the endpoint failure that completes a session flow, or unset while the operation should continue. */
	TOptional<FEndpointFailure> GetEndpointFailure(
		PartyStateChangeResult Result,
		const FString& NetworkId,
		EPlayFabPartyNetworkState NetworkState);

	TOptional<FEndpointFailure> GetEndpointFailureForNetworkState(
		const FString& NetworkId,
		EPlayFabPartyNetworkState NetworkState);

	TOptional<FEndpointFailure> GetEndpointCreationFailure(
		PartyStateChangeResult Result,
		const FString& NetworkId,
		EPlayFabPartyNetworkState NetworkState,
		bool bIsCustomEndpointOperation);

	void CompleteFailure(
		const TOptional<FEndpointFailure>& Failure,
		TFunctionRef<void()> Cleanup,
		TFunctionRef<void(const FEndpointFailure&)> TriggerEndpointFailure,
		TFunctionRef<void()> TriggerOperationFailure);
}
