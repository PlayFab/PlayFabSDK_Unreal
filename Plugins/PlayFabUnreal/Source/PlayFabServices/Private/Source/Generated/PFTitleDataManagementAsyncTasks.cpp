// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFTitleDataManagementAsyncTasks.h"

FClientGetPublisherDataAsyncTask::FClientGetPublisherDataAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFTitleDataManagementGetPublisherDataRequest InRequest,
	const FOnClientGetPublisherDataCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientGetPublisherDataAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientGetPublisherDataAsyncTask::DoWork()
{
	const PFTitleDataManagementGetPublisherDataRequest RequestType = {
		.keys = ConvertFStringArrayToPlayfab(Request.keys),
		.keysCount = (uint32_t)Request.keys.Num()
	};
	HResult = PFTitleDataManagementClientGetPublisherDataAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFTitleDataManagementGetPublisherDataResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientGetPublisherDataAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFTitleDataManagementClientGetPublisherDataGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFTitleDataManagementGetPublisherDataResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFTitleDataManagementGetPublisherDataResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFTitleDataManagementClientGetPublisherDataGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFTitleDataManagementGetPublisherDataResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFTitleDataManagementGetPublisherDataResult> ResultType = ConvertGetPublisherDataResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FClientGetTimeAsyncTask::FClientGetTimeAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	const FOnClientGetTimeCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientGetTimeAsyncTask")),
	EntityHandle(EntityHandle),
	Delegate(InDelegate)
{
};

void FClientGetTimeAsyncTask::DoWork()
{
	
	HResult = PFTitleDataManagementClientGetTimeAsync(EntityHandle.Get(), *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFTitleDataManagementGetTimeResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientGetTimeAsyncTask::ProcessResults()
{
	PFTitleDataManagementGetTimeResult Result = {};
	HResult = PFTitleDataManagementClientGetTimeGetResult(*mAsyncBlock, &Result);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFTitleDataManagementGetTimeResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFTitleDataManagementGetTimeResult> ResultType = ConvertGetTimeResultToUnreal(&Result);

	Delegate.Execute(*ResultType, true);
}

FClientGetTitleDataAsyncTask::FClientGetTitleDataAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFTitleDataManagementGetTitleDataRequest InRequest,
	const FOnClientGetTitleDataCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientGetTitleDataAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientGetTitleDataAsyncTask::DoWork()
{
	const PFTitleDataManagementGetTitleDataRequest RequestType = {
		.keys = ConvertFStringArrayToPlayfab(Request.keys),
		.keysCount = (uint32_t)Request.keys.Num(),
		.overrideLabel = ConvertFStringToCharPtr(Request.overrideLabel)
	};
	HResult = PFTitleDataManagementClientGetTitleDataAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFTitleDataManagementGetTitleDataResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientGetTitleDataAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFTitleDataManagementClientGetTitleDataGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFTitleDataManagementGetTitleDataResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFTitleDataManagementGetTitleDataResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFTitleDataManagementClientGetTitleDataGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFTitleDataManagementGetTitleDataResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFTitleDataManagementGetTitleDataResult> ResultType = ConvertGetTitleDataResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FClientGetTitleNewsAsyncTask::FClientGetTitleNewsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFTitleDataManagementGetTitleNewsRequest InRequest,
	const FOnClientGetTitleNewsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientGetTitleNewsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientGetTitleNewsAsyncTask::DoWork()
{
	const PFTitleDataManagementGetTitleNewsRequest RequestType = {
		.count = Request.count ? new int32(*Request.count) : nullptr
	};
	HResult = PFTitleDataManagementClientGetTitleNewsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFTitleDataManagementGetTitleNewsResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientGetTitleNewsAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFTitleDataManagementClientGetTitleNewsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFTitleDataManagementGetTitleNewsResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFTitleDataManagementGetTitleNewsResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFTitleDataManagementClientGetTitleNewsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFTitleDataManagementGetTitleNewsResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFTitleDataManagementGetTitleNewsResult> ResultType = ConvertGetTitleNewsResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerGetPublisherDataAsyncTask::FServerGetPublisherDataAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFTitleDataManagementGetPublisherDataRequest InRequest,
	const FOnServerGetPublisherDataCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerGetPublisherDataAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerGetPublisherDataAsyncTask::DoWork()
{
	const PFTitleDataManagementGetPublisherDataRequest RequestType = {
		.keys = ConvertFStringArrayToPlayfab(Request.keys),
		.keysCount = (uint32_t)Request.keys.Num()
	};
	HResult = PFTitleDataManagementServerGetPublisherDataAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFTitleDataManagementGetPublisherDataResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerGetPublisherDataAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFTitleDataManagementServerGetPublisherDataGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFTitleDataManagementGetPublisherDataResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFTitleDataManagementGetPublisherDataResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFTitleDataManagementServerGetPublisherDataGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFTitleDataManagementGetPublisherDataResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFTitleDataManagementGetPublisherDataResult> ResultType = ConvertGetPublisherDataResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerGetTimeAsyncTask::FServerGetTimeAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	const FOnServerGetTimeCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerGetTimeAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Delegate(InDelegate)
{
};

void FServerGetTimeAsyncTask::DoWork()
{
	
	HResult = PFTitleDataManagementServerGetTimeAsync(TitleEntityHandle.Get(), *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFTitleDataManagementGetTimeResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerGetTimeAsyncTask::ProcessResults()
{
	PFTitleDataManagementGetTimeResult Result = {};
	HResult = PFTitleDataManagementServerGetTimeGetResult(*mAsyncBlock, &Result);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFTitleDataManagementGetTimeResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFTitleDataManagementGetTimeResult> ResultType = ConvertGetTimeResultToUnreal(&Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerGetTitleDataAsyncTask::FServerGetTitleDataAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFTitleDataManagementGetTitleDataRequest InRequest,
	const FOnServerGetTitleDataCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerGetTitleDataAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerGetTitleDataAsyncTask::DoWork()
{
	const PFTitleDataManagementGetTitleDataRequest RequestType = {
		.keys = ConvertFStringArrayToPlayfab(Request.keys),
		.keysCount = (uint32_t)Request.keys.Num(),
		.overrideLabel = ConvertFStringToCharPtr(Request.overrideLabel)
	};
	HResult = PFTitleDataManagementServerGetTitleDataAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFTitleDataManagementGetTitleDataResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerGetTitleDataAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFTitleDataManagementServerGetTitleDataGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFTitleDataManagementGetTitleDataResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFTitleDataManagementGetTitleDataResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFTitleDataManagementServerGetTitleDataGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFTitleDataManagementGetTitleDataResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFTitleDataManagementGetTitleDataResult> ResultType = ConvertGetTitleDataResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerGetTitleInternalDataAsyncTask::FServerGetTitleInternalDataAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFTitleDataManagementGetTitleDataRequest InRequest,
	const FOnServerGetTitleInternalDataCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerGetTitleInternalDataAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerGetTitleInternalDataAsyncTask::DoWork()
{
	const PFTitleDataManagementGetTitleDataRequest RequestType = {
		.keys = ConvertFStringArrayToPlayfab(Request.keys),
		.keysCount = (uint32_t)Request.keys.Num(),
		.overrideLabel = ConvertFStringToCharPtr(Request.overrideLabel)
	};
	HResult = PFTitleDataManagementServerGetTitleInternalDataAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFTitleDataManagementGetTitleDataResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerGetTitleInternalDataAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFTitleDataManagementServerGetTitleInternalDataGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFTitleDataManagementGetTitleDataResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFTitleDataManagementGetTitleDataResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFTitleDataManagementServerGetTitleInternalDataGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFTitleDataManagementGetTitleDataResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFTitleDataManagementGetTitleDataResult> ResultType = ConvertGetTitleDataResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerGetTitleNewsAsyncTask::FServerGetTitleNewsAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFTitleDataManagementGetTitleNewsRequest InRequest,
	const FOnServerGetTitleNewsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerGetTitleNewsAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerGetTitleNewsAsyncTask::DoWork()
{
	const PFTitleDataManagementGetTitleNewsRequest RequestType = {
		.count = Request.count ? new int32(*Request.count) : nullptr
	};
	HResult = PFTitleDataManagementServerGetTitleNewsAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFTitleDataManagementGetTitleNewsResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerGetTitleNewsAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFTitleDataManagementServerGetTitleNewsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFTitleDataManagementGetTitleNewsResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFTitleDataManagementGetTitleNewsResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFTitleDataManagementServerGetTitleNewsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFTitleDataManagementGetTitleNewsResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFTitleDataManagementGetTitleNewsResult> ResultType = ConvertGetTitleNewsResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerSetPublisherDataAsyncTask::FServerSetPublisherDataAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFTitleDataManagementSetPublisherDataRequest InRequest,
	const FOnServerSetPublisherDataCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerSetPublisherDataAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerSetPublisherDataAsyncTask::DoWork()
{
	const PFTitleDataManagementSetPublisherDataRequest RequestType = {
		.key = ConvertFStringToCharPtr(Request.key),
		.value = ConvertFStringToCharPtr(Request.value)
	};
	HResult = PFTitleDataManagementServerSetPublisherDataAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FServerSetPublisherDataAsyncTask::ProcessResults()
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
FServerSetTitleDataAsyncTask::FServerSetTitleDataAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFTitleDataManagementSetTitleDataRequest InRequest,
	const FOnServerSetTitleDataCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerSetTitleDataAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerSetTitleDataAsyncTask::DoWork()
{
	const PFTitleDataManagementSetTitleDataRequest RequestType = {
		.key = ConvertFStringToCharPtr(Request.key),
		.value = ConvertFStringToCharPtr(Request.value)
	};
	HResult = PFTitleDataManagementServerSetTitleDataAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FServerSetTitleDataAsyncTask::ProcessResults()
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
FServerSetTitleInternalDataAsyncTask::FServerSetTitleInternalDataAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFTitleDataManagementSetTitleDataRequest InRequest,
	const FOnServerSetTitleInternalDataCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerSetTitleInternalDataAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerSetTitleInternalDataAsyncTask::DoWork()
{
	const PFTitleDataManagementSetTitleDataRequest RequestType = {
		.key = ConvertFStringToCharPtr(Request.key),
		.value = ConvertFStringToCharPtr(Request.value)
	};
	HResult = PFTitleDataManagementServerSetTitleInternalDataAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FServerSetTitleInternalDataAsyncTask::ProcessResults()
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

