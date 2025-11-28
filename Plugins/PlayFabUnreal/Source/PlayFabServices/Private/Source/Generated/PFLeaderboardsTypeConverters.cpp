// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFLeaderboardsTypeConverters.h"

const FPFLeaderboardsLeaderboardSortDirection ConvertLeaderboardSortDirectionToUnreal(const PFLeaderboardsLeaderboardSortDirection* enumVal)
{
	if (enumVal == nullptr) {
		return FPFLeaderboardsLeaderboardSortDirection::Descending;
	}

	switch(*enumVal)
	{
	case PFLeaderboardsLeaderboardSortDirection::Descending: return FPFLeaderboardsLeaderboardSortDirection::Descending;
	case PFLeaderboardsLeaderboardSortDirection::Ascending: return FPFLeaderboardsLeaderboardSortDirection::Ascending;
	default:
	return FPFLeaderboardsLeaderboardSortDirection::Descending;
	}
}

const PFLeaderboardsLeaderboardSortDirection ConvertLeaderboardSortDirectionToPlayfab(TSharedPtr<const FPFLeaderboardsLeaderboardSortDirection> enumVal)
{
	if (!enumVal.IsValid()) {
		return PFLeaderboardsLeaderboardSortDirection::Descending;
	}

	switch(*enumVal)
	{
	case FPFLeaderboardsLeaderboardSortDirection::Descending: return PFLeaderboardsLeaderboardSortDirection::Descending;
	case FPFLeaderboardsLeaderboardSortDirection::Ascending: return PFLeaderboardsLeaderboardSortDirection::Ascending;
	default:
	return PFLeaderboardsLeaderboardSortDirection::Descending;
	}
}

const FPFExternalFriendSources ConvertExternalFriendSourcesToUnreal(const PFExternalFriendSources* enumVal)
{
	if (enumVal == nullptr) {
		return FPFExternalFriendSources::None;
	}

	switch(*enumVal)
	{
	case PFExternalFriendSources::None: return FPFExternalFriendSources::None;
	case PFExternalFriendSources::Steam: return FPFExternalFriendSources::Steam;
	case PFExternalFriendSources::Facebook: return FPFExternalFriendSources::Facebook;
	case PFExternalFriendSources::Xbox: return FPFExternalFriendSources::Xbox;
	case PFExternalFriendSources::Psn: return FPFExternalFriendSources::Psn;
	case PFExternalFriendSources::All: return FPFExternalFriendSources::All;
	default:
	return FPFExternalFriendSources::None;
	}
}

const PFExternalFriendSources ConvertExternalFriendSourcesToPlayfab(TSharedPtr<const FPFExternalFriendSources> enumVal)
{
	if (!enumVal.IsValid()) {
		return PFExternalFriendSources::None;
	}

	switch(*enumVal)
	{
	case FPFExternalFriendSources::None: return PFExternalFriendSources::None;
	case FPFExternalFriendSources::Steam: return PFExternalFriendSources::Steam;
	case FPFExternalFriendSources::Facebook: return PFExternalFriendSources::Facebook;
	case FPFExternalFriendSources::Xbox: return PFExternalFriendSources::Xbox;
	case FPFExternalFriendSources::Psn: return PFExternalFriendSources::Psn;
	case FPFExternalFriendSources::All: return PFExternalFriendSources::All;
	default:
	return PFExternalFriendSources::None;
	}
}

TSharedPtr<const FPFLeaderboardsLinkedStatisticColumn> ConvertLinkedStatisticColumnToUnreal(const PFLeaderboardsLinkedStatisticColumn* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFLeaderboardsLinkedStatisticColumn> ConvertedType = MakeShared<FPFLeaderboardsLinkedStatisticColumn>(FPFLeaderboardsLinkedStatisticColumn{
		.linkedStatisticColumnName = Datatype->linkedStatisticColumnName == nullptr ? FString() : FString(Datatype->linkedStatisticColumnName),
		.linkedStatisticName = Datatype->linkedStatisticName == nullptr ? FString() : FString(Datatype->linkedStatisticName)
	});

	return ConvertedType;
}

const PFLeaderboardsLinkedStatisticColumn* ConvertLinkedStatisticColumnToPlayfab(TSharedPtr<const FPFLeaderboardsLinkedStatisticColumn> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFLeaderboardsLinkedStatisticColumn* ConvertedType = new PFLeaderboardsLinkedStatisticColumn{
		.linkedStatisticColumnName = ConvertFStringToCharPtr(Datatype->linkedStatisticColumnName),
		.linkedStatisticName = ConvertFStringToCharPtr(Datatype->linkedStatisticName)
	};

	return ConvertedType;
}

TSharedPtr<const FPFLeaderboardsLeaderboardColumn> ConvertLeaderboardColumnToUnreal(const PFLeaderboardsLeaderboardColumn* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFLeaderboardsLeaderboardColumn> ConvertedType = MakeShared<FPFLeaderboardsLeaderboardColumn>(FPFLeaderboardsLeaderboardColumn{
		.linkedStatisticColumn = ConvertLinkedStatisticColumnToUnreal(Datatype->linkedStatisticColumn),
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name),
		.sortDirection = ConvertLeaderboardSortDirectionToUnreal(&Datatype->sortDirection)
	});

	return ConvertedType;
}

