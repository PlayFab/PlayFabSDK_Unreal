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
DECLARE_DELEGATE_TwoParams(FOnServerGetPlayerTagsCompleted, const FPFSegmentsGetPlayerTagsResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerRemovePlayerTagCompleted, const FString&, bool);
#endif

#pragma pop_macro("IN")