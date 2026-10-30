//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "PlayFabPartyNetwork.h"
#include "SocketSubsystem.h"
#include "OnlineSubsystemPlayFab.h"
#include "OnlineIdentityInterfacePlayFab.h"
#include "PlayFabCustomData.h"


FString GetNetworkStateStateString(EPlayFabPartyNetworkState State)
{
	switch (State)
	{
	case EPlayFabPartyNetworkState::NoNetwork: return TEXT("NoNetwork");
	case EPlayFabPartyNetworkState::JoiningNetwork_Host: return TEXT("JoiningNetwork_Host");
	case EPlayFabPartyNetworkState::JoiningNetwork_Host_PendingEndpointCreation: return TEXT("JoiningNetwork_Host_PendingEndpointCreation");
	case EPlayFabPartyNetworkState::JoiningNetwork_Client: return TEXT("JoiningNetwork_Client");
	case EPlayFabPartyNetworkState::NetworkReady: return TEXT("NetworkReady");
	case EPlayFabPartyNetworkState::LeavingNetwork: return TEXT("LeavingNetwork");
	}
	return TEXT("Unknown");
}

FPlayFabPartyNetwork::FPlayFabPartyNetwork(
	FOnlineSubsystemPlayFab* InOSSPlayFab,
	int32 InMaxDeviceCount,
	int32 InMaxDevicesPerUserCount,
	int32 InMaxEndpointsPerDeviceCount,
	int32 InMaxUserCount,
	int32 InMaxUsersPerDeviceCount,
	PartyDirectPeerConnectivityOptions InDirectPeerConnectivityOptions,
	bool bInCustomDataEnabled
)
	: MaxDeviceCount(InMaxDeviceCount)
	, MaxDevicesPerUserCount(InMaxDevicesPerUserCount)
	, MaxEndpointsPerDeviceCount(InMaxEndpointsPerDeviceCount)
	, MaxUserCount(InMaxUserCount)
	, MaxUsersPerDeviceCount(InMaxUsersPerDeviceCount)
	, DirectPeerConnectivityOptions(InDirectPeerConnectivityOptions)
	, OSSPlayFab(InOSSPlayFab)
	, bCustomDataEnabled(bInCustomDataEnabled)
{
}

FPlayFabPartyNetwork::~FPlayFabPartyNetwork()
{
	CustomDataLocalEndpoint = nullptr;
	CustomDataEndpoints.Reset();
	LeaveNetwork();
}

bool FPlayFabPartyNetwork::CreateAndConnectToNetwork()
{
	UE_LOG_ONLINE(Log, TEXT("FPlayFabPartyNetwork::CreateAndConnectToNetwork()"));

	if (!OSSPlayFab->bPartyInitialized)
	{
		UE_LOG_ONLINE(Warning, TEXT("FPlayFabPartyNetwork::CreateAndConnectToNetwork: Cannot create to playfab network, PartyManager is not initialized."));
		return false;
	}

	if (NetworkState != EPlayFabPartyNetworkState::NoNetwork || Network != nullptr)
	{
		UE_LOG_ONLINE(Warning, TEXT("FPlayFabPartyNetwork::CreateAndConnectToNetwork: Cannot create to playfab network while already connected to a network."));
		return false;
	}

	FOnlineIdentityPlayFabPtr IdentityInterface = OSSPlayFab->GetIdentityInterfacePlayFab();
	PartyLocalUser* LocalPartyUser = nullptr;
	if (IsRunningDedicatedServer())
	{
		TSharedPtr<FPlayFabUser> Server = IdentityInterface ? IdentityInterface->GetServerEntity() : nullptr;
		LocalPartyUser = Server.IsValid() ? Server->GetPartyLocalUser() : nullptr;
	}
	else
	{
		LocalPartyUser = IdentityInterface ? IdentityInterface->GetFirstPartyLocalUser() : nullptr;
	}
	
	if (LocalPartyUser == nullptr)
	{
		UE_LOG_ONLINE(Warning, TEXT("FPlayFabPartyNetwork::CreateAndConnectToNetwork: Could not create new network PlayFabPartyLocalUser was null"));
		return false;
	}

	const FString NewNetworkId = FGuid::NewGuid().ToString();
	const std::string NetworkIdStr = TCHAR_TO_UTF8(*NewNetworkId);

	PartyNetworkConfiguration PlayFabPartyNetworkConfig = {};

	// Setup the network using values from config
	PlayFabPartyNetworkConfig.maxDeviceCount = MaxDeviceCount;				
	PlayFabPartyNetworkConfig.maxDevicesPerUserCount = MaxDevicesPerUserCount;		
	PlayFabPartyNetworkConfig.maxEndpointsPerDeviceCount = MaxEndpointsPerDeviceCount;	
	PlayFabPartyNetworkConfig.maxUserCount = MaxUserCount;					
	PlayFabPartyNetworkConfig.maxUsersPerDeviceCount = MaxUsersPerDeviceCount;
	PlayFabPartyNetworkConfig.directPeerConnectivityOptions = DirectPeerConnectivityOptions;

	// Setup the network invitation configuration to use the network id as an invitation id and allow anyone to join.
	PartyInvitationConfiguration PartyInviteConfig{
		NetworkIdStr.c_str(),					// Invitation identifier
		PartyInvitationRevocability::Anyone,	// Revocability
		0,										// Authorized user count
		nullptr									// Authorized user list
	};

	PartyNetworkDescriptor NewNetworkDescriptor = {};

	uint32_t CachedRegionCount = 0;
	const PartyRegion* CachedRegions = nullptr;
	PartyManager::GetSingleton().GetRegions(&CachedRegionCount, &CachedRegions);
	UE_LOG_ONLINE(Verbose, TEXT("FPlayFabPartyNetwork::CreateAndConnectToNetwork: CachedRegionCount: %u"), CachedRegionCount);

	// Create a new network descriptor
	PartyError Err = PartyManager::GetSingleton().CreateNewNetwork(
		LocalPartyUser,				// Local User
		&PlayFabPartyNetworkConfig,	// Network Config
		0,							// Region List Count
		nullptr,					// Region List
		&PartyInviteConfig,			// Invitation configuration
		nullptr,					// Async Identifier
		&NewNetworkDescriptor,		// OUT network descriptor
		nullptr						// Applied initial invitation identifier
	);

	if (PARTY_FAILED(Err))
	{
		UE_LOG_ONLINE(Warning, TEXT("FPlayFabPartyNetwork::CreateAndConnectToNetwork: CreateNewNetwork failed: %s"), *GetPartyErrorMessage(Err));
		return false;
	}

	// Connect to the new network
	if (InternalConnectToNetwork(LocalPartyUser, NewNetworkId, NewNetworkDescriptor))
	{
		NetworkState = EPlayFabPartyNetworkState::JoiningNetwork_Host;
		NetworkId = NewNetworkId;

		return true;
	}

	return false;
}

