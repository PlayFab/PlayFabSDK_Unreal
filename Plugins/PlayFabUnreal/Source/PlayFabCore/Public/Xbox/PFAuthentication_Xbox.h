// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#if defined(PF_UE_GDK_SUPPORT) || defined(PF_GDK_AVAILABLE)

#include "CoreMinimal.h"
#include "XAsyncTaskManager.h"
#include "Generated/PFAuthenticationUnrealTypes.h"
#include "Xbox/PFAuthenticationAsyncTasks_Xbox.h"
#include "Xbox/PFAuthenticationTypes_Xbox.h"
THIRD_PARTY_INCLUDES_START
#include <playfab/core/PFAuthenticationTypes.h>
#include <playfab/core/PFServiceConfig.h>
#include <playfab/core/PFEntity.h>
THIRD_PARTY_INCLUDES_END

extern "C"
{

/// <summary>
/// Signs the user in using an XUserHandle, returning a session identifier that can subsequently be
/// used for API calls which require an authenticated user
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on GDK.
/// If this is the first time a user has signed in with the Xbox Live account and CreateAccount is set
/// to true, a new PlayFab account will be created and linked to the Xbox Live account. In this case,
/// no email or username will be associated with the PlayFab account. Otherwise, if no PlayFab account
/// is linked to the Xbox Live account, an error indicating this will be returned, so that the title can
/// guide the user through creation of a PlayFab account. See also ClientLinkXboxAccountAsync, ClientUnlinkXboxAccountAsync.
///
/// When the asynchronous task is complete, call <see cref="PFAuthenticationLoginWithXUserGetResult"/> to get the result.
/// </remarks>

bool PLAYFABCORE_API FPFAuthenticationLoginWithXUserAsync(
	_In_ FPFServiceConfigHandle serviceConfigHandle,
	_In_ const FPFAuthenticationLoginWithXUserRequest request,
	_Inout_ FOnPFAuthenticationLoginCompleteDelegate delegate
) noexcept;

}

#endif
