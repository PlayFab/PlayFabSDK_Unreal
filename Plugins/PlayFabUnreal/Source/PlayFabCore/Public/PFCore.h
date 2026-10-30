// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include "CoreMinimal.h"
#include "XAsyncTaskManager.h"
#include "PFCoreAsyncTasks.h"
#include "PFCoreTypes.h"
#if PLATFORM_WINDOWS || (defined(PLATFORM_XSX) && PLATFORM_XSX) || (defined(PLATFORM_XB1) && PLATFORM_XB1)
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/AllowWindowsPlatformAtomics.h"
#endif
THIRD_PARTY_INCLUDES_START
#include <playfab/core/PFCore.h>
THIRD_PARTY_INCLUDES_END
#if PLATFORM_WINDOWS || (defined(PLATFORM_XSX) && PLATFORM_XSX) || (defined(PLATFORM_XB1) && PLATFORM_XB1)
#include "Windows/HideWindowsPlatformAtomics.h"
#include "Windows/HideWindowsPlatformTypes.h"
#endif

extern "C"
{

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC || HC_PLATFORM == HC_PLATFORM_NINTENDO_SWITCH
/// <summary>
/// Initialize PlayFabCore global state. Custom platform hooks must be configured prior to calling PFInitialize.
/// </summary>
/// <remarks>
/// This is reference counted, so independent components may each call it unconditionally. Only the
/// first call performs the underlying initialization; later calls just take an additional reference.
/// Every successful call must be balanced with a call to FPFUninitialize or FPFUninitializeAsync.
/// Note that PFServicesInitialize initializes PlayFabCore without going through this reference count.
/// </remarks>
/// <returns>True if PlayFabCore is initialized and usable. False always indicates a genuine initialization failure.</returns>
bool PLAYFABCORE_API FPFInitialize() noexcept;
#endif

#if HC_PLATFORM == HC_PLATFORM_ANDROID
/// <summary>
/// Initializes PlayFabCore global state. Custom platform hooks must be configured prior to calling PFInitialize.
/// </summary>
/// <param name="args">Args for initializing libHttpClient.</param>
/// <remarks>
/// This will internally call PFInitialize(nullptr) if it hasn't been called already by the
/// title. If control of PFCore background work is needed, the title should explicitly call
/// PFInitialize and PFUninitialize.
///
/// This is reference counted, so independent components may each call it unconditionally. Only the
/// first call performs the underlying initialization; later calls just take an additional reference.
/// Every successful call must be balanced with a call to FPFUninitialize or FPFUninitializeAsync.
/// </remarks>
/// <returns>True if PlayFabCore is initialized and usable. False always indicates a genuine initialization failure.</returns>
bool PLAYFABCORE_API FPFInitialize(
	_In_ JavaVM* javaVm,
	_In_ jobject applicationContext
) noexcept;
#endif

/// <summary>
/// Releases one reference taken by FPFInitialize, cleaning up PlayFab global state once the last one is released.
/// </summary>
/// <param name="delegate">Delegate to be called upon completion of the uninitialization process.</param>
/// <returns>True if the reference was released. False indicates an unbalanced call, i.e. no outstanding reference.</returns>
/// <remarks>
/// The delegate is always invoked asynchronously on the game thread, including when other references
/// remain and no actual teardown is performed.
/// </remarks>
bool PLAYFABCORE_API FPFUninitializeAsync(
	_Inout_ FOnPFUninitializeDelegate delegate
) noexcept;

/// <summary>
/// Blocking equivalent of FPFUninitializeAsync, for teardown paths that must complete before returning.
/// </summary>
/// <returns>True if the reference was released. False indicates an unbalanced call or a failed teardown.</returns>
/// <remarks>
/// Only the release of the last reference blocks; otherwise this returns immediately. Prefer
/// FPFUninitializeAsync unless the caller is shutting down and cannot pump the game thread.
/// </remarks>
bool PLAYFABCORE_API FPFUninitialize() noexcept;

}