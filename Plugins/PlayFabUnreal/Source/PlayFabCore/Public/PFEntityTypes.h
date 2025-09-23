#pragma once

#include "PFCoreUnrealTypes.h"

/// <summary>
/// Handle to an authenticated Entity (TitlePlayer, Title, etc.). Contains the auth tokens needed to make PlayFab service
/// calls. When no longer needed, the Entity handle must be closed with PFEntityCloseHandle.
/// </summary>
typedef TSharedPtr<struct PFEntity> FPFEntityHandle;

typedef uint64_t FPFRegistrationToken;

/// <summary>
/// PlayFab EntityToken and its expiration time. Used to authenticate PlayFab service calls.
/// </summary>
typedef struct FPFEntityToken
{
	/// <summary>
	/// The token used to set X-EntityToken for all entity based API calls.
	/// </summary>
	const FString token;

	/// <summary>
	/// (Optional) The time the token will expire, if it is an expiring token, in UTC.
	/// </summary>
	TSharedPtr<const FDateTime> expiration;

} FPFEntityToken;

/// <summary>
/// EntityToken expired event handler. Needed to reauthenticate players in scenarios where the SDK is unable to automatically
/// refresh the cached EntityToken.
/// </summary>
/// <param name="context">Optional context pointer to data used by the event handler.</param>
/// <param name="entityKey">The EntityKey for the Entity whose auth token expired.</param>
/// <returns></returns>
DECLARE_DELEGATE_TwoParams(FPFEntityTokenExpiredDelegate, TSharedPtr<void>, TSharedPtr<const FPFEntityKey>);

/// <summary>
/// A handler invoked every time an Entity is automatically re-authenticated, thus obtaining a new EntityToken. An entity
/// will be automatically re-authenticated prior to its EntityToken expiring.
/// </summary>
/// <param name="context">Optional context pointer to data used by the event handler.</param>
/// <param name="entityKey">The EntityKey for the Entity whose EntityToken expired.</param>
/// <param name="newToken">The new token for the refreshed entity.</param>
/// <returns></returns>
DECLARE_DELEGATE_ThreeParams(FPFEntityTokenRefreshedDelegate, TSharedPtr<void>, TSharedPtr<const FPFEntityKey>, TSharedPtr<const FPFEntityToken>);