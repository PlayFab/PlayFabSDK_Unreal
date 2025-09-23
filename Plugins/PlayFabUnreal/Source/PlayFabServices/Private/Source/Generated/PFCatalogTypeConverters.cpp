// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFCatalogTypeConverters.h"

const FPFCatalogModerationStatus ConvertModerationStatusToUnreal(const PFCatalogModerationStatus* enumVal)
{
	if (enumVal == nullptr) {
		return FPFCatalogModerationStatus::Unknown;
	}

	switch(*enumVal)
	{
	case PFCatalogModerationStatus::Unknown: return FPFCatalogModerationStatus::Unknown;
	case PFCatalogModerationStatus::AwaitingModeration: return FPFCatalogModerationStatus::AwaitingModeration;
	case PFCatalogModerationStatus::Approved: return FPFCatalogModerationStatus::Approved;
	case PFCatalogModerationStatus::Rejected: return FPFCatalogModerationStatus::Rejected;
	default:
	return FPFCatalogModerationStatus::Unknown;
	}
}

const PFCatalogModerationStatus ConvertModerationStatusToPlayfab(TSharedPtr<const FPFCatalogModerationStatus> enumVal)
{
	if (!enumVal.IsValid()) {
		return PFCatalogModerationStatus::Unknown;
	}

	switch(*enumVal)
	{
	case FPFCatalogModerationStatus::Unknown: return PFCatalogModerationStatus::Unknown;
	case FPFCatalogModerationStatus::AwaitingModeration: return PFCatalogModerationStatus::AwaitingModeration;
	case FPFCatalogModerationStatus::Approved: return PFCatalogModerationStatus::Approved;
	case FPFCatalogModerationStatus::Rejected: return PFCatalogModerationStatus::Rejected;
	default:
	return PFCatalogModerationStatus::Unknown;
	}
}

const FPFCatalogDisplayPropertyType ConvertDisplayPropertyTypeToUnreal(const PFCatalogDisplayPropertyType* enumVal)
{
	if (enumVal == nullptr) {
		return FPFCatalogDisplayPropertyType::None;
	}

	switch(*enumVal)
	{
	case PFCatalogDisplayPropertyType::None: return FPFCatalogDisplayPropertyType::None;
	case PFCatalogDisplayPropertyType::QueryDateTime: return FPFCatalogDisplayPropertyType::QueryDateTime;
	case PFCatalogDisplayPropertyType::QueryDouble: return FPFCatalogDisplayPropertyType::QueryDouble;
	case PFCatalogDisplayPropertyType::QueryString: return FPFCatalogDisplayPropertyType::QueryString;
	case PFCatalogDisplayPropertyType::SearchString: return FPFCatalogDisplayPropertyType::SearchString;
	default:
	return FPFCatalogDisplayPropertyType::None;
	}
}

const PFCatalogDisplayPropertyType ConvertDisplayPropertyTypeToPlayfab(TSharedPtr<const FPFCatalogDisplayPropertyType> enumVal)
{
	if (!enumVal.IsValid()) {
		return PFCatalogDisplayPropertyType::None;
	}

	switch(*enumVal)
	{
	case FPFCatalogDisplayPropertyType::None: return PFCatalogDisplayPropertyType::None;
	case FPFCatalogDisplayPropertyType::QueryDateTime: return PFCatalogDisplayPropertyType::QueryDateTime;
	case FPFCatalogDisplayPropertyType::QueryDouble: return PFCatalogDisplayPropertyType::QueryDouble;
	case FPFCatalogDisplayPropertyType::QueryString: return PFCatalogDisplayPropertyType::QueryString;
	case FPFCatalogDisplayPropertyType::SearchString: return PFCatalogDisplayPropertyType::SearchString;
	default:
	return PFCatalogDisplayPropertyType::None;
	}
}

const FPFCatalogPublishResult ConvertPublishResultToUnreal(const PFCatalogPublishResult* enumVal)
{
	if (enumVal == nullptr) {
		return FPFCatalogPublishResult::Unknown;
	}

	switch(*enumVal)
	{
	case PFCatalogPublishResult::Unknown: return FPFCatalogPublishResult::Unknown;
	case PFCatalogPublishResult::Pending: return FPFCatalogPublishResult::Pending;
	case PFCatalogPublishResult::Succeeded: return FPFCatalogPublishResult::Succeeded;
	case PFCatalogPublishResult::Failed: return FPFCatalogPublishResult::Failed;
	case PFCatalogPublishResult::Canceled: return FPFCatalogPublishResult::Canceled;
	default:
	return FPFCatalogPublishResult::Unknown;
	}
}

const PFCatalogPublishResult ConvertPublishResultToPlayfab(TSharedPtr<const FPFCatalogPublishResult> enumVal)
{
	if (!enumVal.IsValid()) {
		return PFCatalogPublishResult::Unknown;
	}

	switch(*enumVal)
	{
	case FPFCatalogPublishResult::Unknown: return PFCatalogPublishResult::Unknown;
	case FPFCatalogPublishResult::Pending: return PFCatalogPublishResult::Pending;
	case FPFCatalogPublishResult::Succeeded: return PFCatalogPublishResult::Succeeded;
	case FPFCatalogPublishResult::Failed: return PFCatalogPublishResult::Failed;
	case FPFCatalogPublishResult::Canceled: return PFCatalogPublishResult::Canceled;
	default:
	return PFCatalogPublishResult::Unknown;
	}
}

const FPFCatalogConcernCategory ConvertConcernCategoryToUnreal(const PFCatalogConcernCategory* enumVal)
{
	if (enumVal == nullptr) {
		return FPFCatalogConcernCategory::None;
	}

	switch(*enumVal)
	{
	case PFCatalogConcernCategory::None: return FPFCatalogConcernCategory::None;
	case PFCatalogConcernCategory::OffensiveContent: return FPFCatalogConcernCategory::OffensiveContent;
	case PFCatalogConcernCategory::ChildExploitation: return FPFCatalogConcernCategory::ChildExploitation;
	case PFCatalogConcernCategory::MalwareOrVirus: return FPFCatalogConcernCategory::MalwareOrVirus;
	case PFCatalogConcernCategory::PrivacyConcerns: return FPFCatalogConcernCategory::PrivacyConcerns;
	case PFCatalogConcernCategory::MisleadingApp: return FPFCatalogConcernCategory::MisleadingApp;
	case PFCatalogConcernCategory::PoorPerformance: return FPFCatalogConcernCategory::PoorPerformance;
	case PFCatalogConcernCategory::ReviewResponse: return FPFCatalogConcernCategory::ReviewResponse;
	case PFCatalogConcernCategory::SpamAdvertising: return FPFCatalogConcernCategory::SpamAdvertising;
	case PFCatalogConcernCategory::Profanity: return FPFCatalogConcernCategory::Profanity;
	default:
	return FPFCatalogConcernCategory::None;
	}
}

const PFCatalogConcernCategory ConvertConcernCategoryToPlayfab(TSharedPtr<const FPFCatalogConcernCategory> enumVal)
{
	if (!enumVal.IsValid()) {
		return PFCatalogConcernCategory::None;
	}

	switch(*enumVal)
	{
	case FPFCatalogConcernCategory::None: return PFCatalogConcernCategory::None;
	case FPFCatalogConcernCategory::OffensiveContent: return PFCatalogConcernCategory::OffensiveContent;
	case FPFCatalogConcernCategory::ChildExploitation: return PFCatalogConcernCategory::ChildExploitation;
	case FPFCatalogConcernCategory::MalwareOrVirus: return PFCatalogConcernCategory::MalwareOrVirus;
	case FPFCatalogConcernCategory::PrivacyConcerns: return PFCatalogConcernCategory::PrivacyConcerns;
	case FPFCatalogConcernCategory::MisleadingApp: return PFCatalogConcernCategory::MisleadingApp;
	case FPFCatalogConcernCategory::PoorPerformance: return PFCatalogConcernCategory::PoorPerformance;
	case FPFCatalogConcernCategory::ReviewResponse: return PFCatalogConcernCategory::ReviewResponse;
	case FPFCatalogConcernCategory::SpamAdvertising: return PFCatalogConcernCategory::SpamAdvertising;
	case FPFCatalogConcernCategory::Profanity: return PFCatalogConcernCategory::Profanity;
	default:
	return PFCatalogConcernCategory::None;
	}
}

const FPFCatalogHelpfulnessVote ConvertHelpfulnessVoteToUnreal(const PFCatalogHelpfulnessVote* enumVal)
{
	if (enumVal == nullptr) {
		return FPFCatalogHelpfulnessVote::None;
	}

	switch(*enumVal)
	{
	case PFCatalogHelpfulnessVote::None: return FPFCatalogHelpfulnessVote::None;
	case PFCatalogHelpfulnessVote::UnHelpful: return FPFCatalogHelpfulnessVote::UnHelpful;
	case PFCatalogHelpfulnessVote::Helpful: return FPFCatalogHelpfulnessVote::Helpful;
	default:
	return FPFCatalogHelpfulnessVote::None;
	}
}

const PFCatalogHelpfulnessVote ConvertHelpfulnessVoteToPlayfab(TSharedPtr<const FPFCatalogHelpfulnessVote> enumVal)
{
	if (!enumVal.IsValid()) {
		return PFCatalogHelpfulnessVote::None;
	}

	switch(*enumVal)
	{
	case FPFCatalogHelpfulnessVote::None: return PFCatalogHelpfulnessVote::None;
	case FPFCatalogHelpfulnessVote::UnHelpful: return PFCatalogHelpfulnessVote::UnHelpful;
	case FPFCatalogHelpfulnessVote::Helpful: return PFCatalogHelpfulnessVote::Helpful;
	default:
	return PFCatalogHelpfulnessVote::None;
	}
}

TSharedPtr<const FPFCatalogCatalogAlternateId> ConvertCatalogAlternateIdToUnreal(const PFCatalogCatalogAlternateId* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogCatalogAlternateId> ConvertedType = MakeShared<FPFCatalogCatalogAlternateId>(FPFCatalogCatalogAlternateId{
		.type = Datatype->type == nullptr ? FString() : FString(Datatype->type),
		.value = Datatype->value == nullptr ? FString() : FString(Datatype->value)
	});

	return ConvertedType;
}

