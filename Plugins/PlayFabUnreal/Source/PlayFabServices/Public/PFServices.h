// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include "CoreMinimal.h"
#include "XAsyncTaskManager.h"
#include "PFServicesAsyncTasks.h"
#include "PFServicesTypes.h"
THIRD_PARTY_INCLUDES_START
#include <playfab/services/PFServices.h>
#if HC_PLATFORM_IS_PLAYSTATION
#include <playfab/services/PFServicesPS.h>
#endif
THIRD_PARTY_INCLUDES_END

extern "C"
{

#if HC_PLATFORM_IS_PLAYSTATION
/// <summary>
/// Initializes PlayFab Services global state
/// </summary>
/// <remarks>
/// This will internally call PFInitialize(nullptr) if it hasn't been called already by the
/// title. If control of PFCore background work is needed, the title should explicitly call
/// PFInitialize and PFUninitialize.
/// </remarks>
/// <returns>Result code for this API operation.</returns>
bool PLAYFABSERVICES_API FPFServicesInitialize() noexcept;
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC
/// <summary>
/// Initializes PlayFab Services global state
/// </summary>
/// <remarks>
/// This will internally call PFInitialize(nullptr) if it hasn't been called already by the
/// title. If control of PFCore background work is needed, the title should explicitly call
/// PFInitialize and PFUninitialize.
/// </remarks>
/// <returns>Result code for this API operation.</returns>
bool PLAYFABSERVICES_API FPFServicesInitialize() noexcept;
#endif

#if HC_PLATFORM == HC_PLATFORM_ANDROID
/// <summary>
/// Initializes PlayFab Services global state
/// </summary>
/// <param name="args">Arguments for initializing libHttpClient. It contains a Java VM and an application context, both can be retrieved through an Android app activity.</param>
/// <remarks>
/// This will internally call PFInitialize(nullptr) if it hasn't been called already by the
/// title. If control of PFCore background work is needed, the title should explicitly call
/// PFInitialize and PFUninitialize.
/// </remarks>
/// <returns>Result code for this API operation.</returns>
bool PLAYFABSERVICES_API FPFServicesInitialize(
    _In_ HCInitArgs* initArgs
) noexcept;
#endif

/// <summary>
/// Cleanup PlayFab Services global state.
/// </summary>
/// <param name="delegate">Delegate to be called upon completion of the uninitialization process.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This will internally call PFUninitializeAsync() if PFServicesInitialize() needed 
/// to call PFInitialize() interally.
/// Asynchronous result returned via XAsyncGetStatus.</remarks>
bool PLAYFABSERVICES_API FPFServicesUninitializeAsync(
    _Inout_ FOnPFServicesUninitializeDelegate delegate
) noexcept;

}

