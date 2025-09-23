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
#include "PFTitleDataManagementUnrealTypes.h"
#include "PFTitleDataManagementTypeConverters.h"

THIRD_PARTY_INCLUDES_START
#include <playfab/services/PFServices.h>
THIRD_PARTY_INCLUDES_END


/// <summary>
/// Retrieves the key-value store of custom publisher settings
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// This API is designed to return publisher-specific values which can be read, but not written to, by
/// the client. This data is shared across all titles assigned to a particular publisher, and can be used
/// for cross-game coordination. Only titles assigned to a publisher can use this API. For more information
/// email helloplayfab@microsoft.com. Note that there may up to a minute delay in between updating title
/// data and this API call returning the newest value.
///
/// When the asynchronous task is complete, call <see cref="PFTitleDataManagementClientGetPublisherDataGetResultSize"/>
/// and <see cref="PFTitleDataManagementClientGetPublisherDataGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FClientGetPublisherDataAsyncTask : public FXAsyncTask
{
public:
	FClientGetPublisherDataAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFTitleDataManagementGetPublisherDataRequest InRequest,
	const FOnClientGetPublisherDataCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFTitleDataManagementGetPublisherDataRequest Request;
	
	FOnClientGetPublisherDataCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Retrieves the current server time
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// This query retrieves the current time from one of the servers in PlayFab. Please note that due to
/// clock drift between servers, there is a potential variance of up to 5 seconds.
///
/// When the asynchronous task is complete, call <see cref="PFTitleDataManagementClientGetTimeGetResult"/>
/// to get the result.
/// </remarks>
class PLAYFABSERVICES_API FClientGetTimeAsyncTask : public FXAsyncTask
{
public:
	FClientGetTimeAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	const FOnClientGetTimeCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FOnClientGetTimeCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Retrieves the key-value store of custom title settings
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// This API is designed to return title specific values which can be read, but not written to, by the
/// client. For example, a developer could choose to store values which modify the user experience, such
/// as enemy spawn rates, weapon strengths, movement speeds, etc. This allows a developer to update the
/// title without the need to create, test, and ship a new build. If the player belongs to an experiment
/// variant that uses title data overrides, the overrides are applied automatically and returned with
/// the title data. Note that there may up to a minute delay in between updating title data and this API
/// call returning the newest value.
///
/// When the asynchronous task is complete, call <see cref="PFTitleDataManagementClientGetTitleDataGetResultSize"/>
/// and <see cref="PFTitleDataManagementClientGetTitleDataGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FClientGetTitleDataAsyncTask : public FXAsyncTask
{
public:
	FClientGetTitleDataAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFTitleDataManagementGetTitleDataRequest InRequest,
	const FOnClientGetTitleDataCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFTitleDataManagementGetTitleDataRequest Request;
	
	FOnClientGetTitleDataCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Retrieves the title news feed, as configured in the developer portal
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFTitleDataManagementClientGetTitleNewsGetResultSize"/>
/// and <see cref="PFTitleDataManagementClientGetTitleNewsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FClientGetTitleNewsAsyncTask : public FXAsyncTask
{
public:
	FClientGetTitleNewsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFTitleDataManagementGetTitleNewsRequest InRequest,
	const FOnClientGetTitleNewsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFTitleDataManagementGetTitleNewsRequest Request;
	
	FOnClientGetTitleNewsCompleted Delegate;

	HRESULT HResult;
};


#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Retrieves the key-value store of custom publisher settings
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// This API is designed to return publisher-specific values which can be read, but not written to, by
/// the client. This data is shared across all titles assigned to a particular publisher, and can be used
/// for cross-game coordination. Only titles assigned to a publisher can use this API. For more information
/// email helloplayfab@microsoft.com. Note that there may up to a minute delay in between updating title
/// data and this API call returning the newest value. See also ServerSetPublisherDataAsync.
///
/// When the asynchronous task is complete, call <see cref="PFTitleDataManagementServerGetPublisherDataGetResultSize"/>
/// and <see cref="PFTitleDataManagementServerGetPublisherDataGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FServerGetPublisherDataAsyncTask : public FXAsyncTask
{
public:
	FServerGetPublisherDataAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFTitleDataManagementGetPublisherDataRequest InRequest,
	const FOnServerGetPublisherDataCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFTitleDataManagementGetPublisherDataRequest Request;
	
	FOnServerGetPublisherDataCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Retrieves the current server time
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// This query retrieves the current time from one of the servers in PlayFab. Please note that due to
/// clock drift between servers, there is a potential variance of up to 5 seconds.
///
/// When the asynchronous task is complete, call <see cref="PFTitleDataManagementServerGetTimeGetResult"/>
/// to get the result.
/// </remarks>
class PLAYFABSERVICES_API FServerGetTimeAsyncTask : public FXAsyncTask
{
public:
	FServerGetTimeAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	const FOnServerGetTimeCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FOnServerGetTimeCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Retrieves the key-value store of custom title settings
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// This API is designed to return title specific values which can be read, but not written to, by the
/// client. For example, a developer could choose to store values which modify the user experience, such
/// as enemy spawn rates, weapon strengths, movement speeds, etc. This allows a developer to update the
/// title without the need to create, test, and ship a new build. If an override label is specified in
/// the request, the overrides are applied automatically and returned with the title data. Note that there
/// may up to a minute delay in between updating title data and this API call returning the newest value.
/// See also ServerSetTitleDataAsync.
///
/// When the asynchronous task is complete, call <see cref="PFTitleDataManagementServerGetTitleDataGetResultSize"/>
/// and <see cref="PFTitleDataManagementServerGetTitleDataGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FServerGetTitleDataAsyncTask : public FXAsyncTask
{
public:
	FServerGetTitleDataAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFTitleDataManagementGetTitleDataRequest InRequest,
	const FOnServerGetTitleDataCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFTitleDataManagementGetTitleDataRequest Request;
	
	FOnServerGetTitleDataCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Retrieves the key-value store of custom internal title settings
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// This API is designed to return title specific values which are accessible only to the server. This
/// can be used to tweak settings on game servers and Cloud Scripts without needed to update and re-deploy
/// them. Note that there may up to a minute delay in between updating title data and this API call returning
/// the newest value. See also ServerSetTitleInternalDataAsync.
///
/// When the asynchronous task is complete, call <see cref="PFTitleDataManagementServerGetTitleInternalDataGetResultSize"/>
/// and <see cref="PFTitleDataManagementServerGetTitleInternalDataGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FServerGetTitleInternalDataAsyncTask : public FXAsyncTask
{
public:
	FServerGetTitleInternalDataAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFTitleDataManagementGetTitleDataRequest InRequest,
	const FOnServerGetTitleInternalDataCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFTitleDataManagementGetTitleDataRequest Request;
	
	FOnServerGetTitleInternalDataCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Retrieves the title news feed, as configured in the developer portal
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFTitleDataManagementServerGetTitleNewsGetResultSize"/>
/// and <see cref="PFTitleDataManagementServerGetTitleNewsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FServerGetTitleNewsAsyncTask : public FXAsyncTask
{
public:
	FServerGetTitleNewsAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFTitleDataManagementGetTitleNewsRequest InRequest,
	const FOnServerGetTitleNewsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFTitleDataManagementGetTitleNewsRequest Request;
	
	FOnServerGetTitleNewsCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Updates the key-value store of custom publisher settings
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// This API is designed to store publisher-specific values which can be read, but not written to, by
/// the client. This data is shared across all titles assigned to a particular publisher, and can be used
/// for cross-game coordination. Only titles assigned to a publisher can use this API. This operation
/// is additive. If a Key does not exist in the current dataset, it will be added with the specified Value.
/// If it already exists, the Value for that key will be overwritten with the new Value. For more information
/// email helloplayfab@microsoft.com See also ServerGetPublisherDataAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_PUBLISHER_NOT_SET or any of the global PlayFab Service errors. See doc
/// page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FServerSetPublisherDataAsyncTask : public FXAsyncTask
{
public:
	FServerSetPublisherDataAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFTitleDataManagementSetPublisherDataRequest InRequest,
	const FOnServerSetPublisherDataCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFTitleDataManagementSetPublisherDataRequest Request;
	
	FOnServerSetPublisherDataCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Updates the key-value store of custom title settings
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// This API is designed to store title specific values which can be read, but not written to, by the
/// client. For example, a developer could choose to store values which modify the user experience, such
/// as enemy spawn rates, weapon strengths, movement speeds, etc. This allows a developer to update the
/// title without the need to create, test, and ship a new build. This operation is additive. If a Key
/// does not exist in the current dataset, it will be added with the specified Value. If it already exists,
/// the Value for that key will be overwritten with the new Value. See also ServerGetTitleDataAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_DATA_LENGTH_EXCEEDED, E_PF_TOO_MANY_KEYS or any of the global PlayFab
/// Service errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FServerSetTitleDataAsyncTask : public FXAsyncTask
{
public:
	FServerSetTitleDataAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFTitleDataManagementSetTitleDataRequest InRequest,
	const FOnServerSetTitleDataCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFTitleDataManagementSetTitleDataRequest Request;
	
	FOnServerSetTitleDataCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Updates the key-value store of custom title settings
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// This API is designed to store title specific values which are accessible only to the server. This
/// can be used to tweak settings on game servers and Cloud Scripts without needed to update and re-deploy
/// them. This operation is additive. If a Key does not exist in the current dataset, it will be added
/// with the specified Value. If it already exists, the Value for that key will be overwritten with the
/// new Value. See also ServerGetTitleInternalDataAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_DATA_LENGTH_EXCEEDED, E_PF_TOO_MANY_KEYS or any of the global PlayFab
/// Service errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FServerSetTitleInternalDataAsyncTask : public FXAsyncTask
{
public:
	FServerSetTitleInternalDataAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFTitleDataManagementSetTitleDataRequest InRequest,
	const FOnServerSetTitleInternalDataCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFTitleDataManagementSetTitleDataRequest Request;
	
	FOnServerSetTitleInternalDataCompleted Delegate;

	HRESULT HResult;
};

#endif
