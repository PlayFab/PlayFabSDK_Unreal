// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFGroupsAsyncTasks.h"

FAcceptGroupApplicationAsyncTask::FAcceptGroupApplicationAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsAcceptGroupApplicationRequest InRequest,
	const FOnAcceptGroupApplicationCompleted& InDelegate)
	: FXAsyncTask(TEXT("FAcceptGroupApplicationAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FAcceptGroupApplicationAsyncTask::DoWork()
{
	const PFGroupsAcceptGroupApplicationRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.group = ConvertEntityKeyToPlayfab(Request.group)
	};
	HResult = PFGroupsAcceptGroupApplicationAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(ErrorMessage, false);
	}
};

void FAcceptGroupApplicationAsyncTask::ProcessResults()
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

FAcceptGroupInvitationAsyncTask::FAcceptGroupInvitationAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsAcceptGroupInvitationRequest InRequest,
	const FOnAcceptGroupInvitationCompleted& InDelegate)
	: FXAsyncTask(TEXT("FAcceptGroupInvitationAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FAcceptGroupInvitationAsyncTask::DoWork()
{
	const PFGroupsAcceptGroupInvitationRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.group = ConvertEntityKeyToPlayfab(Request.group)
	};
	HResult = PFGroupsAcceptGroupInvitationAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(ErrorMessage, false);
	}
};

void FAcceptGroupInvitationAsyncTask::ProcessResults()
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

FAddMembersAsyncTask::FAddMembersAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsAddMembersRequest InRequest,
	const FOnAddMembersCompleted& InDelegate)
	: FXAsyncTask(TEXT("FAddMembersAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FAddMembersAsyncTask::DoWork()
{
	const PFGroupsAddMembersRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.group = ConvertEntityKeyToPlayfab(Request.group),
		.members = ConvertUnrealArrayToPlayfab<PFEntityKey, FPFEntityKey>(Request.members, ConvertEntityKeyToPlayfab),
		.membersCount = (uint32_t)Request.members.Num(),
		.roleId = ConvertFStringToCharPtr(Request.roleId)
	};
	HResult = PFGroupsAddMembersAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(ErrorMessage, false);
	}
};

void FAddMembersAsyncTask::ProcessResults()
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

FApplyToGroupAsyncTask::FApplyToGroupAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsApplyToGroupRequest InRequest,
	const FOnApplyToGroupCompleted& InDelegate)
	: FXAsyncTask(TEXT("FApplyToGroupAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FApplyToGroupAsyncTask::DoWork()
{
	const PFGroupsApplyToGroupRequest RequestType = {
		.autoAcceptOutstandingInvite = Request.autoAcceptOutstandingInvite ? new bool(*Request.autoAcceptOutstandingInvite) : nullptr,
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.group = ConvertEntityKeyToPlayfab(Request.group)
	};
	HResult = PFGroupsApplyToGroupAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFGroupsApplyToGroupResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FApplyToGroupAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFGroupsApplyToGroupGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFGroupsApplyToGroupResponse{ .ErrorMessage = FString::Printf(TEXT("GetResultSize failure: 0x%08X"), static_cast<uint32>(HResult)) }, false);
		return;
	}

	PFGroupsApplyToGroupResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFGroupsApplyToGroupGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("GetResult failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFGroupsApplyToGroupResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFGroupsApplyToGroupResponse> ResultType = ConvertApplyToGroupResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FBlockEntityAsyncTask::FBlockEntityAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsBlockEntityRequest InRequest,
	const FOnBlockEntityCompleted& InDelegate)
	: FXAsyncTask(TEXT("FBlockEntityAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FBlockEntityAsyncTask::DoWork()
{
	const PFGroupsBlockEntityRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.group = ConvertEntityKeyToPlayfab(Request.group)
	};
	HResult = PFGroupsBlockEntityAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(ErrorMessage, false);
	}
};

void FBlockEntityAsyncTask::ProcessResults()
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

FChangeMemberRoleAsyncTask::FChangeMemberRoleAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsChangeMemberRoleRequest InRequest,
	const FOnChangeMemberRoleCompleted& InDelegate)
	: FXAsyncTask(TEXT("FChangeMemberRoleAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FChangeMemberRoleAsyncTask::DoWork()
{
	const PFGroupsChangeMemberRoleRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.destinationRoleId = ConvertFStringToCharPtr(Request.destinationRoleId),
		.group = ConvertEntityKeyToPlayfab(Request.group),
		.members = ConvertUnrealArrayToPlayfab<PFEntityKey, FPFEntityKey>(Request.members, ConvertEntityKeyToPlayfab),
		.membersCount = (uint32_t)Request.members.Num(),
		.originRoleId = ConvertFStringToCharPtr(Request.originRoleId)
	};
	HResult = PFGroupsChangeMemberRoleAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(ErrorMessage, false);
	}
};

