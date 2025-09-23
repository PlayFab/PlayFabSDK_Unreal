// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFProfilesTypeConverters.h"

const FPFProfilesEffectType ConvertEffectTypeToUnreal(const PFProfilesEffectType* enumVal)
{
	if (enumVal == nullptr) {
		return FPFProfilesEffectType::Allow;
	}

	switch(*enumVal)
	{
	case PFProfilesEffectType::Allow: return FPFProfilesEffectType::Allow;
	case PFProfilesEffectType::Deny: return FPFProfilesEffectType::Deny;
	default:
	return FPFProfilesEffectType::Allow;
	}
}

const PFProfilesEffectType ConvertEffectTypeToPlayfab(TSharedPtr<const FPFProfilesEffectType> enumVal)
{
	if (!enumVal.IsValid()) {
		return PFProfilesEffectType::Allow;
	}

	switch(*enumVal)
	{
	case FPFProfilesEffectType::Allow: return PFProfilesEffectType::Allow;
	case FPFProfilesEffectType::Deny: return PFProfilesEffectType::Deny;
	default:
	return PFProfilesEffectType::Allow;
	}
}

TSharedPtr<const FPFProfilesGetEntityProfileRequest> ConvertGetEntityProfileRequestToUnreal(const PFProfilesGetEntityProfileRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFProfilesGetEntityProfileRequest> ConvertedType = MakeShared<FPFProfilesGetEntityProfileRequest>(FPFProfilesGetEntityProfileRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.dataAsObject = TSharedPtr<const bool>(Datatype->dataAsObject),
		.entity = ConvertEntityKeyToUnreal(Datatype->entity)
	});

	return ConvertedType;
}

const PFProfilesGetEntityProfileRequest* ConvertGetEntityProfileRequestToPlayfab(TSharedPtr<const FPFProfilesGetEntityProfileRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFProfilesGetEntityProfileRequest* ConvertedType = new PFProfilesGetEntityProfileRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.dataAsObject = Datatype->dataAsObject ? new bool(*Datatype->dataAsObject) : nullptr,
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity)
	};

	return ConvertedType;
}

TSharedPtr<const FPFProfilesEntityProfileFileMetadata> ConvertEntityProfileFileMetadataToUnreal(const PFProfilesEntityProfileFileMetadata* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFProfilesEntityProfileFileMetadata> ConvertedType = MakeShared<FPFProfilesEntityProfileFileMetadata>(FPFProfilesEntityProfileFileMetadata{
		.checksum = Datatype->checksum == nullptr ? FString() : FString(Datatype->checksum),
		.fileName = Datatype->fileName == nullptr ? FString() : FString(Datatype->fileName),
		.lastModified = FDateTime::FromUnixTimestamp((int64)Datatype->lastModified),
		.size = Datatype->size
	});

	return ConvertedType;
}

const PFProfilesEntityProfileFileMetadata* ConvertEntityProfileFileMetadataToPlayfab(TSharedPtr<const FPFProfilesEntityProfileFileMetadata> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFProfilesEntityProfileFileMetadata* ConvertedType = new PFProfilesEntityProfileFileMetadata{
		.checksum = ConvertFStringToCharPtr(Datatype->checksum),
		.fileName = ConvertFStringToCharPtr(Datatype->fileName),
		.lastModified = Datatype->lastModified.ToUnixTimestamp(),
		.size = Datatype->size
	};

	return ConvertedType;
}

TSharedPtr<const FPFProfilesEntityDataObject> ConvertEntityDataObjectToUnreal(const PFProfilesEntityDataObject* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFProfilesEntityDataObject> ConvertedType = MakeShared<FPFProfilesEntityDataObject>(FPFProfilesEntityDataObject{
		.dataObject = FPFJsonObject{ .stringValue = FString(Datatype->dataObject.stringValue) },
		.escapedDataObject = Datatype->escapedDataObject == nullptr ? FString() : FString(Datatype->escapedDataObject),
		.objectName = Datatype->objectName == nullptr ? FString() : FString(Datatype->objectName)
	});

	return ConvertedType;
}

