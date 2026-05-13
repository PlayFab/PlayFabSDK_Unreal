// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include "CoreMinimal.h"
#include "XAsyncTaskManager.h"
#include "PFInventoryAsyncTasks.h"

THIRD_PARTY_INCLUDES_START
#include <playfab/services/PFServices.h>
THIRD_PARTY_INCLUDES_END

extern "C"
{
/// <summary>
/// Add inventory items. Up to 10,000 stacks of items can be added to a single inventory collection.
/// Stack size is uncapped.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Given an entity type, entity identifier and container details, will add the specified inventory items.
///
/// When the asynchronous task is complete, call <see cref="PFInventoryAddInventoryItemsGetResultSize"/>
/// and <see cref="PFInventoryAddInventoryItemsGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFInventoryAddInventoryItemsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFInventoryAddInventoryItemsRequest* request,
	_Inout_ FOnAddInventoryItemsCompleted delegate
) noexcept;

/// <summary>
/// Delete an Inventory Collection. More information about Inventory Collections can be found here: https://learn.microsoft.com/en-us/gaming/playfab/features/economy-v2/inventory/collections
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Delete an Inventory Collection by the specified Id for an Entity.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_INVENTORY_COLLECTION_DELETION_DISALLOWED or any of the global PlayFab
/// Service errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
bool PLAYFABSERVICES_API FPFInventoryDeleteInventoryCollectionAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFInventoryDeleteInventoryCollectionRequest* request,
	_Inout_ FOnDeleteInventoryCollectionCompleted delegate
) noexcept;

/// <summary>
/// Delete inventory items
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Given an entity type, entity identifier and container details, will delete the entity's inventory
/// items.
///
/// When the asynchronous task is complete, call <see cref="PFInventoryDeleteInventoryItemsGetResultSize"/>
/// and <see cref="PFInventoryDeleteInventoryItemsGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFInventoryDeleteInventoryItemsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFInventoryDeleteInventoryItemsRequest* request,
	_Inout_ FOnDeleteInventoryItemsCompleted delegate
) noexcept;

/// <summary>
/// Execute a list of Inventory Operations. A maximum list of 50 operations can be performed by a single
/// request. There is also a limit to 300 items that can be modified/added in a single request. For example,
/// adding a bundle with 50 items counts as 50 items modified. All operations must be done within a single
/// inventory collection. This API has a reduced RPS compared to an individual inventory operation with
/// Player Entities limited to 60 requests in 90 seconds.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Execute a list of Inventory Operations for an Entity.
///
/// When the asynchronous task is complete, call <see cref="PFInventoryExecuteInventoryOperationsGetResultSize"/>
/// and <see cref="PFInventoryExecuteInventoryOperationsGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFInventoryExecuteInventoryOperationsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFInventoryExecuteInventoryOperationsRequest* request,
	_Inout_ FOnExecuteInventoryOperationsCompleted delegate
) noexcept;

/// <summary>
/// Transfer a list of inventory items. A maximum list of 50 operations can be performed by a single
/// request. When the response code is 202, one or more operations did not complete within the timeframe
/// of the request. You can identify the pending operations by looking for OperationStatus = 'InProgress'.
/// You can check on the operation status at anytime within 1 day of the request by passing the TransactionToken
/// to the GetInventoryOperationStatus API.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows.
/// Transfer the specified list of inventory items of an entity's container Id to another entity's container
/// Id.
///
/// When the asynchronous task is complete, call <see cref="PFInventoryExecuteTransferOperationsGetResultSize"/>
/// and <see cref="PFInventoryExecuteTransferOperationsGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFInventoryExecuteTransferOperationsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFInventoryExecuteTransferOperationsRequest* request,
	_Inout_ FOnExecuteTransferOperationsCompleted delegate
) noexcept;
#endif

/// <summary>
/// Get Inventory Collection Ids. Up to 50 Ids can be returned at once (or 250 with response compression
/// enabled). You can use continuation tokens to paginate through results that return greater than the
/// limit. It can take a few seconds for new collection Ids to show up.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Get a list of Inventory Collection Ids for the specified Entity.
///
/// When the asynchronous task is complete, call <see cref="PFInventoryGetInventoryCollectionIdsGetResultSize"/>
/// and <see cref="PFInventoryGetInventoryCollectionIdsGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFInventoryGetInventoryCollectionIdsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFInventoryGetInventoryCollectionIdsRequest* request,
	_Inout_ FOnGetInventoryCollectionIdsCompleted delegate
) noexcept;

