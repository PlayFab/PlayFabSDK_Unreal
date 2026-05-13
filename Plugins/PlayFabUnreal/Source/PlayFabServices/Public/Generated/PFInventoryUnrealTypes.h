// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once
#include "PFUnrealTypes.h"

#if defined(PF_GDK_AVAILABLE) && defined(PF_UE_GDK_SUPPORT)
#include "GDKHandle.h"
#endif

#pragma push_macro("IN")
#undef IN

/// <summary>
/// FPFInventoryAlternateId data model.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryAlternateId
{
	/// <summary>
	/// (Optional) Type of the alternate ID.
	/// </summary>
	_Maybenull_ const FString type;

	/// <summary>
	/// (Optional) Value of the alternate ID.
	/// </summary>
	_Maybenull_ const FString value;
};

/// <summary>
/// FPFInventoryInventoryItemReference data model.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryInventoryItemReference
{
	/// <summary>
	/// (Optional) The inventory item alternate id the request applies to.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFInventoryAlternateId> alternateId;

	/// <summary>
	/// (Optional) The inventory item id the request applies to.
	/// </summary>
	_Maybenull_ const FString id;

	/// <summary>
	/// (Optional) The inventory stack id the request should redeem to. (Default="default").
	/// </summary>
	_Maybenull_ const FString stackId;
};

/// <summary>
/// FPFInventoryInitialValues data model.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryInitialValues
{
	/// <summary>
	/// (Optional) Game specific properties for display purposes. The Display Properties field has a 1000
	/// byte limit.
	/// </summary>
	FPFJsonObject displayProperties;
};

/// <summary>
/// FPFInventoryAddInventoryItemsRequest data model. Given an entity type, entity identifier and container
/// details, will add the specified inventory items.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryAddInventoryItemsRequest
{
	/// <summary>
	/// (Optional) The amount to add for the current item.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> amount;

	/// <summary>
	/// (Optional) The id of the entity's collection to perform this action on. (Default="default"). The
	/// number of inventory collections is unlimited.
	/// </summary>
	_Maybenull_ const FString collectionId;

	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// (Optional) The duration to add to the current item expiration date.
	/// </summary>
	_Maybenull_ TSharedPtr<const double> durationInSeconds;

	/// <summary>
	/// (Optional) The entity to perform this action on.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) ETags are used for concurrency checking when updating resources. More information about
	/// using ETags can be found here: https://learn.microsoft.com/en-us/gaming/playfab/features/economy-v2/catalog/etags.
	/// </summary>
	_Maybenull_ const FString eTag;

	/// <summary>
	/// (Optional) The Idempotency ID for this request. Idempotency IDs can be used to prevent operation
	/// replay in the medium term but will be garbage collected eventually.
	/// </summary>
	_Maybenull_ const FString idempotencyId;

	/// <summary>
	/// (Optional) The inventory item the request applies to.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFInventoryInventoryItemReference> item;

	/// <summary>
	/// (Optional) The values to apply to a stack newly created by this request.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFInventoryInitialValues> newStackValues;
};

