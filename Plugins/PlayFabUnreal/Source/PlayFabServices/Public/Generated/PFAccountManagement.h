// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include "CoreMinimal.h"
#include "XAsyncTaskManager.h"
#include "PFAccountManagementAsyncTasks.h"

THIRD_PARTY_INCLUDES_START
#include <playfab/services/PFServices.h>
THIRD_PARTY_INCLUDES_END

extern "C"
{
/// <summary>
/// Adds or updates a contact email to the player's profile.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// This API adds a contact email to the player's profile. If the player's profile already contains a
/// contact email, it will update the contact email to the email address specified.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be one of global PlayFab Service errors. See doc page "Handling PlayFab Errors"
/// for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientAddOrUpdateContactEmailAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementAddOrUpdateContactEmailRequest* request,
	_Inout_ FOnClientAddOrUpdateContactEmailCompleted delegate
) noexcept;
#endif

/// <summary>
/// Adds playfab username/password auth to an existing account created via an anonymous auth method,
/// e.g. automatic device ID login.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Linux and macOS.
/// See also ClientLoginWithEmailAddressAsync, ClientLoginWithPlayFabAsync.
///
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientAddUsernamePasswordGetResultSize"/>
/// and <see cref="PFAccountManagementClientAddUsernamePasswordGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientAddUsernamePasswordAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementAddUsernamePasswordRequest* request,
	_Inout_ FOnClientAddUsernamePasswordCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves the user's PlayFab account details
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientGetAccountInfoGetResultSize"/>
/// and <see cref="PFAccountManagementClientGetAccountInfoGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFAccountManagementClientGetAccountInfoAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementGetAccountInfoRequest* request,
	_Inout_ FOnClientGetAccountInfoCompleted delegate
) noexcept;

/// <summary>
/// Retrieves all of the user's different kinds of info.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientGetPlayerCombinedInfoGetResultSize"/>
/// and <see cref="PFAccountManagementClientGetPlayerCombinedInfoGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFAccountManagementClientGetPlayerCombinedInfoAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementGetPlayerCombinedInfoRequest* request,
	_Inout_ FOnClientGetPlayerCombinedInfoCompleted delegate
) noexcept;

/// <summary>
/// Retrieves the player's profile
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// This API allows for access to details regarding a user in the PlayFab service, usually for purposes
/// of customer support. Note that data returned may be Personally Identifying Information (PII), such
/// as email address, and so care should be taken in how this data is stored and managed. Since this call
/// will always return the relevant information for users who have accessed the title, the recommendation
/// is to not store this data locally.
///
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientGetPlayerProfileGetResultSize"/>
/// and <see cref="PFAccountManagementClientGetPlayerProfileGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFAccountManagementClientGetPlayerProfileAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementGetPlayerProfileRequest* request,
	_Inout_ FOnClientGetPlayerProfileCompleted delegate
) noexcept;

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Battle.net account identifiers.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientGetPlayFabIDsFromBattleNetAccountIdsGetResultSize"/>
/// and <see cref="PFAccountManagementClientGetPlayFabIDsFromBattleNetAccountIdsGetResult"/> to get the
/// result.
/// </remarks>
bool PLAYFABSERVICES_API FPFAccountManagementClientGetPlayFabIDsFromBattleNetAccountIdsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsRequest* request,
	_Inout_ FOnClientGetPlayFabIDsFromBattleNetAccountIdsCompleted delegate
) noexcept;

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Facebook identifiers.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, Android, iOS, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientGetPlayFabIDsFromFacebookIDsGetResultSize"/>
/// and <see cref="PFAccountManagementClientGetPlayFabIDsFromFacebookIDsGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientGetPlayFabIDsFromFacebookIDsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromFacebookIDsRequest* request,
	_Inout_ FOnClientGetPlayFabIDsFromFacebookIDsCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Facebook Instant Game identifiers.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientGetPlayFabIDsFromFacebookInstantGamesIdsGetResultSize"/>
/// and <see cref="PFAccountManagementClientGetPlayFabIDsFromFacebookInstantGamesIdsGetResult"/> to get
/// the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientGetPlayFabIDsFromFacebookInstantGamesIdsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsRequest* request,
	_Inout_ FOnClientGetPlayFabIDsFromFacebookInstantGamesIdsCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Game Center identifiers (referenced
/// in the Game Center Programming Guide as the Player Identifier).
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, iOS, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientGetPlayFabIDsFromGameCenterIDsGetResultSize"/>
/// and <see cref="PFAccountManagementClientGetPlayFabIDsFromGameCenterIDsGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientGetPlayFabIDsFromGameCenterIDsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromGameCenterIDsRequest* request,
	_Inout_ FOnClientGetPlayFabIDsFromGameCenterIDsCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Google identifiers. The Google identifiers
/// are the IDs for the user accounts, available as 'id' in the Google+ People API calls.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, Android, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientGetPlayFabIDsFromGoogleIDsGetResultSize"/>
/// and <see cref="PFAccountManagementClientGetPlayFabIDsFromGoogleIDsGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientGetPlayFabIDsFromGoogleIDsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromGoogleIDsRequest* request,
	_Inout_ FOnClientGetPlayFabIDsFromGoogleIDsCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Google Play Games identifiers. The
/// Google Play Games identifiers are the IDs for the user accounts, available as 'playerId' in the Google
/// Play Games Services - Players API calls.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, Android, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientGetPlayFabIDsFromGooglePlayGamesPlayerIDsGetResultSize"/>
/// and <see cref="PFAccountManagementClientGetPlayFabIDsFromGooglePlayGamesPlayerIDsGetResult"/> to get
/// the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientGetPlayFabIDsFromGooglePlayGamesPlayerIDsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromGooglePlayGamesPlayerIDsRequest* request,
	_Inout_ FOnClientGetPlayFabIDsFromGooglePlayGamesPlayerIDsCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Kongregate identifiers. The Kongregate
/// identifiers are the IDs for the user accounts, available as 'user_id' from the Kongregate API methods(ex:
/// http://developers.kongregate.com/docs/client/getUserId).
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientGetPlayFabIDsFromKongregateIDsGetResultSize"/>
/// and <see cref="PFAccountManagementClientGetPlayFabIDsFromKongregateIDsGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientGetPlayFabIDsFromKongregateIDsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromKongregateIDsRequest* request,
	_Inout_ FOnClientGetPlayFabIDsFromKongregateIDsCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Nintendo Service Account identifiers.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Nintendo Switch, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientGetPlayFabIDsFromNintendoServiceAccountIdsGetResultSize"/>
/// and <see cref="PFAccountManagementClientGetPlayFabIDsFromNintendoServiceAccountIdsGetResult"/> to
/// get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_NINTENDO_SWITCH || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientGetPlayFabIDsFromNintendoServiceAccountIdsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsRequest* request,
	_Inout_ FOnClientGetPlayFabIDsFromNintendoServiceAccountIdsCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Nintendo Switch Device identifiers.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientGetPlayFabIDsFromNintendoSwitchDeviceIdsGetResultSize"/>
/// and <see cref="PFAccountManagementClientGetPlayFabIDsFromNintendoSwitchDeviceIdsGetResult"/> to get
/// the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientGetPlayFabIDsFromNintendoSwitchDeviceIdsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsRequest* request,
	_Inout_ FOnClientGetPlayFabIDsFromNintendoSwitchDeviceIdsCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of PlayStation :tm: Network identifiers.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Sony PlayStation®, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientGetPlayFabIDsFromPSNAccountIDsGetResultSize"/>
/// and <see cref="PFAccountManagementClientGetPlayFabIDsFromPSNAccountIDsGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_4 || HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_5 || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientGetPlayFabIDsFromPSNAccountIDsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromPSNAccountIDsRequest* request,
	_Inout_ FOnClientGetPlayFabIDsFromPSNAccountIDsCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of PlayStation :tm: Network identifiers.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientGetPlayFabIDsFromPSNOnlineIDsGetResultSize"/>
/// and <see cref="PFAccountManagementClientGetPlayFabIDsFromPSNOnlineIDsGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFAccountManagementClientGetPlayFabIDsFromPSNOnlineIDsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromPSNOnlineIDsRequest* request,
	_Inout_ FOnClientGetPlayFabIDsFromPSNOnlineIDsCompleted delegate
) noexcept;

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Steam identifiers. The Steam identifiers
/// are the profile IDs for the user accounts, available as SteamId in the Steamworks Community API calls.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientGetPlayFabIDsFromSteamIDsGetResultSize"/>
/// and <see cref="PFAccountManagementClientGetPlayFabIDsFromSteamIDsGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientGetPlayFabIDsFromSteamIDsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromSteamIDsRequest* request,
	_Inout_ FOnClientGetPlayFabIDsFromSteamIDsCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Steam identifiers. The Steam identifiers
