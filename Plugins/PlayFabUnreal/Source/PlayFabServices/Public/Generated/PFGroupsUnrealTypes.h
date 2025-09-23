// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once
#include "PFUnrealTypes.h"

#pragma push_macro("IN")
#undef IN

/// <summary>
/// FPFGroupsAcceptGroupApplicationRequest data model. Accepts an outstanding invitation to to join a
/// group if the invited entity is not blocked by the group. Nothing is returned in the case of success.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsAcceptGroupApplicationRequest
{
	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// Type of the entity to accept as. Must be the same entity as the claimant or an entity that is a
	/// child of the claimant entity.
	/// </summary>
	TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// The identifier of the group.
	/// </summary>
	TSharedPtr<const FPFEntityKey> group;
};

/// <summary>
/// FPFGroupsAcceptGroupInvitationRequest data model. Accepts an outstanding invitation to join the group
/// if the invited entity is not blocked by the group. Only the invited entity or a parent in its chain
/// (e.g. title) may accept the invitation on the invited entity's behalf. Nothing is returned in the
/// case of success.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsAcceptGroupInvitationRequest
{
	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// (Optional) The optional entity to perform this action on. Defaults to the currently logged in entity.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// The identifier of the group.
	/// </summary>
	TSharedPtr<const FPFEntityKey> group;
};

/// <summary>
/// FPFGroupsAddMembersRequest data model. Adds members to a group or role. Existing members of the group
/// will added to roles within the group, but if the user is not already a member of the group, only title
/// claimants may add them to the group, and others must use the group application or invite system to
/// add new members to a group. Returns nothing if successful.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsAddMembersRequest
{
	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// The identifier of the group.
	/// </summary>
	TSharedPtr<const FPFEntityKey> group;

	/// <summary>
	/// List of entities to add to the group. Only entities of type title_player_account and character may
	/// be added to groups.
	/// </summary>
	TArray<TSharedPtr<const FPFEntityKey>> members;

	/// <summary>
	/// Count of members
	/// </summary>
	uint32 membersCount;

	/// <summary>
	/// (Optional) Optional: The ID of the existing role to add the entities to. If this is not specified,
	/// the default member role for the group will be used. Role IDs must be between 1 and 64 characters
	/// long.
	/// </summary>
	_Maybenull_ const FString roleId;
};

/// <summary>
/// FPFGroupsApplyToGroupRequest data model. Creates an application to join a group. Calling this while
/// a group application already exists will return the same application instead of an error and will not
/// refresh the time before the application expires. By default, if the entity has an invitation to join
/// the group outstanding, this will accept the invitation to join the group instead and return an error
/// indicating such, rather than creating a duplicate application to join that will need to be cleaned
/// up later. Returns information about the application or an error indicating an invitation was accepted
/// instead.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsApplyToGroupRequest
{
	/// <summary>
	/// (Optional) Optional, default true. Automatically accept an outstanding invitation if one exists
	/// instead of creating an application.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> autoAcceptOutstandingInvite;

	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// (Optional) The optional entity to perform this action on. Defaults to the currently logged in entity.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// The identifier of the group.
	/// </summary>
	TSharedPtr<const FPFEntityKey> group;
};

/// <summary>
/// FPFGroupsEntityWithLineage data model. Entity wrapper class that contains the entity key and the
/// entities that make up the lineage of the entity.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsEntityWithLineage
{
	/// <summary>
	/// (Optional) The entity key for the specified entity.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> key;

	/// <summary>
	/// (Optional) Dictionary of entity keys for related entities. Dictionary key is entity type.
	/// </summary>
	_Maybenull_ TMap<const FString, TSharedPtr<const FPFEntityKey>> lineage;

	/// <summary>
	/// Count of lineage
	/// </summary>
	uint32 lineageCount;
};

