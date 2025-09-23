// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include "CoreMinimal.h"
#include "PFEntityAsyncTasks.h"
#include "PFCoreUnrealTypes.h"
#include "PFCoreTypeConverters.h"
#include "PFEntityTypes.h"
#include "ResultMacros.h"
THIRD_PARTY_INCLUDES_START
#include <playfab/core/PFPal.h>
#include <playfab/core/PFTypes.h>
#include <playfab/core/PFAuthenticationTypes.h>
#include <playfab/core/PFServiceConfig.h>
#include <playfab/core/PFEntity.h>
THIRD_PARTY_INCLUDES_END

extern "C"
{

/// <summary>
/// Duplicates a FPFEntityHandle.
/// </summary>
/// <param name="entityHandle">Entity handle to duplicate.</param>
/// <param name="duplicatedEntityHandle">The duplicated handle.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// Both the duplicated handle and the original handle need to be closed with PFEntityCloseHandle when they
/// are no longer needed.
/// </remarks>
bool PLAYFABCORE_API FPFEntityDuplicateHandle(
	_In_ FPFEntityHandle entityHandle,
	_Out_ FPFEntityHandle& duplicatedEntityHandle
) noexcept;

/// <summary>
/// Closes a FPFEntityHandle.
/// </summary>
/// <param name="entityHandle">Entity handle to close.</param>
/// <returns>Result code for this API operation.</returns>
bool PLAYFABCORE_API FPFEntityCloseHandle(
	_In_ FPFEntityHandle entityHandle
) noexcept;

/// <summary>
/// Get the cached PFEntityToken for an Entity.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle returned from a login call.</param>
/// <param name="delegate">Delegate to handle the result of the async operation.</param>
/// <returns>Result code for this API operation.</returns>
bool PLAYFABCORE_API FPFEntityGetEntityTokenAsync(
	_In_ FPFEntityHandle entityHandle,
	_Inout_ FOnEntityGetEntityTokenDelegate delegate
) noexcept;

#if HC_PLATFORM == HC_PLATFORM_MAC || HC_PLATFORM == HC_PLATFORM_LINUX
/// <summary>
/// Gets the size of the buffer needed to hold the PlayFab secretKey. Will fail with E_PF_NOSECRETKEY if there is no 
/// Secret Key associated with the provided Entity.
/// </summary>
/// <param name="handle">Entity handle.</param>
/// <param name="secretKeySize">Buffer size required for the secretKey (including null terminator).</param>
/// <returns>Result code for this API operation.</returns>
bool PLAYFABCORE_API FPFEntityGetSecretKeySize(
	_In_  FPFEntityHandle handle,
	_Out_ TSharedPtr<SIZE_T> secretKeySize
) noexcept;

/// <summary>
/// Gets the PlayFab secretKey associated with a title Entity. Will fail with E_PF_NOSECRETKEY if there is no Secret 
/// Key associated with the provided Entity.
/// </summary>
/// <param name="handle">Entity handle.</param>
/// <param name="secretKeySize">Size of the provided buffer. Required size can be obtained via PFServiceConfigGetSecretKeySize.</param>
/// <param name="secretKey">Buffer the secretKey will be written to.</param>
/// <param name="secretKeyUsed">The number of bytes used in the buffer including the null terminator.</param>
/// <returns>Result code for this API operation.</returns>
bool PLAYFABCORE_API FPFEntityGetSecretKey(
	_In_ FPFEntityHandle handle,
	_In_ SIZE_T secretKeySize,
	_Out_writes_(secretKeySize) FString secretKey,
	_Out_opt_ TSharedPtr<SIZE_T> secretKeyUsed
) noexcept;
#endif


/// <summary>
/// Get the size in bytes needed to store the PFEntityKey for an Entity.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle returned from a auth call.</param>
/// <param name="bufferSize">The buffer size in bytes required for the EntityKey.</param>
/// <returns>Result code for this API operation.</returns>
bool PLAYFABCORE_API FPFEntityGetEntityKeySize(
	_In_ FPFEntityHandle entityHandle,
	_Out_ TSharedPtr<SIZE_T> bufferSize
) noexcept;

/// <summary>
/// Get the PFEntityKey for an entity.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle returned from a auth call.</param>
/// <param name="bufferSize">The size of the buffer for the PFEntityKey. The required size can be obtained from PFEntityGetEntityKeySize.</param>
/// <param name="buffer">Byte buffer used for the PFEntityKey and its fields.</param>
/// <param name="result">Pointer to the PFEntityKey object.</param>
/// <param name="bufferUsed">The number of bytes in the provided buffer that were used.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// entityKey is a pointer within buffer and does not need to be freed separately.
/// </remarks>
bool PLAYFABCORE_API FPFEntityGetEntityKey(
	_In_ FPFEntityHandle entityHandle,
	_In_ SIZE_T bufferSize,
	_Out_writes_bytes_to_(bufferSize, *bufferUsed) TSharedPtr<void> buffer,
	_Outptr_ TSharedPtr<const FPFEntityKey>& entityKey,
	_Out_opt_ TSharedPtr<SIZE_T> bufferUsed
) noexcept;

/// <summary>
/// Convenience method to check if an Entity is a Title Player. This is equivalent to calling PFEntityGetEntityKey and comparing
/// entityKey.type to PFTitlePlayerEntityType.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle returned from a auth call.</param>
/// <param name="isTitlePlayer">Will be set to true if the entity is a TitlePlayer and false otherwise.</param>
/// <returns>Result code for this API operation.</returns>
bool PLAYFABCORE_API FPFEntityIsTitlePlayer(
	_In_ FPFEntityHandle entityHandle,
	_Out_ TSharedPtr<bool> isTitlePlayer
) noexcept;


/// <summary>
/// Gets the size of the buffer needed to hold the API endpoint string from an entity handle.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle returned from a auth call.</param>
/// <param name="apiEndpointSize">Buffer size required for the API endpoint string (including null terminator).</param>
/// <returns>Result code for this API operation.</returns>
bool PLAYFABCORE_API FPFEntityGetAPIEndpointSize(
	_In_  FPFEntityHandle entityHandle,
	_Out_ TSharedPtr<SIZE_T> apiEndpointSize
) noexcept;

/// <summary>
/// Gets the API endpoint for the PFServiceConfig associated with an entity handle.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle returned from a auth call.</param>
/// <param name="apiEndpointSize">Size of the provided buffer. Required size can be obtained via PFEntityGetAPIEndpointSize.</param>
/// <param name="apiEndpoint">Buffer the API endpoint string will be written to.</param>
/// <param name="apiEndpointUsed">The number of bytes used in the buffer including the null terminator.</param>
/// <returns>Result code for this API operation.</returns>
bool PLAYFABCORE_API FPFEntityGetAPIEndpoint(
	_In_ FPFEntityHandle entityHandle,
	_In_ SIZE_T apiEndpointSize,
	_Out_writes_(apiEndpointSize) FString apiEndpoint,
	_Out_opt_ TSharedPtr<SIZE_T> apiEndpointUsed
) noexcept;

/// <summary>
/// Register a handler for EntityToken expired events.
/// </summary>
/// <param name="context">Optional pointer to data used by the event handler.</param>
/// <param name="handler">The event handler, <see cref="XalUserChangeEventHandler"/>.</param>
/// <param name="token">The token for unregistering this callback</param>
/// <returns>Result code for this API operation.  Possible values are S_OK, E_PF_NOT_INITIALIZED, or E_FAIL.</returns>
bool PLAYFABCORE_API FPFEntityRegisterTokenExpiredEventHandler(
	_In_opt_ TSharedPtr<void> context,
	_In_ FPFEntityTokenExpiredDelegate delegate,
	_Out_ TSharedPtr<FPFRegistrationToken> token
) noexcept;

/// <summary>
/// Unregisters a previously registered callback.
/// </summary>
/// <param name="token">The token returned from PFEntityRegisterTokenExpiredEventHandler.</param>
/// <returns></returns>
bool PLAYFABCORE_API FPFEntityUnregisterTokenExpiredEventHandler(
	_In_ FPFRegistrationToken token
) noexcept;

/// <summary>
/// Register a handler for EntityToken refreshed events.
/// </summary>
/// <param name="entityHandle">Entity handle for the entity.</param>
/// <param name="callback">The callback, <see cref="PFEntityTokenRefreshedCallback"/>.</param>
/// <param name="context">Optional pointer to data used by the callback.</param>
/// <param name="token">The token for unregistering the callback.</param>
/// <returns>Result code for this API operation.</returns>
bool PLAYFABCORE_API FPFEntityRegisterTokenRefreshedEventHandler(
	_In_opt_ TSharedPtr<void> context,
	_In_ FPFEntityTokenRefreshedDelegate delegate,
	_Out_ TSharedPtr<FPFRegistrationToken> token
) noexcept;

/// <summary>
/// Unregisters a previously registered PFEntityTokenRefreshedCallback.
/// </summary>
/// <param name="entityHandle">Entity handle for the entity.</param>
/// <param name="token">Registration token from PFEntityRegisterTokenRefreshedCallback.</param>
/// <returns>Result code for this API operation.</returns>
bool PLAYFABCORE_API FPFEntityUnregisterTokenRefreshedEventHandler(
	_In_ FPFRegistrationToken token
) noexcept;

}
