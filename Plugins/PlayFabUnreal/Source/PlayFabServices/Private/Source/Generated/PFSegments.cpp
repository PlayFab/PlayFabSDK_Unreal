#include "PFSegments.h"

bool PLAYFABSERVICES_API FPFSegmentsClientGetPlayerSegmentsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_Inout_ FOnClientGetPlayerSegmentsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientGetPlayerSegmentsAsyncTask>(EntityHandle,delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFSegmentsClientGetPlayerTagsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFSegmentsGetPlayerTagsRequest* request,
	_Inout_ FOnClientGetPlayerTagsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientGetPlayerTagsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFSegmentsServerAddPlayerTagAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFSegmentsAddPlayerTagRequest* request,
	_Inout_ FOnServerAddPlayerTagCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerAddPlayerTagAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFSegmentsServerGetAllSegmentsAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_Inout_ FOnServerGetAllSegmentsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerGetAllSegmentsAsyncTask>(TitleEntityHandle,delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFSegmentsServerGetPlayerSegmentsAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFSegmentsGetPlayersSegmentsRequest* request,
	_Inout_ FOnServerGetPlayerSegmentsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerGetPlayerSegmentsAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFSegmentsServerGetPlayerTagsAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFSegmentsGetPlayerTagsRequest* request,
	_Inout_ FOnServerGetPlayerTagsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerGetPlayerTagsAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFSegmentsServerRemovePlayerTagAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFSegmentsRemovePlayerTagRequest* request,
	_Inout_ FOnServerRemovePlayerTagCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerRemovePlayerTagAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

