//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "HAL/Platform.h"
PRAGMA_DISABLE_UNDEFINED_IDENTIFIER_WARNINGS

#if defined(OSS_PLAYFAB_GDK_SUPPORT)
#include "PlatformDefines.h"

#include "OnlineSubsystemPlayFab.h"

#include "XNetworking.h"
#include <XGameRuntimeFeature.h>

#if defined(OSS_PLAYFAB_GDK)
void FOnlineSubsystemPlayFab::RegisterNetworkInitCallbacks()
{
	RegisterNetworkInitCallbacksGDK();
}

void FOnlineSubsystemPlayFab::UnregisterNetworkInitCallbacks()
{
	UnregisterNetworkInitCallbacksGDK();
}

void FOnlineSubsystemPlayFab::TryInitializePlayFabParty()
{
	TryInitializePlayFabPartyGDK();
}
#endif // OSS_PLAYFAB_GDK

void FOnlineSubsystemPlayFab::RegisterNetworkInitCallbacksGDK()
{
	UE_LOG_ONLINE(Verbose, TEXT("FOnlineSubsystemPlayFab::RegisterNetworkInitCallbacks"));

	if (NetworkInitRegistrationToken != 0 || PartyLifecycle.IsShuttingDown())
	{
		return;
	}

	if (!XGameRuntimeIsFeatureAvailable(XGameRuntimeFeature::XNetworking))
	{
		return;
	}

	XTaskQueueRegistrationToken Registration = {};
	const HRESULT Hr = XNetworkingRegisterConnectivityHintChanged(
		nullptr, &PartyLifecycle, [](void* Context, const XNetworkingConnectivityHint*)
		{
			static_cast<PlayFabPartyLifecycle::FState*>(Context)->NotifyConnectivityChanged();
		}, &Registration);
	if (FAILED(Hr))
	{
		UE_LOG_ONLINE(Error, TEXT("FOnlineSubsystemPlayFab::RegisterNetworkInitCallbacks: registration failed: 0x%08x"), Hr);
		return;
	}

	NetworkInitRegistrationToken = Registration.token;
}

void FOnlineSubsystemPlayFab::UnregisterNetworkInitCallbacksGDK()
{
	UE_LOG_ONLINE(Verbose, TEXT("FOnlineSubsystemPlayFab::UnregisterNetworkInitCallbacks"));

	if (NetworkInitRegistrationToken != 0)
	{
		const XTaskQueueRegistrationToken Registration = {NetworkInitRegistrationToken};
		XNetworkingUnregisterConnectivityHintChanged(Registration, true);
		NetworkInitRegistrationToken = 0;
	}
}

void FOnlineSubsystemPlayFab::TryInitializePlayFabPartyGDK()
{
	UE_LOG_ONLINE(Verbose, TEXT("FOnlineSubsystemPlayFab::TryInitializePlayFabParty"));

	if (XGameRuntimeIsFeatureAvailable(XGameRuntimeFeature::XNetworking))
	{
		XNetworkingConnectivityHint ConnectivityHint;

		auto Hr = XNetworkingGetConnectivityHint(&ConnectivityHint);

		if (SUCCEEDED(Hr))
		{
			PartyLifecycle.ResetConnectivityQueryRetry();
			if (ConnectivityHint.networkInitialized != bNetworkInitialized)
			{
				UE_LOG_ONLINE(Verbose, TEXT("FOnlineSubsystemPlayFab: ConnectivityHint.networkInitialized changed to: %s"),
					ConnectivityHint.networkInitialized ? TEXT("true") : TEXT("false"));
			}
			bNetworkInitialized = ConnectivityHint.networkInitialized;

			if (bNetworkInitialized)
			{
				InitializePlayFabParty();
			}
			else
			{
				UE_LOG_ONLINE(Verbose, TEXT("FOnlineSubsystemPlayFab::TryInitializePlayFabParty: ConnectivityHint.networkInitialized was false, waiting to initialize PlayFab Party"));
			}
		}
		else
		{
			UE_LOG_ONLINE(Warning, TEXT("FOnlineSubsystemPlayFab::TryInitializePlayFabParty: connectivity query failed: 0x%08x; retrying with backoff"), Hr);
			PartyLifecycle.ScheduleConnectivityQueryRetry();
		}
	}
}

#endif // OSS_PLAYFAB_GDK_SUPPORT