// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once
#include "PFUnrealTypes.h"

#if defined(PF_GDK_AVAILABLE) && defined(PF_UE_GDK_SUPPORT)
#include "GDKHandle.h"
#endif

#pragma push_macro("IN")
#undef IN

/// <summary>
/// UserFamilyType enum.
/// </summary>
enum class FPFAccountManagementUserFamilyType : uint32
{
	None,
	Xbox,
	Steam
};

/// <summary>
/// FPFAccountManagementAddOrUpdateContactEmailRequest data model. This API adds a contact email to the
/// player's profile. If the player's profile already contains a contact email, it will update the contact
/// email to the email address specified.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementAddOrUpdateContactEmailRequest
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
	/// The new contact email to associate with the player.
	/// </summary>
	const FString emailAddress;
};

/// <summary>
/// FPFAccountManagementAddUsernamePasswordRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementAddUsernamePasswordRequest
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
	/// User email address attached to their account.
	/// </summary>
	const FString email;

	/// <summary>
	/// Password for the PlayFab account (6-100 characters).
	/// </summary>
	const FString password;

	/// <summary>
	/// PlayFab username for the account (3-20 characters).
	/// </summary>
	const FString username;
};

/// <summary>
/// FPFAccountManagementAddUsernamePasswordResult data model. Each account must have a unique username
/// and email address in the PlayFab service. Once created, the account may be associated with additional
/// accounts (Steam, Facebook, Game Center, etc.), allowing for added social network lists and achievements
/// systems. This can also be used to provide a recovery method if the user loses their original means
/// of access.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementAddUsernamePasswordResult
{
	/// <summary>
	/// (Optional) PlayFab unique user name.
	/// </summary>
	_Maybenull_ const FString username;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFAccountManagementGetAccountInfoRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetAccountInfoRequest
{
	/// <summary>
	/// (Optional) User email address for the account to find (if no Username is specified).
	/// </summary>
	_Maybenull_ const FString email;

	/// <summary>
	/// (Optional) Unique PlayFab identifier of the user whose info is being requested. Optional, defaults
	/// to the authenticated user if no other lookup identifier set.
	/// </summary>
	_Maybenull_ const FString playFabId;

	/// <summary>
	/// (Optional) Title-specific username for the account to find (if no Email is set). Note that if the
	/// non-unique Title Display Names option is enabled for the title, attempts to look up users by Title
	/// Display Name will always return AccountNotFound.
	/// </summary>
	_Maybenull_ const FString titleDisplayName;

	/// <summary>
	/// (Optional) PlayFab Username for the account to find (if no PlayFabId is specified).
	/// </summary>
	_Maybenull_ const FString username;
};

/// <summary>
/// FPFAccountManagementGetAccountInfoResult data model. This API retrieves details regarding the player
/// in the PlayFab service. Note that when this call is used to retrieve data about another player (not
/// the one signed into the local client), some data, such as Personally Identifying Information (PII),
/// will be omitted for privacy reasons or to comply with the requirements of the platform belongs to.
/// The user account returned will be based on the identifier provided in priority order: PlayFabId, Username,
/// Email, then TitleDisplayName. If no identifier is specified, the currently signed in user's information
/// will be returned.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetAccountInfoResult
{
	/// <summary>
	/// (Optional) Account information for the local user.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFUserAccountInfo> accountInfo;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFAccountManagementGetPlayerCombinedInfoRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetPlayerCombinedInfoRequest
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
	/// Flags for which pieces of info to return for the user.
	/// </summary>
	TSharedPtr<const FPFGetPlayerCombinedInfoRequestParams> infoRequestParameters;

	/// <summary>
	/// (Optional) PlayFabId of the user whose data will be returned. If not filled included, we return
	/// the data for the calling player. .
	/// </summary>
	_Maybenull_ const FString playFabId;
};

/// <summary>
/// FPFAccountManagementGetPlayerCombinedInfoResult data model. Returns whatever info is requested in
/// the response for the user. If no user is explicitly requested this defaults to the authenticated user.
/// If the user is the same as the requester, PII (like email address, facebook id) is returned if available.
/// Otherwise, only public information is returned. All parameters default to false.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetPlayerCombinedInfoResult
{
	/// <summary>
	/// (Optional) Results for requested info.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFGetPlayerCombinedInfoResultPayload> infoResultPayload;

	/// <summary>
	/// (Optional) Unique PlayFab assigned ID of the user on whom the operation will be performed.
	/// </summary>
	_Maybenull_ const FString playFabId;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFAccountManagementGetPlayerProfileRequest data model. This API allows for access to details regarding
/// a user in the PlayFab service, usually for purposes of customer support. Note that data returned may
/// be Personally Identifying Information (PII), such as email address, and so care should be taken in
/// how this data is stored and managed. Since this call will always return the relevant information for
/// users who have accessed the title, the recommendation is to not store this data locally.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetPlayerProfileRequest
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
	/// (Optional) Unique PlayFab assigned ID of the user on whom the operation will be performed.
	/// </summary>
	_Maybenull_ const FString playFabId;

	/// <summary>
	/// (Optional) If non-null, this determines which properties of the resulting player profiles to return.
	/// For API calls from the client, only the allowed client profile properties for the title may be requested.
	/// These allowed properties are configured in the Game Manager "Client Profile Options" tab in the "Settings"
	/// section.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFPlayerProfileViewConstraints> profileConstraints;
};

/// <summary>
/// FPFAccountManagementGetPlayerProfileResult data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetPlayerProfileResult
{
	/// <summary>
	/// (Optional) The profile of the player. This profile is not guaranteed to be up-to-date. For a new
	/// player, this profile will not exist.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFPlayerProfileModel> playerProfile;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsRequest
{
	/// <summary>
	/// Array of unique Battle.net account identifiers for which the title needs to get PlayFab identifiers.
	/// The array cannot exceed 10 in length.
	/// </summary>
	const TArray<FString> battleNetAccountIds;

	/// <summary>
	/// Count of battleNetAccountIds
	/// </summary>
	uint32 battleNetAccountIdsCount;
};

/// <summary>
/// FPFAccountManagementBattleNetAccountPlayFabIdPair data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementBattleNetAccountPlayFabIdPair
{
	/// <summary>
	/// (Optional) Unique Battle.net account identifier for a user.
	/// </summary>
	_Maybenull_ const FString battleNetAccountId;

	/// <summary>
	/// (Optional) Unique PlayFab identifier for a user, or null if no PlayFab account is linked to the
	/// Battle.net account identifier.
	/// </summary>
	_Maybenull_ const FString playFabId;
};

/// <summary>
/// FPFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsResult data model. For Battle.net account
/// identifiers which have not been linked to PlayFab accounts, null will be returned.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsResult
{
	/// <summary>
	/// (Optional) Mapping of Battle.net account identifiers to PlayFab identifiers.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFAccountManagementBattleNetAccountPlayFabIdPair>> data;

	/// <summary>
	/// Count of data
	/// </summary>
	uint32 dataCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFAccountManagementGetPlayFabIDsFromFacebookIDsRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetPlayFabIDsFromFacebookIDsRequest
{
	/// <summary>
	/// Array of unique Facebook identifiers for which the title needs to get PlayFab identifiers. The array
	/// cannot exceed 25 in length.
	/// </summary>
	const TArray<FString> facebookIDs;

	/// <summary>
	/// Count of facebookIDs
	/// </summary>
	uint32 facebookIDsCount;
};

/// <summary>
/// FPFAccountManagementFacebookPlayFabIdPair data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementFacebookPlayFabIdPair
{
	/// <summary>
	/// (Optional) Unique Facebook identifier for a user.
	/// </summary>
	_Maybenull_ const FString facebookId;

	/// <summary>
	/// (Optional) Unique PlayFab identifier for a user, or null if no PlayFab account is linked to the
	/// Facebook identifier.
	/// </summary>
	_Maybenull_ const FString playFabId;
};

/// <summary>
/// FPFAccountManagementGetPlayFabIDsFromFacebookIDsResult data model. For Facebook identifiers which
/// have not been linked to PlayFab accounts, null will be returned.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetPlayFabIDsFromFacebookIDsResult
{
	/// <summary>
	/// (Optional) Mapping of Facebook identifiers to PlayFab identifiers.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFAccountManagementFacebookPlayFabIdPair>> data;

	/// <summary>
	/// Count of data
	/// </summary>
	uint32 dataCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsRequest
{
	/// <summary>
	/// Array of unique Facebook Instant Games identifiers for which the title needs to get PlayFab identifiers.
	/// The array cannot exceed 25 in length.
	/// </summary>
	const TArray<FString> facebookInstantGamesIds;

	/// <summary>
	/// Count of facebookInstantGamesIds
	/// </summary>
	uint32 facebookInstantGamesIdsCount;
};

/// <summary>
/// FPFAccountManagementFacebookInstantGamesPlayFabIdPair data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementFacebookInstantGamesPlayFabIdPair
{
	/// <summary>
	/// (Optional) Unique Facebook Instant Games identifier for a user.
	/// </summary>
	_Maybenull_ const FString facebookInstantGamesId;

	/// <summary>
	/// (Optional) Unique PlayFab identifier for a user, or null if no PlayFab account is linked to the
	/// Facebook Instant Games identifier.
	/// </summary>
	_Maybenull_ const FString playFabId;
};

/// <summary>
/// FPFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsResult data model. For Facebook Instant
/// Game identifiers which have not been linked to PlayFab accounts, null will be returned.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsResult
{
	/// <summary>
	/// (Optional) Mapping of Facebook Instant Games identifiers to PlayFab identifiers.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFAccountManagementFacebookInstantGamesPlayFabIdPair>> data;

	/// <summary>
	/// Count of data
	/// </summary>
	uint32 dataCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFAccountManagementGetPlayFabIDsFromGameCenterIDsRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetPlayFabIDsFromGameCenterIDsRequest
{
	/// <summary>
	/// Array of unique Game Center identifiers (the Player Identifier) for which the title needs to get
	/// PlayFab identifiers. The array cannot exceed 25 in length.
	/// </summary>
	const TArray<FString> gameCenterIDs;

	/// <summary>
	/// Count of gameCenterIDs
	/// </summary>
	uint32 gameCenterIDsCount;
};

/// <summary>
/// FPFAccountManagementGameCenterPlayFabIdPair data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGameCenterPlayFabIdPair
{
	/// <summary>
	/// (Optional) Unique Game Center identifier for a user.
	/// </summary>
	_Maybenull_ const FString gameCenterId;

	/// <summary>
	/// (Optional) Unique PlayFab identifier for a user, or null if no PlayFab account is linked to the
	/// Game Center identifier.
	/// </summary>
	_Maybenull_ const FString playFabId;
};

/// <summary>
/// FPFAccountManagementGetPlayFabIDsFromGameCenterIDsResult data model. For Game Center identifiers
/// which have not been linked to PlayFab accounts, null will be returned.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetPlayFabIDsFromGameCenterIDsResult
{
	/// <summary>
	/// (Optional) Mapping of Game Center identifiers to PlayFab identifiers.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFAccountManagementGameCenterPlayFabIdPair>> data;

	/// <summary>
	/// Count of data
	/// </summary>
	uint32 dataCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFAccountManagementGetPlayFabIDsFromGoogleIDsRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetPlayFabIDsFromGoogleIDsRequest
{
	/// <summary>
	/// Array of unique Google identifiers (Google+ user IDs) for which the title needs to get PlayFab identifiers.
	/// The array cannot exceed 25 in length.
	/// </summary>
	const TArray<FString> googleIDs;

	/// <summary>
	/// Count of googleIDs
	/// </summary>
	uint32 googleIDsCount;
};

/// <summary>
/// FPFAccountManagementGooglePlayFabIdPair data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGooglePlayFabIdPair
{
	/// <summary>
	/// (Optional) Unique Google identifier for a user.
	/// </summary>
	_Maybenull_ const FString googleId;

	/// <summary>
	/// (Optional) Unique PlayFab identifier for a user, or null if no PlayFab account is linked to the
	/// Google identifier.
	/// </summary>
	_Maybenull_ const FString playFabId;
};

/// <summary>
/// FPFAccountManagementGetPlayFabIDsFromGoogleIDsResult data model. For Google identifiers which have
/// not been linked to PlayFab accounts, null will be returned.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetPlayFabIDsFromGoogleIDsResult
{
	/// <summary>
	/// (Optional) Mapping of Google identifiers to PlayFab identifiers.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFAccountManagementGooglePlayFabIdPair>> data;

	/// <summary>
	/// Count of data
	/// </summary>
	uint32 dataCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFAccountManagementGetPlayFabIDsFromGooglePlayGamesPlayerIDsRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetPlayFabIDsFromGooglePlayGamesPlayerIDsRequest
{
	/// <summary>
	/// Array of unique Google Play Games identifiers (Google+ user IDs) for which the title needs to get
	/// PlayFab identifiers. The array cannot exceed 25 in length.
	/// </summary>
	const TArray<FString> googlePlayGamesPlayerIDs;

	/// <summary>
	/// Count of googlePlayGamesPlayerIDs
	/// </summary>
	uint32 googlePlayGamesPlayerIDsCount;
};

/// <summary>
/// FPFAccountManagementGooglePlayGamesPlayFabIdPair data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGooglePlayGamesPlayFabIdPair
{
	/// <summary>
	/// (Optional) Unique Google Play Games identifier for a user.
	/// </summary>
	_Maybenull_ const FString googlePlayGamesPlayerId;

	/// <summary>
	/// (Optional) Unique PlayFab identifier for a user, or null if no PlayFab account is linked to the
	/// Google Play Games identifier.
	/// </summary>
	_Maybenull_ const FString playFabId;
};

/// <summary>
/// FPFAccountManagementGetPlayFabIDsFromGooglePlayGamesPlayerIDsResult data model. For Google Play Games
/// identifiers which have not been linked to PlayFab accounts, null will be returned.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetPlayFabIDsFromGooglePlayGamesPlayerIDsResult
{
	/// <summary>
	/// (Optional) Mapping of Google Play Games identifiers to PlayFab identifiers.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFAccountManagementGooglePlayGamesPlayFabIdPair>> data;

	/// <summary>
	/// Count of data
	/// </summary>
	uint32 dataCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFAccountManagementGetPlayFabIDsFromKongregateIDsRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetPlayFabIDsFromKongregateIDsRequest
{
	/// <summary>
	/// Array of unique Kongregate identifiers (Kongregate's user_id) for which the title needs to get PlayFab
	/// identifiers. The array cannot exceed 25 in length.
	/// </summary>
	const TArray<FString> kongregateIDs;

	/// <summary>
	/// Count of kongregateIDs
	/// </summary>
	uint32 kongregateIDsCount;
};

/// <summary>
/// FPFAccountManagementKongregatePlayFabIdPair data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementKongregatePlayFabIdPair
{
	/// <summary>
	/// (Optional) Unique Kongregate identifier for a user.
	/// </summary>
	_Maybenull_ const FString kongregateId;

	/// <summary>
	/// (Optional) Unique PlayFab identifier for a user, or null if no PlayFab account is linked to the
	/// Kongregate identifier.
	/// </summary>
	_Maybenull_ const FString playFabId;
};

/// <summary>
/// FPFAccountManagementGetPlayFabIDsFromKongregateIDsResult data model. For Kongregate identifiers which
/// have not been linked to PlayFab accounts, null will be returned.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetPlayFabIDsFromKongregateIDsResult
{
	/// <summary>
	/// (Optional) Mapping of Kongregate identifiers to PlayFab identifiers.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFAccountManagementKongregatePlayFabIdPair>> data;

	/// <summary>
	/// Count of data
	/// </summary>
	uint32 dataCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsRequest
{
	/// <summary>
	/// Array of unique Nintendo Switch Account identifiers for which the title needs to get PlayFab identifiers.
	/// The array cannot exceed 25 in length.
	/// </summary>
	const TArray<FString> nintendoAccountIds;

	/// <summary>
	/// Count of nintendoAccountIds
	/// </summary>
	uint32 nintendoAccountIdsCount;
};

/// <summary>
/// FPFAccountManagementNintendoServiceAccountPlayFabIdPair data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementNintendoServiceAccountPlayFabIdPair
{
	/// <summary>
	/// (Optional) Unique Nintendo Switch Service Account identifier for a user.
	/// </summary>
	_Maybenull_ const FString nintendoServiceAccountId;

	/// <summary>
	/// (Optional) Unique PlayFab identifier for a user, or null if no PlayFab account is linked to the
	/// Nintendo Switch Service Account identifier.
	/// </summary>
	_Maybenull_ const FString playFabId;
};

/// <summary>
/// FPFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsResult data model. For Nintendo Service
/// Account identifiers which have not been linked to PlayFab accounts, null will be returned.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsResult
{
	/// <summary>
	/// (Optional) Mapping of Nintendo Switch Service Account identifiers to PlayFab identifiers.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFAccountManagementNintendoServiceAccountPlayFabIdPair>> data;

	/// <summary>
	/// Count of data
	/// </summary>
	uint32 dataCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsRequest
{
	/// <summary>
	/// Array of unique Nintendo Switch Device identifiers for which the title needs to get PlayFab identifiers.
	/// The array cannot exceed 25 in length.
	/// </summary>
	const TArray<FString> nintendoSwitchDeviceIds;

	/// <summary>
	/// Count of nintendoSwitchDeviceIds
	/// </summary>
	uint32 nintendoSwitchDeviceIdsCount;
};

/// <summary>
/// FPFAccountManagementNintendoSwitchPlayFabIdPair data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementNintendoSwitchPlayFabIdPair
{
	/// <summary>
	/// (Optional) Unique Nintendo Switch Device identifier for a user.
	/// </summary>
	_Maybenull_ const FString nintendoSwitchDeviceId;

	/// <summary>
	/// (Optional) Unique PlayFab identifier for a user, or null if no PlayFab account is linked to the
	/// Nintendo Switch Device identifier.
	/// </summary>
	_Maybenull_ const FString playFabId;
};

/// <summary>
/// FPFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsResult data model. For Nintendo Switch
/// identifiers which have not been linked to PlayFab accounts, null will be returned.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsResult
{
	/// <summary>
	/// (Optional) Mapping of Nintendo Switch Device identifiers to PlayFab identifiers.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFAccountManagementNintendoSwitchPlayFabIdPair>> data;

	/// <summary>
	/// Count of data
	/// </summary>
	uint32 dataCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFAccountManagementGetPlayFabIDsFromPSNAccountIDsRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetPlayFabIDsFromPSNAccountIDsRequest
{
	/// <summary>
	/// (Optional) Id of the PlayStation :tm: Network issuer environment. If null, defaults to production
	/// environment.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> issuerId;

	/// <summary>
	/// Array of unique PlayStation :tm: Network identifiers for which the title needs to get PlayFab identifiers.
	/// The array cannot exceed 25 in length.
	/// </summary>
	const TArray<FString> PSNAccountIDs;

	/// <summary>
	/// Count of PSNAccountIDs
	/// </summary>
	uint32 PSNAccountIDsCount;
};

/// <summary>
/// FPFAccountManagementPSNAccountPlayFabIdPair data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementPSNAccountPlayFabIdPair
{
	/// <summary>
	/// (Optional) Unique PlayFab identifier for a user, or null if no PlayFab account is linked to the
	/// PlayStation :tm: Network identifier.
	/// </summary>
	_Maybenull_ const FString playFabId;

	/// <summary>
	/// (Optional) Unique PlayStation :tm: Network identifier for a user.
	/// </summary>
	_Maybenull_ const FString PSNAccountId;
};

/// <summary>
/// FPFAccountManagementGetPlayFabIDsFromPSNAccountIDsResult data model. For PlayStation :tm: Network
/// identifiers which have not been linked to PlayFab accounts, null will be returned.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetPlayFabIDsFromPSNAccountIDsResult
{
	/// <summary>
	/// (Optional) Mapping of PlayStation :tm: Network identifiers to PlayFab identifiers.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFAccountManagementPSNAccountPlayFabIdPair>> data;

	/// <summary>
	/// Count of data
	/// </summary>
	uint32 dataCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFAccountManagementGetPlayFabIDsFromPSNOnlineIDsRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetPlayFabIDsFromPSNOnlineIDsRequest
{
	/// <summary>
	/// (Optional) Id of the PlayStation :tm: Network issuer environment. If null, defaults to production
	/// environment.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> issuerId;

	/// <summary>
	/// Array of unique PlayStation :tm: Network identifiers for which the title needs to get PlayFab identifiers.
	/// The array cannot exceed 25 in length.
	/// </summary>
	const TArray<FString> PSNOnlineIDs;

	/// <summary>
	/// Count of PSNOnlineIDs
	/// </summary>
	uint32 PSNOnlineIDsCount;
};

/// <summary>
/// FPFAccountManagementPSNOnlinePlayFabIdPair data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementPSNOnlinePlayFabIdPair
{
	/// <summary>
	/// (Optional) Unique PlayFab identifier for a user, or null if no PlayFab account is linked to the
	/// PlayStation :tm: Network identifier.
	/// </summary>
	_Maybenull_ const FString playFabId;

	/// <summary>
	/// (Optional) Unique PlayStation :tm: Network identifier for a user.
	/// </summary>
	_Maybenull_ const FString PSNOnlineId;
};

/// <summary>
/// FPFAccountManagementGetPlayFabIDsFromPSNOnlineIDsResult data model. For PlayStation :tm: Network
/// identifiers which have not been linked to PlayFab accounts, null will be returned.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetPlayFabIDsFromPSNOnlineIDsResult
{
	/// <summary>
	/// (Optional) Mapping of PlayStation :tm: Network identifiers to PlayFab identifiers.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFAccountManagementPSNOnlinePlayFabIdPair>> data;

	/// <summary>
	/// Count of data
	/// </summary>
	uint32 dataCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFAccountManagementGetPlayFabIDsFromSteamIDsRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetPlayFabIDsFromSteamIDsRequest
{
	/// <summary>
	/// (Optional) Array of unique Steam identifiers (Steam profile IDs) for which the title needs to get
	/// PlayFab identifiers. The array cannot exceed 25 in length.
	/// </summary>
	_Maybenull_ const TArray<FString> steamStringIDs;

	/// <summary>
	/// Count of steamStringIDs
	/// </summary>
	uint32 steamStringIDsCount;
};

/// <summary>
/// FPFAccountManagementSteamPlayFabIdPair data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementSteamPlayFabIdPair
{
	/// <summary>
	/// (Optional) Unique PlayFab identifier for a user, or null if no PlayFab account is linked to the
	/// Steam identifier.
	/// </summary>
	_Maybenull_ const FString playFabId;

	/// <summary>
	/// (Optional) Unique Steam identifier for a user.
	/// </summary>
	_Maybenull_ const FString steamStringId;
};

/// <summary>
/// FPFAccountManagementGetPlayFabIDsFromSteamIDsResult data model. For Steam identifiers which have
/// not been linked to PlayFab accounts, null will be returned.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetPlayFabIDsFromSteamIDsResult
{
	/// <summary>
	/// (Optional) Mapping of Steam identifiers to PlayFab identifiers.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFAccountManagementSteamPlayFabIdPair>> data;

	/// <summary>
	/// Count of data
	/// </summary>
	uint32 dataCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFAccountManagementGetPlayFabIDsFromSteamNamesRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetPlayFabIDsFromSteamNamesRequest
{
	/// <summary>
	/// Array of unique Steam identifiers for which the title needs to get PlayFab identifiers. The array
	/// cannot exceed 25 in length.
	/// </summary>
	const TArray<FString> steamNames;

	/// <summary>
	/// Count of steamNames
	/// </summary>
	uint32 steamNamesCount;
};

/// <summary>
/// FPFAccountManagementSteamNamePlayFabIdPair data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementSteamNamePlayFabIdPair
{
	/// <summary>
	/// (Optional) Unique PlayFab identifier for a user, or null if no PlayFab account is linked to the
	/// Steam identifier.
	/// </summary>
	_Maybenull_ const FString playFabId;

	/// <summary>
	/// (Optional) Unique Steam identifier for a user, also known as Steam persona name.
	/// </summary>
	_Maybenull_ const FString steamName;
};

/// <summary>
/// FPFAccountManagementGetPlayFabIDsFromSteamNamesResult data model. For Steam identifiers which have
/// not been linked to PlayFab accounts, or if the user has not logged in recently, null will be returned.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetPlayFabIDsFromSteamNamesResult
{
	/// <summary>
	/// (Optional) Mapping of Steam identifiers to PlayFab identifiers.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFAccountManagementSteamNamePlayFabIdPair>> data;

	/// <summary>
	/// Count of data
	/// </summary>
	uint32 dataCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFAccountManagementGetPlayFabIDsFromTwitchIDsRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetPlayFabIDsFromTwitchIDsRequest
{
	/// <summary>
	/// Array of unique Twitch identifiers (Twitch's _id) for which the title needs to get PlayFab identifiers.
	/// The array cannot exceed 25 in length.
	/// </summary>
	const TArray<FString> twitchIds;

	/// <summary>
	/// Count of twitchIds
	/// </summary>
	uint32 twitchIdsCount;
};

/// <summary>
/// FPFAccountManagementTwitchPlayFabIdPair data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementTwitchPlayFabIdPair
{
	/// <summary>
	/// (Optional) Unique PlayFab identifier for a user, or null if no PlayFab account is linked to the
	/// Twitch identifier.
	/// </summary>
	_Maybenull_ const FString playFabId;

	/// <summary>
	/// (Optional) Unique Twitch identifier for a user.
	/// </summary>
	_Maybenull_ const FString twitchId;
};

/// <summary>
/// FPFAccountManagementGetPlayFabIDsFromTwitchIDsResult data model. For Twitch identifiers which have
/// not been linked to PlayFab accounts, null will be returned.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetPlayFabIDsFromTwitchIDsResult
{
	/// <summary>
	/// (Optional) Mapping of Twitch identifiers to PlayFab identifiers.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFAccountManagementTwitchPlayFabIdPair>> data;

	/// <summary>
	/// Count of data
	/// </summary>
	uint32 dataCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFAccountManagementGetPlayFabIDsFromXboxLiveIDsRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetPlayFabIDsFromXboxLiveIDsRequest
{
	/// <summary>
	/// (Optional) The ID of Xbox Live sandbox.
	/// </summary>
	_Maybenull_ const FString sandbox;

	/// <summary>
	/// Array of unique Xbox Live account identifiers for which the title needs to get PlayFab identifiers.
	/// The array cannot exceed 25 in length.
	/// </summary>
	const TArray<FString> xboxLiveAccountIDs;

	/// <summary>
	/// Count of xboxLiveAccountIDs
	/// </summary>
	uint32 xboxLiveAccountIDsCount;
};

/// <summary>
/// FPFAccountManagementXboxLiveAccountPlayFabIdPair data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementXboxLiveAccountPlayFabIdPair
{
	/// <summary>
	/// (Optional) Unique PlayFab identifier for a user, or null if no PlayFab account is linked to the
	/// Xbox Live identifier.
	/// </summary>
	_Maybenull_ const FString playFabId;

	/// <summary>
	/// (Optional) Unique Xbox Live identifier for a user.
	/// </summary>
	_Maybenull_ const FString xboxLiveAccountId;
};

/// <summary>
/// FPFAccountManagementGetPlayFabIDsFromXboxLiveIDsResult data model. For XboxLive identifiers which
/// have not been linked to PlayFab accounts, null will be returned.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetPlayFabIDsFromXboxLiveIDsResult
{
	/// <summary>
	/// (Optional) Mapping of Xbox Live identifiers to PlayFab identifiers.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFAccountManagementXboxLiveAccountPlayFabIdPair>> data;

	/// <summary>
	/// Count of data
	/// </summary>
	uint32 dataCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFAccountManagementLinkAndroidDeviceIDRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementLinkAndroidDeviceIDRequest
{
	/// <summary>
	/// (Optional) Specific model of the user's device.
	/// </summary>
	_Maybenull_ const FString androidDevice;

	/// <summary>
	/// Android device identifier for the user's device.
	/// </summary>
	const FString androidDeviceId;

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
	/// (Optional) If another user is already linked to the device, unlink the other user and re-link.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> forceLink;

	/// <summary>
	/// (Optional) Specific Operating System version for the user's device.
	/// </summary>
	_Maybenull_ const FString OS;
};

/// <summary>
/// FPFAccountManagementLinkAppleRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementLinkAppleRequest
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
	/// (Optional) If another user is already linked to a specific Apple account, unlink the other user
	/// and re-link.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> forceLink;

	/// <summary>
	/// The JSON Web token (JWT) returned by Apple after login. Represented as the identityToken field in
	/// the authorization credential payload. Used to validate the request and find the user ID (Apple subject)
	/// to link with.
	/// </summary>
	const FString identityToken;
};

/// <summary>
/// FPFAccountManagementClientLinkBattleNetAccountRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementClientLinkBattleNetAccountRequest
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
	/// (Optional) If another user is already linked to a specific Battle.net account, unlink the other
	/// user and re-link.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> forceLink;

	/// <summary>
	/// The JSON Web Token (JWT) returned by Battle.net after login.
	/// </summary>
	const FString identityToken;
};

/// <summary>
/// FPFAccountManagementLinkCustomIDRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementLinkCustomIDRequest
{
	/// <summary>
	/// Custom unique identifier for the user, generated by the title.
	/// </summary>
	const FString customId;

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
	/// (Optional) If another user is already linked to the custom ID, unlink the other user and re-link.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> forceLink;
};

/// <summary>
/// FPFAccountManagementLinkFacebookAccountRequest data model. Facebook sign-in is accomplished using
/// the Facebook User Access Token. More information on the Token can be found in the Facebook developer
/// documentation (https://developers.facebook.com/docs/facebook-login/access-tokens/). In Unity, for
/// example, the Token is available as AccessToken in the Facebook SDK ScriptableObject FB. Note that
/// titles should never re-use the same Facebook applications between PlayFab Title IDs, as Facebook provides
/// unique user IDs per application and doing so can result in issues with the Facebook ID for the user
/// in their PlayFab account information. If you must re-use an application in a new PlayFab Title ID,
/// please be sure to first unlink all accounts from Facebook, or delete all users in the first Title
/// ID.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementLinkFacebookAccountRequest
{
	/// <summary>
	/// (Optional) Unique identifier from Facebook for the user.
	/// </summary>
	_Maybenull_ const FString accessToken;

	/// <summary>
	/// (Optional) Token used for limited login authentication.
	/// </summary>
	_Maybenull_ const FString authenticationToken;

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
	/// (Optional) If another user is already linked to the account, unlink the other user and re-link.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> forceLink;
};

/// <summary>
/// FPFAccountManagementLinkFacebookInstantGamesIdRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementLinkFacebookInstantGamesIdRequest
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
	/// Facebook Instant Games signature for the user.
	/// </summary>
	const FString facebookInstantGamesSignature;

	/// <summary>
	/// (Optional) If another user is already linked to the Facebook Instant Games ID, unlink the other
	/// user and re-link.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> forceLink;
};

/// <summary>
/// FPFAccountManagementLinkGameCenterAccountRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementLinkGameCenterAccountRequest
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
	/// (Optional) If another user is already linked to the account, unlink the other user and re-link.
	/// If the current user is already linked, link both accounts.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> forceLink;

	/// <summary>
	/// Game Center identifier for the player account to be linked.
	/// </summary>
	const FString gameCenterId;

	/// <summary>
	/// (Optional) The URL for the public encryption key that will be used to verify the signature.
	/// </summary>
	_Maybenull_ const FString publicKeyUrl;

	/// <summary>
	/// (Optional) A random value used to compute the hash and keep it randomized.
	/// </summary>
	_Maybenull_ const FString salt;

	/// <summary>
	/// (Optional) The verification signature of the authentication payload.
	/// </summary>
	_Maybenull_ const FString signature;

	/// <summary>
	/// (Optional) The integer representation of date and time that the signature was created on. PlayFab
	/// will reject authentication signatures not within 10 minutes of the server's current time.
	/// </summary>
	_Maybenull_ const FString timestamp;
};

/// <summary>
/// FPFAccountManagementLinkGoogleAccountRequest data model. Google sign-in is accomplished by obtaining
/// a Google OAuth 2.0 credential using the Google sign-in for Android APIs on the device and passing
/// it to this API.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementLinkGoogleAccountRequest
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
	/// (Optional) If another user is already linked to the account, unlink the other user and re-link.
	/// If the current user is already linked, link both accounts.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> forceLink;

	/// <summary>
	/// (Optional) Server authentication code obtained on the client by calling getServerAuthCode() (https://developers.google.com/identity/sign-in/android/offline-access)
	/// from Google Play for the user.
	/// </summary>
	_Maybenull_ const FString serverAuthCode;
};

/// <summary>
/// FPFAccountManagementLinkGooglePlayGamesServicesAccountRequest data model. Google Play Games sign-in
/// is accomplished by obtaining a Google OAuth 2.0 credential using the Google Play Games sign-in for
/// Android APIs on the device and passing it to this API.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementLinkGooglePlayGamesServicesAccountRequest
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
	/// (Optional) If another user is already linked to the account, unlink the other user and re-link.
	/// If the current user is already linked, link both accounts.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> forceLink;

	/// <summary>
	/// OAuth 2.0 server authentication code obtained on the client by calling the requestServerSideAccess()
	/// (https://developers.google.com/games/services/android/signin) Google Play Games client API.
	/// </summary>
	const FString serverAuthCode;
};

/// <summary>
/// FPFAccountManagementLinkIOSDeviceIDRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementLinkIOSDeviceIDRequest
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
	/// Vendor-specific iOS identifier for the user's device.
	/// </summary>
	const FString deviceId;

	/// <summary>
	/// (Optional) Specific model of the user's device.
	/// </summary>
	_Maybenull_ const FString deviceModel;

	/// <summary>
	/// (Optional) If another user is already linked to the device, unlink the other user and re-link.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> forceLink;

	/// <summary>
	/// (Optional) Specific Operating System version for the user's device.
	/// </summary>
	_Maybenull_ const FString OS;
};

/// <summary>
/// FPFAccountManagementLinkKongregateAccountRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementLinkKongregateAccountRequest
{
	/// <summary>
	/// Valid session auth ticket issued by Kongregate.
	/// </summary>
	const FString authTicket;

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
	/// (Optional) If another user is already linked to the account, unlink the other user and re-link.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> forceLink;

	/// <summary>
	/// Numeric user ID assigned by Kongregate.
	/// </summary>
	const FString kongregateId;
};

/// <summary>
/// FPFAccountManagementClientLinkNintendoServiceAccountRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementClientLinkNintendoServiceAccountRequest
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
	/// (Optional) If another user is already linked to a specific Nintendo Switch account, unlink the other
	/// user and re-link.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> forceLink;

	/// <summary>
	/// The JSON Web token (JWT) returned by Nintendo after login. Used to validate the request and find
	/// the user ID (Nintendo Switch subject) to link with.
	/// </summary>
	const FString identityToken;
};

/// <summary>
/// FPFAccountManagementClientLinkNintendoSwitchDeviceIdRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementClientLinkNintendoSwitchDeviceIdRequest
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
	/// (Optional) If another user is already linked to the Nintendo Switch Device ID, unlink the other
	/// user and re-link.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> forceLink;

	/// <summary>
	/// Nintendo Switch unique identifier for the user's device.
	/// </summary>
	const FString nintendoSwitchDeviceId;
};

/// <summary>
/// FPFAccountManagementLinkOpenIdConnectRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementLinkOpenIdConnectRequest
{
	/// <summary>
	/// A name that identifies which configured OpenID Connect provider relationship to use. Maximum 100
	/// characters.
	/// </summary>
	const FString connectionId;

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
	/// (Optional) If another user is already linked to a specific OpenId Connect user, unlink the other
	/// user and re-link.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> forceLink;

	/// <summary>
	/// The JSON Web token (JWT) returned by the identity provider after login. Represented as the id_token
	/// field in the identity provider's response. Used to validate the request and find the user ID (OpenID
	/// Connect subject) to link with.
	/// </summary>
	const FString idToken;
};

/// <summary>
/// FPFAccountManagementClientLinkPSNAccountRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementClientLinkPSNAccountRequest
{
	/// <summary>
	/// Authentication code provided by the PlayStation :tm: Network.
	/// </summary>
	const FString authCode;

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
	/// (Optional) If another user is already linked to the account, unlink the other user and re-link.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> forceLink;

	/// <summary>
	/// (Optional) Id of the PlayStation :tm: Network issuer environment. If null, defaults to production
	/// environment.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> issuerId;

	/// <summary>
	/// Redirect URI supplied to PlayStation :tm: Network when requesting an auth code.
	/// </summary>
	const FString redirectUri;
};

/// <summary>
/// FPFAccountManagementLinkSteamAccountRequest data model. Steam authentication is accomplished with
/// the Steam Session Ticket. More information on the Ticket can be found in the Steamworks SDK, here:
/// https://partner.steamgames.com/documentation/auth (requires sign-in). NOTE: For Steam authentication
/// to work, the title must be configured with the Steam Application ID and Publisher Key in the PlayFab
/// Game Manager (under Properties). Information on creating a Publisher Key (referred to as the Secret
/// Key in PlayFab) for your title can be found here: https://partner.steamgames.com/documentation/webapi#publisherkey.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementLinkSteamAccountRequest
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
	/// (Optional) If another user is already linked to the account, unlink the other user and re-link.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> forceLink;

	/// <summary>
	/// Authentication token for the user, returned as a byte array from Steam, and converted to a string
	/// (for example, the byte 0x08 should become "08").
	/// </summary>
	const FString steamTicket;

	/// <summary>
	/// (Optional) True if ticket was generated using ISteamUser::GetAuthTicketForWebAPI() using "AzurePlayFab"
	/// as the identity string. False if the ticket was generated with ISteamUser::GetAuthSessionTicket().
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> ticketIsServiceSpecific;
};

/// <summary>
/// FPFAccountManagementLinkTwitchAccountRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementLinkTwitchAccountRequest
{
	/// <summary>
	/// Valid token issued by Twitch.
	/// </summary>
	const FString accessToken;

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
	/// (Optional) If another user is already linked to the account, unlink the other user and re-link.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> forceLink;
};

/// <summary>
/// FPFAccountManagementClientLinkXboxAccountRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementClientLinkXboxAccountRequest
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
	/// (Optional) If another user is already linked to the account, unlink the other user and re-link.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> forceLink;

#if defined(PF_GDK_AVAILABLE) && defined(PF_UE_GDK_SUPPORT)
	/// <summary>
	/// FGDKUserHandle of the account to link to.
	/// </summary>
	FGDKUserHandle user;
#elif defined(PF_GDK_AVAILABLE)
    /// <summary>
    /// XUserHandle of the account to link to.
    /// </summary>
    XUserHandle user;
#else
	/// <summary>
	/// Token provided by the Xbox Live SDK/XDK method GetTokenAndSignatureAsync("POST", "https://playfabapi.com/",
	/// "").
	/// </summary>
	const FString xboxToken;
#endif
};

/// <summary>
/// FPFAccountManagementRemoveContactEmailRequest data model. This API removes an existing contact email
/// from the player's profile.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementRemoveContactEmailRequest
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
};

/// <summary>
/// FPFAccountManagementReportPlayerClientRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementReportPlayerClientRequest
{
	/// <summary>
	/// (Optional) Optional additional comment by reporting player.
	/// </summary>
	_Maybenull_ const FString comment;

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
	/// Unique PlayFab identifier of the reported player.
	/// </summary>
	const FString reporteeId;
};

/// <summary>
/// FPFAccountManagementReportPlayerClientResult data model. Players are currently limited to five reports
/// per day. Attempts by a single user account to submit reports beyond five will result in Updated being
/// returned as false.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementReportPlayerClientResult
{
	/// <summary>
	/// The number of remaining reports which may be filed today.
	/// </summary>
	int32 submissionsRemaining;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFAccountManagementSendAccountRecoveryEmailRequest data model. If the account in question is a "temporary"
/// account (for example, one that was created via a call to LoginFromIOSDeviceID), thisfunction will
/// have no effect. Only PlayFab accounts which have valid email addresses will be able to receive a password
/// reset email using this API.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementSendAccountRecoveryEmailRequest
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
	/// User email address attached to their account.
	/// </summary>
	const FString email;

	/// <summary>
	/// (Optional) The email template id of the account recovery email template to send.
	/// </summary>
	_Maybenull_ const FString emailTemplateId;

	/// <summary>
	/// Unique identifier for the title, found in the Settings > Game Properties section of the PlayFab
	/// developer site when a title has been selected.
	/// </summary>
	const FString titleId;
};

/// <summary>
/// FPFAccountManagementUnlinkAndroidDeviceIDRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementUnlinkAndroidDeviceIDRequest
{
	/// <summary>
	/// (Optional) Android device identifier for the user's device. If not specified, the most recently
	/// signed in Android Device ID will be used.
	/// </summary>
	_Maybenull_ const FString androidDeviceId;

	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;
};

/// <summary>
/// FPFAccountManagementUnlinkAppleRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementUnlinkAppleRequest
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
};

/// <summary>
/// FPFAccountManagementClientUnlinkBattleNetAccountRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementClientUnlinkBattleNetAccountRequest
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
};

/// <summary>
/// FPFAccountManagementUnlinkCustomIDRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementUnlinkCustomIDRequest
{
	/// <summary>
	/// (Optional) Custom unique identifier for the user, generated by the title. If not specified, the
	/// most recently signed in Custom ID will be used.
	/// </summary>
	_Maybenull_ const FString customId;

	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;
};

/// <summary>
/// FPFAccountManagementUnlinkFacebookAccountRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementUnlinkFacebookAccountRequest
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
};

/// <summary>
/// FPFAccountManagementUnlinkFacebookInstantGamesIdRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementUnlinkFacebookInstantGamesIdRequest
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
	/// (Optional) Facebook Instant Games identifier for the user. If not specified, the most recently signed
	/// in ID will be used.
	/// </summary>
	_Maybenull_ const FString facebookInstantGamesId;
};

/// <summary>
/// FPFAccountManagementUnlinkGameCenterAccountRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementUnlinkGameCenterAccountRequest
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
};

