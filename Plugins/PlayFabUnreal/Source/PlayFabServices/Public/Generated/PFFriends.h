// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include "CoreMinimal.h"
#include "XAsyncTaskManager.h"
#include "PFFriendsAsyncTasks.h"

THIRD_PARTY_INCLUDES_START
#include <playfab/services/PFServices.h>
THIRD_PARTY_INCLUDES_END

extern "C"
{
/// <summary>
/// Adds the PlayFab user, based upon a match against a supplied unique identifier, to the friend list
/// of the local user. At least one of FriendPlayFabId,FriendUsername,FriendEmail, or FriendTitleDisplayName
/// should be initialized.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// See also ClientGetFriendsListAsync, ClientSetFriendTagsAsync.
///
/// When the asynchronous task is complete, call <see cref="PFFriendsClientAddFriendGetResult"/> to get
/// the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFFriendsClientAddFriendAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFFriendsClientAddFriendRequest* request,
	_Inout_ FOnClientAddFriendCompleted delegate
) noexcept;

/// <summary>
/// Retrieves the current friend list for the local user, constrained to users who have PlayFab accounts.
/// Friends from linked accounts (Facebook, Steam) are also included. You may optionally exclude some
/// linked services' friends.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// See also ClientAddFriendAsync, ClientGetPlayerProfileAsync, ClientRemoveFriendAsync.
///
/// When the asynchronous task is complete, call <see cref="PFFriendsClientGetFriendsListGetResultSize"/>
/// and <see cref="PFFriendsClientGetFriendsListGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFFriendsClientGetFriendsListAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFFriendsClientGetFriendsListRequest* request,
	_Inout_ FOnClientGetFriendsListCompleted delegate
) noexcept;

/// <summary>
/// Removes a specified user from the friend list of the local user
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// See also ClientAddFriendAsync, ClientSetFriendTagsAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be one of global PlayFab Service errors. See doc page "Handling PlayFab Errors"
/// for more details on error handling.
/// </remarks>
bool PLAYFABSERVICES_API FPFFriendsClientRemoveFriendAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFFriendsClientRemoveFriendRequest* request,
	_Inout_ FOnClientRemoveFriendCompleted delegate
) noexcept;

/// <summary>
/// Updates the tag list for a specified user in the friend list of the local user
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// This operation is not additive. It will completely replace the tag list for the specified user. Please
/// note that only users in the PlayFab friends list can be assigned tags. Attempting to set a tag on
/// a friend only included in the friends list from a social site integration (such as Facebook or Steam)
/// will return the AccountNotFound error. See also ClientAddFriendAsync, ClientRemoveFriendAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be one of global PlayFab Service errors. See doc page "Handling PlayFab Errors"
/// for more details on error handling.
/// </remarks>
bool PLAYFABSERVICES_API FPFFriendsClientSetFriendTagsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFFriendsClientSetFriendTagsRequest* request,
	_Inout_ FOnClientSetFriendTagsCompleted delegate
) noexcept;

/// <summary>
/// Adds the Friend user to the friendlist of the user with PlayFabId. At least one of FriendPlayFabId,FriendUsername,FriendEmail,
/// or FriendTitleDisplayName should be initialized.
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also ServerGetFriendsListAsync, ServerRemoveFriendAsync, ServerSetFriendTagsAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_USERS_ALREADY_FRIENDS or any of the global PlayFab Service errors. See
/// doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFFriendsServerAddFriendAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFFriendsServerAddFriendRequest* request,
	_Inout_ FOnServerAddFriendCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves the current friends for the user with PlayFabId, constrained to users who have PlayFab
/// accounts. Friends from linked accounts (Facebook, Steam) are also included. You may optionally exclude
/// some linked services' friends.
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also ServerAddFriendAsync, ServerGetPlayerProfileAsync, ServerRemoveFriendAsync, ServerSetFriendTagsAsync.
///
/// When the asynchronous task is complete, call <see cref="PFFriendsServerGetFriendsListGetResultSize"/>
/// and <see cref="PFFriendsServerGetFriendsListGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFFriendsServerGetFriendsListAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFFriendsServerGetFriendsListRequest* request,
	_Inout_ FOnServerGetFriendsListCompleted delegate
) noexcept;
#endif

/// <summary>
/// Removes the specified friend from the the user's friend list
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also ServerAddFriendAsync, ServerSetFriendTagsAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_FOUND or any of the global PlayFab Service errors. See doc
/// page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFFriendsServerRemoveFriendAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFFriendsServerRemoveFriendRequest* request,
	_Inout_ FOnServerRemoveFriendCompleted delegate
) noexcept;
#endif

/// <summary>
/// Updates the tag list for a specified user in the friend list of another user
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// This operation is not additive. It will completely replace the tag list for the specified user. Please
/// note that only users in the PlayFab friends list can be assigned tags. Attempting to set a tag on
/// a friend only included in the friends list from a social site integration (such as Facebook or Steam)
/// will return the AccountNotFound error. See also ServerAddFriendAsync, ServerGetFriendsListAsync, ServerRemoveFriendAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be one of global PlayFab Service errors. See doc page "Handling PlayFab Errors"
/// for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFFriendsServerSetFriendTagsAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFFriendsServerSetFriendTagsRequest* request,
	_Inout_ FOnServerSetFriendTagsCompleted delegate
) noexcept;
#endif

}
