//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#if defined(OSS_PLAYFAB_WIN64)
#include "OnlineSessionInterfacePlayFab.h"
#include "OnlineSubsystemPlayFab.h"
#include "PlayFabHelpers.h"

#define OSS_PLAYFAB_GET_NATIVE_SESSION_INTERFACE IOnlineSubsystem* NativeSubsystem = GetNativeOnlineSubsystem(OSSPlayFab);  IOnlineSessionPtr NativeSessionInterface = NativeSubsystem ? NativeSubsystem->GetSessionInterface() : nullptr; if (NativeSessionInterface)

bool FOnlineSessionPlayFab::SendInvite(const FUniqueNetId& SenderId, FName SessionName, const TArray< TSharedRef<const FUniqueNetId> >& RemoteUserNetIds)
{
#if defined(OSS_PLAYFAB_GDK_SUPPORT)
	if (IsNativePlatformSubsystemGDK())
	{
		return SendInviteGDK(SenderId, SessionName, RemoteUserNetIds);
	}
#endif // OSS_PLAYFAB_GDK_SUPPORT

	UE_LOG_ONLINE_SESSION(Verbose, TEXT("FOnlineSessionPlayFab::SendInvite()"));

	// Defer to the native session interface next
	OSS_PLAYFAB_GET_NATIVE_SESSION_INTERFACE
	{
		FNamedOnlineSession* NativeSession = NativeSessionInterface->GetNamedSession(SessionName);
		if (NativeSession != nullptr)
		{
			return NativeSessionInterface->SendSessionInviteToFriends(SenderId, SessionName, RemoteUserNetIds);
		}
	}

#if defined(OSS_PLAYFAB_STEAM)
	// We enter this flow when we have a PlayFab session with no corresponding native Steam session. This can happen when the session
	// is created on a dedicated server where no user is present and thus we can't create a Steam session.
	if (IsNativePlatformSubsystemSteam())
	{
		return SendInviteSteam(SenderId, SessionName, RemoteUserNetIds);
	}
#endif // OSS_PLAYFAB_STEAM

	return false;
}

#endif // OSS_PLAYFAB_WIN64