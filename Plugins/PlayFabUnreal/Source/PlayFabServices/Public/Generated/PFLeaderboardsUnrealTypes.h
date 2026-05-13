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
/// LeaderboardSortDirection enum.
/// </summary>
enum class FPFLeaderboardsLeaderboardSortDirection : uint32
{
	Descending,
	Ascending
};

/// <summary>
/// ExternalFriendSources enum.
/// </summary>
enum class FPFExternalFriendSources : uint32
{
	None = 0x0,
	Steam = 0x1,
	Facebook = 0x2,
	Xbox = 0x4,
	Psn = 0x8,
	All = 0x10
};

DEFINE_ENUM_FLAG_OPERATORS(FPFExternalFriendSources);

/// <summary>
/// FPFLeaderboardsLinkedStatisticColumn data model.
/// </summary>
struct PLAYFABSERVICES_API FPFLeaderboardsLinkedStatisticColumn
{
	/// <summary>
	/// The name of the statistic column that this leaderboard column is sourced from.
	/// </summary>
	const FString linkedStatisticColumnName;

	/// <summary>
	/// The name of the statistic.
	/// </summary>
	const FString linkedStatisticName;
};

/// <summary>
/// FPFLeaderboardsLeaderboardColumn data model.
/// </summary>
struct PLAYFABSERVICES_API FPFLeaderboardsLeaderboardColumn
{
	/// <summary>
	/// (Optional) If the value for this column is sourced from a statistic, details of the linked column.
	/// Null if the leaderboard is not linked.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFLeaderboardsLinkedStatisticColumn> linkedStatisticColumn;

	/// <summary>
	/// A name for the leaderboard column, unique per leaderboard definition.
	/// </summary>
	const FString name;

	/// <summary>
	/// The sort direction for this column.
	/// </summary>
	FPFLeaderboardsLeaderboardSortDirection sortDirection;
};

/// <summary>
/// FPFLeaderboardsLeaderboardEntityRankOnVersionEndConfig data model.
/// </summary>
struct PLAYFABSERVICES_API FPFLeaderboardsLeaderboardEntityRankOnVersionEndConfig
{
	/// <summary>
	/// The type of event to emit when the leaderboard version end.
	/// </summary>
	FPFEventType eventType;

	/// <summary>
	/// The maximum number of entity to return on leaderboard version end. Range is 1 to 1000.
	/// </summary>
	int32 rankLimit;
};

/// <summary>
/// FPFLeaderboardsLeaderboardVersionEndConfig data model.
/// </summary>
struct PLAYFABSERVICES_API FPFLeaderboardsLeaderboardVersionEndConfig
{
	/// <summary>
	/// The type of event to emit when the leaderboard version end.
	/// </summary>
	FPFEventType eventType;
};

/// <summary>
/// FPFLeaderboardsLeaderboardEventEmissionConfig data model.
/// </summary>
struct PLAYFABSERVICES_API FPFLeaderboardsLeaderboardEventEmissionConfig
{
	/// <summary>
	/// (Optional) This event emits the top ranks of the leaderboard when the leaderboard version end.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFLeaderboardsLeaderboardEntityRankOnVersionEndConfig> entityRankOnVersionEndConfig;

	/// <summary>
	/// (Optional) This event is emitted when the leaderboard version end.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFLeaderboardsLeaderboardVersionEndConfig> versionEndConfig;
};

