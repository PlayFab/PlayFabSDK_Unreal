// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFPushNotificationsTypeConverters.h"

TSharedPtr<const FPFPushNotificationsAdvancedPushPlatformMsg> ConvertAdvancedPushPlatformMsgToUnreal(const PFPushNotificationsAdvancedPushPlatformMsg* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFPushNotificationsAdvancedPushPlatformMsg> ConvertedType = MakeShared<FPFPushNotificationsAdvancedPushPlatformMsg>(FPFPushNotificationsAdvancedPushPlatformMsg{
		.gCMDataOnly = TSharedPtr<const bool>(Datatype->gCMDataOnly),
		.json = Datatype->json == nullptr ? FString() : FString(Datatype->json),
		.platform = ConvertPushNotificationPlatformToUnreal(&Datatype->platform)
	});

	return ConvertedType;
}

const PFPushNotificationsAdvancedPushPlatformMsg* ConvertAdvancedPushPlatformMsgToPlayfab(TSharedPtr<const FPFPushNotificationsAdvancedPushPlatformMsg> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFPushNotificationsAdvancedPushPlatformMsg* ConvertedType = new PFPushNotificationsAdvancedPushPlatformMsg{
		.gCMDataOnly = Datatype->gCMDataOnly ? new bool(*Datatype->gCMDataOnly) : nullptr,
		.json = ConvertFStringToCharPtr(Datatype->json),
		.platform = ConvertPushNotificationPlatformToPlayfab(MakeShared<FPFPushNotificationPlatform>(Datatype->platform))
	};

	return ConvertedType;
}

TSharedPtr<const FPFPushNotificationsPushNotificationPackage> ConvertPushNotificationPackageToUnreal(const PFPushNotificationsPushNotificationPackage* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFPushNotificationsPushNotificationPackage> ConvertedType = MakeShared<FPFPushNotificationsPushNotificationPackage>(FPFPushNotificationsPushNotificationPackage{
		.badge = Datatype->badge,
		.customData = Datatype->customData == nullptr ? FString() : FString(Datatype->customData),
		.icon = Datatype->icon == nullptr ? FString() : FString(Datatype->icon),
		.message = Datatype->message == nullptr ? FString() : FString(Datatype->message),
		.sound = Datatype->sound == nullptr ? FString() : FString(Datatype->sound),
		.title = Datatype->title == nullptr ? FString() : FString(Datatype->title)
	});

	return ConvertedType;
}

const PFPushNotificationsPushNotificationPackage* ConvertPushNotificationPackageToPlayfab(TSharedPtr<const FPFPushNotificationsPushNotificationPackage> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFPushNotificationsPushNotificationPackage* ConvertedType = new PFPushNotificationsPushNotificationPackage{
		.badge = Datatype->badge,
		.customData = ConvertFStringToCharPtr(Datatype->customData),
		.icon = ConvertFStringToCharPtr(Datatype->icon),
		.message = ConvertFStringToCharPtr(Datatype->message),
		.sound = ConvertFStringToCharPtr(Datatype->sound),
		.title = ConvertFStringToCharPtr(Datatype->title)
	};

	return ConvertedType;
}

TSharedPtr<const FPFPushNotificationsSendPushNotificationRequest> ConvertSendPushNotificationRequestToUnreal(const PFPushNotificationsSendPushNotificationRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFPushNotificationsSendPushNotificationRequest> ConvertedType = MakeShared<FPFPushNotificationsSendPushNotificationRequest>(FPFPushNotificationsSendPushNotificationRequest{
		.advancedPlatformDelivery = ConvertPlayfabArrayToUnreal(Datatype->advancedPlatformDelivery, Datatype->advancedPlatformDeliveryCount, ConvertAdvancedPushPlatformMsgToUnreal),
		.advancedPlatformDeliveryCount = Datatype->advancedPlatformDeliveryCount,
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.message = Datatype->message == nullptr ? FString() : FString(Datatype->message),
		.package = ConvertPushNotificationPackageToUnreal(Datatype->package),
		.recipient = Datatype->recipient == nullptr ? FString() : FString(Datatype->recipient),
		.subject = Datatype->subject == nullptr ? FString() : FString(Datatype->subject),
		.targetPlatforms = ConvertPlayfabEnumArrayToUnreal(Datatype->targetPlatforms, Datatype->targetPlatformsCount, ConvertPushNotificationPlatformToUnreal),
		.targetPlatformsCount = Datatype->targetPlatformsCount
	});

	return ConvertedType;
}

const PFPushNotificationsSendPushNotificationRequest* ConvertSendPushNotificationRequestToPlayfab(TSharedPtr<const FPFPushNotificationsSendPushNotificationRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFPushNotificationsSendPushNotificationRequest* ConvertedType = new PFPushNotificationsSendPushNotificationRequest{
		.advancedPlatformDelivery = ConvertUnrealArrayToPlayfab(Datatype->advancedPlatformDelivery, ConvertAdvancedPushPlatformMsgToPlayfab),
		.advancedPlatformDeliveryCount = (uint32_t)Datatype->advancedPlatformDelivery.Num(),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.message = ConvertFStringToCharPtr(Datatype->message),
		.package = ConvertPushNotificationPackageToPlayfab(Datatype->package),
		.recipient = ConvertFStringToCharPtr(Datatype->recipient),
		.subject = ConvertFStringToCharPtr(Datatype->subject),
		.targetPlatforms = ConvertUnrealEnumArrayToPlayfab(Datatype->targetPlatforms, ConvertPushNotificationPlatformToPlayfab),
		.targetPlatformsCount = (uint32_t)Datatype->targetPlatforms.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFPushNotificationsSendPushNotificationFromTemplateRequest> ConvertSendPushNotificationFromTemplateRequestToUnreal(const PFPushNotificationsSendPushNotificationFromTemplateRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFPushNotificationsSendPushNotificationFromTemplateRequest> ConvertedType = MakeShared<FPFPushNotificationsSendPushNotificationFromTemplateRequest>(FPFPushNotificationsSendPushNotificationFromTemplateRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.pushNotificationTemplateId = Datatype->pushNotificationTemplateId == nullptr ? FString() : FString(Datatype->pushNotificationTemplateId),
		.recipient = Datatype->recipient == nullptr ? FString() : FString(Datatype->recipient)
	});

	return ConvertedType;
}

const PFPushNotificationsSendPushNotificationFromTemplateRequest* ConvertSendPushNotificationFromTemplateRequestToPlayfab(TSharedPtr<const FPFPushNotificationsSendPushNotificationFromTemplateRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFPushNotificationsSendPushNotificationFromTemplateRequest* ConvertedType = new PFPushNotificationsSendPushNotificationFromTemplateRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.pushNotificationTemplateId = ConvertFStringToCharPtr(Datatype->pushNotificationTemplateId),
		.recipient = ConvertFStringToCharPtr(Datatype->recipient)
	};

	return ConvertedType;
}
