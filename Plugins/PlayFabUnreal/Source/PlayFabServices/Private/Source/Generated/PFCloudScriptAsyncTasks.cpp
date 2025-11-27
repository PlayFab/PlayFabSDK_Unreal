// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFCloudScriptAsyncTasks.h"

FClientExecuteCloudScriptAsyncTask::FClientExecuteCloudScriptAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCloudScriptExecuteCloudScriptRequest InRequest,
	const FOnClientExecuteCloudScriptCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientExecuteCloudScriptAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientExecuteCloudScriptAsyncTask::DoWork()
{
	const PFCloudScriptExecuteCloudScriptRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.functionName = ConvertFStringToCharPtr(Request.functionName),
		.functionParameter = PFJsonObject{ .stringValue = ConvertFStringToCharPtr(Request.functionParameter.stringValue) },
		.generatePlayStreamEvent = Request.generatePlayStreamEvent ? new bool(*Request.generatePlayStreamEvent) : nullptr,
		.revisionSelection = new PFCloudScriptCloudScriptRevisionOption(ConvertCloudScriptRevisionOptionToPlayfab(Request.revisionSelection)),
		.specificRevision = Request.specificRevision ? new int32(*Request.specificRevision) : nullptr
	};
	HResult = PFCloudScriptClientExecuteCloudScriptAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFCloudScriptExecuteCloudScriptResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientExecuteCloudScriptAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFCloudScriptClientExecuteCloudScriptGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFCloudScriptExecuteCloudScriptResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFCloudScriptExecuteCloudScriptResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFCloudScriptClientExecuteCloudScriptGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFCloudScriptExecuteCloudScriptResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFCloudScriptExecuteCloudScriptResult> ResultType = ConvertExecuteCloudScriptResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerExecuteCloudScriptAsyncTask::FServerExecuteCloudScriptAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFCloudScriptExecuteCloudScriptServerRequest InRequest,
	const FOnServerExecuteCloudScriptCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerExecuteCloudScriptAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerExecuteCloudScriptAsyncTask::DoWork()
{
	const PFCloudScriptExecuteCloudScriptServerRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.functionName = ConvertFStringToCharPtr(Request.functionName),
		.functionParameter = PFJsonObject{ .stringValue = ConvertFStringToCharPtr(Request.functionParameter.stringValue) },
		.generatePlayStreamEvent = Request.generatePlayStreamEvent ? new bool(*Request.generatePlayStreamEvent) : nullptr,
		.playFabId = ConvertFStringToCharPtr(Request.playFabId),
		.revisionSelection = new PFCloudScriptCloudScriptRevisionOption(ConvertCloudScriptRevisionOptionToPlayfab(Request.revisionSelection)),
		.specificRevision = Request.specificRevision ? new int32(*Request.specificRevision) : nullptr
	};
	HResult = PFCloudScriptServerExecuteCloudScriptAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFCloudScriptExecuteCloudScriptResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerExecuteCloudScriptAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFCloudScriptServerExecuteCloudScriptGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFCloudScriptExecuteCloudScriptResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFCloudScriptExecuteCloudScriptResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFCloudScriptServerExecuteCloudScriptGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFCloudScriptExecuteCloudScriptResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFCloudScriptExecuteCloudScriptResult> ResultType = ConvertExecuteCloudScriptResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

FExecuteEntityCloudScriptAsyncTask::FExecuteEntityCloudScriptAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCloudScriptExecuteEntityCloudScriptRequest InRequest,
	const FOnExecuteEntityCloudScriptCompleted& InDelegate)
	: FXAsyncTask(TEXT("FExecuteEntityCloudScriptAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FExecuteEntityCloudScriptAsyncTask::DoWork()
{
	const PFCloudScriptExecuteEntityCloudScriptRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.functionName = ConvertFStringToCharPtr(Request.functionName),
		.functionParameter = PFJsonObject{ .stringValue = ConvertFStringToCharPtr(Request.functionParameter.stringValue) },
		.generatePlayStreamEvent = Request.generatePlayStreamEvent ? new bool(*Request.generatePlayStreamEvent) : nullptr,
		.revisionSelection = new PFCloudScriptCloudScriptRevisionOption(ConvertCloudScriptRevisionOptionToPlayfab(Request.revisionSelection)),
		.specificRevision = Request.specificRevision ? new int32(*Request.specificRevision) : nullptr
	};
	HResult = PFCloudScriptExecuteEntityCloudScriptAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFCloudScriptExecuteCloudScriptResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FExecuteEntityCloudScriptAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFCloudScriptExecuteEntityCloudScriptGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFCloudScriptExecuteCloudScriptResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFCloudScriptExecuteCloudScriptResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFCloudScriptExecuteEntityCloudScriptGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFCloudScriptExecuteCloudScriptResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFCloudScriptExecuteCloudScriptResult> ResultType = ConvertExecuteCloudScriptResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FExecuteFunctionAsyncTask::FExecuteFunctionAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCloudScriptExecuteFunctionRequest InRequest,
	const FOnExecuteFunctionCompleted& InDelegate)
	: FXAsyncTask(TEXT("FExecuteFunctionAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FExecuteFunctionAsyncTask::DoWork()
{
	const PFCloudScriptExecuteFunctionRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.functionName = ConvertFStringToCharPtr(Request.functionName),
		.functionParameter = PFJsonObject{ .stringValue = ConvertFStringToCharPtr(Request.functionParameter.stringValue) },
		.generatePlayStreamEvent = Request.generatePlayStreamEvent ? new bool(*Request.generatePlayStreamEvent) : nullptr
	};
	HResult = PFCloudScriptExecuteFunctionAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFCloudScriptExecuteFunctionResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FExecuteFunctionAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFCloudScriptExecuteFunctionGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFCloudScriptExecuteFunctionResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFCloudScriptExecuteFunctionResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFCloudScriptExecuteFunctionGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFCloudScriptExecuteFunctionResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFCloudScriptExecuteFunctionResult> ResultType = ConvertExecuteFunctionResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

#if 0
FListEventHubFunctionsAsyncTask::FListEventHubFunctionsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCloudScriptListFunctionsRequest InRequest,
	const FOnListEventHubFunctionsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FListEventHubFunctionsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FListEventHubFunctionsAsyncTask::DoWork()
{
	const PFCloudScriptListFunctionsRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num()
	};
	HResult = PFCloudScriptListEventHubFunctionsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFCloudScriptListEventHubFunctionsResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FListEventHubFunctionsAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFCloudScriptListEventHubFunctionsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFCloudScriptListEventHubFunctionsResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFCloudScriptListEventHubFunctionsResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFCloudScriptListEventHubFunctionsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFCloudScriptListEventHubFunctionsResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFCloudScriptListEventHubFunctionsResult> ResultType = ConvertListEventHubFunctionsResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if 0
FRegisterEventHubFunctionAsyncTask::FRegisterEventHubFunctionAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCloudScriptRegisterEventHubFunctionRequest InRequest,
	const FOnRegisterEventHubFunctionCompleted& InDelegate)
	: FXAsyncTask(TEXT("FRegisterEventHubFunctionAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FRegisterEventHubFunctionAsyncTask::DoWork()
{
	const PFCloudScriptRegisterEventHubFunctionRequest RequestType = {
		.connectionString = ConvertFStringToCharPtr(Request.connectionString),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.eventHubName = ConvertFStringToCharPtr(Request.eventHubName),
		.functionName = ConvertFStringToCharPtr(Request.functionName)
	};
	HResult = PFCloudScriptRegisterEventHubFunctionAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FRegisterEventHubFunctionAsyncTask::ProcessResults()
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