/// <summary>
/// FPFLeaderboardsCreateLeaderboardDefinitionRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFLeaderboardsCreateLeaderboardDefinitionRequest
{
	/// <summary>
	/// Leaderboard columns describing the sort directions, cannot be changed after creation. A maximum
	/// of 5 columns are allowed.
	/// </summary>
	TArray<TSharedPtr<const FPFLeaderboardsLeaderboardColumn>> columns;

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
	/// The entity type being represented on the leaderboard. If it doesn't correspond to the PlayFab entity
	/// types, use 'external' as the type.
	/// </summary>
	const FString entityType;

	/// <summary>
	/// (Optional) [In Preview]: The configuration for the events emitted by this leaderboard. If not specified,
	/// no events will be emitted.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFLeaderboardsLeaderboardEventEmissionConfig> eventEmissionConfig;

	/// <summary>
	/// A name for the leaderboard, unique per title.
	/// </summary>
	const FString name;

	/// <summary>
	/// Maximum number of entries on this leaderboard.
	/// </summary>
	int32 sizeLimit;

	/// <summary>
	/// (Optional) The version reset configuration for the leaderboard definition.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFVersionConfiguration> versionConfiguration;
};

/// <summary>
/// FPFLeaderboardsDeleteLeaderboardDefinitionRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFLeaderboardsDeleteLeaderboardDefinitionRequest
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
	/// The name of the leaderboard definition to delete.
	/// </summary>
	const FString name;
};

/// <summary>
/// FPFLeaderboardsDeleteLeaderboardEntriesRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFLeaderboardsDeleteLeaderboardEntriesRequest
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
	/// (Optional) The unique Ids of the entries to delete from the leaderboard.
	/// </summary>
	_Maybenull_ const TArray<FString> entityIds;

	/// <summary>
	/// Count of entityIds
	/// </summary>
	uint32 entityIdsCount;

	/// <summary>
	/// The name of the leaderboard.
	/// </summary>
	const FString name;
};

/// <summary>
/// FPFLeaderboardsGetFriendLeaderboardForEntityRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFLeaderboardsGetFriendLeaderboardForEntityRequest
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
	/// (Optional) Indicates which other platforms' friends should be included in the response. In HTTP,
	/// it is represented as a comma-separated list of platforms.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFExternalFriendSources> externalFriendSources;

	/// <summary>
	/// Name of the leaderboard.
	/// </summary>
	const FString leaderboardName;

	/// <summary>
	/// (Optional) Optional version of the leaderboard, defaults to current version.
	/// </summary>
	_Maybenull_ TSharedPtr<const uint32> version;

	/// <summary>
	/// (Optional) Xbox token if Xbox friends should be included. Requires Xbox be configured on PlayFab.
	/// </summary>
	_Maybenull_ const FString xboxToken;
};

/// <summary>
/// FPFLeaderboardsEntityLeaderboardEntry data model. Individual rank of an entity in a leaderboard.
/// </summary>
struct PLAYFABSERVICES_API FPFLeaderboardsEntityLeaderboardEntry
{
	/// <summary>
	/// (Optional) Entity's display name.
	/// </summary>
	_Maybenull_ const FString displayName;

	/// <summary>
	/// (Optional) Entity identifier.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// The time at which the last update to the entry was recorded on the server.
	/// </summary>
	FDateTime lastUpdated;

	/// <summary>
	/// (Optional) An opaque blob of data stored on the leaderboard entry. Note that the metadata is not
	/// used for ranking purposes.
	/// </summary>
	_Maybenull_ const FString metadata;

	/// <summary>
	/// Position on the leaderboard.
	/// </summary>
	int32 rank;

	/// <summary>
	/// (Optional) Scores for the entry.
	/// </summary>
	_Maybenull_ const TArray<FString> scores;

	/// <summary>
	/// Count of scores
	/// </summary>
	uint32 scoresCount;
};

/// <summary>
/// FPFLeaderboardsGetEntityLeaderboardResponse data model. Leaderboard response.
/// </summary>
struct PLAYFABSERVICES_API FPFLeaderboardsGetEntityLeaderboardResponse
{
	/// <summary>
	/// (Optional) Leaderboard columns describing the sort directions.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFLeaderboardsLeaderboardColumn>> columns;

	/// <summary>
	/// Count of columns
	/// </summary>
	uint32 columnsCount;

	/// <summary>
	/// The number of entries on the leaderboard.
	/// </summary>
	uint32 entryCount;