void FChangeMemberRoleAsyncTask::ProcessResults()
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

FCreateGroupAsyncTask::FCreateGroupAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsCreateGroupRequest InRequest,
	const FOnCreateGroupCompleted& InDelegate)
	: FXAsyncTask(TEXT("FCreateGroupAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FCreateGroupAsyncTask::DoWork()
{
	const PFGroupsCreateGroupRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.groupName = ConvertFStringToCharPtr(Request.groupName)
	};
	HResult = PFGroupsCreateGroupAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFGroupsCreateGroupResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FCreateGroupAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFGroupsCreateGroupGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFGroupsCreateGroupResponse{ .ErrorMessage = FString::Printf(TEXT("GetResultSize failure: 0x%08X"), static_cast<uint32>(HResult)) }, false);
		return;
	}

	PFGroupsCreateGroupResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFGroupsCreateGroupGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("GetResult failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFGroupsCreateGroupResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFGroupsCreateGroupResponse> ResultType = ConvertCreateGroupResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FCreateRoleAsyncTask::FCreateRoleAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsCreateGroupRoleRequest InRequest,
	const FOnCreateRoleCompleted& InDelegate)
	: FXAsyncTask(TEXT("FCreateRoleAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FCreateRoleAsyncTask::DoWork()
{
	const PFGroupsCreateGroupRoleRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.group = ConvertEntityKeyToPlayfab(Request.group),
		.roleId = ConvertFStringToCharPtr(Request.roleId),
		.roleName = ConvertFStringToCharPtr(Request.roleName)
	};
	HResult = PFGroupsCreateRoleAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFGroupsCreateGroupRoleResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FCreateRoleAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFGroupsCreateRoleGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFGroupsCreateGroupRoleResponse{ .ErrorMessage = FString::Printf(TEXT("GetResultSize failure: 0x%08X"), static_cast<uint32>(HResult)) }, false);
		return;
	}

	PFGroupsCreateGroupRoleResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFGroupsCreateRoleGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("GetResult failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFGroupsCreateGroupRoleResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFGroupsCreateGroupRoleResponse> ResultType = ConvertCreateGroupRoleResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FDeleteGroupAsyncTask::FDeleteGroupAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsDeleteGroupRequest InRequest,
	const FOnDeleteGroupCompleted& InDelegate)
	: FXAsyncTask(TEXT("FDeleteGroupAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FDeleteGroupAsyncTask::DoWork()
{
	const PFGroupsDeleteGroupRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.group = ConvertEntityKeyToPlayfab(Request.group)
	};
	HResult = PFGroupsDeleteGroupAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(ErrorMessage, false);
	}
};

void FDeleteGroupAsyncTask::ProcessResults()
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

FDeleteRoleAsyncTask::FDeleteRoleAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsDeleteRoleRequest InRequest,
	const FOnDeleteRoleCompleted& InDelegate)
	: FXAsyncTask(TEXT("FDeleteRoleAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FDeleteRoleAsyncTask::DoWork()
{
	const PFGroupsDeleteRoleRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.group = ConvertEntityKeyToPlayfab(Request.group),
		.roleId = ConvertFStringToCharPtr(Request.roleId)
	};
	HResult = PFGroupsDeleteRoleAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(ErrorMessage, false);
	}
};

void FDeleteRoleAsyncTask::ProcessResults()
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

