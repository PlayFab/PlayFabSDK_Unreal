// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFLocalizationAsyncTasks.h"

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FGetLanguageListAsyncTask::FGetLanguageListAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFLocalizationGetLanguageListRequest InRequest,
	const FOnGetLanguageListCompleted& InDelegate)
	: FXAsyncTask(TEXT("FGetLanguageListAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FGetLanguageListAsyncTask::DoWork()
{
	const PFLocalizationGetLanguageListRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num()
	};
	HResult = PFLocalizationGetLanguageListAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFLocalizationGetLanguageListResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FGetLanguageListAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFLocalizationGetLanguageListGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFLocalizationGetLanguageListResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFLocalizationGetLanguageListResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFLocalizationGetLanguageListGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFLocalizationGetLanguageListResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFLocalizationGetLanguageListResponse> ResultType = ConvertGetLanguageListResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