/// <summary>
/// FPFGroupsApplyToGroupResponse data model. Describes an application to join a group.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsApplyToGroupResponse
{
	/// <summary>
	/// (Optional) Type of entity that requested membership.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFGroupsEntityWithLineage> entity;

	/// <summary>
	/// When the application to join will expire and be deleted.
	/// </summary>
	FDateTime expires;

	/// <summary>
	/// (Optional) ID of the group that the entity requesting membership to.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> group;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFGroupsBlockEntityRequest data model. Blocks a list of entities from joining a group. Blocked entities
/// may not create new applications to join, be invited to join, accept an invitation, or have an application
/// accepted. Failure due to being blocked does not clean up existing applications or invitations to the
/// group. No data is returned in the case of success.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsBlockEntityRequest
{
	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// The entity to perform this action on.
	/// </summary>
	TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// The identifier of the group.
	/// </summary>
	TSharedPtr<const FPFEntityKey> group;
};

/// <summary>
/// FPFGroupsChangeMemberRoleRequest data model. Changes the role membership of a list of entities from
/// one role to another in in a single operation. The destination role must already exist. This is equivalent
/// to adding the entities to the destination role and removing from the origin role. Returns nothing
/// if successful.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsChangeMemberRoleRequest
{
	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// (Optional) The ID of the role that the entities will become a member of. This must be an existing
	/// role. Role IDs must be between 1 and 64 characters long.
	/// </summary>
	_Maybenull_ const FString destinationRoleId;

	/// <summary>
	/// The identifier of the group.
	/// </summary>
	TSharedPtr<const FPFEntityKey> group;

	/// <summary>
	/// List of entities to move between roles in the group. All entities in this list must be members of
	/// the group and origin role.
	/// </summary>
	TArray<TSharedPtr<const FPFEntityKey>> members;

	/// <summary>
	/// Count of members
	/// </summary>
	uint32 membersCount;

	/// <summary>
	/// The ID of the role that the entities currently are a member of. Role IDs must be between 1 and 64
	/// characters long.
	/// </summary>
	const FString originRoleId;
};

/// <summary>
/// FPFGroupsCreateGroupRequest data model. Creates a new group, as well as administration and member
/// roles, based off of a title's group template. Returns information about the group that was created.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsCreateGroupRequest
{
	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// (Optional) The optional entity to perform this action on. Defaults to the currently logged in entity.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// The name of the group. This is unique at the title level by default.
	/// </summary>
	const FString groupName;
};

/// <summary>
/// FPFGroupsCreateGroupResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsCreateGroupResponse
{
	/// <summary>
	/// (Optional) The ID of the administrator role for the group.
	/// </summary>
	_Maybenull_ const FString adminRoleId;

	/// <summary>
	/// The server date and time the group was created.
	/// </summary>
	FDateTime created;

	/// <summary>
	/// The identifier of the group.
	/// </summary>
	TSharedPtr<const FPFEntityKey> group;

	/// <summary>
	/// (Optional) The name of the group.
	/// </summary>
	_Maybenull_ const FString groupName;

	/// <summary>
	/// (Optional) The ID of the default member role for the group.
	/// </summary>
	_Maybenull_ const FString memberRoleId;

	/// <summary>
	/// The current version of the profile, can be used for concurrency control during updates.
	/// </summary>
	int32 profileVersion;

	/// <summary>
	/// (Optional) The list of roles and names that belong to the group.
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> roles;

	/// <summary>
	/// Count of roles
	/// </summary>
	uint32 rolesCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFGroupsCreateGroupRoleRequest data model. Creates a new role within an existing group, with no
/// members. Both the role ID and role name must be unique within the group, but the name can be the same
/// as the ID. The role ID is set at creation and cannot be changed. Returns information about the role
/// that was created.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsCreateGroupRoleRequest
{
	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// The identifier of the group.
	/// </summary>
	TSharedPtr<const FPFEntityKey> group;

	/// <summary>
	/// The ID of the role. This must be unique within the group and cannot be changed. Role IDs must be
	/// between 1 and 64 characters long and are restricted to a-Z, A-Z, 0-9, '(', ')', '_', '-' and '.'.
	/// </summary>
	const FString roleId;

	/// <summary>
	/// The name of the role. This must be unique within the group and can be changed later. Role names
	/// must be between 1 and 100 characters long.
	/// </summary>
	const FString roleName;
};

/// <summary>
/// FPFGroupsCreateGroupRoleResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsCreateGroupRoleResponse
{
	/// <summary>
	/// The current version of the group profile, can be used for concurrency control during updates.
	/// </summary>
	int32 profileVersion;

	/// <summary>
	/// (Optional) ID for the role.
	/// </summary>
	_Maybenull_ const FString roleId;

	/// <summary>
	/// (Optional) The name of the role.
	/// </summary>
	_Maybenull_ const FString roleName;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFGroupsDeleteGroupRequest data model. Deletes a group and all roles, invitations, join requests,
/// and blocks associated with it. Permission to delete is only required the group itself to execute this
/// action. The group and data cannot be cannot be recovered once removed, but any abuse reports about
/// the group will remain. No data is returned in the case of success.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsDeleteGroupRequest
{
	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// ID of the group or role to remove.
	/// </summary>
	TSharedPtr<const FPFEntityKey> group;
};

/// <summary>
/// FPFGroupsDeleteRoleRequest data model. Returns information about the role.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsDeleteRoleRequest
{
	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// The identifier of the group.
	/// </summary>
	TSharedPtr<const FPFEntityKey> group;

	/// <summary>
	/// (Optional) The ID of the role to delete. Role IDs must be between 1 and 64 characters long.
	/// </summary>
	_Maybenull_ const FString roleId;
};

/// <summary>
/// FPFGroupsGetGroupRequest data model. Returns the ID, name, role list and other non-membership related
/// information about a group.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsGetGroupRequest
{
	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// (Optional) The identifier of the group.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> group;

	/// <summary>
	/// (Optional) The full name of the group.
	/// </summary>
	_Maybenull_ const FString groupName;
};

/// <summary>
/// FPFGroupsGetGroupResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsGetGroupResponse
{
	/// <summary>
	/// (Optional) The ID of the administrator role for the group.
	/// </summary>
	_Maybenull_ const FString adminRoleId;

	/// <summary>
	/// The server date and time the group was created.
	/// </summary>
	FDateTime created;

	/// <summary>
	/// The identifier of the group.
	/// </summary>
	TSharedPtr<const FPFEntityKey> group;

	/// <summary>
	/// (Optional) The name of the group.
	/// </summary>
	_Maybenull_ const FString groupName;

	/// <summary>
	/// (Optional) The ID of the default member role for the group.
	/// </summary>
	_Maybenull_ const FString memberRoleId;

	/// <summary>
	/// The current version of the profile, can be used for concurrency control during updates.
	/// </summary>
	int32 profileVersion;

	/// <summary>
	/// (Optional) The list of roles and names that belong to the group.
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> roles;

	/// <summary>
	/// Count of roles
	/// </summary>
	uint32 rolesCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFGroupsInviteToGroupRequest data model. Invites a player to join a group, if they are not blocked
/// by the group. An optional role can be provided to automatically assign the player to the role if they
/// accept the invitation. By default, if the entity has an application to the group outstanding, this
/// will accept the application instead and return an error indicating such, rather than creating a duplicate
/// invitation to join that will need to be cleaned up later. Returns information about the new invitation
/// or an error indicating an existing application to join was accepted.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsInviteToGroupRequest
{
	/// <summary>
	/// (Optional) Optional, default true. Automatically accept an application if one exists instead of
	/// creating an invitation.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> autoAcceptOutstandingApplication;

	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// The entity to perform this action on.
	/// </summary>
	TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// The identifier of the group.
	/// </summary>
	TSharedPtr<const FPFEntityKey> group;

	/// <summary>
	/// (Optional) Optional. ID of an existing a role in the group to assign the user to. The group's default
	/// member role is used if this is not specified. Role IDs must be between 1 and 64 characters long.
	/// </summary>
	_Maybenull_ const FString roleId;
};

/// <summary>
/// FPFGroupsInviteToGroupResponse data model. Describes an invitation to a group.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsInviteToGroupResponse
{
	/// <summary>
	/// When the invitation will expire and be deleted.
	/// </summary>
	FDateTime expires;

	/// <summary>
	/// (Optional) The group that the entity invited to.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> group;

	/// <summary>
	/// (Optional) The entity that created the invitation.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFGroupsEntityWithLineage> invitedByEntity;

	/// <summary>
	/// (Optional) The entity that is invited.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFGroupsEntityWithLineage> invitedEntity;

	/// <summary>
	/// (Optional) ID of the role in the group to assign the user to.
	/// </summary>
	_Maybenull_ const FString roleId;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFGroupsIsMemberRequest data model. Checks to see if an entity is a member of a group or role within
/// the group. A result indicating if the entity is a member of the group is returned, or a permission
/// error if the caller does not have permission to read the group's member list.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsIsMemberRequest
{
	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// The entity to perform this action on.
	/// </summary>
	TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// The identifier of the group.
	/// </summary>
	TSharedPtr<const FPFEntityKey> group;

	/// <summary>
	/// (Optional) Optional: ID of the role to check membership of. Defaults to any role (that is, check
	/// to see if the entity is a member of the group in any capacity) if not specified.
	/// </summary>
	_Maybenull_ const FString roleId;
};

/// <summary>
/// FPFGroupsIsMemberResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsIsMemberResponse
{
	/// <summary>
	/// A value indicating whether or not the entity is a member.
	/// </summary>
	bool isMember;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFGroupsListGroupApplicationsRequest data model. Lists all outstanding requests to join a group.
/// Returns a list of all requests to join, as well as when the request will expire. To get the group
/// applications for a specific entity, use ListMembershipOpportunities.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsListGroupApplicationsRequest
{
	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// The identifier of the group.
	/// </summary>
	TSharedPtr<const FPFEntityKey> group;
};

/// <summary>
/// FPFGroupsGroupApplication data model. Describes an application to join a group.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsGroupApplication
{
	/// <summary>
	/// (Optional) Type of entity that requested membership.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFGroupsEntityWithLineage> entity;

	/// <summary>
	/// When the application to join will expire and be deleted.
	/// </summary>
	FDateTime expires;

	/// <summary>
	/// (Optional) ID of the group that the entity requesting membership to.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> group;
};

/// <summary>
/// FPFGroupsListGroupApplicationsResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsListGroupApplicationsResponse
{
	/// <summary>
	/// (Optional) The requested list of applications to the group.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFGroupsGroupApplication>> applications;

	/// <summary>
	/// Count of applications
	/// </summary>
	uint32 applicationsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFGroupsListGroupBlocksRequest data model. Lists all entities blocked from joining a group. A list
/// of blocked entities is returned.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsListGroupBlocksRequest
{
	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// The identifier of the group.
	/// </summary>
	TSharedPtr<const FPFEntityKey> group;
};

/// <summary>
/// FPFGroupsGroupBlock data model. Describes an entity that is blocked from joining a group.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsGroupBlock
{
	/// <summary>
	/// (Optional) The entity that is blocked.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFGroupsEntityWithLineage> entity;

	/// <summary>
	/// ID of the group that the entity is blocked from.
	/// </summary>
	TSharedPtr<const FPFEntityKey> group;
};

/// <summary>
/// FPFGroupsListGroupBlocksResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsListGroupBlocksResponse
{
	/// <summary>
	/// (Optional) The requested list blocked entities.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFGroupsGroupBlock>> blockedEntities;

	/// <summary>
	/// Count of blockedEntities
	/// </summary>
	uint32 blockedEntitiesCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFGroupsListGroupInvitationsRequest data model. Lists all outstanding invitations for a group. Returns
/// a list of entities that have been invited, as well as when the invitation will expire. To get the
/// group invitations for a specific entity, use ListMembershipOpportunities.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsListGroupInvitationsRequest
{
	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// The identifier of the group.
	/// </summary>
	TSharedPtr<const FPFEntityKey> group;
};

/// <summary>
/// FPFGroupsGroupInvitation data model. Describes an invitation to a group.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsGroupInvitation
{
	/// <summary>
	/// When the invitation will expire and be deleted.
	/// </summary>
	FDateTime expires;

	/// <summary>
	/// (Optional) The group that the entity invited to.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> group;

	/// <summary>
	/// (Optional) The entity that created the invitation.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFGroupsEntityWithLineage> invitedByEntity;

	/// <summary>
	/// (Optional) The entity that is invited.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFGroupsEntityWithLineage> invitedEntity;

	/// <summary>
	/// (Optional) ID of the role in the group to assign the user to.
	/// </summary>
	_Maybenull_ const FString roleId;
};

/// <summary>
/// FPFGroupsListGroupInvitationsResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsListGroupInvitationsResponse
{
	/// <summary>
	/// (Optional) The requested list of group invitations.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFGroupsGroupInvitation>> invitations;

	/// <summary>
	/// Count of invitations
	/// </summary>
	uint32 invitationsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFGroupsListGroupMembersRequest data model. Gets a list of members and the roles they belong to
/// within the group. If the caller does not have permission to view the role, and the member is in no
/// other role, the member is not displayed. Returns a list of entities that are members of the group.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsListGroupMembersRequest
{
	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// ID of the group to list the members and roles for.
	/// </summary>
	TSharedPtr<const FPFEntityKey> group;
};

/// <summary>
/// FPFGroupsEntityMemberRole data model.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsEntityMemberRole
{
	/// <summary>
	/// (Optional) The list of members in the role.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFGroupsEntityWithLineage>> members;

	/// <summary>
	/// Count of members
	/// </summary>
	uint32 membersCount;

	/// <summary>
	/// (Optional) The ID of the role.
	/// </summary>
	_Maybenull_ const FString roleId;

	/// <summary>
	/// (Optional) The name of the role.
	/// </summary>
	_Maybenull_ const FString roleName;
};

/// <summary>
/// FPFGroupsListGroupMembersResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsListGroupMembersResponse
{
	/// <summary>
	/// (Optional) The requested list of roles and member entity IDs.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFGroupsEntityMemberRole>> members;

	/// <summary>
	/// Count of members
	/// </summary>
	uint32 membersCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFGroupsListMembershipRequest data model. Lists the groups and roles that an entity is a part of,
/// checking to see if group and role metadata and memberships should be visible to the caller. If the
/// entity is not in any roles that are visible to the caller, the group is not returned in the results,
/// even if the caller otherwise has permission to see that the entity is a member of that group.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsListMembershipRequest
{
	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// (Optional) The optional entity to perform this action on. Defaults to the currently logged in entity.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;
};

/// <summary>
/// FPFGroupsGroupRole data model. Describes a group role.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsGroupRole
{
	/// <summary>
	/// (Optional) ID for the role.
	/// </summary>
	_Maybenull_ const FString roleId;

	/// <summary>
	/// (Optional) The name of the role.
	/// </summary>
	_Maybenull_ const FString roleName;
};

/// <summary>
/// FPFGroupsGroupWithRoles data model. Describes a group and the roles that it contains.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsGroupWithRoles
{
	/// <summary>
	/// (Optional) ID for the group.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> group;

	/// <summary>
	/// (Optional) The name of the group.
	/// </summary>
	_Maybenull_ const FString groupName;

	/// <summary>
	/// The current version of the profile, can be used for concurrency control during updates.
	/// </summary>
	int32 profileVersion;

	/// <summary>
	/// (Optional) The list of roles within the group.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFGroupsGroupRole>> roles;

	/// <summary>
	/// Count of roles
	/// </summary>
	uint32 rolesCount;
};

/// <summary>
/// FPFGroupsListMembershipResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsListMembershipResponse
{
	/// <summary>
	/// (Optional) The list of groups.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFGroupsGroupWithRoles>> groups;

	/// <summary>
	/// Count of groups
	/// </summary>
	uint32 groupsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFGroupsListMembershipOpportunitiesRequest data model. Lists all outstanding group applications
/// and invitations for an entity. Anyone may call this for any entity, but data will only be returned
/// for the entity or a parent of that entity. To list invitations or applications for a group to check
/// if a player is trying to join, use ListGroupInvitations and ListGroupApplications.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsListMembershipOpportunitiesRequest
{
	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// (Optional) The optional entity to perform this action on. Defaults to the currently logged in entity.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;
};

/// <summary>
/// FPFGroupsListMembershipOpportunitiesResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsListMembershipOpportunitiesResponse
{
	/// <summary>
	/// (Optional) The requested list of group applications.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFGroupsGroupApplication>> applications;

	/// <summary>
	/// Count of applications
	/// </summary>
	uint32 applicationsCount;

	/// <summary>
	/// (Optional) The requested list of group invitations.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFGroupsGroupInvitation>> invitations;

	/// <summary>
	/// Count of invitations
	/// </summary>
	uint32 invitationsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFGroupsRemoveGroupApplicationRequest data model. Removes an existing application to join the group.
/// This is used for both rejection of an application as well as withdrawing an application. The applying
/// entity or a parent in its chain (e.g. title) may withdraw the application, and any caller with appropriate
/// access in the group may reject an application. No data is returned in the case of success.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsRemoveGroupApplicationRequest
{
	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// The entity to perform this action on.
	/// </summary>
	TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// The identifier of the group.
	/// </summary>
	TSharedPtr<const FPFEntityKey> group;
};

/// <summary>
/// FPFGroupsRemoveGroupInvitationRequest data model. Removes an existing invitation to join the group.
/// This is used for both rejection of an invitation as well as rescinding an invitation. The invited
/// entity or a parent in its chain (e.g. title) may reject the invitation by calling this method, and
/// any caller with appropriate access in the group may rescind an invitation. No data is returned in
/// the case of success.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsRemoveGroupInvitationRequest
{
	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// The entity to perform this action on.
	/// </summary>
	TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// The identifier of the group.
	/// </summary>
	TSharedPtr<const FPFEntityKey> group;
};

/// <summary>
/// FPFGroupsRemoveMembersRequest data model. Removes members from a group. A member can always remove
/// themselves from a group, regardless of permissions. Returns nothing if successful.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsRemoveMembersRequest
{
	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// The identifier of the group.
	/// </summary>
	TSharedPtr<const FPFEntityKey> group;

	/// <summary>
	/// List of entities to remove.
	/// </summary>
	TArray<TSharedPtr<const FPFEntityKey>> members;

	/// <summary>
	/// Count of members
	/// </summary>
	uint32 membersCount;

	/// <summary>
	/// (Optional) The ID of the role to remove the entities from.
	/// </summary>
	_Maybenull_ const FString roleId;
};

/// <summary>
/// FPFGroupsUnblockEntityRequest data model. Unblocks a list of entities from joining a group. No data
/// is returned in the case of success.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsUnblockEntityRequest
{
	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// The entity to perform this action on.
	/// </summary>
	TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// The identifier of the group.
	/// </summary>
	TSharedPtr<const FPFEntityKey> group;
};

/// <summary>
/// FPFGroupsUpdateGroupRequest data model. Updates data about a group, such as the name or default member
/// role. Returns information about whether the update was successful. Only title claimants may modify
/// the administration role for a group.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsUpdateGroupRequest
{
	/// <summary>
	/// (Optional) Optional: the ID of an existing role to set as the new administrator role for the group.
	/// </summary>
	_Maybenull_ const FString adminRoleId;

	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// (Optional) Optional field used for concurrency control. By specifying the previously returned value
	/// of ProfileVersion from the GetGroup API, you can ensure that the group data update will only be performed
	/// if the group has not been updated by any other clients since the version you last loaded.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> expectedProfileVersion;

	/// <summary>
	/// The identifier of the group.
	/// </summary>
	TSharedPtr<const FPFEntityKey> group;

	/// <summary>
	/// (Optional) Optional: the new name of the group.
	/// </summary>
	_Maybenull_ const FString groupName;

	/// <summary>
	/// (Optional) Optional: the ID of an existing role to set as the new member role for the group.
	/// </summary>
	_Maybenull_ const FString memberRoleId;
};

/// <summary>
/// FPFGroupsUpdateGroupResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsUpdateGroupResponse
{
	/// <summary>
	/// (Optional) Optional reason to explain why the operation was the result that it was.
	/// </summary>
	_Maybenull_ const FString operationReason;

	/// <summary>
	/// New version of the group data.
	/// </summary>
	int32 profileVersion;

	/// <summary>
	/// (Optional) Indicates which operation was completed, either Created, Updated, Deleted or None.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFOperationTypes> setResult;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFGroupsUpdateGroupRoleRequest data model. Updates the role name. Returns information about whether
/// the update was successful.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsUpdateGroupRoleRequest
{
	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// (Optional) Optional field used for concurrency control. By specifying the previously returned value
	/// of ProfileVersion from the GetGroup API, you can ensure that the group data update will only be performed
	/// if the group has not been updated by any other clients since the version you last loaded.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> expectedProfileVersion;

	/// <summary>
	/// The identifier of the group.
	/// </summary>
	TSharedPtr<const FPFEntityKey> group;

	/// <summary>
	/// (Optional) ID of the role to update. Role IDs must be between 1 and 64 characters long.
	/// </summary>
	_Maybenull_ const FString roleId;

	/// <summary>
	/// The new name of the role.
	/// </summary>
	const FString roleName;
};

/// <summary>
/// FPFGroupsUpdateGroupRoleResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFGroupsUpdateGroupRoleResponse
{
	/// <summary>
	/// (Optional) Optional reason to explain why the operation was the result that it was.
	/// </summary>
	_Maybenull_ const FString operationReason;

	/// <summary>
	/// New version of the role data.
	/// </summary>
	int32 profileVersion;

	/// <summary>
	/// (Optional) Indicates which operation was completed, either Created, Updated, Deleted or None.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFOperationTypes> setResult;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

// Delegates Declarations

DECLARE_DELEGATE_TwoParams(FOnAcceptGroupApplicationCompleted, const FString&, bool);

DECLARE_DELEGATE_TwoParams(FOnAcceptGroupInvitationCompleted, const FString&, bool);

DECLARE_DELEGATE_TwoParams(FOnAddMembersCompleted, const FString&, bool);

DECLARE_DELEGATE_TwoParams(FOnApplyToGroupCompleted, const FPFGroupsApplyToGroupResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnBlockEntityCompleted, const FString&, bool);

DECLARE_DELEGATE_TwoParams(FOnChangeMemberRoleCompleted, const FString&, bool);

DECLARE_DELEGATE_TwoParams(FOnCreateGroupCompleted, const FPFGroupsCreateGroupResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnCreateRoleCompleted, const FPFGroupsCreateGroupRoleResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnDeleteGroupCompleted, const FString&, bool);

DECLARE_DELEGATE_TwoParams(FOnDeleteRoleCompleted, const FString&, bool);

DECLARE_DELEGATE_TwoParams(FOnGetGroupCompleted, const FPFGroupsGetGroupResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnInviteToGroupCompleted, const FPFGroupsInviteToGroupResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnIsMemberCompleted, const FPFGroupsIsMemberResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnListGroupApplicationsCompleted, const FPFGroupsListGroupApplicationsResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnListGroupBlocksCompleted, const FPFGroupsListGroupBlocksResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnListGroupInvitationsCompleted, const FPFGroupsListGroupInvitationsResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnListGroupMembersCompleted, const FPFGroupsListGroupMembersResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnListMembershipCompleted, const FPFGroupsListMembershipResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnListMembershipOpportunitiesCompleted, const FPFGroupsListMembershipOpportunitiesResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnRemoveGroupApplicationCompleted, const FString&, bool);

DECLARE_DELEGATE_TwoParams(FOnRemoveGroupInvitationCompleted, const FString&, bool);

DECLARE_DELEGATE_TwoParams(FOnRemoveMembersCompleted, const FString&, bool);

DECLARE_DELEGATE_TwoParams(FOnUnblockEntityCompleted, const FString&, bool);

DECLARE_DELEGATE_TwoParams(FOnUpdateGroupCompleted, const FPFGroupsUpdateGroupResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnUpdateRoleCompleted, const FPFGroupsUpdateGroupRoleResponse&, bool);

#pragma pop_macro("IN")