const PFProfilesEntityDataObject* ConvertEntityDataObjectToPlayfab(TSharedPtr<const FPFProfilesEntityDataObject> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFProfilesEntityDataObject* ConvertedType = new PFProfilesEntityDataObject{
		.dataObject = PFJsonObject{ .stringValue = ConvertFStringToCharPtr(Datatype->dataObject.stringValue) },
		.escapedDataObject = ConvertFStringToCharPtr(Datatype->escapedDataObject),
		.objectName = ConvertFStringToCharPtr(Datatype->objectName)
	};

	return ConvertedType;
}

TSharedPtr<const FPFProfilesEntityPermissionStatement> ConvertEntityPermissionStatementToUnreal(const PFProfilesEntityPermissionStatement* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFProfilesEntityPermissionStatement> ConvertedType = MakeShared<FPFProfilesEntityPermissionStatement>(FPFProfilesEntityPermissionStatement{
		.action = Datatype->action == nullptr ? FString() : FString(Datatype->action),
		.comment = Datatype->comment == nullptr ? FString() : FString(Datatype->comment),
		.condition = FPFJsonObject{ .stringValue = FString(Datatype->condition.stringValue) },
		.effect = ConvertEffectTypeToUnreal(&Datatype->effect),
		.principal = FPFJsonObject{ .stringValue = FString(Datatype->principal.stringValue) },
		.resource = Datatype->resource == nullptr ? FString() : FString(Datatype->resource)
	});

	return ConvertedType;
}

const PFProfilesEntityPermissionStatement* ConvertEntityPermissionStatementToPlayfab(TSharedPtr<const FPFProfilesEntityPermissionStatement> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFProfilesEntityPermissionStatement* ConvertedType = new PFProfilesEntityPermissionStatement{
		.action = ConvertFStringToCharPtr(Datatype->action),
		.comment = ConvertFStringToCharPtr(Datatype->comment),
		.condition = PFJsonObject{ .stringValue = ConvertFStringToCharPtr(Datatype->condition.stringValue) },
		.effect = ConvertEffectTypeToPlayfab(MakeShared<FPFProfilesEffectType>(Datatype->effect)),
		.principal = PFJsonObject{ .stringValue = ConvertFStringToCharPtr(Datatype->principal.stringValue) },
		.resource = ConvertFStringToCharPtr(Datatype->resource)
	};

	return ConvertedType;
}

TSharedPtr<const FPFEntityStatisticValue> ConvertEntityStatisticValueToUnreal(const PFEntityStatisticValue* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFEntityStatisticValue> ConvertedType = MakeShared<FPFEntityStatisticValue>(FPFEntityStatisticValue{
		.metadata = Datatype->metadata == nullptr ? FString() : FString(Datatype->metadata),
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name),
		.scores = ConvertCharArrayToUnreal(Datatype->scores, Datatype->scoresCount),
		.scoresCount = Datatype->scoresCount,
		.version = Datatype->version
	});

	return ConvertedType;
}

const PFEntityStatisticValue* ConvertEntityStatisticValueToPlayfab(TSharedPtr<const FPFEntityStatisticValue> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFEntityStatisticValue* ConvertedType = new PFEntityStatisticValue{
		.metadata = ConvertFStringToCharPtr(Datatype->metadata),
		.name = ConvertFStringToCharPtr(Datatype->name),
		.scores = ConvertFStringArrayToPlayfab(Datatype->scores),
		.scoresCount = (uint32_t)Datatype->scores.Num(),
		.version = Datatype->version
	};

	return ConvertedType;
}