FGetGroupAsyncTask::FGetGroupAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsGetGroupRequest InRequest,
	const FOnGetGroupCompleted& InDelegate)
	: FXAsyncTask(TEXT("FGetGroupAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FGetGroupAsyncTask::DoWork()
{
	const PFGroupsGetGroupRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.group = ConvertEntityKeyToPlayfab(Request.group),
		.groupName = ConvertFStringToCharPtr(Request.groupName)
	};
	HResult = PFGroupsGetGroupAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFGroupsGetGroupResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FGetGroupAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFGroupsGetGroupGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFGroupsGetGroupResponse{ .ErrorMessage = FString::Printf(TEXT("GetResultSize failure: 0x%08X"), static_cast<uint32>(HResult)) }, false);
		return;
	}

	PFGroupsGetGroupResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFGroupsGetGroupGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("GetResult failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFGroupsGetGroupResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFGroupsGetGroupResponse> ResultType = ConvertGetGroupResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FInviteToGroupAsyncTask::FInviteToGroupAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsInviteToGroupRequest InRequest,
	const FOnInviteToGroupCompleted& InDelegate)
	: FXAsyncTask(TEXT("FInviteToGroupAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FInviteToGroupAsyncTask::DoWork()
{
	const PFGroupsInviteToGroupRequest RequestType = {
		.autoAcceptOutstandingApplication = Request.autoAcceptOutstandingApplication ? new bool(*Request.autoAcceptOutstandingApplication) : nullptr,
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.group = ConvertEntityKeyToPlayfab(Request.group),
		.roleId = ConvertFStringToCharPtr(Request.roleId)
	};
	HResult = PFGroupsInviteToGroupAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFGroupsInviteToGroupResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FInviteToGroupAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFGroupsInviteToGroupGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFGroupsInviteToGroupResponse{ .ErrorMessage = FString::Printf(TEXT("GetResultSize failure: 0x%08X"), static_cast<uint32>(HResult)) }, false);
		return;
	}

	PFGroupsInviteToGroupResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFGroupsInviteToGroupGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("GetResult failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFGroupsInviteToGroupResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFGroupsInviteToGroupResponse> ResultType = ConvertInviteToGroupResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FIsMemberAsyncTask::FIsMemberAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsIsMemberRequest InRequest,
	const FOnIsMemberCompleted& InDelegate)
	: FXAsyncTask(TEXT("FIsMemberAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FIsMemberAsyncTask::DoWork()
{
	const PFGroupsIsMemberRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.group = ConvertEntityKeyToPlayfab(Request.group),
		.roleId = ConvertFStringToCharPtr(Request.roleId)
	};
	HResult = PFGroupsIsMemberAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFGroupsIsMemberResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FIsMemberAsyncTask::ProcessResults()
{
	PFGroupsIsMemberResponse Result = {};
	HResult = PFGroupsIsMemberGetResult(*mAsyncBlock, &Result);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("GetResult failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFGroupsIsMemberResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFGroupsIsMemberResponse> ResultType = ConvertIsMemberResponseToUnreal(&Result);

	Delegate.Execute(*ResultType, true);
}

FListGroupApplicationsAsyncTask::FListGroupApplicationsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsListGroupApplicationsRequest InRequest,
	const FOnListGroupApplicationsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FListGroupApplicationsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FListGroupApplicationsAsyncTask::DoWork()
{
	const PFGroupsListGroupApplicationsRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.group = ConvertEntityKeyToPlayfab(Request.group)
	};
	HResult = PFGroupsListGroupApplicationsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFGroupsListGroupApplicationsResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FListGroupApplicationsAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFGroupsListGroupApplicationsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFGroupsListGroupApplicationsResponse{ .ErrorMessage = FString::Printf(TEXT("GetResultSize failure: 0x%08X"), static_cast<uint32>(HResult)) }, false);
		return;
	}

	PFGroupsListGroupApplicationsResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFGroupsListGroupApplicationsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("GetResult failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFGroupsListGroupApplicationsResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFGroupsListGroupApplicationsResponse> ResultType = ConvertListGroupApplicationsResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FListGroupBlocksAsyncTask::FListGroupBlocksAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsListGroupBlocksRequest InRequest,
	const FOnListGroupBlocksCompleted& InDelegate)
	: FXAsyncTask(TEXT("FListGroupBlocksAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FListGroupBlocksAsyncTask::DoWork()
{
	const PFGroupsListGroupBlocksRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.group = ConvertEntityKeyToPlayfab(Request.group)
	};
	HResult = PFGroupsListGroupBlocksAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFGroupsListGroupBlocksResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FListGroupBlocksAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFGroupsListGroupBlocksGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFGroupsListGroupBlocksResponse{ .ErrorMessage = FString::Printf(TEXT("GetResultSize failure: 0x%08X"), static_cast<uint32>(HResult)) }, false);
		return;
	}

	PFGroupsListGroupBlocksResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFGroupsListGroupBlocksGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("GetResult failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFGroupsListGroupBlocksResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFGroupsListGroupBlocksResponse> ResultType = ConvertListGroupBlocksResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FListGroupInvitationsAsyncTask::FListGroupInvitationsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsListGroupInvitationsRequest InRequest,
	const FOnListGroupInvitationsCompleted& InDelegate)
	: FXAsyncTask(TEXT("FListGroupInvitationsAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FListGroupInvitationsAsyncTask::DoWork()
{
	const PFGroupsListGroupInvitationsRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.group = ConvertEntityKeyToPlayfab(Request.group)
	};
	HResult = PFGroupsListGroupInvitationsAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFGroupsListGroupInvitationsResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FListGroupInvitationsAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFGroupsListGroupInvitationsGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFGroupsListGroupInvitationsResponse{ .ErrorMessage = FString::Printf(TEXT("GetResultSize failure: 0x%08X"), static_cast<uint32>(HResult)) }, false);
		return;
	}

	PFGroupsListGroupInvitationsResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFGroupsListGroupInvitationsGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("GetResult failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFGroupsListGroupInvitationsResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFGroupsListGroupInvitationsResponse> ResultType = ConvertListGroupInvitationsResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FListGroupMembersAsyncTask::FListGroupMembersAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsListGroupMembersRequest InRequest,
	const FOnListGroupMembersCompleted& InDelegate)
	: FXAsyncTask(TEXT("FListGroupMembersAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FListGroupMembersAsyncTask::DoWork()
{
	const PFGroupsListGroupMembersRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.group = ConvertEntityKeyToPlayfab(Request.group)
	};
	HResult = PFGroupsListGroupMembersAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFGroupsListGroupMembersResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FListGroupMembersAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFGroupsListGroupMembersGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFGroupsListGroupMembersResponse{ .ErrorMessage = FString::Printf(TEXT("GetResultSize failure: 0x%08X"), static_cast<uint32>(HResult)) }, false);
		return;
	}

	PFGroupsListGroupMembersResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFGroupsListGroupMembersGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("GetResult failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFGroupsListGroupMembersResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFGroupsListGroupMembersResponse> ResultType = ConvertListGroupMembersResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FListMembershipAsyncTask::FListMembershipAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsListMembershipRequest InRequest,
	const FOnListMembershipCompleted& InDelegate)
	: FXAsyncTask(TEXT("FListMembershipAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FListMembershipAsyncTask::DoWork()
{
	const PFGroupsListMembershipRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity)
	};
	HResult = PFGroupsListMembershipAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFGroupsListMembershipResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FListMembershipAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFGroupsListMembershipGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFGroupsListMembershipResponse{ .ErrorMessage = FString::Printf(TEXT("GetResultSize failure: 0x%08X"), static_cast<uint32>(HResult)) }, false);
		return;
	}

	PFGroupsListMembershipResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFGroupsListMembershipGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("GetResult failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFGroupsListMembershipResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFGroupsListMembershipResponse> ResultType = ConvertListMembershipResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FListMembershipOpportunitiesAsyncTask::FListMembershipOpportunitiesAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsListMembershipOpportunitiesRequest InRequest,
	const FOnListMembershipOpportunitiesCompleted& InDelegate)
	: FXAsyncTask(TEXT("FListMembershipOpportunitiesAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FListMembershipOpportunitiesAsyncTask::DoWork()
{
	const PFGroupsListMembershipOpportunitiesRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity)
	};
	HResult = PFGroupsListMembershipOpportunitiesAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFGroupsListMembershipOpportunitiesResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FListMembershipOpportunitiesAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFGroupsListMembershipOpportunitiesGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFGroupsListMembershipOpportunitiesResponse{ .ErrorMessage = FString::Printf(TEXT("GetResultSize failure: 0x%08X"), static_cast<uint32>(HResult)) }, false);
		return;
	}

	PFGroupsListMembershipOpportunitiesResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFGroupsListMembershipOpportunitiesGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("GetResult failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFGroupsListMembershipOpportunitiesResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFGroupsListMembershipOpportunitiesResponse> ResultType = ConvertListMembershipOpportunitiesResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FRemoveGroupApplicationAsyncTask::FRemoveGroupApplicationAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsRemoveGroupApplicationRequest InRequest,
	const FOnRemoveGroupApplicationCompleted& InDelegate)
	: FXAsyncTask(TEXT("FRemoveGroupApplicationAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FRemoveGroupApplicationAsyncTask::DoWork()
{
	const PFGroupsRemoveGroupApplicationRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.group = ConvertEntityKeyToPlayfab(Request.group)
	};
	HResult = PFGroupsRemoveGroupApplicationAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(ErrorMessage, false);
	}
};

