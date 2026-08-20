//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "PlayFabSDKIncludes.h"
#include "OnlineSubsystemPlayFabDefines.h"

class FOnlineSubsystemPlayFab;

enum class EPlayFabPartyNetworkState
{
	NoNetwork,
	JoiningNetwork_Host,
	JoiningNetwork_Host_PendingEndpointCreation,
	JoiningNetwork_Client,
	NetworkReady,
	LeavingNetwork
};

FString GetNetworkStateStateString(EPlayFabPartyNetworkState State);

class FPlayFabPartyNetwork
{
public:
	FPlayFabPartyNetwork(
		FOnlineSubsystemPlayFab* InOSSPlayFab,
		int32 InMaxDeviceCount,
		int32 InMaxDevicesPerUserCount,
		int32 InMaxEndpointsPerDeviceCount,
		int32 InMaxUserCount,
		int32 InMaxUsersPerDeviceCount,
		PartyDirectPeerConnectivityOptions InDirectPeerConnectivityOptions
	);
	~FPlayFabPartyNetwork();

	EPlayFabPartyNetworkState NetworkState = EPlayFabPartyNetworkState::NoNetwork;
	PartyNetwork* Network = nullptr;
	PartyLocalEndpoint* LocalEndpoint = nullptr;
	TMap<uint32, PartyEndpoint*> Endpoints;

	FString NetworkId;
	PartyNetworkDescriptor NetworkDescriptor;

	int32 MaxDeviceCount;
	int32 MaxDevicesPerUserCount;
	int32 MaxEndpointsPerDeviceCount;
	int32 MaxUserCount;
	int32 MaxUsersPerDeviceCount;
	PartyDirectPeerConnectivityOptions DirectPeerConnectivityOptions;

	// Network lifecycle
	bool CreateAndConnectToNetwork();
	bool ConnectToNetwork(const FString& NewNetworkId, const FString& NewNetworkDescriptorStr);
	void LeaveNetwork();
	bool AddChatControlToNetwork(PartyLocalChatControl* LocalChatControl);
	FString SerializeNetworkDescriptor(const PartyNetworkDescriptor& InNetworkDescriptor);
	PartyEndpoint* GetEndpoint(uint32 EndpointId);

private:
	bool InternalConnectToNetwork(PartyLocalUser* PlayFabPartyLocalUser, const FString& InNetworkId, Party::PartyNetworkDescriptor& InNetworkDescriptor);

	FOnlineSubsystemPlayFab* OSSPlayFab = nullptr;
};