TSharedPtr<const FPFProfilesEntityProfileBody> ConvertEntityProfileBodyToUnreal(const PFProfilesEntityProfileBody* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFProfilesEntityProfileBody> ConvertedType = MakeShared<FPFProfilesEntityProfileBody>(FPFProfilesEntityProfileBody{
		.avatarUrl = Datatype->avatarUrl == nullptr ? FString() : FString(Datatype->avatarUrl),
		.created = FDateTime::FromUnixTimestamp((int64)Datatype->created),
		.displayName = Datatype->displayName == nullptr ? FString() : FString(Datatype->displayName),
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.entityChain = Datatype->entityChain == nullptr ? FString() : FString(Datatype->entityChain),
		.experimentVariants = ConvertCharArrayToUnreal(Datatype->experimentVariants, Datatype->experimentVariantsCount),
		.experimentVariantsCount = Datatype->experimentVariantsCount,
		.files = ConvertPlayfabMapToUnreal<PFProfilesEntityProfileFileMetadataDictionaryEntry, FPFProfilesEntityProfileFileMetadata, PFProfilesEntityProfileFileMetadata>(Datatype->files, Datatype->filesCount, ConvertEntityProfileFileMetadataToUnreal),
		.filesCount = Datatype->filesCount,
		.language = Datatype->language == nullptr ? FString() : FString(Datatype->language),
		.lineage = ConvertEntityLineageToUnreal(Datatype->lineage),
		.objects = ConvertPlayfabMapToUnreal<PFProfilesEntityDataObjectDictionaryEntry, FPFProfilesEntityDataObject, PFProfilesEntityDataObject>(Datatype->objects, Datatype->objectsCount, ConvertEntityDataObjectToUnreal),
		.objectsCount = Datatype->objectsCount,
		.permissions = ConvertPlayfabArrayToUnreal(Datatype->permissions, Datatype->permissionsCount, ConvertEntityPermissionStatementToUnreal),
		.permissionsCount = Datatype->permissionsCount,
		.statistics = ConvertPlayfabMapToUnreal<PFEntityStatisticValueDictionaryEntry, FPFEntityStatisticValue, PFEntityStatisticValue>(Datatype->statistics, Datatype->statisticsCount, ConvertEntityStatisticValueToUnreal),
		.statisticsCount = Datatype->statisticsCount,
		.versionNumber = Datatype->versionNumber
	});

	return ConvertedType;
}

const PFProfilesEntityProfileBody* ConvertEntityProfileBodyToPlayfab(TSharedPtr<const FPFProfilesEntityProfileBody> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFProfilesEntityProfileBody* ConvertedType = new PFProfilesEntityProfileBody{
		.avatarUrl = ConvertFStringToCharPtr(Datatype->avatarUrl),
		.created = Datatype->created.ToUnixTimestamp(),
		.displayName = ConvertFStringToCharPtr(Datatype->displayName),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.entityChain = ConvertFStringToCharPtr(Datatype->entityChain),
		.experimentVariants = ConvertFStringArrayToPlayfab(Datatype->experimentVariants),
		.experimentVariantsCount = (uint32_t)Datatype->experimentVariants.Num(),
		.files = ConvertUnrealMapToPlayfab<PFProfilesEntityProfileFileMetadataDictionaryEntry, FPFProfilesEntityProfileFileMetadata, PFProfilesEntityProfileFileMetadata>(Datatype->files, ConvertEntityProfileFileMetadataToPlayfab),
		.filesCount = (uint32_t)Datatype->files.Num(),
		.language = ConvertFStringToCharPtr(Datatype->language),
		.lineage = ConvertEntityLineageToPlayfab(Datatype->lineage),
		.objects = ConvertUnrealMapToPlayfab<PFProfilesEntityDataObjectDictionaryEntry, FPFProfilesEntityDataObject, PFProfilesEntityDataObject>(Datatype->objects, ConvertEntityDataObjectToPlayfab),
		.objectsCount = (uint32_t)Datatype->objects.Num(),
		.permissions = ConvertUnrealArrayToPlayfab(Datatype->permissions, ConvertEntityPermissionStatementToPlayfab),
		.permissionsCount = (uint32_t)Datatype->permissions.Num(),
		.statistics = ConvertUnrealMapToPlayfab<PFEntityStatisticValueDictionaryEntry, FPFEntityStatisticValue, PFEntityStatisticValue>(Datatype->statistics, ConvertEntityStatisticValueToPlayfab),
		.statisticsCount = (uint32_t)Datatype->statistics.Num(),
		.versionNumber = Datatype->versionNumber
	};

	return ConvertedType;
}

