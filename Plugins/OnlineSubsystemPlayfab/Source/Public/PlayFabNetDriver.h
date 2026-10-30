//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "IpNetDriver.h"
#include "OnlineSubsystemPlayFabPackage.h"
#include "OnlineSubsystemPlayFabTypes.h"
#include "Containers/Queue.h"
#include "PlayFabNetDriver.generated.h"

class FNetworkNotify;
namespace Party
{
	struct PartyEndpointMessageReceivedStateChange;
}

DECLARE_DELEGATE_RetVal_ThreeParams(bool, FOnFillCustomMulticastPayload, UWorld*, UNetDriver*, TArray<uint8>&);
DECLARE_DELEGATE_FourParams(FOnCustomDataReceived, UWorld*, UNetDriver*, const FString&, const TArray<uint8>&);

UCLASS(transient, config=Engine)
class ONLINESUBSYSTEMPLAYFAB_API UPlayFabNetDriver : public UIpNetDriver
{
	GENERATED_UCLASS_BODY()

public:

	// UIpNetDriver Interface
	virtual class ISocketSubsystem* GetSocketSubsystem() override;
	virtual bool IsAvailable() const override;
	virtual bool InitBase(bool bInitAsClient, FNetworkNotify* InNotify, const FURL& URL, bool bReuseAddressAndPort, FString& Error) override;
	virtual bool InitListen(FNetworkNotify* InNotify, FURL& LocalURL, bool bReuseAddressAndPort, FString& Error) override;
	virtual bool InitConnect(FNetworkNotify* InNotify, const FURL& ConnectURL, FString& Error) override;
	virtual void Shutdown() override;
	virtual bool IsNetResourceValid() override { return true; }
	virtual void TickDispatch(float DeltaTime) override;
	virtual void TickFlush(float DeltaSeconds) override;

	static FOnFillCustomMulticastPayload FillCustomMulticastPayloadDelegate;
	static FOnCustomDataReceived OnCustomDataReceivedDelegate;

	class FOnlineSubsystemPlayFab* GetOnlineSubsystemPlayFab();
	class FPlayFabSocketSubsystem* GetPlayFabSocketSubsystem();
	static FName GetInstanceName(const UNetDriver* NetDriver);

private:
	void SendCustomMulticastDataForTick();
	void OnCustomDataMessageReceived(const Party::PartyEndpointMessageReceivedStateChange* Change);

	bool bFallbackToPlatformSocketSubsystem = false;
	FName SessionName;
	FDelegateHandle OnCustomDataMessageReceivedDelegateHandle;
	TQueue<TPair<FString, TArray<uint8>>> PendingCustomDataPackets;

protected:
	friend class UPlayFabNetConnection;
	friend class FPlayFabSocketSubsystem;
};