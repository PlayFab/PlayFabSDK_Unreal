// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFAccountManagementAsyncTasks.h"

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FClientAddOrUpdateContactEmailAsyncTask::FClientAddOrUpdateContactEmailAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementAddOrUpdateContactEmailRequest InRequest,
	const FOnClientAddOrUpdateContactEmailCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientAddOrUpdateContactEmailAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientAddOrUpdateContactEmailAsyncTask::DoWork()
{
	const PFAccountManagementAddOrUpdateContactEmailRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.emailAddress = ConvertFStringToCharPtr(Request.emailAddress)
	};
	HResult = PFAccountManagementClientAddOrUpdateContactEmailAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientAddOrUpdateContactEmailAsyncTask::ProcessResults()
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

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FClientAddUsernamePasswordAsyncTask::FClientAddUsernamePasswordAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementAddUsernamePasswordRequest InRequest,
	const FOnClientAddUsernamePasswordCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientAddUsernamePasswordAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientAddUsernamePasswordAsyncTask::DoWork()
{
	const PFAccountManagementAddUsernamePasswordRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.email = ConvertFStringToCharPtr(Request.email),
		.password = ConvertFStringToCharPtr(Request.password),
		.username = ConvertFStringToCharPtr(Request.username)
	};
	HResult = PFAccountManagementClientAddUsernamePasswordAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementAddUsernamePasswordResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientAddUsernamePasswordAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementClientAddUsernamePasswordGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementAddUsernamePasswordResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementAddUsernamePasswordResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementClientAddUsernamePasswordGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementAddUsernamePasswordResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementAddUsernamePasswordResult> ResultType = ConvertAddUsernamePasswordResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

