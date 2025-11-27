// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFStatisticsTypeConverters.h"

const FPFStatisticsStatisticAggregationMethod ConvertStatisticAggregationMethodToUnreal(const PFStatisticsStatisticAggregationMethod* enumVal)
{
	if (enumVal == nullptr) {
		return FPFStatisticsStatisticAggregationMethod::Last;
	}

	switch(*enumVal)
	{
	case PFStatisticsStatisticAggregationMethod::Last: return FPFStatisticsStatisticAggregationMethod::Last;
	case PFStatisticsStatisticAggregationMethod::Min: return FPFStatisticsStatisticAggregationMethod::Min;
	case PFStatisticsStatisticAggregationMethod::Max: return FPFStatisticsStatisticAggregationMethod::Max;
	case PFStatisticsStatisticAggregationMethod::Sum: return FPFStatisticsStatisticAggregationMethod::Sum;
	default:
	return FPFStatisticsStatisticAggregationMethod::Last;
	}
}

const PFStatisticsStatisticAggregationMethod ConvertStatisticAggregationMethodToPlayfab(TSharedPtr<const FPFStatisticsStatisticAggregationMethod> enumVal)
{
	if (!enumVal.IsValid()) {
		return PFStatisticsStatisticAggregationMethod::Last;
	}

	switch(*enumVal)
	{
	case FPFStatisticsStatisticAggregationMethod::Last: return PFStatisticsStatisticAggregationMethod::Last;
	case FPFStatisticsStatisticAggregationMethod::Min: return PFStatisticsStatisticAggregationMethod::Min;
	case FPFStatisticsStatisticAggregationMethod::Max: return PFStatisticsStatisticAggregationMethod::Max;
	case FPFStatisticsStatisticAggregationMethod::Sum: return PFStatisticsStatisticAggregationMethod::Sum;
	default:
	return PFStatisticsStatisticAggregationMethod::Last;
	}
}

TSharedPtr<const FPFStatisticsStatisticColumn> ConvertStatisticColumnToUnreal(const PFStatisticsStatisticColumn* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFStatisticsStatisticColumn> ConvertedType = MakeShared<FPFStatisticsStatisticColumn>(FPFStatisticsStatisticColumn{
		.aggregationMethod = ConvertStatisticAggregationMethodToUnreal(&Datatype->aggregationMethod),
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name)
	});

	return ConvertedType;
}

const PFStatisticsStatisticColumn* ConvertStatisticColumnToPlayfab(TSharedPtr<const FPFStatisticsStatisticColumn> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFStatisticsStatisticColumn* ConvertedType = new PFStatisticsStatisticColumn{
		.aggregationMethod = ConvertStatisticAggregationMethodToPlayfab(MakeShared<FPFStatisticsStatisticAggregationMethod>(Datatype->aggregationMethod)),
		.name = ConvertFStringToCharPtr(Datatype->name)
	};

	return ConvertedType;
}

TSharedPtr<const FPFStatisticsStatisticsUpdateEventConfig> ConvertStatisticsUpdateEventConfigToUnreal(const PFStatisticsStatisticsUpdateEventConfig* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFStatisticsStatisticsUpdateEventConfig> ConvertedType = MakeShared<FPFStatisticsStatisticsUpdateEventConfig>(FPFStatisticsStatisticsUpdateEventConfig{
		.eventType = ConvertEventTypeToUnreal(&Datatype->eventType)
	});

	return ConvertedType;
}

const PFStatisticsStatisticsUpdateEventConfig* ConvertStatisticsUpdateEventConfigToPlayfab(TSharedPtr<const FPFStatisticsStatisticsUpdateEventConfig> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFStatisticsStatisticsUpdateEventConfig* ConvertedType = new PFStatisticsStatisticsUpdateEventConfig{
		.eventType = ConvertEventTypeToPlayfab(MakeShared<FPFEventType>(Datatype->eventType))
	};

	return ConvertedType;
}

TSharedPtr<const FPFStatisticsStatisticsEventEmissionConfig> ConvertStatisticsEventEmissionConfigToUnreal(const PFStatisticsStatisticsEventEmissionConfig* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFStatisticsStatisticsEventEmissionConfig> ConvertedType = MakeShared<FPFStatisticsStatisticsEventEmissionConfig>(FPFStatisticsStatisticsEventEmissionConfig{
		.updateEventConfig = ConvertStatisticsUpdateEventConfigToUnreal(Datatype->updateEventConfig)
	});

	return ConvertedType;
}

const PFStatisticsStatisticsEventEmissionConfig* ConvertStatisticsEventEmissionConfigToPlayfab(TSharedPtr<const FPFStatisticsStatisticsEventEmissionConfig> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFStatisticsStatisticsEventEmissionConfig* ConvertedType = new PFStatisticsStatisticsEventEmissionConfig{
		.updateEventConfig = ConvertStatisticsUpdateEventConfigToPlayfab(Datatype->updateEventConfig)
	};

	return ConvertedType;
}

