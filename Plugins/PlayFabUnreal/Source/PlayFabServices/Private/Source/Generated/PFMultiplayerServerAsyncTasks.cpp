// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFMultiplayerServerAsyncTasks.h"

#if 0
FDeleteSecretAsyncTask::FDeleteSecretAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFMultiplayerServerDeleteSecretRequest InRequest,
	const FOnDeleteSecretCompleted& InDelegate)
	: FXAsyncTask(TEXT("FDeleteSecretAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FDeleteSecretAsyncTask::DoWork()
{
	const PFMultiplayerServerDeleteSecretRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.name = ConvertFStringToCharPtr(Request.name)
	};
	HResult = PFMultiplayerServerDeleteSecretAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FDeleteSecretAsyncTask::ProcessResults()
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

FListBuildAliasesAsyncTask::FListBuildAliasesAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFMultiplayerServerListBuildAliasesRequest InRequest,
	const FOnListBuildAliasesCompleted& InDelegate)
	: FXAsyncTask(TEXT("FListBuildAliasesAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FListBuildAliasesAsyncTask::DoWork()
{
	const PFMultiplayerServerListBuildAliasesRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.pageSize = Request.pageSize ? new int32(*Request.pageSize) : nullptr,
		.skipToken = ConvertFStringToCharPtr(Request.skipToken)
	};
	HResult = PFMultiplayerServerListBuildAliasesAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFMultiplayerServerListBuildAliasesResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FListBuildAliasesAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFMultiplayerServerListBuildAliasesGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFMultiplayerServerListBuildAliasesResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFMultiplayerServerListBuildAliasesResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFMultiplayerServerListBuildAliasesGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFMultiplayerServerListBuildAliasesResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFMultiplayerServerListBuildAliasesResponse> ResultType = ConvertListBuildAliasesResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FListBuildSummariesV2AsyncTask::FListBuildSummariesV2AsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFMultiplayerServerListBuildSummariesRequest InRequest,
	const FOnListBuildSummariesV2Completed& InDelegate)
	: FXAsyncTask(TEXT("FListBuildSummariesV2AsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FListBuildSummariesV2AsyncTask::DoWork()
{
	const PFMultiplayerServerListBuildSummariesRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.pageSize = Request.pageSize ? new int32(*Request.pageSize) : nullptr,
		.skipToken = ConvertFStringToCharPtr(Request.skipToken)
	};
	HResult = PFMultiplayerServerListBuildSummariesV2Async(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFMultiplayerServerListBuildSummariesResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FListBuildSummariesV2AsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFMultiplayerServerListBuildSummariesV2GetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFMultiplayerServerListBuildSummariesResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFMultiplayerServerListBuildSummariesResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFMultiplayerServerListBuildSummariesV2GetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFMultiplayerServerListBuildSummariesResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFMultiplayerServerListBuildSummariesResponse> ResultType = ConvertListBuildSummariesResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FListQosServersForTitleAsyncTask::FListQosServersForTitleAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFMultiplayerServerListQosServersForTitleRequest InRequest,
	const FOnListQosServersForTitleCompleted& InDelegate)
	: FXAsyncTask(TEXT("FListQosServersForTitleAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FListQosServersForTitleAsyncTask::DoWork()
{
	const PFMultiplayerServerListQosServersForTitleRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.includeAllRegions = Request.includeAllRegions ? new bool(*Request.includeAllRegions) : nullptr,
		.routingPreference = ConvertFStringToCharPtr(Request.routingPreference)
	};
	HResult = PFMultiplayerServerListQosServersForTitleAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFMultiplayerServerListQosServersForTitleResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FListQosServersForTitleAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFMultiplayerServerListQosServersForTitleGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFMultiplayerServerListQosServersForTitleResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFMultiplayerServerListQosServersForTitleResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFMultiplayerServerListQosServersForTitleGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFMultiplayerServerListQosServersForTitleResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFMultiplayerServerListQosServersForTitleResponse> ResultType = ConvertListQosServersForTitleResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

#if 0
FListSecretSummariesAsyncTask::FListSecretSummariesAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFMultiplayerServerListSecretSummariesRequest InRequest,
	const FOnListSecretSummariesCompleted& InDelegate)
	: FXAsyncTask(TEXT("FListSecretSummariesAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FListSecretSummariesAsyncTask::DoWork()
{
	const PFMultiplayerServerListSecretSummariesRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.pageSize = Request.pageSize ? new int32(*Request.pageSize) : nullptr,
		.skipToken = ConvertFStringToCharPtr(Request.skipToken)
	};
	HResult = PFMultiplayerServerListSecretSummariesAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFMultiplayerServerListSecretSummariesResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FListSecretSummariesAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFMultiplayerServerListSecretSummariesGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFMultiplayerServerListSecretSummariesResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFMultiplayerServerListSecretSummariesResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFMultiplayerServerListSecretSummariesGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFMultiplayerServerListSecretSummariesResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFMultiplayerServerListSecretSummariesResponse> ResultType = ConvertListSecretSummariesResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

FRequestMultiplayerServerAsyncTask::FRequestMultiplayerServerAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFMultiplayerServerRequestMultiplayerServerRequest InRequest,
	const FOnRequestMultiplayerServerCompleted& InDelegate)
	: FXAsyncTask(TEXT("FRequestMultiplayerServerAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FRequestMultiplayerServerAsyncTask::DoWork()
{
	const PFMultiplayerServerRequestMultiplayerServerRequest RequestType = {
		.buildAliasParams = ConvertBuildAliasParamsToPlayfab(Request.buildAliasParams),
		.buildId = ConvertFStringToCharPtr(Request.buildId),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.initialPlayers = ConvertFStringArrayToPlayfab(Request.initialPlayers),
		.initialPlayersCount = (uint32_t)Request.initialPlayers.Num(),
		.preferredRegions = ConvertFStringArrayToPlayfab(Request.preferredRegions),
		.preferredRegionsCount = (uint32_t)Request.preferredRegions.Num(),
		.sessionCookie = ConvertFStringToCharPtr(Request.sessionCookie),
		.sessionId = ConvertFStringToCharPtr(Request.sessionId)
	};
	HResult = PFMultiplayerServerRequestMultiplayerServerAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFMultiplayerServerRequestMultiplayerServerResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FRequestMultiplayerServerAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFMultiplayerServerRequestMultiplayerServerGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFMultiplayerServerRequestMultiplayerServerResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFMultiplayerServerRequestMultiplayerServerResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFMultiplayerServerRequestMultiplayerServerGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFMultiplayerServerRequestMultiplayerServerResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFMultiplayerServerRequestMultiplayerServerResponse> ResultType = ConvertRequestMultiplayerServerResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

#if 0
FRequestPartyServiceAsyncTask::FRequestPartyServiceAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFMultiplayerServerRequestPartyServiceRequest InRequest,
	const FOnRequestPartyServiceCompleted& InDelegate)
	: FXAsyncTask(TEXT("FRequestPartyServiceAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FRequestPartyServiceAsyncTask::DoWork()
{
	const PFMultiplayerServerRequestPartyServiceRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.networkConfiguration = ConvertPartyNetworkConfigurationToPlayfab(Request.networkConfiguration),
		.partyId = ConvertFStringToCharPtr(Request.partyId),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId),
		.preferredRegions = ConvertFStringArrayToPlayfab(Request.preferredRegions),
		.preferredRegionsCount = (uint32_t)Request.preferredRegions.Num()
	};
	HResult = PFMultiplayerServerRequestPartyServiceAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFMultiplayerServerRequestPartyServiceResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FRequestPartyServiceAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFMultiplayerServerRequestPartyServiceGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFMultiplayerServerRequestPartyServiceResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFMultiplayerServerRequestPartyServiceResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFMultiplayerServerRequestPartyServiceGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFMultiplayerServerRequestPartyServiceResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFMultiplayerServerRequestPartyServiceResponse> ResultType = ConvertRequestPartyServiceResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if 0
FUploadSecretAsyncTask::FUploadSecretAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFMultiplayerServerUploadSecretRequest InRequest,
	const FOnUploadSecretCompleted& InDelegate)
	: FXAsyncTask(TEXT("FUploadSecretAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FUploadSecretAsyncTask::DoWork()
{
	const PFMultiplayerServerUploadSecretRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.forceUpdate = Request.forceUpdate ? new bool(*Request.forceUpdate) : nullptr,
		.gameSecret = ConvertSecretToPlayfab(Request.gameSecret)
	};
	HResult = PFMultiplayerServerUploadSecretAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FUploadSecretAsyncTask::ProcessResults()
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

