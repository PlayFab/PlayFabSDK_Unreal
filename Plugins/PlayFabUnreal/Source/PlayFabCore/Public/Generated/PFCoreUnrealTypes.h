// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once
#include "CoreMinimal.h"
#if PLATFORM_WINDOWS || (defined(PLATFORM_XSX) && PLATFORM_XSX) || (defined(PLATFORM_XB1) && PLATFORM_XB1)
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/AllowWindowsPlatformAtomics.h"
#endif
THIRD_PARTY_INCLUDES_START
#include <playfab/core/PFCore.h>
THIRD_PARTY_INCLUDES_END
#if PLATFORM_WINDOWS || (defined(PLATFORM_XSX) && PLATFORM_XSX) || (defined(PLATFORM_XB1) && PLATFORM_XB1)
#include "Windows/HideWindowsPlatformAtomics.h"
#include "Windows/HideWindowsPlatformTypes.h"
#endif
#pragma push_macro("IN")
#undef IN


/// <summary>
/// FPFTitleActivationStatus enum.
/// </summary>
enum class FPFTitleActivationStatus : uint32_t
{
	None,
	ActivatedTitleKey,
	PendingSteam,
	ActivatedSteam,
	RevokedSteam
};

#if HC_PLATFORM_IS_PLAYSTATION
#pragma push_macro("BSD")
#endif
#undef BSD

/// <summary>
/// FPFCurrency enum.
/// </summary>
enum class FPFCurrency : uint32_t
{
	AED,
	AFN,
	ALL,
	AMD,
	ANG,
	AOA,
	ARS,
	AUD,
	AWG,
	AZN,
	BAM,
	BBD,
	BDT,
	BGN,
	BHD,
	BIF,
	BMD,
	BND,
	BOB,
	BRL,
	BSD,
	BTN,
	BWP,
	BYR,
	BZD,
	CAD,
	CDF,
	CHF,
	CLP,
	CNY,
	COP,
	CRC,
	CUC,
	CUP,
	CVE,
	CZK,
	DJF,
	DKK,
	DOP,
	DZD,
	EGP,
	ERN,
	ETB,
	EUR,
	FJD,
	FKP,
	GBP,
	GEL,
	GGP,
	GHS,
	GIP,
	GMD,
	GNF,
	GTQ,
	GYD,
	HKD,
	HNL,
	HRK,
	HTG,
	HUF,
	IDR,
	ILS,
	IMP,
	INR,
	IQD,
	IRR,
	ISK,
	JEP,
	JMD,
	JOD,
	JPY,
	KES,
	KGS,
	KHR,
	KMF,
	KPW,
	KRW,
	KWD,
	KYD,
	KZT,
	LAK,
	LBP,
	LKR,
	LRD,
	LSL,
	LYD,
	MAD,
	MDL,
	MGA,
	MKD,
	MMK,
	MNT,
	MOP,
	MRO,
	MUR,
	MVR,
	MWK,
	MXN,
	MYR,
	MZN,
	NAD,
	NGN,
	NIO,
	NOK,
	NPR,
	NZD,
	OMR,
	PAB,
	PEN,
	PGK,
	PHP,
	PKR,
	PLN,
	PYG,
	QAR,
	RON,
	RSD,
	RUB,
	RWF,
	SAR,
	SBD,
	SCR,
	SDG,
	SEK,
	SGD,
	SHP,
	SLL,
	SOS,
	SPL,
	SRD,
	STD,
	SVC,
	SYP,
	SZL,
	THB,
	TJS,
	TMT,
	TND,
	TOP,
	TRY,
	TTD,
	TVD,
	TWD,
	TZS,
	UAH,
	UGX,
	USD,
	UYU,
	UZS,
	VEF,
	VND,
	VUV,
	WST,
	XAF,
	XCD,
	XDR,
	XOF,
	XPF,
	YER,
	ZAR,
	ZMW,
	ZWD
};

/// <summary>
/// FPFUserOrigination enum.
/// </summary>
enum class FPFUserOrigination : uint32_t
{
	Organic,
	Steam,
	Google,
	Amazon,
	Facebook,
	Kongregate,
	GamersFirst,
	Unknown,
	IOS,
	LoadTest,
	Android,
	PSN,
	GameCenter,
	CustomId,
	XboxLive,
	Parse,
	Twitch,
	ServerCustomId,
	NintendoSwitchDeviceId,
	FacebookInstantGamesId,
	OpenIdConnect,
	Apple,
	NintendoSwitchAccount,
	GooglePlayGames,
	XboxMobileStore,
	King,
	BattleNet
};

/// <summary>
/// FPFUserDataPermission enum.
/// </summary>
enum class FPFUserDataPermission : uint32_t
{
	Private,
	Public
};

/// <summary>
/// FPFEmailVerificationStatus enum.
/// </summary>
enum class FPFEmailVerificationStatus : uint32_t
{
	Unverified,
	Pending,
	Confirmed
};

/// <summary>
/// FPFLoginIdentityProvider enum.
/// </summary>
enum class FPFLoginIdentityProvider : uint32_t
{
	Unknown,
	PlayFab,
	Custom,
	GameCenter,
	GooglePlay,
	Steam,
	XBoxLive,
	PSN,
	Kongregate,
	Facebook,
	IOSDevice,
	AndroidDevice,
	Twitch,
	WindowsHello,
	GameServer,
	CustomServer,
	NintendoSwitch,
	FacebookInstantGames,
	OpenIdConnect,
	Apple,
	NintendoSwitchAccount,
	GooglePlayGames,
	XboxMobileStore,
	King,
	BattleNet
};

/// <summary>
/// FPFContinentCode enum.
/// </summary>
enum class FPFContinentCode : uint32_t
{
	AF,
	AN,
	AS,
	EU,
	NA,
	OC,
	SA,
	Unknown
};

