// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFGroupsTypeConverters.h"

TSharedPtr<const FPFGroupsAcceptGroupApplicationRequest> ConvertAcceptGroupApplicationRequestToUnreal(const PFGroupsAcceptGroupApplicationRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsAcceptGroupApplicationRequest> ConvertedType = MakeShared<FPFGroupsAcceptGroupApplicationRequest>(FPFGroupsAcceptGroupApplicationRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.group = ConvertEntityKeyToUnreal(Datatype->group)
	});

	return ConvertedType;
}

const PFGroupsAcceptGroupApplicationRequest* ConvertAcceptGroupApplicationRequestToPlayfab(TSharedPtr<const FPFGroupsAcceptGroupApplicationRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsAcceptGroupApplicationRequest* ConvertedType = new PFGroupsAcceptGroupApplicationRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.group = ConvertEntityKeyToPlayfab(Datatype->group)
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsAcceptGroupInvitationRequest> ConvertAcceptGroupInvitationRequestToUnreal(const PFGroupsAcceptGroupInvitationRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsAcceptGroupInvitationRequest> ConvertedType = MakeShared<FPFGroupsAcceptGroupInvitationRequest>(FPFGroupsAcceptGroupInvitationRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.group = ConvertEntityKeyToUnreal(Datatype->group)
	});

	return ConvertedType;
}

const PFGroupsAcceptGroupInvitationRequest* ConvertAcceptGroupInvitationRequestToPlayfab(TSharedPtr<const FPFGroupsAcceptGroupInvitationRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsAcceptGroupInvitationRequest* ConvertedType = new PFGroupsAcceptGroupInvitationRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.group = ConvertEntityKeyToPlayfab(Datatype->group)
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsAddMembersRequest> ConvertAddMembersRequestToUnreal(const PFGroupsAddMembersRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsAddMembersRequest> ConvertedType = MakeShared<FPFGroupsAddMembersRequest>(FPFGroupsAddMembersRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.group = ConvertEntityKeyToUnreal(Datatype->group),
		.members = ConvertPlayfabArrayToUnreal<PFEntityKey, FPFEntityKey>(Datatype->members, Datatype->membersCount, ConvertEntityKeyToUnreal),
		.membersCount = Datatype->membersCount,
		.roleId = Datatype->roleId == nullptr ? FString() : FString(Datatype->roleId)
	});

	return ConvertedType;
}

