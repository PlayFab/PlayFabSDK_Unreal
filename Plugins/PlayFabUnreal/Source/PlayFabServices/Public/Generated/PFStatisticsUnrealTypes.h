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
/// StatisticAggregationMethod enum.
/// </summary>
enum class FPFStatisticsStatisticAggregationMethod : uint32
{
	Last,
	Min,
	Max,
	Sum
};

/// <summary>
/// FPFStatisticsStatisticColumn data model.
/// </summary>
struct PLAYFABSERVICES_API FPFStatisticsStatisticColumn
{
	/// <summary>
	/// Aggregation method for calculating new value of a statistic.
	/// </summary>
	FPFStatisticsStatisticAggregationMethod aggregationMethod;

	/// <summary>
	/// Name of the statistic column, as originally configured.
	/// </summary>
	const FString name;
};

/// <summary>
/// FPFStatisticsStatisticsUpdateEventConfig data model.
/// </summary>
struct PLAYFABSERVICES_API FPFStatisticsStatisticsUpdateEventConfig
{
	/// <summary>
	/// The event type to emit when statistics are updated.
	/// </summary>
	FPFEventType eventType;
};

/// <summary>
/// FPFStatisticsStatisticsEventEmissionConfig data model.
/// </summary>
struct PLAYFABSERVICES_API FPFStatisticsStatisticsEventEmissionConfig
{
	/// <summary>
	/// (Optional) Emitted when statistics are updated.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFStatisticsStatisticsUpdateEventConfig> updateEventConfig;
};

/// <summary>
/// FPFStatisticsCreateStatisticDefinitionRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFStatisticsCreateStatisticDefinitionRequest
{
	/// <summary>
	/// (Optional) [In Preview]: The list of statistic definition names whose scores must be aggregated
	/// towards this stat. If AggregationSource is specified, the entityType of this definition MUST be Title
	/// (making it a CommunityStat). Currently, only one aggregation source can be specified.
	/// </summary>
	_Maybenull_ const TArray<FString> aggregationSources;

	/// <summary>
	/// Count of aggregationSources
	/// </summary>
	uint32 aggregationSourcesCount;

	/// <summary>
	/// (Optional) The columns for the statistic defining the aggregation method for each column. A maximum
	/// of 5 columns are allowed.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFStatisticsStatisticColumn>> columns;

	/// <summary>
	/// Count of columns
	/// </summary>
	uint32 columnsCount;

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
	/// (Optional) The entity type allowed to have score(s) for this statistic.
	/// </summary>
	_Maybenull_ const FString entityType;

	/// <summary>
	/// (Optional) [In Preview]: Configurations for different Statistics events that can be emitted by the
	/// service.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFStatisticsStatisticsEventEmissionConfig> eventEmissionConfig;

	/// <summary>
	/// Name of the statistic. Must be less than 150 characters. Restricted to a-Z, 0-9, '(', ')', '_',
	/// '-' and '.'.
	/// </summary>
	const FString name;

	/// <summary>
	/// (Optional) The version reset configuration for the statistic definition.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFVersionConfiguration> versionConfiguration;
};

/// <summary>
/// FPFStatisticsDeleteStatisticDefinitionRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFStatisticsDeleteStatisticDefinitionRequest
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
	/// Name of the statistic to delete.
	/// </summary>
	const FString name;
};

/// <summary>
/// FPFStatisticsStatisticDelete data model.
/// </summary>
struct PLAYFABSERVICES_API FPFStatisticsStatisticDelete
{
	/// <summary>
	/// Name of the statistic, as originally configured.
	/// </summary>
	const FString name;
};

/// <summary>
/// FPFStatisticsDeleteStatisticsRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFStatisticsDeleteStatisticsRequest
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
	/// Collection of statistics to remove from this entity.
	/// </summary>
	TArray<TSharedPtr<const FPFStatisticsStatisticDelete>> statistics;

	/// <summary>
	/// Count of statistics
	/// </summary>
	uint32 statisticsCount;
};

