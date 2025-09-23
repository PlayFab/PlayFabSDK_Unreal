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
#include "PFProfilesUnrealTypes.h"
#include "PFProfilesTypeConverters.h"

THIRD_PARTY_INCLUDES_START
#include <playfab/services/PFServices.h>
THIRD_PARTY_INCLUDES_END


/// <summary>
/// Retrieves the entity's profile.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Given an entity type and entity identifier will retrieve the profile from the entity store. If the
/// profile being retrieved is the caller's, then the read operation is consistent, if not it is an inconsistent
/// read. An inconsistent read means that we do not guarantee all committed writes have occurred before
/// reading the profile, allowing for a stale read. If consistency is important the Version Number on
/// the result can be used to compare which version of the profile any reader has.
///
/// When the asynchronous task is complete, call <see cref="PFProfilesGetProfileGetResultSize"/> and
/// <see cref="PFProfilesGetProfileGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FGetProfileAsyncTask : public FXAsyncTask
{
public:
	FGetProfileAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFProfilesGetEntityProfileRequest InRequest,
	const FOnGetProfileCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFProfilesGetEntityProfileRequest Request;
	
	FOnGetProfileCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Retrieves the entity's profile.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Given a set of entity types and entity identifiers will retrieve all readable profiles properties
/// for the caller. Profiles that the caller is not allowed to read will silently not be included in the
/// results.
///
/// When the asynchronous task is complete, call <see cref="PFProfilesGetProfilesGetResultSize"/> and
/// <see cref="PFProfilesGetProfilesGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FGetProfilesAsyncTask : public FXAsyncTask
{
public:
	FGetProfilesAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFProfilesGetEntityProfilesRequest InRequest,
	const FOnGetProfilesCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFProfilesGetEntityProfilesRequest Request;
	
	FOnGetProfilesCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Retrieves the title player accounts associated with the given master player account.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Given a master player account id (PlayFab ID), returns all title player accounts associated with
/// it.
///
/// When the asynchronous task is complete, call <see cref="PFProfilesGetTitlePlayersFromMasterPlayerAccountIdsGetResultSize"/>
/// and <see cref="PFProfilesGetTitlePlayersFromMasterPlayerAccountIdsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FGetTitlePlayersFromMasterPlayerAccountIdsAsyncTask : public FXAsyncTask
{
public:
	FGetTitlePlayersFromMasterPlayerAccountIdsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFProfilesGetTitlePlayersFromMasterPlayerAccountIdsRequest InRequest,
	const FOnGetTitlePlayersFromMasterPlayerAccountIdsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFProfilesGetTitlePlayersFromMasterPlayerAccountIdsRequest Request;
	
	FOnGetTitlePlayersFromMasterPlayerAccountIdsCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Updates the entity's language. The precedence hierarchy for communication to the player is Title
/// Player Account language, Master Player Account language, and then title default language if the first
/// two aren't set or supported.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Given an entity profile, will update its language to the one passed in if the profile's version is
/// equal to the one passed in.
///
/// When the asynchronous task is complete, call <see cref="PFProfilesSetProfileLanguageGetResultSize"/>
/// and <see cref="PFProfilesSetProfileLanguageGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FSetProfileLanguageAsyncTask : public FXAsyncTask
{
public:
	FSetProfileLanguageAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFProfilesSetProfileLanguageRequest InRequest,
	const FOnSetProfileLanguageCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFProfilesSetProfileLanguageRequest Request;
	
	FOnSetProfileLanguageCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Sets the profiles access policy
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// This will set the access policy statements on the given entity profile. This is not additive, any
/// existing statements will be replaced with the statements in this request. See also ProfileGetProfileAsync.
///
/// When the asynchronous task is complete, call <see cref="PFProfilesSetProfilePolicyGetResultSize"/>
/// and <see cref="PFProfilesSetProfilePolicyGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FSetProfilePolicyAsyncTask : public FXAsyncTask
{
public:
	FSetProfilePolicyAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFProfilesSetEntityProfilePolicyRequest InRequest,
	const FOnSetProfilePolicyCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFProfilesSetEntityProfilePolicyRequest Request;
	
	FOnSetProfilePolicyCompleted Delegate;

	HRESULT HResult;
};