	/// <summary>
	/// (Optional) The time the next scheduled reset will occur. Null if the leaderboard does not reset
	/// on a schedule.
	/// </summary>
	_Maybenull_ TSharedPtr<const FDateTime> nextReset;

	/// <summary>
	/// (Optional) Individual entity rankings in the leaderboard, in sorted order by rank.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFLeaderboardsEntityLeaderboardEntry>> rankings;

	/// <summary>
	/// Count of rankings
	/// </summary>
	uint32 rankingsCount;

	/// <summary>
	/// Version of the leaderboard being returned.
	/// </summary>
	uint32 version;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFLeaderboardsGetEntityLeaderboardRequest data model. Request to load a leaderboard.
/// </summary>
struct PLAYFABSERVICES_API FPFLeaderboardsGetEntityLeaderboardRequest
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
	/// Name of the leaderboard.
	/// </summary>
	const FString leaderboardName;

	/// <summary>
	/// Maximum number of results to return from the leaderboard. Minimum 1, maximum 100.
	/// </summary>
	uint32 pageSize;

	/// <summary>
	/// (Optional) Index position to start from. 1 is beginning of leaderboard. .
	/// </summary>
	_Maybenull_ TSharedPtr<const uint32> startingPosition;

	/// <summary>
	/// (Optional) Optional version of the leaderboard, defaults to current version.
	/// </summary>
	_Maybenull_ TSharedPtr<const uint32> version;
};

/// <summary>
/// FPFLeaderboardsGetLeaderboardAroundEntityRequest data model. Request to load a section of a leaderboard
/// centered on a specific entity.
/// </summary>
struct PLAYFABSERVICES_API FPFLeaderboardsGetLeaderboardAroundEntityRequest
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
	/// Name of the leaderboard.
	/// </summary>
	const FString leaderboardName;

	/// <summary>
	/// Number of surrounding entries to return (in addition to specified entity). In general, the number
	/// of ranks above and below will be split into half. For example, if the specified value is 10, 5 ranks
	/// above and 5 ranks below will be retrieved. However, the numbers will get skewed in either direction
	/// when the specified entity is towards the top or bottom of the leaderboard. Also, the number of entries
	/// returned can be lower than the value specified for entries at the bottom of the leaderboard.
	/// </summary>
	uint32 maxSurroundingEntries;

	/// <summary>
	/// (Optional) Optional version of the leaderboard, defaults to current.
	/// </summary>
	_Maybenull_ TSharedPtr<const uint32> version;
};

/// <summary>
/// FPFLeaderboardsGetLeaderboardDefinitionRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFLeaderboardsGetLeaderboardDefinitionRequest
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
	/// The name of the leaderboard to retrieve the definition for.
	/// </summary>
	const FString name;
};

/// <summary>
/// FPFLeaderboardsGetLeaderboardDefinitionResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFLeaderboardsGetLeaderboardDefinitionResponse
{
	/// <summary>
	/// Sort direction of the leaderboard columns, cannot be changed after creation.
	/// </summary>
	TArray<TSharedPtr<const FPFLeaderboardsLeaderboardColumn>> columns;

	/// <summary>
	/// Count of columns
	/// </summary>
	uint32 columnsCount;

	/// <summary>
	/// Created time, in UTC.
	/// </summary>
	FDateTime created;

	/// <summary>
	/// The entity type being represented on the leaderboard. If it doesn't correspond to the PlayFab entity
	/// types, use 'external' as the type.
	/// </summary>
	const FString entityType;

	/// <summary>
	/// (Optional) [In Preview]: The configuration for the events emitted by this leaderboard. If not specified,
	/// no events will be emitted.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFLeaderboardsLeaderboardEventEmissionConfig> eventEmissionConfig;

	/// <summary>
	/// (Optional) Last time, in UTC, leaderboard version was incremented.
	/// </summary>
	_Maybenull_ TSharedPtr<const FDateTime> lastResetTime;

	/// <summary>
	/// A name for the leaderboard, unique per title.
	/// </summary>
	const FString name;

	/// <summary>
	/// Maximum number of entries on this leaderboard.
	/// </summary>
	int32 sizeLimit;

	/// <summary>
	/// Latest Leaderboard version.
	/// </summary>
	uint32 version;

	/// <summary>
	/// The version reset configuration for the leaderboard definition.
	/// </summary>
	TSharedPtr<const FPFVersionConfiguration> versionConfiguration;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFLeaderboardsGetLeaderboardForEntitiesRequest data model. Request a leaderboard limited to a collection
/// of entities.
/// </summary>
struct PLAYFABSERVICES_API FPFLeaderboardsGetLeaderboardForEntitiesRequest
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
	/// Collection of Entity IDs to include in the leaderboard.
	/// </summary>
	const TArray<FString> entityIds;

	/// <summary>
	/// Count of entityIds
	/// </summary>
	uint32 entityIdsCount;

	/// <summary>
	/// Name of the leaderboard.
	/// </summary>
	const FString leaderboardName;

	/// <summary>
	/// (Optional) Optional version of the leaderboard, defaults to current.
	/// </summary>
	_Maybenull_ TSharedPtr<const uint32> version;
};

