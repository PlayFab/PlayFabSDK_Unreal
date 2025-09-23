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
/// ChurnRiskLevel enum.
/// </summary>
enum class FPFSegmentsChurnRiskLevel : uint32
{
	NoData,
	LowRisk,
	MediumRisk,
	HighRisk
};

/// <summary>
/// FPFSegmentsGetSegmentResult data model.
/// </summary>
struct PLAYFABSERVICES_API FPFSegmentsGetSegmentResult
{
	/// <summary>
	/// (Optional) Identifier of the segments AB Test, if it is attached to one.
	/// </summary>
	_Maybenull_ const FString aBTestParent;

	/// <summary>
	/// Unique identifier for this segment.
	/// </summary>
	const FString id;

	/// <summary>
	/// (Optional) Segment name.
	/// </summary>
	_Maybenull_ const FString name;
};

/// <summary>
/// FPFSegmentsGetPlayerSegmentsResult data model.
/// </summary>
struct PLAYFABSERVICES_API FPFSegmentsGetPlayerSegmentsResult
{
	/// <summary>
	/// (Optional) Array of segments the requested player currently belongs to.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFSegmentsGetSegmentResult>> segments;

	/// <summary>
	/// Count of segments
	/// </summary>
	uint32 segmentsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFSegmentsGetPlayerTagsRequest data model. This API will return a list of canonical tags which includes
/// both namespace and tag's name. If namespace is not provided, the result is a list of all canonical
/// tags. TagName can be used for segmentation and Namespace is limited to 128 characters.
/// </summary>
struct PLAYFABSERVICES_API FPFSegmentsGetPlayerTagsRequest
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
	/// (Optional) Optional namespace to filter results by.
	/// </summary>
	_Maybenull_ const FString playfabNamespace;

	/// <summary>
	/// Unique PlayFab assigned ID of the user on whom the operation will be performed.
	/// </summary>
	const FString playFabId;
};

/// <summary>
/// FPFSegmentsGetPlayerTagsResult data model.
/// </summary>
struct PLAYFABSERVICES_API FPFSegmentsGetPlayerTagsResult
{
	/// <summary>
	/// Unique PlayFab assigned ID of the user on whom the operation will be performed.
	/// </summary>
	const FString playFabId;

	/// <summary>
	/// Canonical tags (including namespace and tag's name) for the requested user.
	/// </summary>
	const TArray<FString> tags;

	/// <summary>
	/// Count of tags
	/// </summary>
	uint32 tagsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFSegmentsAddPlayerTagRequest data model. This API will trigger a player_tag_added event and add
/// a tag with the given TagName and PlayFabID to the corresponding player profile. TagName can be used
/// for segmentation and it is limited to 256 characters. Also there is a limit on the number of tags
/// a title can have.
/// </summary>
struct PLAYFABSERVICES_API FPFSegmentsAddPlayerTagRequest
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
	/// Unique PlayFab assigned ID of the user on whom the operation will be performed.
	/// </summary>
	const FString playFabId;

	/// <summary>
	/// Unique tag for player profile.
	/// </summary>
	const FString tagName;
};

/// <summary>
/// FPFSegmentsGetAllSegmentsResult data model.
/// </summary>
struct PLAYFABSERVICES_API FPFSegmentsGetAllSegmentsResult
{
	/// <summary>
	/// (Optional) Array of segments for this title.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFSegmentsGetSegmentResult>> segments;

	/// <summary>
	/// Count of segments
	/// </summary>
	uint32 segmentsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFSegmentsGetPlayersSegmentsRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFSegmentsGetPlayersSegmentsRequest
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
	/// Unique PlayFab assigned ID of the user on whom the operation will be performed.
	/// </summary>
	const FString playFabId;
};