bool FPlayFabPartyNetwork::ConnectToNetwork(const FString& NewNetworkId, const FString& NewNetworkDescriptorStr)
{
	UE_LOG_ONLINE(Log, TEXT("FPlayFabPartyNetwork::ConnectToNetwork: NetworkId: %s"), *NewNetworkId);

	if (OSSPlayFab->bPartyInitialized == false)
	{
		UE_LOG_ONLINE(Warning, TEXT("FPlayFabPartyNetwork::ConnectToNetwork: Cannot connect to playfab network, PartyManager is not initialized."));
		return false;
	}

	if (NetworkState != EPlayFabPartyNetworkState::NoNetwork || Network != nullptr)
	{
		UE_LOG_ONLINE(Warning, TEXT("FPlayFabPartyNetwork::ConnectToNetwork: Cannot connect to playfab network while already connected to a network."));
		return false;
	}

	FOnlineIdentityPlayFabPtr IdentityInterface = OSSPlayFab->GetIdentityInterfacePlayFab();
	PartyLocalUser* FirstPartyLocalUser = nullptr;
	if (IsRunningDedicatedServer())
	{
		TSharedPtr<FPlayFabUser> Server = IdentityInterface ? IdentityInterface->GetServerEntity() : nullptr;
		FirstPartyLocalUser = Server.IsValid() ? Server->GetPartyLocalUser() : nullptr;
	}
	else
	{
		FirstPartyLocalUser = IdentityInterface ? IdentityInterface->GetFirstPartyLocalUser() : nullptr;
	}
	if (FirstPartyLocalUser == nullptr)
	{
		UE_LOG_ONLINE(Warning, TEXT("FPlayFabPartyNetwork::ConnectToNetwork: Could not create new network FirstPartyLocalUser was null"));
		return false;
	}

	PartyNetworkDescriptor NewNetworkDescriptor = {};

	// Deserialize the remote network's descriptor
	PartyError Err = PartyManager::DeserializeNetworkDescriptor(TCHAR_TO_UTF8(*NewNetworkDescriptorStr), &NewNetworkDescriptor);

	if (PARTY_FAILED(Err))
	{
		UE_LOG_ONLINE(Warning, TEXT("FPlayFabPartyNetwork::ConnectToNetwork: failed to deserialize descriptor: %s"), *GetPartyErrorMessage(Err));
		return false;
	}

	// Connect to the remote network
	if (InternalConnectToNetwork(FirstPartyLocalUser, NewNetworkId, NewNetworkDescriptor))
	{
		NetworkState = EPlayFabPartyNetworkState::JoiningNetwork_Client;
		NetworkId = NewNetworkId;

		return true;
	}

	return false;
}

