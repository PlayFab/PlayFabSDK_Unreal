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
/// FPFLocalizationGetLanguageListRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFLocalizationGetLanguageListRequest
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
/// FPFLocalizationGetLanguageListResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFLocalizationGetLanguageListResponse
{
	/// <summary>
	/// (Optional) The list of allowed languages, in BCP47 two-letter format.
	/// </summary>
	_Maybenull_ const TArray<FString> languageList;

	/// <summary>
	/// Count of languageList
	/// </summary>
	uint32 languageListCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

// Delegates Declarations

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnGetLanguageListCompleted, const FPFLocalizationGetLanguageListResponse&, bool);
#endif

#pragma pop_macro("IN")