/// <summary>
/// FPFAccountManagementUnlinkGoogleAccountRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementUnlinkGoogleAccountRequest
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
};

/// <summary>
/// FPFAccountManagementUnlinkGooglePlayGamesServicesAccountRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementUnlinkGooglePlayGamesServicesAccountRequest
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
};

/// <summary>
/// FPFAccountManagementUnlinkIOSDeviceIDRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementUnlinkIOSDeviceIDRequest
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
	/// (Optional) Vendor-specific iOS identifier for the user's device. If not specified, the most recently
	/// signed in iOS Device ID will be used.
	/// </summary>
	_Maybenull_ const FString deviceId;
};

/// <summary>
/// FPFAccountManagementUnlinkKongregateAccountRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementUnlinkKongregateAccountRequest
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
};

/// <summary>
/// FPFAccountManagementClientUnlinkNintendoServiceAccountRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementClientUnlinkNintendoServiceAccountRequest
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
};

/// <summary>
/// FPFAccountManagementClientUnlinkNintendoSwitchDeviceIdRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementClientUnlinkNintendoSwitchDeviceIdRequest
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
	/// (Optional) Nintendo Switch Device identifier for the user. If not specified, the most recently signed
	/// in device ID will be used.
	/// </summary>
	_Maybenull_ const FString nintendoSwitchDeviceId;
};

