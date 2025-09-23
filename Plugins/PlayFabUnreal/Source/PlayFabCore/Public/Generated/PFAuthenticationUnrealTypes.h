// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once
#include "Generated/PFCoreUnrealTypes.h"
#include "PFEntity.h"
#include "PFServiceConfig.h"



 
/// <summary>
/// FPFAuthenticationIdentifiedDeviceType enum.
/// </summary>
enum class FPFAuthenticationIdentifiedDeviceType : uint32_t
{
	Unknown,
	XboxOne,
	Scarlett,
	WindowsOneCore,
	WindowsOneCoreMobile,
	Win32,
	android,
	iOS,
	PlayStation,
	Nintendo
};



struct FPFAuthenticationLoginWithAndroidDeviceIDRequest
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
	/// Automatically create a PlayFab account if one is not currently linked to this ID.
	/// </summary>
	bool createAccount;

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
	/// (Optional) Flags for which pieces of info to return for the user.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFGetPlayerCombinedInfoRequestParams> infoRequestParameters;

	/// <summary>
	/// (Optional) Specific Operating System version for the user's device.
	/// </summary>
	_Maybenull_ const FString OS;

	/// <summary>
	/// (Optional) Player secret that is used to verify API request signatures (Enterprise Only).
	/// </summary>
	_Maybenull_ const FString playerSecret;

};



struct FPFAuthenticationUserSettings
{
	/// <summary>
	/// Boolean for whether this player is eligible for gathering device info.
	/// </summary>
	bool gatherDeviceInfo;

	/// <summary>
	/// Boolean for whether this player should report OnFocus play-time tracking.
	/// </summary>
	bool gatherFocusInfo;

	/// <summary>
	/// Boolean for whether this player is eligible for ad tracking.
	/// </summary>
	bool needsAttribution;

};



struct FPFAuthenticationLoginResult
{
	/// <summary>
	/// (Optional) Results for requested info.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFGetPlayerCombinedInfoResultPayload> infoResultPayload;

	/// <summary>
	/// (Optional) The time of this user's previous login. If there was no previous login, then it's DateTime.MinValue.
	/// </summary>
	_Maybenull_ TSharedPtr<const FDateTime> lastLoginTime;

	/// <summary>
	/// True if the master_player_account was newly created on this login.
	/// </summary>
	bool newlyCreated;

	/// <summary>
	/// (Optional) Player's unique PlayFabId.
	/// </summary>
	_Maybenull_ const FString playFabId;

	/// <summary>
	/// (Optional) Settings specific to this user.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFAuthenticationUserSettings> settingsForUser;

	/// <summary>
	/// (Optional) The experimentation treatments for this user at the time of login.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFTreatmentAssignment> treatmentAssignment;

};



struct FPFAuthenticationLoginWithAppleRequest
{
	/// <summary>
	/// Automatically create a PlayFab account if one is not currently linked to this ID.
	/// </summary>
	bool createAccount;

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
	/// The JSON Web token (JWT) returned by Apple after login. Represented as the identityToken field in
	/// the authorization credential payload. If you choose to ignore the expiration date for identity tokens,
	/// you will receive an NotAuthorized error if Apple rotates the signing key. In this case, users have
	/// to login to provide a fresh identity token.
	/// </summary>
	const FString identityToken;

	/// <summary>
	/// (Optional) Flags for which pieces of info to return for the user.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFGetPlayerCombinedInfoRequestParams> infoRequestParameters;

	/// <summary>
	/// (Optional) Player secret that is used to verify API request signatures (Enterprise Only).
	/// </summary>
	_Maybenull_ const FString playerSecret;

};



struct FPFAuthenticationLoginWithBattleNetRequest
{
	/// <summary>
	/// Automatically create a PlayFab account if one is not currently linked to this ID.
	/// </summary>
	bool createAccount;

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
	/// The JSON Web Token (JWT) returned by Battle.net after login.
	/// </summary>
	const FString identityToken;

	/// <summary>
	/// (Optional) Flags for which pieces of info to return for the user.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFGetPlayerCombinedInfoRequestParams> infoRequestParameters;

	/// <summary>
	/// (Optional) Player secret that is used to verify API request signatures (Enterprise Only).
	/// </summary>
	_Maybenull_ const FString playerSecret;

};