/// <summary>
/// FPFLeaderboardsIncrementLeaderboardVersionRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFLeaderboardsIncrementLeaderboardVersionRequest
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
	/// The name of the leaderboard to increment the version for.
	/// </summary>
	const FString name;
};

/// <summary>
/// FPFLeaderboardsIncrementLeaderboardVersionResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFLeaderboardsIncrementLeaderboardVersionResponse
{
	/// <summary>
	/// New Leaderboard version.
	/// </summary>
	uint32 version;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFLeaderboardsListLeaderboardDefinitionsRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFLeaderboardsListLeaderboardDefinitionsRequest
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
/// FPFLeaderboardsLeaderboardDefinition data model.
/// </summary>
struct PLAYFABSERVICES_API FPFLeaderboardsLeaderboardDefinition
{
	/// <summary>
	/// Sort direction of the leaderboard columns, cannot be changed after creation.
	/// </summary>
	TArray<TSharedPtr<const FPFLeaderboardsLeaderboardColumn>> columns;

	/// <summary>
	/// Count of columns
	/// </summary>
	uint32 columnsCount;

	/// <summary>
	/// Created time, in UTC.
	/// </summary>
	FDateTime created;

	/// <summary>
	/// The entity type being represented on the leaderboard. If it doesn't correspond to the PlayFab entity
	/// types, use 'external' as the type.
	/// </summary>
	const FString entityType;

	/// <summary>
	/// (Optional) [In Preview]: The configuration for the events emitted by this leaderboard. If not specified,
	/// no events will be emitted.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFLeaderboardsLeaderboardEventEmissionConfig> eventEmissionConfig;

	/// <summary>
	/// (Optional) Last time, in UTC, leaderboard version was incremented.
	/// </summary>
	_Maybenull_ TSharedPtr<const FDateTime> lastResetTime;

	/// <summary>
	/// A name for the leaderboard, unique per title.
	/// </summary>
	const FString name;

	/// <summary>
	/// Maximum number of entries on this leaderboard.
	/// </summary>
	int32 sizeLimit;

	/// <summary>
	/// Latest Leaderboard version.
	/// </summary>
	uint32 version;

	/// <summary>
	/// The version reset configuration for the leaderboard definition.
	/// </summary>
	TSharedPtr<const FPFVersionConfiguration> versionConfiguration;
};

/// <summary>
/// FPFLeaderboardsListLeaderboardDefinitionsResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFLeaderboardsListLeaderboardDefinitionsResponse
{
	/// <summary>
	/// (Optional) List of leaderboard definitions for the title.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFLeaderboardsLeaderboardDefinition>> leaderboardDefinitions;

	/// <summary>
	/// Count of leaderboardDefinitions
	/// </summary>
	uint32 leaderboardDefinitionsCount;

	/// <summary>
	/// The page size on the response.
	/// </summary>
	int32 pageSize;

	/// <summary>
	/// (Optional) The skip token for the paged response.
	/// </summary>
	_Maybenull_ const FString skipToken;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFLeaderboardsUnlinkLeaderboardFromStatisticRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFLeaderboardsUnlinkLeaderboardFromStatisticRequest
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
	/// The name of the leaderboard definition to unlink.
	/// </summary>
	const FString name;

	/// <summary>
	/// The name of the statistic definition to unlink.
	/// </summary>
	const FString statisticName;
};

/// <summary>
/// FPFLeaderboardsUpdateLeaderboardDefinitionRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFLeaderboardsUpdateLeaderboardDefinitionRequest
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
	/// (Optional) [In Preview]: The configuration for the events emitted by this leaderboard. If not specified,
	/// no events will be emitted.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFLeaderboardsLeaderboardEventEmissionConfig> eventEmissionConfig;

	/// <summary>
	/// The name of the leaderboard to update the definition for.
	/// </summary>
	const FString name;

	/// <summary>
	/// (Optional) Maximum number of entries on this leaderboard.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> sizeLimit;

	/// <summary>
	/// (Optional) The version reset configuration for the leaderboard definition.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFVersionConfiguration> versionConfiguration;
};

