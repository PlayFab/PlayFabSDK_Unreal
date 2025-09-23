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
/// ExternalFriendSources enum.
/// </summary>
enum class FPFFriendsExternalFriendSources : uint32
{
	None = 0x0,
	Steam = 0x1,
	Facebook = 0x2,
	Xbox = 0x4,
	Psn = 0x8,
	All = 0x10
};

DEFINE_ENUM_FLAG_OPERATORS(FPFFriendsExternalFriendSources);

/// <summary>
/// FPFFriendsClientAddFriendRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFFriendsClientAddFriendRequest
{
	/// <summary>
	/// (Optional) Email address of the user to attempt to add to the local user's friend list.
	/// </summary>
	_Maybenull_ const FString friendEmail;

	/// <summary>
	/// (Optional) PlayFab identifier of the user to attempt to add to the local user's friend list.
	/// </summary>
	_Maybenull_ const FString friendPlayFabId;

	/// <summary>
	/// (Optional) Title-specific display name of the user to attempt to add to the local user's friend
	/// list.
	/// </summary>
	_Maybenull_ const FString friendTitleDisplayName;

	/// <summary>
	/// (Optional) PlayFab username of the user to attempt to add to the local user's friend list.
	/// </summary>
	_Maybenull_ const FString friendUsername;
};

/// <summary>
/// FPFFriendsAddFriendResult data model.
/// </summary>
struct PLAYFABSERVICES_API FPFFriendsAddFriendResult
{
	/// <summary>
	/// True if the friend request was processed successfully.
	/// </summary>
	bool created;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFFriendsClientGetFriendsListRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFFriendsClientGetFriendsListRequest
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
	/// (Optional) Indicates which other platforms' friends should be included in the response. In HTTP,
	/// it is represented as a comma-separated list of platforms.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFFriendsExternalFriendSources> externalPlatformFriends;

	/// <summary>
	/// (Optional) If non-null, this determines which properties of the resulting player profiles to return.
	/// For API calls from the client, only the allowed client profile properties for the title may be requested.
	/// These allowed properties are configured in the Game Manager "Client Profile Options" tab in the "Settings"
	/// section.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFPlayerProfileViewConstraints> profileConstraints;

#if defined(PF_GDK_AVAILABLE) && defined(PF_UE_GDK_SUPPORT)
	/// <summary>
	/// (Optional) FGDKUserHandle if Xbox friends should be included.
	/// </summary>
	FGDKUserHandle user;
#elif defined(PF_GDK_AVAILABLE)
    /// <summary>
    /// (Optional) XUserHandle if Xbox friends should be included.
    /// </summary>
    XUserHandle user;
#else
	/// <summary>
	/// (Optional) Xbox token if Xbox friends should be included. Requires Xbox be configured on PlayFab.
	/// </summary>
	_Maybenull_ const FString xboxToken;
#endif
};

/// <summary>
/// FPFFriendsFriendInfo data model.
/// </summary>
struct PLAYFABSERVICES_API FPFFriendsFriendInfo
{
	/// <summary>
	/// (Optional) Available Facebook information (if the user and connected Facebook friend both have PlayFab
	/// Accounts in the same title).
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFUserFacebookInfo> facebookInfo;

	/// <summary>
	/// (Optional) PlayFab unique identifier for this friend.
	/// </summary>
	_Maybenull_ const FString friendPlayFabId;

	/// <summary>
	/// (Optional) Available Game Center information (if the user and connected Game Center friend both
	/// have PlayFab Accounts in the same title).
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFUserGameCenterInfo> gameCenterInfo;

	/// <summary>
	/// (Optional) The profile of the user, if requested.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFPlayerProfileModel> profile;

	/// <summary>
	/// (Optional) Available PlayStation :tm: Network information, if the user connected PlayStation :tm
	/// Network friend both have PlayFab Accounts in the same title.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFUserPsnInfo> PSNInfo;

	/// <summary>
	/// (Optional) Available Steam information (if the user and connected Steam friend both have PlayFab
	/// Accounts in the same title).
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFUserSteamInfo> steamInfo;

	/// <summary>
	/// (Optional) Tags which have been associated with this friend.
	/// </summary>
	_Maybenull_ const TArray<FString> tags;

	/// <summary>
	/// Count of tags
	/// </summary>
	uint32 tagsCount;

	/// <summary>
	/// (Optional) Title-specific display name for this friend.
	/// </summary>
	_Maybenull_ const FString titleDisplayName;

	/// <summary>
	/// (Optional) PlayFab unique username for this friend.
	/// </summary>
	_Maybenull_ const FString username;

	/// <summary>
	/// (Optional) Available Xbox information, (if the user and connected Xbox Live friend both have PlayFab
	/// Accounts in the same title).
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFUserXboxInfo> xboxInfo;
};

/// <summary>
/// FPFFriendsGetFriendsListResult data model. If any additional services are queried for the user's
/// friends, those friends who also have a PlayFab account registered for the title will be returned in
/// the results. For Facebook, user has to have logged into the title's Facebook app recently, and only
/// friends who also plays this game will be included. Note: If the user authenticated with AuthenticationToken
/// when calling LoginWithFacebook, instead of AccessToken, an empty list will be returned. For Xbox Live,
/// user has to have logged into the Xbox Live recently, and only friends who also play this game will
/// be included.
/// </summary>
struct PLAYFABSERVICES_API FPFFriendsGetFriendsListResult
{
	/// <summary>
	/// (Optional) Array of friends found.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFFriendsFriendInfo>> friends;

