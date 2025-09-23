// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include "CoreMinimal.h"
#include "XAsyncTaskManager.h"
#include "PFPlatformSpecificAsyncTasks.h"

THIRD_PARTY_INCLUDES_START
#include <playfab/services/PFServices.h>
THIRD_PARTY_INCLUDES_END

extern "C"
{
/// <summary>
/// Registers the Android device to receive push notifications
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Android.
/// More information can be found on configuring your game for the Google Cloud Messaging service in
/// the Google developer documentation, here: http://developer.android.com/google/gcm/client.html. The
/// steps to configure and send Push Notifications is described in the PlayFab tutorials, here: https://docs.microsoft.com/gaming/playfab/features/engagement/push-notifications/quickstart.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_NO_PUSH_NOTIFICATION_ARN_FOR_TITLE, E_PF_PUSH_SERVICE_ERROR or any of
/// the global PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details on error
/// handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_ANDROID
bool PLAYFABSERVICES_API FPFPlatformSpecificClientAndroidDevicePushNotificationRegistrationAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFPlatformSpecificAndroidDevicePushNotificationRegistrationRequest* request,
	_Inout_ FOnClientAndroidDevicePushNotificationRegistrationCompleted delegate
) noexcept;
#endif

/// <summary>
/// Uses the supplied OAuth code to refresh the internally cached player PlayStation :tm: Network auth
/// token
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_INVALID_PSN_AUTH_CODE, E_PF_PSN_INACCESSIBLE or any of the global PlayFab
/// Service errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if 0
bool PLAYFABSERVICES_API FPFPlatformSpecificClientRefreshPSNAuthTokenAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFPlatformSpecificRefreshPSNAuthTokenRequest* request,
	_Inout_ FOnClientRefreshPSNAuthTokenCompleted delegate
) noexcept;
#endif

/// <summary>
/// Registers the iOS device to receive push notifications
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on iOS.
/// The steps to configure and send Push Notifications is described in the PlayFab tutorials, here: https://docs.microsoft.com/gaming/playfab/features/engagement/push-notifications/quickstart.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_NO_PUSH_NOTIFICATION_ARN_FOR_TITLE, E_PF_PUSH_SERVICE_ERROR or any of
/// the global PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details on error
/// handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_IOS
bool PLAYFABSERVICES_API FPFPlatformSpecificClientRegisterForIOSPushNotificationAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFPlatformSpecificRegisterForIOSPushNotificationRequest* request,
	_Inout_ FOnClientRegisterForIOSPushNotificationCompleted delegate
) noexcept;
#endif

/// <summary>
/// Awards the specified users the specified Steam achievements
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFPlatformSpecificServerAwardSteamAchievementGetResultSize"/>
/// and <see cref="PFPlatformSpecificServerAwardSteamAchievementGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFPlatformSpecificServerAwardSteamAchievementAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFPlatformSpecificAwardSteamAchievementRequest* request,
	_Inout_ FOnServerAwardSteamAchievementCompleted delegate
) noexcept;
#endif

}