/// <summary>
/// Get current inventory items.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Given an entity type, entity identifier and container details, will get the entity's inventory items.
/// .
///
/// When the asynchronous task is complete, call <see cref="PFInventoryGetInventoryItemsGetResultSize"/>
/// and <see cref="PFInventoryGetInventoryItemsGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFInventoryGetInventoryItemsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFInventoryGetInventoryItemsRequest* request,
	_Inout_ FOnGetInventoryItemsCompleted delegate
) noexcept;

/// <summary>
/// Get the status of an inventory operation using an OperationToken. You can check on the operation
/// status at anytime within 1 day of the request by passing the TransactionToken to the this API.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows.
/// Get the status of an Inventory Operation using an OperationToken.
///
/// When the asynchronous task is complete, call <see cref="PFInventoryGetInventoryOperationStatusGetResultSize"/>
/// and <see cref="PFInventoryGetInventoryOperationStatusGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFInventoryGetInventoryOperationStatusAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFInventoryGetInventoryOperationStatusRequest* request,
	_Inout_ FOnGetInventoryOperationStatusCompleted delegate
) noexcept;
#endif

/// <summary>
/// Get transaction history for a player. Up to 250 Events can be returned at once. You can use continuation
/// tokens to paginate through results that return greater than the limit. Getting transaction history
/// has a lower RPS limit than getting a Player's inventory with Player Entities having a limit of 30
/// requests in 300 seconds.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// Get transaction history for specified entity and collection.
///
/// When the asynchronous task is complete, call <see cref="PFInventoryGetTransactionHistoryGetResultSize"/>
/// and <see cref="PFInventoryGetTransactionHistoryGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFInventoryGetTransactionHistoryAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFInventoryGetTransactionHistoryRequest* request,
	_Inout_ FOnGetTransactionHistoryCompleted delegate
) noexcept;
#endif

/// <summary>
/// Purchase an item or bundle. Up to 10,000 stacks of items can be added to a single inventory collection.
/// Stack size is uncapped.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Purchase a single item or bundle, paying the associated price.
///
/// When the asynchronous task is complete, call <see cref="PFInventoryPurchaseInventoryItemsGetResultSize"/>
/// and <see cref="PFInventoryPurchaseInventoryItemsGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFInventoryPurchaseInventoryItemsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFInventoryPurchaseInventoryItemsRequest* request,
	_Inout_ FOnPurchaseInventoryItemsCompleted delegate
) noexcept;

/// <summary>
/// Redeem items.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows and iOS.
/// Redeem items from the Apple App Store.
///
/// When the asynchronous task is complete, call <see cref="PFInventoryRedeemAppleAppStoreInventoryItemsGetResultSize"/>
/// and <see cref="PFInventoryRedeemAppleAppStoreInventoryItemsGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_IOS
bool PLAYFABSERVICES_API FPFInventoryRedeemAppleAppStoreInventoryItemsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFInventoryRedeemAppleAppStoreInventoryItemsRequest* request,
	_Inout_ FOnRedeemAppleAppStoreInventoryItemsCompleted delegate
) noexcept;
#endif

/// <summary>
/// Redeem items.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows and Android.
/// Redeem items from the Google Play Store.
///
/// When the asynchronous task is complete, call <see cref="PFInventoryRedeemGooglePlayInventoryItemsGetResultSize"/>
/// and <see cref="PFInventoryRedeemGooglePlayInventoryItemsGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_ANDROID
bool PLAYFABSERVICES_API FPFInventoryRedeemGooglePlayInventoryItemsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFInventoryRedeemGooglePlayInventoryItemsRequest* request,
	_Inout_ FOnRedeemGooglePlayInventoryItemsCompleted delegate
) noexcept;
#endif

