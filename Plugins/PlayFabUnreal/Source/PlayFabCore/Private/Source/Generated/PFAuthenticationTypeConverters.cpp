// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.


#include "Generated/PFAuthenticationTypeConverters.h"


const FPFAuthenticationIdentifiedDeviceType ConvertIdentifiedDeviceTypeToUnreal(const PFAuthenticationIdentifiedDeviceType* enumVal)
{
	if (enumVal == nullptr) {
		return FPFAuthenticationIdentifiedDeviceType::Unknown;
	}

	switch(*enumVal)
	{
	case PFAuthenticationIdentifiedDeviceType::Unknown: return FPFAuthenticationIdentifiedDeviceType::Unknown;
	case PFAuthenticationIdentifiedDeviceType::XboxOne: return FPFAuthenticationIdentifiedDeviceType::XboxOne;
	case PFAuthenticationIdentifiedDeviceType::Scarlett: return FPFAuthenticationIdentifiedDeviceType::Scarlett;
	case PFAuthenticationIdentifiedDeviceType::WindowsOneCore: return FPFAuthenticationIdentifiedDeviceType::WindowsOneCore;
	case PFAuthenticationIdentifiedDeviceType::WindowsOneCoreMobile: return FPFAuthenticationIdentifiedDeviceType::WindowsOneCoreMobile;
	case PFAuthenticationIdentifiedDeviceType::Win32: return FPFAuthenticationIdentifiedDeviceType::Win32;
	case PFAuthenticationIdentifiedDeviceType::android: return FPFAuthenticationIdentifiedDeviceType::android;
	case PFAuthenticationIdentifiedDeviceType::iOS: return FPFAuthenticationIdentifiedDeviceType::iOS;
	case PFAuthenticationIdentifiedDeviceType::PlayStation: return FPFAuthenticationIdentifiedDeviceType::PlayStation;
	case PFAuthenticationIdentifiedDeviceType::Nintendo: return FPFAuthenticationIdentifiedDeviceType::Nintendo;
	default:
	return FPFAuthenticationIdentifiedDeviceType::Unknown;
	}
}

const PFAuthenticationIdentifiedDeviceType ConvertIdentifiedDeviceTypeToPlayfab(TSharedPtr<const FPFAuthenticationIdentifiedDeviceType> enumVal)
{
	if (!enumVal.IsValid()) {
		return PFAuthenticationIdentifiedDeviceType::Unknown;
	}

	switch(*enumVal)
	{
	case FPFAuthenticationIdentifiedDeviceType::Unknown: return PFAuthenticationIdentifiedDeviceType::Unknown;
	case FPFAuthenticationIdentifiedDeviceType::XboxOne: return PFAuthenticationIdentifiedDeviceType::XboxOne;
	case FPFAuthenticationIdentifiedDeviceType::Scarlett: return PFAuthenticationIdentifiedDeviceType::Scarlett;
	case FPFAuthenticationIdentifiedDeviceType::WindowsOneCore: return PFAuthenticationIdentifiedDeviceType::WindowsOneCore;
	case FPFAuthenticationIdentifiedDeviceType::WindowsOneCoreMobile: return PFAuthenticationIdentifiedDeviceType::WindowsOneCoreMobile;
	case FPFAuthenticationIdentifiedDeviceType::Win32: return PFAuthenticationIdentifiedDeviceType::Win32;
	case FPFAuthenticationIdentifiedDeviceType::android: return PFAuthenticationIdentifiedDeviceType::android;
	case FPFAuthenticationIdentifiedDeviceType::iOS: return PFAuthenticationIdentifiedDeviceType::iOS;
	case FPFAuthenticationIdentifiedDeviceType::PlayStation: return PFAuthenticationIdentifiedDeviceType::PlayStation;
	case FPFAuthenticationIdentifiedDeviceType::Nintendo: return PFAuthenticationIdentifiedDeviceType::Nintendo;
	default:
	return PFAuthenticationIdentifiedDeviceType::Unknown;
	}
}

TSharedPtr<const FPFAuthenticationLoginWithAndroidDeviceIDRequest> ConvertLoginWithAndroidDeviceIDRequestToUnreal(const PFAuthenticationLoginWithAndroidDeviceIDRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationLoginWithAndroidDeviceIDRequest> ConvertedType = MakeShared<FPFAuthenticationLoginWithAndroidDeviceIDRequest>(FPFAuthenticationLoginWithAndroidDeviceIDRequest{
		.androidDevice = Datatype->androidDevice == nullptr ? FString() : FString(Datatype->androidDevice),
		.androidDeviceId = Datatype->androidDeviceId == nullptr ? FString() : FString(Datatype->androidDeviceId),
		.createAccount = Datatype->createAccount,
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToUnreal(Datatype->infoRequestParameters),
		.OS = Datatype->OS == nullptr ? FString() : FString(Datatype->OS),
		.playerSecret = Datatype->playerSecret == nullptr ? FString() : FString(Datatype->playerSecret)
	});

	return ConvertedType;
}