TSharedPtr<const FPFStatisticsCreateStatisticDefinitionRequest> ConvertCreateStatisticDefinitionRequestToUnreal(const PFStatisticsCreateStatisticDefinitionRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFStatisticsCreateStatisticDefinitionRequest> ConvertedType = MakeShared<FPFStatisticsCreateStatisticDefinitionRequest>(FPFStatisticsCreateStatisticDefinitionRequest{
		.aggregationSources = ConvertCharArrayToUnreal(Datatype->aggregationSources, Datatype->aggregationSourcesCount),
		.aggregationSourcesCount = Datatype->aggregationSourcesCount,
		.columns = ConvertPlayfabArrayToUnreal<PFStatisticsStatisticColumn, FPFStatisticsStatisticColumn>(Datatype->columns, Datatype->columnsCount, ConvertStatisticColumnToUnreal),
		.columnsCount = Datatype->columnsCount,
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entityType = Datatype->entityType == nullptr ? FString() : FString(Datatype->entityType),
		.eventEmissionConfig = ConvertStatisticsEventEmissionConfigToUnreal(Datatype->eventEmissionConfig),
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name),
		.versionConfiguration = ConvertVersionConfigurationToUnreal(Datatype->versionConfiguration)
	});

	return ConvertedType;
}

const PFStatisticsCreateStatisticDefinitionRequest* ConvertCreateStatisticDefinitionRequestToPlayfab(TSharedPtr<const FPFStatisticsCreateStatisticDefinitionRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFStatisticsCreateStatisticDefinitionRequest* ConvertedType = new PFStatisticsCreateStatisticDefinitionRequest{
		.aggregationSources = ConvertFStringArrayToPlayfab(Datatype->aggregationSources),
		.aggregationSourcesCount = (uint32_t)Datatype->aggregationSources.Num(),
		.columns = ConvertUnrealArrayToPlayfab<PFStatisticsStatisticColumn, FPFStatisticsStatisticColumn>(Datatype->columns, ConvertStatisticColumnToPlayfab),
		.columnsCount = (uint32_t)Datatype->columns.Num(),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entityType = ConvertFStringToCharPtr(Datatype->entityType),
		.eventEmissionConfig = ConvertStatisticsEventEmissionConfigToPlayfab(Datatype->eventEmissionConfig),
		.name = ConvertFStringToCharPtr(Datatype->name),
		.versionConfiguration = ConvertVersionConfigurationToPlayfab(Datatype->versionConfiguration)
	};

	return ConvertedType;
}

TSharedPtr<const FPFStatisticsDeleteStatisticDefinitionRequest> ConvertDeleteStatisticDefinitionRequestToUnreal(const PFStatisticsDeleteStatisticDefinitionRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFStatisticsDeleteStatisticDefinitionRequest> ConvertedType = MakeShared<FPFStatisticsDeleteStatisticDefinitionRequest>(FPFStatisticsDeleteStatisticDefinitionRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name)
	});

	return ConvertedType;
}

const PFStatisticsDeleteStatisticDefinitionRequest* ConvertDeleteStatisticDefinitionRequestToPlayfab(TSharedPtr<const FPFStatisticsDeleteStatisticDefinitionRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFStatisticsDeleteStatisticDefinitionRequest* ConvertedType = new PFStatisticsDeleteStatisticDefinitionRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.name = ConvertFStringToCharPtr(Datatype->name)
	};

	return ConvertedType;
}

TSharedPtr<const FPFStatisticsStatisticDelete> ConvertStatisticDeleteToUnreal(const PFStatisticsStatisticDelete* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFStatisticsStatisticDelete> ConvertedType = MakeShared<FPFStatisticsStatisticDelete>(FPFStatisticsStatisticDelete{
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name)
	});

	return ConvertedType;
}

const PFStatisticsStatisticDelete* ConvertStatisticDeleteToPlayfab(TSharedPtr<const FPFStatisticsStatisticDelete> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFStatisticsStatisticDelete* ConvertedType = new PFStatisticsStatisticDelete{
		.name = ConvertFStringToCharPtr(Datatype->name)
	};

	return ConvertedType;
}

TSharedPtr<const FPFStatisticsDeleteStatisticsRequest> ConvertDeleteStatisticsRequestToUnreal(const PFStatisticsDeleteStatisticsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFStatisticsDeleteStatisticsRequest> ConvertedType = MakeShared<FPFStatisticsDeleteStatisticsRequest>(FPFStatisticsDeleteStatisticsRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.statistics = ConvertPlayfabArrayToUnreal<PFStatisticsStatisticDelete, FPFStatisticsStatisticDelete>(Datatype->statistics, Datatype->statisticsCount, ConvertStatisticDeleteToUnreal),
		.statisticsCount = Datatype->statisticsCount
	});

	return ConvertedType;
}