/// <summary>
/// FPFAccountManagementUnlinkOpenIdConnectRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementUnlinkOpenIdConnectRequest
{
	/// <summary>
	/// A name that identifies which configured OpenID Connect provider relationship to use. Maximum 100
	/// characters.
	/// </summary>
	const FString connectionId;

	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;
};

/// <summary>
/// FPFAccountManagementClientUnlinkPSNAccountRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementClientUnlinkPSNAccountRequest
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
};

/// <summary>
/// FPFAccountManagementUnlinkSteamAccountRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementUnlinkSteamAccountRequest
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
};

/// <summary>
/// FPFAccountManagementUnlinkTwitchAccountRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementUnlinkTwitchAccountRequest
{
	/// <summary>
	/// (Optional) Valid token issued by Twitch. Used to specify which twitch account to unlink from the
	/// profile. By default it uses the one that is present on the profile.
	/// </summary>
	_Maybenull_ const FString accessToken;

	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;
};

/// <summary>
/// FPFAccountManagementClientUnlinkXboxAccountRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementClientUnlinkXboxAccountRequest
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
};

/// <summary>
/// FPFAccountManagementClientUpdateAvatarUrlRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementClientUpdateAvatarUrlRequest
{
	/// <summary>
	/// URL of the avatar image. If empty, it removes the existing avatar URL.
	/// </summary>
	const FString imageUrl;
};

