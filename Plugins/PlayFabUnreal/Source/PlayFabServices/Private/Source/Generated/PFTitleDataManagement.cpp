#include "PFTitleDataManagement.h"

bool PLAYFABSERVICES_API FPFTitleDataManagementClientGetPublisherDataAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFTitleDataManagementGetPublisherDataRequest* request,
	_Inout_ FOnClientGetPublisherDataCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientGetPublisherDataAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFTitleDataManagementClientGetTimeAsync(
	_In_ FPFEntityHandle EntityHandle,
	_Inout_ FOnClientGetTimeCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientGetTimeAsyncTask>(EntityHandle,delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFTitleDataManagementClientGetTitleDataAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFTitleDataManagementGetTitleDataRequest* request,
	_Inout_ FOnClientGetTitleDataCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientGetTitleDataAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFTitleDataManagementClientGetTitleNewsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFTitleDataManagementGetTitleNewsRequest* request,
	_Inout_ FOnClientGetTitleNewsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientGetTitleNewsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFTitleDataManagementServerGetPublisherDataAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFTitleDataManagementGetPublisherDataRequest* request,
	_Inout_ FOnServerGetPublisherDataCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerGetPublisherDataAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFTitleDataManagementServerGetTimeAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_Inout_ FOnServerGetTimeCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerGetTimeAsyncTask>(TitleEntityHandle,delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFTitleDataManagementServerGetTitleDataAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFTitleDataManagementGetTitleDataRequest* request,
	_Inout_ FOnServerGetTitleDataCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerGetTitleDataAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFTitleDataManagementServerGetTitleInternalDataAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFTitleDataManagementGetTitleDataRequest* request,
	_Inout_ FOnServerGetTitleInternalDataCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerGetTitleInternalDataAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFTitleDataManagementServerGetTitleNewsAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFTitleDataManagementGetTitleNewsRequest* request,
	_Inout_ FOnServerGetTitleNewsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerGetTitleNewsAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFTitleDataManagementServerSetPublisherDataAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFTitleDataManagementSetPublisherDataRequest* request,
	_Inout_ FOnServerSetPublisherDataCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerSetPublisherDataAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFTitleDataManagementServerSetTitleDataAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFTitleDataManagementSetTitleDataRequest* request,
	_Inout_ FOnServerSetTitleDataCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerSetTitleDataAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFTitleDataManagementServerSetTitleInternalDataAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFTitleDataManagementSetTitleDataRequest* request,
	_Inout_ FOnServerSetTitleInternalDataCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerSetTitleInternalDataAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