const PFStatisticsDeleteStatisticsRequest* ConvertDeleteStatisticsRequestToPlayfab(TSharedPtr<const FPFStatisticsDeleteStatisticsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFStatisticsDeleteStatisticsRequest* ConvertedType = new PFStatisticsDeleteStatisticsRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.statistics = ConvertUnrealArrayToPlayfab<PFStatisticsStatisticDelete, FPFStatisticsStatisticDelete>(Datatype->statistics, ConvertStatisticDeleteToPlayfab),
		.statisticsCount = (uint32_t)Datatype->statistics.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFStatisticsDeleteStatisticsResponse> ConvertDeleteStatisticsResponseToUnreal(const PFStatisticsDeleteStatisticsResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFStatisticsDeleteStatisticsResponse> ConvertedType = MakeShared<FPFStatisticsDeleteStatisticsResponse>(FPFStatisticsDeleteStatisticsResponse{
		.entity = ConvertEntityKeyToUnreal(Datatype->entity)
	});

	return ConvertedType;
}

const PFStatisticsDeleteStatisticsResponse* ConvertDeleteStatisticsResponseToPlayfab(TSharedPtr<const FPFStatisticsDeleteStatisticsResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFStatisticsDeleteStatisticsResponse* ConvertedType = new PFStatisticsDeleteStatisticsResponse{
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity)
	};

	return ConvertedType;
}

TSharedPtr<const FPFStatisticsGetStatisticDefinitionRequest> ConvertGetStatisticDefinitionRequestToUnreal(const PFStatisticsGetStatisticDefinitionRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFStatisticsGetStatisticDefinitionRequest> ConvertedType = MakeShared<FPFStatisticsGetStatisticDefinitionRequest>(FPFStatisticsGetStatisticDefinitionRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name)
	});

	return ConvertedType;
}

const PFStatisticsGetStatisticDefinitionRequest* ConvertGetStatisticDefinitionRequestToPlayfab(TSharedPtr<const FPFStatisticsGetStatisticDefinitionRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFStatisticsGetStatisticDefinitionRequest* ConvertedType = new PFStatisticsGetStatisticDefinitionRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.name = ConvertFStringToCharPtr(Datatype->name)
	};

	return ConvertedType;
}

TSharedPtr<const FPFStatisticsGetStatisticDefinitionResponse> ConvertGetStatisticDefinitionResponseToUnreal(const PFStatisticsGetStatisticDefinitionResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFStatisticsGetStatisticDefinitionResponse> ConvertedType = MakeShared<FPFStatisticsGetStatisticDefinitionResponse>(FPFStatisticsGetStatisticDefinitionResponse{
		.aggregationDestinations = ConvertCharArrayToUnreal(Datatype->aggregationDestinations, Datatype->aggregationDestinationsCount),
		.aggregationDestinationsCount = Datatype->aggregationDestinationsCount,
		.aggregationSources = ConvertCharArrayToUnreal(Datatype->aggregationSources, Datatype->aggregationSourcesCount),
		.aggregationSourcesCount = Datatype->aggregationSourcesCount,
		.columns = ConvertPlayfabArrayToUnreal<PFStatisticsStatisticColumn, FPFStatisticsStatisticColumn>(Datatype->columns, Datatype->columnsCount, ConvertStatisticColumnToUnreal),
		.columnsCount = Datatype->columnsCount,
		.created = FDateTime::FromUnixTimestamp((int64)Datatype->created),
		.entityType = Datatype->entityType == nullptr ? FString() : FString(Datatype->entityType),
		.eventEmissionConfig = ConvertStatisticsEventEmissionConfigToUnreal(Datatype->eventEmissionConfig),
		.lastResetTime = ConvertTimeToUnreal(Datatype->lastResetTime),
		.linkedLeaderboardNames = ConvertCharArrayToUnreal(Datatype->linkedLeaderboardNames, Datatype->linkedLeaderboardNamesCount),
		.linkedLeaderboardNamesCount = Datatype->linkedLeaderboardNamesCount,
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name),
		.version = Datatype->version,
		.versionConfiguration = ConvertVersionConfigurationToUnreal(Datatype->versionConfiguration)
	});

	return ConvertedType;
}

const PFStatisticsGetStatisticDefinitionResponse* ConvertGetStatisticDefinitionResponseToPlayfab(TSharedPtr<const FPFStatisticsGetStatisticDefinitionResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFStatisticsGetStatisticDefinitionResponse* ConvertedType = new PFStatisticsGetStatisticDefinitionResponse{
		.aggregationDestinations = ConvertFStringArrayToPlayfab(Datatype->aggregationDestinations),
		.aggregationDestinationsCount = (uint32_t)Datatype->aggregationDestinations.Num(),
		.aggregationSources = ConvertFStringArrayToPlayfab(Datatype->aggregationSources),
		.aggregationSourcesCount = (uint32_t)Datatype->aggregationSources.Num(),
		.columns = ConvertUnrealArrayToPlayfab<PFStatisticsStatisticColumn, FPFStatisticsStatisticColumn>(Datatype->columns, ConvertStatisticColumnToPlayfab),
		.columnsCount = (uint32_t)Datatype->columns.Num(),
		.created = Datatype->created.ToUnixTimestamp(),
		.entityType = ConvertFStringToCharPtr(Datatype->entityType),
		.eventEmissionConfig = ConvertStatisticsEventEmissionConfigToPlayfab(Datatype->eventEmissionConfig),
		.lastResetTime = ConvertFDateTimeToPlayfab(Datatype->lastResetTime),
		.linkedLeaderboardNames = ConvertFStringArrayToPlayfab(Datatype->linkedLeaderboardNames),
		.linkedLeaderboardNamesCount = (uint32_t)Datatype->linkedLeaderboardNames.Num(),
		.name = ConvertFStringToCharPtr(Datatype->name),
		.version = Datatype->version,
		.versionConfiguration = ConvertVersionConfigurationToPlayfab(Datatype->versionConfiguration)
	};

	return ConvertedType;
}

