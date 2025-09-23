#include "PFEvents.h"

#if 0
bool PLAYFABCORE_API FPFEventsDeleteDataConnectionAsync(
	_In_ FPFEntityHandle contextHandle,
	_In_ const FPFEventsDeleteDataConnectionRequest request,
	_Inout_ FOnDeleteDataConnectionDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFEventsDeleteDataConnectionAsyncTask>(contextHandle, request, delegate);
	return true;
}
#endif


#if 0
bool PLAYFABCORE_API FPFEventsGetDataConnectionAsync(
	_In_ FPFEntityHandle contextHandle,
	_In_ const FPFEventsGetDataConnectionRequest request,
	_Inout_ FOnGetDataConnectionDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFEventsGetDataConnectionAsyncTask>(contextHandle, request, delegate);
	return true;
}
#endif


#if 0
bool PLAYFABCORE_API FPFEventsListDataConnectionsAsync(
	_In_ FPFEntityHandle contextHandle,
	_In_ const FPFEventsListDataConnectionsRequest request,
	_Inout_ FOnListDataConnectionsDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFEventsListDataConnectionsAsyncTask>(contextHandle, request, delegate);
	return true;
}
#endif


#if 0
bool PLAYFABCORE_API FPFEventsSetDataConnectionAsync(
	_In_ FPFEntityHandle contextHandle,
	_In_ const FPFEventsSetDataConnectionRequest request,
	_Inout_ FOnSetDataConnectionDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFEventsSetDataConnectionAsyncTask>(contextHandle, request, delegate);
	return true;
}
#endif


#if 0
bool PLAYFABCORE_API FPFEventsSetDataConnectionActiveAsync(
	_In_ FPFEntityHandle contextHandle,
	_In_ const FPFEventsSetDataConnectionActiveRequest request,
	_Inout_ FOnSetDataConnectionActiveDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFEventsSetDataConnectionActiveAsyncTask>(contextHandle, request, delegate);
	return true;
}
#endif


bool PLAYFABCORE_API FPFEventsWriteEventsAsync(
	_In_ FPFEntityHandle contextHandle,
	_In_ const FPFEventsWriteEventsRequest request,
	_Inout_ FOnWriteEventsDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFEventsWriteEventsAsyncTask>(contextHandle, request, delegate);
	return true;
}


bool PLAYFABCORE_API FPFEventsWriteTelemetryEventsAsync(
	_In_ FPFEntityHandle contextHandle,
	_In_ const FPFEventsWriteEventsRequest request,
	_Inout_ FOnWriteTelemetryEventsDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFEventsWriteTelemetryEventsAsyncTask>(contextHandle, request, delegate);
	return true;
}


