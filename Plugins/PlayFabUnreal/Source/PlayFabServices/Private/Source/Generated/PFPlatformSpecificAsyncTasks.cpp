// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFPlatformSpecificAsyncTasks.h"

#if HC_PLATFORM == HC_PLATFORM_ANDROID
FClientAndroidDevicePushNotificationRegistrationAsyncTask::FClientAndroidDevicePushNotificationRegistrationAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFPlatformSpecificAndroidDevicePushNotificationRegistrationRequest InRequest,
	const FOnClientAndroidDevicePushNotificationRegistrationCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientAndroidDevicePushNotificationRegistrationAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientAndroidDevicePushNotificationRegistrationAsyncTask::DoWork()
{
	const PFPlatformSpecificAndroidDevicePushNotificationRegistrationRequest RequestType = {
		.confirmationMessage = ConvertFStringToCharPtr(Request.confirmationMessage),
		.deviceToken = ConvertFStringToCharPtr(Request.deviceToken),
		.sendPushNotificationConfirmation = Request.sendPushNotificationConfirmation ? new bool(*Request.sendPushNotificationConfirmation) : nullptr
	};
	HResult = PFPlatformSpecificClientAndroidDevicePushNotificationRegistrationAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientAndroidDevicePushNotificationRegistrationAsyncTask::ProcessResults()
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

#if 0
FClientRefreshPSNAuthTokenAsyncTask::FClientRefreshPSNAuthTokenAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFPlatformSpecificRefreshPSNAuthTokenRequest InRequest,
	const FOnClientRefreshPSNAuthTokenCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientRefreshPSNAuthTokenAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientRefreshPSNAuthTokenAsyncTask::DoWork()
{
	const PFPlatformSpecificRefreshPSNAuthTokenRequest RequestType = {
		.authCode = ConvertFStringToCharPtr(Request.authCode),
		.issuerId = Request.issuerId ? new int32(*Request.issuerId) : nullptr,
		.redirectUri = ConvertFStringToCharPtr(Request.redirectUri)
	};
	HResult = PFPlatformSpecificClientRefreshPSNAuthTokenAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientRefreshPSNAuthTokenAsyncTask::ProcessResults()
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

#if HC_PLATFORM == HC_PLATFORM_IOS
FClientRegisterForIOSPushNotificationAsyncTask::FClientRegisterForIOSPushNotificationAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFPlatformSpecificRegisterForIOSPushNotificationRequest InRequest,
	const FOnClientRegisterForIOSPushNotificationCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientRegisterForIOSPushNotificationAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientRegisterForIOSPushNotificationAsyncTask::DoWork()
{
	const PFPlatformSpecificRegisterForIOSPushNotificationRequest RequestType = {
		.confirmationMessage = ConvertFStringToCharPtr(Request.confirmationMessage),
		.deviceToken = ConvertFStringToCharPtr(Request.deviceToken),
		.sendPushNotificationConfirmation = Request.sendPushNotificationConfirmation ? new bool(*Request.sendPushNotificationConfirmation) : nullptr
	};
	HResult = PFPlatformSpecificClientRegisterForIOSPushNotificationAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientRegisterForIOSPushNotificationAsyncTask::ProcessResults()
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
FServerAwardSteamAchievementAsyncTask::FServerAwardSteamAchievementAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFPlatformSpecificAwardSteamAchievementRequest InRequest,
	const FOnServerAwardSteamAchievementCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerAwardSteamAchievementAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerAwardSteamAchievementAsyncTask::DoWork()
{
	const PFPlatformSpecificAwardSteamAchievementRequest RequestType = {
		.achievements = ConvertUnrealArrayToPlayfab(Request.achievements, ConvertAwardSteamAchievementItemToPlayfab),
		.achievementsCount = (uint32_t)Request.achievements.Num()
	};
	HResult = PFPlatformSpecificServerAwardSteamAchievementAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFPlatformSpecificAwardSteamAchievementResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerAwardSteamAchievementAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFPlatformSpecificServerAwardSteamAchievementGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFPlatformSpecificAwardSteamAchievementResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFPlatformSpecificAwardSteamAchievementResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFPlatformSpecificServerAwardSteamAchievementGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFPlatformSpecificAwardSteamAchievementResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFPlatformSpecificAwardSteamAchievementResult> ResultType = ConvertAwardSteamAchievementResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