struct FPFAuthenticationLoginWithCustomIDRequest
{
	/// <summary>
	/// Automatically create a PlayFab account if one is not currently linked to this ID.
	/// </summary>
	bool createAccount;

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
	/// (Optional) Flags for which pieces of info to return for the user.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFGetPlayerCombinedInfoRequestParams> infoRequestParameters;

	/// <summary>
	/// (Optional) Player secret that is used to verify API request signatures (Enterprise Only).
	/// </summary>
	_Maybenull_ const FString playerSecret;

};



struct FPFAuthenticationLoginWithEmailAddressRequest
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
	/// Email address for the account.
	/// </summary>
	const FString email;

	/// <summary>
	/// (Optional) Flags for which pieces of info to return for the user.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFGetPlayerCombinedInfoRequestParams> infoRequestParameters;

	/// <summary>
	/// Password for the PlayFab account (6-100 characters).
	/// </summary>
	const FString password;

};



struct FPFAuthenticationLoginWithFacebookRequest
{
	/// <summary>
	/// Unique identifier from Facebook for the user.
	/// </summary>
	const FString accessToken;

	/// <summary>
	/// (Optional) Token used for limited login authentication.
	/// </summary>
	_Maybenull_ const FString authenticationToken;

	/// <summary>
	/// Automatically create a PlayFab account if one is not currently linked to this ID.
	/// </summary>
	bool createAccount;

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
	/// (Optional) Flags for which pieces of info to return for the user.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFGetPlayerCombinedInfoRequestParams> infoRequestParameters;

	/// <summary>
	/// (Optional) Player secret that is used to verify API request signatures (Enterprise Only).
	/// </summary>
	_Maybenull_ const FString playerSecret;

};



struct FPFAuthenticationLoginWithFacebookInstantGamesIdRequest
{
	/// <summary>
	/// Automatically create a PlayFab account if one is not currently linked to this ID.
	/// </summary>
	bool createAccount;

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
	/// (Optional) Flags for which pieces of info to return for the user.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFGetPlayerCombinedInfoRequestParams> infoRequestParameters;

	/// <summary>
	/// (Optional) Player secret that is used to verify API request signatures (Enterprise Only).
	/// </summary>
	_Maybenull_ const FString playerSecret;

};



struct FPFAuthenticationLoginWithGameCenterRequest
{
	/// <summary>
	/// Automatically create a PlayFab account if one is not currently linked to this ID.
	/// </summary>
	bool createAccount;

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
	/// (Optional) Flags for which pieces of info to return for the user.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFGetPlayerCombinedInfoRequestParams> infoRequestParameters;

	/// <summary>
	/// (Optional) Unique Game Center player id.
	/// </summary>
	_Maybenull_ const FString playerId;

	/// <summary>
	/// (Optional) Player secret that is used to verify API request signatures (Enterprise Only).
	/// </summary>
	_Maybenull_ const FString playerSecret;

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



struct FPFAuthenticationLoginWithGoogleAccountRequest
{
	/// <summary>
	/// Automatically create a PlayFab account if one is not currently linked to this ID.
	/// </summary>
	bool createAccount;

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
	/// (Optional) Flags for which pieces of info to return for the user.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFGetPlayerCombinedInfoRequestParams> infoRequestParameters;

	/// <summary>
	/// (Optional) Player secret that is used to verify API request signatures (Enterprise Only).
	/// </summary>
	_Maybenull_ const FString playerSecret;

	/// <summary>
	/// OAuth 2.0 server authentication code obtained on the client by calling the getServerAuthCode() (https://developers.google.com/identity/sign-in/android/offline-access)
	/// Google client API.
	/// </summary>
	const FString serverAuthCode;

	/// <summary>
	/// (Optional) Optional boolean to opt out of setting the MPA email when creating a Google account,
	/// defaults to true.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> setEmail;

};



struct FPFAuthenticationLoginWithGooglePlayGamesServicesRequest
{
	/// <summary>
	/// Automatically create a PlayFab account if one is not currently linked to this ID.
	/// </summary>
	bool createAccount;

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
	/// (Optional) Flags for which pieces of info to return for the user.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFGetPlayerCombinedInfoRequestParams> infoRequestParameters;

	/// <summary>
	/// (Optional) Player secret that is used to verify API request signatures (Enterprise Only).
	/// </summary>
	_Maybenull_ const FString playerSecret;

