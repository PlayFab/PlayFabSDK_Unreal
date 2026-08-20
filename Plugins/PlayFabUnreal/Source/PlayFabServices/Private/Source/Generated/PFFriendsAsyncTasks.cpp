// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFFriendsAsyncTasks.h"

FClientAddFriendAsyncTask::FClientAddFriendAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFFriendsClientAddFriendRequest InRequest,
	const FOnClientAddFriendCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientAddFriendAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientAddFriendAsyncTask::DoWork()
{
	const PFFriendsClientAddFriendRequest RequestType = {
		.friendEmail = ConvertFStringToCharPtr(Request.friendEmail),
		.friendPlayFabId = ConvertFStringToCharPtr(Request.friendPlayFabId),
		.friendTitleDisplayName = ConvertFStringToCharPtr(Request.friendTitleDisplayName),
		.friendUsername = ConvertFStringToCharPtr(Request.friendUsername)
	};
	HResult = PFFriendsClientAddFriendAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFFriendsAddFriendResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientAddFriendAsyncTask::ProcessResults()
{
	PFFriendsAddFriendResult Result = {};
	HResult = PFFriendsClientAddFriendGetResult(*mAsyncBlock, &Result);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("GetResult failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFFriendsAddFriendResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFFriendsAddFriendResult> ResultType = ConvertAddFriendResultToUnreal(&Result);

	Delegate.Execute(*ResultType, true);
}

FClientGetFriendsListAsyncTask::FClientGetFriendsListAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFFriendsClientGetFriendsListRequest InRequest,
	const FOnClientGetFriendsListCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientGetFriendsListAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientGetFriendsListAsyncTask::DoWork()
{
	const PFFriendsClientGetFriendsListRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.externalPlatformFriends = new PFFriendsExternalFriendSources(ConvertExternalFriendSourcesToPlayfab(Request.externalPlatformFriends)),
		.profileConstraints = ConvertPlayerProfileViewConstraintsToPlayfab(Request.profileConstraints),
#if defined(PF_GDK_AVAILABLE)
		.user = Request.user
#else
		.xboxToken = ConvertFStringToCharPtr(Request.xboxToken)
#endif
	};
	HResult = PFFriendsClientGetFriendsListAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFFriendsGetFriendsListResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FClientGetFriendsListAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFFriendsClientGetFriendsListGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFFriendsGetFriendsListResult{ .ErrorMessage = FString::Printf(TEXT("GetResultSize failure: 0x%08X"), static_cast<uint32>(HResult)) }, false);
		return;
	}

	PFFriendsGetFriendsListResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFFriendsClientGetFriendsListGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("GetResult failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFFriendsGetFriendsListResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFFriendsGetFriendsListResult> ResultType = ConvertGetFriendsListResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FClientRemoveFriendAsyncTask::FClientRemoveFriendAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFFriendsClientRemoveFriendRequest InRequest,
	const FOnClientRemoveFriendCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientRemoveFriendAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientRemoveFriendAsyncTask::DoWork()
{
	const PFFriendsClientRemoveFriendRequest RequestType = {
		.friendPlayFabId = ConvertFStringToCharPtr(Request.friendPlayFabId)
	};
	HResult = PFFriendsClientRemoveFriendAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientRemoveFriendAsyncTask::ProcessResults()
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

FClientSetFriendTagsAsyncTask::FClientSetFriendTagsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFFriendsClientSetFriendTagsRequest InRequest,
	const FOnClientSetFriendTagsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FClientSetFriendTagsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FClientSetFriendTagsAsyncTask::DoWork()
{
	const PFFriendsClientSetFriendTagsRequest RequestType = {
		.friendPlayFabId = ConvertFStringToCharPtr(Request.friendPlayFabId),
		.tags = ConvertFStringArrayToPlayfab(Request.tags),
		.tagsCount = (uint32_t)Request.tags.Num()
	};
	HResult = PFFriendsClientSetFriendTagsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(ErrorMessage, false);
	}
};

void FClientSetFriendTagsAsyncTask::ProcessResults()
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

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerAddFriendAsyncTask::FServerAddFriendAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFFriendsServerAddFriendRequest InRequest,
	const FOnServerAddFriendCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerAddFriendAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerAddFriendAsyncTask::DoWork()
{
	const PFFriendsServerAddFriendRequest RequestType = {
		.friendEmail = ConvertFStringToCharPtr(Request.friendEmail),
		.friendPlayFabId = ConvertFStringToCharPtr(Request.friendPlayFabId),
		.friendTitleDisplayName = ConvertFStringToCharPtr(Request.friendTitleDisplayName),
		.friendUsername = ConvertFStringToCharPtr(Request.friendUsername),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId)
	};
	HResult = PFFriendsServerAddFriendAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(ErrorMessage, false);
	}
};

void FServerAddFriendAsyncTask::ProcessResults()
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
FServerGetFriendsListAsyncTask::FServerGetFriendsListAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFFriendsServerGetFriendsListRequest InRequest,
	const FOnServerGetFriendsListCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerGetFriendsListAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerGetFriendsListAsyncTask::DoWork()
{
	const PFFriendsServerGetFriendsListRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.externalPlatformFriends = new PFFriendsExternalFriendSources(ConvertExternalFriendSourcesToPlayfab(Request.externalPlatformFriends)),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId),
		.profileConstraints = ConvertPlayerProfileViewConstraintsToPlayfab(Request.profileConstraints),
		.xboxToken = ConvertFStringToCharPtr(Request.xboxToken)
	};
	HResult = PFFriendsServerGetFriendsListAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFFriendsGetFriendsListResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FServerGetFriendsListAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFFriendsServerGetFriendsListGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFFriendsGetFriendsListResult{ .ErrorMessage = FString::Printf(TEXT("GetResultSize failure: 0x%08X"), static_cast<uint32>(HResult)) }, false);
		return;
	}

	PFFriendsGetFriendsListResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFFriendsServerGetFriendsListGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("GetResult failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFFriendsGetFriendsListResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFFriendsGetFriendsListResult> ResultType = ConvertGetFriendsListResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
FServerRemoveFriendAsyncTask::FServerRemoveFriendAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFFriendsServerRemoveFriendRequest InRequest,
	const FOnServerRemoveFriendCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerRemoveFriendAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerRemoveFriendAsyncTask::DoWork()
{
	const PFFriendsServerRemoveFriendRequest RequestType = {
		.friendPlayFabId = ConvertFStringToCharPtr(Request.friendPlayFabId),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId)
	};
	HResult = PFFriendsServerRemoveFriendAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(ErrorMessage, false);
	}
};

void FServerRemoveFriendAsyncTask::ProcessResults()
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
FServerSetFriendTagsAsyncTask::FServerSetFriendTagsAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFFriendsServerSetFriendTagsRequest InRequest,
	const FOnServerSetFriendTagsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FServerSetFriendTagsAsyncTask")),
	TitleEntityHandle(TitleEntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FServerSetFriendTagsAsyncTask::DoWork()
{
	const PFFriendsServerSetFriendTagsRequest RequestType = {
		.friendPlayFabId = ConvertFStringToCharPtr(Request.friendPlayFabId),
		.playFabId = ConvertFStringToCharPtr(Request.playFabId),
		.tags = ConvertFStringArrayToPlayfab(Request.tags),
		.tagsCount = (uint32_t)Request.tags.Num()
	};
	HResult = PFFriendsServerSetFriendTagsAsync(TitleEntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(ErrorMessage, false);
	}
};

void FServerSetFriendTagsAsyncTask::ProcessResults()
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

