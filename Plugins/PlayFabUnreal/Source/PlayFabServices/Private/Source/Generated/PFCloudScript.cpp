#include "PFCloudScript.h"

bool PLAYFABSERVICES_API FPFCloudScriptClientExecuteCloudScriptAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCloudScriptExecuteCloudScriptRequest* request,
	_Inout_ FOnClientExecuteCloudScriptCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientExecuteCloudScriptAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFCloudScriptServerExecuteCloudScriptAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFCloudScriptExecuteCloudScriptServerRequest* request,
	_Inout_ FOnServerExecuteCloudScriptCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerExecuteCloudScriptAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

bool PLAYFABSERVICES_API FPFCloudScriptExecuteEntityCloudScriptAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCloudScriptExecuteEntityCloudScriptRequest* request,
	_Inout_ FOnExecuteEntityCloudScriptCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FExecuteEntityCloudScriptAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFCloudScriptExecuteFunctionAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCloudScriptExecuteFunctionRequest* request,
	_Inout_ FOnExecuteFunctionCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FExecuteFunctionAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

#if 0
bool PLAYFABSERVICES_API FPFCloudScriptListEventHubFunctionsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCloudScriptListFunctionsRequest* request,
	_Inout_ FOnListEventHubFunctionsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FListEventHubFunctionsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if 0
bool PLAYFABSERVICES_API FPFCloudScriptRegisterEventHubFunctionAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCloudScriptRegisterEventHubFunctionRequest* request,
	_Inout_ FOnRegisterEventHubFunctionCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FRegisterEventHubFunctionAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

