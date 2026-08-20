//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#if defined(OSS_PLAYFAB_WIN64)
#include "OnlineExternalUIInterfacePlayFab.h"
#include "PlayFabHelpers.h"

#define OSS_PLAYFAB_GET_NATIVE_EXTERNALUI_INTERFACE IOnlineSubsystem* NativeSubsystem = GetNativeOnlineSubsystem(OSSPlayFab);  IOnlineExternalUIPtr NativeExternalUIInterface = NativeSubsystem ? NativeSubsystem->GetExternalUIInterface() : nullptr; if (NativeExternalUIInterface)

bool FOnlineExternalUIPlayFab::ShowInviteUI(int32 InLocalUserNum, FName InSessionName)
{
#if defined(OSS_PLAYFAB_GDK_SUPPORT)
	if (IsNativePlatformSubsystemGDK())
	{
		return ShowInviteUIGDK(InLocalUserNum, InSessionName);
	}
#endif // OSS_PLAYFAB_GDK_SUPPORT

	UE_LOG_ONLINE_EXTERNALUI(Verbose, TEXT("FOnlineExternalUIPlayFab::ShowInviteUI()"));
	
	OSS_PLAYFAB_GET_NATIVE_EXTERNALUI_INTERFACE
	{
		return NativeExternalUIInterface->ShowInviteUI(InLocalUserNum, InSessionName);
	}

	return false;
}
#endif // OSS_PLAYFAB_WIN64