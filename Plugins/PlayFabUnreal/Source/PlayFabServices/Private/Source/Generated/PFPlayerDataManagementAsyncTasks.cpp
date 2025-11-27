// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFPlayerDataManagementAsyncTasks.h"

FClientDeletePlayerCustomPropertiesAsyncTask::FClientDeletePlayerCustomPropertiesAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFPlayerDataManagementClientDeletePlayerCustomPropertiesRequest InRequest,
	const FOnClientDeletePlayerCustomPropertiesCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientDeletePlayerCustomPropertiesAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientDeletePlayerCustomPropertiesAsyncTask::DoWork()
{
	const PFPlayerDataManagementClientDeletePlayerCustomPropertiesRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.expectedPropertiesVersion = Request.expectedPropertiesVersion ? new int32(*Request.expectedPropertiesVersion) : nullptr,
		.propertyNames = ConvertFStringArrayToPlayfab(Request.propertyNames),
		.propertyNamesCount = (uint32_t)Request.propertyNames.Num()
	};
	HResult = PFPlayerDataManagementClientDeletePlayerCustomPropertiesAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFPlayerDataManagementClientDeletePlayerCustomPropertiesResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientDeletePlayerCustomPropertiesAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFPlayerDataManagementClientDeletePlayerCustomPropertiesGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFPlayerDataManagementClientDeletePlayerCustomPropertiesResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFPlayerDataManagementClientDeletePlayerCustomPropertiesResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFPlayerDataManagementClientDeletePlayerCustomPropertiesGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFPlayerDataManagementClientDeletePlayerCustomPropertiesResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFPlayerDataManagementClientDeletePlayerCustomPropertiesResult> ResultType = ConvertClientDeletePlayerCustomPropertiesResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FClientGetPlayerCustomPropertyAsyncTask::FClientGetPlayerCustomPropertyAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFPlayerDataManagementClientGetPlayerCustomPropertyRequest InRequest,
	const FOnClientGetPlayerCustomPropertyCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientGetPlayerCustomPropertyAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientGetPlayerCustomPropertyAsyncTask::DoWork()
{
	const PFPlayerDataManagementClientGetPlayerCustomPropertyRequest RequestType = {
		.propertyName = ConvertFStringToCharPtr(Request.propertyName)
	};
	HResult = PFPlayerDataManagementClientGetPlayerCustomPropertyAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFPlayerDataManagementClientGetPlayerCustomPropertyResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientGetPlayerCustomPropertyAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFPlayerDataManagementClientGetPlayerCustomPropertyGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFPlayerDataManagementClientGetPlayerCustomPropertyResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFPlayerDataManagementClientGetPlayerCustomPropertyResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFPlayerDataManagementClientGetPlayerCustomPropertyGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFPlayerDataManagementClientGetPlayerCustomPropertyResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFPlayerDataManagementClientGetPlayerCustomPropertyResult> ResultType = ConvertClientGetPlayerCustomPropertyResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FClientGetUserDataAsyncTask::FClientGetUserDataAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFPlayerDataManagementGetUserDataRequest InRequest,
	const FOnClientGetUserDataCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientGetUserDataAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientGetUserDataAsyncTask::DoWork()
{
	const PFPlayerDataManagementGetUserDataRequest RequestType = {
		.ifChangedFromDataVersion = Request.ifChangedFromDataVersion ? new uint32(*Request.ifChangedFromDataVersion) : nullptr,
		.keys = ConvertFStringArrayToPlayfab(Request.keys),
		.keysCount = (uint32_t)Request.keys.Num(),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId)
	};
	HResult = PFPlayerDataManagementClientGetUserDataAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFPlayerDataManagementClientGetUserDataResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientGetUserDataAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFPlayerDataManagementClientGetUserDataGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFPlayerDataManagementClientGetUserDataResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFPlayerDataManagementClientGetUserDataResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFPlayerDataManagementClientGetUserDataGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFPlayerDataManagementClientGetUserDataResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFPlayerDataManagementClientGetUserDataResult> ResultType = ConvertClientGetUserDataResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FClientGetUserPublisherDataAsyncTask::FClientGetUserPublisherDataAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFPlayerDataManagementGetUserDataRequest InRequest,
	const FOnClientGetUserPublisherDataCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientGetUserPublisherDataAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientGetUserPublisherDataAsyncTask::DoWork()
{
	const PFPlayerDataManagementGetUserDataRequest RequestType = {
		.ifChangedFromDataVersion = Request.ifChangedFromDataVersion ? new uint32(*Request.ifChangedFromDataVersion) : nullptr,
		.keys = ConvertFStringArrayToPlayfab(Request.keys),
		.keysCount = (uint32_t)Request.keys.Num(),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId)
	};
	HResult = PFPlayerDataManagementClientGetUserPublisherDataAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFPlayerDataManagementClientGetUserDataResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientGetUserPublisherDataAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFPlayerDataManagementClientGetUserPublisherDataGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFPlayerDataManagementClientGetUserDataResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFPlayerDataManagementClientGetUserDataResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFPlayerDataManagementClientGetUserPublisherDataGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFPlayerDataManagementClientGetUserDataResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFPlayerDataManagementClientGetUserDataResult> ResultType = ConvertClientGetUserDataResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FClientGetUserPublisherReadOnlyDataAsyncTask::FClientGetUserPublisherReadOnlyDataAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFPlayerDataManagementGetUserDataRequest InRequest,
	const FOnClientGetUserPublisherReadOnlyDataCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientGetUserPublisherReadOnlyDataAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientGetUserPublisherReadOnlyDataAsyncTask::DoWork()
{
	const PFPlayerDataManagementGetUserDataRequest RequestType = {
		.ifChangedFromDataVersion = Request.ifChangedFromDataVersion ? new uint32(*Request.ifChangedFromDataVersion) : nullptr,
		.keys = ConvertFStringArrayToPlayfab(Request.keys),
		.keysCount = (uint32_t)Request.keys.Num(),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId)
	};
	HResult = PFPlayerDataManagementClientGetUserPublisherReadOnlyDataAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFPlayerDataManagementClientGetUserDataResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientGetUserPublisherReadOnlyDataAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFPlayerDataManagementClientGetUserPublisherReadOnlyDataGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFPlayerDataManagementClientGetUserDataResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFPlayerDataManagementClientGetUserDataResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFPlayerDataManagementClientGetUserPublisherReadOnlyDataGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFPlayerDataManagementClientGetUserDataResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFPlayerDataManagementClientGetUserDataResult> ResultType = ConvertClientGetUserDataResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FClientGetUserReadOnlyDataAsyncTask::FClientGetUserReadOnlyDataAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFPlayerDataManagementGetUserDataRequest InRequest,
	const FOnClientGetUserReadOnlyDataCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientGetUserReadOnlyDataAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientGetUserReadOnlyDataAsyncTask::DoWork()
{
	const PFPlayerDataManagementGetUserDataRequest RequestType = {
		.ifChangedFromDataVersion = Request.ifChangedFromDataVersion ? new uint32(*Request.ifChangedFromDataVersion) : nullptr,
		.keys = ConvertFStringArrayToPlayfab(Request.keys),
		.keysCount = (uint32_t)Request.keys.Num(),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId)
	};
	HResult = PFPlayerDataManagementClientGetUserReadOnlyDataAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFPlayerDataManagementClientGetUserDataResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientGetUserReadOnlyDataAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFPlayerDataManagementClientGetUserReadOnlyDataGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFPlayerDataManagementClientGetUserDataResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFPlayerDataManagementClientGetUserDataResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFPlayerDataManagementClientGetUserReadOnlyDataGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFPlayerDataManagementClientGetUserDataResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFPlayerDataManagementClientGetUserDataResult> ResultType = ConvertClientGetUserDataResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FClientListPlayerCustomPropertiesAsyncTask::FClientListPlayerCustomPropertiesAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	const FOnClientListPlayerCustomPropertiesCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientListPlayerCustomPropertiesAsyncTask")),
	EntityHandle(EntityHandle),
	Delegate(InDelegate)
{
};

void FClientListPlayerCustomPropertiesAsyncTask::DoWork()
{
	
	HResult = PFPlayerDataManagementClientListPlayerCustomPropertiesAsync(EntityHandle.Get(), *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFPlayerDataManagementClientListPlayerCustomPropertiesResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientListPlayerCustomPropertiesAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFPlayerDataManagementClientListPlayerCustomPropertiesGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFPlayerDataManagementClientListPlayerCustomPropertiesResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFPlayerDataManagementClientListPlayerCustomPropertiesResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFPlayerDataManagementClientListPlayerCustomPropertiesGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFPlayerDataManagementClientListPlayerCustomPropertiesResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFPlayerDataManagementClientListPlayerCustomPropertiesResult> ResultType = ConvertClientListPlayerCustomPropertiesResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FClientUpdatePlayerCustomPropertiesAsyncTask::FClientUpdatePlayerCustomPropertiesAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFPlayerDataManagementClientUpdatePlayerCustomPropertiesRequest InRequest,
	const FOnClientUpdatePlayerCustomPropertiesCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientUpdatePlayerCustomPropertiesAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientUpdatePlayerCustomPropertiesAsyncTask::DoWork()
{
	const PFPlayerDataManagementClientUpdatePlayerCustomPropertiesRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.expectedPropertiesVersion = Request.expectedPropertiesVersion ? new int32(*Request.expectedPropertiesVersion) : nullptr,
		.properties = ConvertUnrealArrayToPlayfab<PFPlayerDataManagementUpdateProperty, FPFPlayerDataManagementUpdateProperty>(Request.properties, ConvertUpdatePropertyToPlayfab),
		.propertiesCount = (uint32_t)Request.properties.Num()
	};
	HResult = PFPlayerDataManagementClientUpdatePlayerCustomPropertiesAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFPlayerDataManagementClientUpdatePlayerCustomPropertiesResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientUpdatePlayerCustomPropertiesAsyncTask::ProcessResults()
{
	PFPlayerDataManagementClientUpdatePlayerCustomPropertiesResult Result = {};
	HResult = PFPlayerDataManagementClientUpdatePlayerCustomPropertiesGetResult(*mAsyncBlock, &Result);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFPlayerDataManagementClientUpdatePlayerCustomPropertiesResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFPlayerDataManagementClientUpdatePlayerCustomPropertiesResult> ResultType = ConvertClientUpdatePlayerCustomPropertiesResultToUnreal(&Result);

	Delegate.Execute(*ResultType, true);
}

FClientUpdateUserDataAsyncTask::FClientUpdateUserDataAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFPlayerDataManagementClientUpdateUserDataRequest InRequest,
	const FOnClientUpdateUserDataCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientUpdateUserDataAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientUpdateUserDataAsyncTask::DoWork()
{
	const PFPlayerDataManagementClientUpdateUserDataRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.data = ConvertFStringMapToPlayfab(Request.data),
		.dataCount = (uint32_t)Request.data.Num(),
		.keysToRemove = ConvertFStringArrayToPlayfab(Request.keysToRemove),
		.keysToRemoveCount = (uint32_t)Request.keysToRemove.Num(),
		.permission = new PFUserDataPermission(ConvertUserDataPermissionToPlayfab(Request.permission))
	};
	HResult = PFPlayerDataManagementClientUpdateUserDataAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFPlayerDataManagementUpdateUserDataResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientUpdateUserDataAsyncTask::ProcessResults()
{
	PFPlayerDataManagementUpdateUserDataResult Result = {};
	HResult = PFPlayerDataManagementClientUpdateUserDataGetResult(*mAsyncBlock, &Result);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFPlayerDataManagementUpdateUserDataResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFPlayerDataManagementUpdateUserDataResult> ResultType = ConvertUpdateUserDataResultToUnreal(&Result);

	Delegate.Execute(*ResultType, true);
}

FClientUpdateUserPublisherDataAsyncTask::FClientUpdateUserPublisherDataAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFPlayerDataManagementClientUpdateUserDataRequest InRequest,
	const FOnClientUpdateUserPublisherDataCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientUpdateUserPublisherDataAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientUpdateUserPublisherDataAsyncTask::DoWork()
{
	const PFPlayerDataManagementClientUpdateUserDataRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.data = ConvertFStringMapToPlayfab(Request.data),
		.dataCount = (uint32_t)Request.data.Num(),
		.keysToRemove = ConvertFStringArrayToPlayfab(Request.keysToRemove),
		.keysToRemoveCount = (uint32_t)Request.keysToRemove.Num(),
		.permission = new PFUserDataPermission(ConvertUserDataPermissionToPlayfab(Request.permission))
	};
	HResult = PFPlayerDataManagementClientUpdateUserPublisherDataAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFPlayerDataManagementUpdateUserDataResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientUpdateUserPublisherDataAsyncTask::ProcessResults()
{
	PFPlayerDataManagementUpdateUserDataResult Result = {};
	HResult = PFPlayerDataManagementClientUpdateUserPublisherDataGetResult(*mAsyncBlock, &Result);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFPlayerDataManagementUpdateUserDataResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFPlayerDataManagementUpdateUserDataResult> ResultType = ConvertUpdateUserDataResultToUnreal(&Result);

	Delegate.Execute(*ResultType, true);
}

#if HC_PLATFORM == HC_PLATFORM_GDK
FServerDeletePlayerCustomPropertiesAsyncTask::FServerDeletePlayerCustomPropertiesAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFPlayerDataManagementServerDeletePlayerCustomPropertiesRequest InRequest,
	const FOnServerDeletePlayerCustomPropertiesCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerDeletePlayerCustomPropertiesAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerDeletePlayerCustomPropertiesAsyncTask::DoWork()
{
	const PFPlayerDataManagementServerDeletePlayerCustomPropertiesRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.expectedPropertiesVersion = Request.expectedPropertiesVersion ? new int32(*Request.expectedPropertiesVersion) : nullptr,
		.playFabId = ConvertFStringToCharPtr(Request.playFabId),
		.propertyNames = ConvertFStringArrayToPlayfab(Request.propertyNames),
		.propertyNamesCount = (uint32_t)Request.propertyNames.Num()
	};
	HResult = PFPlayerDataManagementServerDeletePlayerCustomPropertiesAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFPlayerDataManagementServerDeletePlayerCustomPropertiesResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerDeletePlayerCustomPropertiesAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFPlayerDataManagementServerDeletePlayerCustomPropertiesGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFPlayerDataManagementServerDeletePlayerCustomPropertiesResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFPlayerDataManagementServerDeletePlayerCustomPropertiesResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFPlayerDataManagementServerDeletePlayerCustomPropertiesGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFPlayerDataManagementServerDeletePlayerCustomPropertiesResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFPlayerDataManagementServerDeletePlayerCustomPropertiesResult> ResultType = ConvertServerDeletePlayerCustomPropertiesResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK
FServerGetPlayerCustomPropertyAsyncTask::FServerGetPlayerCustomPropertyAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFPlayerDataManagementServerGetPlayerCustomPropertyRequest InRequest,
	const FOnServerGetPlayerCustomPropertyCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerGetPlayerCustomPropertyAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerGetPlayerCustomPropertyAsyncTask::DoWork()
{
	const PFPlayerDataManagementServerGetPlayerCustomPropertyRequest RequestType = {
		.playFabId = ConvertFStringToCharPtr(Request.playFabId),
		.propertyName = ConvertFStringToCharPtr(Request.propertyName)
	};
	HResult = PFPlayerDataManagementServerGetPlayerCustomPropertyAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFPlayerDataManagementServerGetPlayerCustomPropertyResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerGetPlayerCustomPropertyAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFPlayerDataManagementServerGetPlayerCustomPropertyGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFPlayerDataManagementServerGetPlayerCustomPropertyResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFPlayerDataManagementServerGetPlayerCustomPropertyResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFPlayerDataManagementServerGetPlayerCustomPropertyGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFPlayerDataManagementServerGetPlayerCustomPropertyResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFPlayerDataManagementServerGetPlayerCustomPropertyResult> ResultType = ConvertServerGetPlayerCustomPropertyResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerGetUserDataAsyncTask::FServerGetUserDataAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFPlayerDataManagementGetUserDataRequest InRequest,
	const FOnServerGetUserDataCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerGetUserDataAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerGetUserDataAsyncTask::DoWork()
{
	const PFPlayerDataManagementGetUserDataRequest RequestType = {
		.ifChangedFromDataVersion = Request.ifChangedFromDataVersion ? new uint32(*Request.ifChangedFromDataVersion) : nullptr,
		.keys = ConvertFStringArrayToPlayfab(Request.keys),
		.keysCount = (uint32_t)Request.keys.Num(),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId)
	};
	HResult = PFPlayerDataManagementServerGetUserDataAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFPlayerDataManagementServerGetUserDataResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerGetUserDataAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFPlayerDataManagementServerGetUserDataGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFPlayerDataManagementServerGetUserDataResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFPlayerDataManagementServerGetUserDataResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFPlayerDataManagementServerGetUserDataGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFPlayerDataManagementServerGetUserDataResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFPlayerDataManagementServerGetUserDataResult> ResultType = ConvertServerGetUserDataResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerGetUserInternalDataAsyncTask::FServerGetUserInternalDataAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFPlayerDataManagementGetUserDataRequest InRequest,
	const FOnServerGetUserInternalDataCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerGetUserInternalDataAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerGetUserInternalDataAsyncTask::DoWork()
{
	const PFPlayerDataManagementGetUserDataRequest RequestType = {
		.ifChangedFromDataVersion = Request.ifChangedFromDataVersion ? new uint32(*Request.ifChangedFromDataVersion) : nullptr,
		.keys = ConvertFStringArrayToPlayfab(Request.keys),
		.keysCount = (uint32_t)Request.keys.Num(),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId)
	};
	HResult = PFPlayerDataManagementServerGetUserInternalDataAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFPlayerDataManagementServerGetUserDataResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerGetUserInternalDataAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFPlayerDataManagementServerGetUserInternalDataGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFPlayerDataManagementServerGetUserDataResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFPlayerDataManagementServerGetUserDataResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFPlayerDataManagementServerGetUserInternalDataGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFPlayerDataManagementServerGetUserDataResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFPlayerDataManagementServerGetUserDataResult> ResultType = ConvertServerGetUserDataResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerGetUserPublisherDataAsyncTask::FServerGetUserPublisherDataAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFPlayerDataManagementGetUserDataRequest InRequest,
	const FOnServerGetUserPublisherDataCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerGetUserPublisherDataAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerGetUserPublisherDataAsyncTask::DoWork()
{
	const PFPlayerDataManagementGetUserDataRequest RequestType = {
		.ifChangedFromDataVersion = Request.ifChangedFromDataVersion ? new uint32(*Request.ifChangedFromDataVersion) : nullptr,
		.keys = ConvertFStringArrayToPlayfab(Request.keys),
		.keysCount = (uint32_t)Request.keys.Num(),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId)
	};
	HResult = PFPlayerDataManagementServerGetUserPublisherDataAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFPlayerDataManagementServerGetUserDataResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerGetUserPublisherDataAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFPlayerDataManagementServerGetUserPublisherDataGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFPlayerDataManagementServerGetUserDataResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFPlayerDataManagementServerGetUserDataResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFPlayerDataManagementServerGetUserPublisherDataGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFPlayerDataManagementServerGetUserDataResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFPlayerDataManagementServerGetUserDataResult> ResultType = ConvertServerGetUserDataResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerGetUserPublisherInternalDataAsyncTask::FServerGetUserPublisherInternalDataAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFPlayerDataManagementGetUserDataRequest InRequest,
	const FOnServerGetUserPublisherInternalDataCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerGetUserPublisherInternalDataAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerGetUserPublisherInternalDataAsyncTask::DoWork()
{
	const PFPlayerDataManagementGetUserDataRequest RequestType = {
		.ifChangedFromDataVersion = Request.ifChangedFromDataVersion ? new uint32(*Request.ifChangedFromDataVersion) : nullptr,
		.keys = ConvertFStringArrayToPlayfab(Request.keys),
		.keysCount = (uint32_t)Request.keys.Num(),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId)
	};
	HResult = PFPlayerDataManagementServerGetUserPublisherInternalDataAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFPlayerDataManagementServerGetUserDataResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerGetUserPublisherInternalDataAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFPlayerDataManagementServerGetUserPublisherInternalDataGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFPlayerDataManagementServerGetUserDataResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFPlayerDataManagementServerGetUserDataResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFPlayerDataManagementServerGetUserPublisherInternalDataGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFPlayerDataManagementServerGetUserDataResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFPlayerDataManagementServerGetUserDataResult> ResultType = ConvertServerGetUserDataResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerGetUserPublisherReadOnlyDataAsyncTask::FServerGetUserPublisherReadOnlyDataAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFPlayerDataManagementGetUserDataRequest InRequest,
	const FOnServerGetUserPublisherReadOnlyDataCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerGetUserPublisherReadOnlyDataAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerGetUserPublisherReadOnlyDataAsyncTask::DoWork()
{
	const PFPlayerDataManagementGetUserDataRequest RequestType = {
		.ifChangedFromDataVersion = Request.ifChangedFromDataVersion ? new uint32(*Request.ifChangedFromDataVersion) : nullptr,
		.keys = ConvertFStringArrayToPlayfab(Request.keys),
		.keysCount = (uint32_t)Request.keys.Num(),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId)
	};
	HResult = PFPlayerDataManagementServerGetUserPublisherReadOnlyDataAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFPlayerDataManagementServerGetUserDataResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerGetUserPublisherReadOnlyDataAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFPlayerDataManagementServerGetUserPublisherReadOnlyDataGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFPlayerDataManagementServerGetUserDataResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFPlayerDataManagementServerGetUserDataResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFPlayerDataManagementServerGetUserPublisherReadOnlyDataGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFPlayerDataManagementServerGetUserDataResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFPlayerDataManagementServerGetUserDataResult> ResultType = ConvertServerGetUserDataResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerGetUserReadOnlyDataAsyncTask::FServerGetUserReadOnlyDataAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFPlayerDataManagementGetUserDataRequest InRequest,
	const FOnServerGetUserReadOnlyDataCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerGetUserReadOnlyDataAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerGetUserReadOnlyDataAsyncTask::DoWork()
{
	const PFPlayerDataManagementGetUserDataRequest RequestType = {
		.ifChangedFromDataVersion = Request.ifChangedFromDataVersion ? new uint32(*Request.ifChangedFromDataVersion) : nullptr,
		.keys = ConvertFStringArrayToPlayfab(Request.keys),
		.keysCount = (uint32_t)Request.keys.Num(),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId)
	};
	HResult = PFPlayerDataManagementServerGetUserReadOnlyDataAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFPlayerDataManagementServerGetUserDataResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerGetUserReadOnlyDataAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFPlayerDataManagementServerGetUserReadOnlyDataGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFPlayerDataManagementServerGetUserDataResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFPlayerDataManagementServerGetUserDataResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFPlayerDataManagementServerGetUserReadOnlyDataGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFPlayerDataManagementServerGetUserDataResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFPlayerDataManagementServerGetUserDataResult> ResultType = ConvertServerGetUserDataResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK
FServerListPlayerCustomPropertiesAsyncTask::FServerListPlayerCustomPropertiesAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFPlayerDataManagementListPlayerCustomPropertiesRequest InRequest,
	const FOnServerListPlayerCustomPropertiesCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerListPlayerCustomPropertiesAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerListPlayerCustomPropertiesAsyncTask::DoWork()
{
	const PFPlayerDataManagementListPlayerCustomPropertiesRequest RequestType = {
		.playFabId = ConvertFStringToCharPtr(Request.playFabId)
	};
	HResult = PFPlayerDataManagementServerListPlayerCustomPropertiesAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFPlayerDataManagementServerListPlayerCustomPropertiesResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerListPlayerCustomPropertiesAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFPlayerDataManagementServerListPlayerCustomPropertiesGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFPlayerDataManagementServerListPlayerCustomPropertiesResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFPlayerDataManagementServerListPlayerCustomPropertiesResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFPlayerDataManagementServerListPlayerCustomPropertiesGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFPlayerDataManagementServerListPlayerCustomPropertiesResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFPlayerDataManagementServerListPlayerCustomPropertiesResult> ResultType = ConvertServerListPlayerCustomPropertiesResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK
FServerUpdatePlayerCustomPropertiesAsyncTask::FServerUpdatePlayerCustomPropertiesAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFPlayerDataManagementServerUpdatePlayerCustomPropertiesRequest InRequest,
	const FOnServerUpdatePlayerCustomPropertiesCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerUpdatePlayerCustomPropertiesAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerUpdatePlayerCustomPropertiesAsyncTask::DoWork()
{
	const PFPlayerDataManagementServerUpdatePlayerCustomPropertiesRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.expectedPropertiesVersion = Request.expectedPropertiesVersion ? new int32(*Request.expectedPropertiesVersion) : nullptr,
		.playFabId = ConvertFStringToCharPtr(Request.playFabId),
		.properties = ConvertUnrealArrayToPlayfab<PFPlayerDataManagementUpdateProperty, FPFPlayerDataManagementUpdateProperty>(Request.properties, ConvertUpdatePropertyToPlayfab),
		.propertiesCount = (uint32_t)Request.properties.Num()
	};
	HResult = PFPlayerDataManagementServerUpdatePlayerCustomPropertiesAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFPlayerDataManagementServerUpdatePlayerCustomPropertiesResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerUpdatePlayerCustomPropertiesAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFPlayerDataManagementServerUpdatePlayerCustomPropertiesGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFPlayerDataManagementServerUpdatePlayerCustomPropertiesResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFPlayerDataManagementServerUpdatePlayerCustomPropertiesResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFPlayerDataManagementServerUpdatePlayerCustomPropertiesGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFPlayerDataManagementServerUpdatePlayerCustomPropertiesResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFPlayerDataManagementServerUpdatePlayerCustomPropertiesResult> ResultType = ConvertServerUpdatePlayerCustomPropertiesResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerUpdateUserDataAsyncTask::FServerUpdateUserDataAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFPlayerDataManagementServerUpdateUserDataRequest InRequest,
	const FOnServerUpdateUserDataCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerUpdateUserDataAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerUpdateUserDataAsyncTask::DoWork()
{
	const PFPlayerDataManagementServerUpdateUserDataRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.data = ConvertFStringMapToPlayfab(Request.data),
		.dataCount = (uint32_t)Request.data.Num(),
		.keysToRemove = ConvertFStringArrayToPlayfab(Request.keysToRemove),
		.keysToRemoveCount = (uint32_t)Request.keysToRemove.Num(),
		.permission = new PFUserDataPermission(ConvertUserDataPermissionToPlayfab(Request.permission)),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId)
	};
	HResult = PFPlayerDataManagementServerUpdateUserDataAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFPlayerDataManagementUpdateUserDataResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerUpdateUserDataAsyncTask::ProcessResults()
{
	PFPlayerDataManagementUpdateUserDataResult Result = {};
	HResult = PFPlayerDataManagementServerUpdateUserDataGetResult(*mAsyncBlock, &Result);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFPlayerDataManagementUpdateUserDataResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFPlayerDataManagementUpdateUserDataResult> ResultType = ConvertUpdateUserDataResultToUnreal(&Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerUpdateUserInternalDataAsyncTask::FServerUpdateUserInternalDataAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFPlayerDataManagementUpdateUserInternalDataRequest InRequest,
	const FOnServerUpdateUserInternalDataCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerUpdateUserInternalDataAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerUpdateUserInternalDataAsyncTask::DoWork()
{
	const PFPlayerDataManagementUpdateUserInternalDataRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.data = ConvertFStringMapToPlayfab(Request.data),
		.dataCount = (uint32_t)Request.data.Num(),
		.keysToRemove = ConvertFStringArrayToPlayfab(Request.keysToRemove),
		.keysToRemoveCount = (uint32_t)Request.keysToRemove.Num(),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId)
	};
	HResult = PFPlayerDataManagementServerUpdateUserInternalDataAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFPlayerDataManagementUpdateUserDataResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerUpdateUserInternalDataAsyncTask::ProcessResults()
{
	PFPlayerDataManagementUpdateUserDataResult Result = {};
	HResult = PFPlayerDataManagementServerUpdateUserInternalDataGetResult(*mAsyncBlock, &Result);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFPlayerDataManagementUpdateUserDataResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFPlayerDataManagementUpdateUserDataResult> ResultType = ConvertUpdateUserDataResultToUnreal(&Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerUpdateUserPublisherDataAsyncTask::FServerUpdateUserPublisherDataAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFPlayerDataManagementServerUpdateUserDataRequest InRequest,
	const FOnServerUpdateUserPublisherDataCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerUpdateUserPublisherDataAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerUpdateUserPublisherDataAsyncTask::DoWork()
{
	const PFPlayerDataManagementServerUpdateUserDataRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.data = ConvertFStringMapToPlayfab(Request.data),
		.dataCount = (uint32_t)Request.data.Num(),
		.keysToRemove = ConvertFStringArrayToPlayfab(Request.keysToRemove),
		.keysToRemoveCount = (uint32_t)Request.keysToRemove.Num(),
		.permission = new PFUserDataPermission(ConvertUserDataPermissionToPlayfab(Request.permission)),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId)
	};
	HResult = PFPlayerDataManagementServerUpdateUserPublisherDataAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFPlayerDataManagementUpdateUserDataResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerUpdateUserPublisherDataAsyncTask::ProcessResults()
{
	PFPlayerDataManagementUpdateUserDataResult Result = {};
	HResult = PFPlayerDataManagementServerUpdateUserPublisherDataGetResult(*mAsyncBlock, &Result);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFPlayerDataManagementUpdateUserDataResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFPlayerDataManagementUpdateUserDataResult> ResultType = ConvertUpdateUserDataResultToUnreal(&Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerUpdateUserPublisherInternalDataAsyncTask::FServerUpdateUserPublisherInternalDataAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFPlayerDataManagementUpdateUserInternalDataRequest InRequest,
	const FOnServerUpdateUserPublisherInternalDataCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerUpdateUserPublisherInternalDataAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerUpdateUserPublisherInternalDataAsyncTask::DoWork()
{
	const PFPlayerDataManagementUpdateUserInternalDataRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.data = ConvertFStringMapToPlayfab(Request.data),
		.dataCount = (uint32_t)Request.data.Num(),
		.keysToRemove = ConvertFStringArrayToPlayfab(Request.keysToRemove),
		.keysToRemoveCount = (uint32_t)Request.keysToRemove.Num(),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId)
	};
	HResult = PFPlayerDataManagementServerUpdateUserPublisherInternalDataAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFPlayerDataManagementUpdateUserDataResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerUpdateUserPublisherInternalDataAsyncTask::ProcessResults()
{
	PFPlayerDataManagementUpdateUserDataResult Result = {};
	HResult = PFPlayerDataManagementServerUpdateUserPublisherInternalDataGetResult(*mAsyncBlock, &Result);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFPlayerDataManagementUpdateUserDataResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFPlayerDataManagementUpdateUserDataResult> ResultType = ConvertUpdateUserDataResultToUnreal(&Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerUpdateUserPublisherReadOnlyDataAsyncTask::FServerUpdateUserPublisherReadOnlyDataAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFPlayerDataManagementServerUpdateUserDataRequest InRequest,
	const FOnServerUpdateUserPublisherReadOnlyDataCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerUpdateUserPublisherReadOnlyDataAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerUpdateUserPublisherReadOnlyDataAsyncTask::DoWork()
{
	const PFPlayerDataManagementServerUpdateUserDataRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.data = ConvertFStringMapToPlayfab(Request.data),
		.dataCount = (uint32_t)Request.data.Num(),
		.keysToRemove = ConvertFStringArrayToPlayfab(Request.keysToRemove),
		.keysToRemoveCount = (uint32_t)Request.keysToRemove.Num(),
		.permission = new PFUserDataPermission(ConvertUserDataPermissionToPlayfab(Request.permission)),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId)
	};
	HResult = PFPlayerDataManagementServerUpdateUserPublisherReadOnlyDataAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFPlayerDataManagementUpdateUserDataResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerUpdateUserPublisherReadOnlyDataAsyncTask::ProcessResults()
{
	PFPlayerDataManagementUpdateUserDataResult Result = {};
	HResult = PFPlayerDataManagementServerUpdateUserPublisherReadOnlyDataGetResult(*mAsyncBlock, &Result);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFPlayerDataManagementUpdateUserDataResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFPlayerDataManagementUpdateUserDataResult> ResultType = ConvertUpdateUserDataResultToUnreal(&Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerUpdateUserReadOnlyDataAsyncTask::FServerUpdateUserReadOnlyDataAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFPlayerDataManagementServerUpdateUserDataRequest InRequest,
	const FOnServerUpdateUserReadOnlyDataCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerUpdateUserReadOnlyDataAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerUpdateUserReadOnlyDataAsyncTask::DoWork()
{
	const PFPlayerDataManagementServerUpdateUserDataRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.data = ConvertFStringMapToPlayfab(Request.data),
		.dataCount = (uint32_t)Request.data.Num(),
		.keysToRemove = ConvertFStringArrayToPlayfab(Request.keysToRemove),
		.keysToRemoveCount = (uint32_t)Request.keysToRemove.Num(),
		.permission = new PFUserDataPermission(ConvertUserDataPermissionToPlayfab(Request.permission)),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId)
	};
	HResult = PFPlayerDataManagementServerUpdateUserReadOnlyDataAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFPlayerDataManagementUpdateUserDataResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerUpdateUserReadOnlyDataAsyncTask::ProcessResults()
{
	PFPlayerDataManagementUpdateUserDataResult Result = {};
	HResult = PFPlayerDataManagementServerUpdateUserReadOnlyDataGetResult(*mAsyncBlock, &Result);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFPlayerDataManagementUpdateUserDataResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFPlayerDataManagementUpdateUserDataResult> ResultType = ConvertUpdateUserDataResultToUnreal(&Result);

	Delegate.Execute(*ResultType, true);
}
#endif

