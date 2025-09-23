// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFPlatformSpecificTypeConverters.h"

TSharedPtr<const FPFPlatformSpecificAndroidDevicePushNotificationRegistrationRequest> ConvertAndroidDevicePushNotificationRegistrationRequestToUnreal(const PFPlatformSpecificAndroidDevicePushNotificationRegistrationRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFPlatformSpecificAndroidDevicePushNotificationRegistrationRequest> ConvertedType = MakeShared<FPFPlatformSpecificAndroidDevicePushNotificationRegistrationRequest>(FPFPlatformSpecificAndroidDevicePushNotificationRegistrationRequest{
		.confirmationMessage = Datatype->confirmationMessage == nullptr ? FString() : FString(Datatype->confirmationMessage),
		.deviceToken = Datatype->deviceToken == nullptr ? FString() : FString(Datatype->deviceToken),
		.sendPushNotificationConfirmation = TSharedPtr<const bool>(Datatype->sendPushNotificationConfirmation)
	});

	return ConvertedType;
}

const PFPlatformSpecificAndroidDevicePushNotificationRegistrationRequest* ConvertAndroidDevicePushNotificationRegistrationRequestToPlayfab(TSharedPtr<const FPFPlatformSpecificAndroidDevicePushNotificationRegistrationRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFPlatformSpecificAndroidDevicePushNotificationRegistrationRequest* ConvertedType = new PFPlatformSpecificAndroidDevicePushNotificationRegistrationRequest{
		.confirmationMessage = ConvertFStringToCharPtr(Datatype->confirmationMessage),
		.deviceToken = ConvertFStringToCharPtr(Datatype->deviceToken),
		.sendPushNotificationConfirmation = Datatype->sendPushNotificationConfirmation ? new bool(*Datatype->sendPushNotificationConfirmation) : nullptr
	};

	return ConvertedType;
}

TSharedPtr<const FPFPlatformSpecificRefreshPSNAuthTokenRequest> ConvertRefreshPSNAuthTokenRequestToUnreal(const PFPlatformSpecificRefreshPSNAuthTokenRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFPlatformSpecificRefreshPSNAuthTokenRequest> ConvertedType = MakeShared<FPFPlatformSpecificRefreshPSNAuthTokenRequest>(FPFPlatformSpecificRefreshPSNAuthTokenRequest{
		.authCode = Datatype->authCode == nullptr ? FString() : FString(Datatype->authCode),
		.issuerId = TSharedPtr<const int32>(Datatype->issuerId),
		.redirectUri = Datatype->redirectUri == nullptr ? FString() : FString(Datatype->redirectUri)
	});

	return ConvertedType;
}

const PFPlatformSpecificRefreshPSNAuthTokenRequest* ConvertRefreshPSNAuthTokenRequestToPlayfab(TSharedPtr<const FPFPlatformSpecificRefreshPSNAuthTokenRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFPlatformSpecificRefreshPSNAuthTokenRequest* ConvertedType = new PFPlatformSpecificRefreshPSNAuthTokenRequest{
		.authCode = ConvertFStringToCharPtr(Datatype->authCode),
		.issuerId = Datatype->issuerId ? new int32(*Datatype->issuerId) : nullptr,
		.redirectUri = ConvertFStringToCharPtr(Datatype->redirectUri)
	};

	return ConvertedType;
}

TSharedPtr<const FPFPlatformSpecificRegisterForIOSPushNotificationRequest> ConvertRegisterForIOSPushNotificationRequestToUnreal(const PFPlatformSpecificRegisterForIOSPushNotificationRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFPlatformSpecificRegisterForIOSPushNotificationRequest> ConvertedType = MakeShared<FPFPlatformSpecificRegisterForIOSPushNotificationRequest>(FPFPlatformSpecificRegisterForIOSPushNotificationRequest{
		.confirmationMessage = Datatype->confirmationMessage == nullptr ? FString() : FString(Datatype->confirmationMessage),
		.deviceToken = Datatype->deviceToken == nullptr ? FString() : FString(Datatype->deviceToken),
		.sendPushNotificationConfirmation = TSharedPtr<const bool>(Datatype->sendPushNotificationConfirmation)
	});

	return ConvertedType;
}