TSharedPtr<const FPFStatisticsGetStatisticsRequest> ConvertGetStatisticsRequestToUnreal(const PFStatisticsGetStatisticsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFStatisticsGetStatisticsRequest> ConvertedType = MakeShared<FPFStatisticsGetStatisticsRequest>(FPFStatisticsGetStatisticsRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.statisticNames = ConvertCharArrayToUnreal(Datatype->statisticNames, Datatype->statisticNamesCount),
		.statisticNamesCount = Datatype->statisticNamesCount
	});

	return ConvertedType;
}

const PFStatisticsGetStatisticsRequest* ConvertGetStatisticsRequestToPlayfab(TSharedPtr<const FPFStatisticsGetStatisticsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFStatisticsGetStatisticsRequest* ConvertedType = new PFStatisticsGetStatisticsRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.statisticNames = ConvertFStringArrayToPlayfab(Datatype->statisticNames),
		.statisticNamesCount = (uint32_t)Datatype->statisticNames.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFStatisticsStatisticColumnCollection> ConvertStatisticColumnCollectionToUnreal(const PFStatisticsStatisticColumnCollection* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFStatisticsStatisticColumnCollection> ConvertedType = MakeShared<FPFStatisticsStatisticColumnCollection>(FPFStatisticsStatisticColumnCollection{
		.columns = ConvertPlayfabArrayToUnreal<PFStatisticsStatisticColumn, FPFStatisticsStatisticColumn>(Datatype->columns, Datatype->columnsCount, ConvertStatisticColumnToUnreal),
		.columnsCount = Datatype->columnsCount
	});

	return ConvertedType;
}

const PFStatisticsStatisticColumnCollection* ConvertStatisticColumnCollectionToPlayfab(TSharedPtr<const FPFStatisticsStatisticColumnCollection> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFStatisticsStatisticColumnCollection* ConvertedType = new PFStatisticsStatisticColumnCollection{
		.columns = ConvertUnrealArrayToPlayfab<PFStatisticsStatisticColumn, FPFStatisticsStatisticColumn>(Datatype->columns, ConvertStatisticColumnToPlayfab),
		.columnsCount = (uint32_t)Datatype->columns.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFStatisticsEntityStatisticValue> ConvertEntityStatisticValueToUnreal(const PFStatisticsEntityStatisticValue* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFStatisticsEntityStatisticValue> ConvertedType = MakeShared<FPFStatisticsEntityStatisticValue>(FPFStatisticsEntityStatisticValue{
		.metadata = Datatype->metadata == nullptr ? FString() : FString(Datatype->metadata),
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name),
		.scores = ConvertCharArrayToUnreal(Datatype->scores, Datatype->scoresCount),
		.scoresCount = Datatype->scoresCount,
		.version = Datatype->version
	});

	return ConvertedType;
}

const PFStatisticsEntityStatisticValue* ConvertEntityStatisticValueToPlayfab(TSharedPtr<const FPFStatisticsEntityStatisticValue> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFStatisticsEntityStatisticValue* ConvertedType = new PFStatisticsEntityStatisticValue{
		.metadata = ConvertFStringToCharPtr(Datatype->metadata),
		.name = ConvertFStringToCharPtr(Datatype->name),
		.scores = ConvertFStringArrayToPlayfab(Datatype->scores),
		.scoresCount = (uint32_t)Datatype->scores.Num(),
		.version = Datatype->version
	};

	return ConvertedType;
}

TSharedPtr<const FPFStatisticsGetStatisticsResponse> ConvertGetStatisticsResponseToUnreal(const PFStatisticsGetStatisticsResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFStatisticsGetStatisticsResponse> ConvertedType = MakeShared<FPFStatisticsGetStatisticsResponse>(FPFStatisticsGetStatisticsResponse{
		.columnDetails = ConvertPlayfabMapToUnreal<PFStatisticsStatisticColumnCollectionDictionaryEntry, FPFStatisticsStatisticColumnCollection, PFStatisticsStatisticColumnCollection>(Datatype->columnDetails, Datatype->columnDetailsCount, ConvertStatisticColumnCollectionToUnreal),
		.columnDetailsCount = Datatype->columnDetailsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.statistics = ConvertPlayfabMapToUnreal<PFStatisticsEntityStatisticValueDictionaryEntry, FPFStatisticsEntityStatisticValue, PFStatisticsEntityStatisticValue>(Datatype->statistics, Datatype->statisticsCount, ConvertEntityStatisticValueToUnreal),
		.statisticsCount = Datatype->statisticsCount
	});

	return ConvertedType;
}

const PFStatisticsGetStatisticsResponse* ConvertGetStatisticsResponseToPlayfab(TSharedPtr<const FPFStatisticsGetStatisticsResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFStatisticsGetStatisticsResponse* ConvertedType = new PFStatisticsGetStatisticsResponse{
		.columnDetails = ConvertUnrealMapToPlayfab<PFStatisticsStatisticColumnCollectionDictionaryEntry, FPFStatisticsStatisticColumnCollection, PFStatisticsStatisticColumnCollection>(Datatype->columnDetails, ConvertStatisticColumnCollectionToPlayfab),
		.columnDetailsCount = (uint32_t)Datatype->columnDetails.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.statistics = ConvertUnrealMapToPlayfab<PFStatisticsEntityStatisticValueDictionaryEntry, FPFStatisticsEntityStatisticValue, PFStatisticsEntityStatisticValue>(Datatype->statistics, ConvertEntityStatisticValueToPlayfab),
		.statisticsCount = (uint32_t)Datatype->statistics.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFStatisticsGetStatisticsForEntitiesRequest> ConvertGetStatisticsForEntitiesRequestToUnreal(const PFStatisticsGetStatisticsForEntitiesRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFStatisticsGetStatisticsForEntitiesRequest> ConvertedType = MakeShared<FPFStatisticsGetStatisticsForEntitiesRequest>(FPFStatisticsGetStatisticsForEntitiesRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entities = ConvertPlayfabArrayToUnreal<PFEntityKey, FPFEntityKey>(Datatype->entities, Datatype->entitiesCount, ConvertEntityKeyToUnreal),
		.entitiesCount = Datatype->entitiesCount,
		.statisticNames = ConvertCharArrayToUnreal(Datatype->statisticNames, Datatype->statisticNamesCount),
		.statisticNamesCount = Datatype->statisticNamesCount
	});

	return ConvertedType;
}

const PFStatisticsGetStatisticsForEntitiesRequest* ConvertGetStatisticsForEntitiesRequestToPlayfab(TSharedPtr<const FPFStatisticsGetStatisticsForEntitiesRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFStatisticsGetStatisticsForEntitiesRequest* ConvertedType = new PFStatisticsGetStatisticsForEntitiesRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entities = ConvertUnrealArrayToPlayfab<PFEntityKey, FPFEntityKey>(Datatype->entities, ConvertEntityKeyToPlayfab),
		.entitiesCount = (uint32_t)Datatype->entities.Num(),
		.statisticNames = ConvertFStringArrayToPlayfab(Datatype->statisticNames),
		.statisticNamesCount = (uint32_t)Datatype->statisticNames.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFStatisticsEntityStatistics> ConvertEntityStatisticsToUnreal(const PFStatisticsEntityStatistics* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFStatisticsEntityStatistics> ConvertedType = MakeShared<FPFStatisticsEntityStatistics>(FPFStatisticsEntityStatistics{
		.entityKey = ConvertEntityKeyToUnreal(Datatype->entityKey),
		.statistics = ConvertPlayfabArrayToUnreal<PFStatisticsEntityStatisticValue, FPFStatisticsEntityStatisticValue>(Datatype->statistics, Datatype->statisticsCount, ConvertEntityStatisticValueToUnreal),
		.statisticsCount = Datatype->statisticsCount
	});

	return ConvertedType;
}

const PFStatisticsEntityStatistics* ConvertEntityStatisticsToPlayfab(TSharedPtr<const FPFStatisticsEntityStatistics> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFStatisticsEntityStatistics* ConvertedType = new PFStatisticsEntityStatistics{
		.entityKey = ConvertEntityKeyToPlayfab(Datatype->entityKey),
		.statistics = ConvertUnrealArrayToPlayfab<PFStatisticsEntityStatisticValue, FPFStatisticsEntityStatisticValue>(Datatype->statistics, ConvertEntityStatisticValueToPlayfab),
		.statisticsCount = (uint32_t)Datatype->statistics.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFStatisticsGetStatisticsForEntitiesResponse> ConvertGetStatisticsForEntitiesResponseToUnreal(const PFStatisticsGetStatisticsForEntitiesResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFStatisticsGetStatisticsForEntitiesResponse> ConvertedType = MakeShared<FPFStatisticsGetStatisticsForEntitiesResponse>(FPFStatisticsGetStatisticsForEntitiesResponse{
		.columnDetails = ConvertPlayfabMapToUnreal<PFStatisticsStatisticColumnCollectionDictionaryEntry, FPFStatisticsStatisticColumnCollection, PFStatisticsStatisticColumnCollection>(Datatype->columnDetails, Datatype->columnDetailsCount, ConvertStatisticColumnCollectionToUnreal),
		.columnDetailsCount = Datatype->columnDetailsCount,
		.entitiesStatistics = ConvertPlayfabArrayToUnreal<PFStatisticsEntityStatistics, FPFStatisticsEntityStatistics>(Datatype->entitiesStatistics, Datatype->entitiesStatisticsCount, ConvertEntityStatisticsToUnreal),
		.entitiesStatisticsCount = Datatype->entitiesStatisticsCount
	});

	return ConvertedType;
}

const PFStatisticsGetStatisticsForEntitiesResponse* ConvertGetStatisticsForEntitiesResponseToPlayfab(TSharedPtr<const FPFStatisticsGetStatisticsForEntitiesResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFStatisticsGetStatisticsForEntitiesResponse* ConvertedType = new PFStatisticsGetStatisticsForEntitiesResponse{
		.columnDetails = ConvertUnrealMapToPlayfab<PFStatisticsStatisticColumnCollectionDictionaryEntry, FPFStatisticsStatisticColumnCollection, PFStatisticsStatisticColumnCollection>(Datatype->columnDetails, ConvertStatisticColumnCollectionToPlayfab),
		.columnDetailsCount = (uint32_t)Datatype->columnDetails.Num(),
		.entitiesStatistics = ConvertUnrealArrayToPlayfab<PFStatisticsEntityStatistics, FPFStatisticsEntityStatistics>(Datatype->entitiesStatistics, ConvertEntityStatisticsToPlayfab),
		.entitiesStatisticsCount = (uint32_t)Datatype->entitiesStatistics.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFStatisticsIncrementStatisticVersionRequest> ConvertIncrementStatisticVersionRequestToUnreal(const PFStatisticsIncrementStatisticVersionRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFStatisticsIncrementStatisticVersionRequest> ConvertedType = MakeShared<FPFStatisticsIncrementStatisticVersionRequest>(FPFStatisticsIncrementStatisticVersionRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name)
	});

	return ConvertedType;
}

const PFStatisticsIncrementStatisticVersionRequest* ConvertIncrementStatisticVersionRequestToPlayfab(TSharedPtr<const FPFStatisticsIncrementStatisticVersionRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFStatisticsIncrementStatisticVersionRequest* ConvertedType = new PFStatisticsIncrementStatisticVersionRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.name = ConvertFStringToCharPtr(Datatype->name)
	};

	return ConvertedType;
}

TSharedPtr<const FPFStatisticsIncrementStatisticVersionResponse> ConvertIncrementStatisticVersionResponseToUnreal(const PFStatisticsIncrementStatisticVersionResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFStatisticsIncrementStatisticVersionResponse> ConvertedType = MakeShared<FPFStatisticsIncrementStatisticVersionResponse>(FPFStatisticsIncrementStatisticVersionResponse{
		.version = Datatype->version
	});

	return ConvertedType;
}

const PFStatisticsIncrementStatisticVersionResponse* ConvertIncrementStatisticVersionResponseToPlayfab(TSharedPtr<const FPFStatisticsIncrementStatisticVersionResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFStatisticsIncrementStatisticVersionResponse* ConvertedType = new PFStatisticsIncrementStatisticVersionResponse{
		.version = Datatype->version
	};

	return ConvertedType;
}

TSharedPtr<const FPFStatisticsListStatisticDefinitionsRequest> ConvertListStatisticDefinitionsRequestToUnreal(const PFStatisticsListStatisticDefinitionsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFStatisticsListStatisticDefinitionsRequest> ConvertedType = MakeShared<FPFStatisticsListStatisticDefinitionsRequest>(FPFStatisticsListStatisticDefinitionsRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount
	});

	return ConvertedType;
}

const PFStatisticsListStatisticDefinitionsRequest* ConvertListStatisticDefinitionsRequestToPlayfab(TSharedPtr<const FPFStatisticsListStatisticDefinitionsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFStatisticsListStatisticDefinitionsRequest* ConvertedType = new PFStatisticsListStatisticDefinitionsRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFStatisticsStatisticDefinition> ConvertStatisticDefinitionToUnreal(const PFStatisticsStatisticDefinition* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFStatisticsStatisticDefinition> ConvertedType = MakeShared<FPFStatisticsStatisticDefinition>(FPFStatisticsStatisticDefinition{
		.aggregationDestinations = ConvertCharArrayToUnreal(Datatype->aggregationDestinations, Datatype->aggregationDestinationsCount),
		.aggregationDestinationsCount = Datatype->aggregationDestinationsCount,
		.aggregationSources = ConvertCharArrayToUnreal(Datatype->aggregationSources, Datatype->aggregationSourcesCount),
		.aggregationSourcesCount = Datatype->aggregationSourcesCount,
		.columns = ConvertPlayfabArrayToUnreal<PFStatisticsStatisticColumn, FPFStatisticsStatisticColumn>(Datatype->columns, Datatype->columnsCount, ConvertStatisticColumnToUnreal),
		.columnsCount = Datatype->columnsCount,
		.created = FDateTime::FromUnixTimestamp((int64)Datatype->created),
		.entityType = Datatype->entityType == nullptr ? FString() : FString(Datatype->entityType),
		.eventEmissionConfig = ConvertStatisticsEventEmissionConfigToUnreal(Datatype->eventEmissionConfig),
		.lastResetTime = ConvertTimeToUnreal(Datatype->lastResetTime),
		.linkedLeaderboardNames = ConvertCharArrayToUnreal(Datatype->linkedLeaderboardNames, Datatype->linkedLeaderboardNamesCount),
		.linkedLeaderboardNamesCount = Datatype->linkedLeaderboardNamesCount,
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name),
		.version = Datatype->version,
		.versionConfiguration = ConvertVersionConfigurationToUnreal(Datatype->versionConfiguration)
	});

	return ConvertedType;
}

const PFStatisticsStatisticDefinition* ConvertStatisticDefinitionToPlayfab(TSharedPtr<const FPFStatisticsStatisticDefinition> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFStatisticsStatisticDefinition* ConvertedType = new PFStatisticsStatisticDefinition{
		.aggregationDestinations = ConvertFStringArrayToPlayfab(Datatype->aggregationDestinations),
		.aggregationDestinationsCount = (uint32_t)Datatype->aggregationDestinations.Num(),
		.aggregationSources = ConvertFStringArrayToPlayfab(Datatype->aggregationSources),
		.aggregationSourcesCount = (uint32_t)Datatype->aggregationSources.Num(),
		.columns = ConvertUnrealArrayToPlayfab<PFStatisticsStatisticColumn, FPFStatisticsStatisticColumn>(Datatype->columns, ConvertStatisticColumnToPlayfab),
		.columnsCount = (uint32_t)Datatype->columns.Num(),
		.created = Datatype->created.ToUnixTimestamp(),
		.entityType = ConvertFStringToCharPtr(Datatype->entityType),
		.eventEmissionConfig = ConvertStatisticsEventEmissionConfigToPlayfab(Datatype->eventEmissionConfig),
		.lastResetTime = ConvertFDateTimeToPlayfab(Datatype->lastResetTime),
		.linkedLeaderboardNames = ConvertFStringArrayToPlayfab(Datatype->linkedLeaderboardNames),
		.linkedLeaderboardNamesCount = (uint32_t)Datatype->linkedLeaderboardNames.Num(),
		.name = ConvertFStringToCharPtr(Datatype->name),
		.version = Datatype->version,
		.versionConfiguration = ConvertVersionConfigurationToPlayfab(Datatype->versionConfiguration)
	};

	return ConvertedType;
}

TSharedPtr<const FPFStatisticsListStatisticDefinitionsResponse> ConvertListStatisticDefinitionsResponseToUnreal(const PFStatisticsListStatisticDefinitionsResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFStatisticsListStatisticDefinitionsResponse> ConvertedType = MakeShared<FPFStatisticsListStatisticDefinitionsResponse>(FPFStatisticsListStatisticDefinitionsResponse{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.statisticDefinitions = ConvertPlayfabArrayToUnreal<PFStatisticsStatisticDefinition, FPFStatisticsStatisticDefinition>(Datatype->statisticDefinitions, Datatype->statisticDefinitionsCount, ConvertStatisticDefinitionToUnreal),
		.statisticDefinitionsCount = Datatype->statisticDefinitionsCount
	});

	return ConvertedType;
}

const PFStatisticsListStatisticDefinitionsResponse* ConvertListStatisticDefinitionsResponseToPlayfab(TSharedPtr<const FPFStatisticsListStatisticDefinitionsResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFStatisticsListStatisticDefinitionsResponse* ConvertedType = new PFStatisticsListStatisticDefinitionsResponse{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.statisticDefinitions = ConvertUnrealArrayToPlayfab<PFStatisticsStatisticDefinition, FPFStatisticsStatisticDefinition>(Datatype->statisticDefinitions, ConvertStatisticDefinitionToPlayfab),
		.statisticDefinitionsCount = (uint32_t)Datatype->statisticDefinitions.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFStatisticsUnlinkAggregationSourceFromStatisticRequest> ConvertUnlinkAggregationSourceFromStatisticRequestToUnreal(const PFStatisticsUnlinkAggregationSourceFromStatisticRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFStatisticsUnlinkAggregationSourceFromStatisticRequest> ConvertedType = MakeShared<FPFStatisticsUnlinkAggregationSourceFromStatisticRequest>(FPFStatisticsUnlinkAggregationSourceFromStatisticRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name),
		.sourceStatisticName = Datatype->sourceStatisticName == nullptr ? FString() : FString(Datatype->sourceStatisticName)
	});

	return ConvertedType;
}

const PFStatisticsUnlinkAggregationSourceFromStatisticRequest* ConvertUnlinkAggregationSourceFromStatisticRequestToPlayfab(TSharedPtr<const FPFStatisticsUnlinkAggregationSourceFromStatisticRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFStatisticsUnlinkAggregationSourceFromStatisticRequest* ConvertedType = new PFStatisticsUnlinkAggregationSourceFromStatisticRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.name = ConvertFStringToCharPtr(Datatype->name),
		.sourceStatisticName = ConvertFStringToCharPtr(Datatype->sourceStatisticName)
	};

	return ConvertedType;
}

TSharedPtr<const FPFStatisticsUpdateStatisticDefinitionRequest> ConvertUpdateStatisticDefinitionRequestToUnreal(const PFStatisticsUpdateStatisticDefinitionRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFStatisticsUpdateStatisticDefinitionRequest> ConvertedType = MakeShared<FPFStatisticsUpdateStatisticDefinitionRequest>(FPFStatisticsUpdateStatisticDefinitionRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.eventEmissionConfig = ConvertStatisticsEventEmissionConfigToUnreal(Datatype->eventEmissionConfig),
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name),
		.versionConfiguration = ConvertVersionConfigurationToUnreal(Datatype->versionConfiguration)
	});

	return ConvertedType;
}

const PFStatisticsUpdateStatisticDefinitionRequest* ConvertUpdateStatisticDefinitionRequestToPlayfab(TSharedPtr<const FPFStatisticsUpdateStatisticDefinitionRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFStatisticsUpdateStatisticDefinitionRequest* ConvertedType = new PFStatisticsUpdateStatisticDefinitionRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.eventEmissionConfig = ConvertStatisticsEventEmissionConfigToPlayfab(Datatype->eventEmissionConfig),
		.name = ConvertFStringToCharPtr(Datatype->name),
		.versionConfiguration = ConvertVersionConfigurationToPlayfab(Datatype->versionConfiguration)
	};

	return ConvertedType;
}