const PFLeaderboardsLeaderboardColumn* ConvertLeaderboardColumnToPlayfab(TSharedPtr<const FPFLeaderboardsLeaderboardColumn> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFLeaderboardsLeaderboardColumn* ConvertedType = new PFLeaderboardsLeaderboardColumn{
		.linkedStatisticColumn = ConvertLinkedStatisticColumnToPlayfab(Datatype->linkedStatisticColumn),
		.name = ConvertFStringToCharPtr(Datatype->name),
		.sortDirection = ConvertLeaderboardSortDirectionToPlayfab(MakeShared<FPFLeaderboardsLeaderboardSortDirection>(Datatype->sortDirection))
	};

	return ConvertedType;
}

TSharedPtr<const FPFLeaderboardsLeaderboardEntityRankOnVersionEndConfig> ConvertLeaderboardEntityRankOnVersionEndConfigToUnreal(const PFLeaderboardsLeaderboardEntityRankOnVersionEndConfig* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFLeaderboardsLeaderboardEntityRankOnVersionEndConfig> ConvertedType = MakeShared<FPFLeaderboardsLeaderboardEntityRankOnVersionEndConfig>(FPFLeaderboardsLeaderboardEntityRankOnVersionEndConfig{
		.eventType = ConvertEventTypeToUnreal(&Datatype->eventType),
		.rankLimit = Datatype->rankLimit
	});

	return ConvertedType;
}

const PFLeaderboardsLeaderboardEntityRankOnVersionEndConfig* ConvertLeaderboardEntityRankOnVersionEndConfigToPlayfab(TSharedPtr<const FPFLeaderboardsLeaderboardEntityRankOnVersionEndConfig> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFLeaderboardsLeaderboardEntityRankOnVersionEndConfig* ConvertedType = new PFLeaderboardsLeaderboardEntityRankOnVersionEndConfig{
		.eventType = ConvertEventTypeToPlayfab(MakeShared<FPFEventType>(Datatype->eventType)),
		.rankLimit = Datatype->rankLimit
	};

	return ConvertedType;
}

TSharedPtr<const FPFLeaderboardsLeaderboardVersionEndConfig> ConvertLeaderboardVersionEndConfigToUnreal(const PFLeaderboardsLeaderboardVersionEndConfig* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFLeaderboardsLeaderboardVersionEndConfig> ConvertedType = MakeShared<FPFLeaderboardsLeaderboardVersionEndConfig>(FPFLeaderboardsLeaderboardVersionEndConfig{
		.eventType = ConvertEventTypeToUnreal(&Datatype->eventType)
	});

	return ConvertedType;
}

const PFLeaderboardsLeaderboardVersionEndConfig* ConvertLeaderboardVersionEndConfigToPlayfab(TSharedPtr<const FPFLeaderboardsLeaderboardVersionEndConfig> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFLeaderboardsLeaderboardVersionEndConfig* ConvertedType = new PFLeaderboardsLeaderboardVersionEndConfig{
		.eventType = ConvertEventTypeToPlayfab(MakeShared<FPFEventType>(Datatype->eventType))
	};

	return ConvertedType;
}

TSharedPtr<const FPFLeaderboardsLeaderboardEventEmissionConfig> ConvertLeaderboardEventEmissionConfigToUnreal(const PFLeaderboardsLeaderboardEventEmissionConfig* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFLeaderboardsLeaderboardEventEmissionConfig> ConvertedType = MakeShared<FPFLeaderboardsLeaderboardEventEmissionConfig>(FPFLeaderboardsLeaderboardEventEmissionConfig{
		.entityRankOnVersionEndConfig = ConvertLeaderboardEntityRankOnVersionEndConfigToUnreal(Datatype->entityRankOnVersionEndConfig),
		.versionEndConfig = ConvertLeaderboardVersionEndConfigToUnreal(Datatype->versionEndConfig)
	});

	return ConvertedType;
}

const PFLeaderboardsLeaderboardEventEmissionConfig* ConvertLeaderboardEventEmissionConfigToPlayfab(TSharedPtr<const FPFLeaderboardsLeaderboardEventEmissionConfig> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFLeaderboardsLeaderboardEventEmissionConfig* ConvertedType = new PFLeaderboardsLeaderboardEventEmissionConfig{
		.entityRankOnVersionEndConfig = ConvertLeaderboardEntityRankOnVersionEndConfigToPlayfab(Datatype->entityRankOnVersionEndConfig),
		.versionEndConfig = ConvertLeaderboardVersionEndConfigToPlayfab(Datatype->versionEndConfig)
	};

	return ConvertedType;
}

