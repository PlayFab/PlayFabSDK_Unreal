// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#include "CoreMinimal.h"
#include "Async/AsyncWork.h"
#include "Async/Async.h"
#include "XAsyncTaskQueueHelpers.h"
#include "XAsyncTaskManager.h"
#include "XAsyncTask.h"
#include "PFEntity.h"
#include "PFServiceConfig.h"
#include "PFInventoryUnrealTypes.h"
#include "PFInventoryTypeConverters.h"

THIRD_PARTY_INCLUDES_START
#include <playfab/services/PFServices.h>
THIRD_PARTY_INCLUDES_END


/// <summary>
/// Add inventory items. Up to 10,000 stacks of items can be added to a single inventory collection.
/// Stack size is uncapped.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Given an entity type, entity identifier and container details, will add the specified inventory items.
///
/// When the asynchronous task is complete, call <see cref="PFInventoryAddInventoryItemsGetResultSize"/>
/// and <see cref="PFInventoryAddInventoryItemsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FAddInventoryItemsAsyncTask : public FXAsyncTask
{
public:
	FAddInventoryItemsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventoryAddInventoryItemsRequest InRequest,
	const FOnAddInventoryItemsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFInventoryAddInventoryItemsRequest Request;
	
	FOnAddInventoryItemsCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Delete an Inventory Collection. More information about Inventory Collections can be found here: https://learn.microsoft.com/en-us/gaming/playfab/features/economy-v2/inventory/collections
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Delete an Inventory Collection by the specified Id for an Entity.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_INVENTORY_COLLECTION_DELETION_DISALLOWED or any of the global PlayFab
/// Service errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FDeleteInventoryCollectionAsyncTask : public FXAsyncTask
{
public:
	FDeleteInventoryCollectionAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventoryDeleteInventoryCollectionRequest InRequest,
	const FOnDeleteInventoryCollectionCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFInventoryDeleteInventoryCollectionRequest Request;
	
	FOnDeleteInventoryCollectionCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Delete inventory items
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Given an entity type, entity identifier and container details, will delete the entity's inventory
/// items.
///
/// When the asynchronous task is complete, call <see cref="PFInventoryDeleteInventoryItemsGetResultSize"/>
/// and <see cref="PFInventoryDeleteInventoryItemsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FDeleteInventoryItemsAsyncTask : public FXAsyncTask
{
public:
	FDeleteInventoryItemsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventoryDeleteInventoryItemsRequest InRequest,
	const FOnDeleteInventoryItemsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFInventoryDeleteInventoryItemsRequest Request;
	
	FOnDeleteInventoryItemsCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Execute a list of Inventory Operations. A maximum list of 50 operations can be performed by a single
/// request. There is also a limit to 300 items that can be modified/added in a single request. For example,
/// adding a bundle with 50 items counts as 50 items modified. All operations must be done within a single
/// inventory collection. This API has a reduced RPS compared to an individual inventory operation with
/// Player Entities limited to 60 requests in 90 seconds.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Execute a list of Inventory Operations for an Entity.
///
/// When the asynchronous task is complete, call <see cref="PFInventoryExecuteInventoryOperationsGetResultSize"/>
/// and <see cref="PFInventoryExecuteInventoryOperationsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FExecuteInventoryOperationsAsyncTask : public FXAsyncTask
{
public:
	FExecuteInventoryOperationsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventoryExecuteInventoryOperationsRequest InRequest,
	const FOnExecuteInventoryOperationsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFInventoryExecuteInventoryOperationsRequest Request;
	
	FOnExecuteInventoryOperationsCompleted Delegate;

	HRESULT HResult;
};


#if HC_PLATFORM == HC_PLATFORM_GDK

/// <summary>
/// Transfer a list of inventory items. A maximum list of 50 operations can be performed by a single
/// request. When the response code is 202, one or more operations did not complete within the timeframe
/// of the request. You can identify the pending operations by looking for OperationStatus = 'InProgress'.
/// You can check on the operation status at anytime within 1 day of the request by passing the TransactionToken
/// to the GetInventoryOperationStatus API.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows.
/// Transfer the specified list of inventory items of an entity's container Id to another entity's container
/// Id.
///
/// When the asynchronous task is complete, call <see cref="PFInventoryExecuteTransferOperationsGetResultSize"/>
/// and <see cref="PFInventoryExecuteTransferOperationsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FExecuteTransferOperationsAsyncTask : public FXAsyncTask
{
public:
	FExecuteTransferOperationsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventoryExecuteTransferOperationsRequest InRequest,
	const FOnExecuteTransferOperationsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFInventoryExecuteTransferOperationsRequest Request;
	
	FOnExecuteTransferOperationsCompleted Delegate;

	HRESULT HResult;
};

#endif


/// <summary>
/// Get Inventory Collection Ids. Up to 50 Ids can be returned at once (or 250 with response compression
/// enabled). You can use continuation tokens to paginate through results that return greater than the
/// limit. It can take a few seconds for new collection Ids to show up.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Get a list of Inventory Collection Ids for the specified Entity.
///
/// When the asynchronous task is complete, call <see cref="PFInventoryGetInventoryCollectionIdsGetResultSize"/>
/// and <see cref="PFInventoryGetInventoryCollectionIdsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FGetInventoryCollectionIdsAsyncTask : public FXAsyncTask
{
public:
	FGetInventoryCollectionIdsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventoryGetInventoryCollectionIdsRequest InRequest,
	const FOnGetInventoryCollectionIdsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFInventoryGetInventoryCollectionIdsRequest Request;
	
	FOnGetInventoryCollectionIdsCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Get current inventory items.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Given an entity type, entity identifier and container details, will get the entity's inventory items.
/// .
///
/// When the asynchronous task is complete, call <see cref="PFInventoryGetInventoryItemsGetResultSize"/>
/// and <see cref="PFInventoryGetInventoryItemsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FGetInventoryItemsAsyncTask : public FXAsyncTask
{
public:
	FGetInventoryItemsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventoryGetInventoryItemsRequest InRequest,
	const FOnGetInventoryItemsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFInventoryGetInventoryItemsRequest Request;
	
	FOnGetInventoryItemsCompleted Delegate;

	HRESULT HResult;
};


#if HC_PLATFORM == HC_PLATFORM_GDK

/// <summary>
/// Get the status of an inventory operation using an OperationToken. You can check on the operation
/// status at anytime within 1 day of the request by passing the TransactionToken to the this API.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows.
/// Get the status of an Inventory Operation using an OperationToken.
///
/// When the asynchronous task is complete, call <see cref="PFInventoryGetInventoryOperationStatusGetResultSize"/>
/// and <see cref="PFInventoryGetInventoryOperationStatusGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FGetInventoryOperationStatusAsyncTask : public FXAsyncTask
{
public:
	FGetInventoryOperationStatusAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventoryGetInventoryOperationStatusRequest InRequest,
	const FOnGetInventoryOperationStatusCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFInventoryGetInventoryOperationStatusRequest Request;
	
	FOnGetInventoryOperationStatusCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Gets the access tokens.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// Gets the access tokens for Microsoft Store authentication.
///
/// When the asynchronous task is complete, call <see cref="PFInventoryGetMicrosoftStoreAccessTokensGetResultSize"/>
/// and <see cref="PFInventoryGetMicrosoftStoreAccessTokensGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FGetMicrosoftStoreAccessTokensAsyncTask : public FXAsyncTask
{
public:
	FGetMicrosoftStoreAccessTokensAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventoryGetMicrosoftStoreAccessTokensRequest InRequest,
	const FOnGetMicrosoftStoreAccessTokensCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFInventoryGetMicrosoftStoreAccessTokensRequest Request;
	
	FOnGetMicrosoftStoreAccessTokensCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Get transaction history for a player. Up to 250 Events can be returned at once. You can use continuation
/// tokens to paginate through results that return greater than the limit. Getting transaction history
/// has a lower RPS limit than getting a Player's inventory with Player Entities having a limit of 30
/// requests in 300 seconds.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// Get transaction history for specified entity and collection.
///
/// When the asynchronous task is complete, call <see cref="PFInventoryGetTransactionHistoryGetResultSize"/>
/// and <see cref="PFInventoryGetTransactionHistoryGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FGetTransactionHistoryAsyncTask : public FXAsyncTask
{
public:
	FGetTransactionHistoryAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventoryGetTransactionHistoryRequest InRequest,
	const FOnGetTransactionHistoryCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFInventoryGetTransactionHistoryRequest Request;
	
	FOnGetTransactionHistoryCompleted Delegate;

	HRESULT HResult;
};

#endif


/// <summary>
/// Purchase an item or bundle. Up to 10,000 stacks of items can be added to a single inventory collection.
/// Stack size is uncapped.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Purchase a single item or bundle, paying the associated price.
///
/// When the asynchronous task is complete, call <see cref="PFInventoryPurchaseInventoryItemsGetResultSize"/>
/// and <see cref="PFInventoryPurchaseInventoryItemsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FPurchaseInventoryItemsAsyncTask : public FXAsyncTask
{
public:
	FPurchaseInventoryItemsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventoryPurchaseInventoryItemsRequest InRequest,
	const FOnPurchaseInventoryItemsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFInventoryPurchaseInventoryItemsRequest Request;
	
	FOnPurchaseInventoryItemsCompleted Delegate;

	HRESULT HResult;
};


#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_IOS

/// <summary>
/// Redeem items.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows and iOS.
/// Redeem items from the Apple App Store.
///
/// When the asynchronous task is complete, call <see cref="PFInventoryRedeemAppleAppStoreInventoryItemsGetResultSize"/>
/// and <see cref="PFInventoryRedeemAppleAppStoreInventoryItemsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FRedeemAppleAppStoreInventoryItemsAsyncTask : public FXAsyncTask
{
public:
	FRedeemAppleAppStoreInventoryItemsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventoryRedeemAppleAppStoreInventoryItemsRequest InRequest,
	const FOnRedeemAppleAppStoreInventoryItemsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFInventoryRedeemAppleAppStoreInventoryItemsRequest Request;
	
	FOnRedeemAppleAppStoreInventoryItemsCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_ANDROID

/// <summary>
/// Redeem items.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows and Android.
/// Redeem items from the Google Play Store.
///
/// When the asynchronous task is complete, call <see cref="PFInventoryRedeemGooglePlayInventoryItemsGetResultSize"/>
/// and <see cref="PFInventoryRedeemGooglePlayInventoryItemsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FRedeemGooglePlayInventoryItemsAsyncTask : public FXAsyncTask
{
public:
	FRedeemGooglePlayInventoryItemsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventoryRedeemGooglePlayInventoryItemsRequest InRequest,
	const FOnRedeemGooglePlayInventoryItemsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFInventoryRedeemGooglePlayInventoryItemsRequest Request;
	
	FOnRedeemGooglePlayInventoryItemsCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Redeem items.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// Redeem items from the Microsoft Store.
///
/// When the asynchronous task is complete, call <see cref="PFInventoryRedeemMicrosoftStoreInventoryItemsGetResultSize"/>
/// and <see cref="PFInventoryRedeemMicrosoftStoreInventoryItemsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FRedeemMicrosoftStoreInventoryItemsAsyncTask : public FXAsyncTask
{
public:
	FRedeemMicrosoftStoreInventoryItemsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventoryRedeemMicrosoftStoreInventoryItemsRequest InRequest,
	const FOnRedeemMicrosoftStoreInventoryItemsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFInventoryRedeemMicrosoftStoreInventoryItemsRequest Request;
	
	FOnRedeemMicrosoftStoreInventoryItemsCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_NINTENDO_SWITCH || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Redeem items.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Nintendo Switch, Linux, and macOS.
/// Redeem items from the Nintendo EShop.
///
/// When the asynchronous task is complete, call <see cref="PFInventoryRedeemNintendoEShopInventoryItemsGetResultSize"/>
/// and <see cref="PFInventoryRedeemNintendoEShopInventoryItemsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FRedeemNintendoEShopInventoryItemsAsyncTask : public FXAsyncTask
{
public:
	FRedeemNintendoEShopInventoryItemsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventoryRedeemNintendoEShopInventoryItemsRequest InRequest,
	const FOnRedeemNintendoEShopInventoryItemsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFInventoryRedeemNintendoEShopInventoryItemsRequest Request;
	
	FOnRedeemNintendoEShopInventoryItemsCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_4 || HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_5 || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Redeem items.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Sony PlayStation®, Linux, and macOS.
/// Redeem items from the PlayStation Store.
///
/// When the asynchronous task is complete, call <see cref="PFInventoryRedeemPlayStationStoreInventoryItemsGetResultSize"/>
/// and <see cref="PFInventoryRedeemPlayStationStoreInventoryItemsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FRedeemPlayStationStoreInventoryItemsAsyncTask : public FXAsyncTask
{
public:
	FRedeemPlayStationStoreInventoryItemsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventoryRedeemPlayStationStoreInventoryItemsRequest InRequest,
	const FOnRedeemPlayStationStoreInventoryItemsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFInventoryRedeemPlayStationStoreInventoryItemsRequest Request;
	
	FOnRedeemPlayStationStoreInventoryItemsCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Redeem items.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// Redeem inventory items from Steam.
///
/// When the asynchronous task is complete, call <see cref="PFInventoryRedeemSteamInventoryItemsGetResultSize"/>
/// and <see cref="PFInventoryRedeemSteamInventoryItemsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FRedeemSteamInventoryItemsAsyncTask : public FXAsyncTask
{
public:
	FRedeemSteamInventoryItemsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventoryRedeemSteamInventoryItemsRequest InRequest,
	const FOnRedeemSteamInventoryItemsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFInventoryRedeemSteamInventoryItemsRequest Request;
	
	FOnRedeemSteamInventoryItemsCompleted Delegate;

	HRESULT HResult;
};

#endif


/// <summary>
/// Subtract inventory items.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Given an entity type, entity identifier and container details, will subtract the specified inventory
/// items. .
///
/// When the asynchronous task is complete, call <see cref="PFInventorySubtractInventoryItemsGetResultSize"/>
/// and <see cref="PFInventorySubtractInventoryItemsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FSubtractInventoryItemsAsyncTask : public FXAsyncTask
{
public:
	FSubtractInventoryItemsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventorySubtractInventoryItemsRequest InRequest,
	const FOnSubtractInventoryItemsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFInventorySubtractInventoryItemsRequest Request;
	
	FOnSubtractInventoryItemsCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Transfer inventory items. When transferring across collections, a 202 response indicates that the
/// transfer did not complete within the timeframe of the request. You can identify the pending operations
/// by looking for OperationStatus = 'InProgress'. You can check on the operation status at anytime within
/// 1 day of the request by passing the TransactionToken to the GetInventoryOperationStatus API. More
/// information about item transfer scenarios can be found here: https://learn.microsoft.com/en-us/gaming/playfab/features/economy-v2/inventory/?tabs=inventory-game-manager#transfer-inventory-items
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Transfer the specified inventory items of an entity's container Id to another entity's container
/// Id.
///
/// When the asynchronous task is complete, call <see cref="PFInventoryTransferInventoryItemsGetResultSize"/>
/// and <see cref="PFInventoryTransferInventoryItemsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FTransferInventoryItemsAsyncTask : public FXAsyncTask
{
public:
	FTransferInventoryItemsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventoryTransferInventoryItemsRequest InRequest,
	const FOnTransferInventoryItemsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFInventoryTransferInventoryItemsRequest Request;
	
	FOnTransferInventoryItemsCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Update inventory items
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Given an entity type, entity identifier and container details, will update the entity's inventory
/// items.
///
/// When the asynchronous task is complete, call <see cref="PFInventoryUpdateInventoryItemsGetResultSize"/>
/// and <see cref="PFInventoryUpdateInventoryItemsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FUpdateInventoryItemsAsyncTask : public FXAsyncTask
{
public:
	FUpdateInventoryItemsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventoryUpdateInventoryItemsRequest InRequest,
	const FOnUpdateInventoryItemsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFInventoryUpdateInventoryItemsRequest Request;
	
	FOnUpdateInventoryItemsCompleted Delegate;

	HRESULT HResult;
};

