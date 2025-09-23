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
#include "PFPushNotificationsUnrealTypes.h"
#include "PFPushNotificationsTypeConverters.h"

THIRD_PARTY_INCLUDES_START
#include <playfab/services/PFServices.h>
THIRD_PARTY_INCLUDES_END

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Sends an iOS/Android Push Notification to a specific user, if that user's device has been configured
/// for Push Notifications in PlayFab. If a user has linked both Android and iOS devices, both will be
/// notified.
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_PUSH_NOT_ENABLED_FOR_ACCOUNT, E_PF_PUSH_SERVICE_ERROR or any of the
/// global PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FServerSendPushNotificationAsyncTask : public FXAsyncTask
{
public:
	FServerSendPushNotificationAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFPushNotificationsSendPushNotificationRequest InRequest,
	const FOnServerSendPushNotificationCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFPushNotificationsSendPushNotificationRequest Request;
	
	FOnServerSendPushNotificationCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Sends an iOS/Android Push Notification template to a specific user, if that user's device has been
/// configured for Push Notifications in PlayFab. If a user has linked both Android and iOS devices, both
/// will be notified.
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_PUSH_NOT_ENABLED_FOR_ACCOUNT, E_PF_PUSH_NOTIFICATION_TEMPLATE_NOT_FOUND,
/// E_PF_PUSH_SERVICE_ERROR or any of the global PlayFab Service errors. See doc page "Handling PlayFab
/// Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FServerSendPushNotificationFromTemplateAsyncTask : public FXAsyncTask
{
public:
	FServerSendPushNotificationFromTemplateAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFPushNotificationsSendPushNotificationFromTemplateRequest InRequest,
	const FOnServerSendPushNotificationFromTemplateCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFPushNotificationsSendPushNotificationFromTemplateRequest Request;
	
	FOnServerSendPushNotificationFromTemplateCompleted Delegate;

	HRESULT HResult;
};

#endif
