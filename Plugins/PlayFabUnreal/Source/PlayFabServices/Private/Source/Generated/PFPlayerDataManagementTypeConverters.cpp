// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFPlayerDataManagementTypeConverters.h"

TSharedPtr<const FPFPlayerDataManagementClientDeletePlayerCustomPropertiesRequest> ConvertClientDeletePlayerCustomPropertiesRequestToUnreal(const PFPlayerDataManagementClientDeletePlayerCustomPropertiesRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFPlayerDataManagementClientDeletePlayerCustomPropertiesRequest> ConvertedType = MakeShared<FPFPlayerDataManagementClientDeletePlayerCustomPropertiesRequest>(FPFPlayerDataManagementClientDeletePlayerCustomPropertiesRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.expectedPropertiesVersion = TSharedPtr<const int32>(Datatype->expectedPropertiesVersion),
		.propertyNames = ConvertCharArrayToUnreal(Datatype->propertyNames, Datatype->propertyNamesCount),
		.propertyNamesCount = Datatype->propertyNamesCount
	});

	return ConvertedType;
}

const PFPlayerDataManagementClientDeletePlayerCustomPropertiesRequest* ConvertClientDeletePlayerCustomPropertiesRequestToPlayfab(TSharedPtr<const FPFPlayerDataManagementClientDeletePlayerCustomPropertiesRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFPlayerDataManagementClientDeletePlayerCustomPropertiesRequest* ConvertedType = new PFPlayerDataManagementClientDeletePlayerCustomPropertiesRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.expectedPropertiesVersion = Datatype->expectedPropertiesVersion ? new int32(*Datatype->expectedPropertiesVersion) : nullptr,
		.propertyNames = ConvertFStringArrayToPlayfab(Datatype->propertyNames),
		.propertyNamesCount = (uint32_t)Datatype->propertyNames.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFPlayerDataManagementDeletedPropertyDetails> ConvertDeletedPropertyDetailsToUnreal(const PFPlayerDataManagementDeletedPropertyDetails* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFPlayerDataManagementDeletedPropertyDetails> ConvertedType = MakeShared<FPFPlayerDataManagementDeletedPropertyDetails>(FPFPlayerDataManagementDeletedPropertyDetails{
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name),
		.wasDeleted = Datatype->wasDeleted
	});

	return ConvertedType;
}

const PFPlayerDataManagementDeletedPropertyDetails* ConvertDeletedPropertyDetailsToPlayfab(TSharedPtr<const FPFPlayerDataManagementDeletedPropertyDetails> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFPlayerDataManagementDeletedPropertyDetails* ConvertedType = new PFPlayerDataManagementDeletedPropertyDetails{
		.name = ConvertFStringToCharPtr(Datatype->name),
		.wasDeleted = Datatype->wasDeleted
	};

	return ConvertedType;
}

TSharedPtr<const FPFPlayerDataManagementClientDeletePlayerCustomPropertiesResult> ConvertClientDeletePlayerCustomPropertiesResultToUnreal(const PFPlayerDataManagementClientDeletePlayerCustomPropertiesResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFPlayerDataManagementClientDeletePlayerCustomPropertiesResult> ConvertedType = MakeShared<FPFPlayerDataManagementClientDeletePlayerCustomPropertiesResult>(FPFPlayerDataManagementClientDeletePlayerCustomPropertiesResult{
		.deletedProperties = ConvertPlayfabArrayToUnreal(Datatype->deletedProperties, Datatype->deletedPropertiesCount, ConvertDeletedPropertyDetailsToUnreal),
		.deletedPropertiesCount = Datatype->deletedPropertiesCount,
		.propertiesVersion = Datatype->propertiesVersion
	});

	return ConvertedType;
}

const PFPlayerDataManagementClientDeletePlayerCustomPropertiesResult* ConvertClientDeletePlayerCustomPropertiesResultToPlayfab(TSharedPtr<const FPFPlayerDataManagementClientDeletePlayerCustomPropertiesResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFPlayerDataManagementClientDeletePlayerCustomPropertiesResult* ConvertedType = new PFPlayerDataManagementClientDeletePlayerCustomPropertiesResult{
		.deletedProperties = ConvertUnrealArrayToPlayfab(Datatype->deletedProperties, ConvertDeletedPropertyDetailsToPlayfab),
		.deletedPropertiesCount = (uint32_t)Datatype->deletedProperties.Num(),
		.propertiesVersion = Datatype->propertiesVersion
	};

	return ConvertedType;
}

