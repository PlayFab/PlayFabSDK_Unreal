#include "PFGroups.h"

bool PLAYFABSERVICES_API FPFGroupsAcceptGroupApplicationAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFGroupsAcceptGroupApplicationRequest* request,
	_Inout_ FOnAcceptGroupApplicationCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FAcceptGroupApplicationAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFGroupsAcceptGroupInvitationAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFGroupsAcceptGroupInvitationRequest* request,
	_Inout_ FOnAcceptGroupInvitationCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FAcceptGroupInvitationAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFGroupsAddMembersAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFGroupsAddMembersRequest* request,
	_Inout_ FOnAddMembersCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FAddMembersAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFGroupsApplyToGroupAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFGroupsApplyToGroupRequest* request,
	_Inout_ FOnApplyToGroupCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FApplyToGroupAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFGroupsBlockEntityAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFGroupsBlockEntityRequest* request,
	_Inout_ FOnBlockEntityCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FBlockEntityAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFGroupsChangeMemberRoleAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFGroupsChangeMemberRoleRequest* request,
	_Inout_ FOnChangeMemberRoleCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FChangeMemberRoleAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFGroupsCreateGroupAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFGroupsCreateGroupRequest* request,
	_Inout_ FOnCreateGroupCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FCreateGroupAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFGroupsCreateRoleAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFGroupsCreateGroupRoleRequest* request,
	_Inout_ FOnCreateRoleCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FCreateRoleAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFGroupsDeleteGroupAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFGroupsDeleteGroupRequest* request,
	_Inout_ FOnDeleteGroupCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FDeleteGroupAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFGroupsDeleteRoleAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFGroupsDeleteRoleRequest* request,
	_Inout_ FOnDeleteRoleCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FDeleteRoleAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFGroupsGetGroupAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFGroupsGetGroupRequest* request,
	_Inout_ FOnGetGroupCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FGetGroupAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFGroupsInviteToGroupAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFGroupsInviteToGroupRequest* request,
	_Inout_ FOnInviteToGroupCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FInviteToGroupAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFGroupsIsMemberAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFGroupsIsMemberRequest* request,
	_Inout_ FOnIsMemberCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FIsMemberAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFGroupsListGroupApplicationsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFGroupsListGroupApplicationsRequest* request,
	_Inout_ FOnListGroupApplicationsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FListGroupApplicationsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFGroupsListGroupBlocksAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFGroupsListGroupBlocksRequest* request,
	_Inout_ FOnListGroupBlocksCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FListGroupBlocksAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFGroupsListGroupInvitationsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFGroupsListGroupInvitationsRequest* request,
	_Inout_ FOnListGroupInvitationsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FListGroupInvitationsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFGroupsListGroupMembersAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFGroupsListGroupMembersRequest* request,
	_Inout_ FOnListGroupMembersCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FListGroupMembersAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFGroupsListMembershipAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFGroupsListMembershipRequest* request,
	_Inout_ FOnListMembershipCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FListMembershipAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFGroupsListMembershipOpportunitiesAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFGroupsListMembershipOpportunitiesRequest* request,
	_Inout_ FOnListMembershipOpportunitiesCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FListMembershipOpportunitiesAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFGroupsRemoveGroupApplicationAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFGroupsRemoveGroupApplicationRequest* request,
	_Inout_ FOnRemoveGroupApplicationCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FRemoveGroupApplicationAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFGroupsRemoveGroupInvitationAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFGroupsRemoveGroupInvitationRequest* request,
	_Inout_ FOnRemoveGroupInvitationCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FRemoveGroupInvitationAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFGroupsRemoveMembersAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFGroupsRemoveMembersRequest* request,
	_Inout_ FOnRemoveMembersCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FRemoveMembersAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFGroupsUnblockEntityAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFGroupsUnblockEntityRequest* request,
	_Inout_ FOnUnblockEntityCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FUnblockEntityAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFGroupsUpdateGroupAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFGroupsUpdateGroupRequest* request,
	_Inout_ FOnUpdateGroupCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FUpdateGroupAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFGroupsUpdateRoleAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFGroupsUpdateGroupRoleRequest* request,
	_Inout_ FOnUpdateRoleCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FUpdateRoleAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