/// are persona names.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientGetPlayFabIDsFromSteamNamesGetResultSize"/>
/// and <see cref="PFAccountManagementClientGetPlayFabIDsFromSteamNamesGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFAccountManagementClientGetPlayFabIDsFromSteamNamesAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromSteamNamesRequest* request,
	_Inout_ FOnClientGetPlayFabIDsFromSteamNamesCompleted delegate
) noexcept;

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Twitch identifiers. The Twitch identifiers
/// are the IDs for the user accounts, available as '_id' from the Twitch API methods (ex: https://github.com/justintv/Twitch-API/blob/master/v3_resources/users.md#get-usersuser).
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientGetPlayFabIDsFromTwitchIDsGetResultSize"/>
/// and <see cref="PFAccountManagementClientGetPlayFabIDsFromTwitchIDsGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientGetPlayFabIDsFromTwitchIDsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromTwitchIDsRequest* request,
	_Inout_ FOnClientGetPlayFabIDsFromTwitchIDsCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of XboxLive identifiers.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientGetPlayFabIDsFromXboxLiveIDsGetResultSize"/>
/// and <see cref="PFAccountManagementClientGetPlayFabIDsFromXboxLiveIDsGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientGetPlayFabIDsFromXboxLiveIDsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromXboxLiveIDsRequest* request,
	_Inout_ FOnClientGetPlayFabIDsFromXboxLiveIDsCompleted delegate
) noexcept;
#endif

/// <summary>
/// Links the Android device identifier to the user's PlayFab account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Linux and macOS.
/// See also ClientLoginWithAndroidDeviceIDAsync, ClientUnlinkAndroidDeviceIDAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_LINKED_DEVICE_ALREADY_CLAIMED or any of the global PlayFab Service errors.
/// See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientLinkAndroidDeviceIDAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementLinkAndroidDeviceIDRequest* request,
	_Inout_ FOnClientLinkAndroidDeviceIDCompleted delegate
) noexcept;
#endif

/// <summary>
/// Links the Apple account associated with the token to the user's PlayFab account.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Linux, iOS, and macOS.
/// See also ClientLoginWithAppleAsync, ClientUnlinkAppleAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_APPLE_NOT_ENABLED_FOR_TITLE, E_PF_INVALID_IDENTITY_PROVIDER_ID, E_PF_LINKED_IDENTIFIER_ALREADY_CLAIMED,
/// E_PF_TOKEN_SIGNING_KEY_NOT_FOUND or any of the global PlayFab Service errors. See doc page "Handling
/// PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientLinkAppleAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementLinkAppleRequest* request,
	_Inout_ FOnClientLinkAppleCompleted delegate
) noexcept;
#endif

/// <summary>
/// Links the Battle.net account associated with the token to the user's PlayFab account.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows.
/// See also ClientLoginWithBattleNetAsync, ClientUnlinkBattleNetAccountAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_BATTLE_NET_NOT_ENABLED_FOR_TITLE, E_PF_INVALID_IDENTITY_PROVIDER_ID,
/// E_PF_LINKED_IDENTIFIER_ALREADY_CLAIMED, E_PF_TOKEN_SIGNING_KEY_NOT_FOUND or any of the global PlayFab
/// Service errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFAccountManagementClientLinkBattleNetAccountAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementClientLinkBattleNetAccountRequest* request,
	_Inout_ FOnClientLinkBattleNetAccountCompleted delegate
) noexcept;
#endif

/// <summary>
/// Links the custom identifier, generated by the title, to the user's PlayFab account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// See also ClientLoginWithCustomIDAsync, ClientUnlinkCustomIDAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_LINKED_IDENTIFIER_ALREADY_CLAIMED or any of the global PlayFab Service
/// errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
bool PLAYFABSERVICES_API FPFAccountManagementClientLinkCustomIDAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementLinkCustomIDRequest* request,
	_Inout_ FOnClientLinkCustomIDCompleted delegate
) noexcept;

/// <summary>
/// Links the Facebook account associated with the provided Facebook access token to the user's PlayFab
/// account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Linux, Android, iOS, and macOS.
/// Facebook sign-in is accomplished using the Facebook User Access Token. More information on the Token
/// can be found in the Facebook developer documentation (https://developers.facebook.com/docs/facebook-login/access-tokens/).
/// In Unity, for example, the Token is available as AccessToken in the Facebook SDK ScriptableObject
/// FB. Note that titles should never re-use the same Facebook applications between PlayFab Title IDs,
/// as Facebook provides unique user IDs per application and doing so can result in issues with the Facebook
/// ID for the user in their PlayFab account information. If you must re-use an application in a new PlayFab
/// Title ID, please be sure to first unlink all accounts from Facebook, or delete all users in the first
/// Title ID. See also ClientLoginWithFacebookAsync, ClientUnlinkFacebookAccountAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_ALREADY_LINKED, E_PF_ACCOUNT_NOT_FOUND, E_PF_FACEBOOK_API_ERROR,
/// E_PF_INVALID_FACEBOOK_TOKEN, E_PF_LINKED_ACCOUNT_ALREADY_CLAIMED or any of the global PlayFab Service
/// errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientLinkFacebookAccountAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementLinkFacebookAccountRequest* request,
	_Inout_ FOnClientLinkFacebookAccountCompleted delegate
) noexcept;
#endif

/// <summary>
/// Links the Facebook Instant Games Id to the user's PlayFab account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Linux and macOS.
/// See also ClientLoginWithFacebookInstantGamesIdAsync, ClientUnlinkFacebookInstantGamesIdAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_FACEBOOK_INSTANT_GAMES_AUTH_NOT_CONFIGURED_FOR_TITLE, E_PF_INVALID_FACEBOOK_INSTANT_GAMES_SIGNATURE,
/// E_PF_LINKED_IDENTIFIER_ALREADY_CLAIMED or any of the global PlayFab Service errors. See doc page "Handling
/// PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientLinkFacebookInstantGamesIdAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementLinkFacebookInstantGamesIdRequest* request,
	_Inout_ FOnClientLinkFacebookInstantGamesIdCompleted delegate
) noexcept;
#endif