/// <summary>
/// FPFStatisticsDeleteStatisticsResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFStatisticsDeleteStatisticsResponse
{
	/// <summary>
	/// (Optional) The entity id and type.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFStatisticsGetStatisticDefinitionRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFStatisticsGetStatisticDefinitionRequest
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
	/// Name of the statistic. Must be less than 150 characters.
	/// </summary>
	const FString name;
};

/// <summary>
/// FPFStatisticsGetStatisticDefinitionResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFStatisticsGetStatisticDefinitionResponse
{
	/// <summary>
	/// (Optional) The list of statistic definitions names this definition aggregates to. .
	/// </summary>
	_Maybenull_ const TArray<FString> aggregationDestinations;

	/// <summary>
	/// Count of aggregationDestinations
	/// </summary>
	uint32 aggregationDestinationsCount;

	/// <summary>
	/// (Optional) The list of statistic definitions names whose values must be aggregated towards this
	/// stat. If AggregationSource is specified, the entityType of this definition MUST be Title (making
	/// it a CommunityStat). Currently, only one aggregation source can be specified.
	/// </summary>
	_Maybenull_ const TArray<FString> aggregationSources;

	/// <summary>
	/// Count of aggregationSources
	/// </summary>
	uint32 aggregationSourcesCount;

	/// <summary>
	/// (Optional) The columns for the statistic defining the aggregation method for each column.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFStatisticsStatisticColumn>> columns;

	/// <summary>
	/// Count of columns
	/// </summary>
	uint32 columnsCount;

	/// <summary>
	/// Created time, in UTC.
	/// </summary>
	FDateTime created;

	/// <summary>
	/// (Optional) The entity type that can have this statistic.
	/// </summary>
	_Maybenull_ const FString entityType;

	/// <summary>
	/// (Optional) [In Preview]: Configurations for different Statistics events that can be emitted by the
	/// service.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFStatisticsStatisticsEventEmissionConfig> eventEmissionConfig;

	/// <summary>
	/// (Optional) Last time, in UTC, statistic version was incremented.
	/// </summary>
	_Maybenull_ TSharedPtr<const FDateTime> lastResetTime;

	/// <summary>
	/// (Optional) The list of leaderboards that are linked to this statistic definition.
	/// </summary>
	_Maybenull_ const TArray<FString> linkedLeaderboardNames;

	/// <summary>
	/// Count of linkedLeaderboardNames
	/// </summary>
	uint32 linkedLeaderboardNamesCount;

	/// <summary>
	/// (Optional) Name of the statistic.
	/// </summary>
	_Maybenull_ const FString name;

	/// <summary>
	/// Statistic version.
	/// </summary>
	uint32 version;

	/// <summary>
	/// (Optional) The version reset configuration for the leaderboard definition.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFVersionConfiguration> versionConfiguration;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFStatisticsGetStatisticsRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFStatisticsGetStatisticsRequest
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
	/// (Optional) The list of statistics to return for the user. If set to null, the current version of
	/// all statistics are returned.
	/// </summary>
	_Maybenull_ const TArray<FString> statisticNames;

	/// <summary>
	/// Count of statisticNames
	/// </summary>
	uint32 statisticNamesCount;
};

/// <summary>
/// FPFStatisticsStatisticColumnCollection data model.
/// </summary>
struct PLAYFABSERVICES_API FPFStatisticsStatisticColumnCollection
{
	/// <summary>
	/// (Optional) Columns for the statistic defining the aggregation method for each column.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFStatisticsStatisticColumn>> columns;

	/// <summary>
	/// Count of columns
	/// </summary>
	uint32 columnsCount;
};

/// <summary>
/// FPFStatisticsEntityStatisticValue data model.
/// </summary>
struct PLAYFABSERVICES_API FPFStatisticsEntityStatisticValue
{
	/// <summary>
	/// (Optional) Metadata associated with the Statistic.
	/// </summary>
	_Maybenull_ const FString metadata;

	/// <summary>
	/// (Optional) Statistic name.
	/// </summary>
	_Maybenull_ const FString name;