/// <summary>
/// Redeem items from the Microsoft Store. Supported entitlement types are Developer Manager Consumable
/// and Durable.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// Redeem items from the Microsoft Store.
///
/// When the asynchronous task is complete, call <see cref="PFInventoryRedeemMicrosoftStoreInventoryItemsGetResultSize"/>
/// and <see cref="PFInventoryRedeemMicrosoftStoreInventoryItemsGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFInventoryRedeemMicrosoftStoreInventoryItemsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFInventoryRedeemMicrosoftStoreInventoryItemsRequest* request,
	_Inout_ FOnRedeemMicrosoftStoreInventoryItemsCompleted delegate
) noexcept;
#endif

/// <summary>
/// Redeem items.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Nintendo Switch, Linux, and macOS.
/// Redeem items from the Nintendo EShop.
///
/// When the asynchronous task is complete, call <see cref="PFInventoryRedeemNintendoEShopInventoryItemsGetResultSize"/>
/// and <see cref="PFInventoryRedeemNintendoEShopInventoryItemsGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_NINTENDO_SWITCH || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFInventoryRedeemNintendoEShopInventoryItemsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFInventoryRedeemNintendoEShopInventoryItemsRequest* request,
	_Inout_ FOnRedeemNintendoEShopInventoryItemsCompleted delegate
) noexcept;
#endif

/// <summary>
/// Redeem items.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Sony PlayStation®, Linux, and macOS.
/// Redeem items from the PlayStation Store.
///
/// When the asynchronous task is complete, call <see cref="PFInventoryRedeemPlayStationStoreInventoryItemsGetResultSize"/>
/// and <see cref="PFInventoryRedeemPlayStationStoreInventoryItemsGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_4 || HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_5 || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFInventoryRedeemPlayStationStoreInventoryItemsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFInventoryRedeemPlayStationStoreInventoryItemsRequest* request,
	_Inout_ FOnRedeemPlayStationStoreInventoryItemsCompleted delegate
) noexcept;
#endif

/// <summary>
/// Redeem items.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// Redeem inventory items from Steam.
///
/// When the asynchronous task is complete, call <see cref="PFInventoryRedeemSteamInventoryItemsGetResultSize"/>
/// and <see cref="PFInventoryRedeemSteamInventoryItemsGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFInventoryRedeemSteamInventoryItemsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFInventoryRedeemSteamInventoryItemsRequest* request,
	_Inout_ FOnRedeemSteamInventoryItemsCompleted delegate
) noexcept;
#endif

/// <summary>
/// Subtract inventory items.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Given an entity type, entity identifier and container details, will subtract the specified inventory
/// items. .
///
/// When the asynchronous task is complete, call <see cref="PFInventorySubtractInventoryItemsGetResultSize"/>
/// and <see cref="PFInventorySubtractInventoryItemsGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFInventorySubtractInventoryItemsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFInventorySubtractInventoryItemsRequest* request,
	_Inout_ FOnSubtractInventoryItemsCompleted delegate
) noexcept;

/// <summary>
/// Transfer inventory items. When transferring across collections, a 202 response indicates that the
/// transfer did not complete within the timeframe of the request. You can identify the pending operations
/// by looking for OperationStatus = 'InProgress'. You can check on the operation status at anytime within
/// 1 day of the request by passing the TransactionToken to the GetInventoryOperationStatus API. More
/// information about item transfer scenarios can be found here: https://learn.microsoft.com/en-us/gaming/playfab/features/economy-v2/inventory/?tabs=inventory-game-manager#transfer-inventory-items
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Transfer the specified inventory items of an entity's container Id to another entity's container
/// Id.
///
/// When the asynchronous task is complete, call <see cref="PFInventoryTransferInventoryItemsGetResultSize"/>
/// and <see cref="PFInventoryTransferInventoryItemsGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFInventoryTransferInventoryItemsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFInventoryTransferInventoryItemsRequest* request,
	_Inout_ FOnTransferInventoryItemsCompleted delegate
) noexcept;

/// <summary>
/// Update inventory items
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Given an entity type, entity identifier and container details, will update the entity's inventory
/// items.
///
/// When the asynchronous task is complete, call <see cref="PFInventoryUpdateInventoryItemsGetResultSize"/>
/// and <see cref="PFInventoryUpdateInventoryItemsGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFInventoryUpdateInventoryItemsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFInventoryUpdateInventoryItemsRequest* request,
	_Inout_ FOnUpdateInventoryItemsCompleted delegate
) noexcept;

}