/// <summary>
/// FPFCountryCode enum.
/// </summary>
enum class FPFCountryCode : uint32_t
{
	AF,
	AX,
	AL,
	DZ,
	AS,
	AD,
	AO,
	AI,
	AQ,
	AG,
	AR,
	AM,
	AW,
	AU,
	AT,
	AZ,
	BS,
	BH,
	BD,
	BB,
	BY,
	BE,
	BZ,
	BJ,
	BM,
	BT,
	BO,
	BQ,
	BA,
	BW,
	BV,
	BR,
	IO,
	BN,
	BG,
	BF,
	BI,
	KH,
	CM,
	CA,
	CV,
	KY,
	CF,
	TD,
	CL,
	CN,
	CX,
	CC,
	CO,
	KM,
	CG,
	CD,
	CK,
	CR,
	CI,
	HR,
	CU,
	CW,
	CY,
	CZ,
	DK,
	DJ,
	DM,
	DO,
	EC,
	EG,
	SV,
	GQ,
	ER,
	EE,
	ET,
	FK,
	FO,
	FJ,
	FI,
	FR,
	GF,
	PF,
	TF,
	GA,
	GM,
	GE,
	DE,
	GH,
	GI,
	GR,
	GL,
	GD,
	GP,
	GU,
	GT,
	GG,
	GN,
	GW,
	GY,
	HT,
	HM,
	VA,
	HN,
	HK,
	HU,
	IS,
	IN,
	ID,
	IR,
	IQ,
	IE,
	IM,
	IL,
	IT,
	JM,
	JP,
	JE,
	JO,
	KZ,
	KE,
	KI,
	KP,
	KR,
	KW,
	KG,
	LA,
	LV,
	LB,
	LS,
	LR,
	LY,
	LI,
	LT,
	LU,
	MO,
	MK,
	MG,
	MW,
	MY,
	MV,
	ML,
	MT,
	MH,
	MQ,
	MR,
	MU,
	YT,
	MX,
	FM,
	MD,
	MC,
	MN,
	ME,
	MS,
	MA,
	MZ,
	MM,
	NA,
	NR,
	NP,
	NL,
	NC,
	NZ,
	NI,
	NE,
	NG,
	NU,
	NF,
	MP,
	NO,
	OM,
	PK,
	PW,
	PS,
	PA,
	PG,
	PY,
	PE,
	PH,
	PN,
	PL,
	PT,
	PR,
	QA,
	RE,
	RO,
	RU,
	RW,
	BL,
	SH,
	KN,
	LC,
	MF,
	PM,
	VC,
	WS,
	SM,
	ST,
	SA,
	SN,
	RS,
	SC,
	SL,
	SG,
	SX,
	SK,
	SI,
	SB,
	SO,
	ZA,
	GS,
	SS,
	ES,
	LK,
	SD,
	SR,
	SJ,
	SZ,
	SE,
	CH,
	SY,
	TW,
	TJ,
	TZ,
	TH,
	TL,
	TG,
	TK,
	TO,
	TT,
	TN,
	TR,
	TM,
	TC,
	TV,
	UG,
	UA,
	AE,
	GB,
	US,
	UM,
	UY,
	UZ,
	VU,
	VE,
	VN,
	VG,
	VI,
	WF,
	EH,
	YE,
	ZM,
	ZW,
	Unknown
};

/// <summary>
/// FPFSubscriptionProviderStatus enum.
/// </summary>
enum class FPFSubscriptionProviderStatus : uint32_t
{
	NoError,
	Cancelled,
	UnknownError,
	BillingError,
	ProductUnavailable,
	CustomerDidNotAcceptPriceChange,
	FreeTrial,
	PaymentPending
};

/// <summary>
/// FPFPushNotificationPlatform enum.
/// </summary>
enum class FPFPushNotificationPlatform : uint32_t
{
	ApplePushNotificationService,
	GoogleCloudMessaging
};



/// <summary>
/// FPFItemInstance data model. A unique instance of an item in a user's inventory. Note, to retrieve
/// additional information for an item such as Tags, Description that are the same across all instances
/// of the item, a call to GetCatalogItems is required. The ItemID of can be matched to a catalog entry,
/// which contains the additional information. Also note that Custom Data is only set when the User's
/// specific instance has updated the CustomData via a call to UpdateUserInventoryItemCustomData. Other
/// fields such as UnitPrice and UnitCurrency are only set when the item was granted via a purchase.
/// </summary>
struct PLAYFABCORE_API FPFItemInstance
{
	/// <summary>
	/// (Optional) Game specific comment associated with this instance when it was added to the user inventory.
	/// </summary>
	_Maybenull_ const FString annotation;

	/// <summary>
	/// (Optional) Array of unique items that were awarded when this catalog item was purchased.
	/// </summary>
	_Maybenull_ const TArray<FString> bundleContents;

	/// <summary>
	/// Count of bundleContents
	/// </summary>
	uint32 bundleContentsCount;

	/// <summary>
	/// (Optional) Unique identifier for the parent inventory item, as defined in the catalog, for object
	/// which were added from a bundle or container.
	/// </summary>
	_Maybenull_ const FString bundleParent;

	/// <summary>
	/// (Optional) Catalog version for the inventory item, when this instance was created.
	/// </summary>
	_Maybenull_ const FString catalogVersion;

	/// <summary>
	/// (Optional) A set of custom key-value pairs on the instance of the inventory item, which is not to
	/// be confused with the catalog item's custom data.
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customData;

	/// <summary>
	/// Count of customData
	/// </summary>
	uint32 customDataCount;

	/// <summary>
	/// (Optional) CatalogItem.DisplayName at the time this item was purchased.
	/// </summary>
	_Maybenull_ const FString displayName;

	/// <summary>
	/// (Optional) Timestamp for when this instance will expire.
	/// </summary>
	_Maybenull_ TSharedPtr<const FDateTime> expiration;

	/// <summary>
	/// (Optional) Class name for the inventory item, as defined in the catalog.
	/// </summary>
	_Maybenull_ const FString itemClass;

	/// <summary>
	/// (Optional) Unique identifier for the inventory item, as defined in the catalog.
	/// </summary>
	_Maybenull_ const FString itemId;

	/// <summary>
	/// (Optional) Unique item identifier for this specific instance of the item.
	/// </summary>
	_Maybenull_ const FString itemInstanceId;

	/// <summary>
	/// (Optional) Timestamp for when this instance was purchased.
	/// </summary>
	_Maybenull_ TSharedPtr<const FDateTime> purchaseDate;

	/// <summary>
	/// (Optional) Total number of remaining uses, if this is a consumable item.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> remainingUses;

	/// <summary>
	/// (Optional) Currency type for the cost of the catalog item. Not available when granting items.
	/// </summary>
	_Maybenull_ const FString unitCurrency;

	/// <summary>
	/// Cost of the catalog item in the given currency. Not available when granting items.
	/// </summary>
	uint32 unitPrice;

	/// <summary>
	/// (Optional) The number of uses that were added or removed to this item in this call.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> usesIncrementedBy;

};