/// <summary>
/// FPFSegmentsGetPlayersInSegmentRequest data model. Initial request must contain at least a Segment
/// ID. Subsequent requests must contain the Segment ID as well as the Continuation Token. Failure to
/// send the Continuation Token will result in a new player segment list being generated. Each time the
/// Continuation Token is passed in the length of the Total Seconds to Live is refreshed. If too much
/// time passes between requests to the point that a subsequent request is past the Total Seconds to Live
/// an error will be returned and paging will be terminated. This API is resource intensive and should
/// not be used in scenarios which might generate high request volumes. Only one request to this API at
/// a time should be made per title. Concurrent requests to the API may be rejected with the APIConcurrentRequestLimitExceeded
/// error.
/// </summary>
struct PLAYFABSERVICES_API FPFSegmentsGetPlayersInSegmentRequest
{
	/// <summary>
	/// (Optional) Continuation token if retrieving subsequent pages of results.
	/// </summary>
	_Maybenull_ const FString continuationToken;

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
	/// (Optional) If set to true, the profiles are loaded asynchronously and the response will include
	/// a continuation token and approximate profile count until the first batch of profiles is loaded. Use
	/// this parameter to help avoid network timeouts.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> getProfilesAsync;

	/// <summary>
	/// (Optional) Maximum is 10,000. The value 0 will prevent loading any profiles and return only the
	/// count of profiles matching this segment.
	/// </summary>
	_Maybenull_ TSharedPtr<const uint32> maxBatchSize;

	/// <summary>
	/// (Optional) Number of seconds to keep the continuation token active. After token expiration it is
	/// not possible to continue paging results. Default is 300 (5 minutes). Maximum is 5,400 (90 minutes).
	/// </summary>
	_Maybenull_ TSharedPtr<const uint32> secondsToLive;

	/// <summary>
	/// Unique identifier for this segment.
	/// </summary>
	const FString segmentId;
};

/// <summary>
/// FPFSegmentsAdCampaignAttribution data model.
/// </summary>
struct PLAYFABSERVICES_API FPFSegmentsAdCampaignAttribution
{
	/// <summary>
	/// UTC time stamp of attribution.
	/// </summary>
	FDateTime attributedAt;

	/// <summary>
	/// (Optional) Attribution campaign identifier.
	/// </summary>
	_Maybenull_ const FString campaignId;

	/// <summary>
	/// (Optional) Attribution network name.
	/// </summary>
	_Maybenull_ const FString platform;
};

/// <summary>
/// FPFSegmentsContactEmailInfo data model.
/// </summary>
struct PLAYFABSERVICES_API FPFSegmentsContactEmailInfo
{
	/// <summary>
	/// (Optional) The email address.
	/// </summary>
	_Maybenull_ const FString emailAddress;

	/// <summary>
	/// (Optional) The name of the email info data.
	/// </summary>
	_Maybenull_ const FString name;

	/// <summary>
	/// (Optional) The verification status of the email.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEmailVerificationStatus> verificationStatus;
};

/// <summary>
/// FPFSegmentsPlayerLinkedAccount data model.
/// </summary>
struct PLAYFABSERVICES_API FPFSegmentsPlayerLinkedAccount
{
	/// <summary>
	/// (Optional) Linked account's email.
	/// </summary>
	_Maybenull_ const FString email;

	/// <summary>
	/// (Optional) Authentication platform.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFLoginIdentityProvider> platform;

	/// <summary>
	/// (Optional) Platform user identifier.
	/// </summary>
	_Maybenull_ const FString platformUserId;

	/// <summary>
	/// (Optional) Linked account's username.
	/// </summary>
	_Maybenull_ const FString username;
};

/// <summary>
/// FPFSegmentsPlayerLocation data model.
/// </summary>
struct PLAYFABSERVICES_API FPFSegmentsPlayerLocation
{
	/// <summary>
	/// (Optional) City of the player's geographic location.
	/// </summary>
	_Maybenull_ const FString city;

	/// <summary>
	/// The two-character continent code for this location.
	/// </summary>
	FPFContinentCode continentCode;

	/// <summary>
	/// The two-character ISO 3166-1 country code for the country associated with the location.
	/// </summary>
	FPFCountryCode countryCode;

	/// <summary>
	/// (Optional) Latitude coordinate of the player's geographic location.
	/// </summary>
	_Maybenull_ TSharedPtr<const double> latitude;

	/// <summary>
	/// (Optional) Longitude coordinate of the player's geographic location.
	/// </summary>
	_Maybenull_ TSharedPtr<const double> longitude;
};