void FPlayFabPartyNetwork::LeaveNetwork()
{
	UE_LOG_ONLINE(Log, TEXT("FPlayFabPartyNetwork::LeaveNetwork()"));

	if (NetworkState != EPlayFabPartyNetworkState::LeavingNetwork && NetworkState != EPlayFabPartyNetworkState::NoNetwork && Network)
	{
		NetworkState = EPlayFabPartyNetworkState::LeavingNetwork;
		Network->LeaveNetwork(nullptr);
	}
}

bool FPlayFabPartyNetwork::AddChatControlToNetwork(PartyLocalChatControl* LocalChatControl)
{
	if (Network && NetworkState == EPlayFabPartyNetworkState::NetworkReady)
	{
		PartyError Err = Network->ConnectChatControl(LocalChatControl, nullptr);

		if (PARTY_FAILED(Err))
		{
			UE_LOG_ONLINE(Warning, TEXT("FPlayFabPartyNetwork::AddChatControlToNetwork failed: %s\n"), *GetPartyErrorMessage(Err));
			return false;
		}

		return true;
	}
	else
	{
		UE_LOG_ONLINE(Warning, TEXT("FPlayFabPartyNetwork::AddChatControlToNetwork failed: Network is null or state is invalid!\n"));
	}

	return false;
}

FString FPlayFabPartyNetwork::SerializeNetworkDescriptor(const PartyNetworkDescriptor& InNetworkDescriptor)
{
	FString NetworkDescriptorStr;
	
	char Descriptor[c_maxSerializedNetworkDescriptorStringLength + 1] = {};

	PartyError Err = PartyManager::SerializeNetworkDescriptor(
		&InNetworkDescriptor,
		Descriptor
	);

	if (PARTY_FAILED(Err))
	{
		UE_LOG_ONLINE(Warning, TEXT("Failed to serialize network descriptor: %s\n"), *GetPartyErrorMessage(Err));
	}
	else
	{
		NetworkDescriptorStr = UTF8_TO_TCHAR(Descriptor);
	}

	UE_LOG_ONLINE(Verbose, TEXT("FPlayFabPartyNetwork::SerializeNetworkDescriptor: NetworkDescriptor: %s"), *NetworkDescriptorStr);

	return NetworkDescriptorStr;
}

PartyEndpoint* FPlayFabPartyNetwork::GetEndpoint(uint32 EndpointId)
{
	if (EndpointId != 0)
	{
		PartyEndpoint** PlayFabPartyEndpoint = Endpoints.Find(EndpointId);

		if (PlayFabPartyEndpoint == nullptr || *PlayFabPartyEndpoint == nullptr)
		{
			UE_LOG(LogSockets, Warning, TEXT("FPlayFabPartyNetwork::GetEndpoint: Could not find Enpoint for UniqueId %d"), EndpointId);
		}
		else
		{
			return *PlayFabPartyEndpoint;
		}
	}
	else
	{
		UE_LOG(LogSockets, Warning, TEXT("FPlayFabPartyNetwork::GetEndpoint: UniqueId was invalid"));
	}

	return nullptr;
}


bool FPlayFabPartyNetwork::InternalConnectToNetwork(PartyLocalUser* PlayFabPartyLocalUser, const FString& InNetworkId, Party::PartyNetworkDescriptor& InNetworkDescriptor)
{
	// This portion of connecting to the network is the same for
	// both creating a new and joining an existing network.

	if (PlayFabPartyLocalUser == nullptr)
	{
		UE_LOG_ONLINE(Warning, TEXT("FPlayFabPartyNetwork::InternalConnectToNetwork: Could not create new network PlayFabPartyLocalUser was null"));
		return false;
	}

	PartyError Err = PartyManager::GetSingleton().ConnectToNetwork(
		&InNetworkDescriptor,	// Network descriptor
		nullptr,				// Async identifier
		&Network				// OUT network
	);

	if (PARTY_FAILED(Err))
	{
		UE_LOG_ONLINE(Warning, TEXT("FPlayFabPartyNetwork::InternalConnectToNetwork: ConnectToNetwork failed: %s"), *GetPartyErrorMessage(Err));
		return false;
	}

	// Authenticate the local user on the network so we can participate in it
	Err = Network->AuthenticateLocalUser(
		PlayFabPartyLocalUser,			// Local user
		TCHAR_TO_UTF8(*InNetworkId),	// Invite value
		nullptr							// Async identifier
	);

	if (PARTY_FAILED(Err))
	{
		UE_LOG_ONLINE(Warning, TEXT("FPlayFabPartyNetwork::InternalConnectToNetwork: AuthenticateLocalUser failed: %s"), *GetPartyErrorMessage(Err));
		return false;
	}

	// Establish a network endpoint for game message traffic
	Err = Network->CreateEndpoint(
		PlayFabPartyLocalUser,	// Local user
		0,						// Property Count
		nullptr,				// Property name keys
		nullptr,				// Property Values
		nullptr,				// Async identifier
		&LocalEndpoint			// OUT local endpoint
	);

	if (PARTY_FAILED(Err))
	{
		UE_LOG_ONLINE(Warning, TEXT("FPlayFabPartyNetwork::InternalConnectToNetwork: CreateEndpoint failed: %s"), *GetPartyErrorMessage(Err));
		return false;
	}

	if (bCustomDataEnabled)
	{
		PartyString PropertyKey = PlayFabCustomData::ChannelKey;
		PartyDataBuffer PropertyValue{
			const_cast<ANSICHAR*>(PlayFabCustomData::ChannelValue),
			static_cast<uint32>(sizeof(PlayFabCustomData::ChannelValue))
		};
		Err = Network->CreateEndpoint(
			PlayFabPartyLocalUser,
			1,
			&PropertyKey,
			&PropertyValue,
			this,
			&CustomDataLocalEndpoint);
		if (PARTY_FAILED(Err))
		{
			CustomDataLocalEndpoint = nullptr;
			UE_LOG_ONLINE(Warning, TEXT("FPlayFabPartyNetwork::InternalConnectToNetwork: Custom endpoint creation failed: %s"), *GetPartyErrorMessage(Err));
		}
	}

	return true;
}

