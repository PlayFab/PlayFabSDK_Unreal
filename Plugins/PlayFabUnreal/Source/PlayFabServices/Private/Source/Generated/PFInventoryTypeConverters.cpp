// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFInventoryTypeConverters.h"

TSharedPtr<const FPFInventoryAlternateId> ConvertAlternateIdToUnreal(const PFInventoryAlternateId* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryAlternateId> ConvertedType = MakeShared<FPFInventoryAlternateId>(FPFInventoryAlternateId{
		.type = Datatype->type == nullptr ? FString() : FString(Datatype->type),
		.value = Datatype->value == nullptr ? FString() : FString(Datatype->value)
	});

	return ConvertedType;
}

const PFInventoryAlternateId* ConvertAlternateIdToPlayfab(TSharedPtr<const FPFInventoryAlternateId> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryAlternateId* ConvertedType = new PFInventoryAlternateId{
		.type = ConvertFStringToCharPtr(Datatype->type),
		.value = ConvertFStringToCharPtr(Datatype->value)
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryInventoryItemReference> ConvertInventoryItemReferenceToUnreal(const PFInventoryInventoryItemReference* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryInventoryItemReference> ConvertedType = MakeShared<FPFInventoryInventoryItemReference>(FPFInventoryInventoryItemReference{
		.alternateId = ConvertAlternateIdToUnreal(Datatype->alternateId),
		.id = Datatype->id == nullptr ? FString() : FString(Datatype->id),
		.stackId = Datatype->stackId == nullptr ? FString() : FString(Datatype->stackId)
	});

	return ConvertedType;
}

const PFInventoryInventoryItemReference* ConvertInventoryItemReferenceToPlayfab(TSharedPtr<const FPFInventoryInventoryItemReference> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryInventoryItemReference* ConvertedType = new PFInventoryInventoryItemReference{
		.alternateId = ConvertAlternateIdToPlayfab(Datatype->alternateId),
		.id = ConvertFStringToCharPtr(Datatype->id),
		.stackId = ConvertFStringToCharPtr(Datatype->stackId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryInitialValues> ConvertInitialValuesToUnreal(const PFInventoryInitialValues* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryInitialValues> ConvertedType = MakeShared<FPFInventoryInitialValues>(FPFInventoryInitialValues{
		.displayProperties = FPFJsonObject{ .stringValue = FString(Datatype->displayProperties.stringValue) }
	});

	return ConvertedType;
}

const PFInventoryInitialValues* ConvertInitialValuesToPlayfab(TSharedPtr<const FPFInventoryInitialValues> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryInitialValues* ConvertedType = new PFInventoryInitialValues{
		.displayProperties = PFJsonObject{ .stringValue = ConvertFStringToCharPtr(Datatype->displayProperties.stringValue) }
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryAddInventoryItemsRequest> ConvertAddInventoryItemsRequestToUnreal(const PFInventoryAddInventoryItemsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryAddInventoryItemsRequest> ConvertedType = MakeShared<FPFInventoryAddInventoryItemsRequest>(FPFInventoryAddInventoryItemsRequest{
		.amount = TSharedPtr<const int32>(Datatype->amount),
		.collectionId = Datatype->collectionId == nullptr ? FString() : FString(Datatype->collectionId),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.durationInSeconds = TSharedPtr<const double>(Datatype->durationInSeconds),
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.eTag = Datatype->eTag == nullptr ? FString() : FString(Datatype->eTag),
		.idempotencyId = Datatype->idempotencyId == nullptr ? FString() : FString(Datatype->idempotencyId),
		.item = ConvertInventoryItemReferenceToUnreal(Datatype->item),
		.newStackValues = ConvertInitialValuesToUnreal(Datatype->newStackValues)
	});

	return ConvertedType;
}

const PFInventoryAddInventoryItemsRequest* ConvertAddInventoryItemsRequestToPlayfab(TSharedPtr<const FPFInventoryAddInventoryItemsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryAddInventoryItemsRequest* ConvertedType = new PFInventoryAddInventoryItemsRequest{
		.amount = Datatype->amount ? new int32(*Datatype->amount) : nullptr,
		.collectionId = ConvertFStringToCharPtr(Datatype->collectionId),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.durationInSeconds = Datatype->durationInSeconds ? new double(*Datatype->durationInSeconds) : nullptr,
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.eTag = ConvertFStringToCharPtr(Datatype->eTag),
		.idempotencyId = ConvertFStringToCharPtr(Datatype->idempotencyId),
		.item = ConvertInventoryItemReferenceToPlayfab(Datatype->item),
		.newStackValues = ConvertInitialValuesToPlayfab(Datatype->newStackValues)
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryAddInventoryItemsResponse> ConvertAddInventoryItemsResponseToUnreal(const PFInventoryAddInventoryItemsResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryAddInventoryItemsResponse> ConvertedType = MakeShared<FPFInventoryAddInventoryItemsResponse>(FPFInventoryAddInventoryItemsResponse{
		.eTag = Datatype->eTag == nullptr ? FString() : FString(Datatype->eTag),
		.idempotencyId = Datatype->idempotencyId == nullptr ? FString() : FString(Datatype->idempotencyId),
		.transactionIds = ConvertCharArrayToUnreal(Datatype->transactionIds, Datatype->transactionIdsCount),
		.transactionIdsCount = Datatype->transactionIdsCount
	});

	return ConvertedType;
}

const PFInventoryAddInventoryItemsResponse* ConvertAddInventoryItemsResponseToPlayfab(TSharedPtr<const FPFInventoryAddInventoryItemsResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryAddInventoryItemsResponse* ConvertedType = new PFInventoryAddInventoryItemsResponse{
		.eTag = ConvertFStringToCharPtr(Datatype->eTag),
		.idempotencyId = ConvertFStringToCharPtr(Datatype->idempotencyId),
		.transactionIds = ConvertFStringArrayToPlayfab(Datatype->transactionIds),
		.transactionIdsCount = (uint32_t)Datatype->transactionIds.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryDeleteInventoryCollectionRequest> ConvertDeleteInventoryCollectionRequestToUnreal(const PFInventoryDeleteInventoryCollectionRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryDeleteInventoryCollectionRequest> ConvertedType = MakeShared<FPFInventoryDeleteInventoryCollectionRequest>(FPFInventoryDeleteInventoryCollectionRequest{
		.collectionId = Datatype->collectionId == nullptr ? FString() : FString(Datatype->collectionId),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.eTag = Datatype->eTag == nullptr ? FString() : FString(Datatype->eTag)
	});

	return ConvertedType;
}

const PFInventoryDeleteInventoryCollectionRequest* ConvertDeleteInventoryCollectionRequestToPlayfab(TSharedPtr<const FPFInventoryDeleteInventoryCollectionRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryDeleteInventoryCollectionRequest* ConvertedType = new PFInventoryDeleteInventoryCollectionRequest{
		.collectionId = ConvertFStringToCharPtr(Datatype->collectionId),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.eTag = ConvertFStringToCharPtr(Datatype->eTag)
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryDeleteInventoryItemsRequest> ConvertDeleteInventoryItemsRequestToUnreal(const PFInventoryDeleteInventoryItemsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryDeleteInventoryItemsRequest> ConvertedType = MakeShared<FPFInventoryDeleteInventoryItemsRequest>(FPFInventoryDeleteInventoryItemsRequest{
		.collectionId = Datatype->collectionId == nullptr ? FString() : FString(Datatype->collectionId),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.eTag = Datatype->eTag == nullptr ? FString() : FString(Datatype->eTag),
		.idempotencyId = Datatype->idempotencyId == nullptr ? FString() : FString(Datatype->idempotencyId),
		.item = ConvertInventoryItemReferenceToUnreal(Datatype->item)
	});

	return ConvertedType;
}

const PFInventoryDeleteInventoryItemsRequest* ConvertDeleteInventoryItemsRequestToPlayfab(TSharedPtr<const FPFInventoryDeleteInventoryItemsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryDeleteInventoryItemsRequest* ConvertedType = new PFInventoryDeleteInventoryItemsRequest{
		.collectionId = ConvertFStringToCharPtr(Datatype->collectionId),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.eTag = ConvertFStringToCharPtr(Datatype->eTag),
		.idempotencyId = ConvertFStringToCharPtr(Datatype->idempotencyId),
		.item = ConvertInventoryItemReferenceToPlayfab(Datatype->item)
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryDeleteInventoryItemsResponse> ConvertDeleteInventoryItemsResponseToUnreal(const PFInventoryDeleteInventoryItemsResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryDeleteInventoryItemsResponse> ConvertedType = MakeShared<FPFInventoryDeleteInventoryItemsResponse>(FPFInventoryDeleteInventoryItemsResponse{
		.eTag = Datatype->eTag == nullptr ? FString() : FString(Datatype->eTag),
		.idempotencyId = Datatype->idempotencyId == nullptr ? FString() : FString(Datatype->idempotencyId),
		.transactionIds = ConvertCharArrayToUnreal(Datatype->transactionIds, Datatype->transactionIdsCount),
		.transactionIdsCount = Datatype->transactionIdsCount
	});

	return ConvertedType;
}

const PFInventoryDeleteInventoryItemsResponse* ConvertDeleteInventoryItemsResponseToPlayfab(TSharedPtr<const FPFInventoryDeleteInventoryItemsResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryDeleteInventoryItemsResponse* ConvertedType = new PFInventoryDeleteInventoryItemsResponse{
		.eTag = ConvertFStringToCharPtr(Datatype->eTag),
		.idempotencyId = ConvertFStringToCharPtr(Datatype->idempotencyId),
		.transactionIds = ConvertFStringArrayToPlayfab(Datatype->transactionIds),
		.transactionIdsCount = (uint32_t)Datatype->transactionIds.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryAddInventoryItemsOperation> ConvertAddInventoryItemsOperationToUnreal(const PFInventoryAddInventoryItemsOperation* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryAddInventoryItemsOperation> ConvertedType = MakeShared<FPFInventoryAddInventoryItemsOperation>(FPFInventoryAddInventoryItemsOperation{
		.amount = TSharedPtr<const int32>(Datatype->amount),
		.durationInSeconds = TSharedPtr<const double>(Datatype->durationInSeconds),
		.item = ConvertInventoryItemReferenceToUnreal(Datatype->item),
		.newStackValues = ConvertInitialValuesToUnreal(Datatype->newStackValues)
	});

	return ConvertedType;
}

const PFInventoryAddInventoryItemsOperation* ConvertAddInventoryItemsOperationToPlayfab(TSharedPtr<const FPFInventoryAddInventoryItemsOperation> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryAddInventoryItemsOperation* ConvertedType = new PFInventoryAddInventoryItemsOperation{
		.amount = Datatype->amount ? new int32(*Datatype->amount) : nullptr,
		.durationInSeconds = Datatype->durationInSeconds ? new double(*Datatype->durationInSeconds) : nullptr,
		.item = ConvertInventoryItemReferenceToPlayfab(Datatype->item),
		.newStackValues = ConvertInitialValuesToPlayfab(Datatype->newStackValues)
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryDeleteInventoryItemsOperation> ConvertDeleteInventoryItemsOperationToUnreal(const PFInventoryDeleteInventoryItemsOperation* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryDeleteInventoryItemsOperation> ConvertedType = MakeShared<FPFInventoryDeleteInventoryItemsOperation>(FPFInventoryDeleteInventoryItemsOperation{
		.item = ConvertInventoryItemReferenceToUnreal(Datatype->item)
	});

	return ConvertedType;
}

const PFInventoryDeleteInventoryItemsOperation* ConvertDeleteInventoryItemsOperationToPlayfab(TSharedPtr<const FPFInventoryDeleteInventoryItemsOperation> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryDeleteInventoryItemsOperation* ConvertedType = new PFInventoryDeleteInventoryItemsOperation{
		.item = ConvertInventoryItemReferenceToPlayfab(Datatype->item)
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryPurchasePriceAmount> ConvertPurchasePriceAmountToUnreal(const PFInventoryPurchasePriceAmount* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryPurchasePriceAmount> ConvertedType = MakeShared<FPFInventoryPurchasePriceAmount>(FPFInventoryPurchasePriceAmount{
		.amount = Datatype->amount,
		.itemId = Datatype->itemId == nullptr ? FString() : FString(Datatype->itemId),
		.stackId = Datatype->stackId == nullptr ? FString() : FString(Datatype->stackId)
	});

	return ConvertedType;
}

const PFInventoryPurchasePriceAmount* ConvertPurchasePriceAmountToPlayfab(TSharedPtr<const FPFInventoryPurchasePriceAmount> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryPurchasePriceAmount* ConvertedType = new PFInventoryPurchasePriceAmount{
		.amount = Datatype->amount,
		.itemId = ConvertFStringToCharPtr(Datatype->itemId),
		.stackId = ConvertFStringToCharPtr(Datatype->stackId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryPurchaseInventoryItemsOperation> ConvertPurchaseInventoryItemsOperationToUnreal(const PFInventoryPurchaseInventoryItemsOperation* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryPurchaseInventoryItemsOperation> ConvertedType = MakeShared<FPFInventoryPurchaseInventoryItemsOperation>(FPFInventoryPurchaseInventoryItemsOperation{
		.amount = TSharedPtr<const int32>(Datatype->amount),
		.deleteEmptyStacks = Datatype->deleteEmptyStacks,
		.durationInSeconds = TSharedPtr<const double>(Datatype->durationInSeconds),
		.item = ConvertInventoryItemReferenceToUnreal(Datatype->item),
		.newStackValues = ConvertInitialValuesToUnreal(Datatype->newStackValues),
		.priceAmounts = ConvertPlayfabArrayToUnreal<PFInventoryPurchasePriceAmount, FPFInventoryPurchasePriceAmount>(Datatype->priceAmounts, Datatype->priceAmountsCount, ConvertPurchasePriceAmountToUnreal),
		.priceAmountsCount = Datatype->priceAmountsCount,
		.storeId = Datatype->storeId == nullptr ? FString() : FString(Datatype->storeId)
	});

	return ConvertedType;
}

const PFInventoryPurchaseInventoryItemsOperation* ConvertPurchaseInventoryItemsOperationToPlayfab(TSharedPtr<const FPFInventoryPurchaseInventoryItemsOperation> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryPurchaseInventoryItemsOperation* ConvertedType = new PFInventoryPurchaseInventoryItemsOperation{
		.amount = Datatype->amount ? new int32(*Datatype->amount) : nullptr,
		.deleteEmptyStacks = Datatype->deleteEmptyStacks,
		.durationInSeconds = Datatype->durationInSeconds ? new double(*Datatype->durationInSeconds) : nullptr,
		.item = ConvertInventoryItemReferenceToPlayfab(Datatype->item),
		.newStackValues = ConvertInitialValuesToPlayfab(Datatype->newStackValues),
		.priceAmounts = ConvertUnrealArrayToPlayfab<PFInventoryPurchasePriceAmount, FPFInventoryPurchasePriceAmount>(Datatype->priceAmounts, ConvertPurchasePriceAmountToPlayfab),
		.priceAmountsCount = (uint32_t)Datatype->priceAmounts.Num(),
		.storeId = ConvertFStringToCharPtr(Datatype->storeId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventorySubtractInventoryItemsOperation> ConvertSubtractInventoryItemsOperationToUnreal(const PFInventorySubtractInventoryItemsOperation* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventorySubtractInventoryItemsOperation> ConvertedType = MakeShared<FPFInventorySubtractInventoryItemsOperation>(FPFInventorySubtractInventoryItemsOperation{
		.amount = TSharedPtr<const int32>(Datatype->amount),
		.deleteEmptyStacks = Datatype->deleteEmptyStacks,
		.durationInSeconds = TSharedPtr<const double>(Datatype->durationInSeconds),
		.item = ConvertInventoryItemReferenceToUnreal(Datatype->item)
	});

	return ConvertedType;
}

const PFInventorySubtractInventoryItemsOperation* ConvertSubtractInventoryItemsOperationToPlayfab(TSharedPtr<const FPFInventorySubtractInventoryItemsOperation> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventorySubtractInventoryItemsOperation* ConvertedType = new PFInventorySubtractInventoryItemsOperation{
		.amount = Datatype->amount ? new int32(*Datatype->amount) : nullptr,
		.deleteEmptyStacks = Datatype->deleteEmptyStacks,
		.durationInSeconds = Datatype->durationInSeconds ? new double(*Datatype->durationInSeconds) : nullptr,
		.item = ConvertInventoryItemReferenceToPlayfab(Datatype->item)
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryTransferInventoryItemsOperation> ConvertTransferInventoryItemsOperationToUnreal(const PFInventoryTransferInventoryItemsOperation* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryTransferInventoryItemsOperation> ConvertedType = MakeShared<FPFInventoryTransferInventoryItemsOperation>(FPFInventoryTransferInventoryItemsOperation{
		.amount = TSharedPtr<const int32>(Datatype->amount),
		.deleteEmptyStacks = Datatype->deleteEmptyStacks,
		.givingItem = ConvertInventoryItemReferenceToUnreal(Datatype->givingItem),
		.newStackValues = ConvertInitialValuesToUnreal(Datatype->newStackValues),
		.receivingItem = ConvertInventoryItemReferenceToUnreal(Datatype->receivingItem)
	});

	return ConvertedType;
}

const PFInventoryTransferInventoryItemsOperation* ConvertTransferInventoryItemsOperationToPlayfab(TSharedPtr<const FPFInventoryTransferInventoryItemsOperation> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryTransferInventoryItemsOperation* ConvertedType = new PFInventoryTransferInventoryItemsOperation{
		.amount = Datatype->amount ? new int32(*Datatype->amount) : nullptr,
		.deleteEmptyStacks = Datatype->deleteEmptyStacks,
		.givingItem = ConvertInventoryItemReferenceToPlayfab(Datatype->givingItem),
		.newStackValues = ConvertInitialValuesToPlayfab(Datatype->newStackValues),
		.receivingItem = ConvertInventoryItemReferenceToPlayfab(Datatype->receivingItem)
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryInventoryItem> ConvertInventoryItemToUnreal(const PFInventoryInventoryItem* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryInventoryItem> ConvertedType = MakeShared<FPFInventoryInventoryItem>(FPFInventoryInventoryItem{
		.amount = TSharedPtr<const int32>(Datatype->amount),
		.displayProperties = FPFJsonObject{ .stringValue = FString(Datatype->displayProperties.stringValue) },
		.expirationDate = ConvertTimeToUnreal(Datatype->expirationDate),
		.id = Datatype->id == nullptr ? FString() : FString(Datatype->id),
		.stackId = Datatype->stackId == nullptr ? FString() : FString(Datatype->stackId),
		.type = Datatype->type == nullptr ? FString() : FString(Datatype->type)
	});

	return ConvertedType;
}

const PFInventoryInventoryItem* ConvertInventoryItemToPlayfab(TSharedPtr<const FPFInventoryInventoryItem> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryInventoryItem* ConvertedType = new PFInventoryInventoryItem{
		.amount = Datatype->amount ? new int32(*Datatype->amount) : nullptr,
		.displayProperties = PFJsonObject{ .stringValue = ConvertFStringToCharPtr(Datatype->displayProperties.stringValue) },
		.expirationDate = ConvertFDateTimeToPlayfab(Datatype->expirationDate),
		.id = ConvertFStringToCharPtr(Datatype->id),
		.stackId = ConvertFStringToCharPtr(Datatype->stackId),
		.type = ConvertFStringToCharPtr(Datatype->type)
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryUpdateInventoryItemsOperation> ConvertUpdateInventoryItemsOperationToUnreal(const PFInventoryUpdateInventoryItemsOperation* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryUpdateInventoryItemsOperation> ConvertedType = MakeShared<FPFInventoryUpdateInventoryItemsOperation>(FPFInventoryUpdateInventoryItemsOperation{
		.item = ConvertInventoryItemToUnreal(Datatype->item)
	});

	return ConvertedType;
}

const PFInventoryUpdateInventoryItemsOperation* ConvertUpdateInventoryItemsOperationToPlayfab(TSharedPtr<const FPFInventoryUpdateInventoryItemsOperation> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryUpdateInventoryItemsOperation* ConvertedType = new PFInventoryUpdateInventoryItemsOperation{
		.item = ConvertInventoryItemToPlayfab(Datatype->item)
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryInventoryOperation> ConvertInventoryOperationToUnreal(const PFInventoryInventoryOperation* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryInventoryOperation> ConvertedType = MakeShared<FPFInventoryInventoryOperation>(FPFInventoryInventoryOperation{
		.add = ConvertAddInventoryItemsOperationToUnreal(Datatype->add),
		.deleteOp = ConvertDeleteInventoryItemsOperationToUnreal(Datatype->deleteOp),
		.purchase = ConvertPurchaseInventoryItemsOperationToUnreal(Datatype->purchase),
		.subtract = ConvertSubtractInventoryItemsOperationToUnreal(Datatype->subtract),
		.transfer = ConvertTransferInventoryItemsOperationToUnreal(Datatype->transfer),
		.update = ConvertUpdateInventoryItemsOperationToUnreal(Datatype->update)
	});

	return ConvertedType;
}

const PFInventoryInventoryOperation* ConvertInventoryOperationToPlayfab(TSharedPtr<const FPFInventoryInventoryOperation> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryInventoryOperation* ConvertedType = new PFInventoryInventoryOperation{
		.add = ConvertAddInventoryItemsOperationToPlayfab(Datatype->add),
		.deleteOp = ConvertDeleteInventoryItemsOperationToPlayfab(Datatype->deleteOp),
		.purchase = ConvertPurchaseInventoryItemsOperationToPlayfab(Datatype->purchase),
		.subtract = ConvertSubtractInventoryItemsOperationToPlayfab(Datatype->subtract),
		.transfer = ConvertTransferInventoryItemsOperationToPlayfab(Datatype->transfer),
		.update = ConvertUpdateInventoryItemsOperationToPlayfab(Datatype->update)
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryExecuteInventoryOperationsRequest> ConvertExecuteInventoryOperationsRequestToUnreal(const PFInventoryExecuteInventoryOperationsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryExecuteInventoryOperationsRequest> ConvertedType = MakeShared<FPFInventoryExecuteInventoryOperationsRequest>(FPFInventoryExecuteInventoryOperationsRequest{
		.collectionId = Datatype->collectionId == nullptr ? FString() : FString(Datatype->collectionId),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.eTag = Datatype->eTag == nullptr ? FString() : FString(Datatype->eTag),
		.idempotencyId = Datatype->idempotencyId == nullptr ? FString() : FString(Datatype->idempotencyId),
		.operations = ConvertPlayfabArrayToUnreal<PFInventoryInventoryOperation, FPFInventoryInventoryOperation>(Datatype->operations, Datatype->operationsCount, ConvertInventoryOperationToUnreal),
		.operationsCount = Datatype->operationsCount
	});

	return ConvertedType;
}

const PFInventoryExecuteInventoryOperationsRequest* ConvertExecuteInventoryOperationsRequestToPlayfab(TSharedPtr<const FPFInventoryExecuteInventoryOperationsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryExecuteInventoryOperationsRequest* ConvertedType = new PFInventoryExecuteInventoryOperationsRequest{
		.collectionId = ConvertFStringToCharPtr(Datatype->collectionId),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.eTag = ConvertFStringToCharPtr(Datatype->eTag),
		.idempotencyId = ConvertFStringToCharPtr(Datatype->idempotencyId),
		.operations = ConvertUnrealArrayToPlayfab<PFInventoryInventoryOperation, FPFInventoryInventoryOperation>(Datatype->operations, ConvertInventoryOperationToPlayfab),
		.operationsCount = (uint32_t)Datatype->operations.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryExecuteInventoryOperationsResponse> ConvertExecuteInventoryOperationsResponseToUnreal(const PFInventoryExecuteInventoryOperationsResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryExecuteInventoryOperationsResponse> ConvertedType = MakeShared<FPFInventoryExecuteInventoryOperationsResponse>(FPFInventoryExecuteInventoryOperationsResponse{
		.eTag = Datatype->eTag == nullptr ? FString() : FString(Datatype->eTag),
		.idempotencyId = Datatype->idempotencyId == nullptr ? FString() : FString(Datatype->idempotencyId),
		.transactionIds = ConvertCharArrayToUnreal(Datatype->transactionIds, Datatype->transactionIdsCount),
		.transactionIdsCount = Datatype->transactionIdsCount
	});

	return ConvertedType;
}

const PFInventoryExecuteInventoryOperationsResponse* ConvertExecuteInventoryOperationsResponseToPlayfab(TSharedPtr<const FPFInventoryExecuteInventoryOperationsResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryExecuteInventoryOperationsResponse* ConvertedType = new PFInventoryExecuteInventoryOperationsResponse{
		.eTag = ConvertFStringToCharPtr(Datatype->eTag),
		.idempotencyId = ConvertFStringToCharPtr(Datatype->idempotencyId),
		.transactionIds = ConvertFStringArrayToPlayfab(Datatype->transactionIds),
		.transactionIdsCount = (uint32_t)Datatype->transactionIds.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryExecuteTransferOperationsRequest> ConvertExecuteTransferOperationsRequestToUnreal(const PFInventoryExecuteTransferOperationsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryExecuteTransferOperationsRequest> ConvertedType = MakeShared<FPFInventoryExecuteTransferOperationsRequest>(FPFInventoryExecuteTransferOperationsRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.givingCollectionId = Datatype->givingCollectionId == nullptr ? FString() : FString(Datatype->givingCollectionId),
		.givingEntity = ConvertEntityKeyToUnreal(Datatype->givingEntity),
		.givingETag = Datatype->givingETag == nullptr ? FString() : FString(Datatype->givingETag),
		.idempotencyId = Datatype->idempotencyId == nullptr ? FString() : FString(Datatype->idempotencyId),
		.operations = ConvertPlayfabArrayToUnreal<PFInventoryTransferInventoryItemsOperation, FPFInventoryTransferInventoryItemsOperation>(Datatype->operations, Datatype->operationsCount, ConvertTransferInventoryItemsOperationToUnreal),
		.operationsCount = Datatype->operationsCount,
		.receivingCollectionId = Datatype->receivingCollectionId == nullptr ? FString() : FString(Datatype->receivingCollectionId),
		.receivingEntity = ConvertEntityKeyToUnreal(Datatype->receivingEntity)
	});

	return ConvertedType;
}

const PFInventoryExecuteTransferOperationsRequest* ConvertExecuteTransferOperationsRequestToPlayfab(TSharedPtr<const FPFInventoryExecuteTransferOperationsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryExecuteTransferOperationsRequest* ConvertedType = new PFInventoryExecuteTransferOperationsRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.givingCollectionId = ConvertFStringToCharPtr(Datatype->givingCollectionId),
		.givingEntity = ConvertEntityKeyToPlayfab(Datatype->givingEntity),
		.givingETag = ConvertFStringToCharPtr(Datatype->givingETag),
		.idempotencyId = ConvertFStringToCharPtr(Datatype->idempotencyId),
		.operations = ConvertUnrealArrayToPlayfab<PFInventoryTransferInventoryItemsOperation, FPFInventoryTransferInventoryItemsOperation>(Datatype->operations, ConvertTransferInventoryItemsOperationToPlayfab),
		.operationsCount = (uint32_t)Datatype->operations.Num(),
		.receivingCollectionId = ConvertFStringToCharPtr(Datatype->receivingCollectionId),
		.receivingEntity = ConvertEntityKeyToPlayfab(Datatype->receivingEntity)
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryExecuteTransferOperationsResponse> ConvertExecuteTransferOperationsResponseToUnreal(const PFInventoryExecuteTransferOperationsResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryExecuteTransferOperationsResponse> ConvertedType = MakeShared<FPFInventoryExecuteTransferOperationsResponse>(FPFInventoryExecuteTransferOperationsResponse{
		.givingETag = Datatype->givingETag == nullptr ? FString() : FString(Datatype->givingETag),
		.givingTransactionIds = ConvertCharArrayToUnreal(Datatype->givingTransactionIds, Datatype->givingTransactionIdsCount),
		.givingTransactionIdsCount = Datatype->givingTransactionIdsCount,
		.idempotencyId = Datatype->idempotencyId == nullptr ? FString() : FString(Datatype->idempotencyId),
		.operationStatus = Datatype->operationStatus == nullptr ? FString() : FString(Datatype->operationStatus),
		.operationToken = Datatype->operationToken == nullptr ? FString() : FString(Datatype->operationToken),
		.receivingETag = Datatype->receivingETag == nullptr ? FString() : FString(Datatype->receivingETag),
		.receivingTransactionIds = ConvertCharArrayToUnreal(Datatype->receivingTransactionIds, Datatype->receivingTransactionIdsCount),
		.receivingTransactionIdsCount = Datatype->receivingTransactionIdsCount
	});

	return ConvertedType;
}

const PFInventoryExecuteTransferOperationsResponse* ConvertExecuteTransferOperationsResponseToPlayfab(TSharedPtr<const FPFInventoryExecuteTransferOperationsResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryExecuteTransferOperationsResponse* ConvertedType = new PFInventoryExecuteTransferOperationsResponse{
		.givingETag = ConvertFStringToCharPtr(Datatype->givingETag),
		.givingTransactionIds = ConvertFStringArrayToPlayfab(Datatype->givingTransactionIds),
		.givingTransactionIdsCount = (uint32_t)Datatype->givingTransactionIds.Num(),
		.idempotencyId = ConvertFStringToCharPtr(Datatype->idempotencyId),
		.operationStatus = ConvertFStringToCharPtr(Datatype->operationStatus),
		.operationToken = ConvertFStringToCharPtr(Datatype->operationToken),
		.receivingETag = ConvertFStringToCharPtr(Datatype->receivingETag),
		.receivingTransactionIds = ConvertFStringArrayToPlayfab(Datatype->receivingTransactionIds),
		.receivingTransactionIdsCount = (uint32_t)Datatype->receivingTransactionIds.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryGetInventoryCollectionIdsRequest> ConvertGetInventoryCollectionIdsRequestToUnreal(const PFInventoryGetInventoryCollectionIdsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryGetInventoryCollectionIdsRequest> ConvertedType = MakeShared<FPFInventoryGetInventoryCollectionIdsRequest>(FPFInventoryGetInventoryCollectionIdsRequest{
		.continuationToken = Datatype->continuationToken == nullptr ? FString() : FString(Datatype->continuationToken),
		.count = Datatype->count,
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity)
	});

	return ConvertedType;
}

const PFInventoryGetInventoryCollectionIdsRequest* ConvertGetInventoryCollectionIdsRequestToPlayfab(TSharedPtr<const FPFInventoryGetInventoryCollectionIdsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryGetInventoryCollectionIdsRequest* ConvertedType = new PFInventoryGetInventoryCollectionIdsRequest{
		.continuationToken = ConvertFStringToCharPtr(Datatype->continuationToken),
		.count = Datatype->count,
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity)
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryGetInventoryCollectionIdsResponse> ConvertGetInventoryCollectionIdsResponseToUnreal(const PFInventoryGetInventoryCollectionIdsResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryGetInventoryCollectionIdsResponse> ConvertedType = MakeShared<FPFInventoryGetInventoryCollectionIdsResponse>(FPFInventoryGetInventoryCollectionIdsResponse{
		.collectionIds = ConvertCharArrayToUnreal(Datatype->collectionIds, Datatype->collectionIdsCount),
		.collectionIdsCount = Datatype->collectionIdsCount,
		.continuationToken = Datatype->continuationToken == nullptr ? FString() : FString(Datatype->continuationToken)
	});

	return ConvertedType;
}

const PFInventoryGetInventoryCollectionIdsResponse* ConvertGetInventoryCollectionIdsResponseToPlayfab(TSharedPtr<const FPFInventoryGetInventoryCollectionIdsResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryGetInventoryCollectionIdsResponse* ConvertedType = new PFInventoryGetInventoryCollectionIdsResponse{
		.collectionIds = ConvertFStringArrayToPlayfab(Datatype->collectionIds),
		.collectionIdsCount = (uint32_t)Datatype->collectionIds.Num(),
		.continuationToken = ConvertFStringToCharPtr(Datatype->continuationToken)
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryGetInventoryItemsRequest> ConvertGetInventoryItemsRequestToUnreal(const PFInventoryGetInventoryItemsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryGetInventoryItemsRequest> ConvertedType = MakeShared<FPFInventoryGetInventoryItemsRequest>(FPFInventoryGetInventoryItemsRequest{
		.collectionId = Datatype->collectionId == nullptr ? FString() : FString(Datatype->collectionId),
		.continuationToken = Datatype->continuationToken == nullptr ? FString() : FString(Datatype->continuationToken),
		.count = Datatype->count,
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.filter = Datatype->filter == nullptr ? FString() : FString(Datatype->filter)
	});

	return ConvertedType;
}

const PFInventoryGetInventoryItemsRequest* ConvertGetInventoryItemsRequestToPlayfab(TSharedPtr<const FPFInventoryGetInventoryItemsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryGetInventoryItemsRequest* ConvertedType = new PFInventoryGetInventoryItemsRequest{
		.collectionId = ConvertFStringToCharPtr(Datatype->collectionId),
		.continuationToken = ConvertFStringToCharPtr(Datatype->continuationToken),
		.count = Datatype->count,
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.filter = ConvertFStringToCharPtr(Datatype->filter)
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryGetInventoryItemsResponse> ConvertGetInventoryItemsResponseToUnreal(const PFInventoryGetInventoryItemsResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryGetInventoryItemsResponse> ConvertedType = MakeShared<FPFInventoryGetInventoryItemsResponse>(FPFInventoryGetInventoryItemsResponse{
		.continuationToken = Datatype->continuationToken == nullptr ? FString() : FString(Datatype->continuationToken),
		.eTag = Datatype->eTag == nullptr ? FString() : FString(Datatype->eTag),
		.items = ConvertPlayfabArrayToUnreal<PFInventoryInventoryItem, FPFInventoryInventoryItem>(Datatype->items, Datatype->itemsCount, ConvertInventoryItemToUnreal),
		.itemsCount = Datatype->itemsCount
	});

	return ConvertedType;
}

const PFInventoryGetInventoryItemsResponse* ConvertGetInventoryItemsResponseToPlayfab(TSharedPtr<const FPFInventoryGetInventoryItemsResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryGetInventoryItemsResponse* ConvertedType = new PFInventoryGetInventoryItemsResponse{
		.continuationToken = ConvertFStringToCharPtr(Datatype->continuationToken),
		.eTag = ConvertFStringToCharPtr(Datatype->eTag),
		.items = ConvertUnrealArrayToPlayfab<PFInventoryInventoryItem, FPFInventoryInventoryItem>(Datatype->items, ConvertInventoryItemToPlayfab),
		.itemsCount = (uint32_t)Datatype->items.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryGetInventoryOperationStatusRequest> ConvertGetInventoryOperationStatusRequestToUnreal(const PFInventoryGetInventoryOperationStatusRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryGetInventoryOperationStatusRequest> ConvertedType = MakeShared<FPFInventoryGetInventoryOperationStatusRequest>(FPFInventoryGetInventoryOperationStatusRequest{
		.collectionId = Datatype->collectionId == nullptr ? FString() : FString(Datatype->collectionId),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.operationToken = Datatype->operationToken == nullptr ? FString() : FString(Datatype->operationToken)
	});

	return ConvertedType;
}

const PFInventoryGetInventoryOperationStatusRequest* ConvertGetInventoryOperationStatusRequestToPlayfab(TSharedPtr<const FPFInventoryGetInventoryOperationStatusRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryGetInventoryOperationStatusRequest* ConvertedType = new PFInventoryGetInventoryOperationStatusRequest{
		.collectionId = ConvertFStringToCharPtr(Datatype->collectionId),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.operationToken = ConvertFStringToCharPtr(Datatype->operationToken)
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryGetInventoryOperationStatusResponse> ConvertGetInventoryOperationStatusResponseToUnreal(const PFInventoryGetInventoryOperationStatusResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryGetInventoryOperationStatusResponse> ConvertedType = MakeShared<FPFInventoryGetInventoryOperationStatusResponse>(FPFInventoryGetInventoryOperationStatusResponse{
		.operationStatus = Datatype->operationStatus == nullptr ? FString() : FString(Datatype->operationStatus)
	});

	return ConvertedType;
}

const PFInventoryGetInventoryOperationStatusResponse* ConvertGetInventoryOperationStatusResponseToPlayfab(TSharedPtr<const FPFInventoryGetInventoryOperationStatusResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryGetInventoryOperationStatusResponse* ConvertedType = new PFInventoryGetInventoryOperationStatusResponse{
		.operationStatus = ConvertFStringToCharPtr(Datatype->operationStatus)
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryGetMicrosoftStoreAccessTokensRequest> ConvertGetMicrosoftStoreAccessTokensRequestToUnreal(const PFInventoryGetMicrosoftStoreAccessTokensRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryGetMicrosoftStoreAccessTokensRequest> ConvertedType = MakeShared<FPFInventoryGetMicrosoftStoreAccessTokensRequest>(FPFInventoryGetMicrosoftStoreAccessTokensRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount
	});

	return ConvertedType;
}

const PFInventoryGetMicrosoftStoreAccessTokensRequest* ConvertGetMicrosoftStoreAccessTokensRequestToPlayfab(TSharedPtr<const FPFInventoryGetMicrosoftStoreAccessTokensRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryGetMicrosoftStoreAccessTokensRequest* ConvertedType = new PFInventoryGetMicrosoftStoreAccessTokensRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryGetMicrosoftStoreAccessTokensResponse> ConvertGetMicrosoftStoreAccessTokensResponseToUnreal(const PFInventoryGetMicrosoftStoreAccessTokensResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryGetMicrosoftStoreAccessTokensResponse> ConvertedType = MakeShared<FPFInventoryGetMicrosoftStoreAccessTokensResponse>(FPFInventoryGetMicrosoftStoreAccessTokensResponse{
		.collectionsAccessToken = Datatype->collectionsAccessToken == nullptr ? FString() : FString(Datatype->collectionsAccessToken),
		.collectionsAccessTokenExpirationDate = FDateTime::FromUnixTimestamp((int64)Datatype->collectionsAccessTokenExpirationDate)
	});

	return ConvertedType;
}

const PFInventoryGetMicrosoftStoreAccessTokensResponse* ConvertGetMicrosoftStoreAccessTokensResponseToPlayfab(TSharedPtr<const FPFInventoryGetMicrosoftStoreAccessTokensResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryGetMicrosoftStoreAccessTokensResponse* ConvertedType = new PFInventoryGetMicrosoftStoreAccessTokensResponse{
		.collectionsAccessToken = ConvertFStringToCharPtr(Datatype->collectionsAccessToken),
		.collectionsAccessTokenExpirationDate = Datatype->collectionsAccessTokenExpirationDate.ToUnixTimestamp()
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryGetTransactionHistoryRequest> ConvertGetTransactionHistoryRequestToUnreal(const PFInventoryGetTransactionHistoryRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryGetTransactionHistoryRequest> ConvertedType = MakeShared<FPFInventoryGetTransactionHistoryRequest>(FPFInventoryGetTransactionHistoryRequest{
		.collectionId = Datatype->collectionId == nullptr ? FString() : FString(Datatype->collectionId),
		.continuationToken = Datatype->continuationToken == nullptr ? FString() : FString(Datatype->continuationToken),
		.count = Datatype->count,
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.filter = Datatype->filter == nullptr ? FString() : FString(Datatype->filter),
		.orderBy = Datatype->orderBy == nullptr ? FString() : FString(Datatype->orderBy)
	});

	return ConvertedType;
}

const PFInventoryGetTransactionHistoryRequest* ConvertGetTransactionHistoryRequestToPlayfab(TSharedPtr<const FPFInventoryGetTransactionHistoryRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryGetTransactionHistoryRequest* ConvertedType = new PFInventoryGetTransactionHistoryRequest{
		.collectionId = ConvertFStringToCharPtr(Datatype->collectionId),
		.continuationToken = ConvertFStringToCharPtr(Datatype->continuationToken),
		.count = Datatype->count,
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.filter = ConvertFStringToCharPtr(Datatype->filter),
		.orderBy = ConvertFStringToCharPtr(Datatype->orderBy)
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryTransactionClawbackDetails> ConvertTransactionClawbackDetailsToUnreal(const PFInventoryTransactionClawbackDetails* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryTransactionClawbackDetails> ConvertedType = MakeShared<FPFInventoryTransactionClawbackDetails>(FPFInventoryTransactionClawbackDetails{
		.transactionIdClawedback = Datatype->transactionIdClawedback == nullptr ? FString() : FString(Datatype->transactionIdClawedback)
	});

	return ConvertedType;
}

const PFInventoryTransactionClawbackDetails* ConvertTransactionClawbackDetailsToPlayfab(TSharedPtr<const FPFInventoryTransactionClawbackDetails> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryTransactionClawbackDetails* ConvertedType = new PFInventoryTransactionClawbackDetails{
		.transactionIdClawedback = ConvertFStringToCharPtr(Datatype->transactionIdClawedback)
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryTransactionOperation> ConvertTransactionOperationToUnreal(const PFInventoryTransactionOperation* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryTransactionOperation> ConvertedType = MakeShared<FPFInventoryTransactionOperation>(FPFInventoryTransactionOperation{
		.amount = TSharedPtr<const int32>(Datatype->amount),
		.durationInSeconds = TSharedPtr<const double>(Datatype->durationInSeconds),
		.itemFriendlyId = Datatype->itemFriendlyId == nullptr ? FString() : FString(Datatype->itemFriendlyId),
		.itemId = Datatype->itemId == nullptr ? FString() : FString(Datatype->itemId),
		.itemType = Datatype->itemType == nullptr ? FString() : FString(Datatype->itemType),
		.stackId = Datatype->stackId == nullptr ? FString() : FString(Datatype->stackId),
		.type = Datatype->type == nullptr ? FString() : FString(Datatype->type)
	});

	return ConvertedType;
}

const PFInventoryTransactionOperation* ConvertTransactionOperationToPlayfab(TSharedPtr<const FPFInventoryTransactionOperation> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryTransactionOperation* ConvertedType = new PFInventoryTransactionOperation{
		.amount = Datatype->amount ? new int32(*Datatype->amount) : nullptr,
		.durationInSeconds = Datatype->durationInSeconds ? new double(*Datatype->durationInSeconds) : nullptr,
		.itemFriendlyId = ConvertFStringToCharPtr(Datatype->itemFriendlyId),
		.itemId = ConvertFStringToCharPtr(Datatype->itemId),
		.itemType = ConvertFStringToCharPtr(Datatype->itemType),
		.stackId = ConvertFStringToCharPtr(Datatype->stackId),
		.type = ConvertFStringToCharPtr(Datatype->type)
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryTransactionPurchaseDetails> ConvertTransactionPurchaseDetailsToUnreal(const PFInventoryTransactionPurchaseDetails* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryTransactionPurchaseDetails> ConvertedType = MakeShared<FPFInventoryTransactionPurchaseDetails>(FPFInventoryTransactionPurchaseDetails{
		.itemFriendlyId = Datatype->itemFriendlyId == nullptr ? FString() : FString(Datatype->itemFriendlyId),
		.itemId = Datatype->itemId == nullptr ? FString() : FString(Datatype->itemId),
		.storeFriendlyId = Datatype->storeFriendlyId == nullptr ? FString() : FString(Datatype->storeFriendlyId),
		.storeId = Datatype->storeId == nullptr ? FString() : FString(Datatype->storeId)
	});

	return ConvertedType;
}

const PFInventoryTransactionPurchaseDetails* ConvertTransactionPurchaseDetailsToPlayfab(TSharedPtr<const FPFInventoryTransactionPurchaseDetails> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryTransactionPurchaseDetails* ConvertedType = new PFInventoryTransactionPurchaseDetails{
		.itemFriendlyId = ConvertFStringToCharPtr(Datatype->itemFriendlyId),
		.itemId = ConvertFStringToCharPtr(Datatype->itemId),
		.storeFriendlyId = ConvertFStringToCharPtr(Datatype->storeFriendlyId),
		.storeId = ConvertFStringToCharPtr(Datatype->storeId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryTransactionRedeemDetails> ConvertTransactionRedeemDetailsToUnreal(const PFInventoryTransactionRedeemDetails* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryTransactionRedeemDetails> ConvertedType = MakeShared<FPFInventoryTransactionRedeemDetails>(FPFInventoryTransactionRedeemDetails{
		.marketplace = Datatype->marketplace == nullptr ? FString() : FString(Datatype->marketplace),
		.marketplaceTransactionId = Datatype->marketplaceTransactionId == nullptr ? FString() : FString(Datatype->marketplaceTransactionId),
		.offerId = Datatype->offerId == nullptr ? FString() : FString(Datatype->offerId)
	});

	return ConvertedType;
}

const PFInventoryTransactionRedeemDetails* ConvertTransactionRedeemDetailsToPlayfab(TSharedPtr<const FPFInventoryTransactionRedeemDetails> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryTransactionRedeemDetails* ConvertedType = new PFInventoryTransactionRedeemDetails{
		.marketplace = ConvertFStringToCharPtr(Datatype->marketplace),
		.marketplaceTransactionId = ConvertFStringToCharPtr(Datatype->marketplaceTransactionId),
		.offerId = ConvertFStringToCharPtr(Datatype->offerId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryTransactionTransferDetails> ConvertTransactionTransferDetailsToUnreal(const PFInventoryTransactionTransferDetails* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryTransactionTransferDetails> ConvertedType = MakeShared<FPFInventoryTransactionTransferDetails>(FPFInventoryTransactionTransferDetails{
		.givingCollectionId = Datatype->givingCollectionId == nullptr ? FString() : FString(Datatype->givingCollectionId),
		.givingEntity = ConvertEntityKeyToUnreal(Datatype->givingEntity),
		.receivingCollectionId = Datatype->receivingCollectionId == nullptr ? FString() : FString(Datatype->receivingCollectionId),
		.receivingEntity = ConvertEntityKeyToUnreal(Datatype->receivingEntity),
		.transferId = Datatype->transferId == nullptr ? FString() : FString(Datatype->transferId)
	});

	return ConvertedType;
}

const PFInventoryTransactionTransferDetails* ConvertTransactionTransferDetailsToPlayfab(TSharedPtr<const FPFInventoryTransactionTransferDetails> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryTransactionTransferDetails* ConvertedType = new PFInventoryTransactionTransferDetails{
		.givingCollectionId = ConvertFStringToCharPtr(Datatype->givingCollectionId),
		.givingEntity = ConvertEntityKeyToPlayfab(Datatype->givingEntity),
		.receivingCollectionId = ConvertFStringToCharPtr(Datatype->receivingCollectionId),
		.receivingEntity = ConvertEntityKeyToPlayfab(Datatype->receivingEntity),
		.transferId = ConvertFStringToCharPtr(Datatype->transferId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryTransaction> ConvertTransactionToUnreal(const PFInventoryTransaction* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryTransaction> ConvertedType = MakeShared<FPFInventoryTransaction>(FPFInventoryTransaction{
		.apiName = Datatype->apiName == nullptr ? FString() : FString(Datatype->apiName),
		.clawbackDetails = ConvertTransactionClawbackDetailsToUnreal(Datatype->clawbackDetails),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.itemType = Datatype->itemType == nullptr ? FString() : FString(Datatype->itemType),
		.operations = ConvertPlayfabArrayToUnreal<PFInventoryTransactionOperation, FPFInventoryTransactionOperation>(Datatype->operations, Datatype->operationsCount, ConvertTransactionOperationToUnreal),
		.operationsCount = Datatype->operationsCount,
		.operationType = Datatype->operationType == nullptr ? FString() : FString(Datatype->operationType),
		.purchaseDetails = ConvertTransactionPurchaseDetailsToUnreal(Datatype->purchaseDetails),
		.redeemDetails = ConvertTransactionRedeemDetailsToUnreal(Datatype->redeemDetails),
		.timestamp = FDateTime::FromUnixTimestamp((int64)Datatype->timestamp),
		.transactionId = Datatype->transactionId == nullptr ? FString() : FString(Datatype->transactionId),
		.transferDetails = ConvertTransactionTransferDetailsToUnreal(Datatype->transferDetails)
	});

	return ConvertedType;
}

const PFInventoryTransaction* ConvertTransactionToPlayfab(TSharedPtr<const FPFInventoryTransaction> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryTransaction* ConvertedType = new PFInventoryTransaction{
		.apiName = ConvertFStringToCharPtr(Datatype->apiName),
		.clawbackDetails = ConvertTransactionClawbackDetailsToPlayfab(Datatype->clawbackDetails),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.itemType = ConvertFStringToCharPtr(Datatype->itemType),
		.operations = ConvertUnrealArrayToPlayfab<PFInventoryTransactionOperation, FPFInventoryTransactionOperation>(Datatype->operations, ConvertTransactionOperationToPlayfab),
		.operationsCount = (uint32_t)Datatype->operations.Num(),
		.operationType = ConvertFStringToCharPtr(Datatype->operationType),
		.purchaseDetails = ConvertTransactionPurchaseDetailsToPlayfab(Datatype->purchaseDetails),
		.redeemDetails = ConvertTransactionRedeemDetailsToPlayfab(Datatype->redeemDetails),
		.timestamp = Datatype->timestamp.ToUnixTimestamp(),
		.transactionId = ConvertFStringToCharPtr(Datatype->transactionId),
		.transferDetails = ConvertTransactionTransferDetailsToPlayfab(Datatype->transferDetails)
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryGetTransactionHistoryResponse> ConvertGetTransactionHistoryResponseToUnreal(const PFInventoryGetTransactionHistoryResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryGetTransactionHistoryResponse> ConvertedType = MakeShared<FPFInventoryGetTransactionHistoryResponse>(FPFInventoryGetTransactionHistoryResponse{
		.continuationToken = Datatype->continuationToken == nullptr ? FString() : FString(Datatype->continuationToken),
		.transactions = ConvertPlayfabArrayToUnreal<PFInventoryTransaction, FPFInventoryTransaction>(Datatype->transactions, Datatype->transactionsCount, ConvertTransactionToUnreal),
		.transactionsCount = Datatype->transactionsCount
	});

	return ConvertedType;
}

const PFInventoryGetTransactionHistoryResponse* ConvertGetTransactionHistoryResponseToPlayfab(TSharedPtr<const FPFInventoryGetTransactionHistoryResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryGetTransactionHistoryResponse* ConvertedType = new PFInventoryGetTransactionHistoryResponse{
		.continuationToken = ConvertFStringToCharPtr(Datatype->continuationToken),
		.transactions = ConvertUnrealArrayToPlayfab<PFInventoryTransaction, FPFInventoryTransaction>(Datatype->transactions, ConvertTransactionToPlayfab),
		.transactionsCount = (uint32_t)Datatype->transactions.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryPurchaseInventoryItemsRequest> ConvertPurchaseInventoryItemsRequestToUnreal(const PFInventoryPurchaseInventoryItemsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryPurchaseInventoryItemsRequest> ConvertedType = MakeShared<FPFInventoryPurchaseInventoryItemsRequest>(FPFInventoryPurchaseInventoryItemsRequest{
		.amount = TSharedPtr<const int32>(Datatype->amount),
		.collectionId = Datatype->collectionId == nullptr ? FString() : FString(Datatype->collectionId),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.deleteEmptyStacks = Datatype->deleteEmptyStacks,
		.durationInSeconds = TSharedPtr<const double>(Datatype->durationInSeconds),
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.eTag = Datatype->eTag == nullptr ? FString() : FString(Datatype->eTag),
		.idempotencyId = Datatype->idempotencyId == nullptr ? FString() : FString(Datatype->idempotencyId),
		.item = ConvertInventoryItemReferenceToUnreal(Datatype->item),
		.newStackValues = ConvertInitialValuesToUnreal(Datatype->newStackValues),
		.priceAmounts = ConvertPlayfabArrayToUnreal<PFInventoryPurchasePriceAmount, FPFInventoryPurchasePriceAmount>(Datatype->priceAmounts, Datatype->priceAmountsCount, ConvertPurchasePriceAmountToUnreal),
		.priceAmountsCount = Datatype->priceAmountsCount,
		.storeId = Datatype->storeId == nullptr ? FString() : FString(Datatype->storeId)
	});

	return ConvertedType;
}

const PFInventoryPurchaseInventoryItemsRequest* ConvertPurchaseInventoryItemsRequestToPlayfab(TSharedPtr<const FPFInventoryPurchaseInventoryItemsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryPurchaseInventoryItemsRequest* ConvertedType = new PFInventoryPurchaseInventoryItemsRequest{
		.amount = Datatype->amount ? new int32(*Datatype->amount) : nullptr,
		.collectionId = ConvertFStringToCharPtr(Datatype->collectionId),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.deleteEmptyStacks = Datatype->deleteEmptyStacks,
		.durationInSeconds = Datatype->durationInSeconds ? new double(*Datatype->durationInSeconds) : nullptr,
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.eTag = ConvertFStringToCharPtr(Datatype->eTag),
		.idempotencyId = ConvertFStringToCharPtr(Datatype->idempotencyId),
		.item = ConvertInventoryItemReferenceToPlayfab(Datatype->item),
		.newStackValues = ConvertInitialValuesToPlayfab(Datatype->newStackValues),
		.priceAmounts = ConvertUnrealArrayToPlayfab<PFInventoryPurchasePriceAmount, FPFInventoryPurchasePriceAmount>(Datatype->priceAmounts, ConvertPurchasePriceAmountToPlayfab),
		.priceAmountsCount = (uint32_t)Datatype->priceAmounts.Num(),
		.storeId = ConvertFStringToCharPtr(Datatype->storeId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryPurchaseInventoryItemsResponse> ConvertPurchaseInventoryItemsResponseToUnreal(const PFInventoryPurchaseInventoryItemsResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryPurchaseInventoryItemsResponse> ConvertedType = MakeShared<FPFInventoryPurchaseInventoryItemsResponse>(FPFInventoryPurchaseInventoryItemsResponse{
		.eTag = Datatype->eTag == nullptr ? FString() : FString(Datatype->eTag),
		.idempotencyId = Datatype->idempotencyId == nullptr ? FString() : FString(Datatype->idempotencyId),
		.transactionIds = ConvertCharArrayToUnreal(Datatype->transactionIds, Datatype->transactionIdsCount),
		.transactionIdsCount = Datatype->transactionIdsCount
	});

	return ConvertedType;
}

const PFInventoryPurchaseInventoryItemsResponse* ConvertPurchaseInventoryItemsResponseToPlayfab(TSharedPtr<const FPFInventoryPurchaseInventoryItemsResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryPurchaseInventoryItemsResponse* ConvertedType = new PFInventoryPurchaseInventoryItemsResponse{
		.eTag = ConvertFStringToCharPtr(Datatype->eTag),
		.idempotencyId = ConvertFStringToCharPtr(Datatype->idempotencyId),
		.transactionIds = ConvertFStringArrayToPlayfab(Datatype->transactionIds),
		.transactionIdsCount = (uint32_t)Datatype->transactionIds.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryRedeemAppleAppStoreInventoryItemsRequest> ConvertRedeemAppleAppStoreInventoryItemsRequestToUnreal(const PFInventoryRedeemAppleAppStoreInventoryItemsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryRedeemAppleAppStoreInventoryItemsRequest> ConvertedType = MakeShared<FPFInventoryRedeemAppleAppStoreInventoryItemsRequest>(FPFInventoryRedeemAppleAppStoreInventoryItemsRequest{
		.collectionId = Datatype->collectionId == nullptr ? FString() : FString(Datatype->collectionId),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.receipt = Datatype->receipt == nullptr ? FString() : FString(Datatype->receipt)
	});

	return ConvertedType;
}

const PFInventoryRedeemAppleAppStoreInventoryItemsRequest* ConvertRedeemAppleAppStoreInventoryItemsRequestToPlayfab(TSharedPtr<const FPFInventoryRedeemAppleAppStoreInventoryItemsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryRedeemAppleAppStoreInventoryItemsRequest* ConvertedType = new PFInventoryRedeemAppleAppStoreInventoryItemsRequest{
		.collectionId = ConvertFStringToCharPtr(Datatype->collectionId),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.receipt = ConvertFStringToCharPtr(Datatype->receipt)
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryRedemptionFailure> ConvertRedemptionFailureToUnreal(const PFInventoryRedemptionFailure* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryRedemptionFailure> ConvertedType = MakeShared<FPFInventoryRedemptionFailure>(FPFInventoryRedemptionFailure{
		.failureCode = Datatype->failureCode == nullptr ? FString() : FString(Datatype->failureCode),
		.failureDetails = Datatype->failureDetails == nullptr ? FString() : FString(Datatype->failureDetails),
		.marketplaceAlternateId = Datatype->marketplaceAlternateId == nullptr ? FString() : FString(Datatype->marketplaceAlternateId),
		.marketplaceTransactionId = Datatype->marketplaceTransactionId == nullptr ? FString() : FString(Datatype->marketplaceTransactionId)
	});

	return ConvertedType;
}

const PFInventoryRedemptionFailure* ConvertRedemptionFailureToPlayfab(TSharedPtr<const FPFInventoryRedemptionFailure> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryRedemptionFailure* ConvertedType = new PFInventoryRedemptionFailure{
		.failureCode = ConvertFStringToCharPtr(Datatype->failureCode),
		.failureDetails = ConvertFStringToCharPtr(Datatype->failureDetails),
		.marketplaceAlternateId = ConvertFStringToCharPtr(Datatype->marketplaceAlternateId),
		.marketplaceTransactionId = ConvertFStringToCharPtr(Datatype->marketplaceTransactionId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryRedemptionSuccess> ConvertRedemptionSuccessToUnreal(const PFInventoryRedemptionSuccess* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryRedemptionSuccess> ConvertedType = MakeShared<FPFInventoryRedemptionSuccess>(FPFInventoryRedemptionSuccess{
		.marketplaceAlternateId = Datatype->marketplaceAlternateId == nullptr ? FString() : FString(Datatype->marketplaceAlternateId),
		.marketplaceTransactionId = Datatype->marketplaceTransactionId == nullptr ? FString() : FString(Datatype->marketplaceTransactionId),
		.successTimestamp = FDateTime::FromUnixTimestamp((int64)Datatype->successTimestamp)
	});

	return ConvertedType;
}

const PFInventoryRedemptionSuccess* ConvertRedemptionSuccessToPlayfab(TSharedPtr<const FPFInventoryRedemptionSuccess> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryRedemptionSuccess* ConvertedType = new PFInventoryRedemptionSuccess{
		.marketplaceAlternateId = ConvertFStringToCharPtr(Datatype->marketplaceAlternateId),
		.marketplaceTransactionId = ConvertFStringToCharPtr(Datatype->marketplaceTransactionId),
		.successTimestamp = Datatype->successTimestamp.ToUnixTimestamp()
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryRedeemAppleAppStoreInventoryItemsResponse> ConvertRedeemAppleAppStoreInventoryItemsResponseToUnreal(const PFInventoryRedeemAppleAppStoreInventoryItemsResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryRedeemAppleAppStoreInventoryItemsResponse> ConvertedType = MakeShared<FPFInventoryRedeemAppleAppStoreInventoryItemsResponse>(FPFInventoryRedeemAppleAppStoreInventoryItemsResponse{
		.failed = ConvertPlayfabArrayToUnreal<PFInventoryRedemptionFailure, FPFInventoryRedemptionFailure>(Datatype->failed, Datatype->failedCount, ConvertRedemptionFailureToUnreal),
		.failedCount = Datatype->failedCount,
		.succeeded = ConvertPlayfabArrayToUnreal<PFInventoryRedemptionSuccess, FPFInventoryRedemptionSuccess>(Datatype->succeeded, Datatype->succeededCount, ConvertRedemptionSuccessToUnreal),
		.succeededCount = Datatype->succeededCount,
		.transactionIds = ConvertCharArrayToUnreal(Datatype->transactionIds, Datatype->transactionIdsCount),
		.transactionIdsCount = Datatype->transactionIdsCount
	});

	return ConvertedType;
}

const PFInventoryRedeemAppleAppStoreInventoryItemsResponse* ConvertRedeemAppleAppStoreInventoryItemsResponseToPlayfab(TSharedPtr<const FPFInventoryRedeemAppleAppStoreInventoryItemsResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryRedeemAppleAppStoreInventoryItemsResponse* ConvertedType = new PFInventoryRedeemAppleAppStoreInventoryItemsResponse{
		.failed = ConvertUnrealArrayToPlayfab<PFInventoryRedemptionFailure, FPFInventoryRedemptionFailure>(Datatype->failed, ConvertRedemptionFailureToPlayfab),
		.failedCount = (uint32_t)Datatype->failed.Num(),
		.succeeded = ConvertUnrealArrayToPlayfab<PFInventoryRedemptionSuccess, FPFInventoryRedemptionSuccess>(Datatype->succeeded, ConvertRedemptionSuccessToPlayfab),
		.succeededCount = (uint32_t)Datatype->succeeded.Num(),
		.transactionIds = ConvertFStringArrayToPlayfab(Datatype->transactionIds),
		.transactionIdsCount = (uint32_t)Datatype->transactionIds.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryGooglePlayProductPurchase> ConvertGooglePlayProductPurchaseToUnreal(const PFInventoryGooglePlayProductPurchase* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryGooglePlayProductPurchase> ConvertedType = MakeShared<FPFInventoryGooglePlayProductPurchase>(FPFInventoryGooglePlayProductPurchase{
		.productId = Datatype->productId == nullptr ? FString() : FString(Datatype->productId),
		.token = Datatype->token == nullptr ? FString() : FString(Datatype->token)
	});

	return ConvertedType;
}

const PFInventoryGooglePlayProductPurchase* ConvertGooglePlayProductPurchaseToPlayfab(TSharedPtr<const FPFInventoryGooglePlayProductPurchase> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryGooglePlayProductPurchase* ConvertedType = new PFInventoryGooglePlayProductPurchase{
		.productId = ConvertFStringToCharPtr(Datatype->productId),
		.token = ConvertFStringToCharPtr(Datatype->token)
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryRedeemGooglePlayInventoryItemsRequest> ConvertRedeemGooglePlayInventoryItemsRequestToUnreal(const PFInventoryRedeemGooglePlayInventoryItemsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryRedeemGooglePlayInventoryItemsRequest> ConvertedType = MakeShared<FPFInventoryRedeemGooglePlayInventoryItemsRequest>(FPFInventoryRedeemGooglePlayInventoryItemsRequest{
		.collectionId = Datatype->collectionId == nullptr ? FString() : FString(Datatype->collectionId),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.purchases = ConvertPlayfabArrayToUnreal<PFInventoryGooglePlayProductPurchase, FPFInventoryGooglePlayProductPurchase>(Datatype->purchases, Datatype->purchasesCount, ConvertGooglePlayProductPurchaseToUnreal),
		.purchasesCount = Datatype->purchasesCount
	});

	return ConvertedType;
}

const PFInventoryRedeemGooglePlayInventoryItemsRequest* ConvertRedeemGooglePlayInventoryItemsRequestToPlayfab(TSharedPtr<const FPFInventoryRedeemGooglePlayInventoryItemsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryRedeemGooglePlayInventoryItemsRequest* ConvertedType = new PFInventoryRedeemGooglePlayInventoryItemsRequest{
		.collectionId = ConvertFStringToCharPtr(Datatype->collectionId),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.purchases = ConvertUnrealArrayToPlayfab<PFInventoryGooglePlayProductPurchase, FPFInventoryGooglePlayProductPurchase>(Datatype->purchases, ConvertGooglePlayProductPurchaseToPlayfab),
		.purchasesCount = (uint32_t)Datatype->purchases.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryRedeemGooglePlayInventoryItemsResponse> ConvertRedeemGooglePlayInventoryItemsResponseToUnreal(const PFInventoryRedeemGooglePlayInventoryItemsResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryRedeemGooglePlayInventoryItemsResponse> ConvertedType = MakeShared<FPFInventoryRedeemGooglePlayInventoryItemsResponse>(FPFInventoryRedeemGooglePlayInventoryItemsResponse{
		.failed = ConvertPlayfabArrayToUnreal<PFInventoryRedemptionFailure, FPFInventoryRedemptionFailure>(Datatype->failed, Datatype->failedCount, ConvertRedemptionFailureToUnreal),
		.failedCount = Datatype->failedCount,
		.succeeded = ConvertPlayfabArrayToUnreal<PFInventoryRedemptionSuccess, FPFInventoryRedemptionSuccess>(Datatype->succeeded, Datatype->succeededCount, ConvertRedemptionSuccessToUnreal),
		.succeededCount = Datatype->succeededCount,
		.transactionIds = ConvertCharArrayToUnreal(Datatype->transactionIds, Datatype->transactionIdsCount),
		.transactionIdsCount = Datatype->transactionIdsCount
	});

	return ConvertedType;
}

const PFInventoryRedeemGooglePlayInventoryItemsResponse* ConvertRedeemGooglePlayInventoryItemsResponseToPlayfab(TSharedPtr<const FPFInventoryRedeemGooglePlayInventoryItemsResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryRedeemGooglePlayInventoryItemsResponse* ConvertedType = new PFInventoryRedeemGooglePlayInventoryItemsResponse{
		.failed = ConvertUnrealArrayToPlayfab<PFInventoryRedemptionFailure, FPFInventoryRedemptionFailure>(Datatype->failed, ConvertRedemptionFailureToPlayfab),
		.failedCount = (uint32_t)Datatype->failed.Num(),
		.succeeded = ConvertUnrealArrayToPlayfab<PFInventoryRedemptionSuccess, FPFInventoryRedemptionSuccess>(Datatype->succeeded, ConvertRedemptionSuccessToPlayfab),
		.succeededCount = (uint32_t)Datatype->succeeded.Num(),
		.transactionIds = ConvertFStringArrayToPlayfab(Datatype->transactionIds),
		.transactionIdsCount = (uint32_t)Datatype->transactionIds.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryRedeemMicrosoftStoreInventoryItemsRequest> ConvertRedeemMicrosoftStoreInventoryItemsRequestToUnreal(const PFInventoryRedeemMicrosoftStoreInventoryItemsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryRedeemMicrosoftStoreInventoryItemsRequest> ConvertedType = MakeShared<FPFInventoryRedeemMicrosoftStoreInventoryItemsRequest>(FPFInventoryRedeemMicrosoftStoreInventoryItemsRequest{
		.collectionId = Datatype->collectionId == nullptr ? FString() : FString(Datatype->collectionId),
		.collectionsIdKey = Datatype->collectionsIdKey == nullptr ? FString() : FString(Datatype->collectionsIdKey),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
#if defined(PF_GDK_AVAILABLE) && defined(PF_UE_GDK_SUPPORT)
		.user = Datatype->user == nullptr ? FGDKUserHandle() : FGDKUserHandle(Datatype->user)
#elif defined(PF_GDK_AVAILABLE)
		.user = Datatype->user == nullptr ? XUserHandle() : Datatype->user
#else
		.xboxToken = Datatype->xboxToken == nullptr ? FString() : FString(Datatype->xboxToken)
#endif
	});

	return ConvertedType;
}

const PFInventoryRedeemMicrosoftStoreInventoryItemsRequest* ConvertRedeemMicrosoftStoreInventoryItemsRequestToPlayfab(TSharedPtr<const FPFInventoryRedeemMicrosoftStoreInventoryItemsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryRedeemMicrosoftStoreInventoryItemsRequest* ConvertedType = new PFInventoryRedeemMicrosoftStoreInventoryItemsRequest{
		.collectionId = ConvertFStringToCharPtr(Datatype->collectionId),
		.collectionsIdKey = ConvertFStringToCharPtr(Datatype->collectionsIdKey),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
#if defined(PF_GDK_AVAILABLE)
		.user = Datatype->user
#else
		.xboxToken = ConvertFStringToCharPtr(Datatype->xboxToken)
#endif
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryRedeemMicrosoftStoreInventoryItemsResponse> ConvertRedeemMicrosoftStoreInventoryItemsResponseToUnreal(const PFInventoryRedeemMicrosoftStoreInventoryItemsResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryRedeemMicrosoftStoreInventoryItemsResponse> ConvertedType = MakeShared<FPFInventoryRedeemMicrosoftStoreInventoryItemsResponse>(FPFInventoryRedeemMicrosoftStoreInventoryItemsResponse{
		.failed = ConvertPlayfabArrayToUnreal<PFInventoryRedemptionFailure, FPFInventoryRedemptionFailure>(Datatype->failed, Datatype->failedCount, ConvertRedemptionFailureToUnreal),
		.failedCount = Datatype->failedCount,
		.succeeded = ConvertPlayfabArrayToUnreal<PFInventoryRedemptionSuccess, FPFInventoryRedemptionSuccess>(Datatype->succeeded, Datatype->succeededCount, ConvertRedemptionSuccessToUnreal),
		.succeededCount = Datatype->succeededCount,
		.transactionIds = ConvertCharArrayToUnreal(Datatype->transactionIds, Datatype->transactionIdsCount),
		.transactionIdsCount = Datatype->transactionIdsCount
	});

	return ConvertedType;
}

const PFInventoryRedeemMicrosoftStoreInventoryItemsResponse* ConvertRedeemMicrosoftStoreInventoryItemsResponseToPlayfab(TSharedPtr<const FPFInventoryRedeemMicrosoftStoreInventoryItemsResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryRedeemMicrosoftStoreInventoryItemsResponse* ConvertedType = new PFInventoryRedeemMicrosoftStoreInventoryItemsResponse{
		.failed = ConvertUnrealArrayToPlayfab<PFInventoryRedemptionFailure, FPFInventoryRedemptionFailure>(Datatype->failed, ConvertRedemptionFailureToPlayfab),
		.failedCount = (uint32_t)Datatype->failed.Num(),
		.succeeded = ConvertUnrealArrayToPlayfab<PFInventoryRedemptionSuccess, FPFInventoryRedemptionSuccess>(Datatype->succeeded, ConvertRedemptionSuccessToPlayfab),
		.succeededCount = (uint32_t)Datatype->succeeded.Num(),
		.transactionIds = ConvertFStringArrayToPlayfab(Datatype->transactionIds),
		.transactionIdsCount = (uint32_t)Datatype->transactionIds.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryRedeemNintendoEShopInventoryItemsRequest> ConvertRedeemNintendoEShopInventoryItemsRequestToUnreal(const PFInventoryRedeemNintendoEShopInventoryItemsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryRedeemNintendoEShopInventoryItemsRequest> ConvertedType = MakeShared<FPFInventoryRedeemNintendoEShopInventoryItemsRequest>(FPFInventoryRedeemNintendoEShopInventoryItemsRequest{
		.collectionId = Datatype->collectionId == nullptr ? FString() : FString(Datatype->collectionId),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.nintendoServiceAccountIdToken = Datatype->nintendoServiceAccountIdToken == nullptr ? FString() : FString(Datatype->nintendoServiceAccountIdToken)
	});

	return ConvertedType;
}

const PFInventoryRedeemNintendoEShopInventoryItemsRequest* ConvertRedeemNintendoEShopInventoryItemsRequestToPlayfab(TSharedPtr<const FPFInventoryRedeemNintendoEShopInventoryItemsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryRedeemNintendoEShopInventoryItemsRequest* ConvertedType = new PFInventoryRedeemNintendoEShopInventoryItemsRequest{
		.collectionId = ConvertFStringToCharPtr(Datatype->collectionId),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.nintendoServiceAccountIdToken = ConvertFStringToCharPtr(Datatype->nintendoServiceAccountIdToken)
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryRedeemNintendoEShopInventoryItemsResponse> ConvertRedeemNintendoEShopInventoryItemsResponseToUnreal(const PFInventoryRedeemNintendoEShopInventoryItemsResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryRedeemNintendoEShopInventoryItemsResponse> ConvertedType = MakeShared<FPFInventoryRedeemNintendoEShopInventoryItemsResponse>(FPFInventoryRedeemNintendoEShopInventoryItemsResponse{
		.failed = ConvertPlayfabArrayToUnreal<PFInventoryRedemptionFailure, FPFInventoryRedemptionFailure>(Datatype->failed, Datatype->failedCount, ConvertRedemptionFailureToUnreal),
		.failedCount = Datatype->failedCount,
		.succeeded = ConvertPlayfabArrayToUnreal<PFInventoryRedemptionSuccess, FPFInventoryRedemptionSuccess>(Datatype->succeeded, Datatype->succeededCount, ConvertRedemptionSuccessToUnreal),
		.succeededCount = Datatype->succeededCount,
		.transactionIds = ConvertCharArrayToUnreal(Datatype->transactionIds, Datatype->transactionIdsCount),
		.transactionIdsCount = Datatype->transactionIdsCount
	});

	return ConvertedType;
}

const PFInventoryRedeemNintendoEShopInventoryItemsResponse* ConvertRedeemNintendoEShopInventoryItemsResponseToPlayfab(TSharedPtr<const FPFInventoryRedeemNintendoEShopInventoryItemsResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryRedeemNintendoEShopInventoryItemsResponse* ConvertedType = new PFInventoryRedeemNintendoEShopInventoryItemsResponse{
		.failed = ConvertUnrealArrayToPlayfab<PFInventoryRedemptionFailure, FPFInventoryRedemptionFailure>(Datatype->failed, ConvertRedemptionFailureToPlayfab),
		.failedCount = (uint32_t)Datatype->failed.Num(),
		.succeeded = ConvertUnrealArrayToPlayfab<PFInventoryRedemptionSuccess, FPFInventoryRedemptionSuccess>(Datatype->succeeded, ConvertRedemptionSuccessToPlayfab),
		.succeededCount = (uint32_t)Datatype->succeeded.Num(),
		.transactionIds = ConvertFStringArrayToPlayfab(Datatype->transactionIds),
		.transactionIdsCount = (uint32_t)Datatype->transactionIds.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryRedeemPlayStationStoreInventoryItemsRequest> ConvertRedeemPlayStationStoreInventoryItemsRequestToUnreal(const PFInventoryRedeemPlayStationStoreInventoryItemsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryRedeemPlayStationStoreInventoryItemsRequest> ConvertedType = MakeShared<FPFInventoryRedeemPlayStationStoreInventoryItemsRequest>(FPFInventoryRedeemPlayStationStoreInventoryItemsRequest{
		.authorizationCode = Datatype->authorizationCode == nullptr ? FString() : FString(Datatype->authorizationCode),
		.collectionId = Datatype->collectionId == nullptr ? FString() : FString(Datatype->collectionId),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.redirectUri = Datatype->redirectUri == nullptr ? FString() : FString(Datatype->redirectUri),
		.serviceLabel = Datatype->serviceLabel == nullptr ? FString() : FString(Datatype->serviceLabel)
	});

	return ConvertedType;
}

const PFInventoryRedeemPlayStationStoreInventoryItemsRequest* ConvertRedeemPlayStationStoreInventoryItemsRequestToPlayfab(TSharedPtr<const FPFInventoryRedeemPlayStationStoreInventoryItemsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryRedeemPlayStationStoreInventoryItemsRequest* ConvertedType = new PFInventoryRedeemPlayStationStoreInventoryItemsRequest{
		.authorizationCode = ConvertFStringToCharPtr(Datatype->authorizationCode),
		.collectionId = ConvertFStringToCharPtr(Datatype->collectionId),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.redirectUri = ConvertFStringToCharPtr(Datatype->redirectUri),
		.serviceLabel = ConvertFStringToCharPtr(Datatype->serviceLabel)
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryRedeemPlayStationStoreInventoryItemsResponse> ConvertRedeemPlayStationStoreInventoryItemsResponseToUnreal(const PFInventoryRedeemPlayStationStoreInventoryItemsResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryRedeemPlayStationStoreInventoryItemsResponse> ConvertedType = MakeShared<FPFInventoryRedeemPlayStationStoreInventoryItemsResponse>(FPFInventoryRedeemPlayStationStoreInventoryItemsResponse{
		.failed = ConvertPlayfabArrayToUnreal<PFInventoryRedemptionFailure, FPFInventoryRedemptionFailure>(Datatype->failed, Datatype->failedCount, ConvertRedemptionFailureToUnreal),
		.failedCount = Datatype->failedCount,
		.succeeded = ConvertPlayfabArrayToUnreal<PFInventoryRedemptionSuccess, FPFInventoryRedemptionSuccess>(Datatype->succeeded, Datatype->succeededCount, ConvertRedemptionSuccessToUnreal),
		.succeededCount = Datatype->succeededCount,
		.transactionIds = ConvertCharArrayToUnreal(Datatype->transactionIds, Datatype->transactionIdsCount),
		.transactionIdsCount = Datatype->transactionIdsCount
	});

	return ConvertedType;
}

const PFInventoryRedeemPlayStationStoreInventoryItemsResponse* ConvertRedeemPlayStationStoreInventoryItemsResponseToPlayfab(TSharedPtr<const FPFInventoryRedeemPlayStationStoreInventoryItemsResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryRedeemPlayStationStoreInventoryItemsResponse* ConvertedType = new PFInventoryRedeemPlayStationStoreInventoryItemsResponse{
		.failed = ConvertUnrealArrayToPlayfab<PFInventoryRedemptionFailure, FPFInventoryRedemptionFailure>(Datatype->failed, ConvertRedemptionFailureToPlayfab),
		.failedCount = (uint32_t)Datatype->failed.Num(),
		.succeeded = ConvertUnrealArrayToPlayfab<PFInventoryRedemptionSuccess, FPFInventoryRedemptionSuccess>(Datatype->succeeded, ConvertRedemptionSuccessToPlayfab),
		.succeededCount = (uint32_t)Datatype->succeeded.Num(),
		.transactionIds = ConvertFStringArrayToPlayfab(Datatype->transactionIds),
		.transactionIdsCount = (uint32_t)Datatype->transactionIds.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryRedeemSteamInventoryItemsRequest> ConvertRedeemSteamInventoryItemsRequestToUnreal(const PFInventoryRedeemSteamInventoryItemsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryRedeemSteamInventoryItemsRequest> ConvertedType = MakeShared<FPFInventoryRedeemSteamInventoryItemsRequest>(FPFInventoryRedeemSteamInventoryItemsRequest{
		.collectionId = Datatype->collectionId == nullptr ? FString() : FString(Datatype->collectionId),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity)
	});

	return ConvertedType;
}

const PFInventoryRedeemSteamInventoryItemsRequest* ConvertRedeemSteamInventoryItemsRequestToPlayfab(TSharedPtr<const FPFInventoryRedeemSteamInventoryItemsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryRedeemSteamInventoryItemsRequest* ConvertedType = new PFInventoryRedeemSteamInventoryItemsRequest{
		.collectionId = ConvertFStringToCharPtr(Datatype->collectionId),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity)
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryRedeemSteamInventoryItemsResponse> ConvertRedeemSteamInventoryItemsResponseToUnreal(const PFInventoryRedeemSteamInventoryItemsResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryRedeemSteamInventoryItemsResponse> ConvertedType = MakeShared<FPFInventoryRedeemSteamInventoryItemsResponse>(FPFInventoryRedeemSteamInventoryItemsResponse{
		.failed = ConvertPlayfabArrayToUnreal<PFInventoryRedemptionFailure, FPFInventoryRedemptionFailure>(Datatype->failed, Datatype->failedCount, ConvertRedemptionFailureToUnreal),
		.failedCount = Datatype->failedCount,
		.succeeded = ConvertPlayfabArrayToUnreal<PFInventoryRedemptionSuccess, FPFInventoryRedemptionSuccess>(Datatype->succeeded, Datatype->succeededCount, ConvertRedemptionSuccessToUnreal),
		.succeededCount = Datatype->succeededCount,
		.transactionIds = ConvertCharArrayToUnreal(Datatype->transactionIds, Datatype->transactionIdsCount),
		.transactionIdsCount = Datatype->transactionIdsCount
	});

	return ConvertedType;
}

const PFInventoryRedeemSteamInventoryItemsResponse* ConvertRedeemSteamInventoryItemsResponseToPlayfab(TSharedPtr<const FPFInventoryRedeemSteamInventoryItemsResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryRedeemSteamInventoryItemsResponse* ConvertedType = new PFInventoryRedeemSteamInventoryItemsResponse{
		.failed = ConvertUnrealArrayToPlayfab<PFInventoryRedemptionFailure, FPFInventoryRedemptionFailure>(Datatype->failed, ConvertRedemptionFailureToPlayfab),
		.failedCount = (uint32_t)Datatype->failed.Num(),
		.succeeded = ConvertUnrealArrayToPlayfab<PFInventoryRedemptionSuccess, FPFInventoryRedemptionSuccess>(Datatype->succeeded, ConvertRedemptionSuccessToPlayfab),
		.succeededCount = (uint32_t)Datatype->succeeded.Num(),
		.transactionIds = ConvertFStringArrayToPlayfab(Datatype->transactionIds),
		.transactionIdsCount = (uint32_t)Datatype->transactionIds.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventorySubtractInventoryItemsRequest> ConvertSubtractInventoryItemsRequestToUnreal(const PFInventorySubtractInventoryItemsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventorySubtractInventoryItemsRequest> ConvertedType = MakeShared<FPFInventorySubtractInventoryItemsRequest>(FPFInventorySubtractInventoryItemsRequest{
		.amount = TSharedPtr<const int32>(Datatype->amount),
		.collectionId = Datatype->collectionId == nullptr ? FString() : FString(Datatype->collectionId),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.deleteEmptyStacks = Datatype->deleteEmptyStacks,
		.durationInSeconds = TSharedPtr<const double>(Datatype->durationInSeconds),
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.eTag = Datatype->eTag == nullptr ? FString() : FString(Datatype->eTag),
		.idempotencyId = Datatype->idempotencyId == nullptr ? FString() : FString(Datatype->idempotencyId),
		.item = ConvertInventoryItemReferenceToUnreal(Datatype->item)
	});

	return ConvertedType;
}

const PFInventorySubtractInventoryItemsRequest* ConvertSubtractInventoryItemsRequestToPlayfab(TSharedPtr<const FPFInventorySubtractInventoryItemsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventorySubtractInventoryItemsRequest* ConvertedType = new PFInventorySubtractInventoryItemsRequest{
		.amount = Datatype->amount ? new int32(*Datatype->amount) : nullptr,
		.collectionId = ConvertFStringToCharPtr(Datatype->collectionId),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.deleteEmptyStacks = Datatype->deleteEmptyStacks,
		.durationInSeconds = Datatype->durationInSeconds ? new double(*Datatype->durationInSeconds) : nullptr,
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.eTag = ConvertFStringToCharPtr(Datatype->eTag),
		.idempotencyId = ConvertFStringToCharPtr(Datatype->idempotencyId),
		.item = ConvertInventoryItemReferenceToPlayfab(Datatype->item)
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventorySubtractInventoryItemsResponse> ConvertSubtractInventoryItemsResponseToUnreal(const PFInventorySubtractInventoryItemsResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventorySubtractInventoryItemsResponse> ConvertedType = MakeShared<FPFInventorySubtractInventoryItemsResponse>(FPFInventorySubtractInventoryItemsResponse{
		.eTag = Datatype->eTag == nullptr ? FString() : FString(Datatype->eTag),
		.idempotencyId = Datatype->idempotencyId == nullptr ? FString() : FString(Datatype->idempotencyId),
		.transactionIds = ConvertCharArrayToUnreal(Datatype->transactionIds, Datatype->transactionIdsCount),
		.transactionIdsCount = Datatype->transactionIdsCount
	});

	return ConvertedType;
}

const PFInventorySubtractInventoryItemsResponse* ConvertSubtractInventoryItemsResponseToPlayfab(TSharedPtr<const FPFInventorySubtractInventoryItemsResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventorySubtractInventoryItemsResponse* ConvertedType = new PFInventorySubtractInventoryItemsResponse{
		.eTag = ConvertFStringToCharPtr(Datatype->eTag),
		.idempotencyId = ConvertFStringToCharPtr(Datatype->idempotencyId),
		.transactionIds = ConvertFStringArrayToPlayfab(Datatype->transactionIds),
		.transactionIdsCount = (uint32_t)Datatype->transactionIds.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryTransferInventoryItemsRequest> ConvertTransferInventoryItemsRequestToUnreal(const PFInventoryTransferInventoryItemsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryTransferInventoryItemsRequest> ConvertedType = MakeShared<FPFInventoryTransferInventoryItemsRequest>(FPFInventoryTransferInventoryItemsRequest{
		.amount = TSharedPtr<const int32>(Datatype->amount),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.deleteEmptyStacks = Datatype->deleteEmptyStacks,
		.givingCollectionId = Datatype->givingCollectionId == nullptr ? FString() : FString(Datatype->givingCollectionId),
		.givingEntity = ConvertEntityKeyToUnreal(Datatype->givingEntity),
		.givingETag = Datatype->givingETag == nullptr ? FString() : FString(Datatype->givingETag),
		.givingItem = ConvertInventoryItemReferenceToUnreal(Datatype->givingItem),
		.idempotencyId = Datatype->idempotencyId == nullptr ? FString() : FString(Datatype->idempotencyId),
		.newStackValues = ConvertInitialValuesToUnreal(Datatype->newStackValues),
		.receivingCollectionId = Datatype->receivingCollectionId == nullptr ? FString() : FString(Datatype->receivingCollectionId),
		.receivingEntity = ConvertEntityKeyToUnreal(Datatype->receivingEntity),
		.receivingItem = ConvertInventoryItemReferenceToUnreal(Datatype->receivingItem)
	});

	return ConvertedType;
}

const PFInventoryTransferInventoryItemsRequest* ConvertTransferInventoryItemsRequestToPlayfab(TSharedPtr<const FPFInventoryTransferInventoryItemsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryTransferInventoryItemsRequest* ConvertedType = new PFInventoryTransferInventoryItemsRequest{
		.amount = Datatype->amount ? new int32(*Datatype->amount) : nullptr,
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.deleteEmptyStacks = Datatype->deleteEmptyStacks,
		.givingCollectionId = ConvertFStringToCharPtr(Datatype->givingCollectionId),
		.givingEntity = ConvertEntityKeyToPlayfab(Datatype->givingEntity),
		.givingETag = ConvertFStringToCharPtr(Datatype->givingETag),
		.givingItem = ConvertInventoryItemReferenceToPlayfab(Datatype->givingItem),
		.idempotencyId = ConvertFStringToCharPtr(Datatype->idempotencyId),
		.newStackValues = ConvertInitialValuesToPlayfab(Datatype->newStackValues),
		.receivingCollectionId = ConvertFStringToCharPtr(Datatype->receivingCollectionId),
		.receivingEntity = ConvertEntityKeyToPlayfab(Datatype->receivingEntity),
		.receivingItem = ConvertInventoryItemReferenceToPlayfab(Datatype->receivingItem)
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryTransferInventoryItemsResponse> ConvertTransferInventoryItemsResponseToUnreal(const PFInventoryTransferInventoryItemsResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryTransferInventoryItemsResponse> ConvertedType = MakeShared<FPFInventoryTransferInventoryItemsResponse>(FPFInventoryTransferInventoryItemsResponse{
		.givingETag = Datatype->givingETag == nullptr ? FString() : FString(Datatype->givingETag),
		.givingTransactionIds = ConvertCharArrayToUnreal(Datatype->givingTransactionIds, Datatype->givingTransactionIdsCount),
		.givingTransactionIdsCount = Datatype->givingTransactionIdsCount,
		.idempotencyId = Datatype->idempotencyId == nullptr ? FString() : FString(Datatype->idempotencyId),
		.operationStatus = Datatype->operationStatus == nullptr ? FString() : FString(Datatype->operationStatus),
		.operationToken = Datatype->operationToken == nullptr ? FString() : FString(Datatype->operationToken),
		.receivingTransactionIds = ConvertCharArrayToUnreal(Datatype->receivingTransactionIds, Datatype->receivingTransactionIdsCount),
		.receivingTransactionIdsCount = Datatype->receivingTransactionIdsCount
	});

	return ConvertedType;
}

const PFInventoryTransferInventoryItemsResponse* ConvertTransferInventoryItemsResponseToPlayfab(TSharedPtr<const FPFInventoryTransferInventoryItemsResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryTransferInventoryItemsResponse* ConvertedType = new PFInventoryTransferInventoryItemsResponse{
		.givingETag = ConvertFStringToCharPtr(Datatype->givingETag),
		.givingTransactionIds = ConvertFStringArrayToPlayfab(Datatype->givingTransactionIds),
		.givingTransactionIdsCount = (uint32_t)Datatype->givingTransactionIds.Num(),
		.idempotencyId = ConvertFStringToCharPtr(Datatype->idempotencyId),
		.operationStatus = ConvertFStringToCharPtr(Datatype->operationStatus),
		.operationToken = ConvertFStringToCharPtr(Datatype->operationToken),
		.receivingTransactionIds = ConvertFStringArrayToPlayfab(Datatype->receivingTransactionIds),
		.receivingTransactionIdsCount = (uint32_t)Datatype->receivingTransactionIds.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryUpdateInventoryItemsRequest> ConvertUpdateInventoryItemsRequestToUnreal(const PFInventoryUpdateInventoryItemsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryUpdateInventoryItemsRequest> ConvertedType = MakeShared<FPFInventoryUpdateInventoryItemsRequest>(FPFInventoryUpdateInventoryItemsRequest{
		.collectionId = Datatype->collectionId == nullptr ? FString() : FString(Datatype->collectionId),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.eTag = Datatype->eTag == nullptr ? FString() : FString(Datatype->eTag),
		.idempotencyId = Datatype->idempotencyId == nullptr ? FString() : FString(Datatype->idempotencyId),
		.item = ConvertInventoryItemToUnreal(Datatype->item)
	});

	return ConvertedType;
}

const PFInventoryUpdateInventoryItemsRequest* ConvertUpdateInventoryItemsRequestToPlayfab(TSharedPtr<const FPFInventoryUpdateInventoryItemsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryUpdateInventoryItemsRequest* ConvertedType = new PFInventoryUpdateInventoryItemsRequest{
		.collectionId = ConvertFStringToCharPtr(Datatype->collectionId),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.eTag = ConvertFStringToCharPtr(Datatype->eTag),
		.idempotencyId = ConvertFStringToCharPtr(Datatype->idempotencyId),
		.item = ConvertInventoryItemToPlayfab(Datatype->item)
	};

	return ConvertedType;
}

TSharedPtr<const FPFInventoryUpdateInventoryItemsResponse> ConvertUpdateInventoryItemsResponseToUnreal(const PFInventoryUpdateInventoryItemsResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFInventoryUpdateInventoryItemsResponse> ConvertedType = MakeShared<FPFInventoryUpdateInventoryItemsResponse>(FPFInventoryUpdateInventoryItemsResponse{
		.eTag = Datatype->eTag == nullptr ? FString() : FString(Datatype->eTag),
		.idempotencyId = Datatype->idempotencyId == nullptr ? FString() : FString(Datatype->idempotencyId),
		.transactionIds = ConvertCharArrayToUnreal(Datatype->transactionIds, Datatype->transactionIdsCount),
		.transactionIdsCount = Datatype->transactionIdsCount
	});

	return ConvertedType;
}

const PFInventoryUpdateInventoryItemsResponse* ConvertUpdateInventoryItemsResponseToPlayfab(TSharedPtr<const FPFInventoryUpdateInventoryItemsResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFInventoryUpdateInventoryItemsResponse* ConvertedType = new PFInventoryUpdateInventoryItemsResponse{
		.eTag = ConvertFStringToCharPtr(Datatype->eTag),
		.idempotencyId = ConvertFStringToCharPtr(Datatype->idempotencyId),
		.transactionIds = ConvertFStringArrayToPlayfab(Datatype->transactionIds),
		.transactionIdsCount = (uint32_t)Datatype->transactionIds.Num()
	};

	return ConvertedType;
}