void FRemoveGroupApplicationAsyncTask::ProcessResults()
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

FRemoveGroupInvitationAsyncTask::FRemoveGroupInvitationAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsRemoveGroupInvitationRequest InRequest,
	const FOnRemoveGroupInvitationCompleted& InDelegate)
	: FXAsyncTask(TEXT("FRemoveGroupInvitationAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FRemoveGroupInvitationAsyncTask::DoWork()
{
	const PFGroupsRemoveGroupInvitationRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.group = ConvertEntityKeyToPlayfab(Request.group)
	};
	HResult = PFGroupsRemoveGroupInvitationAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(ErrorMessage, false);
	}
};

void FRemoveGroupInvitationAsyncTask::ProcessResults()
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

FRemoveMembersAsyncTask::FRemoveMembersAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsRemoveMembersRequest InRequest,
	const FOnRemoveMembersCompleted& InDelegate)
	: FXAsyncTask(TEXT("FRemoveMembersAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FRemoveMembersAsyncTask::DoWork()
{
	const PFGroupsRemoveMembersRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.group = ConvertEntityKeyToPlayfab(Request.group),
		.members = ConvertUnrealArrayToPlayfab<PFEntityKey, FPFEntityKey>(Request.members, ConvertEntityKeyToPlayfab),
		.membersCount = (uint32_t)Request.members.Num(),
		.roleId = ConvertFStringToCharPtr(Request.roleId)
	};
	HResult = PFGroupsRemoveMembersAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(ErrorMessage, false);
	}
};