TSharedPtr<const FPFPlayerDataManagementClientGetPlayerCustomPropertyRequest> ConvertClientGetPlayerCustomPropertyRequestToUnreal(const PFPlayerDataManagementClientGetPlayerCustomPropertyRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFPlayerDataManagementClientGetPlayerCustomPropertyRequest> ConvertedType = MakeShared<FPFPlayerDataManagementClientGetPlayerCustomPropertyRequest>(FPFPlayerDataManagementClientGetPlayerCustomPropertyRequest{
		.propertyName = Datatype->propertyName == nullptr ? FString() : FString(Datatype->propertyName)
	});

	return ConvertedType;
}

const PFPlayerDataManagementClientGetPlayerCustomPropertyRequest* ConvertClientGetPlayerCustomPropertyRequestToPlayfab(TSharedPtr<const FPFPlayerDataManagementClientGetPlayerCustomPropertyRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFPlayerDataManagementClientGetPlayerCustomPropertyRequest* ConvertedType = new PFPlayerDataManagementClientGetPlayerCustomPropertyRequest{
		.propertyName = ConvertFStringToCharPtr(Datatype->propertyName)
	};

	return ConvertedType;
}

TSharedPtr<const FPFPlayerDataManagementCustomPropertyDetails> ConvertCustomPropertyDetailsToUnreal(const PFPlayerDataManagementCustomPropertyDetails* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFPlayerDataManagementCustomPropertyDetails> ConvertedType = MakeShared<FPFPlayerDataManagementCustomPropertyDetails>(FPFPlayerDataManagementCustomPropertyDetails{
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name),
		.value = FPFJsonObject{ .stringValue = FString(Datatype->value.stringValue) }
	});

	return ConvertedType;
}

const PFPlayerDataManagementCustomPropertyDetails* ConvertCustomPropertyDetailsToPlayfab(TSharedPtr<const FPFPlayerDataManagementCustomPropertyDetails> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFPlayerDataManagementCustomPropertyDetails* ConvertedType = new PFPlayerDataManagementCustomPropertyDetails{
		.name = ConvertFStringToCharPtr(Datatype->name),
		.value = PFJsonObject{ .stringValue = ConvertFStringToCharPtr(Datatype->value.stringValue) }
	};

	return ConvertedType;
}

TSharedPtr<const FPFPlayerDataManagementClientGetPlayerCustomPropertyResult> ConvertClientGetPlayerCustomPropertyResultToUnreal(const PFPlayerDataManagementClientGetPlayerCustomPropertyResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFPlayerDataManagementClientGetPlayerCustomPropertyResult> ConvertedType = MakeShared<FPFPlayerDataManagementClientGetPlayerCustomPropertyResult>(FPFPlayerDataManagementClientGetPlayerCustomPropertyResult{
		.propertiesVersion = Datatype->propertiesVersion,
		.property = ConvertCustomPropertyDetailsToUnreal(Datatype->property)
	});

	return ConvertedType;
}

const PFPlayerDataManagementClientGetPlayerCustomPropertyResult* ConvertClientGetPlayerCustomPropertyResultToPlayfab(TSharedPtr<const FPFPlayerDataManagementClientGetPlayerCustomPropertyResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFPlayerDataManagementClientGetPlayerCustomPropertyResult* ConvertedType = new PFPlayerDataManagementClientGetPlayerCustomPropertyResult{
		.propertiesVersion = Datatype->propertiesVersion,
		.property = ConvertCustomPropertyDetailsToPlayfab(Datatype->property)
	};

	return ConvertedType;
}

TSharedPtr<const FPFPlayerDataManagementGetUserDataRequest> ConvertGetUserDataRequestToUnreal(const PFPlayerDataManagementGetUserDataRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFPlayerDataManagementGetUserDataRequest> ConvertedType = MakeShared<FPFPlayerDataManagementGetUserDataRequest>(FPFPlayerDataManagementGetUserDataRequest{
		.ifChangedFromDataVersion = TSharedPtr<const uint32>(Datatype->ifChangedFromDataVersion),
		.keys = ConvertCharArrayToUnreal(Datatype->keys, Datatype->keysCount),
		.keysCount = Datatype->keysCount,
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId)
	});

	return ConvertedType;
}

