// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include "CoreMinimal.h"
#include "XAsyncTaskManager.h"
#include "PFSegmentsAsyncTasks.h"

THIRD_PARTY_INCLUDES_START
#include <playfab/services/PFServices.h>
THIRD_PARTY_INCLUDES_END

extern "C"
{
/// <summary>
/// List all segments that a player currently belongs to at this moment in time.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFSegmentsClientGetPlayerSegmentsGetResultSize"/>
/// and <see cref="PFSegmentsClientGetPlayerSegmentsGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFSegmentsClientGetPlayerSegmentsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_Inout_ FOnClientGetPlayerSegmentsCompleted delegate
) noexcept;

/// <summary>
/// Get all tags with a given Namespace (optional) from a player profile.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// This API will return a list of canonical tags which includes both namespace and tag's name. If namespace
/// is not provided, the result is a list of all canonical tags. TagName can be used for segmentation
/// and Namespace is limited to 128 characters.
///
/// When the asynchronous task is complete, call <see cref="PFSegmentsClientGetPlayerTagsGetResultSize"/>
/// and <see cref="PFSegmentsClientGetPlayerTagsGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFSegmentsClientGetPlayerTagsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFSegmentsGetPlayerTagsRequest* request,
	_Inout_ FOnClientGetPlayerTagsCompleted delegate
) noexcept;

/// <summary>
/// Adds a given tag to a player profile. The tag's namespace is automatically generated based on the
/// source of the tag.
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// This API will trigger a player_tag_added event and add a tag with the given TagName and PlayFabID
/// to the corresponding player profile. TagName can be used for segmentation and it is limited to 256
/// characters. Also there is a limit on the number of tags a title can have. See also ServerGetPlayerTagsAsync,
/// ServerRemovePlayerTagAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_PLAYER_TAG_COUNT_LIMIT_EXCEEDED or any of the global PlayFab Service
/// errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFSegmentsServerAddPlayerTagAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFSegmentsAddPlayerTagRequest* request,
	_Inout_ FOnServerAddPlayerTagCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves an array of player segment definitions. Results from this can be used in subsequent API
/// calls such as GetPlayersInSegment which requires a Segment ID. While segment names can change the
/// ID for that segment will not change.
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// Request has no paramaters. See also ServerGetPlayersInSegmentAsync.
///
/// When the asynchronous task is complete, call <see cref="PFSegmentsServerGetAllSegmentsGetResultSize"/>
/// and <see cref="PFSegmentsServerGetAllSegmentsGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFSegmentsServerGetAllSegmentsAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_Inout_ FOnServerGetAllSegmentsCompleted delegate
) noexcept;
#endif

/// <summary>
/// List all segments that a player currently belongs to at this moment in time.
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also ServerGetAllSegmentsAsync.
///
/// When the asynchronous task is complete, call <see cref="PFSegmentsServerGetPlayerSegmentsGetResultSize"/>
/// and <see cref="PFSegmentsServerGetPlayerSegmentsGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFSegmentsServerGetPlayerSegmentsAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFSegmentsGetPlayersSegmentsRequest* request,
	_Inout_ FOnServerGetPlayerSegmentsCompleted delegate
) noexcept;
#endif

/// <summary>
/// Get all tags with a given Namespace (optional) from a player profile.
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// This API will return a list of canonical tags which includes both namespace and tag's name. If namespace
/// is not provided, the result is a list of all canonical tags. TagName can be used for segmentation
/// and Namespace is limited to 128 characters. See also ServerAddPlayerTagAsync, ServerRemovePlayerTagAsync.
///
/// When the asynchronous task is complete, call <see cref="PFSegmentsServerGetPlayerTagsGetResultSize"/>
/// and <see cref="PFSegmentsServerGetPlayerTagsGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFSegmentsServerGetPlayerTagsAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFSegmentsGetPlayerTagsRequest* request,
	_Inout_ FOnServerGetPlayerTagsCompleted delegate
) noexcept;
#endif

/// <summary>
/// Remove a given tag from a player profile. The tag's namespace is automatically generated based on
/// the source of the tag.
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// This API will trigger a player_tag_removed event and remove a tag with the given TagName and PlayFabID
/// from the corresponding player profile. TagName can be used for segmentation and it is limited to 256
/// characters See also ServerAddPlayerTagAsync, ServerGetPlayerTagsAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be one of global PlayFab Service errors. See doc page "Handling PlayFab Errors"
/// for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFSegmentsServerRemovePlayerTagAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFSegmentsRemovePlayerTagRequest* request,
	_Inout_ FOnServerRemovePlayerTagCompleted delegate
) noexcept;
#endif

}