/// <summary>
/// FPFUserAndroidDeviceInfo data model.
/// </summary>
struct PLAYFABCORE_API FPFUserAndroidDeviceInfo
{
	/// <summary>
	/// (Optional) Android device ID.
	/// </summary>
	_Maybenull_ const FString androidDeviceId;

};



/// <summary>
/// FPFUserAppleIdInfo data model.
/// </summary>
struct PLAYFABCORE_API FPFUserAppleIdInfo
{
	/// <summary>
	/// (Optional) Apple subject ID.
	/// </summary>
	_Maybenull_ const FString appleSubjectId;

};



/// <summary>
/// FPFUserBattleNetInfo data model.
/// </summary>
struct PLAYFABCORE_API FPFUserBattleNetInfo
{
	/// <summary>
	/// (Optional) Battle.net identifier.
	/// </summary>
	_Maybenull_ const FString battleNetAccountId;

	/// <summary>
	/// (Optional) Battle.net display name.
	/// </summary>
	_Maybenull_ const FString battleNetBattleTag;

};



/// <summary>
/// FPFUserCustomIdInfo data model.
/// </summary>
struct PLAYFABCORE_API FPFUserCustomIdInfo
{
	/// <summary>
	/// (Optional) Custom ID.
	/// </summary>
	_Maybenull_ const FString customId;

};



/// <summary>
/// FPFUserFacebookInfo data model.
/// </summary>
struct PLAYFABCORE_API FPFUserFacebookInfo
{
	/// <summary>
	/// (Optional) Facebook identifier.
	/// </summary>
	_Maybenull_ const FString facebookId;

	/// <summary>
	/// (Optional) Facebook full name.
	/// </summary>
	_Maybenull_ const FString fullName;

};



/// <summary>
/// FPFUserFacebookInstantGamesIdInfo data model.
/// </summary>
struct PLAYFABCORE_API FPFUserFacebookInstantGamesIdInfo
{
	/// <summary>
	/// (Optional) Facebook Instant Games ID.
	/// </summary>
	_Maybenull_ const FString facebookInstantGamesId;

};



/// <summary>
/// FPFUserGameCenterInfo data model.
/// </summary>
struct PLAYFABCORE_API FPFUserGameCenterInfo
{
	/// <summary>
	/// (Optional) Gamecenter identifier.
	/// </summary>
	_Maybenull_ const FString gameCenterId;

};



/// <summary>
/// FPFUserGoogleInfo data model.
/// </summary>
struct PLAYFABCORE_API FPFUserGoogleInfo
{
	/// <summary>
	/// (Optional) Email address of the Google account.
	/// </summary>
	_Maybenull_ const FString googleEmail;

	/// <summary>
	/// (Optional) Gender information of the Google account.
	/// </summary>
	_Maybenull_ const FString googleGender;

	/// <summary>
	/// (Optional) Google ID.
	/// </summary>
	_Maybenull_ const FString googleId;

	/// <summary>
	/// (Optional) Locale of the Google account.
	/// </summary>
	_Maybenull_ const FString googleLocale;

	/// <summary>
	/// (Optional) Name of the Google account user.
	/// </summary>
	_Maybenull_ const FString googleName;

};



/// <summary>
/// FPFUserGooglePlayGamesInfo data model.
/// </summary>
struct PLAYFABCORE_API FPFUserGooglePlayGamesInfo
{
	/// <summary>
	/// (Optional) Avatar image url of the Google Play Games player.
	/// </summary>
	_Maybenull_ const FString googlePlayGamesPlayerAvatarImageUrl;

	/// <summary>
	/// (Optional) Display name of the Google Play Games player.
	/// </summary>
	_Maybenull_ const FString googlePlayGamesPlayerDisplayName;

	/// <summary>
	/// (Optional) Google Play Games player ID.
	/// </summary>
	_Maybenull_ const FString googlePlayGamesPlayerId;

};



/// <summary>
/// FPFUserIosDeviceInfo data model.
/// </summary>
struct PLAYFABCORE_API FPFUserIosDeviceInfo
{
	/// <summary>
	/// (Optional) IOS device ID.
	/// </summary>
	_Maybenull_ const FString iosDeviceId;

};



/// <summary>
/// FPFUserKongregateInfo data model.
/// </summary>
struct PLAYFABCORE_API FPFUserKongregateInfo
{
	/// <summary>
	/// (Optional) Kongregate ID.
	/// </summary>
	_Maybenull_ const FString kongregateId;

	/// <summary>
	/// (Optional) Kongregate Username.
	/// </summary>
	_Maybenull_ const FString kongregateName;

};



/// <summary>
/// FPFUserNintendoSwitchAccountIdInfo data model.
/// </summary>
struct PLAYFABCORE_API FPFUserNintendoSwitchAccountIdInfo
{
	/// <summary>
	/// (Optional) Nintendo Switch account subject ID.
	/// </summary>
	_Maybenull_ const FString nintendoSwitchAccountSubjectId;

};



/// <summary>
/// FPFUserNintendoSwitchDeviceIdInfo data model.
/// </summary>
struct PLAYFABCORE_API FPFUserNintendoSwitchDeviceIdInfo
{
	/// <summary>
	/// (Optional) Nintendo Switch Device ID.
	/// </summary>
	_Maybenull_ const FString nintendoSwitchDeviceId;

};



/// <summary>
/// FPFUserOpenIdInfo data model.
/// </summary>
struct PLAYFABCORE_API FPFUserOpenIdInfo
{
	/// <summary>
	/// (Optional) OpenID Connection ID.
	/// </summary>
	_Maybenull_ const FString connectionId;

	/// <summary>
	/// (Optional) OpenID Issuer.
	/// </summary>
	_Maybenull_ const FString issuer;

	/// <summary>
	/// (Optional) OpenID Subject.
	/// </summary>
	_Maybenull_ const FString subject;

};



/// <summary>
/// FPFUserPrivateAccountInfo data model.
/// </summary>
struct PLAYFABCORE_API FPFUserPrivateAccountInfo
{
	/// <summary>
	/// (Optional) User email address.
	/// </summary>
	_Maybenull_ const FString email;

};



/// <summary>
/// FPFUserPsnInfo data model.
/// </summary>
struct PLAYFABCORE_API FPFUserPsnInfo
{
	/// <summary>
	/// (Optional) PlayStation :tm: Network account ID.
	/// </summary>
	_Maybenull_ const FString psnAccountId;

	/// <summary>
	/// (Optional) PlayStation :tm: Network online ID.
	/// </summary>
	_Maybenull_ const FString psnOnlineId;

};



