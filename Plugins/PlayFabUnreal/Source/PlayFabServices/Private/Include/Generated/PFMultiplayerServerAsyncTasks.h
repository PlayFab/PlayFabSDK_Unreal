// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#include "CoreMinimal.h"
#include "Async/AsyncWork.h"
#include "Async/Async.h"
#include "XAsyncTaskQueueHelpers.h"
#include "XAsyncTaskManager.h"
#include "XAsyncTask.h"
#include "PFEntity.h"
#include "PFServiceConfig.h"
#include "PFMultiplayerServerUnrealTypes.h"
#include "PFMultiplayerServerTypeConverters.h"

THIRD_PARTY_INCLUDES_START
#include <playfab/services/PFServices.h>
THIRD_PARTY_INCLUDES_END

#if 0

/// <summary>
/// Deletes a multiplayer server game secret.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FDeleteSecretAsyncTask : public FXAsyncTask
{
public:
	FDeleteSecretAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFMultiplayerServerDeleteSecretRequest InRequest,
	const FOnDeleteSecretCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFMultiplayerServerDeleteSecretRequest Request;
	
	FOnDeleteSecretCompleted Delegate;

	HRESULT HResult;
};

#endif


/// <summary>
/// Lists details of all build aliases for a title. Accepts tokens for title and if game client access
/// is enabled, allows game client to request list of builds with player entity token.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Returns a list of summarized details of all multiplayer server builds for a title. See also MultiplayerServerCreateBuildWithManagedContainerAsync,
/// MultiplayerServerDeleteBuildAsync, MultiplayerServerGetBuildAsync.
///
/// When the asynchronous task is complete, call <see cref="PFMultiplayerServerListBuildAliasesGetResultSize"/>
/// and <see cref="PFMultiplayerServerListBuildAliasesGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FListBuildAliasesAsyncTask : public FXAsyncTask
{
public:
	FListBuildAliasesAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFMultiplayerServerListBuildAliasesRequest InRequest,
	const FOnListBuildAliasesCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFMultiplayerServerListBuildAliasesRequest Request;
	
	FOnListBuildAliasesCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Lists summarized details of all multiplayer server builds for a title. Accepts tokens for title and
/// if game client access is enabled, allows game client to request list of builds with player entity
/// token.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Returns a list of summarized details of all multiplayer server builds for a title. See also MultiplayerServerCreateBuildWithManagedContainerAsync,
/// MultiplayerServerDeleteBuildAsync, MultiplayerServerGetBuildAsync.
///
/// When the asynchronous task is complete, call <see cref="PFMultiplayerServerListBuildSummariesV2GetResultSize"/>
/// and <see cref="PFMultiplayerServerListBuildSummariesV2GetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FListBuildSummariesV2AsyncTask : public FXAsyncTask
{
public:
	FListBuildSummariesV2AsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFMultiplayerServerListBuildSummariesRequest InRequest,
	const FOnListBuildSummariesV2Completed& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFMultiplayerServerListBuildSummariesRequest Request;
	
	FOnListBuildSummariesV2Completed Delegate;

	HRESULT HResult;
};



/// <summary>
/// Lists quality of service servers for the title. By default, servers are only returned for regions
/// where a Multiplayer Servers build has been deployed.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Returns a list of quality of service servers for a title.
///
/// When the asynchronous task is complete, call <see cref="PFMultiplayerServerListQosServersForTitleGetResultSize"/>
/// and <see cref="PFMultiplayerServerListQosServersForTitleGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FListQosServersForTitleAsyncTask : public FXAsyncTask
{
public:
	FListQosServersForTitleAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFMultiplayerServerListQosServersForTitleRequest InRequest,
	const FOnListQosServersForTitleCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFMultiplayerServerListQosServersForTitleRequest Request;
	
	FOnListQosServersForTitleCompleted Delegate;

	HRESULT HResult;
};


#if 0

/// <summary>
/// Lists multiplayer server game secrets for a title.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// Returns a list of multiplayer server game secrets for a title. See also MultiplayerServerDeleteSecretAsync,
/// MultiplayerServerUploadSecretAsync.
///
/// When the asynchronous task is complete, call <see cref="PFMultiplayerServerListSecretSummariesGetResultSize"/>
/// and <see cref="PFMultiplayerServerListSecretSummariesGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FListSecretSummariesAsyncTask : public FXAsyncTask
{
public:
	FListSecretSummariesAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFMultiplayerServerListSecretSummariesRequest InRequest,
	const FOnListSecretSummariesCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFMultiplayerServerListSecretSummariesRequest Request;
	
	FOnListSecretSummariesCompleted Delegate;

	HRESULT HResult;
};

#endif


/// <summary>
/// Request a multiplayer server session. Accepts tokens for title and if game client access is enabled,
/// allows game client to request a server with player entity token.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Requests a multiplayer server session from a particular build in any of the given preferred regions.
/// See also MultiplayerServerGetMultiplayerServerDetailsAsync.
///
/// When the asynchronous task is complete, call <see cref="PFMultiplayerServerRequestMultiplayerServerGetResultSize"/>
/// and <see cref="PFMultiplayerServerRequestMultiplayerServerGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FRequestMultiplayerServerAsyncTask : public FXAsyncTask
{
public:
	FRequestMultiplayerServerAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFMultiplayerServerRequestMultiplayerServerRequest InRequest,
	const FOnRequestMultiplayerServerCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFMultiplayerServerRequestMultiplayerServerRequest Request;
	
	FOnRequestMultiplayerServerCompleted Delegate;

	HRESULT HResult;
};


#if 0

/// <summary>
/// Request a party session.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// Requests a party session from a particular set of builds if build alias params is provided, in any
/// of the given preferred regions.
///
/// When the asynchronous task is complete, call <see cref="PFMultiplayerServerRequestPartyServiceGetResultSize"/>
/// and <see cref="PFMultiplayerServerRequestPartyServiceGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FRequestPartyServiceAsyncTask : public FXAsyncTask
{
public:
	FRequestPartyServiceAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFMultiplayerServerRequestPartyServiceRequest InRequest,
	const FOnRequestPartyServiceCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFMultiplayerServerRequestPartyServiceRequest Request;
	
	FOnRequestPartyServiceCompleted Delegate;

	HRESULT HResult;
};

#endif

#if 0

/// <summary>
/// Uploads a multiplayer server game secret.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FUploadSecretAsyncTask : public FXAsyncTask
{
public:
	FUploadSecretAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFMultiplayerServerUploadSecretRequest InRequest,
	const FOnUploadSecretCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFMultiplayerServerUploadSecretRequest Request;
	
	FOnUploadSecretCompleted Delegate;

	HRESULT HResult;
};

#endif
