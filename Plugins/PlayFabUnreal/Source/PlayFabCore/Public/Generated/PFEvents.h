// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include "CoreMinimal.h"
#include "XAsyncTaskManager.h"
#include "PFEventsAsyncTasks.h"
#include "Generated/PFEventsUnrealTypes.h"
THIRD_PARTY_INCLUDES_START
#include <playfab/core/PFEventsTypes.h>
#include <playfab/core/PFServiceConfig.h>
#include <playfab/core/PFEntity.h>
THIRD_PARTY_INCLUDES_END

extern "C"
{

/// <summary>
/// Deletes a Data Connection from a title.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// See also EventGetDataConnectionAsync, EventSetDataConnectionAsync.
///
/// When the asynchronous task is complete, call <see cref="PFEventsDeleteDataConnectionGetResult"/>
/// to get the result.
/// </remarks>
#if 0
bool PLAYFABCORE_API FPFEventsDeleteDataConnectionAsync(
	_In_ FPFEntityHandle entityHandle,
	_In_ const FPFEventsDeleteDataConnectionRequest request,
	_Inout_ FOnDeleteDataConnectionDelegate delegate
) noexcept;
#endif


/// <summary>
/// Retrieves a single Data Connection associated with a title.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// See also EventSetDataConnectionAsync.
///
/// When the asynchronous task is complete, call <see cref="PFEventsGetDataConnectionGetResultSize"/>
/// and <see cref="PFEventsGetDataConnectionGetResult"/> to get the result.
/// </remarks>
#if 0
bool PLAYFABCORE_API FPFEventsGetDataConnectionAsync(
	_In_ FPFEntityHandle entityHandle,
	_In_ const FPFEventsGetDataConnectionRequest request,
	_Inout_ FOnGetDataConnectionDelegate delegate
) noexcept;
#endif


/// <summary>
/// Retrieves the list of Data Connections associated with a title.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// See also EventGetDataConnectionAsync.
///
/// When the asynchronous task is complete, call <see cref="PFEventsListDataConnectionsGetResultSize"/>
/// and <see cref="PFEventsListDataConnectionsGetResult"/> to get the result.
/// </remarks>
#if 0
bool PLAYFABCORE_API FPFEventsListDataConnectionsAsync(
	_In_ FPFEntityHandle entityHandle,
	_In_ const FPFEventsListDataConnectionsRequest request,
	_Inout_ FOnListDataConnectionsDelegate delegate
) noexcept;
#endif


/// <summary>
/// Creates or updates a Data Connection on a title.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// See also EventGetDataConnectionAsync.
///
/// When the asynchronous task is complete, call <see cref="PFEventsSetDataConnectionGetResultSize"/>
/// and <see cref="PFEventsSetDataConnectionGetResult"/> to get the result.
/// </remarks>
#if 0
bool PLAYFABCORE_API FPFEventsSetDataConnectionAsync(
	_In_ FPFEntityHandle entityHandle,
	_In_ const FPFEventsSetDataConnectionRequest request,
	_Inout_ FOnSetDataConnectionDelegate delegate
) noexcept;
#endif


/// <summary>
/// Sets a Data Connection for the title to either the active or deactivated state.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// See also EventSetDataConnectionAsync.
///
/// When the asynchronous task is complete, call <see cref="PFEventsSetDataConnectionActiveGetResultSize"/>
/// and <see cref="PFEventsSetDataConnectionActiveGetResult"/> to get the result.
/// </remarks>
#if 0
bool PLAYFABCORE_API FPFEventsSetDataConnectionActiveAsync(
	_In_ FPFEntityHandle entityHandle,
	_In_ const FPFEventsSetDataConnectionActiveRequest request,
	_Inout_ FOnSetDataConnectionActiveDelegate delegate
) noexcept;
#endif


/// <summary>
/// Write batches of entity based events to PlayStream. The namespace of the Event must be 'custom' or
/// start with 'custom.'.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFEventsWriteEventsGetResultSize"/> and <see
/// cref="PFEventsWriteEventsGetResult"/> to get the result.
/// </remarks>
bool PLAYFABCORE_API FPFEventsWriteEventsAsync(
	_In_ FPFEntityHandle entityHandle,
	_In_ const FPFEventsWriteEventsRequest request,
	_Inout_ FOnWriteEventsDelegate delegate
) noexcept;


/// <summary>
/// Write batches of entity based events to as Telemetry events (bypass PlayStream). The namespace must
/// be 'custom' or start with 'custom.'
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// This API must be called with either X-EntityToken or X-TelemetryKey headers. If sending X-EntityToken
/// the value must be a valid EntityToken for your title. If using X-TelemetryKey the value must be a
/// Telemetry Key configured for your title set to 'Active'. If both are provided, X-TelemetryKey will
/// be ignored.
///
/// When the asynchronous task is complete, call <see cref="PFEventsWriteTelemetryEventsGetResultSize"/>
/// and <see cref="PFEventsWriteTelemetryEventsGetResult"/> to get the result.
/// </remarks>
bool PLAYFABCORE_API FPFEventsWriteTelemetryEventsAsync(
	_In_ FPFEntityHandle entityHandle,
	_In_ const FPFEventsWriteEventsRequest request,
	_Inout_ FOnWriteTelemetryEventsDelegate delegate
) noexcept;


}