TSharedPtr<const FPFStatisticsStatisticUpdate> ConvertStatisticUpdateToUnreal(const PFStatisticsStatisticUpdate* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFStatisticsStatisticUpdate> ConvertedType = MakeShared<FPFStatisticsStatisticUpdate>(FPFStatisticsStatisticUpdate{
		.metadata = Datatype->metadata == nullptr ? FString() : FString(Datatype->metadata),
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name),
		.scores = ConvertCharArrayToUnreal(Datatype->scores, Datatype->scoresCount),
		.scoresCount = Datatype->scoresCount,
		.version = TSharedPtr<const uint32>(Datatype->version)
	});

	return ConvertedType;
}

const PFStatisticsStatisticUpdate* ConvertStatisticUpdateToPlayfab(TSharedPtr<const FPFStatisticsStatisticUpdate> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFStatisticsStatisticUpdate* ConvertedType = new PFStatisticsStatisticUpdate{
		.metadata = ConvertFStringToCharPtr(Datatype->metadata),
		.name = ConvertFStringToCharPtr(Datatype->name),
		.scores = ConvertFStringArrayToPlayfab(Datatype->scores),
		.scoresCount = (uint32_t)Datatype->scores.Num(),
		.version = Datatype->version ? new uint32(*Datatype->version) : nullptr
	};

	return ConvertedType;
}