const PFCatalogCatalogAlternateId* ConvertCatalogAlternateIdToPlayfab(TSharedPtr<const FPFCatalogCatalogAlternateId> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogCatalogAlternateId* ConvertedType = new PFCatalogCatalogAlternateId{
		.type = ConvertFStringToCharPtr(Datatype->type),
		.value = ConvertFStringToCharPtr(Datatype->value)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogContent> ConvertContentToUnreal(const PFCatalogContent* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogContent> ConvertedType = MakeShared<FPFCatalogContent>(FPFCatalogContent{
		.id = Datatype->id == nullptr ? FString() : FString(Datatype->id),
		.maxClientVersion = Datatype->maxClientVersion == nullptr ? FString() : FString(Datatype->maxClientVersion),
		.minClientVersion = Datatype->minClientVersion == nullptr ? FString() : FString(Datatype->minClientVersion),
		.tags = ConvertCharArrayToUnreal(Datatype->tags, Datatype->tagsCount),
		.tagsCount = Datatype->tagsCount,
		.type = Datatype->type == nullptr ? FString() : FString(Datatype->type),
		.url = Datatype->url == nullptr ? FString() : FString(Datatype->url)
	});

	return ConvertedType;
}

const PFCatalogContent* ConvertContentToPlayfab(TSharedPtr<const FPFCatalogContent> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogContent* ConvertedType = new PFCatalogContent{
		.id = ConvertFStringToCharPtr(Datatype->id),
		.maxClientVersion = ConvertFStringToCharPtr(Datatype->maxClientVersion),
		.minClientVersion = ConvertFStringToCharPtr(Datatype->minClientVersion),
		.tags = ConvertFStringArrayToPlayfab(Datatype->tags),
		.tagsCount = (uint32_t)Datatype->tags.Num(),
		.type = ConvertFStringToCharPtr(Datatype->type),
		.url = ConvertFStringToCharPtr(Datatype->url)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogDeepLink> ConvertDeepLinkToUnreal(const PFCatalogDeepLink* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogDeepLink> ConvertedType = MakeShared<FPFCatalogDeepLink>(FPFCatalogDeepLink{
		.platform = Datatype->platform == nullptr ? FString() : FString(Datatype->platform),
		.url = Datatype->url == nullptr ? FString() : FString(Datatype->url)
	});

	return ConvertedType;
}

const PFCatalogDeepLink* ConvertDeepLinkToPlayfab(TSharedPtr<const FPFCatalogDeepLink> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogDeepLink* ConvertedType = new PFCatalogDeepLink{
		.platform = ConvertFStringToCharPtr(Datatype->platform),
		.url = ConvertFStringToCharPtr(Datatype->url)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogImage> ConvertImageToUnreal(const PFCatalogImage* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogImage> ConvertedType = MakeShared<FPFCatalogImage>(FPFCatalogImage{
		.id = Datatype->id == nullptr ? FString() : FString(Datatype->id),
		.tag = Datatype->tag == nullptr ? FString() : FString(Datatype->tag),
		.type = Datatype->type == nullptr ? FString() : FString(Datatype->type),
		.url = Datatype->url == nullptr ? FString() : FString(Datatype->url)
	});

	return ConvertedType;
}

const PFCatalogImage* ConvertImageToPlayfab(TSharedPtr<const FPFCatalogImage> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogImage* ConvertedType = new PFCatalogImage{
		.id = ConvertFStringToCharPtr(Datatype->id),
		.tag = ConvertFStringToCharPtr(Datatype->tag),
		.type = ConvertFStringToCharPtr(Datatype->type),
		.url = ConvertFStringToCharPtr(Datatype->url)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogCatalogPriceAmount> ConvertCatalogPriceAmountToUnreal(const PFCatalogCatalogPriceAmount* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogCatalogPriceAmount> ConvertedType = MakeShared<FPFCatalogCatalogPriceAmount>(FPFCatalogCatalogPriceAmount{
		.amount = Datatype->amount,
		.itemId = Datatype->itemId == nullptr ? FString() : FString(Datatype->itemId)
	});

	return ConvertedType;
}

const PFCatalogCatalogPriceAmount* ConvertCatalogPriceAmountToPlayfab(TSharedPtr<const FPFCatalogCatalogPriceAmount> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogCatalogPriceAmount* ConvertedType = new PFCatalogCatalogPriceAmount{
		.amount = Datatype->amount,
		.itemId = ConvertFStringToCharPtr(Datatype->itemId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogCatalogPrice> ConvertCatalogPriceToUnreal(const PFCatalogCatalogPrice* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogCatalogPrice> ConvertedType = MakeShared<FPFCatalogCatalogPrice>(FPFCatalogCatalogPrice{
		.amounts = ConvertPlayfabArrayToUnreal(Datatype->amounts, Datatype->amountsCount, ConvertCatalogPriceAmountToUnreal),
		.amountsCount = Datatype->amountsCount,
		.unitAmount = TSharedPtr<const int32>(Datatype->unitAmount),
		.unitDurationInSeconds = TSharedPtr<const double>(Datatype->unitDurationInSeconds)
	});

	return ConvertedType;
}

const PFCatalogCatalogPrice* ConvertCatalogPriceToPlayfab(TSharedPtr<const FPFCatalogCatalogPrice> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogCatalogPrice* ConvertedType = new PFCatalogCatalogPrice{
		.amounts = ConvertUnrealArrayToPlayfab(Datatype->amounts, ConvertCatalogPriceAmountToPlayfab),
		.amountsCount = (uint32_t)Datatype->amounts.Num(),
		.unitAmount = Datatype->unitAmount ? new int32(*Datatype->unitAmount) : nullptr,
		.unitDurationInSeconds = Datatype->unitDurationInSeconds ? new double(*Datatype->unitDurationInSeconds) : nullptr
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogCatalogPriceOptions> ConvertCatalogPriceOptionsToUnreal(const PFCatalogCatalogPriceOptions* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogCatalogPriceOptions> ConvertedType = MakeShared<FPFCatalogCatalogPriceOptions>(FPFCatalogCatalogPriceOptions{
		.prices = ConvertPlayfabArrayToUnreal(Datatype->prices, Datatype->pricesCount, ConvertCatalogPriceToUnreal),
		.pricesCount = Datatype->pricesCount
	});

	return ConvertedType;
}

const PFCatalogCatalogPriceOptions* ConvertCatalogPriceOptionsToPlayfab(TSharedPtr<const FPFCatalogCatalogPriceOptions> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogCatalogPriceOptions* ConvertedType = new PFCatalogCatalogPriceOptions{
		.prices = ConvertUnrealArrayToPlayfab(Datatype->prices, ConvertCatalogPriceToPlayfab),
		.pricesCount = (uint32_t)Datatype->prices.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogCatalogItemReference> ConvertCatalogItemReferenceToUnreal(const PFCatalogCatalogItemReference* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogCatalogItemReference> ConvertedType = MakeShared<FPFCatalogCatalogItemReference>(FPFCatalogCatalogItemReference{
		.amount = TSharedPtr<const int32>(Datatype->amount),
		.id = Datatype->id == nullptr ? FString() : FString(Datatype->id),
		.priceOptions = ConvertCatalogPriceOptionsToUnreal(Datatype->priceOptions)
	});

	return ConvertedType;
}

const PFCatalogCatalogItemReference* ConvertCatalogItemReferenceToPlayfab(TSharedPtr<const FPFCatalogCatalogItemReference> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogCatalogItemReference* ConvertedType = new PFCatalogCatalogItemReference{
		.amount = Datatype->amount ? new int32(*Datatype->amount) : nullptr,
		.id = ConvertFStringToCharPtr(Datatype->id),
		.priceOptions = ConvertCatalogPriceOptionsToPlayfab(Datatype->priceOptions)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogKeywordSet> ConvertKeywordSetToUnreal(const PFCatalogKeywordSet* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogKeywordSet> ConvertedType = MakeShared<FPFCatalogKeywordSet>(FPFCatalogKeywordSet{
		.values = ConvertCharArrayToUnreal(Datatype->values, Datatype->valuesCount),
		.valuesCount = Datatype->valuesCount
	});

	return ConvertedType;
}

const PFCatalogKeywordSet* ConvertKeywordSetToPlayfab(TSharedPtr<const FPFCatalogKeywordSet> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogKeywordSet* ConvertedType = new PFCatalogKeywordSet{
		.values = ConvertFStringArrayToPlayfab(Datatype->values),
		.valuesCount = (uint32_t)Datatype->values.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogModerationState> ConvertModerationStateToUnreal(const PFCatalogModerationState* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogModerationState> ConvertedType = MakeShared<FPFCatalogModerationState>(FPFCatalogModerationState{
		.lastModifiedDate = ConvertTimeToUnreal(Datatype->lastModifiedDate),
		.reason = Datatype->reason == nullptr ? FString() : FString(Datatype->reason),
		.status = MakeShared<FPFCatalogModerationStatus>(ConvertModerationStatusToUnreal(Datatype->status))
	});

	return ConvertedType;
}

const PFCatalogModerationState* ConvertModerationStateToPlayfab(TSharedPtr<const FPFCatalogModerationState> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogModerationState* ConvertedType = new PFCatalogModerationState{
		.lastModifiedDate = ConvertFDateTimeToPlayfab(Datatype->lastModifiedDate),
		.reason = ConvertFStringToCharPtr(Datatype->reason),
		.status = new PFCatalogModerationStatus(ConvertModerationStatusToPlayfab(Datatype->status))
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogRating> ConvertRatingToUnreal(const PFCatalogRating* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogRating> ConvertedType = MakeShared<FPFCatalogRating>(FPFCatalogRating{
		.average = TSharedPtr<const float>(Datatype->average),
		.count1Star = TSharedPtr<const int32>(Datatype->count1Star),
		.count2Star = TSharedPtr<const int32>(Datatype->count2Star),
		.count3Star = TSharedPtr<const int32>(Datatype->count3Star),
		.count4Star = TSharedPtr<const int32>(Datatype->count4Star),
		.count5Star = TSharedPtr<const int32>(Datatype->count5Star),
		.totalCount = TSharedPtr<const int32>(Datatype->totalCount)
	});

	return ConvertedType;
}

const PFCatalogRating* ConvertRatingToPlayfab(TSharedPtr<const FPFCatalogRating> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogRating* ConvertedType = new PFCatalogRating{
		.average = Datatype->average ? new float(*Datatype->average) : nullptr,
		.count1Star = Datatype->count1Star ? new int32(*Datatype->count1Star) : nullptr,
		.count2Star = Datatype->count2Star ? new int32(*Datatype->count2Star) : nullptr,
		.count3Star = Datatype->count3Star ? new int32(*Datatype->count3Star) : nullptr,
		.count4Star = Datatype->count4Star ? new int32(*Datatype->count4Star) : nullptr,
		.count5Star = Datatype->count5Star ? new int32(*Datatype->count5Star) : nullptr,
		.totalCount = Datatype->totalCount ? new int32(*Datatype->totalCount) : nullptr
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogRealMoneyPriceDetails> ConvertRealMoneyPriceDetailsToUnreal(const PFCatalogRealMoneyPriceDetails* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogRealMoneyPriceDetails> ConvertedType = MakeShared<FPFCatalogRealMoneyPriceDetails>(FPFCatalogRealMoneyPriceDetails{
		.appleAppStorePrices = ConvertIntMapToUnreal(Datatype->appleAppStorePrices, Datatype->appleAppStorePricesCount),
		.appleAppStorePricesCount = Datatype->appleAppStorePricesCount,
		.googlePlayPrices = ConvertIntMapToUnreal(Datatype->googlePlayPrices, Datatype->googlePlayPricesCount),
		.googlePlayPricesCount = Datatype->googlePlayPricesCount,
		.microsoftStorePrices = ConvertIntMapToUnreal(Datatype->microsoftStorePrices, Datatype->microsoftStorePricesCount),
		.microsoftStorePricesCount = Datatype->microsoftStorePricesCount,
		.nintendoEShopPrices = ConvertIntMapToUnreal(Datatype->nintendoEShopPrices, Datatype->nintendoEShopPricesCount),
		.nintendoEShopPricesCount = Datatype->nintendoEShopPricesCount,
		.playStationStorePrices = ConvertIntMapToUnreal(Datatype->playStationStorePrices, Datatype->playStationStorePricesCount),
		.playStationStorePricesCount = Datatype->playStationStorePricesCount,
		.steamPrices = ConvertIntMapToUnreal(Datatype->steamPrices, Datatype->steamPricesCount),
		.steamPricesCount = Datatype->steamPricesCount
	});

	return ConvertedType;
}

const PFCatalogRealMoneyPriceDetails* ConvertRealMoneyPriceDetailsToPlayfab(TSharedPtr<const FPFCatalogRealMoneyPriceDetails> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogRealMoneyPriceDetails* ConvertedType = new PFCatalogRealMoneyPriceDetails{
		.appleAppStorePrices = ConvertIntMapToPlayfab(Datatype->appleAppStorePrices),
		.appleAppStorePricesCount = (uint32_t)Datatype->appleAppStorePrices.Num(),
		.googlePlayPrices = ConvertIntMapToPlayfab(Datatype->googlePlayPrices),
		.googlePlayPricesCount = (uint32_t)Datatype->googlePlayPrices.Num(),
		.microsoftStorePrices = ConvertIntMapToPlayfab(Datatype->microsoftStorePrices),
		.microsoftStorePricesCount = (uint32_t)Datatype->microsoftStorePrices.Num(),
		.nintendoEShopPrices = ConvertIntMapToPlayfab(Datatype->nintendoEShopPrices),
		.nintendoEShopPricesCount = (uint32_t)Datatype->nintendoEShopPrices.Num(),
		.playStationStorePrices = ConvertIntMapToPlayfab(Datatype->playStationStorePrices),
		.playStationStorePricesCount = (uint32_t)Datatype->playStationStorePrices.Num(),
		.steamPrices = ConvertIntMapToPlayfab(Datatype->steamPrices),
		.steamPricesCount = (uint32_t)Datatype->steamPrices.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogFilterOptions> ConvertFilterOptionsToUnreal(const PFCatalogFilterOptions* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogFilterOptions> ConvertedType = MakeShared<FPFCatalogFilterOptions>(FPFCatalogFilterOptions{
		.filter = Datatype->filter == nullptr ? FString() : FString(Datatype->filter),
		.includeAllItems = TSharedPtr<const bool>(Datatype->includeAllItems)
	});

	return ConvertedType;
}

const PFCatalogFilterOptions* ConvertFilterOptionsToPlayfab(TSharedPtr<const FPFCatalogFilterOptions> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogFilterOptions* ConvertedType = new PFCatalogFilterOptions{
		.filter = ConvertFStringToCharPtr(Datatype->filter),
		.includeAllItems = Datatype->includeAllItems ? new bool(*Datatype->includeAllItems) : nullptr
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogPermissions> ConvertPermissionsToUnreal(const PFCatalogPermissions* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogPermissions> ConvertedType = MakeShared<FPFCatalogPermissions>(FPFCatalogPermissions{
		.segmentIds = ConvertCharArrayToUnreal(Datatype->segmentIds, Datatype->segmentIdsCount),
		.segmentIdsCount = Datatype->segmentIdsCount
	});

	return ConvertedType;
}

const PFCatalogPermissions* ConvertPermissionsToPlayfab(TSharedPtr<const FPFCatalogPermissions> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogPermissions* ConvertedType = new PFCatalogPermissions{
		.segmentIds = ConvertFStringArrayToPlayfab(Datatype->segmentIds),
		.segmentIdsCount = (uint32_t)Datatype->segmentIds.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogCatalogPriceAmountOverride> ConvertCatalogPriceAmountOverrideToUnreal(const PFCatalogCatalogPriceAmountOverride* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogCatalogPriceAmountOverride> ConvertedType = MakeShared<FPFCatalogCatalogPriceAmountOverride>(FPFCatalogCatalogPriceAmountOverride{
		.fixedValue = TSharedPtr<const int32>(Datatype->fixedValue),
		.itemId = Datatype->itemId == nullptr ? FString() : FString(Datatype->itemId),
		.multiplier = TSharedPtr<const double>(Datatype->multiplier)
	});

	return ConvertedType;
}

const PFCatalogCatalogPriceAmountOverride* ConvertCatalogPriceAmountOverrideToPlayfab(TSharedPtr<const FPFCatalogCatalogPriceAmountOverride> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogCatalogPriceAmountOverride* ConvertedType = new PFCatalogCatalogPriceAmountOverride{
		.fixedValue = Datatype->fixedValue ? new int32(*Datatype->fixedValue) : nullptr,
		.itemId = ConvertFStringToCharPtr(Datatype->itemId),
		.multiplier = Datatype->multiplier ? new double(*Datatype->multiplier) : nullptr
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogCatalogPriceOverride> ConvertCatalogPriceOverrideToUnreal(const PFCatalogCatalogPriceOverride* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogCatalogPriceOverride> ConvertedType = MakeShared<FPFCatalogCatalogPriceOverride>(FPFCatalogCatalogPriceOverride{
		.amounts = ConvertPlayfabArrayToUnreal(Datatype->amounts, Datatype->amountsCount, ConvertCatalogPriceAmountOverrideToUnreal),
		.amountsCount = Datatype->amountsCount
	});

	return ConvertedType;
}

const PFCatalogCatalogPriceOverride* ConvertCatalogPriceOverrideToPlayfab(TSharedPtr<const FPFCatalogCatalogPriceOverride> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogCatalogPriceOverride* ConvertedType = new PFCatalogCatalogPriceOverride{
		.amounts = ConvertUnrealArrayToPlayfab(Datatype->amounts, ConvertCatalogPriceAmountOverrideToPlayfab),
		.amountsCount = (uint32_t)Datatype->amounts.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogCatalogPriceOptionsOverride> ConvertCatalogPriceOptionsOverrideToUnreal(const PFCatalogCatalogPriceOptionsOverride* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogCatalogPriceOptionsOverride> ConvertedType = MakeShared<FPFCatalogCatalogPriceOptionsOverride>(FPFCatalogCatalogPriceOptionsOverride{
		.prices = ConvertPlayfabArrayToUnreal(Datatype->prices, Datatype->pricesCount, ConvertCatalogPriceOverrideToUnreal),
		.pricesCount = Datatype->pricesCount
	});

	return ConvertedType;
}

const PFCatalogCatalogPriceOptionsOverride* ConvertCatalogPriceOptionsOverrideToPlayfab(TSharedPtr<const FPFCatalogCatalogPriceOptionsOverride> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogCatalogPriceOptionsOverride* ConvertedType = new PFCatalogCatalogPriceOptionsOverride{
		.prices = ConvertUnrealArrayToPlayfab(Datatype->prices, ConvertCatalogPriceOverrideToPlayfab),
		.pricesCount = (uint32_t)Datatype->prices.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogStoreDetails> ConvertStoreDetailsToUnreal(const PFCatalogStoreDetails* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogStoreDetails> ConvertedType = MakeShared<FPFCatalogStoreDetails>(FPFCatalogStoreDetails{
		.filterOptions = ConvertFilterOptionsToUnreal(Datatype->filterOptions),
		.permissions = ConvertPermissionsToUnreal(Datatype->permissions),
		.priceOptionsOverride = ConvertCatalogPriceOptionsOverrideToUnreal(Datatype->priceOptionsOverride)
	});

	return ConvertedType;
}

const PFCatalogStoreDetails* ConvertStoreDetailsToPlayfab(TSharedPtr<const FPFCatalogStoreDetails> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogStoreDetails* ConvertedType = new PFCatalogStoreDetails{
		.filterOptions = ConvertFilterOptionsToPlayfab(Datatype->filterOptions),
		.permissions = ConvertPermissionsToPlayfab(Datatype->permissions),
		.priceOptionsOverride = ConvertCatalogPriceOptionsOverrideToPlayfab(Datatype->priceOptionsOverride)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogCatalogItem> ConvertCatalogItemToUnreal(const PFCatalogCatalogItem* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogCatalogItem> ConvertedType = MakeShared<FPFCatalogCatalogItem>(FPFCatalogCatalogItem{
		.alternateIds = ConvertPlayfabArrayToUnreal(Datatype->alternateIds, Datatype->alternateIdsCount, ConvertCatalogAlternateIdToUnreal),
		.alternateIdsCount = Datatype->alternateIdsCount,
		.contents = ConvertPlayfabArrayToUnreal(Datatype->contents, Datatype->contentsCount, ConvertContentToUnreal),
		.contentsCount = Datatype->contentsCount,
		.contentType = Datatype->contentType == nullptr ? FString() : FString(Datatype->contentType),
		.creationDate = ConvertTimeToUnreal(Datatype->creationDate),
		.creatorEntity = ConvertEntityKeyToUnreal(Datatype->creatorEntity),
		.deepLinks = ConvertPlayfabArrayToUnreal(Datatype->deepLinks, Datatype->deepLinksCount, ConvertDeepLinkToUnreal),
		.deepLinksCount = Datatype->deepLinksCount,
		.defaultStackId = Datatype->defaultStackId == nullptr ? FString() : FString(Datatype->defaultStackId),
		.description = ConvertCharMapToUnreal(Datatype->description, Datatype->descriptionCount),
		.descriptionCount = Datatype->descriptionCount,
		.displayProperties = FPFJsonObject{ .stringValue = FString(Datatype->displayProperties.stringValue) },
		.displayVersion = Datatype->displayVersion == nullptr ? FString() : FString(Datatype->displayVersion),
		.endDate = ConvertTimeToUnreal(Datatype->endDate),
		.eTag = Datatype->eTag == nullptr ? FString() : FString(Datatype->eTag),
		.id = Datatype->id == nullptr ? FString() : FString(Datatype->id),
		.images = ConvertPlayfabArrayToUnreal(Datatype->images, Datatype->imagesCount, ConvertImageToUnreal),
		.imagesCount = Datatype->imagesCount,
		.isHidden = TSharedPtr<const bool>(Datatype->isHidden),
		.itemReferences = ConvertPlayfabArrayToUnreal(Datatype->itemReferences, Datatype->itemReferencesCount, ConvertCatalogItemReferenceToUnreal),
		.itemReferencesCount = Datatype->itemReferencesCount,
		.keywords = ConvertPlayfabMapToUnreal<PFCatalogKeywordSetDictionaryEntry, FPFCatalogKeywordSet, PFCatalogKeywordSet>(Datatype->keywords, Datatype->keywordsCount, ConvertKeywordSetToUnreal),
		.keywordsCount = Datatype->keywordsCount,
		.lastModifiedDate = ConvertTimeToUnreal(Datatype->lastModifiedDate),
		.moderation = ConvertModerationStateToUnreal(Datatype->moderation),
		.platforms = ConvertCharArrayToUnreal(Datatype->platforms, Datatype->platformsCount),
		.platformsCount = Datatype->platformsCount,
		.priceOptions = ConvertCatalogPriceOptionsToUnreal(Datatype->priceOptions),
		.rating = ConvertRatingToUnreal(Datatype->rating),
		.realMoneyPriceDetails = ConvertRealMoneyPriceDetailsToUnreal(Datatype->realMoneyPriceDetails),
		.startDate = ConvertTimeToUnreal(Datatype->startDate),
		.storeDetails = ConvertStoreDetailsToUnreal(Datatype->storeDetails),
		.tags = ConvertCharArrayToUnreal(Datatype->tags, Datatype->tagsCount),
		.tagsCount = Datatype->tagsCount,
		.title = ConvertCharMapToUnreal(Datatype->title, Datatype->titleCount),
		.titleCount = Datatype->titleCount,
		.type = Datatype->type == nullptr ? FString() : FString(Datatype->type)
	});

	return ConvertedType;
}

const PFCatalogCatalogItem* ConvertCatalogItemToPlayfab(TSharedPtr<const FPFCatalogCatalogItem> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogCatalogItem* ConvertedType = new PFCatalogCatalogItem{
		.alternateIds = ConvertUnrealArrayToPlayfab(Datatype->alternateIds, ConvertCatalogAlternateIdToPlayfab),
		.alternateIdsCount = (uint32_t)Datatype->alternateIds.Num(),
		.contents = ConvertUnrealArrayToPlayfab(Datatype->contents, ConvertContentToPlayfab),
		.contentsCount = (uint32_t)Datatype->contents.Num(),
		.contentType = ConvertFStringToCharPtr(Datatype->contentType),
		.creationDate = ConvertFDateTimeToPlayfab(Datatype->creationDate),
		.creatorEntity = ConvertEntityKeyToPlayfab(Datatype->creatorEntity),
		.deepLinks = ConvertUnrealArrayToPlayfab(Datatype->deepLinks, ConvertDeepLinkToPlayfab),
		.deepLinksCount = (uint32_t)Datatype->deepLinks.Num(),
		.defaultStackId = ConvertFStringToCharPtr(Datatype->defaultStackId),
		.description = ConvertFStringMapToPlayfab(Datatype->description),
		.descriptionCount = (uint32_t)Datatype->description.Num(),
		.displayProperties = PFJsonObject{ .stringValue = ConvertFStringToCharPtr(Datatype->displayProperties.stringValue) },
		.displayVersion = ConvertFStringToCharPtr(Datatype->displayVersion),
		.endDate = ConvertFDateTimeToPlayfab(Datatype->endDate),
		.eTag = ConvertFStringToCharPtr(Datatype->eTag),
		.id = ConvertFStringToCharPtr(Datatype->id),
		.images = ConvertUnrealArrayToPlayfab(Datatype->images, ConvertImageToPlayfab),
		.imagesCount = (uint32_t)Datatype->images.Num(),
		.isHidden = Datatype->isHidden ? new bool(*Datatype->isHidden) : nullptr,
		.itemReferences = ConvertUnrealArrayToPlayfab(Datatype->itemReferences, ConvertCatalogItemReferenceToPlayfab),
		.itemReferencesCount = (uint32_t)Datatype->itemReferences.Num(),
		.keywords = ConvertUnrealMapToPlayfab<PFCatalogKeywordSetDictionaryEntry, FPFCatalogKeywordSet, PFCatalogKeywordSet>(Datatype->keywords, ConvertKeywordSetToPlayfab),
		.keywordsCount = (uint32_t)Datatype->keywords.Num(),
		.lastModifiedDate = ConvertFDateTimeToPlayfab(Datatype->lastModifiedDate),
		.moderation = ConvertModerationStateToPlayfab(Datatype->moderation),
		.platforms = ConvertFStringArrayToPlayfab(Datatype->platforms),
		.platformsCount = (uint32_t)Datatype->platforms.Num(),
		.priceOptions = ConvertCatalogPriceOptionsToPlayfab(Datatype->priceOptions),
		.rating = ConvertRatingToPlayfab(Datatype->rating),
		.realMoneyPriceDetails = ConvertRealMoneyPriceDetailsToPlayfab(Datatype->realMoneyPriceDetails),
		.startDate = ConvertFDateTimeToPlayfab(Datatype->startDate),
		.storeDetails = ConvertStoreDetailsToPlayfab(Datatype->storeDetails),
		.tags = ConvertFStringArrayToPlayfab(Datatype->tags),
		.tagsCount = (uint32_t)Datatype->tags.Num(),
		.title = ConvertFStringMapToPlayfab(Datatype->title),
		.titleCount = (uint32_t)Datatype->title.Num(),
		.type = ConvertFStringToCharPtr(Datatype->type)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogCreateDraftItemRequest> ConvertCreateDraftItemRequestToUnreal(const PFCatalogCreateDraftItemRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogCreateDraftItemRequest> ConvertedType = MakeShared<FPFCatalogCreateDraftItemRequest>(FPFCatalogCreateDraftItemRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.item = ConvertCatalogItemToUnreal(Datatype->item),
		.publish = Datatype->publish
	});

	return ConvertedType;
}

const PFCatalogCreateDraftItemRequest* ConvertCreateDraftItemRequestToPlayfab(TSharedPtr<const FPFCatalogCreateDraftItemRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogCreateDraftItemRequest* ConvertedType = new PFCatalogCreateDraftItemRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.item = ConvertCatalogItemToPlayfab(Datatype->item),
		.publish = Datatype->publish
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogCreateDraftItemResponse> ConvertCreateDraftItemResponseToUnreal(const PFCatalogCreateDraftItemResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogCreateDraftItemResponse> ConvertedType = MakeShared<FPFCatalogCreateDraftItemResponse>(FPFCatalogCreateDraftItemResponse{
		.item = ConvertCatalogItemToUnreal(Datatype->item)
	});

	return ConvertedType;
}

const PFCatalogCreateDraftItemResponse* ConvertCreateDraftItemResponseToPlayfab(TSharedPtr<const FPFCatalogCreateDraftItemResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogCreateDraftItemResponse* ConvertedType = new PFCatalogCreateDraftItemResponse{
		.item = ConvertCatalogItemToPlayfab(Datatype->item)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogUploadInfo> ConvertUploadInfoToUnreal(const PFCatalogUploadInfo* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogUploadInfo> ConvertedType = MakeShared<FPFCatalogUploadInfo>(FPFCatalogUploadInfo{
		.fileName = Datatype->fileName == nullptr ? FString() : FString(Datatype->fileName)
	});

	return ConvertedType;
}

const PFCatalogUploadInfo* ConvertUploadInfoToPlayfab(TSharedPtr<const FPFCatalogUploadInfo> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogUploadInfo* ConvertedType = new PFCatalogUploadInfo{
		.fileName = ConvertFStringToCharPtr(Datatype->fileName)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogCreateUploadUrlsRequest> ConvertCreateUploadUrlsRequestToUnreal(const PFCatalogCreateUploadUrlsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogCreateUploadUrlsRequest> ConvertedType = MakeShared<FPFCatalogCreateUploadUrlsRequest>(FPFCatalogCreateUploadUrlsRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.files = ConvertPlayfabArrayToUnreal(Datatype->files, Datatype->filesCount, ConvertUploadInfoToUnreal),
		.filesCount = Datatype->filesCount
	});

	return ConvertedType;
}

const PFCatalogCreateUploadUrlsRequest* ConvertCreateUploadUrlsRequestToPlayfab(TSharedPtr<const FPFCatalogCreateUploadUrlsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogCreateUploadUrlsRequest* ConvertedType = new PFCatalogCreateUploadUrlsRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.files = ConvertUnrealArrayToPlayfab(Datatype->files, ConvertUploadInfoToPlayfab),
		.filesCount = (uint32_t)Datatype->files.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogUploadUrlMetadata> ConvertUploadUrlMetadataToUnreal(const PFCatalogUploadUrlMetadata* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogUploadUrlMetadata> ConvertedType = MakeShared<FPFCatalogUploadUrlMetadata>(FPFCatalogUploadUrlMetadata{
		.fileName = Datatype->fileName == nullptr ? FString() : FString(Datatype->fileName),
		.id = Datatype->id == nullptr ? FString() : FString(Datatype->id),
		.url = Datatype->url == nullptr ? FString() : FString(Datatype->url)
	});

	return ConvertedType;
}

const PFCatalogUploadUrlMetadata* ConvertUploadUrlMetadataToPlayfab(TSharedPtr<const FPFCatalogUploadUrlMetadata> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogUploadUrlMetadata* ConvertedType = new PFCatalogUploadUrlMetadata{
		.fileName = ConvertFStringToCharPtr(Datatype->fileName),
		.id = ConvertFStringToCharPtr(Datatype->id),
		.url = ConvertFStringToCharPtr(Datatype->url)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogCreateUploadUrlsResponse> ConvertCreateUploadUrlsResponseToUnreal(const PFCatalogCreateUploadUrlsResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogCreateUploadUrlsResponse> ConvertedType = MakeShared<FPFCatalogCreateUploadUrlsResponse>(FPFCatalogCreateUploadUrlsResponse{
		.uploadUrls = ConvertPlayfabArrayToUnreal(Datatype->uploadUrls, Datatype->uploadUrlsCount, ConvertUploadUrlMetadataToUnreal),
		.uploadUrlsCount = Datatype->uploadUrlsCount
	});

	return ConvertedType;
}

const PFCatalogCreateUploadUrlsResponse* ConvertCreateUploadUrlsResponseToPlayfab(TSharedPtr<const FPFCatalogCreateUploadUrlsResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogCreateUploadUrlsResponse* ConvertedType = new PFCatalogCreateUploadUrlsResponse{
		.uploadUrls = ConvertUnrealArrayToPlayfab(Datatype->uploadUrls, ConvertUploadUrlMetadataToPlayfab),
		.uploadUrlsCount = (uint32_t)Datatype->uploadUrls.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogDeleteEntityItemReviewsRequest> ConvertDeleteEntityItemReviewsRequestToUnreal(const PFCatalogDeleteEntityItemReviewsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogDeleteEntityItemReviewsRequest> ConvertedType = MakeShared<FPFCatalogDeleteEntityItemReviewsRequest>(FPFCatalogDeleteEntityItemReviewsRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity)
	});

	return ConvertedType;
}

const PFCatalogDeleteEntityItemReviewsRequest* ConvertDeleteEntityItemReviewsRequestToPlayfab(TSharedPtr<const FPFCatalogDeleteEntityItemReviewsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogDeleteEntityItemReviewsRequest* ConvertedType = new PFCatalogDeleteEntityItemReviewsRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogDeleteItemRequest> ConvertDeleteItemRequestToUnreal(const PFCatalogDeleteItemRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogDeleteItemRequest> ConvertedType = MakeShared<FPFCatalogDeleteItemRequest>(FPFCatalogDeleteItemRequest{
		.alternateId = ConvertCatalogAlternateIdToUnreal(Datatype->alternateId),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.id = Datatype->id == nullptr ? FString() : FString(Datatype->id)
	});

	return ConvertedType;
}

const PFCatalogDeleteItemRequest* ConvertDeleteItemRequestToPlayfab(TSharedPtr<const FPFCatalogDeleteItemRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogDeleteItemRequest* ConvertedType = new PFCatalogDeleteItemRequest{
		.alternateId = ConvertCatalogAlternateIdToPlayfab(Datatype->alternateId),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.id = ConvertFStringToCharPtr(Datatype->id)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogGetCatalogConfigRequest> ConvertGetCatalogConfigRequestToUnreal(const PFCatalogGetCatalogConfigRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogGetCatalogConfigRequest> ConvertedType = MakeShared<FPFCatalogGetCatalogConfigRequest>(FPFCatalogGetCatalogConfigRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount
	});

	return ConvertedType;
}

const PFCatalogGetCatalogConfigRequest* ConvertGetCatalogConfigRequestToPlayfab(TSharedPtr<const FPFCatalogGetCatalogConfigRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogGetCatalogConfigRequest* ConvertedType = new PFCatalogGetCatalogConfigRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogCatalogSpecificConfig> ConvertCatalogSpecificConfigToUnreal(const PFCatalogCatalogSpecificConfig* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogCatalogSpecificConfig> ConvertedType = MakeShared<FPFCatalogCatalogSpecificConfig>(FPFCatalogCatalogSpecificConfig{
		.contentTypes = ConvertCharArrayToUnreal(Datatype->contentTypes, Datatype->contentTypesCount),
		.contentTypesCount = Datatype->contentTypesCount,
		.tags = ConvertCharArrayToUnreal(Datatype->tags, Datatype->tagsCount),
		.tagsCount = Datatype->tagsCount
	});

	return ConvertedType;
}

const PFCatalogCatalogSpecificConfig* ConvertCatalogSpecificConfigToPlayfab(TSharedPtr<const FPFCatalogCatalogSpecificConfig> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogCatalogSpecificConfig* ConvertedType = new PFCatalogCatalogSpecificConfig{
		.contentTypes = ConvertFStringArrayToPlayfab(Datatype->contentTypes),
		.contentTypesCount = (uint32_t)Datatype->contentTypes.Num(),
		.tags = ConvertFStringArrayToPlayfab(Datatype->tags),
		.tagsCount = (uint32_t)Datatype->tags.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogDeepLinkFormat> ConvertDeepLinkFormatToUnreal(const PFCatalogDeepLinkFormat* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogDeepLinkFormat> ConvertedType = MakeShared<FPFCatalogDeepLinkFormat>(FPFCatalogDeepLinkFormat{
		.format = Datatype->format == nullptr ? FString() : FString(Datatype->format),
		.platform = Datatype->platform == nullptr ? FString() : FString(Datatype->platform)
	});

	return ConvertedType;
}

const PFCatalogDeepLinkFormat* ConvertDeepLinkFormatToPlayfab(TSharedPtr<const FPFCatalogDeepLinkFormat> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogDeepLinkFormat* ConvertedType = new PFCatalogDeepLinkFormat{
		.format = ConvertFStringToCharPtr(Datatype->format),
		.platform = ConvertFStringToCharPtr(Datatype->platform)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogDisplayPropertyIndexInfo> ConvertDisplayPropertyIndexInfoToUnreal(const PFCatalogDisplayPropertyIndexInfo* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogDisplayPropertyIndexInfo> ConvertedType = MakeShared<FPFCatalogDisplayPropertyIndexInfo>(FPFCatalogDisplayPropertyIndexInfo{
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name),
		.type = MakeShared<FPFCatalogDisplayPropertyType>(ConvertDisplayPropertyTypeToUnreal(Datatype->type))
	});

	return ConvertedType;
}

const PFCatalogDisplayPropertyIndexInfo* ConvertDisplayPropertyIndexInfoToPlayfab(TSharedPtr<const FPFCatalogDisplayPropertyIndexInfo> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogDisplayPropertyIndexInfo* ConvertedType = new PFCatalogDisplayPropertyIndexInfo{
		.name = ConvertFStringToCharPtr(Datatype->name),
		.type = new PFCatalogDisplayPropertyType(ConvertDisplayPropertyTypeToPlayfab(Datatype->type))
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogFileConfig> ConvertFileConfigToUnreal(const PFCatalogFileConfig* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogFileConfig> ConvertedType = MakeShared<FPFCatalogFileConfig>(FPFCatalogFileConfig{
		.contentTypes = ConvertCharArrayToUnreal(Datatype->contentTypes, Datatype->contentTypesCount),
		.contentTypesCount = Datatype->contentTypesCount,
		.tags = ConvertCharArrayToUnreal(Datatype->tags, Datatype->tagsCount),
		.tagsCount = Datatype->tagsCount
	});

	return ConvertedType;
}

const PFCatalogFileConfig* ConvertFileConfigToPlayfab(TSharedPtr<const FPFCatalogFileConfig> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogFileConfig* ConvertedType = new PFCatalogFileConfig{
		.contentTypes = ConvertFStringArrayToPlayfab(Datatype->contentTypes),
		.contentTypesCount = (uint32_t)Datatype->contentTypes.Num(),
		.tags = ConvertFStringArrayToPlayfab(Datatype->tags),
		.tagsCount = (uint32_t)Datatype->tags.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogImageConfig> ConvertImageConfigToUnreal(const PFCatalogImageConfig* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogImageConfig> ConvertedType = MakeShared<FPFCatalogImageConfig>(FPFCatalogImageConfig{
		.tags = ConvertCharArrayToUnreal(Datatype->tags, Datatype->tagsCount),
		.tagsCount = Datatype->tagsCount
	});

	return ConvertedType;
}

const PFCatalogImageConfig* ConvertImageConfigToPlayfab(TSharedPtr<const FPFCatalogImageConfig> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogImageConfig* ConvertedType = new PFCatalogImageConfig{
		.tags = ConvertFStringArrayToPlayfab(Datatype->tags),
		.tagsCount = (uint32_t)Datatype->tags.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogCategoryRatingConfig> ConvertCategoryRatingConfigToUnreal(const PFCatalogCategoryRatingConfig* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogCategoryRatingConfig> ConvertedType = MakeShared<FPFCatalogCategoryRatingConfig>(FPFCatalogCategoryRatingConfig{
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name)
	});

	return ConvertedType;
}

const PFCatalogCategoryRatingConfig* ConvertCategoryRatingConfigToPlayfab(TSharedPtr<const FPFCatalogCategoryRatingConfig> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogCategoryRatingConfig* ConvertedType = new PFCatalogCategoryRatingConfig{
		.name = ConvertFStringToCharPtr(Datatype->name)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogReviewConfig> ConvertReviewConfigToUnreal(const PFCatalogReviewConfig* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogReviewConfig> ConvertedType = MakeShared<FPFCatalogReviewConfig>(FPFCatalogReviewConfig{
		.categoryRatings = ConvertPlayfabArrayToUnreal(Datatype->categoryRatings, Datatype->categoryRatingsCount, ConvertCategoryRatingConfigToUnreal),
		.categoryRatingsCount = Datatype->categoryRatingsCount
	});

	return ConvertedType;
}

const PFCatalogReviewConfig* ConvertReviewConfigToPlayfab(TSharedPtr<const FPFCatalogReviewConfig> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogReviewConfig* ConvertedType = new PFCatalogReviewConfig{
		.categoryRatings = ConvertUnrealArrayToPlayfab(Datatype->categoryRatings, ConvertCategoryRatingConfigToPlayfab),
		.categoryRatingsCount = (uint32_t)Datatype->categoryRatings.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogUserGeneratedContentSpecificConfig> ConvertUserGeneratedContentSpecificConfigToUnreal(const PFCatalogUserGeneratedContentSpecificConfig* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogUserGeneratedContentSpecificConfig> ConvertedType = MakeShared<FPFCatalogUserGeneratedContentSpecificConfig>(FPFCatalogUserGeneratedContentSpecificConfig{
		.contentTypes = ConvertCharArrayToUnreal(Datatype->contentTypes, Datatype->contentTypesCount),
		.contentTypesCount = Datatype->contentTypesCount,
		.tags = ConvertCharArrayToUnreal(Datatype->tags, Datatype->tagsCount),
		.tagsCount = Datatype->tagsCount
	});

	return ConvertedType;
}

const PFCatalogUserGeneratedContentSpecificConfig* ConvertUserGeneratedContentSpecificConfigToPlayfab(TSharedPtr<const FPFCatalogUserGeneratedContentSpecificConfig> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogUserGeneratedContentSpecificConfig* ConvertedType = new PFCatalogUserGeneratedContentSpecificConfig{
		.contentTypes = ConvertFStringArrayToPlayfab(Datatype->contentTypes),
		.contentTypesCount = (uint32_t)Datatype->contentTypes.Num(),
		.tags = ConvertFStringArrayToPlayfab(Datatype->tags),
		.tagsCount = (uint32_t)Datatype->tags.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogCatalogConfig> ConvertCatalogConfigToUnreal(const PFCatalogCatalogConfig* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogCatalogConfig> ConvertedType = MakeShared<FPFCatalogCatalogConfig>(FPFCatalogCatalogConfig{
		.adminEntities = ConvertPlayfabArrayToUnreal(Datatype->adminEntities, Datatype->adminEntitiesCount, ConvertEntityKeyToUnreal),
		.adminEntitiesCount = Datatype->adminEntitiesCount,
		.catalog = ConvertCatalogSpecificConfigToUnreal(Datatype->catalog),
		.deepLinkFormats = ConvertPlayfabArrayToUnreal(Datatype->deepLinkFormats, Datatype->deepLinkFormatsCount, ConvertDeepLinkFormatToUnreal),
		.deepLinkFormatsCount = Datatype->deepLinkFormatsCount,
		.displayPropertyIndexInfos = ConvertPlayfabArrayToUnreal(Datatype->displayPropertyIndexInfos, Datatype->displayPropertyIndexInfosCount, ConvertDisplayPropertyIndexInfoToUnreal),
		.displayPropertyIndexInfosCount = Datatype->displayPropertyIndexInfosCount,
		.file = ConvertFileConfigToUnreal(Datatype->file),
		.image = ConvertImageConfigToUnreal(Datatype->image),
		.isCatalogEnabled = Datatype->isCatalogEnabled,
		.platforms = ConvertCharArrayToUnreal(Datatype->platforms, Datatype->platformsCount),
		.platformsCount = Datatype->platformsCount,
		.review = ConvertReviewConfigToUnreal(Datatype->review),
		.reviewerEntities = ConvertPlayfabArrayToUnreal(Datatype->reviewerEntities, Datatype->reviewerEntitiesCount, ConvertEntityKeyToUnreal),
		.reviewerEntitiesCount = Datatype->reviewerEntitiesCount,
		.userGeneratedContent = ConvertUserGeneratedContentSpecificConfigToUnreal(Datatype->userGeneratedContent)
	});

	return ConvertedType;
}

const PFCatalogCatalogConfig* ConvertCatalogConfigToPlayfab(TSharedPtr<const FPFCatalogCatalogConfig> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogCatalogConfig* ConvertedType = new PFCatalogCatalogConfig{
		.adminEntities = ConvertUnrealArrayToPlayfab(Datatype->adminEntities, ConvertEntityKeyToPlayfab),
		.adminEntitiesCount = (uint32_t)Datatype->adminEntities.Num(),
		.catalog = ConvertCatalogSpecificConfigToPlayfab(Datatype->catalog),
		.deepLinkFormats = ConvertUnrealArrayToPlayfab(Datatype->deepLinkFormats, ConvertDeepLinkFormatToPlayfab),
		.deepLinkFormatsCount = (uint32_t)Datatype->deepLinkFormats.Num(),
		.displayPropertyIndexInfos = ConvertUnrealArrayToPlayfab(Datatype->displayPropertyIndexInfos, ConvertDisplayPropertyIndexInfoToPlayfab),
		.displayPropertyIndexInfosCount = (uint32_t)Datatype->displayPropertyIndexInfos.Num(),
		.file = ConvertFileConfigToPlayfab(Datatype->file),
		.image = ConvertImageConfigToPlayfab(Datatype->image),
		.isCatalogEnabled = Datatype->isCatalogEnabled,
		.platforms = ConvertFStringArrayToPlayfab(Datatype->platforms),
		.platformsCount = (uint32_t)Datatype->platforms.Num(),
		.review = ConvertReviewConfigToPlayfab(Datatype->review),
		.reviewerEntities = ConvertUnrealArrayToPlayfab(Datatype->reviewerEntities, ConvertEntityKeyToPlayfab),
		.reviewerEntitiesCount = (uint32_t)Datatype->reviewerEntities.Num(),
		.userGeneratedContent = ConvertUserGeneratedContentSpecificConfigToPlayfab(Datatype->userGeneratedContent)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogGetCatalogConfigResponse> ConvertGetCatalogConfigResponseToUnreal(const PFCatalogGetCatalogConfigResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogGetCatalogConfigResponse> ConvertedType = MakeShared<FPFCatalogGetCatalogConfigResponse>(FPFCatalogGetCatalogConfigResponse{
		.config = ConvertCatalogConfigToUnreal(Datatype->config)
	});

	return ConvertedType;
}

const PFCatalogGetCatalogConfigResponse* ConvertGetCatalogConfigResponseToPlayfab(TSharedPtr<const FPFCatalogGetCatalogConfigResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogGetCatalogConfigResponse* ConvertedType = new PFCatalogGetCatalogConfigResponse{
		.config = ConvertCatalogConfigToPlayfab(Datatype->config)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogGetDraftItemRequest> ConvertGetDraftItemRequestToUnreal(const PFCatalogGetDraftItemRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogGetDraftItemRequest> ConvertedType = MakeShared<FPFCatalogGetDraftItemRequest>(FPFCatalogGetDraftItemRequest{
		.alternateId = ConvertCatalogAlternateIdToUnreal(Datatype->alternateId),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.id = Datatype->id == nullptr ? FString() : FString(Datatype->id)
	});

	return ConvertedType;
}

const PFCatalogGetDraftItemRequest* ConvertGetDraftItemRequestToPlayfab(TSharedPtr<const FPFCatalogGetDraftItemRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogGetDraftItemRequest* ConvertedType = new PFCatalogGetDraftItemRequest{
		.alternateId = ConvertCatalogAlternateIdToPlayfab(Datatype->alternateId),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.id = ConvertFStringToCharPtr(Datatype->id)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogGetDraftItemResponse> ConvertGetDraftItemResponseToUnreal(const PFCatalogGetDraftItemResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogGetDraftItemResponse> ConvertedType = MakeShared<FPFCatalogGetDraftItemResponse>(FPFCatalogGetDraftItemResponse{
		.item = ConvertCatalogItemToUnreal(Datatype->item)
	});

	return ConvertedType;
}

const PFCatalogGetDraftItemResponse* ConvertGetDraftItemResponseToPlayfab(TSharedPtr<const FPFCatalogGetDraftItemResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogGetDraftItemResponse* ConvertedType = new PFCatalogGetDraftItemResponse{
		.item = ConvertCatalogItemToPlayfab(Datatype->item)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogGetDraftItemsRequest> ConvertGetDraftItemsRequestToUnreal(const PFCatalogGetDraftItemsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogGetDraftItemsRequest> ConvertedType = MakeShared<FPFCatalogGetDraftItemsRequest>(FPFCatalogGetDraftItemsRequest{
		.alternateIds = ConvertPlayfabArrayToUnreal(Datatype->alternateIds, Datatype->alternateIdsCount, ConvertCatalogAlternateIdToUnreal),
		.alternateIdsCount = Datatype->alternateIdsCount,
		.continuationToken = Datatype->continuationToken == nullptr ? FString() : FString(Datatype->continuationToken),
		.count = TSharedPtr<const int32>(Datatype->count),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.ids = ConvertCharArrayToUnreal(Datatype->ids, Datatype->idsCount),
		.idsCount = Datatype->idsCount
	});

	return ConvertedType;
}

const PFCatalogGetDraftItemsRequest* ConvertGetDraftItemsRequestToPlayfab(TSharedPtr<const FPFCatalogGetDraftItemsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogGetDraftItemsRequest* ConvertedType = new PFCatalogGetDraftItemsRequest{
		.alternateIds = ConvertUnrealArrayToPlayfab(Datatype->alternateIds, ConvertCatalogAlternateIdToPlayfab),
		.alternateIdsCount = (uint32_t)Datatype->alternateIds.Num(),
		.continuationToken = ConvertFStringToCharPtr(Datatype->continuationToken),
		.count = Datatype->count ? new int32(*Datatype->count) : nullptr,
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.ids = ConvertFStringArrayToPlayfab(Datatype->ids),
		.idsCount = (uint32_t)Datatype->ids.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogGetDraftItemsResponse> ConvertGetDraftItemsResponseToUnreal(const PFCatalogGetDraftItemsResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogGetDraftItemsResponse> ConvertedType = MakeShared<FPFCatalogGetDraftItemsResponse>(FPFCatalogGetDraftItemsResponse{
		.continuationToken = Datatype->continuationToken == nullptr ? FString() : FString(Datatype->continuationToken),
		.items = ConvertPlayfabArrayToUnreal(Datatype->items, Datatype->itemsCount, ConvertCatalogItemToUnreal),
		.itemsCount = Datatype->itemsCount
	});

	return ConvertedType;
}

const PFCatalogGetDraftItemsResponse* ConvertGetDraftItemsResponseToPlayfab(TSharedPtr<const FPFCatalogGetDraftItemsResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogGetDraftItemsResponse* ConvertedType = new PFCatalogGetDraftItemsResponse{
		.continuationToken = ConvertFStringToCharPtr(Datatype->continuationToken),
		.items = ConvertUnrealArrayToPlayfab(Datatype->items, ConvertCatalogItemToPlayfab),
		.itemsCount = (uint32_t)Datatype->items.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogGetEntityDraftItemsRequest> ConvertGetEntityDraftItemsRequestToUnreal(const PFCatalogGetEntityDraftItemsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogGetEntityDraftItemsRequest> ConvertedType = MakeShared<FPFCatalogGetEntityDraftItemsRequest>(FPFCatalogGetEntityDraftItemsRequest{
		.continuationToken = Datatype->continuationToken == nullptr ? FString() : FString(Datatype->continuationToken),
		.count = Datatype->count,
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.filter = Datatype->filter == nullptr ? FString() : FString(Datatype->filter)
	});

	return ConvertedType;
}

const PFCatalogGetEntityDraftItemsRequest* ConvertGetEntityDraftItemsRequestToPlayfab(TSharedPtr<const FPFCatalogGetEntityDraftItemsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogGetEntityDraftItemsRequest* ConvertedType = new PFCatalogGetEntityDraftItemsRequest{
		.continuationToken = ConvertFStringToCharPtr(Datatype->continuationToken),
		.count = Datatype->count,
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.filter = ConvertFStringToCharPtr(Datatype->filter)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogGetEntityDraftItemsResponse> ConvertGetEntityDraftItemsResponseToUnreal(const PFCatalogGetEntityDraftItemsResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogGetEntityDraftItemsResponse> ConvertedType = MakeShared<FPFCatalogGetEntityDraftItemsResponse>(FPFCatalogGetEntityDraftItemsResponse{
		.continuationToken = Datatype->continuationToken == nullptr ? FString() : FString(Datatype->continuationToken),
		.items = ConvertPlayfabArrayToUnreal(Datatype->items, Datatype->itemsCount, ConvertCatalogItemToUnreal),
		.itemsCount = Datatype->itemsCount
	});

	return ConvertedType;
}

const PFCatalogGetEntityDraftItemsResponse* ConvertGetEntityDraftItemsResponseToPlayfab(TSharedPtr<const FPFCatalogGetEntityDraftItemsResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogGetEntityDraftItemsResponse* ConvertedType = new PFCatalogGetEntityDraftItemsResponse{
		.continuationToken = ConvertFStringToCharPtr(Datatype->continuationToken),
		.items = ConvertUnrealArrayToPlayfab(Datatype->items, ConvertCatalogItemToPlayfab),
		.itemsCount = (uint32_t)Datatype->items.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogGetEntityItemReviewRequest> ConvertGetEntityItemReviewRequestToUnreal(const PFCatalogGetEntityItemReviewRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogGetEntityItemReviewRequest> ConvertedType = MakeShared<FPFCatalogGetEntityItemReviewRequest>(FPFCatalogGetEntityItemReviewRequest{
		.alternateId = ConvertCatalogAlternateIdToUnreal(Datatype->alternateId),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.id = Datatype->id == nullptr ? FString() : FString(Datatype->id)
	});

	return ConvertedType;
}

const PFCatalogGetEntityItemReviewRequest* ConvertGetEntityItemReviewRequestToPlayfab(TSharedPtr<const FPFCatalogGetEntityItemReviewRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogGetEntityItemReviewRequest* ConvertedType = new PFCatalogGetEntityItemReviewRequest{
		.alternateId = ConvertCatalogAlternateIdToPlayfab(Datatype->alternateId),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.id = ConvertFStringToCharPtr(Datatype->id)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogReview> ConvertReviewToUnreal(const PFCatalogReview* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogReview> ConvertedType = MakeShared<FPFCatalogReview>(FPFCatalogReview{
		.categoryRatings = ConvertIntMapToUnreal(Datatype->categoryRatings, Datatype->categoryRatingsCount),
		.categoryRatingsCount = Datatype->categoryRatingsCount,
		.helpfulNegative = Datatype->helpfulNegative,
		.helpfulPositive = Datatype->helpfulPositive,
		.isInstalled = Datatype->isInstalled,
		.itemId = Datatype->itemId == nullptr ? FString() : FString(Datatype->itemId),
		.itemVersion = Datatype->itemVersion == nullptr ? FString() : FString(Datatype->itemVersion),
		.locale = Datatype->locale == nullptr ? FString() : FString(Datatype->locale),
		.rating = Datatype->rating,
		.reviewerEntity = ConvertEntityKeyToUnreal(Datatype->reviewerEntity),
		.reviewId = Datatype->reviewId == nullptr ? FString() : FString(Datatype->reviewId),
		.reviewText = Datatype->reviewText == nullptr ? FString() : FString(Datatype->reviewText),
		.submitted = FDateTime::FromUnixTimestamp((int64)Datatype->submitted),
		.title = Datatype->title == nullptr ? FString() : FString(Datatype->title)
	});

	return ConvertedType;
}

const PFCatalogReview* ConvertReviewToPlayfab(TSharedPtr<const FPFCatalogReview> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogReview* ConvertedType = new PFCatalogReview{
		.categoryRatings = ConvertIntMapToPlayfab(Datatype->categoryRatings),
		.categoryRatingsCount = (uint32_t)Datatype->categoryRatings.Num(),
		.helpfulNegative = Datatype->helpfulNegative,
		.helpfulPositive = Datatype->helpfulPositive,
		.isInstalled = Datatype->isInstalled,
		.itemId = ConvertFStringToCharPtr(Datatype->itemId),
		.itemVersion = ConvertFStringToCharPtr(Datatype->itemVersion),
		.locale = ConvertFStringToCharPtr(Datatype->locale),
		.rating = Datatype->rating,
		.reviewerEntity = ConvertEntityKeyToPlayfab(Datatype->reviewerEntity),
		.reviewId = ConvertFStringToCharPtr(Datatype->reviewId),
		.reviewText = ConvertFStringToCharPtr(Datatype->reviewText),
		.submitted = Datatype->submitted.ToUnixTimestamp(),
		.title = ConvertFStringToCharPtr(Datatype->title)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogGetEntityItemReviewResponse> ConvertGetEntityItemReviewResponseToUnreal(const PFCatalogGetEntityItemReviewResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogGetEntityItemReviewResponse> ConvertedType = MakeShared<FPFCatalogGetEntityItemReviewResponse>(FPFCatalogGetEntityItemReviewResponse{
		.review = ConvertReviewToUnreal(Datatype->review)
	});

	return ConvertedType;
}

const PFCatalogGetEntityItemReviewResponse* ConvertGetEntityItemReviewResponseToPlayfab(TSharedPtr<const FPFCatalogGetEntityItemReviewResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogGetEntityItemReviewResponse* ConvertedType = new PFCatalogGetEntityItemReviewResponse{
		.review = ConvertReviewToPlayfab(Datatype->review)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogGetItemRequest> ConvertGetItemRequestToUnreal(const PFCatalogGetItemRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogGetItemRequest> ConvertedType = MakeShared<FPFCatalogGetItemRequest>(FPFCatalogGetItemRequest{
		.alternateId = ConvertCatalogAlternateIdToUnreal(Datatype->alternateId),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.id = Datatype->id == nullptr ? FString() : FString(Datatype->id)
	});

	return ConvertedType;
}

const PFCatalogGetItemRequest* ConvertGetItemRequestToPlayfab(TSharedPtr<const FPFCatalogGetItemRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogGetItemRequest* ConvertedType = new PFCatalogGetItemRequest{
		.alternateId = ConvertCatalogAlternateIdToPlayfab(Datatype->alternateId),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.id = ConvertFStringToCharPtr(Datatype->id)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogGetItemResponse> ConvertGetItemResponseToUnreal(const PFCatalogGetItemResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogGetItemResponse> ConvertedType = MakeShared<FPFCatalogGetItemResponse>(FPFCatalogGetItemResponse{
		.item = ConvertCatalogItemToUnreal(Datatype->item)
	});

	return ConvertedType;
}

const PFCatalogGetItemResponse* ConvertGetItemResponseToPlayfab(TSharedPtr<const FPFCatalogGetItemResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogGetItemResponse* ConvertedType = new PFCatalogGetItemResponse{
		.item = ConvertCatalogItemToPlayfab(Datatype->item)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogGetItemContainersRequest> ConvertGetItemContainersRequestToUnreal(const PFCatalogGetItemContainersRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogGetItemContainersRequest> ConvertedType = MakeShared<FPFCatalogGetItemContainersRequest>(FPFCatalogGetItemContainersRequest{
		.alternateId = ConvertCatalogAlternateIdToUnreal(Datatype->alternateId),
		.continuationToken = Datatype->continuationToken == nullptr ? FString() : FString(Datatype->continuationToken),
		.count = Datatype->count,
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.id = Datatype->id == nullptr ? FString() : FString(Datatype->id)
	});

	return ConvertedType;
}

const PFCatalogGetItemContainersRequest* ConvertGetItemContainersRequestToPlayfab(TSharedPtr<const FPFCatalogGetItemContainersRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogGetItemContainersRequest* ConvertedType = new PFCatalogGetItemContainersRequest{
		.alternateId = ConvertCatalogAlternateIdToPlayfab(Datatype->alternateId),
		.continuationToken = ConvertFStringToCharPtr(Datatype->continuationToken),
		.count = Datatype->count,
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.id = ConvertFStringToCharPtr(Datatype->id)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogGetItemContainersResponse> ConvertGetItemContainersResponseToUnreal(const PFCatalogGetItemContainersResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogGetItemContainersResponse> ConvertedType = MakeShared<FPFCatalogGetItemContainersResponse>(FPFCatalogGetItemContainersResponse{
		.containers = ConvertPlayfabArrayToUnreal(Datatype->containers, Datatype->containersCount, ConvertCatalogItemToUnreal),
		.containersCount = Datatype->containersCount,
		.continuationToken = Datatype->continuationToken == nullptr ? FString() : FString(Datatype->continuationToken)
	});

	return ConvertedType;
}

const PFCatalogGetItemContainersResponse* ConvertGetItemContainersResponseToPlayfab(TSharedPtr<const FPFCatalogGetItemContainersResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogGetItemContainersResponse* ConvertedType = new PFCatalogGetItemContainersResponse{
		.containers = ConvertUnrealArrayToPlayfab(Datatype->containers, ConvertCatalogItemToPlayfab),
		.containersCount = (uint32_t)Datatype->containers.Num(),
		.continuationToken = ConvertFStringToCharPtr(Datatype->continuationToken)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogGetItemModerationStateRequest> ConvertGetItemModerationStateRequestToUnreal(const PFCatalogGetItemModerationStateRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogGetItemModerationStateRequest> ConvertedType = MakeShared<FPFCatalogGetItemModerationStateRequest>(FPFCatalogGetItemModerationStateRequest{
		.alternateId = ConvertCatalogAlternateIdToUnreal(Datatype->alternateId),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.id = Datatype->id == nullptr ? FString() : FString(Datatype->id)
	});

	return ConvertedType;
}

const PFCatalogGetItemModerationStateRequest* ConvertGetItemModerationStateRequestToPlayfab(TSharedPtr<const FPFCatalogGetItemModerationStateRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogGetItemModerationStateRequest* ConvertedType = new PFCatalogGetItemModerationStateRequest{
		.alternateId = ConvertCatalogAlternateIdToPlayfab(Datatype->alternateId),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.id = ConvertFStringToCharPtr(Datatype->id)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogGetItemModerationStateResponse> ConvertGetItemModerationStateResponseToUnreal(const PFCatalogGetItemModerationStateResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogGetItemModerationStateResponse> ConvertedType = MakeShared<FPFCatalogGetItemModerationStateResponse>(FPFCatalogGetItemModerationStateResponse{
		.state = ConvertModerationStateToUnreal(Datatype->state)
	});

	return ConvertedType;
}

const PFCatalogGetItemModerationStateResponse* ConvertGetItemModerationStateResponseToPlayfab(TSharedPtr<const FPFCatalogGetItemModerationStateResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogGetItemModerationStateResponse* ConvertedType = new PFCatalogGetItemModerationStateResponse{
		.state = ConvertModerationStateToPlayfab(Datatype->state)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogGetItemPublishStatusRequest> ConvertGetItemPublishStatusRequestToUnreal(const PFCatalogGetItemPublishStatusRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogGetItemPublishStatusRequest> ConvertedType = MakeShared<FPFCatalogGetItemPublishStatusRequest>(FPFCatalogGetItemPublishStatusRequest{
		.alternateId = ConvertCatalogAlternateIdToUnreal(Datatype->alternateId),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.id = Datatype->id == nullptr ? FString() : FString(Datatype->id)
	});

	return ConvertedType;
}

const PFCatalogGetItemPublishStatusRequest* ConvertGetItemPublishStatusRequestToPlayfab(TSharedPtr<const FPFCatalogGetItemPublishStatusRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogGetItemPublishStatusRequest* ConvertedType = new PFCatalogGetItemPublishStatusRequest{
		.alternateId = ConvertCatalogAlternateIdToPlayfab(Datatype->alternateId),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.id = ConvertFStringToCharPtr(Datatype->id)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogGetItemPublishStatusResponse> ConvertGetItemPublishStatusResponseToUnreal(const PFCatalogGetItemPublishStatusResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogGetItemPublishStatusResponse> ConvertedType = MakeShared<FPFCatalogGetItemPublishStatusResponse>(FPFCatalogGetItemPublishStatusResponse{
		.result = MakeShared<FPFCatalogPublishResult>(ConvertPublishResultToUnreal(Datatype->result)),
		.statusMessage = Datatype->statusMessage == nullptr ? FString() : FString(Datatype->statusMessage)
	});

	return ConvertedType;
}

const PFCatalogGetItemPublishStatusResponse* ConvertGetItemPublishStatusResponseToPlayfab(TSharedPtr<const FPFCatalogGetItemPublishStatusResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogGetItemPublishStatusResponse* ConvertedType = new PFCatalogGetItemPublishStatusResponse{
		.result = new PFCatalogPublishResult(ConvertPublishResultToPlayfab(Datatype->result)),
		.statusMessage = ConvertFStringToCharPtr(Datatype->statusMessage)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogGetItemReviewsRequest> ConvertGetItemReviewsRequestToUnreal(const PFCatalogGetItemReviewsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogGetItemReviewsRequest> ConvertedType = MakeShared<FPFCatalogGetItemReviewsRequest>(FPFCatalogGetItemReviewsRequest{
		.alternateId = ConvertCatalogAlternateIdToUnreal(Datatype->alternateId),
		.continuationToken = Datatype->continuationToken == nullptr ? FString() : FString(Datatype->continuationToken),
		.count = Datatype->count,
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.id = Datatype->id == nullptr ? FString() : FString(Datatype->id),
		.orderBy = Datatype->orderBy == nullptr ? FString() : FString(Datatype->orderBy)
	});

	return ConvertedType;
}

const PFCatalogGetItemReviewsRequest* ConvertGetItemReviewsRequestToPlayfab(TSharedPtr<const FPFCatalogGetItemReviewsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogGetItemReviewsRequest* ConvertedType = new PFCatalogGetItemReviewsRequest{
		.alternateId = ConvertCatalogAlternateIdToPlayfab(Datatype->alternateId),
		.continuationToken = ConvertFStringToCharPtr(Datatype->continuationToken),
		.count = Datatype->count,
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.id = ConvertFStringToCharPtr(Datatype->id),
		.orderBy = ConvertFStringToCharPtr(Datatype->orderBy)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogGetItemReviewsResponse> ConvertGetItemReviewsResponseToUnreal(const PFCatalogGetItemReviewsResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogGetItemReviewsResponse> ConvertedType = MakeShared<FPFCatalogGetItemReviewsResponse>(FPFCatalogGetItemReviewsResponse{
		.continuationToken = Datatype->continuationToken == nullptr ? FString() : FString(Datatype->continuationToken),
		.reviews = ConvertPlayfabArrayToUnreal(Datatype->reviews, Datatype->reviewsCount, ConvertReviewToUnreal),
		.reviewsCount = Datatype->reviewsCount
	});

	return ConvertedType;
}

const PFCatalogGetItemReviewsResponse* ConvertGetItemReviewsResponseToPlayfab(TSharedPtr<const FPFCatalogGetItemReviewsResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogGetItemReviewsResponse* ConvertedType = new PFCatalogGetItemReviewsResponse{
		.continuationToken = ConvertFStringToCharPtr(Datatype->continuationToken),
		.reviews = ConvertUnrealArrayToPlayfab(Datatype->reviews, ConvertReviewToPlayfab),
		.reviewsCount = (uint32_t)Datatype->reviews.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogGetItemReviewSummaryRequest> ConvertGetItemReviewSummaryRequestToUnreal(const PFCatalogGetItemReviewSummaryRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogGetItemReviewSummaryRequest> ConvertedType = MakeShared<FPFCatalogGetItemReviewSummaryRequest>(FPFCatalogGetItemReviewSummaryRequest{
		.alternateId = ConvertCatalogAlternateIdToUnreal(Datatype->alternateId),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.id = Datatype->id == nullptr ? FString() : FString(Datatype->id)
	});

	return ConvertedType;
}

const PFCatalogGetItemReviewSummaryRequest* ConvertGetItemReviewSummaryRequestToPlayfab(TSharedPtr<const FPFCatalogGetItemReviewSummaryRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogGetItemReviewSummaryRequest* ConvertedType = new PFCatalogGetItemReviewSummaryRequest{
		.alternateId = ConvertCatalogAlternateIdToPlayfab(Datatype->alternateId),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.id = ConvertFStringToCharPtr(Datatype->id)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogGetItemReviewSummaryResponse> ConvertGetItemReviewSummaryResponseToUnreal(const PFCatalogGetItemReviewSummaryResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogGetItemReviewSummaryResponse> ConvertedType = MakeShared<FPFCatalogGetItemReviewSummaryResponse>(FPFCatalogGetItemReviewSummaryResponse{
		.leastFavorableReview = ConvertReviewToUnreal(Datatype->leastFavorableReview),
		.mostFavorableReview = ConvertReviewToUnreal(Datatype->mostFavorableReview),
		.rating = ConvertRatingToUnreal(Datatype->rating),
		.reviewsCount = Datatype->reviewsCount
	});

	return ConvertedType;
}

const PFCatalogGetItemReviewSummaryResponse* ConvertGetItemReviewSummaryResponseToPlayfab(TSharedPtr<const FPFCatalogGetItemReviewSummaryResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogGetItemReviewSummaryResponse* ConvertedType = new PFCatalogGetItemReviewSummaryResponse{
		.leastFavorableReview = ConvertReviewToPlayfab(Datatype->leastFavorableReview),
		.mostFavorableReview = ConvertReviewToPlayfab(Datatype->mostFavorableReview),
		.rating = ConvertRatingToPlayfab(Datatype->rating),
		.reviewsCount = Datatype->reviewsCount
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogGetItemsRequest> ConvertGetItemsRequestToUnreal(const PFCatalogGetItemsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogGetItemsRequest> ConvertedType = MakeShared<FPFCatalogGetItemsRequest>(FPFCatalogGetItemsRequest{
		.alternateIds = ConvertPlayfabArrayToUnreal(Datatype->alternateIds, Datatype->alternateIdsCount, ConvertCatalogAlternateIdToUnreal),
		.alternateIdsCount = Datatype->alternateIdsCount,
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.ids = ConvertCharArrayToUnreal(Datatype->ids, Datatype->idsCount),
		.idsCount = Datatype->idsCount
	});

	return ConvertedType;
}

const PFCatalogGetItemsRequest* ConvertGetItemsRequestToPlayfab(TSharedPtr<const FPFCatalogGetItemsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogGetItemsRequest* ConvertedType = new PFCatalogGetItemsRequest{
		.alternateIds = ConvertUnrealArrayToPlayfab(Datatype->alternateIds, ConvertCatalogAlternateIdToPlayfab),
		.alternateIdsCount = (uint32_t)Datatype->alternateIds.Num(),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.ids = ConvertFStringArrayToPlayfab(Datatype->ids),
		.idsCount = (uint32_t)Datatype->ids.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogGetItemsResponse> ConvertGetItemsResponseToUnreal(const PFCatalogGetItemsResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogGetItemsResponse> ConvertedType = MakeShared<FPFCatalogGetItemsResponse>(FPFCatalogGetItemsResponse{
		.items = ConvertPlayfabArrayToUnreal(Datatype->items, Datatype->itemsCount, ConvertCatalogItemToUnreal),
		.itemsCount = Datatype->itemsCount
	});

	return ConvertedType;
}

const PFCatalogGetItemsResponse* ConvertGetItemsResponseToPlayfab(TSharedPtr<const FPFCatalogGetItemsResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogGetItemsResponse* ConvertedType = new PFCatalogGetItemsResponse{
		.items = ConvertUnrealArrayToPlayfab(Datatype->items, ConvertCatalogItemToPlayfab),
		.itemsCount = (uint32_t)Datatype->items.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogPublishDraftItemRequest> ConvertPublishDraftItemRequestToUnreal(const PFCatalogPublishDraftItemRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogPublishDraftItemRequest> ConvertedType = MakeShared<FPFCatalogPublishDraftItemRequest>(FPFCatalogPublishDraftItemRequest{
		.alternateId = ConvertCatalogAlternateIdToUnreal(Datatype->alternateId),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.eTag = Datatype->eTag == nullptr ? FString() : FString(Datatype->eTag),
		.id = Datatype->id == nullptr ? FString() : FString(Datatype->id)
	});

	return ConvertedType;
}

const PFCatalogPublishDraftItemRequest* ConvertPublishDraftItemRequestToPlayfab(TSharedPtr<const FPFCatalogPublishDraftItemRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogPublishDraftItemRequest* ConvertedType = new PFCatalogPublishDraftItemRequest{
		.alternateId = ConvertCatalogAlternateIdToPlayfab(Datatype->alternateId),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.eTag = ConvertFStringToCharPtr(Datatype->eTag),
		.id = ConvertFStringToCharPtr(Datatype->id)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogReportItemRequest> ConvertReportItemRequestToUnreal(const PFCatalogReportItemRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogReportItemRequest> ConvertedType = MakeShared<FPFCatalogReportItemRequest>(FPFCatalogReportItemRequest{
		.alternateId = ConvertCatalogAlternateIdToUnreal(Datatype->alternateId),
		.concernCategory = MakeShared<FPFCatalogConcernCategory>(ConvertConcernCategoryToUnreal(Datatype->concernCategory)),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.id = Datatype->id == nullptr ? FString() : FString(Datatype->id),
		.reason = Datatype->reason == nullptr ? FString() : FString(Datatype->reason)
	});

	return ConvertedType;
}

const PFCatalogReportItemRequest* ConvertReportItemRequestToPlayfab(TSharedPtr<const FPFCatalogReportItemRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogReportItemRequest* ConvertedType = new PFCatalogReportItemRequest{
		.alternateId = ConvertCatalogAlternateIdToPlayfab(Datatype->alternateId),
		.concernCategory = new PFCatalogConcernCategory(ConvertConcernCategoryToPlayfab(Datatype->concernCategory)),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.id = ConvertFStringToCharPtr(Datatype->id),
		.reason = ConvertFStringToCharPtr(Datatype->reason)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogReportItemReviewRequest> ConvertReportItemReviewRequestToUnreal(const PFCatalogReportItemReviewRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogReportItemReviewRequest> ConvertedType = MakeShared<FPFCatalogReportItemReviewRequest>(FPFCatalogReportItemReviewRequest{
		.alternateId = ConvertCatalogAlternateIdToUnreal(Datatype->alternateId),
		.concernCategory = MakeShared<FPFCatalogConcernCategory>(ConvertConcernCategoryToUnreal(Datatype->concernCategory)),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.itemId = Datatype->itemId == nullptr ? FString() : FString(Datatype->itemId),
		.reason = Datatype->reason == nullptr ? FString() : FString(Datatype->reason),
		.reviewId = Datatype->reviewId == nullptr ? FString() : FString(Datatype->reviewId)
	});

	return ConvertedType;
}

const PFCatalogReportItemReviewRequest* ConvertReportItemReviewRequestToPlayfab(TSharedPtr<const FPFCatalogReportItemReviewRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogReportItemReviewRequest* ConvertedType = new PFCatalogReportItemReviewRequest{
		.alternateId = ConvertCatalogAlternateIdToPlayfab(Datatype->alternateId),
		.concernCategory = new PFCatalogConcernCategory(ConvertConcernCategoryToPlayfab(Datatype->concernCategory)),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.itemId = ConvertFStringToCharPtr(Datatype->itemId),
		.reason = ConvertFStringToCharPtr(Datatype->reason),
		.reviewId = ConvertFStringToCharPtr(Datatype->reviewId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogReviewItemRequest> ConvertReviewItemRequestToUnreal(const PFCatalogReviewItemRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogReviewItemRequest> ConvertedType = MakeShared<FPFCatalogReviewItemRequest>(FPFCatalogReviewItemRequest{
		.alternateId = ConvertCatalogAlternateIdToUnreal(Datatype->alternateId),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.id = Datatype->id == nullptr ? FString() : FString(Datatype->id),
		.review = ConvertReviewToUnreal(Datatype->review)
	});

	return ConvertedType;
}

const PFCatalogReviewItemRequest* ConvertReviewItemRequestToPlayfab(TSharedPtr<const FPFCatalogReviewItemRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogReviewItemRequest* ConvertedType = new PFCatalogReviewItemRequest{
		.alternateId = ConvertCatalogAlternateIdToPlayfab(Datatype->alternateId),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.id = ConvertFStringToCharPtr(Datatype->id),
		.review = ConvertReviewToPlayfab(Datatype->review)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogStoreReference> ConvertStoreReferenceToUnreal(const PFCatalogStoreReference* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogStoreReference> ConvertedType = MakeShared<FPFCatalogStoreReference>(FPFCatalogStoreReference{
		.alternateId = ConvertCatalogAlternateIdToUnreal(Datatype->alternateId),
		.id = Datatype->id == nullptr ? FString() : FString(Datatype->id)
	});

	return ConvertedType;
}

const PFCatalogStoreReference* ConvertStoreReferenceToPlayfab(TSharedPtr<const FPFCatalogStoreReference> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogStoreReference* ConvertedType = new PFCatalogStoreReference{
		.alternateId = ConvertCatalogAlternateIdToPlayfab(Datatype->alternateId),
		.id = ConvertFStringToCharPtr(Datatype->id)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogSearchItemsRequest> ConvertSearchItemsRequestToUnreal(const PFCatalogSearchItemsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogSearchItemsRequest> ConvertedType = MakeShared<FPFCatalogSearchItemsRequest>(FPFCatalogSearchItemsRequest{
		.continuationToken = Datatype->continuationToken == nullptr ? FString() : FString(Datatype->continuationToken),
		.count = Datatype->count,
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.filter = Datatype->filter == nullptr ? FString() : FString(Datatype->filter),
		.language = Datatype->language == nullptr ? FString() : FString(Datatype->language),
		.orderBy = Datatype->orderBy == nullptr ? FString() : FString(Datatype->orderBy),
		.search = Datatype->search == nullptr ? FString() : FString(Datatype->search),
		.select = Datatype->select == nullptr ? FString() : FString(Datatype->select),
		.store = ConvertStoreReferenceToUnreal(Datatype->store)
	});

	return ConvertedType;
}

const PFCatalogSearchItemsRequest* ConvertSearchItemsRequestToPlayfab(TSharedPtr<const FPFCatalogSearchItemsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogSearchItemsRequest* ConvertedType = new PFCatalogSearchItemsRequest{
		.continuationToken = ConvertFStringToCharPtr(Datatype->continuationToken),
		.count = Datatype->count,
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.filter = ConvertFStringToCharPtr(Datatype->filter),
		.language = ConvertFStringToCharPtr(Datatype->language),
		.orderBy = ConvertFStringToCharPtr(Datatype->orderBy),
		.search = ConvertFStringToCharPtr(Datatype->search),
		.select = ConvertFStringToCharPtr(Datatype->select),
		.store = ConvertStoreReferenceToPlayfab(Datatype->store)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogSearchItemsResponse> ConvertSearchItemsResponseToUnreal(const PFCatalogSearchItemsResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogSearchItemsResponse> ConvertedType = MakeShared<FPFCatalogSearchItemsResponse>(FPFCatalogSearchItemsResponse{
		.continuationToken = Datatype->continuationToken == nullptr ? FString() : FString(Datatype->continuationToken),
		.items = ConvertPlayfabArrayToUnreal(Datatype->items, Datatype->itemsCount, ConvertCatalogItemToUnreal),
		.itemsCount = Datatype->itemsCount
	});

	return ConvertedType;
}

const PFCatalogSearchItemsResponse* ConvertSearchItemsResponseToPlayfab(TSharedPtr<const FPFCatalogSearchItemsResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogSearchItemsResponse* ConvertedType = new PFCatalogSearchItemsResponse{
		.continuationToken = ConvertFStringToCharPtr(Datatype->continuationToken),
		.items = ConvertUnrealArrayToPlayfab(Datatype->items, ConvertCatalogItemToPlayfab),
		.itemsCount = (uint32_t)Datatype->items.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogSetItemModerationStateRequest> ConvertSetItemModerationStateRequestToUnreal(const PFCatalogSetItemModerationStateRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogSetItemModerationStateRequest> ConvertedType = MakeShared<FPFCatalogSetItemModerationStateRequest>(FPFCatalogSetItemModerationStateRequest{
		.alternateId = ConvertCatalogAlternateIdToUnreal(Datatype->alternateId),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.id = Datatype->id == nullptr ? FString() : FString(Datatype->id),
		.reason = Datatype->reason == nullptr ? FString() : FString(Datatype->reason),
		.status = MakeShared<FPFCatalogModerationStatus>(ConvertModerationStatusToUnreal(Datatype->status))
	});

	return ConvertedType;
}

const PFCatalogSetItemModerationStateRequest* ConvertSetItemModerationStateRequestToPlayfab(TSharedPtr<const FPFCatalogSetItemModerationStateRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogSetItemModerationStateRequest* ConvertedType = new PFCatalogSetItemModerationStateRequest{
		.alternateId = ConvertCatalogAlternateIdToPlayfab(Datatype->alternateId),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.id = ConvertFStringToCharPtr(Datatype->id),
		.reason = ConvertFStringToCharPtr(Datatype->reason),
		.status = new PFCatalogModerationStatus(ConvertModerationStatusToPlayfab(Datatype->status))
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogSubmitItemReviewVoteRequest> ConvertSubmitItemReviewVoteRequestToUnreal(const PFCatalogSubmitItemReviewVoteRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogSubmitItemReviewVoteRequest> ConvertedType = MakeShared<FPFCatalogSubmitItemReviewVoteRequest>(FPFCatalogSubmitItemReviewVoteRequest{
		.alternateId = ConvertCatalogAlternateIdToUnreal(Datatype->alternateId),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.itemId = Datatype->itemId == nullptr ? FString() : FString(Datatype->itemId),
		.reviewId = Datatype->reviewId == nullptr ? FString() : FString(Datatype->reviewId),
		.vote = MakeShared<FPFCatalogHelpfulnessVote>(ConvertHelpfulnessVoteToUnreal(Datatype->vote))
	});

	return ConvertedType;
}

const PFCatalogSubmitItemReviewVoteRequest* ConvertSubmitItemReviewVoteRequestToPlayfab(TSharedPtr<const FPFCatalogSubmitItemReviewVoteRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogSubmitItemReviewVoteRequest* ConvertedType = new PFCatalogSubmitItemReviewVoteRequest{
		.alternateId = ConvertCatalogAlternateIdToPlayfab(Datatype->alternateId),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.itemId = ConvertFStringToCharPtr(Datatype->itemId),
		.reviewId = ConvertFStringToCharPtr(Datatype->reviewId),
		.vote = new PFCatalogHelpfulnessVote(ConvertHelpfulnessVoteToPlayfab(Datatype->vote))
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogReviewTakedown> ConvertReviewTakedownToUnreal(const PFCatalogReviewTakedown* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogReviewTakedown> ConvertedType = MakeShared<FPFCatalogReviewTakedown>(FPFCatalogReviewTakedown{
		.alternateId = ConvertCatalogAlternateIdToUnreal(Datatype->alternateId),
		.itemId = Datatype->itemId == nullptr ? FString() : FString(Datatype->itemId),
		.reviewId = Datatype->reviewId == nullptr ? FString() : FString(Datatype->reviewId)
	});

	return ConvertedType;
}

const PFCatalogReviewTakedown* ConvertReviewTakedownToPlayfab(TSharedPtr<const FPFCatalogReviewTakedown> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogReviewTakedown* ConvertedType = new PFCatalogReviewTakedown{
		.alternateId = ConvertCatalogAlternateIdToPlayfab(Datatype->alternateId),
		.itemId = ConvertFStringToCharPtr(Datatype->itemId),
		.reviewId = ConvertFStringToCharPtr(Datatype->reviewId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogTakedownItemReviewsRequest> ConvertTakedownItemReviewsRequestToUnreal(const PFCatalogTakedownItemReviewsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogTakedownItemReviewsRequest> ConvertedType = MakeShared<FPFCatalogTakedownItemReviewsRequest>(FPFCatalogTakedownItemReviewsRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.reviews = ConvertPlayfabArrayToUnreal(Datatype->reviews, Datatype->reviewsCount, ConvertReviewTakedownToUnreal),
		.reviewsCount = Datatype->reviewsCount
	});

	return ConvertedType;
}

const PFCatalogTakedownItemReviewsRequest* ConvertTakedownItemReviewsRequestToPlayfab(TSharedPtr<const FPFCatalogTakedownItemReviewsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogTakedownItemReviewsRequest* ConvertedType = new PFCatalogTakedownItemReviewsRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.reviews = ConvertUnrealArrayToPlayfab(Datatype->reviews, ConvertReviewTakedownToPlayfab),
		.reviewsCount = (uint32_t)Datatype->reviews.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogUpdateCatalogConfigRequest> ConvertUpdateCatalogConfigRequestToUnreal(const PFCatalogUpdateCatalogConfigRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogUpdateCatalogConfigRequest> ConvertedType = MakeShared<FPFCatalogUpdateCatalogConfigRequest>(FPFCatalogUpdateCatalogConfigRequest{
		.config = ConvertCatalogConfigToUnreal(Datatype->config),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount
	});

	return ConvertedType;
}

const PFCatalogUpdateCatalogConfigRequest* ConvertUpdateCatalogConfigRequestToPlayfab(TSharedPtr<const FPFCatalogUpdateCatalogConfigRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogUpdateCatalogConfigRequest* ConvertedType = new PFCatalogUpdateCatalogConfigRequest{
		.config = ConvertCatalogConfigToPlayfab(Datatype->config),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogUpdateDraftItemRequest> ConvertUpdateDraftItemRequestToUnreal(const PFCatalogUpdateDraftItemRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogUpdateDraftItemRequest> ConvertedType = MakeShared<FPFCatalogUpdateDraftItemRequest>(FPFCatalogUpdateDraftItemRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.item = ConvertCatalogItemToUnreal(Datatype->item),
		.publish = Datatype->publish
	});

	return ConvertedType;
}

const PFCatalogUpdateDraftItemRequest* ConvertUpdateDraftItemRequestToPlayfab(TSharedPtr<const FPFCatalogUpdateDraftItemRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogUpdateDraftItemRequest* ConvertedType = new PFCatalogUpdateDraftItemRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.item = ConvertCatalogItemToPlayfab(Datatype->item),
		.publish = Datatype->publish
	};

	return ConvertedType;
}

TSharedPtr<const FPFCatalogUpdateDraftItemResponse> ConvertUpdateDraftItemResponseToUnreal(const PFCatalogUpdateDraftItemResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCatalogUpdateDraftItemResponse> ConvertedType = MakeShared<FPFCatalogUpdateDraftItemResponse>(FPFCatalogUpdateDraftItemResponse{
		.item = ConvertCatalogItemToUnreal(Datatype->item)
	});

	return ConvertedType;
}

const PFCatalogUpdateDraftItemResponse* ConvertUpdateDraftItemResponseToPlayfab(TSharedPtr<const FPFCatalogUpdateDraftItemResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCatalogUpdateDraftItemResponse* ConvertedType = new PFCatalogUpdateDraftItemResponse{
		.item = ConvertCatalogItemToPlayfab(Datatype->item)
	};

	return ConvertedType;
}