/// <summary>
/// FPFUserServerCustomIdInfo data model.
/// </summary>
struct PLAYFABCORE_API FPFUserServerCustomIdInfo
{
	/// <summary>
	/// (Optional) Custom ID.
	/// </summary>
	_Maybenull_ const FString customId;

};



/// <summary>
/// FPFUserSteamInfo data model.
/// </summary>
struct PLAYFABCORE_API FPFUserSteamInfo
{
	/// <summary>
	/// (Optional) What stage of game ownership the user is listed as being in, from Steam.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFTitleActivationStatus> steamActivationStatus;

	/// <summary>
	/// (Optional) The country in which the player resides, from Steam data.
	/// </summary>
	_Maybenull_ const FString steamCountry;

	/// <summary>
	/// (Optional) Currency type set in the user Steam account.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCurrency> steamCurrency;

	/// <summary>
	/// (Optional) Steam identifier.
	/// </summary>
	_Maybenull_ const FString steamId;

	/// <summary>
	/// (Optional) Steam display name.
	/// </summary>
	_Maybenull_ const FString steamName;

};



/// <summary>
/// FPFEntityKey data model. Combined entity type and ID structure which uniquely identifies a single
/// entity.
/// </summary>
struct PLAYFABCORE_API FPFEntityKey
{
	/// <summary>
	/// Unique ID of the entity.
	/// </summary>
	const FString id;

	/// <summary>
	/// (Optional) Entity type. See https://docs.microsoft.com/gaming/playfab/features/data/entities/available-built-in-entity-types.
	/// </summary>
	_Maybenull_ const FString type;

};



/// <summary>
/// FPFUserTitleInfo data model.
/// </summary>
struct PLAYFABCORE_API FPFUserTitleInfo
{
	/// <summary>
	/// (Optional) URL to the player's avatar.
	/// </summary>
	_Maybenull_ const FString avatarUrl;

	/// <summary>
	/// Timestamp indicating when the user was first associated with this game (this can differ significantly
	/// from when the user first registered with PlayFab).
	/// </summary>
	FDateTime created;

	/// <summary>
	/// (Optional) Name of the user, as it is displayed in-game.
	/// </summary>
	_Maybenull_ const FString displayName;

	/// <summary>
	/// (Optional) Timestamp indicating when the user first signed into this game (this can differ from
	/// the Created timestamp, as other events, such as issuing a beta key to the user, can associate the
	/// title to the user).
	/// </summary>
	_Maybenull_ TSharedPtr<const FDateTime> firstLogin;

	/// <summary>
	/// (Optional) Boolean indicating whether or not the user is currently banned for a title.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> isBanned;

	/// <summary>
	/// (Optional) Timestamp for the last user login for this title.
	/// </summary>
	_Maybenull_ TSharedPtr<const FDateTime> lastLogin;

	/// <summary>
	/// (Optional) Source by which the user first joined the game, if known.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFUserOrigination> origination;

	/// <summary>
	/// (Optional) Title player account entity for this user.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> titlePlayerAccount;

};



/// <summary>
/// FPFUserTwitchInfo data model.
/// </summary>
struct PLAYFABCORE_API FPFUserTwitchInfo
{
	/// <summary>
	/// (Optional) Twitch ID.
	/// </summary>
	_Maybenull_ const FString twitchId;

	/// <summary>
	/// (Optional) Twitch Username.
	/// </summary>
	_Maybenull_ const FString twitchUserName;

};



/// <summary>
/// FPFUserXboxInfo data model.
/// </summary>
struct PLAYFABCORE_API FPFUserXboxInfo
{
	/// <summary>
	/// (Optional) XBox user ID.
	/// </summary>
	_Maybenull_ const FString xboxUserId;

	/// <summary>
	/// (Optional) XBox user sandbox.
	/// </summary>
	_Maybenull_ const FString xboxUserSandbox;

};



/// <summary>
/// FPFUserAccountInfo data model.
/// </summary>
struct PLAYFABCORE_API FPFUserAccountInfo
{
	/// <summary>
	/// (Optional) User Android device information, if an Android device has been linked.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFUserAndroidDeviceInfo> androidDeviceInfo;

	/// <summary>
	/// (Optional) Sign in with Apple account information, if an Apple account has been linked.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFUserAppleIdInfo> appleAccountInfo;

	/// <summary>
	/// (Optional) Battle.net account information, if a Battle.net account has been linked.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFUserBattleNetInfo> battleNetAccountInfo;

	/// <summary>
	/// Timestamp indicating when the user account was created.
	/// </summary>
	FDateTime created;

	/// <summary>
	/// (Optional) Custom ID information, if a custom ID has been assigned.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFUserCustomIdInfo> customIdInfo;

	/// <summary>
	/// (Optional) User Facebook information, if a Facebook account has been linked.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFUserFacebookInfo> facebookInfo;

	/// <summary>
	/// (Optional) Facebook Instant Games account information, if a Facebook Instant Games account has been
	/// linked.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFUserFacebookInstantGamesIdInfo> facebookInstantGamesIdInfo;

	/// <summary>
	/// (Optional) User Gamecenter information, if a Gamecenter account has been linked.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFUserGameCenterInfo> gameCenterInfo;

	/// <summary>
	/// (Optional) User Google account information, if a Google account has been linked.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFUserGoogleInfo> googleInfo;

	/// <summary>
	/// (Optional) User Google Play Games account information, if a Google Play Games account has been linked.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFUserGooglePlayGamesInfo> googlePlayGamesInfo;

	/// <summary>
	/// (Optional) User iOS device information, if an iOS device has been linked.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFUserIosDeviceInfo> iosDeviceInfo;

	/// <summary>
	/// (Optional) User Kongregate account information, if a Kongregate account has been linked.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFUserKongregateInfo> kongregateInfo;

	/// <summary>
	/// (Optional) Nintendo Switch account information, if a Nintendo Switch account has been linked.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFUserNintendoSwitchAccountIdInfo> nintendoSwitchAccountInfo;

	/// <summary>
	/// (Optional) Nintendo Switch device information, if a Nintendo Switch device has been linked.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFUserNintendoSwitchDeviceIdInfo> nintendoSwitchDeviceIdInfo;

	/// <summary>
	/// (Optional) OpenID Connect information, if any OpenID Connect accounts have been linked.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFUserOpenIdInfo>> openIdInfo;

	/// <summary>
	/// Count of openIdInfo
	/// </summary>
	uint32 openIdInfoCount;

