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
#include "PFFriendsUnrealTypes.h"
#include "PFFriendsTypeConverters.h"

THIRD_PARTY_INCLUDES_START
#include <playfab/services/PFServices.h>
THIRD_PARTY_INCLUDES_END


/// <summary>
/// Adds the PlayFab user, based upon a match against a supplied unique identifier, to the friend list
/// of the local user. At least one of FriendPlayFabId,FriendUsername,FriendEmail, or FriendTitleDisplayName
/// should be initialized.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// See also ClientGetFriendsListAsync, ClientSetFriendTagsAsync.
///
/// When the asynchronous task is complete, call <see cref="PFFriendsClientAddFriendGetResult"/> to get
/// the result.
/// </remarks>
class PLAYFABSERVICES_API FClientAddFriendAsyncTask : public FXAsyncTask
{
public:
	FClientAddFriendAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFFriendsClientAddFriendRequest InRequest,
	const FOnClientAddFriendCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFFriendsClientAddFriendRequest Request;
	
	FOnClientAddFriendCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Retrieves the current friend list for the local user, constrained to users who have PlayFab accounts.
/// Friends from linked accounts (Facebook, Steam) are also included. You may optionally exclude some
/// linked services' friends.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// See also ClientAddFriendAsync, ClientGetPlayerProfileAsync, ClientRemoveFriendAsync.
///
/// When the asynchronous task is complete, call <see cref="PFFriendsClientGetFriendsListGetResultSize"/>
/// and <see cref="PFFriendsClientGetFriendsListGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FClientGetFriendsListAsyncTask : public FXAsyncTask
{
public:
	FClientGetFriendsListAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFFriendsClientGetFriendsListRequest InRequest,
	const FOnClientGetFriendsListCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFFriendsClientGetFriendsListRequest Request;
	
	FOnClientGetFriendsListCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Removes a specified user from the friend list of the local user
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// See also ClientAddFriendAsync, ClientSetFriendTagsAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be one of global PlayFab Service errors. See doc page "Handling PlayFab Errors"
/// for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FClientRemoveFriendAsyncTask : public FXAsyncTask
{
public:
	FClientRemoveFriendAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFFriendsClientRemoveFriendRequest InRequest,
	const FOnClientRemoveFriendCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFFriendsClientRemoveFriendRequest Request;
	
	FOnClientRemoveFriendCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Updates the tag list for a specified user in the friend list of the local user
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FClientSetFriendTagsAsyncTask : public FXAsyncTask
{
public:
	FClientSetFriendTagsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFFriendsClientSetFriendTagsRequest InRequest,
	const FOnClientSetFriendTagsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFFriendsClientSetFriendTagsRequest Request;
	
	FOnClientSetFriendTagsCompleted Delegate;

	HRESULT HResult;
};


#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Adds the Friend user to the friendlist of the user with PlayFabId. At least one of FriendPlayFabId,FriendUsername,FriendEmail,
/// or FriendTitleDisplayName should be initialized.
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also ServerGetFriendsListAsync, ServerRemoveFriendAsync, ServerSetFriendTagsAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_USERS_ALREADY_FRIENDS or any of the global PlayFab Service errors. See
/// doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FServerAddFriendAsyncTask : public FXAsyncTask
{
public:
	FServerAddFriendAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFFriendsServerAddFriendRequest InRequest,
	const FOnServerAddFriendCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFFriendsServerAddFriendRequest Request;
	
	FOnServerAddFriendCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Retrieves the current friends for the user with PlayFabId, constrained to users who have PlayFab
/// accounts. Friends from linked accounts (Facebook, Steam) are also included. You may optionally exclude
/// some linked services' friends.
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also ServerAddFriendAsync, ServerGetPlayerProfileAsync, ServerRemoveFriendAsync, ServerSetFriendTagsAsync.
///
/// When the asynchronous task is complete, call <see cref="PFFriendsServerGetFriendsListGetResultSize"/>
/// and <see cref="PFFriendsServerGetFriendsListGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FServerGetFriendsListAsyncTask : public FXAsyncTask
{
public:
	FServerGetFriendsListAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFFriendsServerGetFriendsListRequest InRequest,
	const FOnServerGetFriendsListCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFFriendsServerGetFriendsListRequest Request;
	
	FOnServerGetFriendsListCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Removes the specified friend from the the user's friend list
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also ServerAddFriendAsync, ServerSetFriendTagsAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_FOUND or any of the global PlayFab Service errors. See doc
/// page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FServerRemoveFriendAsyncTask : public FXAsyncTask
{
public:
	FServerRemoveFriendAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFFriendsServerRemoveFriendRequest InRequest,
	const FOnServerRemoveFriendCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFFriendsServerRemoveFriendRequest Request;
	
	FOnServerRemoveFriendCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Updates the tag list for a specified user in the friend list of another user
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FServerSetFriendTagsAsyncTask : public FXAsyncTask
{
public:
	FServerSetFriendTagsAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFFriendsServerSetFriendTagsRequest InRequest,
	const FOnServerSetFriendTagsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFFriendsServerSetFriendTagsRequest Request;
	
	FOnServerSetFriendTagsCompleted Delegate;

	HRESULT HResult;
};

#endif
