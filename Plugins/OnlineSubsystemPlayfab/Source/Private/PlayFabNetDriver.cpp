//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "PlayFabNetDriver.h"
#include "SocketSubsystem.h"
#include "PlayFabSocketSubsystem.h"
#include "OnlineSubsystemPlayFab.h"
#include "OnlineSubsystemPlayFabPrivate.h"
#include "OnlineSubsystemSessionSettings.h"
#include "PlayFabSocket.h"
#include "PlayFabHelpers.h"

UPlayFabNetDriver::UPlayFabNetDriver(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

class ISocketSubsystem* UPlayFabNetDriver::GetSocketSubsystem()
{
	return bFallbackToPlatformSocketSubsystem ? ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM) : ISocketSubsystem::Get(PLAYFAB_SOCKET_SUBSYSTEM);
}

bool UPlayFabNetDriver::IsAvailable() const
{
	FName SubsystemName = PLAYFAB_SUBSYSTEM;
#if WITH_EDITOR
	SubsystemName = GetOnlineSubsystemName(PLAYFAB_SUBSYSTEM, GetInstanceName(this));
#endif

	if (IOnlineSubsystem::DoesInstanceExist(SubsystemName) && !bFallbackToPlatformSocketSubsystem)
	{
		ISocketSubsystem* PlayFabSocketSubsystem = ISocketSubsystem::Get(PLAYFAB_SOCKET_SUBSYSTEM);
		if (PlayFabSocketSubsystem)
		{
			return true;
		}
	}

	return false;
}

bool UPlayFabNetDriver::InitBase(bool bInitAsClient, FNetworkNotify* InNotify, const FURL& URL, bool bReuseAddressAndPort, FString& Error)
{
	if (bFallbackToPlatformSocketSubsystem)
	{
		UE_LOG(LogSockets, Verbose, TEXT("PlayFabNetDriver::InitBase: URL = %s bFallbackToPlatformSocketSubsystem = true; Returning early Super::InitBase instead of setting up PlayFab Sockets."), *URL.Host);
		return Super::InitBase(bInitAsClient, InNotify, URL, bReuseAddressAndPort, Error);
	}

	// Parse SessionName from URL options if present
	SessionName = NAME_GameSession;
	for (const FString& Option : URL.Op)
	{
		if (Option.StartsWith(TEXT("SessionName=")))
		{
			FString SessionNameStr = Option.Mid(FCString::Strlen(TEXT("SessionName=")));
			if (!SessionNameStr.IsEmpty())
			{
				SessionName = FName(*SessionNameStr);
			}
			break;
		}
	}

	if (FOnlineSubsystemPlayFab* OSSPlayFab = GetOnlineSubsystemPlayFab())
	{
		if (FPlayFabSocketSubsystem* SocketSubsystem = GetPlayFabSocketSubsystem())
		{
			FUniqueSocket NewSocket = CreateSocketForProtocol(FNetworkProtocolTypes::PlayFab);
			if (!NewSocket.IsValid())
			{
				UE_LOG(LogSockets, Error, TEXT("PlayFabNetDriver::InitBase: Failed to create PlayFab socket"));
				return false;
			}

			FPlayFabSocket* PlayFabSocket = static_cast<FPlayFabSocket*>(NewSocket.Get());
			PlayFabSocket->SetPartyNetwork(OSSPlayFab->GetPartyNetwork(SessionName));

			SetSocketAndLocalAddress(TSharedPtr<FSocket>(NewSocket.Release(), FSocketDeleter(GetSocketSubsystem())));

			SocketSubsystem->LinkNetDriver(this);

			if (UNetDriver::InitBase(bInitAsClient, InNotify, URL, bReuseAddressAndPort, Error))
			{
				return true;
			}
		}
	}

	return false;
}

bool UPlayFabNetDriver::InitListen(FNetworkNotify* InNotify, FURL& LocalURL, bool bReuseAddressAndPort, FString& Error)
{
	return Super::InitListen(InNotify, LocalURL, bReuseAddressAndPort, Error);
}

bool UPlayFabNetDriver::InitConnect(FNetworkNotify* InNotify, const FURL& InConnectURL, FString& Error)
{
	if (InConnectURL.Host.StartsWith(TEXT("0.0.0.0")))
	{
		UE_LOG(LogSockets, Verbose, TEXT("PlayFabNetDriver::InitConnect: URL = %s bFallbackToPlatformSocketSubsystem = false"), *InConnectURL.Host);
		bFallbackToPlatformSocketSubsystem = false;
	}
	else
	{
		UE_LOG(LogSockets, Verbose, TEXT("PlayFabNetDriver::InitConnect: URL = %s bFallbackToPlatformSocketSubsystem = true; Connecting to a dedicated server."), *InConnectURL.Host);
		bFallbackToPlatformSocketSubsystem = true;
	}

	return Super::InitConnect(InNotify, InConnectURL, Error);
}

void UPlayFabNetDriver::Shutdown()
{
	UE_LOG(LogSockets, Verbose, TEXT("PlayFabNetDriver: Shutdown called on netdriver"));

	Super::Shutdown();
}

void UPlayFabNetDriver::TickDispatch(float DeltaTime)
{
	Super::TickDispatch(DeltaTime);
}

FOnlineSubsystemPlayFab* UPlayFabNetDriver::GetOnlineSubsystemPlayFab()
{
	FName InstanceName = GetInstanceName(this);
	IOnlineSubsystem* OSSPlayFab = GetOnlineSubsystem(PLAYFAB_SUBSYSTEM, InstanceName);
	return static_cast<FOnlineSubsystemPlayFab*>(OSSPlayFab);
}

FName UPlayFabNetDriver::GetInstanceName(const UNetDriver* NetDriver)
{
	if (UWorld* InWorld = NetDriver->GetWorld())
	{
		if (FWorldContext* WorldContext = GEngine->GetWorldContextFromWorld(InWorld))
		{
			return FName(WorldContext->ContextHandle.ToString());
		}
	}

	if (GEngine)
	{
		if (FWorldContext* WorldContext = GEngine->GetWorldContextFromPendingNetGameNetDriver(NetDriver))
		{
			return FName(WorldContext->ContextHandle.ToString());
		}
	}

	return FOnlineSubsystemImpl::DefaultInstanceName;
}

FPlayFabSocketSubsystem* UPlayFabNetDriver::GetPlayFabSocketSubsystem()
{
	return static_cast<FPlayFabSocketSubsystem*>(GetSocketSubsystem());
}