/// <summary>
/// FPFInventoryAddInventoryItemsResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryAddInventoryItemsResponse
{
	/// <summary>
	/// (Optional) ETags are used for concurrency checking when updating resources. More information about
	/// using ETags can be found here: https://learn.microsoft.com/en-us/gaming/playfab/features/economy-v2/catalog/etags.
	/// </summary>
	_Maybenull_ const FString eTag;

	/// <summary>
	/// (Optional) The idempotency id used in the request.
	/// </summary>
	_Maybenull_ const FString idempotencyId;

	/// <summary>
	/// (Optional) The ids of transactions that occurred as a result of the request.
	/// </summary>
	_Maybenull_ const TArray<FString> transactionIds;

	/// <summary>
	/// Count of transactionIds
	/// </summary>
	uint32 transactionIdsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFInventoryDeleteInventoryCollectionRequest data model. Delete an Inventory Collection by the specified
/// Id for an Entity.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryDeleteInventoryCollectionRequest
{
	/// <summary>
	/// (Optional) The inventory collection id the request applies to.
	/// </summary>
	_Maybenull_ const FString collectionId;

	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// (Optional) The entity the request is about. Set to the caller by default.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) ETags are used for concurrency checking when updating resources. More information about
	/// using ETags can be found here: https://learn.microsoft.com/en-us/gaming/playfab/features/economy-v2/catalog/etags.
	/// </summary>
	_Maybenull_ const FString eTag;
};

/// <summary>
/// FPFInventoryDeleteInventoryItemsRequest data model. Given an entity type, entity identifier and container
/// details, will delete the entity's inventory items.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryDeleteInventoryItemsRequest
{
	/// <summary>
	/// (Optional) The id of the entity's collection to perform this action on. (Default="default"). The
	/// number of inventory collections is unlimited.
	/// </summary>
	_Maybenull_ const FString collectionId;

	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// (Optional) The entity to perform this action on.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) ETags are used for concurrency checking when updating resources. More information about
	/// using ETags can be found here: https://learn.microsoft.com/en-us/gaming/playfab/features/economy-v2/catalog/etags.
	/// </summary>
	_Maybenull_ const FString eTag;

	/// <summary>
	/// (Optional) The Idempotency ID for this request. Idempotency IDs can be used to prevent operation
	/// replay in the medium term but will be garbage collected eventually.
	/// </summary>
	_Maybenull_ const FString idempotencyId;

	/// <summary>
	/// (Optional) The inventory item the request applies to.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFInventoryInventoryItemReference> item;
};

/// <summary>
/// FPFInventoryDeleteInventoryItemsResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryDeleteInventoryItemsResponse
{
	/// <summary>
	/// (Optional) ETags are used for concurrency checking when updating resources.
	/// </summary>
	_Maybenull_ const FString eTag;

	/// <summary>
	/// (Optional) The idempotency id used in the request.
	/// </summary>
	_Maybenull_ const FString idempotencyId;

	/// <summary>
	/// (Optional) The ids of transactions that occurred as a result of the request.
	/// </summary>
	_Maybenull_ const TArray<FString> transactionIds;

	/// <summary>
	/// Count of transactionIds
	/// </summary>
	uint32 transactionIdsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFInventoryAddInventoryItemsOperation data model.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryAddInventoryItemsOperation
{
	/// <summary>
	/// (Optional) The amount to add to the current item amount.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> amount;

	/// <summary>
	/// (Optional) The duration to add to the current item expiration date.
	/// </summary>
	_Maybenull_ TSharedPtr<const double> durationInSeconds;

	/// <summary>
	/// (Optional) The inventory item the operation applies to.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFInventoryInventoryItemReference> item;

	/// <summary>
	/// (Optional) The values to apply to a stack newly created by this operation.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFInventoryInitialValues> newStackValues;
};

/// <summary>
/// FPFInventoryDeleteInventoryItemsOperation data model.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryDeleteInventoryItemsOperation
{
	/// <summary>
	/// (Optional) The inventory item the operation applies to.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFInventoryInventoryItemReference> item;
};

/// <summary>
/// FPFInventoryPurchasePriceAmount data model.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryPurchasePriceAmount
{
	/// <summary>
	/// The amount of the inventory item to use in the purchase .
	/// </summary>
	int32 amount;

	/// <summary>
	/// (Optional) The inventory item id to use in the purchase .
	/// </summary>
	_Maybenull_ const FString itemId;

	/// <summary>
	/// (Optional) The inventory stack id the to use in the purchase. Set to "default" by default.
	/// </summary>
	_Maybenull_ const FString stackId;
};

/// <summary>
/// FPFInventoryPurchaseInventoryItemsOperation data model.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryPurchaseInventoryItemsOperation
{
	/// <summary>
	/// (Optional) The amount to purchase.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> amount;

	/// <summary>
	/// Indicates whether stacks reduced to an amount of 0 during the operation should be deleted from the
	/// inventory. (Default = false).
	/// </summary>
	bool deleteEmptyStacks;

	/// <summary>
	/// (Optional) The duration to purchase.
	/// </summary>
	_Maybenull_ TSharedPtr<const double> durationInSeconds;

	/// <summary>
	/// (Optional) The inventory item the operation applies to.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFInventoryInventoryItemReference> item;

	/// <summary>
	/// (Optional) The values to apply to a stack newly created by this operation.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFInventoryInitialValues> newStackValues;

	/// <summary>
	/// (Optional) The per-item price the item is expected to be purchased at. This must match a value configured
	/// in the Catalog or specified Store.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFInventoryPurchasePriceAmount>> priceAmounts;

	/// <summary>
	/// Count of priceAmounts
	/// </summary>
	uint32 priceAmountsCount;

	/// <summary>
	/// (Optional) The id of the Store to purchase the item from.
	/// </summary>
	_Maybenull_ const FString storeId;
};

/// <summary>
/// FPFInventorySubtractInventoryItemsOperation data model.
/// </summary>
struct PLAYFABSERVICES_API FPFInventorySubtractInventoryItemsOperation
{
	/// <summary>
	/// (Optional) The amount to subtract from the current item amount.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> amount;

	/// <summary>
	/// Indicates whether stacks reduced to an amount of 0 during the request should be deleted from the
	/// inventory. (Default = false).
	/// </summary>
	bool deleteEmptyStacks;

	/// <summary>
	/// (Optional) The duration to subtract from the current item expiration date.
	/// </summary>
	_Maybenull_ TSharedPtr<const double> durationInSeconds;

	/// <summary>
	/// (Optional) The inventory item the operation applies to.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFInventoryInventoryItemReference> item;
};

/// <summary>
/// FPFInventoryTransferInventoryItemsOperation data model.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryTransferInventoryItemsOperation
{
	/// <summary>
	/// (Optional) The amount to transfer.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> amount;

	/// <summary>
	/// Indicates whether stacks reduced to an amount of 0 during the operation should be deleted from the
	/// inventory. (Default = false).
	/// </summary>
	bool deleteEmptyStacks;

	/// <summary>
	/// (Optional) The inventory item the operation is transferring from.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFInventoryInventoryItemReference> givingItem;

	/// <summary>
	/// (Optional) The values to apply to a stack newly created by this operation.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFInventoryInitialValues> newStackValues;

	/// <summary>
	/// (Optional) The inventory item the operation is transferring to.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFInventoryInventoryItemReference> receivingItem;
};

/// <summary>
/// FPFInventoryInventoryItem data model.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryInventoryItem
{
	/// <summary>
	/// (Optional) The amount of the item.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> amount;

	/// <summary>
	/// (Optional) Game specific properties for display purposes. This is an arbitrary JSON blob. The Display
	/// Properties field has a 1000 byte limit.
	/// </summary>
	FPFJsonObject displayProperties;

	/// <summary>
	/// (Optional) Only used for subscriptions. The date of when the item will expire in UTC.
	/// </summary>
	_Maybenull_ TSharedPtr<const FDateTime> expirationDate;

	/// <summary>
	/// (Optional) The id of the item. This should correspond to the item id in the catalog.
	/// </summary>
	_Maybenull_ const FString id;

	/// <summary>
	/// (Optional) The stack id of the item.
	/// </summary>
	_Maybenull_ const FString stackId;

	/// <summary>
	/// (Optional) Only used for subscriptions. The date of when the item started in UTC.
	/// </summary>
	_Maybenull_ TSharedPtr<const FDateTime> startDate;

	/// <summary>
	/// (Optional) The type of the item. This should correspond to the item type in the catalog.
	/// </summary>
	_Maybenull_ const FString type;
};

/// <summary>
/// FPFInventoryUpdateInventoryItemsOperation data model.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryUpdateInventoryItemsOperation
{
	/// <summary>
	/// (Optional) The inventory item to update with the specified values.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFInventoryInventoryItem> item;
};

/// <summary>
/// FPFInventoryInventoryOperation data model.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryInventoryOperation
{
	/// <summary>
	/// (Optional) The add operation.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFInventoryAddInventoryItemsOperation> add;

	/// <summary>
	/// (Optional) The delete operation.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFInventoryDeleteInventoryItemsOperation> deleteOp;

	/// <summary>
	/// (Optional) The purchase operation.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFInventoryPurchaseInventoryItemsOperation> purchase;

	/// <summary>
	/// (Optional) The subtract operation.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFInventorySubtractInventoryItemsOperation> subtract;

	/// <summary>
	/// (Optional) The transfer operation.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFInventoryTransferInventoryItemsOperation> transfer;

	/// <summary>
	/// (Optional) The update operation.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFInventoryUpdateInventoryItemsOperation> update;
};

/// <summary>
/// FPFInventoryExecuteInventoryOperationsRequest data model. Execute a list of Inventory Operations
/// for an Entity.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryExecuteInventoryOperationsRequest
{
	/// <summary>
	/// (Optional) The id of the entity's collection to perform this action on. (Default="default"). The
	/// number of inventory collections is unlimited.
	/// </summary>
	_Maybenull_ const FString collectionId;

	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// (Optional) The entity to perform this action on.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) ETags are used for concurrency checking when updating resources. More information about
	/// using ETags can be found here: https://learn.microsoft.com/en-us/gaming/playfab/features/economy-v2/catalog/etags.
	/// </summary>
	_Maybenull_ const FString eTag;

	/// <summary>
	/// (Optional) The Idempotency ID for this request. Idempotency IDs can be used to prevent operation
	/// replay in the medium term but will be garbage collected eventually.
	/// </summary>
	_Maybenull_ const FString idempotencyId;

	/// <summary>
	/// (Optional) The operations to run transactionally. The operations will be executed in-order sequentially
	/// and will succeed or fail as a batch. Up to 50 operations can be added.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFInventoryInventoryOperation>> operations;

	/// <summary>
	/// Count of operations
	/// </summary>
	uint32 operationsCount;
};

/// <summary>
/// FPFInventoryExecuteInventoryOperationsResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryExecuteInventoryOperationsResponse
{
	/// <summary>
	/// (Optional) ETags are used for concurrency checking when updating resources. More information about
	/// using ETags can be found here: https://learn.microsoft.com/en-us/gaming/playfab/features/economy-v2/catalog/etags.
	/// </summary>
	_Maybenull_ const FString eTag;

	/// <summary>
	/// (Optional) The idempotency id used in the request.
	/// </summary>
	_Maybenull_ const FString idempotencyId;

	/// <summary>
	/// (Optional) The ids of the transactions that occurred as a result of the request.
	/// </summary>
	_Maybenull_ const TArray<FString> transactionIds;

	/// <summary>
	/// Count of transactionIds
	/// </summary>
	uint32 transactionIdsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFInventoryExecuteTransferOperationsRequest data model. Transfer the specified list of inventory
/// items of an entity's container Id to another entity's container Id.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryExecuteTransferOperationsRequest
{
	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// (Optional) The inventory collection id the request is transferring from. (Default="default").
	/// </summary>
	_Maybenull_ const FString givingCollectionId;

	/// <summary>
	/// (Optional) The entity the request is transferring from. Set to the caller by default.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> givingEntity;

	/// <summary>
	/// (Optional) ETags are used for concurrency checking when updating resources. More information about
	/// using ETags can be found here: https://learn.microsoft.com/en-us/gaming/playfab/features/economy-v2/catalog/etags.
	/// </summary>
	_Maybenull_ const FString givingETag;

	/// <summary>
	/// (Optional) The idempotency id for the request.
	/// </summary>
	_Maybenull_ const FString idempotencyId;

	/// <summary>
	/// (Optional) The transfer operations to run transactionally. The operations will be executed in-order
	/// sequentially and will succeed or fail as a batch. Up to 50 operations can be added.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFInventoryTransferInventoryItemsOperation>> operations;

	/// <summary>
	/// Count of operations
	/// </summary>
	uint32 operationsCount;

	/// <summary>
	/// (Optional) The inventory collection id the request is transferring to. (Default="default").
	/// </summary>
	_Maybenull_ const FString receivingCollectionId;

	/// <summary>
	/// (Optional) The entity the request is transferring to. Set to the caller by default.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> receivingEntity;
};

/// <summary>
/// FPFInventoryExecuteTransferOperationsResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryExecuteTransferOperationsResponse
{
	/// <summary>
	/// (Optional) ETags are used for concurrency checking when updating resources (before transferring
	/// from). This value will be empty if the operation has not completed yet. More information about using
	/// ETags can be found here: https://learn.microsoft.com/en-us/gaming/playfab/features/economy-v2/catalog/etags.
	/// </summary>
	_Maybenull_ const FString givingETag;

	/// <summary>
	/// (Optional) The ids of transactions that occurred as a result of the request's giving action.
	/// </summary>
	_Maybenull_ const TArray<FString> givingTransactionIds;

	/// <summary>
	/// Count of givingTransactionIds
	/// </summary>
	uint32 givingTransactionIdsCount;

	/// <summary>
	/// (Optional) The Idempotency ID for this request.
	/// </summary>
	_Maybenull_ const FString idempotencyId;

	/// <summary>
	/// (Optional) The transfer operation status. Possible values are 'InProgress' or 'Completed'. If the
	/// operation has completed, the response code will be 200. Otherwise, it will be 202.
	/// </summary>
	_Maybenull_ const FString operationStatus;

	/// <summary>
	/// (Optional) The token that can be used to get the status of the transfer operation. This will only
	/// have a value if OperationStatus is 'InProgress'.
	/// </summary>
	_Maybenull_ const FString operationToken;

	/// <summary>
	/// (Optional) ETags are used for concurrency checking when updating resources (before transferring
	/// to). This value will be empty if the operation has not completed yet.
	/// </summary>
	_Maybenull_ const FString receivingETag;

	/// <summary>
	/// (Optional) The ids of transactions that occurred as a result of the request's receiving action.
	/// </summary>
	_Maybenull_ const TArray<FString> receivingTransactionIds;

	/// <summary>
	/// Count of receivingTransactionIds
	/// </summary>
	uint32 receivingTransactionIdsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFInventoryGetInventoryCollectionIdsRequest data model. Get a list of Inventory Collection Ids for
/// the specified Entity.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryGetInventoryCollectionIdsRequest
{
	/// <summary>
	/// (Optional) An opaque token used to retrieve the next page of collection ids, if any are available.
	/// </summary>
	_Maybenull_ const FString continuationToken;

	/// <summary>
	/// Number of items to retrieve. This value is optional. The default value is 10.
	/// </summary>
	int32 count;

	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// (Optional) The entity the request is about. Set to the caller by default.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;
};

/// <summary>
/// FPFInventoryGetInventoryCollectionIdsResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryGetInventoryCollectionIdsResponse
{
	/// <summary>
	/// (Optional) The requested inventory collection ids.
	/// </summary>
	_Maybenull_ const TArray<FString> collectionIds;

	/// <summary>
	/// Count of collectionIds
	/// </summary>
	uint32 collectionIdsCount;

	/// <summary>
	/// (Optional) An opaque token used to retrieve the next page of collection ids, if any are available.
	/// </summary>
	_Maybenull_ const FString continuationToken;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFInventoryGetInventoryItemsRequest data model. Given an entity type, entity identifier and container
/// details, will get the entity's inventory items. .
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryGetInventoryItemsRequest
{
	/// <summary>
	/// (Optional) The id of the entity's collection to perform this action on. (Default="default").
	/// </summary>
	_Maybenull_ const FString collectionId;

	/// <summary>
	/// (Optional) An opaque token used to retrieve the next page of items in the inventory, if any are
	/// available. Should be null on initial request.
	/// </summary>
	_Maybenull_ const FString continuationToken;

	/// <summary>
	/// Number of items to retrieve. This value is optional. Maximum page size is 50. The default value
	/// is 10.
	/// </summary>
	int32 count;

	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// (Optional) The entity to perform this action on.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) OData Filter to refine the items returned. InventoryItem properties 'type', 'id', and
	/// 'stackId' can be used in the filter. For example: "type eq 'currency'".
	/// </summary>
	_Maybenull_ const FString filter;
};

/// <summary>
/// FPFInventoryGetInventoryItemsResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryGetInventoryItemsResponse
{
	/// <summary>
	/// (Optional) An opaque token used to retrieve the next page of items, if any are available.
	/// </summary>
	_Maybenull_ const FString continuationToken;

	/// <summary>
	/// (Optional) ETags are used for concurrency checking when updating resources. More information about
	/// using ETags can be found here: https://learn.microsoft.com/en-us/gaming/playfab/features/economy-v2/catalog/etags.
	/// </summary>
	_Maybenull_ const FString eTag;

	/// <summary>
	/// (Optional) The requested inventory items.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFInventoryInventoryItem>> items;

	/// <summary>
	/// Count of items
	/// </summary>
	uint32 itemsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFInventoryGetInventoryOperationStatusRequest data model. Get the status of an Inventory Operation
/// using an OperationToken.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryGetInventoryOperationStatusRequest
{
	/// <summary>
	/// (Optional) The id of the entity's collection to perform this action on. (Default="default").
	/// </summary>
	_Maybenull_ const FString collectionId;

	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// (Optional) The entity to perform this action on.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) The token to get the status of the inventory operation.
	/// </summary>
	_Maybenull_ const FString operationToken;
};

/// <summary>
/// FPFInventoryGetInventoryOperationStatusResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryGetInventoryOperationStatusResponse
{
	/// <summary>
	/// (Optional) The inventory operation status.
	/// </summary>
	_Maybenull_ const FString operationStatus;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFInventoryGetTransactionHistoryRequest data model. Get transaction history for specified entity
/// and collection.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryGetTransactionHistoryRequest
{
	/// <summary>
	/// (Optional) The id of the entity's collection to perform this action on. (Default="default").
	/// </summary>
	_Maybenull_ const FString collectionId;

	/// <summary>
	/// (Optional) An opaque token used to retrieve the next page of items, if any are available. Should
	/// be null on initial request.
	/// </summary>
	_Maybenull_ const FString continuationToken;

	/// <summary>
	/// Number of items to retrieve. This value is optional. The default value is 10.
	/// </summary>
	int32 count;

	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// (Optional) The entity to perform this action on.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) An OData filter used to refine the TransactionHistory. Transaction properties 'timestamp',
	/// 'transactionid', 'apiname' and 'operationtype' can be used in the filter. Properties 'transactionid',
	/// 'apiname', and 'operationtype' cannot be used together in a single request. The 'timestamp' property
	/// can be combined with 'apiname' or 'operationtype' in a single request. For example: "timestamp ge
	/// 2023-06-20T23:30Z" or "transactionid eq '10'" or "(timestamp ge 2023-06-20T23:30Z) and (apiname eq
	/// 'AddInventoryItems')". By default, a 6 month timespan from the current date is used.
	/// </summary>
	_Maybenull_ const FString filter;

	/// <summary>
	/// (Optional) An OData orderby to order TransactionHistory results. The only supported values are 'timestamp
	/// asc' or 'timestamp desc'. Default orderby is 'timestamp asc'.
	/// </summary>
	_Maybenull_ const FString orderBy;
};

/// <summary>
/// FPFInventoryTransactionClawbackDetails data model.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryTransactionClawbackDetails
{
	/// <summary>
	/// (Optional) The id of the clawed back operation.
	/// </summary>
	_Maybenull_ const FString transactionIdClawedback;
};

/// <summary>
/// FPFInventoryTransactionOperation data model.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryTransactionOperation
{
	/// <summary>
	/// (Optional) The amount of items in this transaction.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> amount;

	/// <summary>
	/// (Optional) The duration modified in this transaction.
	/// </summary>
	_Maybenull_ TSharedPtr<const double> durationInSeconds;

	/// <summary>
	/// (Optional) The friendly id of the items in this transaction.
	/// </summary>
	_Maybenull_ const FString itemFriendlyId;

	/// <summary>
	/// (Optional) The item id of the items in this transaction.
	/// </summary>
	_Maybenull_ const FString itemId;

	/// <summary>
	/// (Optional) The type of item that the operation occurred on.
	/// </summary>
	_Maybenull_ const FString itemType;

	/// <summary>
	/// (Optional) The stack id of the items in this transaction.
	/// </summary>
	_Maybenull_ const FString stackId;

	/// <summary>
	/// (Optional) The type of the operation that occurred.
	/// </summary>
	_Maybenull_ const FString type;
};

/// <summary>
/// FPFInventoryTransactionPurchaseDetails data model.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryTransactionPurchaseDetails
{
	/// <summary>
	/// (Optional) The friendly id of the item that was purchased.
	/// </summary>
	_Maybenull_ const FString itemFriendlyId;

	/// <summary>
	/// (Optional) The id of the item that was purchased.
	/// </summary>
	_Maybenull_ const FString itemId;

	/// <summary>
	/// (Optional) The friendly id of the Store the item was purchased from or null.
	/// </summary>
	_Maybenull_ const FString storeFriendlyId;

	/// <summary>
	/// (Optional) The id of the Store the item was purchased from or null.
	/// </summary>
	_Maybenull_ const FString storeId;
};

/// <summary>
/// FPFInventoryTransactionRedeemDetails data model.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryTransactionRedeemDetails
{
	/// <summary>
	/// (Optional) The marketplace that the offer is being redeemed from.
	/// </summary>
	_Maybenull_ const FString marketplace;

	/// <summary>
	/// (Optional) The transaction Id returned from the marketplace.
	/// </summary>
	_Maybenull_ const FString marketplaceTransactionId;

	/// <summary>
	/// (Optional) The offer Id of the item being redeemed.
	/// </summary>
	_Maybenull_ const FString offerId;
};

/// <summary>
/// FPFInventoryTransactionTransferDetails data model.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryTransactionTransferDetails
{
	/// <summary>
	/// (Optional) The collection id the items were transferred from or null if it was the current collection.
	/// </summary>
	_Maybenull_ const FString givingCollectionId;

	/// <summary>
	/// (Optional) The entity the items were transferred from or null if it was the current entity.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> givingEntity;

	/// <summary>
	/// (Optional) The collection id the items were transferred to or null if it was the current collection.
	/// </summary>
	_Maybenull_ const FString receivingCollectionId;

	/// <summary>
	/// (Optional) The entity the items were transferred to or null if it was the current entity.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> receivingEntity;

	/// <summary>
	/// (Optional) The id of the transfer that occurred.
	/// </summary>
	_Maybenull_ const FString transferId;
};

/// <summary>
/// FPFInventoryTransaction data model.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryTransaction
{
	/// <summary>
	/// (Optional) The API call that caused this transaction.
	/// </summary>
	_Maybenull_ const FString apiName;

	/// <summary>
	/// (Optional) Additional details about the transaction. Null if it was not a clawback operation.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFInventoryTransactionClawbackDetails> clawbackDetails;

	/// <summary>
	/// (Optional) The custom tags associated with this transactions.
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// (Optional) The type of item that the the operation occurred on.
	/// </summary>
	_Maybenull_ const FString itemType;

	/// <summary>
	/// (Optional) The operations that occurred.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFInventoryTransactionOperation>> operations;

	/// <summary>
	/// Count of operations
	/// </summary>
	uint32 operationsCount;

	/// <summary>
	/// (Optional) The type of operation that was run.
	/// </summary>
	_Maybenull_ const FString operationType;

	/// <summary>
	/// (Optional) Additional details about the transaction. Null if it was not a purchase operation.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFInventoryTransactionPurchaseDetails> purchaseDetails;

	/// <summary>
	/// (Optional) Additional details about the transaction. Null if it was not a redeem operation.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFInventoryTransactionRedeemDetails> redeemDetails;

	/// <summary>
	/// The time this transaction occurred in UTC.
	/// </summary>
	FDateTime timestamp;

	/// <summary>
	/// (Optional) The id of the transaction. This should be treated like an opaque token.
	/// </summary>
	_Maybenull_ const FString transactionId;

	/// <summary>
	/// (Optional) Additional details about the transaction. Null if it was not a transfer operation.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFInventoryTransactionTransferDetails> transferDetails;
};

/// <summary>
/// FPFInventoryGetTransactionHistoryResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryGetTransactionHistoryResponse
{
	/// <summary>
	/// (Optional) An opaque token used to retrieve the next page of items, if any are available. Should
	/// be null on initial request.
	/// </summary>
	_Maybenull_ const FString continuationToken;

	/// <summary>
	/// (Optional) The requested inventory transactions.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFInventoryTransaction>> transactions;

	/// <summary>
	/// Count of transactions
	/// </summary>
	uint32 transactionsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFInventoryPurchaseInventoryItemsRequest data model. Purchase a single item or bundle, paying the
/// associated price.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryPurchaseInventoryItemsRequest
{
	/// <summary>
	/// (Optional) The amount to purchase.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> amount;

	/// <summary>
	/// (Optional) The id of the entity's collection to perform this action on. (Default="default"). The
	/// number of inventory collections is unlimited.
	/// </summary>
	_Maybenull_ const FString collectionId;

	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// Indicates whether stacks reduced to an amount of 0 during the request should be deleted from the
	/// inventory. (Default=false).
	/// </summary>
	bool deleteEmptyStacks;

	/// <summary>
	/// (Optional) The duration to purchase.
	/// </summary>
	_Maybenull_ TSharedPtr<const double> durationInSeconds;

	/// <summary>
	/// (Optional) The entity to perform this action on.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) ETags are used for concurrency checking when updating resources. More information about
	/// using ETags can be found here: https://learn.microsoft.com/en-us/gaming/playfab/features/economy-v2/catalog/etags.
	/// </summary>
	_Maybenull_ const FString eTag;

	/// <summary>
	/// (Optional) The Idempotency ID for this request. Idempotency IDs can be used to prevent operation
	/// replay in the medium term but will be garbage collected eventually.
	/// </summary>
	_Maybenull_ const FString idempotencyId;

	/// <summary>
	/// (Optional) The inventory item the request applies to.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFInventoryInventoryItemReference> item;

	/// <summary>
	/// (Optional) The values to apply to a stack newly created by this request.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFInventoryInitialValues> newStackValues;

	/// <summary>
	/// (Optional) The per-item price the item is expected to be purchased at. This must match a value configured
	/// in the Catalog or specified Store. .
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFInventoryPurchasePriceAmount>> priceAmounts;

	/// <summary>
	/// Count of priceAmounts
	/// </summary>
	uint32 priceAmountsCount;

	/// <summary>
	/// (Optional) The id of the Store to purchase the item from.
	/// </summary>
	_Maybenull_ const FString storeId;
};

/// <summary>
/// FPFInventoryPurchaseInventoryItemsResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryPurchaseInventoryItemsResponse
{
	/// <summary>
	/// (Optional) ETags are used for concurrency checking when updating resources. More information about
	/// using ETags can be found here: https://learn.microsoft.com/en-us/gaming/playfab/features/economy-v2/catalog/etags.
	/// </summary>
	_Maybenull_ const FString eTag;

	/// <summary>
	/// (Optional) The idempotency id used in the request.
	/// </summary>
	_Maybenull_ const FString idempotencyId;

	/// <summary>
	/// (Optional) The ids of transactions that occurred as a result of the request.
	/// </summary>
	_Maybenull_ const TArray<FString> transactionIds;

	/// <summary>
	/// Count of transactionIds
	/// </summary>
	uint32 transactionIdsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFInventoryRedeemAppleAppStoreInventoryItemsRequest data model. Redeem items from the Apple App
/// Store.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryRedeemAppleAppStoreInventoryItemsRequest
{
	/// <summary>
	/// (Optional) The id of the entity's collection to perform this action on. (Default="default").
	/// </summary>
	_Maybenull_ const FString collectionId;

	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// (Optional) The entity to perform this action on.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) The receipt provided by the Apple marketplace upon successful purchase.
	/// </summary>
	_Maybenull_ const FString receipt;
};

/// <summary>
/// FPFInventoryRedemptionFailure data model.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryRedemptionFailure
{
	/// <summary>
	/// (Optional) The marketplace failure code.
	/// </summary>
	_Maybenull_ const FString failureCode;

	/// <summary>
	/// (Optional) The marketplace error details explaining why the offer failed to redeem.
	/// </summary>
	_Maybenull_ const FString failureDetails;

	/// <summary>
	/// (Optional) The Marketplace Alternate ID being redeemed.
	/// </summary>
	_Maybenull_ const FString marketplaceAlternateId;

	/// <summary>
	/// (Optional) The transaction id in the external marketplace.
	/// </summary>
	_Maybenull_ const FString marketplaceTransactionId;
};

/// <summary>
/// FPFInventoryRedemptionSuccess data model.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryRedemptionSuccess
{
	/// <summary>
	/// (Optional) The timestamp for when the redeem expired.
	/// </summary>
	_Maybenull_ TSharedPtr<const FDateTime> expirationTimestamp;

	/// <summary>
	/// (Optional) The Marketplace Alternate ID being redeemed.
	/// </summary>
	_Maybenull_ const FString marketplaceAlternateId;

	/// <summary>
	/// (Optional) The transaction id in the external marketplace.
	/// </summary>
	_Maybenull_ const FString marketplaceTransactionId;

	/// <summary>
	/// The timestamp for when the redeem was completed.
	/// </summary>
	FDateTime successTimestamp;
};

/// <summary>
/// FPFInventoryRedeemAppleAppStoreInventoryItemsResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryRedeemAppleAppStoreInventoryItemsResponse
{
	/// <summary>
	/// (Optional) The list of failed redemptions from the external marketplace.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFInventoryRedemptionFailure>> failed;

	/// <summary>
	/// Count of failed
	/// </summary>
	uint32 failedCount;

	/// <summary>
	/// (Optional) The list of successful redemptions from the external marketplace.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFInventoryRedemptionSuccess>> succeeded;

	/// <summary>
	/// Count of succeeded
	/// </summary>
	uint32 succeededCount;

	/// <summary>
	/// (Optional) The Transaction IDs associated with the inventory modifications.
	/// </summary>
	_Maybenull_ const TArray<FString> transactionIds;

	/// <summary>
	/// Count of transactionIds
	/// </summary>
	uint32 transactionIdsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFInventoryGooglePlayProductPurchase data model.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryGooglePlayProductPurchase
{
	/// <summary>
	/// (Optional) The Product ID (SKU) of the InApp product purchased from the Google Play store.
	/// </summary>
	_Maybenull_ const FString productId;

	/// <summary>
	/// (Optional) The token provided to the player's device when the product was purchased.
	/// </summary>
	_Maybenull_ const FString token;
};

/// <summary>
/// FPFInventoryRedeemGooglePlayInventoryItemsRequest data model. Redeem items from the Google Play Store.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryRedeemGooglePlayInventoryItemsRequest
{
	/// <summary>
	/// (Optional) The id of the entity's collection to perform this action on. (Default="default").
	/// </summary>
	_Maybenull_ const FString collectionId;

	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// (Optional) The entity to perform this action on.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) The list of purchases to redeem.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFInventoryGooglePlayProductPurchase>> purchases;

	/// <summary>
	/// Count of purchases
	/// </summary>
	uint32 purchasesCount;
};

/// <summary>
/// FPFInventoryRedeemGooglePlayInventoryItemsResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryRedeemGooglePlayInventoryItemsResponse
{
	/// <summary>
	/// (Optional) The list of failed redemptions from the external marketplace.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFInventoryRedemptionFailure>> failed;

	/// <summary>
	/// Count of failed
	/// </summary>
	uint32 failedCount;

	/// <summary>
	/// (Optional) The list of successful redemptions from the external marketplace.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFInventoryRedemptionSuccess>> succeeded;

	/// <summary>
	/// Count of succeeded
	/// </summary>
	uint32 succeededCount;

	/// <summary>
	/// (Optional) The Transaction IDs associated with the inventory modifications.
	/// </summary>
	_Maybenull_ const TArray<FString> transactionIds;

	/// <summary>
	/// Count of transactionIds
	/// </summary>
	uint32 transactionIdsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFInventoryRedeemMicrosoftStoreInventoryItemsRequest data model. Redeem items from the Microsoft
/// Store.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryRedeemMicrosoftStoreInventoryItemsRequest
{
	/// <summary>
	/// (Optional) The id of the entity's collection to perform this action on. (Default="default").
	/// </summary>
	_Maybenull_ const FString collectionId;

	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// (Optional) The entity to perform this action on.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

#if defined(PF_GDK_AVAILABLE) && defined(PF_UE_GDK_SUPPORT)
	/// <summary>
	/// FGDKUserHandle used for delegated Microsoft Store authentication.
	/// </summary>
	FGDKUserHandle user;
#elif defined(PF_GDK_AVAILABLE)
    /// <summary>
    /// XUserHandle used for delegated Microsoft Store authentication.
    /// </summary>
    XUserHandle user;
#else
	/// <summary>
	/// (Optional) Xbox Token used for delegated business partner authentication. Token provided by the
	/// Xbox Live SDK method GetTokenAndSignatureAsync("POST", "https://playfabapi.com/", "").
	/// </summary>
	_Maybenull_ const FString xboxToken;
#endif
};

/// <summary>
/// FPFInventoryRedeemMicrosoftStoreInventoryItemsResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryRedeemMicrosoftStoreInventoryItemsResponse
{
	/// <summary>
	/// (Optional) The list of failed redemptions from the external marketplace.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFInventoryRedemptionFailure>> failed;

	/// <summary>
	/// Count of failed
	/// </summary>
	uint32 failedCount;

	/// <summary>
	/// (Optional) The list of successful redemptions from the external marketplace.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFInventoryRedemptionSuccess>> succeeded;

	/// <summary>
	/// Count of succeeded
	/// </summary>
	uint32 succeededCount;

	/// <summary>
	/// (Optional) The Transaction IDs associated with the inventory modifications.
	/// </summary>
	_Maybenull_ const TArray<FString> transactionIds;

	/// <summary>
	/// Count of transactionIds
	/// </summary>
	uint32 transactionIdsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFInventoryRedeemNintendoEShopInventoryItemsRequest data model. Redeem items from the Nintendo EShop.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryRedeemNintendoEShopInventoryItemsRequest
{
	/// <summary>
	/// (Optional) The id of the entity's collection to perform this action on. (Default="default").
	/// </summary>
	_Maybenull_ const FString collectionId;

	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// (Optional) The entity to perform this action on.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) The Nintendo provided token authorizing redemption.
	/// </summary>
	_Maybenull_ const FString nintendoServiceAccountIdToken;
};

/// <summary>
/// FPFInventoryRedeemNintendoEShopInventoryItemsResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryRedeemNintendoEShopInventoryItemsResponse
{
	/// <summary>
	/// (Optional) The list of failed redemptions from the external marketplace.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFInventoryRedemptionFailure>> failed;

	/// <summary>
	/// Count of failed
	/// </summary>
	uint32 failedCount;

	/// <summary>
	/// (Optional) The list of successful redemptions from the external marketplace.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFInventoryRedemptionSuccess>> succeeded;

	/// <summary>
	/// Count of succeeded
	/// </summary>
	uint32 succeededCount;

	/// <summary>
	/// (Optional) The Transaction IDs associated with the inventory modifications.
	/// </summary>
	_Maybenull_ const TArray<FString> transactionIds;

	/// <summary>
	/// Count of transactionIds
	/// </summary>
	uint32 transactionIdsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFInventoryRedeemPlayStationStoreInventoryItemsRequest data model. Redeem items from the PlayStation
/// Store.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryRedeemPlayStationStoreInventoryItemsRequest
{
	/// <summary>
	/// (Optional) Auth code returned by PlayStation :tm: Network OAuth system.
	/// </summary>
	_Maybenull_ const FString authorizationCode;

	/// <summary>
	/// (Optional) The id of the entity's collection to perform this action on. (Default="default").
	/// </summary>
	_Maybenull_ const FString collectionId;

	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// (Optional) The entity to perform this action on.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) Redirect URI supplied to PlayStation :tm: Network when requesting an auth code.
	/// </summary>
	_Maybenull_ const FString redirectUri;

	/// <summary>
	/// (Optional) Optional Service Label to pass into the request.
	/// </summary>
	_Maybenull_ const FString serviceLabel;
};

/// <summary>
/// FPFInventoryRedeemPlayStationStoreInventoryItemsResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryRedeemPlayStationStoreInventoryItemsResponse
{
	/// <summary>
	/// (Optional) The list of failed redemptions from the external marketplace.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFInventoryRedemptionFailure>> failed;

	/// <summary>
	/// Count of failed
	/// </summary>
	uint32 failedCount;

	/// <summary>
	/// (Optional) The list of successful redemptions from the external marketplace.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFInventoryRedemptionSuccess>> succeeded;

	/// <summary>
	/// Count of succeeded
	/// </summary>
	uint32 succeededCount;

	/// <summary>
	/// (Optional) The Transaction IDs associated with the inventory modifications.
	/// </summary>
	_Maybenull_ const TArray<FString> transactionIds;

	/// <summary>
	/// Count of transactionIds
	/// </summary>
	uint32 transactionIdsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFInventoryRedeemSteamInventoryItemsRequest data model. Redeem inventory items from Steam.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryRedeemSteamInventoryItemsRequest
{
	/// <summary>
	/// (Optional) The id of the entity's collection to perform this action on. (Default="default").
	/// </summary>
	_Maybenull_ const FString collectionId;

	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// (Optional) The entity to perform this action on.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;
};

/// <summary>
/// FPFInventoryRedeemSteamInventoryItemsResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryRedeemSteamInventoryItemsResponse
{
	/// <summary>
	/// (Optional) The list of failed redemptions from the external marketplace.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFInventoryRedemptionFailure>> failed;

	/// <summary>
	/// Count of failed
	/// </summary>
	uint32 failedCount;

	/// <summary>
	/// (Optional) The list of successful redemptions from the external marketplace.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFInventoryRedemptionSuccess>> succeeded;

	/// <summary>
	/// Count of succeeded
	/// </summary>
	uint32 succeededCount;

	/// <summary>
	/// (Optional) The Transaction IDs associated with the inventory modifications.
	/// </summary>
	_Maybenull_ const TArray<FString> transactionIds;

	/// <summary>
	/// Count of transactionIds
	/// </summary>
	uint32 transactionIdsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFInventorySubtractInventoryItemsRequest data model. Given an entity type, entity identifier and
/// container details, will subtract the specified inventory items. .
/// </summary>
struct PLAYFABSERVICES_API FPFInventorySubtractInventoryItemsRequest
{
	/// <summary>
	/// (Optional) The amount to subtract for the current item.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> amount;

	/// <summary>
	/// (Optional) The id of the entity's collection to perform this action on. (Default="default"). The
	/// number of inventory collections is unlimited.
	/// </summary>
	_Maybenull_ const FString collectionId;

	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// Indicates whether stacks reduced to an amount of 0 during the request should be deleted from the
	/// inventory. (Default=false).
	/// </summary>
	bool deleteEmptyStacks;

	/// <summary>
	/// (Optional) The duration to subtract from the current item expiration date.
	/// </summary>
	_Maybenull_ TSharedPtr<const double> durationInSeconds;

	/// <summary>
	/// (Optional) The entity to perform this action on.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) ETags are used for concurrency checking when updating resources. More information about
	/// using ETags can be found here: https://learn.microsoft.com/en-us/gaming/playfab/features/economy-v2/catalog/etags.
	/// </summary>
	_Maybenull_ const FString eTag;

	/// <summary>
	/// (Optional) The Idempotency ID for this request. Idempotency IDs can be used to prevent operation
	/// replay in the medium term but will be garbage collected eventually.
	/// </summary>
	_Maybenull_ const FString idempotencyId;

	/// <summary>
	/// (Optional) The inventory item the request applies to.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFInventoryInventoryItemReference> item;
};

/// <summary>
/// FPFInventorySubtractInventoryItemsResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFInventorySubtractInventoryItemsResponse
{
	/// <summary>
	/// (Optional) ETags are used for concurrency checking when updating resources. More information about
	/// using ETags can be found here: https://learn.microsoft.com/en-us/gaming/playfab/features/economy-v2/catalog/etags.
	/// </summary>
	_Maybenull_ const FString eTag;

	/// <summary>
	/// (Optional) The idempotency id used in the request.
	/// </summary>
	_Maybenull_ const FString idempotencyId;

	/// <summary>
	/// (Optional) The ids of transactions that occurred as a result of the request.
	/// </summary>
	_Maybenull_ const TArray<FString> transactionIds;

	/// <summary>
	/// Count of transactionIds
	/// </summary>
	uint32 transactionIdsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFInventoryTransferInventoryItemsRequest data model. Transfer the specified inventory items of an
/// entity's container Id to another entity's container Id.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryTransferInventoryItemsRequest
{
	/// <summary>
	/// (Optional) The amount to transfer .
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> amount;

	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// Indicates whether stacks reduced to an amount of 0 during the request should be deleted from the
	/// inventory. (Default = false).
	/// </summary>
	bool deleteEmptyStacks;

	/// <summary>
	/// (Optional) The inventory collection id the request is transferring from. (Default="default").
	/// </summary>
	_Maybenull_ const FString givingCollectionId;

	/// <summary>
	/// (Optional) The entity the request is transferring from. Set to the caller by default.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> givingEntity;

	/// <summary>
	/// (Optional) ETags are used for concurrency checking when updating resources (before transferring
	/// from). More information about using ETags can be found here: https://learn.microsoft.com/en-us/gaming/playfab/features/economy-v2/catalog/etags.
	/// </summary>
	_Maybenull_ const FString givingETag;

	/// <summary>
	/// (Optional) The inventory item the request is transferring from.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFInventoryInventoryItemReference> givingItem;

	/// <summary>
	/// (Optional) The idempotency id for the request.
	/// </summary>
	_Maybenull_ const FString idempotencyId;

	/// <summary>
	/// (Optional) The values to apply to a stack newly created by this request.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFInventoryInitialValues> newStackValues;

	/// <summary>
	/// (Optional) The inventory collection id the request is transferring to. (Default="default").
	/// </summary>
	_Maybenull_ const FString receivingCollectionId;

	/// <summary>
	/// (Optional) The entity the request is transferring to. Set to the caller by default.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> receivingEntity;

	/// <summary>
	/// (Optional) The inventory item the request is transferring to.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFInventoryInventoryItemReference> receivingItem;
};

/// <summary>
/// FPFInventoryTransferInventoryItemsResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryTransferInventoryItemsResponse
{
	/// <summary>
	/// (Optional) ETags are used for concurrency checking when updating resources (after transferring from).
	/// More information about using ETags can be found here: https://learn.microsoft.com/en-us/gaming/playfab/features/economy-v2/catalog/etags.
	/// </summary>
	_Maybenull_ const FString givingETag;

	/// <summary>
	/// (Optional) The ids of transactions that occurred as a result of the request's giving action.
	/// </summary>
	_Maybenull_ const TArray<FString> givingTransactionIds;

	/// <summary>
	/// Count of givingTransactionIds
	/// </summary>
	uint32 givingTransactionIdsCount;

	/// <summary>
	/// (Optional) The idempotency id for the request.
	/// </summary>
	_Maybenull_ const FString idempotencyId;

	/// <summary>
	/// (Optional) The transfer operation status. Possible values are 'InProgress' or 'Completed'. If the
	/// operation has completed, the response code will be 200. Otherwise, it will be 202.
	/// </summary>
	_Maybenull_ const FString operationStatus;

	/// <summary>
	/// (Optional) The token that can be used to get the status of the transfer operation. This will only
	/// have a value if OperationStatus is 'InProgress'.
	/// </summary>
	_Maybenull_ const FString operationToken;

	/// <summary>
	/// (Optional) The ids of transactions that occurred as a result of the request's receiving action.
	/// </summary>
	_Maybenull_ const TArray<FString> receivingTransactionIds;

	/// <summary>
	/// Count of receivingTransactionIds
	/// </summary>
	uint32 receivingTransactionIdsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFInventoryUpdateInventoryItemsRequest data model. Given an entity type, entity identifier and container
/// details, will update the entity's inventory items.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryUpdateInventoryItemsRequest
{
	/// <summary>
	/// (Optional) The id of the entity's collection to perform this action on. (Default="default"). The
	/// number of inventory collections is unlimited.
	/// </summary>
	_Maybenull_ const FString collectionId;

	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// (Optional) The entity to perform this action on.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) ETags are used for concurrency checking when updating resources. More information about
	/// using ETags can be found here: https://learn.microsoft.com/en-us/gaming/playfab/features/economy-v2/catalog/etags.
	/// </summary>
	_Maybenull_ const FString eTag;

	/// <summary>
	/// (Optional) The Idempotency ID for this request. Idempotency IDs can be used to prevent operation
	/// replay in the medium term but will be garbage collected eventually.
	/// </summary>
	_Maybenull_ const FString idempotencyId;

	/// <summary>
	/// (Optional) The inventory item to update with the specified values.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFInventoryInventoryItem> item;
};

/// <summary>
/// FPFInventoryUpdateInventoryItemsResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFInventoryUpdateInventoryItemsResponse
{
	/// <summary>
	/// (Optional) ETags are used for concurrency checking when updating resources. More information about
	/// using ETags can be found here: https://learn.microsoft.com/en-us/gaming/playfab/features/economy-v2/catalog/etags.
	/// </summary>
	_Maybenull_ const FString eTag;

	/// <summary>
	/// (Optional) The idempotency id used in the request.
	/// </summary>
	_Maybenull_ const FString idempotencyId;

	/// <summary>
	/// (Optional) The ids of transactions that occurred as a result of the request.
	/// </summary>
	_Maybenull_ const TArray<FString> transactionIds;

	/// <summary>
	/// Count of transactionIds
	/// </summary>
	uint32 transactionIdsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

// Delegates Declarations

DECLARE_DELEGATE_TwoParams(FOnAddInventoryItemsCompleted, const FPFInventoryAddInventoryItemsResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnDeleteInventoryCollectionCompleted, const FString&, bool);

DECLARE_DELEGATE_TwoParams(FOnDeleteInventoryItemsCompleted, const FPFInventoryDeleteInventoryItemsResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnExecuteInventoryOperationsCompleted, const FPFInventoryExecuteInventoryOperationsResponse&, bool);

#if HC_PLATFORM == HC_PLATFORM_GDK
DECLARE_DELEGATE_TwoParams(FOnExecuteTransferOperationsCompleted, const FPFInventoryExecuteTransferOperationsResponse&, bool);
#endif

DECLARE_DELEGATE_TwoParams(FOnGetInventoryCollectionIdsCompleted, const FPFInventoryGetInventoryCollectionIdsResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnGetInventoryItemsCompleted, const FPFInventoryGetInventoryItemsResponse&, bool);

#if HC_PLATFORM == HC_PLATFORM_GDK
DECLARE_DELEGATE_TwoParams(FOnGetInventoryOperationStatusCompleted, const FPFInventoryGetInventoryOperationStatusResponse&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnGetTransactionHistoryCompleted, const FPFInventoryGetTransactionHistoryResponse&, bool);
#endif

DECLARE_DELEGATE_TwoParams(FOnPurchaseInventoryItemsCompleted, const FPFInventoryPurchaseInventoryItemsResponse&, bool);

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_IOS
DECLARE_DELEGATE_TwoParams(FOnRedeemAppleAppStoreInventoryItemsCompleted, const FPFInventoryRedeemAppleAppStoreInventoryItemsResponse&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_ANDROID
DECLARE_DELEGATE_TwoParams(FOnRedeemGooglePlayInventoryItemsCompleted, const FPFInventoryRedeemGooglePlayInventoryItemsResponse&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnRedeemMicrosoftStoreInventoryItemsCompleted, const FPFInventoryRedeemMicrosoftStoreInventoryItemsResponse&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_NINTENDO_SWITCH || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnRedeemNintendoEShopInventoryItemsCompleted, const FPFInventoryRedeemNintendoEShopInventoryItemsResponse&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_4 || HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_5 || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnRedeemPlayStationStoreInventoryItemsCompleted, const FPFInventoryRedeemPlayStationStoreInventoryItemsResponse&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnRedeemSteamInventoryItemsCompleted, const FPFInventoryRedeemSteamInventoryItemsResponse&, bool);
#endif

DECLARE_DELEGATE_TwoParams(FOnSubtractInventoryItemsCompleted, const FPFInventorySubtractInventoryItemsResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnTransferInventoryItemsCompleted, const FPFInventoryTransferInventoryItemsResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnUpdateInventoryItemsCompleted, const FPFInventoryUpdateInventoryItemsResponse&, bool);

#pragma pop_macro("IN")