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
#include "PFStatisticsUnrealTypes.h"
#include "PFStatisticsTypeConverters.h"

THIRD_PARTY_INCLUDES_START
#include <playfab/services/PFServices.h>
THIRD_PARTY_INCLUDES_END

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Create a new entity statistic definition.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also StatisticDeleteStatisticDefinitionAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_AGGREGATION_TYPE_NOT_ALLOWED_FOR_MULTI_COLUMN_STATISTIC, E_PF_API_NOT_ENABLED_FOR_TITLE,
/// E_PF_DUPLICATE_COLUMN_NAME_FOUND, E_PF_DUPLICATE_STATISTIC_NAME, E_PF_EXTERNAL_ENTITY_NOT_ALLOWED_FOR_TIER,
/// E_PF_INVALID_BASE_TIME_FOR_INTERVAL, E_PF_MAX_QUERYABLE_VERSIONS_VALUE_NOT_ALLOWED_FOR_TIER, E_PF_STATISTIC_COUNT_LIMIT_EXCEEDED,
/// E_PF_STATISTIC_DEFINITION_HAS_NULL_OR_EMPTY_VERSION_CONFIGURATION, E_PF_STATISTIC_NAME_CONFLICT, E_PF_VERSION_CONFIGURATION_IS_REQUIRED
/// or any of the global PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details
/// on error handling.
/// </remarks>
class PLAYFABSERVICES_API FCreateStatisticDefinitionAsyncTask : public FXAsyncTask
{
public:
	FCreateStatisticDefinitionAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFStatisticsCreateStatisticDefinitionRequest InRequest,
	const FOnCreateStatisticDefinitionCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFStatisticsCreateStatisticDefinitionRequest Request;
	
	FOnCreateStatisticDefinitionCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Delete an entity statistic definition. Will delete all statistics on entity profiles and leaderboards.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also StatisticCreateStatisticDefinitionAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_STATISTIC_DEFINITION_MODIFICATION_NOT_ALLOWED_WHILE_LINKED, E_PF_STATISTIC_NOT_FOUND,
/// E_PF_STATISTIC_UPDATE_IN_PROGRESS or any of the global PlayFab Service errors. See doc page "Handling
/// PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FDeleteStatisticDefinitionAsyncTask : public FXAsyncTask
{
public:
	FDeleteStatisticDefinitionAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFStatisticsDeleteStatisticDefinitionRequest InRequest,
	const FOnDeleteStatisticDefinitionCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFStatisticsDeleteStatisticDefinitionRequest Request;
	
	FOnDeleteStatisticDefinitionCompleted Delegate;

	HRESULT HResult;
};

#endif


/// <summary>
/// Delete statistics on an entity profile. This will remove all rankings from associated leaderboards.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// See also StatisticUpdateStatisticsAsync.
///
/// When the asynchronous task is complete, call <see cref="PFStatisticsDeleteStatisticsGetResultSize"/>
/// and <see cref="PFStatisticsDeleteStatisticsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FDeleteStatisticsAsyncTask : public FXAsyncTask
{
public:
	FDeleteStatisticsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFStatisticsDeleteStatisticsRequest InRequest,
	const FOnDeleteStatisticsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFStatisticsDeleteStatisticsRequest Request;
	
	FOnDeleteStatisticsCompleted Delegate;

	HRESULT HResult;
};


#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Get current statistic definition information
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also StatisticCreateStatisticDefinitionAsync, StatisticDeleteStatisticDefinitionAsync.
///
/// When the asynchronous task is complete, call <see cref="PFStatisticsGetStatisticDefinitionGetResultSize"/>
/// and <see cref="PFStatisticsGetStatisticDefinitionGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FGetStatisticDefinitionAsyncTask : public FXAsyncTask
{
public:
	FGetStatisticDefinitionAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFStatisticsGetStatisticDefinitionRequest InRequest,
	const FOnGetStatisticDefinitionCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFStatisticsGetStatisticDefinitionRequest Request;
	
	FOnGetStatisticDefinitionCompleted Delegate;

	HRESULT HResult;
};

#endif


/// <summary>
/// Gets statistics for the specified entity.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// See also StatisticDeleteStatisticsAsync.
///
/// When the asynchronous task is complete, call <see cref="PFStatisticsGetStatisticsGetResultSize"/>
/// and <see cref="PFStatisticsGetStatisticsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FGetStatisticsAsyncTask : public FXAsyncTask
{
public:
	FGetStatisticsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFStatisticsGetStatisticsRequest InRequest,
	const FOnGetStatisticsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFStatisticsGetStatisticsRequest Request;
	
	FOnGetStatisticsCompleted Delegate;

	HRESULT HResult;
};


#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Gets statistics for the specified collection of entities.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also StatisticDeleteStatisticsAsync.
///
/// When the asynchronous task is complete, call <see cref="PFStatisticsGetStatisticsForEntitiesGetResultSize"/>
/// and <see cref="PFStatisticsGetStatisticsForEntitiesGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FGetStatisticsForEntitiesAsyncTask : public FXAsyncTask
{
public:
	FGetStatisticsForEntitiesAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFStatisticsGetStatisticsForEntitiesRequest InRequest,
	const FOnGetStatisticsForEntitiesCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFStatisticsGetStatisticsForEntitiesRequest Request;
	
	FOnGetStatisticsForEntitiesCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Increment an entity statistic definition version.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also StatisticCreateStatisticDefinitionAsync.
///
/// When the asynchronous task is complete, call <see cref="PFStatisticsIncrementStatisticVersionGetResult"/>
/// to get the result.
/// </remarks>
class PLAYFABSERVICES_API FIncrementStatisticVersionAsyncTask : public FXAsyncTask
{
public:
	FIncrementStatisticVersionAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFStatisticsIncrementStatisticVersionRequest InRequest,
	const FOnIncrementStatisticVersionCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFStatisticsIncrementStatisticVersionRequest Request;
	
	FOnIncrementStatisticVersionCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Get all current statistic definitions information
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also StatisticCreateStatisticDefinitionAsync, StatisticDeleteStatisticDefinitionAsync.
///
/// When the asynchronous task is complete, call <see cref="PFStatisticsListStatisticDefinitionsGetResultSize"/>
/// and <see cref="PFStatisticsListStatisticDefinitionsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FListStatisticDefinitionsAsyncTask : public FXAsyncTask
{
public:
	FListStatisticDefinitionsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFStatisticsListStatisticDefinitionsRequest InRequest,
	const FOnListStatisticDefinitionsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFStatisticsListStatisticDefinitionsRequest Request;
	
	FOnListStatisticDefinitionsCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK

/// <summary>
/// Update an existing entity statistic definition.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows.
/// See also StatisticCreateStatisticDefinitionAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_API_NOT_ENABLED_FOR_TITLE, E_PF_INVALID_BASE_TIME_FOR_INTERVAL, E_PF_MAX_QUERYABLE_VERSIONS_VALUE_NOT_ALLOWED_FOR_TIER,
/// E_PF_RESET_INTERVAL_CANNOT_BE_MODIFIED, E_PF_STATISTIC_NOT_FOUND or any of the global PlayFab Service
/// errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FUpdateStatisticDefinitionAsyncTask : public FXAsyncTask
{
public:
	FUpdateStatisticDefinitionAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFStatisticsUpdateStatisticDefinitionRequest InRequest,
	const FOnUpdateStatisticDefinitionCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFStatisticsUpdateStatisticDefinitionRequest Request;
	
	FOnUpdateStatisticDefinitionCompleted Delegate;

	HRESULT HResult;
};

#endif


/// <summary>
/// Update statistics on an entity profile. Depending on the statistic definition, this may result in
/// entity being ranked on various leaderboards.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// See also StatisticDeleteStatisticsAsync.
///
/// When the asynchronous task is complete, call <see cref="PFStatisticsUpdateStatisticsGetResultSize"/>
/// and <see cref="PFStatisticsUpdateStatisticsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FUpdateStatisticsAsyncTask : public FXAsyncTask
{
public:
	FUpdateStatisticsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFStatisticsUpdateStatisticsRequest InRequest,
	const FOnUpdateStatisticsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFStatisticsUpdateStatisticsRequest Request;
	
	FOnUpdateStatisticsCompleted Delegate;

	HRESULT HResult;
};