const PFPlayerDataManagementGetUserDataRequest* ConvertGetUserDataRequestToPlayfab(TSharedPtr<const FPFPlayerDataManagementGetUserDataRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFPlayerDataManagementGetUserDataRequest* ConvertedType = new PFPlayerDataManagementGetUserDataRequest{
		.ifChangedFromDataVersion = Datatype->ifChangedFromDataVersion ? new uint32(*Datatype->ifChangedFromDataVersion) : nullptr,
		.keys = ConvertFStringArrayToPlayfab(Datatype->keys),
		.keysCount = (uint32_t)Datatype->keys.Num(),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFPlayerDataManagementClientGetUserDataResult> ConvertClientGetUserDataResultToUnreal(const PFPlayerDataManagementClientGetUserDataResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFPlayerDataManagementClientGetUserDataResult> ConvertedType = MakeShared<FPFPlayerDataManagementClientGetUserDataResult>(FPFPlayerDataManagementClientGetUserDataResult{
		.data = ConvertPlayfabMapToUnreal<PFUserDataRecordDictionaryEntry, FPFUserDataRecord, PFUserDataRecord>(Datatype->data, Datatype->dataCount, ConvertUserDataRecordToUnreal),
		.dataCount = Datatype->dataCount,
		.dataVersion = Datatype->dataVersion
	});

	return ConvertedType;
}

const PFPlayerDataManagementClientGetUserDataResult* ConvertClientGetUserDataResultToPlayfab(TSharedPtr<const FPFPlayerDataManagementClientGetUserDataResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFPlayerDataManagementClientGetUserDataResult* ConvertedType = new PFPlayerDataManagementClientGetUserDataResult{
		.data = ConvertUnrealMapToPlayfab<PFUserDataRecordDictionaryEntry, FPFUserDataRecord, PFUserDataRecord>(Datatype->data, ConvertUserDataRecordToPlayfab),
		.dataCount = (uint32_t)Datatype->data.Num(),
		.dataVersion = Datatype->dataVersion
	};

	return ConvertedType;
}

TSharedPtr<const FPFPlayerDataManagementClientListPlayerCustomPropertiesResult> ConvertClientListPlayerCustomPropertiesResultToUnreal(const PFPlayerDataManagementClientListPlayerCustomPropertiesResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFPlayerDataManagementClientListPlayerCustomPropertiesResult> ConvertedType = MakeShared<FPFPlayerDataManagementClientListPlayerCustomPropertiesResult>(FPFPlayerDataManagementClientListPlayerCustomPropertiesResult{
		.properties = ConvertPlayfabArrayToUnreal(Datatype->properties, Datatype->propertiesCount, ConvertCustomPropertyDetailsToUnreal),
		.propertiesCount = Datatype->propertiesCount,
		.propertiesVersion = Datatype->propertiesVersion
	});

	return ConvertedType;
}

const PFPlayerDataManagementClientListPlayerCustomPropertiesResult* ConvertClientListPlayerCustomPropertiesResultToPlayfab(TSharedPtr<const FPFPlayerDataManagementClientListPlayerCustomPropertiesResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFPlayerDataManagementClientListPlayerCustomPropertiesResult* ConvertedType = new PFPlayerDataManagementClientListPlayerCustomPropertiesResult{
		.properties = ConvertUnrealArrayToPlayfab(Datatype->properties, ConvertCustomPropertyDetailsToPlayfab),
		.propertiesCount = (uint32_t)Datatype->properties.Num(),
		.propertiesVersion = Datatype->propertiesVersion
	};

	return ConvertedType;
}

TSharedPtr<const FPFPlayerDataManagementUpdateProperty> ConvertUpdatePropertyToUnreal(const PFPlayerDataManagementUpdateProperty* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFPlayerDataManagementUpdateProperty> ConvertedType = MakeShared<FPFPlayerDataManagementUpdateProperty>(FPFPlayerDataManagementUpdateProperty{
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name),
		.value = FPFJsonObject{ .stringValue = FString(Datatype->value.stringValue) }
	});

	return ConvertedType;
}

const PFPlayerDataManagementUpdateProperty* ConvertUpdatePropertyToPlayfab(TSharedPtr<const FPFPlayerDataManagementUpdateProperty> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFPlayerDataManagementUpdateProperty* ConvertedType = new PFPlayerDataManagementUpdateProperty{
		.name = ConvertFStringToCharPtr(Datatype->name),
		.value = PFJsonObject{ .stringValue = ConvertFStringToCharPtr(Datatype->value.stringValue) }
	};

	return ConvertedType;
}

TSharedPtr<const FPFPlayerDataManagementClientUpdatePlayerCustomPropertiesRequest> ConvertClientUpdatePlayerCustomPropertiesRequestToUnreal(const PFPlayerDataManagementClientUpdatePlayerCustomPropertiesRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFPlayerDataManagementClientUpdatePlayerCustomPropertiesRequest> ConvertedType = MakeShared<FPFPlayerDataManagementClientUpdatePlayerCustomPropertiesRequest>(FPFPlayerDataManagementClientUpdatePlayerCustomPropertiesRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.expectedPropertiesVersion = TSharedPtr<const int32>(Datatype->expectedPropertiesVersion),
		.properties = ConvertPlayfabArrayToUnreal(Datatype->properties, Datatype->propertiesCount, ConvertUpdatePropertyToUnreal),
		.propertiesCount = Datatype->propertiesCount
	});

	return ConvertedType;
}