	/// <summary>
	/// OAuth 2.0 server authentication code obtained on the client by calling the requestServerSideAccess()
	/// (https://developers.google.com/games/services/android/signin) Google Play Games client API.
	/// </summary>
	const FString serverAuthCode;

};



struct FPFAuthenticationLoginWithIOSDeviceIDRequest
{
	/// <summary>
	/// Automatically create a PlayFab account if one is not currently linked to this ID.
	/// </summary>
	bool createAccount;

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
	/// (Optional) Flags for which pieces of info to return for the user.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFGetPlayerCombinedInfoRequestParams> infoRequestParameters;

	/// <summary>
	/// (Optional) Specific Operating System version for the user's device.
	/// </summary>
	_Maybenull_ const FString OS;

	/// <summary>
	/// (Optional) Player secret that is used to verify API request signatures (Enterprise Only).
	/// </summary>
	_Maybenull_ const FString playerSecret;

};



struct FPFAuthenticationLoginWithKongregateRequest
{
	/// <summary>
	/// Token issued by Kongregate's client API for the user.
	/// </summary>
	const FString authTicket;

	/// <summary>
	/// Automatically create a PlayFab account if one is not currently linked to this ID.
	/// </summary>
	bool createAccount;

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
	/// (Optional) Flags for which pieces of info to return for the user.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFGetPlayerCombinedInfoRequestParams> infoRequestParameters;

	/// <summary>
	/// Numeric user ID assigned by Kongregate.
	/// </summary>
	const FString kongregateId;

	/// <summary>
	/// (Optional) Player secret that is used to verify API request signatures (Enterprise Only).
	/// </summary>
	_Maybenull_ const FString playerSecret;

};



struct FPFAuthenticationLoginWithNintendoServiceAccountRequest
{
	/// <summary>
	/// Automatically create a PlayFab account if one is not currently linked to this ID.
	/// </summary>
	bool createAccount;

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
	/// The JSON Web token (JWT) returned by Nintendo after login.
	/// </summary>
	const FString identityToken;

	/// <summary>
	/// (Optional) Flags for which pieces of info to return for the user.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFGetPlayerCombinedInfoRequestParams> infoRequestParameters;

	/// <summary>
	/// (Optional) Player secret that is used to verify API request signatures (Enterprise Only).
	/// </summary>
	_Maybenull_ const FString playerSecret;

};



struct FPFAuthenticationLoginWithNintendoSwitchDeviceIdRequest
{
	/// <summary>
	/// Automatically create a PlayFab account if one is not currently linked to this ID.
	/// </summary>
	bool createAccount;

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
	/// (Optional) Flags for which pieces of info to return for the user.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFGetPlayerCombinedInfoRequestParams> infoRequestParameters;

	/// <summary>
	/// (Optional) Nintendo Switch unique identifier for the user's device.
	/// </summary>
	_Maybenull_ const FString nintendoSwitchDeviceId;

	/// <summary>
	/// (Optional) Player secret that is used to verify API request signatures (Enterprise Only).
	/// </summary>
	_Maybenull_ const FString playerSecret;

};



struct FPFAuthenticationLoginWithOpenIdConnectRequest
{
	/// <summary>
	/// A name that identifies which configured OpenID Connect provider relationship to use. Maximum 100
	/// characters.
	/// </summary>
	const FString connectionId;

	/// <summary>
	/// Automatically create a PlayFab account if one is not currently linked to this ID.
	/// </summary>
	bool createAccount;

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
	/// The JSON Web token (JWT) returned by the identity provider after login. Represented as the id_token
	/// field in the identity provider's response.
	/// </summary>
	const FString idToken;

	/// <summary>
	/// (Optional) Flags for which pieces of info to return for the user.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFGetPlayerCombinedInfoRequestParams> infoRequestParameters;

	/// <summary>
	/// (Optional) Player secret that is used to verify API request signatures (Enterprise Only).
	/// </summary>
	_Maybenull_ const FString playerSecret;

};



struct FPFAuthenticationLoginWithPlayFabRequest
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
	/// (Optional) Flags for which pieces of info to return for the user.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFGetPlayerCombinedInfoRequestParams> infoRequestParameters;

