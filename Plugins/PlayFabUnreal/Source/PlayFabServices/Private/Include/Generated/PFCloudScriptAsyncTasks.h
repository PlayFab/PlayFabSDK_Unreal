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
#include "PFCloudScriptUnrealTypes.h"
#include "PFCloudScriptTypeConverters.h"

THIRD_PARTY_INCLUDES_START
#include <playfab/services/PFServices.h>
THIRD_PARTY_INCLUDES_END


/// <summary>
/// Executes a CloudScript function, with the 'currentPlayerId' set to the PlayFab ID of the authenticated
/// player. The PlayFab ID is the entity ID of the player's master_player_account entity.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFCloudScriptClientExecuteCloudScriptGetResultSize"/>
/// and <see cref="PFCloudScriptClientExecuteCloudScriptGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FClientExecuteCloudScriptAsyncTask : public FXAsyncTask
{
public:
	FClientExecuteCloudScriptAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCloudScriptExecuteCloudScriptRequest InRequest,
	const FOnClientExecuteCloudScriptCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFCloudScriptExecuteCloudScriptRequest Request;
	
	FOnClientExecuteCloudScriptCompleted Delegate;

	HRESULT HResult;
};


#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Executes a CloudScript function, with the 'currentPlayerId' set to the PlayFab ID of the authenticated
/// player. The PlayFab ID is the entity ID of the player's master_player_account entity.
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFCloudScriptServerExecuteCloudScriptGetResultSize"/>
/// and <see cref="PFCloudScriptServerExecuteCloudScriptGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FServerExecuteCloudScriptAsyncTask : public FXAsyncTask
{
public:
	FServerExecuteCloudScriptAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFCloudScriptExecuteCloudScriptServerRequest InRequest,
	const FOnServerExecuteCloudScriptCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFCloudScriptExecuteCloudScriptServerRequest Request;
	
	FOnServerExecuteCloudScriptCompleted Delegate;

	HRESULT HResult;
};

#endif


/// <summary>
/// Cloud Script is one of PlayFab's most versatile features. It allows client code to request execution
/// of any kind of custom server-side functionality you can implement, and it can be used in conjunction
/// with virtually anything.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Executes CloudScript with the entity profile that is defined in the request.
///
/// When the asynchronous task is complete, call <see cref="PFCloudScriptExecuteEntityCloudScriptGetResultSize"/>
/// and <see cref="PFCloudScriptExecuteEntityCloudScriptGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FExecuteEntityCloudScriptAsyncTask : public FXAsyncTask
{
public:
	FExecuteEntityCloudScriptAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCloudScriptExecuteEntityCloudScriptRequest InRequest,
	const FOnExecuteEntityCloudScriptCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFCloudScriptExecuteEntityCloudScriptRequest Request;
	
	FOnExecuteEntityCloudScriptCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Cloud Script is one of PlayFab's most versatile features. It allows client code to request execution
/// of any kind of custom server-side functionality you can implement, and it can be used in conjunction
/// with virtually anything.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Executes an Azure Function with the profile of the entity that is defined in the request. See also
/// CloudScriptRegisterHttpFunctionAsync, CloudScriptRegisterQueuedFunctionAsync.
///
/// When the asynchronous task is complete, call <see cref="PFCloudScriptExecuteFunctionGetResultSize"/>
/// and <see cref="PFCloudScriptExecuteFunctionGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FExecuteFunctionAsyncTask : public FXAsyncTask
{
public:
	FExecuteFunctionAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCloudScriptExecuteFunctionRequest InRequest,
	const FOnExecuteFunctionCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFCloudScriptExecuteFunctionRequest Request;
	
	FOnExecuteFunctionCompleted Delegate;

	HRESULT HResult;
};


#if 0

/// <summary>
/// Lists all currently registered Event Hub triggered Azure Functions for a given title.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// See also CloudScriptListFunctionsAsync, CloudScriptListHttpFunctionsAsync, CloudScriptListQueuedFunctionsAsync,
/// CloudScriptRegisterEventHubFunctionAsync.
///
/// When the asynchronous task is complete, call <see cref="PFCloudScriptListEventHubFunctionsGetResultSize"/>
/// and <see cref="PFCloudScriptListEventHubFunctionsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FListEventHubFunctionsAsyncTask : public FXAsyncTask
{
public:
	FListEventHubFunctionsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCloudScriptListFunctionsRequest InRequest,
	const FOnListEventHubFunctionsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFCloudScriptListFunctionsRequest Request;
	
	FOnListEventHubFunctionsCompleted Delegate;

	HRESULT HResult;
};

#endif

#if 0

/// <summary>
/// Registers an event hub triggered Azure Function with a title.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FRegisterEventHubFunctionAsyncTask : public FXAsyncTask
{
public:
	FRegisterEventHubFunctionAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCloudScriptRegisterEventHubFunctionRequest InRequest,
	const FOnRegisterEventHubFunctionCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFCloudScriptRegisterEventHubFunctionRequest Request;
	
	FOnRegisterEventHubFunctionCompleted Delegate;

	HRESULT HResult;
};

#endif
