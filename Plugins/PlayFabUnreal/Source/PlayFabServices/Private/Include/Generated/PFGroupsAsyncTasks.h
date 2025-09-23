// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#include "CoreMinimal.h"
#include "Async/AsyncWork.h"
#include "Async/Async.h"
#include "XAsyncTaskQueueHelpers.h"
#include "XAsyncTaskManager.h"
#include "XAsyncTask.h"
#include "PFEntity.h"
#include "PFServiceConfig.h"
#include "PFGroupsUnrealTypes.h"
#include "PFGroupsTypeConverters.h"

THIRD_PARTY_INCLUDES_START
#include <playfab/services/PFServices.h>
THIRD_PARTY_INCLUDES_END


/// <summary>
/// Accepts an outstanding invitation to to join a group
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Accepts an outstanding invitation to to join a group if the invited entity is not blocked by the
/// group. Nothing is returned in the case of success. See also GroupApplyToGroupAsync, GroupListGroupApplicationsAsync,
/// GroupRemoveGroupApplicationAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ENTITY_BLOCKED_BY_GROUP, E_PF_ENTITY_IS_ALREADY_MEMBER, E_PF_GROUP_APPLICATION_NOT_FOUND
/// or any of the global PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details
/// on error handling.
/// </remarks>
class PLAYFABSERVICES_API FAcceptGroupApplicationAsyncTask : public FXAsyncTask
{
public:
	FAcceptGroupApplicationAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsAcceptGroupApplicationRequest InRequest,
	const FOnAcceptGroupApplicationCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFGroupsAcceptGroupApplicationRequest Request;
	
	FOnAcceptGroupApplicationCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Accepts an invitation to join a group
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Accepts an outstanding invitation to join the group if the invited entity is not blocked by the group.
/// Only the invited entity or a parent in its chain (e.g. title) may accept the invitation on the invited
/// entity's behalf. Nothing is returned in the case of success. See also GroupInviteToGroupAsync, GroupListGroupInvitationsAsync,
/// GroupListMembershipOpportunitiesAsync, GroupRemoveGroupInvitationAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ENTITY_BLOCKED_BY_GROUP, E_PF_ENTITY_IS_ALREADY_MEMBER, E_PF_GROUP_INVITATION_NOT_FOUND,
/// E_PF_ROLE_DOES_NOT_EXIST or any of the global PlayFab Service errors. See doc page "Handling PlayFab
/// Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FAcceptGroupInvitationAsyncTask : public FXAsyncTask
{
public:
	FAcceptGroupInvitationAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsAcceptGroupInvitationRequest InRequest,
	const FOnAcceptGroupInvitationCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFGroupsAcceptGroupInvitationRequest Request;
	
	FOnAcceptGroupInvitationCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Adds members to a group or role.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Adds members to a group or role. Existing members of the group will added to roles within the group,
/// but if the user is not already a member of the group, only title claimants may add them to the group,
/// and others must use the group application or invite system to add new members to a group. Returns
/// nothing if successful. See also GroupApplyToGroupAsync, GroupInviteToGroupAsync, GroupListGroupMembersAsync,
/// GroupRemoveMembersAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ROLE_DOES_NOT_EXIST or any of the global PlayFab Service errors. See
/// doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FAddMembersAsyncTask : public FXAsyncTask
{
public:
	FAddMembersAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsAddMembersRequest InRequest,
	const FOnAddMembersCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFGroupsAddMembersRequest Request;
	
	FOnAddMembersCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Applies to join a group
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Creates an application to join a group. Calling this while a group application already exists will
/// return the same application instead of an error and will not refresh the time before the application
/// expires. By default, if the entity has an invitation to join the group outstanding, this will accept
/// the invitation to join the group instead and return an error indicating such, rather than creating
/// a duplicate application to join that will need to be cleaned up later. Returns information about the
/// application or an error indicating an invitation was accepted instead. See also GroupAcceptGroupApplicationAsync,
/// GroupListGroupApplicationsAsync, GroupRemoveGroupApplicationAsync.
///
/// When the asynchronous task is complete, call <see cref="PFGroupsApplyToGroupGetResultSize"/> and
/// <see cref="PFGroupsApplyToGroupGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FApplyToGroupAsyncTask : public FXAsyncTask
{
public:
	FApplyToGroupAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsApplyToGroupRequest InRequest,
	const FOnApplyToGroupCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFGroupsApplyToGroupRequest Request;
	
	FOnApplyToGroupCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Blocks a list of entities from joining a group.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Blocks a list of entities from joining a group. Blocked entities may not create new applications
/// to join, be invited to join, accept an invitation, or have an application accepted. Failure due to
/// being blocked does not clean up existing applications or invitations to the group. No data is returned
/// in the case of success. See also GroupListGroupBlocksAsync, GroupUnblockEntityAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be one of global PlayFab Service errors. See doc page "Handling PlayFab Errors"
/// for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FBlockEntityAsyncTask : public FXAsyncTask
{
public:
	FBlockEntityAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsBlockEntityRequest InRequest,
	const FOnBlockEntityCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFGroupsBlockEntityRequest Request;
	
	FOnBlockEntityCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Changes the role membership of a list of entities from one role to another.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Changes the role membership of a list of entities from one role to another in in a single operation.
/// The destination role must already exist. This is equivalent to adding the entities to the destination
/// role and removing from the origin role. Returns nothing if successful. See also GroupAddMembersAsync,
/// GroupCreateRoleAsync, GroupRemoveMembersAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ROLE_DOES_NOT_EXIST or any of the global PlayFab Service errors. See
/// doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FChangeMemberRoleAsyncTask : public FXAsyncTask
{
public:
	FChangeMemberRoleAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsChangeMemberRoleRequest InRequest,
	const FOnChangeMemberRoleCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFGroupsChangeMemberRoleRequest Request;
	
	FOnChangeMemberRoleCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Creates a new group.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Creates a new group, as well as administration and member roles, based off of a title's group template.
/// Returns information about the group that was created. See also GroupAddMembersAsync, GroupApplyToGroupAsync,
/// GroupDeleteGroupAsync, GroupInviteToGroupAsync, GroupListGroupMembersAsync, GroupRemoveMembersAsync.
///
/// When the asynchronous task is complete, call <see cref="PFGroupsCreateGroupGetResultSize"/> and <see
/// cref="PFGroupsCreateGroupGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FCreateGroupAsyncTask : public FXAsyncTask
{
public:
	FCreateGroupAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsCreateGroupRequest InRequest,
	const FOnCreateGroupCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFGroupsCreateGroupRequest Request;
	
	FOnCreateGroupCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Creates a new group role.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Creates a new role within an existing group, with no members. Both the role ID and role name must
/// be unique within the group, but the name can be the same as the ID. The role ID is set at creation
/// and cannot be changed. Returns information about the role that was created. See also GroupDeleteRoleAsync.
///
/// When the asynchronous task is complete, call <see cref="PFGroupsCreateRoleGetResultSize"/> and <see
/// cref="PFGroupsCreateRoleGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FCreateRoleAsyncTask : public FXAsyncTask
{
public:
	FCreateRoleAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsCreateGroupRoleRequest InRequest,
	const FOnCreateRoleCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFGroupsCreateGroupRoleRequest Request;
	
	FOnCreateRoleCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Deletes a group and all roles, invitations, join requests, and blocks associated with it.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Deletes a group and all roles, invitations, join requests, and blocks associated with it. Permission
/// to delete is only required the group itself to execute this action. The group and data cannot be cannot
/// be recovered once removed, but any abuse reports about the group will remain. No data is returned
/// in the case of success. See also GroupCreateGroupAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be one of global PlayFab Service errors. See doc page "Handling PlayFab Errors"
/// for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FDeleteGroupAsyncTask : public FXAsyncTask
{
public:
	FDeleteGroupAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsDeleteGroupRequest InRequest,
	const FOnDeleteGroupCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFGroupsDeleteGroupRequest Request;
	
	FOnDeleteGroupCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Deletes an existing role in a group.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Returns information about the role See also GroupCreateRoleAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ROLE_DOES_NOT_EXIST, E_PF_ROLE_IS_GROUP_ADMIN, E_PF_ROLE_IS_GROUP_DEFAULT_MEMBER
/// or any of the global PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details
/// on error handling.
/// </remarks>
class PLAYFABSERVICES_API FDeleteRoleAsyncTask : public FXAsyncTask
{
public:
	FDeleteRoleAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsDeleteRoleRequest InRequest,
	const FOnDeleteRoleCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFGroupsDeleteRoleRequest Request;
	
	FOnDeleteRoleCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Gets information about a group and its roles
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Returns the ID, name, role list and other non-membership related information about a group. See also
/// GroupUpdateGroupAsync.
///
/// When the asynchronous task is complete, call <see cref="PFGroupsGetGroupGetResultSize"/> and <see
/// cref="PFGroupsGetGroupGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FGetGroupAsyncTask : public FXAsyncTask
{
public:
	FGetGroupAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsGetGroupRequest InRequest,
	const FOnGetGroupCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFGroupsGetGroupRequest Request;
	
	FOnGetGroupCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Invites a player to join a group
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Invites a player to join a group, if they are not blocked by the group. An optional role can be provided
/// to automatically assign the player to the role if they accept the invitation. By default, if the entity
/// has an application to the group outstanding, this will accept the application instead and return an
/// error indicating such, rather than creating a duplicate invitation to join that will need to be cleaned
/// up later. Returns information about the new invitation or an error indicating an existing application
/// to join was accepted. See also GroupAcceptGroupInvitationAsync, GroupListGroupInvitationsAsync, GroupListMembershipOpportunitiesAsync,
/// GroupRemoveGroupInvitationAsync.
///
/// When the asynchronous task is complete, call <see cref="PFGroupsInviteToGroupGetResultSize"/> and
/// <see cref="PFGroupsInviteToGroupGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FInviteToGroupAsyncTask : public FXAsyncTask
{
public:
	FInviteToGroupAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsInviteToGroupRequest InRequest,
	const FOnInviteToGroupCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFGroupsInviteToGroupRequest Request;
	
	FOnInviteToGroupCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Checks to see if an entity is a member of a group or role within the group
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Checks to see if an entity is a member of a group or role within the group. A result indicating if
/// the entity is a member of the group is returned, or a permission error if the caller does not have
/// permission to read the group's member list. See also GroupGetGroupAsync.
///
/// When the asynchronous task is complete, call <see cref="PFGroupsIsMemberGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FIsMemberAsyncTask : public FXAsyncTask
{
public:
	FIsMemberAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsIsMemberRequest InRequest,
	const FOnIsMemberCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFGroupsIsMemberRequest Request;
	
	FOnIsMemberCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Lists all outstanding requests to join a group
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Lists all outstanding requests to join a group. Returns a list of all requests to join, as well as
/// when the request will expire. To get the group applications for a specific entity, use ListMembershipOpportunities.
/// See also GroupAcceptGroupApplicationAsync, GroupApplyToGroupAsync, GroupRemoveGroupApplicationAsync.
///
/// When the asynchronous task is complete, call <see cref="PFGroupsListGroupApplicationsGetResultSize"/>
/// and <see cref="PFGroupsListGroupApplicationsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FListGroupApplicationsAsyncTask : public FXAsyncTask
{
public:
	FListGroupApplicationsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsListGroupApplicationsRequest InRequest,
	const FOnListGroupApplicationsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFGroupsListGroupApplicationsRequest Request;
	
	FOnListGroupApplicationsCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Lists all entities blocked from joining a group
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Lists all entities blocked from joining a group. A list of blocked entities is returned See also
/// GroupBlockEntityAsync, GroupUnblockEntityAsync.
///
/// When the asynchronous task is complete, call <see cref="PFGroupsListGroupBlocksGetResultSize"/> and
/// <see cref="PFGroupsListGroupBlocksGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FListGroupBlocksAsyncTask : public FXAsyncTask
{
public:
	FListGroupBlocksAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsListGroupBlocksRequest InRequest,
	const FOnListGroupBlocksCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFGroupsListGroupBlocksRequest Request;
	
	FOnListGroupBlocksCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Lists all outstanding invitations for a group
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Lists all outstanding invitations for a group. Returns a list of entities that have been invited,
/// as well as when the invitation will expire. To get the group invitations for a specific entity, use
/// ListMembershipOpportunities. See also GroupAcceptGroupInvitationAsync, GroupInviteToGroupAsync, GroupListMembershipOpportunitiesAsync,
/// GroupRemoveGroupInvitationAsync.
///
/// When the asynchronous task is complete, call <see cref="PFGroupsListGroupInvitationsGetResultSize"/>
/// and <see cref="PFGroupsListGroupInvitationsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FListGroupInvitationsAsyncTask : public FXAsyncTask
{
public:
	FListGroupInvitationsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsListGroupInvitationsRequest InRequest,
	const FOnListGroupInvitationsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFGroupsListGroupInvitationsRequest Request;
	
	FOnListGroupInvitationsCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Lists all members for a group
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Gets a list of members and the roles they belong to within the group. If the caller does not have
/// permission to view the role, and the member is in no other role, the member is not displayed. Returns
/// a list of entities that are members of the group. See also GroupListMembershipAsync.
///
/// When the asynchronous task is complete, call <see cref="PFGroupsListGroupMembersGetResultSize"/>
/// and <see cref="PFGroupsListGroupMembersGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FListGroupMembersAsyncTask : public FXAsyncTask
{
public:
	FListGroupMembersAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsListGroupMembersRequest InRequest,
	const FOnListGroupMembersCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFGroupsListGroupMembersRequest Request;
	
	FOnListGroupMembersCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Lists all groups and roles for an entity
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Lists the groups and roles that an entity is a part of, checking to see if group and role metadata
/// and memberships should be visible to the caller. If the entity is not in any roles that are visible
/// to the caller, the group is not returned in the results, even if the caller otherwise has permission
/// to see that the entity is a member of that group. See also GroupListGroupMembersAsync, GroupListMembershipOpportunitiesAsync.
///
/// When the asynchronous task is complete, call <see cref="PFGroupsListMembershipGetResultSize"/> and
/// <see cref="PFGroupsListMembershipGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FListMembershipAsyncTask : public FXAsyncTask
{
public:
	FListMembershipAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsListMembershipRequest InRequest,
	const FOnListMembershipCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFGroupsListMembershipRequest Request;
	
	FOnListMembershipCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Lists all outstanding invitations and group applications for an entity
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Lists all outstanding group applications and invitations for an entity. Anyone may call this for
/// any entity, but data will only be returned for the entity or a parent of that entity. To list invitations
/// or applications for a group to check if a player is trying to join, use ListGroupInvitations and ListGroupApplications.
/// See also GroupListGroupApplicationsAsync, GroupListGroupInvitationsAsync.
///
/// When the asynchronous task is complete, call <see cref="PFGroupsListMembershipOpportunitiesGetResultSize"/>
/// and <see cref="PFGroupsListMembershipOpportunitiesGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FListMembershipOpportunitiesAsyncTask : public FXAsyncTask
{
public:
	FListMembershipOpportunitiesAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsListMembershipOpportunitiesRequest InRequest,
	const FOnListMembershipOpportunitiesCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFGroupsListMembershipOpportunitiesRequest Request;
	
	FOnListMembershipOpportunitiesCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Removes an application to join a group
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Removes an existing application to join the group. This is used for both rejection of an application
/// as well as withdrawing an application. The applying entity or a parent in its chain (e.g. title) may
/// withdraw the application, and any caller with appropriate access in the group may reject an application.
/// No data is returned in the case of success. See also GroupAcceptGroupApplicationAsync, GroupApplyToGroupAsync,
/// GroupListGroupApplicationsAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_GROUP_APPLICATION_NOT_FOUND or any of the global PlayFab Service errors.
/// See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FRemoveGroupApplicationAsyncTask : public FXAsyncTask
{
public:
	FRemoveGroupApplicationAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsRemoveGroupApplicationRequest InRequest,
	const FOnRemoveGroupApplicationCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFGroupsRemoveGroupApplicationRequest Request;
	
	FOnRemoveGroupApplicationCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Removes an invitation join a group
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Removes an existing invitation to join the group. This is used for both rejection of an invitation
/// as well as rescinding an invitation. The invited entity or a parent in its chain (e.g. title) may
/// reject the invitation by calling this method, and any caller with appropriate access in the group
/// may rescind an invitation. No data is returned in the case of success. See also GroupAcceptGroupInvitationAsync,
/// GroupInviteToGroupAsync, GroupListGroupInvitationsAsync, GroupListMembershipOpportunitiesAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_GROUP_INVITATION_NOT_FOUND or any of the global PlayFab Service errors.
/// See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FRemoveGroupInvitationAsyncTask : public FXAsyncTask
{
public:
	FRemoveGroupInvitationAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsRemoveGroupInvitationRequest InRequest,
	const FOnRemoveGroupInvitationCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFGroupsRemoveGroupInvitationRequest Request;
	
	FOnRemoveGroupInvitationCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Removes members from a group.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Removes members from a group. A member can always remove themselves from a group, regardless of permissions.
/// Returns nothing if successful. See also GroupAddMembersAsync, GroupListGroupMembersAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ROLE_DOES_NOT_EXIST or any of the global PlayFab Service errors. See
/// doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FRemoveMembersAsyncTask : public FXAsyncTask
{
public:
	FRemoveMembersAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsRemoveMembersRequest InRequest,
	const FOnRemoveMembersCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFGroupsRemoveMembersRequest Request;
	
	FOnRemoveMembersCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Unblocks a list of entities from joining a group
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Unblocks a list of entities from joining a group. No data is returned in the case of success. See
/// also GroupBlockEntityAsync, GroupListGroupBlocksAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be one of global PlayFab Service errors. See doc page "Handling PlayFab Errors"
/// for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FUnblockEntityAsyncTask : public FXAsyncTask
{
public:
	FUnblockEntityAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsUnblockEntityRequest InRequest,
	const FOnUnblockEntityCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFGroupsUnblockEntityRequest Request;
	
	FOnUnblockEntityCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Updates non-membership data about a group.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Updates data about a group, such as the name or default member role. Returns information about whether
/// the update was successful. Only title claimants may modify the administration role for a group. See
/// also GroupCreateGroupAsync, GroupDeleteGroupAsync, GroupGetGroupAsync.
///
/// When the asynchronous task is complete, call <see cref="PFGroupsUpdateGroupGetResultSize"/> and <see
/// cref="PFGroupsUpdateGroupGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FUpdateGroupAsyncTask : public FXAsyncTask
{
public:
	FUpdateGroupAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsUpdateGroupRequest InRequest,
	const FOnUpdateGroupCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFGroupsUpdateGroupRequest Request;
	
	FOnUpdateGroupCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Updates metadata about a role.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Updates the role name. Returns information about whether the update was successful. See also GroupCreateRoleAsync,
/// GroupDeleteRoleAsync.
///
/// When the asynchronous task is complete, call <see cref="PFGroupsUpdateRoleGetResultSize"/> and <see
/// cref="PFGroupsUpdateRoleGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FUpdateRoleAsyncTask : public FXAsyncTask
{
public:
	FUpdateRoleAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFGroupsUpdateGroupRoleRequest InRequest,
	const FOnUpdateRoleCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFGroupsUpdateGroupRoleRequest Request;
	
	FOnUpdateRoleCompleted Delegate;

	HRESULT HResult;
};