TSharedPtr<const FPFLeaderboardsCreateLeaderboardDefinitionRequest> ConvertCreateLeaderboardDefinitionRequestToUnreal(const PFLeaderboardsCreateLeaderboardDefinitionRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFLeaderboardsCreateLeaderboardDefinitionRequest> ConvertedType = MakeShared<FPFLeaderboardsCreateLeaderboardDefinitionRequest>(FPFLeaderboardsCreateLeaderboardDefinitionRequest{
		.columns = ConvertPlayfabArrayToUnreal<PFLeaderboardsLeaderboardColumn, FPFLeaderboardsLeaderboardColumn>(Datatype->columns, Datatype->columnsCount, ConvertLeaderboardColumnToUnreal),
		.columnsCount = Datatype->columnsCount,
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entityType = Datatype->entityType == nullptr ? FString() : FString(Datatype->entityType),
		.eventEmissionConfig = ConvertLeaderboardEventEmissionConfigToUnreal(Datatype->eventEmissionConfig),
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name),
		.sizeLimit = Datatype->sizeLimit,
		.versionConfiguration = ConvertVersionConfigurationToUnreal(Datatype->versionConfiguration)
	});

	return ConvertedType;
}

const PFLeaderboardsCreateLeaderboardDefinitionRequest* ConvertCreateLeaderboardDefinitionRequestToPlayfab(TSharedPtr<const FPFLeaderboardsCreateLeaderboardDefinitionRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFLeaderboardsCreateLeaderboardDefinitionRequest* ConvertedType = new PFLeaderboardsCreateLeaderboardDefinitionRequest{
		.columns = ConvertUnrealArrayToPlayfab<PFLeaderboardsLeaderboardColumn, FPFLeaderboardsLeaderboardColumn>(Datatype->columns, ConvertLeaderboardColumnToPlayfab),
		.columnsCount = (uint32_t)Datatype->columns.Num(),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entityType = ConvertFStringToCharPtr(Datatype->entityType),
		.eventEmissionConfig = ConvertLeaderboardEventEmissionConfigToPlayfab(Datatype->eventEmissionConfig),
		.name = ConvertFStringToCharPtr(Datatype->name),
		.sizeLimit = Datatype->sizeLimit,
		.versionConfiguration = ConvertVersionConfigurationToPlayfab(Datatype->versionConfiguration)
	};

	return ConvertedType;
}

TSharedPtr<const FPFLeaderboardsDeleteLeaderboardDefinitionRequest> ConvertDeleteLeaderboardDefinitionRequestToUnreal(const PFLeaderboardsDeleteLeaderboardDefinitionRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFLeaderboardsDeleteLeaderboardDefinitionRequest> ConvertedType = MakeShared<FPFLeaderboardsDeleteLeaderboardDefinitionRequest>(FPFLeaderboardsDeleteLeaderboardDefinitionRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name)
	});

	return ConvertedType;
}

const PFLeaderboardsDeleteLeaderboardDefinitionRequest* ConvertDeleteLeaderboardDefinitionRequestToPlayfab(TSharedPtr<const FPFLeaderboardsDeleteLeaderboardDefinitionRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFLeaderboardsDeleteLeaderboardDefinitionRequest* ConvertedType = new PFLeaderboardsDeleteLeaderboardDefinitionRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.name = ConvertFStringToCharPtr(Datatype->name)
	};

	return ConvertedType;
}

TSharedPtr<const FPFLeaderboardsDeleteLeaderboardEntriesRequest> ConvertDeleteLeaderboardEntriesRequestToUnreal(const PFLeaderboardsDeleteLeaderboardEntriesRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFLeaderboardsDeleteLeaderboardEntriesRequest> ConvertedType = MakeShared<FPFLeaderboardsDeleteLeaderboardEntriesRequest>(FPFLeaderboardsDeleteLeaderboardEntriesRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entityIds = ConvertCharArrayToUnreal(Datatype->entityIds, Datatype->entityIdsCount),
		.entityIdsCount = Datatype->entityIdsCount,
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name)
	});

	return ConvertedType;
}

const PFLeaderboardsDeleteLeaderboardEntriesRequest* ConvertDeleteLeaderboardEntriesRequestToPlayfab(TSharedPtr<const FPFLeaderboardsDeleteLeaderboardEntriesRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFLeaderboardsDeleteLeaderboardEntriesRequest* ConvertedType = new PFLeaderboardsDeleteLeaderboardEntriesRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entityIds = ConvertFStringArrayToPlayfab(Datatype->entityIds),
		.entityIdsCount = (uint32_t)Datatype->entityIds.Num(),
		.name = ConvertFStringToCharPtr(Datatype->name)
	};

	return ConvertedType;
}

TSharedPtr<const FPFLeaderboardsGetFriendLeaderboardForEntityRequest> ConvertGetFriendLeaderboardForEntityRequestToUnreal(const PFLeaderboardsGetFriendLeaderboardForEntityRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFLeaderboardsGetFriendLeaderboardForEntityRequest> ConvertedType = MakeShared<FPFLeaderboardsGetFriendLeaderboardForEntityRequest>(FPFLeaderboardsGetFriendLeaderboardForEntityRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.externalFriendSources = MakeShared<FPFExternalFriendSources>(ConvertExternalFriendSourcesToUnreal(Datatype->externalFriendSources)),
		.leaderboardName = Datatype->leaderboardName == nullptr ? FString() : FString(Datatype->leaderboardName),
		.version = TSharedPtr<const uint32>(Datatype->version),
		.xboxToken = Datatype->xboxToken == nullptr ? FString() : FString(Datatype->xboxToken)
	});

	return ConvertedType;
}

