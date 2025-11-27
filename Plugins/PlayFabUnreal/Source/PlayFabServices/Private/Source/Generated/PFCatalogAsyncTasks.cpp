// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFCatalogAsyncTasks.h"

FCreateDraftItemAsyncTask::FCreateDraftItemAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogCreateDraftItemRequest InRequest,
	const FOnCreateDraftItemCompleted& InDelegate)
	: FXAsyncTask(TEXT("FCreateDraftItemAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FCreateDraftItemAsyncTask::DoWork()
{
	const PFCatalogCreateDraftItemRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.item = ConvertCatalogItemToPlayfab(Request.item),
		.publish = Request.publish
	};
	HResult = PFCatalogCreateDraftItemAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFCatalogCreateDraftItemResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FCreateDraftItemAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFCatalogCreateDraftItemGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFCatalogCreateDraftItemResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFCatalogCreateDraftItemResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFCatalogCreateDraftItemGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFCatalogCreateDraftItemResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFCatalogCreateDraftItemResponse> ResultType = ConvertCreateDraftItemResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FCreateUploadUrlsAsyncTask::FCreateUploadUrlsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogCreateUploadUrlsRequest InRequest,
	const FOnCreateUploadUrlsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FCreateUploadUrlsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FCreateUploadUrlsAsyncTask::DoWork()
{
	const PFCatalogCreateUploadUrlsRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.files = ConvertUnrealArrayToPlayfab<PFCatalogUploadInfo, FPFCatalogUploadInfo>(Request.files, ConvertUploadInfoToPlayfab),
		.filesCount = (uint32_t)Request.files.Num()
	};
	HResult = PFCatalogCreateUploadUrlsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFCatalogCreateUploadUrlsResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FCreateUploadUrlsAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFCatalogCreateUploadUrlsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFCatalogCreateUploadUrlsResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFCatalogCreateUploadUrlsResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFCatalogCreateUploadUrlsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFCatalogCreateUploadUrlsResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFCatalogCreateUploadUrlsResponse> ResultType = ConvertCreateUploadUrlsResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

#if HC_PLATFORM == HC_PLATFORM_GDK
FDeleteEntityItemReviewsAsyncTask::FDeleteEntityItemReviewsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogDeleteEntityItemReviewsRequest InRequest,
	const FOnDeleteEntityItemReviewsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FDeleteEntityItemReviewsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FDeleteEntityItemReviewsAsyncTask::DoWork()
{
	const PFCatalogDeleteEntityItemReviewsRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity)
	};
	HResult = PFCatalogDeleteEntityItemReviewsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FDeleteEntityItemReviewsAsyncTask::ProcessResults()
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
#endif

FDeleteItemAsyncTask::FDeleteItemAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogDeleteItemRequest InRequest,
	const FOnDeleteItemCompleted& InDelegate)
	: FXAsyncTask(TEXT("FDeleteItemAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FDeleteItemAsyncTask::DoWork()
{
	const PFCatalogDeleteItemRequest RequestType = {
		.alternateId = ConvertCatalogAlternateIdToPlayfab(Request.alternateId),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.id = ConvertFStringToCharPtr(Request.id)
	};
	HResult = PFCatalogDeleteItemAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FDeleteItemAsyncTask::ProcessResults()
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

#if HC_PLATFORM == HC_PLATFORM_GDK
FGetCatalogConfigAsyncTask::FGetCatalogConfigAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogGetCatalogConfigRequest InRequest,
	const FOnGetCatalogConfigCompleted& InDelegate)
	: FXAsyncTask(TEXT("FGetCatalogConfigAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FGetCatalogConfigAsyncTask::DoWork()
{
	const PFCatalogGetCatalogConfigRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num()
	};
	HResult = PFCatalogGetCatalogConfigAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFCatalogGetCatalogConfigResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FGetCatalogConfigAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFCatalogGetCatalogConfigGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFCatalogGetCatalogConfigResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFCatalogGetCatalogConfigResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFCatalogGetCatalogConfigGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFCatalogGetCatalogConfigResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFCatalogGetCatalogConfigResponse> ResultType = ConvertGetCatalogConfigResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

FGetDraftItemAsyncTask::FGetDraftItemAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogGetDraftItemRequest InRequest,
	const FOnGetDraftItemCompleted& InDelegate)
	: FXAsyncTask(TEXT("FGetDraftItemAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FGetDraftItemAsyncTask::DoWork()
{
	const PFCatalogGetDraftItemRequest RequestType = {
		.alternateId = ConvertCatalogAlternateIdToPlayfab(Request.alternateId),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.id = ConvertFStringToCharPtr(Request.id)
	};
	HResult = PFCatalogGetDraftItemAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFCatalogGetDraftItemResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FGetDraftItemAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFCatalogGetDraftItemGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFCatalogGetDraftItemResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFCatalogGetDraftItemResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFCatalogGetDraftItemGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFCatalogGetDraftItemResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFCatalogGetDraftItemResponse> ResultType = ConvertGetDraftItemResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FGetDraftItemsAsyncTask::FGetDraftItemsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogGetDraftItemsRequest InRequest,
	const FOnGetDraftItemsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FGetDraftItemsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FGetDraftItemsAsyncTask::DoWork()
{
	const PFCatalogGetDraftItemsRequest RequestType = {
		.alternateIds = ConvertUnrealArrayToPlayfab<PFCatalogCatalogAlternateId, FPFCatalogCatalogAlternateId>(Request.alternateIds, ConvertCatalogAlternateIdToPlayfab),
		.alternateIdsCount = (uint32_t)Request.alternateIds.Num(),
		.continuationToken = ConvertFStringToCharPtr(Request.continuationToken),
		.count = Request.count ? new int32(*Request.count) : nullptr,
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.ids = ConvertFStringArrayToPlayfab(Request.ids),
		.idsCount = (uint32_t)Request.ids.Num()
	};
	HResult = PFCatalogGetDraftItemsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFCatalogGetDraftItemsResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FGetDraftItemsAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFCatalogGetDraftItemsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFCatalogGetDraftItemsResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFCatalogGetDraftItemsResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFCatalogGetDraftItemsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFCatalogGetDraftItemsResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFCatalogGetDraftItemsResponse> ResultType = ConvertGetDraftItemsResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FGetEntityDraftItemsAsyncTask::FGetEntityDraftItemsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogGetEntityDraftItemsRequest InRequest,
	const FOnGetEntityDraftItemsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FGetEntityDraftItemsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FGetEntityDraftItemsAsyncTask::DoWork()
{
	const PFCatalogGetEntityDraftItemsRequest RequestType = {
		.continuationToken = ConvertFStringToCharPtr(Request.continuationToken),
		.count = Request.count,
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.filter = ConvertFStringToCharPtr(Request.filter)
	};
	HResult = PFCatalogGetEntityDraftItemsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFCatalogGetEntityDraftItemsResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FGetEntityDraftItemsAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFCatalogGetEntityDraftItemsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFCatalogGetEntityDraftItemsResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFCatalogGetEntityDraftItemsResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFCatalogGetEntityDraftItemsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFCatalogGetEntityDraftItemsResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFCatalogGetEntityDraftItemsResponse> ResultType = ConvertGetEntityDraftItemsResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FGetEntityItemReviewAsyncTask::FGetEntityItemReviewAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogGetEntityItemReviewRequest InRequest,
	const FOnGetEntityItemReviewCompleted& InDelegate)
	: FXAsyncTask(TEXT("FGetEntityItemReviewAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FGetEntityItemReviewAsyncTask::DoWork()
{
	const PFCatalogGetEntityItemReviewRequest RequestType = {
		.alternateId = ConvertCatalogAlternateIdToPlayfab(Request.alternateId),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.id = ConvertFStringToCharPtr(Request.id)
	};
	HResult = PFCatalogGetEntityItemReviewAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFCatalogGetEntityItemReviewResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FGetEntityItemReviewAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFCatalogGetEntityItemReviewGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFCatalogGetEntityItemReviewResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFCatalogGetEntityItemReviewResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFCatalogGetEntityItemReviewGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFCatalogGetEntityItemReviewResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFCatalogGetEntityItemReviewResponse> ResultType = ConvertGetEntityItemReviewResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FGetItemAsyncTask::FGetItemAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogGetItemRequest InRequest,
	const FOnGetItemCompleted& InDelegate)
	: FXAsyncTask(TEXT("FGetItemAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FGetItemAsyncTask::DoWork()
{
	const PFCatalogGetItemRequest RequestType = {
		.alternateId = ConvertCatalogAlternateIdToPlayfab(Request.alternateId),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.id = ConvertFStringToCharPtr(Request.id)
	};
	HResult = PFCatalogGetItemAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFCatalogGetItemResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FGetItemAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFCatalogGetItemGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFCatalogGetItemResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFCatalogGetItemResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFCatalogGetItemGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFCatalogGetItemResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFCatalogGetItemResponse> ResultType = ConvertGetItemResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FGetItemContainersAsyncTask::FGetItemContainersAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogGetItemContainersRequest InRequest,
	const FOnGetItemContainersCompleted& InDelegate)
	: FXAsyncTask(TEXT("FGetItemContainersAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FGetItemContainersAsyncTask::DoWork()
{
	const PFCatalogGetItemContainersRequest RequestType = {
		.alternateId = ConvertCatalogAlternateIdToPlayfab(Request.alternateId),
		.continuationToken = ConvertFStringToCharPtr(Request.continuationToken),
		.count = Request.count,
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.id = ConvertFStringToCharPtr(Request.id)
	};
	HResult = PFCatalogGetItemContainersAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFCatalogGetItemContainersResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FGetItemContainersAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFCatalogGetItemContainersGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFCatalogGetItemContainersResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFCatalogGetItemContainersResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFCatalogGetItemContainersGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFCatalogGetItemContainersResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFCatalogGetItemContainersResponse> ResultType = ConvertGetItemContainersResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

#if HC_PLATFORM == HC_PLATFORM_GDK
FGetItemModerationStateAsyncTask::FGetItemModerationStateAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogGetItemModerationStateRequest InRequest,
	const FOnGetItemModerationStateCompleted& InDelegate)
	: FXAsyncTask(TEXT("FGetItemModerationStateAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FGetItemModerationStateAsyncTask::DoWork()
{
	const PFCatalogGetItemModerationStateRequest RequestType = {
		.alternateId = ConvertCatalogAlternateIdToPlayfab(Request.alternateId),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.id = ConvertFStringToCharPtr(Request.id)
	};
	HResult = PFCatalogGetItemModerationStateAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFCatalogGetItemModerationStateResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FGetItemModerationStateAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFCatalogGetItemModerationStateGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFCatalogGetItemModerationStateResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFCatalogGetItemModerationStateResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFCatalogGetItemModerationStateGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFCatalogGetItemModerationStateResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFCatalogGetItemModerationStateResponse> ResultType = ConvertGetItemModerationStateResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

FGetItemPublishStatusAsyncTask::FGetItemPublishStatusAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogGetItemPublishStatusRequest InRequest,
	const FOnGetItemPublishStatusCompleted& InDelegate)
	: FXAsyncTask(TEXT("FGetItemPublishStatusAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FGetItemPublishStatusAsyncTask::DoWork()
{
	const PFCatalogGetItemPublishStatusRequest RequestType = {
		.alternateId = ConvertCatalogAlternateIdToPlayfab(Request.alternateId),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.id = ConvertFStringToCharPtr(Request.id)
	};
	HResult = PFCatalogGetItemPublishStatusAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFCatalogGetItemPublishStatusResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FGetItemPublishStatusAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFCatalogGetItemPublishStatusGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFCatalogGetItemPublishStatusResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFCatalogGetItemPublishStatusResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFCatalogGetItemPublishStatusGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFCatalogGetItemPublishStatusResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFCatalogGetItemPublishStatusResponse> ResultType = ConvertGetItemPublishStatusResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FGetItemReviewsAsyncTask::FGetItemReviewsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogGetItemReviewsRequest InRequest,
	const FOnGetItemReviewsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FGetItemReviewsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FGetItemReviewsAsyncTask::DoWork()
{
	const PFCatalogGetItemReviewsRequest RequestType = {
		.alternateId = ConvertCatalogAlternateIdToPlayfab(Request.alternateId),
		.continuationToken = ConvertFStringToCharPtr(Request.continuationToken),
		.count = Request.count,
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.id = ConvertFStringToCharPtr(Request.id),
		.orderBy = ConvertFStringToCharPtr(Request.orderBy)
	};
	HResult = PFCatalogGetItemReviewsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFCatalogGetItemReviewsResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FGetItemReviewsAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFCatalogGetItemReviewsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFCatalogGetItemReviewsResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFCatalogGetItemReviewsResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFCatalogGetItemReviewsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFCatalogGetItemReviewsResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFCatalogGetItemReviewsResponse> ResultType = ConvertGetItemReviewsResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FGetItemReviewSummaryAsyncTask::FGetItemReviewSummaryAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogGetItemReviewSummaryRequest InRequest,
	const FOnGetItemReviewSummaryCompleted& InDelegate)
	: FXAsyncTask(TEXT("FGetItemReviewSummaryAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FGetItemReviewSummaryAsyncTask::DoWork()
{
	const PFCatalogGetItemReviewSummaryRequest RequestType = {
		.alternateId = ConvertCatalogAlternateIdToPlayfab(Request.alternateId),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.id = ConvertFStringToCharPtr(Request.id)
	};
	HResult = PFCatalogGetItemReviewSummaryAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFCatalogGetItemReviewSummaryResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FGetItemReviewSummaryAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFCatalogGetItemReviewSummaryGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFCatalogGetItemReviewSummaryResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFCatalogGetItemReviewSummaryResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFCatalogGetItemReviewSummaryGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFCatalogGetItemReviewSummaryResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFCatalogGetItemReviewSummaryResponse> ResultType = ConvertGetItemReviewSummaryResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FGetItemsAsyncTask::FGetItemsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogGetItemsRequest InRequest,
	const FOnGetItemsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FGetItemsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FGetItemsAsyncTask::DoWork()
{
	const PFCatalogGetItemsRequest RequestType = {
		.alternateIds = ConvertUnrealArrayToPlayfab<PFCatalogCatalogAlternateId, FPFCatalogCatalogAlternateId>(Request.alternateIds, ConvertCatalogAlternateIdToPlayfab),
		.alternateIdsCount = (uint32_t)Request.alternateIds.Num(),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.ids = ConvertFStringArrayToPlayfab(Request.ids),
		.idsCount = (uint32_t)Request.ids.Num()
	};
	HResult = PFCatalogGetItemsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFCatalogGetItemsResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FGetItemsAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFCatalogGetItemsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFCatalogGetItemsResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFCatalogGetItemsResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFCatalogGetItemsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFCatalogGetItemsResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFCatalogGetItemsResponse> ResultType = ConvertGetItemsResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FPublishDraftItemAsyncTask::FPublishDraftItemAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogPublishDraftItemRequest InRequest,
	const FOnPublishDraftItemCompleted& InDelegate)
	: FXAsyncTask(TEXT("FPublishDraftItemAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FPublishDraftItemAsyncTask::DoWork()
{
	const PFCatalogPublishDraftItemRequest RequestType = {
		.alternateId = ConvertCatalogAlternateIdToPlayfab(Request.alternateId),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.eTag = ConvertFStringToCharPtr(Request.eTag),
		.id = ConvertFStringToCharPtr(Request.id)
	};
	HResult = PFCatalogPublishDraftItemAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FPublishDraftItemAsyncTask::ProcessResults()
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

FReportItemAsyncTask::FReportItemAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogReportItemRequest InRequest,
	const FOnReportItemCompleted& InDelegate)
	: FXAsyncTask(TEXT("FReportItemAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FReportItemAsyncTask::DoWork()
{
	const PFCatalogReportItemRequest RequestType = {
		.alternateId = ConvertCatalogAlternateIdToPlayfab(Request.alternateId),
		.concernCategory = new PFCatalogConcernCategory(ConvertConcernCategoryToPlayfab(Request.concernCategory)),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.id = ConvertFStringToCharPtr(Request.id),
		.reason = ConvertFStringToCharPtr(Request.reason)
	};
	HResult = PFCatalogReportItemAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FReportItemAsyncTask::ProcessResults()
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

FReportItemReviewAsyncTask::FReportItemReviewAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogReportItemReviewRequest InRequest,
	const FOnReportItemReviewCompleted& InDelegate)
	: FXAsyncTask(TEXT("FReportItemReviewAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FReportItemReviewAsyncTask::DoWork()
{
	const PFCatalogReportItemReviewRequest RequestType = {
		.alternateId = ConvertCatalogAlternateIdToPlayfab(Request.alternateId),
		.concernCategory = new PFCatalogConcernCategory(ConvertConcernCategoryToPlayfab(Request.concernCategory)),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.itemId = ConvertFStringToCharPtr(Request.itemId),
		.reason = ConvertFStringToCharPtr(Request.reason),
		.reviewId = ConvertFStringToCharPtr(Request.reviewId)
	};
	HResult = PFCatalogReportItemReviewAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FReportItemReviewAsyncTask::ProcessResults()
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

FReviewItemAsyncTask::FReviewItemAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogReviewItemRequest InRequest,
	const FOnReviewItemCompleted& InDelegate)
	: FXAsyncTask(TEXT("FReviewItemAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FReviewItemAsyncTask::DoWork()
{
	const PFCatalogReviewItemRequest RequestType = {
		.alternateId = ConvertCatalogAlternateIdToPlayfab(Request.alternateId),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.id = ConvertFStringToCharPtr(Request.id),
		.review = ConvertReviewToPlayfab(Request.review)
	};
	HResult = PFCatalogReviewItemAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FReviewItemAsyncTask::ProcessResults()
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

FSearchItemsAsyncTask::FSearchItemsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogSearchItemsRequest InRequest,
	const FOnSearchItemsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FSearchItemsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FSearchItemsAsyncTask::DoWork()
{
	const PFCatalogSearchItemsRequest RequestType = {
		.continuationToken = ConvertFStringToCharPtr(Request.continuationToken),
		.count = Request.count,
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.filter = ConvertFStringToCharPtr(Request.filter),
		.language = ConvertFStringToCharPtr(Request.language),
		.orderBy = ConvertFStringToCharPtr(Request.orderBy),
		.search = ConvertFStringToCharPtr(Request.search),
		.select = ConvertFStringToCharPtr(Request.select),
		.store = ConvertStoreReferenceToPlayfab(Request.store)
	};
	HResult = PFCatalogSearchItemsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFCatalogSearchItemsResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FSearchItemsAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFCatalogSearchItemsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFCatalogSearchItemsResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFCatalogSearchItemsResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFCatalogSearchItemsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFCatalogSearchItemsResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFCatalogSearchItemsResponse> ResultType = ConvertSearchItemsResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

#if HC_PLATFORM == HC_PLATFORM_GDK
FSetItemModerationStateAsyncTask::FSetItemModerationStateAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogSetItemModerationStateRequest InRequest,
	const FOnSetItemModerationStateCompleted& InDelegate)
	: FXAsyncTask(TEXT("FSetItemModerationStateAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FSetItemModerationStateAsyncTask::DoWork()
{
	const PFCatalogSetItemModerationStateRequest RequestType = {
		.alternateId = ConvertCatalogAlternateIdToPlayfab(Request.alternateId),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.id = ConvertFStringToCharPtr(Request.id),
		.reason = ConvertFStringToCharPtr(Request.reason),
		.status = new PFCatalogModerationStatus(ConvertModerationStatusToPlayfab(Request.status))
	};
	HResult = PFCatalogSetItemModerationStateAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FSetItemModerationStateAsyncTask::ProcessResults()
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
#endif

FSubmitItemReviewVoteAsyncTask::FSubmitItemReviewVoteAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogSubmitItemReviewVoteRequest InRequest,
	const FOnSubmitItemReviewVoteCompleted& InDelegate)
	: FXAsyncTask(TEXT("FSubmitItemReviewVoteAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FSubmitItemReviewVoteAsyncTask::DoWork()
{
	const PFCatalogSubmitItemReviewVoteRequest RequestType = {
		.alternateId = ConvertCatalogAlternateIdToPlayfab(Request.alternateId),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.itemId = ConvertFStringToCharPtr(Request.itemId),
		.reviewId = ConvertFStringToCharPtr(Request.reviewId),
		.vote = new PFCatalogHelpfulnessVote(ConvertHelpfulnessVoteToPlayfab(Request.vote))
	};
	HResult = PFCatalogSubmitItemReviewVoteAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FSubmitItemReviewVoteAsyncTask::ProcessResults()
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

#if HC_PLATFORM == HC_PLATFORM_GDK
FTakedownItemReviewsAsyncTask::FTakedownItemReviewsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogTakedownItemReviewsRequest InRequest,
	const FOnTakedownItemReviewsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FTakedownItemReviewsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FTakedownItemReviewsAsyncTask::DoWork()
{
	const PFCatalogTakedownItemReviewsRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.reviews = ConvertUnrealArrayToPlayfab<PFCatalogReviewTakedown, FPFCatalogReviewTakedown>(Request.reviews, ConvertReviewTakedownToPlayfab),
		.reviewsCount = (uint32_t)Request.reviews.Num()
	};
	HResult = PFCatalogTakedownItemReviewsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FTakedownItemReviewsAsyncTask::ProcessResults()
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
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK
FUpdateCatalogConfigAsyncTask::FUpdateCatalogConfigAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogUpdateCatalogConfigRequest InRequest,
	const FOnUpdateCatalogConfigCompleted& InDelegate)
	: FXAsyncTask(TEXT("FUpdateCatalogConfigAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FUpdateCatalogConfigAsyncTask::DoWork()
{
	const PFCatalogUpdateCatalogConfigRequest RequestType = {
		.config = ConvertCatalogConfigToPlayfab(Request.config),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num()
	};
	HResult = PFCatalogUpdateCatalogConfigAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FUpdateCatalogConfigAsyncTask::ProcessResults()
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
#endif

FUpdateDraftItemAsyncTask::FUpdateDraftItemAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogUpdateDraftItemRequest InRequest,
	const FOnUpdateDraftItemCompleted& InDelegate)
	: FXAsyncTask(TEXT("FUpdateDraftItemAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FUpdateDraftItemAsyncTask::DoWork()
{
	const PFCatalogUpdateDraftItemRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.item = ConvertCatalogItemToPlayfab(Request.item),
		.publish = Request.publish
	};
	HResult = PFCatalogUpdateDraftItemAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFCatalogUpdateDraftItemResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FUpdateDraftItemAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFCatalogUpdateDraftItemGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFCatalogUpdateDraftItemResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFCatalogUpdateDraftItemResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFCatalogUpdateDraftItemGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFCatalogUpdateDraftItemResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFCatalogUpdateDraftItemResponse> ResultType = ConvertUpdateDraftItemResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