	/// <summary>
	/// Count of friends
	/// </summary>
	uint32 friendsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFFriendsClientRemoveFriendRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFFriendsClientRemoveFriendRequest
{
	/// <summary>
	/// PlayFab identifier of the friend account which is to be removed.
	/// </summary>
	const FString friendPlayFabId;
};

/// <summary>
/// FPFFriendsClientSetFriendTagsRequest data model. This operation is not additive. It will completely
/// replace the tag list for the specified user. Please note that only users in the PlayFab friends list
/// can be assigned tags. Attempting to set a tag on a friend only included in the friends list from a
/// social site integration (such as Facebook or Steam) will return the AccountNotFound error.
/// </summary>
struct PLAYFABSERVICES_API FPFFriendsClientSetFriendTagsRequest
{
	/// <summary>
	/// PlayFab identifier of the friend account to which the tag(s) should be applied.
	/// </summary>
	const FString friendPlayFabId;

	/// <summary>
	/// Array of tags to set on the friend account.
	/// </summary>
	const TArray<FString> tags;

	/// <summary>
	/// Count of tags
	/// </summary>
	uint32 tagsCount;
};

/// <summary>
/// FPFFriendsServerAddFriendRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFFriendsServerAddFriendRequest
{
	/// <summary>
	/// (Optional) Email address of the user being added.
	/// </summary>
	_Maybenull_ const FString friendEmail;

	/// <summary>
	/// (Optional) The PlayFab identifier of the user being added.
	/// </summary>
	_Maybenull_ const FString friendPlayFabId;

	/// <summary>
	/// (Optional) Title-specific display name of the user to being added.
	/// </summary>
	_Maybenull_ const FString friendTitleDisplayName;

	/// <summary>
	/// (Optional) The PlayFab username of the user being added.
	/// </summary>
	_Maybenull_ const FString friendUsername;

	/// <summary>
	/// PlayFab identifier of the player to add a new friend.
	/// </summary>
	const FString playFabId;
};

/// <summary>
/// FPFFriendsServerGetFriendsListRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFFriendsServerGetFriendsListRequest
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
	/// (Optional) Indicates which other platforms' friends should be included in the response. In HTTP,
	/// it is represented as a comma-separated list of platforms.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFFriendsExternalFriendSources> externalPlatformFriends;

	/// <summary>
	/// PlayFab identifier of the player whose friend list to get.
	/// </summary>
	const FString playFabId;

	/// <summary>
	/// (Optional) If non-null, this determines which properties of the resulting player profiles to return.
	/// For API calls from the client, only the allowed client profile properties for the title may be requested.
	/// These allowed properties are configured in the Game Manager "Client Profile Options" tab in the "Settings"
	/// section.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFPlayerProfileViewConstraints> profileConstraints;

	/// <summary>
	/// (Optional) Xbox token if Xbox friends should be included. Requires Xbox be configured on PlayFab.
	/// </summary>
	_Maybenull_ const FString xboxToken;
};

/// <summary>
/// FPFFriendsServerRemoveFriendRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFFriendsServerRemoveFriendRequest
{
	/// <summary>
	/// PlayFab identifier of the friend account which is to be removed.
	/// </summary>
	const FString friendPlayFabId;

	/// <summary>
	/// Unique PlayFab assigned ID of the user on whom the operation will be performed.
	/// </summary>
	const FString playFabId;
};

/// <summary>
/// FPFFriendsServerSetFriendTagsRequest data model. This operation is not additive. It will completely
/// replace the tag list for the specified user. Please note that only users in the PlayFab friends list
/// can be assigned tags. Attempting to set a tag on a friend only included in the friends list from a
/// social site integration (such as Facebook or Steam) will return the AccountNotFound error.
/// </summary>
struct PLAYFABSERVICES_API FPFFriendsServerSetFriendTagsRequest
{
	/// <summary>
	/// PlayFab identifier of the friend account to which the tag(s) should be applied.
	/// </summary>
	const FString friendPlayFabId;

	/// <summary>
	/// PlayFab identifier of the player whose friend is to be updated.
	/// </summary>
	const FString playFabId;

	/// <summary>
	/// Array of tags to set on the friend account.
	/// </summary>
	const TArray<FString> tags;

	/// <summary>
	/// Count of tags
	/// </summary>
	uint32 tagsCount;
};

// Delegates Declarations

DECLARE_DELEGATE_TwoParams(FOnClientAddFriendCompleted, const FPFFriendsAddFriendResult&, bool);

DECLARE_DELEGATE_TwoParams(FOnClientGetFriendsListCompleted, const FPFFriendsGetFriendsListResult&, bool);

DECLARE_DELEGATE_TwoParams(FOnClientRemoveFriendCompleted, const FString&, bool);

DECLARE_DELEGATE_TwoParams(FOnClientSetFriendTagsCompleted, const FString&, bool);

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerAddFriendCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerGetFriendsListCompleted, const FPFFriendsGetFriendsListResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerRemoveFriendCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerSetFriendTagsCompleted, const FString&, bool);
#endif

#pragma pop_macro("IN")