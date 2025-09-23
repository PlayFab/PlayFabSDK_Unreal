#include "PFPlatformSpecific.h"

#if HC_PLATFORM == HC_PLATFORM_ANDROID
bool PLAYFABSERVICES_API FPFPlatformSpecificClientAndroidDevicePushNotificationRegistrationAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFPlatformSpecificAndroidDevicePushNotificationRegistrationRequest* request,
	_Inout_ FOnClientAndroidDevicePushNotificationRegistrationCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientAndroidDevicePushNotificationRegistrationAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if 0
bool PLAYFABSERVICES_API FPFPlatformSpecificClientRefreshPSNAuthTokenAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFPlatformSpecificRefreshPSNAuthTokenRequest* request,
	_Inout_ FOnClientRefreshPSNAuthTokenCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientRefreshPSNAuthTokenAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_IOS
bool PLAYFABSERVICES_API FPFPlatformSpecificClientRegisterForIOSPushNotificationAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFPlatformSpecificRegisterForIOSPushNotificationRequest* request,
	_Inout_ FOnClientRegisterForIOSPushNotificationCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientRegisterForIOSPushNotificationAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFPlatformSpecificServerAwardSteamAchievementAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFPlatformSpecificAwardSteamAchievementRequest* request,
	_Inout_ FOnServerAwardSteamAchievementCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerAwardSteamAchievementAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

