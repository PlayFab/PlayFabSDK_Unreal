#include "PFPlayerDataManagement.h"

bool PLAYFABSERVICES_API FPFPlayerDataManagementClientDeletePlayerCustomPropertiesAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFPlayerDataManagementClientDeletePlayerCustomPropertiesRequest* request,
	_Inout_ FOnClientDeletePlayerCustomPropertiesCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientDeletePlayerCustomPropertiesAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFPlayerDataManagementClientGetPlayerCustomPropertyAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFPlayerDataManagementClientGetPlayerCustomPropertyRequest* request,
	_Inout_ FOnClientGetPlayerCustomPropertyCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientGetPlayerCustomPropertyAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFPlayerDataManagementClientGetUserDataAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFPlayerDataManagementGetUserDataRequest* request,
	_Inout_ FOnClientGetUserDataCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientGetUserDataAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFPlayerDataManagementClientGetUserPublisherDataAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFPlayerDataManagementGetUserDataRequest* request,
	_Inout_ FOnClientGetUserPublisherDataCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientGetUserPublisherDataAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFPlayerDataManagementClientGetUserPublisherReadOnlyDataAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFPlayerDataManagementGetUserDataRequest* request,
	_Inout_ FOnClientGetUserPublisherReadOnlyDataCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientGetUserPublisherReadOnlyDataAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFPlayerDataManagementClientGetUserReadOnlyDataAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFPlayerDataManagementGetUserDataRequest* request,
	_Inout_ FOnClientGetUserReadOnlyDataCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientGetUserReadOnlyDataAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFPlayerDataManagementClientListPlayerCustomPropertiesAsync(
	_In_ FPFEntityHandle EntityHandle,
	_Inout_ FOnClientListPlayerCustomPropertiesCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientListPlayerCustomPropertiesAsyncTask>(EntityHandle,delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFPlayerDataManagementClientUpdatePlayerCustomPropertiesAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFPlayerDataManagementClientUpdatePlayerCustomPropertiesRequest* request,
	_Inout_ FOnClientUpdatePlayerCustomPropertiesCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientUpdatePlayerCustomPropertiesAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFPlayerDataManagementClientUpdateUserDataAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFPlayerDataManagementClientUpdateUserDataRequest* request,
	_Inout_ FOnClientUpdateUserDataCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientUpdateUserDataAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFPlayerDataManagementClientUpdateUserPublisherDataAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFPlayerDataManagementClientUpdateUserDataRequest* request,
	_Inout_ FOnClientUpdateUserPublisherDataCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientUpdateUserPublisherDataAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFPlayerDataManagementServerDeletePlayerCustomPropertiesAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFPlayerDataManagementServerDeletePlayerCustomPropertiesRequest* request,
	_Inout_ FOnServerDeletePlayerCustomPropertiesCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerDeletePlayerCustomPropertiesAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFPlayerDataManagementServerGetPlayerCustomPropertyAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFPlayerDataManagementServerGetPlayerCustomPropertyRequest* request,
	_Inout_ FOnServerGetPlayerCustomPropertyCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerGetPlayerCustomPropertyAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFPlayerDataManagementServerGetUserDataAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFPlayerDataManagementGetUserDataRequest* request,
	_Inout_ FOnServerGetUserDataCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerGetUserDataAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFPlayerDataManagementServerGetUserInternalDataAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFPlayerDataManagementGetUserDataRequest* request,
	_Inout_ FOnServerGetUserInternalDataCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerGetUserInternalDataAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFPlayerDataManagementServerGetUserPublisherDataAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFPlayerDataManagementGetUserDataRequest* request,
	_Inout_ FOnServerGetUserPublisherDataCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerGetUserPublisherDataAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFPlayerDataManagementServerGetUserPublisherInternalDataAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFPlayerDataManagementGetUserDataRequest* request,
	_Inout_ FOnServerGetUserPublisherInternalDataCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerGetUserPublisherInternalDataAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFPlayerDataManagementServerGetUserPublisherReadOnlyDataAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFPlayerDataManagementGetUserDataRequest* request,
	_Inout_ FOnServerGetUserPublisherReadOnlyDataCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerGetUserPublisherReadOnlyDataAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFPlayerDataManagementServerGetUserReadOnlyDataAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFPlayerDataManagementGetUserDataRequest* request,
	_Inout_ FOnServerGetUserReadOnlyDataCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerGetUserReadOnlyDataAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFPlayerDataManagementServerListPlayerCustomPropertiesAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFPlayerDataManagementListPlayerCustomPropertiesRequest* request,
	_Inout_ FOnServerListPlayerCustomPropertiesCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerListPlayerCustomPropertiesAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFPlayerDataManagementServerUpdatePlayerCustomPropertiesAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFPlayerDataManagementServerUpdatePlayerCustomPropertiesRequest* request,
	_Inout_ FOnServerUpdatePlayerCustomPropertiesCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerUpdatePlayerCustomPropertiesAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFPlayerDataManagementServerUpdateUserDataAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFPlayerDataManagementServerUpdateUserDataRequest* request,
	_Inout_ FOnServerUpdateUserDataCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerUpdateUserDataAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFPlayerDataManagementServerUpdateUserInternalDataAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFPlayerDataManagementUpdateUserInternalDataRequest* request,
	_Inout_ FOnServerUpdateUserInternalDataCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerUpdateUserInternalDataAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFPlayerDataManagementServerUpdateUserPublisherDataAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFPlayerDataManagementServerUpdateUserDataRequest* request,
	_Inout_ FOnServerUpdateUserPublisherDataCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerUpdateUserPublisherDataAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFPlayerDataManagementServerUpdateUserPublisherInternalDataAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFPlayerDataManagementUpdateUserInternalDataRequest* request,
	_Inout_ FOnServerUpdateUserPublisherInternalDataCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerUpdateUserPublisherInternalDataAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFPlayerDataManagementServerUpdateUserPublisherReadOnlyDataAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFPlayerDataManagementServerUpdateUserDataRequest* request,
	_Inout_ FOnServerUpdateUserPublisherReadOnlyDataCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerUpdateUserPublisherReadOnlyDataAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFPlayerDataManagementServerUpdateUserReadOnlyDataAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFPlayerDataManagementServerUpdateUserDataRequest* request,
	_Inout_ FOnServerUpdateUserReadOnlyDataCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerUpdateUserReadOnlyDataAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