TSharedPtr<const FPFProfilesGetEntityProfileResponse> ConvertGetEntityProfileResponseToUnreal(const PFProfilesGetEntityProfileResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFProfilesGetEntityProfileResponse> ConvertedType = MakeShared<FPFProfilesGetEntityProfileResponse>(FPFProfilesGetEntityProfileResponse{
		.profile = ConvertEntityProfileBodyToUnreal(Datatype->profile)
	});

	return ConvertedType;
}

const PFProfilesGetEntityProfileResponse* ConvertGetEntityProfileResponseToPlayfab(TSharedPtr<const FPFProfilesGetEntityProfileResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFProfilesGetEntityProfileResponse* ConvertedType = new PFProfilesGetEntityProfileResponse{
		.profile = ConvertEntityProfileBodyToPlayfab(Datatype->profile)
	};

	return ConvertedType;
}

TSharedPtr<const FPFProfilesGetEntityProfilesRequest> ConvertGetEntityProfilesRequestToUnreal(const PFProfilesGetEntityProfilesRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFProfilesGetEntityProfilesRequest> ConvertedType = MakeShared<FPFProfilesGetEntityProfilesRequest>(FPFProfilesGetEntityProfilesRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.dataAsObject = TSharedPtr<const bool>(Datatype->dataAsObject),
		.entities = ConvertPlayfabArrayToUnreal(Datatype->entities, Datatype->entitiesCount, ConvertEntityKeyToUnreal),
		.entitiesCount = Datatype->entitiesCount
	});

	return ConvertedType;
}