/// <summary>
/// FPFAccountManagementUpdateUserTitleDisplayNameRequest data model. In addition to the PlayFab username,
/// titles can make use of a DisplayName which is also a unique identifier, but specific to the title.
/// This allows for unique names which more closely match the theme or genre of a title, for example.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementUpdateUserTitleDisplayNameRequest
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
	/// New title display name for the user - must be between 3 and 25 characters.
	/// </summary>
	const FString displayName;
};

/// <summary>
/// FPFAccountManagementUpdateUserTitleDisplayNameResult data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementUpdateUserTitleDisplayNameResult
{
	/// <summary>
	/// (Optional) Current title display name for the user (this will be the original display name if the
	/// rename attempt failed).
	/// </summary>
	_Maybenull_ const FString displayName;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFAccountManagementBanRequest data model. Represents a single ban request.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementBanRequest
{
	/// <summary>
	/// (Optional) The duration in hours for the ban. Leave this blank for a permanent ban.
	/// </summary>
	_Maybenull_ TSharedPtr<const uint32> durationInHours;

	/// <summary>
	/// (Optional) IP address to be banned. May affect multiple players.
	/// </summary>
	_Maybenull_ const FString IPAddress;

	/// <summary>
	/// Unique PlayFab assigned ID of the user on whom the operation will be performed.
	/// </summary>
	const FString playFabId;

	/// <summary>
	/// (Optional) The reason for this ban. Maximum 140 characters.
	/// </summary>
	_Maybenull_ const FString reason;

	/// <summary>
	/// (Optional) The family type of the user that should be included in the ban if applicable. May affect
	/// multiple players.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFAccountManagementUserFamilyType> userFamilyType;
};

/// <summary>
/// FPFAccountManagementBanUsersRequest data model. The existence of each user will not be verified.
/// When banning by IP or MAC address, multiple players may be affected, so use this feature with caution.
/// Returns information about the new bans.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementBanUsersRequest
{
	/// <summary>
	/// List of ban requests to be applied. Maximum 100.
	/// </summary>
	TArray<TSharedPtr<const FPFAccountManagementBanRequest>> bans;

	/// <summary>
	/// Count of bans
	/// </summary>
	uint32 bansCount;

	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;
};

/// <summary>
/// FPFAccountManagementBanInfo data model. Contains information for a ban.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementBanInfo
{
	/// <summary>
	/// The active state of this ban. Expired bans may still have this value set to true but they will have
	/// no effect.
	/// </summary>
	bool active;

	/// <summary>
	/// (Optional) The unique Ban Id associated with this ban.
	/// </summary>
	_Maybenull_ const FString banId;

	/// <summary>
	/// (Optional) The time when this ban was applied.
	/// </summary>
	_Maybenull_ TSharedPtr<const FDateTime> created;

	/// <summary>
	/// (Optional) The time when this ban expires. Permanent bans do not have expiration date.
	/// </summary>
	_Maybenull_ TSharedPtr<const FDateTime> expires;

	/// <summary>
	/// (Optional) The IP address on which the ban was applied. May affect multiple players.
	/// </summary>
	_Maybenull_ const FString IPAddress;

	/// <summary>
	/// (Optional) Unique PlayFab assigned ID of the user on whom the operation will be performed.
	/// </summary>
	_Maybenull_ const FString playFabId;

	/// <summary>
	/// (Optional) The reason why this ban was applied.
	/// </summary>
	_Maybenull_ const FString reason;

	/// <summary>
	/// (Optional) The family type of the user that is included in the ban.
	/// </summary>
	_Maybenull_ const FString userFamilyType;
};

/// <summary>
/// FPFAccountManagementBanUsersResult data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementBanUsersResult
{
	/// <summary>
	/// (Optional) Information on the bans that were applied.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFAccountManagementBanInfo>> banData;

	/// <summary>
	/// Count of banData
	/// </summary>
	uint32 banDataCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFAccountManagementDeletePlayerRequest data model. Deletes all data associated with the player,
/// including statistics, custom data, inventory, purchases, virtual currency balances, characters and
/// shared group memberships. Removes the player from all leaderboards and player search indexes. Does
/// not delete PlayStream event history associated with the player. Does not delete the publisher user
/// account that created the player in the title nor associated data such as username, password, email
/// address, account linkages, or friends list. Note, this API queues the player for deletion and returns
/// immediately. It may take several minutes or more before all player data is fully deleted. Until the
/// player data is fully deleted, attempts to recreate the player with the same user account in the same
/// title will fail with the 'AccountDeleted' error. This API must be enabled for use as an option in
/// the game manager website. It is disabled by default.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementDeletePlayerRequest
{
	/// <summary>
	/// Unique PlayFab assigned ID of the user on whom the operation will be performed.
	/// </summary>
	const FString playFabId;
};

/// <summary>
/// FPFAccountManagementGetServerCustomIDsFromPlayFabIDsRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetServerCustomIDsFromPlayFabIDsRequest
{
	/// <summary>
	/// Array of unique PlayFab player identifiers for which the title needs to get server custom identifiers.
	/// Cannot contain more than 25 identifiers.
	/// </summary>
	const TArray<FString> playFabIDs;

	/// <summary>
	/// Count of playFabIDs
	/// </summary>
	uint32 playFabIDsCount;
};

/// <summary>
/// FPFAccountManagementServerCustomIDPlayFabIDPair data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementServerCustomIDPlayFabIDPair
{
	/// <summary>
	/// (Optional) Unique PlayFab identifier.
	/// </summary>
	_Maybenull_ const FString playFabId;

	/// <summary>
	/// (Optional) Unique server custom identifier for this player.
	/// </summary>
	_Maybenull_ const FString serverCustomId;
};

/// <summary>
/// FPFAccountManagementGetServerCustomIDsFromPlayFabIDsResult data model. For a PlayFab account that
/// isn't associated with a server custom identity, ServerCustomId will be null.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetServerCustomIDsFromPlayFabIDsResult
{
	/// <summary>
	/// (Optional) Mapping of server custom player identifiers to PlayFab identifiers.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFAccountManagementServerCustomIDPlayFabIDPair>> data;

	/// <summary>
	/// Count of data
	/// </summary>
	uint32 dataCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFAccountManagementGetUserAccountInfoRequest data model. This API allows for access to details regarding
/// a user in the PlayFab service, usually for purposes of customer support. Note that data returned may
/// be Personally Identifying Information (PII), such as email address, and so care should be taken in
/// how this data is stored and managed. Since this call will always return the relevant information for
/// users who have accessed the title, the recommendation is to not store this data locally.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetUserAccountInfoRequest
{
	/// <summary>
	/// Unique PlayFab assigned ID of the user on whom the operation will be performed.
	/// </summary>
	const FString playFabId;
};

/// <summary>
/// FPFAccountManagementGetUserAccountInfoResult data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetUserAccountInfoResult
{
	/// <summary>
	/// (Optional) Account details for the user whose information was requested.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFUserAccountInfo> userInfo;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFAccountManagementGetUserBansRequest data model. Get all bans for a user, including inactive and
/// expired bans. .
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetUserBansRequest
{
	/// <summary>
	/// Unique PlayFab assigned ID of the user on whom the operation will be performed.
	/// </summary>
	const FString playFabId;
};

/// <summary>
/// FPFAccountManagementGetUserBansResult data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetUserBansResult
{
	/// <summary>
	/// (Optional) Information about the bans.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFAccountManagementBanInfo>> banData;

	/// <summary>
	/// Count of banData
	/// </summary>
	uint32 banDataCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFAccountManagementServerLinkBattleNetAccountRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementServerLinkBattleNetAccountRequest
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
	/// (Optional) If another user is already linked to a specific Battle.net account, unlink the other
	/// user and re-link.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> forceLink;

	/// <summary>
	/// The JSON Web Token (JWT) returned by Battle.net after login.
	/// </summary>
	const FString identityToken;

	/// <summary>
	/// Unique PlayFab assigned ID of the user on whom the operation will be performed.
	/// </summary>
	const FString playFabId;
};

/// <summary>
/// FPFAccountManagementServerLinkNintendoServiceAccountRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementServerLinkNintendoServiceAccountRequest
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
	/// (Optional) If another user is already linked to a specific Nintendo Switch account, unlink the other
	/// user and re-link.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> forceLink;

	/// <summary>
	/// The JSON Web token (JWT) returned by Nintendo after login. Used to validate the request and find
	/// the user ID (Nintendo Switch subject) to link with.
	/// </summary>
	const FString identityToken;

	/// <summary>
	/// Unique PlayFab assigned ID of the user on whom the operation will be performed.
	/// </summary>
	const FString playFabId;
};

/// <summary>
/// FPFAccountManagementLinkNintendoServiceAccountSubjectRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementLinkNintendoServiceAccountSubjectRequest
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
	/// (Optional) If another user is already linked to a specific Nintendo Service Account, unlink the
	/// other user and re-link.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> forceLink;

	/// <summary>
	/// Unique PlayFab assigned ID of the user on whom the operation will be performed.
	/// </summary>
	const FString playFabId;

	/// <summary>
	/// The Nintendo Service Account subject or id to link to the PlayFab user.
	/// </summary>
	const FString subject;
};

/// <summary>
/// FPFAccountManagementServerLinkNintendoSwitchDeviceIdRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementServerLinkNintendoSwitchDeviceIdRequest
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
	/// (Optional) If another user is already linked to the Nintendo Switch Device ID, unlink the other
	/// user and re-link.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> forceLink;

	/// <summary>
	/// Nintendo Switch unique identifier for the user's device.
	/// </summary>
	const FString nintendoSwitchDeviceId;

	/// <summary>
	/// Unique PlayFab assigned ID of the user on whom the operation will be performed.
	/// </summary>
	const FString playFabId;
};

/// <summary>
/// FPFAccountManagementServerLinkPSNAccountRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementServerLinkPSNAccountRequest
{
	/// <summary>
	/// Authentication code provided by the PlayStation :tm: Network.
	/// </summary>
	const FString authCode;

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
	/// (Optional) If another user is already linked to the account, unlink the other user and re-link.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> forceLink;

	/// <summary>
	/// (Optional) Id of the PlayStation :tm: Network issuer environment. If null, defaults to production
	/// environment.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> issuerId;

	/// <summary>
	/// Unique PlayFab assigned ID of the user on whom the operation will be performed.
	/// </summary>
	const FString playFabId;

	/// <summary>
	/// Redirect URI supplied to PlayStation :tm: Network when requesting an auth code.
	/// </summary>
	const FString redirectUri;
};

/// <summary>
/// FPFAccountManagementLinkPSNIdRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementLinkPSNIdRequest
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
	/// (Optional) If another user is already linked to the account, unlink the other user and re-link.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> forceLink;

	/// <summary>
	/// (Optional) Id of the PlayStation :tm: Network issuer environment. If null, defaults to production
	/// environment.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> issuerId;

	/// <summary>
	/// Unique PlayFab assigned ID of the user on whom the operation will be performed.
	/// </summary>
	const FString playFabId;

	/// <summary>
	/// Id of the PlayStation :tm: Network user. Also known as the PSN Account Id.
	/// </summary>
	const FString PSNUserId;
};

