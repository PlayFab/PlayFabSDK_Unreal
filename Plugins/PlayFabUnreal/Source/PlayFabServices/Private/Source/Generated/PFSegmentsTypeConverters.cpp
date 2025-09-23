// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFSegmentsTypeConverters.h"

const FPFSegmentsChurnRiskLevel ConvertChurnRiskLevelToUnreal(const PFSegmentsChurnRiskLevel* enumVal)
{
	if (enumVal == nullptr) {
		return FPFSegmentsChurnRiskLevel::NoData;
	}

	switch(*enumVal)
	{
	case PFSegmentsChurnRiskLevel::NoData: return FPFSegmentsChurnRiskLevel::NoData;
	case PFSegmentsChurnRiskLevel::LowRisk: return FPFSegmentsChurnRiskLevel::LowRisk;
	case PFSegmentsChurnRiskLevel::MediumRisk: return FPFSegmentsChurnRiskLevel::MediumRisk;
	case PFSegmentsChurnRiskLevel::HighRisk: return FPFSegmentsChurnRiskLevel::HighRisk;
	default:
	return FPFSegmentsChurnRiskLevel::NoData;
	}
}

const PFSegmentsChurnRiskLevel ConvertChurnRiskLevelToPlayfab(TSharedPtr<const FPFSegmentsChurnRiskLevel> enumVal)
{
	if (!enumVal.IsValid()) {
		return PFSegmentsChurnRiskLevel::NoData;
	}

	switch(*enumVal)
	{
	case FPFSegmentsChurnRiskLevel::NoData: return PFSegmentsChurnRiskLevel::NoData;
	case FPFSegmentsChurnRiskLevel::LowRisk: return PFSegmentsChurnRiskLevel::LowRisk;
	case FPFSegmentsChurnRiskLevel::MediumRisk: return PFSegmentsChurnRiskLevel::MediumRisk;
	case FPFSegmentsChurnRiskLevel::HighRisk: return PFSegmentsChurnRiskLevel::HighRisk;
	default:
	return PFSegmentsChurnRiskLevel::NoData;
	}
}

TSharedPtr<const FPFSegmentsGetSegmentResult> ConvertGetSegmentResultToUnreal(const PFSegmentsGetSegmentResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFSegmentsGetSegmentResult> ConvertedType = MakeShared<FPFSegmentsGetSegmentResult>(FPFSegmentsGetSegmentResult{
		.aBTestParent = Datatype->aBTestParent == nullptr ? FString() : FString(Datatype->aBTestParent),
		.id = Datatype->id == nullptr ? FString() : FString(Datatype->id),
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name)
	});

	return ConvertedType;
}

const PFSegmentsGetSegmentResult* ConvertGetSegmentResultToPlayfab(TSharedPtr<const FPFSegmentsGetSegmentResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFSegmentsGetSegmentResult* ConvertedType = new PFSegmentsGetSegmentResult{
		.aBTestParent = ConvertFStringToCharPtr(Datatype->aBTestParent),
		.id = ConvertFStringToCharPtr(Datatype->id),
		.name = ConvertFStringToCharPtr(Datatype->name)
	};

	return ConvertedType;
}

TSharedPtr<const FPFSegmentsGetPlayerSegmentsResult> ConvertGetPlayerSegmentsResultToUnreal(const PFSegmentsGetPlayerSegmentsResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFSegmentsGetPlayerSegmentsResult> ConvertedType = MakeShared<FPFSegmentsGetPlayerSegmentsResult>(FPFSegmentsGetPlayerSegmentsResult{
		.segments = ConvertPlayfabArrayToUnreal(Datatype->segments, Datatype->segmentsCount, ConvertGetSegmentResultToUnreal),
		.segmentsCount = Datatype->segmentsCount
	});

	return ConvertedType;
}