	/// <summary>
	/// (Optional) Unique identifier for the user account.
	/// </summary>
	_Maybenull_ const FString playFabId;

	/// <summary>
	/// (Optional) Personal information for the user which is considered more sensitive.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFUserPrivateAccountInfo> privateInfo;

	/// <summary>
	/// (Optional) User PlayStation :tm: Network account information, if a PlayStation :tm: Network account
	/// has been linked.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFUserPsnInfo> psnInfo;

	/// <summary>
	/// (Optional) Server Custom ID information, if a server custom ID has been assigned.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFUserServerCustomIdInfo> serverCustomIdInfo;

	/// <summary>
	/// (Optional) User Steam information, if a Steam account has been linked.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFUserSteamInfo> steamInfo;

	/// <summary>
	/// (Optional) Title-specific information for the user account.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFUserTitleInfo> titleInfo;

	/// <summary>
	/// (Optional) User Twitch account information, if a Twitch account has been linked.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFUserTwitchInfo> twitchInfo;

	/// <summary>
	/// (Optional) User account name in the PlayFab service.
	/// </summary>
	_Maybenull_ const FString username;

	/// <summary>
	/// (Optional) User XBox account information, if a XBox account has been linked.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFUserXboxInfo> xboxInfo;

};



/// <summary>
/// FPFCharacterResult data model.
/// </summary>
struct PLAYFABCORE_API FPFCharacterResult
{
	/// <summary>
	/// (Optional) The id for this character on this player.
	/// </summary>
	_Maybenull_ const FString characterId;

	/// <summary>
	/// (Optional) The name of this character.
	/// </summary>
	_Maybenull_ const FString characterName;

	/// <summary>
	/// (Optional) The type-string that was given to this character on creation.
	/// </summary>
	_Maybenull_ const FString characterType;

};



/// <summary>
/// FPFUserDataRecord data model.
/// </summary>
struct PLAYFABCORE_API FPFUserDataRecord
{
	/// <summary>
	/// Timestamp for when this data was last updated.
	/// </summary>
	FDateTime lastUpdated;

	/// <summary>
	/// (Optional) Indicates whether this data can be read by all users (public) or only the user (private).
	/// This is used for GetUserData requests being made by one player about another player.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFUserDataPermission> permission;

	/// <summary>
	/// (Optional) Data stored for the specified user data key.
	/// </summary>
	_Maybenull_ const FString value;

};



/// <summary>
/// FPFVirtualCurrencyRechargeTime data model.
/// </summary>
struct PLAYFABCORE_API FPFVirtualCurrencyRechargeTime
{
	/// <summary>
	/// Maximum value to which the regenerating currency will automatically increment. Note that it can
	/// exceed this value through use of the AddUserVirtualCurrency API call. However, it will not regenerate
	/// automatically until it has fallen below this value.
	/// </summary>
	int32 rechargeMax;

	/// <summary>
	/// Server timestamp in UTC indicating the next time the virtual currency will be incremented.
	/// </summary>
	FDateTime rechargeTime;

	/// <summary>
	/// Time remaining (in seconds) before the next recharge increment of the virtual currency.
	/// </summary>
	int32 secondsToRecharge;

};



/// <summary>
/// FPFPlayerProfileViewConstraints data model.
/// </summary>
struct PLAYFABCORE_API FPFPlayerProfileViewConstraints
{
	/// <summary>
	/// Whether to show player's avatar URL. Defaults to false.
	/// </summary>
	bool showAvatarUrl;

	/// <summary>
	/// Whether to show the banned until time. Defaults to false.
	/// </summary>
	bool showBannedUntil;

	/// <summary>
	/// Whether to show campaign attributions. Defaults to false.
	/// </summary>
	bool showCampaignAttributions;

	/// <summary>
	/// Whether to show contact email addresses. Defaults to false.
	/// </summary>
	bool showContactEmailAddresses;

	/// <summary>
	/// Whether to show the created date. Defaults to false.
	/// </summary>
	bool showCreated;

	/// <summary>
	/// Whether to show the display name. Defaults to false.
	/// </summary>
	bool showDisplayName;

	/// <summary>
	/// Whether to show player's experiment variants. Defaults to false.
	/// </summary>
	bool showExperimentVariants;

	/// <summary>
	/// Whether to show the last login time. Defaults to false.
	/// </summary>
	bool showLastLogin;

	/// <summary>
	/// Whether to show the linked accounts. Defaults to false.
	/// </summary>
	bool showLinkedAccounts;

	/// <summary>
	/// Whether to show player's locations. Defaults to false.
	/// </summary>
	bool showLocations;

	/// <summary>
	/// Whether to show player's membership information. Defaults to false.
	/// </summary>
	bool showMemberships;

	/// <summary>
	/// Whether to show origination. Defaults to false.
	/// </summary>
	bool showOrigination;

	/// <summary>
	/// Whether to show push notification registrations. Defaults to false.
	/// </summary>
	bool showPushNotificationRegistrations;

	/// <summary>
	/// Reserved for future development.
	/// </summary>
	bool showStatistics;

	/// <summary>
	/// Whether to show tags. Defaults to false.
	/// </summary>
	bool showTags;

	/// <summary>
	/// Whether to show the total value to date in usd. Defaults to false.
	/// </summary>
	bool showTotalValueToDateInUsd;

	/// <summary>
	/// Whether to show the values to date. Defaults to false.
	/// </summary>
	bool showValuesToDate;

};



/// <summary>
/// FPFAdCampaignAttributionModel data model.
/// </summary>
struct PLAYFABCORE_API FPFAdCampaignAttributionModel
{
	/// <summary>
	/// UTC time stamp of attribution.
	/// </summary>
	FDateTime attributedAt;

	/// <summary>
	/// (Optional) Attribution campaign identifier.
	/// </summary>
	_Maybenull_ const FString campaignId;

	/// <summary>
	/// (Optional) Attribution network name.
	/// </summary>
	_Maybenull_ const FString platform;

};



/// <summary>
/// FPFContactEmailInfoModel data model.
/// </summary>
struct PLAYFABCORE_API FPFContactEmailInfoModel
{
	/// <summary>
	/// (Optional) The email address.
	/// </summary>
	_Maybenull_ const FString emailAddress;

	/// <summary>
	/// (Optional) The name of the email info data.
	/// </summary>
	_Maybenull_ const FString name;

	/// <summary>
	/// (Optional) The verification status of the email.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEmailVerificationStatus> verificationStatus;

};