/// <summary>
/// FPFAccountManagementLinkServerCustomIdRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementLinkServerCustomIdRequest
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
	/// (Optional) If another user is already linked to the custom ID, unlink the other user and re-link.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> forceLink;

	/// <summary>
	/// Unique PlayFab identifier.
	/// </summary>
	const FString playFabId;

	/// <summary>
	/// Unique server custom identifier for this player.
	/// </summary>
	const FString serverCustomId;
};

/// <summary>
/// FPFAccountManagementLinkSteamIdRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementLinkSteamIdRequest
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
	/// (Optional) If another user is already linked to the account, unlink the other user and re-link.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> forceLink;

	/// <summary>
	/// Unique PlayFab identifier for a user, or null if no PlayFab account is linked to the Xbox Live identifier.
	/// </summary>
	const FString playFabId;

	/// <summary>
	/// Unique Steam identifier for a user.
	/// </summary>
	const FString steamId;
};

/// <summary>
/// FPFAccountManagementServerLinkXboxAccountRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementServerLinkXboxAccountRequest
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
	/// (Optional) If another user is already linked to the account, unlink the other user and re-link.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> forceLink;

	/// <summary>
	/// Unique PlayFab identifier for a user, or null if no PlayFab account is linked to the Xbox Live identifier.
	/// </summary>
	const FString playFabId;

	/// <summary>
	/// Token provided by the Xbox Live SDK/XDK method GetTokenAndSignatureAsync("POST", "https://playfabapi.com/",
	/// "").
	/// </summary>
	const FString xboxToken;
};