const PFSegmentsGetPlayerSegmentsResult* ConvertGetPlayerSegmentsResultToPlayfab(TSharedPtr<const FPFSegmentsGetPlayerSegmentsResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFSegmentsGetPlayerSegmentsResult* ConvertedType = new PFSegmentsGetPlayerSegmentsResult{
		.segments = ConvertUnrealArrayToPlayfab(Datatype->segments, ConvertGetSegmentResultToPlayfab),
		.segmentsCount = (uint32_t)Datatype->segments.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFSegmentsGetPlayerTagsRequest> ConvertGetPlayerTagsRequestToUnreal(const PFSegmentsGetPlayerTagsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFSegmentsGetPlayerTagsRequest> ConvertedType = MakeShared<FPFSegmentsGetPlayerTagsRequest>(FPFSegmentsGetPlayerTagsRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.playfabNamespace = Datatype->playfabNamespace == nullptr ? FString() : FString(Datatype->playfabNamespace),
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId)
	});

	return ConvertedType;
}

const PFSegmentsGetPlayerTagsRequest* ConvertGetPlayerTagsRequestToPlayfab(TSharedPtr<const FPFSegmentsGetPlayerTagsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFSegmentsGetPlayerTagsRequest* ConvertedType = new PFSegmentsGetPlayerTagsRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.playfabNamespace = ConvertFStringToCharPtr(Datatype->playfabNamespace),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFSegmentsGetPlayerTagsResult> ConvertGetPlayerTagsResultToUnreal(const PFSegmentsGetPlayerTagsResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFSegmentsGetPlayerTagsResult> ConvertedType = MakeShared<FPFSegmentsGetPlayerTagsResult>(FPFSegmentsGetPlayerTagsResult{
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId),
		.tags = ConvertCharArrayToUnreal(Datatype->tags, Datatype->tagsCount),
		.tagsCount = Datatype->tagsCount
	});

	return ConvertedType;
}

const PFSegmentsGetPlayerTagsResult* ConvertGetPlayerTagsResultToPlayfab(TSharedPtr<const FPFSegmentsGetPlayerTagsResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFSegmentsGetPlayerTagsResult* ConvertedType = new PFSegmentsGetPlayerTagsResult{
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId),
		.tags = ConvertFStringArrayToPlayfab(Datatype->tags),
		.tagsCount = (uint32_t)Datatype->tags.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFSegmentsAddPlayerTagRequest> ConvertAddPlayerTagRequestToUnreal(const PFSegmentsAddPlayerTagRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFSegmentsAddPlayerTagRequest> ConvertedType = MakeShared<FPFSegmentsAddPlayerTagRequest>(FPFSegmentsAddPlayerTagRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId),
		.tagName = Datatype->tagName == nullptr ? FString() : FString(Datatype->tagName)
	});

	return ConvertedType;
}

const PFSegmentsAddPlayerTagRequest* ConvertAddPlayerTagRequestToPlayfab(TSharedPtr<const FPFSegmentsAddPlayerTagRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFSegmentsAddPlayerTagRequest* ConvertedType = new PFSegmentsAddPlayerTagRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId),
		.tagName = ConvertFStringToCharPtr(Datatype->tagName)
	};

	return ConvertedType;
}

TSharedPtr<const FPFSegmentsGetAllSegmentsResult> ConvertGetAllSegmentsResultToUnreal(const PFSegmentsGetAllSegmentsResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFSegmentsGetAllSegmentsResult> ConvertedType = MakeShared<FPFSegmentsGetAllSegmentsResult>(FPFSegmentsGetAllSegmentsResult{
		.segments = ConvertPlayfabArrayToUnreal(Datatype->segments, Datatype->segmentsCount, ConvertGetSegmentResultToUnreal),
		.segmentsCount = Datatype->segmentsCount
	});

	return ConvertedType;
}

const PFSegmentsGetAllSegmentsResult* ConvertGetAllSegmentsResultToPlayfab(TSharedPtr<const FPFSegmentsGetAllSegmentsResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFSegmentsGetAllSegmentsResult* ConvertedType = new PFSegmentsGetAllSegmentsResult{
		.segments = ConvertUnrealArrayToPlayfab(Datatype->segments, ConvertGetSegmentResultToPlayfab),
		.segmentsCount = (uint32_t)Datatype->segments.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFSegmentsGetPlayersSegmentsRequest> ConvertGetPlayersSegmentsRequestToUnreal(const PFSegmentsGetPlayersSegmentsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFSegmentsGetPlayersSegmentsRequest> ConvertedType = MakeShared<FPFSegmentsGetPlayersSegmentsRequest>(FPFSegmentsGetPlayersSegmentsRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId)
	});

	return ConvertedType;
}