/// <summary>
/// FPFLinkedPlatformAccountModel data model.
/// </summary>
struct PLAYFABCORE_API FPFLinkedPlatformAccountModel
{
	/// <summary>
	/// (Optional) Linked account email of the user on the platform, if available.
	/// </summary>
	_Maybenull_ const FString email;

	/// <summary>
	/// (Optional) Authentication platform.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFLoginIdentityProvider> platform;

	/// <summary>
	/// (Optional) Unique account identifier of the user on the platform.
	/// </summary>
	_Maybenull_ const FString platformUserId;

	/// <summary>
	/// (Optional) Linked account username of the user on the platform, if available.
	/// </summary>
	_Maybenull_ const FString username;

};



/// <summary>
/// FPFLocationModel data model.
/// </summary>
struct PLAYFABCORE_API FPFLocationModel
{
	/// <summary>
	/// (Optional) City name.
	/// </summary>
	_Maybenull_ const FString city;

	/// <summary>
	/// (Optional) The two-character continent code for this location.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFContinentCode> continentCode;

	/// <summary>
	/// (Optional) The two-character ISO 3166-1 country code for the country associated with the location.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCountryCode> countryCode;

	/// <summary>
	/// (Optional) Latitude coordinate of the geographic location.
	/// </summary>
	_Maybenull_ TSharedPtr<const double> latitude;

	/// <summary>
	/// (Optional) Longitude coordinate of the geographic location.
	/// </summary>
	_Maybenull_ TSharedPtr<const double> longitude;

};



/// <summary>
/// FPFSubscriptionModel data model.
/// </summary>
struct PLAYFABCORE_API FPFSubscriptionModel
{
	/// <summary>
	/// When this subscription expires.
	/// </summary>
	FDateTime expiration;

	/// <summary>
	/// The time the subscription was orignially purchased.
	/// </summary>
	FDateTime initialSubscriptionTime;

	/// <summary>
	/// Whether this subscription is currently active. That is, if Expiration > now.
	/// </summary>
	bool isActive;

	/// <summary>
	/// (Optional) The status of this subscription, according to the subscription provider.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFSubscriptionProviderStatus> status;

	/// <summary>
	/// (Optional) The id for this subscription.
	/// </summary>
	_Maybenull_ const FString subscriptionId;

	/// <summary>
	/// (Optional) The item id for this subscription from the primary catalog.
	/// </summary>
	_Maybenull_ const FString subscriptionItemId;

	/// <summary>
	/// (Optional) The provider for this subscription. Apple or Google Play are supported today.
	/// </summary>
	_Maybenull_ const FString subscriptionProvider;

};



/// <summary>
/// FPFMembershipModel data model.
/// </summary>
struct PLAYFABCORE_API FPFMembershipModel
{
	/// <summary>
	/// Whether this membership is active. That is, whether the MembershipExpiration time has been reached.
	/// </summary>
	bool isActive;

	/// <summary>
	/// The time this membership expires.
	/// </summary>
	FDateTime membershipExpiration;

	/// <summary>
	/// (Optional) The id of the membership.
	/// </summary>
	_Maybenull_ const FString membershipId;

	/// <summary>
	/// (Optional) Membership expirations can be explicitly overridden (via game manager or the admin api).
	/// If this membership has been overridden, this will be the new expiration time.
	/// </summary>
	_Maybenull_ TSharedPtr<const FDateTime> overrideExpiration;

	/// <summary>
	/// (Optional) The list of subscriptions that this player has for this membership.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFSubscriptionModel>> subscriptions;

	/// <summary>
	/// Count of subscriptions
	/// </summary>
	uint32 subscriptionsCount;

};



/// <summary>
/// FPFPushNotificationRegistrationModel data model.
/// </summary>
struct PLAYFABCORE_API FPFPushNotificationRegistrationModel
{
	/// <summary>
	/// (Optional) Notification configured endpoint.
	/// </summary>
	_Maybenull_ const FString notificationEndpointARN;

	/// <summary>
	/// (Optional) Push notification platform.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFPushNotificationPlatform> platform;

};



/// <summary>
/// FPFStatisticModel data model.
/// </summary>
struct PLAYFABCORE_API FPFStatisticModel
{
	/// <summary>
	/// (Optional) Statistic name.
	/// </summary>
	_Maybenull_ const FString name;

	/// <summary>
	/// Statistic value.
	/// </summary>
	int32 value;

	/// <summary>
	/// Statistic version (0 if not a versioned statistic).
	/// </summary>
	int32 version;

};



/// <summary>
/// FPFTagModel data model.
/// </summary>
struct PLAYFABCORE_API FPFTagModel
{
	/// <summary>
	/// (Optional) Full value of the tag, including namespace.
	/// </summary>
	_Maybenull_ const FString tagValue;

};



/// <summary>
/// FPFValueToDateModel data model.
/// </summary>
struct PLAYFABCORE_API FPFValueToDateModel
{
	/// <summary>
	/// (Optional) ISO 4217 code of the currency used in the purchases.
	/// </summary>
	_Maybenull_ const FString currency;

	/// <summary>
	/// Total value of the purchases in a whole number of 1/100 monetary units. For example, 999 indicates
	/// nine dollars and ninety-nine cents when Currency is 'USD').
	/// </summary>
	uint32 totalValue;

	/// <summary>
	/// (Optional) Total value of the purchases in a string representation of decimal monetary units. For
	/// example, '9.99' indicates nine dollars and ninety-nine cents when Currency is 'USD'.
	/// </summary>
	_Maybenull_ const FString totalValueAsDecimal;

};



/// <summary>
/// FPFPlayerProfileModel data model.
/// </summary>
struct PLAYFABCORE_API FPFPlayerProfileModel
{
	/// <summary>
	/// (Optional) List of advertising campaigns the player has been attributed to.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFAdCampaignAttributionModel>> adCampaignAttributions;

	/// <summary>
	/// Count of adCampaignAttributions
	/// </summary>
	uint32 adCampaignAttributionsCount;

	/// <summary>
	/// (Optional) URL of the player's avatar image.
	/// </summary>
	_Maybenull_ const FString avatarUrl;

	/// <summary>
	/// (Optional) If the player is currently banned, the UTC Date when the ban expires.
	/// </summary>
	_Maybenull_ TSharedPtr<const FDateTime> bannedUntil;

	/// <summary>
	/// (Optional) List of all contact email info associated with the player account.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFContactEmailInfoModel>> contactEmailAddresses;

