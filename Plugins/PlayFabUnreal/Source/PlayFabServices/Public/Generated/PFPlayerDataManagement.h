// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include "CoreMinimal.h"
#include "XAsyncTaskManager.h"
#include "PFPlayerDataManagementAsyncTasks.h"

THIRD_PARTY_INCLUDES_START
#include <playfab/services/PFServices.h>
THIRD_PARTY_INCLUDES_END

extern "C"
{
/// <summary>
/// Deletes title-specific custom properties for a player
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Deletes custom properties for the specified player. The list of provided property names must be non-empty.
/// See also ClientGetPlayerCustomPropertyAsync, ClientListPlayerCustomPropertiesAsync, ClientUpdatePlayerCustomPropertiesAsync.
///
/// When the asynchronous task is complete, call <see cref="PFPlayerDataManagementClientDeletePlayerCustomPropertiesGetResultSize"/>
/// and <see cref="PFPlayerDataManagementClientDeletePlayerCustomPropertiesGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFPlayerDataManagementClientDeletePlayerCustomPropertiesAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFPlayerDataManagementClientDeletePlayerCustomPropertiesRequest* request,
	_Inout_ FOnClientDeletePlayerCustomPropertiesCompleted delegate
) noexcept;

/// <summary>
/// Retrieves a title-specific custom property value for a player.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// See also ClientDeletePlayerCustomPropertiesAsync, ClientListPlayerCustomPropertiesAsync, ClientUpdatePlayerCustomPropertiesAsync.
///
/// When the asynchronous task is complete, call <see cref="PFPlayerDataManagementClientGetPlayerCustomPropertyGetResultSize"/>
/// and <see cref="PFPlayerDataManagementClientGetPlayerCustomPropertyGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFPlayerDataManagementClientGetPlayerCustomPropertyAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFPlayerDataManagementClientGetPlayerCustomPropertyRequest* request,
	_Inout_ FOnClientGetPlayerCustomPropertyCompleted delegate
) noexcept;

/// <summary>
/// Retrieves the title-specific custom data for the user which is readable and writable by the client
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
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
bool PLAYFABSERVICES_API FPFPlayerDataManagementClientGetUserDataAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFPlayerDataManagementGetUserDataRequest* request,
	_Inout_ FOnClientGetUserDataCompleted delegate
) noexcept;

/// <summary>
/// Retrieves the publisher-specific custom data for the user which is readable and writable by the client
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
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
bool PLAYFABSERVICES_API FPFPlayerDataManagementClientGetUserPublisherDataAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFPlayerDataManagementGetUserDataRequest* request,
	_Inout_ FOnClientGetUserPublisherDataCompleted delegate
) noexcept;

/// <summary>
/// Retrieves the publisher-specific custom data for the user which can only be read by the client
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
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
bool PLAYFABSERVICES_API FPFPlayerDataManagementClientGetUserPublisherReadOnlyDataAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFPlayerDataManagementGetUserDataRequest* request,
	_Inout_ FOnClientGetUserPublisherReadOnlyDataCompleted delegate
) noexcept;

/// <summary>
/// Retrieves the title-specific custom data for the user which can only be read by the client
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
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
bool PLAYFABSERVICES_API FPFPlayerDataManagementClientGetUserReadOnlyDataAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFPlayerDataManagementGetUserDataRequest* request,
	_Inout_ FOnClientGetUserReadOnlyDataCompleted delegate
) noexcept;

/// <summary>
/// Retrieves title-specific custom property values for a player.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// See also ClientDeletePlayerCustomPropertiesAsync, ClientGetPlayerCustomPropertyAsync, ClientUpdatePlayerCustomPropertiesAsync.
///
/// When the asynchronous task is complete, call <see cref="PFPlayerDataManagementClientListPlayerCustomPropertiesGetResultSize"/>
/// and <see cref="PFPlayerDataManagementClientListPlayerCustomPropertiesGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFPlayerDataManagementClientListPlayerCustomPropertiesAsync(
	_In_ FPFEntityHandle EntityHandle,
	_Inout_ FOnClientListPlayerCustomPropertiesCompleted delegate
) noexcept;

/// <summary>
/// Updates the title-specific custom property values for a player
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
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
bool PLAYFABSERVICES_API FPFPlayerDataManagementClientUpdatePlayerCustomPropertiesAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFPlayerDataManagementClientUpdatePlayerCustomPropertiesRequest* request,
	_Inout_ FOnClientUpdatePlayerCustomPropertiesCompleted delegate
) noexcept;

/// <summary>
/// Creates and updates the title-specific custom data for the user which is readable and writable by
/// the client
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
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
bool PLAYFABSERVICES_API FPFPlayerDataManagementClientUpdateUserDataAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFPlayerDataManagementClientUpdateUserDataRequest* request,
	_Inout_ FOnClientUpdateUserDataCompleted delegate
) noexcept;

/// <summary>
/// Creates and updates the publisher-specific custom data for the user which is readable and writable
/// by the client
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
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
bool PLAYFABSERVICES_API FPFPlayerDataManagementClientUpdateUserPublisherDataAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFPlayerDataManagementClientUpdateUserDataRequest* request,
	_Inout_ FOnClientUpdateUserPublisherDataCompleted delegate
) noexcept;