const PFAuthenticationLoginWithAndroidDeviceIDRequest* ConvertLoginWithAndroidDeviceIDRequestToPlayfab(TSharedPtr<const FPFAuthenticationLoginWithAndroidDeviceIDRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationLoginWithAndroidDeviceIDRequest* ConvertedType = new PFAuthenticationLoginWithAndroidDeviceIDRequest{
		.androidDevice = ConvertFStringToCharPtr(Datatype->androidDevice),
		.androidDeviceId = ConvertFStringToCharPtr(Datatype->androidDeviceId),
		.createAccount = Datatype->createAccount,
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(Datatype->infoRequestParameters),
		.OS = ConvertFStringToCharPtr(Datatype->OS),
		.playerSecret = ConvertFStringToCharPtr(Datatype->playerSecret)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAuthenticationUserSettings> ConvertUserSettingsToUnreal(const PFAuthenticationUserSettings* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationUserSettings> ConvertedType = MakeShared<FPFAuthenticationUserSettings>(FPFAuthenticationUserSettings{
		.gatherDeviceInfo = Datatype->gatherDeviceInfo,
		.gatherFocusInfo = Datatype->gatherFocusInfo,
		.needsAttribution = Datatype->needsAttribution
	});

	return ConvertedType;
}

const PFAuthenticationUserSettings* ConvertUserSettingsToPlayfab(TSharedPtr<const FPFAuthenticationUserSettings> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationUserSettings* ConvertedType = new PFAuthenticationUserSettings{
		.gatherDeviceInfo = Datatype->gatherDeviceInfo,
		.gatherFocusInfo = Datatype->gatherFocusInfo,
		.needsAttribution = Datatype->needsAttribution
	};

	return ConvertedType;
}

TSharedPtr<const FPFAuthenticationLoginResult> ConvertLoginResultToUnreal(const PFAuthenticationLoginResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationLoginResult> ConvertedType = MakeShared<FPFAuthenticationLoginResult>(FPFAuthenticationLoginResult{
		.infoResultPayload = ConvertGetPlayerCombinedInfoResultPayloadToUnreal(Datatype->infoResultPayload),
		.lastLoginTime = ConvertTimeToUnreal(Datatype->lastLoginTime),
		.newlyCreated = Datatype->newlyCreated,
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId),
		.settingsForUser = ConvertUserSettingsToUnreal(Datatype->settingsForUser),
		.treatmentAssignment = ConvertTreatmentAssignmentToUnreal(Datatype->treatmentAssignment)
	});

	return ConvertedType;
}

const PFAuthenticationLoginResult* ConvertLoginResultToPlayfab(TSharedPtr<const FPFAuthenticationLoginResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationLoginResult* ConvertedType = new PFAuthenticationLoginResult{
		.infoResultPayload = ConvertGetPlayerCombinedInfoResultPayloadToPlayfab(Datatype->infoResultPayload),
		.lastLoginTime = ConvertFDateTimeToPlayfab(Datatype->lastLoginTime),
		.newlyCreated = Datatype->newlyCreated,
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId),
		.settingsForUser = ConvertUserSettingsToPlayfab(Datatype->settingsForUser),
		.treatmentAssignment = ConvertTreatmentAssignmentToPlayfab(Datatype->treatmentAssignment)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAuthenticationLoginWithAppleRequest> ConvertLoginWithAppleRequestToUnreal(const PFAuthenticationLoginWithAppleRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationLoginWithAppleRequest> ConvertedType = MakeShared<FPFAuthenticationLoginWithAppleRequest>(FPFAuthenticationLoginWithAppleRequest{
		.createAccount = Datatype->createAccount,
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.identityToken = Datatype->identityToken == nullptr ? FString() : FString(Datatype->identityToken),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToUnreal(Datatype->infoRequestParameters),
		.playerSecret = Datatype->playerSecret == nullptr ? FString() : FString(Datatype->playerSecret)
	});

	return ConvertedType;
}

const PFAuthenticationLoginWithAppleRequest* ConvertLoginWithAppleRequestToPlayfab(TSharedPtr<const FPFAuthenticationLoginWithAppleRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationLoginWithAppleRequest* ConvertedType = new PFAuthenticationLoginWithAppleRequest{
		.createAccount = Datatype->createAccount,
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.identityToken = ConvertFStringToCharPtr(Datatype->identityToken),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(Datatype->infoRequestParameters),
		.playerSecret = ConvertFStringToCharPtr(Datatype->playerSecret)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAuthenticationLoginWithBattleNetRequest> ConvertLoginWithBattleNetRequestToUnreal(const PFAuthenticationLoginWithBattleNetRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationLoginWithBattleNetRequest> ConvertedType = MakeShared<FPFAuthenticationLoginWithBattleNetRequest>(FPFAuthenticationLoginWithBattleNetRequest{
		.createAccount = Datatype->createAccount,
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.identityToken = Datatype->identityToken == nullptr ? FString() : FString(Datatype->identityToken),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToUnreal(Datatype->infoRequestParameters),
		.playerSecret = Datatype->playerSecret == nullptr ? FString() : FString(Datatype->playerSecret)
	});

	return ConvertedType;
}

const PFAuthenticationLoginWithBattleNetRequest* ConvertLoginWithBattleNetRequestToPlayfab(TSharedPtr<const FPFAuthenticationLoginWithBattleNetRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationLoginWithBattleNetRequest* ConvertedType = new PFAuthenticationLoginWithBattleNetRequest{
		.createAccount = Datatype->createAccount,
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.identityToken = ConvertFStringToCharPtr(Datatype->identityToken),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(Datatype->infoRequestParameters),
		.playerSecret = ConvertFStringToCharPtr(Datatype->playerSecret)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAuthenticationLoginWithCustomIDRequest> ConvertLoginWithCustomIDRequestToUnreal(const PFAuthenticationLoginWithCustomIDRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationLoginWithCustomIDRequest> ConvertedType = MakeShared<FPFAuthenticationLoginWithCustomIDRequest>(FPFAuthenticationLoginWithCustomIDRequest{
		.createAccount = Datatype->createAccount,
		.customId = Datatype->customId == nullptr ? FString() : FString(Datatype->customId),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToUnreal(Datatype->infoRequestParameters),
		.playerSecret = Datatype->playerSecret == nullptr ? FString() : FString(Datatype->playerSecret)
	});

	return ConvertedType;
}

const PFAuthenticationLoginWithCustomIDRequest* ConvertLoginWithCustomIDRequestToPlayfab(TSharedPtr<const FPFAuthenticationLoginWithCustomIDRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationLoginWithCustomIDRequest* ConvertedType = new PFAuthenticationLoginWithCustomIDRequest{
		.createAccount = Datatype->createAccount,
		.customId = ConvertFStringToCharPtr(Datatype->customId),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(Datatype->infoRequestParameters),
		.playerSecret = ConvertFStringToCharPtr(Datatype->playerSecret)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAuthenticationLoginWithEmailAddressRequest> ConvertLoginWithEmailAddressRequestToUnreal(const PFAuthenticationLoginWithEmailAddressRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationLoginWithEmailAddressRequest> ConvertedType = MakeShared<FPFAuthenticationLoginWithEmailAddressRequest>(FPFAuthenticationLoginWithEmailAddressRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.email = Datatype->email == nullptr ? FString() : FString(Datatype->email),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToUnreal(Datatype->infoRequestParameters),
		.password = Datatype->password == nullptr ? FString() : FString(Datatype->password)
	});

	return ConvertedType;
}

const PFAuthenticationLoginWithEmailAddressRequest* ConvertLoginWithEmailAddressRequestToPlayfab(TSharedPtr<const FPFAuthenticationLoginWithEmailAddressRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationLoginWithEmailAddressRequest* ConvertedType = new PFAuthenticationLoginWithEmailAddressRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.email = ConvertFStringToCharPtr(Datatype->email),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(Datatype->infoRequestParameters),
		.password = ConvertFStringToCharPtr(Datatype->password)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAuthenticationLoginWithFacebookRequest> ConvertLoginWithFacebookRequestToUnreal(const PFAuthenticationLoginWithFacebookRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationLoginWithFacebookRequest> ConvertedType = MakeShared<FPFAuthenticationLoginWithFacebookRequest>(FPFAuthenticationLoginWithFacebookRequest{
		.accessToken = Datatype->accessToken == nullptr ? FString() : FString(Datatype->accessToken),
		.authenticationToken = Datatype->authenticationToken == nullptr ? FString() : FString(Datatype->authenticationToken),
		.createAccount = Datatype->createAccount,
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToUnreal(Datatype->infoRequestParameters),
		.playerSecret = Datatype->playerSecret == nullptr ? FString() : FString(Datatype->playerSecret)
	});

	return ConvertedType;
}

const PFAuthenticationLoginWithFacebookRequest* ConvertLoginWithFacebookRequestToPlayfab(TSharedPtr<const FPFAuthenticationLoginWithFacebookRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationLoginWithFacebookRequest* ConvertedType = new PFAuthenticationLoginWithFacebookRequest{
		.accessToken = ConvertFStringToCharPtr(Datatype->accessToken),
		.authenticationToken = ConvertFStringToCharPtr(Datatype->authenticationToken),
		.createAccount = Datatype->createAccount,
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(Datatype->infoRequestParameters),
		.playerSecret = ConvertFStringToCharPtr(Datatype->playerSecret)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAuthenticationLoginWithFacebookInstantGamesIdRequest> ConvertLoginWithFacebookInstantGamesIdRequestToUnreal(const PFAuthenticationLoginWithFacebookInstantGamesIdRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationLoginWithFacebookInstantGamesIdRequest> ConvertedType = MakeShared<FPFAuthenticationLoginWithFacebookInstantGamesIdRequest>(FPFAuthenticationLoginWithFacebookInstantGamesIdRequest{
		.createAccount = Datatype->createAccount,
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.facebookInstantGamesSignature = Datatype->facebookInstantGamesSignature == nullptr ? FString() : FString(Datatype->facebookInstantGamesSignature),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToUnreal(Datatype->infoRequestParameters),
		.playerSecret = Datatype->playerSecret == nullptr ? FString() : FString(Datatype->playerSecret)
	});

	return ConvertedType;
}

const PFAuthenticationLoginWithFacebookInstantGamesIdRequest* ConvertLoginWithFacebookInstantGamesIdRequestToPlayfab(TSharedPtr<const FPFAuthenticationLoginWithFacebookInstantGamesIdRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationLoginWithFacebookInstantGamesIdRequest* ConvertedType = new PFAuthenticationLoginWithFacebookInstantGamesIdRequest{
		.createAccount = Datatype->createAccount,
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.facebookInstantGamesSignature = ConvertFStringToCharPtr(Datatype->facebookInstantGamesSignature),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(Datatype->infoRequestParameters),
		.playerSecret = ConvertFStringToCharPtr(Datatype->playerSecret)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAuthenticationLoginWithGameCenterRequest> ConvertLoginWithGameCenterRequestToUnreal(const PFAuthenticationLoginWithGameCenterRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationLoginWithGameCenterRequest> ConvertedType = MakeShared<FPFAuthenticationLoginWithGameCenterRequest>(FPFAuthenticationLoginWithGameCenterRequest{
		.createAccount = Datatype->createAccount,
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToUnreal(Datatype->infoRequestParameters),
		.playerId = Datatype->playerId == nullptr ? FString() : FString(Datatype->playerId),
		.playerSecret = Datatype->playerSecret == nullptr ? FString() : FString(Datatype->playerSecret),
		.publicKeyUrl = Datatype->publicKeyUrl == nullptr ? FString() : FString(Datatype->publicKeyUrl),
		.salt = Datatype->salt == nullptr ? FString() : FString(Datatype->salt),
		.signature = Datatype->signature == nullptr ? FString() : FString(Datatype->signature),
		.timestamp = Datatype->timestamp == nullptr ? FString() : FString(Datatype->timestamp)
	});

	return ConvertedType;
}

const PFAuthenticationLoginWithGameCenterRequest* ConvertLoginWithGameCenterRequestToPlayfab(TSharedPtr<const FPFAuthenticationLoginWithGameCenterRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationLoginWithGameCenterRequest* ConvertedType = new PFAuthenticationLoginWithGameCenterRequest{
		.createAccount = Datatype->createAccount,
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(Datatype->infoRequestParameters),
		.playerId = ConvertFStringToCharPtr(Datatype->playerId),
		.playerSecret = ConvertFStringToCharPtr(Datatype->playerSecret),
		.publicKeyUrl = ConvertFStringToCharPtr(Datatype->publicKeyUrl),
		.salt = ConvertFStringToCharPtr(Datatype->salt),
		.signature = ConvertFStringToCharPtr(Datatype->signature),
		.timestamp = ConvertFStringToCharPtr(Datatype->timestamp)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAuthenticationLoginWithGoogleAccountRequest> ConvertLoginWithGoogleAccountRequestToUnreal(const PFAuthenticationLoginWithGoogleAccountRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationLoginWithGoogleAccountRequest> ConvertedType = MakeShared<FPFAuthenticationLoginWithGoogleAccountRequest>(FPFAuthenticationLoginWithGoogleAccountRequest{
		.createAccount = Datatype->createAccount,
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToUnreal(Datatype->infoRequestParameters),
		.playerSecret = Datatype->playerSecret == nullptr ? FString() : FString(Datatype->playerSecret),
		.serverAuthCode = Datatype->serverAuthCode == nullptr ? FString() : FString(Datatype->serverAuthCode),
		.setEmail = TSharedPtr<const bool>(Datatype->setEmail)
	});

	return ConvertedType;
}

const PFAuthenticationLoginWithGoogleAccountRequest* ConvertLoginWithGoogleAccountRequestToPlayfab(TSharedPtr<const FPFAuthenticationLoginWithGoogleAccountRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationLoginWithGoogleAccountRequest* ConvertedType = new PFAuthenticationLoginWithGoogleAccountRequest{
		.createAccount = Datatype->createAccount,
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(Datatype->infoRequestParameters),
		.playerSecret = ConvertFStringToCharPtr(Datatype->playerSecret),
		.serverAuthCode = ConvertFStringToCharPtr(Datatype->serverAuthCode),
		.setEmail = new bool(*Datatype->setEmail)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAuthenticationLoginWithGooglePlayGamesServicesRequest> ConvertLoginWithGooglePlayGamesServicesRequestToUnreal(const PFAuthenticationLoginWithGooglePlayGamesServicesRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationLoginWithGooglePlayGamesServicesRequest> ConvertedType = MakeShared<FPFAuthenticationLoginWithGooglePlayGamesServicesRequest>(FPFAuthenticationLoginWithGooglePlayGamesServicesRequest{
		.createAccount = Datatype->createAccount,
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToUnreal(Datatype->infoRequestParameters),
		.playerSecret = Datatype->playerSecret == nullptr ? FString() : FString(Datatype->playerSecret),
		.serverAuthCode = Datatype->serverAuthCode == nullptr ? FString() : FString(Datatype->serverAuthCode)
	});

	return ConvertedType;
}

const PFAuthenticationLoginWithGooglePlayGamesServicesRequest* ConvertLoginWithGooglePlayGamesServicesRequestToPlayfab(TSharedPtr<const FPFAuthenticationLoginWithGooglePlayGamesServicesRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationLoginWithGooglePlayGamesServicesRequest* ConvertedType = new PFAuthenticationLoginWithGooglePlayGamesServicesRequest{
		.createAccount = Datatype->createAccount,
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(Datatype->infoRequestParameters),
		.playerSecret = ConvertFStringToCharPtr(Datatype->playerSecret),
		.serverAuthCode = ConvertFStringToCharPtr(Datatype->serverAuthCode)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAuthenticationLoginWithIOSDeviceIDRequest> ConvertLoginWithIOSDeviceIDRequestToUnreal(const PFAuthenticationLoginWithIOSDeviceIDRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationLoginWithIOSDeviceIDRequest> ConvertedType = MakeShared<FPFAuthenticationLoginWithIOSDeviceIDRequest>(FPFAuthenticationLoginWithIOSDeviceIDRequest{
		.createAccount = Datatype->createAccount,
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.deviceId = Datatype->deviceId == nullptr ? FString() : FString(Datatype->deviceId),
		.deviceModel = Datatype->deviceModel == nullptr ? FString() : FString(Datatype->deviceModel),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToUnreal(Datatype->infoRequestParameters),
		.OS = Datatype->OS == nullptr ? FString() : FString(Datatype->OS),
		.playerSecret = Datatype->playerSecret == nullptr ? FString() : FString(Datatype->playerSecret)
	});

	return ConvertedType;
}

const PFAuthenticationLoginWithIOSDeviceIDRequest* ConvertLoginWithIOSDeviceIDRequestToPlayfab(TSharedPtr<const FPFAuthenticationLoginWithIOSDeviceIDRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationLoginWithIOSDeviceIDRequest* ConvertedType = new PFAuthenticationLoginWithIOSDeviceIDRequest{
		.createAccount = Datatype->createAccount,
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.deviceId = ConvertFStringToCharPtr(Datatype->deviceId),
		.deviceModel = ConvertFStringToCharPtr(Datatype->deviceModel),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(Datatype->infoRequestParameters),
		.OS = ConvertFStringToCharPtr(Datatype->OS),
		.playerSecret = ConvertFStringToCharPtr(Datatype->playerSecret)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAuthenticationLoginWithKongregateRequest> ConvertLoginWithKongregateRequestToUnreal(const PFAuthenticationLoginWithKongregateRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationLoginWithKongregateRequest> ConvertedType = MakeShared<FPFAuthenticationLoginWithKongregateRequest>(FPFAuthenticationLoginWithKongregateRequest{
		.authTicket = Datatype->authTicket == nullptr ? FString() : FString(Datatype->authTicket),
		.createAccount = Datatype->createAccount,
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToUnreal(Datatype->infoRequestParameters),
		.kongregateId = Datatype->kongregateId == nullptr ? FString() : FString(Datatype->kongregateId),
		.playerSecret = Datatype->playerSecret == nullptr ? FString() : FString(Datatype->playerSecret)
	});

	return ConvertedType;
}

const PFAuthenticationLoginWithKongregateRequest* ConvertLoginWithKongregateRequestToPlayfab(TSharedPtr<const FPFAuthenticationLoginWithKongregateRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationLoginWithKongregateRequest* ConvertedType = new PFAuthenticationLoginWithKongregateRequest{
		.authTicket = ConvertFStringToCharPtr(Datatype->authTicket),
		.createAccount = Datatype->createAccount,
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(Datatype->infoRequestParameters),
		.kongregateId = ConvertFStringToCharPtr(Datatype->kongregateId),
		.playerSecret = ConvertFStringToCharPtr(Datatype->playerSecret)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAuthenticationLoginWithNintendoServiceAccountRequest> ConvertLoginWithNintendoServiceAccountRequestToUnreal(const PFAuthenticationLoginWithNintendoServiceAccountRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationLoginWithNintendoServiceAccountRequest> ConvertedType = MakeShared<FPFAuthenticationLoginWithNintendoServiceAccountRequest>(FPFAuthenticationLoginWithNintendoServiceAccountRequest{
		.createAccount = Datatype->createAccount,
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.identityToken = Datatype->identityToken == nullptr ? FString() : FString(Datatype->identityToken),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToUnreal(Datatype->infoRequestParameters),
		.playerSecret = Datatype->playerSecret == nullptr ? FString() : FString(Datatype->playerSecret)
	});

	return ConvertedType;
}

const PFAuthenticationLoginWithNintendoServiceAccountRequest* ConvertLoginWithNintendoServiceAccountRequestToPlayfab(TSharedPtr<const FPFAuthenticationLoginWithNintendoServiceAccountRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationLoginWithNintendoServiceAccountRequest* ConvertedType = new PFAuthenticationLoginWithNintendoServiceAccountRequest{
		.createAccount = Datatype->createAccount,
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.identityToken = ConvertFStringToCharPtr(Datatype->identityToken),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(Datatype->infoRequestParameters),
		.playerSecret = ConvertFStringToCharPtr(Datatype->playerSecret)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAuthenticationLoginWithNintendoSwitchDeviceIdRequest> ConvertLoginWithNintendoSwitchDeviceIdRequestToUnreal(const PFAuthenticationLoginWithNintendoSwitchDeviceIdRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationLoginWithNintendoSwitchDeviceIdRequest> ConvertedType = MakeShared<FPFAuthenticationLoginWithNintendoSwitchDeviceIdRequest>(FPFAuthenticationLoginWithNintendoSwitchDeviceIdRequest{
		.createAccount = Datatype->createAccount,
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToUnreal(Datatype->infoRequestParameters),
		.nintendoSwitchDeviceId = Datatype->nintendoSwitchDeviceId == nullptr ? FString() : FString(Datatype->nintendoSwitchDeviceId),
		.playerSecret = Datatype->playerSecret == nullptr ? FString() : FString(Datatype->playerSecret)
	});

	return ConvertedType;
}

const PFAuthenticationLoginWithNintendoSwitchDeviceIdRequest* ConvertLoginWithNintendoSwitchDeviceIdRequestToPlayfab(TSharedPtr<const FPFAuthenticationLoginWithNintendoSwitchDeviceIdRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationLoginWithNintendoSwitchDeviceIdRequest* ConvertedType = new PFAuthenticationLoginWithNintendoSwitchDeviceIdRequest{
		.createAccount = Datatype->createAccount,
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(Datatype->infoRequestParameters),
		.nintendoSwitchDeviceId = ConvertFStringToCharPtr(Datatype->nintendoSwitchDeviceId),
		.playerSecret = ConvertFStringToCharPtr(Datatype->playerSecret)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAuthenticationLoginWithOpenIdConnectRequest> ConvertLoginWithOpenIdConnectRequestToUnreal(const PFAuthenticationLoginWithOpenIdConnectRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationLoginWithOpenIdConnectRequest> ConvertedType = MakeShared<FPFAuthenticationLoginWithOpenIdConnectRequest>(FPFAuthenticationLoginWithOpenIdConnectRequest{
		.connectionId = Datatype->connectionId == nullptr ? FString() : FString(Datatype->connectionId),
		.createAccount = Datatype->createAccount,
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.idToken = Datatype->idToken == nullptr ? FString() : FString(Datatype->idToken),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToUnreal(Datatype->infoRequestParameters),
		.playerSecret = Datatype->playerSecret == nullptr ? FString() : FString(Datatype->playerSecret)
	});

	return ConvertedType;
}

const PFAuthenticationLoginWithOpenIdConnectRequest* ConvertLoginWithOpenIdConnectRequestToPlayfab(TSharedPtr<const FPFAuthenticationLoginWithOpenIdConnectRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationLoginWithOpenIdConnectRequest* ConvertedType = new PFAuthenticationLoginWithOpenIdConnectRequest{
		.connectionId = ConvertFStringToCharPtr(Datatype->connectionId),
		.createAccount = Datatype->createAccount,
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.idToken = ConvertFStringToCharPtr(Datatype->idToken),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(Datatype->infoRequestParameters),
		.playerSecret = ConvertFStringToCharPtr(Datatype->playerSecret)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAuthenticationLoginWithPlayFabRequest> ConvertLoginWithPlayFabRequestToUnreal(const PFAuthenticationLoginWithPlayFabRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationLoginWithPlayFabRequest> ConvertedType = MakeShared<FPFAuthenticationLoginWithPlayFabRequest>(FPFAuthenticationLoginWithPlayFabRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToUnreal(Datatype->infoRequestParameters),
		.password = Datatype->password == nullptr ? FString() : FString(Datatype->password),
		.username = Datatype->username == nullptr ? FString() : FString(Datatype->username)
	});

	return ConvertedType;
}

const PFAuthenticationLoginWithPlayFabRequest* ConvertLoginWithPlayFabRequestToPlayfab(TSharedPtr<const FPFAuthenticationLoginWithPlayFabRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationLoginWithPlayFabRequest* ConvertedType = new PFAuthenticationLoginWithPlayFabRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(Datatype->infoRequestParameters),
		.password = ConvertFStringToCharPtr(Datatype->password),
		.username = ConvertFStringToCharPtr(Datatype->username)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAuthenticationLoginWithPSNRequest> ConvertLoginWithPSNRequestToUnreal(const PFAuthenticationLoginWithPSNRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationLoginWithPSNRequest> ConvertedType = MakeShared<FPFAuthenticationLoginWithPSNRequest>(FPFAuthenticationLoginWithPSNRequest{
		.authCode = Datatype->authCode == nullptr ? FString() : FString(Datatype->authCode),
		.createAccount = Datatype->createAccount,
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToUnreal(Datatype->infoRequestParameters),
		.issuerId = TSharedPtr<const int32>(Datatype->issuerId),
		.playerSecret = Datatype->playerSecret == nullptr ? FString() : FString(Datatype->playerSecret),
		.redirectUri = Datatype->redirectUri == nullptr ? FString() : FString(Datatype->redirectUri)
	});

	return ConvertedType;
}

const PFAuthenticationLoginWithPSNRequest* ConvertLoginWithPSNRequestToPlayfab(TSharedPtr<const FPFAuthenticationLoginWithPSNRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationLoginWithPSNRequest* ConvertedType = new PFAuthenticationLoginWithPSNRequest{
		.authCode = ConvertFStringToCharPtr(Datatype->authCode),
		.createAccount = Datatype->createAccount,
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(Datatype->infoRequestParameters),
		.issuerId = new int32(*Datatype->issuerId),
		.playerSecret = ConvertFStringToCharPtr(Datatype->playerSecret),
		.redirectUri = ConvertFStringToCharPtr(Datatype->redirectUri)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAuthenticationLoginWithSteamRequest> ConvertLoginWithSteamRequestToUnreal(const PFAuthenticationLoginWithSteamRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationLoginWithSteamRequest> ConvertedType = MakeShared<FPFAuthenticationLoginWithSteamRequest>(FPFAuthenticationLoginWithSteamRequest{
		.createAccount = Datatype->createAccount,
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToUnreal(Datatype->infoRequestParameters),
		.playerSecret = Datatype->playerSecret == nullptr ? FString() : FString(Datatype->playerSecret),
		.steamTicket = Datatype->steamTicket == nullptr ? FString() : FString(Datatype->steamTicket),
		.ticketIsServiceSpecific = TSharedPtr<const bool>(Datatype->ticketIsServiceSpecific)
	});

	return ConvertedType;
}

const PFAuthenticationLoginWithSteamRequest* ConvertLoginWithSteamRequestToPlayfab(TSharedPtr<const FPFAuthenticationLoginWithSteamRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationLoginWithSteamRequest* ConvertedType = new PFAuthenticationLoginWithSteamRequest{
		.createAccount = Datatype->createAccount,
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(Datatype->infoRequestParameters),
		.playerSecret = ConvertFStringToCharPtr(Datatype->playerSecret),
		.steamTicket = ConvertFStringToCharPtr(Datatype->steamTicket),
		.ticketIsServiceSpecific = new bool(*Datatype->ticketIsServiceSpecific)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAuthenticationLoginWithTwitchRequest> ConvertLoginWithTwitchRequestToUnreal(const PFAuthenticationLoginWithTwitchRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationLoginWithTwitchRequest> ConvertedType = MakeShared<FPFAuthenticationLoginWithTwitchRequest>(FPFAuthenticationLoginWithTwitchRequest{
		.accessToken = Datatype->accessToken == nullptr ? FString() : FString(Datatype->accessToken),
		.createAccount = Datatype->createAccount,
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToUnreal(Datatype->infoRequestParameters),
		.playerSecret = Datatype->playerSecret == nullptr ? FString() : FString(Datatype->playerSecret)
	});

	return ConvertedType;
}

const PFAuthenticationLoginWithTwitchRequest* ConvertLoginWithTwitchRequestToPlayfab(TSharedPtr<const FPFAuthenticationLoginWithTwitchRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationLoginWithTwitchRequest* ConvertedType = new PFAuthenticationLoginWithTwitchRequest{
		.accessToken = ConvertFStringToCharPtr(Datatype->accessToken),
		.createAccount = Datatype->createAccount,
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(Datatype->infoRequestParameters),
		.playerSecret = ConvertFStringToCharPtr(Datatype->playerSecret)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAuthenticationLoginWithXboxRequest> ConvertLoginWithXboxRequestToUnreal(const PFAuthenticationLoginWithXboxRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationLoginWithXboxRequest> ConvertedType = MakeShared<FPFAuthenticationLoginWithXboxRequest>(FPFAuthenticationLoginWithXboxRequest{
		.createAccount = Datatype->createAccount,
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToUnreal(Datatype->infoRequestParameters),
		.playerSecret = Datatype->playerSecret == nullptr ? FString() : FString(Datatype->playerSecret),
		.xboxToken = Datatype->xboxToken == nullptr ? FString() : FString(Datatype->xboxToken)
	});

	return ConvertedType;
}

const PFAuthenticationLoginWithXboxRequest* ConvertLoginWithXboxRequestToPlayfab(TSharedPtr<const FPFAuthenticationLoginWithXboxRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationLoginWithXboxRequest* ConvertedType = new PFAuthenticationLoginWithXboxRequest{
		.createAccount = Datatype->createAccount,
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(Datatype->infoRequestParameters),
		.playerSecret = ConvertFStringToCharPtr(Datatype->playerSecret),
		.xboxToken = ConvertFStringToCharPtr(Datatype->xboxToken)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAuthenticationRegisterPlayFabUserRequest> ConvertRegisterPlayFabUserRequestToUnreal(const PFAuthenticationRegisterPlayFabUserRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationRegisterPlayFabUserRequest> ConvertedType = MakeShared<FPFAuthenticationRegisterPlayFabUserRequest>(FPFAuthenticationRegisterPlayFabUserRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.displayName = Datatype->displayName == nullptr ? FString() : FString(Datatype->displayName),
		.email = Datatype->email == nullptr ? FString() : FString(Datatype->email),
		.encryptedRequest = Datatype->encryptedRequest == nullptr ? FString() : FString(Datatype->encryptedRequest),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToUnreal(Datatype->infoRequestParameters),
		.password = Datatype->password == nullptr ? FString() : FString(Datatype->password),
		.playerSecret = Datatype->playerSecret == nullptr ? FString() : FString(Datatype->playerSecret),
		.requireBothUsernameAndEmail = TSharedPtr<const bool>(Datatype->requireBothUsernameAndEmail),
		.titleId = Datatype->titleId == nullptr ? FString() : FString(Datatype->titleId),
		.username = Datatype->username == nullptr ? FString() : FString(Datatype->username)
	});

	return ConvertedType;
}

const PFAuthenticationRegisterPlayFabUserRequest* ConvertRegisterPlayFabUserRequestToPlayfab(TSharedPtr<const FPFAuthenticationRegisterPlayFabUserRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationRegisterPlayFabUserRequest* ConvertedType = new PFAuthenticationRegisterPlayFabUserRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.displayName = ConvertFStringToCharPtr(Datatype->displayName),
		.email = ConvertFStringToCharPtr(Datatype->email),
		.encryptedRequest = ConvertFStringToCharPtr(Datatype->encryptedRequest),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(Datatype->infoRequestParameters),
		.password = ConvertFStringToCharPtr(Datatype->password),
		.playerSecret = ConvertFStringToCharPtr(Datatype->playerSecret),
		.requireBothUsernameAndEmail = new bool(*Datatype->requireBothUsernameAndEmail),
		.titleId = ConvertFStringToCharPtr(Datatype->titleId),
		.username = ConvertFStringToCharPtr(Datatype->username)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAuthenticationRegisterPlayFabUserResult> ConvertRegisterPlayFabUserResultToUnreal(const PFAuthenticationRegisterPlayFabUserResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationRegisterPlayFabUserResult> ConvertedType = MakeShared<FPFAuthenticationRegisterPlayFabUserResult>(FPFAuthenticationRegisterPlayFabUserResult{
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId),
		.settingsForUser = ConvertUserSettingsToUnreal(Datatype->settingsForUser),
		.username = Datatype->username == nullptr ? FString() : FString(Datatype->username)
	});

	return ConvertedType;
}

const PFAuthenticationRegisterPlayFabUserResult* ConvertRegisterPlayFabUserResultToPlayfab(TSharedPtr<const FPFAuthenticationRegisterPlayFabUserResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationRegisterPlayFabUserResult* ConvertedType = new PFAuthenticationRegisterPlayFabUserResult{
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId),
		.settingsForUser = ConvertUserSettingsToPlayfab(Datatype->settingsForUser),
		.username = ConvertFStringToCharPtr(Datatype->username)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAuthenticationServerLoginWithAndroidDeviceIDRequest> ConvertServerLoginWithAndroidDeviceIDRequestToUnreal(const PFAuthenticationServerLoginWithAndroidDeviceIDRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationServerLoginWithAndroidDeviceIDRequest> ConvertedType = MakeShared<FPFAuthenticationServerLoginWithAndroidDeviceIDRequest>(FPFAuthenticationServerLoginWithAndroidDeviceIDRequest{
		.androidDevice = Datatype->androidDevice == nullptr ? FString() : FString(Datatype->androidDevice),
		.androidDeviceId = Datatype->androidDeviceId == nullptr ? FString() : FString(Datatype->androidDeviceId),
		.createAccount = Datatype->createAccount,
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToUnreal(Datatype->infoRequestParameters),
		.OS = Datatype->OS == nullptr ? FString() : FString(Datatype->OS)
	});

	return ConvertedType;
}

const PFAuthenticationServerLoginWithAndroidDeviceIDRequest* ConvertServerLoginWithAndroidDeviceIDRequestToPlayfab(TSharedPtr<const FPFAuthenticationServerLoginWithAndroidDeviceIDRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationServerLoginWithAndroidDeviceIDRequest* ConvertedType = new PFAuthenticationServerLoginWithAndroidDeviceIDRequest{
		.androidDevice = ConvertFStringToCharPtr(Datatype->androidDevice),
		.androidDeviceId = ConvertFStringToCharPtr(Datatype->androidDeviceId),
		.createAccount = Datatype->createAccount,
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(Datatype->infoRequestParameters),
		.OS = ConvertFStringToCharPtr(Datatype->OS)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAuthenticationServerLoginWithBattleNetRequest> ConvertServerLoginWithBattleNetRequestToUnreal(const PFAuthenticationServerLoginWithBattleNetRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationServerLoginWithBattleNetRequest> ConvertedType = MakeShared<FPFAuthenticationServerLoginWithBattleNetRequest>(FPFAuthenticationServerLoginWithBattleNetRequest{
		.createAccount = Datatype->createAccount,
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.identityToken = Datatype->identityToken == nullptr ? FString() : FString(Datatype->identityToken),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToUnreal(Datatype->infoRequestParameters)
	});

	return ConvertedType;
}

const PFAuthenticationServerLoginWithBattleNetRequest* ConvertServerLoginWithBattleNetRequestToPlayfab(TSharedPtr<const FPFAuthenticationServerLoginWithBattleNetRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationServerLoginWithBattleNetRequest* ConvertedType = new PFAuthenticationServerLoginWithBattleNetRequest{
		.createAccount = Datatype->createAccount,
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.identityToken = ConvertFStringToCharPtr(Datatype->identityToken),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(Datatype->infoRequestParameters)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAuthenticationServerLoginWithCustomIDRequest> ConvertServerLoginWithCustomIDRequestToUnreal(const PFAuthenticationServerLoginWithCustomIDRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationServerLoginWithCustomIDRequest> ConvertedType = MakeShared<FPFAuthenticationServerLoginWithCustomIDRequest>(FPFAuthenticationServerLoginWithCustomIDRequest{
		.createAccount = Datatype->createAccount,
		.customId = Datatype->customId == nullptr ? FString() : FString(Datatype->customId),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToUnreal(Datatype->infoRequestParameters)
	});

	return ConvertedType;
}

const PFAuthenticationServerLoginWithCustomIDRequest* ConvertServerLoginWithCustomIDRequestToPlayfab(TSharedPtr<const FPFAuthenticationServerLoginWithCustomIDRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationServerLoginWithCustomIDRequest* ConvertedType = new PFAuthenticationServerLoginWithCustomIDRequest{
		.createAccount = Datatype->createAccount,
		.customId = ConvertFStringToCharPtr(Datatype->customId),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(Datatype->infoRequestParameters)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAuthenticationServerLoginWithIOSDeviceIDRequest> ConvertServerLoginWithIOSDeviceIDRequestToUnreal(const PFAuthenticationServerLoginWithIOSDeviceIDRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationServerLoginWithIOSDeviceIDRequest> ConvertedType = MakeShared<FPFAuthenticationServerLoginWithIOSDeviceIDRequest>(FPFAuthenticationServerLoginWithIOSDeviceIDRequest{
		.createAccount = Datatype->createAccount,
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.deviceId = Datatype->deviceId == nullptr ? FString() : FString(Datatype->deviceId),
		.deviceModel = Datatype->deviceModel == nullptr ? FString() : FString(Datatype->deviceModel),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToUnreal(Datatype->infoRequestParameters),
		.OS = Datatype->OS == nullptr ? FString() : FString(Datatype->OS)
	});

	return ConvertedType;
}

const PFAuthenticationServerLoginWithIOSDeviceIDRequest* ConvertServerLoginWithIOSDeviceIDRequestToPlayfab(TSharedPtr<const FPFAuthenticationServerLoginWithIOSDeviceIDRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationServerLoginWithIOSDeviceIDRequest* ConvertedType = new PFAuthenticationServerLoginWithIOSDeviceIDRequest{
		.createAccount = Datatype->createAccount,
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.deviceId = ConvertFStringToCharPtr(Datatype->deviceId),
		.deviceModel = ConvertFStringToCharPtr(Datatype->deviceModel),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(Datatype->infoRequestParameters),
		.OS = ConvertFStringToCharPtr(Datatype->OS)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAuthenticationServerLoginWithPSNRequest> ConvertServerLoginWithPSNRequestToUnreal(const PFAuthenticationServerLoginWithPSNRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationServerLoginWithPSNRequest> ConvertedType = MakeShared<FPFAuthenticationServerLoginWithPSNRequest>(FPFAuthenticationServerLoginWithPSNRequest{
		.authCode = Datatype->authCode == nullptr ? FString() : FString(Datatype->authCode),
		.createAccount = Datatype->createAccount,
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToUnreal(Datatype->infoRequestParameters),
		.issuerId = TSharedPtr<const int32>(Datatype->issuerId),
		.redirectUri = Datatype->redirectUri == nullptr ? FString() : FString(Datatype->redirectUri)
	});

	return ConvertedType;
}

const PFAuthenticationServerLoginWithPSNRequest* ConvertServerLoginWithPSNRequestToPlayfab(TSharedPtr<const FPFAuthenticationServerLoginWithPSNRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationServerLoginWithPSNRequest* ConvertedType = new PFAuthenticationServerLoginWithPSNRequest{
		.authCode = ConvertFStringToCharPtr(Datatype->authCode),
		.createAccount = Datatype->createAccount,
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(Datatype->infoRequestParameters),
		.issuerId = new int32(*Datatype->issuerId),
		.redirectUri = ConvertFStringToCharPtr(Datatype->redirectUri)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAuthenticationLoginWithServerCustomIdRequest> ConvertLoginWithServerCustomIdRequestToUnreal(const PFAuthenticationLoginWithServerCustomIdRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationLoginWithServerCustomIdRequest> ConvertedType = MakeShared<FPFAuthenticationLoginWithServerCustomIdRequest>(FPFAuthenticationLoginWithServerCustomIdRequest{
		.createAccount = Datatype->createAccount,
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToUnreal(Datatype->infoRequestParameters),
		.playerSecret = Datatype->playerSecret == nullptr ? FString() : FString(Datatype->playerSecret),
		.serverCustomId = Datatype->serverCustomId == nullptr ? FString() : FString(Datatype->serverCustomId)
	});

	return ConvertedType;
}

const PFAuthenticationLoginWithServerCustomIdRequest* ConvertLoginWithServerCustomIdRequestToPlayfab(TSharedPtr<const FPFAuthenticationLoginWithServerCustomIdRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationLoginWithServerCustomIdRequest* ConvertedType = new PFAuthenticationLoginWithServerCustomIdRequest{
		.createAccount = Datatype->createAccount,
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(Datatype->infoRequestParameters),
		.playerSecret = ConvertFStringToCharPtr(Datatype->playerSecret),
		.serverCustomId = ConvertFStringToCharPtr(Datatype->serverCustomId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAuthenticationLoginWithSteamIdRequest> ConvertLoginWithSteamIdRequestToUnreal(const PFAuthenticationLoginWithSteamIdRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationLoginWithSteamIdRequest> ConvertedType = MakeShared<FPFAuthenticationLoginWithSteamIdRequest>(FPFAuthenticationLoginWithSteamIdRequest{
		.createAccount = Datatype->createAccount,
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToUnreal(Datatype->infoRequestParameters),
		.steamId = Datatype->steamId == nullptr ? FString() : FString(Datatype->steamId)
	});

	return ConvertedType;
}

const PFAuthenticationLoginWithSteamIdRequest* ConvertLoginWithSteamIdRequestToPlayfab(TSharedPtr<const FPFAuthenticationLoginWithSteamIdRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationLoginWithSteamIdRequest* ConvertedType = new PFAuthenticationLoginWithSteamIdRequest{
		.createAccount = Datatype->createAccount,
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(Datatype->infoRequestParameters),
		.steamId = ConvertFStringToCharPtr(Datatype->steamId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAuthenticationServerLoginWithXboxRequest> ConvertServerLoginWithXboxRequestToUnreal(const PFAuthenticationServerLoginWithXboxRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationServerLoginWithXboxRequest> ConvertedType = MakeShared<FPFAuthenticationServerLoginWithXboxRequest>(FPFAuthenticationServerLoginWithXboxRequest{
		.createAccount = Datatype->createAccount,
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToUnreal(Datatype->infoRequestParameters),
		.xboxToken = Datatype->xboxToken == nullptr ? FString() : FString(Datatype->xboxToken)
	});

	return ConvertedType;
}

const PFAuthenticationServerLoginWithXboxRequest* ConvertServerLoginWithXboxRequestToPlayfab(TSharedPtr<const FPFAuthenticationServerLoginWithXboxRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationServerLoginWithXboxRequest* ConvertedType = new PFAuthenticationServerLoginWithXboxRequest{
		.createAccount = Datatype->createAccount,
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(Datatype->infoRequestParameters),
		.xboxToken = ConvertFStringToCharPtr(Datatype->xboxToken)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAuthenticationLoginWithXboxIdRequest> ConvertLoginWithXboxIdRequestToUnreal(const PFAuthenticationLoginWithXboxIdRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationLoginWithXboxIdRequest> ConvertedType = MakeShared<FPFAuthenticationLoginWithXboxIdRequest>(FPFAuthenticationLoginWithXboxIdRequest{
		.createAccount = Datatype->createAccount,
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToUnreal(Datatype->infoRequestParameters),
		.sandbox = Datatype->sandbox == nullptr ? FString() : FString(Datatype->sandbox),
		.xboxId = Datatype->xboxId == nullptr ? FString() : FString(Datatype->xboxId)
	});

	return ConvertedType;
}

const PFAuthenticationLoginWithXboxIdRequest* ConvertLoginWithXboxIdRequestToPlayfab(TSharedPtr<const FPFAuthenticationLoginWithXboxIdRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationLoginWithXboxIdRequest* ConvertedType = new PFAuthenticationLoginWithXboxIdRequest{
		.createAccount = Datatype->createAccount,
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(Datatype->infoRequestParameters),
		.sandbox = ConvertFStringToCharPtr(Datatype->sandbox),
		.xboxId = ConvertFStringToCharPtr(Datatype->xboxId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAuthenticationAuthenticateCustomIdRequest> ConvertAuthenticateCustomIdRequestToUnreal(const PFAuthenticationAuthenticateCustomIdRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationAuthenticateCustomIdRequest> ConvertedType = MakeShared<FPFAuthenticationAuthenticateCustomIdRequest>(FPFAuthenticationAuthenticateCustomIdRequest{
		.customId = Datatype->customId == nullptr ? FString() : FString(Datatype->customId),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount
	});

	return ConvertedType;
}

const PFAuthenticationAuthenticateCustomIdRequest* ConvertAuthenticateCustomIdRequestToPlayfab(TSharedPtr<const FPFAuthenticationAuthenticateCustomIdRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationAuthenticateCustomIdRequest* ConvertedType = new PFAuthenticationAuthenticateCustomIdRequest{
		.customId = ConvertFStringToCharPtr(Datatype->customId),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAuthenticationEntityTokenResponse> ConvertEntityTokenResponseToUnreal(const PFAuthenticationEntityTokenResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationEntityTokenResponse> ConvertedType = MakeShared<FPFAuthenticationEntityTokenResponse>(FPFAuthenticationEntityTokenResponse{
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.entityToken = Datatype->entityToken == nullptr ? FString() : FString(Datatype->entityToken),
		.tokenExpiration = ConvertTimeToUnreal(Datatype->tokenExpiration)
	});

	return ConvertedType;
}

const PFAuthenticationEntityTokenResponse* ConvertEntityTokenResponseToPlayfab(TSharedPtr<const FPFAuthenticationEntityTokenResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationEntityTokenResponse* ConvertedType = new PFAuthenticationEntityTokenResponse{
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.entityToken = ConvertFStringToCharPtr(Datatype->entityToken),
		.tokenExpiration = ConvertFDateTimeToPlayfab(Datatype->tokenExpiration)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAuthenticationAuthenticateCustomIdResult> ConvertAuthenticateCustomIdResultToUnreal(const PFAuthenticationAuthenticateCustomIdResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationAuthenticateCustomIdResult> ConvertedType = MakeShared<FPFAuthenticationAuthenticateCustomIdResult>(FPFAuthenticationAuthenticateCustomIdResult{
		.entityToken = ConvertEntityTokenResponseToUnreal(Datatype->entityToken),
		.newlyCreated = Datatype->newlyCreated
	});

	return ConvertedType;
}

const PFAuthenticationAuthenticateCustomIdResult* ConvertAuthenticateCustomIdResultToPlayfab(TSharedPtr<const FPFAuthenticationAuthenticateCustomIdResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationAuthenticateCustomIdResult* ConvertedType = new PFAuthenticationAuthenticateCustomIdResult{
		.entityToken = ConvertEntityTokenResponseToPlayfab(Datatype->entityToken),
		.newlyCreated = Datatype->newlyCreated
	};

	return ConvertedType;
}

TSharedPtr<const FPFAuthenticationDeleteRequest> ConvertDeleteRequestToUnreal(const PFAuthenticationDeleteRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationDeleteRequest> ConvertedType = MakeShared<FPFAuthenticationDeleteRequest>(FPFAuthenticationDeleteRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity)
	});

	return ConvertedType;
}

const PFAuthenticationDeleteRequest* ConvertDeleteRequestToPlayfab(TSharedPtr<const FPFAuthenticationDeleteRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationDeleteRequest* ConvertedType = new PFAuthenticationDeleteRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAuthenticationGetEntityRequest> ConvertGetEntityRequestToUnreal(const PFAuthenticationGetEntityRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationGetEntityRequest> ConvertedType = MakeShared<FPFAuthenticationGetEntityRequest>(FPFAuthenticationGetEntityRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity)
	});

	return ConvertedType;
}

const PFAuthenticationGetEntityRequest* ConvertGetEntityRequestToPlayfab(TSharedPtr<const FPFAuthenticationGetEntityRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationGetEntityRequest* ConvertedType = new PFAuthenticationGetEntityRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAuthenticationValidateEntityTokenRequest> ConvertValidateEntityTokenRequestToUnreal(const PFAuthenticationValidateEntityTokenRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationValidateEntityTokenRequest> ConvertedType = MakeShared<FPFAuthenticationValidateEntityTokenRequest>(FPFAuthenticationValidateEntityTokenRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entityToken = Datatype->entityToken == nullptr ? FString() : FString(Datatype->entityToken)
	});

	return ConvertedType;
}

const PFAuthenticationValidateEntityTokenRequest* ConvertValidateEntityTokenRequestToPlayfab(TSharedPtr<const FPFAuthenticationValidateEntityTokenRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationValidateEntityTokenRequest* ConvertedType = new PFAuthenticationValidateEntityTokenRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entityToken = ConvertFStringToCharPtr(Datatype->entityToken)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAuthenticationValidateEntityTokenResponse> ConvertValidateEntityTokenResponseToUnreal(const PFAuthenticationValidateEntityTokenResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAuthenticationValidateEntityTokenResponse> ConvertedType = MakeShared<FPFAuthenticationValidateEntityTokenResponse>(FPFAuthenticationValidateEntityTokenResponse{
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.identifiedDeviceType = MakeShared<FPFAuthenticationIdentifiedDeviceType>(ConvertIdentifiedDeviceTypeToUnreal(Datatype->identifiedDeviceType)),
		.identityProvider = MakeShared<FPFLoginIdentityProvider>(ConvertLoginIdentityProviderToUnreal(Datatype->identityProvider)),
		.identityProviderIssuedId = Datatype->identityProviderIssuedId == nullptr ? FString() : FString(Datatype->identityProviderIssuedId),
		.lineage = ConvertEntityLineageToUnreal(Datatype->lineage)
	});

	return ConvertedType;
}

const PFAuthenticationValidateEntityTokenResponse* ConvertValidateEntityTokenResponseToPlayfab(TSharedPtr<const FPFAuthenticationValidateEntityTokenResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAuthenticationValidateEntityTokenResponse* ConvertedType = new PFAuthenticationValidateEntityTokenResponse{
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.identifiedDeviceType = new PFAuthenticationIdentifiedDeviceType(ConvertIdentifiedDeviceTypeToPlayfab(Datatype->identifiedDeviceType)),
		.identityProvider = new PFLoginIdentityProvider(ConvertLoginIdentityProviderToPlayfab(Datatype->identityProvider)),
		.identityProviderIssuedId = ConvertFStringToCharPtr(Datatype->identityProviderIssuedId),
		.lineage = ConvertEntityLineageToPlayfab(Datatype->lineage)
	};

	return ConvertedType;
}