/// <summary>
/// Links the Game Center account associated with the provided Game Center ID to the user's PlayFab account.
/// Logging in with a Game Center ID is insecure if you do not include the optional PublicKeyUrl, Salt,
/// Signature, and Timestamp parameters in this request. It is recommended you require these parameters
/// on all Game Center calls by going to the Apple Add-ons page in the PlayFab Game Manager and enabling
/// the 'Require secure authentication only for this app' option.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Linux, iOS, and macOS.
/// See also ClientUnlinkGameCenterAccountAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_ALREADY_LINKED, E_PF_GAME_CENTER_AUTHENTICATION_FAILED, E_PF_INVALID_GAME_CENTER_AUTH_REQUEST,
/// E_PF_LINKED_ACCOUNT_ALREADY_CLAIMED or any of the global PlayFab Service errors. See doc page "Handling
/// PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientLinkGameCenterAccountAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementLinkGameCenterAccountRequest* request,
	_Inout_ FOnClientLinkGameCenterAccountCompleted delegate
) noexcept;
#endif

/// <summary>
/// Links the currently signed-in user account to their Google account, using their Google account credentials
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Linux, Android, and macOS.
/// Google sign-in is accomplished by obtaining a Google OAuth 2.0 credential using the Google sign-in
/// for Android APIs on the device and passing it to this API. See also ClientLoginWithGoogleAccountAsync,
/// ClientUnlinkGoogleAccountAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_ALREADY_LINKED, E_PF_GOOGLE_O_AUTH_ERROR, E_PF_GOOGLE_O_AUTH_NO_ID_TOKEN_INCLUDED_IN_RESPONSE,
/// E_PF_GOOGLE_O_AUTH_NOT_CONFIGURED_FOR_TITLE, E_PF_INVALID_GOOGLE_TOKEN, E_PF_LINKED_ACCOUNT_ALREADY_CLAIMED
/// or any of the global PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details
/// on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientLinkGoogleAccountAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementLinkGoogleAccountRequest* request,
	_Inout_ FOnClientLinkGoogleAccountCompleted delegate
) noexcept;
#endif

/// <summary>
/// Links the currently signed-in user account to their Google Play Games account, using their Google
/// Play Games account credentials
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Linux, Android, and macOS.
/// Google Play Games sign-in is accomplished by obtaining a Google OAuth 2.0 credential using the Google
/// Play Games sign-in for Android APIs on the device and passing it to this API. See also ClientLoginWithGooglePlayGamesServicesAsync,
/// ClientUnlinkGooglePlayGamesServicesAccountAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_ALREADY_LINKED, E_PF_GOOGLE_O_AUTH_ERROR, E_PF_GOOGLE_O_AUTH_NOT_CONFIGURED_FOR_TITLE,
/// E_PF_INVALID_GOOGLE_PLAY_GAMES_SERVER_AUTH_CODE, E_PF_INVALID_GOOGLE_TOKEN, E_PF_LINKED_ACCOUNT_ALREADY_CLAIMED
/// or any of the global PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details
/// on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientLinkGooglePlayGamesServicesAccountAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementLinkGooglePlayGamesServicesAccountRequest* request,
	_Inout_ FOnClientLinkGooglePlayGamesServicesAccountCompleted delegate
) noexcept;
#endif

/// <summary>
/// Links the vendor-specific iOS device identifier to the user's PlayFab account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Linux and macOS.
/// See also ClientLoginWithIOSDeviceIDAsync, ClientUnlinkIOSDeviceIDAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_LINKED_DEVICE_ALREADY_CLAIMED or any of the global PlayFab Service errors.
/// See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientLinkIOSDeviceIDAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementLinkIOSDeviceIDRequest* request,
	_Inout_ FOnClientLinkIOSDeviceIDCompleted delegate
) noexcept;
#endif

/// <summary>
/// Links the Kongregate identifier to the user's PlayFab account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Linux and macOS.
/// See also ClientLoginWithKongregateAsync, ClientUnlinkKongregateAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_FEATURE_NOT_CONFIGURED_FOR_TITLE, E_PF_INVALID_KONGREGATE_TOKEN, E_PF_LINKED_ACCOUNT_ALREADY_CLAIMED
/// or any of the global PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details
/// on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientLinkKongregateAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementLinkKongregateAccountRequest* request,
	_Inout_ FOnClientLinkKongregateCompleted delegate
) noexcept;
#endif

/// <summary>
/// Links the Nintendo account associated with the token to the user's PlayFab account.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Nintendo Switch, Linux, and macOS.
/// See also ClientLoginWithNintendoServiceAccountAsync, ClientUnlinkNintendoServiceAccountAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_INVALID_IDENTITY_PROVIDER_ID, E_PF_LINKED_IDENTIFIER_ALREADY_CLAIMED,
/// E_PF_NINTENDO_SWITCH_NOT_ENABLED_FOR_TITLE or any of the global PlayFab Service errors. See doc page
/// "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_NINTENDO_SWITCH || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientLinkNintendoServiceAccountAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementClientLinkNintendoServiceAccountRequest* request,
	_Inout_ FOnClientLinkNintendoServiceAccountCompleted delegate
) noexcept;
#endif

/// <summary>
/// Links the NintendoSwitchDeviceId to the user's PlayFab account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Linux and macOS.
/// See also ClientLoginWithNintendoSwitchDeviceIdAsync, ClientUnlinkNintendoSwitchDeviceIdAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_LINKED_IDENTIFIER_ALREADY_CLAIMED or any of the global PlayFab Service
/// errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientLinkNintendoSwitchDeviceIdAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementClientLinkNintendoSwitchDeviceIdRequest* request,
	_Inout_ FOnClientLinkNintendoSwitchDeviceIdCompleted delegate
) noexcept;
#endif

/// <summary>
/// Links an OpenID Connect account to a user's PlayFab account, based on an existing relationship between
/// a title and an Open ID Connect provider and the OpenId Connect JWT from that provider.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// See also ClientLoginWithOpenIdConnectAsync, ClientUnlinkOpenIdConnectAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_INVALID_IDENTITY_PROVIDER_ID, E_PF_LINKED_IDENTIFIER_ALREADY_CLAIMED
/// or any of the global PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details
/// on error handling.
/// </remarks>
bool PLAYFABSERVICES_API FPFAccountManagementClientLinkOpenIdConnectAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementLinkOpenIdConnectRequest* request,
	_Inout_ FOnClientLinkOpenIdConnectCompleted delegate
) noexcept;

/// <summary>
/// Links the PlayStation :tm: Network account associated with the provided access code to the user's
/// PlayFab account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Sony PlayStation®, Linux, and macOS.
/// See also ClientLoginWithPSNAsync, ClientUnlinkPSNAccountAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_ALREADY_LINKED, E_PF_INVALID_PSN_AUTH_CODE, E_PF_INVALID_PSN_AUTH_CODE,
/// E_PF_INVALID_PSN_ISSUER_ID, E_PF_LINKED_ACCOUNT_ALREADY_CLAIMED, E_PF_PSN_INACCESSIBLE or any of the
/// global PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_4 || HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_5 || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientLinkPSNAccountAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementClientLinkPSNAccountRequest* request,
	_Inout_ FOnClientLinkPSNAccountCompleted delegate
) noexcept;
#endif

/// <summary>
/// Links the Steam account associated with the provided Steam authentication ticket to the user's PlayFab
/// account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// Steam authentication is accomplished with the Steam Session Ticket. More information on the Ticket
/// can be found in the Steamworks SDK, here: https://partner.steamgames.com/documentation/auth (requires
/// sign-in). NOTE: For Steam authentication to work, the title must be configured with the Steam Application
/// ID and Publisher Key in the PlayFab Game Manager (under Properties). Information on creating a Publisher
/// Key (referred to as the Secret Key in PlayFab) for your title can be found here: https://partner.steamgames.com/documentation/webapi#publisherkey.
/// See also ClientLoginWithSteamAsync, ClientUnlinkSteamAccountAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_ALREADY_LINKED, E_PF_INVALID_STEAM_TICKET, E_PF_LINKED_ACCOUNT_ALREADY_CLAIMED,
/// E_PF_STEAM_NOT_ENABLED_FOR_TITLE, E_PF_STEAM_USER_NOT_FOUND or any of the global PlayFab Service errors.
/// See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientLinkSteamAccountAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementLinkSteamAccountRequest* request,
	_Inout_ FOnClientLinkSteamAccountCompleted delegate
) noexcept;
#endif

