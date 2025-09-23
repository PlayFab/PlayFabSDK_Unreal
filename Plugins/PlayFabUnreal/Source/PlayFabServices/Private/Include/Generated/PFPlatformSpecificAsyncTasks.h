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
#include "PFPlatformSpecificUnrealTypes.h"
#include "PFPlatformSpecificTypeConverters.h"

THIRD_PARTY_INCLUDES_START
#include <playfab/services/PFServices.h>
THIRD_PARTY_INCLUDES_END

#if HC_PLATFORM == HC_PLATFORM_ANDROID

/// <summary>
/// Registers the Android device to receive push notifications
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FClientAndroidDevicePushNotificationRegistrationAsyncTask : public FXAsyncTask
{
public:
	FClientAndroidDevicePushNotificationRegistrationAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFPlatformSpecificAndroidDevicePushNotificationRegistrationRequest InRequest,
	const FOnClientAndroidDevicePushNotificationRegistrationCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFPlatformSpecificAndroidDevicePushNotificationRegistrationRequest Request;
	
	FOnClientAndroidDevicePushNotificationRegistrationCompleted Delegate;

	HRESULT HResult;
};

#endif

#if 0

/// <summary>
/// Uses the supplied OAuth code to refresh the internally cached player PlayStation :tm: Network auth
/// token
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_INVALID_PSN_AUTH_CODE, E_PF_PSN_INACCESSIBLE or any of the global PlayFab
/// Service errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FClientRefreshPSNAuthTokenAsyncTask : public FXAsyncTask
{
public:
	FClientRefreshPSNAuthTokenAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFPlatformSpecificRefreshPSNAuthTokenRequest InRequest,
	const FOnClientRefreshPSNAuthTokenCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFPlatformSpecificRefreshPSNAuthTokenRequest Request;
	
	FOnClientRefreshPSNAuthTokenCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_IOS

/// <summary>
/// Registers the iOS device to receive push notifications
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FClientRegisterForIOSPushNotificationAsyncTask : public FXAsyncTask
{
public:
	FClientRegisterForIOSPushNotificationAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFPlatformSpecificRegisterForIOSPushNotificationRequest InRequest,
	const FOnClientRegisterForIOSPushNotificationCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFPlatformSpecificRegisterForIOSPushNotificationRequest Request;
	
	FOnClientRegisterForIOSPushNotificationCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Awards the specified users the specified Steam achievements
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFPlatformSpecificServerAwardSteamAchievementGetResultSize"/>
/// and <see cref="PFPlatformSpecificServerAwardSteamAchievementGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FServerAwardSteamAchievementAsyncTask : public FXAsyncTask
{
public:
	FServerAwardSteamAchievementAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFPlatformSpecificAwardSteamAchievementRequest InRequest,
	const FOnServerAwardSteamAchievementCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFPlatformSpecificAwardSteamAchievementRequest Request;
	
	FOnServerAwardSteamAchievementCompleted Delegate;

	HRESULT HResult;
};

#endif