const PFSegmentsGetPlayersSegmentsRequest* ConvertGetPlayersSegmentsRequestToPlayfab(TSharedPtr<const FPFSegmentsGetPlayersSegmentsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFSegmentsGetPlayersSegmentsRequest* ConvertedType = new PFSegmentsGetPlayersSegmentsRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFSegmentsGetPlayersInSegmentRequest> ConvertGetPlayersInSegmentRequestToUnreal(const PFSegmentsGetPlayersInSegmentRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFSegmentsGetPlayersInSegmentRequest> ConvertedType = MakeShared<FPFSegmentsGetPlayersInSegmentRequest>(FPFSegmentsGetPlayersInSegmentRequest{
		.continuationToken = Datatype->continuationToken == nullptr ? FString() : FString(Datatype->continuationToken),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.getProfilesAsync = TSharedPtr<const bool>(Datatype->getProfilesAsync),
		.maxBatchSize = TSharedPtr<const uint32>(Datatype->maxBatchSize),
		.secondsToLive = TSharedPtr<const uint32>(Datatype->secondsToLive),
		.segmentId = Datatype->segmentId == nullptr ? FString() : FString(Datatype->segmentId)
	});

	return ConvertedType;
}

const PFSegmentsGetPlayersInSegmentRequest* ConvertGetPlayersInSegmentRequestToPlayfab(TSharedPtr<const FPFSegmentsGetPlayersInSegmentRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFSegmentsGetPlayersInSegmentRequest* ConvertedType = new PFSegmentsGetPlayersInSegmentRequest{
		.continuationToken = ConvertFStringToCharPtr(Datatype->continuationToken),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.getProfilesAsync = Datatype->getProfilesAsync ? new bool(*Datatype->getProfilesAsync) : nullptr,
		.maxBatchSize = Datatype->maxBatchSize ? new uint32(*Datatype->maxBatchSize) : nullptr,
		.secondsToLive = Datatype->secondsToLive ? new uint32(*Datatype->secondsToLive) : nullptr,
		.segmentId = ConvertFStringToCharPtr(Datatype->segmentId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFSegmentsAdCampaignAttribution> ConvertAdCampaignAttributionToUnreal(const PFSegmentsAdCampaignAttribution* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFSegmentsAdCampaignAttribution> ConvertedType = MakeShared<FPFSegmentsAdCampaignAttribution>(FPFSegmentsAdCampaignAttribution{
		.attributedAt = FDateTime::FromUnixTimestamp((int64)Datatype->attributedAt),
		.campaignId = Datatype->campaignId == nullptr ? FString() : FString(Datatype->campaignId),
		.platform = Datatype->platform == nullptr ? FString() : FString(Datatype->platform)
	});

	return ConvertedType;
}

const PFSegmentsAdCampaignAttribution* ConvertAdCampaignAttributionToPlayfab(TSharedPtr<const FPFSegmentsAdCampaignAttribution> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFSegmentsAdCampaignAttribution* ConvertedType = new PFSegmentsAdCampaignAttribution{
		.attributedAt = Datatype->attributedAt.ToUnixTimestamp(),
		.campaignId = ConvertFStringToCharPtr(Datatype->campaignId),
		.platform = ConvertFStringToCharPtr(Datatype->platform)
	};

	return ConvertedType;
}

TSharedPtr<const FPFSegmentsContactEmailInfo> ConvertContactEmailInfoToUnreal(const PFSegmentsContactEmailInfo* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFSegmentsContactEmailInfo> ConvertedType = MakeShared<FPFSegmentsContactEmailInfo>(FPFSegmentsContactEmailInfo{
		.emailAddress = Datatype->emailAddress == nullptr ? FString() : FString(Datatype->emailAddress),
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name),
		.verificationStatus = MakeShared<FPFEmailVerificationStatus>(ConvertEmailVerificationStatusToUnreal(Datatype->verificationStatus))
	});

	return ConvertedType;
}

const PFSegmentsContactEmailInfo* ConvertContactEmailInfoToPlayfab(TSharedPtr<const FPFSegmentsContactEmailInfo> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFSegmentsContactEmailInfo* ConvertedType = new PFSegmentsContactEmailInfo{
		.emailAddress = ConvertFStringToCharPtr(Datatype->emailAddress),
		.name = ConvertFStringToCharPtr(Datatype->name),
		.verificationStatus = new PFEmailVerificationStatus(ConvertEmailVerificationStatusToPlayfab(Datatype->verificationStatus))
	};

	return ConvertedType;
}

TSharedPtr<const FPFSegmentsPlayerLinkedAccount> ConvertPlayerLinkedAccountToUnreal(const PFSegmentsPlayerLinkedAccount* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFSegmentsPlayerLinkedAccount> ConvertedType = MakeShared<FPFSegmentsPlayerLinkedAccount>(FPFSegmentsPlayerLinkedAccount{
		.email = Datatype->email == nullptr ? FString() : FString(Datatype->email),
		.platform = MakeShared<FPFLoginIdentityProvider>(ConvertLoginIdentityProviderToUnreal(Datatype->platform)),
		.platformUserId = Datatype->platformUserId == nullptr ? FString() : FString(Datatype->platformUserId),
		.username = Datatype->username == nullptr ? FString() : FString(Datatype->username)
	});

	return ConvertedType;
}

const PFSegmentsPlayerLinkedAccount* ConvertPlayerLinkedAccountToPlayfab(TSharedPtr<const FPFSegmentsPlayerLinkedAccount> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFSegmentsPlayerLinkedAccount* ConvertedType = new PFSegmentsPlayerLinkedAccount{
		.email = ConvertFStringToCharPtr(Datatype->email),
		.platform = new PFLoginIdentityProvider(ConvertLoginIdentityProviderToPlayfab(Datatype->platform)),
		.platformUserId = ConvertFStringToCharPtr(Datatype->platformUserId),
		.username = ConvertFStringToCharPtr(Datatype->username)
	};

	return ConvertedType;
}

TSharedPtr<const FPFSegmentsPlayerLocation> ConvertPlayerLocationToUnreal(const PFSegmentsPlayerLocation* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFSegmentsPlayerLocation> ConvertedType = MakeShared<FPFSegmentsPlayerLocation>(FPFSegmentsPlayerLocation{
		.city = Datatype->city == nullptr ? FString() : FString(Datatype->city),
		.continentCode = ConvertContinentCodeToUnreal(&Datatype->continentCode),
		.countryCode = ConvertCountryCodeToUnreal(&Datatype->countryCode),
		.latitude = TSharedPtr<const double>(Datatype->latitude),
		.longitude = TSharedPtr<const double>(Datatype->longitude)
	});

	return ConvertedType;
}

const PFSegmentsPlayerLocation* ConvertPlayerLocationToPlayfab(TSharedPtr<const FPFSegmentsPlayerLocation> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFSegmentsPlayerLocation* ConvertedType = new PFSegmentsPlayerLocation{
		.city = ConvertFStringToCharPtr(Datatype->city),
		.continentCode = ConvertContinentCodeToPlayfab(MakeShared<FPFContinentCode>(Datatype->continentCode)),
		.countryCode = ConvertCountryCodeToPlayfab(MakeShared<FPFCountryCode>(Datatype->countryCode)),
		.latitude = Datatype->latitude ? new double(*Datatype->latitude) : nullptr,
		.longitude = Datatype->longitude ? new double(*Datatype->longitude) : nullptr
	};

	return ConvertedType;
}

TSharedPtr<const FPFSegmentsPlayerStatistic> ConvertPlayerStatisticToUnreal(const PFSegmentsPlayerStatistic* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFSegmentsPlayerStatistic> ConvertedType = MakeShared<FPFSegmentsPlayerStatistic>(FPFSegmentsPlayerStatistic{
		.id = Datatype->id == nullptr ? FString() : FString(Datatype->id),
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name),
		.statisticValue = Datatype->statisticValue,
		.statisticVersion = Datatype->statisticVersion
	});

	return ConvertedType;
}

const PFSegmentsPlayerStatistic* ConvertPlayerStatisticToPlayfab(TSharedPtr<const FPFSegmentsPlayerStatistic> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFSegmentsPlayerStatistic* ConvertedType = new PFSegmentsPlayerStatistic{
		.id = ConvertFStringToCharPtr(Datatype->id),
		.name = ConvertFStringToCharPtr(Datatype->name),
		.statisticValue = Datatype->statisticValue,
		.statisticVersion = Datatype->statisticVersion
	};

	return ConvertedType;
}

TSharedPtr<const FPFSegmentsPushNotificationRegistration> ConvertPushNotificationRegistrationToUnreal(const PFSegmentsPushNotificationRegistration* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFSegmentsPushNotificationRegistration> ConvertedType = MakeShared<FPFSegmentsPushNotificationRegistration>(FPFSegmentsPushNotificationRegistration{
		.notificationEndpointARN = Datatype->notificationEndpointARN == nullptr ? FString() : FString(Datatype->notificationEndpointARN),
		.platform = MakeShared<FPFPushNotificationPlatform>(ConvertPushNotificationPlatformToUnreal(Datatype->platform))
	});

	return ConvertedType;
}

const PFSegmentsPushNotificationRegistration* ConvertPushNotificationRegistrationToPlayfab(TSharedPtr<const FPFSegmentsPushNotificationRegistration> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFSegmentsPushNotificationRegistration* ConvertedType = new PFSegmentsPushNotificationRegistration{
		.notificationEndpointARN = ConvertFStringToCharPtr(Datatype->notificationEndpointARN),
		.platform = new PFPushNotificationPlatform(ConvertPushNotificationPlatformToPlayfab(Datatype->platform))
	};

	return ConvertedType;
}

TSharedPtr<const FPFSegmentsPlayerProfile> ConvertPlayerProfileToUnreal(const PFSegmentsPlayerProfile* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFSegmentsPlayerProfile> ConvertedType = MakeShared<FPFSegmentsPlayerProfile>(FPFSegmentsPlayerProfile{
		.adCampaignAttributions = ConvertPlayfabArrayToUnreal(Datatype->adCampaignAttributions, Datatype->adCampaignAttributionsCount, ConvertAdCampaignAttributionToUnreal),
		.adCampaignAttributionsCount = Datatype->adCampaignAttributionsCount,
		.avatarUrl = Datatype->avatarUrl == nullptr ? FString() : FString(Datatype->avatarUrl),
		.bannedUntil = ConvertTimeToUnreal(Datatype->bannedUntil),
		.churnPrediction = MakeShared<FPFSegmentsChurnRiskLevel>(ConvertChurnRiskLevelToUnreal(Datatype->churnPrediction)),
		.contactEmailAddresses = ConvertPlayfabArrayToUnreal(Datatype->contactEmailAddresses, Datatype->contactEmailAddressesCount, ConvertContactEmailInfoToUnreal),
		.contactEmailAddressesCount = Datatype->contactEmailAddressesCount,
		.created = ConvertTimeToUnreal(Datatype->created),
		.customProperties = FPFJsonObject{ .stringValue = FString(Datatype->customProperties.stringValue) },
		.displayName = Datatype->displayName == nullptr ? FString() : FString(Datatype->displayName),
		.lastLogin = ConvertTimeToUnreal(Datatype->lastLogin),
		.linkedAccounts = ConvertPlayfabArrayToUnreal(Datatype->linkedAccounts, Datatype->linkedAccountsCount, ConvertPlayerLinkedAccountToUnreal),
		.linkedAccountsCount = Datatype->linkedAccountsCount,
		.locations = ConvertPlayfabMapToUnreal<PFSegmentsPlayerLocationDictionaryEntry, FPFSegmentsPlayerLocation, PFSegmentsPlayerLocation>(Datatype->locations, Datatype->locationsCount, ConvertPlayerLocationToUnreal),
		.locationsCount = Datatype->locationsCount,
		.origination = MakeShared<FPFLoginIdentityProvider>(ConvertLoginIdentityProviderToUnreal(Datatype->origination)),
		.playerExperimentVariants = ConvertCharArrayToUnreal(Datatype->playerExperimentVariants, Datatype->playerExperimentVariantsCount),
		.playerExperimentVariantsCount = Datatype->playerExperimentVariantsCount,
		.playerId = Datatype->playerId == nullptr ? FString() : FString(Datatype->playerId),
		.playerStatistics = ConvertPlayfabArrayToUnreal(Datatype->playerStatistics, Datatype->playerStatisticsCount, ConvertPlayerStatisticToUnreal),
		.playerStatisticsCount = Datatype->playerStatisticsCount,
		.publisherId = Datatype->publisherId == nullptr ? FString() : FString(Datatype->publisherId),
		.pushNotificationRegistrations = ConvertPlayfabArrayToUnreal(Datatype->pushNotificationRegistrations, Datatype->pushNotificationRegistrationsCount, ConvertPushNotificationRegistrationToUnreal),
		.pushNotificationRegistrationsCount = Datatype->pushNotificationRegistrationsCount,
		.statistics = ConvertIntMapToUnreal(Datatype->statistics, Datatype->statisticsCount),
		.statisticsCount = Datatype->statisticsCount,
		.tags = ConvertCharArrayToUnreal(Datatype->tags, Datatype->tagsCount),
		.tagsCount = Datatype->tagsCount,
		.titleId = Datatype->titleId == nullptr ? FString() : FString(Datatype->titleId),
		.totalValueToDateInUSD = TSharedPtr<const uint32>(Datatype->totalValueToDateInUSD),
		.valuesToDate = ConvertUintMapToUnreal(Datatype->valuesToDate, Datatype->valuesToDateCount),
		.valuesToDateCount = Datatype->valuesToDateCount,
		.virtualCurrencyBalances = ConvertIntMapToUnreal(Datatype->virtualCurrencyBalances, Datatype->virtualCurrencyBalancesCount),
		.virtualCurrencyBalancesCount = Datatype->virtualCurrencyBalancesCount
	});

	return ConvertedType;
}

const PFSegmentsPlayerProfile* ConvertPlayerProfileToPlayfab(TSharedPtr<const FPFSegmentsPlayerProfile> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFSegmentsPlayerProfile* ConvertedType = new PFSegmentsPlayerProfile{
		.adCampaignAttributions = ConvertUnrealArrayToPlayfab(Datatype->adCampaignAttributions, ConvertAdCampaignAttributionToPlayfab),
		.adCampaignAttributionsCount = (uint32_t)Datatype->adCampaignAttributions.Num(),
		.avatarUrl = ConvertFStringToCharPtr(Datatype->avatarUrl),
		.bannedUntil = ConvertFDateTimeToPlayfab(Datatype->bannedUntil),
		.churnPrediction = new PFSegmentsChurnRiskLevel(ConvertChurnRiskLevelToPlayfab(Datatype->churnPrediction)),
		.contactEmailAddresses = ConvertUnrealArrayToPlayfab(Datatype->contactEmailAddresses, ConvertContactEmailInfoToPlayfab),
		.contactEmailAddressesCount = (uint32_t)Datatype->contactEmailAddresses.Num(),
		.created = ConvertFDateTimeToPlayfab(Datatype->created),
		.customProperties = PFJsonObject{ .stringValue = ConvertFStringToCharPtr(Datatype->customProperties.stringValue) },
		.displayName = ConvertFStringToCharPtr(Datatype->displayName),
		.lastLogin = ConvertFDateTimeToPlayfab(Datatype->lastLogin),
		.linkedAccounts = ConvertUnrealArrayToPlayfab(Datatype->linkedAccounts, ConvertPlayerLinkedAccountToPlayfab),
		.linkedAccountsCount = (uint32_t)Datatype->linkedAccounts.Num(),
		.locations = ConvertUnrealMapToPlayfab<PFSegmentsPlayerLocationDictionaryEntry, FPFSegmentsPlayerLocation, PFSegmentsPlayerLocation>(Datatype->locations, ConvertPlayerLocationToPlayfab),
		.locationsCount = (uint32_t)Datatype->locations.Num(),
		.origination = new PFLoginIdentityProvider(ConvertLoginIdentityProviderToPlayfab(Datatype->origination)),
		.playerExperimentVariants = ConvertFStringArrayToPlayfab(Datatype->playerExperimentVariants),
		.playerExperimentVariantsCount = (uint32_t)Datatype->playerExperimentVariants.Num(),
		.playerId = ConvertFStringToCharPtr(Datatype->playerId),
		.playerStatistics = ConvertUnrealArrayToPlayfab(Datatype->playerStatistics, ConvertPlayerStatisticToPlayfab),
		.playerStatisticsCount = (uint32_t)Datatype->playerStatistics.Num(),
		.publisherId = ConvertFStringToCharPtr(Datatype->publisherId),
		.pushNotificationRegistrations = ConvertUnrealArrayToPlayfab(Datatype->pushNotificationRegistrations, ConvertPushNotificationRegistrationToPlayfab),
		.pushNotificationRegistrationsCount = (uint32_t)Datatype->pushNotificationRegistrations.Num(),
		.statistics = ConvertIntMapToPlayfab(Datatype->statistics),
		.statisticsCount = (uint32_t)Datatype->statistics.Num(),
		.tags = ConvertFStringArrayToPlayfab(Datatype->tags),
		.tagsCount = (uint32_t)Datatype->tags.Num(),
		.titleId = ConvertFStringToCharPtr(Datatype->titleId),
		.totalValueToDateInUSD = Datatype->totalValueToDateInUSD ? new uint32(*Datatype->totalValueToDateInUSD) : nullptr,
		.valuesToDate = ConvertUintMapToPlayfab(Datatype->valuesToDate),
		.valuesToDateCount = (uint32_t)Datatype->valuesToDate.Num(),
		.virtualCurrencyBalances = ConvertIntMapToPlayfab(Datatype->virtualCurrencyBalances),
		.virtualCurrencyBalancesCount = (uint32_t)Datatype->virtualCurrencyBalances.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFSegmentsGetPlayersInSegmentResult> ConvertGetPlayersInSegmentResultToUnreal(const PFSegmentsGetPlayersInSegmentResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFSegmentsGetPlayersInSegmentResult> ConvertedType = MakeShared<FPFSegmentsGetPlayersInSegmentResult>(FPFSegmentsGetPlayersInSegmentResult{
		.continuationToken = Datatype->continuationToken == nullptr ? FString() : FString(Datatype->continuationToken),
		.playerProfiles = ConvertPlayfabArrayToUnreal(Datatype->playerProfiles, Datatype->playerProfilesCount, ConvertPlayerProfileToUnreal),
		.playerProfilesCount = Datatype->playerProfilesCount,
		.profilesInSegment = Datatype->profilesInSegment
	});

	return ConvertedType;
}

const PFSegmentsGetPlayersInSegmentResult* ConvertGetPlayersInSegmentResultToPlayfab(TSharedPtr<const FPFSegmentsGetPlayersInSegmentResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFSegmentsGetPlayersInSegmentResult* ConvertedType = new PFSegmentsGetPlayersInSegmentResult{
		.continuationToken = ConvertFStringToCharPtr(Datatype->continuationToken),
		.playerProfiles = ConvertUnrealArrayToPlayfab(Datatype->playerProfiles, ConvertPlayerProfileToPlayfab),
		.playerProfilesCount = (uint32_t)Datatype->playerProfiles.Num(),
		.profilesInSegment = Datatype->profilesInSegment
	};

	return ConvertedType;
}

TSharedPtr<const FPFSegmentsRemovePlayerTagRequest> ConvertRemovePlayerTagRequestToUnreal(const PFSegmentsRemovePlayerTagRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFSegmentsRemovePlayerTagRequest> ConvertedType = MakeShared<FPFSegmentsRemovePlayerTagRequest>(FPFSegmentsRemovePlayerTagRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId),
		.tagName = Datatype->tagName == nullptr ? FString() : FString(Datatype->tagName)
	});

	return ConvertedType;
}

const PFSegmentsRemovePlayerTagRequest* ConvertRemovePlayerTagRequestToPlayfab(TSharedPtr<const FPFSegmentsRemovePlayerTagRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFSegmentsRemovePlayerTagRequest* ConvertedType = new PFSegmentsRemovePlayerTagRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId),
		.tagName = ConvertFStringToCharPtr(Datatype->tagName)
	};

	return ConvertedType;
}
