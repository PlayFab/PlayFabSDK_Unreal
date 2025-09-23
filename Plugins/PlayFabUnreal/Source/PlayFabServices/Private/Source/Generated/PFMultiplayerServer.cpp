#include "PFMultiplayerServer.h"

#if 0
bool PLAYFABSERVICES_API FPFMultiplayerServerDeleteSecretAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFMultiplayerServerDeleteSecretRequest* request,
	_Inout_ FOnDeleteSecretCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FDeleteSecretAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

bool PLAYFABSERVICES_API FPFMultiplayerServerListBuildAliasesAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFMultiplayerServerListBuildAliasesRequest* request,
	_Inout_ FOnListBuildAliasesCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FListBuildAliasesAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFMultiplayerServerListBuildSummariesV2Async(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFMultiplayerServerListBuildSummariesRequest* request,
	_Inout_ FOnListBuildSummariesV2Completed delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FListBuildSummariesV2AsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFMultiplayerServerListQosServersForTitleAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFMultiplayerServerListQosServersForTitleRequest* request,
	_Inout_ FOnListQosServersForTitleCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FListQosServersForTitleAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

#if 0
bool PLAYFABSERVICES_API FPFMultiplayerServerListSecretSummariesAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFMultiplayerServerListSecretSummariesRequest* request,
	_Inout_ FOnListSecretSummariesCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FListSecretSummariesAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

bool PLAYFABSERVICES_API FPFMultiplayerServerRequestMultiplayerServerAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFMultiplayerServerRequestMultiplayerServerRequest* request,
	_Inout_ FOnRequestMultiplayerServerCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FRequestMultiplayerServerAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

#if 0
bool PLAYFABSERVICES_API FPFMultiplayerServerRequestPartyServiceAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFMultiplayerServerRequestPartyServiceRequest* request,
	_Inout_ FOnRequestPartyServiceCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FRequestPartyServiceAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if 0
bool PLAYFABSERVICES_API FPFMultiplayerServerUploadSecretAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFMultiplayerServerUploadSecretRequest* request,
	_Inout_ FOnUploadSecretCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FUploadSecretAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