void FRemoveMembersAsyncTask::ProcessResults()
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

FUnblockEntityAsyncTask::FUnblockEntityAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsUnblockEntityRequest InRequest,
	const FOnUnblockEntityCompleted& InDelegate)
	: FXAsyncTask(TEXT("FUnblockEntityAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FUnblockEntityAsyncTask::DoWork()
{
	const PFGroupsUnblockEntityRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity),
		.group = ConvertEntityKeyToPlayfab(Request.group)
	};
	HResult = PFGroupsUnblockEntityAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(ErrorMessage, false);
	}
};

void FUnblockEntityAsyncTask::ProcessResults()
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

FUpdateGroupAsyncTask::FUpdateGroupAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsUpdateGroupRequest InRequest,
	const FOnUpdateGroupCompleted& InDelegate)
	: FXAsyncTask(TEXT("FUpdateGroupAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FUpdateGroupAsyncTask::DoWork()
{
	const PFGroupsUpdateGroupRequest RequestType = {
		.adminRoleId = ConvertFStringToCharPtr(Request.adminRoleId),
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.expectedProfileVersion = Request.expectedProfileVersion ? new int32(*Request.expectedProfileVersion) : nullptr,
		.group = ConvertEntityKeyToPlayfab(Request.group),
		.groupName = ConvertFStringToCharPtr(Request.groupName),
		.memberRoleId = ConvertFStringToCharPtr(Request.memberRoleId)
	};
	HResult = PFGroupsUpdateGroupAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFGroupsUpdateGroupResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FUpdateGroupAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFGroupsUpdateGroupGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFGroupsUpdateGroupResponse{ .ErrorMessage = FString::Printf(TEXT("GetResultSize failure: 0x%08X"), static_cast<uint32>(HResult)) }, false);
		return;
	}

	PFGroupsUpdateGroupResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFGroupsUpdateGroupGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("GetResult failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFGroupsUpdateGroupResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFGroupsUpdateGroupResponse> ResultType = ConvertUpdateGroupResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

FUpdateRoleAsyncTask::FUpdateRoleAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsUpdateGroupRoleRequest InRequest,
	const FOnUpdateRoleCompleted& InDelegate)
	: FXAsyncTask(TEXT("FUpdateRoleAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FUpdateRoleAsyncTask::DoWork()
{
	const PFGroupsUpdateGroupRoleRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.expectedProfileVersion = Request.expectedProfileVersion ? new int32(*Request.expectedProfileVersion) : nullptr,
		.group = ConvertEntityKeyToPlayfab(Request.group),
		.roleId = ConvertFStringToCharPtr(Request.roleId),
		.roleName = ConvertFStringToCharPtr(Request.roleName)
	};
	HResult = PFGroupsUpdateRoleAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFGroupsUpdateGroupRoleResponse{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FUpdateRoleAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFGroupsUpdateRoleGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFGroupsUpdateGroupRoleResponse{ .ErrorMessage = FString::Printf(TEXT("GetResultSize failure: 0x%08X"), static_cast<uint32>(HResult)) }, false);
		return;
	}

	PFGroupsUpdateGroupRoleResponse *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFGroupsUpdateRoleGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("GetResult failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFGroupsUpdateGroupRoleResponse{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFGroupsUpdateGroupRoleResponse> ResultType = ConvertUpdateGroupRoleResponseToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

