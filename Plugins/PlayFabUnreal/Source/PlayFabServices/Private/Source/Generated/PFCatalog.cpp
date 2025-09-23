#include "PFCatalog.h"

bool PLAYFABSERVICES_API FPFCatalogCreateDraftItemAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogCreateDraftItemRequest* request,
	_Inout_ FOnCreateDraftItemCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FCreateDraftItemAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFCatalogCreateUploadUrlsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogCreateUploadUrlsRequest* request,
	_Inout_ FOnCreateUploadUrlsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FCreateUploadUrlsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFCatalogDeleteEntityItemReviewsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogDeleteEntityItemReviewsRequest* request,
	_Inout_ FOnDeleteEntityItemReviewsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FDeleteEntityItemReviewsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

bool PLAYFABSERVICES_API FPFCatalogDeleteItemAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogDeleteItemRequest* request,
	_Inout_ FOnDeleteItemCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FDeleteItemAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFCatalogGetCatalogConfigAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogGetCatalogConfigRequest* request,
	_Inout_ FOnGetCatalogConfigCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FGetCatalogConfigAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

bool PLAYFABSERVICES_API FPFCatalogGetDraftItemAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogGetDraftItemRequest* request,
	_Inout_ FOnGetDraftItemCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FGetDraftItemAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFCatalogGetDraftItemsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogGetDraftItemsRequest* request,
	_Inout_ FOnGetDraftItemsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FGetDraftItemsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFCatalogGetEntityDraftItemsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogGetEntityDraftItemsRequest* request,
	_Inout_ FOnGetEntityDraftItemsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FGetEntityDraftItemsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFCatalogGetEntityItemReviewAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogGetEntityItemReviewRequest* request,
	_Inout_ FOnGetEntityItemReviewCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FGetEntityItemReviewAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFCatalogGetItemAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogGetItemRequest* request,
	_Inout_ FOnGetItemCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FGetItemAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFCatalogGetItemContainersAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogGetItemContainersRequest* request,
	_Inout_ FOnGetItemContainersCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FGetItemContainersAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFCatalogGetItemModerationStateAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogGetItemModerationStateRequest* request,
	_Inout_ FOnGetItemModerationStateCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FGetItemModerationStateAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

bool PLAYFABSERVICES_API FPFCatalogGetItemPublishStatusAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogGetItemPublishStatusRequest* request,
	_Inout_ FOnGetItemPublishStatusCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FGetItemPublishStatusAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFCatalogGetItemReviewsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogGetItemReviewsRequest* request,
	_Inout_ FOnGetItemReviewsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FGetItemReviewsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFCatalogGetItemReviewSummaryAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogGetItemReviewSummaryRequest* request,
	_Inout_ FOnGetItemReviewSummaryCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FGetItemReviewSummaryAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFCatalogGetItemsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogGetItemsRequest* request,
	_Inout_ FOnGetItemsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FGetItemsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFCatalogPublishDraftItemAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogPublishDraftItemRequest* request,
	_Inout_ FOnPublishDraftItemCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPublishDraftItemAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFCatalogReportItemAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogReportItemRequest* request,
	_Inout_ FOnReportItemCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FReportItemAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFCatalogReportItemReviewAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogReportItemReviewRequest* request,
	_Inout_ FOnReportItemReviewCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FReportItemReviewAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFCatalogReviewItemAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogReviewItemRequest* request,
	_Inout_ FOnReviewItemCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FReviewItemAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFCatalogSearchItemsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogSearchItemsRequest* request,
	_Inout_ FOnSearchItemsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FSearchItemsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFCatalogSetItemModerationStateAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogSetItemModerationStateRequest* request,
	_Inout_ FOnSetItemModerationStateCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FSetItemModerationStateAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

bool PLAYFABSERVICES_API FPFCatalogSubmitItemReviewVoteAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogSubmitItemReviewVoteRequest* request,
	_Inout_ FOnSubmitItemReviewVoteCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FSubmitItemReviewVoteAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFCatalogTakedownItemReviewsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogTakedownItemReviewsRequest* request,
	_Inout_ FOnTakedownItemReviewsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FTakedownItemReviewsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFCatalogUpdateCatalogConfigAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogUpdateCatalogConfigRequest* request,
	_Inout_ FOnUpdateCatalogConfigCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FUpdateCatalogConfigAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

bool PLAYFABSERVICES_API FPFCatalogUpdateDraftItemAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogUpdateDraftItemRequest* request,
	_Inout_ FOnUpdateDraftItemCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FUpdateDraftItemAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