const PFLeaderboardsGetFriendLeaderboardForEntityRequest* ConvertGetFriendLeaderboardForEntityRequestToPlayfab(TSharedPtr<const FPFLeaderboardsGetFriendLeaderboardForEntityRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFLeaderboardsGetFriendLeaderboardForEntityRequest* ConvertedType = new PFLeaderboardsGetFriendLeaderboardForEntityRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.externalFriendSources = new PFExternalFriendSources(ConvertExternalFriendSourcesToPlayfab(Datatype->externalFriendSources)),
		.leaderboardName = ConvertFStringToCharPtr(Datatype->leaderboardName),
		.version = Datatype->version ? new uint32(*Datatype->version) : nullptr,
		.xboxToken = ConvertFStringToCharPtr(Datatype->xboxToken)
	};

	return ConvertedType;
}

TSharedPtr<const FPFLeaderboardsEntityLeaderboardEntry> ConvertEntityLeaderboardEntryToUnreal(const PFLeaderboardsEntityLeaderboardEntry* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFLeaderboardsEntityLeaderboardEntry> ConvertedType = MakeShared<FPFLeaderboardsEntityLeaderboardEntry>(FPFLeaderboardsEntityLeaderboardEntry{
		.displayName = Datatype->displayName == nullptr ? FString() : FString(Datatype->displayName),
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.lastUpdated = FDateTime::FromUnixTimestamp((int64)Datatype->lastUpdated),
		.metadata = Datatype->metadata == nullptr ? FString() : FString(Datatype->metadata),
		.rank = Datatype->rank,
		.scores = ConvertCharArrayToUnreal(Datatype->scores, Datatype->scoresCount),
		.scoresCount = Datatype->scoresCount
	});

	return ConvertedType;
}

const PFLeaderboardsEntityLeaderboardEntry* ConvertEntityLeaderboardEntryToPlayfab(TSharedPtr<const FPFLeaderboardsEntityLeaderboardEntry> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFLeaderboardsEntityLeaderboardEntry* ConvertedType = new PFLeaderboardsEntityLeaderboardEntry{
		.displayName = ConvertFStringToCharPtr(Datatype->displayName),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.lastUpdated = Datatype->lastUpdated.ToUnixTimestamp(),
		.metadata = ConvertFStringToCharPtr(Datatype->metadata),
		.rank = Datatype->rank,
		.scores = ConvertFStringArrayToPlayfab(Datatype->scores),
		.scoresCount = (uint32_t)Datatype->scores.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFLeaderboardsGetEntityLeaderboardResponse> ConvertGetEntityLeaderboardResponseToUnreal(const PFLeaderboardsGetEntityLeaderboardResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFLeaderboardsGetEntityLeaderboardResponse> ConvertedType = MakeShared<FPFLeaderboardsGetEntityLeaderboardResponse>(FPFLeaderboardsGetEntityLeaderboardResponse{
		.columns = ConvertPlayfabArrayToUnreal<PFLeaderboardsLeaderboardColumn, FPFLeaderboardsLeaderboardColumn>(Datatype->columns, Datatype->columnsCount, ConvertLeaderboardColumnToUnreal),
		.columnsCount = Datatype->columnsCount,
		.entryCount = Datatype->entryCount,
		.nextReset = ConvertTimeToUnreal(Datatype->nextReset),
		.rankings = ConvertPlayfabArrayToUnreal<PFLeaderboardsEntityLeaderboardEntry, FPFLeaderboardsEntityLeaderboardEntry>(Datatype->rankings, Datatype->rankingsCount, ConvertEntityLeaderboardEntryToUnreal),
		.rankingsCount = Datatype->rankingsCount,
		.version = Datatype->version
	});

	return ConvertedType;
}

const PFLeaderboardsGetEntityLeaderboardResponse* ConvertGetEntityLeaderboardResponseToPlayfab(TSharedPtr<const FPFLeaderboardsGetEntityLeaderboardResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFLeaderboardsGetEntityLeaderboardResponse* ConvertedType = new PFLeaderboardsGetEntityLeaderboardResponse{
		.columns = ConvertUnrealArrayToPlayfab<PFLeaderboardsLeaderboardColumn, FPFLeaderboardsLeaderboardColumn>(Datatype->columns, ConvertLeaderboardColumnToPlayfab),
		.columnsCount = (uint32_t)Datatype->columns.Num(),
		.entryCount = Datatype->entryCount,
		.nextReset = ConvertFDateTimeToPlayfab(Datatype->nextReset),
		.rankings = ConvertUnrealArrayToPlayfab<PFLeaderboardsEntityLeaderboardEntry, FPFLeaderboardsEntityLeaderboardEntry>(Datatype->rankings, ConvertEntityLeaderboardEntryToPlayfab),
		.rankingsCount = (uint32_t)Datatype->rankings.Num(),
		.version = Datatype->version
	};

	return ConvertedType;
}

TSharedPtr<const FPFLeaderboardsGetEntityLeaderboardRequest> ConvertGetEntityLeaderboardRequestToUnreal(const PFLeaderboardsGetEntityLeaderboardRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFLeaderboardsGetEntityLeaderboardRequest> ConvertedType = MakeShared<FPFLeaderboardsGetEntityLeaderboardRequest>(FPFLeaderboardsGetEntityLeaderboardRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.leaderboardName = Datatype->leaderboardName == nullptr ? FString() : FString(Datatype->leaderboardName),
		.pageSize = Datatype->pageSize,
		.startingPosition = TSharedPtr<const uint32>(Datatype->startingPosition),
		.version = TSharedPtr<const uint32>(Datatype->version)
	});

	return ConvertedType;
}

const PFLeaderboardsGetEntityLeaderboardRequest* ConvertGetEntityLeaderboardRequestToPlayfab(TSharedPtr<const FPFLeaderboardsGetEntityLeaderboardRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFLeaderboardsGetEntityLeaderboardRequest* ConvertedType = new PFLeaderboardsGetEntityLeaderboardRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.leaderboardName = ConvertFStringToCharPtr(Datatype->leaderboardName),
		.pageSize = Datatype->pageSize,
		.startingPosition = Datatype->startingPosition ? new uint32(*Datatype->startingPosition) : nullptr,
		.version = Datatype->version ? new uint32(*Datatype->version) : nullptr
	};

	return ConvertedType;
}