bool FPlayFabPartyNetwork::MulticastCustomData(const TArray<uint8>& Payload)
{
	const PlayFabCustomData::ESendAction SendAction = PlayFabCustomData::GetSendAction(
		CustomDataLocalEndpoint != nullptr,
		Payload.Num(),
		CustomDataEndpoints.Num());
	if (SendAction == PlayFabCustomData::ESendAction::Reject)
	{
		return false;
	}
	if (SendAction == PlayFabCustomData::ESendAction::SucceedWithoutSend)
	{
		return true;
	}

	TArray<PartyEndpoint*> Targets;
	CustomDataEndpoints.GenerateValueArray(Targets);
	PartySendMessageQueuingConfiguration QueueConfiguration{};
	QueueConfiguration.priority = c_maxSendMessageQueuingPriority;
	QueueConfiguration.identityForCancelFilters = static_cast<uint32>(reinterpret_cast<uintptr_t>(this));
	QueueConfiguration.timeoutInMilliseconds = 100;
	PartyDataBuffer Buffer{ const_cast<uint8*>(Payload.GetData()), static_cast<uint32>(Payload.Num()) };
	const PartyError Err = CustomDataLocalEndpoint->SendMessage(
		static_cast<uint32>(Targets.Num()),
		Targets.GetData(),
		PartySendMessageOptions::AllowLazyAcknowledgement,
		&QueueConfiguration,
		1,
		&Buffer,
		nullptr);
	if (PARTY_FAILED(Err))
	{
		UE_LOG_ONLINE(Warning, TEXT("FPlayFabPartyNetwork::MulticastCustomData: SendMessage failed: %s"), *GetPartyErrorMessage(Err));
		return false;
	}
	return true;
}

bool FPlayFabPartyNetwork::HandleCustomEndpointCreated(PartyEndpoint* Endpoint)
{
	if (!bCustomDataEnabled || !PlayFabCustomData::IsCustomEndpoint(Endpoint))
	{
		return false;
	}

	if (Endpoint == CustomDataLocalEndpoint)
	{
		return true;
	}

	uint16 EndpointId = 0;
	if (PARTY_SUCCEEDED(Endpoint->GetUniqueIdentifier(&EndpointId)) && EndpointId != 0)
	{
		CustomDataEndpoints.Add(EndpointId, Endpoint);
	}
	return true;
}

bool FPlayFabPartyNetwork::HandleCustomEndpointDestroyed(PartyEndpoint* Endpoint)
{
	if (Endpoint == CustomDataLocalEndpoint)
	{
		CustomDataLocalEndpoint = nullptr;
		return true;
	}

	for (auto It = CustomDataEndpoints.CreateIterator(); It; ++It)
	{
		if (It.Value() == Endpoint)
		{
			It.RemoveCurrent();
			return true;
		}
	}
	return false;
}

bool FPlayFabPartyNetwork::IsCustomDataMessage(const PartyEndpointMessageReceivedStateChange& StateChange) const
{
	return PlayFabCustomData::IsReceivedOnEndpoint(StateChange, CustomDataLocalEndpoint);
}

void FPlayFabPartyNetwork::ResetCustomData()
{
	CustomDataLocalEndpoint = nullptr;
	CustomDataEndpoints.Reset();
}
