#include "PFPushNotifications.h"

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFPushNotificationsServerSendPushNotificationAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFPushNotificationsSendPushNotificationRequest* request,
	_Inout_ FOnServerSendPushNotificationCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerSendPushNotificationAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFPushNotificationsServerSendPushNotificationFromTemplateAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFPushNotificationsSendPushNotificationFromTemplateRequest* request,
	_Inout_ FOnServerSendPushNotificationFromTemplateCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerSendPushNotificationFromTemplateAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