/// <summary>
/// Links the Twitch account associated with the token to the user's PlayFab account.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Linux and macOS.
/// See also ClientLoginWithTwitchAsync, ClientUnlinkTwitchAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_ALREADY_LINKED, E_PF_FEATURE_NOT_CONFIGURED_FOR_TITLE, E_PF_INVALID_TWITCH_TOKEN,
/// E_PF_LINKED_ACCOUNT_ALREADY_CLAIMED, E_PF_TWITCH_RESPONSE_ERROR or any of the global PlayFab Service
/// errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientLinkTwitchAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementLinkTwitchAccountRequest* request,
	_Inout_ FOnClientLinkTwitchCompleted delegate
) noexcept;
#endif

/// <summary>
/// Links the Xbox Live account associated with the provided access code to the user's PlayFab account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also ClientLoginWithXboxAsync, ClientUnlinkXboxAccountAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_ALREADY_LINKED, E_PF_EXPIRED_XBOX_LIVE_TOKEN, E_PF_INVALID_XBOX_LIVE_TOKEN,
/// E_PF_LINKED_ACCOUNT_ALREADY_CLAIMED or any of the global PlayFab Service errors. See doc page "Handling
/// PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientLinkXboxAccountAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementClientLinkXboxAccountRequest* request,
	_Inout_ FOnClientLinkXboxAccountCompleted delegate
) noexcept;
#endif

/// <summary>
/// Removes a contact email from the player's profile.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// This API removes an existing contact email from the player's profile.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be one of global PlayFab Service errors. See doc page "Handling PlayFab Errors"
/// for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientRemoveContactEmailAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementRemoveContactEmailRequest* request,
	_Inout_ FOnClientRemoveContactEmailCompleted delegate
) noexcept;
#endif

/// <summary>
/// Submit a report for another player (due to bad bahavior, etc.), so that customer service representatives
/// for the title can take action concerning potentially toxic players.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientReportPlayerGetResult"/>
/// to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFAccountManagementClientReportPlayerAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementReportPlayerClientRequest* request,
	_Inout_ FOnClientReportPlayerCompleted delegate
) noexcept;

/// <summary>
/// Forces an email to be sent to the registered email address for the user's account, with a link allowing
/// the user to change the password.If an account recovery email template ID is provided, an email using
/// the custom email template will be used.
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Linux and macOS.
/// If the account in question is a 'temporary' account (for example, one that was created via a call
/// to LoginFromIOSDeviceID), thisfunction will have no effect. Only PlayFab accounts which have valid
/// email addresses will be able to receive a password reset email using this API.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_EMAIL_RECIPIENT_BLACKLISTED, E_PF_INVALID_EMAIL_ADDRESS, E_PF_NO_CONTACT_EMAIL_ADDRESS_FOUND,
/// E_PF_SMTP_ADDON_NOT_ENABLED or any of the global PlayFab Service errors. See doc page "Handling PlayFab
/// Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientSendAccountRecoveryEmailAsync(
	_In_ FPFServiceConfigHandle ServiceConfigHandle,
	_In_ const FPFAccountManagementSendAccountRecoveryEmailRequest* request,
	_Inout_ FOnClientSendAccountRecoveryEmailCompleted delegate
) noexcept;
#endif

/// <summary>
/// Unlinks the related Android device identifier from the user's PlayFab account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Linux and macOS.
/// See also ClientLinkAndroidDeviceIDAsync, ClientLoginWithAndroidDeviceIDAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED, E_PF_DEVICE_NOT_LINKED or any of the global PlayFab
/// Service errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientUnlinkAndroidDeviceIDAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementUnlinkAndroidDeviceIDRequest* request,
	_Inout_ FOnClientUnlinkAndroidDeviceIDCompleted delegate
) noexcept;
#endif

/// <summary>
/// Unlinks the related Apple account from the user's PlayFab account.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Linux, iOS, and macOS.
/// See also ClientLinkAppleAsync, ClientLoginWithAppleAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED, E_PF_APPLE_NOT_ENABLED_FOR_TITLE or any of the global
/// PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientUnlinkAppleAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementUnlinkAppleRequest* request,
	_Inout_ FOnClientUnlinkAppleCompleted delegate
) noexcept;
#endif

/// <summary>
/// Unlinks the related Battle.net account from the user's PlayFab account.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows.
/// See also ClientLinkBattleNetAccountAsync, ClientLoginWithBattleNetAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED, E_PF_BATTLE_NET_NOT_ENABLED_FOR_TITLE or any of
/// the global PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details on error
/// handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFAccountManagementClientUnlinkBattleNetAccountAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementClientUnlinkBattleNetAccountRequest* request,
	_Inout_ FOnClientUnlinkBattleNetAccountCompleted delegate
) noexcept;
#endif

/// <summary>
/// Unlinks the related custom identifier from the user's PlayFab account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// See also ClientLinkCustomIDAsync, ClientLoginWithCustomIDAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED, E_PF_CUSTOM_ID_NOT_LINKED or any of the global PlayFab
/// Service errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
bool PLAYFABSERVICES_API FPFAccountManagementClientUnlinkCustomIDAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementUnlinkCustomIDRequest* request,
	_Inout_ FOnClientUnlinkCustomIDCompleted delegate
) noexcept;

/// <summary>
/// Unlinks the related Facebook account from the user's PlayFab account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Linux, Android, iOS, and macOS.
/// See also ClientLinkFacebookAccountAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED or any of the global PlayFab Service errors. See
/// doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientUnlinkFacebookAccountAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementUnlinkFacebookAccountRequest* request,
	_Inout_ FOnClientUnlinkFacebookAccountCompleted delegate
) noexcept;
#endif

/// <summary>
/// Unlinks the related Facebook Instant Game Ids from the user's PlayFab account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Linux and macOS.
/// See also ClientLinkFacebookInstantGamesIdAsync, ClientLoginWithFacebookInstantGamesIdAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED, E_PF_FACEBOOK_INSTANT_GAMES_ID_NOT_LINKED or any
/// of the global PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details on error
/// handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientUnlinkFacebookInstantGamesIdAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementUnlinkFacebookInstantGamesIdRequest* request,
	_Inout_ FOnClientUnlinkFacebookInstantGamesIdCompleted delegate
) noexcept;
#endif

/// <summary>
/// Unlinks the related Game Center account from the user's PlayFab account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Linux, iOS, and macOS.
/// See also ClientLinkGameCenterAccountAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED or any of the global PlayFab Service errors. See
/// doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientUnlinkGameCenterAccountAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementUnlinkGameCenterAccountRequest* request,
	_Inout_ FOnClientUnlinkGameCenterAccountCompleted delegate
) noexcept;
#endif

/// <summary>
/// Unlinks the related Google account from the user's PlayFab account (https://developers.google.com/android/reference/com/google/android/gms/auth/GoogleAuthUtil#public-methods).
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Linux, Android, and macOS.
/// See also ClientLinkGoogleAccountAsync, ClientLoginWithGoogleAccountAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED or any of the global PlayFab Service errors. See
/// doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientUnlinkGoogleAccountAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementUnlinkGoogleAccountRequest* request,
	_Inout_ FOnClientUnlinkGoogleAccountCompleted delegate
) noexcept;
#endif