/// <summary>
/// FPFSegmentsPlayerStatistic data model.
/// </summary>
struct PLAYFABSERVICES_API FPFSegmentsPlayerStatistic
{
	/// <summary>
	/// (Optional) Statistic ID.
	/// </summary>
	_Maybenull_ const FString id;

	/// <summary>
	/// (Optional) Statistic name.
	/// </summary>
	_Maybenull_ const FString name;

	/// <summary>
	/// Current statistic value.
	/// </summary>
	int32 statisticValue;

	/// <summary>
	/// Statistic version (0 if not a versioned statistic).
	/// </summary>
	int32 statisticVersion;
};

/// <summary>
/// FPFSegmentsPushNotificationRegistration data model.
/// </summary>
struct PLAYFABSERVICES_API FPFSegmentsPushNotificationRegistration
{
	/// <summary>
	/// (Optional) Notification configured endpoint.
	/// </summary>
	_Maybenull_ const FString notificationEndpointARN;

	/// <summary>
	/// (Optional) Push notification platform.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFPushNotificationPlatform> platform;
};

/// <summary>
/// FPFSegmentsPlayerProfile data model.
/// </summary>
struct PLAYFABSERVICES_API FPFSegmentsPlayerProfile
{
	/// <summary>
	/// (Optional) Array of ad campaigns player has been attributed to.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFSegmentsAdCampaignAttribution>> adCampaignAttributions;

	/// <summary>
	/// Count of adCampaignAttributions
	/// </summary>
	uint32 adCampaignAttributionsCount;

	/// <summary>
	/// (Optional) Image URL of the player's avatar.
	/// </summary>
	_Maybenull_ const FString avatarUrl;

	/// <summary>
	/// (Optional) Banned until UTC Date. If permanent ban this is set for 20 years after the original ban
	/// date.
	/// </summary>
	_Maybenull_ TSharedPtr<const FDateTime> bannedUntil;

	/// <summary>
	/// (Optional) The prediction of the player to churn within the next seven days.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFSegmentsChurnRiskLevel> churnPrediction;

	/// <summary>
	/// (Optional) Array of contact email addresses associated with the player.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFSegmentsContactEmailInfo>> contactEmailAddresses;

	/// <summary>
	/// Count of contactEmailAddresses
	/// </summary>
	uint32 contactEmailAddressesCount;

	/// <summary>
	/// (Optional) Player record created.
	/// </summary>
	_Maybenull_ TSharedPtr<const FDateTime> created;

	/// <summary>
	/// (Optional) Dictionary of player's custom properties.
	/// </summary>
	FPFJsonObject customProperties;

	/// <summary>
	/// (Optional) Player Display Name.
	/// </summary>
	_Maybenull_ const FString displayName;

	/// <summary>
	/// (Optional) Last login.
	/// </summary>
	_Maybenull_ TSharedPtr<const FDateTime> lastLogin;

	/// <summary>
	/// (Optional) Array of third party accounts linked to this player.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFSegmentsPlayerLinkedAccount>> linkedAccounts;

	/// <summary>
	/// Count of linkedAccounts
	/// </summary>
	uint32 linkedAccountsCount;

	/// <summary>
	/// (Optional) Dictionary of player's locations by type.
	/// </summary>
	_Maybenull_ TMap<const FString, TSharedPtr<const FPFSegmentsPlayerLocation>> locations;

	/// <summary>
	/// Count of locations
	/// </summary>
	uint32 locationsCount;

	/// <summary>
	/// (Optional) Player account origination.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFLoginIdentityProvider> origination;

	/// <summary>
	/// (Optional) List of player variants for experimentation.
	/// </summary>
	_Maybenull_ const TArray<FString> playerExperimentVariants;

	/// <summary>
	/// Count of playerExperimentVariants
	/// </summary>
	uint32 playerExperimentVariantsCount;

	/// <summary>
	/// (Optional) PlayFab Player ID.
	/// </summary>
	_Maybenull_ const FString playerId;

	/// <summary>
	/// (Optional) Array of player statistics.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFSegmentsPlayerStatistic>> playerStatistics;

	/// <summary>
	/// Count of playerStatistics
	/// </summary>
	uint32 playerStatisticsCount;