TSharedPtr<const FPFStatisticsUpdateStatisticsRequest> ConvertUpdateStatisticsRequestToUnreal(const PFStatisticsUpdateStatisticsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFStatisticsUpdateStatisticsRequest> ConvertedType = MakeShared<FPFStatisticsUpdateStatisticsRequest>(FPFStatisticsUpdateStatisticsRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.statistics = ConvertPlayfabArrayToUnreal<PFStatisticsStatisticUpdate, FPFStatisticsStatisticUpdate>(Datatype->statistics, Datatype->statisticsCount, ConvertStatisticUpdateToUnreal),
		.statisticsCount = Datatype->statisticsCount,
		.transactionId = Datatype->transactionId == nullptr ? FString() : FString(Datatype->transactionId)
	});

	return ConvertedType;
}

const PFStatisticsUpdateStatisticsRequest* ConvertUpdateStatisticsRequestToPlayfab(TSharedPtr<const FPFStatisticsUpdateStatisticsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFStatisticsUpdateStatisticsRequest* ConvertedType = new PFStatisticsUpdateStatisticsRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.statistics = ConvertUnrealArrayToPlayfab<PFStatisticsStatisticUpdate, FPFStatisticsStatisticUpdate>(Datatype->statistics, ConvertStatisticUpdateToPlayfab),
		.statisticsCount = (uint32_t)Datatype->statistics.Num(),
		.transactionId = ConvertFStringToCharPtr(Datatype->transactionId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFStatisticsUpdateStatisticsResponse> ConvertUpdateStatisticsResponseToUnreal(const PFStatisticsUpdateStatisticsResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFStatisticsUpdateStatisticsResponse> ConvertedType = MakeShared<FPFStatisticsUpdateStatisticsResponse>(FPFStatisticsUpdateStatisticsResponse{
		.columnDetails = ConvertPlayfabMapToUnreal<PFStatisticsStatisticColumnCollectionDictionaryEntry, FPFStatisticsStatisticColumnCollection, PFStatisticsStatisticColumnCollection>(Datatype->columnDetails, Datatype->columnDetailsCount, ConvertStatisticColumnCollectionToUnreal),
		.columnDetailsCount = Datatype->columnDetailsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.statistics = ConvertPlayfabMapToUnreal<PFStatisticsEntityStatisticValueDictionaryEntry, FPFStatisticsEntityStatisticValue, PFStatisticsEntityStatisticValue>(Datatype->statistics, Datatype->statisticsCount, ConvertEntityStatisticValueToUnreal),
		.statisticsCount = Datatype->statisticsCount
	});

	return ConvertedType;
}

const PFStatisticsUpdateStatisticsResponse* ConvertUpdateStatisticsResponseToPlayfab(TSharedPtr<const FPFStatisticsUpdateStatisticsResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFStatisticsUpdateStatisticsResponse* ConvertedType = new PFStatisticsUpdateStatisticsResponse{
		.columnDetails = ConvertUnrealMapToPlayfab<PFStatisticsStatisticColumnCollectionDictionaryEntry, FPFStatisticsStatisticColumnCollection, PFStatisticsStatisticColumnCollection>(Datatype->columnDetails, ConvertStatisticColumnCollectionToPlayfab),
		.columnDetailsCount = (uint32_t)Datatype->columnDetails.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.statistics = ConvertUnrealMapToPlayfab<PFStatisticsEntityStatisticValueDictionaryEntry, FPFStatisticsEntityStatisticValue, PFStatisticsEntityStatisticValue>(Datatype->statistics, ConvertEntityStatisticValueToPlayfab),
		.statisticsCount = (uint32_t)Datatype->statistics.Num()
	};

	return ConvertedType;
}
