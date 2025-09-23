// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#if defined(PF_GDK_AVAILABLE) || defined(PF_UE_GDK_SUPPORT)

#include "PFCoreUnrealTypes.h"

#if defined(PF_UE_GDK_SUPPORT)
#include "GDKHandle.h"
#endif

extern "C"
{

/// <summary>
/// FPFAuthenticationLoginWithXUserRequest data model. If this is the first time a user has signed in with
/// the Xbox Live account and CreateAccount is set to true, a new PlayFab account will be created and
/// linked to the Xbox Live account. In this case, no email or username will be associated with the PlayFab
/// account. Otherwise, if no PlayFab account is linked to the Xbox Live account, an error indicating
/// this will be returned, so that the title can guide the user through creation of a PlayFab account.
/// Request object for PFAuthenticationLoginWithXUserAsync.
/// </summary>
typedef struct FPFAuthenticationLoginWithXUserRequest
{
    /// <summary>
    /// Automatically create a PlayFab account if one is not currently linked to this ID.
    /// </summary>
    bool createAccount;

    /// <summary>
    /// (Optional) The optional custom tags associated with the request (e.g. build number, external
    /// trace identifiers, etc.).
    /// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

    /// <summary>
    /// Count of customTags
    /// </summary>
	uint32 customTagsCount;

    /// <summary>
    /// (Optional) Flags for which pieces of info to return for the user.
    /// </summary>
	_Maybenull_ TSharedPtr<const FPFGetPlayerCombinedInfoRequestParams> infoRequestParameters;

    /// <summary>
    /// (Optional) Player secret that is used to verify API request signatures (Enterprise Only).
    /// </summary>
	_Maybenull_ const FString playerSecret;

#if defined(PF_UE_GDK_SUPPORT)
    /// <summary>
    /// FGDKUserHandle used for Xbox authentication.
    /// </summary>
    FGDKUserHandle user;
#else
    /// <summary>
    /// XUserHandle used for Xbox authentication.
    /// </summary>
    XUserHandle user;
#endif

} FPFAuthenticationLoginWithXUserRequest;

}

#endif
