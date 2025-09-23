// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include "CoreMinimal.h"
#include "XAsyncTaskManager.h"
#include "PFCloudScriptAsyncTasks.h"

THIRD_PARTY_INCLUDES_START
#include <playfab/services/PFServices.h>
THIRD_PARTY_INCLUDES_END

extern "C"
{
/// <summary>
/// Executes a CloudScript function, with the 'currentPlayerId' set to the PlayFab ID of the authenticated
/// player. The PlayFab ID is the entity ID of the player's master_player_account entity.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFCloudScriptClientExecuteCloudScriptGetResultSize"/>
/// and <see cref="PFCloudScriptClientExecuteCloudScriptGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFCloudScriptClientExecuteCloudScriptAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCloudScriptExecuteCloudScriptRequest* request,
	_Inout_ FOnClientExecuteCloudScriptCompleted delegate
) noexcept;

/// <summary>
/// Executes a CloudScript function, with the 'currentPlayerId' set to the PlayFab ID of the authenticated
/// player. The PlayFab ID is the entity ID of the player's master_player_account entity.
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFCloudScriptServerExecuteCloudScriptGetResultSize"/>
/// and <see cref="PFCloudScriptServerExecuteCloudScriptGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFCloudScriptServerExecuteCloudScriptAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFCloudScriptExecuteCloudScriptServerRequest* request,
	_Inout_ FOnServerExecuteCloudScriptCompleted delegate
) noexcept;
#endif

/// <summary>
/// Cloud Script is one of PlayFab's most versatile features. It allows client code to request execution
/// of any kind of custom server-side functionality you can implement, and it can be used in conjunction
/// with virtually anything.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Executes CloudScript with the entity profile that is defined in the request.
///
/// When the asynchronous task is complete, call <see cref="PFCloudScriptExecuteEntityCloudScriptGetResultSize"/>
/// and <see cref="PFCloudScriptExecuteEntityCloudScriptGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFCloudScriptExecuteEntityCloudScriptAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCloudScriptExecuteEntityCloudScriptRequest* request,
	_Inout_ FOnExecuteEntityCloudScriptCompleted delegate
) noexcept;

/// <summary>
/// Cloud Script is one of PlayFab's most versatile features. It allows client code to request execution
/// of any kind of custom server-side functionality you can implement, and it can be used in conjunction
/// with virtually anything.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Executes an Azure Function with the profile of the entity that is defined in the request. See also
/// CloudScriptRegisterHttpFunctionAsync, CloudScriptRegisterQueuedFunctionAsync.
///
/// When the asynchronous task is complete, call <see cref="PFCloudScriptExecuteFunctionGetResultSize"/>
/// and <see cref="PFCloudScriptExecuteFunctionGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFCloudScriptExecuteFunctionAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCloudScriptExecuteFunctionRequest* request,
	_Inout_ FOnExecuteFunctionCompleted delegate
) noexcept;

/// <summary>
/// Lists all currently registered Event Hub triggered Azure Functions for a given title.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// See also CloudScriptListFunctionsAsync, CloudScriptListHttpFunctionsAsync, CloudScriptListQueuedFunctionsAsync,
/// CloudScriptRegisterEventHubFunctionAsync.
///
/// When the asynchronous task is complete, call <see cref="PFCloudScriptListEventHubFunctionsGetResultSize"/>
/// and <see cref="PFCloudScriptListEventHubFunctionsGetResult"/> to get the result.
/// </remarks>
#if 0
bool PLAYFABSERVICES_API FPFCloudScriptListEventHubFunctionsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCloudScriptListFunctionsRequest* request,
	_Inout_ FOnListEventHubFunctionsCompleted delegate
) noexcept;
#endif

/// <summary>
/// Registers an event hub triggered Azure Function with a title.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// A title can have many functions, RegisterEventHubFunction associates a function name with an event
/// hub name and connection string. See also CloudScriptExecuteFunctionAsync, CloudScriptListEventHubFunctionsAsync,
/// CloudScriptListFunctionsAsync, CloudScriptPostFunctionResultForEntityTriggeredActionAsync, CloudScriptPostFunctionResultForFunctionExecutionAsync,
/// CloudScriptPostFunctionResultForPlayerTriggeredActionAsync, CloudScriptPostFunctionResultForScheduledTaskAsync,
/// CloudScriptRegisterHttpFunctionAsync, CloudScriptRegisterQueuedFunctionAsync, CloudScriptUnregisterFunctionAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be one of global PlayFab Service errors. See doc page "Handling PlayFab Errors"
/// for more details on error handling.
/// </remarks>
#if 0
bool PLAYFABSERVICES_API FPFCloudScriptRegisterEventHubFunctionAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCloudScriptRegisterEventHubFunctionRequest* request,
	_Inout_ FOnRegisterEventHubFunctionCompleted delegate
) noexcept;
#endif

}