	/// <summary>
	/// (Optional) Publisher this player belongs to.
	/// </summary>
	_Maybenull_ const FString publisherId;

	/// <summary>
	/// (Optional) Array of configured push notification end points.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFSegmentsPushNotificationRegistration>> pushNotificationRegistrations;

	/// <summary>
	/// Count of pushNotificationRegistrations
	/// </summary>
	uint32 pushNotificationRegistrationsCount;

	/// <summary>
	/// (Optional) Dictionary of player's statistics using only the latest version's value.
	/// </summary>
	_Maybenull_ TMap<const FString, int32> statistics;

	/// <summary>
	/// Count of statistics
	/// </summary>
	uint32 statisticsCount;

	/// <summary>
	/// (Optional) List of player's tags for segmentation.
	/// </summary>
	_Maybenull_ const TArray<FString> tags;

	/// <summary>
	/// Count of tags
	/// </summary>
	uint32 tagsCount;

	/// <summary>
	/// (Optional) Title ID this profile applies to.
	/// </summary>
	_Maybenull_ const FString titleId;

	/// <summary>
	/// (Optional) A sum of player's total purchases in USD across all currencies.
	/// </summary>
	_Maybenull_ TSharedPtr<const uint32> totalValueToDateInUSD;

	/// <summary>
	/// (Optional) Dictionary of player's total purchases by currency.
	/// </summary>
	_Maybenull_ TMap<const FString, uint32> valuesToDate;

	/// <summary>
	/// Count of valuesToDate
	/// </summary>
	uint32 valuesToDateCount;

	/// <summary>
	/// (Optional) Dictionary of player's virtual currency balances.
	/// </summary>
	_Maybenull_ TMap<const FString, int32> virtualCurrencyBalances;

	/// <summary>
	/// Count of virtualCurrencyBalances
	/// </summary>
	uint32 virtualCurrencyBalancesCount;
};

/// <summary>
/// FPFSegmentsGetPlayersInSegmentResult data model.
/// </summary>
struct PLAYFABSERVICES_API FPFSegmentsGetPlayersInSegmentResult
{
	/// <summary>
	/// (Optional) Continuation token to use to retrieve subsequent pages of results. If token returns null
	/// there are no more results.
	/// </summary>
	_Maybenull_ const FString continuationToken;

	/// <summary>
	/// (Optional) Array of player profiles in this segment.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFSegmentsPlayerProfile>> playerProfiles;

	/// <summary>
	/// Count of playerProfiles
	/// </summary>
	uint32 playerProfilesCount;

	/// <summary>
	/// Count of profiles matching this segment.
	/// </summary>
	int32 profilesInSegment;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFSegmentsRemovePlayerTagRequest data model. This API will trigger a player_tag_removed event and
/// remove a tag with the given TagName and PlayFabID from the corresponding player profile. TagName can
/// be used for segmentation and it is limited to 256 characters.
/// </summary>
struct PLAYFABSERVICES_API FPFSegmentsRemovePlayerTagRequest
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
	/// Unique PlayFab assigned ID of the user on whom the operation will be performed.
	/// </summary>
	const FString playFabId;

	/// <summary>
	/// Unique tag for player profile.
	/// </summary>
	const FString tagName;
};

// Delegates Declarations

DECLARE_DELEGATE_TwoParams(FOnClientGetPlayerSegmentsCompleted, const FPFSegmentsGetPlayerSegmentsResult&, bool);

DECLARE_DELEGATE_TwoParams(FOnClientGetPlayerTagsCompleted, const FPFSegmentsGetPlayerTagsResult&, bool);

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerAddPlayerTagCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerGetAllSegmentsCompleted, const FPFSegmentsGetAllSegmentsResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerGetPlayerSegmentsCompleted, const FPFSegmentsGetPlayerSegmentsResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerGetPlayersInSegmentCompleted, const FPFSegmentsGetPlayersInSegmentResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerGetPlayerTagsCompleted, const FPFSegmentsGetPlayerTagsResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerRemovePlayerTagCompleted, const FString&, bool);
#endif

#pragma pop_macro("IN")