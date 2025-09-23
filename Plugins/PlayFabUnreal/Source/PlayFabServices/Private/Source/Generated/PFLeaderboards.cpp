#include "PFLeaderboards.h"

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFLeaderboardsCreateLeaderboardDefinitionAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFLeaderboardsCreateLeaderboardDefinitionRequest* request,
	_Inout_ FOnCreateLeaderboardDefinitionCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FCreateLeaderboardDefinitionAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFLeaderboardsDeleteLeaderboardDefinitionAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFLeaderboardsDeleteLeaderboardDefinitionRequest* request,
	_Inout_ FOnDeleteLeaderboardDefinitionCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FDeleteLeaderboardDefinitionAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFLeaderboardsDeleteLeaderboardEntriesAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFLeaderboardsDeleteLeaderboardEntriesRequest* request,
	_Inout_ FOnDeleteLeaderboardEntriesCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FDeleteLeaderboardEntriesAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

bool PLAYFABSERVICES_API FPFLeaderboardsGetFriendLeaderboardForEntityAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFLeaderboardsGetFriendLeaderboardForEntityRequest* request,
	_Inout_ FOnGetFriendLeaderboardForEntityCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FGetFriendLeaderboardForEntityAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFLeaderboardsGetLeaderboardAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFLeaderboardsGetEntityLeaderboardRequest* request,
	_Inout_ FOnGetLeaderboardCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FGetLeaderboardAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFLeaderboardsGetLeaderboardAroundEntityAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFLeaderboardsGetLeaderboardAroundEntityRequest* request,
	_Inout_ FOnGetLeaderboardAroundEntityCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FGetLeaderboardAroundEntityAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFLeaderboardsGetLeaderboardDefinitionAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFLeaderboardsGetLeaderboardDefinitionRequest* request,
	_Inout_ FOnGetLeaderboardDefinitionCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FGetLeaderboardDefinitionAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFLeaderboardsGetLeaderboardForEntitiesAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFLeaderboardsGetLeaderboardForEntitiesRequest* request,
	_Inout_ FOnGetLeaderboardForEntitiesCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FGetLeaderboardForEntitiesAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFLeaderboardsIncrementLeaderboardVersionAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFLeaderboardsIncrementLeaderboardVersionRequest* request,
	_Inout_ FOnIncrementLeaderboardVersionCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FIncrementLeaderboardVersionAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFLeaderboardsListLeaderboardDefinitionsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFLeaderboardsListLeaderboardDefinitionsRequest* request,
	_Inout_ FOnListLeaderboardDefinitionsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FListLeaderboardDefinitionsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFLeaderboardsUnlinkLeaderboardFromStatisticAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFLeaderboardsUnlinkLeaderboardFromStatisticRequest* request,
	_Inout_ FOnUnlinkLeaderboardFromStatisticCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FUnlinkLeaderboardFromStatisticAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFLeaderboardsUpdateLeaderboardDefinitionAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFLeaderboardsUpdateLeaderboardDefinitionRequest* request,
	_Inout_ FOnUpdateLeaderboardDefinitionCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FUpdateLeaderboardDefinitionAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFLeaderboardsUpdateLeaderboardEntriesAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFLeaderboardsUpdateLeaderboardEntriesRequest* request,
	_Inout_ FOnUpdateLeaderboardEntriesCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FUpdateLeaderboardEntriesAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