const PFPlayerDataManagementClientUpdatePlayerCustomPropertiesRequest* ConvertClientUpdatePlayerCustomPropertiesRequestToPlayfab(TSharedPtr<const FPFPlayerDataManagementClientUpdatePlayerCustomPropertiesRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFPlayerDataManagementClientUpdatePlayerCustomPropertiesRequest* ConvertedType = new PFPlayerDataManagementClientUpdatePlayerCustomPropertiesRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.expectedPropertiesVersion = Datatype->expectedPropertiesVersion ? new int32(*Datatype->expectedPropertiesVersion) : nullptr,
		.properties = ConvertUnrealArrayToPlayfab(Datatype->properties, ConvertUpdatePropertyToPlayfab),
		.propertiesCount = (uint32_t)Datatype->properties.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFPlayerDataManagementClientUpdatePlayerCustomPropertiesResult> ConvertClientUpdatePlayerCustomPropertiesResultToUnreal(const PFPlayerDataManagementClientUpdatePlayerCustomPropertiesResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFPlayerDataManagementClientUpdatePlayerCustomPropertiesResult> ConvertedType = MakeShared<FPFPlayerDataManagementClientUpdatePlayerCustomPropertiesResult>(FPFPlayerDataManagementClientUpdatePlayerCustomPropertiesResult{
		.propertiesVersion = Datatype->propertiesVersion
	});

	return ConvertedType;
}

const PFPlayerDataManagementClientUpdatePlayerCustomPropertiesResult* ConvertClientUpdatePlayerCustomPropertiesResultToPlayfab(TSharedPtr<const FPFPlayerDataManagementClientUpdatePlayerCustomPropertiesResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFPlayerDataManagementClientUpdatePlayerCustomPropertiesResult* ConvertedType = new PFPlayerDataManagementClientUpdatePlayerCustomPropertiesResult{
		.propertiesVersion = Datatype->propertiesVersion
	};

	return ConvertedType;
}

TSharedPtr<const FPFPlayerDataManagementClientUpdateUserDataRequest> ConvertClientUpdateUserDataRequestToUnreal(const PFPlayerDataManagementClientUpdateUserDataRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFPlayerDataManagementClientUpdateUserDataRequest> ConvertedType = MakeShared<FPFPlayerDataManagementClientUpdateUserDataRequest>(FPFPlayerDataManagementClientUpdateUserDataRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.data = ConvertCharMapToUnreal(Datatype->data, Datatype->dataCount),
		.dataCount = Datatype->dataCount,
		.keysToRemove = ConvertCharArrayToUnreal(Datatype->keysToRemove, Datatype->keysToRemoveCount),
		.keysToRemoveCount = Datatype->keysToRemoveCount,
		.permission = MakeShared<FPFUserDataPermission>(ConvertUserDataPermissionToUnreal(Datatype->permission))
	});

	return ConvertedType;
}

