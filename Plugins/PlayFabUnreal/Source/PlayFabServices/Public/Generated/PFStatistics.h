// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include "CoreMinimal.h"
#include "XAsyncTaskManager.h"
#include "PFStatisticsAsyncTasks.h"

THIRD_PARTY_INCLUDES_START
#include <playfab/services/PFServices.h>
THIRD_PARTY_INCLUDES_END

extern "C"
{
/// <summary>
/// Create a new entity statistic definition.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also StatisticDeleteStatisticDefinitionAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_AGGREGATION_TYPE_NOT_ALLOWED_FOR_LINKED_STAT, E_PF_AGGREGATION_TYPE_NOT_ALLOWED_FOR_MULTI_COLUMN_STATISTIC,
/// E_PF_API_NOT_ENABLED_FOR_TITLE, E_PF_DUPLICATE_COLUMN_NAME_FOUND, E_PF_DUPLICATE_STATISTIC_NAME, E_PF_ENTITY_TYPE_SPECIFIED_REQUIRES_AGGREGATION_SOURCE,
/// E_PF_EXTERNAL_ENTITY_NOT_ALLOWED_FOR_TIER, E_PF_INVALID_BASE_TIME_FOR_INTERVAL, E_PF_INVALID_ENTITY_TYPE_FOR_AGGREGATION,
/// E_PF_MAX_QUERYABLE_VERSIONS_EXCEEDED, E_PF_MAX_QUERYABLE_VERSIONS_VALUE_NOT_ALLOWED_FOR_TIER, E_PF_MULTI_LEVEL_AGGREGATION_NOT_ALLOWED,
/// E_PF_PLAY_FAB_ERROR_EVENT_NOT_SUPPORTED_FOR_ENTITY_TYPE, E_PF_STATISTIC_COLUMN_AGGREGATION_MISMATCH,
/// E_PF_STATISTIC_COLUMN_LENGTH_MISMATCH, E_PF_STATISTIC_COUNT_LIMIT_EXCEEDED, E_PF_STATISTIC_DEFINITION_HAS_NULL_OR_EMPTY_VERSION_CONFIGURATION,
/// E_PF_STATISTIC_NAME_CONFLICT, E_PF_STATISTIC_NOT_FOUND, E_PF_VERSION_CONFIGURATION_CANNOT_BE_SPECIFIED_FOR_LINKED_STAT,
/// E_PF_VERSION_CONFIGURATION_IS_REQUIRED or any of the global PlayFab Service errors. See doc page "Handling
/// PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFStatisticsCreateStatisticDefinitionAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFStatisticsCreateStatisticDefinitionRequest* request,
	_Inout_ FOnCreateStatisticDefinitionCompleted delegate
) noexcept;
#endif

/// <summary>
/// Delete an entity statistic definition. Will delete all statistics on entity profiles and leaderboards.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
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
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFStatisticsDeleteStatisticDefinitionAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFStatisticsDeleteStatisticDefinitionRequest* request,
	_Inout_ FOnDeleteStatisticDefinitionCompleted delegate
) noexcept;
#endif

/// <summary>
/// Delete statistics on an entity profile. This will remove all rankings from associated leaderboards.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// See also StatisticUpdateStatisticsAsync.
///
/// When the asynchronous task is complete, call <see cref="PFStatisticsDeleteStatisticsGetResultSize"/>
/// and <see cref="PFStatisticsDeleteStatisticsGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFStatisticsDeleteStatisticsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFStatisticsDeleteStatisticsRequest* request,
	_Inout_ FOnDeleteStatisticsCompleted delegate
) noexcept;

/// <summary>
/// Get current statistic definition information
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also StatisticCreateStatisticDefinitionAsync, StatisticDeleteStatisticDefinitionAsync.
///
/// When the asynchronous task is complete, call <see cref="PFStatisticsGetStatisticDefinitionGetResultSize"/>
/// and <see cref="PFStatisticsGetStatisticDefinitionGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFStatisticsGetStatisticDefinitionAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFStatisticsGetStatisticDefinitionRequest* request,
	_Inout_ FOnGetStatisticDefinitionCompleted delegate
) noexcept;
#endif

