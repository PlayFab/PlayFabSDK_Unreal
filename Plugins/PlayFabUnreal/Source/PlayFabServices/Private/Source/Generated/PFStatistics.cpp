#include "PFStatistics.h"

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFStatisticsCreateStatisticDefinitionAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFStatisticsCreateStatisticDefinitionRequest* request,
	_Inout_ FOnCreateStatisticDefinitionCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FCreateStatisticDefinitionAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFStatisticsDeleteStatisticDefinitionAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFStatisticsDeleteStatisticDefinitionRequest* request,
	_Inout_ FOnDeleteStatisticDefinitionCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FDeleteStatisticDefinitionAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

bool PLAYFABSERVICES_API FPFStatisticsDeleteStatisticsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFStatisticsDeleteStatisticsRequest* request,
	_Inout_ FOnDeleteStatisticsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FDeleteStatisticsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFStatisticsGetStatisticDefinitionAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFStatisticsGetStatisticDefinitionRequest* request,
	_Inout_ FOnGetStatisticDefinitionCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FGetStatisticDefinitionAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

bool PLAYFABSERVICES_API FPFStatisticsGetStatisticsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFStatisticsGetStatisticsRequest* request,
	_Inout_ FOnGetStatisticsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FGetStatisticsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFStatisticsGetStatisticsForEntitiesAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFStatisticsGetStatisticsForEntitiesRequest* request,
	_Inout_ FOnGetStatisticsForEntitiesCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FGetStatisticsForEntitiesAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFStatisticsIncrementStatisticVersionAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFStatisticsIncrementStatisticVersionRequest* request,
	_Inout_ FOnIncrementStatisticVersionCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FIncrementStatisticVersionAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFStatisticsListStatisticDefinitionsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFStatisticsListStatisticDefinitionsRequest* request,
	_Inout_ FOnListStatisticDefinitionsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FListStatisticDefinitionsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFStatisticsUpdateStatisticDefinitionAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFStatisticsUpdateStatisticDefinitionRequest* request,
	_Inout_ FOnUpdateStatisticDefinitionCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FUpdateStatisticDefinitionAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

bool PLAYFABSERVICES_API FPFStatisticsUpdateStatisticsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFStatisticsUpdateStatisticsRequest* request,
	_Inout_ FOnUpdateStatisticsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FUpdateStatisticsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