const PFPlayerDataManagementClientUpdateUserDataRequest* ConvertClientUpdateUserDataRequestToPlayfab(TSharedPtr<const FPFPlayerDataManagementClientUpdateUserDataRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFPlayerDataManagementClientUpdateUserDataRequest* ConvertedType = new PFPlayerDataManagementClientUpdateUserDataRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.data = ConvertFStringMapToPlayfab(Datatype->data),
		.dataCount = (uint32_t)Datatype->data.Num(),
		.keysToRemove = ConvertFStringArrayToPlayfab(Datatype->keysToRemove),
		.keysToRemoveCount = (uint32_t)Datatype->keysToRemove.Num(),
		.permission = new PFUserDataPermission(ConvertUserDataPermissionToPlayfab(Datatype->permission))
	};

	return ConvertedType;
}

TSharedPtr<const FPFPlayerDataManagementUpdateUserDataResult> ConvertUpdateUserDataResultToUnreal(const PFPlayerDataManagementUpdateUserDataResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFPlayerDataManagementUpdateUserDataResult> ConvertedType = MakeShared<FPFPlayerDataManagementUpdateUserDataResult>(FPFPlayerDataManagementUpdateUserDataResult{
		.dataVersion = Datatype->dataVersion
	});

	return ConvertedType;
}

const PFPlayerDataManagementUpdateUserDataResult* ConvertUpdateUserDataResultToPlayfab(TSharedPtr<const FPFPlayerDataManagementUpdateUserDataResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFPlayerDataManagementUpdateUserDataResult* ConvertedType = new PFPlayerDataManagementUpdateUserDataResult{
		.dataVersion = Datatype->dataVersion
	};

	return ConvertedType;
}

TSharedPtr<const FPFPlayerDataManagementServerDeletePlayerCustomPropertiesRequest> ConvertServerDeletePlayerCustomPropertiesRequestToUnreal(const PFPlayerDataManagementServerDeletePlayerCustomPropertiesRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFPlayerDataManagementServerDeletePlayerCustomPropertiesRequest> ConvertedType = MakeShared<FPFPlayerDataManagementServerDeletePlayerCustomPropertiesRequest>(FPFPlayerDataManagementServerDeletePlayerCustomPropertiesRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.expectedPropertiesVersion = TSharedPtr<const int32>(Datatype->expectedPropertiesVersion),
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId),
		.propertyNames = ConvertCharArrayToUnreal(Datatype->propertyNames, Datatype->propertyNamesCount),
		.propertyNamesCount = Datatype->propertyNamesCount
	});

	return ConvertedType;
}

const PFPlayerDataManagementServerDeletePlayerCustomPropertiesRequest* ConvertServerDeletePlayerCustomPropertiesRequestToPlayfab(TSharedPtr<const FPFPlayerDataManagementServerDeletePlayerCustomPropertiesRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFPlayerDataManagementServerDeletePlayerCustomPropertiesRequest* ConvertedType = new PFPlayerDataManagementServerDeletePlayerCustomPropertiesRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.expectedPropertiesVersion = Datatype->expectedPropertiesVersion ? new int32(*Datatype->expectedPropertiesVersion) : nullptr,
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId),
		.propertyNames = ConvertFStringArrayToPlayfab(Datatype->propertyNames),
		.propertyNamesCount = (uint32_t)Datatype->propertyNames.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFPlayerDataManagementServerDeletePlayerCustomPropertiesResult> ConvertServerDeletePlayerCustomPropertiesResultToUnreal(const PFPlayerDataManagementServerDeletePlayerCustomPropertiesResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFPlayerDataManagementServerDeletePlayerCustomPropertiesResult> ConvertedType = MakeShared<FPFPlayerDataManagementServerDeletePlayerCustomPropertiesResult>(FPFPlayerDataManagementServerDeletePlayerCustomPropertiesResult{
		.deletedProperties = ConvertPlayfabArrayToUnreal(Datatype->deletedProperties, Datatype->deletedPropertiesCount, ConvertDeletedPropertyDetailsToUnreal),
		.deletedPropertiesCount = Datatype->deletedPropertiesCount,
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId),
		.propertiesVersion = Datatype->propertiesVersion
	});

	return ConvertedType;
}