/// <summary>
/// FPFAccountManagementRevokeAllBansForUserRequest data model. Setting the active state of all non-expired
/// bans for a user to Inactive. Expired bans with an Active state will be ignored, however. Returns information
/// about applied updates only.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementRevokeAllBansForUserRequest
{
	/// <summary>
	/// Unique PlayFab assigned ID of the user on whom the operation will be performed.
	/// </summary>
	const FString playFabId;
};

/// <summary>
/// FPFAccountManagementRevokeAllBansForUserResult data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementRevokeAllBansForUserResult
{
	/// <summary>
	/// (Optional) Information on the bans that were revoked.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFAccountManagementBanInfo>> banData;

	/// <summary>
	/// Count of banData
	/// </summary>
	uint32 banDataCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFAccountManagementRevokeBansRequest data model. Setting the active state of all bans requested
/// to Inactive regardless of whether that ban has already expired. BanIds that do not exist will be skipped.
/// Returns information about applied updates only. .
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementRevokeBansRequest
{
	/// <summary>
	/// Ids of the bans to be revoked. Maximum 100.
	/// </summary>
	const TArray<FString> banIds;

	/// <summary>
	/// Count of banIds
	/// </summary>
	uint32 banIdsCount;
};

/// <summary>
/// FPFAccountManagementRevokeBansResult data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementRevokeBansResult
{
	/// <summary>
	/// (Optional) Information on the bans that were revoked.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFAccountManagementBanInfo>> banData;

	/// <summary>
	/// Count of banData
	/// </summary>
	uint32 banDataCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFAccountManagementSendCustomAccountRecoveryEmailRequest data model. PlayFab accounts which have
/// valid email address or username will be able to receive a password reset email using this API.The
/// email sent must be an account recovery email template. The username or email can be passed in to send
/// the email.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementSendCustomAccountRecoveryEmailRequest
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
	/// (Optional) User email address attached to their account.
	/// </summary>
	_Maybenull_ const FString email;

	/// <summary>
	/// The email template id of the account recovery email template to send.
	/// </summary>
	const FString emailTemplateId;

	/// <summary>
	/// (Optional) The user's username requesting an account recovery.
	/// </summary>
	_Maybenull_ const FString username;
};

/// <summary>
/// FPFAccountManagementSendEmailFromTemplateRequest data model. Sends an email for only players that
/// have contact emails associated with them. Takes in an email template ID specifyingthe email template
/// to send.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementSendEmailFromTemplateRequest
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
	/// The email template id of the email template to send.
	/// </summary>
	const FString emailTemplateId;

	/// <summary>
	/// Unique PlayFab assigned ID of the user on whom the operation will be performed.
	/// </summary>
	const FString playFabId;
};

