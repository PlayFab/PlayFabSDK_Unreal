// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFLeaderboardsAsyncTasks.h"

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FCreateLeaderboardDefinitionAsyncTask::FCreateLeaderboardDefinitionAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFLeaderboardsCreateLeaderboardDefinitionRequest InRequest,
	const FOnCreateLeaderboardDefinitionCompleted& InDelegate)
	: FXAsyncTask(TEXT("FCreateLeaderboardDefinitionAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FCreateLeaderboardDefinitionAsyncTask::DoWork()
{
	const PFLeaderboardsCreateLeaderboardDefinitionRequest RequestType = {
		.columns = ConvertUnrealArrayToPlayfab<PFLeaderboardsLeaderboardColumn, FPFLeaderboardsLeaderboardColumn>(Request.columns, ConvertLeaderboardColumnToPlayfab),
		.columnsCount = (uint32_t)Request.columns.Num(),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entityType = ConvertFStringToCharPtr(Request.entityType),
		.eventEmissionConfig = ConvertLeaderboardEventEmissionConfigToPlayfab(Request.eventEmissionConfig),
		.name = ConvertFStringToCharPtr(Request.name),
		.sizeLimit = Request.sizeLimit,
		.versionConfiguration = ConvertVersionConfigurationToPlayfab(Request.versionConfiguration)
	};
	HResult = PFLeaderboardsCreateLeaderboardDefinitionAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(ErrorMessage, false);
	}
};

void FCreateLeaderboardDefinitionAsyncTask::ProcessResults()
{
	if (HResult != S_OK)
	{
		Delegate.Execute(FString::Printf(TEXT("Async failure: 0x%08X"), static_cast<uint32>(HResult)), false);
	}
	else
	{
		Delegate.Execute(FString(), true);
	}
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FDeleteLeaderboardDefinitionAsyncTask::FDeleteLeaderboardDefinitionAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFLeaderboardsDeleteLeaderboardDefinitionRequest InRequest,
	const FOnDeleteLeaderboardDefinitionCompleted& InDelegate)
	: FXAsyncTask(TEXT("FDeleteLeaderboardDefinitionAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FDeleteLeaderboardDefinitionAsyncTask::DoWork()
{
	const PFLeaderboardsDeleteLeaderboardDefinitionRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.name = ConvertFStringToCharPtr(Request.name)
	};
	HResult = PFLeaderboardsDeleteLeaderboardDefinitionAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(ErrorMessage, false);
	}
};

void FDeleteLeaderboardDefinitionAsyncTask::ProcessResults()
{
	if (HResult != S_OK)
	{
		Delegate.Execute(FString::Printf(TEXT("Async failure: 0x%08X"), static_cast<uint32>(HResult)), false);
	}
	else
	{
		Delegate.Execute(FString(), true);
	}
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FDeleteLeaderboardEntriesAsyncTask::FDeleteLeaderboardEntriesAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFLeaderboardsDeleteLeaderboardEntriesRequest InRequest,
	const FOnDeleteLeaderboardEntriesCompleted& InDelegate)
	: FXAsyncTask(TEXT("FDeleteLeaderboardEntriesAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FDeleteLeaderboardEntriesAsyncTask::DoWork()
{
	const PFLeaderboardsDeleteLeaderboardEntriesRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entityIds = ConvertFStringArrayToPlayfab(Request.entityIds),
		.entityIdsCount = (uint32_t)Request.entityIds.Num(),
		.name = ConvertFStringToCharPtr(Request.name)
	};
	HResult = PFLeaderboardsDeleteLeaderboardEntriesAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(ErrorMessage, false);
	}
};

void FDeleteLeaderboardEntriesAsyncTask::ProcessResults()
{
	if (HResult != S_OK)
	{
		Delegate.Execute(FString::Printf(TEXT("Async failure: 0x%08X"), static_cast<uint32>(HResult)), false);
	}
	else
	{
		Delegate.Execute(FString(), true);
	}
}
#endif

FGetFriendLeaderboardForEntityAsyncTask::FGetFriendLeaderboardForEntityAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFLeaderboardsGetFriendLeaderboardForEntityRequest InRequest,
	const FOnGetFriendLeaderboardForEntityCompleted& InDelegate)
	: FXAsyncTask(TEXT("FGetFriendLeaderboardForEntityAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FGetFriendLeaderboardForEntityAsyncTask::DoWork()
{
	const PFLeaderboardsGetFriendLeaderboardForEntityRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.externalFriendSources = new PFExternalFriendSources(ConvertExternalFriendSourcesToPlayfab(Request.externalFriendSources)),
		.leaderboardName = ConvertFStringToCharPtr(Request.leaderboardName),
		.version = Request.version ? new uint32(*Request.version) : nullptr,
		.xboxToken = ConvertFStringToCharPtr(Request.xboxToken)
	};
	HResult = PFLeaderboardsGetFriendLeaderboardForEntityAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFLeaderboardsGetEntityLeaderboardResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FGetFriendLeaderboardForEntityAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFLeaderboardsGetFriendLeaderboardForEntityGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFLeaderboardsGetEntityLeaderboardResponse{ .ErrorMessage = FString::Printf(TEXT("GetResultSize failure: 0x%08X"), static_cast<uint32>(HResult)) }, false);
		return;
	}

	PFLeaderboardsGetEntityLeaderboardResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFLeaderboardsGetFriendLeaderboardForEntityGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("GetResult failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFLeaderboardsGetEntityLeaderboardResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFLeaderboardsGetEntityLeaderboardResponse> ResultType = ConvertGetEntityLeaderboardResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FGetLeaderboardAsyncTask::FGetLeaderboardAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFLeaderboardsGetEntityLeaderboardRequest InRequest,
	const FOnGetLeaderboardCompleted& InDelegate)
	: FXAsyncTask(TEXT("FGetLeaderboardAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FGetLeaderboardAsyncTask::DoWork()
{
	const PFLeaderboardsGetEntityLeaderboardRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.leaderboardName = ConvertFStringToCharPtr(Request.leaderboardName),
		.pageSize = Request.pageSize,
		.startingPosition = Request.startingPosition ? new uint32(*Request.startingPosition) : nullptr,
		.version = Request.version ? new uint32(*Request.version) : nullptr
	};
	HResult = PFLeaderboardsGetLeaderboardAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFLeaderboardsGetEntityLeaderboardResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FGetLeaderboardAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFLeaderboardsGetLeaderboardGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFLeaderboardsGetEntityLeaderboardResponse{ .ErrorMessage = FString::Printf(TEXT("GetResultSize failure: 0x%08X"), static_cast<uint32>(HResult)) }, false);
		return;
	}

	PFLeaderboardsGetEntityLeaderboardResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFLeaderboardsGetLeaderboardGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("GetResult failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFLeaderboardsGetEntityLeaderboardResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFLeaderboardsGetEntityLeaderboardResponse> ResultType = ConvertGetEntityLeaderboardResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FGetLeaderboardAroundEntityAsyncTask::FGetLeaderboardAroundEntityAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFLeaderboardsGetLeaderboardAroundEntityRequest InRequest,
	const FOnGetLeaderboardAroundEntityCompleted& InDelegate)
	: FXAsyncTask(TEXT("FGetLeaderboardAroundEntityAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FGetLeaderboardAroundEntityAsyncTask::DoWork()
{
	const PFLeaderboardsGetLeaderboardAroundEntityRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.leaderboardName = ConvertFStringToCharPtr(Request.leaderboardName),
		.maxSurroundingEntries = Request.maxSurroundingEntries,
		.version = Request.version ? new uint32(*Request.version) : nullptr
	};
	HResult = PFLeaderboardsGetLeaderboardAroundEntityAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFLeaderboardsGetEntityLeaderboardResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FGetLeaderboardAroundEntityAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFLeaderboardsGetLeaderboardAroundEntityGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFLeaderboardsGetEntityLeaderboardResponse{ .ErrorMessage = FString::Printf(TEXT("GetResultSize failure: 0x%08X"), static_cast<uint32>(HResult)) }, false);
		return;
	}

	PFLeaderboardsGetEntityLeaderboardResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFLeaderboardsGetLeaderboardAroundEntityGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("GetResult failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFLeaderboardsGetEntityLeaderboardResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFLeaderboardsGetEntityLeaderboardResponse> ResultType = ConvertGetEntityLeaderboardResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FGetLeaderboardDefinitionAsyncTask::FGetLeaderboardDefinitionAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFLeaderboardsGetLeaderboardDefinitionRequest InRequest,
	const FOnGetLeaderboardDefinitionCompleted& InDelegate)
	: FXAsyncTask(TEXT("FGetLeaderboardDefinitionAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FGetLeaderboardDefinitionAsyncTask::DoWork()
{
	const PFLeaderboardsGetLeaderboardDefinitionRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.name = ConvertFStringToCharPtr(Request.name)
	};
	HResult = PFLeaderboardsGetLeaderboardDefinitionAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFLeaderboardsGetLeaderboardDefinitionResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FGetLeaderboardDefinitionAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFLeaderboardsGetLeaderboardDefinitionGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFLeaderboardsGetLeaderboardDefinitionResponse{ .ErrorMessage = FString::Printf(TEXT("GetResultSize failure: 0x%08X"), static_cast<uint32>(HResult)) }, false);
		return;
	}

	PFLeaderboardsGetLeaderboardDefinitionResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFLeaderboardsGetLeaderboardDefinitionGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("GetResult failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFLeaderboardsGetLeaderboardDefinitionResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFLeaderboardsGetLeaderboardDefinitionResponse> ResultType = ConvertGetLeaderboardDefinitionResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FGetLeaderboardForEntitiesAsyncTask::FGetLeaderboardForEntitiesAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFLeaderboardsGetLeaderboardForEntitiesRequest InRequest,
	const FOnGetLeaderboardForEntitiesCompleted& InDelegate)
	: FXAsyncTask(TEXT("FGetLeaderboardForEntitiesAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FGetLeaderboardForEntitiesAsyncTask::DoWork()
{
	const PFLeaderboardsGetLeaderboardForEntitiesRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entityIds = ConvertFStringArrayToPlayfab(Request.entityIds),
		.entityIdsCount = (uint32_t)Request.entityIds.Num(),
		.leaderboardName = ConvertFStringToCharPtr(Request.leaderboardName),
		.version = Request.version ? new uint32(*Request.version) : nullptr
	};
	HResult = PFLeaderboardsGetLeaderboardForEntitiesAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFLeaderboardsGetEntityLeaderboardResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FGetLeaderboardForEntitiesAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFLeaderboardsGetLeaderboardForEntitiesGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFLeaderboardsGetEntityLeaderboardResponse{ .ErrorMessage = FString::Printf(TEXT("GetResultSize failure: 0x%08X"), static_cast<uint32>(HResult)) }, false);
		return;
	}

	PFLeaderboardsGetEntityLeaderboardResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFLeaderboardsGetLeaderboardForEntitiesGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("GetResult failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFLeaderboardsGetEntityLeaderboardResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFLeaderboardsGetEntityLeaderboardResponse> ResultType = ConvertGetEntityLeaderboardResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FIncrementLeaderboardVersionAsyncTask::FIncrementLeaderboardVersionAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFLeaderboardsIncrementLeaderboardVersionRequest InRequest,
	const FOnIncrementLeaderboardVersionCompleted& InDelegate)
	: FXAsyncTask(TEXT("FIncrementLeaderboardVersionAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FIncrementLeaderboardVersionAsyncTask::DoWork()
{
	const PFLeaderboardsIncrementLeaderboardVersionRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.name = ConvertFStringToCharPtr(Request.name)
	};
	HResult = PFLeaderboardsIncrementLeaderboardVersionAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFLeaderboardsIncrementLeaderboardVersionResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FIncrementLeaderboardVersionAsyncTask::ProcessResults()
{
	PFLeaderboardsIncrementLeaderboardVersionResponse Result = {};
	HResult = PFLeaderboardsIncrementLeaderboardVersionGetResult(*mAsyncBlock, &Result);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("GetResult failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFLeaderboardsIncrementLeaderboardVersionResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFLeaderboardsIncrementLeaderboardVersionResponse> ResultType = ConvertIncrementLeaderboardVersionResponseToUnreal(&Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FListLeaderboardDefinitionsAsyncTask::FListLeaderboardDefinitionsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFLeaderboardsListLeaderboardDefinitionsRequest InRequest,
	const FOnListLeaderboardDefinitionsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FListLeaderboardDefinitionsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FListLeaderboardDefinitionsAsyncTask::DoWork()
{
	const PFLeaderboardsListLeaderboardDefinitionsRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.pageSize = Request.pageSize ? new int32(*Request.pageSize) : nullptr,
		.skipToken = ConvertFStringToCharPtr(Request.skipToken)
	};
	HResult = PFLeaderboardsListLeaderboardDefinitionsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFLeaderboardsListLeaderboardDefinitionsResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FListLeaderboardDefinitionsAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFLeaderboardsListLeaderboardDefinitionsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFLeaderboardsListLeaderboardDefinitionsResponse{ .ErrorMessage = FString::Printf(TEXT("GetResultSize failure: 0x%08X"), static_cast<uint32>(HResult)) }, false);
		return;
	}

	PFLeaderboardsListLeaderboardDefinitionsResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFLeaderboardsListLeaderboardDefinitionsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("GetResult failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFLeaderboardsListLeaderboardDefinitionsResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFLeaderboardsListLeaderboardDefinitionsResponse> ResultType = ConvertListLeaderboardDefinitionsResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FUnlinkLeaderboardFromStatisticAsyncTask::FUnlinkLeaderboardFromStatisticAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFLeaderboardsUnlinkLeaderboardFromStatisticRequest InRequest,
	const FOnUnlinkLeaderboardFromStatisticCompleted& InDelegate)
	: FXAsyncTask(TEXT("FUnlinkLeaderboardFromStatisticAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FUnlinkLeaderboardFromStatisticAsyncTask::DoWork()
{
	const PFLeaderboardsUnlinkLeaderboardFromStatisticRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.name = ConvertFStringToCharPtr(Request.name),
		.statisticName = ConvertFStringToCharPtr(Request.statisticName)
	};
	HResult = PFLeaderboardsUnlinkLeaderboardFromStatisticAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(ErrorMessage, false);
	}
};

void FUnlinkLeaderboardFromStatisticAsyncTask::ProcessResults()
{
	if (HResult != S_OK)
	{
		Delegate.Execute(FString::Printf(TEXT("Async failure: 0x%08X"), static_cast<uint32>(HResult)), false);
	}
	else
	{
		Delegate.Execute(FString(), true);
	}
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK
FUpdateLeaderboardDefinitionAsyncTask::FUpdateLeaderboardDefinitionAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFLeaderboardsUpdateLeaderboardDefinitionRequest InRequest,
	const FOnUpdateLeaderboardDefinitionCompleted& InDelegate)
	: FXAsyncTask(TEXT("FUpdateLeaderboardDefinitionAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FUpdateLeaderboardDefinitionAsyncTask::DoWork()
{
	const PFLeaderboardsUpdateLeaderboardDefinitionRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.eventEmissionConfig = ConvertLeaderboardEventEmissionConfigToPlayfab(Request.eventEmissionConfig),
		.name = ConvertFStringToCharPtr(Request.name),
		.sizeLimit = Request.sizeLimit ? new int32(*Request.sizeLimit) : nullptr,
		.versionConfiguration = ConvertVersionConfigurationToPlayfab(Request.versionConfiguration)
	};
	HResult = PFLeaderboardsUpdateLeaderboardDefinitionAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(ErrorMessage, false);
	}
};

void FUpdateLeaderboardDefinitionAsyncTask::ProcessResults()
{
	if (HResult != S_OK)
	{
		Delegate.Execute(FString::Printf(TEXT("Async failure: 0x%08X"), static_cast<uint32>(HResult)), false);
	}
	else
	{
		Delegate.Execute(FString(), true);
	}
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FUpdateLeaderboardEntriesAsyncTask::FUpdateLeaderboardEntriesAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFLeaderboardsUpdateLeaderboardEntriesRequest InRequest,
	const FOnUpdateLeaderboardEntriesCompleted& InDelegate)
	: FXAsyncTask(TEXT("FUpdateLeaderboardEntriesAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FUpdateLeaderboardEntriesAsyncTask::DoWork()
{
	const PFLeaderboardsUpdateLeaderboardEntriesRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entries = ConvertUnrealArrayToPlayfab<PFLeaderboardsLeaderboardEntryUpdate, FPFLeaderboardsLeaderboardEntryUpdate>(Request.entries, ConvertLeaderboardEntryUpdateToPlayfab),
		.entriesCount = (uint32_t)Request.entries.Num(),
		.leaderboardName = ConvertFStringToCharPtr(Request.leaderboardName)
	};
	HResult = PFLeaderboardsUpdateLeaderboardEntriesAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(ErrorMessage, false);
	}
};

void FUpdateLeaderboardEntriesAsyncTask::ProcessResults()
{
	if (HResult != S_OK)
	{
		Delegate.Execute(FString::Printf(TEXT("Async failure: 0x%08X"), static_cast<uint32>(HResult)), false);
	}
	else
	{
		Delegate.Execute(FString(), true);
	}
}
#endif