/// <summary>
/// Deletes title-specific custom properties for a player
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows.
/// Deletes custom properties for the specified player. The list of provided property names must be non-empty.
/// See also ServerGetPlayerCustomPropertyAsync, ServerListPlayerCustomPropertiesAsync, ServerUpdatePlayerCustomPropertiesAsync.
///
/// When the asynchronous task is complete, call <see cref="PFPlayerDataManagementServerDeletePlayerCustomPropertiesGetResultSize"/>
/// and <see cref="PFPlayerDataManagementServerDeletePlayerCustomPropertiesGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFPlayerDataManagementServerDeletePlayerCustomPropertiesAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFPlayerDataManagementServerDeletePlayerCustomPropertiesRequest* request,
	_Inout_ FOnServerDeletePlayerCustomPropertiesCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves a title-specific custom property value for a player.
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows.
/// See also ServerDeletePlayerCustomPropertiesAsync, ServerListPlayerCustomPropertiesAsync, ServerUpdatePlayerCustomPropertiesAsync.
///
/// When the asynchronous task is complete, call <see cref="PFPlayerDataManagementServerGetPlayerCustomPropertyGetResultSize"/>
/// and <see cref="PFPlayerDataManagementServerGetPlayerCustomPropertyGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFPlayerDataManagementServerGetPlayerCustomPropertyAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFPlayerDataManagementServerGetPlayerCustomPropertyRequest* request,
	_Inout_ FOnServerGetPlayerCustomPropertyCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves the title-specific custom data for the user which is readable and writable by the client
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
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
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFPlayerDataManagementServerGetUserDataAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFPlayerDataManagementGetUserDataRequest* request,
	_Inout_ FOnServerGetUserDataCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves the title-specific custom data for the user which cannot be accessed by the client
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
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
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFPlayerDataManagementServerGetUserInternalDataAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFPlayerDataManagementGetUserDataRequest* request,
	_Inout_ FOnServerGetUserInternalDataCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves the publisher-specific custom data for the user which is readable and writable by the client
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
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
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFPlayerDataManagementServerGetUserPublisherDataAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFPlayerDataManagementGetUserDataRequest* request,
	_Inout_ FOnServerGetUserPublisherDataCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves the publisher-specific custom data for the user which cannot be accessed by the client
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
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
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFPlayerDataManagementServerGetUserPublisherInternalDataAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFPlayerDataManagementGetUserDataRequest* request,
	_Inout_ FOnServerGetUserPublisherInternalDataCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves the publisher-specific custom data for the user which can only be read by the client
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
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
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFPlayerDataManagementServerGetUserPublisherReadOnlyDataAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFPlayerDataManagementGetUserDataRequest* request,
	_Inout_ FOnServerGetUserPublisherReadOnlyDataCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves the title-specific custom data for the user which can only be read by the client
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
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
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFPlayerDataManagementServerGetUserReadOnlyDataAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFPlayerDataManagementGetUserDataRequest* request,
	_Inout_ FOnServerGetUserReadOnlyDataCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves title-specific custom property values for a player.
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows.
/// See also ServerDeletePlayerCustomPropertiesAsync, ServerGetPlayerCustomPropertyAsync, ServerUpdatePlayerCustomPropertiesAsync.
///
/// When the asynchronous task is complete, call <see cref="PFPlayerDataManagementServerListPlayerCustomPropertiesGetResultSize"/>
/// and <see cref="PFPlayerDataManagementServerListPlayerCustomPropertiesGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFPlayerDataManagementServerListPlayerCustomPropertiesAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFPlayerDataManagementListPlayerCustomPropertiesRequest* request,
	_Inout_ FOnServerListPlayerCustomPropertiesCompleted delegate
) noexcept;
#endif

/// <summary>
/// Updates the title-specific custom property values for a player
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
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
#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFPlayerDataManagementServerUpdatePlayerCustomPropertiesAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFPlayerDataManagementServerUpdatePlayerCustomPropertiesRequest* request,
	_Inout_ FOnServerUpdatePlayerCustomPropertiesCompleted delegate
) noexcept;
#endif

/// <summary>
/// Updates the title-specific custom data for the user which is readable and writable by the client
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
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
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFPlayerDataManagementServerUpdateUserDataAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFPlayerDataManagementServerUpdateUserDataRequest* request,
	_Inout_ FOnServerUpdateUserDataCompleted delegate
) noexcept;
#endif

/// <summary>
/// Updates the title-specific custom data for the user which cannot be accessed by the client
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
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
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFPlayerDataManagementServerUpdateUserInternalDataAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFPlayerDataManagementUpdateUserInternalDataRequest* request,
	_Inout_ FOnServerUpdateUserInternalDataCompleted delegate
) noexcept;
#endif

/// <summary>
/// Updates the publisher-specific custom data for the user which is readable and writable by the client
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
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
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFPlayerDataManagementServerUpdateUserPublisherDataAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFPlayerDataManagementServerUpdateUserDataRequest* request,
	_Inout_ FOnServerUpdateUserPublisherDataCompleted delegate
) noexcept;
#endif

/// <summary>
/// Updates the publisher-specific custom data for the user which cannot be accessed by the client
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
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
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFPlayerDataManagementServerUpdateUserPublisherInternalDataAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFPlayerDataManagementUpdateUserInternalDataRequest* request,
	_Inout_ FOnServerUpdateUserPublisherInternalDataCompleted delegate
) noexcept;
#endif

/// <summary>
/// Updates the publisher-specific custom data for the user which can only be read by the client
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
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
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFPlayerDataManagementServerUpdateUserPublisherReadOnlyDataAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFPlayerDataManagementServerUpdateUserDataRequest* request,
	_Inout_ FOnServerUpdateUserPublisherReadOnlyDataCompleted delegate
) noexcept;
#endif

/// <summary>
/// Updates the title-specific custom data for the user which can only be read by the client
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
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
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFPlayerDataManagementServerUpdateUserReadOnlyDataAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFPlayerDataManagementServerUpdateUserDataRequest* request,
	_Inout_ FOnServerUpdateUserReadOnlyDataCompleted delegate
) noexcept;
#endif

}