/// <summary>
/// Gets statistics for the specified entity.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// See also StatisticDeleteStatisticsAsync.
///
/// When the asynchronous task is complete, call <see cref="PFStatisticsGetStatisticsGetResultSize"/>
/// and <see cref="PFStatisticsGetStatisticsGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFStatisticsGetStatisticsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFStatisticsGetStatisticsRequest* request,
	_Inout_ FOnGetStatisticsCompleted delegate
) noexcept;

/// <summary>
/// Gets statistics for the specified collection of entities.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also StatisticDeleteStatisticsAsync.
///
/// When the asynchronous task is complete, call <see cref="PFStatisticsGetStatisticsForEntitiesGetResultSize"/>
/// and <see cref="PFStatisticsGetStatisticsForEntitiesGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFStatisticsGetStatisticsForEntitiesAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFStatisticsGetStatisticsForEntitiesRequest* request,
	_Inout_ FOnGetStatisticsForEntitiesCompleted delegate
) noexcept;
#endif

/// <summary>
/// Increment an entity statistic definition version.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also StatisticCreateStatisticDefinitionAsync.
///
/// When the asynchronous task is complete, call <see cref="PFStatisticsIncrementStatisticVersionGetResult"/>
/// to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFStatisticsIncrementStatisticVersionAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFStatisticsIncrementStatisticVersionRequest* request,
	_Inout_ FOnIncrementStatisticVersionCompleted delegate
) noexcept;
#endif

/// <summary>
/// Get all current statistic definitions information
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also StatisticCreateStatisticDefinitionAsync, StatisticDeleteStatisticDefinitionAsync.
///
/// When the asynchronous task is complete, call <see cref="PFStatisticsListStatisticDefinitionsGetResultSize"/>
/// and <see cref="PFStatisticsListStatisticDefinitionsGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFStatisticsListStatisticDefinitionsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFStatisticsListStatisticDefinitionsRequest* request,
	_Inout_ FOnListStatisticDefinitionsCompleted delegate
) noexcept;
#endif

/// <summary>
/// Unlinks an aggregation source from a statistic definition.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// See also StatisticCreateStatisticDefinitionAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_API_NOT_ENABLED_FOR_TITLE, E_PF_STATISTIC_NOT_FOUND or any of the global
/// PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if 0
bool PLAYFABSERVICES_API FPFStatisticsUnlinkAggregationSourceFromStatisticAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFStatisticsUnlinkAggregationSourceFromStatisticRequest* request,
	_Inout_ FOnUnlinkAggregationSourceFromStatisticCompleted delegate
) noexcept;
#endif

/// <summary>
/// Update an existing entity statistic definition.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows.
/// See also StatisticCreateStatisticDefinitionAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_API_NOT_ENABLED_FOR_TITLE, E_PF_INVALID_BASE_TIME_FOR_INTERVAL, E_PF_MAX_QUERYABLE_VERSIONS_EXCEEDED,
/// E_PF_MAX_QUERYABLE_VERSIONS_VALUE_NOT_ALLOWED_FOR_TIER, E_PF_RESET_INTERVAL_CANNOT_BE_MODIFIED, E_PF_STATISTIC_NOT_FOUND
/// or any of the global PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details
/// on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFStatisticsUpdateStatisticDefinitionAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFStatisticsUpdateStatisticDefinitionRequest* request,
	_Inout_ FOnUpdateStatisticDefinitionCompleted delegate
) noexcept;
#endif

/// <summary>
/// Update statistics on an entity profile. Depending on the statistic definition, this may result in
/// entity being ranked on various leaderboards.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// See also StatisticDeleteStatisticsAsync.
///
/// When the asynchronous task is complete, call <see cref="PFStatisticsUpdateStatisticsGetResultSize"/>
/// and <see cref="PFStatisticsUpdateStatisticsGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFStatisticsUpdateStatisticsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFStatisticsUpdateStatisticsRequest* request,
	_Inout_ FOnUpdateStatisticsCompleted delegate
) noexcept;

}
