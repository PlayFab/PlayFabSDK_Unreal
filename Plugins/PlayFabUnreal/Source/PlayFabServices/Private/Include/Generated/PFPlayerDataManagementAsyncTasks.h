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
#include "PFPlayerDataManagementUnrealTypes.h"
#include "PFPlayerDataManagementTypeConverters.h"

THIRD_PARTY_INCLUDES_START
#include <playfab/services/PFServices.h>
THIRD_PARTY_INCLUDES_END


/// <summary>
/// Deletes title-specific custom properties for a player
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Deletes custom properties for the specified player. The list of provided property names must be non-empty.
/// See also ClientGetPlayerCustomPropertyAsync, ClientListPlayerCustomPropertiesAsync, ClientUpdatePlayerCustomPropertiesAsync.
///
/// When the asynchronous task is complete, call <see cref="PFPlayerDataManagementClientDeletePlayerCustomPropertiesGetResultSize"/>
/// and <see cref="PFPlayerDataManagementClientDeletePlayerCustomPropertiesGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FClientDeletePlayerCustomPropertiesAsyncTask : public FXAsyncTask
{
public:
	FClientDeletePlayerCustomPropertiesAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFPlayerDataManagementClientDeletePlayerCustomPropertiesRequest InRequest,
	const FOnClientDeletePlayerCustomPropertiesCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFPlayerDataManagementClientDeletePlayerCustomPropertiesRequest Request;
	
	FOnClientDeletePlayerCustomPropertiesCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Retrieves a title-specific custom property value for a player.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// See also ClientDeletePlayerCustomPropertiesAsync, ClientListPlayerCustomPropertiesAsync, ClientUpdatePlayerCustomPropertiesAsync.
///
/// When the asynchronous task is complete, call <see cref="PFPlayerDataManagementClientGetPlayerCustomPropertyGetResultSize"/>
/// and <see cref="PFPlayerDataManagementClientGetPlayerCustomPropertyGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FClientGetPlayerCustomPropertyAsyncTask : public FXAsyncTask
{
public:
	FClientGetPlayerCustomPropertyAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFPlayerDataManagementClientGetPlayerCustomPropertyRequest InRequest,
	const FOnClientGetPlayerCustomPropertyCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFPlayerDataManagementClientGetPlayerCustomPropertyRequest Request;
	
	FOnClientGetPlayerCustomPropertyCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Retrieves the title-specific custom data for the user which is readable and writable by the client
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Data is stored as JSON key-value pairs. Every time the data is updated via any source, the version
/// counter is incremented. If the Version parameter is provided, then this call will only return data
/// if the current version on the system is greater than the value provided. If the Keys parameter is
/// provided, the data object returned will only contain the data specific to the indicated Keys. Otherwise,
/// the full set of custom user data will be returned. See also ClientGetUserReadOnlyDataAsync, ClientUpdateUserDataAsync.
///
/// When the asynchronous task is complete, call <see cref="PFPlayerDataManagementClientGetUserDataGetResultSize"/>
/// and <see cref="PFPlayerDataManagementClientGetUserDataGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FClientGetUserDataAsyncTask : public FXAsyncTask
{
public:
	FClientGetUserDataAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFPlayerDataManagementGetUserDataRequest InRequest,
	const FOnClientGetUserDataCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFPlayerDataManagementGetUserDataRequest Request;
	
	FOnClientGetUserDataCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Retrieves the publisher-specific custom data for the user which is readable and writable by the client
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Data is stored as JSON key-value pairs. If the Keys parameter is provided, the data object returned
/// will only contain the data specific to the indicated Keys. Otherwise, the full set of custom user
/// data will be returned. See also ClientGetUserPublisherReadOnlyDataAsync, ClientUpdateUserPublisherDataAsync.
///
/// When the asynchronous task is complete, call <see cref="PFPlayerDataManagementClientGetUserPublisherDataGetResultSize"/>
/// and <see cref="PFPlayerDataManagementClientGetUserPublisherDataGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FClientGetUserPublisherDataAsyncTask : public FXAsyncTask
{
public:
	FClientGetUserPublisherDataAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFPlayerDataManagementGetUserDataRequest InRequest,
	const FOnClientGetUserPublisherDataCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFPlayerDataManagementGetUserDataRequest Request;
	
	FOnClientGetUserPublisherDataCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Retrieves the publisher-specific custom data for the user which can only be read by the client
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Data is stored as JSON key-value pairs. If the Keys parameter is provided, the data object returned
/// will only contain the data specific to the indicated Keys. Otherwise, the full set of custom user
/// data will be returned. See also ClientGetUserPublisherDataAsync, ClientUpdateUserPublisherDataAsync.
///
/// When the asynchronous task is complete, call <see cref="PFPlayerDataManagementClientGetUserPublisherReadOnlyDataGetResultSize"/>
/// and <see cref="PFPlayerDataManagementClientGetUserPublisherReadOnlyDataGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FClientGetUserPublisherReadOnlyDataAsyncTask : public FXAsyncTask
{
public:
	FClientGetUserPublisherReadOnlyDataAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFPlayerDataManagementGetUserDataRequest InRequest,
	const FOnClientGetUserPublisherReadOnlyDataCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFPlayerDataManagementGetUserDataRequest Request;
	
	FOnClientGetUserPublisherReadOnlyDataCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Retrieves the title-specific custom data for the user which can only be read by the client
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Data is stored as JSON key-value pairs. Every time the data is updated via any source, the version
/// counter is incremented. If the Version parameter is provided, then this call will only return data
/// if the current version on the system is greater than the value provided. If the Keys parameter is
/// provided, the data object returned will only contain the data specific to the indicated Keys. Otherwise,
/// the full set of custom user data will be returned. See also ClientGetUserDataAsync, ClientUpdateUserDataAsync.
///
/// When the asynchronous task is complete, call <see cref="PFPlayerDataManagementClientGetUserReadOnlyDataGetResultSize"/>
/// and <see cref="PFPlayerDataManagementClientGetUserReadOnlyDataGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FClientGetUserReadOnlyDataAsyncTask : public FXAsyncTask
{
public:
	FClientGetUserReadOnlyDataAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFPlayerDataManagementGetUserDataRequest InRequest,
	const FOnClientGetUserReadOnlyDataCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFPlayerDataManagementGetUserDataRequest Request;
	
	FOnClientGetUserReadOnlyDataCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Retrieves title-specific custom property values for a player.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// See also ClientDeletePlayerCustomPropertiesAsync, ClientGetPlayerCustomPropertyAsync, ClientUpdatePlayerCustomPropertiesAsync.
///
/// When the asynchronous task is complete, call <see cref="PFPlayerDataManagementClientListPlayerCustomPropertiesGetResultSize"/>
/// and <see cref="PFPlayerDataManagementClientListPlayerCustomPropertiesGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FClientListPlayerCustomPropertiesAsyncTask : public FXAsyncTask
{
public:
	FClientListPlayerCustomPropertiesAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	const FOnClientListPlayerCustomPropertiesCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FOnClientListPlayerCustomPropertiesCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Updates the title-specific custom property values for a player
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Performs an additive update of the custom properties for the specified player. In updating the player's
/// custom properties, properties which already exist will have their values overwritten. No other properties
/// will be changed apart from those specified in the call. See also ClientDeletePlayerCustomPropertiesAsync,
/// ClientGetPlayerCustomPropertyAsync, ClientListPlayerCustomPropertiesAsync.
///
/// When the asynchronous task is complete, call <see cref="PFPlayerDataManagementClientUpdatePlayerCustomPropertiesGetResult"/>
/// to get the result.
/// </remarks>
class PLAYFABSERVICES_API FClientUpdatePlayerCustomPropertiesAsyncTask : public FXAsyncTask
{
public:
	FClientUpdatePlayerCustomPropertiesAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFPlayerDataManagementClientUpdatePlayerCustomPropertiesRequest InRequest,
	const FOnClientUpdatePlayerCustomPropertiesCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFPlayerDataManagementClientUpdatePlayerCustomPropertiesRequest Request;
	
	FOnClientUpdatePlayerCustomPropertiesCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Creates and updates the title-specific custom data for the user which is readable and writable by
/// the client
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// This function performs an additive update of the arbitrary strings containing the custom data for
/// the user. In updating the custom data object, keys which already exist in the object will have their
/// values overwritten, while keys with null values will be removed. New keys will be added, with the
/// given values. No other key-value pairs will be changed apart from those specified in the call. See
/// also ClientGetUserDataAsync, ClientGetUserReadOnlyDataAsync.
///
/// When the asynchronous task is complete, call <see cref="PFPlayerDataManagementClientUpdateUserDataGetResult"/>
/// to get the result.
/// </remarks>
class PLAYFABSERVICES_API FClientUpdateUserDataAsyncTask : public FXAsyncTask
{
public:
	FClientUpdateUserDataAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFPlayerDataManagementClientUpdateUserDataRequest InRequest,
	const FOnClientUpdateUserDataCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFPlayerDataManagementClientUpdateUserDataRequest Request;
	
	FOnClientUpdateUserDataCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Creates and updates the publisher-specific custom data for the user which is readable and writable
/// by the client
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// This function performs an additive update of the arbitrary strings containing the custom data for
/// the user. In updating the custom data object, keys which already exist in the object will have their
/// values overwritten, while keys with null values will be removed. New keys will be added, with the
/// given values. No other key-value pairs will be changed apart from those specified in the call. See
/// also ClientGetUserPublisherDataAsync, ClientGetUserPublisherReadOnlyDataAsync.
///
/// When the asynchronous task is complete, call <see cref="PFPlayerDataManagementClientUpdateUserPublisherDataGetResult"/>
/// to get the result.
/// </remarks>
class PLAYFABSERVICES_API FClientUpdateUserPublisherDataAsyncTask : public FXAsyncTask
{
public:
	FClientUpdateUserPublisherDataAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFPlayerDataManagementClientUpdateUserDataRequest InRequest,
	const FOnClientUpdateUserPublisherDataCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFPlayerDataManagementClientUpdateUserDataRequest Request;
	
	FOnClientUpdateUserPublisherDataCompleted Delegate;

	HRESULT HResult;
};


#if HC_PLATFORM == HC_PLATFORM_GDK

/// <summary>
/// Deletes title-specific custom properties for a player
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows.
/// Deletes custom properties for the specified player. The list of provided property names must be non-empty.
/// See also ServerGetPlayerCustomPropertyAsync, ServerListPlayerCustomPropertiesAsync, ServerUpdatePlayerCustomPropertiesAsync.
///
/// When the asynchronous task is complete, call <see cref="PFPlayerDataManagementServerDeletePlayerCustomPropertiesGetResultSize"/>
/// and <see cref="PFPlayerDataManagementServerDeletePlayerCustomPropertiesGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FServerDeletePlayerCustomPropertiesAsyncTask : public FXAsyncTask
{
public:
	FServerDeletePlayerCustomPropertiesAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFPlayerDataManagementServerDeletePlayerCustomPropertiesRequest InRequest,
	const FOnServerDeletePlayerCustomPropertiesCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFPlayerDataManagementServerDeletePlayerCustomPropertiesRequest Request;
	
	FOnServerDeletePlayerCustomPropertiesCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK

/// <summary>
/// Retrieves a title-specific custom property value for a player.
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows.
/// See also ServerDeletePlayerCustomPropertiesAsync, ServerListPlayerCustomPropertiesAsync, ServerUpdatePlayerCustomPropertiesAsync.
///
/// When the asynchronous task is complete, call <see cref="PFPlayerDataManagementServerGetPlayerCustomPropertyGetResultSize"/>
/// and <see cref="PFPlayerDataManagementServerGetPlayerCustomPropertyGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FServerGetPlayerCustomPropertyAsyncTask : public FXAsyncTask
{
public:
	FServerGetPlayerCustomPropertyAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFPlayerDataManagementServerGetPlayerCustomPropertyRequest InRequest,
	const FOnServerGetPlayerCustomPropertyCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFPlayerDataManagementServerGetPlayerCustomPropertyRequest Request;
	
	FOnServerGetPlayerCustomPropertyCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Retrieves the title-specific custom data for the user which is readable and writable by the client
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// Data is stored as JSON key-value pairs. If the Keys parameter is provided, the data object returned
/// will only contain the data specific to the indicated Keys. Otherwise, the full set of custom user
/// data will be returned. See also ServerGetUserInternalDataAsync, ServerGetUserReadOnlyDataAsync, ServerUpdateUserDataAsync,
/// ServerUpdateUserInternalDataAsync, ServerUpdateUserReadOnlyDataAsync.
///
/// When the asynchronous task is complete, call <see cref="PFPlayerDataManagementServerGetUserDataGetResultSize"/>
/// and <see cref="PFPlayerDataManagementServerGetUserDataGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FServerGetUserDataAsyncTask : public FXAsyncTask
{
public:
	FServerGetUserDataAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFPlayerDataManagementGetUserDataRequest InRequest,
	const FOnServerGetUserDataCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFPlayerDataManagementGetUserDataRequest Request;
	
	FOnServerGetUserDataCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Retrieves the title-specific custom data for the user which cannot be accessed by the client
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// Data is stored as JSON key-value pairs. If the Keys parameter is provided, the data object returned
/// will only contain the data specific to the indicated Keys. Otherwise, the full set of custom user
/// data will be returned. See also ServerGetUserDataAsync, ServerGetUserReadOnlyDataAsync, ServerUpdateUserDataAsync,
/// ServerUpdateUserInternalDataAsync, ServerUpdateUserReadOnlyDataAsync.
///
/// When the asynchronous task is complete, call <see cref="PFPlayerDataManagementServerGetUserInternalDataGetResultSize"/>
/// and <see cref="PFPlayerDataManagementServerGetUserInternalDataGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FServerGetUserInternalDataAsyncTask : public FXAsyncTask
{
public:
	FServerGetUserInternalDataAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFPlayerDataManagementGetUserDataRequest InRequest,
	const FOnServerGetUserInternalDataCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFPlayerDataManagementGetUserDataRequest Request;
	
	FOnServerGetUserInternalDataCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Retrieves the publisher-specific custom data for the user which is readable and writable by the client
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// Data is stored as JSON key-value pairs. If the Keys parameter is provided, the data object returned
/// will only contain the data specific to the indicated Keys. Otherwise, the full set of custom user
/// data will be returned. See also ServerGetUserPublisherInternalDataAsync, ServerGetUserPublisherReadOnlyDataAsync,
/// ServerUpdateUserPublisherDataAsync, ServerUpdateUserPublisherInternalDataAsync, ServerUpdateUserPublisherReadOnlyDataAsync.
///
/// When the asynchronous task is complete, call <see cref="PFPlayerDataManagementServerGetUserPublisherDataGetResultSize"/>
/// and <see cref="PFPlayerDataManagementServerGetUserPublisherDataGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FServerGetUserPublisherDataAsyncTask : public FXAsyncTask
{
public:
	FServerGetUserPublisherDataAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFPlayerDataManagementGetUserDataRequest InRequest,
	const FOnServerGetUserPublisherDataCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFPlayerDataManagementGetUserDataRequest Request;
	
	FOnServerGetUserPublisherDataCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Retrieves the publisher-specific custom data for the user which cannot be accessed by the client
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// Data is stored as JSON key-value pairs. If the Keys parameter is provided, the data object returned
/// will only contain the data specific to the indicated Keys. Otherwise, the full set of custom user
/// data will be returned. See also ServerGetUserPublisherDataAsync, ServerGetUserPublisherReadOnlyDataAsync,
/// ServerUpdateUserPublisherDataAsync, ServerUpdateUserPublisherInternalDataAsync, ServerUpdateUserPublisherReadOnlyDataAsync.
///
/// When the asynchronous task is complete, call <see cref="PFPlayerDataManagementServerGetUserPublisherInternalDataGetResultSize"/>
/// and <see cref="PFPlayerDataManagementServerGetUserPublisherInternalDataGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FServerGetUserPublisherInternalDataAsyncTask : public FXAsyncTask
{
public:
	FServerGetUserPublisherInternalDataAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFPlayerDataManagementGetUserDataRequest InRequest,
	const FOnServerGetUserPublisherInternalDataCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFPlayerDataManagementGetUserDataRequest Request;
	
	FOnServerGetUserPublisherInternalDataCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Retrieves the publisher-specific custom data for the user which can only be read by the client
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// Data is stored as JSON key-value pairs. If the Keys parameter is provided, the data object returned
/// will only contain the data specific to the indicated Keys. Otherwise, the full set of custom user
/// data will be returned. See also ServerGetUserPublisherDataAsync, ServerGetUserPublisherInternalDataAsync,
/// ServerUpdateUserPublisherDataAsync, ServerUpdateUserPublisherInternalDataAsync, ServerUpdateUserPublisherReadOnlyDataAsync.
///
/// When the asynchronous task is complete, call <see cref="PFPlayerDataManagementServerGetUserPublisherReadOnlyDataGetResultSize"/>
/// and <see cref="PFPlayerDataManagementServerGetUserPublisherReadOnlyDataGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FServerGetUserPublisherReadOnlyDataAsyncTask : public FXAsyncTask
{
public:
	FServerGetUserPublisherReadOnlyDataAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFPlayerDataManagementGetUserDataRequest InRequest,
	const FOnServerGetUserPublisherReadOnlyDataCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFPlayerDataManagementGetUserDataRequest Request;
	
	FOnServerGetUserPublisherReadOnlyDataCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Retrieves the title-specific custom data for the user which can only be read by the client
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// Data is stored as JSON key-value pairs. If the Keys parameter is provided, the data object returned
/// will only contain the data specific to the indicated Keys. Otherwise, the full set of custom user
/// data will be returned. See also ServerGetUserDataAsync, ServerGetUserInternalDataAsync, ServerUpdateUserDataAsync,
/// ServerUpdateUserInternalDataAsync, ServerUpdateUserReadOnlyDataAsync.
///
/// When the asynchronous task is complete, call <see cref="PFPlayerDataManagementServerGetUserReadOnlyDataGetResultSize"/>
/// and <see cref="PFPlayerDataManagementServerGetUserReadOnlyDataGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FServerGetUserReadOnlyDataAsyncTask : public FXAsyncTask
{
public:
	FServerGetUserReadOnlyDataAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFPlayerDataManagementGetUserDataRequest InRequest,
	const FOnServerGetUserReadOnlyDataCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFPlayerDataManagementGetUserDataRequest Request;
	
	FOnServerGetUserReadOnlyDataCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK

/// <summary>
/// Retrieves title-specific custom property values for a player.
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows.
/// See also ServerDeletePlayerCustomPropertiesAsync, ServerGetPlayerCustomPropertyAsync, ServerUpdatePlayerCustomPropertiesAsync.
///
/// When the asynchronous task is complete, call <see cref="PFPlayerDataManagementServerListPlayerCustomPropertiesGetResultSize"/>
/// and <see cref="PFPlayerDataManagementServerListPlayerCustomPropertiesGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FServerListPlayerCustomPropertiesAsyncTask : public FXAsyncTask
{
public:
	FServerListPlayerCustomPropertiesAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFPlayerDataManagementListPlayerCustomPropertiesRequest InRequest,
	const FOnServerListPlayerCustomPropertiesCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFPlayerDataManagementListPlayerCustomPropertiesRequest Request;
	
	FOnServerListPlayerCustomPropertiesCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK

/// <summary>
/// Updates the title-specific custom property values for a player
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows.
/// Performs an additive update of the custom properties for the specified player. In updating the player's
/// custom properties, properties which already exist will have their values overwritten. No other properties
/// will be changed apart from those specified in the call. See also ServerDeletePlayerCustomPropertiesAsync,
/// ServerGetPlayerCustomPropertyAsync, ServerListPlayerCustomPropertiesAsync.
///
/// When the asynchronous task is complete, call <see cref="PFPlayerDataManagementServerUpdatePlayerCustomPropertiesGetResultSize"/>
/// and <see cref="PFPlayerDataManagementServerUpdatePlayerCustomPropertiesGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FServerUpdatePlayerCustomPropertiesAsyncTask : public FXAsyncTask
{
public:
	FServerUpdatePlayerCustomPropertiesAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFPlayerDataManagementServerUpdatePlayerCustomPropertiesRequest InRequest,
	const FOnServerUpdatePlayerCustomPropertiesCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFPlayerDataManagementServerUpdatePlayerCustomPropertiesRequest Request;
	
	FOnServerUpdatePlayerCustomPropertiesCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Updates the title-specific custom data for the user which is readable and writable by the client
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// This function performs an additive update of the arbitrary JSON object containing the custom data
/// for the user. In updating the custom data object, keys which already exist in the object will have
/// their values overwritten, while keys with null values will be removed. No other key-value pairs will
/// be changed apart from those specified in the call. See also ServerGetUserDataAsync, ServerGetUserInternalDataAsync,
/// ServerGetUserReadOnlyDataAsync, ServerUpdateUserInternalDataAsync, ServerUpdateUserReadOnlyDataAsync.
///
/// When the asynchronous task is complete, call <see cref="PFPlayerDataManagementServerUpdateUserDataGetResult"/>
/// to get the result.
/// </remarks>
class PLAYFABSERVICES_API FServerUpdateUserDataAsyncTask : public FXAsyncTask
{
public:
	FServerUpdateUserDataAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFPlayerDataManagementServerUpdateUserDataRequest InRequest,
	const FOnServerUpdateUserDataCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFPlayerDataManagementServerUpdateUserDataRequest Request;
	
	FOnServerUpdateUserDataCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Updates the title-specific custom data for the user which cannot be accessed by the client
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// This function performs an additive update of the arbitrary JSON object containing the custom data
/// for the user. In updating the custom data object, keys which already exist in the object will have
/// their values overwritten, keys with null values will be removed. No other key-value pairs will be
/// changed apart from those specified in the call. See also ServerGetUserDataAsync, ServerGetUserInternalDataAsync,
/// ServerGetUserReadOnlyDataAsync, ServerUpdateUserDataAsync, ServerUpdateUserReadOnlyDataAsync.
///
/// When the asynchronous task is complete, call <see cref="PFPlayerDataManagementServerUpdateUserInternalDataGetResult"/>
/// to get the result.
/// </remarks>
class PLAYFABSERVICES_API FServerUpdateUserInternalDataAsyncTask : public FXAsyncTask
{
public:
	FServerUpdateUserInternalDataAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFPlayerDataManagementUpdateUserInternalDataRequest InRequest,
	const FOnServerUpdateUserInternalDataCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFPlayerDataManagementUpdateUserInternalDataRequest Request;
	
	FOnServerUpdateUserInternalDataCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Updates the publisher-specific custom data for the user which is readable and writable by the client
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// This function performs an additive update of the arbitrary JSON object containing the custom data
/// for the user. In updating the custom data object, keys which already exist in the object will have
/// their values overwritten, while keys with null values will be removed. No other key-value pairs will
/// be changed apart from those specified in the call. See also ServerGetUserPublisherDataAsync, ServerGetUserPublisherInternalDataAsync,
/// ServerGetUserPublisherReadOnlyDataAsync, ServerUpdateUserPublisherInternalDataAsync, ServerUpdateUserPublisherReadOnlyDataAsync.
///
/// When the asynchronous task is complete, call <see cref="PFPlayerDataManagementServerUpdateUserPublisherDataGetResult"/>
/// to get the result.
/// </remarks>
class PLAYFABSERVICES_API FServerUpdateUserPublisherDataAsyncTask : public FXAsyncTask
{
public:
	FServerUpdateUserPublisherDataAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFPlayerDataManagementServerUpdateUserDataRequest InRequest,
	const FOnServerUpdateUserPublisherDataCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFPlayerDataManagementServerUpdateUserDataRequest Request;
	
	FOnServerUpdateUserPublisherDataCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Updates the publisher-specific custom data for the user which cannot be accessed by the client
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// This function performs an additive update of the arbitrary JSON object containing the custom data
/// for the user. In updating the custom data object, keys which already exist in the object will have
/// their values overwritten, keys with null values will be removed. No other key-value pairs will be
/// changed apart from those specified in the call. See also ServerGetUserPublisherDataAsync, ServerGetUserPublisherInternalDataAsync,
/// ServerGetUserPublisherReadOnlyDataAsync, ServerUpdateUserPublisherDataAsync, ServerUpdateUserPublisherReadOnlyDataAsync.
///
/// When the asynchronous task is complete, call <see cref="PFPlayerDataManagementServerUpdateUserPublisherInternalDataGetResult"/>
/// to get the result.
/// </remarks>
class PLAYFABSERVICES_API FServerUpdateUserPublisherInternalDataAsyncTask : public FXAsyncTask
{
public:
	FServerUpdateUserPublisherInternalDataAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFPlayerDataManagementUpdateUserInternalDataRequest InRequest,
	const FOnServerUpdateUserPublisherInternalDataCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFPlayerDataManagementUpdateUserInternalDataRequest Request;
	
	FOnServerUpdateUserPublisherInternalDataCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Updates the publisher-specific custom data for the user which can only be read by the client
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// This function performs an additive update of the arbitrary JSON object containing the custom data
/// for the user. In updating the custom data object, keys which already exist in the object will have
/// their values overwritten, keys with null values will be removed. No other key-value pairs will be
/// changed apart from those specified in the call. See also ServerGetUserPublisherDataAsync, ServerGetUserPublisherInternalDataAsync,
/// ServerGetUserPublisherReadOnlyDataAsync, ServerUpdateUserPublisherDataAsync, ServerUpdateUserPublisherInternalDataAsync.
///
/// When the asynchronous task is complete, call <see cref="PFPlayerDataManagementServerUpdateUserPublisherReadOnlyDataGetResult"/>
/// to get the result.
/// </remarks>
class PLAYFABSERVICES_API FServerUpdateUserPublisherReadOnlyDataAsyncTask : public FXAsyncTask
{
public:
	FServerUpdateUserPublisherReadOnlyDataAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFPlayerDataManagementServerUpdateUserDataRequest InRequest,
	const FOnServerUpdateUserPublisherReadOnlyDataCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFPlayerDataManagementServerUpdateUserDataRequest Request;
	
	FOnServerUpdateUserPublisherReadOnlyDataCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Updates the title-specific custom data for the user which can only be read by the client
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// This function performs an additive update of the arbitrary JSON object containing the custom data
/// for the user. In updating the custom data object, keys which already exist in the object will have
/// their values overwritten, keys with null values will be removed. No other key-value pairs will be
/// changed apart from those specified in the call. See also ServerGetUserDataAsync, ServerGetUserInternalDataAsync,
/// ServerGetUserReadOnlyDataAsync, ServerUpdateUserDataAsync, ServerUpdateUserInternalDataAsync.
///
/// When the asynchronous task is complete, call <see cref="PFPlayerDataManagementServerUpdateUserReadOnlyDataGetResult"/>
/// to get the result.
/// </remarks>
class PLAYFABSERVICES_API FServerUpdateUserReadOnlyDataAsyncTask : public FXAsyncTask
{
public:
	FServerUpdateUserReadOnlyDataAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFPlayerDataManagementServerUpdateUserDataRequest InRequest,
	const FOnServerUpdateUserReadOnlyDataCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFPlayerDataManagementServerUpdateUserDataRequest Request;
	
	FOnServerUpdateUserReadOnlyDataCompleted Delegate;

	HRESULT HResult;
};

#endif
