// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFSegmentsAsyncTasks.h"

FClientGetPlayerSegmentsAsyncTask::FClientGetPlayerSegmentsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	const FOnClientGetPlayerSegmentsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientGetPlayerSegmentsAsyncTask")),
	EntityHandle(EntityHandle),
	Delegate(InDelegate)
{
};

void FClientGetPlayerSegmentsAsyncTask::DoWork()
{
	
	HResult = PFSegmentsClientGetPlayerSegmentsAsync(EntityHandle.Get(), *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFSegmentsGetPlayerSegmentsResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientGetPlayerSegmentsAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFSegmentsClientGetPlayerSegmentsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFSegmentsGetPlayerSegmentsResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFSegmentsGetPlayerSegmentsResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFSegmentsClientGetPlayerSegmentsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFSegmentsGetPlayerSegmentsResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFSegmentsGetPlayerSegmentsResult> ResultType = ConvertGetPlayerSegmentsResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FClientGetPlayerTagsAsyncTask::FClientGetPlayerTagsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFSegmentsGetPlayerTagsRequest InRequest,
	const FOnClientGetPlayerTagsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientGetPlayerTagsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientGetPlayerTagsAsyncTask::DoWork()
{
	const PFSegmentsGetPlayerTagsRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.playfabNamespace = ConvertFStringToCharPtr(Request.playfabNamespace),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId)
	};
	HResult = PFSegmentsClientGetPlayerTagsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFSegmentsGetPlayerTagsResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientGetPlayerTagsAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFSegmentsClientGetPlayerTagsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFSegmentsGetPlayerTagsResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFSegmentsGetPlayerTagsResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFSegmentsClientGetPlayerTagsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFSegmentsGetPlayerTagsResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFSegmentsGetPlayerTagsResult> ResultType = ConvertGetPlayerTagsResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerAddPlayerTagAsyncTask::FServerAddPlayerTagAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFSegmentsAddPlayerTagRequest InRequest,
	const FOnServerAddPlayerTagCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerAddPlayerTagAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerAddPlayerTagAsyncTask::DoWork()
{
	const PFSegmentsAddPlayerTagRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId),
		.tagName = ConvertFStringToCharPtr(Request.tagName)
	};
	HResult = PFSegmentsServerAddPlayerTagAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FServerAddPlayerTagAsyncTask::ProcessResults()
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

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerGetAllSegmentsAsyncTask::FServerGetAllSegmentsAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	const FOnServerGetAllSegmentsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerGetAllSegmentsAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Delegate(InDelegate)
{
};

void FServerGetAllSegmentsAsyncTask::DoWork()
{
	
	HResult = PFSegmentsServerGetAllSegmentsAsync(TitleEntityHandle.Get(), *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFSegmentsGetAllSegmentsResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerGetAllSegmentsAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFSegmentsServerGetAllSegmentsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFSegmentsGetAllSegmentsResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFSegmentsGetAllSegmentsResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFSegmentsServerGetAllSegmentsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFSegmentsGetAllSegmentsResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFSegmentsGetAllSegmentsResult> ResultType = ConvertGetAllSegmentsResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerGetPlayerSegmentsAsyncTask::FServerGetPlayerSegmentsAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFSegmentsGetPlayersSegmentsRequest InRequest,
	const FOnServerGetPlayerSegmentsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerGetPlayerSegmentsAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerGetPlayerSegmentsAsyncTask::DoWork()
{
	const PFSegmentsGetPlayersSegmentsRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId)
	};
	HResult = PFSegmentsServerGetPlayerSegmentsAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFSegmentsGetPlayerSegmentsResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerGetPlayerSegmentsAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFSegmentsServerGetPlayerSegmentsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFSegmentsGetPlayerSegmentsResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFSegmentsGetPlayerSegmentsResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFSegmentsServerGetPlayerSegmentsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFSegmentsGetPlayerSegmentsResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFSegmentsGetPlayerSegmentsResult> ResultType = ConvertGetPlayerSegmentsResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerGetPlayersInSegmentAsyncTask::FServerGetPlayersInSegmentAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFSegmentsGetPlayersInSegmentRequest InRequest,
	const FOnServerGetPlayersInSegmentCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerGetPlayersInSegmentAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerGetPlayersInSegmentAsyncTask::DoWork()
{
	const PFSegmentsGetPlayersInSegmentRequest RequestType = {
		.continuationToken = ConvertFStringToCharPtr(Request.continuationToken),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.getProfilesAsync = Request.getProfilesAsync ? new bool(*Request.getProfilesAsync) : nullptr,
		.maxBatchSize = Request.maxBatchSize ? new uint32(*Request.maxBatchSize) : nullptr,
		.secondsToLive = Request.secondsToLive ? new uint32(*Request.secondsToLive) : nullptr,
		.segmentId = ConvertFStringToCharPtr(Request.segmentId)
	};
	HResult = PFSegmentsServerGetPlayersInSegmentAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFSegmentsGetPlayersInSegmentResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerGetPlayersInSegmentAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFSegmentsServerGetPlayersInSegmentGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFSegmentsGetPlayersInSegmentResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFSegmentsGetPlayersInSegmentResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFSegmentsServerGetPlayersInSegmentGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFSegmentsGetPlayersInSegmentResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFSegmentsGetPlayersInSegmentResult> ResultType = ConvertGetPlayersInSegmentResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerGetPlayerTagsAsyncTask::FServerGetPlayerTagsAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFSegmentsGetPlayerTagsRequest InRequest,
	const FOnServerGetPlayerTagsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerGetPlayerTagsAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerGetPlayerTagsAsyncTask::DoWork()
{
	const PFSegmentsGetPlayerTagsRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.playfabNamespace = ConvertFStringToCharPtr(Request.playfabNamespace),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId)
	};
	HResult = PFSegmentsServerGetPlayerTagsAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFSegmentsGetPlayerTagsResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerGetPlayerTagsAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFSegmentsServerGetPlayerTagsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFSegmentsGetPlayerTagsResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFSegmentsGetPlayerTagsResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFSegmentsServerGetPlayerTagsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFSegmentsGetPlayerTagsResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFSegmentsGetPlayerTagsResult> ResultType = ConvertGetPlayerTagsResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerRemovePlayerTagAsyncTask::FServerRemovePlayerTagAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFSegmentsRemovePlayerTagRequest InRequest,
	const FOnServerRemovePlayerTagCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerRemovePlayerTagAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerRemovePlayerTagAsyncTask::DoWork()
{
	const PFSegmentsRemovePlayerTagRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId),
		.tagName = ConvertFStringToCharPtr(Request.tagName)
	};
	HResult = PFSegmentsServerRemovePlayerTagAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FServerRemovePlayerTagAsyncTask::ProcessResults()
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