	/// <summary>
	/// (Optional) Statistic scores.
	/// </summary>
	_Maybenull_ const TArray<FString> scores;

	/// <summary>
	/// Count of scores
	/// </summary>
	uint32 scoresCount;

	/// <summary>
	/// Statistic version.
	/// </summary>
	int32 version;
};

/// <summary>
/// FPFStatisticsGetStatisticsResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFStatisticsGetStatisticsResponse
{
	/// <summary>
	/// (Optional) A mapping of statistic name to the columns defined in the corresponding definition.
	/// </summary>
	_Maybenull_ TMap<const FString, TSharedPtr<const FPFStatisticsStatisticColumnCollection>> columnDetails;

	/// <summary>
	/// Count of columnDetails
	/// </summary>
	uint32 columnDetailsCount;

	/// <summary>
	/// (Optional) The entity id and type.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) List of statistics keyed by Name. Only the latest version of a statistic is returned.
	/// </summary>
	_Maybenull_ TMap<const FString, TSharedPtr<const FPFStatisticsEntityStatisticValue>> statistics;

	/// <summary>
	/// Count of statistics
	/// </summary>
	uint32 statisticsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFStatisticsGetStatisticsForEntitiesRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFStatisticsGetStatisticsForEntitiesRequest
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
	/// Collection of Entity IDs to retrieve statistics for.
	/// </summary>
	TArray<TSharedPtr<const FPFEntityKey>> entities;

	/// <summary>
	/// Count of entities
	/// </summary>
	uint32 entitiesCount;

	/// <summary>
	/// (Optional) The list of statistics to return for the user. If set to null, the current version of
	/// all statistics are returned.
	/// </summary>
	_Maybenull_ const TArray<FString> statisticNames;

	/// <summary>
	/// Count of statisticNames
	/// </summary>
	uint32 statisticNamesCount;
};

/// <summary>
/// FPFStatisticsEntityStatistics data model.
/// </summary>
struct PLAYFABSERVICES_API FPFStatisticsEntityStatistics
{
	/// <summary>
	/// (Optional) The entity for which the statistics are returned.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entityKey;

	/// <summary>
	/// (Optional) The statistics for the given entity key.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFStatisticsEntityStatisticValue>> statistics;

	/// <summary>
	/// Count of statistics
	/// </summary>
	uint32 statisticsCount;
};

/// <summary>
/// FPFStatisticsGetStatisticsForEntitiesResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFStatisticsGetStatisticsForEntitiesResponse
{
	/// <summary>
	/// (Optional) A mapping of statistic name to the columns defined in the corresponding definition.
	/// </summary>
	_Maybenull_ TMap<const FString, TSharedPtr<const FPFStatisticsStatisticColumnCollection>> columnDetails;

	/// <summary>
	/// Count of columnDetails
	/// </summary>
	uint32 columnDetailsCount;

	/// <summary>
	/// (Optional) List of entities mapped to their statistics. Only the latest version of a statistic is
	/// returned.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFStatisticsEntityStatistics>> entitiesStatistics;

	/// <summary>
	/// Count of entitiesStatistics
	/// </summary>
	uint32 entitiesStatisticsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFStatisticsIncrementStatisticVersionRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFStatisticsIncrementStatisticVersionRequest
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
	/// Name of the statistic to increment the version of.
	/// </summary>
	const FString name;
};

/// <summary>
/// FPFStatisticsIncrementStatisticVersionResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFStatisticsIncrementStatisticVersionResponse
{
	/// <summary>
	/// New statistic version.
	/// </summary>
	uint32 version;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFStatisticsListStatisticDefinitionsRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFStatisticsListStatisticDefinitionsRequest
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
	/// (Optional) The page size for the request.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> pageSize;

	/// <summary>
	/// (Optional) The skip token for the paged request.
	/// </summary>
	_Maybenull_ const FString skipToken;
};

