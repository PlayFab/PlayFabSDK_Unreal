// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#include "CoreMinimal.h"
#include "Async/AsyncWork.h"
#include "Async/Async.h"
#include "XAsyncTaskQueueHelpers.h"
#include "XAsyncTaskManager.h"
#include "XAsyncTask.h"
#include "PFEntity.h"
#include "PFServiceConfig.h"
#include "PFAccountManagementUnrealTypes.h"
#include "PFAccountManagementTypeConverters.h"

THIRD_PARTY_INCLUDES_START
#include <playfab/services/PFServices.h>
THIRD_PARTY_INCLUDES_END

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Adds or updates a contact email to the player's profile.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FClientAddOrUpdateContactEmailAsyncTask : public FXAsyncTask
{
public:
	FClientAddOrUpdateContactEmailAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementAddOrUpdateContactEmailRequest InRequest,
	const FOnClientAddOrUpdateContactEmailCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementAddOrUpdateContactEmailRequest Request;
	
	FOnClientAddOrUpdateContactEmailCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Adds playfab username/password auth to an existing account created via an anonymous auth method,
/// e.g. automatic device ID login.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Linux and macOS.
/// See also ClientLoginWithEmailAddressAsync, ClientLoginWithPlayFabAsync.
///
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientAddUsernamePasswordGetResultSize"/>
/// and <see cref="PFAccountManagementClientAddUsernamePasswordGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FClientAddUsernamePasswordAsyncTask : public FXAsyncTask
{
public:
	FClientAddUsernamePasswordAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementAddUsernamePasswordRequest InRequest,
	const FOnClientAddUsernamePasswordCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementAddUsernamePasswordRequest Request;
	
	FOnClientAddUsernamePasswordCompleted Delegate;

	HRESULT HResult;
};

#endif


/// <summary>
/// Retrieves the user's PlayFab account details
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientGetAccountInfoGetResultSize"/>
/// and <see cref="PFAccountManagementClientGetAccountInfoGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FClientGetAccountInfoAsyncTask : public FXAsyncTask
{
public:
	FClientGetAccountInfoAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementGetAccountInfoRequest InRequest,
	const FOnClientGetAccountInfoCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementGetAccountInfoRequest Request;
	
	FOnClientGetAccountInfoCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Retrieves all of the user's different kinds of info.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientGetPlayerCombinedInfoGetResultSize"/>
/// and <see cref="PFAccountManagementClientGetPlayerCombinedInfoGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FClientGetPlayerCombinedInfoAsyncTask : public FXAsyncTask
{
public:
	FClientGetPlayerCombinedInfoAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementGetPlayerCombinedInfoRequest InRequest,
	const FOnClientGetPlayerCombinedInfoCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementGetPlayerCombinedInfoRequest Request;
	
	FOnClientGetPlayerCombinedInfoCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Retrieves the player's profile
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FClientGetPlayerProfileAsyncTask : public FXAsyncTask
{
public:
	FClientGetPlayerProfileAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementGetPlayerProfileRequest InRequest,
	const FOnClientGetPlayerProfileCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementGetPlayerProfileRequest Request;
	
	FOnClientGetPlayerProfileCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Battle.net account identifiers.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientGetPlayFabIDsFromBattleNetAccountIdsGetResultSize"/>
/// and <see cref="PFAccountManagementClientGetPlayFabIDsFromBattleNetAccountIdsGetResult"/> to get the
/// result.
/// </remarks>
class PLAYFABSERVICES_API FClientGetPlayFabIDsFromBattleNetAccountIdsAsyncTask : public FXAsyncTask
{
public:
	FClientGetPlayFabIDsFromBattleNetAccountIdsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsRequest InRequest,
	const FOnClientGetPlayFabIDsFromBattleNetAccountIdsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsRequest Request;
	
	FOnClientGetPlayFabIDsFromBattleNetAccountIdsCompleted Delegate;

	HRESULT HResult;
};


#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Facebook identifiers.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, Android, iOS, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientGetPlayFabIDsFromFacebookIDsGetResultSize"/>
/// and <see cref="PFAccountManagementClientGetPlayFabIDsFromFacebookIDsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FClientGetPlayFabIDsFromFacebookIDsAsyncTask : public FXAsyncTask
{
public:
	FClientGetPlayFabIDsFromFacebookIDsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementGetPlayFabIDsFromFacebookIDsRequest InRequest,
	const FOnClientGetPlayFabIDsFromFacebookIDsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementGetPlayFabIDsFromFacebookIDsRequest Request;
	
	FOnClientGetPlayFabIDsFromFacebookIDsCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Facebook Instant Game identifiers.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientGetPlayFabIDsFromFacebookInstantGamesIdsGetResultSize"/>
/// and <see cref="PFAccountManagementClientGetPlayFabIDsFromFacebookInstantGamesIdsGetResult"/> to get
/// the result.
/// </remarks>
class PLAYFABSERVICES_API FClientGetPlayFabIDsFromFacebookInstantGamesIdsAsyncTask : public FXAsyncTask
{
public:
	FClientGetPlayFabIDsFromFacebookInstantGamesIdsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsRequest InRequest,
	const FOnClientGetPlayFabIDsFromFacebookInstantGamesIdsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsRequest Request;
	
	FOnClientGetPlayFabIDsFromFacebookInstantGamesIdsCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Game Center identifiers (referenced
/// in the Game Center Programming Guide as the Player Identifier).
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, iOS, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientGetPlayFabIDsFromGameCenterIDsGetResultSize"/>
/// and <see cref="PFAccountManagementClientGetPlayFabIDsFromGameCenterIDsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FClientGetPlayFabIDsFromGameCenterIDsAsyncTask : public FXAsyncTask
{
public:
	FClientGetPlayFabIDsFromGameCenterIDsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementGetPlayFabIDsFromGameCenterIDsRequest InRequest,
	const FOnClientGetPlayFabIDsFromGameCenterIDsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementGetPlayFabIDsFromGameCenterIDsRequest Request;
	
	FOnClientGetPlayFabIDsFromGameCenterIDsCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Google identifiers. The Google identifiers
/// are the IDs for the user accounts, available as 'id' in the Google+ People API calls.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, Android, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientGetPlayFabIDsFromGoogleIDsGetResultSize"/>
/// and <see cref="PFAccountManagementClientGetPlayFabIDsFromGoogleIDsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FClientGetPlayFabIDsFromGoogleIDsAsyncTask : public FXAsyncTask
{
public:
	FClientGetPlayFabIDsFromGoogleIDsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementGetPlayFabIDsFromGoogleIDsRequest InRequest,
	const FOnClientGetPlayFabIDsFromGoogleIDsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementGetPlayFabIDsFromGoogleIDsRequest Request;
	
	FOnClientGetPlayFabIDsFromGoogleIDsCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Google Play Games identifiers. The
/// Google Play Games identifiers are the IDs for the user accounts, available as 'playerId' in the Google
/// Play Games Services - Players API calls.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, Android, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientGetPlayFabIDsFromGooglePlayGamesPlayerIDsGetResultSize"/>
/// and <see cref="PFAccountManagementClientGetPlayFabIDsFromGooglePlayGamesPlayerIDsGetResult"/> to get
/// the result.
/// </remarks>
class PLAYFABSERVICES_API FClientGetPlayFabIDsFromGooglePlayGamesPlayerIDsAsyncTask : public FXAsyncTask
{
public:
	FClientGetPlayFabIDsFromGooglePlayGamesPlayerIDsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementGetPlayFabIDsFromGooglePlayGamesPlayerIDsRequest InRequest,
	const FOnClientGetPlayFabIDsFromGooglePlayGamesPlayerIDsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementGetPlayFabIDsFromGooglePlayGamesPlayerIDsRequest Request;
	
	FOnClientGetPlayFabIDsFromGooglePlayGamesPlayerIDsCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Kongregate identifiers. The Kongregate
/// identifiers are the IDs for the user accounts, available as 'user_id' from the Kongregate API methods(ex:
/// http://developers.kongregate.com/docs/client/getUserId).
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientGetPlayFabIDsFromKongregateIDsGetResultSize"/>
/// and <see cref="PFAccountManagementClientGetPlayFabIDsFromKongregateIDsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FClientGetPlayFabIDsFromKongregateIDsAsyncTask : public FXAsyncTask
{
public:
	FClientGetPlayFabIDsFromKongregateIDsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementGetPlayFabIDsFromKongregateIDsRequest InRequest,
	const FOnClientGetPlayFabIDsFromKongregateIDsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementGetPlayFabIDsFromKongregateIDsRequest Request;
	
	FOnClientGetPlayFabIDsFromKongregateIDsCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_NINTENDO_SWITCH || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Nintendo Service Account identifiers.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Nintendo Switch, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientGetPlayFabIDsFromNintendoServiceAccountIdsGetResultSize"/>
/// and <see cref="PFAccountManagementClientGetPlayFabIDsFromNintendoServiceAccountIdsGetResult"/> to
/// get the result.
/// </remarks>
class PLAYFABSERVICES_API FClientGetPlayFabIDsFromNintendoServiceAccountIdsAsyncTask : public FXAsyncTask
{
public:
	FClientGetPlayFabIDsFromNintendoServiceAccountIdsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsRequest InRequest,
	const FOnClientGetPlayFabIDsFromNintendoServiceAccountIdsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsRequest Request;
	
	FOnClientGetPlayFabIDsFromNintendoServiceAccountIdsCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Nintendo Switch Device identifiers.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientGetPlayFabIDsFromNintendoSwitchDeviceIdsGetResultSize"/>
/// and <see cref="PFAccountManagementClientGetPlayFabIDsFromNintendoSwitchDeviceIdsGetResult"/> to get
/// the result.
/// </remarks>
class PLAYFABSERVICES_API FClientGetPlayFabIDsFromNintendoSwitchDeviceIdsAsyncTask : public FXAsyncTask
{
public:
	FClientGetPlayFabIDsFromNintendoSwitchDeviceIdsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsRequest InRequest,
	const FOnClientGetPlayFabIDsFromNintendoSwitchDeviceIdsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsRequest Request;
	
	FOnClientGetPlayFabIDsFromNintendoSwitchDeviceIdsCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_4 || HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_5 || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of PlayStation :tm: Network identifiers.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Sony PlayStation®, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientGetPlayFabIDsFromPSNAccountIDsGetResultSize"/>
/// and <see cref="PFAccountManagementClientGetPlayFabIDsFromPSNAccountIDsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FClientGetPlayFabIDsFromPSNAccountIDsAsyncTask : public FXAsyncTask
{
public:
	FClientGetPlayFabIDsFromPSNAccountIDsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementGetPlayFabIDsFromPSNAccountIDsRequest InRequest,
	const FOnClientGetPlayFabIDsFromPSNAccountIDsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementGetPlayFabIDsFromPSNAccountIDsRequest Request;
	
	FOnClientGetPlayFabIDsFromPSNAccountIDsCompleted Delegate;

	HRESULT HResult;
};

#endif


/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of PlayStation :tm: Network identifiers.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientGetPlayFabIDsFromPSNOnlineIDsGetResultSize"/>
/// and <see cref="PFAccountManagementClientGetPlayFabIDsFromPSNOnlineIDsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FClientGetPlayFabIDsFromPSNOnlineIDsAsyncTask : public FXAsyncTask
{
public:
	FClientGetPlayFabIDsFromPSNOnlineIDsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementGetPlayFabIDsFromPSNOnlineIDsRequest InRequest,
	const FOnClientGetPlayFabIDsFromPSNOnlineIDsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementGetPlayFabIDsFromPSNOnlineIDsRequest Request;
	
	FOnClientGetPlayFabIDsFromPSNOnlineIDsCompleted Delegate;

	HRESULT HResult;
};


#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Steam identifiers. The Steam identifiers
/// are the profile IDs for the user accounts, available as SteamId in the Steamworks Community API calls.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientGetPlayFabIDsFromSteamIDsGetResultSize"/>
/// and <see cref="PFAccountManagementClientGetPlayFabIDsFromSteamIDsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FClientGetPlayFabIDsFromSteamIDsAsyncTask : public FXAsyncTask
{
public:
	FClientGetPlayFabIDsFromSteamIDsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementGetPlayFabIDsFromSteamIDsRequest InRequest,
	const FOnClientGetPlayFabIDsFromSteamIDsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementGetPlayFabIDsFromSteamIDsRequest Request;
	
	FOnClientGetPlayFabIDsFromSteamIDsCompleted Delegate;

	HRESULT HResult;
};

#endif


/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Steam identifiers. The Steam identifiers
/// are persona names.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientGetPlayFabIDsFromSteamNamesGetResultSize"/>
/// and <see cref="PFAccountManagementClientGetPlayFabIDsFromSteamNamesGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FClientGetPlayFabIDsFromSteamNamesAsyncTask : public FXAsyncTask
{
public:
	FClientGetPlayFabIDsFromSteamNamesAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementGetPlayFabIDsFromSteamNamesRequest InRequest,
	const FOnClientGetPlayFabIDsFromSteamNamesCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementGetPlayFabIDsFromSteamNamesRequest Request;
	
	FOnClientGetPlayFabIDsFromSteamNamesCompleted Delegate;

	HRESULT HResult;
};


#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Twitch identifiers. The Twitch identifiers
/// are the IDs for the user accounts, available as '_id' from the Twitch API methods (ex: https://github.com/justintv/Twitch-API/blob/master/v3_resources/users.md#get-usersuser).
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientGetPlayFabIDsFromTwitchIDsGetResultSize"/>
/// and <see cref="PFAccountManagementClientGetPlayFabIDsFromTwitchIDsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FClientGetPlayFabIDsFromTwitchIDsAsyncTask : public FXAsyncTask
{
public:
	FClientGetPlayFabIDsFromTwitchIDsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementGetPlayFabIDsFromTwitchIDsRequest InRequest,
	const FOnClientGetPlayFabIDsFromTwitchIDsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementGetPlayFabIDsFromTwitchIDsRequest Request;
	
	FOnClientGetPlayFabIDsFromTwitchIDsCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of XboxLive identifiers.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientGetPlayFabIDsFromXboxLiveIDsGetResultSize"/>
/// and <see cref="PFAccountManagementClientGetPlayFabIDsFromXboxLiveIDsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FClientGetPlayFabIDsFromXboxLiveIDsAsyncTask : public FXAsyncTask
{
public:
	FClientGetPlayFabIDsFromXboxLiveIDsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementGetPlayFabIDsFromXboxLiveIDsRequest InRequest,
	const FOnClientGetPlayFabIDsFromXboxLiveIDsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementGetPlayFabIDsFromXboxLiveIDsRequest Request;
	
	FOnClientGetPlayFabIDsFromXboxLiveIDsCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Links the Android device identifier to the user's PlayFab account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Linux and macOS.
/// See also ClientLoginWithAndroidDeviceIDAsync, ClientUnlinkAndroidDeviceIDAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_LINKED_DEVICE_ALREADY_CLAIMED or any of the global PlayFab Service errors.
/// See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FClientLinkAndroidDeviceIDAsyncTask : public FXAsyncTask
{
public:
	FClientLinkAndroidDeviceIDAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementLinkAndroidDeviceIDRequest InRequest,
	const FOnClientLinkAndroidDeviceIDCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementLinkAndroidDeviceIDRequest Request;
	
	FOnClientLinkAndroidDeviceIDCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Links the Apple account associated with the token to the user's PlayFab account.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FClientLinkAppleAsyncTask : public FXAsyncTask
{
public:
	FClientLinkAppleAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementLinkAppleRequest InRequest,
	const FOnClientLinkAppleCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementLinkAppleRequest Request;
	
	FOnClientLinkAppleCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK

/// <summary>
/// Links the Battle.net account associated with the token to the user's PlayFab account.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FClientLinkBattleNetAccountAsyncTask : public FXAsyncTask
{
public:
	FClientLinkBattleNetAccountAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementClientLinkBattleNetAccountRequest InRequest,
	const FOnClientLinkBattleNetAccountCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementClientLinkBattleNetAccountRequest Request;
	
	FOnClientLinkBattleNetAccountCompleted Delegate;

	HRESULT HResult;
};

#endif


/// <summary>
/// Links the custom identifier, generated by the title, to the user's PlayFab account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// See also ClientLoginWithCustomIDAsync, ClientUnlinkCustomIDAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_LINKED_IDENTIFIER_ALREADY_CLAIMED or any of the global PlayFab Service
/// errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FClientLinkCustomIDAsyncTask : public FXAsyncTask
{
public:
	FClientLinkCustomIDAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementLinkCustomIDRequest InRequest,
	const FOnClientLinkCustomIDCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementLinkCustomIDRequest Request;
	
	FOnClientLinkCustomIDCompleted Delegate;

	HRESULT HResult;
};


#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Links the Facebook account associated with the provided Facebook access token to the user's PlayFab
/// account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FClientLinkFacebookAccountAsyncTask : public FXAsyncTask
{
public:
	FClientLinkFacebookAccountAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementLinkFacebookAccountRequest InRequest,
	const FOnClientLinkFacebookAccountCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementLinkFacebookAccountRequest Request;
	
	FOnClientLinkFacebookAccountCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Links the Facebook Instant Games Id to the user's PlayFab account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FClientLinkFacebookInstantGamesIdAsyncTask : public FXAsyncTask
{
public:
	FClientLinkFacebookInstantGamesIdAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementLinkFacebookInstantGamesIdRequest InRequest,
	const FOnClientLinkFacebookInstantGamesIdCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementLinkFacebookInstantGamesIdRequest Request;
	
	FOnClientLinkFacebookInstantGamesIdCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Links the Game Center account associated with the provided Game Center ID to the user's PlayFab account.
/// Logging in with a Game Center ID is insecure if you do not include the optional PublicKeyUrl, Salt,
/// Signature, and Timestamp parameters in this request. It is recommended you require these parameters
/// on all Game Center calls by going to the Apple Add-ons page in the PlayFab Game Manager and enabling
/// the 'Require secure authentication only for this app' option.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FClientLinkGameCenterAccountAsyncTask : public FXAsyncTask
{
public:
	FClientLinkGameCenterAccountAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementLinkGameCenterAccountRequest InRequest,
	const FOnClientLinkGameCenterAccountCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementLinkGameCenterAccountRequest Request;
	
	FOnClientLinkGameCenterAccountCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Links the currently signed-in user account to their Google account, using their Google account credentials
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FClientLinkGoogleAccountAsyncTask : public FXAsyncTask
{
public:
	FClientLinkGoogleAccountAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementLinkGoogleAccountRequest InRequest,
	const FOnClientLinkGoogleAccountCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementLinkGoogleAccountRequest Request;
	
	FOnClientLinkGoogleAccountCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Links the currently signed-in user account to their Google Play Games account, using their Google
/// Play Games account credentials
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FClientLinkGooglePlayGamesServicesAccountAsyncTask : public FXAsyncTask
{
public:
	FClientLinkGooglePlayGamesServicesAccountAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementLinkGooglePlayGamesServicesAccountRequest InRequest,
	const FOnClientLinkGooglePlayGamesServicesAccountCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementLinkGooglePlayGamesServicesAccountRequest Request;
	
	FOnClientLinkGooglePlayGamesServicesAccountCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Links the vendor-specific iOS device identifier to the user's PlayFab account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Linux and macOS.
/// See also ClientLoginWithIOSDeviceIDAsync, ClientUnlinkIOSDeviceIDAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_LINKED_DEVICE_ALREADY_CLAIMED or any of the global PlayFab Service errors.
/// See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FClientLinkIOSDeviceIDAsyncTask : public FXAsyncTask
{
public:
	FClientLinkIOSDeviceIDAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementLinkIOSDeviceIDRequest InRequest,
	const FOnClientLinkIOSDeviceIDCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementLinkIOSDeviceIDRequest Request;
	
	FOnClientLinkIOSDeviceIDCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Links the Kongregate identifier to the user's PlayFab account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FClientLinkKongregateAsyncTask : public FXAsyncTask
{
public:
	FClientLinkKongregateAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementLinkKongregateAccountRequest InRequest,
	const FOnClientLinkKongregateCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementLinkKongregateAccountRequest Request;
	
	FOnClientLinkKongregateCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_NINTENDO_SWITCH || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Links the Nintendo account associated with the token to the user's PlayFab account.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FClientLinkNintendoServiceAccountAsyncTask : public FXAsyncTask
{
public:
	FClientLinkNintendoServiceAccountAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementClientLinkNintendoServiceAccountRequest InRequest,
	const FOnClientLinkNintendoServiceAccountCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementClientLinkNintendoServiceAccountRequest Request;
	
	FOnClientLinkNintendoServiceAccountCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Links the NintendoSwitchDeviceId to the user's PlayFab account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Linux and macOS.
/// See also ClientLoginWithNintendoSwitchDeviceIdAsync, ClientUnlinkNintendoSwitchDeviceIdAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_LINKED_IDENTIFIER_ALREADY_CLAIMED or any of the global PlayFab Service
/// errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FClientLinkNintendoSwitchDeviceIdAsyncTask : public FXAsyncTask
{
public:
	FClientLinkNintendoSwitchDeviceIdAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementClientLinkNintendoSwitchDeviceIdRequest InRequest,
	const FOnClientLinkNintendoSwitchDeviceIdCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementClientLinkNintendoSwitchDeviceIdRequest Request;
	
	FOnClientLinkNintendoSwitchDeviceIdCompleted Delegate;

	HRESULT HResult;
};

#endif


/// <summary>
/// Links an OpenID Connect account to a user's PlayFab account, based on an existing relationship between
/// a title and an Open ID Connect provider and the OpenId Connect JWT from that provider.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FClientLinkOpenIdConnectAsyncTask : public FXAsyncTask
{
public:
	FClientLinkOpenIdConnectAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementLinkOpenIdConnectRequest InRequest,
	const FOnClientLinkOpenIdConnectCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementLinkOpenIdConnectRequest Request;
	
	FOnClientLinkOpenIdConnectCompleted Delegate;

	HRESULT HResult;
};


#if HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_4 || HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_5 || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Links the PlayStation :tm: Network account associated with the provided access code to the user's
/// PlayFab account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FClientLinkPSNAccountAsyncTask : public FXAsyncTask
{
public:
	FClientLinkPSNAccountAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementClientLinkPSNAccountRequest InRequest,
	const FOnClientLinkPSNAccountCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementClientLinkPSNAccountRequest Request;
	
	FOnClientLinkPSNAccountCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Links the Steam account associated with the provided Steam authentication ticket to the user's PlayFab
/// account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FClientLinkSteamAccountAsyncTask : public FXAsyncTask
{
public:
	FClientLinkSteamAccountAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementLinkSteamAccountRequest InRequest,
	const FOnClientLinkSteamAccountCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementLinkSteamAccountRequest Request;
	
	FOnClientLinkSteamAccountCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Links the Twitch account associated with the token to the user's PlayFab account.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FClientLinkTwitchAsyncTask : public FXAsyncTask
{
public:
	FClientLinkTwitchAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementLinkTwitchAccountRequest InRequest,
	const FOnClientLinkTwitchCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementLinkTwitchAccountRequest Request;
	
	FOnClientLinkTwitchCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Links the Xbox Live account associated with the provided access code to the user's PlayFab account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FClientLinkXboxAccountAsyncTask : public FXAsyncTask
{
public:
	FClientLinkXboxAccountAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementClientLinkXboxAccountRequest InRequest,
	const FOnClientLinkXboxAccountCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementClientLinkXboxAccountRequest Request;
	
	FOnClientLinkXboxAccountCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Removes a contact email from the player's profile.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// This API removes an existing contact email from the player's profile.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be one of global PlayFab Service errors. See doc page "Handling PlayFab Errors"
/// for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FClientRemoveContactEmailAsyncTask : public FXAsyncTask
{
public:
	FClientRemoveContactEmailAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementRemoveContactEmailRequest InRequest,
	const FOnClientRemoveContactEmailCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementRemoveContactEmailRequest Request;
	
	FOnClientRemoveContactEmailCompleted Delegate;

	HRESULT HResult;
};

#endif


/// <summary>
/// Submit a report for another player (due to bad bahavior, etc.), so that customer service representatives
/// for the title can take action concerning potentially toxic players.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementClientReportPlayerGetResult"/>
/// to get the result.
/// </remarks>
class PLAYFABSERVICES_API FClientReportPlayerAsyncTask : public FXAsyncTask
{
public:
	FClientReportPlayerAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementReportPlayerClientRequest InRequest,
	const FOnClientReportPlayerCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementReportPlayerClientRequest Request;
	
	FOnClientReportPlayerCompleted Delegate;

	HRESULT HResult;
};


#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Forces an email to be sent to the registered email address for the user's account, with a link allowing
/// the user to change the password.If an account recovery email template ID is provided, an email using
/// the custom email template will be used.
/// </summary>
/// <param name="serviceConfigHandle">FPFServiceConfigHandle returned from PFServiceConfigCreateHandle call.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FClientSendAccountRecoveryEmailAsyncTask : public FXAsyncTask
{
public:
	FClientSendAccountRecoveryEmailAsyncTask(
	_In_ FPFServiceConfigHandle ServiceConfigHandle,
	FPFAccountManagementSendAccountRecoveryEmailRequest InRequest,
	const FOnClientSendAccountRecoveryEmailCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFServiceConfigHandle ServiceConfigHandle;
	
	FPFAccountManagementSendAccountRecoveryEmailRequest Request;
	
	FOnClientSendAccountRecoveryEmailCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Unlinks the related Android device identifier from the user's PlayFab account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Linux and macOS.
/// See also ClientLinkAndroidDeviceIDAsync, ClientLoginWithAndroidDeviceIDAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED, E_PF_DEVICE_NOT_LINKED or any of the global PlayFab
/// Service errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FClientUnlinkAndroidDeviceIDAsyncTask : public FXAsyncTask
{
public:
	FClientUnlinkAndroidDeviceIDAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementUnlinkAndroidDeviceIDRequest InRequest,
	const FOnClientUnlinkAndroidDeviceIDCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementUnlinkAndroidDeviceIDRequest Request;
	
	FOnClientUnlinkAndroidDeviceIDCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Unlinks the related Apple account from the user's PlayFab account.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Linux, iOS, and macOS.
/// See also ClientLinkAppleAsync, ClientLoginWithAppleAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED, E_PF_APPLE_NOT_ENABLED_FOR_TITLE or any of the global
/// PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FClientUnlinkAppleAsyncTask : public FXAsyncTask
{
public:
	FClientUnlinkAppleAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementUnlinkAppleRequest InRequest,
	const FOnClientUnlinkAppleCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementUnlinkAppleRequest Request;
	
	FOnClientUnlinkAppleCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK

/// <summary>
/// Unlinks the related Battle.net account from the user's PlayFab account.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FClientUnlinkBattleNetAccountAsyncTask : public FXAsyncTask
{
public:
	FClientUnlinkBattleNetAccountAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementClientUnlinkBattleNetAccountRequest InRequest,
	const FOnClientUnlinkBattleNetAccountCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementClientUnlinkBattleNetAccountRequest Request;
	
	FOnClientUnlinkBattleNetAccountCompleted Delegate;

	HRESULT HResult;
};

#endif


/// <summary>
/// Unlinks the related custom identifier from the user's PlayFab account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// See also ClientLinkCustomIDAsync, ClientLoginWithCustomIDAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED, E_PF_CUSTOM_ID_NOT_LINKED or any of the global PlayFab
/// Service errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FClientUnlinkCustomIDAsyncTask : public FXAsyncTask
{
public:
	FClientUnlinkCustomIDAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementUnlinkCustomIDRequest InRequest,
	const FOnClientUnlinkCustomIDCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementUnlinkCustomIDRequest Request;
	
	FOnClientUnlinkCustomIDCompleted Delegate;

	HRESULT HResult;
};


#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Unlinks the related Facebook account from the user's PlayFab account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Linux, Android, iOS, and macOS.
/// See also ClientLinkFacebookAccountAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED or any of the global PlayFab Service errors. See
/// doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FClientUnlinkFacebookAccountAsyncTask : public FXAsyncTask
{
public:
	FClientUnlinkFacebookAccountAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementUnlinkFacebookAccountRequest InRequest,
	const FOnClientUnlinkFacebookAccountCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementUnlinkFacebookAccountRequest Request;
	
	FOnClientUnlinkFacebookAccountCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Unlinks the related Facebook Instant Game Ids from the user's PlayFab account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FClientUnlinkFacebookInstantGamesIdAsyncTask : public FXAsyncTask
{
public:
	FClientUnlinkFacebookInstantGamesIdAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementUnlinkFacebookInstantGamesIdRequest InRequest,
	const FOnClientUnlinkFacebookInstantGamesIdCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementUnlinkFacebookInstantGamesIdRequest Request;
	
	FOnClientUnlinkFacebookInstantGamesIdCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Unlinks the related Game Center account from the user's PlayFab account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Linux, iOS, and macOS.
/// See also ClientLinkGameCenterAccountAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED or any of the global PlayFab Service errors. See
/// doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FClientUnlinkGameCenterAccountAsyncTask : public FXAsyncTask
{
public:
	FClientUnlinkGameCenterAccountAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementUnlinkGameCenterAccountRequest InRequest,
	const FOnClientUnlinkGameCenterAccountCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementUnlinkGameCenterAccountRequest Request;
	
	FOnClientUnlinkGameCenterAccountCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Unlinks the related Google account from the user's PlayFab account (https://developers.google.com/android/reference/com/google/android/gms/auth/GoogleAuthUtil#public-methods).
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Linux, Android, and macOS.
/// See also ClientLinkGoogleAccountAsync, ClientLoginWithGoogleAccountAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED or any of the global PlayFab Service errors. See
/// doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FClientUnlinkGoogleAccountAsyncTask : public FXAsyncTask
{
public:
	FClientUnlinkGoogleAccountAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementUnlinkGoogleAccountRequest InRequest,
	const FOnClientUnlinkGoogleAccountCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementUnlinkGoogleAccountRequest Request;
	
	FOnClientUnlinkGoogleAccountCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Unlinks the related Google Play Games account from the user's PlayFab account.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Linux, Android, and macOS.
/// See also ClientLinkGooglePlayGamesServicesAccountAsync, ClientLoginWithGooglePlayGamesServicesAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED or any of the global PlayFab Service errors. See
/// doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FClientUnlinkGooglePlayGamesServicesAccountAsyncTask : public FXAsyncTask
{
public:
	FClientUnlinkGooglePlayGamesServicesAccountAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementUnlinkGooglePlayGamesServicesAccountRequest InRequest,
	const FOnClientUnlinkGooglePlayGamesServicesAccountCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementUnlinkGooglePlayGamesServicesAccountRequest Request;
	
	FOnClientUnlinkGooglePlayGamesServicesAccountCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Unlinks the related iOS device identifier from the user's PlayFab account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Linux and macOS.
/// See also ClientLinkIOSDeviceIDAsync, ClientLoginWithIOSDeviceIDAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED, E_PF_DEVICE_NOT_LINKED or any of the global PlayFab
/// Service errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FClientUnlinkIOSDeviceIDAsyncTask : public FXAsyncTask
{
public:
	FClientUnlinkIOSDeviceIDAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementUnlinkIOSDeviceIDRequest InRequest,
	const FOnClientUnlinkIOSDeviceIDCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementUnlinkIOSDeviceIDRequest Request;
	
	FOnClientUnlinkIOSDeviceIDCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Unlinks the related Kongregate identifier from the user's PlayFab account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Linux and macOS.
/// See also ClientLinkKongregateAsync, ClientLoginWithKongregateAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED or any of the global PlayFab Service errors. See
/// doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FClientUnlinkKongregateAsyncTask : public FXAsyncTask
{
public:
	FClientUnlinkKongregateAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementUnlinkKongregateAccountRequest InRequest,
	const FOnClientUnlinkKongregateCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementUnlinkKongregateAccountRequest Request;
	
	FOnClientUnlinkKongregateCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_NINTENDO_SWITCH || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Unlinks the related Nintendo account from the user's PlayFab account.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FClientUnlinkNintendoServiceAccountAsyncTask : public FXAsyncTask
{
public:
	FClientUnlinkNintendoServiceAccountAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementClientUnlinkNintendoServiceAccountRequest InRequest,
	const FOnClientUnlinkNintendoServiceAccountCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementClientUnlinkNintendoServiceAccountRequest Request;
	
	FOnClientUnlinkNintendoServiceAccountCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Unlinks the related NintendoSwitchDeviceId from the user's PlayFab account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FClientUnlinkNintendoSwitchDeviceIdAsyncTask : public FXAsyncTask
{
public:
	FClientUnlinkNintendoSwitchDeviceIdAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementClientUnlinkNintendoSwitchDeviceIdRequest InRequest,
	const FOnClientUnlinkNintendoSwitchDeviceIdCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementClientUnlinkNintendoSwitchDeviceIdRequest Request;
	
	FOnClientUnlinkNintendoSwitchDeviceIdCompleted Delegate;

	HRESULT HResult;
};

#endif


/// <summary>
/// Unlinks an OpenID Connect account from a user's PlayFab account, based on the connection ID of an
/// existing relationship between a title and an Open ID Connect provider.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// See also ClientLinkOpenIdConnectAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED or any of the global PlayFab Service errors. See
/// doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FClientUnlinkOpenIdConnectAsyncTask : public FXAsyncTask
{
public:
	FClientUnlinkOpenIdConnectAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementUnlinkOpenIdConnectRequest InRequest,
	const FOnClientUnlinkOpenIdConnectCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementUnlinkOpenIdConnectRequest Request;
	
	FOnClientUnlinkOpenIdConnectCompleted Delegate;

	HRESULT HResult;
};


#if HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_4 || HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_5 || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Unlinks the related PlayStation :tm: Network account from the user's PlayFab account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Sony PlayStation®, Linux, and macOS.
/// See also ClientLinkPSNAccountAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED or any of the global PlayFab Service errors. See
/// doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FClientUnlinkPSNAccountAsyncTask : public FXAsyncTask
{
public:
	FClientUnlinkPSNAccountAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementClientUnlinkPSNAccountRequest InRequest,
	const FOnClientUnlinkPSNAccountCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementClientUnlinkPSNAccountRequest Request;
	
	FOnClientUnlinkPSNAccountCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Unlinks the related Steam account from the user's PlayFab account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also ClientLinkSteamAccountAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED or any of the global PlayFab Service errors. See
/// doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FClientUnlinkSteamAccountAsyncTask : public FXAsyncTask
{
public:
	FClientUnlinkSteamAccountAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementUnlinkSteamAccountRequest InRequest,
	const FOnClientUnlinkSteamAccountCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementUnlinkSteamAccountRequest Request;
	
	FOnClientUnlinkSteamAccountCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Unlinks the related Twitch account from the user's PlayFab account.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FClientUnlinkTwitchAsyncTask : public FXAsyncTask
{
public:
	FClientUnlinkTwitchAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementUnlinkTwitchAccountRequest InRequest,
	const FOnClientUnlinkTwitchCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementUnlinkTwitchAccountRequest Request;
	
	FOnClientUnlinkTwitchCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Unlinks the related Xbox Live account from the user's PlayFab account
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also ClientLinkXboxAccountAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED, E_PF_INVALID_XBOX_LIVE_TOKEN or any of the global
/// PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FClientUnlinkXboxAccountAsyncTask : public FXAsyncTask
{
public:
	FClientUnlinkXboxAccountAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementClientUnlinkXboxAccountRequest InRequest,
	const FOnClientUnlinkXboxAccountCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementClientUnlinkXboxAccountRequest Request;
	
	FOnClientUnlinkXboxAccountCompleted Delegate;

	HRESULT HResult;
};

#endif


/// <summary>
/// Update the avatar URL of the player
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be one of global PlayFab Service errors. See doc page "Handling PlayFab Errors"
/// for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FClientUpdateAvatarUrlAsyncTask : public FXAsyncTask
{
public:
	FClientUpdateAvatarUrlAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementClientUpdateAvatarUrlRequest InRequest,
	const FOnClientUpdateAvatarUrlCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementClientUpdateAvatarUrlRequest Request;
	
	FOnClientUpdateAvatarUrlCompleted Delegate;

	HRESULT HResult;
};


#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Updates the title specific display name for the user
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FClientUpdateUserTitleDisplayNameAsyncTask : public FXAsyncTask
{
public:
	FClientUpdateUserTitleDisplayNameAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementUpdateUserTitleDisplayNameRequest InRequest,
	const FOnClientUpdateUserTitleDisplayNameCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementUpdateUserTitleDisplayNameRequest Request;
	
	FOnClientUpdateUserTitleDisplayNameCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Bans users by PlayFab ID with optional IP address, or MAC address for the provided game.
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FServerBanUsersAsyncTask : public FXAsyncTask
{
public:
	FServerBanUsersAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementBanUsersRequest InRequest,
	const FOnServerBanUsersCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementBanUsersRequest Request;
	
	FOnServerBanUsersCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Removes a user's player account from a title and deletes all associated data
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FServerDeletePlayerAsyncTask : public FXAsyncTask
{
public:
	FServerDeletePlayerAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementDeletePlayerRequest InRequest,
	const FOnServerDeletePlayerCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementDeletePlayerRequest Request;
	
	FOnServerDeletePlayerCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Returns whatever info is requested in the response for the user. Note that PII (like email address,
/// facebook id) may be returned. All parameters default to false.
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementServerGetPlayerCombinedInfoGetResultSize"/>
/// and <see cref="PFAccountManagementServerGetPlayerCombinedInfoGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FServerGetPlayerCombinedInfoAsyncTask : public FXAsyncTask
{
public:
	FServerGetPlayerCombinedInfoAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementGetPlayerCombinedInfoRequest InRequest,
	const FOnServerGetPlayerCombinedInfoCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementGetPlayerCombinedInfoRequest Request;
	
	FOnServerGetPlayerCombinedInfoCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Retrieves the player's profile
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FServerGetPlayerProfileAsyncTask : public FXAsyncTask
{
public:
	FServerGetPlayerProfileAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementGetPlayerProfileRequest InRequest,
	const FOnServerGetPlayerProfileCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementGetPlayerProfileRequest Request;
	
	FOnServerGetPlayerProfileCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Battle.net account identifiers.
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementServerGetPlayFabIDsFromBattleNetAccountIdsGetResultSize"/>
/// and <see cref="PFAccountManagementServerGetPlayFabIDsFromBattleNetAccountIdsGetResult"/> to get the
/// result.
/// </remarks>
class PLAYFABSERVICES_API FServerGetPlayFabIDsFromBattleNetAccountIdsAsyncTask : public FXAsyncTask
{
public:
	FServerGetPlayFabIDsFromBattleNetAccountIdsAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsRequest InRequest,
	const FOnServerGetPlayFabIDsFromBattleNetAccountIdsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsRequest Request;
	
	FOnServerGetPlayFabIDsFromBattleNetAccountIdsCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Facebook identifiers.
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementServerGetPlayFabIDsFromFacebookIDsGetResultSize"/>
/// and <see cref="PFAccountManagementServerGetPlayFabIDsFromFacebookIDsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FServerGetPlayFabIDsFromFacebookIDsAsyncTask : public FXAsyncTask
{
public:
	FServerGetPlayFabIDsFromFacebookIDsAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementGetPlayFabIDsFromFacebookIDsRequest InRequest,
	const FOnServerGetPlayFabIDsFromFacebookIDsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementGetPlayFabIDsFromFacebookIDsRequest Request;
	
	FOnServerGetPlayFabIDsFromFacebookIDsCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Facebook Instant Games identifiers.
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementServerGetPlayFabIDsFromFacebookInstantGamesIdsGetResultSize"/>
/// and <see cref="PFAccountManagementServerGetPlayFabIDsFromFacebookInstantGamesIdsGetResult"/> to get
/// the result.
/// </remarks>
class PLAYFABSERVICES_API FServerGetPlayFabIDsFromFacebookInstantGamesIdsAsyncTask : public FXAsyncTask
{
public:
	FServerGetPlayFabIDsFromFacebookInstantGamesIdsAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsRequest InRequest,
	const FOnServerGetPlayFabIDsFromFacebookInstantGamesIdsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsRequest Request;
	
	FOnServerGetPlayFabIDsFromFacebookInstantGamesIdsCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Nintendo Service Account identifiers.
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementServerGetPlayFabIDsFromNintendoServiceAccountIdsGetResultSize"/>
/// and <see cref="PFAccountManagementServerGetPlayFabIDsFromNintendoServiceAccountIdsGetResult"/> to
/// get the result.
/// </remarks>
class PLAYFABSERVICES_API FServerGetPlayFabIDsFromNintendoServiceAccountIdsAsyncTask : public FXAsyncTask
{
public:
	FServerGetPlayFabIDsFromNintendoServiceAccountIdsAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsRequest InRequest,
	const FOnServerGetPlayFabIDsFromNintendoServiceAccountIdsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsRequest Request;
	
	FOnServerGetPlayFabIDsFromNintendoServiceAccountIdsCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Nintendo Switch Device identifiers.
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementServerGetPlayFabIDsFromNintendoSwitchDeviceIdsGetResultSize"/>
/// and <see cref="PFAccountManagementServerGetPlayFabIDsFromNintendoSwitchDeviceIdsGetResult"/> to get
/// the result.
/// </remarks>
class PLAYFABSERVICES_API FServerGetPlayFabIDsFromNintendoSwitchDeviceIdsAsyncTask : public FXAsyncTask
{
public:
	FServerGetPlayFabIDsFromNintendoSwitchDeviceIdsAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsRequest InRequest,
	const FOnServerGetPlayFabIDsFromNintendoSwitchDeviceIdsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsRequest Request;
	
	FOnServerGetPlayFabIDsFromNintendoSwitchDeviceIdsCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of PlayStation :tm: Network identifiers.
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementServerGetPlayFabIDsFromPSNAccountIDsGetResultSize"/>
/// and <see cref="PFAccountManagementServerGetPlayFabIDsFromPSNAccountIDsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FServerGetPlayFabIDsFromPSNAccountIDsAsyncTask : public FXAsyncTask
{
public:
	FServerGetPlayFabIDsFromPSNAccountIDsAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementGetPlayFabIDsFromPSNAccountIDsRequest InRequest,
	const FOnServerGetPlayFabIDsFromPSNAccountIDsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementGetPlayFabIDsFromPSNAccountIDsRequest Request;
	
	FOnServerGetPlayFabIDsFromPSNAccountIDsCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of PlayStation :tm: Network identifiers.
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementServerGetPlayFabIDsFromPSNOnlineIDsGetResultSize"/>
/// and <see cref="PFAccountManagementServerGetPlayFabIDsFromPSNOnlineIDsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FServerGetPlayFabIDsFromPSNOnlineIDsAsyncTask : public FXAsyncTask
{
public:
	FServerGetPlayFabIDsFromPSNOnlineIDsAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementGetPlayFabIDsFromPSNOnlineIDsRequest InRequest,
	const FOnServerGetPlayFabIDsFromPSNOnlineIDsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementGetPlayFabIDsFromPSNOnlineIDsRequest Request;
	
	FOnServerGetPlayFabIDsFromPSNOnlineIDsCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Steam identifiers. The Steam identifiers
/// are the profile IDs for the user accounts, available as SteamId in the Steamworks Community API calls.
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementServerGetPlayFabIDsFromSteamIDsGetResultSize"/>
/// and <see cref="PFAccountManagementServerGetPlayFabIDsFromSteamIDsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FServerGetPlayFabIDsFromSteamIDsAsyncTask : public FXAsyncTask
{
public:
	FServerGetPlayFabIDsFromSteamIDsAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementGetPlayFabIDsFromSteamIDsRequest InRequest,
	const FOnServerGetPlayFabIDsFromSteamIDsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementGetPlayFabIDsFromSteamIDsRequest Request;
	
	FOnServerGetPlayFabIDsFromSteamIDsCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Steam identifiers. The Steam identifiers
/// are persona names.
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementServerGetPlayFabIDsFromSteamNamesGetResultSize"/>
/// and <see cref="PFAccountManagementServerGetPlayFabIDsFromSteamNamesGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FServerGetPlayFabIDsFromSteamNamesAsyncTask : public FXAsyncTask
{
public:
	FServerGetPlayFabIDsFromSteamNamesAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementGetPlayFabIDsFromSteamNamesRequest InRequest,
	const FOnServerGetPlayFabIDsFromSteamNamesCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementGetPlayFabIDsFromSteamNamesRequest Request;
	
	FOnServerGetPlayFabIDsFromSteamNamesCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of Twitch identifiers. The Twitch identifiers
/// are the IDs for the user accounts, available as '_id' from the Twitch API methods (ex: https://github.com/justintv/Twitch-API/blob/master/v3_resources/users.md#get-usersuser).
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementServerGetPlayFabIDsFromTwitchIDsGetResultSize"/>
/// and <see cref="PFAccountManagementServerGetPlayFabIDsFromTwitchIDsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FServerGetPlayFabIDsFromTwitchIDsAsyncTask : public FXAsyncTask
{
public:
	FServerGetPlayFabIDsFromTwitchIDsAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementGetPlayFabIDsFromTwitchIDsRequest InRequest,
	const FOnServerGetPlayFabIDsFromTwitchIDsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementGetPlayFabIDsFromTwitchIDsRequest Request;
	
	FOnServerGetPlayFabIDsFromTwitchIDsCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Retrieves the unique PlayFab identifiers for the given set of XboxLive identifiers.
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementServerGetPlayFabIDsFromXboxLiveIDsGetResultSize"/>
/// and <see cref="PFAccountManagementServerGetPlayFabIDsFromXboxLiveIDsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FServerGetPlayFabIDsFromXboxLiveIDsAsyncTask : public FXAsyncTask
{
public:
	FServerGetPlayFabIDsFromXboxLiveIDsAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementGetPlayFabIDsFromXboxLiveIDsRequest InRequest,
	const FOnServerGetPlayFabIDsFromXboxLiveIDsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementGetPlayFabIDsFromXboxLiveIDsRequest Request;
	
	FOnServerGetPlayFabIDsFromXboxLiveIDsCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Retrieves the associated PlayFab account identifiers for the given set of server custom identifiers.
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFAccountManagementServerGetServerCustomIDsFromPlayFabIDsGetResultSize"/>
/// and <see cref="PFAccountManagementServerGetServerCustomIDsFromPlayFabIDsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FServerGetServerCustomIDsFromPlayFabIDsAsyncTask : public FXAsyncTask
{
public:
	FServerGetServerCustomIDsFromPlayFabIDsAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementGetServerCustomIDsFromPlayFabIDsRequest InRequest,
	const FOnServerGetServerCustomIDsFromPlayFabIDsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementGetServerCustomIDsFromPlayFabIDsRequest Request;
	
	FOnServerGetServerCustomIDsFromPlayFabIDsCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Retrieves the relevant details for a specified user
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FServerGetUserAccountInfoAsyncTask : public FXAsyncTask
{
public:
	FServerGetUserAccountInfoAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementGetUserAccountInfoRequest InRequest,
	const FOnServerGetUserAccountInfoCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementGetUserAccountInfoRequest Request;
	
	FOnServerGetUserAccountInfoCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Gets all bans for a user.
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// Get all bans for a user, including inactive and expired bans.  See also ServerBanUsersAsync, ServerRevokeAllBansForUserAsync,
/// ServerRevokeBansAsync, ServerUpdateBansAsync.
///
/// When the asynchronous task is complete, call <see cref="PFAccountManagementServerGetUserBansGetResultSize"/>
/// and <see cref="PFAccountManagementServerGetUserBansGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FServerGetUserBansAsyncTask : public FXAsyncTask
{
public:
	FServerGetUserBansAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementGetUserBansRequest InRequest,
	const FOnServerGetUserBansCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementGetUserBansRequest Request;
	
	FOnServerGetUserBansCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK

/// <summary>
/// Links the Battle.net account associated with the token to the user's PlayFab account.
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FServerLinkBattleNetAccountAsyncTask : public FXAsyncTask
{
public:
	FServerLinkBattleNetAccountAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementServerLinkBattleNetAccountRequest InRequest,
	const FOnServerLinkBattleNetAccountCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementServerLinkBattleNetAccountRequest Request;
	
	FOnServerLinkBattleNetAccountCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Links the Nintendo account associated with the token to the user's PlayFab account
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FServerLinkNintendoServiceAccountAsyncTask : public FXAsyncTask
{
public:
	FServerLinkNintendoServiceAccountAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementServerLinkNintendoServiceAccountRequest InRequest,
	const FOnServerLinkNintendoServiceAccountCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementServerLinkNintendoServiceAccountRequest Request;
	
	FOnServerLinkNintendoServiceAccountCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Links the Nintendo account associated with the Nintendo Service Account subject or id to the user's
/// PlayFab account
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FServerLinkNintendoServiceAccountSubjectAsyncTask : public FXAsyncTask
{
public:
	FServerLinkNintendoServiceAccountSubjectAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementLinkNintendoServiceAccountSubjectRequest InRequest,
	const FOnServerLinkNintendoServiceAccountSubjectCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementLinkNintendoServiceAccountSubjectRequest Request;
	
	FOnServerLinkNintendoServiceAccountSubjectCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Links the NintendoSwitchDeviceId to the user's PlayFab account
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also ServerUnlinkNintendoSwitchDeviceIdAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_LINKED_ACCOUNT_ALREADY_CLAIMED or any of the global PlayFab Service
/// errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FServerLinkNintendoSwitchDeviceIdAsyncTask : public FXAsyncTask
{
public:
	FServerLinkNintendoSwitchDeviceIdAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementServerLinkNintendoSwitchDeviceIdRequest InRequest,
	const FOnServerLinkNintendoSwitchDeviceIdCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementServerLinkNintendoSwitchDeviceIdRequest Request;
	
	FOnServerLinkNintendoSwitchDeviceIdCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Links the PlayStation :tm: Network account associated with the provided access code to the user's
/// PlayFab account
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FServerLinkPSNAccountAsyncTask : public FXAsyncTask
{
public:
	FServerLinkPSNAccountAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementServerLinkPSNAccountRequest InRequest,
	const FOnServerLinkPSNAccountCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementServerLinkPSNAccountRequest Request;
	
	FOnServerLinkPSNAccountCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK

/// <summary>
/// Links the PlayStation :tm: Network account associated with the provided user id to the user's PlayFab
/// account
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows.
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_ALREADY_LINKED, E_PF_ACCOUNT_NOT_FOUND, E_PF_INVALID_NAMESPACE_MISMATCH,
/// E_PF_INVALID_PSN_AUTH_CODE, E_PF_INVALID_PSN_ISSUER_ID, E_PF_LINKED_ACCOUNT_ALREADY_CLAIMED, E_PF_PSN_INACCESSIBLE
/// or any of the global PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details
/// on error handling.
/// </remarks>
class PLAYFABSERVICES_API FServerLinkPSNIdAsyncTask : public FXAsyncTask
{
public:
	FServerLinkPSNIdAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementLinkPSNIdRequest InRequest,
	const FOnServerLinkPSNIdCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementLinkPSNIdRequest Request;
	
	FOnServerLinkPSNIdCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Links the custom server identifier, generated by the title, to the user's PlayFab account.
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_FOUND, E_PF_LINKED_IDENTIFIER_ALREADY_CLAIMED or any of
/// the global PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details on error
/// handling.
/// </remarks>
class PLAYFABSERVICES_API FServerLinkServerCustomIdAsyncTask : public FXAsyncTask
{
public:
	FServerLinkServerCustomIdAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementLinkServerCustomIdRequest InRequest,
	const FOnServerLinkServerCustomIdCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementLinkServerCustomIdRequest Request;
	
	FOnServerLinkServerCustomIdCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Links the Steam account associated with the provided Steam ID to the user's PlayFab account 
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FServerLinkSteamIdAsyncTask : public FXAsyncTask
{
public:
	FServerLinkSteamIdAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementLinkSteamIdRequest InRequest,
	const FOnServerLinkSteamIdCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementLinkSteamIdRequest Request;
	
	FOnServerLinkSteamIdCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Links the Xbox Live account associated with the provided access code to the user's PlayFab account
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FServerLinkXboxAccountAsyncTask : public FXAsyncTask
{
public:
	FServerLinkXboxAccountAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementServerLinkXboxAccountRequest InRequest,
	const FOnServerLinkXboxAccountCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementServerLinkXboxAccountRequest Request;
	
	FOnServerLinkXboxAccountCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Revoke all active bans for a user.
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FServerRevokeAllBansForUserAsyncTask : public FXAsyncTask
{
public:
	FServerRevokeAllBansForUserAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementRevokeAllBansForUserRequest InRequest,
	const FOnServerRevokeAllBansForUserCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementRevokeAllBansForUserRequest Request;
	
	FOnServerRevokeAllBansForUserCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Revoke all active bans specified with BanId.
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FServerRevokeBansAsyncTask : public FXAsyncTask
{
public:
	FServerRevokeBansAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementRevokeBansRequest InRequest,
	const FOnServerRevokeBansCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementRevokeBansRequest Request;
	
	FOnServerRevokeBansCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Forces an email to be sent to the registered contact email address for the user's account based on
/// an account recovery email template
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FServerSendCustomAccountRecoveryEmailAsyncTask : public FXAsyncTask
{
public:
	FServerSendCustomAccountRecoveryEmailAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementSendCustomAccountRecoveryEmailRequest InRequest,
	const FOnServerSendCustomAccountRecoveryEmailCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementSendCustomAccountRecoveryEmailRequest Request;
	
	FOnServerSendCustomAccountRecoveryEmailCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Sends an email based on an email template to a player's contact email 
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FServerSendEmailFromTemplateAsyncTask : public FXAsyncTask
{
public:
	FServerSendEmailFromTemplateAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementSendEmailFromTemplateRequest InRequest,
	const FOnServerSendEmailFromTemplateCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementSendEmailFromTemplateRequest Request;
	
	FOnServerSendEmailFromTemplateCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK

/// <summary>
/// Unlinks the related Battle.net account from the user's PlayFab account.
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FServerUnlinkBattleNetAccountAsyncTask : public FXAsyncTask
{
public:
	FServerUnlinkBattleNetAccountAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementServerUnlinkBattleNetAccountRequest InRequest,
	const FOnServerUnlinkBattleNetAccountCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementServerUnlinkBattleNetAccountRequest Request;
	
	FOnServerUnlinkBattleNetAccountCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Unlinks the related Nintendo account from the user's PlayFab account
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FServerUnlinkNintendoServiceAccountAsyncTask : public FXAsyncTask
{
public:
	FServerUnlinkNintendoServiceAccountAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementServerUnlinkNintendoServiceAccountRequest InRequest,
	const FOnServerUnlinkNintendoServiceAccountCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementServerUnlinkNintendoServiceAccountRequest Request;
	
	FOnServerUnlinkNintendoServiceAccountCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Unlinks the related NintendoSwitchDeviceId from the user's PlayFab account
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FServerUnlinkNintendoSwitchDeviceIdAsyncTask : public FXAsyncTask
{
public:
	FServerUnlinkNintendoSwitchDeviceIdAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementServerUnlinkNintendoSwitchDeviceIdRequest InRequest,
	const FOnServerUnlinkNintendoSwitchDeviceIdCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementServerUnlinkNintendoSwitchDeviceIdRequest Request;
	
	FOnServerUnlinkNintendoSwitchDeviceIdCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Unlinks the related PlayStation :tm: Network account from the user's PlayFab account
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also ServerLinkPSNAccountAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED or any of the global PlayFab Service errors. See
/// doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FServerUnlinkPSNAccountAsyncTask : public FXAsyncTask
{
public:
	FServerUnlinkPSNAccountAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementServerUnlinkPSNAccountRequest InRequest,
	const FOnServerUnlinkPSNAccountCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementServerUnlinkPSNAccountRequest Request;
	
	FOnServerUnlinkPSNAccountCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Unlinks the custom server identifier from the user's PlayFab account.
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also ServerLinkServerCustomIdAsync, ServerLoginWithServerCustomIdAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED, E_PF_IDENTIFIER_NOT_LINKED or any of the global
/// PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FServerUnlinkServerCustomIdAsyncTask : public FXAsyncTask
{
public:
	FServerUnlinkServerCustomIdAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementUnlinkServerCustomIdRequest InRequest,
	const FOnServerUnlinkServerCustomIdCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementUnlinkServerCustomIdRequest Request;
	
	FOnServerUnlinkServerCustomIdCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Unlinks the Steam account associated with the provided Steam ID to the user's PlayFab account 
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also ServerLinkSteamIdAsync, ServerLoginWithSteamIdAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED or any of the global PlayFab Service errors. See
/// doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FServerUnlinkSteamIdAsyncTask : public FXAsyncTask
{
public:
	FServerUnlinkSteamIdAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementUnlinkSteamIdRequest InRequest,
	const FOnServerUnlinkSteamIdCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementUnlinkSteamIdRequest Request;
	
	FOnServerUnlinkSteamIdCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Unlinks the related Xbox Live account from the user's PlayFab account
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// See also ServerLinkXboxAccountAsync.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_ACCOUNT_NOT_LINKED, E_PF_INVALID_XBOX_LIVE_TOKEN or any of the global
/// PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FServerUnlinkXboxAccountAsyncTask : public FXAsyncTask
{
public:
	FServerUnlinkXboxAccountAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementServerUnlinkXboxAccountRequest InRequest,
	const FOnServerUnlinkXboxAccountCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementServerUnlinkXboxAccountRequest Request;
	
	FOnServerUnlinkXboxAccountCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Update the avatar URL of the specified player
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be one of global PlayFab Service errors. See doc page "Handling PlayFab Errors"
/// for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FServerUpdateAvatarUrlAsyncTask : public FXAsyncTask
{
public:
	FServerUpdateAvatarUrlAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementServerUpdateAvatarUrlRequest InRequest,
	const FOnServerUpdateAvatarUrlCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementServerUpdateAvatarUrlRequest Request;
	
	FOnServerUpdateAvatarUrlCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Updates information of a list of existing bans specified with Ban Ids.
/// </summary>
/// <param name="titleEntityHandle">FPFEntityHandle for a title Entity obtained using PFAuthenticationGetEntityWithSecretKeyAsync.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FServerUpdateBansAsyncTask : public FXAsyncTask
{
public:
	FServerUpdateBansAsyncTask(
	_In_ FPFEntityHandle TitleEntityHandle,
	FPFAccountManagementUpdateBansRequest InRequest,
	const FOnServerUpdateBansCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle TitleEntityHandle;
	
	FPFAccountManagementUpdateBansRequest Request;
	
	FOnServerUpdateBansCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Retrieves the title player accounts associated with the given XUIDs.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// Given a collection of Xbox IDs (XUIDs), returns all title player accounts.
///
/// When the asynchronous task is complete, call <see cref="PFAccountManagementGetTitlePlayersFromXboxLiveIDsGetResultSize"/>
/// and <see cref="PFAccountManagementGetTitlePlayersFromXboxLiveIDsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FGetTitlePlayersFromXboxLiveIDsAsyncTask : public FXAsyncTask
{
public:
	FGetTitlePlayersFromXboxLiveIDsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementGetTitlePlayersFromXboxLiveIDsRequest InRequest,
	const FOnGetTitlePlayersFromXboxLiveIDsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementGetTitlePlayersFromXboxLiveIDsRequest Request;
	
	FOnGetTitlePlayersFromXboxLiveIDsCompleted Delegate;

	HRESULT HResult;
};

#endif


/// <summary>
/// Update the display name of the entity
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Given an entity profile, will update its display name to the one passed in if the profile's version
/// is equal to the specified value See also ProfileGetProfileAsync.
///
/// When the asynchronous task is complete, call <see cref="PFAccountManagementSetDisplayNameGetResultSize"/>
/// and <see cref="PFAccountManagementSetDisplayNameGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FSetDisplayNameAsyncTask : public FXAsyncTask
{
public:
	FSetDisplayNameAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFAccountManagementSetDisplayNameRequest InRequest,
	const FOnSetDisplayNameCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFAccountManagementSetDisplayNameRequest Request;
	
	FOnSetDisplayNameCompleted Delegate;

	HRESULT HResult;
};