const PFPlatformSpecificRegisterForIOSPushNotificationRequest* ConvertRegisterForIOSPushNotificationRequestToPlayfab(TSharedPtr<const FPFPlatformSpecificRegisterForIOSPushNotificationRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFPlatformSpecificRegisterForIOSPushNotificationRequest* ConvertedType = new PFPlatformSpecificRegisterForIOSPushNotificationRequest{
		.confirmationMessage = ConvertFStringToCharPtr(Datatype->confirmationMessage),
		.deviceToken = ConvertFStringToCharPtr(Datatype->deviceToken),
		.sendPushNotificationConfirmation = Datatype->sendPushNotificationConfirmation ? new bool(*Datatype->sendPushNotificationConfirmation) : nullptr
	};

	return ConvertedType;
}

TSharedPtr<const FPFPlatformSpecificAwardSteamAchievementItem> ConvertAwardSteamAchievementItemToUnreal(const PFPlatformSpecificAwardSteamAchievementItem* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFPlatformSpecificAwardSteamAchievementItem> ConvertedType = MakeShared<FPFPlatformSpecificAwardSteamAchievementItem>(FPFPlatformSpecificAwardSteamAchievementItem{
		.achievementName = Datatype->achievementName == nullptr ? FString() : FString(Datatype->achievementName),
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId),
		.result = Datatype->result
	});

	return ConvertedType;
}

const PFPlatformSpecificAwardSteamAchievementItem* ConvertAwardSteamAchievementItemToPlayfab(TSharedPtr<const FPFPlatformSpecificAwardSteamAchievementItem> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFPlatformSpecificAwardSteamAchievementItem* ConvertedType = new PFPlatformSpecificAwardSteamAchievementItem{
		.achievementName = ConvertFStringToCharPtr(Datatype->achievementName),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId),
		.result = Datatype->result
	};

	return ConvertedType;
}

TSharedPtr<const FPFPlatformSpecificAwardSteamAchievementRequest> ConvertAwardSteamAchievementRequestToUnreal(const PFPlatformSpecificAwardSteamAchievementRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFPlatformSpecificAwardSteamAchievementRequest> ConvertedType = MakeShared<FPFPlatformSpecificAwardSteamAchievementRequest>(FPFPlatformSpecificAwardSteamAchievementRequest{
		.achievements = ConvertPlayfabArrayToUnreal(Datatype->achievements, Datatype->achievementsCount, ConvertAwardSteamAchievementItemToUnreal),
		.achievementsCount = Datatype->achievementsCount
	});

	return ConvertedType;
}

const PFPlatformSpecificAwardSteamAchievementRequest* ConvertAwardSteamAchievementRequestToPlayfab(TSharedPtr<const FPFPlatformSpecificAwardSteamAchievementRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFPlatformSpecificAwardSteamAchievementRequest* ConvertedType = new PFPlatformSpecificAwardSteamAchievementRequest{
		.achievements = ConvertUnrealArrayToPlayfab(Datatype->achievements, ConvertAwardSteamAchievementItemToPlayfab),
		.achievementsCount = (uint32_t)Datatype->achievements.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFPlatformSpecificAwardSteamAchievementResult> ConvertAwardSteamAchievementResultToUnreal(const PFPlatformSpecificAwardSteamAchievementResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFPlatformSpecificAwardSteamAchievementResult> ConvertedType = MakeShared<FPFPlatformSpecificAwardSteamAchievementResult>(FPFPlatformSpecificAwardSteamAchievementResult{
		.achievementResults = ConvertPlayfabArrayToUnreal(Datatype->achievementResults, Datatype->achievementResultsCount, ConvertAwardSteamAchievementItemToUnreal),
		.achievementResultsCount = Datatype->achievementResultsCount
	});

	return ConvertedType;
}

const PFPlatformSpecificAwardSteamAchievementResult* ConvertAwardSteamAchievementResultToPlayfab(TSharedPtr<const FPFPlatformSpecificAwardSteamAchievementResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFPlatformSpecificAwardSteamAchievementResult* ConvertedType = new PFPlatformSpecificAwardSteamAchievementResult{
		.achievementResults = ConvertUnrealArrayToPlayfab(Datatype->achievementResults, ConvertAwardSteamAchievementItemToPlayfab),
		.achievementResultsCount = (uint32_t)Datatype->achievementResults.Num()
	};

	return ConvertedType;
}