const PFGroupsAddMembersRequest* ConvertAddMembersRequestToPlayfab(TSharedPtr<const FPFGroupsAddMembersRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsAddMembersRequest* ConvertedType = new PFGroupsAddMembersRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.group = ConvertEntityKeyToPlayfab(Datatype->group),
		.members = ConvertUnrealArrayToPlayfab<PFEntityKey, FPFEntityKey>(Datatype->members, ConvertEntityKeyToPlayfab),
		.membersCount = (uint32_t)Datatype->members.Num(),
		.roleId = ConvertFStringToCharPtr(Datatype->roleId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsApplyToGroupRequest> ConvertApplyToGroupRequestToUnreal(const PFGroupsApplyToGroupRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsApplyToGroupRequest> ConvertedType = MakeShared<FPFGroupsApplyToGroupRequest>(FPFGroupsApplyToGroupRequest{
		.autoAcceptOutstandingInvite = TSharedPtr<const bool>(Datatype->autoAcceptOutstandingInvite),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.group = ConvertEntityKeyToUnreal(Datatype->group)
	});

	return ConvertedType;
}

const PFGroupsApplyToGroupRequest* ConvertApplyToGroupRequestToPlayfab(TSharedPtr<const FPFGroupsApplyToGroupRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsApplyToGroupRequest* ConvertedType = new PFGroupsApplyToGroupRequest{
		.autoAcceptOutstandingInvite = Datatype->autoAcceptOutstandingInvite ? new bool(*Datatype->autoAcceptOutstandingInvite) : nullptr,
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.group = ConvertEntityKeyToPlayfab(Datatype->group)
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsEntityWithLineage> ConvertEntityWithLineageToUnreal(const PFGroupsEntityWithLineage* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsEntityWithLineage> ConvertedType = MakeShared<FPFGroupsEntityWithLineage>(FPFGroupsEntityWithLineage{
		.key = ConvertEntityKeyToUnreal(Datatype->key),
		.lineage = ConvertPlayfabMapToUnreal<PFEntityKeyDictionaryEntry, FPFEntityKey, PFEntityKey>(Datatype->lineage, Datatype->lineageCount, ConvertEntityKeyToUnreal),
		.lineageCount = Datatype->lineageCount
	});

	return ConvertedType;
}

const PFGroupsEntityWithLineage* ConvertEntityWithLineageToPlayfab(TSharedPtr<const FPFGroupsEntityWithLineage> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsEntityWithLineage* ConvertedType = new PFGroupsEntityWithLineage{
		.key = ConvertEntityKeyToPlayfab(Datatype->key),
		.lineage = ConvertUnrealMapToPlayfab<PFEntityKeyDictionaryEntry, FPFEntityKey, PFEntityKey>(Datatype->lineage, ConvertEntityKeyToPlayfab),
		.lineageCount = (uint32_t)Datatype->lineage.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsApplyToGroupResponse> ConvertApplyToGroupResponseToUnreal(const PFGroupsApplyToGroupResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsApplyToGroupResponse> ConvertedType = MakeShared<FPFGroupsApplyToGroupResponse>(FPFGroupsApplyToGroupResponse{
		.entity = ConvertEntityWithLineageToUnreal(Datatype->entity),
		.expires = FDateTime::FromUnixTimestamp((int64)Datatype->expires),
		.group = ConvertEntityKeyToUnreal(Datatype->group)
	});

	return ConvertedType;
}

const PFGroupsApplyToGroupResponse* ConvertApplyToGroupResponseToPlayfab(TSharedPtr<const FPFGroupsApplyToGroupResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsApplyToGroupResponse* ConvertedType = new PFGroupsApplyToGroupResponse{
		.entity = ConvertEntityWithLineageToPlayfab(Datatype->entity),
		.expires = Datatype->expires.ToUnixTimestamp(),
		.group = ConvertEntityKeyToPlayfab(Datatype->group)
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsBlockEntityRequest> ConvertBlockEntityRequestToUnreal(const PFGroupsBlockEntityRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsBlockEntityRequest> ConvertedType = MakeShared<FPFGroupsBlockEntityRequest>(FPFGroupsBlockEntityRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.group = ConvertEntityKeyToUnreal(Datatype->group)
	});

	return ConvertedType;
}

const PFGroupsBlockEntityRequest* ConvertBlockEntityRequestToPlayfab(TSharedPtr<const FPFGroupsBlockEntityRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsBlockEntityRequest* ConvertedType = new PFGroupsBlockEntityRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.group = ConvertEntityKeyToPlayfab(Datatype->group)
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsChangeMemberRoleRequest> ConvertChangeMemberRoleRequestToUnreal(const PFGroupsChangeMemberRoleRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsChangeMemberRoleRequest> ConvertedType = MakeShared<FPFGroupsChangeMemberRoleRequest>(FPFGroupsChangeMemberRoleRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.destinationRoleId = Datatype->destinationRoleId == nullptr ? FString() : FString(Datatype->destinationRoleId),
		.group = ConvertEntityKeyToUnreal(Datatype->group),
		.members = ConvertPlayfabArrayToUnreal<PFEntityKey, FPFEntityKey>(Datatype->members, Datatype->membersCount, ConvertEntityKeyToUnreal),
		.membersCount = Datatype->membersCount,
		.originRoleId = Datatype->originRoleId == nullptr ? FString() : FString(Datatype->originRoleId)
	});

	return ConvertedType;
}

const PFGroupsChangeMemberRoleRequest* ConvertChangeMemberRoleRequestToPlayfab(TSharedPtr<const FPFGroupsChangeMemberRoleRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsChangeMemberRoleRequest* ConvertedType = new PFGroupsChangeMemberRoleRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.destinationRoleId = ConvertFStringToCharPtr(Datatype->destinationRoleId),
		.group = ConvertEntityKeyToPlayfab(Datatype->group),
		.members = ConvertUnrealArrayToPlayfab<PFEntityKey, FPFEntityKey>(Datatype->members, ConvertEntityKeyToPlayfab),
		.membersCount = (uint32_t)Datatype->members.Num(),
		.originRoleId = ConvertFStringToCharPtr(Datatype->originRoleId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsCreateGroupRequest> ConvertCreateGroupRequestToUnreal(const PFGroupsCreateGroupRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsCreateGroupRequest> ConvertedType = MakeShared<FPFGroupsCreateGroupRequest>(FPFGroupsCreateGroupRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.groupName = Datatype->groupName == nullptr ? FString() : FString(Datatype->groupName)
	});

	return ConvertedType;
}

const PFGroupsCreateGroupRequest* ConvertCreateGroupRequestToPlayfab(TSharedPtr<const FPFGroupsCreateGroupRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsCreateGroupRequest* ConvertedType = new PFGroupsCreateGroupRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.groupName = ConvertFStringToCharPtr(Datatype->groupName)
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsCreateGroupResponse> ConvertCreateGroupResponseToUnreal(const PFGroupsCreateGroupResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsCreateGroupResponse> ConvertedType = MakeShared<FPFGroupsCreateGroupResponse>(FPFGroupsCreateGroupResponse{
		.adminRoleId = Datatype->adminRoleId == nullptr ? FString() : FString(Datatype->adminRoleId),
		.created = FDateTime::FromUnixTimestamp((int64)Datatype->created),
		.group = ConvertEntityKeyToUnreal(Datatype->group),
		.groupName = Datatype->groupName == nullptr ? FString() : FString(Datatype->groupName),
		.memberRoleId = Datatype->memberRoleId == nullptr ? FString() : FString(Datatype->memberRoleId),
		.profileVersion = Datatype->profileVersion,
		.roles = ConvertCharMapToUnreal(Datatype->roles, Datatype->rolesCount),
		.rolesCount = Datatype->rolesCount
	});

	return ConvertedType;
}

const PFGroupsCreateGroupResponse* ConvertCreateGroupResponseToPlayfab(TSharedPtr<const FPFGroupsCreateGroupResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsCreateGroupResponse* ConvertedType = new PFGroupsCreateGroupResponse{
		.adminRoleId = ConvertFStringToCharPtr(Datatype->adminRoleId),
		.created = Datatype->created.ToUnixTimestamp(),
		.group = ConvertEntityKeyToPlayfab(Datatype->group),
		.groupName = ConvertFStringToCharPtr(Datatype->groupName),
		.memberRoleId = ConvertFStringToCharPtr(Datatype->memberRoleId),
		.profileVersion = Datatype->profileVersion,
		.roles = ConvertFStringMapToPlayfab(Datatype->roles),
		.rolesCount = (uint32_t)Datatype->roles.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsCreateGroupRoleRequest> ConvertCreateGroupRoleRequestToUnreal(const PFGroupsCreateGroupRoleRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsCreateGroupRoleRequest> ConvertedType = MakeShared<FPFGroupsCreateGroupRoleRequest>(FPFGroupsCreateGroupRoleRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.group = ConvertEntityKeyToUnreal(Datatype->group),
		.roleId = Datatype->roleId == nullptr ? FString() : FString(Datatype->roleId),
		.roleName = Datatype->roleName == nullptr ? FString() : FString(Datatype->roleName)
	});

	return ConvertedType;
}

const PFGroupsCreateGroupRoleRequest* ConvertCreateGroupRoleRequestToPlayfab(TSharedPtr<const FPFGroupsCreateGroupRoleRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsCreateGroupRoleRequest* ConvertedType = new PFGroupsCreateGroupRoleRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.group = ConvertEntityKeyToPlayfab(Datatype->group),
		.roleId = ConvertFStringToCharPtr(Datatype->roleId),
		.roleName = ConvertFStringToCharPtr(Datatype->roleName)
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsCreateGroupRoleResponse> ConvertCreateGroupRoleResponseToUnreal(const PFGroupsCreateGroupRoleResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsCreateGroupRoleResponse> ConvertedType = MakeShared<FPFGroupsCreateGroupRoleResponse>(FPFGroupsCreateGroupRoleResponse{
		.profileVersion = Datatype->profileVersion,
		.roleId = Datatype->roleId == nullptr ? FString() : FString(Datatype->roleId),
		.roleName = Datatype->roleName == nullptr ? FString() : FString(Datatype->roleName)
	});

	return ConvertedType;
}

const PFGroupsCreateGroupRoleResponse* ConvertCreateGroupRoleResponseToPlayfab(TSharedPtr<const FPFGroupsCreateGroupRoleResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsCreateGroupRoleResponse* ConvertedType = new PFGroupsCreateGroupRoleResponse{
		.profileVersion = Datatype->profileVersion,
		.roleId = ConvertFStringToCharPtr(Datatype->roleId),
		.roleName = ConvertFStringToCharPtr(Datatype->roleName)
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsDeleteGroupRequest> ConvertDeleteGroupRequestToUnreal(const PFGroupsDeleteGroupRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsDeleteGroupRequest> ConvertedType = MakeShared<FPFGroupsDeleteGroupRequest>(FPFGroupsDeleteGroupRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.group = ConvertEntityKeyToUnreal(Datatype->group)
	});

	return ConvertedType;
}

const PFGroupsDeleteGroupRequest* ConvertDeleteGroupRequestToPlayfab(TSharedPtr<const FPFGroupsDeleteGroupRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsDeleteGroupRequest* ConvertedType = new PFGroupsDeleteGroupRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.group = ConvertEntityKeyToPlayfab(Datatype->group)
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsDeleteRoleRequest> ConvertDeleteRoleRequestToUnreal(const PFGroupsDeleteRoleRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsDeleteRoleRequest> ConvertedType = MakeShared<FPFGroupsDeleteRoleRequest>(FPFGroupsDeleteRoleRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.group = ConvertEntityKeyToUnreal(Datatype->group),
		.roleId = Datatype->roleId == nullptr ? FString() : FString(Datatype->roleId)
	});

	return ConvertedType;
}

const PFGroupsDeleteRoleRequest* ConvertDeleteRoleRequestToPlayfab(TSharedPtr<const FPFGroupsDeleteRoleRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsDeleteRoleRequest* ConvertedType = new PFGroupsDeleteRoleRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.group = ConvertEntityKeyToPlayfab(Datatype->group),
		.roleId = ConvertFStringToCharPtr(Datatype->roleId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsGetGroupRequest> ConvertGetGroupRequestToUnreal(const PFGroupsGetGroupRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsGetGroupRequest> ConvertedType = MakeShared<FPFGroupsGetGroupRequest>(FPFGroupsGetGroupRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.group = ConvertEntityKeyToUnreal(Datatype->group),
		.groupName = Datatype->groupName == nullptr ? FString() : FString(Datatype->groupName)
	});

	return ConvertedType;
}

const PFGroupsGetGroupRequest* ConvertGetGroupRequestToPlayfab(TSharedPtr<const FPFGroupsGetGroupRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsGetGroupRequest* ConvertedType = new PFGroupsGetGroupRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.group = ConvertEntityKeyToPlayfab(Datatype->group),
		.groupName = ConvertFStringToCharPtr(Datatype->groupName)
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsGetGroupResponse> ConvertGetGroupResponseToUnreal(const PFGroupsGetGroupResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsGetGroupResponse> ConvertedType = MakeShared<FPFGroupsGetGroupResponse>(FPFGroupsGetGroupResponse{
		.adminRoleId = Datatype->adminRoleId == nullptr ? FString() : FString(Datatype->adminRoleId),
		.created = FDateTime::FromUnixTimestamp((int64)Datatype->created),
		.group = ConvertEntityKeyToUnreal(Datatype->group),
		.groupName = Datatype->groupName == nullptr ? FString() : FString(Datatype->groupName),
		.memberRoleId = Datatype->memberRoleId == nullptr ? FString() : FString(Datatype->memberRoleId),
		.profileVersion = Datatype->profileVersion,
		.roles = ConvertCharMapToUnreal(Datatype->roles, Datatype->rolesCount),
		.rolesCount = Datatype->rolesCount
	});

	return ConvertedType;
}

const PFGroupsGetGroupResponse* ConvertGetGroupResponseToPlayfab(TSharedPtr<const FPFGroupsGetGroupResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsGetGroupResponse* ConvertedType = new PFGroupsGetGroupResponse{
		.adminRoleId = ConvertFStringToCharPtr(Datatype->adminRoleId),
		.created = Datatype->created.ToUnixTimestamp(),
		.group = ConvertEntityKeyToPlayfab(Datatype->group),
		.groupName = ConvertFStringToCharPtr(Datatype->groupName),
		.memberRoleId = ConvertFStringToCharPtr(Datatype->memberRoleId),
		.profileVersion = Datatype->profileVersion,
		.roles = ConvertFStringMapToPlayfab(Datatype->roles),
		.rolesCount = (uint32_t)Datatype->roles.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsInviteToGroupRequest> ConvertInviteToGroupRequestToUnreal(const PFGroupsInviteToGroupRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsInviteToGroupRequest> ConvertedType = MakeShared<FPFGroupsInviteToGroupRequest>(FPFGroupsInviteToGroupRequest{
		.autoAcceptOutstandingApplication = TSharedPtr<const bool>(Datatype->autoAcceptOutstandingApplication),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.group = ConvertEntityKeyToUnreal(Datatype->group),
		.roleId = Datatype->roleId == nullptr ? FString() : FString(Datatype->roleId)
	});

	return ConvertedType;
}

const PFGroupsInviteToGroupRequest* ConvertInviteToGroupRequestToPlayfab(TSharedPtr<const FPFGroupsInviteToGroupRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsInviteToGroupRequest* ConvertedType = new PFGroupsInviteToGroupRequest{
		.autoAcceptOutstandingApplication = Datatype->autoAcceptOutstandingApplication ? new bool(*Datatype->autoAcceptOutstandingApplication) : nullptr,
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.group = ConvertEntityKeyToPlayfab(Datatype->group),
		.roleId = ConvertFStringToCharPtr(Datatype->roleId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsInviteToGroupResponse> ConvertInviteToGroupResponseToUnreal(const PFGroupsInviteToGroupResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsInviteToGroupResponse> ConvertedType = MakeShared<FPFGroupsInviteToGroupResponse>(FPFGroupsInviteToGroupResponse{
		.expires = FDateTime::FromUnixTimestamp((int64)Datatype->expires),
		.group = ConvertEntityKeyToUnreal(Datatype->group),
		.invitedByEntity = ConvertEntityWithLineageToUnreal(Datatype->invitedByEntity),
		.invitedEntity = ConvertEntityWithLineageToUnreal(Datatype->invitedEntity),
		.roleId = Datatype->roleId == nullptr ? FString() : FString(Datatype->roleId)
	});

	return ConvertedType;
}

const PFGroupsInviteToGroupResponse* ConvertInviteToGroupResponseToPlayfab(TSharedPtr<const FPFGroupsInviteToGroupResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsInviteToGroupResponse* ConvertedType = new PFGroupsInviteToGroupResponse{
		.expires = Datatype->expires.ToUnixTimestamp(),
		.group = ConvertEntityKeyToPlayfab(Datatype->group),
		.invitedByEntity = ConvertEntityWithLineageToPlayfab(Datatype->invitedByEntity),
		.invitedEntity = ConvertEntityWithLineageToPlayfab(Datatype->invitedEntity),
		.roleId = ConvertFStringToCharPtr(Datatype->roleId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsIsMemberRequest> ConvertIsMemberRequestToUnreal(const PFGroupsIsMemberRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsIsMemberRequest> ConvertedType = MakeShared<FPFGroupsIsMemberRequest>(FPFGroupsIsMemberRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.group = ConvertEntityKeyToUnreal(Datatype->group),
		.roleId = Datatype->roleId == nullptr ? FString() : FString(Datatype->roleId)
	});

	return ConvertedType;
}

const PFGroupsIsMemberRequest* ConvertIsMemberRequestToPlayfab(TSharedPtr<const FPFGroupsIsMemberRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsIsMemberRequest* ConvertedType = new PFGroupsIsMemberRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.group = ConvertEntityKeyToPlayfab(Datatype->group),
		.roleId = ConvertFStringToCharPtr(Datatype->roleId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsIsMemberResponse> ConvertIsMemberResponseToUnreal(const PFGroupsIsMemberResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsIsMemberResponse> ConvertedType = MakeShared<FPFGroupsIsMemberResponse>(FPFGroupsIsMemberResponse{
		.isMember = Datatype->isMember
	});

	return ConvertedType;
}

const PFGroupsIsMemberResponse* ConvertIsMemberResponseToPlayfab(TSharedPtr<const FPFGroupsIsMemberResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsIsMemberResponse* ConvertedType = new PFGroupsIsMemberResponse{
		.isMember = Datatype->isMember
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsListGroupApplicationsRequest> ConvertListGroupApplicationsRequestToUnreal(const PFGroupsListGroupApplicationsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsListGroupApplicationsRequest> ConvertedType = MakeShared<FPFGroupsListGroupApplicationsRequest>(FPFGroupsListGroupApplicationsRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.group = ConvertEntityKeyToUnreal(Datatype->group)
	});

	return ConvertedType;
}

const PFGroupsListGroupApplicationsRequest* ConvertListGroupApplicationsRequestToPlayfab(TSharedPtr<const FPFGroupsListGroupApplicationsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsListGroupApplicationsRequest* ConvertedType = new PFGroupsListGroupApplicationsRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.group = ConvertEntityKeyToPlayfab(Datatype->group)
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsGroupApplication> ConvertGroupApplicationToUnreal(const PFGroupsGroupApplication* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsGroupApplication> ConvertedType = MakeShared<FPFGroupsGroupApplication>(FPFGroupsGroupApplication{
		.entity = ConvertEntityWithLineageToUnreal(Datatype->entity),
		.expires = FDateTime::FromUnixTimestamp((int64)Datatype->expires),
		.group = ConvertEntityKeyToUnreal(Datatype->group)
	});

	return ConvertedType;
}

const PFGroupsGroupApplication* ConvertGroupApplicationToPlayfab(TSharedPtr<const FPFGroupsGroupApplication> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsGroupApplication* ConvertedType = new PFGroupsGroupApplication{
		.entity = ConvertEntityWithLineageToPlayfab(Datatype->entity),
		.expires = Datatype->expires.ToUnixTimestamp(),
		.group = ConvertEntityKeyToPlayfab(Datatype->group)
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsListGroupApplicationsResponse> ConvertListGroupApplicationsResponseToUnreal(const PFGroupsListGroupApplicationsResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsListGroupApplicationsResponse> ConvertedType = MakeShared<FPFGroupsListGroupApplicationsResponse>(FPFGroupsListGroupApplicationsResponse{
		.applications = ConvertPlayfabArrayToUnreal<PFGroupsGroupApplication, FPFGroupsGroupApplication>(Datatype->applications, Datatype->applicationsCount, ConvertGroupApplicationToUnreal),
		.applicationsCount = Datatype->applicationsCount
	});

	return ConvertedType;
}

const PFGroupsListGroupApplicationsResponse* ConvertListGroupApplicationsResponseToPlayfab(TSharedPtr<const FPFGroupsListGroupApplicationsResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsListGroupApplicationsResponse* ConvertedType = new PFGroupsListGroupApplicationsResponse{
		.applications = ConvertUnrealArrayToPlayfab<PFGroupsGroupApplication, FPFGroupsGroupApplication>(Datatype->applications, ConvertGroupApplicationToPlayfab),
		.applicationsCount = (uint32_t)Datatype->applications.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsListGroupBlocksRequest> ConvertListGroupBlocksRequestToUnreal(const PFGroupsListGroupBlocksRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsListGroupBlocksRequest> ConvertedType = MakeShared<FPFGroupsListGroupBlocksRequest>(FPFGroupsListGroupBlocksRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.group = ConvertEntityKeyToUnreal(Datatype->group)
	});

	return ConvertedType;
}

const PFGroupsListGroupBlocksRequest* ConvertListGroupBlocksRequestToPlayfab(TSharedPtr<const FPFGroupsListGroupBlocksRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsListGroupBlocksRequest* ConvertedType = new PFGroupsListGroupBlocksRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.group = ConvertEntityKeyToPlayfab(Datatype->group)
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsGroupBlock> ConvertGroupBlockToUnreal(const PFGroupsGroupBlock* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsGroupBlock> ConvertedType = MakeShared<FPFGroupsGroupBlock>(FPFGroupsGroupBlock{
		.entity = ConvertEntityWithLineageToUnreal(Datatype->entity),
		.group = ConvertEntityKeyToUnreal(Datatype->group)
	});

	return ConvertedType;
}

const PFGroupsGroupBlock* ConvertGroupBlockToPlayfab(TSharedPtr<const FPFGroupsGroupBlock> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsGroupBlock* ConvertedType = new PFGroupsGroupBlock{
		.entity = ConvertEntityWithLineageToPlayfab(Datatype->entity),
		.group = ConvertEntityKeyToPlayfab(Datatype->group)
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsListGroupBlocksResponse> ConvertListGroupBlocksResponseToUnreal(const PFGroupsListGroupBlocksResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsListGroupBlocksResponse> ConvertedType = MakeShared<FPFGroupsListGroupBlocksResponse>(FPFGroupsListGroupBlocksResponse{
		.blockedEntities = ConvertPlayfabArrayToUnreal<PFGroupsGroupBlock, FPFGroupsGroupBlock>(Datatype->blockedEntities, Datatype->blockedEntitiesCount, ConvertGroupBlockToUnreal),
		.blockedEntitiesCount = Datatype->blockedEntitiesCount
	});

	return ConvertedType;
}

const PFGroupsListGroupBlocksResponse* ConvertListGroupBlocksResponseToPlayfab(TSharedPtr<const FPFGroupsListGroupBlocksResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsListGroupBlocksResponse* ConvertedType = new PFGroupsListGroupBlocksResponse{
		.blockedEntities = ConvertUnrealArrayToPlayfab<PFGroupsGroupBlock, FPFGroupsGroupBlock>(Datatype->blockedEntities, ConvertGroupBlockToPlayfab),
		.blockedEntitiesCount = (uint32_t)Datatype->blockedEntities.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsListGroupInvitationsRequest> ConvertListGroupInvitationsRequestToUnreal(const PFGroupsListGroupInvitationsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsListGroupInvitationsRequest> ConvertedType = MakeShared<FPFGroupsListGroupInvitationsRequest>(FPFGroupsListGroupInvitationsRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.group = ConvertEntityKeyToUnreal(Datatype->group)
	});

	return ConvertedType;
}

const PFGroupsListGroupInvitationsRequest* ConvertListGroupInvitationsRequestToPlayfab(TSharedPtr<const FPFGroupsListGroupInvitationsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsListGroupInvitationsRequest* ConvertedType = new PFGroupsListGroupInvitationsRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.group = ConvertEntityKeyToPlayfab(Datatype->group)
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsGroupInvitation> ConvertGroupInvitationToUnreal(const PFGroupsGroupInvitation* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsGroupInvitation> ConvertedType = MakeShared<FPFGroupsGroupInvitation>(FPFGroupsGroupInvitation{
		.expires = FDateTime::FromUnixTimestamp((int64)Datatype->expires),
		.group = ConvertEntityKeyToUnreal(Datatype->group),
		.invitedByEntity = ConvertEntityWithLineageToUnreal(Datatype->invitedByEntity),
		.invitedEntity = ConvertEntityWithLineageToUnreal(Datatype->invitedEntity),
		.roleId = Datatype->roleId == nullptr ? FString() : FString(Datatype->roleId)
	});

	return ConvertedType;
}

const PFGroupsGroupInvitation* ConvertGroupInvitationToPlayfab(TSharedPtr<const FPFGroupsGroupInvitation> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsGroupInvitation* ConvertedType = new PFGroupsGroupInvitation{
		.expires = Datatype->expires.ToUnixTimestamp(),
		.group = ConvertEntityKeyToPlayfab(Datatype->group),
		.invitedByEntity = ConvertEntityWithLineageToPlayfab(Datatype->invitedByEntity),
		.invitedEntity = ConvertEntityWithLineageToPlayfab(Datatype->invitedEntity),
		.roleId = ConvertFStringToCharPtr(Datatype->roleId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsListGroupInvitationsResponse> ConvertListGroupInvitationsResponseToUnreal(const PFGroupsListGroupInvitationsResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsListGroupInvitationsResponse> ConvertedType = MakeShared<FPFGroupsListGroupInvitationsResponse>(FPFGroupsListGroupInvitationsResponse{
		.invitations = ConvertPlayfabArrayToUnreal<PFGroupsGroupInvitation, FPFGroupsGroupInvitation>(Datatype->invitations, Datatype->invitationsCount, ConvertGroupInvitationToUnreal),
		.invitationsCount = Datatype->invitationsCount
	});

	return ConvertedType;
}

const PFGroupsListGroupInvitationsResponse* ConvertListGroupInvitationsResponseToPlayfab(TSharedPtr<const FPFGroupsListGroupInvitationsResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsListGroupInvitationsResponse* ConvertedType = new PFGroupsListGroupInvitationsResponse{
		.invitations = ConvertUnrealArrayToPlayfab<PFGroupsGroupInvitation, FPFGroupsGroupInvitation>(Datatype->invitations, ConvertGroupInvitationToPlayfab),
		.invitationsCount = (uint32_t)Datatype->invitations.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsListGroupMembersRequest> ConvertListGroupMembersRequestToUnreal(const PFGroupsListGroupMembersRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsListGroupMembersRequest> ConvertedType = MakeShared<FPFGroupsListGroupMembersRequest>(FPFGroupsListGroupMembersRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.group = ConvertEntityKeyToUnreal(Datatype->group)
	});

	return ConvertedType;
}

const PFGroupsListGroupMembersRequest* ConvertListGroupMembersRequestToPlayfab(TSharedPtr<const FPFGroupsListGroupMembersRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsListGroupMembersRequest* ConvertedType = new PFGroupsListGroupMembersRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.group = ConvertEntityKeyToPlayfab(Datatype->group)
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsEntityMemberRole> ConvertEntityMemberRoleToUnreal(const PFGroupsEntityMemberRole* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsEntityMemberRole> ConvertedType = MakeShared<FPFGroupsEntityMemberRole>(FPFGroupsEntityMemberRole{
		.members = ConvertPlayfabArrayToUnreal<PFGroupsEntityWithLineage, FPFGroupsEntityWithLineage>(Datatype->members, Datatype->membersCount, ConvertEntityWithLineageToUnreal),
		.membersCount = Datatype->membersCount,
		.roleId = Datatype->roleId == nullptr ? FString() : FString(Datatype->roleId),
		.roleName = Datatype->roleName == nullptr ? FString() : FString(Datatype->roleName)
	});

	return ConvertedType;
}

const PFGroupsEntityMemberRole* ConvertEntityMemberRoleToPlayfab(TSharedPtr<const FPFGroupsEntityMemberRole> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsEntityMemberRole* ConvertedType = new PFGroupsEntityMemberRole{
		.members = ConvertUnrealArrayToPlayfab<PFGroupsEntityWithLineage, FPFGroupsEntityWithLineage>(Datatype->members, ConvertEntityWithLineageToPlayfab),
		.membersCount = (uint32_t)Datatype->members.Num(),
		.roleId = ConvertFStringToCharPtr(Datatype->roleId),
		.roleName = ConvertFStringToCharPtr(Datatype->roleName)
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsListGroupMembersResponse> ConvertListGroupMembersResponseToUnreal(const PFGroupsListGroupMembersResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsListGroupMembersResponse> ConvertedType = MakeShared<FPFGroupsListGroupMembersResponse>(FPFGroupsListGroupMembersResponse{
		.members = ConvertPlayfabArrayToUnreal<PFGroupsEntityMemberRole, FPFGroupsEntityMemberRole>(Datatype->members, Datatype->membersCount, ConvertEntityMemberRoleToUnreal),
		.membersCount = Datatype->membersCount
	});

	return ConvertedType;
}

const PFGroupsListGroupMembersResponse* ConvertListGroupMembersResponseToPlayfab(TSharedPtr<const FPFGroupsListGroupMembersResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsListGroupMembersResponse* ConvertedType = new PFGroupsListGroupMembersResponse{
		.members = ConvertUnrealArrayToPlayfab<PFGroupsEntityMemberRole, FPFGroupsEntityMemberRole>(Datatype->members, ConvertEntityMemberRoleToPlayfab),
		.membersCount = (uint32_t)Datatype->members.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsListMembershipRequest> ConvertListMembershipRequestToUnreal(const PFGroupsListMembershipRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsListMembershipRequest> ConvertedType = MakeShared<FPFGroupsListMembershipRequest>(FPFGroupsListMembershipRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity)
	});

	return ConvertedType;
}

const PFGroupsListMembershipRequest* ConvertListMembershipRequestToPlayfab(TSharedPtr<const FPFGroupsListMembershipRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsListMembershipRequest* ConvertedType = new PFGroupsListMembershipRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity)
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsGroupRole> ConvertGroupRoleToUnreal(const PFGroupsGroupRole* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsGroupRole> ConvertedType = MakeShared<FPFGroupsGroupRole>(FPFGroupsGroupRole{
		.roleId = Datatype->roleId == nullptr ? FString() : FString(Datatype->roleId),
		.roleName = Datatype->roleName == nullptr ? FString() : FString(Datatype->roleName)
	});

	return ConvertedType;
}

const PFGroupsGroupRole* ConvertGroupRoleToPlayfab(TSharedPtr<const FPFGroupsGroupRole> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsGroupRole* ConvertedType = new PFGroupsGroupRole{
		.roleId = ConvertFStringToCharPtr(Datatype->roleId),
		.roleName = ConvertFStringToCharPtr(Datatype->roleName)
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsGroupWithRoles> ConvertGroupWithRolesToUnreal(const PFGroupsGroupWithRoles* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsGroupWithRoles> ConvertedType = MakeShared<FPFGroupsGroupWithRoles>(FPFGroupsGroupWithRoles{
		.group = ConvertEntityKeyToUnreal(Datatype->group),
		.groupName = Datatype->groupName == nullptr ? FString() : FString(Datatype->groupName),
		.profileVersion = Datatype->profileVersion,
		.roles = ConvertPlayfabArrayToUnreal<PFGroupsGroupRole, FPFGroupsGroupRole>(Datatype->roles, Datatype->rolesCount, ConvertGroupRoleToUnreal),
		.rolesCount = Datatype->rolesCount
	});

	return ConvertedType;
}

const PFGroupsGroupWithRoles* ConvertGroupWithRolesToPlayfab(TSharedPtr<const FPFGroupsGroupWithRoles> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsGroupWithRoles* ConvertedType = new PFGroupsGroupWithRoles{
		.group = ConvertEntityKeyToPlayfab(Datatype->group),
		.groupName = ConvertFStringToCharPtr(Datatype->groupName),
		.profileVersion = Datatype->profileVersion,
		.roles = ConvertUnrealArrayToPlayfab<PFGroupsGroupRole, FPFGroupsGroupRole>(Datatype->roles, ConvertGroupRoleToPlayfab),
		.rolesCount = (uint32_t)Datatype->roles.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsListMembershipResponse> ConvertListMembershipResponseToUnreal(const PFGroupsListMembershipResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsListMembershipResponse> ConvertedType = MakeShared<FPFGroupsListMembershipResponse>(FPFGroupsListMembershipResponse{
		.groups = ConvertPlayfabArrayToUnreal<PFGroupsGroupWithRoles, FPFGroupsGroupWithRoles>(Datatype->groups, Datatype->groupsCount, ConvertGroupWithRolesToUnreal),
		.groupsCount = Datatype->groupsCount
	});

	return ConvertedType;
}

const PFGroupsListMembershipResponse* ConvertListMembershipResponseToPlayfab(TSharedPtr<const FPFGroupsListMembershipResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsListMembershipResponse* ConvertedType = new PFGroupsListMembershipResponse{
		.groups = ConvertUnrealArrayToPlayfab<PFGroupsGroupWithRoles, FPFGroupsGroupWithRoles>(Datatype->groups, ConvertGroupWithRolesToPlayfab),
		.groupsCount = (uint32_t)Datatype->groups.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsListMembershipOpportunitiesRequest> ConvertListMembershipOpportunitiesRequestToUnreal(const PFGroupsListMembershipOpportunitiesRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsListMembershipOpportunitiesRequest> ConvertedType = MakeShared<FPFGroupsListMembershipOpportunitiesRequest>(FPFGroupsListMembershipOpportunitiesRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity)
	});

	return ConvertedType;
}

const PFGroupsListMembershipOpportunitiesRequest* ConvertListMembershipOpportunitiesRequestToPlayfab(TSharedPtr<const FPFGroupsListMembershipOpportunitiesRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsListMembershipOpportunitiesRequest* ConvertedType = new PFGroupsListMembershipOpportunitiesRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity)
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsListMembershipOpportunitiesResponse> ConvertListMembershipOpportunitiesResponseToUnreal(const PFGroupsListMembershipOpportunitiesResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsListMembershipOpportunitiesResponse> ConvertedType = MakeShared<FPFGroupsListMembershipOpportunitiesResponse>(FPFGroupsListMembershipOpportunitiesResponse{
		.applications = ConvertPlayfabArrayToUnreal<PFGroupsGroupApplication, FPFGroupsGroupApplication>(Datatype->applications, Datatype->applicationsCount, ConvertGroupApplicationToUnreal),
		.applicationsCount = Datatype->applicationsCount,
		.invitations = ConvertPlayfabArrayToUnreal<PFGroupsGroupInvitation, FPFGroupsGroupInvitation>(Datatype->invitations, Datatype->invitationsCount, ConvertGroupInvitationToUnreal),
		.invitationsCount = Datatype->invitationsCount
	});

	return ConvertedType;
}

const PFGroupsListMembershipOpportunitiesResponse* ConvertListMembershipOpportunitiesResponseToPlayfab(TSharedPtr<const FPFGroupsListMembershipOpportunitiesResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsListMembershipOpportunitiesResponse* ConvertedType = new PFGroupsListMembershipOpportunitiesResponse{
		.applications = ConvertUnrealArrayToPlayfab<PFGroupsGroupApplication, FPFGroupsGroupApplication>(Datatype->applications, ConvertGroupApplicationToPlayfab),
		.applicationsCount = (uint32_t)Datatype->applications.Num(),
		.invitations = ConvertUnrealArrayToPlayfab<PFGroupsGroupInvitation, FPFGroupsGroupInvitation>(Datatype->invitations, ConvertGroupInvitationToPlayfab),
		.invitationsCount = (uint32_t)Datatype->invitations.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsRemoveGroupApplicationRequest> ConvertRemoveGroupApplicationRequestToUnreal(const PFGroupsRemoveGroupApplicationRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsRemoveGroupApplicationRequest> ConvertedType = MakeShared<FPFGroupsRemoveGroupApplicationRequest>(FPFGroupsRemoveGroupApplicationRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.group = ConvertEntityKeyToUnreal(Datatype->group)
	});

	return ConvertedType;
}

const PFGroupsRemoveGroupApplicationRequest* ConvertRemoveGroupApplicationRequestToPlayfab(TSharedPtr<const FPFGroupsRemoveGroupApplicationRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsRemoveGroupApplicationRequest* ConvertedType = new PFGroupsRemoveGroupApplicationRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.group = ConvertEntityKeyToPlayfab(Datatype->group)
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsRemoveGroupInvitationRequest> ConvertRemoveGroupInvitationRequestToUnreal(const PFGroupsRemoveGroupInvitationRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsRemoveGroupInvitationRequest> ConvertedType = MakeShared<FPFGroupsRemoveGroupInvitationRequest>(FPFGroupsRemoveGroupInvitationRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.group = ConvertEntityKeyToUnreal(Datatype->group)
	});

	return ConvertedType;
}

const PFGroupsRemoveGroupInvitationRequest* ConvertRemoveGroupInvitationRequestToPlayfab(TSharedPtr<const FPFGroupsRemoveGroupInvitationRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsRemoveGroupInvitationRequest* ConvertedType = new PFGroupsRemoveGroupInvitationRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.group = ConvertEntityKeyToPlayfab(Datatype->group)
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsRemoveMembersRequest> ConvertRemoveMembersRequestToUnreal(const PFGroupsRemoveMembersRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsRemoveMembersRequest> ConvertedType = MakeShared<FPFGroupsRemoveMembersRequest>(FPFGroupsRemoveMembersRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.group = ConvertEntityKeyToUnreal(Datatype->group),
		.members = ConvertPlayfabArrayToUnreal<PFEntityKey, FPFEntityKey>(Datatype->members, Datatype->membersCount, ConvertEntityKeyToUnreal),
		.membersCount = Datatype->membersCount,
		.roleId = Datatype->roleId == nullptr ? FString() : FString(Datatype->roleId)
	});

	return ConvertedType;
}

const PFGroupsRemoveMembersRequest* ConvertRemoveMembersRequestToPlayfab(TSharedPtr<const FPFGroupsRemoveMembersRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsRemoveMembersRequest* ConvertedType = new PFGroupsRemoveMembersRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.group = ConvertEntityKeyToPlayfab(Datatype->group),
		.members = ConvertUnrealArrayToPlayfab<PFEntityKey, FPFEntityKey>(Datatype->members, ConvertEntityKeyToPlayfab),
		.membersCount = (uint32_t)Datatype->members.Num(),
		.roleId = ConvertFStringToCharPtr(Datatype->roleId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsUnblockEntityRequest> ConvertUnblockEntityRequestToUnreal(const PFGroupsUnblockEntityRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsUnblockEntityRequest> ConvertedType = MakeShared<FPFGroupsUnblockEntityRequest>(FPFGroupsUnblockEntityRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.group = ConvertEntityKeyToUnreal(Datatype->group)
	});

	return ConvertedType;
}

const PFGroupsUnblockEntityRequest* ConvertUnblockEntityRequestToPlayfab(TSharedPtr<const FPFGroupsUnblockEntityRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsUnblockEntityRequest* ConvertedType = new PFGroupsUnblockEntityRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.group = ConvertEntityKeyToPlayfab(Datatype->group)
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsUpdateGroupRequest> ConvertUpdateGroupRequestToUnreal(const PFGroupsUpdateGroupRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsUpdateGroupRequest> ConvertedType = MakeShared<FPFGroupsUpdateGroupRequest>(FPFGroupsUpdateGroupRequest{
		.adminRoleId = Datatype->adminRoleId == nullptr ? FString() : FString(Datatype->adminRoleId),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.expectedProfileVersion = TSharedPtr<const int32>(Datatype->expectedProfileVersion),
		.group = ConvertEntityKeyToUnreal(Datatype->group),
		.groupName = Datatype->groupName == nullptr ? FString() : FString(Datatype->groupName),
		.memberRoleId = Datatype->memberRoleId == nullptr ? FString() : FString(Datatype->memberRoleId)
	});

	return ConvertedType;
}

const PFGroupsUpdateGroupRequest* ConvertUpdateGroupRequestToPlayfab(TSharedPtr<const FPFGroupsUpdateGroupRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsUpdateGroupRequest* ConvertedType = new PFGroupsUpdateGroupRequest{
		.adminRoleId = ConvertFStringToCharPtr(Datatype->adminRoleId),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.expectedProfileVersion = Datatype->expectedProfileVersion ? new int32(*Datatype->expectedProfileVersion) : nullptr,
		.group = ConvertEntityKeyToPlayfab(Datatype->group),
		.groupName = ConvertFStringToCharPtr(Datatype->groupName),
		.memberRoleId = ConvertFStringToCharPtr(Datatype->memberRoleId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsUpdateGroupResponse> ConvertUpdateGroupResponseToUnreal(const PFGroupsUpdateGroupResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsUpdateGroupResponse> ConvertedType = MakeShared<FPFGroupsUpdateGroupResponse>(FPFGroupsUpdateGroupResponse{
		.operationReason = Datatype->operationReason == nullptr ? FString() : FString(Datatype->operationReason),
		.profileVersion = Datatype->profileVersion,
		.setResult = MakeShared<FPFOperationTypes>(ConvertOperationTypesToUnreal(Datatype->setResult))
	});

	return ConvertedType;
}

const PFGroupsUpdateGroupResponse* ConvertUpdateGroupResponseToPlayfab(TSharedPtr<const FPFGroupsUpdateGroupResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsUpdateGroupResponse* ConvertedType = new PFGroupsUpdateGroupResponse{
		.operationReason = ConvertFStringToCharPtr(Datatype->operationReason),
		.profileVersion = Datatype->profileVersion,
		.setResult = new PFOperationTypes(ConvertOperationTypesToPlayfab(Datatype->setResult))
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsUpdateGroupRoleRequest> ConvertUpdateGroupRoleRequestToUnreal(const PFGroupsUpdateGroupRoleRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsUpdateGroupRoleRequest> ConvertedType = MakeShared<FPFGroupsUpdateGroupRoleRequest>(FPFGroupsUpdateGroupRoleRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.expectedProfileVersion = TSharedPtr<const int32>(Datatype->expectedProfileVersion),
		.group = ConvertEntityKeyToUnreal(Datatype->group),
		.roleId = Datatype->roleId == nullptr ? FString() : FString(Datatype->roleId),
		.roleName = Datatype->roleName == nullptr ? FString() : FString(Datatype->roleName)
	});

	return ConvertedType;
}

const PFGroupsUpdateGroupRoleRequest* ConvertUpdateGroupRoleRequestToPlayfab(TSharedPtr<const FPFGroupsUpdateGroupRoleRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsUpdateGroupRoleRequest* ConvertedType = new PFGroupsUpdateGroupRoleRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.expectedProfileVersion = Datatype->expectedProfileVersion ? new int32(*Datatype->expectedProfileVersion) : nullptr,
		.group = ConvertEntityKeyToPlayfab(Datatype->group),
		.roleId = ConvertFStringToCharPtr(Datatype->roleId),
		.roleName = ConvertFStringToCharPtr(Datatype->roleName)
	};

	return ConvertedType;
}

TSharedPtr<const FPFGroupsUpdateGroupRoleResponse> ConvertUpdateGroupRoleResponseToUnreal(const PFGroupsUpdateGroupRoleResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFGroupsUpdateGroupRoleResponse> ConvertedType = MakeShared<FPFGroupsUpdateGroupRoleResponse>(FPFGroupsUpdateGroupRoleResponse{
		.operationReason = Datatype->operationReason == nullptr ? FString() : FString(Datatype->operationReason),
		.profileVersion = Datatype->profileVersion,
		.setResult = MakeShared<FPFOperationTypes>(ConvertOperationTypesToUnreal(Datatype->setResult))
	});

	return ConvertedType;
}

const PFGroupsUpdateGroupRoleResponse* ConvertUpdateGroupRoleResponseToPlayfab(TSharedPtr<const FPFGroupsUpdateGroupRoleResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFGroupsUpdateGroupRoleResponse* ConvertedType = new PFGroupsUpdateGroupRoleResponse{
		.operationReason = ConvertFStringToCharPtr(Datatype->operationReason),
		.profileVersion = Datatype->profileVersion,
		.setResult = new PFOperationTypes(ConvertOperationTypesToPlayfab(Datatype->setResult))
	};

	return ConvertedType;
}