/// <summary>
/// FPFStatisticsStatisticDefinition data model.
/// </summary>
struct PLAYFABSERVICES_API FPFStatisticsStatisticDefinition
{
	/// <summary>
	/// (Optional) The list of statistic definitions names this definition aggregates to. .
	/// </summary>
	_Maybenull_ const TArray<FString> aggregationDestinations;

	/// <summary>
	/// Count of aggregationDestinations
	/// </summary>
	uint32 aggregationDestinationsCount;

	/// <summary>
	/// (Optional) The list of statistic definitions names whose values must be aggregated towards this
	/// stat. If AggregationSource is specified, the entityType of this definition MUST be Title (making
	/// it a CommunityStat). Currently, only one aggregation source can be specified.
	/// </summary>
	_Maybenull_ const TArray<FString> aggregationSources;

	/// <summary>
	/// Count of aggregationSources
	/// </summary>
	uint32 aggregationSourcesCount;

	/// <summary>
	/// (Optional) The columns for the statistic defining the aggregation method for each column.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFStatisticsStatisticColumn>> columns;

	/// <summary>
	/// Count of columns
	/// </summary>
	uint32 columnsCount;

	/// <summary>
	/// Created time, in UTC.
	/// </summary>
	FDateTime created;

	/// <summary>
	/// (Optional) The entity type that can have this statistic.
	/// </summary>
	_Maybenull_ const FString entityType;

	/// <summary>
	/// (Optional) [In Preview]: Configurations for different Statistics events that can be emitted by the
	/// service.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFStatisticsStatisticsEventEmissionConfig> eventEmissionConfig;

	/// <summary>
	/// (Optional) Last time, in UTC, statistic version was incremented.
	/// </summary>
	_Maybenull_ TSharedPtr<const FDateTime> lastResetTime;

	/// <summary>
	/// (Optional) The list of leaderboards that are linked to this statistic definition.
	/// </summary>
	_Maybenull_ const TArray<FString> linkedLeaderboardNames;

	/// <summary>
	/// Count of linkedLeaderboardNames
	/// </summary>
	uint32 linkedLeaderboardNamesCount;

	/// <summary>
	/// (Optional) Name of the statistic.
	/// </summary>
	_Maybenull_ const FString name;

	/// <summary>
	/// Statistic version.
	/// </summary>
	uint32 version;

	/// <summary>
	/// (Optional) The version reset configuration for the leaderboard definition.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFVersionConfiguration> versionConfiguration;
};

/// <summary>
/// FPFStatisticsListStatisticDefinitionsResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFStatisticsListStatisticDefinitionsResponse
{
	/// <summary>
	/// The page size on the response.
	/// </summary>
	int32 pageSize;

	/// <summary>
	/// (Optional) The skip token for the paged response.
	/// </summary>
	_Maybenull_ const FString skipToken;

	/// <summary>
	/// (Optional) List of statistic definitions for the title.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFStatisticsStatisticDefinition>> statisticDefinitions;

	/// <summary>
	/// Count of statisticDefinitions
	/// </summary>
	uint32 statisticDefinitionsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFStatisticsUnlinkAggregationSourceFromStatisticRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFStatisticsUnlinkAggregationSourceFromStatisticRequest
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
	/// The name of the statistic to unlink.
	/// </summary>
	const FString name;

	/// <summary>
	/// The name of the aggregation source statistic to unlink.
	/// </summary>
	const FString sourceStatisticName;
};

/// <summary>
/// FPFStatisticsUpdateStatisticDefinitionRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFStatisticsUpdateStatisticDefinitionRequest
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
	/// (Optional) [In Preview]: Configurations for different Statistics events that can be emitted by the
	/// service.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFStatisticsStatisticsEventEmissionConfig> eventEmissionConfig;

	/// <summary>
	/// Name of the statistic. Must be less than 150 characters. Restricted to a-Z, 0-9, '(', ')', '_',
	/// '-' and '.'.
	/// </summary>
	const FString name;

	/// <summary>
	/// (Optional) The version reset configuration for the statistic definition.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFVersionConfiguration> versionConfiguration;
};