/// <summary>
/// FPFAccountManagementServerUnlinkBattleNetAccountRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementServerUnlinkBattleNetAccountRequest
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
/// FPFAccountManagementServerUnlinkNintendoServiceAccountRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementServerUnlinkNintendoServiceAccountRequest
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
/// FPFAccountManagementServerUnlinkNintendoSwitchDeviceIdRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementServerUnlinkNintendoSwitchDeviceIdRequest
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
	/// (Optional) Nintendo Switch Device identifier for the user. If not specified, the most recently signed
	/// in device ID will be used.
	/// </summary>
	_Maybenull_ const FString nintendoSwitchDeviceId;

	/// <summary>
	/// Unique PlayFab assigned ID of the user on whom the operation will be performed.
	/// </summary>
	const FString playFabId;
};

/// <summary>
/// FPFAccountManagementServerUnlinkPSNAccountRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementServerUnlinkPSNAccountRequest
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
/// FPFAccountManagementUnlinkServerCustomIdRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementUnlinkServerCustomIdRequest
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
	/// Unique PlayFab identifier.
	/// </summary>
	const FString playFabId;

	/// <summary>
	/// Unique server custom identifier for this player.
	/// </summary>
	const FString serverCustomId;
};

/// <summary>
/// FPFAccountManagementUnlinkSteamIdRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementUnlinkSteamIdRequest
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
	/// Unique PlayFab identifier for a user, or null if no PlayFab account is linked to the Steam account.
	/// </summary>
	const FString playFabId;
};

/// <summary>
/// FPFAccountManagementServerUnlinkXboxAccountRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementServerUnlinkXboxAccountRequest
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
	/// Unique PlayFab identifier for a user, or null if no PlayFab account is linked to the Xbox Live identifier.
	/// </summary>
	const FString playFabId;
};

/// <summary>
/// FPFAccountManagementServerUpdateAvatarUrlRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementServerUpdateAvatarUrlRequest
{
	/// <summary>
	/// URL of the avatar image. If empty, it removes the existing avatar URL.
	/// </summary>
	const FString imageUrl;

	/// <summary>
	/// Unique PlayFab assigned ID of the user on whom the operation will be performed.
	/// </summary>
	const FString playFabId;
};

/// <summary>
/// FPFAccountManagementUpdateBanRequest data model. Represents a single update ban request.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementUpdateBanRequest
{
	/// <summary>
	/// (Optional) The updated active state for the ban. Null for no change.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> active;

	/// <summary>
	/// The id of the ban to be updated.
	/// </summary>
	const FString banId;

	/// <summary>
	/// (Optional) The updated expiration date for the ban. Null for no change.
	/// </summary>
	_Maybenull_ TSharedPtr<const FDateTime> expires;

	/// <summary>
	/// (Optional) The updated IP address for the ban. Null for no change.
	/// </summary>
	_Maybenull_ const FString IPAddress;

	/// <summary>
	/// (Optional) Whether to make this ban permanent. Set to true to make this ban permanent. This will
	/// not modify Active state.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> permanent;

	/// <summary>
	/// (Optional) The updated reason for the ban to be updated. Maximum 140 characters. Null for no change.
	/// </summary>
	_Maybenull_ const FString reason;

	/// <summary>
	/// (Optional) The updated family type of the user that should be included in the ban. Null for no change.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFAccountManagementUserFamilyType> userFamilyType;
};

/// <summary>
/// FPFAccountManagementUpdateBansRequest data model. For each ban, only updates the values that are
/// set. Leave any value to null for no change. If a ban could not be found, the rest are still applied.
/// Returns information about applied updates only.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementUpdateBansRequest
{
	/// <summary>
	/// List of bans to be updated. Maximum 100.
	/// </summary>
	TArray<TSharedPtr<const FPFAccountManagementUpdateBanRequest>> bans;

	/// <summary>
	/// Count of bans
	/// </summary>
	uint32 bansCount;
};

/// <summary>
/// FPFAccountManagementUpdateBansResult data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementUpdateBansResult
{
	/// <summary>
	/// (Optional) Information on the bans that were updated.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFAccountManagementBanInfo>> banData;

	/// <summary>
	/// Count of banData
	/// </summary>
	uint32 banDataCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFAccountManagementGetTitlePlayersFromXboxLiveIDsRequest data model. Given a collection of Xbox
/// IDs (XUIDs), returns all title player accounts.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetTitlePlayersFromXboxLiveIDsRequest
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
	/// Xbox Sandbox the players had on their Xbox tokens.
	/// </summary>
	const FString sandbox;

	/// <summary>
	/// (Optional) Optional ID of title to get players from, required if calling using a master_player_account.
	/// </summary>
	_Maybenull_ const FString titleId;

	/// <summary>
	/// List of Xbox Live XUIDs.
	/// </summary>
	const TArray<FString> xboxLiveIds;

	/// <summary>
	/// Count of xboxLiveIds
	/// </summary>
	uint32 xboxLiveIdsCount;
};

/// <summary>
/// FPFAccountManagementGetTitlePlayersFromProviderIDsResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementGetTitlePlayersFromProviderIDsResponse
{
	/// <summary>
	/// (Optional) Dictionary of provider identifiers mapped to title_player_account lineage. Missing lineage
	/// indicates the player either doesn't exist or doesn't play the requested title.
	/// </summary>
	_Maybenull_ TMap<const FString, TSharedPtr<const FPFEntityLineage>> titlePlayerAccounts;

	/// <summary>
	/// Count of titlePlayerAccounts
	/// </summary>
	uint32 titlePlayerAccountsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFAccountManagementSetDisplayNameRequest data model. Given an entity profile, will update its display
/// name to the one passed in if the profile's version is equal to the specified value.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementSetDisplayNameRequest
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
	/// (Optional) The new value to be set on Entity Profile's display name.
	/// </summary>
	_Maybenull_ const FString displayName;

	/// <summary>
	/// (Optional) The optional entity to perform this action on. Defaults to the currently logged in entity.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) The expected version of a profile to perform this update on.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> expectedVersion;
};