const PFPlayerDataManagementServerDeletePlayerCustomPropertiesResult* ConvertServerDeletePlayerCustomPropertiesResultToPlayfab(TSharedPtr<const FPFPlayerDataManagementServerDeletePlayerCustomPropertiesResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFPlayerDataManagementServerDeletePlayerCustomPropertiesResult* ConvertedType = new PFPlayerDataManagementServerDeletePlayerCustomPropertiesResult{
		.deletedProperties = ConvertUnrealArrayToPlayfab(Datatype->deletedProperties, ConvertDeletedPropertyDetailsToPlayfab),
		.deletedPropertiesCount = (uint32_t)Datatype->deletedProperties.Num(),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId),
		.propertiesVersion = Datatype->propertiesVersion
	};

	return ConvertedType;
}

TSharedPtr<const FPFPlayerDataManagementServerGetPlayerCustomPropertyRequest> ConvertServerGetPlayerCustomPropertyRequestToUnreal(const PFPlayerDataManagementServerGetPlayerCustomPropertyRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFPlayerDataManagementServerGetPlayerCustomPropertyRequest> ConvertedType = MakeShared<FPFPlayerDataManagementServerGetPlayerCustomPropertyRequest>(FPFPlayerDataManagementServerGetPlayerCustomPropertyRequest{
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId),
		.propertyName = Datatype->propertyName == nullptr ? FString() : FString(Datatype->propertyName)
	});

	return ConvertedType;
}

const PFPlayerDataManagementServerGetPlayerCustomPropertyRequest* ConvertServerGetPlayerCustomPropertyRequestToPlayfab(TSharedPtr<const FPFPlayerDataManagementServerGetPlayerCustomPropertyRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFPlayerDataManagementServerGetPlayerCustomPropertyRequest* ConvertedType = new PFPlayerDataManagementServerGetPlayerCustomPropertyRequest{
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId),
		.propertyName = ConvertFStringToCharPtr(Datatype->propertyName)
	};

	return ConvertedType;
}

TSharedPtr<const FPFPlayerDataManagementServerGetPlayerCustomPropertyResult> ConvertServerGetPlayerCustomPropertyResultToUnreal(const PFPlayerDataManagementServerGetPlayerCustomPropertyResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFPlayerDataManagementServerGetPlayerCustomPropertyResult> ConvertedType = MakeShared<FPFPlayerDataManagementServerGetPlayerCustomPropertyResult>(FPFPlayerDataManagementServerGetPlayerCustomPropertyResult{
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId),
		.propertiesVersion = Datatype->propertiesVersion,
		.property = ConvertCustomPropertyDetailsToUnreal(Datatype->property)
	});

	return ConvertedType;
}

const PFPlayerDataManagementServerGetPlayerCustomPropertyResult* ConvertServerGetPlayerCustomPropertyResultToPlayfab(TSharedPtr<const FPFPlayerDataManagementServerGetPlayerCustomPropertyResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFPlayerDataManagementServerGetPlayerCustomPropertyResult* ConvertedType = new PFPlayerDataManagementServerGetPlayerCustomPropertyResult{
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId),
		.propertiesVersion = Datatype->propertiesVersion,
		.property = ConvertCustomPropertyDetailsToPlayfab(Datatype->property)
	};

	return ConvertedType;
}

TSharedPtr<const FPFPlayerDataManagementServerGetUserDataResult> ConvertServerGetUserDataResultToUnreal(const PFPlayerDataManagementServerGetUserDataResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFPlayerDataManagementServerGetUserDataResult> ConvertedType = MakeShared<FPFPlayerDataManagementServerGetUserDataResult>(FPFPlayerDataManagementServerGetUserDataResult{
		.data = ConvertPlayfabMapToUnreal<PFUserDataRecordDictionaryEntry, FPFUserDataRecord, PFUserDataRecord>(Datatype->data, Datatype->dataCount, ConvertUserDataRecordToUnreal),
		.dataCount = Datatype->dataCount,
		.dataVersion = Datatype->dataVersion,
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId)
	});

	return ConvertedType;
}