/// <summary>
/// FPFLeaderboardsLeaderboardEntryUpdate data model.
/// </summary>
struct PLAYFABSERVICES_API FPFLeaderboardsLeaderboardEntryUpdate
{
	/// <summary>
	/// The unique Id for the entry. If using PlayFab Entities, this would be the entityId of the entity.
	/// </summary>
	const FString entityId;

	/// <summary>
	/// (Optional) Arbitrary metadata to store along side the leaderboard entry, will be returned by all
	/// Leaderboard APIs.
	/// </summary>
	_Maybenull_ const FString metadata;

	/// <summary>
	/// (Optional) The scores for the leaderboard. The number of values provided here must match the number
	/// of columns in the Leaderboard definition.
	/// </summary>
	_Maybenull_ const TArray<FString> scores;

	/// <summary>
	/// Count of scores
	/// </summary>
	uint32 scoresCount;
};

/// <summary>
/// FPFLeaderboardsUpdateLeaderboardEntriesRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFLeaderboardsUpdateLeaderboardEntriesRequest
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
	/// (Optional) The entries to add or update on the leaderboard.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFLeaderboardsLeaderboardEntryUpdate>> entries;

	/// <summary>
	/// Count of entries
	/// </summary>
	uint32 entriesCount;

	/// <summary>
	/// The name of the leaderboard.
	/// </summary>
	const FString leaderboardName;
};

// Delegates Declarations

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnCreateLeaderboardDefinitionCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnDeleteLeaderboardDefinitionCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnDeleteLeaderboardEntriesCompleted, const FString&, bool);
#endif

DECLARE_DELEGATE_TwoParams(FOnGetFriendLeaderboardForEntityCompleted, const FPFLeaderboardsGetEntityLeaderboardResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnGetLeaderboardCompleted, const FPFLeaderboardsGetEntityLeaderboardResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnGetLeaderboardAroundEntityCompleted, const FPFLeaderboardsGetEntityLeaderboardResponse&, bool);

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnGetLeaderboardDefinitionCompleted, const FPFLeaderboardsGetLeaderboardDefinitionResponse&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnGetLeaderboardForEntitiesCompleted, const FPFLeaderboardsGetEntityLeaderboardResponse&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnIncrementLeaderboardVersionCompleted, const FPFLeaderboardsIncrementLeaderboardVersionResponse&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnListLeaderboardDefinitionsCompleted, const FPFLeaderboardsListLeaderboardDefinitionsResponse&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnUnlinkLeaderboardFromStatisticCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK
DECLARE_DELEGATE_TwoParams(FOnUpdateLeaderboardDefinitionCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnUpdateLeaderboardEntriesCompleted, const FString&, bool);
#endif

#pragma pop_macro("IN")