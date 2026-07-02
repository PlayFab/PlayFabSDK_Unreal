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
/// <returns>Result code for this API operation.</returns>
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
/// </remarks>
/// <returns>Result code for this API operation.</returns>
bool PLAYFABCORE_API FPFInitialize(
	_In_ JavaVM* javaVm,
	_In_ jobject applicationContext
) noexcept;
#endif

/// <summary>
/// Cleanup PlayFab global state.
/// </summary>
/// <param name="delegate">Delegate to be called upon completion of the uninitialization process.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>Asynchronous result returned via the provided delegate.</remarks>
bool PLAYFABCORE_API FPFUninitializeAsync(
	_Inout_ FOnPFUninitializeDelegate delegate
) noexcept;

}