TSharedPtr<const FPFLeaderboardsGetLeaderboardAroundEntityRequest> ConvertGetLeaderboardAroundEntityRequestToUnreal(const PFLeaderboardsGetLeaderboardAroundEntityRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFLeaderboardsGetLeaderboardAroundEntityRequest> ConvertedType = MakeShared<FPFLeaderboardsGetLeaderboardAroundEntityRequest>(FPFLeaderboardsGetLeaderboardAroundEntityRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.leaderboardName = Datatype->leaderboardName == nullptr ? FString() : FString(Datatype->leaderboardName),
		.maxSurroundingEntries = Datatype->maxSurroundingEntries,
		.version = TSharedPtr<const uint32>(Datatype->version)
	});

	return ConvertedType;
}

const PFLeaderboardsGetLeaderboardAroundEntityRequest* ConvertGetLeaderboardAroundEntityRequestToPlayfab(TSharedPtr<const FPFLeaderboardsGetLeaderboardAroundEntityRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFLeaderboardsGetLeaderboardAroundEntityRequest* ConvertedType = new PFLeaderboardsGetLeaderboardAroundEntityRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.leaderboardName = ConvertFStringToCharPtr(Datatype->leaderboardName),
		.maxSurroundingEntries = Datatype->maxSurroundingEntries,
		.version = Datatype->version ? new uint32(*Datatype->version) : nullptr
	};

	return ConvertedType;
}

TSharedPtr<const FPFLeaderboardsGetLeaderboardDefinitionRequest> ConvertGetLeaderboardDefinitionRequestToUnreal(const PFLeaderboardsGetLeaderboardDefinitionRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFLeaderboardsGetLeaderboardDefinitionRequest> ConvertedType = MakeShared<FPFLeaderboardsGetLeaderboardDefinitionRequest>(FPFLeaderboardsGetLeaderboardDefinitionRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name)
	});

	return ConvertedType;
}

const PFLeaderboardsGetLeaderboardDefinitionRequest* ConvertGetLeaderboardDefinitionRequestToPlayfab(TSharedPtr<const FPFLeaderboardsGetLeaderboardDefinitionRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFLeaderboardsGetLeaderboardDefinitionRequest* ConvertedType = new PFLeaderboardsGetLeaderboardDefinitionRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.name = ConvertFStringToCharPtr(Datatype->name)
	};

	return ConvertedType;
}

TSharedPtr<const FPFLeaderboardsGetLeaderboardDefinitionResponse> ConvertGetLeaderboardDefinitionResponseToUnreal(const PFLeaderboardsGetLeaderboardDefinitionResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFLeaderboardsGetLeaderboardDefinitionResponse> ConvertedType = MakeShared<FPFLeaderboardsGetLeaderboardDefinitionResponse>(FPFLeaderboardsGetLeaderboardDefinitionResponse{
		.columns = ConvertPlayfabArrayToUnreal<PFLeaderboardsLeaderboardColumn, FPFLeaderboardsLeaderboardColumn>(Datatype->columns, Datatype->columnsCount, ConvertLeaderboardColumnToUnreal),
		.columnsCount = Datatype->columnsCount,
		.created = FDateTime::FromUnixTimestamp((int64)Datatype->created),
		.entityType = Datatype->entityType == nullptr ? FString() : FString(Datatype->entityType),
		.eventEmissionConfig = ConvertLeaderboardEventEmissionConfigToUnreal(Datatype->eventEmissionConfig),
		.lastResetTime = ConvertTimeToUnreal(Datatype->lastResetTime),
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name),
		.sizeLimit = Datatype->sizeLimit,
		.version = Datatype->version,
		.versionConfiguration = ConvertVersionConfigurationToUnreal(Datatype->versionConfiguration)
	});

	return ConvertedType;
}

