//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "PlayFabPartyNetworkCompletion.h"

namespace PlayFabPartyNetworkCompletion
{
	TOptional<FEndpointFailure> GetEndpointFailure(
		PartyStateChangeResult Result,
		const FString& NetworkId,
		EPlayFabPartyNetworkState NetworkState)
	{
		if (Result == PartyStateChangeResult::Succeeded)
		{
			return {};
		}

		return GetEndpointFailureForNetworkState(NetworkId, NetworkState);
	}

	TOptional<FEndpointFailure> GetEndpointFailureForNetworkState(
		const FString& NetworkId,
		EPlayFabPartyNetworkState NetworkState)
	{
		const bool bIsHosting = NetworkState == EPlayFabPartyNetworkState::JoiningNetwork_Host ||
			NetworkState == EPlayFabPartyNetworkState::JoiningNetwork_Host_PendingEndpointCreation;
		if (!bIsHosting && NetworkState != EPlayFabPartyNetworkState::JoiningNetwork_Client)
		{
			return {};
		}

		FEndpointFailure Failure;
		Failure.NetworkId = NetworkId;
		Failure.bIsHosting = bIsHosting;
		return Failure;
	}

	TOptional<FEndpointFailure> GetEndpointCreationFailure(
		PartyStateChangeResult Result,
		const FString& NetworkId,
		EPlayFabPartyNetworkState NetworkState,
		bool bIsCustomEndpointOperation)
	{
		return bIsCustomEndpointOperation ? TOptional<FEndpointFailure>() : GetEndpointFailure(Result, NetworkId, NetworkState);
	}

	void CompleteFailure(
		const TOptional<FEndpointFailure>& Failure,
		TFunctionRef<void()> Cleanup,
		TFunctionRef<void(const FEndpointFailure&)> TriggerEndpointFailure,
		TFunctionRef<void()> TriggerOperationFailure)
	{
		Cleanup();
		if (Failure.IsSet())
		{
			TriggerEndpointFailure(Failure.GetValue());
		}
		TriggerOperationFailure();
	}
}
