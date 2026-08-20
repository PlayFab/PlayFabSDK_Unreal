// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFProfilesAsyncTasks.h"

FGetProfileAsyncTask::FGetProfileAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFProfilesGetEntityProfileRequest InRequest,
	const FOnGetProfileCompleted& InDelegate)
	: FXAsyncTask(TEXT("FGetProfileAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FGetProfileAsyncTask::DoWork()
{
	const PFProfilesGetEntityProfileRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.dataAsObject = Request.dataAsObject ? new bool(*Request.dataAsObject) : nullptr,
		.entity = ConvertEntityKeyToPlayfab(Request.entity)
	};
	HResult = PFProfilesGetProfileAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFProfilesGetEntityProfileResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FGetProfileAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFProfilesGetProfileGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFProfilesGetEntityProfileResponse{ .ErrorMessage = FString::Printf(TEXT("GetResultSize failure: 0x%08X"), static_cast<uint32>(HResult)) }, false);
		return;
	}

	PFProfilesGetEntityProfileResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFProfilesGetProfileGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("GetResult failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFProfilesGetEntityProfileResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFProfilesGetEntityProfileResponse> ResultType = ConvertGetEntityProfileResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FGetProfilesAsyncTask::FGetProfilesAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFProfilesGetEntityProfilesRequest InRequest,
	const FOnGetProfilesCompleted& InDelegate)
	: FXAsyncTask(TEXT("FGetProfilesAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FGetProfilesAsyncTask::DoWork()
{
	const PFProfilesGetEntityProfilesRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.dataAsObject = Request.dataAsObject ? new bool(*Request.dataAsObject) : nullptr,
		.entities = ConvertUnrealArrayToPlayfab<PFEntityKey, FPFEntityKey>(Request.entities, ConvertEntityKeyToPlayfab),
		.entitiesCount = (uint32_t)Request.entities.Num()
	};
	HResult = PFProfilesGetProfilesAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFProfilesGetEntityProfilesResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FGetProfilesAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFProfilesGetProfilesGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFProfilesGetEntityProfilesResponse{ .ErrorMessage = FString::Printf(TEXT("GetResultSize failure: 0x%08X"), static_cast<uint32>(HResult)) }, false);
		return;
	}

	PFProfilesGetEntityProfilesResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFProfilesGetProfilesGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("GetResult failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFProfilesGetEntityProfilesResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFProfilesGetEntityProfilesResponse> ResultType = ConvertGetEntityProfilesResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FGetTitlePlayersFromMasterPlayerAccountIdsAsyncTask::FGetTitlePlayersFromMasterPlayerAccountIdsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFProfilesGetTitlePlayersFromMasterPlayerAccountIdsRequest InRequest,
	const FOnGetTitlePlayersFromMasterPlayerAccountIdsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FGetTitlePlayersFromMasterPlayerAccountIdsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FGetTitlePlayersFromMasterPlayerAccountIdsAsyncTask::DoWork()
{
	const PFProfilesGetTitlePlayersFromMasterPlayerAccountIdsRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.masterPlayerAccountIds = ConvertFStringArrayToPlayfab(Request.masterPlayerAccountIds),
		.masterPlayerAccountIdsCount = (uint32_t)Request.masterPlayerAccountIds.Num(),
		.titleId = ConvertFStringToCharPtr(Request.titleId)
	};
	HResult = PFProfilesGetTitlePlayersFromMasterPlayerAccountIdsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFProfilesGetTitlePlayersFromMasterPlayerAccountIdsResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FGetTitlePlayersFromMasterPlayerAccountIdsAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFProfilesGetTitlePlayersFromMasterPlayerAccountIdsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFProfilesGetTitlePlayersFromMasterPlayerAccountIdsResponse{ .ErrorMessage = FString::Printf(TEXT("GetResultSize failure: 0x%08X"), static_cast<uint32>(HResult)) }, false);
		return;
	}

	PFProfilesGetTitlePlayersFromMasterPlayerAccountIdsResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFProfilesGetTitlePlayersFromMasterPlayerAccountIdsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("GetResult failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFProfilesGetTitlePlayersFromMasterPlayerAccountIdsResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFProfilesGetTitlePlayersFromMasterPlayerAccountIdsResponse> ResultType = ConvertGetTitlePlayersFromMasterPlayerAccountIdsResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FSetProfileLanguageAsyncTask::FSetProfileLanguageAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFProfilesSetProfileLanguageRequest InRequest,
	const FOnSetProfileLanguageCompleted& InDelegate)
	: FXAsyncTask(TEXT("FSetProfileLanguageAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FSetProfileLanguageAsyncTask::DoWork()
{
	const PFProfilesSetProfileLanguageRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.expectedVersion = Request.expectedVersion ? new int32(*Request.expectedVersion) : nullptr,
		.language = ConvertFStringToCharPtr(Request.language)
	};
	HResult = PFProfilesSetProfileLanguageAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFProfilesSetProfileLanguageResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FSetProfileLanguageAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFProfilesSetProfileLanguageGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFProfilesSetProfileLanguageResponse{ .ErrorMessage = FString::Printf(TEXT("GetResultSize failure: 0x%08X"), static_cast<uint32>(HResult)) }, false);
		return;
	}

	PFProfilesSetProfileLanguageResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFProfilesSetProfileLanguageGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("GetResult failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFProfilesSetProfileLanguageResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFProfilesSetProfileLanguageResponse> ResultType = ConvertSetProfileLanguageResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FSetProfilePolicyAsyncTask::FSetProfilePolicyAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFProfilesSetEntityProfilePolicyRequest InRequest,
	const FOnSetProfilePolicyCompleted& InDelegate)
	: FXAsyncTask(TEXT("FSetProfilePolicyAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FSetProfilePolicyAsyncTask::DoWork()
{
	const PFProfilesSetEntityProfilePolicyRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.statements = ConvertUnrealArrayToPlayfab<PFProfilesEntityPermissionStatement, FPFProfilesEntityPermissionStatement>(Request.statements, ConvertEntityPermissionStatementToPlayfab),
		.statementsCount = (uint32_t)Request.statements.Num()
	};
	HResult = PFProfilesSetProfilePolicyAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFProfilesSetEntityProfilePolicyResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FSetProfilePolicyAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFProfilesSetProfilePolicyGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFProfilesSetEntityProfilePolicyResponse{ .ErrorMessage = FString::Printf(TEXT("GetResultSize failure: 0x%08X"), static_cast<uint32>(HResult)) }, false);
		return;
	}

	PFProfilesSetEntityProfilePolicyResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFProfilesSetProfilePolicyGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("GetResult failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFProfilesSetEntityProfilePolicyResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFProfilesSetEntityProfilePolicyResponse> ResultType = ConvertSetEntityProfilePolicyResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