const PFLeaderboardsGetLeaderboardDefinitionResponse* ConvertGetLeaderboardDefinitionResponseToPlayfab(TSharedPtr<const FPFLeaderboardsGetLeaderboardDefinitionResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFLeaderboardsGetLeaderboardDefinitionResponse* ConvertedType = new PFLeaderboardsGetLeaderboardDefinitionResponse{
		.columns = ConvertUnrealArrayToPlayfab<PFLeaderboardsLeaderboardColumn, FPFLeaderboardsLeaderboardColumn>(Datatype->columns, ConvertLeaderboardColumnToPlayfab),
		.columnsCount = (uint32_t)Datatype->columns.Num(),
		.created = Datatype->created.ToUnixTimestamp(),
		.entityType = ConvertFStringToCharPtr(Datatype->entityType),
		.eventEmissionConfig = ConvertLeaderboardEventEmissionConfigToPlayfab(Datatype->eventEmissionConfig),
		.lastResetTime = ConvertFDateTimeToPlayfab(Datatype->lastResetTime),
		.name = ConvertFStringToCharPtr(Datatype->name),
		.sizeLimit = Datatype->sizeLimit,
		.version = Datatype->version,
		.versionConfiguration = ConvertVersionConfigurationToPlayfab(Datatype->versionConfiguration)
	};

	return ConvertedType;
}

TSharedPtr<const FPFLeaderboardsGetLeaderboardForEntitiesRequest> ConvertGetLeaderboardForEntitiesRequestToUnreal(const PFLeaderboardsGetLeaderboardForEntitiesRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFLeaderboardsGetLeaderboardForEntitiesRequest> ConvertedType = MakeShared<FPFLeaderboardsGetLeaderboardForEntitiesRequest>(FPFLeaderboardsGetLeaderboardForEntitiesRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entityIds = ConvertCharArrayToUnreal(Datatype->entityIds, Datatype->entityIdsCount),
		.entityIdsCount = Datatype->entityIdsCount,
		.leaderboardName = Datatype->leaderboardName == nullptr ? FString() : FString(Datatype->leaderboardName),
		.version = TSharedPtr<const uint32>(Datatype->version)
	});

	return ConvertedType;
}

const PFLeaderboardsGetLeaderboardForEntitiesRequest* ConvertGetLeaderboardForEntitiesRequestToPlayfab(TSharedPtr<const FPFLeaderboardsGetLeaderboardForEntitiesRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFLeaderboardsGetLeaderboardForEntitiesRequest* ConvertedType = new PFLeaderboardsGetLeaderboardForEntitiesRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entityIds = ConvertFStringArrayToPlayfab(Datatype->entityIds),
		.entityIdsCount = (uint32_t)Datatype->entityIds.Num(),
		.leaderboardName = ConvertFStringToCharPtr(Datatype->leaderboardName),
		.version = Datatype->version ? new uint32(*Datatype->version) : nullptr
	};

	return ConvertedType;
}

TSharedPtr<const FPFLeaderboardsIncrementLeaderboardVersionRequest> ConvertIncrementLeaderboardVersionRequestToUnreal(const PFLeaderboardsIncrementLeaderboardVersionRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFLeaderboardsIncrementLeaderboardVersionRequest> ConvertedType = MakeShared<FPFLeaderboardsIncrementLeaderboardVersionRequest>(FPFLeaderboardsIncrementLeaderboardVersionRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name)
	});

	return ConvertedType;
}

const PFLeaderboardsIncrementLeaderboardVersionRequest* ConvertIncrementLeaderboardVersionRequestToPlayfab(TSharedPtr<const FPFLeaderboardsIncrementLeaderboardVersionRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFLeaderboardsIncrementLeaderboardVersionRequest* ConvertedType = new PFLeaderboardsIncrementLeaderboardVersionRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.name = ConvertFStringToCharPtr(Datatype->name)
	};

	return ConvertedType;
}

TSharedPtr<const FPFLeaderboardsIncrementLeaderboardVersionResponse> ConvertIncrementLeaderboardVersionResponseToUnreal(const PFLeaderboardsIncrementLeaderboardVersionResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFLeaderboardsIncrementLeaderboardVersionResponse> ConvertedType = MakeShared<FPFLeaderboardsIncrementLeaderboardVersionResponse>(FPFLeaderboardsIncrementLeaderboardVersionResponse{
		.version = Datatype->version
	});

	return ConvertedType;
}

const PFLeaderboardsIncrementLeaderboardVersionResponse* ConvertIncrementLeaderboardVersionResponseToPlayfab(TSharedPtr<const FPFLeaderboardsIncrementLeaderboardVersionResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFLeaderboardsIncrementLeaderboardVersionResponse* ConvertedType = new PFLeaderboardsIncrementLeaderboardVersionResponse{
		.version = Datatype->version
	};

	return ConvertedType;
}

TSharedPtr<const FPFLeaderboardsListLeaderboardDefinitionsRequest> ConvertListLeaderboardDefinitionsRequestToUnreal(const PFLeaderboardsListLeaderboardDefinitionsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFLeaderboardsListLeaderboardDefinitionsRequest> ConvertedType = MakeShared<FPFLeaderboardsListLeaderboardDefinitionsRequest>(FPFLeaderboardsListLeaderboardDefinitionsRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount
	});

	return ConvertedType;
}

