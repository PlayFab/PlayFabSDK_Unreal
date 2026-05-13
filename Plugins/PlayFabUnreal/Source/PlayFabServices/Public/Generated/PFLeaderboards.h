// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include "CoreMinimal.h"
#include "XAsyncTaskManager.h"
#include "PFLeaderboardsAsyncTasks.h"

THIRD_PARTY_INCLUDES_START
#include <playfab/services/PFServices.h>
THIRD_PARTY_INCLUDES_END

extern "C"
{
/// <summary>
/// Creates a new leaderboard definition.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also LeaderboardDeleteLeaderboardDefinitionAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_API_NOT_ENABLED_FOR_TITLE, E_PF_DUPLICATE_COLUMN_NAME_FOUND, E_PF_DUPLICATE_LINKED_STATISTIC_COLUMN_NAME_FOUND,
/// E_PF_ENTITY_TYPE_MISMATCH_WITH_STAT_DEFINITION, E_PF_EXTERNAL_ENTITY_NOT_ALLOWED_FOR_TIER, E_PF_INVALID_BASE_TIME_FOR_INTERVAL,
/// E_PF_LEADERBOARD_COUNT_LIMIT_EXCEEDED, E_PF_LEADERBOARD_NAME_CONFLICT, E_PF_LEADERBOARD_SIZE_LIMIT_EXCEEDED,
/// E_PF_LINKED_STATISTIC_COLUMN_MISMATCH, E_PF_LINKED_STATISTIC_COLUMN_NOT_FOUND, E_PF_LINKED_STATISTIC_COLUMN_REQUIRED,
/// E_PF_LINKING_STATS_NOT_ALLOWED_FOR_ENTITY_TYPE, E_PF_MAX_QUERYABLE_VERSIONS_EXCEEDED, E_PF_MAX_QUERYABLE_VERSIONS_VALUE_NOT_ALLOWED_FOR_TIER,
/// E_PF_MULTIPLE_LINKED_STATISTICS_NOT_ALLOWED, E_PF_PLAY_FAB_ERROR_EVENT_NOT_SUPPORTED_FOR_ENTITY_TYPE,
/// E_PF_STAT_DEFINITION_ALREADY_LINKED_TO_LEADERBOARD, E_PF_STATISTIC_NOT_FOUND, E_PF_VERSION_CONFIGURATION_IS_REQUIRED
/// or any of the global PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details
/// on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFLeaderboardsCreateLeaderboardDefinitionAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFLeaderboardsCreateLeaderboardDefinitionRequest* request,
	_Inout_ FOnCreateLeaderboardDefinitionCompleted delegate
) noexcept;
#endif

/// <summary>
/// Deletes a leaderboard definition.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also LeaderboardCreateLeaderboardDefinitionAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_LEADERBOARD_DEFINITION_MODIFICATION_NOT_ALLOWED_WHILE_LINKED, E_PF_LEADERBOARD_NOT_FOUND
/// or any of the global PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details
/// on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFLeaderboardsDeleteLeaderboardDefinitionAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFLeaderboardsDeleteLeaderboardDefinitionRequest* request,
	_Inout_ FOnDeleteLeaderboardDefinitionCompleted delegate
) noexcept;
#endif

/// <summary>
/// Deletes the specified entries from the given leaderboard.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also LeaderboardUpdateLeaderboardEntriesAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_API_NOT_ENABLED_FOR_TITLE, E_PF_LEADERBOARD_NOT_FOUND, E_PF_LEADERBOARD_UPDATE_NOT_ALLOWED_WHILE_LINKED
/// or any of the global PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details
/// on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFLeaderboardsDeleteLeaderboardEntriesAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFLeaderboardsDeleteLeaderboardEntriesRequest* request,
	_Inout_ FOnDeleteLeaderboardEntriesCompleted delegate
) noexcept;
#endif

/// <summary>
/// Get the friend leaderboard for the specified entity. A maximum of 25 friend entries are listed in
/// the leaderboard.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFLeaderboardsGetFriendLeaderboardForEntityGetResultSize"/>
/// and <see cref="PFLeaderboardsGetFriendLeaderboardForEntityGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFLeaderboardsGetFriendLeaderboardForEntityAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFLeaderboardsGetFriendLeaderboardForEntityRequest* request,
	_Inout_ FOnGetFriendLeaderboardForEntityCompleted delegate
) noexcept;

/// <summary>
/// Get the leaderboard for a specific entity type and statistic.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFLeaderboardsGetLeaderboardGetResultSize"/>
/// and <see cref="PFLeaderboardsGetLeaderboardGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFLeaderboardsGetLeaderboardAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFLeaderboardsGetEntityLeaderboardRequest* request,
	_Inout_ FOnGetLeaderboardCompleted delegate
) noexcept;