/// <summary>
/// Unlinks the related Google Play Games account from the user's PlayFab account.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Linux, Android, and macOS.
/// See also ClientLinkGooglePlayGamesServicesAccountAsync, ClientLoginWithGooglePlayGamesServicesAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED or any of the global PlayFab Service errors. See
/// doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientUnlinkGooglePlayGamesServicesAccountAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementUnlinkGooglePlayGamesServicesAccountRequest* request,
	_Inout_ FOnClientUnlinkGooglePlayGamesServicesAccountCompleted delegate
) noexcept;
#endif

/// <summary>
/// Unlinks the related iOS device identifier from the user's PlayFab account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Linux and macOS.
/// See also ClientLinkIOSDeviceIDAsync, ClientLoginWithIOSDeviceIDAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED, E_PF_DEVICE_NOT_LINKED or any of the global PlayFab
/// Service errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientUnlinkIOSDeviceIDAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementUnlinkIOSDeviceIDRequest* request,
	_Inout_ FOnClientUnlinkIOSDeviceIDCompleted delegate
) noexcept;
#endif

/// <summary>
/// Unlinks the related Kongregate identifier from the user's PlayFab account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Linux and macOS.
/// See also ClientLinkKongregateAsync, ClientLoginWithKongregateAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED or any of the global PlayFab Service errors. See
/// doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientUnlinkKongregateAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementUnlinkKongregateAccountRequest* request,
	_Inout_ FOnClientUnlinkKongregateCompleted delegate
) noexcept;
#endif

/// <summary>
/// Unlinks the related Nintendo account from the user's PlayFab account.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Nintendo Switch, Linux, and macOS.
/// See also ClientLinkNintendoServiceAccountAsync, ClientLoginWithNintendoServiceAccountAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED, E_PF_NINTENDO_SWITCH_NOT_ENABLED_FOR_TITLE or any
/// of the global PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details on error
/// handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_NINTENDO_SWITCH || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientUnlinkNintendoServiceAccountAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementClientUnlinkNintendoServiceAccountRequest* request,
	_Inout_ FOnClientUnlinkNintendoServiceAccountCompleted delegate
) noexcept;
#endif

/// <summary>
/// Unlinks the related NintendoSwitchDeviceId from the user's PlayFab account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Linux and macOS.
/// See also ClientLinkNintendoSwitchDeviceIdAsync, ClientLoginWithNintendoSwitchDeviceIdAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED, E_PF_NINTENDO_SWITCH_DEVICE_ID_NOT_LINKED or any
/// of the global PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details on error
/// handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientUnlinkNintendoSwitchDeviceIdAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementClientUnlinkNintendoSwitchDeviceIdRequest* request,
	_Inout_ FOnClientUnlinkNintendoSwitchDeviceIdCompleted delegate
) noexcept;
#endif

/// <summary>
/// Unlinks an OpenID Connect account from a user's PlayFab account, based on the connection ID of an
/// existing relationship between a title and an Open ID Connect provider.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// See also ClientLinkOpenIdConnectAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED or any of the global PlayFab Service errors. See
/// doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
bool PLAYFABSERVICES_API FPFAccountManagementClientUnlinkOpenIdConnectAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementUnlinkOpenIdConnectRequest* request,
	_Inout_ FOnClientUnlinkOpenIdConnectCompleted delegate
) noexcept;

/// <summary>
/// Unlinks the related PlayStation :tm: Network account from the user's PlayFab account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Sony PlayStation®, Linux, and macOS.
/// See also ClientLinkPSNAccountAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED or any of the global PlayFab Service errors. See
/// doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_4 || HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_5 || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientUnlinkPSNAccountAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementClientUnlinkPSNAccountRequest* request,
	_Inout_ FOnClientUnlinkPSNAccountCompleted delegate
) noexcept;
#endif

/// <summary>
/// Unlinks the related Steam account from the user's PlayFab account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also ClientLinkSteamAccountAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED or any of the global PlayFab Service errors. See
/// doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientUnlinkSteamAccountAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementUnlinkSteamAccountRequest* request,
	_Inout_ FOnClientUnlinkSteamAccountCompleted delegate
) noexcept;
#endif

/// <summary>
/// Unlinks the related Twitch account from the user's PlayFab account.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Linux and macOS.
/// See also ClientLinkTwitchAsync, ClientLoginWithTwitchAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED, E_PF_FEATURE_NOT_CONFIGURED_FOR_TITLE, E_PF_INVALID_TWITCH_TOKEN
/// or any of the global PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details
/// on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientUnlinkTwitchAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementUnlinkTwitchAccountRequest* request,
	_Inout_ FOnClientUnlinkTwitchCompleted delegate
) noexcept;
#endif

/// <summary>
/// Unlinks the related Xbox Live account from the user's PlayFab account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also ClientLinkXboxAccountAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED, E_PF_INVALID_XBOX_LIVE_TOKEN or any of the global
/// PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientUnlinkXboxAccountAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementClientUnlinkXboxAccountRequest* request,
	_Inout_ FOnClientUnlinkXboxAccountCompleted delegate
) noexcept;
#endif

/// <summary>
/// Update the avatar URL of the player
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be one of global PlayFab Service errors. See doc page "Handling PlayFab Errors"
/// for more details on error handling.
/// </remarks>
bool PLAYFABSERVICES_API FPFAccountManagementClientUpdateAvatarUrlAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementClientUpdateAvatarUrlRequest* request,
	_Inout_ FOnClientUpdateAvatarUrlCompleted delegate
) noexcept;

/// <summary>
/// Updates the title specific display name for the user
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// In addition to the PlayFab username, titles can make use of a DisplayName which is also a unique
/// identifier, but specific to the title. This allows for unique names which more closely match the theme
/// or genre of a title, for example.
///
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientUpdateUserTitleDisplayNameGetResultSize"/>
/// and <see cref="PFAccountManagementClientUpdateUserTitleDisplayNameGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientUpdateUserTitleDisplayNameAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementUpdateUserTitleDisplayNameRequest* request,
	_Inout_ FOnClientUpdateUserTitleDisplayNameCompleted delegate
) noexcept;
#endif

/// <summary>
/// Bans users by PlayFab ID with optional IP address, or MAC address for the provided game.
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// The existence of each user will not be verified. When banning by IP or MAC address, multiple players
/// may be affected, so use this feature with caution. Returns information about the new bans. See also
/// ServerGetUserBansAsync, ServerRevokeAllBansForUserAsync, ServerRevokeBansAsync, ServerUpdateBansAsync.
///
/// When the asynchronous task is complete, call <see cref="PFAccountManagementServerBanUsersGetResultSize"/>
/// and <see cref="PFAccountManagementServerBanUsersGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerBanUsersAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementBanUsersRequest* request,
	_Inout_ FOnServerBanUsersCompleted delegate
) noexcept;
#endif

/// <summary>
/// Removes a user's player account from a title and deletes all associated data
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// Deletes all data associated with the player, including statistics, custom data, inventory, purchases,
/// virtual currency balances, characters and shared group memberships. Removes the player from all leaderboards
/// and player search indexes. Does not delete PlayStream event history associated with the player. Does
/// not delete the publisher user account that created the player in the title nor associated data such
/// as username, password, email address, account linkages, or friends list. Note, this API queues the
/// player for deletion and returns immediately. It may take several minutes or more before all player
/// data is fully deleted. Until the player data is fully deleted, attempts to recreate the player with
/// the same user account in the same title will fail with the 'AccountDeleted' error. This API must be
/// enabled for use as an option in the game manager website. It is disabled by default.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_API_NOT_ENABLED_FOR_GAME_SERVER_ACCESS or any of the global PlayFab
/// Service errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerDeletePlayerAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementDeletePlayerRequest* request,
	_Inout_ FOnServerDeletePlayerCompleted delegate
) noexcept;
#endif

