// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include "CoreMinimal.h"
#include "XAsyncTaskManager.h"
#include "PFTitleDataManagementAsyncTasks.h"

THIRD_PARTY_INCLUDES_START
#include <playfab/services/PFServices.h>
THIRD_PARTY_INCLUDES_END

extern "C"
{
/// <summary>
/// Retrieves the key-value store of custom publisher settings
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
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
bool PLAYFABSERVICES_API FPFTitleDataManagementClientGetPublisherDataAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFTitleDataManagementGetPublisherDataRequest* request,
	_Inout_ FOnClientGetPublisherDataCompleted delegate
) noexcept;

/// <summary>
/// Retrieves the current server time
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// This query retrieves the current time from one of the servers in PlayFab. Please note that due to
/// clock drift between servers, there is a potential variance of up to 5 seconds.
///
/// When the asynchronous task is complete, call <see cref="PFTitleDataManagementClientGetTimeGetResult"/>
/// to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFTitleDataManagementClientGetTimeAsync(
	_In_ FPFEntityHandle EntityHandle,
	_Inout_ FOnClientGetTimeCompleted delegate
) noexcept;

/// <summary>
/// Retrieves the key-value store of custom title settings
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
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
bool PLAYFABSERVICES_API FPFTitleDataManagementClientGetTitleDataAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFTitleDataManagementGetTitleDataRequest* request,
	_Inout_ FOnClientGetTitleDataCompleted delegate
) noexcept;

/// <summary>
/// Retrieves the title news feed, as configured in the developer portal
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFTitleDataManagementClientGetTitleNewsGetResultSize"/>
/// and <see cref="PFTitleDataManagementClientGetTitleNewsGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFTitleDataManagementClientGetTitleNewsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFTitleDataManagementGetTitleNewsRequest* request,
	_Inout_ FOnClientGetTitleNewsCompleted delegate
) noexcept;

/// <summary>
/// Retrieves the key-value store of custom publisher settings
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
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
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFTitleDataManagementServerGetPublisherDataAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFTitleDataManagementGetPublisherDataRequest* request,
	_Inout_ FOnServerGetPublisherDataCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves the current server time
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// This query retrieves the current time from one of the servers in PlayFab. Please note that due to
/// clock drift between servers, there is a potential variance of up to 5 seconds.
///
/// When the asynchronous task is complete, call <see cref="PFTitleDataManagementServerGetTimeGetResult"/>
/// to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFTitleDataManagementServerGetTimeAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_Inout_ FOnServerGetTimeCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves the key-value store of custom title settings
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
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
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFTitleDataManagementServerGetTitleDataAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFTitleDataManagementGetTitleDataRequest* request,
	_Inout_ FOnServerGetTitleDataCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves the key-value store of custom internal title settings
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
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
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFTitleDataManagementServerGetTitleInternalDataAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFTitleDataManagementGetTitleDataRequest* request,
	_Inout_ FOnServerGetTitleInternalDataCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves the title news feed, as configured in the developer portal
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFTitleDataManagementServerGetTitleNewsGetResultSize"/>
/// and <see cref="PFTitleDataManagementServerGetTitleNewsGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFTitleDataManagementServerGetTitleNewsAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFTitleDataManagementGetTitleNewsRequest* request,
	_Inout_ FOnServerGetTitleNewsCompleted delegate
) noexcept;
#endif

/// <summary>
/// Updates the key-value store of custom publisher settings
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
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
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFTitleDataManagementServerSetPublisherDataAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFTitleDataManagementSetPublisherDataRequest* request,
	_Inout_ FOnServerSetPublisherDataCompleted delegate
) noexcept;
#endif

/// <summary>
/// Updates the key-value store of custom title settings
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
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
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFTitleDataManagementServerSetTitleDataAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFTitleDataManagementSetTitleDataRequest* request,
	_Inout_ FOnServerSetTitleDataCompleted delegate
) noexcept;
#endif

/// <summary>
/// Updates the key-value store of custom title settings
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
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
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFTitleDataManagementServerSetTitleInternalDataAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFTitleDataManagementSetTitleDataRequest* request,
	_Inout_ FOnServerSetTitleInternalDataCompleted delegate
) noexcept;
#endif

}
