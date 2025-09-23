// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFStatisticsAsyncTasks.h"

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FCreateStatisticDefinitionAsyncTask::FCreateStatisticDefinitionAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFStatisticsCreateStatisticDefinitionRequest InRequest,
	const FOnCreateStatisticDefinitionCompleted& InDelegate)
	: FXAsyncTask(TEXT("FCreateStatisticDefinitionAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FCreateStatisticDefinitionAsyncTask::DoWork()
{
	const PFStatisticsCreateStatisticDefinitionRequest RequestType = {
		.aggregationSources = ConvertFStringArrayToPlayfab(Request.aggregationSources),
		.aggregationSourcesCount = (uint32_t)Request.aggregationSources.Num(),
		.columns = ConvertUnrealArrayToPlayfab(Request.columns, ConvertStatisticColumnToPlayfab),
		.columnsCount = (uint32_t)Request.columns.Num(),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entityType = ConvertFStringToCharPtr(Request.entityType),
		.eventEmissionConfig = ConvertStatisticsEventEmissionConfigToPlayfab(Request.eventEmissionConfig),
		.name = ConvertFStringToCharPtr(Request.name),
		.versionConfiguration = ConvertVersionConfigurationToPlayfab(Request.versionConfiguration)
	};
	HResult = PFStatisticsCreateStatisticDefinitionAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FCreateStatisticDefinitionAsyncTask::ProcessResults()
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
FDeleteStatisticDefinitionAsyncTask::FDeleteStatisticDefinitionAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFStatisticsDeleteStatisticDefinitionRequest InRequest,
	const FOnDeleteStatisticDefinitionCompleted& InDelegate)
	: FXAsyncTask(TEXT("FDeleteStatisticDefinitionAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FDeleteStatisticDefinitionAsyncTask::DoWork()
{
	const PFStatisticsDeleteStatisticDefinitionRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.name = ConvertFStringToCharPtr(Request.name)
	};
	HResult = PFStatisticsDeleteStatisticDefinitionAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FDeleteStatisticDefinitionAsyncTask::ProcessResults()
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

FDeleteStatisticsAsyncTask::FDeleteStatisticsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFStatisticsDeleteStatisticsRequest InRequest,
	const FOnDeleteStatisticsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FDeleteStatisticsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FDeleteStatisticsAsyncTask::DoWork()
{
	const PFStatisticsDeleteStatisticsRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.statistics = ConvertUnrealArrayToPlayfab(Request.statistics, ConvertStatisticDeleteToPlayfab),
		.statisticsCount = (uint32_t)Request.statistics.Num()
	};
	HResult = PFStatisticsDeleteStatisticsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFStatisticsDeleteStatisticsResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FDeleteStatisticsAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFStatisticsDeleteStatisticsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFStatisticsDeleteStatisticsResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFStatisticsDeleteStatisticsResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFStatisticsDeleteStatisticsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFStatisticsDeleteStatisticsResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFStatisticsDeleteStatisticsResponse> ResultType = ConvertDeleteStatisticsResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FGetStatisticDefinitionAsyncTask::FGetStatisticDefinitionAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFStatisticsGetStatisticDefinitionRequest InRequest,
	const FOnGetStatisticDefinitionCompleted& InDelegate)
	: FXAsyncTask(TEXT("FGetStatisticDefinitionAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FGetStatisticDefinitionAsyncTask::DoWork()
{
	const PFStatisticsGetStatisticDefinitionRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.name = ConvertFStringToCharPtr(Request.name)
	};
	HResult = PFStatisticsGetStatisticDefinitionAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFStatisticsGetStatisticDefinitionResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FGetStatisticDefinitionAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFStatisticsGetStatisticDefinitionGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFStatisticsGetStatisticDefinitionResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFStatisticsGetStatisticDefinitionResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFStatisticsGetStatisticDefinitionGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFStatisticsGetStatisticDefinitionResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFStatisticsGetStatisticDefinitionResponse> ResultType = ConvertGetStatisticDefinitionResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

FGetStatisticsAsyncTask::FGetStatisticsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFStatisticsGetStatisticsRequest InRequest,
	const FOnGetStatisticsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FGetStatisticsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FGetStatisticsAsyncTask::DoWork()
{
	const PFStatisticsGetStatisticsRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.statisticNames = ConvertFStringArrayToPlayfab(Request.statisticNames),
		.statisticNamesCount = (uint32_t)Request.statisticNames.Num()
	};
	HResult = PFStatisticsGetStatisticsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFStatisticsGetStatisticsResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FGetStatisticsAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFStatisticsGetStatisticsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFStatisticsGetStatisticsResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFStatisticsGetStatisticsResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFStatisticsGetStatisticsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFStatisticsGetStatisticsResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFStatisticsGetStatisticsResponse> ResultType = ConvertGetStatisticsResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FGetStatisticsForEntitiesAsyncTask::FGetStatisticsForEntitiesAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFStatisticsGetStatisticsForEntitiesRequest InRequest,
	const FOnGetStatisticsForEntitiesCompleted& InDelegate)
	: FXAsyncTask(TEXT("FGetStatisticsForEntitiesAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FGetStatisticsForEntitiesAsyncTask::DoWork()
{
	const PFStatisticsGetStatisticsForEntitiesRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entities = ConvertUnrealArrayToPlayfab(Request.entities, ConvertEntityKeyToPlayfab),
		.entitiesCount = (uint32_t)Request.entities.Num(),
		.statisticNames = ConvertFStringArrayToPlayfab(Request.statisticNames),
		.statisticNamesCount = (uint32_t)Request.statisticNames.Num()
	};
	HResult = PFStatisticsGetStatisticsForEntitiesAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFStatisticsGetStatisticsForEntitiesResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FGetStatisticsForEntitiesAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFStatisticsGetStatisticsForEntitiesGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFStatisticsGetStatisticsForEntitiesResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFStatisticsGetStatisticsForEntitiesResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFStatisticsGetStatisticsForEntitiesGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFStatisticsGetStatisticsForEntitiesResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFStatisticsGetStatisticsForEntitiesResponse> ResultType = ConvertGetStatisticsForEntitiesResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FIncrementStatisticVersionAsyncTask::FIncrementStatisticVersionAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFStatisticsIncrementStatisticVersionRequest InRequest,
	const FOnIncrementStatisticVersionCompleted& InDelegate)
	: FXAsyncTask(TEXT("FIncrementStatisticVersionAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FIncrementStatisticVersionAsyncTask::DoWork()
{
	const PFStatisticsIncrementStatisticVersionRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.name = ConvertFStringToCharPtr(Request.name)
	};
	HResult = PFStatisticsIncrementStatisticVersionAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFStatisticsIncrementStatisticVersionResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FIncrementStatisticVersionAsyncTask::ProcessResults()
{
	PFStatisticsIncrementStatisticVersionResponse Result = {};
	HResult = PFStatisticsIncrementStatisticVersionGetResult(*mAsyncBlock, &Result);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFStatisticsIncrementStatisticVersionResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFStatisticsIncrementStatisticVersionResponse> ResultType = ConvertIncrementStatisticVersionResponseToUnreal(&Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FListStatisticDefinitionsAsyncTask::FListStatisticDefinitionsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFStatisticsListStatisticDefinitionsRequest InRequest,
	const FOnListStatisticDefinitionsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FListStatisticDefinitionsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FListStatisticDefinitionsAsyncTask::DoWork()
{
	const PFStatisticsListStatisticDefinitionsRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num()
	};
	HResult = PFStatisticsListStatisticDefinitionsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFStatisticsListStatisticDefinitionsResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FListStatisticDefinitionsAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFStatisticsListStatisticDefinitionsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFStatisticsListStatisticDefinitionsResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFStatisticsListStatisticDefinitionsResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFStatisticsListStatisticDefinitionsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFStatisticsListStatisticDefinitionsResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFStatisticsListStatisticDefinitionsResponse> ResultType = ConvertListStatisticDefinitionsResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK
FUpdateStatisticDefinitionAsyncTask::FUpdateStatisticDefinitionAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFStatisticsUpdateStatisticDefinitionRequest InRequest,
	const FOnUpdateStatisticDefinitionCompleted& InDelegate)
	: FXAsyncTask(TEXT("FUpdateStatisticDefinitionAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FUpdateStatisticDefinitionAsyncTask::DoWork()
{
	const PFStatisticsUpdateStatisticDefinitionRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.eventEmissionConfig = ConvertStatisticsEventEmissionConfigToPlayfab(Request.eventEmissionConfig),
		.name = ConvertFStringToCharPtr(Request.name),
		.versionConfiguration = ConvertVersionConfigurationToPlayfab(Request.versionConfiguration)
	};
	HResult = PFStatisticsUpdateStatisticDefinitionAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FUpdateStatisticDefinitionAsyncTask::ProcessResults()
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

FUpdateStatisticsAsyncTask::FUpdateStatisticsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFStatisticsUpdateStatisticsRequest InRequest,
	const FOnUpdateStatisticsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FUpdateStatisticsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FUpdateStatisticsAsyncTask::DoWork()
{
	const PFStatisticsUpdateStatisticsRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.statistics = ConvertUnrealArrayToPlayfab(Request.statistics, ConvertStatisticUpdateToPlayfab),
		.statisticsCount = (uint32_t)Request.statistics.Num(),
		.transactionId = ConvertFStringToCharPtr(Request.transactionId)
	};
	HResult = PFStatisticsUpdateStatisticsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFStatisticsUpdateStatisticsResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FUpdateStatisticsAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFStatisticsUpdateStatisticsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFStatisticsUpdateStatisticsResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFStatisticsUpdateStatisticsResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFStatisticsUpdateStatisticsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFStatisticsUpdateStatisticsResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFStatisticsUpdateStatisticsResponse> ResultType = ConvertUpdateStatisticsResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