	/// <summary>
	/// Count of contactEmailAddresses
	/// </summary>
	uint32 contactEmailAddressesCount;

	/// <summary>
	/// (Optional) Player record created.
	/// </summary>
	_Maybenull_ TSharedPtr<const FDateTime> created;

	/// <summary>
	/// (Optional) Player display name.
	/// </summary>
	_Maybenull_ const FString displayName;

	/// <summary>
	/// (Optional) List of experiment variants for the player. Note that these variants are not guaranteed
	/// to be up-to-date when returned during login because the player profile is updated only after login.
	/// Instead, use the LoginResult.TreatmentAssignment property during login to get the correct variants
	/// and variables.
	/// </summary>
	_Maybenull_ const TArray<FString> experimentVariants;

	/// <summary>
	/// Count of experimentVariants
	/// </summary>
	uint32 experimentVariantsCount;

	/// <summary>
	/// (Optional) UTC time when the player most recently logged in to the title.
	/// </summary>
	_Maybenull_ TSharedPtr<const FDateTime> lastLogin;

	/// <summary>
	/// (Optional) List of all authentication systems linked to this player account.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFLinkedPlatformAccountModel>> linkedAccounts;

	/// <summary>
	/// Count of linkedAccounts
	/// </summary>
	uint32 linkedAccountsCount;

	/// <summary>
	/// (Optional) List of geographic locations from which the player has logged in to the title.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFLocationModel>> locations;

	/// <summary>
	/// Count of locations
	/// </summary>
	uint32 locationsCount;

	/// <summary>
	/// (Optional) List of memberships for the player, along with whether are expired.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFMembershipModel>> memberships;

	/// <summary>
	/// Count of memberships
	/// </summary>
	uint32 membershipsCount;

	/// <summary>
	/// (Optional) Player account origination.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFLoginIdentityProvider> origination;

	/// <summary>
	/// (Optional) PlayFab player account unique identifier.
	/// </summary>
	_Maybenull_ const FString playerId;

	/// <summary>
	/// (Optional) Publisher this player belongs to.
	/// </summary>
	_Maybenull_ const FString publisherId;

	/// <summary>
	/// (Optional) List of configured end points registered for sending the player push notifications.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFPushNotificationRegistrationModel>> pushNotificationRegistrations;

	/// <summary>
	/// Count of pushNotificationRegistrations
	/// </summary>
	uint32 pushNotificationRegistrationsCount;

	/// <summary>
	/// (Optional) List of leaderboard statistic values for the player.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFStatisticModel>> statistics;

	/// <summary>
	/// Count of statistics
	/// </summary>
	uint32 statisticsCount;

	/// <summary>
	/// (Optional) List of player's tags for segmentation.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFTagModel>> tags;

	/// <summary>
	/// Count of tags
	/// </summary>
	uint32 tagsCount;

	/// <summary>
	/// (Optional) Title ID this player profile applies to.
	/// </summary>
	_Maybenull_ const FString titleId;

	/// <summary>
	/// (Optional) Sum of the player's purchases made with real-money currencies, converted to US dollars
	/// equivalent and represented as a whole number of cents (1/100 USD). For example, 999 indicates nine
	/// dollars and ninety-nine cents.
	/// </summary>
	_Maybenull_ TSharedPtr<const uint32> totalValueToDateInUSD;

	/// <summary>
	/// (Optional) List of the player's lifetime purchase totals, summed by real-money currency.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFValueToDateModel>> valuesToDate;

	/// <summary>
	/// Count of valuesToDate
	/// </summary>
	uint32 valuesToDateCount;

};



/// <summary>
/// FPFGetPlayerCombinedInfoRequestParams data model.
/// </summary>
struct PLAYFABCORE_API FPFGetPlayerCombinedInfoRequestParams
{
	/// <summary>
	/// Whether to get character inventories. Defaults to false.
	/// </summary>
	bool getCharacterInventories;

	/// <summary>
	/// Whether to get the list of characters. Defaults to false.
	/// </summary>
	bool getCharacterList;

	/// <summary>
	/// Whether to get player profile. Defaults to false. Has no effect for a new player.
	/// </summary>
	bool getPlayerProfile;

	/// <summary>
	/// Whether to get player statistics. Defaults to false.
	/// </summary>
	bool getPlayerStatistics;

	/// <summary>
	/// Whether to get title data. Defaults to false.
	/// </summary>
	bool getTitleData;

	/// <summary>
	/// Whether to get the player's account Info. Defaults to false.
	/// </summary>
	bool getUserAccountInfo;

	/// <summary>
	/// Whether to get the player's custom data. Defaults to false.
	/// </summary>
	bool getUserData;

	/// <summary>
	/// Whether to get the player's inventory. Defaults to false.
	/// </summary>
	bool getUserInventory;

	/// <summary>
	/// Whether to get the player's read only data. Defaults to false.
	/// </summary>
	bool getUserReadOnlyData;

	/// <summary>
	/// Whether to get the player's virtual currency balances. Defaults to false.
	/// </summary>
	bool getUserVirtualCurrency;

	/// <summary>
	/// (Optional) Specific statistics to retrieve. Leave null to get all keys. Has no effect if GetPlayerStatistics
	/// is false.
	/// </summary>
	_Maybenull_ const TArray<FString> playerStatisticNames;

	/// <summary>
	/// Count of playerStatisticNames
	/// </summary>
	uint32 playerStatisticNamesCount;

	/// <summary>
	/// (Optional) Specifies the properties to return from the player profile. Defaults to returning the
	/// player's display name.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFPlayerProfileViewConstraints> profileConstraints;

	/// <summary>
	/// (Optional) Specific keys to search for in the custom data. Leave null to get all keys. Has no effect
	/// if GetTitleData is false.
	/// </summary>
	_Maybenull_ const TArray<FString> titleDataKeys;

	/// <summary>
	/// Count of titleDataKeys
	/// </summary>
	uint32 titleDataKeysCount;

	/// <summary>
	/// (Optional) Specific keys to search for in the custom data. Leave null to get all keys. Has no effect
	/// if GetUserData is false.
	/// </summary>
	_Maybenull_ const TArray<FString> userDataKeys;

	/// <summary>
	/// Count of userDataKeys
	/// </summary>
	uint32 userDataKeysCount;

	/// <summary>
	/// (Optional) Specific keys to search for in the custom data. Leave null to get all keys. Has no effect
	/// if GetUserReadOnlyData is false.
	/// </summary>
	_Maybenull_ const TArray<FString> userReadOnlyDataKeys;