/// <summary>
/// Returns whatever info is requested in the response for the user. Note that PII (like email address,
/// facebook id) may be returned. All parameters default to false.
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementServerGetPlayerCombinedInfoGetResultSize"/>
/// and <see cref="PFAccountManagementServerGetPlayerCombinedInfoGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerGetPlayerCombinedInfoAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementGetPlayerCombinedInfoRequest* request,
	_Inout_ FOnServerGetPlayerCombinedInfoCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves the player's profile
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// This API allows for access to details regarding a user in the PlayFab service, usually for purposes
/// of customer support. Note that data returned may be Personally Identifying Information (PII), such
/// as email address, and so care should be taken in how this data is stored and managed. Since this call
/// will always return the relevant information for users who have accessed the title, the recommendation
/// is to not store this data locally.
///
/// When the asynchronous task is complete, call <see cref="PFAccountManagementServerGetPlayerProfileGetResultSize"/>
/// and <see cref="PFAccountManagementServerGetPlayerProfileGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerGetPlayerProfileAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementGetPlayerProfileRequest* request,
	_Inout_ FOnServerGetPlayerProfileCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Battle.net account identifiers.
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementServerGetPlayFabIDsFromBattleNetAccountIdsGetResultSize"/>
/// and <see cref="PFAccountManagementServerGetPlayFabIDsFromBattleNetAccountIdsGetResult"/> to get the
/// result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFAccountManagementServerGetPlayFabIDsFromBattleNetAccountIdsAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsRequest* request,
	_Inout_ FOnServerGetPlayFabIDsFromBattleNetAccountIdsCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Facebook identifiers.
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementServerGetPlayFabIDsFromFacebookIDsGetResultSize"/>
/// and <see cref="PFAccountManagementServerGetPlayFabIDsFromFacebookIDsGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerGetPlayFabIDsFromFacebookIDsAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromFacebookIDsRequest* request,
	_Inout_ FOnServerGetPlayFabIDsFromFacebookIDsCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Facebook Instant Games identifiers.
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementServerGetPlayFabIDsFromFacebookInstantGamesIdsGetResultSize"/>
/// and <see cref="PFAccountManagementServerGetPlayFabIDsFromFacebookInstantGamesIdsGetResult"/> to get
/// the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerGetPlayFabIDsFromFacebookInstantGamesIdsAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsRequest* request,
	_Inout_ FOnServerGetPlayFabIDsFromFacebookInstantGamesIdsCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Nintendo Service Account identifiers.
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementServerGetPlayFabIDsFromNintendoServiceAccountIdsGetResultSize"/>
/// and <see cref="PFAccountManagementServerGetPlayFabIDsFromNintendoServiceAccountIdsGetResult"/> to
/// get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerGetPlayFabIDsFromNintendoServiceAccountIdsAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsRequest* request,
	_Inout_ FOnServerGetPlayFabIDsFromNintendoServiceAccountIdsCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Nintendo Switch Device identifiers.
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementServerGetPlayFabIDsFromNintendoSwitchDeviceIdsGetResultSize"/>
/// and <see cref="PFAccountManagementServerGetPlayFabIDsFromNintendoSwitchDeviceIdsGetResult"/> to get
/// the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerGetPlayFabIDsFromNintendoSwitchDeviceIdsAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsRequest* request,
	_Inout_ FOnServerGetPlayFabIDsFromNintendoSwitchDeviceIdsCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of PlayStation :tm: Network identifiers.
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementServerGetPlayFabIDsFromPSNAccountIDsGetResultSize"/>
/// and <see cref="PFAccountManagementServerGetPlayFabIDsFromPSNAccountIDsGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerGetPlayFabIDsFromPSNAccountIDsAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromPSNAccountIDsRequest* request,
	_Inout_ FOnServerGetPlayFabIDsFromPSNAccountIDsCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of PlayStation :tm: Network identifiers.
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementServerGetPlayFabIDsFromPSNOnlineIDsGetResultSize"/>
/// and <see cref="PFAccountManagementServerGetPlayFabIDsFromPSNOnlineIDsGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFAccountManagementServerGetPlayFabIDsFromPSNOnlineIDsAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromPSNOnlineIDsRequest* request,
	_Inout_ FOnServerGetPlayFabIDsFromPSNOnlineIDsCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Steam identifiers. The Steam identifiers
/// are the profile IDs for the user accounts, available as SteamId in the Steamworks Community API calls.
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementServerGetPlayFabIDsFromSteamIDsGetResultSize"/>
/// and <see cref="PFAccountManagementServerGetPlayFabIDsFromSteamIDsGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerGetPlayFabIDsFromSteamIDsAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromSteamIDsRequest* request,
	_Inout_ FOnServerGetPlayFabIDsFromSteamIDsCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Steam identifiers. The Steam identifiers
/// are persona names.
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementServerGetPlayFabIDsFromSteamNamesGetResultSize"/>
/// and <see cref="PFAccountManagementServerGetPlayFabIDsFromSteamNamesGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFAccountManagementServerGetPlayFabIDsFromSteamNamesAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromSteamNamesRequest* request,
	_Inout_ FOnServerGetPlayFabIDsFromSteamNamesCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Twitch identifiers. The Twitch identifiers
/// are the IDs for the user accounts, available as '_id' from the Twitch API methods (ex: https://github.com/justintv/Twitch-API/blob/master/v3_resources/users.md#get-usersuser).
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementServerGetPlayFabIDsFromTwitchIDsGetResultSize"/>
/// and <see cref="PFAccountManagementServerGetPlayFabIDsFromTwitchIDsGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerGetPlayFabIDsFromTwitchIDsAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromTwitchIDsRequest* request,
	_Inout_ FOnServerGetPlayFabIDsFromTwitchIDsCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of XboxLive identifiers.
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementServerGetPlayFabIDsFromXboxLiveIDsGetResultSize"/>
/// and <see cref="PFAccountManagementServerGetPlayFabIDsFromXboxLiveIDsGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerGetPlayFabIDsFromXboxLiveIDsAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromXboxLiveIDsRequest* request,
	_Inout_ FOnServerGetPlayFabIDsFromXboxLiveIDsCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves the associated PlayFab account identifiers for the given set of server custom identifiers.
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementServerGetServerCustomIDsFromPlayFabIDsGetResultSize"/>
/// and <see cref="PFAccountManagementServerGetServerCustomIDsFromPlayFabIDsGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerGetServerCustomIDsFromPlayFabIDsAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementGetServerCustomIDsFromPlayFabIDsRequest* request,
	_Inout_ FOnServerGetServerCustomIDsFromPlayFabIDsCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves the relevant details for a specified user
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// This API allows for access to details regarding a user in the PlayFab service, usually for purposes
/// of customer support. Note that data returned may be Personally Identifying Information (PII), such
/// as email address, and so care should be taken in how this data is stored and managed. Since this call
/// will always return the relevant information for users who have accessed the title, the recommendation
/// is to not store this data locally. See also ServerGetUserInventoryAsync.
///
/// When the asynchronous task is complete, call <see cref="PFAccountManagementServerGetUserAccountInfoGetResultSize"/>
/// and <see cref="PFAccountManagementServerGetUserAccountInfoGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerGetUserAccountInfoAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementGetUserAccountInfoRequest* request,
	_Inout_ FOnServerGetUserAccountInfoCompleted delegate
) noexcept;
#endif