/// <summary>
/// FPFAccountManagementSetDisplayNameResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFAccountManagementSetDisplayNameResponse
{
	/// <summary>
	/// (Optional) The type of operation that occured on the profile's display name.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFOperationTypes> operationResult;

	/// <summary>
	/// (Optional) The updated version of the profile after the display name update.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> versionNumber;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

// Delegates Declarations

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientAddOrUpdateContactEmailCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientAddUsernamePasswordCompleted, const FPFAccountManagementAddUsernamePasswordResult&, bool);
#endif

DECLARE_DELEGATE_TwoParams(FOnClientGetAccountInfoCompleted, const FPFAccountManagementGetAccountInfoResult&, bool);

DECLARE_DELEGATE_TwoParams(FOnClientGetPlayerCombinedInfoCompleted, const FPFAccountManagementGetPlayerCombinedInfoResult&, bool);

DECLARE_DELEGATE_TwoParams(FOnClientGetPlayerProfileCompleted, const FPFAccountManagementGetPlayerProfileResult&, bool);

DECLARE_DELEGATE_TwoParams(FOnClientGetPlayFabIDsFromBattleNetAccountIdsCompleted, const FPFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsResult&, bool);

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientGetPlayFabIDsFromFacebookIDsCompleted, const FPFAccountManagementGetPlayFabIDsFromFacebookIDsResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientGetPlayFabIDsFromFacebookInstantGamesIdsCompleted, const FPFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientGetPlayFabIDsFromGameCenterIDsCompleted, const FPFAccountManagementGetPlayFabIDsFromGameCenterIDsResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientGetPlayFabIDsFromGoogleIDsCompleted, const FPFAccountManagementGetPlayFabIDsFromGoogleIDsResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientGetPlayFabIDsFromGooglePlayGamesPlayerIDsCompleted, const FPFAccountManagementGetPlayFabIDsFromGooglePlayGamesPlayerIDsResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientGetPlayFabIDsFromKongregateIDsCompleted, const FPFAccountManagementGetPlayFabIDsFromKongregateIDsResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_NINTENDO_SWITCH || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientGetPlayFabIDsFromNintendoServiceAccountIdsCompleted, const FPFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientGetPlayFabIDsFromNintendoSwitchDeviceIdsCompleted, const FPFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_4 || HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_5 || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientGetPlayFabIDsFromPSNAccountIDsCompleted, const FPFAccountManagementGetPlayFabIDsFromPSNAccountIDsResult&, bool);
#endif

DECLARE_DELEGATE_TwoParams(FOnClientGetPlayFabIDsFromPSNOnlineIDsCompleted, const FPFAccountManagementGetPlayFabIDsFromPSNOnlineIDsResult&, bool);

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientGetPlayFabIDsFromSteamIDsCompleted, const FPFAccountManagementGetPlayFabIDsFromSteamIDsResult&, bool);
#endif

DECLARE_DELEGATE_TwoParams(FOnClientGetPlayFabIDsFromSteamNamesCompleted, const FPFAccountManagementGetPlayFabIDsFromSteamNamesResult&, bool);

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientGetPlayFabIDsFromTwitchIDsCompleted, const FPFAccountManagementGetPlayFabIDsFromTwitchIDsResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientGetPlayFabIDsFromXboxLiveIDsCompleted, const FPFAccountManagementGetPlayFabIDsFromXboxLiveIDsResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientLinkAndroidDeviceIDCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientLinkAppleCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK
DECLARE_DELEGATE_TwoParams(FOnClientLinkBattleNetAccountCompleted, const FString&, bool);
#endif

DECLARE_DELEGATE_TwoParams(FOnClientLinkCustomIDCompleted, const FString&, bool);

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientLinkFacebookAccountCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientLinkFacebookInstantGamesIdCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientLinkGameCenterAccountCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientLinkGoogleAccountCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientLinkGooglePlayGamesServicesAccountCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientLinkIOSDeviceIDCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientLinkKongregateCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_NINTENDO_SWITCH || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientLinkNintendoServiceAccountCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientLinkNintendoSwitchDeviceIdCompleted, const FString&, bool);
#endif

DECLARE_DELEGATE_TwoParams(FOnClientLinkOpenIdConnectCompleted, const FString&, bool);

#if HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_4 || HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_5 || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientLinkPSNAccountCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientLinkSteamAccountCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientLinkTwitchCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientLinkXboxAccountCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientRemoveContactEmailCompleted, const FString&, bool);
#endif

DECLARE_DELEGATE_TwoParams(FOnClientReportPlayerCompleted, const FPFAccountManagementReportPlayerClientResult&, bool);

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientSendAccountRecoveryEmailCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientUnlinkAndroidDeviceIDCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientUnlinkAppleCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK
DECLARE_DELEGATE_TwoParams(FOnClientUnlinkBattleNetAccountCompleted, const FString&, bool);
#endif

DECLARE_DELEGATE_TwoParams(FOnClientUnlinkCustomIDCompleted, const FString&, bool);

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientUnlinkFacebookAccountCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientUnlinkFacebookInstantGamesIdCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientUnlinkGameCenterAccountCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientUnlinkGoogleAccountCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientUnlinkGooglePlayGamesServicesAccountCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientUnlinkIOSDeviceIDCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientUnlinkKongregateCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_NINTENDO_SWITCH || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientUnlinkNintendoServiceAccountCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientUnlinkNintendoSwitchDeviceIdCompleted, const FString&, bool);
#endif

DECLARE_DELEGATE_TwoParams(FOnClientUnlinkOpenIdConnectCompleted, const FString&, bool);

#if HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_4 || HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_5 || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientUnlinkPSNAccountCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientUnlinkSteamAccountCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientUnlinkTwitchCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientUnlinkXboxAccountCompleted, const FString&, bool);
#endif

DECLARE_DELEGATE_TwoParams(FOnClientUpdateAvatarUrlCompleted, const FString&, bool);

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnClientUpdateUserTitleDisplayNameCompleted, const FPFAccountManagementUpdateUserTitleDisplayNameResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerBanUsersCompleted, const FPFAccountManagementBanUsersResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerDeletePlayerCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerGetPlayerCombinedInfoCompleted, const FPFAccountManagementGetPlayerCombinedInfoResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerGetPlayerProfileCompleted, const FPFAccountManagementGetPlayerProfileResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK
DECLARE_DELEGATE_TwoParams(FOnServerGetPlayFabIDsFromBattleNetAccountIdsCompleted, const FPFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerGetPlayFabIDsFromFacebookIDsCompleted, const FPFAccountManagementGetPlayFabIDsFromFacebookIDsResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerGetPlayFabIDsFromFacebookInstantGamesIdsCompleted, const FPFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerGetPlayFabIDsFromNintendoServiceAccountIdsCompleted, const FPFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerGetPlayFabIDsFromNintendoSwitchDeviceIdsCompleted, const FPFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerGetPlayFabIDsFromPSNAccountIDsCompleted, const FPFAccountManagementGetPlayFabIDsFromPSNAccountIDsResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK
DECLARE_DELEGATE_TwoParams(FOnServerGetPlayFabIDsFromPSNOnlineIDsCompleted, const FPFAccountManagementGetPlayFabIDsFromPSNOnlineIDsResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerGetPlayFabIDsFromSteamIDsCompleted, const FPFAccountManagementGetPlayFabIDsFromSteamIDsResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK
DECLARE_DELEGATE_TwoParams(FOnServerGetPlayFabIDsFromSteamNamesCompleted, const FPFAccountManagementGetPlayFabIDsFromSteamNamesResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerGetPlayFabIDsFromTwitchIDsCompleted, const FPFAccountManagementGetPlayFabIDsFromTwitchIDsResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerGetPlayFabIDsFromXboxLiveIDsCompleted, const FPFAccountManagementGetPlayFabIDsFromXboxLiveIDsResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerGetServerCustomIDsFromPlayFabIDsCompleted, const FPFAccountManagementGetServerCustomIDsFromPlayFabIDsResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerGetUserAccountInfoCompleted, const FPFAccountManagementGetUserAccountInfoResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerGetUserBansCompleted, const FPFAccountManagementGetUserBansResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK
DECLARE_DELEGATE_TwoParams(FOnServerLinkBattleNetAccountCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerLinkNintendoServiceAccountCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerLinkNintendoServiceAccountSubjectCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerLinkNintendoSwitchDeviceIdCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerLinkPSNAccountCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK
DECLARE_DELEGATE_TwoParams(FOnServerLinkPSNIdCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerLinkServerCustomIdCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerLinkSteamIdCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerLinkXboxAccountCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerRevokeAllBansForUserCompleted, const FPFAccountManagementRevokeAllBansForUserResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerRevokeBansCompleted, const FPFAccountManagementRevokeBansResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerSendCustomAccountRecoveryEmailCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerSendEmailFromTemplateCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK
DECLARE_DELEGATE_TwoParams(FOnServerUnlinkBattleNetAccountCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerUnlinkNintendoServiceAccountCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerUnlinkNintendoSwitchDeviceIdCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerUnlinkPSNAccountCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerUnlinkServerCustomIdCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerUnlinkSteamIdCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerUnlinkXboxAccountCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerUpdateAvatarUrlCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerUpdateBansCompleted, const FPFAccountManagementUpdateBansResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnGetTitlePlayersFromXboxLiveIDsCompleted, const FPFAccountManagementGetTitlePlayersFromProviderIDsResponse&, bool);
#endif

DECLARE_DELEGATE_TwoParams(FOnSetDisplayNameCompleted, const FPFAccountManagementSetDisplayNameResponse&, bool);

#pragma pop_macro("IN")