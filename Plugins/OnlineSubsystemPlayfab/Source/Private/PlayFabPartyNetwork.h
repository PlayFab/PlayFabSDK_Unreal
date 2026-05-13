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
	FPlayFabPartyNetwork(FOnlineSubsystemPlayFab* InOSSPlayFab);
	~FPlayFabPartyNetwork();

	EPlayFabPartyNetworkState NetworkState = EPlayFabPartyNetworkState::NoNetwork;
	PartyNetwork* Network = nullptr;
	PartyLocalEndpoint* LocalEndpoint = nullptr;
	TMap<uint32, PartyEndpoint*> Endpoints;

	FString NetworkId;
	PartyNetworkDescriptor NetworkDescriptor;

	int32 MaxDeviceCount = 8;
	int32 MaxDevicesPerUserCount = 1;
	int32 MaxEndpointsPerDeviceCount = 1;
	int32 MaxUserCount = 8;
	int32 MaxUsersPerDeviceCount = 1;
	PartyDirectPeerConnectivityOptions DirectPeerConnectivityOptions
		= PartyDirectPeerConnectivityOptions::AnyPlatformType | PartyDirectPeerConnectivityOptions::AnyEntityLoginProvider;

	// Network lifecycle
	bool CreateAndConnectToNetwork();
	bool ConnectToNetwork(const FString& NewNetworkId, const FString& NewNetworkDescriptorStr);
	void LeaveNetwork();
	bool AddChatControlToNetwork(PartyLocalChatControl* LocalChatControl);
	FString SerializeNetworkDescriptor(const PartyNetworkDescriptor& InNetworkDescriptor);
	PartyEndpoint* GetEndpoint(uint32 EndpointId);
	void ParseDirectPeerConnectivityOptions();

private:
	bool InternalConnectToNetwork(PartyLocalUser* PlayFabPartyLocalUser, const FString& InNetworkId, Party::PartyNetworkDescriptor& InNetworkDescriptor);

	FOnlineSubsystemPlayFab* OSSPlayFab = nullptr;
};
