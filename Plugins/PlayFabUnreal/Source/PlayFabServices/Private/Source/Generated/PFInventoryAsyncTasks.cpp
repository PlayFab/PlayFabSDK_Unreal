// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFInventoryAsyncTasks.h"

FAddInventoryItemsAsyncTask::FAddInventoryItemsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventoryAddInventoryItemsRequest InRequest,
	const FOnAddInventoryItemsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FAddInventoryItemsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FAddInventoryItemsAsyncTask::DoWork()
{
	const PFInventoryAddInventoryItemsRequest RequestType = {
		.amount = Request.amount ? new int32(*Request.amount) : nullptr,
		.collectionId = ConvertFStringToCharPtr(Request.collectionId),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.durationInSeconds = Request.durationInSeconds ? new double(*Request.durationInSeconds) : nullptr,
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.eTag = ConvertFStringToCharPtr(Request.eTag),
		.idempotencyId = ConvertFStringToCharPtr(Request.idempotencyId),
		.item = ConvertInventoryItemReferenceToPlayfab(Request.item),
		.newStackValues = ConvertInitialValuesToPlayfab(Request.newStackValues)
	};
	HResult = PFInventoryAddInventoryItemsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFInventoryAddInventoryItemsResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FAddInventoryItemsAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFInventoryAddInventoryItemsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFInventoryAddInventoryItemsResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFInventoryAddInventoryItemsResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFInventoryAddInventoryItemsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFInventoryAddInventoryItemsResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFInventoryAddInventoryItemsResponse> ResultType = ConvertAddInventoryItemsResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FDeleteInventoryCollectionAsyncTask::FDeleteInventoryCollectionAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventoryDeleteInventoryCollectionRequest InRequest,
	const FOnDeleteInventoryCollectionCompleted& InDelegate)
	: FXAsyncTask(TEXT("FDeleteInventoryCollectionAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FDeleteInventoryCollectionAsyncTask::DoWork()
{
	const PFInventoryDeleteInventoryCollectionRequest RequestType = {
		.collectionId = ConvertFStringToCharPtr(Request.collectionId),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.eTag = ConvertFStringToCharPtr(Request.eTag)
	};
	HResult = PFInventoryDeleteInventoryCollectionAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FDeleteInventoryCollectionAsyncTask::ProcessResults()
{
	if (HResult != S_OK)
	{
		Delegate.Execute(FString("Async task failure"), false);
	}
	else
	{
		Delegate.Execute(FString(), true);
	}
}

FDeleteInventoryItemsAsyncTask::FDeleteInventoryItemsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventoryDeleteInventoryItemsRequest InRequest,
	const FOnDeleteInventoryItemsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FDeleteInventoryItemsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FDeleteInventoryItemsAsyncTask::DoWork()
{
	const PFInventoryDeleteInventoryItemsRequest RequestType = {
		.collectionId = ConvertFStringToCharPtr(Request.collectionId),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.eTag = ConvertFStringToCharPtr(Request.eTag),
		.idempotencyId = ConvertFStringToCharPtr(Request.idempotencyId),
		.item = ConvertInventoryItemReferenceToPlayfab(Request.item)
	};
	HResult = PFInventoryDeleteInventoryItemsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFInventoryDeleteInventoryItemsResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FDeleteInventoryItemsAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFInventoryDeleteInventoryItemsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFInventoryDeleteInventoryItemsResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFInventoryDeleteInventoryItemsResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFInventoryDeleteInventoryItemsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFInventoryDeleteInventoryItemsResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFInventoryDeleteInventoryItemsResponse> ResultType = ConvertDeleteInventoryItemsResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FExecuteInventoryOperationsAsyncTask::FExecuteInventoryOperationsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventoryExecuteInventoryOperationsRequest InRequest,
	const FOnExecuteInventoryOperationsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FExecuteInventoryOperationsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FExecuteInventoryOperationsAsyncTask::DoWork()
{
	const PFInventoryExecuteInventoryOperationsRequest RequestType = {
		.collectionId = ConvertFStringToCharPtr(Request.collectionId),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.eTag = ConvertFStringToCharPtr(Request.eTag),
		.idempotencyId = ConvertFStringToCharPtr(Request.idempotencyId),
		.operations = ConvertUnrealArrayToPlayfab<PFInventoryInventoryOperation, FPFInventoryInventoryOperation>(Request.operations, ConvertInventoryOperationToPlayfab),
		.operationsCount = (uint32_t)Request.operations.Num()
	};
	HResult = PFInventoryExecuteInventoryOperationsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFInventoryExecuteInventoryOperationsResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FExecuteInventoryOperationsAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFInventoryExecuteInventoryOperationsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFInventoryExecuteInventoryOperationsResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFInventoryExecuteInventoryOperationsResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFInventoryExecuteInventoryOperationsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFInventoryExecuteInventoryOperationsResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFInventoryExecuteInventoryOperationsResponse> ResultType = ConvertExecuteInventoryOperationsResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

#if HC_PLATFORM == HC_PLATFORM_GDK
FExecuteTransferOperationsAsyncTask::FExecuteTransferOperationsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventoryExecuteTransferOperationsRequest InRequest,
	const FOnExecuteTransferOperationsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FExecuteTransferOperationsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FExecuteTransferOperationsAsyncTask::DoWork()
{
	const PFInventoryExecuteTransferOperationsRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.givingCollectionId = ConvertFStringToCharPtr(Request.givingCollectionId),
		.givingEntity = ConvertEntityKeyToPlayfab(Request.givingEntity),
		.givingETag = ConvertFStringToCharPtr(Request.givingETag),
		.idempotencyId = ConvertFStringToCharPtr(Request.idempotencyId),
		.operations = ConvertUnrealArrayToPlayfab<PFInventoryTransferInventoryItemsOperation, FPFInventoryTransferInventoryItemsOperation>(Request.operations, ConvertTransferInventoryItemsOperationToPlayfab),
		.operationsCount = (uint32_t)Request.operations.Num(),
		.receivingCollectionId = ConvertFStringToCharPtr(Request.receivingCollectionId),
		.receivingEntity = ConvertEntityKeyToPlayfab(Request.receivingEntity)
	};
	HResult = PFInventoryExecuteTransferOperationsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFInventoryExecuteTransferOperationsResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FExecuteTransferOperationsAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFInventoryExecuteTransferOperationsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFInventoryExecuteTransferOperationsResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFInventoryExecuteTransferOperationsResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFInventoryExecuteTransferOperationsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFInventoryExecuteTransferOperationsResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFInventoryExecuteTransferOperationsResponse> ResultType = ConvertExecuteTransferOperationsResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

FGetInventoryCollectionIdsAsyncTask::FGetInventoryCollectionIdsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventoryGetInventoryCollectionIdsRequest InRequest,
	const FOnGetInventoryCollectionIdsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FGetInventoryCollectionIdsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FGetInventoryCollectionIdsAsyncTask::DoWork()
{
	const PFInventoryGetInventoryCollectionIdsRequest RequestType = {
		.continuationToken = ConvertFStringToCharPtr(Request.continuationToken),
		.count = Request.count,
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity)
	};
	HResult = PFInventoryGetInventoryCollectionIdsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFInventoryGetInventoryCollectionIdsResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FGetInventoryCollectionIdsAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFInventoryGetInventoryCollectionIdsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFInventoryGetInventoryCollectionIdsResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFInventoryGetInventoryCollectionIdsResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFInventoryGetInventoryCollectionIdsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFInventoryGetInventoryCollectionIdsResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFInventoryGetInventoryCollectionIdsResponse> ResultType = ConvertGetInventoryCollectionIdsResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FGetInventoryItemsAsyncTask::FGetInventoryItemsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventoryGetInventoryItemsRequest InRequest,
	const FOnGetInventoryItemsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FGetInventoryItemsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FGetInventoryItemsAsyncTask::DoWork()
{
	const PFInventoryGetInventoryItemsRequest RequestType = {
		.collectionId = ConvertFStringToCharPtr(Request.collectionId),
		.continuationToken = ConvertFStringToCharPtr(Request.continuationToken),
		.count = Request.count,
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.filter = ConvertFStringToCharPtr(Request.filter)
	};
	HResult = PFInventoryGetInventoryItemsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFInventoryGetInventoryItemsResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FGetInventoryItemsAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFInventoryGetInventoryItemsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFInventoryGetInventoryItemsResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFInventoryGetInventoryItemsResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFInventoryGetInventoryItemsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFInventoryGetInventoryItemsResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFInventoryGetInventoryItemsResponse> ResultType = ConvertGetInventoryItemsResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

#if HC_PLATFORM == HC_PLATFORM_GDK
FGetInventoryOperationStatusAsyncTask::FGetInventoryOperationStatusAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventoryGetInventoryOperationStatusRequest InRequest,
	const FOnGetInventoryOperationStatusCompleted& InDelegate)
	: FXAsyncTask(TEXT("FGetInventoryOperationStatusAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FGetInventoryOperationStatusAsyncTask::DoWork()
{
	const PFInventoryGetInventoryOperationStatusRequest RequestType = {
		.collectionId = ConvertFStringToCharPtr(Request.collectionId),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.operationToken = ConvertFStringToCharPtr(Request.operationToken)
	};
	HResult = PFInventoryGetInventoryOperationStatusAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFInventoryGetInventoryOperationStatusResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FGetInventoryOperationStatusAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFInventoryGetInventoryOperationStatusGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFInventoryGetInventoryOperationStatusResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFInventoryGetInventoryOperationStatusResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFInventoryGetInventoryOperationStatusGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFInventoryGetInventoryOperationStatusResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFInventoryGetInventoryOperationStatusResponse> ResultType = ConvertGetInventoryOperationStatusResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FGetMicrosoftStoreAccessTokensAsyncTask::FGetMicrosoftStoreAccessTokensAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventoryGetMicrosoftStoreAccessTokensRequest InRequest,
	const FOnGetMicrosoftStoreAccessTokensCompleted& InDelegate)
	: FXAsyncTask(TEXT("FGetMicrosoftStoreAccessTokensAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FGetMicrosoftStoreAccessTokensAsyncTask::DoWork()
{
	const PFInventoryGetMicrosoftStoreAccessTokensRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num()
	};
	HResult = PFInventoryGetMicrosoftStoreAccessTokensAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFInventoryGetMicrosoftStoreAccessTokensResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FGetMicrosoftStoreAccessTokensAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFInventoryGetMicrosoftStoreAccessTokensGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFInventoryGetMicrosoftStoreAccessTokensResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFInventoryGetMicrosoftStoreAccessTokensResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFInventoryGetMicrosoftStoreAccessTokensGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFInventoryGetMicrosoftStoreAccessTokensResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFInventoryGetMicrosoftStoreAccessTokensResponse> ResultType = ConvertGetMicrosoftStoreAccessTokensResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FGetTransactionHistoryAsyncTask::FGetTransactionHistoryAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventoryGetTransactionHistoryRequest InRequest,
	const FOnGetTransactionHistoryCompleted& InDelegate)
	: FXAsyncTask(TEXT("FGetTransactionHistoryAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FGetTransactionHistoryAsyncTask::DoWork()
{
	const PFInventoryGetTransactionHistoryRequest RequestType = {
		.collectionId = ConvertFStringToCharPtr(Request.collectionId),
		.continuationToken = ConvertFStringToCharPtr(Request.continuationToken),
		.count = Request.count,
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.filter = ConvertFStringToCharPtr(Request.filter),
		.orderBy = ConvertFStringToCharPtr(Request.orderBy)
	};
	HResult = PFInventoryGetTransactionHistoryAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFInventoryGetTransactionHistoryResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FGetTransactionHistoryAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFInventoryGetTransactionHistoryGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFInventoryGetTransactionHistoryResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFInventoryGetTransactionHistoryResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFInventoryGetTransactionHistoryGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFInventoryGetTransactionHistoryResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFInventoryGetTransactionHistoryResponse> ResultType = ConvertGetTransactionHistoryResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

FPurchaseInventoryItemsAsyncTask::FPurchaseInventoryItemsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventoryPurchaseInventoryItemsRequest InRequest,
	const FOnPurchaseInventoryItemsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FPurchaseInventoryItemsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FPurchaseInventoryItemsAsyncTask::DoWork()
{
	const PFInventoryPurchaseInventoryItemsRequest RequestType = {
		.amount = Request.amount ? new int32(*Request.amount) : nullptr,
		.collectionId = ConvertFStringToCharPtr(Request.collectionId),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.deleteEmptyStacks = Request.deleteEmptyStacks,
		.durationInSeconds = Request.durationInSeconds ? new double(*Request.durationInSeconds) : nullptr,
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.eTag = ConvertFStringToCharPtr(Request.eTag),
		.idempotencyId = ConvertFStringToCharPtr(Request.idempotencyId),
		.item = ConvertInventoryItemReferenceToPlayfab(Request.item),
		.newStackValues = ConvertInitialValuesToPlayfab(Request.newStackValues),
		.priceAmounts = ConvertUnrealArrayToPlayfab<PFInventoryPurchasePriceAmount, FPFInventoryPurchasePriceAmount>(Request.priceAmounts, ConvertPurchasePriceAmountToPlayfab),
		.priceAmountsCount = (uint32_t)Request.priceAmounts.Num(),
		.storeId = ConvertFStringToCharPtr(Request.storeId)
	};
	HResult = PFInventoryPurchaseInventoryItemsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFInventoryPurchaseInventoryItemsResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FPurchaseInventoryItemsAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFInventoryPurchaseInventoryItemsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFInventoryPurchaseInventoryItemsResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFInventoryPurchaseInventoryItemsResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFInventoryPurchaseInventoryItemsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFInventoryPurchaseInventoryItemsResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFInventoryPurchaseInventoryItemsResponse> ResultType = ConvertPurchaseInventoryItemsResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_IOS
FRedeemAppleAppStoreInventoryItemsAsyncTask::FRedeemAppleAppStoreInventoryItemsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventoryRedeemAppleAppStoreInventoryItemsRequest InRequest,
	const FOnRedeemAppleAppStoreInventoryItemsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FRedeemAppleAppStoreInventoryItemsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FRedeemAppleAppStoreInventoryItemsAsyncTask::DoWork()
{
	const PFInventoryRedeemAppleAppStoreInventoryItemsRequest RequestType = {
		.collectionId = ConvertFStringToCharPtr(Request.collectionId),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.receipt = ConvertFStringToCharPtr(Request.receipt)
	};
	HResult = PFInventoryRedeemAppleAppStoreInventoryItemsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFInventoryRedeemAppleAppStoreInventoryItemsResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FRedeemAppleAppStoreInventoryItemsAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFInventoryRedeemAppleAppStoreInventoryItemsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFInventoryRedeemAppleAppStoreInventoryItemsResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFInventoryRedeemAppleAppStoreInventoryItemsResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFInventoryRedeemAppleAppStoreInventoryItemsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFInventoryRedeemAppleAppStoreInventoryItemsResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFInventoryRedeemAppleAppStoreInventoryItemsResponse> ResultType = ConvertRedeemAppleAppStoreInventoryItemsResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_ANDROID
FRedeemGooglePlayInventoryItemsAsyncTask::FRedeemGooglePlayInventoryItemsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventoryRedeemGooglePlayInventoryItemsRequest InRequest,
	const FOnRedeemGooglePlayInventoryItemsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FRedeemGooglePlayInventoryItemsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FRedeemGooglePlayInventoryItemsAsyncTask::DoWork()
{
	const PFInventoryRedeemGooglePlayInventoryItemsRequest RequestType = {
		.collectionId = ConvertFStringToCharPtr(Request.collectionId),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.purchases = ConvertUnrealArrayToPlayfab<PFInventoryGooglePlayProductPurchase, FPFInventoryGooglePlayProductPurchase>(Request.purchases, ConvertGooglePlayProductPurchaseToPlayfab),
		.purchasesCount = (uint32_t)Request.purchases.Num()
	};
	HResult = PFInventoryRedeemGooglePlayInventoryItemsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFInventoryRedeemGooglePlayInventoryItemsResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FRedeemGooglePlayInventoryItemsAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFInventoryRedeemGooglePlayInventoryItemsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFInventoryRedeemGooglePlayInventoryItemsResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFInventoryRedeemGooglePlayInventoryItemsResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFInventoryRedeemGooglePlayInventoryItemsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFInventoryRedeemGooglePlayInventoryItemsResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFInventoryRedeemGooglePlayInventoryItemsResponse> ResultType = ConvertRedeemGooglePlayInventoryItemsResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FRedeemMicrosoftStoreInventoryItemsAsyncTask::FRedeemMicrosoftStoreInventoryItemsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventoryRedeemMicrosoftStoreInventoryItemsRequest InRequest,
	const FOnRedeemMicrosoftStoreInventoryItemsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FRedeemMicrosoftStoreInventoryItemsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FRedeemMicrosoftStoreInventoryItemsAsyncTask::DoWork()
{
	const PFInventoryRedeemMicrosoftStoreInventoryItemsRequest RequestType = {
		.collectionId = ConvertFStringToCharPtr(Request.collectionId),
		.collectionsIdKey = ConvertFStringToCharPtr(Request.collectionsIdKey),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
#if defined(PF_GDK_AVAILABLE)
		.user = Request.user
#else
		.xboxToken = ConvertFStringToCharPtr(Request.xboxToken)
#endif
	};
	HResult = PFInventoryRedeemMicrosoftStoreInventoryItemsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFInventoryRedeemMicrosoftStoreInventoryItemsResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FRedeemMicrosoftStoreInventoryItemsAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFInventoryRedeemMicrosoftStoreInventoryItemsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFInventoryRedeemMicrosoftStoreInventoryItemsResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFInventoryRedeemMicrosoftStoreInventoryItemsResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFInventoryRedeemMicrosoftStoreInventoryItemsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFInventoryRedeemMicrosoftStoreInventoryItemsResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFInventoryRedeemMicrosoftStoreInventoryItemsResponse> ResultType = ConvertRedeemMicrosoftStoreInventoryItemsResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_NINTENDO_SWITCH || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FRedeemNintendoEShopInventoryItemsAsyncTask::FRedeemNintendoEShopInventoryItemsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventoryRedeemNintendoEShopInventoryItemsRequest InRequest,
	const FOnRedeemNintendoEShopInventoryItemsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FRedeemNintendoEShopInventoryItemsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FRedeemNintendoEShopInventoryItemsAsyncTask::DoWork()
{
	const PFInventoryRedeemNintendoEShopInventoryItemsRequest RequestType = {
		.collectionId = ConvertFStringToCharPtr(Request.collectionId),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.nintendoServiceAccountIdToken = ConvertFStringToCharPtr(Request.nintendoServiceAccountIdToken)
	};
	HResult = PFInventoryRedeemNintendoEShopInventoryItemsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFInventoryRedeemNintendoEShopInventoryItemsResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FRedeemNintendoEShopInventoryItemsAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFInventoryRedeemNintendoEShopInventoryItemsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFInventoryRedeemNintendoEShopInventoryItemsResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFInventoryRedeemNintendoEShopInventoryItemsResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFInventoryRedeemNintendoEShopInventoryItemsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFInventoryRedeemNintendoEShopInventoryItemsResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFInventoryRedeemNintendoEShopInventoryItemsResponse> ResultType = ConvertRedeemNintendoEShopInventoryItemsResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_4 || HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_5 || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FRedeemPlayStationStoreInventoryItemsAsyncTask::FRedeemPlayStationStoreInventoryItemsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventoryRedeemPlayStationStoreInventoryItemsRequest InRequest,
	const FOnRedeemPlayStationStoreInventoryItemsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FRedeemPlayStationStoreInventoryItemsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FRedeemPlayStationStoreInventoryItemsAsyncTask::DoWork()
{
	const PFInventoryRedeemPlayStationStoreInventoryItemsRequest RequestType = {
		.authorizationCode = ConvertFStringToCharPtr(Request.authorizationCode),
		.collectionId = ConvertFStringToCharPtr(Request.collectionId),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.redirectUri = ConvertFStringToCharPtr(Request.redirectUri),
		.serviceLabel = ConvertFStringToCharPtr(Request.serviceLabel)
	};
	HResult = PFInventoryRedeemPlayStationStoreInventoryItemsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFInventoryRedeemPlayStationStoreInventoryItemsResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FRedeemPlayStationStoreInventoryItemsAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFInventoryRedeemPlayStationStoreInventoryItemsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFInventoryRedeemPlayStationStoreInventoryItemsResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFInventoryRedeemPlayStationStoreInventoryItemsResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFInventoryRedeemPlayStationStoreInventoryItemsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFInventoryRedeemPlayStationStoreInventoryItemsResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFInventoryRedeemPlayStationStoreInventoryItemsResponse> ResultType = ConvertRedeemPlayStationStoreInventoryItemsResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FRedeemSteamInventoryItemsAsyncTask::FRedeemSteamInventoryItemsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventoryRedeemSteamInventoryItemsRequest InRequest,
	const FOnRedeemSteamInventoryItemsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FRedeemSteamInventoryItemsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FRedeemSteamInventoryItemsAsyncTask::DoWork()
{
	const PFInventoryRedeemSteamInventoryItemsRequest RequestType = {
		.collectionId = ConvertFStringToCharPtr(Request.collectionId),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity)
	};
	HResult = PFInventoryRedeemSteamInventoryItemsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFInventoryRedeemSteamInventoryItemsResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FRedeemSteamInventoryItemsAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFInventoryRedeemSteamInventoryItemsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFInventoryRedeemSteamInventoryItemsResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFInventoryRedeemSteamInventoryItemsResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFInventoryRedeemSteamInventoryItemsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFInventoryRedeemSteamInventoryItemsResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFInventoryRedeemSteamInventoryItemsResponse> ResultType = ConvertRedeemSteamInventoryItemsResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

FSubtractInventoryItemsAsyncTask::FSubtractInventoryItemsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventorySubtractInventoryItemsRequest InRequest,
	const FOnSubtractInventoryItemsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FSubtractInventoryItemsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FSubtractInventoryItemsAsyncTask::DoWork()
{
	const PFInventorySubtractInventoryItemsRequest RequestType = {
		.amount = Request.amount ? new int32(*Request.amount) : nullptr,
		.collectionId = ConvertFStringToCharPtr(Request.collectionId),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.deleteEmptyStacks = Request.deleteEmptyStacks,
		.durationInSeconds = Request.durationInSeconds ? new double(*Request.durationInSeconds) : nullptr,
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.eTag = ConvertFStringToCharPtr(Request.eTag),
		.idempotencyId = ConvertFStringToCharPtr(Request.idempotencyId),
		.item = ConvertInventoryItemReferenceToPlayfab(Request.item)
	};
	HResult = PFInventorySubtractInventoryItemsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFInventorySubtractInventoryItemsResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FSubtractInventoryItemsAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFInventorySubtractInventoryItemsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFInventorySubtractInventoryItemsResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFInventorySubtractInventoryItemsResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFInventorySubtractInventoryItemsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFInventorySubtractInventoryItemsResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFInventorySubtractInventoryItemsResponse> ResultType = ConvertSubtractInventoryItemsResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FTransferInventoryItemsAsyncTask::FTransferInventoryItemsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventoryTransferInventoryItemsRequest InRequest,
	const FOnTransferInventoryItemsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FTransferInventoryItemsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FTransferInventoryItemsAsyncTask::DoWork()
{
	const PFInventoryTransferInventoryItemsRequest RequestType = {
		.amount = Request.amount ? new int32(*Request.amount) : nullptr,
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.deleteEmptyStacks = Request.deleteEmptyStacks,
		.givingCollectionId = ConvertFStringToCharPtr(Request.givingCollectionId),
		.givingEntity = ConvertEntityKeyToPlayfab(Request.givingEntity),
		.givingETag = ConvertFStringToCharPtr(Request.givingETag),
		.givingItem = ConvertInventoryItemReferenceToPlayfab(Request.givingItem),
		.idempotencyId = ConvertFStringToCharPtr(Request.idempotencyId),
		.newStackValues = ConvertInitialValuesToPlayfab(Request.newStackValues),
		.receivingCollectionId = ConvertFStringToCharPtr(Request.receivingCollectionId),
		.receivingEntity = ConvertEntityKeyToPlayfab(Request.receivingEntity),
		.receivingItem = ConvertInventoryItemReferenceToPlayfab(Request.receivingItem)
	};
	HResult = PFInventoryTransferInventoryItemsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFInventoryTransferInventoryItemsResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FTransferInventoryItemsAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFInventoryTransferInventoryItemsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFInventoryTransferInventoryItemsResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFInventoryTransferInventoryItemsResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFInventoryTransferInventoryItemsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFInventoryTransferInventoryItemsResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFInventoryTransferInventoryItemsResponse> ResultType = ConvertTransferInventoryItemsResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FUpdateInventoryItemsAsyncTask::FUpdateInventoryItemsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFInventoryUpdateInventoryItemsRequest InRequest,
	const FOnUpdateInventoryItemsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FUpdateInventoryItemsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FUpdateInventoryItemsAsyncTask::DoWork()
{
	const PFInventoryUpdateInventoryItemsRequest RequestType = {
		.collectionId = ConvertFStringToCharPtr(Request.collectionId),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.eTag = ConvertFStringToCharPtr(Request.eTag),
		.idempotencyId = ConvertFStringToCharPtr(Request.idempotencyId),
		.item = ConvertInventoryItemToPlayfab(Request.item)
	};
	HResult = PFInventoryUpdateInventoryItemsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFInventoryUpdateInventoryItemsResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FUpdateInventoryItemsAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFInventoryUpdateInventoryItemsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFInventoryUpdateInventoryItemsResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFInventoryUpdateInventoryItemsResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFInventoryUpdateInventoryItemsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFInventoryUpdateInventoryItemsResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFInventoryUpdateInventoryItemsResponse> ResultType = ConvertUpdateInventoryItemsResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

