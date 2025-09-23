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
/// AzureVmSize enum.
/// </summary>
enum class FPFMultiplayerServerAzureVmSize : uint32
{
	Standard_A1,
	Standard_A2,
	Standard_A3,
	Standard_A4,
	Standard_A1_v2,
	Standard_A2_v2,
	Standard_A4_v2,
	Standard_A8_v2,
	Standard_D1_v2,
	Standard_D2_v2,
	Standard_D3_v2,
	Standard_D4_v2,
	Standard_D5_v2,
	Standard_D2_v3,
	Standard_D4_v3,
	Standard_D8_v3,
	Standard_D16_v3,
	Standard_F1,
	Standard_F2,
	Standard_F4,
	Standard_F8,
	Standard_F16,
	Standard_F2s_v2,
	Standard_F4s_v2,
	Standard_F8s_v2,
	Standard_F16s_v2,
	Standard_D2as_v4,
	Standard_D4as_v4,
	Standard_D8as_v4,
	Standard_D16as_v4,
	Standard_D2a_v4,
	Standard_D4a_v4,
	Standard_D8a_v4,
	Standard_D16a_v4,
	Standard_D2ads_v5,
	Standard_D4ads_v5,
	Standard_D8ads_v5,
	Standard_D16ads_v5,
	Standard_D2ads_v6,
	Standard_D4ads_v6,
	Standard_D8ads_v6,
	Standard_D16ads_v6,
	Standard_E2a_v4,
	Standard_E4a_v4,
	Standard_E8a_v4,
	Standard_E16a_v4,
	Standard_E2as_v4,
	Standard_E4as_v4,
	Standard_E8as_v4,
	Standard_E16as_v4,
	Standard_D2s_v3,
	Standard_D4s_v3,
	Standard_D8s_v3,
	Standard_D16s_v3,
	Standard_DS1_v2,
	Standard_DS2_v2,
	Standard_DS3_v2,
	Standard_DS4_v2,
	Standard_DS5_v2,
	Standard_NC4as_T4_v3,
	Standard_D2d_v4,
	Standard_D4d_v4,
	Standard_D8d_v4,
	Standard_D16d_v4,
	Standard_D2ds_v4,
	Standard_D4ds_v4,
	Standard_D8ds_v4,
	Standard_D16ds_v4,
	Standard_HB120_16rs_v3,
	Standard_HB120_32rs_v3,
	Standard_HB120_64rs_v3,
	Standard_HB120_96rs_v3,
	Standard_HB120rs_v3,
	Standard_D2d_v5,
	Standard_D4d_v5,
	Standard_D8d_v5,
	Standard_D16d_v5,
	Standard_D32d_v5,
	Standard_D2ds_v5,
	Standard_D4ds_v5,
	Standard_D8ds_v5,
	Standard_D16ds_v5,
	Standard_D32ds_v5
};

/// <summary>
/// ProtocolType enum.
/// </summary>
enum class FPFMultiplayerServerProtocolType : uint32
{
	TCP,
	UDP
};

/// <summary>
/// FPFMultiplayerServerDeleteSecretRequest data model. Deletes a multiplayer server game secret.
/// </summary>
struct PLAYFABSERVICES_API FPFMultiplayerServerDeleteSecretRequest
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
	/// The name of the secret.
	/// </summary>
	const FString name;
};

/// <summary>
/// FPFMultiplayerServerListBuildAliasesRequest data model. Returns a list of summarized details of all
/// multiplayer server builds for a title.
/// </summary>
struct PLAYFABSERVICES_API FPFMultiplayerServerListBuildAliasesRequest
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
/// FPFMultiplayerServerBuildSelectionCriterion data model.
/// </summary>
struct PLAYFABSERVICES_API FPFMultiplayerServerBuildSelectionCriterion
{
	/// <summary>
	/// (Optional) Dictionary of build ids and their respective weights for distribution of allocation requests.
	/// </summary>
	_Maybenull_ TMap<const FString, uint32> buildWeightDistribution;