const PFPlayerDataManagementServerGetUserDataResult* ConvertServerGetUserDataResultToPlayfab(TSharedPtr<const FPFPlayerDataManagementServerGetUserDataResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFPlayerDataManagementServerGetUserDataResult* ConvertedType = new PFPlayerDataManagementServerGetUserDataResult{
		.data = ConvertUnrealMapToPlayfab<PFUserDataRecordDictionaryEntry, FPFUserDataRecord, PFUserDataRecord>(Datatype->data, ConvertUserDataRecordToPlayfab),
		.dataCount = (uint32_t)Datatype->data.Num(),
		.dataVersion = Datatype->dataVersion,
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFPlayerDataManagementListPlayerCustomPropertiesRequest> ConvertListPlayerCustomPropertiesRequestToUnreal(const PFPlayerDataManagementListPlayerCustomPropertiesRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFPlayerDataManagementListPlayerCustomPropertiesRequest> ConvertedType = MakeShared<FPFPlayerDataManagementListPlayerCustomPropertiesRequest>(FPFPlayerDataManagementListPlayerCustomPropertiesRequest{
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId)
	});

	return ConvertedType;
}

const PFPlayerDataManagementListPlayerCustomPropertiesRequest* ConvertListPlayerCustomPropertiesRequestToPlayfab(TSharedPtr<const FPFPlayerDataManagementListPlayerCustomPropertiesRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFPlayerDataManagementListPlayerCustomPropertiesRequest* ConvertedType = new PFPlayerDataManagementListPlayerCustomPropertiesRequest{
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFPlayerDataManagementServerListPlayerCustomPropertiesResult> ConvertServerListPlayerCustomPropertiesResultToUnreal(const PFPlayerDataManagementServerListPlayerCustomPropertiesResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFPlayerDataManagementServerListPlayerCustomPropertiesResult> ConvertedType = MakeShared<FPFPlayerDataManagementServerListPlayerCustomPropertiesResult>(FPFPlayerDataManagementServerListPlayerCustomPropertiesResult{
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId),
		.properties = ConvertPlayfabArrayToUnreal(Datatype->properties, Datatype->propertiesCount, ConvertCustomPropertyDetailsToUnreal),
		.propertiesCount = Datatype->propertiesCount,
		.propertiesVersion = Datatype->propertiesVersion
	});

	return ConvertedType;
}

const PFPlayerDataManagementServerListPlayerCustomPropertiesResult* ConvertServerListPlayerCustomPropertiesResultToPlayfab(TSharedPtr<const FPFPlayerDataManagementServerListPlayerCustomPropertiesResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFPlayerDataManagementServerListPlayerCustomPropertiesResult* ConvertedType = new PFPlayerDataManagementServerListPlayerCustomPropertiesResult{
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId),
		.properties = ConvertUnrealArrayToPlayfab(Datatype->properties, ConvertCustomPropertyDetailsToPlayfab),
		.propertiesCount = (uint32_t)Datatype->properties.Num(),
		.propertiesVersion = Datatype->propertiesVersion
	};

	return ConvertedType;
}

TSharedPtr<const FPFPlayerDataManagementServerUpdatePlayerCustomPropertiesRequest> ConvertServerUpdatePlayerCustomPropertiesRequestToUnreal(const PFPlayerDataManagementServerUpdatePlayerCustomPropertiesRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFPlayerDataManagementServerUpdatePlayerCustomPropertiesRequest> ConvertedType = MakeShared<FPFPlayerDataManagementServerUpdatePlayerCustomPropertiesRequest>(FPFPlayerDataManagementServerUpdatePlayerCustomPropertiesRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.expectedPropertiesVersion = TSharedPtr<const int32>(Datatype->expectedPropertiesVersion),
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId),
		.properties = ConvertPlayfabArrayToUnreal(Datatype->properties, Datatype->propertiesCount, ConvertUpdatePropertyToUnreal),
		.propertiesCount = Datatype->propertiesCount
	});

	return ConvertedType;
}

const PFPlayerDataManagementServerUpdatePlayerCustomPropertiesRequest* ConvertServerUpdatePlayerCustomPropertiesRequestToPlayfab(TSharedPtr<const FPFPlayerDataManagementServerUpdatePlayerCustomPropertiesRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFPlayerDataManagementServerUpdatePlayerCustomPropertiesRequest* ConvertedType = new PFPlayerDataManagementServerUpdatePlayerCustomPropertiesRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.expectedPropertiesVersion = Datatype->expectedPropertiesVersion ? new int32(*Datatype->expectedPropertiesVersion) : nullptr,
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId),
		.properties = ConvertUnrealArrayToPlayfab(Datatype->properties, ConvertUpdatePropertyToPlayfab),
		.propertiesCount = (uint32_t)Datatype->properties.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFPlayerDataManagementServerUpdatePlayerCustomPropertiesResult> ConvertServerUpdatePlayerCustomPropertiesResultToUnreal(const PFPlayerDataManagementServerUpdatePlayerCustomPropertiesResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFPlayerDataManagementServerUpdatePlayerCustomPropertiesResult> ConvertedType = MakeShared<FPFPlayerDataManagementServerUpdatePlayerCustomPropertiesResult>(FPFPlayerDataManagementServerUpdatePlayerCustomPropertiesResult{
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId),
		.propertiesVersion = Datatype->propertiesVersion
	});

	return ConvertedType;
}