const PFProfilesGetEntityProfilesRequest* ConvertGetEntityProfilesRequestToPlayfab(TSharedPtr<const FPFProfilesGetEntityProfilesRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFProfilesGetEntityProfilesRequest* ConvertedType = new PFProfilesGetEntityProfilesRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.dataAsObject = Datatype->dataAsObject ? new bool(*Datatype->dataAsObject) : nullptr,
		.entities = ConvertUnrealArrayToPlayfab(Datatype->entities, ConvertEntityKeyToPlayfab),
		.entitiesCount = (uint32_t)Datatype->entities.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFProfilesGetEntityProfilesResponse> ConvertGetEntityProfilesResponseToUnreal(const PFProfilesGetEntityProfilesResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFProfilesGetEntityProfilesResponse> ConvertedType = MakeShared<FPFProfilesGetEntityProfilesResponse>(FPFProfilesGetEntityProfilesResponse{
		.profiles = ConvertPlayfabArrayToUnreal(Datatype->profiles, Datatype->profilesCount, ConvertEntityProfileBodyToUnreal),
		.profilesCount = Datatype->profilesCount
	});

	return ConvertedType;
}

const PFProfilesGetEntityProfilesResponse* ConvertGetEntityProfilesResponseToPlayfab(TSharedPtr<const FPFProfilesGetEntityProfilesResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFProfilesGetEntityProfilesResponse* ConvertedType = new PFProfilesGetEntityProfilesResponse{
		.profiles = ConvertUnrealArrayToPlayfab(Datatype->profiles, ConvertEntityProfileBodyToPlayfab),
		.profilesCount = (uint32_t)Datatype->profiles.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFProfilesGetTitlePlayersFromMasterPlayerAccountIdsRequest> ConvertGetTitlePlayersFromMasterPlayerAccountIdsRequestToUnreal(const PFProfilesGetTitlePlayersFromMasterPlayerAccountIdsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFProfilesGetTitlePlayersFromMasterPlayerAccountIdsRequest> ConvertedType = MakeShared<FPFProfilesGetTitlePlayersFromMasterPlayerAccountIdsRequest>(FPFProfilesGetTitlePlayersFromMasterPlayerAccountIdsRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.masterPlayerAccountIds = ConvertCharArrayToUnreal(Datatype->masterPlayerAccountIds, Datatype->masterPlayerAccountIdsCount),
		.masterPlayerAccountIdsCount = Datatype->masterPlayerAccountIdsCount,
		.titleId = Datatype->titleId == nullptr ? FString() : FString(Datatype->titleId)
	});

	return ConvertedType;
}

const PFProfilesGetTitlePlayersFromMasterPlayerAccountIdsRequest* ConvertGetTitlePlayersFromMasterPlayerAccountIdsRequestToPlayfab(TSharedPtr<const FPFProfilesGetTitlePlayersFromMasterPlayerAccountIdsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFProfilesGetTitlePlayersFromMasterPlayerAccountIdsRequest* ConvertedType = new PFProfilesGetTitlePlayersFromMasterPlayerAccountIdsRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.masterPlayerAccountIds = ConvertFStringArrayToPlayfab(Datatype->masterPlayerAccountIds),
		.masterPlayerAccountIdsCount = (uint32_t)Datatype->masterPlayerAccountIds.Num(),
		.titleId = ConvertFStringToCharPtr(Datatype->titleId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFProfilesGetTitlePlayersFromMasterPlayerAccountIdsResponse> ConvertGetTitlePlayersFromMasterPlayerAccountIdsResponseToUnreal(const PFProfilesGetTitlePlayersFromMasterPlayerAccountIdsResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFProfilesGetTitlePlayersFromMasterPlayerAccountIdsResponse> ConvertedType = MakeShared<FPFProfilesGetTitlePlayersFromMasterPlayerAccountIdsResponse>(FPFProfilesGetTitlePlayersFromMasterPlayerAccountIdsResponse{
		.titleId = Datatype->titleId == nullptr ? FString() : FString(Datatype->titleId),
		.titlePlayerAccounts = ConvertPlayfabMapToUnreal<PFEntityKeyDictionaryEntry, FPFEntityKey, PFEntityKey>(Datatype->titlePlayerAccounts, Datatype->titlePlayerAccountsCount, ConvertEntityKeyToUnreal),
		.titlePlayerAccountsCount = Datatype->titlePlayerAccountsCount
	});

	return ConvertedType;
}

const PFProfilesGetTitlePlayersFromMasterPlayerAccountIdsResponse* ConvertGetTitlePlayersFromMasterPlayerAccountIdsResponseToPlayfab(TSharedPtr<const FPFProfilesGetTitlePlayersFromMasterPlayerAccountIdsResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFProfilesGetTitlePlayersFromMasterPlayerAccountIdsResponse* ConvertedType = new PFProfilesGetTitlePlayersFromMasterPlayerAccountIdsResponse{
		.titleId = ConvertFStringToCharPtr(Datatype->titleId),
		.titlePlayerAccounts = ConvertUnrealMapToPlayfab<PFEntityKeyDictionaryEntry, FPFEntityKey, PFEntityKey>(Datatype->titlePlayerAccounts, ConvertEntityKeyToPlayfab),
		.titlePlayerAccountsCount = (uint32_t)Datatype->titlePlayerAccounts.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFProfilesSetProfileLanguageRequest> ConvertSetProfileLanguageRequestToUnreal(const PFProfilesSetProfileLanguageRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFProfilesSetProfileLanguageRequest> ConvertedType = MakeShared<FPFProfilesSetProfileLanguageRequest>(FPFProfilesSetProfileLanguageRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.expectedVersion = TSharedPtr<const int32>(Datatype->expectedVersion),
		.language = Datatype->language == nullptr ? FString() : FString(Datatype->language)
	});

	return ConvertedType;
}

const PFProfilesSetProfileLanguageRequest* ConvertSetProfileLanguageRequestToPlayfab(TSharedPtr<const FPFProfilesSetProfileLanguageRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFProfilesSetProfileLanguageRequest* ConvertedType = new PFProfilesSetProfileLanguageRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.expectedVersion = Datatype->expectedVersion ? new int32(*Datatype->expectedVersion) : nullptr,
		.language = ConvertFStringToCharPtr(Datatype->language)
	};

	return ConvertedType;
}

TSharedPtr<const FPFProfilesSetProfileLanguageResponse> ConvertSetProfileLanguageResponseToUnreal(const PFProfilesSetProfileLanguageResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFProfilesSetProfileLanguageResponse> ConvertedType = MakeShared<FPFProfilesSetProfileLanguageResponse>(FPFProfilesSetProfileLanguageResponse{
		.operationResult = MakeShared<FPFOperationTypes>(ConvertOperationTypesToUnreal(Datatype->operationResult)),
		.versionNumber = TSharedPtr<const int32>(Datatype->versionNumber)
	});

	return ConvertedType;
}

const PFProfilesSetProfileLanguageResponse* ConvertSetProfileLanguageResponseToPlayfab(TSharedPtr<const FPFProfilesSetProfileLanguageResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFProfilesSetProfileLanguageResponse* ConvertedType = new PFProfilesSetProfileLanguageResponse{
		.operationResult = new PFOperationTypes(ConvertOperationTypesToPlayfab(Datatype->operationResult)),
		.versionNumber = Datatype->versionNumber ? new int32(*Datatype->versionNumber) : nullptr
	};

	return ConvertedType;
}

TSharedPtr<const FPFProfilesSetEntityProfilePolicyRequest> ConvertSetEntityProfilePolicyRequestToUnreal(const PFProfilesSetEntityProfilePolicyRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFProfilesSetEntityProfilePolicyRequest> ConvertedType = MakeShared<FPFProfilesSetEntityProfilePolicyRequest>(FPFProfilesSetEntityProfilePolicyRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.statements = ConvertPlayfabArrayToUnreal(Datatype->statements, Datatype->statementsCount, ConvertEntityPermissionStatementToUnreal),
		.statementsCount = Datatype->statementsCount
	});

	return ConvertedType;
}

const PFProfilesSetEntityProfilePolicyRequest* ConvertSetEntityProfilePolicyRequestToPlayfab(TSharedPtr<const FPFProfilesSetEntityProfilePolicyRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFProfilesSetEntityProfilePolicyRequest* ConvertedType = new PFProfilesSetEntityProfilePolicyRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.statements = ConvertUnrealArrayToPlayfab(Datatype->statements, ConvertEntityPermissionStatementToPlayfab),
		.statementsCount = (uint32_t)Datatype->statements.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFProfilesSetEntityProfilePolicyResponse> ConvertSetEntityProfilePolicyResponseToUnreal(const PFProfilesSetEntityProfilePolicyResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFProfilesSetEntityProfilePolicyResponse> ConvertedType = MakeShared<FPFProfilesSetEntityProfilePolicyResponse>(FPFProfilesSetEntityProfilePolicyResponse{
		.permissions = ConvertPlayfabArrayToUnreal(Datatype->permissions, Datatype->permissionsCount, ConvertEntityPermissionStatementToUnreal),
		.permissionsCount = Datatype->permissionsCount
	});

	return ConvertedType;
}

const PFProfilesSetEntityProfilePolicyResponse* ConvertSetEntityProfilePolicyResponseToPlayfab(TSharedPtr<const FPFProfilesSetEntityProfilePolicyResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFProfilesSetEntityProfilePolicyResponse* ConvertedType = new PFProfilesSetEntityProfilePolicyResponse{
		.permissions = ConvertUnrealArrayToPlayfab(Datatype->permissions, ConvertEntityPermissionStatementToPlayfab),
		.permissionsCount = (uint32_t)Datatype->permissions.Num()
	};

	return ConvertedType;
}