FClientGetAccountInfoAsyncTask::FClientGetAccountInfoAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementGetAccountInfoRequest InRequest,
	const FOnClientGetAccountInfoCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientGetAccountInfoAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientGetAccountInfoAsyncTask::DoWork()
{
	const PFAccountManagementGetAccountInfoRequest RequestType = {
		.email = ConvertFStringToCharPtr(Request.email),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId),
		.titleDisplayName = ConvertFStringToCharPtr(Request.titleDisplayName),
		.username = ConvertFStringToCharPtr(Request.username)
	};
	HResult = PFAccountManagementClientGetAccountInfoAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementGetAccountInfoResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientGetAccountInfoAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementClientGetAccountInfoGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementGetAccountInfoResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementGetAccountInfoResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementClientGetAccountInfoGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementGetAccountInfoResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementGetAccountInfoResult> ResultType = ConvertGetAccountInfoResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FClientGetPlayerCombinedInfoAsyncTask::FClientGetPlayerCombinedInfoAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementGetPlayerCombinedInfoRequest InRequest,
	const FOnClientGetPlayerCombinedInfoCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientGetPlayerCombinedInfoAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientGetPlayerCombinedInfoAsyncTask::DoWork()
{
	const PFAccountManagementGetPlayerCombinedInfoRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(Request.infoRequestParameters),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId)
	};
	HResult = PFAccountManagementClientGetPlayerCombinedInfoAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementGetPlayerCombinedInfoResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientGetPlayerCombinedInfoAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementClientGetPlayerCombinedInfoGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementGetPlayerCombinedInfoResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementGetPlayerCombinedInfoResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementClientGetPlayerCombinedInfoGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementGetPlayerCombinedInfoResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementGetPlayerCombinedInfoResult> ResultType = ConvertGetPlayerCombinedInfoResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FClientGetPlayerProfileAsyncTask::FClientGetPlayerProfileAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementGetPlayerProfileRequest InRequest,
	const FOnClientGetPlayerProfileCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientGetPlayerProfileAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientGetPlayerProfileAsyncTask::DoWork()
{
	const PFAccountManagementGetPlayerProfileRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId),
		.profileConstraints = ConvertPlayerProfileViewConstraintsToPlayfab(Request.profileConstraints)
	};
	HResult = PFAccountManagementClientGetPlayerProfileAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementGetPlayerProfileResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientGetPlayerProfileAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementClientGetPlayerProfileGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementGetPlayerProfileResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementGetPlayerProfileResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementClientGetPlayerProfileGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementGetPlayerProfileResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementGetPlayerProfileResult> ResultType = ConvertGetPlayerProfileResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FClientGetPlayFabIDsFromBattleNetAccountIdsAsyncTask::FClientGetPlayFabIDsFromBattleNetAccountIdsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsRequest InRequest,
	const FOnClientGetPlayFabIDsFromBattleNetAccountIdsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientGetPlayFabIDsFromBattleNetAccountIdsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientGetPlayFabIDsFromBattleNetAccountIdsAsyncTask::DoWork()
{
	const PFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsRequest RequestType = {
		.battleNetAccountIds = ConvertFStringArrayToPlayfab(Request.battleNetAccountIds),
		.battleNetAccountIdsCount = (uint32_t)Request.battleNetAccountIds.Num()
	};
	HResult = PFAccountManagementClientGetPlayFabIDsFromBattleNetAccountIdsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientGetPlayFabIDsFromBattleNetAccountIdsAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementClientGetPlayFabIDsFromBattleNetAccountIdsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementClientGetPlayFabIDsFromBattleNetAccountIdsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsResult> ResultType = ConvertGetPlayFabIDsFromBattleNetAccountIdsResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC
FClientGetPlayFabIDsFromFacebookIDsAsyncTask::FClientGetPlayFabIDsFromFacebookIDsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementGetPlayFabIDsFromFacebookIDsRequest InRequest,
	const FOnClientGetPlayFabIDsFromFacebookIDsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientGetPlayFabIDsFromFacebookIDsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientGetPlayFabIDsFromFacebookIDsAsyncTask::DoWork()
{
	const PFAccountManagementGetPlayFabIDsFromFacebookIDsRequest RequestType = {
		.facebookIDs = ConvertFStringArrayToPlayfab(Request.facebookIDs),
		.facebookIDsCount = (uint32_t)Request.facebookIDs.Num()
	};
	HResult = PFAccountManagementClientGetPlayFabIDsFromFacebookIDsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromFacebookIDsResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientGetPlayFabIDsFromFacebookIDsAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementClientGetPlayFabIDsFromFacebookIDsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromFacebookIDsResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementGetPlayFabIDsFromFacebookIDsResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementClientGetPlayFabIDsFromFacebookIDsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromFacebookIDsResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromFacebookIDsResult> ResultType = ConvertGetPlayFabIDsFromFacebookIDsResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FClientGetPlayFabIDsFromFacebookInstantGamesIdsAsyncTask::FClientGetPlayFabIDsFromFacebookInstantGamesIdsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsRequest InRequest,
	const FOnClientGetPlayFabIDsFromFacebookInstantGamesIdsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientGetPlayFabIDsFromFacebookInstantGamesIdsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientGetPlayFabIDsFromFacebookInstantGamesIdsAsyncTask::DoWork()
{
	const PFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsRequest RequestType = {
		.facebookInstantGamesIds = ConvertFStringArrayToPlayfab(Request.facebookInstantGamesIds),
		.facebookInstantGamesIdsCount = (uint32_t)Request.facebookInstantGamesIds.Num()
	};
	HResult = PFAccountManagementClientGetPlayFabIDsFromFacebookInstantGamesIdsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientGetPlayFabIDsFromFacebookInstantGamesIdsAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementClientGetPlayFabIDsFromFacebookInstantGamesIdsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementClientGetPlayFabIDsFromFacebookInstantGamesIdsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsResult> ResultType = ConvertGetPlayFabIDsFromFacebookInstantGamesIdsResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC
FClientGetPlayFabIDsFromGameCenterIDsAsyncTask::FClientGetPlayFabIDsFromGameCenterIDsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementGetPlayFabIDsFromGameCenterIDsRequest InRequest,
	const FOnClientGetPlayFabIDsFromGameCenterIDsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientGetPlayFabIDsFromGameCenterIDsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientGetPlayFabIDsFromGameCenterIDsAsyncTask::DoWork()
{
	const PFAccountManagementGetPlayFabIDsFromGameCenterIDsRequest RequestType = {
		.gameCenterIDs = ConvertFStringArrayToPlayfab(Request.gameCenterIDs),
		.gameCenterIDsCount = (uint32_t)Request.gameCenterIDs.Num()
	};
	HResult = PFAccountManagementClientGetPlayFabIDsFromGameCenterIDsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromGameCenterIDsResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientGetPlayFabIDsFromGameCenterIDsAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementClientGetPlayFabIDsFromGameCenterIDsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromGameCenterIDsResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementGetPlayFabIDsFromGameCenterIDsResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementClientGetPlayFabIDsFromGameCenterIDsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromGameCenterIDsResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromGameCenterIDsResult> ResultType = ConvertGetPlayFabIDsFromGameCenterIDsResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_MAC
FClientGetPlayFabIDsFromGoogleIDsAsyncTask::FClientGetPlayFabIDsFromGoogleIDsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementGetPlayFabIDsFromGoogleIDsRequest InRequest,
	const FOnClientGetPlayFabIDsFromGoogleIDsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientGetPlayFabIDsFromGoogleIDsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientGetPlayFabIDsFromGoogleIDsAsyncTask::DoWork()
{
	const PFAccountManagementGetPlayFabIDsFromGoogleIDsRequest RequestType = {
		.googleIDs = ConvertFStringArrayToPlayfab(Request.googleIDs),
		.googleIDsCount = (uint32_t)Request.googleIDs.Num()
	};
	HResult = PFAccountManagementClientGetPlayFabIDsFromGoogleIDsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromGoogleIDsResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientGetPlayFabIDsFromGoogleIDsAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementClientGetPlayFabIDsFromGoogleIDsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromGoogleIDsResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementGetPlayFabIDsFromGoogleIDsResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementClientGetPlayFabIDsFromGoogleIDsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromGoogleIDsResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromGoogleIDsResult> ResultType = ConvertGetPlayFabIDsFromGoogleIDsResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_MAC
FClientGetPlayFabIDsFromGooglePlayGamesPlayerIDsAsyncTask::FClientGetPlayFabIDsFromGooglePlayGamesPlayerIDsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementGetPlayFabIDsFromGooglePlayGamesPlayerIDsRequest InRequest,
	const FOnClientGetPlayFabIDsFromGooglePlayGamesPlayerIDsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientGetPlayFabIDsFromGooglePlayGamesPlayerIDsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientGetPlayFabIDsFromGooglePlayGamesPlayerIDsAsyncTask::DoWork()
{
	const PFAccountManagementGetPlayFabIDsFromGooglePlayGamesPlayerIDsRequest RequestType = {
		.googlePlayGamesPlayerIDs = ConvertFStringArrayToPlayfab(Request.googlePlayGamesPlayerIDs),
		.googlePlayGamesPlayerIDsCount = (uint32_t)Request.googlePlayGamesPlayerIDs.Num()
	};
	HResult = PFAccountManagementClientGetPlayFabIDsFromGooglePlayGamesPlayerIDsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromGooglePlayGamesPlayerIDsResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientGetPlayFabIDsFromGooglePlayGamesPlayerIDsAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementClientGetPlayFabIDsFromGooglePlayGamesPlayerIDsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromGooglePlayGamesPlayerIDsResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementGetPlayFabIDsFromGooglePlayGamesPlayerIDsResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementClientGetPlayFabIDsFromGooglePlayGamesPlayerIDsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromGooglePlayGamesPlayerIDsResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromGooglePlayGamesPlayerIDsResult> ResultType = ConvertGetPlayFabIDsFromGooglePlayGamesPlayerIDsResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FClientGetPlayFabIDsFromKongregateIDsAsyncTask::FClientGetPlayFabIDsFromKongregateIDsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementGetPlayFabIDsFromKongregateIDsRequest InRequest,
	const FOnClientGetPlayFabIDsFromKongregateIDsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientGetPlayFabIDsFromKongregateIDsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientGetPlayFabIDsFromKongregateIDsAsyncTask::DoWork()
{
	const PFAccountManagementGetPlayFabIDsFromKongregateIDsRequest RequestType = {
		.kongregateIDs = ConvertFStringArrayToPlayfab(Request.kongregateIDs),
		.kongregateIDsCount = (uint32_t)Request.kongregateIDs.Num()
	};
	HResult = PFAccountManagementClientGetPlayFabIDsFromKongregateIDsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromKongregateIDsResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientGetPlayFabIDsFromKongregateIDsAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementClientGetPlayFabIDsFromKongregateIDsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromKongregateIDsResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementGetPlayFabIDsFromKongregateIDsResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementClientGetPlayFabIDsFromKongregateIDsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromKongregateIDsResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromKongregateIDsResult> ResultType = ConvertGetPlayFabIDsFromKongregateIDsResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_NINTENDO_SWITCH || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FClientGetPlayFabIDsFromNintendoServiceAccountIdsAsyncTask::FClientGetPlayFabIDsFromNintendoServiceAccountIdsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsRequest InRequest,
	const FOnClientGetPlayFabIDsFromNintendoServiceAccountIdsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientGetPlayFabIDsFromNintendoServiceAccountIdsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientGetPlayFabIDsFromNintendoServiceAccountIdsAsyncTask::DoWork()
{
	const PFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsRequest RequestType = {
		.nintendoAccountIds = ConvertFStringArrayToPlayfab(Request.nintendoAccountIds),
		.nintendoAccountIdsCount = (uint32_t)Request.nintendoAccountIds.Num()
	};
	HResult = PFAccountManagementClientGetPlayFabIDsFromNintendoServiceAccountIdsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientGetPlayFabIDsFromNintendoServiceAccountIdsAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementClientGetPlayFabIDsFromNintendoServiceAccountIdsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementClientGetPlayFabIDsFromNintendoServiceAccountIdsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsResult> ResultType = ConvertGetPlayFabIDsFromNintendoServiceAccountIdsResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FClientGetPlayFabIDsFromNintendoSwitchDeviceIdsAsyncTask::FClientGetPlayFabIDsFromNintendoSwitchDeviceIdsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsRequest InRequest,
	const FOnClientGetPlayFabIDsFromNintendoSwitchDeviceIdsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientGetPlayFabIDsFromNintendoSwitchDeviceIdsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientGetPlayFabIDsFromNintendoSwitchDeviceIdsAsyncTask::DoWork()
{
	const PFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsRequest RequestType = {
		.nintendoSwitchDeviceIds = ConvertFStringArrayToPlayfab(Request.nintendoSwitchDeviceIds),
		.nintendoSwitchDeviceIdsCount = (uint32_t)Request.nintendoSwitchDeviceIds.Num()
	};
	HResult = PFAccountManagementClientGetPlayFabIDsFromNintendoSwitchDeviceIdsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientGetPlayFabIDsFromNintendoSwitchDeviceIdsAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementClientGetPlayFabIDsFromNintendoSwitchDeviceIdsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementClientGetPlayFabIDsFromNintendoSwitchDeviceIdsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsResult> ResultType = ConvertGetPlayFabIDsFromNintendoSwitchDeviceIdsResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_4 || HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_5 || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FClientGetPlayFabIDsFromPSNAccountIDsAsyncTask::FClientGetPlayFabIDsFromPSNAccountIDsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementGetPlayFabIDsFromPSNAccountIDsRequest InRequest,
	const FOnClientGetPlayFabIDsFromPSNAccountIDsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientGetPlayFabIDsFromPSNAccountIDsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientGetPlayFabIDsFromPSNAccountIDsAsyncTask::DoWork()
{
	const PFAccountManagementGetPlayFabIDsFromPSNAccountIDsRequest RequestType = {
		.issuerId = Request.issuerId ? new int32(*Request.issuerId) : nullptr,
		.PSNAccountIDs = ConvertFStringArrayToPlayfab(Request.PSNAccountIDs),
		.PSNAccountIDsCount = (uint32_t)Request.PSNAccountIDs.Num()
	};
	HResult = PFAccountManagementClientGetPlayFabIDsFromPSNAccountIDsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromPSNAccountIDsResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientGetPlayFabIDsFromPSNAccountIDsAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementClientGetPlayFabIDsFromPSNAccountIDsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromPSNAccountIDsResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementGetPlayFabIDsFromPSNAccountIDsResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementClientGetPlayFabIDsFromPSNAccountIDsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromPSNAccountIDsResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromPSNAccountIDsResult> ResultType = ConvertGetPlayFabIDsFromPSNAccountIDsResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

FClientGetPlayFabIDsFromPSNOnlineIDsAsyncTask::FClientGetPlayFabIDsFromPSNOnlineIDsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementGetPlayFabIDsFromPSNOnlineIDsRequest InRequest,
	const FOnClientGetPlayFabIDsFromPSNOnlineIDsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientGetPlayFabIDsFromPSNOnlineIDsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientGetPlayFabIDsFromPSNOnlineIDsAsyncTask::DoWork()
{
	const PFAccountManagementGetPlayFabIDsFromPSNOnlineIDsRequest RequestType = {
		.issuerId = Request.issuerId ? new int32(*Request.issuerId) : nullptr,
		.PSNOnlineIDs = ConvertFStringArrayToPlayfab(Request.PSNOnlineIDs),
		.PSNOnlineIDsCount = (uint32_t)Request.PSNOnlineIDs.Num()
	};
	HResult = PFAccountManagementClientGetPlayFabIDsFromPSNOnlineIDsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromPSNOnlineIDsResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientGetPlayFabIDsFromPSNOnlineIDsAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementClientGetPlayFabIDsFromPSNOnlineIDsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromPSNOnlineIDsResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementGetPlayFabIDsFromPSNOnlineIDsResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementClientGetPlayFabIDsFromPSNOnlineIDsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromPSNOnlineIDsResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromPSNOnlineIDsResult> ResultType = ConvertGetPlayFabIDsFromPSNOnlineIDsResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FClientGetPlayFabIDsFromSteamIDsAsyncTask::FClientGetPlayFabIDsFromSteamIDsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementGetPlayFabIDsFromSteamIDsRequest InRequest,
	const FOnClientGetPlayFabIDsFromSteamIDsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientGetPlayFabIDsFromSteamIDsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientGetPlayFabIDsFromSteamIDsAsyncTask::DoWork()
{
	const PFAccountManagementGetPlayFabIDsFromSteamIDsRequest RequestType = {
		.steamStringIDs = ConvertFStringArrayToPlayfab(Request.steamStringIDs),
		.steamStringIDsCount = (uint32_t)Request.steamStringIDs.Num()
	};
	HResult = PFAccountManagementClientGetPlayFabIDsFromSteamIDsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromSteamIDsResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientGetPlayFabIDsFromSteamIDsAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementClientGetPlayFabIDsFromSteamIDsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromSteamIDsResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementGetPlayFabIDsFromSteamIDsResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementClientGetPlayFabIDsFromSteamIDsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromSteamIDsResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromSteamIDsResult> ResultType = ConvertGetPlayFabIDsFromSteamIDsResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

FClientGetPlayFabIDsFromSteamNamesAsyncTask::FClientGetPlayFabIDsFromSteamNamesAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementGetPlayFabIDsFromSteamNamesRequest InRequest,
	const FOnClientGetPlayFabIDsFromSteamNamesCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientGetPlayFabIDsFromSteamNamesAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientGetPlayFabIDsFromSteamNamesAsyncTask::DoWork()
{
	const PFAccountManagementGetPlayFabIDsFromSteamNamesRequest RequestType = {
		.steamNames = ConvertFStringArrayToPlayfab(Request.steamNames),
		.steamNamesCount = (uint32_t)Request.steamNames.Num()
	};
	HResult = PFAccountManagementClientGetPlayFabIDsFromSteamNamesAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromSteamNamesResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientGetPlayFabIDsFromSteamNamesAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementClientGetPlayFabIDsFromSteamNamesGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromSteamNamesResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementGetPlayFabIDsFromSteamNamesResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementClientGetPlayFabIDsFromSteamNamesGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromSteamNamesResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromSteamNamesResult> ResultType = ConvertGetPlayFabIDsFromSteamNamesResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FClientGetPlayFabIDsFromTwitchIDsAsyncTask::FClientGetPlayFabIDsFromTwitchIDsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementGetPlayFabIDsFromTwitchIDsRequest InRequest,
	const FOnClientGetPlayFabIDsFromTwitchIDsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientGetPlayFabIDsFromTwitchIDsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientGetPlayFabIDsFromTwitchIDsAsyncTask::DoWork()
{
	const PFAccountManagementGetPlayFabIDsFromTwitchIDsRequest RequestType = {
		.twitchIds = ConvertFStringArrayToPlayfab(Request.twitchIds),
		.twitchIdsCount = (uint32_t)Request.twitchIds.Num()
	};
	HResult = PFAccountManagementClientGetPlayFabIDsFromTwitchIDsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromTwitchIDsResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientGetPlayFabIDsFromTwitchIDsAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementClientGetPlayFabIDsFromTwitchIDsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromTwitchIDsResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementGetPlayFabIDsFromTwitchIDsResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementClientGetPlayFabIDsFromTwitchIDsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromTwitchIDsResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromTwitchIDsResult> ResultType = ConvertGetPlayFabIDsFromTwitchIDsResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FClientGetPlayFabIDsFromXboxLiveIDsAsyncTask::FClientGetPlayFabIDsFromXboxLiveIDsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementGetPlayFabIDsFromXboxLiveIDsRequest InRequest,
	const FOnClientGetPlayFabIDsFromXboxLiveIDsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientGetPlayFabIDsFromXboxLiveIDsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientGetPlayFabIDsFromXboxLiveIDsAsyncTask::DoWork()
{
	const PFAccountManagementGetPlayFabIDsFromXboxLiveIDsRequest RequestType = {
		.sandbox = ConvertFStringToCharPtr(Request.sandbox),
		.xboxLiveAccountIDs = ConvertFStringArrayToPlayfab(Request.xboxLiveAccountIDs),
		.xboxLiveAccountIDsCount = (uint32_t)Request.xboxLiveAccountIDs.Num()
	};
	HResult = PFAccountManagementClientGetPlayFabIDsFromXboxLiveIDsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromXboxLiveIDsResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientGetPlayFabIDsFromXboxLiveIDsAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementClientGetPlayFabIDsFromXboxLiveIDsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromXboxLiveIDsResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementGetPlayFabIDsFromXboxLiveIDsResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementClientGetPlayFabIDsFromXboxLiveIDsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromXboxLiveIDsResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromXboxLiveIDsResult> ResultType = ConvertGetPlayFabIDsFromXboxLiveIDsResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FClientLinkAndroidDeviceIDAsyncTask::FClientLinkAndroidDeviceIDAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementLinkAndroidDeviceIDRequest InRequest,
	const FOnClientLinkAndroidDeviceIDCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientLinkAndroidDeviceIDAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientLinkAndroidDeviceIDAsyncTask::DoWork()
{
	const PFAccountManagementLinkAndroidDeviceIDRequest RequestType = {
		.androidDevice = ConvertFStringToCharPtr(Request.androidDevice),
		.androidDeviceId = ConvertFStringToCharPtr(Request.androidDeviceId),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.forceLink = Request.forceLink ? new bool(*Request.forceLink) : nullptr,
		.OS = ConvertFStringToCharPtr(Request.OS)
	};
	HResult = PFAccountManagementClientLinkAndroidDeviceIDAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientLinkAndroidDeviceIDAsyncTask::ProcessResults()
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

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC
FClientLinkAppleAsyncTask::FClientLinkAppleAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementLinkAppleRequest InRequest,
	const FOnClientLinkAppleCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientLinkAppleAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientLinkAppleAsyncTask::DoWork()
{
	const PFAccountManagementLinkAppleRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.forceLink = Request.forceLink ? new bool(*Request.forceLink) : nullptr,
		.identityToken = ConvertFStringToCharPtr(Request.identityToken)
	};
	HResult = PFAccountManagementClientLinkAppleAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientLinkAppleAsyncTask::ProcessResults()
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

#if HC_PLATFORM == HC_PLATFORM_GDK
FClientLinkBattleNetAccountAsyncTask::FClientLinkBattleNetAccountAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementClientLinkBattleNetAccountRequest InRequest,
	const FOnClientLinkBattleNetAccountCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientLinkBattleNetAccountAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientLinkBattleNetAccountAsyncTask::DoWork()
{
	const PFAccountManagementClientLinkBattleNetAccountRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.forceLink = Request.forceLink ? new bool(*Request.forceLink) : nullptr,
		.identityToken = ConvertFStringToCharPtr(Request.identityToken)
	};
	HResult = PFAccountManagementClientLinkBattleNetAccountAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientLinkBattleNetAccountAsyncTask::ProcessResults()
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

FClientLinkCustomIDAsyncTask::FClientLinkCustomIDAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementLinkCustomIDRequest InRequest,
	const FOnClientLinkCustomIDCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientLinkCustomIDAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientLinkCustomIDAsyncTask::DoWork()
{
	const PFAccountManagementLinkCustomIDRequest RequestType = {
		.customId = ConvertFStringToCharPtr(Request.customId),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.forceLink = Request.forceLink ? new bool(*Request.forceLink) : nullptr
	};
	HResult = PFAccountManagementClientLinkCustomIDAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientLinkCustomIDAsyncTask::ProcessResults()
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

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC
FClientLinkFacebookAccountAsyncTask::FClientLinkFacebookAccountAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementLinkFacebookAccountRequest InRequest,
	const FOnClientLinkFacebookAccountCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientLinkFacebookAccountAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientLinkFacebookAccountAsyncTask::DoWork()
{
	const PFAccountManagementLinkFacebookAccountRequest RequestType = {
		.accessToken = ConvertFStringToCharPtr(Request.accessToken),
		.authenticationToken = ConvertFStringToCharPtr(Request.authenticationToken),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.forceLink = Request.forceLink ? new bool(*Request.forceLink) : nullptr
	};
	HResult = PFAccountManagementClientLinkFacebookAccountAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientLinkFacebookAccountAsyncTask::ProcessResults()
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

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FClientLinkFacebookInstantGamesIdAsyncTask::FClientLinkFacebookInstantGamesIdAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementLinkFacebookInstantGamesIdRequest InRequest,
	const FOnClientLinkFacebookInstantGamesIdCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientLinkFacebookInstantGamesIdAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientLinkFacebookInstantGamesIdAsyncTask::DoWork()
{
	const PFAccountManagementLinkFacebookInstantGamesIdRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.facebookInstantGamesSignature = ConvertFStringToCharPtr(Request.facebookInstantGamesSignature),
		.forceLink = Request.forceLink ? new bool(*Request.forceLink) : nullptr
	};
	HResult = PFAccountManagementClientLinkFacebookInstantGamesIdAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientLinkFacebookInstantGamesIdAsyncTask::ProcessResults()
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

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC
FClientLinkGameCenterAccountAsyncTask::FClientLinkGameCenterAccountAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementLinkGameCenterAccountRequest InRequest,
	const FOnClientLinkGameCenterAccountCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientLinkGameCenterAccountAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientLinkGameCenterAccountAsyncTask::DoWork()
{
	const PFAccountManagementLinkGameCenterAccountRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.forceLink = Request.forceLink ? new bool(*Request.forceLink) : nullptr,
		.gameCenterId = ConvertFStringToCharPtr(Request.gameCenterId),
		.publicKeyUrl = ConvertFStringToCharPtr(Request.publicKeyUrl),
		.salt = ConvertFStringToCharPtr(Request.salt),
		.signature = ConvertFStringToCharPtr(Request.signature),
		.timestamp = ConvertFStringToCharPtr(Request.timestamp)
	};
	HResult = PFAccountManagementClientLinkGameCenterAccountAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientLinkGameCenterAccountAsyncTask::ProcessResults()
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

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_MAC
FClientLinkGoogleAccountAsyncTask::FClientLinkGoogleAccountAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementLinkGoogleAccountRequest InRequest,
	const FOnClientLinkGoogleAccountCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientLinkGoogleAccountAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientLinkGoogleAccountAsyncTask::DoWork()
{
	const PFAccountManagementLinkGoogleAccountRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.forceLink = Request.forceLink ? new bool(*Request.forceLink) : nullptr,
		.serverAuthCode = ConvertFStringToCharPtr(Request.serverAuthCode)
	};
	HResult = PFAccountManagementClientLinkGoogleAccountAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientLinkGoogleAccountAsyncTask::ProcessResults()
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

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_MAC
FClientLinkGooglePlayGamesServicesAccountAsyncTask::FClientLinkGooglePlayGamesServicesAccountAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementLinkGooglePlayGamesServicesAccountRequest InRequest,
	const FOnClientLinkGooglePlayGamesServicesAccountCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientLinkGooglePlayGamesServicesAccountAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientLinkGooglePlayGamesServicesAccountAsyncTask::DoWork()
{
	const PFAccountManagementLinkGooglePlayGamesServicesAccountRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.forceLink = Request.forceLink ? new bool(*Request.forceLink) : nullptr,
		.serverAuthCode = ConvertFStringToCharPtr(Request.serverAuthCode)
	};
	HResult = PFAccountManagementClientLinkGooglePlayGamesServicesAccountAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientLinkGooglePlayGamesServicesAccountAsyncTask::ProcessResults()
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

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FClientLinkIOSDeviceIDAsyncTask::FClientLinkIOSDeviceIDAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementLinkIOSDeviceIDRequest InRequest,
	const FOnClientLinkIOSDeviceIDCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientLinkIOSDeviceIDAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientLinkIOSDeviceIDAsyncTask::DoWork()
{
	const PFAccountManagementLinkIOSDeviceIDRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.deviceId = ConvertFStringToCharPtr(Request.deviceId),
		.deviceModel = ConvertFStringToCharPtr(Request.deviceModel),
		.forceLink = Request.forceLink ? new bool(*Request.forceLink) : nullptr,
		.OS = ConvertFStringToCharPtr(Request.OS)
	};
	HResult = PFAccountManagementClientLinkIOSDeviceIDAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientLinkIOSDeviceIDAsyncTask::ProcessResults()
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

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FClientLinkKongregateAsyncTask::FClientLinkKongregateAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementLinkKongregateAccountRequest InRequest,
	const FOnClientLinkKongregateCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientLinkKongregateAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientLinkKongregateAsyncTask::DoWork()
{
	const PFAccountManagementLinkKongregateAccountRequest RequestType = {
		.authTicket = ConvertFStringToCharPtr(Request.authTicket),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.forceLink = Request.forceLink ? new bool(*Request.forceLink) : nullptr,
		.kongregateId = ConvertFStringToCharPtr(Request.kongregateId)
	};
	HResult = PFAccountManagementClientLinkKongregateAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientLinkKongregateAsyncTask::ProcessResults()
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

#if HC_PLATFORM == HC_PLATFORM_NINTENDO_SWITCH || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FClientLinkNintendoServiceAccountAsyncTask::FClientLinkNintendoServiceAccountAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementClientLinkNintendoServiceAccountRequest InRequest,
	const FOnClientLinkNintendoServiceAccountCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientLinkNintendoServiceAccountAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientLinkNintendoServiceAccountAsyncTask::DoWork()
{
	const PFAccountManagementClientLinkNintendoServiceAccountRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.forceLink = Request.forceLink ? new bool(*Request.forceLink) : nullptr,
		.identityToken = ConvertFStringToCharPtr(Request.identityToken)
	};
	HResult = PFAccountManagementClientLinkNintendoServiceAccountAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientLinkNintendoServiceAccountAsyncTask::ProcessResults()
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

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FClientLinkNintendoSwitchDeviceIdAsyncTask::FClientLinkNintendoSwitchDeviceIdAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementClientLinkNintendoSwitchDeviceIdRequest InRequest,
	const FOnClientLinkNintendoSwitchDeviceIdCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientLinkNintendoSwitchDeviceIdAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientLinkNintendoSwitchDeviceIdAsyncTask::DoWork()
{
	const PFAccountManagementClientLinkNintendoSwitchDeviceIdRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.forceLink = Request.forceLink ? new bool(*Request.forceLink) : nullptr,
		.nintendoSwitchDeviceId = ConvertFStringToCharPtr(Request.nintendoSwitchDeviceId)
	};
	HResult = PFAccountManagementClientLinkNintendoSwitchDeviceIdAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientLinkNintendoSwitchDeviceIdAsyncTask::ProcessResults()
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

FClientLinkOpenIdConnectAsyncTask::FClientLinkOpenIdConnectAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementLinkOpenIdConnectRequest InRequest,
	const FOnClientLinkOpenIdConnectCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientLinkOpenIdConnectAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientLinkOpenIdConnectAsyncTask::DoWork()
{
	const PFAccountManagementLinkOpenIdConnectRequest RequestType = {
		.connectionId = ConvertFStringToCharPtr(Request.connectionId),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.forceLink = Request.forceLink ? new bool(*Request.forceLink) : nullptr,
		.idToken = ConvertFStringToCharPtr(Request.idToken)
	};
	HResult = PFAccountManagementClientLinkOpenIdConnectAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientLinkOpenIdConnectAsyncTask::ProcessResults()
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

#if HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_4 || HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_5 || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FClientLinkPSNAccountAsyncTask::FClientLinkPSNAccountAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementClientLinkPSNAccountRequest InRequest,
	const FOnClientLinkPSNAccountCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientLinkPSNAccountAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientLinkPSNAccountAsyncTask::DoWork()
{
	const PFAccountManagementClientLinkPSNAccountRequest RequestType = {
		.authCode = ConvertFStringToCharPtr(Request.authCode),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.forceLink = Request.forceLink ? new bool(*Request.forceLink) : nullptr,
		.issuerId = Request.issuerId ? new int32(*Request.issuerId) : nullptr,
		.redirectUri = ConvertFStringToCharPtr(Request.redirectUri)
	};
	HResult = PFAccountManagementClientLinkPSNAccountAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientLinkPSNAccountAsyncTask::ProcessResults()
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
FClientLinkSteamAccountAsyncTask::FClientLinkSteamAccountAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementLinkSteamAccountRequest InRequest,
	const FOnClientLinkSteamAccountCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientLinkSteamAccountAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientLinkSteamAccountAsyncTask::DoWork()
{
	const PFAccountManagementLinkSteamAccountRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.forceLink = Request.forceLink ? new bool(*Request.forceLink) : nullptr,
		.steamTicket = ConvertFStringToCharPtr(Request.steamTicket),
		.ticketIsServiceSpecific = Request.ticketIsServiceSpecific ? new bool(*Request.ticketIsServiceSpecific) : nullptr
	};
	HResult = PFAccountManagementClientLinkSteamAccountAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientLinkSteamAccountAsyncTask::ProcessResults()
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

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FClientLinkTwitchAsyncTask::FClientLinkTwitchAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementLinkTwitchAccountRequest InRequest,
	const FOnClientLinkTwitchCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientLinkTwitchAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientLinkTwitchAsyncTask::DoWork()
{
	const PFAccountManagementLinkTwitchAccountRequest RequestType = {
		.accessToken = ConvertFStringToCharPtr(Request.accessToken),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.forceLink = Request.forceLink ? new bool(*Request.forceLink) : nullptr
	};
	HResult = PFAccountManagementClientLinkTwitchAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientLinkTwitchAsyncTask::ProcessResults()
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
FClientLinkXboxAccountAsyncTask::FClientLinkXboxAccountAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementClientLinkXboxAccountRequest InRequest,
	const FOnClientLinkXboxAccountCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientLinkXboxAccountAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientLinkXboxAccountAsyncTask::DoWork()
{
	const PFAccountManagementClientLinkXboxAccountRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.forceLink = Request.forceLink ? new bool(*Request.forceLink) : nullptr,
#if defined(PF_GDK_AVAILABLE)
		.user = Request.user
#else
		.xboxToken = ConvertFStringToCharPtr(Request.xboxToken)
#endif
	};
	HResult = PFAccountManagementClientLinkXboxAccountAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientLinkXboxAccountAsyncTask::ProcessResults()
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
FClientRemoveContactEmailAsyncTask::FClientRemoveContactEmailAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementRemoveContactEmailRequest InRequest,
	const FOnClientRemoveContactEmailCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientRemoveContactEmailAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientRemoveContactEmailAsyncTask::DoWork()
{
	const PFAccountManagementRemoveContactEmailRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num()
	};
	HResult = PFAccountManagementClientRemoveContactEmailAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientRemoveContactEmailAsyncTask::ProcessResults()
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

FClientReportPlayerAsyncTask::FClientReportPlayerAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementReportPlayerClientRequest InRequest,
	const FOnClientReportPlayerCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientReportPlayerAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientReportPlayerAsyncTask::DoWork()
{
	const PFAccountManagementReportPlayerClientRequest RequestType = {
		.comment = ConvertFStringToCharPtr(Request.comment),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.reporteeId = ConvertFStringToCharPtr(Request.reporteeId)
	};
	HResult = PFAccountManagementClientReportPlayerAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementReportPlayerClientResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientReportPlayerAsyncTask::ProcessResults()
{
	PFAccountManagementReportPlayerClientResult Result = {};
	HResult = PFAccountManagementClientReportPlayerGetResult(*mAsyncBlock, &Result);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementReportPlayerClientResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementReportPlayerClientResult> ResultType = ConvertReportPlayerClientResultToUnreal(&Result);

	Delegate.Execute(*ResultType, true);
}

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FClientSendAccountRecoveryEmailAsyncTask::FClientSendAccountRecoveryEmailAsyncTask(
	_In_ FPFServiceConfigHandle ServiceConfigHandle,
	FPFAccountManagementSendAccountRecoveryEmailRequest InRequest,
	const FOnClientSendAccountRecoveryEmailCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientSendAccountRecoveryEmailAsyncTask")),
	ServiceConfigHandle(ServiceConfigHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientSendAccountRecoveryEmailAsyncTask::DoWork()
{
	const PFAccountManagementSendAccountRecoveryEmailRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.email = ConvertFStringToCharPtr(Request.email),
		.emailTemplateId = ConvertFStringToCharPtr(Request.emailTemplateId),
		.titleId = ConvertFStringToCharPtr(Request.titleId)
	};
	HResult = PFAccountManagementClientSendAccountRecoveryEmailAsync(ServiceConfigHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientSendAccountRecoveryEmailAsyncTask::ProcessResults()
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

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FClientUnlinkAndroidDeviceIDAsyncTask::FClientUnlinkAndroidDeviceIDAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementUnlinkAndroidDeviceIDRequest InRequest,
	const FOnClientUnlinkAndroidDeviceIDCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientUnlinkAndroidDeviceIDAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientUnlinkAndroidDeviceIDAsyncTask::DoWork()
{
	const PFAccountManagementUnlinkAndroidDeviceIDRequest RequestType = {
		.androidDeviceId = ConvertFStringToCharPtr(Request.androidDeviceId),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num()
	};
	HResult = PFAccountManagementClientUnlinkAndroidDeviceIDAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientUnlinkAndroidDeviceIDAsyncTask::ProcessResults()
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

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC
FClientUnlinkAppleAsyncTask::FClientUnlinkAppleAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementUnlinkAppleRequest InRequest,
	const FOnClientUnlinkAppleCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientUnlinkAppleAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientUnlinkAppleAsyncTask::DoWork()
{
	const PFAccountManagementUnlinkAppleRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num()
	};
	HResult = PFAccountManagementClientUnlinkAppleAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientUnlinkAppleAsyncTask::ProcessResults()
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

#if HC_PLATFORM == HC_PLATFORM_GDK
FClientUnlinkBattleNetAccountAsyncTask::FClientUnlinkBattleNetAccountAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementClientUnlinkBattleNetAccountRequest InRequest,
	const FOnClientUnlinkBattleNetAccountCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientUnlinkBattleNetAccountAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientUnlinkBattleNetAccountAsyncTask::DoWork()
{
	const PFAccountManagementClientUnlinkBattleNetAccountRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num()
	};
	HResult = PFAccountManagementClientUnlinkBattleNetAccountAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientUnlinkBattleNetAccountAsyncTask::ProcessResults()
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

FClientUnlinkCustomIDAsyncTask::FClientUnlinkCustomIDAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementUnlinkCustomIDRequest InRequest,
	const FOnClientUnlinkCustomIDCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientUnlinkCustomIDAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientUnlinkCustomIDAsyncTask::DoWork()
{
	const PFAccountManagementUnlinkCustomIDRequest RequestType = {
		.customId = ConvertFStringToCharPtr(Request.customId),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num()
	};
	HResult = PFAccountManagementClientUnlinkCustomIDAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientUnlinkCustomIDAsyncTask::ProcessResults()
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

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC
FClientUnlinkFacebookAccountAsyncTask::FClientUnlinkFacebookAccountAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementUnlinkFacebookAccountRequest InRequest,
	const FOnClientUnlinkFacebookAccountCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientUnlinkFacebookAccountAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientUnlinkFacebookAccountAsyncTask::DoWork()
{
	const PFAccountManagementUnlinkFacebookAccountRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num()
	};
	HResult = PFAccountManagementClientUnlinkFacebookAccountAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientUnlinkFacebookAccountAsyncTask::ProcessResults()
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

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FClientUnlinkFacebookInstantGamesIdAsyncTask::FClientUnlinkFacebookInstantGamesIdAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementUnlinkFacebookInstantGamesIdRequest InRequest,
	const FOnClientUnlinkFacebookInstantGamesIdCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientUnlinkFacebookInstantGamesIdAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientUnlinkFacebookInstantGamesIdAsyncTask::DoWork()
{
	const PFAccountManagementUnlinkFacebookInstantGamesIdRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.facebookInstantGamesId = ConvertFStringToCharPtr(Request.facebookInstantGamesId)
	};
	HResult = PFAccountManagementClientUnlinkFacebookInstantGamesIdAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientUnlinkFacebookInstantGamesIdAsyncTask::ProcessResults()
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

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC
FClientUnlinkGameCenterAccountAsyncTask::FClientUnlinkGameCenterAccountAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementUnlinkGameCenterAccountRequest InRequest,
	const FOnClientUnlinkGameCenterAccountCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientUnlinkGameCenterAccountAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientUnlinkGameCenterAccountAsyncTask::DoWork()
{
	const PFAccountManagementUnlinkGameCenterAccountRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num()
	};
	HResult = PFAccountManagementClientUnlinkGameCenterAccountAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientUnlinkGameCenterAccountAsyncTask::ProcessResults()
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

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_MAC
FClientUnlinkGoogleAccountAsyncTask::FClientUnlinkGoogleAccountAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementUnlinkGoogleAccountRequest InRequest,
	const FOnClientUnlinkGoogleAccountCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientUnlinkGoogleAccountAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientUnlinkGoogleAccountAsyncTask::DoWork()
{
	const PFAccountManagementUnlinkGoogleAccountRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num()
	};
	HResult = PFAccountManagementClientUnlinkGoogleAccountAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientUnlinkGoogleAccountAsyncTask::ProcessResults()
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

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_MAC
FClientUnlinkGooglePlayGamesServicesAccountAsyncTask::FClientUnlinkGooglePlayGamesServicesAccountAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementUnlinkGooglePlayGamesServicesAccountRequest InRequest,
	const FOnClientUnlinkGooglePlayGamesServicesAccountCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientUnlinkGooglePlayGamesServicesAccountAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientUnlinkGooglePlayGamesServicesAccountAsyncTask::DoWork()
{
	const PFAccountManagementUnlinkGooglePlayGamesServicesAccountRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num()
	};
	HResult = PFAccountManagementClientUnlinkGooglePlayGamesServicesAccountAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientUnlinkGooglePlayGamesServicesAccountAsyncTask::ProcessResults()
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

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FClientUnlinkIOSDeviceIDAsyncTask::FClientUnlinkIOSDeviceIDAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementUnlinkIOSDeviceIDRequest InRequest,
	const FOnClientUnlinkIOSDeviceIDCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientUnlinkIOSDeviceIDAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientUnlinkIOSDeviceIDAsyncTask::DoWork()
{
	const PFAccountManagementUnlinkIOSDeviceIDRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.deviceId = ConvertFStringToCharPtr(Request.deviceId)
	};
	HResult = PFAccountManagementClientUnlinkIOSDeviceIDAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientUnlinkIOSDeviceIDAsyncTask::ProcessResults()
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

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FClientUnlinkKongregateAsyncTask::FClientUnlinkKongregateAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementUnlinkKongregateAccountRequest InRequest,
	const FOnClientUnlinkKongregateCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientUnlinkKongregateAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientUnlinkKongregateAsyncTask::DoWork()
{
	const PFAccountManagementUnlinkKongregateAccountRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num()
	};
	HResult = PFAccountManagementClientUnlinkKongregateAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientUnlinkKongregateAsyncTask::ProcessResults()
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

#if HC_PLATFORM == HC_PLATFORM_NINTENDO_SWITCH || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FClientUnlinkNintendoServiceAccountAsyncTask::FClientUnlinkNintendoServiceAccountAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementClientUnlinkNintendoServiceAccountRequest InRequest,
	const FOnClientUnlinkNintendoServiceAccountCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientUnlinkNintendoServiceAccountAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientUnlinkNintendoServiceAccountAsyncTask::DoWork()
{
	const PFAccountManagementClientUnlinkNintendoServiceAccountRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num()
	};
	HResult = PFAccountManagementClientUnlinkNintendoServiceAccountAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientUnlinkNintendoServiceAccountAsyncTask::ProcessResults()
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

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FClientUnlinkNintendoSwitchDeviceIdAsyncTask::FClientUnlinkNintendoSwitchDeviceIdAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementClientUnlinkNintendoSwitchDeviceIdRequest InRequest,
	const FOnClientUnlinkNintendoSwitchDeviceIdCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientUnlinkNintendoSwitchDeviceIdAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientUnlinkNintendoSwitchDeviceIdAsyncTask::DoWork()
{
	const PFAccountManagementClientUnlinkNintendoSwitchDeviceIdRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.nintendoSwitchDeviceId = ConvertFStringToCharPtr(Request.nintendoSwitchDeviceId)
	};
	HResult = PFAccountManagementClientUnlinkNintendoSwitchDeviceIdAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientUnlinkNintendoSwitchDeviceIdAsyncTask::ProcessResults()
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

FClientUnlinkOpenIdConnectAsyncTask::FClientUnlinkOpenIdConnectAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementUnlinkOpenIdConnectRequest InRequest,
	const FOnClientUnlinkOpenIdConnectCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientUnlinkOpenIdConnectAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientUnlinkOpenIdConnectAsyncTask::DoWork()
{
	const PFAccountManagementUnlinkOpenIdConnectRequest RequestType = {
		.connectionId = ConvertFStringToCharPtr(Request.connectionId),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num()
	};
	HResult = PFAccountManagementClientUnlinkOpenIdConnectAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientUnlinkOpenIdConnectAsyncTask::ProcessResults()
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

#if HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_4 || HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_5 || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FClientUnlinkPSNAccountAsyncTask::FClientUnlinkPSNAccountAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementClientUnlinkPSNAccountRequest InRequest,
	const FOnClientUnlinkPSNAccountCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientUnlinkPSNAccountAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientUnlinkPSNAccountAsyncTask::DoWork()
{
	const PFAccountManagementClientUnlinkPSNAccountRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num()
	};
	HResult = PFAccountManagementClientUnlinkPSNAccountAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientUnlinkPSNAccountAsyncTask::ProcessResults()
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
FClientUnlinkSteamAccountAsyncTask::FClientUnlinkSteamAccountAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementUnlinkSteamAccountRequest InRequest,
	const FOnClientUnlinkSteamAccountCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientUnlinkSteamAccountAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientUnlinkSteamAccountAsyncTask::DoWork()
{
	const PFAccountManagementUnlinkSteamAccountRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num()
	};
	HResult = PFAccountManagementClientUnlinkSteamAccountAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientUnlinkSteamAccountAsyncTask::ProcessResults()
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

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FClientUnlinkTwitchAsyncTask::FClientUnlinkTwitchAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementUnlinkTwitchAccountRequest InRequest,
	const FOnClientUnlinkTwitchCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientUnlinkTwitchAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientUnlinkTwitchAsyncTask::DoWork()
{
	const PFAccountManagementUnlinkTwitchAccountRequest RequestType = {
		.accessToken = ConvertFStringToCharPtr(Request.accessToken),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num()
	};
	HResult = PFAccountManagementClientUnlinkTwitchAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientUnlinkTwitchAsyncTask::ProcessResults()
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
FClientUnlinkXboxAccountAsyncTask::FClientUnlinkXboxAccountAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementClientUnlinkXboxAccountRequest InRequest,
	const FOnClientUnlinkXboxAccountCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientUnlinkXboxAccountAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientUnlinkXboxAccountAsyncTask::DoWork()
{
	const PFAccountManagementClientUnlinkXboxAccountRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num()
	};
	HResult = PFAccountManagementClientUnlinkXboxAccountAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientUnlinkXboxAccountAsyncTask::ProcessResults()
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

FClientUpdateAvatarUrlAsyncTask::FClientUpdateAvatarUrlAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementClientUpdateAvatarUrlRequest InRequest,
	const FOnClientUpdateAvatarUrlCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientUpdateAvatarUrlAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientUpdateAvatarUrlAsyncTask::DoWork()
{
	const PFAccountManagementClientUpdateAvatarUrlRequest RequestType = {
		.imageUrl = ConvertFStringToCharPtr(Request.imageUrl)
	};
	HResult = PFAccountManagementClientUpdateAvatarUrlAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientUpdateAvatarUrlAsyncTask::ProcessResults()
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

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FClientUpdateUserTitleDisplayNameAsyncTask::FClientUpdateUserTitleDisplayNameAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementUpdateUserTitleDisplayNameRequest InRequest,
	const FOnClientUpdateUserTitleDisplayNameCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientUpdateUserTitleDisplayNameAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientUpdateUserTitleDisplayNameAsyncTask::DoWork()
{
	const PFAccountManagementUpdateUserTitleDisplayNameRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.displayName = ConvertFStringToCharPtr(Request.displayName)
	};
	HResult = PFAccountManagementClientUpdateUserTitleDisplayNameAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementUpdateUserTitleDisplayNameResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientUpdateUserTitleDisplayNameAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementClientUpdateUserTitleDisplayNameGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementUpdateUserTitleDisplayNameResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementUpdateUserTitleDisplayNameResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementClientUpdateUserTitleDisplayNameGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementUpdateUserTitleDisplayNameResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementUpdateUserTitleDisplayNameResult> ResultType = ConvertUpdateUserTitleDisplayNameResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerBanUsersAsyncTask::FServerBanUsersAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementBanUsersRequest InRequest,
	const FOnServerBanUsersCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerBanUsersAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerBanUsersAsyncTask::DoWork()
{
	const PFAccountManagementBanUsersRequest RequestType = {
		.bans = ConvertUnrealArrayToPlayfab(Request.bans, ConvertBanRequestToPlayfab),
		.bansCount = (uint32_t)Request.bans.Num(),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num()
	};
	HResult = PFAccountManagementServerBanUsersAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementBanUsersResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerBanUsersAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementServerBanUsersGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementBanUsersResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementBanUsersResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementServerBanUsersGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementBanUsersResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementBanUsersResult> ResultType = ConvertBanUsersResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerDeletePlayerAsyncTask::FServerDeletePlayerAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementDeletePlayerRequest InRequest,
	const FOnServerDeletePlayerCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerDeletePlayerAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerDeletePlayerAsyncTask::DoWork()
{
	const PFAccountManagementDeletePlayerRequest RequestType = {
		.playFabId = ConvertFStringToCharPtr(Request.playFabId)
	};
	HResult = PFAccountManagementServerDeletePlayerAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FServerDeletePlayerAsyncTask::ProcessResults()
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
FServerGetPlayerCombinedInfoAsyncTask::FServerGetPlayerCombinedInfoAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementGetPlayerCombinedInfoRequest InRequest,
	const FOnServerGetPlayerCombinedInfoCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerGetPlayerCombinedInfoAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerGetPlayerCombinedInfoAsyncTask::DoWork()
{
	const PFAccountManagementGetPlayerCombinedInfoRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(Request.infoRequestParameters),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId)
	};
	HResult = PFAccountManagementServerGetPlayerCombinedInfoAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementGetPlayerCombinedInfoResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerGetPlayerCombinedInfoAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementServerGetPlayerCombinedInfoGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementGetPlayerCombinedInfoResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementGetPlayerCombinedInfoResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementServerGetPlayerCombinedInfoGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementGetPlayerCombinedInfoResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementGetPlayerCombinedInfoResult> ResultType = ConvertGetPlayerCombinedInfoResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerGetPlayerProfileAsyncTask::FServerGetPlayerProfileAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementGetPlayerProfileRequest InRequest,
	const FOnServerGetPlayerProfileCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerGetPlayerProfileAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerGetPlayerProfileAsyncTask::DoWork()
{
	const PFAccountManagementGetPlayerProfileRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId),
		.profileConstraints = ConvertPlayerProfileViewConstraintsToPlayfab(Request.profileConstraints)
	};
	HResult = PFAccountManagementServerGetPlayerProfileAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementGetPlayerProfileResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerGetPlayerProfileAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementServerGetPlayerProfileGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementGetPlayerProfileResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementGetPlayerProfileResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementServerGetPlayerProfileGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementGetPlayerProfileResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementGetPlayerProfileResult> ResultType = ConvertGetPlayerProfileResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK
FServerGetPlayFabIDsFromBattleNetAccountIdsAsyncTask::FServerGetPlayFabIDsFromBattleNetAccountIdsAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsRequest InRequest,
	const FOnServerGetPlayFabIDsFromBattleNetAccountIdsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerGetPlayFabIDsFromBattleNetAccountIdsAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerGetPlayFabIDsFromBattleNetAccountIdsAsyncTask::DoWork()
{
	const PFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsRequest RequestType = {
		.battleNetAccountIds = ConvertFStringArrayToPlayfab(Request.battleNetAccountIds),
		.battleNetAccountIdsCount = (uint32_t)Request.battleNetAccountIds.Num()
	};
	HResult = PFAccountManagementServerGetPlayFabIDsFromBattleNetAccountIdsAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerGetPlayFabIDsFromBattleNetAccountIdsAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementServerGetPlayFabIDsFromBattleNetAccountIdsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementServerGetPlayFabIDsFromBattleNetAccountIdsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsResult> ResultType = ConvertGetPlayFabIDsFromBattleNetAccountIdsResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerGetPlayFabIDsFromFacebookIDsAsyncTask::FServerGetPlayFabIDsFromFacebookIDsAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementGetPlayFabIDsFromFacebookIDsRequest InRequest,
	const FOnServerGetPlayFabIDsFromFacebookIDsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerGetPlayFabIDsFromFacebookIDsAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerGetPlayFabIDsFromFacebookIDsAsyncTask::DoWork()
{
	const PFAccountManagementGetPlayFabIDsFromFacebookIDsRequest RequestType = {
		.facebookIDs = ConvertFStringArrayToPlayfab(Request.facebookIDs),
		.facebookIDsCount = (uint32_t)Request.facebookIDs.Num()
	};
	HResult = PFAccountManagementServerGetPlayFabIDsFromFacebookIDsAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromFacebookIDsResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerGetPlayFabIDsFromFacebookIDsAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementServerGetPlayFabIDsFromFacebookIDsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromFacebookIDsResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementGetPlayFabIDsFromFacebookIDsResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementServerGetPlayFabIDsFromFacebookIDsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromFacebookIDsResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromFacebookIDsResult> ResultType = ConvertGetPlayFabIDsFromFacebookIDsResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerGetPlayFabIDsFromFacebookInstantGamesIdsAsyncTask::FServerGetPlayFabIDsFromFacebookInstantGamesIdsAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsRequest InRequest,
	const FOnServerGetPlayFabIDsFromFacebookInstantGamesIdsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerGetPlayFabIDsFromFacebookInstantGamesIdsAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerGetPlayFabIDsFromFacebookInstantGamesIdsAsyncTask::DoWork()
{
	const PFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsRequest RequestType = {
		.facebookInstantGamesIds = ConvertFStringArrayToPlayfab(Request.facebookInstantGamesIds),
		.facebookInstantGamesIdsCount = (uint32_t)Request.facebookInstantGamesIds.Num()
	};
	HResult = PFAccountManagementServerGetPlayFabIDsFromFacebookInstantGamesIdsAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerGetPlayFabIDsFromFacebookInstantGamesIdsAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementServerGetPlayFabIDsFromFacebookInstantGamesIdsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementServerGetPlayFabIDsFromFacebookInstantGamesIdsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsResult> ResultType = ConvertGetPlayFabIDsFromFacebookInstantGamesIdsResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerGetPlayFabIDsFromNintendoServiceAccountIdsAsyncTask::FServerGetPlayFabIDsFromNintendoServiceAccountIdsAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsRequest InRequest,
	const FOnServerGetPlayFabIDsFromNintendoServiceAccountIdsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerGetPlayFabIDsFromNintendoServiceAccountIdsAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerGetPlayFabIDsFromNintendoServiceAccountIdsAsyncTask::DoWork()
{
	const PFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsRequest RequestType = {
		.nintendoAccountIds = ConvertFStringArrayToPlayfab(Request.nintendoAccountIds),
		.nintendoAccountIdsCount = (uint32_t)Request.nintendoAccountIds.Num()
	};
	HResult = PFAccountManagementServerGetPlayFabIDsFromNintendoServiceAccountIdsAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerGetPlayFabIDsFromNintendoServiceAccountIdsAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementServerGetPlayFabIDsFromNintendoServiceAccountIdsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementServerGetPlayFabIDsFromNintendoServiceAccountIdsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsResult> ResultType = ConvertGetPlayFabIDsFromNintendoServiceAccountIdsResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerGetPlayFabIDsFromNintendoSwitchDeviceIdsAsyncTask::FServerGetPlayFabIDsFromNintendoSwitchDeviceIdsAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsRequest InRequest,
	const FOnServerGetPlayFabIDsFromNintendoSwitchDeviceIdsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerGetPlayFabIDsFromNintendoSwitchDeviceIdsAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerGetPlayFabIDsFromNintendoSwitchDeviceIdsAsyncTask::DoWork()
{
	const PFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsRequest RequestType = {
		.nintendoSwitchDeviceIds = ConvertFStringArrayToPlayfab(Request.nintendoSwitchDeviceIds),
		.nintendoSwitchDeviceIdsCount = (uint32_t)Request.nintendoSwitchDeviceIds.Num()
	};
	HResult = PFAccountManagementServerGetPlayFabIDsFromNintendoSwitchDeviceIdsAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerGetPlayFabIDsFromNintendoSwitchDeviceIdsAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementServerGetPlayFabIDsFromNintendoSwitchDeviceIdsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementServerGetPlayFabIDsFromNintendoSwitchDeviceIdsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsResult> ResultType = ConvertGetPlayFabIDsFromNintendoSwitchDeviceIdsResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerGetPlayFabIDsFromPSNAccountIDsAsyncTask::FServerGetPlayFabIDsFromPSNAccountIDsAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementGetPlayFabIDsFromPSNAccountIDsRequest InRequest,
	const FOnServerGetPlayFabIDsFromPSNAccountIDsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerGetPlayFabIDsFromPSNAccountIDsAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerGetPlayFabIDsFromPSNAccountIDsAsyncTask::DoWork()
{
	const PFAccountManagementGetPlayFabIDsFromPSNAccountIDsRequest RequestType = {
		.issuerId = Request.issuerId ? new int32(*Request.issuerId) : nullptr,
		.PSNAccountIDs = ConvertFStringArrayToPlayfab(Request.PSNAccountIDs),
		.PSNAccountIDsCount = (uint32_t)Request.PSNAccountIDs.Num()
	};
	HResult = PFAccountManagementServerGetPlayFabIDsFromPSNAccountIDsAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromPSNAccountIDsResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerGetPlayFabIDsFromPSNAccountIDsAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementServerGetPlayFabIDsFromPSNAccountIDsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromPSNAccountIDsResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementGetPlayFabIDsFromPSNAccountIDsResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementServerGetPlayFabIDsFromPSNAccountIDsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromPSNAccountIDsResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromPSNAccountIDsResult> ResultType = ConvertGetPlayFabIDsFromPSNAccountIDsResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK
FServerGetPlayFabIDsFromPSNOnlineIDsAsyncTask::FServerGetPlayFabIDsFromPSNOnlineIDsAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementGetPlayFabIDsFromPSNOnlineIDsRequest InRequest,
	const FOnServerGetPlayFabIDsFromPSNOnlineIDsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerGetPlayFabIDsFromPSNOnlineIDsAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerGetPlayFabIDsFromPSNOnlineIDsAsyncTask::DoWork()
{
	const PFAccountManagementGetPlayFabIDsFromPSNOnlineIDsRequest RequestType = {
		.issuerId = Request.issuerId ? new int32(*Request.issuerId) : nullptr,
		.PSNOnlineIDs = ConvertFStringArrayToPlayfab(Request.PSNOnlineIDs),
		.PSNOnlineIDsCount = (uint32_t)Request.PSNOnlineIDs.Num()
	};
	HResult = PFAccountManagementServerGetPlayFabIDsFromPSNOnlineIDsAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromPSNOnlineIDsResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerGetPlayFabIDsFromPSNOnlineIDsAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementServerGetPlayFabIDsFromPSNOnlineIDsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromPSNOnlineIDsResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementGetPlayFabIDsFromPSNOnlineIDsResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementServerGetPlayFabIDsFromPSNOnlineIDsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromPSNOnlineIDsResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromPSNOnlineIDsResult> ResultType = ConvertGetPlayFabIDsFromPSNOnlineIDsResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerGetPlayFabIDsFromSteamIDsAsyncTask::FServerGetPlayFabIDsFromSteamIDsAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementGetPlayFabIDsFromSteamIDsRequest InRequest,
	const FOnServerGetPlayFabIDsFromSteamIDsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerGetPlayFabIDsFromSteamIDsAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerGetPlayFabIDsFromSteamIDsAsyncTask::DoWork()
{
	const PFAccountManagementGetPlayFabIDsFromSteamIDsRequest RequestType = {
		.steamStringIDs = ConvertFStringArrayToPlayfab(Request.steamStringIDs),
		.steamStringIDsCount = (uint32_t)Request.steamStringIDs.Num()
	};
	HResult = PFAccountManagementServerGetPlayFabIDsFromSteamIDsAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromSteamIDsResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerGetPlayFabIDsFromSteamIDsAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementServerGetPlayFabIDsFromSteamIDsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromSteamIDsResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementGetPlayFabIDsFromSteamIDsResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementServerGetPlayFabIDsFromSteamIDsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromSteamIDsResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromSteamIDsResult> ResultType = ConvertGetPlayFabIDsFromSteamIDsResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK
FServerGetPlayFabIDsFromSteamNamesAsyncTask::FServerGetPlayFabIDsFromSteamNamesAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementGetPlayFabIDsFromSteamNamesRequest InRequest,
	const FOnServerGetPlayFabIDsFromSteamNamesCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerGetPlayFabIDsFromSteamNamesAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerGetPlayFabIDsFromSteamNamesAsyncTask::DoWork()
{
	const PFAccountManagementGetPlayFabIDsFromSteamNamesRequest RequestType = {
		.steamNames = ConvertFStringArrayToPlayfab(Request.steamNames),
		.steamNamesCount = (uint32_t)Request.steamNames.Num()
	};
	HResult = PFAccountManagementServerGetPlayFabIDsFromSteamNamesAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromSteamNamesResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerGetPlayFabIDsFromSteamNamesAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementServerGetPlayFabIDsFromSteamNamesGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromSteamNamesResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementGetPlayFabIDsFromSteamNamesResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementServerGetPlayFabIDsFromSteamNamesGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromSteamNamesResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromSteamNamesResult> ResultType = ConvertGetPlayFabIDsFromSteamNamesResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerGetPlayFabIDsFromTwitchIDsAsyncTask::FServerGetPlayFabIDsFromTwitchIDsAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementGetPlayFabIDsFromTwitchIDsRequest InRequest,
	const FOnServerGetPlayFabIDsFromTwitchIDsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerGetPlayFabIDsFromTwitchIDsAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerGetPlayFabIDsFromTwitchIDsAsyncTask::DoWork()
{
	const PFAccountManagementGetPlayFabIDsFromTwitchIDsRequest RequestType = {
		.twitchIds = ConvertFStringArrayToPlayfab(Request.twitchIds),
		.twitchIdsCount = (uint32_t)Request.twitchIds.Num()
	};
	HResult = PFAccountManagementServerGetPlayFabIDsFromTwitchIDsAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromTwitchIDsResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerGetPlayFabIDsFromTwitchIDsAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementServerGetPlayFabIDsFromTwitchIDsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromTwitchIDsResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementGetPlayFabIDsFromTwitchIDsResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementServerGetPlayFabIDsFromTwitchIDsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromTwitchIDsResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromTwitchIDsResult> ResultType = ConvertGetPlayFabIDsFromTwitchIDsResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerGetPlayFabIDsFromXboxLiveIDsAsyncTask::FServerGetPlayFabIDsFromXboxLiveIDsAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementGetPlayFabIDsFromXboxLiveIDsRequest InRequest,
	const FOnServerGetPlayFabIDsFromXboxLiveIDsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerGetPlayFabIDsFromXboxLiveIDsAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerGetPlayFabIDsFromXboxLiveIDsAsyncTask::DoWork()
{
	const PFAccountManagementGetPlayFabIDsFromXboxLiveIDsRequest RequestType = {
		.sandbox = ConvertFStringToCharPtr(Request.sandbox),
		.xboxLiveAccountIDs = ConvertFStringArrayToPlayfab(Request.xboxLiveAccountIDs),
		.xboxLiveAccountIDsCount = (uint32_t)Request.xboxLiveAccountIDs.Num()
	};
	HResult = PFAccountManagementServerGetPlayFabIDsFromXboxLiveIDsAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromXboxLiveIDsResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerGetPlayFabIDsFromXboxLiveIDsAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementServerGetPlayFabIDsFromXboxLiveIDsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromXboxLiveIDsResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementGetPlayFabIDsFromXboxLiveIDsResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementServerGetPlayFabIDsFromXboxLiveIDsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementGetPlayFabIDsFromXboxLiveIDsResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromXboxLiveIDsResult> ResultType = ConvertGetPlayFabIDsFromXboxLiveIDsResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerGetServerCustomIDsFromPlayFabIDsAsyncTask::FServerGetServerCustomIDsFromPlayFabIDsAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementGetServerCustomIDsFromPlayFabIDsRequest InRequest,
	const FOnServerGetServerCustomIDsFromPlayFabIDsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerGetServerCustomIDsFromPlayFabIDsAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerGetServerCustomIDsFromPlayFabIDsAsyncTask::DoWork()
{
	const PFAccountManagementGetServerCustomIDsFromPlayFabIDsRequest RequestType = {
		.playFabIDs = ConvertFStringArrayToPlayfab(Request.playFabIDs),
		.playFabIDsCount = (uint32_t)Request.playFabIDs.Num()
	};
	HResult = PFAccountManagementServerGetServerCustomIDsFromPlayFabIDsAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementGetServerCustomIDsFromPlayFabIDsResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerGetServerCustomIDsFromPlayFabIDsAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementServerGetServerCustomIDsFromPlayFabIDsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementGetServerCustomIDsFromPlayFabIDsResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementGetServerCustomIDsFromPlayFabIDsResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementServerGetServerCustomIDsFromPlayFabIDsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementGetServerCustomIDsFromPlayFabIDsResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementGetServerCustomIDsFromPlayFabIDsResult> ResultType = ConvertGetServerCustomIDsFromPlayFabIDsResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerGetUserAccountInfoAsyncTask::FServerGetUserAccountInfoAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementGetUserAccountInfoRequest InRequest,
	const FOnServerGetUserAccountInfoCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerGetUserAccountInfoAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerGetUserAccountInfoAsyncTask::DoWork()
{
	const PFAccountManagementGetUserAccountInfoRequest RequestType = {
		.playFabId = ConvertFStringToCharPtr(Request.playFabId)
	};
	HResult = PFAccountManagementServerGetUserAccountInfoAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementGetUserAccountInfoResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerGetUserAccountInfoAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementServerGetUserAccountInfoGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementGetUserAccountInfoResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementGetUserAccountInfoResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementServerGetUserAccountInfoGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementGetUserAccountInfoResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementGetUserAccountInfoResult> ResultType = ConvertGetUserAccountInfoResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerGetUserBansAsyncTask::FServerGetUserBansAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementGetUserBansRequest InRequest,
	const FOnServerGetUserBansCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerGetUserBansAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerGetUserBansAsyncTask::DoWork()
{
	const PFAccountManagementGetUserBansRequest RequestType = {
		.playFabId = ConvertFStringToCharPtr(Request.playFabId)
	};
	HResult = PFAccountManagementServerGetUserBansAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementGetUserBansResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerGetUserBansAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementServerGetUserBansGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementGetUserBansResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementGetUserBansResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementServerGetUserBansGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementGetUserBansResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementGetUserBansResult> ResultType = ConvertGetUserBansResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK
FServerLinkBattleNetAccountAsyncTask::FServerLinkBattleNetAccountAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementServerLinkBattleNetAccountRequest InRequest,
	const FOnServerLinkBattleNetAccountCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerLinkBattleNetAccountAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerLinkBattleNetAccountAsyncTask::DoWork()
{
	const PFAccountManagementServerLinkBattleNetAccountRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.forceLink = Request.forceLink ? new bool(*Request.forceLink) : nullptr,
		.identityToken = ConvertFStringToCharPtr(Request.identityToken),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId)
	};
	HResult = PFAccountManagementServerLinkBattleNetAccountAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FServerLinkBattleNetAccountAsyncTask::ProcessResults()
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
FServerLinkNintendoServiceAccountAsyncTask::FServerLinkNintendoServiceAccountAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementServerLinkNintendoServiceAccountRequest InRequest,
	const FOnServerLinkNintendoServiceAccountCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerLinkNintendoServiceAccountAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerLinkNintendoServiceAccountAsyncTask::DoWork()
{
	const PFAccountManagementServerLinkNintendoServiceAccountRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.forceLink = Request.forceLink ? new bool(*Request.forceLink) : nullptr,
		.identityToken = ConvertFStringToCharPtr(Request.identityToken),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId)
	};
	HResult = PFAccountManagementServerLinkNintendoServiceAccountAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FServerLinkNintendoServiceAccountAsyncTask::ProcessResults()
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
FServerLinkNintendoServiceAccountSubjectAsyncTask::FServerLinkNintendoServiceAccountSubjectAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementLinkNintendoServiceAccountSubjectRequest InRequest,
	const FOnServerLinkNintendoServiceAccountSubjectCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerLinkNintendoServiceAccountSubjectAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerLinkNintendoServiceAccountSubjectAsyncTask::DoWork()
{
	const PFAccountManagementLinkNintendoServiceAccountSubjectRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.forceLink = Request.forceLink ? new bool(*Request.forceLink) : nullptr,
		.playFabId = ConvertFStringToCharPtr(Request.playFabId),
		.subject = ConvertFStringToCharPtr(Request.subject)
	};
	HResult = PFAccountManagementServerLinkNintendoServiceAccountSubjectAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FServerLinkNintendoServiceAccountSubjectAsyncTask::ProcessResults()
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
FServerLinkNintendoSwitchDeviceIdAsyncTask::FServerLinkNintendoSwitchDeviceIdAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementServerLinkNintendoSwitchDeviceIdRequest InRequest,
	const FOnServerLinkNintendoSwitchDeviceIdCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerLinkNintendoSwitchDeviceIdAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerLinkNintendoSwitchDeviceIdAsyncTask::DoWork()
{
	const PFAccountManagementServerLinkNintendoSwitchDeviceIdRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.forceLink = Request.forceLink ? new bool(*Request.forceLink) : nullptr,
		.nintendoSwitchDeviceId = ConvertFStringToCharPtr(Request.nintendoSwitchDeviceId),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId)
	};
	HResult = PFAccountManagementServerLinkNintendoSwitchDeviceIdAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FServerLinkNintendoSwitchDeviceIdAsyncTask::ProcessResults()
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
FServerLinkPSNAccountAsyncTask::FServerLinkPSNAccountAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementServerLinkPSNAccountRequest InRequest,
	const FOnServerLinkPSNAccountCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerLinkPSNAccountAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerLinkPSNAccountAsyncTask::DoWork()
{
	const PFAccountManagementServerLinkPSNAccountRequest RequestType = {
		.authCode = ConvertFStringToCharPtr(Request.authCode),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.forceLink = Request.forceLink ? new bool(*Request.forceLink) : nullptr,
		.issuerId = Request.issuerId ? new int32(*Request.issuerId) : nullptr,
		.playFabId = ConvertFStringToCharPtr(Request.playFabId),
		.redirectUri = ConvertFStringToCharPtr(Request.redirectUri)
	};
	HResult = PFAccountManagementServerLinkPSNAccountAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FServerLinkPSNAccountAsyncTask::ProcessResults()
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

#if HC_PLATFORM == HC_PLATFORM_GDK
FServerLinkPSNIdAsyncTask::FServerLinkPSNIdAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementLinkPSNIdRequest InRequest,
	const FOnServerLinkPSNIdCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerLinkPSNIdAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerLinkPSNIdAsyncTask::DoWork()
{
	const PFAccountManagementLinkPSNIdRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.forceLink = Request.forceLink ? new bool(*Request.forceLink) : nullptr,
		.issuerId = Request.issuerId ? new int32(*Request.issuerId) : nullptr,
		.playFabId = ConvertFStringToCharPtr(Request.playFabId),
		.PSNUserId = ConvertFStringToCharPtr(Request.PSNUserId)
	};
	HResult = PFAccountManagementServerLinkPSNIdAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FServerLinkPSNIdAsyncTask::ProcessResults()
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
FServerLinkServerCustomIdAsyncTask::FServerLinkServerCustomIdAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementLinkServerCustomIdRequest InRequest,
	const FOnServerLinkServerCustomIdCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerLinkServerCustomIdAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerLinkServerCustomIdAsyncTask::DoWork()
{
	const PFAccountManagementLinkServerCustomIdRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.forceLink = Request.forceLink ? new bool(*Request.forceLink) : nullptr,
		.playFabId = ConvertFStringToCharPtr(Request.playFabId),
		.serverCustomId = ConvertFStringToCharPtr(Request.serverCustomId)
	};
	HResult = PFAccountManagementServerLinkServerCustomIdAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FServerLinkServerCustomIdAsyncTask::ProcessResults()
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
FServerLinkSteamIdAsyncTask::FServerLinkSteamIdAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementLinkSteamIdRequest InRequest,
	const FOnServerLinkSteamIdCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerLinkSteamIdAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerLinkSteamIdAsyncTask::DoWork()
{
	const PFAccountManagementLinkSteamIdRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.forceLink = Request.forceLink ? new bool(*Request.forceLink) : nullptr,
		.playFabId = ConvertFStringToCharPtr(Request.playFabId),
		.steamId = ConvertFStringToCharPtr(Request.steamId)
	};
	HResult = PFAccountManagementServerLinkSteamIdAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FServerLinkSteamIdAsyncTask::ProcessResults()
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
FServerLinkXboxAccountAsyncTask::FServerLinkXboxAccountAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementServerLinkXboxAccountRequest InRequest,
	const FOnServerLinkXboxAccountCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerLinkXboxAccountAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerLinkXboxAccountAsyncTask::DoWork()
{
	const PFAccountManagementServerLinkXboxAccountRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.forceLink = Request.forceLink ? new bool(*Request.forceLink) : nullptr,
		.playFabId = ConvertFStringToCharPtr(Request.playFabId),
		.xboxToken = ConvertFStringToCharPtr(Request.xboxToken)
	};
	HResult = PFAccountManagementServerLinkXboxAccountAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FServerLinkXboxAccountAsyncTask::ProcessResults()
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
FServerRevokeAllBansForUserAsyncTask::FServerRevokeAllBansForUserAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementRevokeAllBansForUserRequest InRequest,
	const FOnServerRevokeAllBansForUserCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerRevokeAllBansForUserAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerRevokeAllBansForUserAsyncTask::DoWork()
{
	const PFAccountManagementRevokeAllBansForUserRequest RequestType = {
		.playFabId = ConvertFStringToCharPtr(Request.playFabId)
	};
	HResult = PFAccountManagementServerRevokeAllBansForUserAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementRevokeAllBansForUserResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerRevokeAllBansForUserAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementServerRevokeAllBansForUserGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementRevokeAllBansForUserResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementRevokeAllBansForUserResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementServerRevokeAllBansForUserGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementRevokeAllBansForUserResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementRevokeAllBansForUserResult> ResultType = ConvertRevokeAllBansForUserResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerRevokeBansAsyncTask::FServerRevokeBansAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementRevokeBansRequest InRequest,
	const FOnServerRevokeBansCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerRevokeBansAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerRevokeBansAsyncTask::DoWork()
{
	const PFAccountManagementRevokeBansRequest RequestType = {
		.banIds = ConvertFStringArrayToPlayfab(Request.banIds),
		.banIdsCount = (uint32_t)Request.banIds.Num()
	};
	HResult = PFAccountManagementServerRevokeBansAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementRevokeBansResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerRevokeBansAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementServerRevokeBansGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementRevokeBansResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementRevokeBansResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementServerRevokeBansGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementRevokeBansResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementRevokeBansResult> ResultType = ConvertRevokeBansResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerSendCustomAccountRecoveryEmailAsyncTask::FServerSendCustomAccountRecoveryEmailAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementSendCustomAccountRecoveryEmailRequest InRequest,
	const FOnServerSendCustomAccountRecoveryEmailCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerSendCustomAccountRecoveryEmailAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerSendCustomAccountRecoveryEmailAsyncTask::DoWork()
{
	const PFAccountManagementSendCustomAccountRecoveryEmailRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.email = ConvertFStringToCharPtr(Request.email),
		.emailTemplateId = ConvertFStringToCharPtr(Request.emailTemplateId),
		.username = ConvertFStringToCharPtr(Request.username)
	};
	HResult = PFAccountManagementServerSendCustomAccountRecoveryEmailAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FServerSendCustomAccountRecoveryEmailAsyncTask::ProcessResults()
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
FServerSendEmailFromTemplateAsyncTask::FServerSendEmailFromTemplateAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementSendEmailFromTemplateRequest InRequest,
	const FOnServerSendEmailFromTemplateCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerSendEmailFromTemplateAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerSendEmailFromTemplateAsyncTask::DoWork()
{
	const PFAccountManagementSendEmailFromTemplateRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.emailTemplateId = ConvertFStringToCharPtr(Request.emailTemplateId),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId)
	};
	HResult = PFAccountManagementServerSendEmailFromTemplateAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FServerSendEmailFromTemplateAsyncTask::ProcessResults()
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

#if HC_PLATFORM == HC_PLATFORM_GDK
FServerUnlinkBattleNetAccountAsyncTask::FServerUnlinkBattleNetAccountAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementServerUnlinkBattleNetAccountRequest InRequest,
	const FOnServerUnlinkBattleNetAccountCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerUnlinkBattleNetAccountAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerUnlinkBattleNetAccountAsyncTask::DoWork()
{
	const PFAccountManagementServerUnlinkBattleNetAccountRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId)
	};
	HResult = PFAccountManagementServerUnlinkBattleNetAccountAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FServerUnlinkBattleNetAccountAsyncTask::ProcessResults()
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
FServerUnlinkNintendoServiceAccountAsyncTask::FServerUnlinkNintendoServiceAccountAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementServerUnlinkNintendoServiceAccountRequest InRequest,
	const FOnServerUnlinkNintendoServiceAccountCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerUnlinkNintendoServiceAccountAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerUnlinkNintendoServiceAccountAsyncTask::DoWork()
{
	const PFAccountManagementServerUnlinkNintendoServiceAccountRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId)
	};
	HResult = PFAccountManagementServerUnlinkNintendoServiceAccountAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FServerUnlinkNintendoServiceAccountAsyncTask::ProcessResults()
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
FServerUnlinkNintendoSwitchDeviceIdAsyncTask::FServerUnlinkNintendoSwitchDeviceIdAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementServerUnlinkNintendoSwitchDeviceIdRequest InRequest,
	const FOnServerUnlinkNintendoSwitchDeviceIdCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerUnlinkNintendoSwitchDeviceIdAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerUnlinkNintendoSwitchDeviceIdAsyncTask::DoWork()
{
	const PFAccountManagementServerUnlinkNintendoSwitchDeviceIdRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.nintendoSwitchDeviceId = ConvertFStringToCharPtr(Request.nintendoSwitchDeviceId),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId)
	};
	HResult = PFAccountManagementServerUnlinkNintendoSwitchDeviceIdAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FServerUnlinkNintendoSwitchDeviceIdAsyncTask::ProcessResults()
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
FServerUnlinkPSNAccountAsyncTask::FServerUnlinkPSNAccountAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementServerUnlinkPSNAccountRequest InRequest,
	const FOnServerUnlinkPSNAccountCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerUnlinkPSNAccountAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerUnlinkPSNAccountAsyncTask::DoWork()
{
	const PFAccountManagementServerUnlinkPSNAccountRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId)
	};
	HResult = PFAccountManagementServerUnlinkPSNAccountAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FServerUnlinkPSNAccountAsyncTask::ProcessResults()
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
FServerUnlinkServerCustomIdAsyncTask::FServerUnlinkServerCustomIdAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementUnlinkServerCustomIdRequest InRequest,
	const FOnServerUnlinkServerCustomIdCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerUnlinkServerCustomIdAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerUnlinkServerCustomIdAsyncTask::DoWork()
{
	const PFAccountManagementUnlinkServerCustomIdRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId),
		.serverCustomId = ConvertFStringToCharPtr(Request.serverCustomId)
	};
	HResult = PFAccountManagementServerUnlinkServerCustomIdAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FServerUnlinkServerCustomIdAsyncTask::ProcessResults()
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
FServerUnlinkSteamIdAsyncTask::FServerUnlinkSteamIdAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementUnlinkSteamIdRequest InRequest,
	const FOnServerUnlinkSteamIdCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerUnlinkSteamIdAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerUnlinkSteamIdAsyncTask::DoWork()
{
	const PFAccountManagementUnlinkSteamIdRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId)
	};
	HResult = PFAccountManagementServerUnlinkSteamIdAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FServerUnlinkSteamIdAsyncTask::ProcessResults()
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
FServerUnlinkXboxAccountAsyncTask::FServerUnlinkXboxAccountAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementServerUnlinkXboxAccountRequest InRequest,
	const FOnServerUnlinkXboxAccountCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerUnlinkXboxAccountAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerUnlinkXboxAccountAsyncTask::DoWork()
{
	const PFAccountManagementServerUnlinkXboxAccountRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId)
	};
	HResult = PFAccountManagementServerUnlinkXboxAccountAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FServerUnlinkXboxAccountAsyncTask::ProcessResults()
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
FServerUpdateAvatarUrlAsyncTask::FServerUpdateAvatarUrlAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementServerUpdateAvatarUrlRequest InRequest,
	const FOnServerUpdateAvatarUrlCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerUpdateAvatarUrlAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerUpdateAvatarUrlAsyncTask::DoWork()
{
	const PFAccountManagementServerUpdateAvatarUrlRequest RequestType = {
		.imageUrl = ConvertFStringToCharPtr(Request.imageUrl),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId)
	};
	HResult = PFAccountManagementServerUpdateAvatarUrlAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(ErrorMessage, false);
	}
};

void FServerUpdateAvatarUrlAsyncTask::ProcessResults()
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
FServerUpdateBansAsyncTask::FServerUpdateBansAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementUpdateBansRequest InRequest,
	const FOnServerUpdateBansCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerUpdateBansAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerUpdateBansAsyncTask::DoWork()
{
	const PFAccountManagementUpdateBansRequest RequestType = {
		.bans = ConvertUnrealArrayToPlayfab(Request.bans, ConvertUpdateBanRequestToPlayfab),
		.bansCount = (uint32_t)Request.bans.Num()
	};
	HResult = PFAccountManagementServerUpdateBansAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementUpdateBansResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerUpdateBansAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementServerUpdateBansGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementUpdateBansResult{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementUpdateBansResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementServerUpdateBansGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementUpdateBansResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementUpdateBansResult> ResultType = ConvertUpdateBansResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FGetTitlePlayersFromXboxLiveIDsAsyncTask::FGetTitlePlayersFromXboxLiveIDsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementGetTitlePlayersFromXboxLiveIDsRequest InRequest,
	const FOnGetTitlePlayersFromXboxLiveIDsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FGetTitlePlayersFromXboxLiveIDsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FGetTitlePlayersFromXboxLiveIDsAsyncTask::DoWork()
{
	const PFAccountManagementGetTitlePlayersFromXboxLiveIDsRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.sandbox = ConvertFStringToCharPtr(Request.sandbox),
		.titleId = ConvertFStringToCharPtr(Request.titleId),
		.xboxLiveIds = ConvertFStringArrayToPlayfab(Request.xboxLiveIds),
		.xboxLiveIdsCount = (uint32_t)Request.xboxLiveIds.Num()
	};
	HResult = PFAccountManagementGetTitlePlayersFromXboxLiveIDsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementGetTitlePlayersFromProviderIDsResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FGetTitlePlayersFromXboxLiveIDsAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementGetTitlePlayersFromXboxLiveIDsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementGetTitlePlayersFromProviderIDsResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementGetTitlePlayersFromProviderIDsResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementGetTitlePlayersFromXboxLiveIDsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementGetTitlePlayersFromProviderIDsResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementGetTitlePlayersFromProviderIDsResponse> ResultType = ConvertGetTitlePlayersFromProviderIDsResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

FSetDisplayNameAsyncTask::FSetDisplayNameAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementSetDisplayNameRequest InRequest,
	const FOnSetDisplayNameCompleted& InDelegate)
	: FXAsyncTask(TEXT("FSetDisplayNameAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FSetDisplayNameAsyncTask::DoWork()
{
	const PFAccountManagementSetDisplayNameRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.displayName = ConvertFStringToCharPtr(Request.displayName),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.expectedVersion = Request.expectedVersion ? new int32(*Request.expectedVersion) : nullptr
	};
	HResult = PFAccountManagementSetDisplayNameAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("DoWork failure");
		Delegate.Execute(FPFAccountManagementSetDisplayNameResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FSetDisplayNameAsyncTask::ProcessResults()
{
	uint64 ResultSize = 0;
	HResult = PFAccountManagementSetDisplayNameGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFAccountManagementSetDisplayNameResponse{ .ErrorMessage = FString("GetResultSize failure") }, false);
		return;
	}

	PFAccountManagementSetDisplayNameResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFAccountManagementSetDisplayNameGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString("GetResult failure");
		Delegate.Execute(FPFAccountManagementSetDisplayNameResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFAccountManagementSetDisplayNameResponse> ResultType = ConvertSetDisplayNameResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

