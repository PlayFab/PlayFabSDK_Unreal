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
/// FPFTitleDataManagementGetPublisherDataRequest data model. This API is designed to return publisher-specific
/// values which can be read, but not written to, by the client. This data is shared across all titles
/// assigned to a particular publisher, and can be used for cross-game coordination. Only titles assigned
/// to a publisher can use this API. For more information email helloplayfab@microsoft.com. Note that
/// there may up to a minute delay in between updating title data and this API call returning the newest
/// value.
/// </summary>
struct PLAYFABSERVICES_API FPFTitleDataManagementGetPublisherDataRequest
{
	/// <summary>
	///  array of keys to get back data from the Publisher data blob, set by the admin tools.
	/// </summary>
	const TArray<FString> keys;

	/// <summary>
	/// Count of keys
	/// </summary>
	uint32 keysCount;
};

/// <summary>
/// FPFTitleDataManagementGetPublisherDataResult data model.
/// </summary>
struct PLAYFABSERVICES_API FPFTitleDataManagementGetPublisherDataResult
{
	/// <summary>
	/// (Optional) A dictionary object of key / value pairs.
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> data;

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
/// FPFTitleDataManagementGetTimeResult data model. Time is always returned as Coordinated Universal
/// Time (UTC).
/// </summary>
struct PLAYFABSERVICES_API FPFTitleDataManagementGetTimeResult
{
	/// <summary>
	/// Current server time when the request was received, in UTC.
	/// </summary>
	FDateTime time;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFTitleDataManagementGetTitleDataRequest data model. This API is designed to return title specific
/// values which can be read, but not written to, by the client. For example, a developer could choose
/// to store values which modify the user experience, such as enemy spawn rates, weapon strengths, movement
/// speeds, etc. This allows a developer to update the title without the need to create, test, and ship
/// a new build. If the player belongs to an experiment variant that uses title data overrides, the overrides
/// are applied automatically and returned with the title data. Note that there may up to a minute delay
/// in between updating title data and this API call returning the newest value.
/// </summary>
struct PLAYFABSERVICES_API FPFTitleDataManagementGetTitleDataRequest
{
	/// <summary>
	/// (Optional) Specific keys to search for in the title data (leave null to get all keys).
	/// </summary>
	_Maybenull_ const TArray<FString> keys;

	/// <summary>
	/// Count of keys
	/// </summary>
	uint32 keysCount;

	/// <summary>
	/// (Optional) Optional field that specifies the name of an override. This value is ignored when used
	/// by the game client; otherwise, the overrides are applied automatically to the title data.
	/// </summary>
	_Maybenull_ const FString overrideLabel;
};

/// <summary>
/// FPFTitleDataManagementGetTitleDataResult data model.
/// </summary>
struct PLAYFABSERVICES_API FPFTitleDataManagementGetTitleDataResult
{
	/// <summary>
	/// (Optional) A dictionary object of key / value pairs.
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> data;

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
/// FPFTitleDataManagementGetTitleNewsRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFTitleDataManagementGetTitleNewsRequest
{
	/// <summary>
	/// (Optional) Limits the results to the last n entries. Defaults to 10 if not set.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> count;
};

/// <summary>
/// FPFTitleDataManagementTitleNewsItem data model.
/// </summary>
struct PLAYFABSERVICES_API FPFTitleDataManagementTitleNewsItem
{
	/// <summary>
	/// (Optional) News item text.
	/// </summary>
	_Maybenull_ const FString body;

	/// <summary>
	/// (Optional) Unique identifier of news item.
	/// </summary>
	_Maybenull_ const FString newsId;

	/// <summary>
	/// Date and time when the news item was posted.
	/// </summary>
	FDateTime timestamp;

	/// <summary>
	/// (Optional) Title of the news item.
	/// </summary>
	_Maybenull_ const FString title;
};

/// <summary>
/// FPFTitleDataManagementGetTitleNewsResult data model.
/// </summary>
struct PLAYFABSERVICES_API FPFTitleDataManagementGetTitleNewsResult
{
	/// <summary>
	/// (Optional) Array of news items.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFTitleDataManagementTitleNewsItem>> news;

	/// <summary>
	/// Count of news
	/// </summary>
	uint32 newsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFTitleDataManagementSetPublisherDataRequest data model. This API is designed to store publisher-specific
/// values which can be read, but not written to, by the client. This data is shared across all titles
/// assigned to a particular publisher, and can be used for cross-game coordination. Only titles assigned
/// to a publisher can use this API. This operation is additive. If a Key does not exist in the current
/// dataset, it will be added with the specified Value. If it already exists, the Value for that key will
/// be overwritten with the new Value. For more information email helloplayfab@microsoft.com.
/// </summary>
struct PLAYFABSERVICES_API FPFTitleDataManagementSetPublisherDataRequest
{
	/// <summary>
	/// Key we want to set a value on (note, this is additive - will only replace an existing key's value
	/// if they are the same name.) Keys are trimmed of whitespace. Keys may not begin with the '!' character.
	/// </summary>
	const FString key;

	/// <summary>
	/// (Optional) New value to set. Set to null to remove a value.
	/// </summary>
	_Maybenull_ const FString value;
};

/// <summary>
/// FPFTitleDataManagementSetTitleDataRequest data model. This API is designed to store title specific
/// values which can be read, but not written to, by the client. For example, a developer could choose
/// to store values which modify the user experience, such as enemy spawn rates, weapon strengths, movement
/// speeds, etc. This allows a developer to update the title without the need to create, test, and ship
/// a new build. This operation is additive. If a Key does not exist in the current dataset, it will be
/// added with the specified Value. If it already exists, the Value for that key will be overwritten with
/// the new Value.
/// </summary>
struct PLAYFABSERVICES_API FPFTitleDataManagementSetTitleDataRequest
{
	/// <summary>
	/// Key we want to set a value on (note, this is additive - will only replace an existing key's value
	/// if they are the same name.) Keys are trimmed of whitespace. Keys may not begin with the '!' character.
	/// </summary>
	const FString key;

	/// <summary>
	/// (Optional) New value to set. Set to null to remove a value.
	/// </summary>
	_Maybenull_ const FString value;
};

// Delegates Declarations

DECLARE_DELEGATE_TwoParams(FOnClientGetPublisherDataCompleted, const FPFTitleDataManagementGetPublisherDataResult&, bool);

DECLARE_DELEGATE_TwoParams(FOnClientGetTimeCompleted, const FPFTitleDataManagementGetTimeResult&, bool);

DECLARE_DELEGATE_TwoParams(FOnClientGetTitleDataCompleted, const FPFTitleDataManagementGetTitleDataResult&, bool);

DECLARE_DELEGATE_TwoParams(FOnClientGetTitleNewsCompleted, const FPFTitleDataManagementGetTitleNewsResult&, bool);

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerGetPublisherDataCompleted, const FPFTitleDataManagementGetPublisherDataResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerGetTimeCompleted, const FPFTitleDataManagementGetTimeResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerGetTitleDataCompleted, const FPFTitleDataManagementGetTitleDataResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerGetTitleInternalDataCompleted, const FPFTitleDataManagementGetTitleDataResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerGetTitleNewsCompleted, const FPFTitleDataManagementGetTitleNewsResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerSetPublisherDataCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerSetTitleDataCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerSetTitleInternalDataCompleted, const FString&, bool);
#endif

#pragma pop_macro("IN")