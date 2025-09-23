// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include "CoreMinimal.h"
#include "PFEntity.h"
#include "PFServiceConfig.h"
#include "Generated/PFAuthenticationUnrealTypes.h"
#include "ResultMacros.h"

#if defined(PF_UE_GDK_SUPPORT)
#include "GDKHandle.h"
#endif

#if defined(PF_GDK_AVAILABLE)
#include "XUser.h"
#endif


/// <summary>
/// Handle to a PlayFab Local User.
/// </summary>
typedef TSharedPtr<struct PFLocalUser> FPFLocalUserHandle;

#if defined(PF_UE_GDK_SUPPORT) && defined(PF_GDK_AVAILABLE)

/// <summary>
/// Creates a PlayFab Local User to be used when a PlayFab identity is needed but PlayFab login is unavailable (ex. the device is offline). 
/// </summary>
/// <param name="serviceConfigHandle">FPFServiceConfigHandle that will be used to log this user into PlayFab.</param>
/// <param name="user">XUserHandle for the Xbox user.</param>
/// <param name="customContext">Custom context to be associated with the local user.</param>
/// <param name="localUserHandle">TSharedPtr to a FPFLocalUserHandle to write.</param>
/// <returns>Result code for this API operation.  Possible values are S_OK, E_PF_NOT_INITIALIZED, or E_INVALIDARG.</returns>
bool PLAYFABCORE_API FPFLocalUserCreateHandleWithXboxUser(
    _In_ FPFServiceConfigHandle serviceConfigHandle,
    _In_ FGDKUserHandle user,
    _In_opt_ TSharedPtr<void> customContext,
    _Out_ FPFLocalUserHandle& localUserHandle
) noexcept;

#elif defined(PF_GDK_AVAILABLE)

/// <summary>
/// Creates a PlayFab Local User to be used when a PlayFab identity is needed but PlayFab login is unavailable (ex. the device is offline). 
/// </summary>
/// <param name="serviceConfigHandle">FPFServiceConfigHandle that will be used to log this user into PlayFab.</param>
/// <param name="user">XUserHandle for the Xbox user.</param>
/// <param name="customContext">Custom context to be associated with the local user.</param>
/// <param name="localUserHandle">TSharedPtr to a FPFLocalUserHandle to write.</param>
/// <returns>Result code for this API operation.  Possible values are S_OK, E_PF_NOT_INITIALIZED, or E_INVALIDARG.</returns>
bool PLAYFABCORE_API FPFLocalUserCreateHandleWithXboxUser(
    _In_ FPFServiceConfigHandle serviceConfigHandle,
    _In_ XUserHandle user,
    _In_opt_ TSharedPtr<void> customContext,
    _Out_ FPFLocalUserHandle& localUserHandle
) noexcept;

#endif

/// <summary>
/// Creates a PlayFab Local User to be used when a PlayFab identity is needed but PlayFab login is unavailable (ex. the device is offline).
/// It is the title's responsibility to ensure the localId provided is:
/// 1) Locally Unique. If multiple users play the title on the same device (simultaneously or during different play sessions) they must
///    have different localIds.
/// 2) The same for a given user across multiple play sessions.
/// Additionally, the title must provide a custom PFLocalUserLoginHandler. This handler will be called by the SDK to authenticate the user
/// with PlayFab. See <see cref="PFLocalUserLoginHandler"> for more details.
/// </summary>
/// <param name="serviceConfigHandle">FPFServiceConfigHandle that will be used to log this user into PlayFab.</param>
/// <param name="persistedLocalId">Locally unique ID string that identifies the user. ID will be persisted across play sessions.</param>
/// <param name="loginHandle">Custom handler that will be called to log the local user into PlayFab.</param>
/// <param name="customContext">Custom context to be associated with the local user.</param>
/// <param name="localUserHandle">TSharedPtr to a FPFLocalUserHandle to write.</param>
bool PLAYFABCORE_API FPFLocalUserCreateHandleWithPersistedLocalId(
    _In_ FPFServiceConfigHandle serviceConfigHandle,
    _In_ FString& persistedLocalId,
    _In_opt_ TSharedPtr<void> customContext,
    _Out_ FPFLocalUserHandle& localUserHandle
) noexcept;

/// <summary>
/// Duplicates a FPFLocalUserHandle.
/// </summary>
/// <param name="localUserHandle">LocalUser handle to duplicate.</param>
/// <param name="duplicatedHandle">Duplicated handle.</param>
bool PLAYFABCORE_API FPFLocalUserDuplicateHandle(
    _In_ FPFLocalUserHandle localUserHandle,
    _Out_ FPFLocalUserHandle& duplicatedHandle
) noexcept;

/// <summary>
/// Closes a FPFLocalUserHandle.
/// </summary>
/// <param name="handle">LocalUser handle to close.</param>
bool PLAYFABCORE_API FPFLocalUserCloseHandle(
    _In_ FPFLocalUserHandle localUserHandle
) noexcept;

/// <summary>
/// Gets the unique local Id for user.
/// </summary>
/// <param name="localUserHandle">User to get the ID for.</param>
/// <param name="localUserId">Returned localId string.</param>
/// <returns></returns>
bool PLAYFABCORE_API FPFLocalUserGetLocalId(
    _In_ FPFLocalUserHandle localUserHandle,
    _Out_ FString& localUserId
) noexcept;

/// <summary>
/// Get the custom context that was associated with a local user when it was created.
/// </summary>
/// <param name="localUserHandle">FPFLocalUserHandle for the user.</param>
/// <param name="customContext">Custom context TSharedPtr to write.</param>
/// <returns>Result code for this API operation.</returns>
bool PLAYFABCORE_API FPFLocalUserGetCustomContext(
    _In_ FPFLocalUserHandle localUserHandle,
    _Out_ TSharedPtr<void> customContext
) noexcept;

/// <summary>
/// Get the PFEntityHandle associated with the local user if there is one. If the user isn't logged into PlayFab and there isn't an
/// associated handle, E_PF_CORE_LOCAL_USER_NOT_LOGGED_IN will be returned.
/// </summary>
/// <param name="localUserHandle">FPFLocalUserHandle for the user.</param>
/// <param name="entityHandle">Entity handle TSharedPtr to set.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// If the call succeeds, the populated PFEntityHandle is managed by TSharedPtr with automatic cleanup.
/// </remarks>
bool PLAYFABCORE_API FPFLocalUserTryGetEntityHandle(
    _In_ FPFLocalUserHandle localUserHandle,
    _Out_ FPFEntityHandle& entityHandle
) noexcept;

/// <summary>
/// Attempts to login the local user with the default PlayFab login provider, or the custom login handler provided when the local
/// user was created.
/// </summary>
/// <param name="localUserHandle">PFLocalUserHandle for the user.</param>
/// <param name="createAccount">Whether or not to automatically create a PlayFab account if one doesn't yet exist for the user.</param>
/// <param name="delegate">Delegate to be called upon completion.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// The resulting PFEntityHandle will automatically be associated with the local user who is logging in.
/// </remarks>
bool PLAYFABCORE_API FPFLocalUserLoginAsync(
    _In_ FPFLocalUserHandle localUserHandle,
    _In_ bool createAccount,
    _In_ FOnPFAuthenticationLoginCompleteDelegate delegate
) noexcept;