/// <summary>
/// Get the leaderboard around a specific entity.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFLeaderboardsGetLeaderboardAroundEntityGetResultSize"/>
/// and <see cref="PFLeaderboardsGetLeaderboardAroundEntityGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFLeaderboardsGetLeaderboardAroundEntityAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFLeaderboardsGetLeaderboardAroundEntityRequest* request,
	_Inout_ FOnGetLeaderboardAroundEntityCompleted delegate
) noexcept;

/// <summary>
/// Gets the specified leaderboard definition.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also LeaderboardDeleteLeaderboardDefinitionAsync.
///
/// When the asynchronous task is complete, call <see cref="PFLeaderboardsGetLeaderboardDefinitionGetResultSize"/>
/// and <see cref="PFLeaderboardsGetLeaderboardDefinitionGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFLeaderboardsGetLeaderboardDefinitionAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFLeaderboardsGetLeaderboardDefinitionRequest* request,
	_Inout_ FOnGetLeaderboardDefinitionCompleted delegate
) noexcept;
#endif

/// <summary>
/// Get the leaderboard limited to a set of entities.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFLeaderboardsGetLeaderboardForEntitiesGetResultSize"/>
/// and <see cref="PFLeaderboardsGetLeaderboardForEntitiesGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFLeaderboardsGetLeaderboardForEntitiesAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFLeaderboardsGetLeaderboardForEntitiesRequest* request,
	_Inout_ FOnGetLeaderboardForEntitiesCompleted delegate
) noexcept;
#endif

/// <summary>
/// Increment a leaderboard version.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also LeaderboardCreateLeaderboardDefinitionAsync.
///
/// When the asynchronous task is complete, call <see cref="PFLeaderboardsIncrementLeaderboardVersionGetResult"/>
/// to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFLeaderboardsIncrementLeaderboardVersionAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFLeaderboardsIncrementLeaderboardVersionRequest* request,
	_Inout_ FOnIncrementLeaderboardVersionCompleted delegate
) noexcept;
#endif

/// <summary>
/// Lists the leaderboard definitions defined for the Title.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also LeaderboardDeleteLeaderboardDefinitionAsync.
///
/// When the asynchronous task is complete, call <see cref="PFLeaderboardsListLeaderboardDefinitionsGetResultSize"/>
/// and <see cref="PFLeaderboardsListLeaderboardDefinitionsGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFLeaderboardsListLeaderboardDefinitionsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFLeaderboardsListLeaderboardDefinitionsRequest* request,
	_Inout_ FOnListLeaderboardDefinitionsCompleted delegate
) noexcept;
#endif

/// <summary>
/// Unlinks a leaderboard definition from it's linked statistic definition.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also LeaderboardCreateLeaderboardDefinitionAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_LEADERBOARD_NOT_FOUND, E_PF_NO_LINKED_STATISTIC_TO_LEADERBOARD or any
/// of the global PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details on error
/// handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFLeaderboardsUnlinkLeaderboardFromStatisticAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFLeaderboardsUnlinkLeaderboardFromStatisticRequest* request,
	_Inout_ FOnUnlinkLeaderboardFromStatisticCompleted delegate
) noexcept;
#endif

/// <summary>
/// Updates a leaderboard definition.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows.
/// See also LeaderboardDeleteLeaderboardDefinitionAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_LEADERBOARD_SIZE_LIMIT_EXCEEDED, E_PF_MAX_QUERYABLE_VERSIONS_EXCEEDED,
/// E_PF_MAX_QUERYABLE_VERSIONS_VALUE_NOT_ALLOWED_FOR_TIER, E_PF_PLAY_FAB_ERROR_EVENT_NOT_SUPPORTED_FOR_ENTITY_TYPE,
/// E_PF_RESET_INTERVAL_CANNOT_BE_MODIFIED or any of the global PlayFab Service errors. See doc page "Handling
/// PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFLeaderboardsUpdateLeaderboardDefinitionAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFLeaderboardsUpdateLeaderboardDefinitionRequest* request,
	_Inout_ FOnUpdateLeaderboardDefinitionCompleted delegate
) noexcept;
#endif

/// <summary>
/// Adds or updates entries on the specified leaderboard.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also LeaderboardDeleteLeaderboardEntriesAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_API_NOT_ENABLED_FOR_GAME_CLIENT_ACCESS, E_PF_LEADERBOARD_COLUMN_LENGTH_MISMATCH,
/// E_PF_LEADERBOARD_NOT_FOUND, E_PF_LEADERBOARD_UPDATE_NOT_ALLOWED_WHILE_LINKED, E_PF_METADATA_LENGTH_EXCEEDED
/// or any of the global PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details
/// on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFLeaderboardsUpdateLeaderboardEntriesAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFLeaderboardsUpdateLeaderboardEntriesRequest* request,
	_Inout_ FOnUpdateLeaderboardEntriesCompleted delegate
) noexcept;
#endif

}
