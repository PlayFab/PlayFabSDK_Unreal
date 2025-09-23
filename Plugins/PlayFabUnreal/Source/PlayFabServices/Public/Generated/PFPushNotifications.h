// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include "CoreMinimal.h"
#include "XAsyncTaskManager.h"
#include "PFPushNotificationsAsyncTasks.h"

THIRD_PARTY_INCLUDES_START
#include <playfab/services/PFServices.h>
THIRD_PARTY_INCLUDES_END

extern "C"
{
/// <summary>
/// Sends an iOS/Android Push Notification to a specific user, if that user's device has been configured
/// for Push Notifications in PlayFab. If a user has linked both Android and iOS devices, both will be
/// notified.
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_PUSH_NOT_ENABLED_FOR_ACCOUNT, E_PF_PUSH_SERVICE_ERROR or any of the
/// global PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFPushNotificationsServerSendPushNotificationAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFPushNotificationsSendPushNotificationRequest* request,
	_Inout_ FOnServerSendPushNotificationCompleted delegate
) noexcept;
#endif

/// <summary>
/// Sends an iOS/Android Push Notification template to a specific user, if that user's device has been
/// configured for Push Notifications in PlayFab. If a user has linked both Android and iOS devices, both
/// will be notified.
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_PUSH_NOT_ENABLED_FOR_ACCOUNT, E_PF_PUSH_NOTIFICATION_TEMPLATE_NOT_FOUND,
/// E_PF_PUSH_SERVICE_ERROR or any of the global PlayFab Service errors. See doc page "Handling PlayFab
/// Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFPushNotificationsServerSendPushNotificationFromTemplateAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFPushNotificationsSendPushNotificationFromTemplateRequest* request,
	_Inout_ FOnServerSendPushNotificationFromTemplateCompleted delegate
) noexcept;
#endif

}
