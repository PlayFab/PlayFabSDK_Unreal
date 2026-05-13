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
#include "PFLeaderboardsUnrealTypes.h"
#include "PFLeaderboardsTypeConverters.h"

THIRD_PARTY_INCLUDES_START
#include <playfab/services/PFServices.h>
THIRD_PARTY_INCLUDES_END

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Creates a new leaderboard definition.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FCreateLeaderboardDefinitionAsyncTask : public FXAsyncTask
{
public:
	FCreateLeaderboardDefinitionAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFLeaderboardsCreateLeaderboardDefinitionRequest InRequest,
	const FOnCreateLeaderboardDefinitionCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFLeaderboardsCreateLeaderboardDefinitionRequest Request;
	
	FOnCreateLeaderboardDefinitionCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Deletes a leaderboard definition.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FDeleteLeaderboardDefinitionAsyncTask : public FXAsyncTask
{
public:
	FDeleteLeaderboardDefinitionAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFLeaderboardsDeleteLeaderboardDefinitionRequest InRequest,
	const FOnDeleteLeaderboardDefinitionCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFLeaderboardsDeleteLeaderboardDefinitionRequest Request;
	
	FOnDeleteLeaderboardDefinitionCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Deletes the specified entries from the given leaderboard.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FDeleteLeaderboardEntriesAsyncTask : public FXAsyncTask
{
public:
	FDeleteLeaderboardEntriesAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFLeaderboardsDeleteLeaderboardEntriesRequest InRequest,
	const FOnDeleteLeaderboardEntriesCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFLeaderboardsDeleteLeaderboardEntriesRequest Request;
	
	FOnDeleteLeaderboardEntriesCompleted Delegate;

	HRESULT HResult;
};

#endif


/// <summary>
/// Get the friend leaderboard for the specified entity. A maximum of 25 friend entries are listed in
/// the leaderboard.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFLeaderboardsGetFriendLeaderboardForEntityGetResultSize"/>
/// and <see cref="PFLeaderboardsGetFriendLeaderboardForEntityGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FGetFriendLeaderboardForEntityAsyncTask : public FXAsyncTask
{
public:
	FGetFriendLeaderboardForEntityAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFLeaderboardsGetFriendLeaderboardForEntityRequest InRequest,
	const FOnGetFriendLeaderboardForEntityCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFLeaderboardsGetFriendLeaderboardForEntityRequest Request;
	
	FOnGetFriendLeaderboardForEntityCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Get the leaderboard for a specific entity type and statistic.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFLeaderboardsGetLeaderboardGetResultSize"/>
/// and <see cref="PFLeaderboardsGetLeaderboardGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FGetLeaderboardAsyncTask : public FXAsyncTask
{
public:
	FGetLeaderboardAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFLeaderboardsGetEntityLeaderboardRequest InRequest,
	const FOnGetLeaderboardCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFLeaderboardsGetEntityLeaderboardRequest Request;
	
	FOnGetLeaderboardCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Get the leaderboard around a specific entity.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFLeaderboardsGetLeaderboardAroundEntityGetResultSize"/>
/// and <see cref="PFLeaderboardsGetLeaderboardAroundEntityGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FGetLeaderboardAroundEntityAsyncTask : public FXAsyncTask
{
public:
	FGetLeaderboardAroundEntityAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFLeaderboardsGetLeaderboardAroundEntityRequest InRequest,
	const FOnGetLeaderboardAroundEntityCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFLeaderboardsGetLeaderboardAroundEntityRequest Request;
	
	FOnGetLeaderboardAroundEntityCompleted Delegate;

	HRESULT HResult;
};


#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Gets the specified leaderboard definition.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also LeaderboardDeleteLeaderboardDefinitionAsync.
///
/// When the asynchronous task is complete, call <see cref="PFLeaderboardsGetLeaderboardDefinitionGetResultSize"/>
/// and <see cref="PFLeaderboardsGetLeaderboardDefinitionGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FGetLeaderboardDefinitionAsyncTask : public FXAsyncTask
{
public:
	FGetLeaderboardDefinitionAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFLeaderboardsGetLeaderboardDefinitionRequest InRequest,
	const FOnGetLeaderboardDefinitionCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFLeaderboardsGetLeaderboardDefinitionRequest Request;
	
	FOnGetLeaderboardDefinitionCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Get the leaderboard limited to a set of entities.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFLeaderboardsGetLeaderboardForEntitiesGetResultSize"/>
/// and <see cref="PFLeaderboardsGetLeaderboardForEntitiesGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FGetLeaderboardForEntitiesAsyncTask : public FXAsyncTask
{
public:
	FGetLeaderboardForEntitiesAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFLeaderboardsGetLeaderboardForEntitiesRequest InRequest,
	const FOnGetLeaderboardForEntitiesCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFLeaderboardsGetLeaderboardForEntitiesRequest Request;
	
	FOnGetLeaderboardForEntitiesCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Increment a leaderboard version.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also LeaderboardCreateLeaderboardDefinitionAsync.
///
/// When the asynchronous task is complete, call <see cref="PFLeaderboardsIncrementLeaderboardVersionGetResult"/>
/// to get the result.
/// </remarks>
class PLAYFABSERVICES_API FIncrementLeaderboardVersionAsyncTask : public FXAsyncTask
{
public:
	FIncrementLeaderboardVersionAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFLeaderboardsIncrementLeaderboardVersionRequest InRequest,
	const FOnIncrementLeaderboardVersionCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFLeaderboardsIncrementLeaderboardVersionRequest Request;
	
	FOnIncrementLeaderboardVersionCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Lists the leaderboard definitions defined for the Title.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also LeaderboardDeleteLeaderboardDefinitionAsync.
///
/// When the asynchronous task is complete, call <see cref="PFLeaderboardsListLeaderboardDefinitionsGetResultSize"/>
/// and <see cref="PFLeaderboardsListLeaderboardDefinitionsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FListLeaderboardDefinitionsAsyncTask : public FXAsyncTask
{
public:
	FListLeaderboardDefinitionsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFLeaderboardsListLeaderboardDefinitionsRequest InRequest,
	const FOnListLeaderboardDefinitionsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFLeaderboardsListLeaderboardDefinitionsRequest Request;
	
	FOnListLeaderboardDefinitionsCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Unlinks a leaderboard definition from it's linked statistic definition.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FUnlinkLeaderboardFromStatisticAsyncTask : public FXAsyncTask
{
public:
	FUnlinkLeaderboardFromStatisticAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFLeaderboardsUnlinkLeaderboardFromStatisticRequest InRequest,
	const FOnUnlinkLeaderboardFromStatisticCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFLeaderboardsUnlinkLeaderboardFromStatisticRequest Request;
	
	FOnUnlinkLeaderboardFromStatisticCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK

/// <summary>
/// Updates a leaderboard definition.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FUpdateLeaderboardDefinitionAsyncTask : public FXAsyncTask
{
public:
	FUpdateLeaderboardDefinitionAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFLeaderboardsUpdateLeaderboardDefinitionRequest InRequest,
	const FOnUpdateLeaderboardDefinitionCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFLeaderboardsUpdateLeaderboardDefinitionRequest Request;
	
	FOnUpdateLeaderboardDefinitionCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Adds or updates entries on the specified leaderboard.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FUpdateLeaderboardEntriesAsyncTask : public FXAsyncTask
{
public:
	FUpdateLeaderboardEntriesAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFLeaderboardsUpdateLeaderboardEntriesRequest InRequest,
	const FOnUpdateLeaderboardEntriesCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFLeaderboardsUpdateLeaderboardEntriesRequest Request;
	
	FOnUpdateLeaderboardEntriesCompleted Delegate;

	HRESULT HResult;
};

#endif
