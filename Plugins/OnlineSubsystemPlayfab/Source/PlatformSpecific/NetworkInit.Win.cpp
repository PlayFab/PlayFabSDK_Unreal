//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include "HAL/Platform.h"
PRAGMA_DISABLE_UNDEFINED_IDENTIFIER_WARNINGS

#if OSS_PLAYFAB_WIN64
#include "OnlineSessionSettings.h"
#include "PlatformDefines.h"
#include "OnlineSubsystemPlayFab.h"
#include "PlayFabHelpers.h"

void FOnlineSubsystemPlayFab::RegisterNetworkInitCallbacks()
{
#if defined(OSS_PLAYFAB_GDK_SUPPORT)
	if (IsNativePlatformSubsystemGDK())
	{
		RegisterNetworkInitCallbacksGDK();
		return;
	}
#endif // OSS_PLAYFAB_GDK_SUPPORT

	UE_LOG_ONLINE(Verbose, TEXT("FOnlineSubsystemPlayFab::RegisterNetworkInitCallbacks"));
}

void FOnlineSubsystemPlayFab::UnregisterNetworkInitCallbacks()
{
#if defined(OSS_PLAYFAB_GDK_SUPPORT)
	if (IsNativePlatformSubsystemGDK())
	{
		UnregisterNetworkInitCallbacksGDK();
		return;
	}
#endif // OSS_PLAYFAB_GDK_SUPPORT

	UE_LOG_ONLINE(Verbose, TEXT("FOnlineSubsystemPlayFab::UnregisterNetworkInitCallbacks"));
}

void FOnlineSubsystemPlayFab::TryInitializePlayFabParty()
{
#if defined(OSS_PLAYFAB_GDK_SUPPORT)
	if (IsNativePlatformSubsystemGDK())
	{
		TryInitializePlayFabPartyGDK();
		return;
	}
#endif // OSS_PLAYFAB_GDK_SUPPORT

	UE_LOG_ONLINE(Verbose, TEXT("FOnlineSubsystemPlayFab::TryInitializePlayFabParty"));
	InitializePlayFabParty();
}

#endif // OSS_PLAYFAB_WIN64