/// <summary>
/// Gets all bans for a user.
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// Get all bans for a user, including inactive and expired bans.  See also ServerBanUsersAsync, ServerRevokeAllBansForUserAsync,
/// ServerRevokeBansAsync, ServerUpdateBansAsync.
///
/// When the asynchronous task is complete, call <see cref="PFAccountManagementServerGetUserBansGetResultSize"/>
/// and <see cref="PFAccountManagementServerGetUserBansGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerGetUserBansAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementGetUserBansRequest* request,
	_Inout_ FOnServerGetUserBansCompleted delegate
) noexcept;
#endif

/// <summary>
/// Links the Battle.net account associated with the token to the user's PlayFab account.
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows.
/// See also ServerUnlinkBattleNetAccountAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_BATTLE_NET_NOT_ENABLED_FOR_TITLE, E_PF_LINKED_IDENTIFIER_ALREADY_CLAIMED
/// or any of the global PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details
/// on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFAccountManagementServerLinkBattleNetAccountAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementServerLinkBattleNetAccountRequest* request,
	_Inout_ FOnServerLinkBattleNetAccountCompleted delegate
) noexcept;
#endif

/// <summary>
/// Links the Nintendo account associated with the token to the user's PlayFab account
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also ServerLinkNintendoServiceAccountSubjectAsync, ServerUnlinkNintendoServiceAccountAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_INVALID_IDENTITY_PROVIDER_ID, E_PF_LINKED_IDENTIFIER_ALREADY_CLAIMED,
/// E_PF_NINTENDO_SWITCH_NOT_ENABLED_FOR_TITLE or any of the global PlayFab Service errors. See doc page
/// "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerLinkNintendoServiceAccountAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementServerLinkNintendoServiceAccountRequest* request,
	_Inout_ FOnServerLinkNintendoServiceAccountCompleted delegate
) noexcept;
#endif

/// <summary>
/// Links the Nintendo account associated with the Nintendo Service Account subject or id to the user's
/// PlayFab account
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also ServerLinkNintendoServiceAccountAsync, ServerUnlinkNintendoServiceAccountAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_INVALID_IDENTITY_PROVIDER_ID, E_PF_LINKED_IDENTIFIER_ALREADY_CLAIMED,
/// E_PF_NINTENDO_SWITCH_NOT_ENABLED_FOR_TITLE or any of the global PlayFab Service errors. See doc page
/// "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerLinkNintendoServiceAccountSubjectAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementLinkNintendoServiceAccountSubjectRequest* request,
	_Inout_ FOnServerLinkNintendoServiceAccountSubjectCompleted delegate
) noexcept;
#endif

/// <summary>
/// Links the NintendoSwitchDeviceId to the user's PlayFab account
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also ServerUnlinkNintendoSwitchDeviceIdAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_LINKED_ACCOUNT_ALREADY_CLAIMED or any of the global PlayFab Service
/// errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerLinkNintendoSwitchDeviceIdAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementServerLinkNintendoSwitchDeviceIdRequest* request,
	_Inout_ FOnServerLinkNintendoSwitchDeviceIdCompleted delegate
) noexcept;
#endif

/// <summary>
/// Links the PlayStation :tm: Network account associated with the provided access code to the user's
/// PlayFab account
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also ServerUnlinkPSNAccountAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_ALREADY_LINKED, E_PF_ACCOUNT_NOT_FOUND, E_PF_INVALID_NAMESPACE_MISMATCH,
/// E_PF_INVALID_PSN_AUTH_CODE, E_PF_INVALID_PSN_ISSUER_ID, E_PF_LINKED_ACCOUNT_ALREADY_CLAIMED, E_PF_PSN_INACCESSIBLE,
/// E_PF_REQUEST_VIEW_CONSTRAINT_PARAMS_NOT_ALLOWED or any of the global PlayFab Service errors. See doc
/// page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerLinkPSNAccountAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementServerLinkPSNAccountRequest* request,
	_Inout_ FOnServerLinkPSNAccountCompleted delegate
) noexcept;
#endif

/// <summary>
/// Links the PlayStation :tm: Network account associated with the provided user id to the user's PlayFab
/// account
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows.
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_ALREADY_LINKED, E_PF_ACCOUNT_NOT_FOUND, E_PF_INVALID_NAMESPACE_MISMATCH,
/// E_PF_INVALID_PSN_AUTH_CODE, E_PF_INVALID_PSN_ISSUER_ID, E_PF_LINKED_ACCOUNT_ALREADY_CLAIMED, E_PF_PSN_INACCESSIBLE
/// or any of the global PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details
/// on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFAccountManagementServerLinkPSNIdAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementLinkPSNIdRequest* request,
	_Inout_ FOnServerLinkPSNIdCompleted delegate
) noexcept;
#endif

/// <summary>
/// Links the custom server identifier, generated by the title, to the user's PlayFab account.
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_FOUND, E_PF_LINKED_IDENTIFIER_ALREADY_CLAIMED or any of
/// the global PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details on error
/// handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerLinkServerCustomIdAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementLinkServerCustomIdRequest* request,
	_Inout_ FOnServerLinkServerCustomIdCompleted delegate
) noexcept;
#endif

/// <summary>
/// Links the Steam account associated with the provided Steam ID to the user's PlayFab account 
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also ServerLoginWithSteamIdAsync, ServerUnlinkSteamIdAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_ALREADY_LINKED, E_PF_INVALID_STEAM_TICKET, E_PF_LINKED_ACCOUNT_ALREADY_CLAIMED,
/// E_PF_STEAM_NOT_ENABLED_FOR_TITLE, E_PF_STEAM_USER_NOT_FOUND or any of the global PlayFab Service errors.
/// See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerLinkSteamIdAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementLinkSteamIdRequest* request,
	_Inout_ FOnServerLinkSteamIdCompleted delegate
) noexcept;
#endif

/// <summary>
/// Links the Xbox Live account associated with the provided access code to the user's PlayFab account
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also ServerLoginWithXboxAsync, ServerUnlinkXboxAccountAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_ALREADY_LINKED, E_PF_INVALID_XBOX_LIVE_TOKEN, E_PF_LINKED_ACCOUNT_ALREADY_CLAIMED
/// or any of the global PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details
/// on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerLinkXboxAccountAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementServerLinkXboxAccountRequest* request,
	_Inout_ FOnServerLinkXboxAccountCompleted delegate
) noexcept;
#endif

/// <summary>
/// Revoke all active bans for a user.
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// Setting the active state of all non-expired bans for a user to Inactive. Expired bans with an Active
/// state will be ignored, however. Returns information about applied updates only. See also ServerBanUsersAsync,
/// ServerGetUserBansAsync, ServerRevokeBansAsync, ServerUpdateBansAsync.
///
/// When the asynchronous task is complete, call <see cref="PFAccountManagementServerRevokeAllBansForUserGetResultSize"/>
/// and <see cref="PFAccountManagementServerRevokeAllBansForUserGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerRevokeAllBansForUserAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementRevokeAllBansForUserRequest* request,
	_Inout_ FOnServerRevokeAllBansForUserCompleted delegate
) noexcept;
#endif

