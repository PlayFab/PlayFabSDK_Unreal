#include "PFInventory.h"

bool PLAYFABSERVICES_API FPFInventoryAddInventoryItemsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFInventoryAddInventoryItemsRequest* request,
	_Inout_ FOnAddInventoryItemsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FAddInventoryItemsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFInventoryDeleteInventoryCollectionAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFInventoryDeleteInventoryCollectionRequest* request,
	_Inout_ FOnDeleteInventoryCollectionCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FDeleteInventoryCollectionAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFInventoryDeleteInventoryItemsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFInventoryDeleteInventoryItemsRequest* request,
	_Inout_ FOnDeleteInventoryItemsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FDeleteInventoryItemsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFInventoryExecuteInventoryOperationsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFInventoryExecuteInventoryOperationsRequest* request,
	_Inout_ FOnExecuteInventoryOperationsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FExecuteInventoryOperationsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFInventoryExecuteTransferOperationsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFInventoryExecuteTransferOperationsRequest* request,
	_Inout_ FOnExecuteTransferOperationsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FExecuteTransferOperationsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

bool PLAYFABSERVICES_API FPFInventoryGetInventoryCollectionIdsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFInventoryGetInventoryCollectionIdsRequest* request,
	_Inout_ FOnGetInventoryCollectionIdsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FGetInventoryCollectionIdsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFInventoryGetInventoryItemsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFInventoryGetInventoryItemsRequest* request,
	_Inout_ FOnGetInventoryItemsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FGetInventoryItemsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFInventoryGetInventoryOperationStatusAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFInventoryGetInventoryOperationStatusRequest* request,
	_Inout_ FOnGetInventoryOperationStatusCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FGetInventoryOperationStatusAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFInventoryGetTransactionHistoryAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFInventoryGetTransactionHistoryRequest* request,
	_Inout_ FOnGetTransactionHistoryCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FGetTransactionHistoryAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

bool PLAYFABSERVICES_API FPFInventoryPurchaseInventoryItemsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFInventoryPurchaseInventoryItemsRequest* request,
	_Inout_ FOnPurchaseInventoryItemsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPurchaseInventoryItemsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_IOS
bool PLAYFABSERVICES_API FPFInventoryRedeemAppleAppStoreInventoryItemsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFInventoryRedeemAppleAppStoreInventoryItemsRequest* request,
	_Inout_ FOnRedeemAppleAppStoreInventoryItemsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FRedeemAppleAppStoreInventoryItemsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_ANDROID
bool PLAYFABSERVICES_API FPFInventoryRedeemGooglePlayInventoryItemsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFInventoryRedeemGooglePlayInventoryItemsRequest* request,
	_Inout_ FOnRedeemGooglePlayInventoryItemsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FRedeemGooglePlayInventoryItemsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFInventoryRedeemMicrosoftStoreInventoryItemsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFInventoryRedeemMicrosoftStoreInventoryItemsRequest* request,
	_Inout_ FOnRedeemMicrosoftStoreInventoryItemsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FRedeemMicrosoftStoreInventoryItemsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_NINTENDO_SWITCH || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFInventoryRedeemNintendoEShopInventoryItemsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFInventoryRedeemNintendoEShopInventoryItemsRequest* request,
	_Inout_ FOnRedeemNintendoEShopInventoryItemsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FRedeemNintendoEShopInventoryItemsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_4 || HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_5 || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFInventoryRedeemPlayStationStoreInventoryItemsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFInventoryRedeemPlayStationStoreInventoryItemsRequest* request,
	_Inout_ FOnRedeemPlayStationStoreInventoryItemsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FRedeemPlayStationStoreInventoryItemsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFInventoryRedeemSteamInventoryItemsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFInventoryRedeemSteamInventoryItemsRequest* request,
	_Inout_ FOnRedeemSteamInventoryItemsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FRedeemSteamInventoryItemsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

bool PLAYFABSERVICES_API FPFInventorySubtractInventoryItemsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFInventorySubtractInventoryItemsRequest* request,
	_Inout_ FOnSubtractInventoryItemsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FSubtractInventoryItemsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFInventoryTransferInventoryItemsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFInventoryTransferInventoryItemsRequest* request,
	_Inout_ FOnTransferInventoryItemsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FTransferInventoryItemsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFInventoryUpdateInventoryItemsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFInventoryUpdateInventoryItemsRequest* request,
	_Inout_ FOnUpdateInventoryItemsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FUpdateInventoryItemsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