	/// <summary>
	/// Password for the PlayFab account (6-100 characters).
	/// </summary>
	const FString password;

	/// <summary>
	/// PlayFab username for the account.
	/// </summary>
	const FString username;

};



struct FPFAuthenticationLoginWithPSNRequest
{
	/// <summary>
	/// Auth code provided by the PlayStation :tm: Network OAuth provider.
	/// </summary>
	const FString authCode;

	/// <summary>
	/// Automatically create a PlayFab account if one is not currently linked to this ID.
	/// </summary>
	bool createAccount;

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
	/// (Optional) Flags for which pieces of info to return for the user.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFGetPlayerCombinedInfoRequestParams> infoRequestParameters;

	/// <summary>
	/// (Optional) Id of the PlayStation :tm: Network issuer environment. If null, defaults to production
	/// environment.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> issuerId;

	/// <summary>
	/// (Optional) Player secret that is used to verify API request signatures (Enterprise Only).
	/// </summary>
	_Maybenull_ const FString playerSecret;

	/// <summary>
	/// (Optional) Redirect URI supplied to PlayStation :tm: Network when requesting an auth code.
	/// </summary>
	_Maybenull_ const FString redirectUri;

};



struct FPFAuthenticationLoginWithSteamRequest
{
	/// <summary>
	/// Automatically create a PlayFab account if one is not currently linked to this ID.
	/// </summary>
	bool createAccount;

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
	/// (Optional) Flags for which pieces of info to return for the user.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFGetPlayerCombinedInfoRequestParams> infoRequestParameters;

	/// <summary>
	/// (Optional) Player secret that is used to verify API request signatures (Enterprise Only).
	/// </summary>
	_Maybenull_ const FString playerSecret;

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



struct FPFAuthenticationLoginWithTwitchRequest
{
	/// <summary>
	/// Token issued by Twitch's API for the user.
	/// </summary>
	const FString accessToken;

	/// <summary>
	/// Automatically create a PlayFab account if one is not currently linked to this ID.
	/// </summary>
	bool createAccount;

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
	/// (Optional) Flags for which pieces of info to return for the user.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFGetPlayerCombinedInfoRequestParams> infoRequestParameters;

	/// <summary>
	/// (Optional) Player secret that is used to verify API request signatures (Enterprise Only).
	/// </summary>
	_Maybenull_ const FString playerSecret;

};



struct FPFAuthenticationLoginWithXboxRequest
{
	/// <summary>
	/// Automatically create a PlayFab account if one is not currently linked to this ID.
	/// </summary>
	bool createAccount;

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
	/// (Optional) Flags for which pieces of info to return for the user.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFGetPlayerCombinedInfoRequestParams> infoRequestParameters;

	/// <summary>
	/// (Optional) Player secret that is used to verify API request signatures (Enterprise Only).
	/// </summary>
	_Maybenull_ const FString playerSecret;

	/// <summary>
	/// Token provided by the Xbox Live SDK/XDK method GetTokenAndSignatureAsync("POST", "https://playfabapi.com/",
	/// "").
	/// </summary>
	const FString xboxToken;

};



struct FPFAuthenticationRegisterPlayFabUserRequest
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
	/// (Optional) An optional parameter for setting the display name for this title (3-25 characters).
	/// </summary>
	_Maybenull_ const FString displayName;

	/// <summary>
	/// (Optional) User email address attached to their account.
	/// </summary>
	_Maybenull_ const FString email;

	/// <summary>
	/// (Optional) Base64 encoded body that is encrypted with the Title's public RSA key (Enterprise Only).
	/// </summary>
	_Maybenull_ const FString encryptedRequest;

	/// <summary>
	/// (Optional) Flags for which pieces of info to return for the user.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFGetPlayerCombinedInfoRequestParams> infoRequestParameters;

	/// <summary>
	/// (Optional) Password for the PlayFab account (6-100 characters).
	/// </summary>
	_Maybenull_ const FString password;

	/// <summary>
	/// (Optional) Player secret that is used to verify API request signatures (Enterprise Only).
	/// </summary>
	_Maybenull_ const FString playerSecret;

	/// <summary>
	/// (Optional) An optional parameter that specifies whether both the username and email parameters are
	/// required. If true, both parameters are required; if false, the user must supply either the username
	/// or email parameter. The default value is true.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> requireBothUsernameAndEmail;