const PFLeaderboardsListLeaderboardDefinitionsRequest* ConvertListLeaderboardDefinitionsRequestToPlayfab(TSharedPtr<const FPFLeaderboardsListLeaderboardDefinitionsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFLeaderboardsListLeaderboardDefinitionsRequest* ConvertedType = new PFLeaderboardsListLeaderboardDefinitionsRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFLeaderboardsLeaderboardDefinition> ConvertLeaderboardDefinitionToUnreal(const PFLeaderboardsLeaderboardDefinition* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFLeaderboardsLeaderboardDefinition> ConvertedType = MakeShared<FPFLeaderboardsLeaderboardDefinition>(FPFLeaderboardsLeaderboardDefinition{
		.columns = ConvertPlayfabArrayToUnreal<PFLeaderboardsLeaderboardColumn, FPFLeaderboardsLeaderboardColumn>(Datatype->columns, Datatype->columnsCount, ConvertLeaderboardColumnToUnreal),
		.columnsCount = Datatype->columnsCount,
		.created = FDateTime::FromUnixTimestamp((int64)Datatype->created),
		.entityType = Datatype->entityType == nullptr ? FString() : FString(Datatype->entityType),
		.eventEmissionConfig = ConvertLeaderboardEventEmissionConfigToUnreal(Datatype->eventEmissionConfig),
		.lastResetTime = ConvertTimeToUnreal(Datatype->lastResetTime),
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name),
		.sizeLimit = Datatype->sizeLimit,
		.version = Datatype->version,
		.versionConfiguration = ConvertVersionConfigurationToUnreal(Datatype->versionConfiguration)
	});

	return ConvertedType;
}

const PFLeaderboardsLeaderboardDefinition* ConvertLeaderboardDefinitionToPlayfab(TSharedPtr<const FPFLeaderboardsLeaderboardDefinition> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFLeaderboardsLeaderboardDefinition* ConvertedType = new PFLeaderboardsLeaderboardDefinition{
		.columns = ConvertUnrealArrayToPlayfab<PFLeaderboardsLeaderboardColumn, FPFLeaderboardsLeaderboardColumn>(Datatype->columns, ConvertLeaderboardColumnToPlayfab),
		.columnsCount = (uint32_t)Datatype->columns.Num(),
		.created = Datatype->created.ToUnixTimestamp(),
		.entityType = ConvertFStringToCharPtr(Datatype->entityType),
		.eventEmissionConfig = ConvertLeaderboardEventEmissionConfigToPlayfab(Datatype->eventEmissionConfig),
		.lastResetTime = ConvertFDateTimeToPlayfab(Datatype->lastResetTime),
		.name = ConvertFStringToCharPtr(Datatype->name),
		.sizeLimit = Datatype->sizeLimit,
		.version = Datatype->version,
		.versionConfiguration = ConvertVersionConfigurationToPlayfab(Datatype->versionConfiguration)
	};

	return ConvertedType;
}

TSharedPtr<const FPFLeaderboardsListLeaderboardDefinitionsResponse> ConvertListLeaderboardDefinitionsResponseToUnreal(const PFLeaderboardsListLeaderboardDefinitionsResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFLeaderboardsListLeaderboardDefinitionsResponse> ConvertedType = MakeShared<FPFLeaderboardsListLeaderboardDefinitionsResponse>(FPFLeaderboardsListLeaderboardDefinitionsResponse{
		.leaderboardDefinitions = ConvertPlayfabArrayToUnreal<PFLeaderboardsLeaderboardDefinition, FPFLeaderboardsLeaderboardDefinition>(Datatype->leaderboardDefinitions, Datatype->leaderboardDefinitionsCount, ConvertLeaderboardDefinitionToUnreal),
		.leaderboardDefinitionsCount = Datatype->leaderboardDefinitionsCount
	});

	return ConvertedType;
}

const PFLeaderboardsListLeaderboardDefinitionsResponse* ConvertListLeaderboardDefinitionsResponseToPlayfab(TSharedPtr<const FPFLeaderboardsListLeaderboardDefinitionsResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFLeaderboardsListLeaderboardDefinitionsResponse* ConvertedType = new PFLeaderboardsListLeaderboardDefinitionsResponse{
		.leaderboardDefinitions = ConvertUnrealArrayToPlayfab<PFLeaderboardsLeaderboardDefinition, FPFLeaderboardsLeaderboardDefinition>(Datatype->leaderboardDefinitions, ConvertLeaderboardDefinitionToPlayfab),
		.leaderboardDefinitionsCount = (uint32_t)Datatype->leaderboardDefinitions.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFLeaderboardsUnlinkLeaderboardFromStatisticRequest> ConvertUnlinkLeaderboardFromStatisticRequestToUnreal(const PFLeaderboardsUnlinkLeaderboardFromStatisticRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFLeaderboardsUnlinkLeaderboardFromStatisticRequest> ConvertedType = MakeShared<FPFLeaderboardsUnlinkLeaderboardFromStatisticRequest>(FPFLeaderboardsUnlinkLeaderboardFromStatisticRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name),
		.statisticName = Datatype->statisticName == nullptr ? FString() : FString(Datatype->statisticName)
	});

	return ConvertedType;
}

