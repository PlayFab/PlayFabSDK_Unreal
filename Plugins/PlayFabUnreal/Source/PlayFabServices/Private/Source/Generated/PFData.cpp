#include "PFData.h"

bool PLAYFABSERVICES_API FPFDataAbortFileUploadsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFDataAbortFileUploadsRequest* request,
	_Inout_ FOnAbortFileUploadsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FAbortFileUploadsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFDataDeleteFilesAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFDataDeleteFilesRequest* request,
	_Inout_ FOnDeleteFilesCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FDeleteFilesAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFDataFinalizeFileUploadsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFDataFinalizeFileUploadsRequest* request,
	_Inout_ FOnFinalizeFileUploadsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FFinalizeFileUploadsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFDataGetFilesAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFDataGetFilesRequest* request,
	_Inout_ FOnGetFilesCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FGetFilesAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFDataGetObjectsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFDataGetObjectsRequest* request,
	_Inout_ FOnGetObjectsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FGetObjectsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFDataInitiateFileUploadsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFDataInitiateFileUploadsRequest* request,
	_Inout_ FOnInitiateFileUploadsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FInitiateFileUploadsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFDataSetObjectsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFDataSetObjectsRequest* request,
	_Inout_ FOnSetObjectsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FSetObjectsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

