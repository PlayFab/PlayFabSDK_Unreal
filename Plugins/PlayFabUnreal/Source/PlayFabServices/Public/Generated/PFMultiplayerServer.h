// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include "CoreMinimal.h"
#include "XAsyncTaskManager.h"
#include "PFMultiplayerServerAsyncTasks.h"

THIRD_PARTY_INCLUDES_START
#include <playfab/services/PFServices.h>
THIRD_PARTY_INCLUDES_END

extern "C"
{
/// <summary>
/// Deletes a multiplayer server game secret.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// Deletes a multiplayer server game secret. See also MultiplayerServerListSecretSummariesAsync, MultiplayerServerUploadSecretAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_API_NOT_ENABLED_FOR_GAME_CLIENT_ACCESS, E_PF_MULTIPLAYER_SERVER_BAD_REQUEST,
/// E_PF_MULTIPLAYER_SERVER_FORBIDDEN, E_PF_MULTIPLAYER_SERVER_INTERNAL_SERVER_ERROR, E_PF_MULTIPLAYER_SERVER_NO_CONTENT,
/// E_PF_MULTIPLAYER_SERVER_NOT_FOUND, E_PF_MULTIPLAYER_SERVER_TOO_MANY_REQUESTS, E_PF_MULTIPLAYER_SERVER_UNAUTHORIZED,
/// E_PF_MULTIPLAYER_SERVER_UNAVAILABLE or any of the global PlayFab Service errors. See doc page "Handling
/// PlayFab Errors" for more details on error handling.
/// </remarks>
#if 0
bool PLAYFABSERVICES_API FPFMultiplayerServerDeleteSecretAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFMultiplayerServerDeleteSecretRequest* request,
	_Inout_ FOnDeleteSecretCompleted delegate
) noexcept;
#endif

/// <summary>
/// Lists details of all build aliases for a title. Accepts tokens for title and if game client access
/// is enabled, allows game client to request list of builds with player entity token.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Returns a list of summarized details of all multiplayer server builds for a title. See also MultiplayerServerCreateBuildWithManagedContainerAsync,
/// MultiplayerServerDeleteBuildAsync, MultiplayerServerGetBuildAsync.
///
/// When the asynchronous task is complete, call <see cref="PFMultiplayerServerListBuildAliasesGetResultSize"/>
/// and <see cref="PFMultiplayerServerListBuildAliasesGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFMultiplayerServerListBuildAliasesAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFMultiplayerServerListBuildAliasesRequest* request,
	_Inout_ FOnListBuildAliasesCompleted delegate
) noexcept;

/// <summary>
/// Lists summarized details of all multiplayer server builds for a title. Accepts tokens for title and
/// if game client access is enabled, allows game client to request list of builds with player entity
/// token.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Returns a list of summarized details of all multiplayer server builds for a title. See also MultiplayerServerCreateBuildWithManagedContainerAsync,
/// MultiplayerServerDeleteBuildAsync, MultiplayerServerGetBuildAsync.
///
/// When the asynchronous task is complete, call <see cref="PFMultiplayerServerListBuildSummariesV2GetResultSize"/>
/// and <see cref="PFMultiplayerServerListBuildSummariesV2GetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFMultiplayerServerListBuildSummariesV2Async(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFMultiplayerServerListBuildSummariesRequest* request,
	_Inout_ FOnListBuildSummariesV2Completed delegate
) noexcept;

/// <summary>
/// Lists quality of service servers for the title. By default, servers are only returned for regions
/// where a Multiplayer Servers build has been deployed.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Returns a list of quality of service servers for a title.
///
/// When the asynchronous task is complete, call <see cref="PFMultiplayerServerListQosServersForTitleGetResultSize"/>
/// and <see cref="PFMultiplayerServerListQosServersForTitleGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFMultiplayerServerListQosServersForTitleAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFMultiplayerServerListQosServersForTitleRequest* request,
	_Inout_ FOnListQosServersForTitleCompleted delegate
) noexcept;

/// <summary>
/// Lists multiplayer server game secrets for a title.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// Returns a list of multiplayer server game secrets for a title. See also MultiplayerServerDeleteSecretAsync,
/// MultiplayerServerUploadSecretAsync.
///
/// When the asynchronous task is complete, call <see cref="PFMultiplayerServerListSecretSummariesGetResultSize"/>
/// and <see cref="PFMultiplayerServerListSecretSummariesGetResult"/> to get the result.
/// </remarks>
#if 0
bool PLAYFABSERVICES_API FPFMultiplayerServerListSecretSummariesAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFMultiplayerServerListSecretSummariesRequest* request,
	_Inout_ FOnListSecretSummariesCompleted delegate
) noexcept;
#endif

/// <summary>
/// Request a multiplayer server session. Accepts tokens for title and if game client access is enabled,
/// allows game client to request a server with player entity token.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Requests a multiplayer server session from a particular build in any of the given preferred regions.
/// See also MultiplayerServerGetMultiplayerServerDetailsAsync.
///
/// When the asynchronous task is complete, call <see cref="PFMultiplayerServerRequestMultiplayerServerGetResultSize"/>
/// and <see cref="PFMultiplayerServerRequestMultiplayerServerGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFMultiplayerServerRequestMultiplayerServerAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFMultiplayerServerRequestMultiplayerServerRequest* request,
	_Inout_ FOnRequestMultiplayerServerCompleted delegate
) noexcept;

/// <summary>
/// Request a party session.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// Requests a party session from a particular set of builds if build alias params is provided, in any
/// of the given preferred regions.
///
/// When the asynchronous task is complete, call <see cref="PFMultiplayerServerRequestPartyServiceGetResultSize"/>
/// and <see cref="PFMultiplayerServerRequestPartyServiceGetResult"/> to get the result.
/// </remarks>
#if 0
bool PLAYFABSERVICES_API FPFMultiplayerServerRequestPartyServiceAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFMultiplayerServerRequestPartyServiceRequest* request,
	_Inout_ FOnRequestPartyServiceCompleted delegate
) noexcept;
#endif

/// <summary>
/// Uploads a multiplayer server game secret.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// Uploads a multiplayer server game secret. See also MultiplayerServerDeleteSecretAsync, MultiplayerServerListSecretSummariesAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_API_NOT_ENABLED_FOR_GAME_CLIENT_ACCESS, E_PF_MULTIPLAYER_SERVER_BAD_REQUEST,
/// E_PF_MULTIPLAYER_SERVER_CONFLICT, E_PF_MULTIPLAYER_SERVER_FORBIDDEN, E_PF_MULTIPLAYER_SERVER_INTERNAL_SERVER_ERROR,
/// E_PF_MULTIPLAYER_SERVER_NO_CONTENT, E_PF_MULTIPLAYER_SERVER_NOT_FOUND, E_PF_MULTIPLAYER_SERVER_TOO_MANY_REQUESTS,
/// E_PF_MULTIPLAYER_SERVER_UNAUTHORIZED, E_PF_MULTIPLAYER_SERVER_UNAVAILABLE or any of the global PlayFab
/// Service errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if 0
bool PLAYFABSERVICES_API FPFMultiplayerServerUploadSecretAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFMultiplayerServerUploadSecretRequest* request,
	_Inout_ FOnUploadSecretCompleted delegate
) noexcept;
#endif

}