/// <summary>
/// FPFStatisticsStatisticUpdate data model.
/// </summary>
struct PLAYFABSERVICES_API FPFStatisticsStatisticUpdate
{
	/// <summary>
	/// (Optional) Arbitrary metadata to store along side the statistic, will be returned by all Leaderboard
	/// APIs.
	/// </summary>
	_Maybenull_ const FString metadata;

	/// <summary>
	/// Name of the statistic, as originally configured.
	/// </summary>
	const FString name;

	/// <summary>
	/// (Optional) Statistic scores for the entity. This will be used in accordance with the aggregation
	/// method configured for the statistics.The maximum value allowed for each individual score is 9223372036854775807.
	/// The minimum value for each individual score is -9223372036854775807The values are formatted as strings
	/// to avoid interop issues with client libraries unable to handle 64bit integers.
	/// </summary>
	_Maybenull_ const TArray<FString> scores;

	/// <summary>
	/// Count of scores
	/// </summary>
	uint32 scoresCount;

	/// <summary>
	/// (Optional) Optional field to indicate the version of the statistic to set. When empty defaults to
	/// the statistic's current version.
	/// </summary>
	_Maybenull_ TSharedPtr<const uint32> version;
};

/// <summary>
/// FPFStatisticsUpdateStatisticsRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFStatisticsUpdateStatisticsRequest
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
	/// Collection of statistics to update, maximum 50.
	/// </summary>
	TArray<TSharedPtr<const FPFStatisticsStatisticUpdate>> statistics;

	/// <summary>
	/// Count of statistics
	/// </summary>
	uint32 statisticsCount;

	/// <summary>
	/// (Optional) Optional transactionId of this update which can be used to ensure idempotence.
	/// </summary>
	_Maybenull_ const FString transactionId;
};

/// <summary>
/// FPFStatisticsUpdateStatisticsResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFStatisticsUpdateStatisticsResponse
{
	/// <summary>
	/// (Optional) A mapping of statistic name to the columns defined in the corresponding definition.
	/// </summary>
	_Maybenull_ TMap<const FString, TSharedPtr<const FPFStatisticsStatisticColumnCollection>> columnDetails;

	/// <summary>
	/// Count of columnDetails
	/// </summary>
	uint32 columnDetailsCount;

	/// <summary>
	/// (Optional) The entity id and type.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) Updated entity profile statistics.
	/// </summary>
	_Maybenull_ TMap<const FString, TSharedPtr<const FPFStatisticsEntityStatisticValue>> statistics;

	/// <summary>
	/// Count of statistics
	/// </summary>
	uint32 statisticsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

// Delegates Declarations

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnCreateStatisticDefinitionCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnDeleteStatisticDefinitionCompleted, const FString&, bool);
#endif

DECLARE_DELEGATE_TwoParams(FOnDeleteStatisticsCompleted, const FPFStatisticsDeleteStatisticsResponse&, bool);

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnGetStatisticDefinitionCompleted, const FPFStatisticsGetStatisticDefinitionResponse&, bool);
#endif

DECLARE_DELEGATE_TwoParams(FOnGetStatisticsCompleted, const FPFStatisticsGetStatisticsResponse&, bool);

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnGetStatisticsForEntitiesCompleted, const FPFStatisticsGetStatisticsForEntitiesResponse&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnIncrementStatisticVersionCompleted, const FPFStatisticsIncrementStatisticVersionResponse&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnListStatisticDefinitionsCompleted, const FPFStatisticsListStatisticDefinitionsResponse&, bool);
#endif

#if 0
DECLARE_DELEGATE_TwoParams(FOnUnlinkAggregationSourceFromStatisticCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK
DECLARE_DELEGATE_TwoParams(FOnUpdateStatisticDefinitionCompleted, const FString&, bool);
#endif

DECLARE_DELEGATE_TwoParams(FOnUpdateStatisticsCompleted, const FPFStatisticsUpdateStatisticsResponse&, bool);

#pragma pop_macro("IN")