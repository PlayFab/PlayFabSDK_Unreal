// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include "CoreMinimal.h"
#include "PFHttpConfigTypes.h"
THIRD_PARTY_INCLUDES_START
#include <playfab/core/PFPal.h>
#include <playfab/core/PFHttpConfig.h>
THIRD_PARTY_INCLUDES_END

extern "C"
{

/// <summary>
/// Sets global HTTP retry settings for the SDK.
/// </summary>
/// <param name="settings">Pointer to retry settings.</param>
/// <returns>Result code for this API operation.</returns>
bool PLAYFABCORE_API FPFSetHttpRetrySettings(
	_In_ const TSharedPtr<FPFHttpRetrySettings>& settings
) noexcept;

/// <summary>
/// Gets the current HTTP retry settings for the SDK.
/// </summary>
/// <param name="settings">Pointer to retry settings that will be populated.</param>
/// <returns>Result code for this API operation.</returns>
bool PLAYFABCORE_API FPFGetHttpRetrySettings(
	_Out_ TSharedPtr<FPFHttpRetrySettings> settings
) noexcept;

/// <summary>
/// Sets global generic HTTP settings for the SDK.
/// </summary>
/// <param name="settings">Pointer to generic settings.</param>
/// <returns>Result code for this API operation.</returns>
bool PLAYFABCORE_API FPFSetHttpSettings(
	_In_ const TSharedPtr<FPFHttpSettings>& settings
) noexcept;

/// <summary>
/// Gets the current generic HTTP settings for the SDK.
/// </summary>
/// <param name="settings">Pointer to generic settings that will be populated.</param>
/// <returns>Result code for this API operation.</returns>
bool PLAYFABCORE_API FPFGetHttpSettings(
	_Out_ TSharedPtr<FPFHttpSettings> settings
) noexcept;
}