	/// <summary>
	/// Count of userReadOnlyDataKeys
	/// </summary>
	uint32 userReadOnlyDataKeysCount;

};



/// <summary>
/// FPFCharacterInventory data model.
/// </summary>
struct PLAYFABCORE_API FPFCharacterInventory
{
	/// <summary>
	/// (Optional) The id of this character.
	/// </summary>
	_Maybenull_ const FString characterId;

	/// <summary>
	/// (Optional) The inventory of this character.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFItemInstance>> inventory;

	/// <summary>
	/// Count of inventory
	/// </summary>
	uint32 inventoryCount;

};



/// <summary>
/// FPFStatisticValue data model.
/// </summary>
struct PLAYFABCORE_API FPFStatisticValue
{
	/// <summary>
	/// (Optional) Unique name of the statistic.
	/// </summary>
	_Maybenull_ const FString statisticName;

	/// <summary>
	/// Statistic value for the player.
	/// </summary>
	int32 value;

	/// <summary>
	/// For updates to an existing statistic value for a player, the version of the statistic when it was
	/// loaded.
	/// </summary>
	uint32 version;

};



/// <summary>
/// FPFGetPlayerCombinedInfoResultPayload data model.
/// </summary>
struct PLAYFABCORE_API FPFGetPlayerCombinedInfoResultPayload
{
	/// <summary>
	/// (Optional) Account information for the user. This is always retrieved.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFUserAccountInfo> accountInfo;

	/// <summary>
	/// (Optional) Inventories for each character for the user.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFCharacterInventory>> characterInventories;

	/// <summary>
	/// Count of characterInventories
	/// </summary>
	uint32 characterInventoriesCount;

	/// <summary>
	/// (Optional) List of characters for the user.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFCharacterResult>> characterList;

	/// <summary>
	/// Count of characterList
	/// </summary>
	uint32 characterListCount;

	/// <summary>
	/// (Optional) The profile of the players. This profile is not guaranteed to be up-to-date. For a new
	/// player, this profile will not exist.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFPlayerProfileModel> playerProfile;

	/// <summary>
	/// (Optional) List of statistics for this player.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFStatisticValue>> playerStatistics;

	/// <summary>
	/// Count of playerStatistics
	/// </summary>
	uint32 playerStatisticsCount;

	/// <summary>
	/// (Optional) Title data for this title.
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> titleData;

	/// <summary>
	/// Count of titleData
	/// </summary>
	uint32 titleDataCount;

	/// <summary>
	/// (Optional) User specific custom data.
	/// </summary>
	_Maybenull_ TMap<const FString, TSharedPtr<const FPFUserDataRecord>> userData;

	/// <summary>
	/// Count of userData
	/// </summary>
	uint32 userDataCount;

	/// <summary>
	/// The version of the UserData that was returned.
	/// </summary>
	uint32 userDataVersion;

	/// <summary>
	/// (Optional) Array of inventory items in the user's current inventory.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFItemInstance>> userInventory;

	/// <summary>
	/// Count of userInventory
	/// </summary>
	uint32 userInventoryCount;

	/// <summary>
	/// (Optional) User specific read-only data.
	/// </summary>
	_Maybenull_ TMap<const FString, TSharedPtr<const FPFUserDataRecord>> userReadOnlyData;

	/// <summary>
	/// Count of userReadOnlyData
	/// </summary>
	uint32 userReadOnlyDataCount;

	/// <summary>
	/// The version of the Read-Only UserData that was returned.
	/// </summary>
	uint32 userReadOnlyDataVersion;

	/// <summary>
	/// (Optional) Dictionary of virtual currency balance(s) belonging to the user.
	/// </summary>
	_Maybenull_ TMap<const FString, int32> userVirtualCurrency;

	/// <summary>
	/// Count of userVirtualCurrency
	/// </summary>
	uint32 userVirtualCurrencyCount;

	/// <summary>
	/// (Optional) Dictionary of remaining times and timestamps for virtual currencies.
	/// </summary>
	_Maybenull_ TMap<const FString, TSharedPtr<const FPFVirtualCurrencyRechargeTime>> userVirtualCurrencyRechargeTimes;

	/// <summary>
	/// Count of userVirtualCurrencyRechargeTimes
	/// </summary>
	uint32 userVirtualCurrencyRechargeTimesCount;

};



/// <summary>
/// FPFVariable data model.
/// </summary>
struct PLAYFABCORE_API FPFVariable
{
	/// <summary>
	/// Name of the variable.
	/// </summary>
	const FString name;

	/// <summary>
	/// (Optional) Value of the variable.
	/// </summary>
	_Maybenull_ const FString value;

};



/// <summary>
/// FPFTreatmentAssignment data model.
/// </summary>
struct PLAYFABCORE_API FPFTreatmentAssignment
{
	/// <summary>
	/// (Optional) List of the experiment variables.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFVariable>> variables;

	/// <summary>
	/// Count of variables
	/// </summary>
	uint32 variablesCount;

	/// <summary>
	/// (Optional) List of the experiment variants.
	/// </summary>
	_Maybenull_ const TArray<FString> variants;

	/// <summary>
	/// Count of variants
	/// </summary>
	uint32 variantsCount;

};



/// <summary>
/// FPFEntityLineage data model.
/// </summary>
struct PLAYFABCORE_API FPFEntityLineage
{
	/// <summary>
	/// (Optional) The Character Id of the associated entity.
	/// </summary>
	_Maybenull_ const FString characterId;

	/// <summary>
	/// (Optional) The Group Id of the associated entity.
	/// </summary>
	_Maybenull_ const FString groupId;

	/// <summary>
	/// (Optional) The Master Player Account Id of the associated entity.
	/// </summary>
	_Maybenull_ const FString masterPlayerAccountId;

	/// <summary>
	/// (Optional) The Namespace Id of the associated entity.
	/// </summary>
	_Maybenull_ const FString namespaceId;

	/// <summary>
	/// (Optional) The Title Id of the associated entity.
	/// </summary>
	_Maybenull_ const FString titleId;

	/// <summary>
	/// (Optional) The Title Player Account Id of the associated entity.
	/// </summary>
	_Maybenull_ const FString titlePlayerAccountId;

};

// Delegates Declarations

/// <summary>
/// String representation of a Json Object
/// </summary>
struct PLAYFABCORE_API FPFJsonObject
{
	_Maybenull_ const FString stringValue;
};	

#pragma pop_macro("IN")