	/// <summary>
	/// Count of buildWeightDistribution
	/// </summary>
	uint32 buildWeightDistributionCount;
};

/// <summary>
/// FPFMultiplayerServerBuildAliasDetailsResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFMultiplayerServerBuildAliasDetailsResponse
{
	/// <summary>
	/// (Optional) The guid string alias Id of the alias to be created or updated.
	/// </summary>
	_Maybenull_ const FString aliasId;

	/// <summary>
	/// (Optional) The alias name.
	/// </summary>
	_Maybenull_ const FString aliasName;

	/// <summary>
	/// (Optional) Array of build selection criteria.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFMultiplayerServerBuildSelectionCriterion>> buildSelectionCriteria;

	/// <summary>
	/// Count of buildSelectionCriteria
	/// </summary>
	uint32 buildSelectionCriteriaCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFMultiplayerServerListBuildAliasesResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFMultiplayerServerListBuildAliasesResponse
{
	/// <summary>
	/// (Optional) The list of build aliases for the title.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFMultiplayerServerBuildAliasDetailsResponse>> buildAliases;

	/// <summary>
	/// Count of buildAliases
	/// </summary>
	uint32 buildAliasesCount;

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
/// FPFMultiplayerServerListBuildSummariesRequest data model. Returns a list of summarized details of
/// all multiplayer server builds for a title.
/// </summary>
struct PLAYFABSERVICES_API FPFMultiplayerServerListBuildSummariesRequest
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
/// FPFMultiplayerServerCurrentServerStats data model.
/// </summary>
struct PLAYFABSERVICES_API FPFMultiplayerServerCurrentServerStats
{
	/// <summary>
	/// The number of active multiplayer servers.
	/// </summary>
	int32 active;

	/// <summary>
	/// The number of multiplayer servers still downloading game resources (such as assets).
	/// </summary>
	int32 propping;

	/// <summary>
	/// The number of standingby multiplayer servers.
	/// </summary>
	int32 standingBy;

	/// <summary>
	/// The total number of multiplayer servers.
	/// </summary>
	int32 total;
};

/// <summary>
/// FPFMultiplayerServerDynamicStandbyThreshold data model.
/// </summary>
struct PLAYFABSERVICES_API FPFMultiplayerServerDynamicStandbyThreshold
{
	/// <summary>
	/// When the trigger threshold is reached, multiply by this value.
	/// </summary>
	double multiplier;

	/// <summary>
	/// The multiplier will be applied when the actual standby divided by target standby floor is less than
	/// this value.
	/// </summary>
	double triggerThresholdPercentage;
};

/// <summary>
/// FPFMultiplayerServerDynamicStandbySettings data model.
/// </summary>
struct PLAYFABSERVICES_API FPFMultiplayerServerDynamicStandbySettings
{
	/// <summary>
	/// (Optional) List of auto standing by trigger values and corresponding standing by multiplier. Defaults
	/// to 1.5X at 50%, 3X at 25%, and 4X at 5%.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFMultiplayerServerDynamicStandbyThreshold>> dynamicFloorMultiplierThresholds;

	/// <summary>
	/// Count of dynamicFloorMultiplierThresholds
	/// </summary>
	uint32 dynamicFloorMultiplierThresholdsCount;

	/// <summary>
	/// When true, dynamic standby will be enabled.
	/// </summary>
	bool isEnabled;

	/// <summary>
	/// (Optional) The time it takes to reduce target standing by to configured floor value after an increase.
	/// Defaults to 30 minutes.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> rampDownSeconds;
};

/// <summary>
/// FPFMultiplayerServerSchedule data model.
/// </summary>
struct PLAYFABSERVICES_API FPFMultiplayerServerSchedule
{
	/// <summary>
	/// (Optional) A short description about this schedule. For example, "Game launch on July 15th".
	/// </summary>
	_Maybenull_ const FString description;

	/// <summary>
	/// The date and time in UTC at which the schedule ends. If IsRecurringWeekly is true, this schedule
	/// will keep renewing for future weeks until disabled or removed.
	/// </summary>
	FDateTime endTime;

	/// <summary>
	/// Disables the schedule.
	/// </summary>
	bool isDisabled;

	/// <summary>
	/// If true, the StartTime and EndTime will get renewed every week.
	/// </summary>
	bool isRecurringWeekly;

	/// <summary>
	/// The date and time in UTC at which the schedule starts.
	/// </summary>
	FDateTime startTime;

	/// <summary>
	/// The standby target to maintain for the duration of the schedule.
	/// </summary>
	int32 targetStandby;
};

/// <summary>
/// FPFMultiplayerServerScheduledStandbySettings data model.
/// </summary>
struct PLAYFABSERVICES_API FPFMultiplayerServerScheduledStandbySettings
{
	/// <summary>
	/// When true, scheduled standby will be enabled.
	/// </summary>
	bool isEnabled;

	/// <summary>
	/// (Optional) A list of non-overlapping schedules.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFMultiplayerServerSchedule>> scheduleList;

	/// <summary>
	/// Count of scheduleList
	/// </summary>
	uint32 scheduleListCount;
};

/// <summary>
/// FPFMultiplayerServerBuildRegion data model.
/// </summary>
struct PLAYFABSERVICES_API FPFMultiplayerServerBuildRegion
{
	/// <summary>
	/// (Optional) The current multiplayer server stats for the region.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFMultiplayerServerCurrentServerStats> currentServerStats;

	/// <summary>
	/// (Optional) Optional settings to control dynamic adjustment of standby target.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFMultiplayerServerDynamicStandbySettings> dynamicStandbySettings;

	/// <summary>
	/// Whether the game assets provided for the build have been replicated to this region.
	/// </summary>
	bool isAssetReplicationComplete;

	/// <summary>
	/// The maximum number of multiplayer servers for the region.
	/// </summary>
	int32 maxServers;

	/// <summary>
	/// (Optional) Regional override for the number of multiplayer servers to host on a single VM of the
	/// build.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> multiplayerServerCountPerVm;

	/// <summary>
	/// (Optional) The build region.
	/// </summary>
	_Maybenull_ const FString region;

	/// <summary>
	/// (Optional) Optional settings to set the standby target to specified values during the supplied schedules.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFMultiplayerServerScheduledStandbySettings> scheduledStandbySettings;

	/// <summary>
	/// The target number of standby multiplayer servers for the region.
	/// </summary>
	int32 standbyServers;

	/// <summary>
	/// (Optional) The status of multiplayer servers in the build region. Valid values are - Unknown, Initialized,
	/// Deploying, Deployed, Unhealthy, Deleting, Deleted.
	/// </summary>
	_Maybenull_ const FString status;

	/// <summary>
	/// (Optional) Regional override for the VM size the build was created on.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFMultiplayerServerAzureVmSize> vmSize;
};

/// <summary>
/// FPFMultiplayerServerBuildSummary data model.
/// </summary>
struct PLAYFABSERVICES_API FPFMultiplayerServerBuildSummary
{
	/// <summary>
	/// (Optional) The guid string build ID of the build.
	/// </summary>
	_Maybenull_ const FString buildId;

	/// <summary>
	/// (Optional) The build name.
	/// </summary>
	_Maybenull_ const FString buildName;

	/// <summary>
	/// (Optional) The time the build was created in UTC.
	/// </summary>
	_Maybenull_ TSharedPtr<const FDateTime> creationTime;

	/// <summary>
	/// (Optional) The metadata of the build.
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> metadata;

	/// <summary>
	/// Count of metadata
	/// </summary>
	uint32 metadataCount;

	/// <summary>
	/// (Optional) The configuration and status for each region in the build.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFMultiplayerServerBuildRegion>> regionConfigurations;

	/// <summary>
	/// Count of regionConfigurations
	/// </summary>
	uint32 regionConfigurationsCount;
};

/// <summary>
/// FPFMultiplayerServerListBuildSummariesResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFMultiplayerServerListBuildSummariesResponse
{
	/// <summary>
	/// (Optional) The list of build summaries for a title.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFMultiplayerServerBuildSummary>> buildSummaries;

	/// <summary>
	/// Count of buildSummaries
	/// </summary>
	uint32 buildSummariesCount;

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
/// FPFMultiplayerServerListQosServersForTitleRequest data model. Returns a list of quality of service
/// servers for a title.
/// </summary>
struct PLAYFABSERVICES_API FPFMultiplayerServerListQosServersForTitleRequest
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
	/// (Optional) Indicates that the response should contain Qos servers for all regions, including those
	/// where there are no builds deployed for the title.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> includeAllRegions;

	/// <summary>
	/// (Optional) Indicates the Routing Preference used by the Qos servers. The default Routing Preference
	/// is Microsoft.
	/// </summary>
	_Maybenull_ const FString routingPreference;
};

/// <summary>
/// FPFMultiplayerServerQosServer data model.
/// </summary>
struct PLAYFABSERVICES_API FPFMultiplayerServerQosServer
{
	/// <summary>
	/// (Optional) The region the QoS server is located in.
	/// </summary>
	_Maybenull_ const FString region;

	/// <summary>
	/// (Optional) The QoS server URL.
	/// </summary>
	_Maybenull_ const FString serverUrl;
};

/// <summary>
/// FPFMultiplayerServerListQosServersForTitleResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFMultiplayerServerListQosServersForTitleResponse
{
	/// <summary>
	/// The page size on the response.
	/// </summary>
	int32 pageSize;

	/// <summary>
	/// (Optional) The list of QoS servers.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFMultiplayerServerQosServer>> qosServers;

	/// <summary>
	/// Count of qosServers
	/// </summary>
	uint32 qosServersCount;

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
/// FPFMultiplayerServerListSecretSummariesRequest data model. Returns a list of multiplayer server game
/// secrets for a title.
/// </summary>
struct PLAYFABSERVICES_API FPFMultiplayerServerListSecretSummariesRequest
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
/// FPFMultiplayerServerSecretSummary data model.
/// </summary>
struct PLAYFABSERVICES_API FPFMultiplayerServerSecretSummary
{
	/// <summary>
	/// (Optional) Optional secret expiration date.
	/// </summary>
	_Maybenull_ TSharedPtr<const FDateTime> expirationDate;

	/// <summary>
	/// (Optional) The name of the secret.
	/// </summary>
	_Maybenull_ const FString name;

	/// <summary>
	/// (Optional) The secret version auto-generated after upload.
	/// </summary>
	_Maybenull_ const FString version;
};

/// <summary>
/// FPFMultiplayerServerListSecretSummariesResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFMultiplayerServerListSecretSummariesResponse
{
	/// <summary>
	/// The page size on the response.
	/// </summary>
	int32 pageSize;

	/// <summary>
	/// (Optional) The list of game secret.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFMultiplayerServerSecretSummary>> secretSummaries;

	/// <summary>
	/// Count of secretSummaries
	/// </summary>
	uint32 secretSummariesCount;

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
/// FPFMultiplayerServerBuildAliasParams data model.
/// </summary>
struct PLAYFABSERVICES_API FPFMultiplayerServerBuildAliasParams
{
	/// <summary>
	/// The guid string alias ID to use for the request.
	/// </summary>
	const FString aliasId;
};

/// <summary>
/// FPFMultiplayerServerRequestMultiplayerServerRequest data model. Requests a multiplayer server session
/// from a particular build in any of the given preferred regions.
/// </summary>
struct PLAYFABSERVICES_API FPFMultiplayerServerRequestMultiplayerServerRequest
{
	/// <summary>
	/// (Optional) The identifiers of the build alias to use for the request.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFMultiplayerServerBuildAliasParams> buildAliasParams;

	/// <summary>
	/// (Optional) The guid string build ID of the multiplayer server to request.
	/// </summary>
	_Maybenull_ const FString buildId;

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
	/// (Optional) Initial list of players (potentially matchmade) allowed to connect to the game. This
	/// list is passed to the game server when requested (via GSDK) and can be used to validate players connecting
	/// to it.
	/// </summary>
	_Maybenull_ const TArray<FString> initialPlayers;

	/// <summary>
	/// Count of initialPlayers
	/// </summary>
	uint32 initialPlayersCount;

	/// <summary>
	/// The preferred regions to request a multiplayer server from. The Multiplayer Service will iterate
	/// through the regions in the specified order and allocate a server from the first one that has servers
	/// available.
	/// </summary>
	const TArray<FString> preferredRegions;

	/// <summary>
	/// Count of preferredRegions
	/// </summary>
	uint32 preferredRegionsCount;

	/// <summary>
	/// (Optional) Data encoded as a string that is passed to the game server when requested. This can be
	/// used to communicate information such as game mode or map through the request flow. Maximum size is
	/// 8KB.
	/// </summary>
	_Maybenull_ const FString sessionCookie;

	/// <summary>
	/// A guid string session ID created track the multiplayer server session over its life.
	/// </summary>
	const FString sessionId;
};

/// <summary>
/// FPFMultiplayerServerConnectedPlayer data model.
/// </summary>
struct PLAYFABSERVICES_API FPFMultiplayerServerConnectedPlayer
{
	/// <summary>
	/// (Optional) The player ID of the player connected to the multiplayer server.
	/// </summary>
	_Maybenull_ const FString playerId;
};

/// <summary>
/// FPFMultiplayerServerPort data model.
/// </summary>
struct PLAYFABSERVICES_API FPFMultiplayerServerPort
{
	/// <summary>
	/// The name for the port.
	/// </summary>
	const FString name;

	/// <summary>
	/// The number for the port.
	/// </summary>
	int32 num;

	/// <summary>
	/// The protocol for the port.
	/// </summary>
	FPFMultiplayerServerProtocolType protocol;
};

/// <summary>
/// FPFMultiplayerServerPublicIpAddress data model.
/// </summary>
struct PLAYFABSERVICES_API FPFMultiplayerServerPublicIpAddress
{
	/// <summary>
	/// FQDN of the public IP.
	/// </summary>
	const FString fQDN;

	/// <summary>
	/// Server IP Address.
	/// </summary>
	const FString ipAddress;

	/// <summary>
	/// Routing Type of the public IP.
	/// </summary>
	const FString routingType;
};

/// <summary>
/// FPFMultiplayerServerRequestMultiplayerServerResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFMultiplayerServerRequestMultiplayerServerResponse
{
	/// <summary>
	/// (Optional) The identity of the build in which the server was allocated.
	/// </summary>
	_Maybenull_ const FString buildId;

	/// <summary>
	/// (Optional) The connected players in the multiplayer server.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFMultiplayerServerConnectedPlayer>> connectedPlayers;

	/// <summary>
	/// Count of connectedPlayers
	/// </summary>
	uint32 connectedPlayersCount;

	/// <summary>
	/// (Optional) The fully qualified domain name of the virtual machine that is hosting this multiplayer
	/// server.
	/// </summary>
	_Maybenull_ const FString fQDN;

	/// <summary>
	/// (Optional) The public IPv4 address of the virtual machine that is hosting this multiplayer server.
	/// </summary>
	_Maybenull_ const FString iPV4Address;

	/// <summary>
	/// (Optional) The time (UTC) at which a change in the multiplayer server state was observed.
	/// </summary>
	_Maybenull_ TSharedPtr<const FDateTime> lastStateTransitionTime;

	/// <summary>
	/// (Optional) The ports the multiplayer server uses.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFMultiplayerServerPort>> ports;

	/// <summary>
	/// Count of ports
	/// </summary>
	uint32 portsCount;

	/// <summary>
	/// (Optional) The list of public Ipv4 addresses associated with the server.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFMultiplayerServerPublicIpAddress>> publicIPV4Addresses;

	/// <summary>
	/// Count of publicIPV4Addresses
	/// </summary>
	uint32 publicIPV4AddressesCount;

	/// <summary>
	/// (Optional) The region the multiplayer server is located in.
	/// </summary>
	_Maybenull_ const FString region;

	/// <summary>
	/// (Optional) The string server ID of the multiplayer server generated by PlayFab.
	/// </summary>
	_Maybenull_ const FString serverId;

	/// <summary>
	/// (Optional) The guid string session ID of the multiplayer server.
	/// </summary>
	_Maybenull_ const FString sessionId;

	/// <summary>
	/// (Optional) The state of the multiplayer server.
	/// </summary>
	_Maybenull_ const FString state;

	/// <summary>
	/// (Optional) The virtual machine ID that the multiplayer server is located on.
	/// </summary>
	_Maybenull_ const FString vmId;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFMultiplayerServerPartyInvitationConfiguration data model.
/// </summary>
struct PLAYFABSERVICES_API FPFMultiplayerServerPartyInvitationConfiguration
{
	/// <summary>
	/// (Optional) The list of PlayFab EntityKeys that the invitation allows to authenticate into the network.
	/// If this list is empty, all users are allowed to authenticate using the invitation's identifier. This
	/// list may contain no more than 1024 items.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFEntityKey>> entityKeys;

	/// <summary>
	/// Count of entityKeys
	/// </summary>
	uint32 entityKeysCount;

	/// <summary>
	/// (Optional) The invite identifier for this party. If this value is specified, it must be no longer
	/// than 127 characters.
	/// </summary>
	_Maybenull_ const FString identifier;

	/// <summary>
	/// (Optional) Controls which participants can revoke this invite.
	/// </summary>
	_Maybenull_ const FString revocability;
};

/// <summary>
/// FPFMultiplayerServerPartyNetworkConfiguration data model.
/// </summary>
struct PLAYFABSERVICES_API FPFMultiplayerServerPartyNetworkConfiguration
{
	/// <summary>
	/// (Optional) Controls whether and how to support direct peer-to-peer connection attempts among devices
	/// in the network.
	/// </summary>
	_Maybenull_ const FString directPeerConnectivityOptions;

	/// <summary>
	/// The maximum number of devices allowed to connect to the network. Must be between 1 and 128, inclusive.
	/// </summary>
	uint32 maxDevices;

	/// <summary>
	/// The maximum number of devices allowed per user. Must be greater than 0.
	/// </summary>
	uint32 maxDevicesPerUser;

	/// <summary>
	/// The maximum number of endpoints allowed per device. Must be between 0 and 32, inclusive.
	/// </summary>
	uint32 maxEndpointsPerDevice;

	/// <summary>
	/// The maximum number of unique users allowed in the network. Must be greater than 0.
	/// </summary>
	uint32 maxUsers;

	/// <summary>
	/// The maximum number of users allowed per device. Must be between 1 and 8, inclusive.
	/// </summary>
	uint32 maxUsersPerDevice;

	/// <summary>
	/// (Optional) An optionally-specified configuration for the initial invitation for this party. If not
	/// provided, default configuration values will be used: a title-unique invitation identifier will be
	/// generated, the revocability will be Anyone, and the EntityID list will be empty.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFMultiplayerServerPartyInvitationConfiguration> partyInvitationConfiguration;
};

/// <summary>
/// FPFMultiplayerServerRequestPartyServiceRequest data model. Requests a party session from a particular
/// set of builds if build alias params is provided, in any of the given preferred regions.
/// </summary>
struct PLAYFABSERVICES_API FPFMultiplayerServerRequestPartyServiceRequest
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
	/// The network configuration for this request.
	/// </summary>
	TSharedPtr<const FPFMultiplayerServerPartyNetworkConfiguration> networkConfiguration;

	/// <summary>
	/// (Optional) A guid string party ID created track the party session over its life.
	/// </summary>
	_Maybenull_ const FString partyId;

	/// <summary>
	/// The preferred regions to request a party session from. The party service will iterate through the
	/// regions in the specified order and allocate a party session from the first one that is available.
	/// </summary>
	const TArray<FString> preferredRegions;

	/// <summary>
	/// Count of preferredRegions
	/// </summary>
	uint32 preferredRegionsCount;
};

/// <summary>
/// FPFMultiplayerServerRequestPartyServiceResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFMultiplayerServerRequestPartyServiceResponse
{
	/// <summary>
	/// (Optional) The invitation identifier supplied in the PartyInvitationConfiguration, or the PlayFab-generated
	/// guid if none was supplied.
	/// </summary>
	_Maybenull_ const FString invitationId;

	/// <summary>
	/// (Optional) The guid string party ID of the party session.
	/// </summary>
	_Maybenull_ const FString partyId;

	/// <summary>
	/// (Optional) A base-64 encoded string containing the serialized network descriptor for this party.
	/// </summary>
	_Maybenull_ const FString serializedNetworkDescriptor;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFMultiplayerServerSecret data model.
/// </summary>
struct PLAYFABSERVICES_API FPFMultiplayerServerSecret
{
	/// <summary>
	/// (Optional) Optional secret expiration date.
	/// </summary>
	_Maybenull_ TSharedPtr<const FDateTime> expirationDate;

	/// <summary>
	/// A name for the secret. This is used to reference secrets in build configurations.
	/// </summary>
	const FString name;

	/// <summary>
	/// Secret value.
	/// </summary>
	const FString value;
};

/// <summary>
/// FPFMultiplayerServerUploadSecretRequest data model. Uploads a multiplayer server game secret.
/// </summary>
struct PLAYFABSERVICES_API FPFMultiplayerServerUploadSecretRequest
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
	/// (Optional) Forces the secret renewal if the secret already exists. Default is false.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> forceUpdate;

	/// <summary>
	/// The game secret to add.
	/// </summary>
	TSharedPtr<const FPFMultiplayerServerSecret> gameSecret;
};

// Delegates Declarations

#if 0
DECLARE_DELEGATE_TwoParams(FOnDeleteSecretCompleted, const FString&, bool);
#endif

DECLARE_DELEGATE_TwoParams(FOnListBuildAliasesCompleted, const FPFMultiplayerServerListBuildAliasesResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnListBuildSummariesV2Completed, const FPFMultiplayerServerListBuildSummariesResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnListQosServersForTitleCompleted, const FPFMultiplayerServerListQosServersForTitleResponse&, bool);

#if 0
DECLARE_DELEGATE_TwoParams(FOnListSecretSummariesCompleted, const FPFMultiplayerServerListSecretSummariesResponse&, bool);
#endif

DECLARE_DELEGATE_TwoParams(FOnRequestMultiplayerServerCompleted, const FPFMultiplayerServerRequestMultiplayerServerResponse&, bool);

#if 0
DECLARE_DELEGATE_TwoParams(FOnRequestPartyServiceCompleted, const FPFMultiplayerServerRequestPartyServiceResponse&, bool);
#endif

#if 0
DECLARE_DELEGATE_TwoParams(FOnUploadSecretCompleted, const FString&, bool);
#endif

#pragma pop_macro("IN")