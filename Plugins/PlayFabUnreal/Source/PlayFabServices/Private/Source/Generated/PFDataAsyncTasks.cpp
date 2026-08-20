// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFDataAsyncTasks.h"

FAbortFileUploadsAsyncTask::FAbortFileUploadsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFDataAbortFileUploadsRequest InRequest,
	const FOnAbortFileUploadsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FAbortFileUploadsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FAbortFileUploadsAsyncTask::DoWork()
{
	const PFDataAbortFileUploadsRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.fileNames = ConvertFStringArrayToPlayfab(Request.fileNames),
		.fileNamesCount = (uint32_t)Request.fileNames.Num(),
		.profileVersion = Request.profileVersion ? new int32(*Request.profileVersion) : nullptr
	};
	HResult = PFDataAbortFileUploadsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFDataAbortFileUploadsResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FAbortFileUploadsAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFDataAbortFileUploadsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFDataAbortFileUploadsResponse{ .ErrorMessage = FString::Printf(TEXT("GetResultSize failure: 0x%08X"), static_cast<uint32>(HResult)) }, false);
		return;
	}

	PFDataAbortFileUploadsResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFDataAbortFileUploadsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("GetResult failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFDataAbortFileUploadsResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFDataAbortFileUploadsResponse> ResultType = ConvertAbortFileUploadsResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FDeleteFilesAsyncTask::FDeleteFilesAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFDataDeleteFilesRequest InRequest,
	const FOnDeleteFilesCompleted& InDelegate)
	: FXAsyncTask(TEXT("FDeleteFilesAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FDeleteFilesAsyncTask::DoWork()
{
	const PFDataDeleteFilesRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.fileNames = ConvertFStringArrayToPlayfab(Request.fileNames),
		.fileNamesCount = (uint32_t)Request.fileNames.Num(),
		.profileVersion = Request.profileVersion ? new int32(*Request.profileVersion) : nullptr
	};
	HResult = PFDataDeleteFilesAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFDataDeleteFilesResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FDeleteFilesAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFDataDeleteFilesGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFDataDeleteFilesResponse{ .ErrorMessage = FString::Printf(TEXT("GetResultSize failure: 0x%08X"), static_cast<uint32>(HResult)) }, false);
		return;
	}

	PFDataDeleteFilesResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFDataDeleteFilesGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("GetResult failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFDataDeleteFilesResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFDataDeleteFilesResponse> ResultType = ConvertDeleteFilesResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FFinalizeFileUploadsAsyncTask::FFinalizeFileUploadsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFDataFinalizeFileUploadsRequest InRequest,
	const FOnFinalizeFileUploadsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FFinalizeFileUploadsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FFinalizeFileUploadsAsyncTask::DoWork()
{
	const PFDataFinalizeFileUploadsRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.fileNames = ConvertFStringArrayToPlayfab(Request.fileNames),
		.fileNamesCount = (uint32_t)Request.fileNames.Num(),
		.profileVersion = Request.profileVersion
	};
	HResult = PFDataFinalizeFileUploadsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFDataFinalizeFileUploadsResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FFinalizeFileUploadsAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFDataFinalizeFileUploadsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFDataFinalizeFileUploadsResponse{ .ErrorMessage = FString::Printf(TEXT("GetResultSize failure: 0x%08X"), static_cast<uint32>(HResult)) }, false);
		return;
	}

	PFDataFinalizeFileUploadsResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFDataFinalizeFileUploadsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("GetResult failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFDataFinalizeFileUploadsResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFDataFinalizeFileUploadsResponse> ResultType = ConvertFinalizeFileUploadsResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FGetFilesAsyncTask::FGetFilesAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFDataGetFilesRequest InRequest,
	const FOnGetFilesCompleted& InDelegate)
	: FXAsyncTask(TEXT("FGetFilesAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FGetFilesAsyncTask::DoWork()
{
	const PFDataGetFilesRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity)
	};
	HResult = PFDataGetFilesAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFDataGetFilesResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FGetFilesAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFDataGetFilesGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFDataGetFilesResponse{ .ErrorMessage = FString::Printf(TEXT("GetResultSize failure: 0x%08X"), static_cast<uint32>(HResult)) }, false);
		return;
	}

	PFDataGetFilesResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFDataGetFilesGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("GetResult failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFDataGetFilesResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFDataGetFilesResponse> ResultType = ConvertGetFilesResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FGetObjectsAsyncTask::FGetObjectsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFDataGetObjectsRequest InRequest,
	const FOnGetObjectsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FGetObjectsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FGetObjectsAsyncTask::DoWork()
{
	const PFDataGetObjectsRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.escapeObject = Request.escapeObject ? new bool(*Request.escapeObject) : nullptr
	};
	HResult = PFDataGetObjectsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFDataGetObjectsResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FGetObjectsAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFDataGetObjectsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFDataGetObjectsResponse{ .ErrorMessage = FString::Printf(TEXT("GetResultSize failure: 0x%08X"), static_cast<uint32>(HResult)) }, false);
		return;
	}

	PFDataGetObjectsResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFDataGetObjectsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("GetResult failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFDataGetObjectsResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFDataGetObjectsResponse> ResultType = ConvertGetObjectsResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FInitiateFileUploadsAsyncTask::FInitiateFileUploadsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFDataInitiateFileUploadsRequest InRequest,
	const FOnInitiateFileUploadsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FInitiateFileUploadsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FInitiateFileUploadsAsyncTask::DoWork()
{
	const PFDataInitiateFileUploadsRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.fileNames = ConvertFStringArrayToPlayfab(Request.fileNames),
		.fileNamesCount = (uint32_t)Request.fileNames.Num(),
		.profileVersion = Request.profileVersion ? new int32(*Request.profileVersion) : nullptr
	};
	HResult = PFDataInitiateFileUploadsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFDataInitiateFileUploadsResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FInitiateFileUploadsAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFDataInitiateFileUploadsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFDataInitiateFileUploadsResponse{ .ErrorMessage = FString::Printf(TEXT("GetResultSize failure: 0x%08X"), static_cast<uint32>(HResult)) }, false);
		return;
	}

	PFDataInitiateFileUploadsResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFDataInitiateFileUploadsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("GetResult failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFDataInitiateFileUploadsResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFDataInitiateFileUploadsResponse> ResultType = ConvertInitiateFileUploadsResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FSetObjectsAsyncTask::FSetObjectsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFDataSetObjectsRequest InRequest,
	const FOnSetObjectsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FSetObjectsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FSetObjectsAsyncTask::DoWork()
{
	const PFDataSetObjectsRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.expectedProfileVersion = Request.expectedProfileVersion ? new int32(*Request.expectedProfileVersion) : nullptr,
		.objects = ConvertUnrealArrayToPlayfab<PFDataSetObject, FPFDataSetObject>(Request.objects, ConvertSetObjectToPlayfab),
		.objectsCount = (uint32_t)Request.objects.Num()
	};
	HResult = PFDataSetObjectsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFDataSetObjectsResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FSetObjectsAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFDataSetObjectsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFDataSetObjectsResponse{ .ErrorMessage = FString::Printf(TEXT("GetResultSize failure: 0x%08X"), static_cast<uint32>(HResult)) }, false);
		return;
	}

	PFDataSetObjectsResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFDataSetObjectsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("GetResult failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFDataSetObjectsResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFDataSetObjectsResponse> ResultType = ConvertSetObjectsResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

