// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFPushNotificationsAsyncTasks.h"

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerSendPushNotificationAsyncTask::FServerSendPushNotificationAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFPushNotificationsSendPushNotificationRequest InRequest,
	const FOnServerSendPushNotificationCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerSendPushNotificationAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerSendPushNotificationAsyncTask::DoWork()
{
	const PFPushNotificationsSendPushNotificationRequest RequestType = {
		.advancedPlatformDelivery = ConvertUnrealArrayToPlayfab(Request.advancedPlatformDelivery, ConvertAdvancedPushPlatformMsgToPlayfab),
		.advancedPlatformDeliveryCount = (uint32_t)Request.advancedPlatformDelivery.Num(),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.message = ConvertFStringToCharPtr(Request.message),
		.package = ConvertPushNotificationPackageToPlayfab(Request.package),
		.recipient = ConvertFStringToCharPtr(Request.recipient),
		.subject = ConvertFStringToCharPtr(Request.subject),
		.targetPlatforms = ConvertUnrealEnumArrayToPlayfab(Request.targetPlatforms, ConvertPushNotificationPlatformToPlayfab),
		.targetPlatformsCount = (uint32_t)Request.targetPlatforms.Num()
	};
	HResult = PFPushNotificationsServerSendPushNotificationAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FServerSendPushNotificationAsyncTask::ProcessResults()
{
	if (HResult != S_OK)
	{
		Delegate.Execute(FString("Async task failure"), false);
	}
	else
	{
		Delegate.Execute(FString(), true);
	}
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerSendPushNotificationFromTemplateAsyncTask::FServerSendPushNotificationFromTemplateAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFPushNotificationsSendPushNotificationFromTemplateRequest InRequest,
	const FOnServerSendPushNotificationFromTemplateCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerSendPushNotificationFromTemplateAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerSendPushNotificationFromTemplateAsyncTask::DoWork()
{
	const PFPushNotificationsSendPushNotificationFromTemplateRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.pushNotificationTemplateId = ConvertFStringToCharPtr(Request.pushNotificationTemplateId),
		.recipient = ConvertFStringToCharPtr(Request.recipient)
	};
	HResult = PFPushNotificationsServerSendPushNotificationFromTemplateAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FServerSendPushNotificationFromTemplateAsyncTask::ProcessResults()
{
	if (HResult != S_OK)
	{
		Delegate.Execute(FString("Async task failure"), false);
	}
	else
	{
		Delegate.Execute(FString(), true);
	}
}
#endif