	/// <summary>
	/// Unique identifier for the title, found in the Settings > Game Properties section of the PlayFab
	/// developer site when a title has been selected.
	/// </summary>
	const FString titleId;

	/// <summary>
	/// (Optional) PlayFab username for the account (3-20 characters).
	/// </summary>
	_Maybenull_ const FString username;

};



struct FPFAuthenticationRegisterPlayFabUserResult
{
	/// <summary>
	/// (Optional) PlayFab unique identifier for this newly created account.
	/// </summary>
	_Maybenull_ const FString playFabId;

	/// <summary>
	/// (Optional) Settings specific to this user.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFAuthenticationUserSettings> settingsForUser;

	/// <summary>
	/// (Optional) PlayFab unique user name.
	/// </summary>
	_Maybenull_ const FString username;

};



struct FPFAuthenticationServerLoginWithAndroidDeviceIDRequest
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
	/// Automatically create a PlayFab account if one is not currently linked to this ID.
	/// </summary>
	bool createAccount;

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
	/// (Optional) Flags for which pieces of info to return for the user.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFGetPlayerCombinedInfoRequestParams> infoRequestParameters;

	/// <summary>
	/// (Optional) Specific Operating System version for the user's device.
	/// </summary>
	_Maybenull_ const FString OS;

};



struct FPFAuthenticationServerLoginWithBattleNetRequest
{
	/// <summary>
	/// Automatically create a PlayFab account if one is not currently linked to this ID.
	/// </summary>
	bool createAccount;

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
	/// The JSON Web Token (JWT) returned by Battle.net after login.
	/// </summary>
	const FString identityToken;

	/// <summary>
	/// (Optional) Flags for which pieces of info to return for the user.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFGetPlayerCombinedInfoRequestParams> infoRequestParameters;

};



struct FPFAuthenticationServerLoginWithCustomIDRequest
{
	/// <summary>
	/// Automatically create a PlayFab account if one is not currently linked to this ID.
	/// </summary>
	bool createAccount;

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
	/// (Optional) Flags for which pieces of info to return for the user.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFGetPlayerCombinedInfoRequestParams> infoRequestParameters;

};



struct FPFAuthenticationServerLoginWithIOSDeviceIDRequest
{
	/// <summary>
	/// Automatically create a PlayFab account if one is not currently linked to this ID.
	/// </summary>
	bool createAccount;

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
	/// (Optional) Flags for which pieces of info to return for the user.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFGetPlayerCombinedInfoRequestParams> infoRequestParameters;

	/// <summary>
	/// (Optional) Specific Operating System version for the user's device.
	/// </summary>
	_Maybenull_ const FString OS;

};



struct FPFAuthenticationServerLoginWithPSNRequest
{
	/// <summary>
	/// Auth code provided by the PlayStation :tm: Network OAuth provider.
	/// </summary>
	const FString authCode;

	/// <summary>
	/// Automatically create a PlayFab account if one is not currently linked to this ID.
	/// </summary>
	bool createAccount;

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
	/// (Optional) Flags for which pieces of info to return for the user.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFGetPlayerCombinedInfoRequestParams> infoRequestParameters;

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



struct FPFAuthenticationLoginWithServerCustomIdRequest
{
	/// <summary>
	/// Automatically create a PlayFab account if one is not currently linked to this ID.
	/// </summary>
	bool createAccount;

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
	/// (Optional) Flags for which pieces of info to return for the user.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFGetPlayerCombinedInfoRequestParams> infoRequestParameters;

	/// <summary>
	/// (Optional) Player secret that is used to verify API request signatures (Enterprise Only).
	/// </summary>
	_Maybenull_ const FString playerSecret;

	/// <summary>
	/// The backend server identifier for this player.
	/// </summary>
	const FString serverCustomId;

};



struct FPFAuthenticationLoginWithSteamIdRequest
{
	/// <summary>
	/// Automatically create a PlayFab account if one is not currently linked to this ID.
	/// </summary>
	bool createAccount;

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
	/// (Optional) Flags for which pieces of info to return for the user.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFGetPlayerCombinedInfoRequestParams> infoRequestParameters;