const PFLeaderboardsUnlinkLeaderboardFromStatisticRequest* ConvertUnlinkLeaderboardFromStatisticRequestToPlayfab(TSharedPtr<const FPFLeaderboardsUnlinkLeaderboardFromStatisticRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFLeaderboardsUnlinkLeaderboardFromStatisticRequest* ConvertedType = new PFLeaderboardsUnlinkLeaderboardFromStatisticRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.name = ConvertFStringToCharPtr(Datatype->name),
		.statisticName = ConvertFStringToCharPtr(Datatype->statisticName)
	};

	return ConvertedType;
}

TSharedPtr<const FPFLeaderboardsUpdateLeaderboardDefinitionRequest> ConvertUpdateLeaderboardDefinitionRequestToUnreal(const PFLeaderboardsUpdateLeaderboardDefinitionRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFLeaderboardsUpdateLeaderboardDefinitionRequest> ConvertedType = MakeShared<FPFLeaderboardsUpdateLeaderboardDefinitionRequest>(FPFLeaderboardsUpdateLeaderboardDefinitionRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.eventEmissionConfig = ConvertLeaderboardEventEmissionConfigToUnreal(Datatype->eventEmissionConfig),
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name),
		.sizeLimit = TSharedPtr<const int32>(Datatype->sizeLimit),
		.versionConfiguration = ConvertVersionConfigurationToUnreal(Datatype->versionConfiguration)
	});

	return ConvertedType;
}

const PFLeaderboardsUpdateLeaderboardDefinitionRequest* ConvertUpdateLeaderboardDefinitionRequestToPlayfab(TSharedPtr<const FPFLeaderboardsUpdateLeaderboardDefinitionRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFLeaderboardsUpdateLeaderboardDefinitionRequest* ConvertedType = new PFLeaderboardsUpdateLeaderboardDefinitionRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.eventEmissionConfig = ConvertLeaderboardEventEmissionConfigToPlayfab(Datatype->eventEmissionConfig),
		.name = ConvertFStringToCharPtr(Datatype->name),
		.sizeLimit = Datatype->sizeLimit ? new int32(*Datatype->sizeLimit) : nullptr,
		.versionConfiguration = ConvertVersionConfigurationToPlayfab(Datatype->versionConfiguration)
	};

	return ConvertedType;
}

TSharedPtr<const FPFLeaderboardsLeaderboardEntryUpdate> ConvertLeaderboardEntryUpdateToUnreal(const PFLeaderboardsLeaderboardEntryUpdate* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFLeaderboardsLeaderboardEntryUpdate> ConvertedType = MakeShared<FPFLeaderboardsLeaderboardEntryUpdate>(FPFLeaderboardsLeaderboardEntryUpdate{
		.entityId = Datatype->entityId == nullptr ? FString() : FString(Datatype->entityId),
		.metadata = Datatype->metadata == nullptr ? FString() : FString(Datatype->metadata),
		.scores = ConvertCharArrayToUnreal(Datatype->scores, Datatype->scoresCount),
		.scoresCount = Datatype->scoresCount
	});

	return ConvertedType;
}

const PFLeaderboardsLeaderboardEntryUpdate* ConvertLeaderboardEntryUpdateToPlayfab(TSharedPtr<const FPFLeaderboardsLeaderboardEntryUpdate> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFLeaderboardsLeaderboardEntryUpdate* ConvertedType = new PFLeaderboardsLeaderboardEntryUpdate{
		.entityId = ConvertFStringToCharPtr(Datatype->entityId),
		.metadata = ConvertFStringToCharPtr(Datatype->metadata),
		.scores = ConvertFStringArrayToPlayfab(Datatype->scores),
		.scoresCount = (uint32_t)Datatype->scores.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFLeaderboardsUpdateLeaderboardEntriesRequest> ConvertUpdateLeaderboardEntriesRequestToUnreal(const PFLeaderboardsUpdateLeaderboardEntriesRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFLeaderboardsUpdateLeaderboardEntriesRequest> ConvertedType = MakeShared<FPFLeaderboardsUpdateLeaderboardEntriesRequest>(FPFLeaderboardsUpdateLeaderboardEntriesRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entries = ConvertPlayfabArrayToUnreal<PFLeaderboardsLeaderboardEntryUpdate, FPFLeaderboardsLeaderboardEntryUpdate>(Datatype->entries, Datatype->entriesCount, ConvertLeaderboardEntryUpdateToUnreal),
		.entriesCount = Datatype->entriesCount,
		.leaderboardName = Datatype->leaderboardName == nullptr ? FString() : FString(Datatype->leaderboardName)
	});

	return ConvertedType;
}

const PFLeaderboardsUpdateLeaderboardEntriesRequest* ConvertUpdateLeaderboardEntriesRequestToPlayfab(TSharedPtr<const FPFLeaderboardsUpdateLeaderboardEntriesRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFLeaderboardsUpdateLeaderboardEntriesRequest* ConvertedType = new PFLeaderboardsUpdateLeaderboardEntriesRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entries = ConvertUnrealArrayToPlayfab<PFLeaderboardsLeaderboardEntryUpdate, FPFLeaderboardsLeaderboardEntryUpdate>(Datatype->entries, ConvertLeaderboardEntryUpdateToPlayfab),
		.entriesCount = (uint32_t)Datatype->entries.Num(),
		.leaderboardName = ConvertFStringToCharPtr(Datatype->leaderboardName)
	};

	return ConvertedType;
}
