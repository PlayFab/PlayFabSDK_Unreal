#include "PFProfiles.h"

bool PLAYFABSERVICES_API FPFProfilesGetProfileAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFProfilesGetEntityProfileRequest* request,
	_Inout_ FOnGetProfileCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FGetProfileAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFProfilesGetProfilesAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFProfilesGetEntityProfilesRequest* request,
	_Inout_ FOnGetProfilesCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FGetProfilesAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFProfilesGetTitlePlayersFromMasterPlayerAccountIdsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFProfilesGetTitlePlayersFromMasterPlayerAccountIdsRequest* request,
	_Inout_ FOnGetTitlePlayersFromMasterPlayerAccountIdsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FGetTitlePlayersFromMasterPlayerAccountIdsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFProfilesSetProfileLanguageAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFProfilesSetProfileLanguageRequest* request,
	_Inout_ FOnSetProfileLanguageCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FSetProfileLanguageAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFProfilesSetProfilePolicyAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFProfilesSetEntityProfilePolicyRequest* request,
	_Inout_ FOnSetProfilePolicyCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FSetProfilePolicyAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