	/// <summary>
	/// Unique Steam identifier for a user.
	/// </summary>
	const FString steamId;

};



struct FPFAuthenticationServerLoginWithXboxRequest
{
	/// <summary>
	/// Automatically create a PlayFab account if one is not currently linked to this ID.
	/// </summary>
	bool createAccount;

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
	/// (Optional) Flags for which pieces of info to return for the user.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFGetPlayerCombinedInfoRequestParams> infoRequestParameters;

	/// <summary>
	/// Token provided by the Xbox Live SDK/XDK method GetTokenAndSignatureAsync("POST", "https://playfabapi.com/",
	/// "").
	/// </summary>
	const FString xboxToken;

};



struct FPFAuthenticationLoginWithXboxIdRequest
{
	/// <summary>
	/// Automatically create a PlayFab account if one is not currently linked to this ID.
	/// </summary>
	bool createAccount;

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
	/// (Optional) Flags for which pieces of info to return for the user.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFGetPlayerCombinedInfoRequestParams> infoRequestParameters;

	/// <summary>
	/// The id of Xbox Live sandbox.
	/// </summary>
	const FString sandbox;

	/// <summary>
	/// Unique Xbox identifier for a user.
	/// </summary>
	const FString xboxId;

};



struct FPFAuthenticationAuthenticateCustomIdRequest
{
	/// <summary>
	/// The customId used to create and retrieve game_server entity tokens. This is unique at the title
	/// level. CustomId must be between 32 and 100 characters.
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

};



struct FPFAuthenticationEntityTokenResponse
{
	/// <summary>
	/// (Optional) The entity id and type.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) The token used to set X-EntityToken for all entity based API calls.
	/// </summary>
	_Maybenull_ const FString entityToken;

	/// <summary>
	/// (Optional) The time the token will expire, if it is an expiring token, in UTC.
	/// </summary>
	_Maybenull_ TSharedPtr<const FDateTime> tokenExpiration;

};



struct FPFAuthenticationAuthenticateCustomIdResult
{
	/// <summary>
	/// (Optional) The token generated used to set X-EntityToken for game_server calls.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFAuthenticationEntityTokenResponse> entityToken;

	/// <summary>
	/// True if the account was newly created on this authentication.
	/// </summary>
	bool newlyCreated;

};



struct FPFAuthenticationDeleteRequest
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
	/// The game_server entity to be removed.
	/// </summary>
	TSharedPtr<const FPFEntityKey> entity;

};



struct FPFAuthenticationGetEntityRequest
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
	/// (Optional) The optional entity to perform this action on. Defaults to the currently logged in entity.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

};



struct FPFAuthenticationValidateEntityTokenRequest
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
	/// Client EntityToken.
	/// </summary>
	const FString entityToken;

};



struct FPFAuthenticationValidateEntityTokenResponse
{
	/// <summary>
	/// (Optional) The entity id and type.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) The authenticated device for this entity, for the given login.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFAuthenticationIdentifiedDeviceType> identifiedDeviceType;

	/// <summary>
	/// (Optional) The identity provider for this entity, for the given login.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFLoginIdentityProvider> identityProvider;

	/// <summary>
	/// (Optional) The ID issued by the identity provider, e.g. a XUID on Xbox Live.
	/// </summary>
	_Maybenull_ const FString identityProviderIssuedId;

	/// <summary>
	/// (Optional) The lineage of this profile.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityLineage> lineage;

};

// Delegates Declarations

DECLARE_DELEGATE_ThreeParams(FOnPFAuthenticationLoginCompleteDelegate, const FPFAuthenticationLoginResult*, FPFEntityHandle*, bool);
 
DECLARE_DELEGATE_ThreeParams(FOnPFAuthenticationServerLoginCompleteDelegate, const FPFAuthenticationLoginResult*, PFAuthenticationEntityTokenResponse const**, bool);

#if 0
DECLARE_DELEGATE_TwoParams(FOnRegisterPlayFabUserDelegate, const FPFAuthenticationRegisterPlayFabUserResult*, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_ThreeParams(FOnAuthenticateGameServerWithCustomIdDelegate, FPFEntityHandle*, bool*, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_OneParam(FOnDeleteDelegate, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnGetEntityDelegate, FPFEntityHandle*, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnGetEntityWithSecretKeyDelegate, FPFEntityHandle*, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnValidateEntityTokenDelegate, const FPFAuthenticationValidateEntityTokenResponse*, bool);
#endif