/// <summary>
/// Revoke all active bans specified with BanId.
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// Setting the active state of all bans requested to Inactive regardless of whether that ban has already
/// expired. BanIds that do not exist will be skipped. Returns information about applied updates only.
///  See also ServerBanUsersAsync, ServerGetUserBansAsync, ServerRevokeAllBansForUserAsync, ServerUpdateBansAsync.
///
/// When the asynchronous task is complete, call <see cref="PFAccountManagementServerRevokeBansGetResultSize"/>
/// and <see cref="PFAccountManagementServerRevokeBansGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerRevokeBansAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementRevokeBansRequest* request,
	_Inout_ FOnServerRevokeBansCompleted delegate
) noexcept;
#endif

/// <summary>
/// Forces an email to be sent to the registered contact email address for the user's account based on
/// an account recovery email template
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// PlayFab accounts which have valid email address or username will be able to receive a password reset
/// email using this API.The email sent must be an account recovery email template. The username or email
/// can be passed in to send the email.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_EMAIL_CLIENT_CANCELED_TASK, E_PF_EMAIL_CLIENT_TIMEOUT, E_PF_EMAIL_MESSAGE_TO_ADDRESS_IS_MISSING,
/// E_PF_EMAIL_TEMPLATE_MISSING, E_PF_NO_CONTACT_EMAIL_ADDRESS_FOUND, E_PF_SMTP_ADDON_NOT_ENABLED or any
/// of the global PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details on error
/// handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerSendCustomAccountRecoveryEmailAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementSendCustomAccountRecoveryEmailRequest* request,
	_Inout_ FOnServerSendCustomAccountRecoveryEmailCompleted delegate
) noexcept;
#endif

/// <summary>
/// Sends an email based on an email template to a player's contact email 
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// Sends an email for only players that have contact emails associated with them. Takes in an email
/// template ID specifyingthe email template to send.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_EMAIL_CLIENT_CANCELED_TASK, E_PF_EMAIL_CLIENT_TIMEOUT, E_PF_EMAIL_TEMPLATE_MISSING,
/// E_PF_NO_CONTACT_EMAIL_ADDRESS_FOUND, E_PF_SMTP_ADDON_NOT_ENABLED or any of the global PlayFab Service
/// errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerSendEmailFromTemplateAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementSendEmailFromTemplateRequest* request,
	_Inout_ FOnServerSendEmailFromTemplateCompleted delegate
) noexcept;
#endif

/// <summary>
/// Unlinks the related Battle.net account from the user's PlayFab account.
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows.
/// See also ServerLinkBattleNetAccountAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED, E_PF_BATTLE_NET_NOT_ENABLED_FOR_TITLE or any of
/// the global PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details on error
/// handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFAccountManagementServerUnlinkBattleNetAccountAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementServerUnlinkBattleNetAccountRequest* request,
	_Inout_ FOnServerUnlinkBattleNetAccountCompleted delegate
) noexcept;
#endif

/// <summary>
/// Unlinks the related Nintendo account from the user's PlayFab account
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also ServerLinkNintendoServiceAccountAsync, ServerLinkNintendoServiceAccountSubjectAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED, E_PF_NINTENDO_SWITCH_NOT_ENABLED_FOR_TITLE or any
/// of the global PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details on error
/// handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerUnlinkNintendoServiceAccountAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementServerUnlinkNintendoServiceAccountRequest* request,
	_Inout_ FOnServerUnlinkNintendoServiceAccountCompleted delegate
) noexcept;
#endif

/// <summary>
/// Unlinks the related NintendoSwitchDeviceId from the user's PlayFab account
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also ServerLinkNintendoSwitchDeviceIdAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED, E_PF_NINTENDO_SWITCH_DEVICE_ID_NOT_LINKED or any
/// of the global PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details on error
/// handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerUnlinkNintendoSwitchDeviceIdAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementServerUnlinkNintendoSwitchDeviceIdRequest* request,
	_Inout_ FOnServerUnlinkNintendoSwitchDeviceIdCompleted delegate
) noexcept;
#endif

/// <summary>
/// Unlinks the related PlayStation :tm: Network account from the user's PlayFab account
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also ServerLinkPSNAccountAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED or any of the global PlayFab Service errors. See
/// doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerUnlinkPSNAccountAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementServerUnlinkPSNAccountRequest* request,
	_Inout_ FOnServerUnlinkPSNAccountCompleted delegate
) noexcept;
#endif

/// <summary>
/// Unlinks the custom server identifier from the user's PlayFab account.
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also ServerLinkServerCustomIdAsync, ServerLoginWithServerCustomIdAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED, E_PF_IDENTIFIER_NOT_LINKED or any of the global
/// PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerUnlinkServerCustomIdAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementUnlinkServerCustomIdRequest* request,
	_Inout_ FOnServerUnlinkServerCustomIdCompleted delegate
) noexcept;
#endif

/// <summary>
/// Unlinks the Steam account associated with the provided Steam ID to the user's PlayFab account 
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also ServerLinkSteamIdAsync, ServerLoginWithSteamIdAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED or any of the global PlayFab Service errors. See
/// doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerUnlinkSteamIdAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementUnlinkSteamIdRequest* request,
	_Inout_ FOnServerUnlinkSteamIdCompleted delegate
) noexcept;
#endif

/// <summary>
/// Unlinks the related Xbox Live account from the user's PlayFab account
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also ServerLinkXboxAccountAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED, E_PF_INVALID_XBOX_LIVE_TOKEN or any of the global
/// PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerUnlinkXboxAccountAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementServerUnlinkXboxAccountRequest* request,
	_Inout_ FOnServerUnlinkXboxAccountCompleted delegate
) noexcept;
#endif

/// <summary>
/// Update the avatar URL of the specified player
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be one of global PlayFab Service errors. See doc page "Handling PlayFab Errors"
/// for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerUpdateAvatarUrlAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementServerUpdateAvatarUrlRequest* request,
	_Inout_ FOnServerUpdateAvatarUrlCompleted delegate
) noexcept;
#endif

/// <summary>
/// Updates information of a list of existing bans specified with Ban Ids.
/// </summary>
/// <param name="serviceConfigHandle">PFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="secretKey">Title Secret Key used to authenticate the service request.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// For each ban, only updates the values that are set. Leave any value to null for no change. If a ban
/// could not be found, the rest are still applied. Returns information about applied updates only. See
/// also ServerBanUsersAsync, ServerGetUserBansAsync, ServerRevokeAllBansForUserAsync, ServerRevokeBansAsync.
///
/// When the asynchronous task is complete, call <see cref="PFAccountManagementServerUpdateBansGetResultSize"/>
/// and <see cref="PFAccountManagementServerUpdateBansGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerUpdateBansAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementUpdateBansRequest* request,
	_Inout_ FOnServerUpdateBansCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves the title player accounts associated with the given XUIDs.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// Given a collection of Xbox IDs (XUIDs), returns all title player accounts.
///
/// When the asynchronous task is complete, call <see cref="PFAccountManagementGetTitlePlayersFromXboxLiveIDsGetResultSize"/>
/// and <see cref="PFAccountManagementGetTitlePlayersFromXboxLiveIDsGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementGetTitlePlayersFromXboxLiveIDsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementGetTitlePlayersFromXboxLiveIDsRequest* request,
	_Inout_ FOnGetTitlePlayersFromXboxLiveIDsCompleted delegate
) noexcept;
#endif

/// <summary>
/// Update the display name of the entity
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Given an entity profile, will update its display name to the one passed in if the profile's version
/// is equal to the specified value See also ProfileGetProfileAsync.
///
/// When the asynchronous task is complete, call <see cref="PFAccountManagementSetDisplayNameGetResultSize"/>
/// and <see cref="PFAccountManagementSetDisplayNameGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFAccountManagementSetDisplayNameAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementSetDisplayNameRequest* request,
	_Inout_ FOnSetDisplayNameCompleted delegate
) noexcept;

}