const PFPlayerDataManagementServerUpdatePlayerCustomPropertiesResult* ConvertServerUpdatePlayerCustomPropertiesResultToPlayfab(TSharedPtr<const FPFPlayerDataManagementServerUpdatePlayerCustomPropertiesResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFPlayerDataManagementServerUpdatePlayerCustomPropertiesResult* ConvertedType = new PFPlayerDataManagementServerUpdatePlayerCustomPropertiesResult{
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId),
		.propertiesVersion = Datatype->propertiesVersion
	};

	return ConvertedType;
}

TSharedPtr<const FPFPlayerDataManagementServerUpdateUserDataRequest> ConvertServerUpdateUserDataRequestToUnreal(const PFPlayerDataManagementServerUpdateUserDataRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFPlayerDataManagementServerUpdateUserDataRequest> ConvertedType = MakeShared<FPFPlayerDataManagementServerUpdateUserDataRequest>(FPFPlayerDataManagementServerUpdateUserDataRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.data = ConvertCharMapToUnreal(Datatype->data, Datatype->dataCount),
		.dataCount = Datatype->dataCount,
		.keysToRemove = ConvertCharArrayToUnreal(Datatype->keysToRemove, Datatype->keysToRemoveCount),
		.keysToRemoveCount = Datatype->keysToRemoveCount,
		.permission = MakeShared<FPFUserDataPermission>(ConvertUserDataPermissionToUnreal(Datatype->permission)),
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId)
	});

	return ConvertedType;
}

const PFPlayerDataManagementServerUpdateUserDataRequest* ConvertServerUpdateUserDataRequestToPlayfab(TSharedPtr<const FPFPlayerDataManagementServerUpdateUserDataRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFPlayerDataManagementServerUpdateUserDataRequest* ConvertedType = new PFPlayerDataManagementServerUpdateUserDataRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.data = ConvertFStringMapToPlayfab(Datatype->data),
		.dataCount = (uint32_t)Datatype->data.Num(),
		.keysToRemove = ConvertFStringArrayToPlayfab(Datatype->keysToRemove),
		.keysToRemoveCount = (uint32_t)Datatype->keysToRemove.Num(),
		.permission = new PFUserDataPermission(ConvertUserDataPermissionToPlayfab(Datatype->permission)),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFPlayerDataManagementUpdateUserInternalDataRequest> ConvertUpdateUserInternalDataRequestToUnreal(const PFPlayerDataManagementUpdateUserInternalDataRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFPlayerDataManagementUpdateUserInternalDataRequest> ConvertedType = MakeShared<FPFPlayerDataManagementUpdateUserInternalDataRequest>(FPFPlayerDataManagementUpdateUserInternalDataRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.data = ConvertCharMapToUnreal(Datatype->data, Datatype->dataCount),
		.dataCount = Datatype->dataCount,
		.keysToRemove = ConvertCharArrayToUnreal(Datatype->keysToRemove, Datatype->keysToRemoveCount),
		.keysToRemoveCount = Datatype->keysToRemoveCount,
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId)
	});

	return ConvertedType;
}

const PFPlayerDataManagementUpdateUserInternalDataRequest* ConvertUpdateUserInternalDataRequestToPlayfab(TSharedPtr<const FPFPlayerDataManagementUpdateUserInternalDataRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFPlayerDataManagementUpdateUserInternalDataRequest* ConvertedType = new PFPlayerDataManagementUpdateUserInternalDataRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.data = ConvertFStringMapToPlayfab(Datatype->data),
		.dataCount = (uint32_t)Datatype->data.Num(),
		.keysToRemove = ConvertFStringArrayToPlayfab(Datatype->keysToRemove),
		.keysToRemoveCount = (uint32_t)Datatype->keysToRemove.Num(),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId)
	};

	return ConvertedType;
}
