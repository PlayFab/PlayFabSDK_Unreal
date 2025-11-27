// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFAccountManagementTypeConverters.h"

const FPFAccountManagementUserFamilyType ConvertUserFamilyTypeToUnreal(const PFAccountManagementUserFamilyType* enumVal)
{
	if (enumVal == nullptr) {
		return FPFAccountManagementUserFamilyType::None;
	}

	switch(*enumVal)
	{
	case PFAccountManagementUserFamilyType::None: return FPFAccountManagementUserFamilyType::None;
	case PFAccountManagementUserFamilyType::Xbox: return FPFAccountManagementUserFamilyType::Xbox;
	case PFAccountManagementUserFamilyType::Steam: return FPFAccountManagementUserFamilyType::Steam;
	default:
	return FPFAccountManagementUserFamilyType::None;
	}
}

const PFAccountManagementUserFamilyType ConvertUserFamilyTypeToPlayfab(TSharedPtr<const FPFAccountManagementUserFamilyType> enumVal)
{
	if (!enumVal.IsValid()) {
		return PFAccountManagementUserFamilyType::None;
	}

	switch(*enumVal)
	{
	case FPFAccountManagementUserFamilyType::None: return PFAccountManagementUserFamilyType::None;
	case FPFAccountManagementUserFamilyType::Xbox: return PFAccountManagementUserFamilyType::Xbox;
	case FPFAccountManagementUserFamilyType::Steam: return PFAccountManagementUserFamilyType::Steam;
	default:
	return PFAccountManagementUserFamilyType::None;
	}
}

TSharedPtr<const FPFAccountManagementAddOrUpdateContactEmailRequest> ConvertAddOrUpdateContactEmailRequestToUnreal(const PFAccountManagementAddOrUpdateContactEmailRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementAddOrUpdateContactEmailRequest> ConvertedType = MakeShared<FPFAccountManagementAddOrUpdateContactEmailRequest>(FPFAccountManagementAddOrUpdateContactEmailRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.emailAddress = Datatype->emailAddress == nullptr ? FString() : FString(Datatype->emailAddress)
	});

	return ConvertedType;
}

const PFAccountManagementAddOrUpdateContactEmailRequest* ConvertAddOrUpdateContactEmailRequestToPlayfab(TSharedPtr<const FPFAccountManagementAddOrUpdateContactEmailRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementAddOrUpdateContactEmailRequest* ConvertedType = new PFAccountManagementAddOrUpdateContactEmailRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.emailAddress = ConvertFStringToCharPtr(Datatype->emailAddress)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementAddUsernamePasswordRequest> ConvertAddUsernamePasswordRequestToUnreal(const PFAccountManagementAddUsernamePasswordRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementAddUsernamePasswordRequest> ConvertedType = MakeShared<FPFAccountManagementAddUsernamePasswordRequest>(FPFAccountManagementAddUsernamePasswordRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.email = Datatype->email == nullptr ? FString() : FString(Datatype->email),
		.password = Datatype->password == nullptr ? FString() : FString(Datatype->password),
		.username = Datatype->username == nullptr ? FString() : FString(Datatype->username)
	});

	return ConvertedType;
}

const PFAccountManagementAddUsernamePasswordRequest* ConvertAddUsernamePasswordRequestToPlayfab(TSharedPtr<const FPFAccountManagementAddUsernamePasswordRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementAddUsernamePasswordRequest* ConvertedType = new PFAccountManagementAddUsernamePasswordRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.email = ConvertFStringToCharPtr(Datatype->email),
		.password = ConvertFStringToCharPtr(Datatype->password),
		.username = ConvertFStringToCharPtr(Datatype->username)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementAddUsernamePasswordResult> ConvertAddUsernamePasswordResultToUnreal(const PFAccountManagementAddUsernamePasswordResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementAddUsernamePasswordResult> ConvertedType = MakeShared<FPFAccountManagementAddUsernamePasswordResult>(FPFAccountManagementAddUsernamePasswordResult{
		.username = Datatype->username == nullptr ? FString() : FString(Datatype->username)
	});

	return ConvertedType;
}

const PFAccountManagementAddUsernamePasswordResult* ConvertAddUsernamePasswordResultToPlayfab(TSharedPtr<const FPFAccountManagementAddUsernamePasswordResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementAddUsernamePasswordResult* ConvertedType = new PFAccountManagementAddUsernamePasswordResult{
		.username = ConvertFStringToCharPtr(Datatype->username)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetAccountInfoRequest> ConvertGetAccountInfoRequestToUnreal(const PFAccountManagementGetAccountInfoRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetAccountInfoRequest> ConvertedType = MakeShared<FPFAccountManagementGetAccountInfoRequest>(FPFAccountManagementGetAccountInfoRequest{
		.email = Datatype->email == nullptr ? FString() : FString(Datatype->email),
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId),
		.titleDisplayName = Datatype->titleDisplayName == nullptr ? FString() : FString(Datatype->titleDisplayName),
		.username = Datatype->username == nullptr ? FString() : FString(Datatype->username)
	});

	return ConvertedType;
}

const PFAccountManagementGetAccountInfoRequest* ConvertGetAccountInfoRequestToPlayfab(TSharedPtr<const FPFAccountManagementGetAccountInfoRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetAccountInfoRequest* ConvertedType = new PFAccountManagementGetAccountInfoRequest{
		.email = ConvertFStringToCharPtr(Datatype->email),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId),
		.titleDisplayName = ConvertFStringToCharPtr(Datatype->titleDisplayName),
		.username = ConvertFStringToCharPtr(Datatype->username)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetAccountInfoResult> ConvertGetAccountInfoResultToUnreal(const PFAccountManagementGetAccountInfoResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetAccountInfoResult> ConvertedType = MakeShared<FPFAccountManagementGetAccountInfoResult>(FPFAccountManagementGetAccountInfoResult{
		.accountInfo = ConvertUserAccountInfoToUnreal(Datatype->accountInfo)
	});

	return ConvertedType;
}

const PFAccountManagementGetAccountInfoResult* ConvertGetAccountInfoResultToPlayfab(TSharedPtr<const FPFAccountManagementGetAccountInfoResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetAccountInfoResult* ConvertedType = new PFAccountManagementGetAccountInfoResult{
		.accountInfo = ConvertUserAccountInfoToPlayfab(Datatype->accountInfo)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetPlayerCombinedInfoRequest> ConvertGetPlayerCombinedInfoRequestToUnreal(const PFAccountManagementGetPlayerCombinedInfoRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetPlayerCombinedInfoRequest> ConvertedType = MakeShared<FPFAccountManagementGetPlayerCombinedInfoRequest>(FPFAccountManagementGetPlayerCombinedInfoRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToUnreal(Datatype->infoRequestParameters),
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId)
	});

	return ConvertedType;
}

const PFAccountManagementGetPlayerCombinedInfoRequest* ConvertGetPlayerCombinedInfoRequestToPlayfab(TSharedPtr<const FPFAccountManagementGetPlayerCombinedInfoRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetPlayerCombinedInfoRequest* ConvertedType = new PFAccountManagementGetPlayerCombinedInfoRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(Datatype->infoRequestParameters),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetPlayerCombinedInfoResult> ConvertGetPlayerCombinedInfoResultToUnreal(const PFAccountManagementGetPlayerCombinedInfoResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetPlayerCombinedInfoResult> ConvertedType = MakeShared<FPFAccountManagementGetPlayerCombinedInfoResult>(FPFAccountManagementGetPlayerCombinedInfoResult{
		.infoResultPayload = ConvertGetPlayerCombinedInfoResultPayloadToUnreal(Datatype->infoResultPayload),
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId)
	});

	return ConvertedType;
}

const PFAccountManagementGetPlayerCombinedInfoResult* ConvertGetPlayerCombinedInfoResultToPlayfab(TSharedPtr<const FPFAccountManagementGetPlayerCombinedInfoResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetPlayerCombinedInfoResult* ConvertedType = new PFAccountManagementGetPlayerCombinedInfoResult{
		.infoResultPayload = ConvertGetPlayerCombinedInfoResultPayloadToPlayfab(Datatype->infoResultPayload),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetPlayerProfileRequest> ConvertGetPlayerProfileRequestToUnreal(const PFAccountManagementGetPlayerProfileRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetPlayerProfileRequest> ConvertedType = MakeShared<FPFAccountManagementGetPlayerProfileRequest>(FPFAccountManagementGetPlayerProfileRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId),
		.profileConstraints = ConvertPlayerProfileViewConstraintsToUnreal(Datatype->profileConstraints)
	});

	return ConvertedType;
}

const PFAccountManagementGetPlayerProfileRequest* ConvertGetPlayerProfileRequestToPlayfab(TSharedPtr<const FPFAccountManagementGetPlayerProfileRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetPlayerProfileRequest* ConvertedType = new PFAccountManagementGetPlayerProfileRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId),
		.profileConstraints = ConvertPlayerProfileViewConstraintsToPlayfab(Datatype->profileConstraints)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetPlayerProfileResult> ConvertGetPlayerProfileResultToUnreal(const PFAccountManagementGetPlayerProfileResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetPlayerProfileResult> ConvertedType = MakeShared<FPFAccountManagementGetPlayerProfileResult>(FPFAccountManagementGetPlayerProfileResult{
		.playerProfile = ConvertPlayerProfileModelToUnreal(Datatype->playerProfile)
	});

	return ConvertedType;
}

const PFAccountManagementGetPlayerProfileResult* ConvertGetPlayerProfileResultToPlayfab(TSharedPtr<const FPFAccountManagementGetPlayerProfileResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetPlayerProfileResult* ConvertedType = new PFAccountManagementGetPlayerProfileResult{
		.playerProfile = ConvertPlayerProfileModelToPlayfab(Datatype->playerProfile)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsRequest> ConvertGetPlayFabIDsFromBattleNetAccountIdsRequestToUnreal(const PFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsRequest> ConvertedType = MakeShared<FPFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsRequest>(FPFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsRequest{
		.battleNetAccountIds = ConvertCharArrayToUnreal(Datatype->battleNetAccountIds, Datatype->battleNetAccountIdsCount),
		.battleNetAccountIdsCount = Datatype->battleNetAccountIdsCount
	});

	return ConvertedType;
}

const PFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsRequest* ConvertGetPlayFabIDsFromBattleNetAccountIdsRequestToPlayfab(TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsRequest* ConvertedType = new PFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsRequest{
		.battleNetAccountIds = ConvertFStringArrayToPlayfab(Datatype->battleNetAccountIds),
		.battleNetAccountIdsCount = (uint32_t)Datatype->battleNetAccountIds.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementBattleNetAccountPlayFabIdPair> ConvertBattleNetAccountPlayFabIdPairToUnreal(const PFAccountManagementBattleNetAccountPlayFabIdPair* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementBattleNetAccountPlayFabIdPair> ConvertedType = MakeShared<FPFAccountManagementBattleNetAccountPlayFabIdPair>(FPFAccountManagementBattleNetAccountPlayFabIdPair{
		.battleNetAccountId = Datatype->battleNetAccountId == nullptr ? FString() : FString(Datatype->battleNetAccountId),
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId)
	});

	return ConvertedType;
}

const PFAccountManagementBattleNetAccountPlayFabIdPair* ConvertBattleNetAccountPlayFabIdPairToPlayfab(TSharedPtr<const FPFAccountManagementBattleNetAccountPlayFabIdPair> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementBattleNetAccountPlayFabIdPair* ConvertedType = new PFAccountManagementBattleNetAccountPlayFabIdPair{
		.battleNetAccountId = ConvertFStringToCharPtr(Datatype->battleNetAccountId),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsResult> ConvertGetPlayFabIDsFromBattleNetAccountIdsResultToUnreal(const PFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsResult> ConvertedType = MakeShared<FPFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsResult>(FPFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsResult{
		.data = ConvertPlayfabArrayToUnreal<PFAccountManagementBattleNetAccountPlayFabIdPair, FPFAccountManagementBattleNetAccountPlayFabIdPair>(Datatype->data, Datatype->dataCount, ConvertBattleNetAccountPlayFabIdPairToUnreal),
		.dataCount = Datatype->dataCount
	});

	return ConvertedType;
}

const PFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsResult* ConvertGetPlayFabIDsFromBattleNetAccountIdsResultToPlayfab(TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsResult* ConvertedType = new PFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsResult{
		.data = ConvertUnrealArrayToPlayfab<PFAccountManagementBattleNetAccountPlayFabIdPair, FPFAccountManagementBattleNetAccountPlayFabIdPair>(Datatype->data, ConvertBattleNetAccountPlayFabIdPairToPlayfab),
		.dataCount = (uint32_t)Datatype->data.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromFacebookIDsRequest> ConvertGetPlayFabIDsFromFacebookIDsRequestToUnreal(const PFAccountManagementGetPlayFabIDsFromFacebookIDsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromFacebookIDsRequest> ConvertedType = MakeShared<FPFAccountManagementGetPlayFabIDsFromFacebookIDsRequest>(FPFAccountManagementGetPlayFabIDsFromFacebookIDsRequest{
		.facebookIDs = ConvertCharArrayToUnreal(Datatype->facebookIDs, Datatype->facebookIDsCount),
		.facebookIDsCount = Datatype->facebookIDsCount
	});

	return ConvertedType;
}

const PFAccountManagementGetPlayFabIDsFromFacebookIDsRequest* ConvertGetPlayFabIDsFromFacebookIDsRequestToPlayfab(TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromFacebookIDsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetPlayFabIDsFromFacebookIDsRequest* ConvertedType = new PFAccountManagementGetPlayFabIDsFromFacebookIDsRequest{
		.facebookIDs = ConvertFStringArrayToPlayfab(Datatype->facebookIDs),
		.facebookIDsCount = (uint32_t)Datatype->facebookIDs.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementFacebookPlayFabIdPair> ConvertFacebookPlayFabIdPairToUnreal(const PFAccountManagementFacebookPlayFabIdPair* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementFacebookPlayFabIdPair> ConvertedType = MakeShared<FPFAccountManagementFacebookPlayFabIdPair>(FPFAccountManagementFacebookPlayFabIdPair{
		.facebookId = Datatype->facebookId == nullptr ? FString() : FString(Datatype->facebookId),
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId)
	});

	return ConvertedType;
}

const PFAccountManagementFacebookPlayFabIdPair* ConvertFacebookPlayFabIdPairToPlayfab(TSharedPtr<const FPFAccountManagementFacebookPlayFabIdPair> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementFacebookPlayFabIdPair* ConvertedType = new PFAccountManagementFacebookPlayFabIdPair{
		.facebookId = ConvertFStringToCharPtr(Datatype->facebookId),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromFacebookIDsResult> ConvertGetPlayFabIDsFromFacebookIDsResultToUnreal(const PFAccountManagementGetPlayFabIDsFromFacebookIDsResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromFacebookIDsResult> ConvertedType = MakeShared<FPFAccountManagementGetPlayFabIDsFromFacebookIDsResult>(FPFAccountManagementGetPlayFabIDsFromFacebookIDsResult{
		.data = ConvertPlayfabArrayToUnreal<PFAccountManagementFacebookPlayFabIdPair, FPFAccountManagementFacebookPlayFabIdPair>(Datatype->data, Datatype->dataCount, ConvertFacebookPlayFabIdPairToUnreal),
		.dataCount = Datatype->dataCount
	});

	return ConvertedType;
}

const PFAccountManagementGetPlayFabIDsFromFacebookIDsResult* ConvertGetPlayFabIDsFromFacebookIDsResultToPlayfab(TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromFacebookIDsResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetPlayFabIDsFromFacebookIDsResult* ConvertedType = new PFAccountManagementGetPlayFabIDsFromFacebookIDsResult{
		.data = ConvertUnrealArrayToPlayfab<PFAccountManagementFacebookPlayFabIdPair, FPFAccountManagementFacebookPlayFabIdPair>(Datatype->data, ConvertFacebookPlayFabIdPairToPlayfab),
		.dataCount = (uint32_t)Datatype->data.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsRequest> ConvertGetPlayFabIDsFromFacebookInstantGamesIdsRequestToUnreal(const PFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsRequest> ConvertedType = MakeShared<FPFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsRequest>(FPFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsRequest{
		.facebookInstantGamesIds = ConvertCharArrayToUnreal(Datatype->facebookInstantGamesIds, Datatype->facebookInstantGamesIdsCount),
		.facebookInstantGamesIdsCount = Datatype->facebookInstantGamesIdsCount
	});

	return ConvertedType;
}

const PFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsRequest* ConvertGetPlayFabIDsFromFacebookInstantGamesIdsRequestToPlayfab(TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsRequest* ConvertedType = new PFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsRequest{
		.facebookInstantGamesIds = ConvertFStringArrayToPlayfab(Datatype->facebookInstantGamesIds),
		.facebookInstantGamesIdsCount = (uint32_t)Datatype->facebookInstantGamesIds.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementFacebookInstantGamesPlayFabIdPair> ConvertFacebookInstantGamesPlayFabIdPairToUnreal(const PFAccountManagementFacebookInstantGamesPlayFabIdPair* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementFacebookInstantGamesPlayFabIdPair> ConvertedType = MakeShared<FPFAccountManagementFacebookInstantGamesPlayFabIdPair>(FPFAccountManagementFacebookInstantGamesPlayFabIdPair{
		.facebookInstantGamesId = Datatype->facebookInstantGamesId == nullptr ? FString() : FString(Datatype->facebookInstantGamesId),
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId)
	});

	return ConvertedType;
}

const PFAccountManagementFacebookInstantGamesPlayFabIdPair* ConvertFacebookInstantGamesPlayFabIdPairToPlayfab(TSharedPtr<const FPFAccountManagementFacebookInstantGamesPlayFabIdPair> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementFacebookInstantGamesPlayFabIdPair* ConvertedType = new PFAccountManagementFacebookInstantGamesPlayFabIdPair{
		.facebookInstantGamesId = ConvertFStringToCharPtr(Datatype->facebookInstantGamesId),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsResult> ConvertGetPlayFabIDsFromFacebookInstantGamesIdsResultToUnreal(const PFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsResult> ConvertedType = MakeShared<FPFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsResult>(FPFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsResult{
		.data = ConvertPlayfabArrayToUnreal<PFAccountManagementFacebookInstantGamesPlayFabIdPair, FPFAccountManagementFacebookInstantGamesPlayFabIdPair>(Datatype->data, Datatype->dataCount, ConvertFacebookInstantGamesPlayFabIdPairToUnreal),
		.dataCount = Datatype->dataCount
	});

	return ConvertedType;
}

const PFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsResult* ConvertGetPlayFabIDsFromFacebookInstantGamesIdsResultToPlayfab(TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsResult* ConvertedType = new PFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsResult{
		.data = ConvertUnrealArrayToPlayfab<PFAccountManagementFacebookInstantGamesPlayFabIdPair, FPFAccountManagementFacebookInstantGamesPlayFabIdPair>(Datatype->data, ConvertFacebookInstantGamesPlayFabIdPairToPlayfab),
		.dataCount = (uint32_t)Datatype->data.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromGameCenterIDsRequest> ConvertGetPlayFabIDsFromGameCenterIDsRequestToUnreal(const PFAccountManagementGetPlayFabIDsFromGameCenterIDsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromGameCenterIDsRequest> ConvertedType = MakeShared<FPFAccountManagementGetPlayFabIDsFromGameCenterIDsRequest>(FPFAccountManagementGetPlayFabIDsFromGameCenterIDsRequest{
		.gameCenterIDs = ConvertCharArrayToUnreal(Datatype->gameCenterIDs, Datatype->gameCenterIDsCount),
		.gameCenterIDsCount = Datatype->gameCenterIDsCount
	});

	return ConvertedType;
}

const PFAccountManagementGetPlayFabIDsFromGameCenterIDsRequest* ConvertGetPlayFabIDsFromGameCenterIDsRequestToPlayfab(TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromGameCenterIDsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetPlayFabIDsFromGameCenterIDsRequest* ConvertedType = new PFAccountManagementGetPlayFabIDsFromGameCenterIDsRequest{
		.gameCenterIDs = ConvertFStringArrayToPlayfab(Datatype->gameCenterIDs),
		.gameCenterIDsCount = (uint32_t)Datatype->gameCenterIDs.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGameCenterPlayFabIdPair> ConvertGameCenterPlayFabIdPairToUnreal(const PFAccountManagementGameCenterPlayFabIdPair* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGameCenterPlayFabIdPair> ConvertedType = MakeShared<FPFAccountManagementGameCenterPlayFabIdPair>(FPFAccountManagementGameCenterPlayFabIdPair{
		.gameCenterId = Datatype->gameCenterId == nullptr ? FString() : FString(Datatype->gameCenterId),
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId)
	});

	return ConvertedType;
}

const PFAccountManagementGameCenterPlayFabIdPair* ConvertGameCenterPlayFabIdPairToPlayfab(TSharedPtr<const FPFAccountManagementGameCenterPlayFabIdPair> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGameCenterPlayFabIdPair* ConvertedType = new PFAccountManagementGameCenterPlayFabIdPair{
		.gameCenterId = ConvertFStringToCharPtr(Datatype->gameCenterId),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromGameCenterIDsResult> ConvertGetPlayFabIDsFromGameCenterIDsResultToUnreal(const PFAccountManagementGetPlayFabIDsFromGameCenterIDsResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromGameCenterIDsResult> ConvertedType = MakeShared<FPFAccountManagementGetPlayFabIDsFromGameCenterIDsResult>(FPFAccountManagementGetPlayFabIDsFromGameCenterIDsResult{
		.data = ConvertPlayfabArrayToUnreal<PFAccountManagementGameCenterPlayFabIdPair, FPFAccountManagementGameCenterPlayFabIdPair>(Datatype->data, Datatype->dataCount, ConvertGameCenterPlayFabIdPairToUnreal),
		.dataCount = Datatype->dataCount
	});

	return ConvertedType;
}

const PFAccountManagementGetPlayFabIDsFromGameCenterIDsResult* ConvertGetPlayFabIDsFromGameCenterIDsResultToPlayfab(TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromGameCenterIDsResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetPlayFabIDsFromGameCenterIDsResult* ConvertedType = new PFAccountManagementGetPlayFabIDsFromGameCenterIDsResult{
		.data = ConvertUnrealArrayToPlayfab<PFAccountManagementGameCenterPlayFabIdPair, FPFAccountManagementGameCenterPlayFabIdPair>(Datatype->data, ConvertGameCenterPlayFabIdPairToPlayfab),
		.dataCount = (uint32_t)Datatype->data.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromGoogleIDsRequest> ConvertGetPlayFabIDsFromGoogleIDsRequestToUnreal(const PFAccountManagementGetPlayFabIDsFromGoogleIDsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromGoogleIDsRequest> ConvertedType = MakeShared<FPFAccountManagementGetPlayFabIDsFromGoogleIDsRequest>(FPFAccountManagementGetPlayFabIDsFromGoogleIDsRequest{
		.googleIDs = ConvertCharArrayToUnreal(Datatype->googleIDs, Datatype->googleIDsCount),
		.googleIDsCount = Datatype->googleIDsCount
	});

	return ConvertedType;
}

const PFAccountManagementGetPlayFabIDsFromGoogleIDsRequest* ConvertGetPlayFabIDsFromGoogleIDsRequestToPlayfab(TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromGoogleIDsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetPlayFabIDsFromGoogleIDsRequest* ConvertedType = new PFAccountManagementGetPlayFabIDsFromGoogleIDsRequest{
		.googleIDs = ConvertFStringArrayToPlayfab(Datatype->googleIDs),
		.googleIDsCount = (uint32_t)Datatype->googleIDs.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGooglePlayFabIdPair> ConvertGooglePlayFabIdPairToUnreal(const PFAccountManagementGooglePlayFabIdPair* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGooglePlayFabIdPair> ConvertedType = MakeShared<FPFAccountManagementGooglePlayFabIdPair>(FPFAccountManagementGooglePlayFabIdPair{
		.googleId = Datatype->googleId == nullptr ? FString() : FString(Datatype->googleId),
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId)
	});

	return ConvertedType;
}

const PFAccountManagementGooglePlayFabIdPair* ConvertGooglePlayFabIdPairToPlayfab(TSharedPtr<const FPFAccountManagementGooglePlayFabIdPair> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGooglePlayFabIdPair* ConvertedType = new PFAccountManagementGooglePlayFabIdPair{
		.googleId = ConvertFStringToCharPtr(Datatype->googleId),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromGoogleIDsResult> ConvertGetPlayFabIDsFromGoogleIDsResultToUnreal(const PFAccountManagementGetPlayFabIDsFromGoogleIDsResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromGoogleIDsResult> ConvertedType = MakeShared<FPFAccountManagementGetPlayFabIDsFromGoogleIDsResult>(FPFAccountManagementGetPlayFabIDsFromGoogleIDsResult{
		.data = ConvertPlayfabArrayToUnreal<PFAccountManagementGooglePlayFabIdPair, FPFAccountManagementGooglePlayFabIdPair>(Datatype->data, Datatype->dataCount, ConvertGooglePlayFabIdPairToUnreal),
		.dataCount = Datatype->dataCount
	});

	return ConvertedType;
}

const PFAccountManagementGetPlayFabIDsFromGoogleIDsResult* ConvertGetPlayFabIDsFromGoogleIDsResultToPlayfab(TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromGoogleIDsResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetPlayFabIDsFromGoogleIDsResult* ConvertedType = new PFAccountManagementGetPlayFabIDsFromGoogleIDsResult{
		.data = ConvertUnrealArrayToPlayfab<PFAccountManagementGooglePlayFabIdPair, FPFAccountManagementGooglePlayFabIdPair>(Datatype->data, ConvertGooglePlayFabIdPairToPlayfab),
		.dataCount = (uint32_t)Datatype->data.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromGooglePlayGamesPlayerIDsRequest> ConvertGetPlayFabIDsFromGooglePlayGamesPlayerIDsRequestToUnreal(const PFAccountManagementGetPlayFabIDsFromGooglePlayGamesPlayerIDsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromGooglePlayGamesPlayerIDsRequest> ConvertedType = MakeShared<FPFAccountManagementGetPlayFabIDsFromGooglePlayGamesPlayerIDsRequest>(FPFAccountManagementGetPlayFabIDsFromGooglePlayGamesPlayerIDsRequest{
		.googlePlayGamesPlayerIDs = ConvertCharArrayToUnreal(Datatype->googlePlayGamesPlayerIDs, Datatype->googlePlayGamesPlayerIDsCount),
		.googlePlayGamesPlayerIDsCount = Datatype->googlePlayGamesPlayerIDsCount
	});

	return ConvertedType;
}

const PFAccountManagementGetPlayFabIDsFromGooglePlayGamesPlayerIDsRequest* ConvertGetPlayFabIDsFromGooglePlayGamesPlayerIDsRequestToPlayfab(TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromGooglePlayGamesPlayerIDsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetPlayFabIDsFromGooglePlayGamesPlayerIDsRequest* ConvertedType = new PFAccountManagementGetPlayFabIDsFromGooglePlayGamesPlayerIDsRequest{
		.googlePlayGamesPlayerIDs = ConvertFStringArrayToPlayfab(Datatype->googlePlayGamesPlayerIDs),
		.googlePlayGamesPlayerIDsCount = (uint32_t)Datatype->googlePlayGamesPlayerIDs.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGooglePlayGamesPlayFabIdPair> ConvertGooglePlayGamesPlayFabIdPairToUnreal(const PFAccountManagementGooglePlayGamesPlayFabIdPair* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGooglePlayGamesPlayFabIdPair> ConvertedType = MakeShared<FPFAccountManagementGooglePlayGamesPlayFabIdPair>(FPFAccountManagementGooglePlayGamesPlayFabIdPair{
		.googlePlayGamesPlayerId = Datatype->googlePlayGamesPlayerId == nullptr ? FString() : FString(Datatype->googlePlayGamesPlayerId),
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId)
	});

	return ConvertedType;
}

const PFAccountManagementGooglePlayGamesPlayFabIdPair* ConvertGooglePlayGamesPlayFabIdPairToPlayfab(TSharedPtr<const FPFAccountManagementGooglePlayGamesPlayFabIdPair> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGooglePlayGamesPlayFabIdPair* ConvertedType = new PFAccountManagementGooglePlayGamesPlayFabIdPair{
		.googlePlayGamesPlayerId = ConvertFStringToCharPtr(Datatype->googlePlayGamesPlayerId),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromGooglePlayGamesPlayerIDsResult> ConvertGetPlayFabIDsFromGooglePlayGamesPlayerIDsResultToUnreal(const PFAccountManagementGetPlayFabIDsFromGooglePlayGamesPlayerIDsResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromGooglePlayGamesPlayerIDsResult> ConvertedType = MakeShared<FPFAccountManagementGetPlayFabIDsFromGooglePlayGamesPlayerIDsResult>(FPFAccountManagementGetPlayFabIDsFromGooglePlayGamesPlayerIDsResult{
		.data = ConvertPlayfabArrayToUnreal<PFAccountManagementGooglePlayGamesPlayFabIdPair, FPFAccountManagementGooglePlayGamesPlayFabIdPair>(Datatype->data, Datatype->dataCount, ConvertGooglePlayGamesPlayFabIdPairToUnreal),
		.dataCount = Datatype->dataCount
	});

	return ConvertedType;
}

const PFAccountManagementGetPlayFabIDsFromGooglePlayGamesPlayerIDsResult* ConvertGetPlayFabIDsFromGooglePlayGamesPlayerIDsResultToPlayfab(TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromGooglePlayGamesPlayerIDsResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetPlayFabIDsFromGooglePlayGamesPlayerIDsResult* ConvertedType = new PFAccountManagementGetPlayFabIDsFromGooglePlayGamesPlayerIDsResult{
		.data = ConvertUnrealArrayToPlayfab<PFAccountManagementGooglePlayGamesPlayFabIdPair, FPFAccountManagementGooglePlayGamesPlayFabIdPair>(Datatype->data, ConvertGooglePlayGamesPlayFabIdPairToPlayfab),
		.dataCount = (uint32_t)Datatype->data.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromKongregateIDsRequest> ConvertGetPlayFabIDsFromKongregateIDsRequestToUnreal(const PFAccountManagementGetPlayFabIDsFromKongregateIDsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromKongregateIDsRequest> ConvertedType = MakeShared<FPFAccountManagementGetPlayFabIDsFromKongregateIDsRequest>(FPFAccountManagementGetPlayFabIDsFromKongregateIDsRequest{
		.kongregateIDs = ConvertCharArrayToUnreal(Datatype->kongregateIDs, Datatype->kongregateIDsCount),
		.kongregateIDsCount = Datatype->kongregateIDsCount
	});

	return ConvertedType;
}

const PFAccountManagementGetPlayFabIDsFromKongregateIDsRequest* ConvertGetPlayFabIDsFromKongregateIDsRequestToPlayfab(TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromKongregateIDsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetPlayFabIDsFromKongregateIDsRequest* ConvertedType = new PFAccountManagementGetPlayFabIDsFromKongregateIDsRequest{
		.kongregateIDs = ConvertFStringArrayToPlayfab(Datatype->kongregateIDs),
		.kongregateIDsCount = (uint32_t)Datatype->kongregateIDs.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementKongregatePlayFabIdPair> ConvertKongregatePlayFabIdPairToUnreal(const PFAccountManagementKongregatePlayFabIdPair* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementKongregatePlayFabIdPair> ConvertedType = MakeShared<FPFAccountManagementKongregatePlayFabIdPair>(FPFAccountManagementKongregatePlayFabIdPair{
		.kongregateId = Datatype->kongregateId == nullptr ? FString() : FString(Datatype->kongregateId),
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId)
	});

	return ConvertedType;
}

const PFAccountManagementKongregatePlayFabIdPair* ConvertKongregatePlayFabIdPairToPlayfab(TSharedPtr<const FPFAccountManagementKongregatePlayFabIdPair> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementKongregatePlayFabIdPair* ConvertedType = new PFAccountManagementKongregatePlayFabIdPair{
		.kongregateId = ConvertFStringToCharPtr(Datatype->kongregateId),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromKongregateIDsResult> ConvertGetPlayFabIDsFromKongregateIDsResultToUnreal(const PFAccountManagementGetPlayFabIDsFromKongregateIDsResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromKongregateIDsResult> ConvertedType = MakeShared<FPFAccountManagementGetPlayFabIDsFromKongregateIDsResult>(FPFAccountManagementGetPlayFabIDsFromKongregateIDsResult{
		.data = ConvertPlayfabArrayToUnreal<PFAccountManagementKongregatePlayFabIdPair, FPFAccountManagementKongregatePlayFabIdPair>(Datatype->data, Datatype->dataCount, ConvertKongregatePlayFabIdPairToUnreal),
		.dataCount = Datatype->dataCount
	});

	return ConvertedType;
}

const PFAccountManagementGetPlayFabIDsFromKongregateIDsResult* ConvertGetPlayFabIDsFromKongregateIDsResultToPlayfab(TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromKongregateIDsResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetPlayFabIDsFromKongregateIDsResult* ConvertedType = new PFAccountManagementGetPlayFabIDsFromKongregateIDsResult{
		.data = ConvertUnrealArrayToPlayfab<PFAccountManagementKongregatePlayFabIdPair, FPFAccountManagementKongregatePlayFabIdPair>(Datatype->data, ConvertKongregatePlayFabIdPairToPlayfab),
		.dataCount = (uint32_t)Datatype->data.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsRequest> ConvertGetPlayFabIDsFromNintendoServiceAccountIdsRequestToUnreal(const PFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsRequest> ConvertedType = MakeShared<FPFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsRequest>(FPFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsRequest{
		.nintendoAccountIds = ConvertCharArrayToUnreal(Datatype->nintendoAccountIds, Datatype->nintendoAccountIdsCount),
		.nintendoAccountIdsCount = Datatype->nintendoAccountIdsCount
	});

	return ConvertedType;
}

const PFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsRequest* ConvertGetPlayFabIDsFromNintendoServiceAccountIdsRequestToPlayfab(TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsRequest* ConvertedType = new PFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsRequest{
		.nintendoAccountIds = ConvertFStringArrayToPlayfab(Datatype->nintendoAccountIds),
		.nintendoAccountIdsCount = (uint32_t)Datatype->nintendoAccountIds.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementNintendoServiceAccountPlayFabIdPair> ConvertNintendoServiceAccountPlayFabIdPairToUnreal(const PFAccountManagementNintendoServiceAccountPlayFabIdPair* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementNintendoServiceAccountPlayFabIdPair> ConvertedType = MakeShared<FPFAccountManagementNintendoServiceAccountPlayFabIdPair>(FPFAccountManagementNintendoServiceAccountPlayFabIdPair{
		.nintendoServiceAccountId = Datatype->nintendoServiceAccountId == nullptr ? FString() : FString(Datatype->nintendoServiceAccountId),
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId)
	});

	return ConvertedType;
}

const PFAccountManagementNintendoServiceAccountPlayFabIdPair* ConvertNintendoServiceAccountPlayFabIdPairToPlayfab(TSharedPtr<const FPFAccountManagementNintendoServiceAccountPlayFabIdPair> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementNintendoServiceAccountPlayFabIdPair* ConvertedType = new PFAccountManagementNintendoServiceAccountPlayFabIdPair{
		.nintendoServiceAccountId = ConvertFStringToCharPtr(Datatype->nintendoServiceAccountId),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsResult> ConvertGetPlayFabIDsFromNintendoServiceAccountIdsResultToUnreal(const PFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsResult> ConvertedType = MakeShared<FPFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsResult>(FPFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsResult{
		.data = ConvertPlayfabArrayToUnreal<PFAccountManagementNintendoServiceAccountPlayFabIdPair, FPFAccountManagementNintendoServiceAccountPlayFabIdPair>(Datatype->data, Datatype->dataCount, ConvertNintendoServiceAccountPlayFabIdPairToUnreal),
		.dataCount = Datatype->dataCount
	});

	return ConvertedType;
}

const PFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsResult* ConvertGetPlayFabIDsFromNintendoServiceAccountIdsResultToPlayfab(TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsResult* ConvertedType = new PFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsResult{
		.data = ConvertUnrealArrayToPlayfab<PFAccountManagementNintendoServiceAccountPlayFabIdPair, FPFAccountManagementNintendoServiceAccountPlayFabIdPair>(Datatype->data, ConvertNintendoServiceAccountPlayFabIdPairToPlayfab),
		.dataCount = (uint32_t)Datatype->data.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsRequest> ConvertGetPlayFabIDsFromNintendoSwitchDeviceIdsRequestToUnreal(const PFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsRequest> ConvertedType = MakeShared<FPFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsRequest>(FPFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsRequest{
		.nintendoSwitchDeviceIds = ConvertCharArrayToUnreal(Datatype->nintendoSwitchDeviceIds, Datatype->nintendoSwitchDeviceIdsCount),
		.nintendoSwitchDeviceIdsCount = Datatype->nintendoSwitchDeviceIdsCount
	});

	return ConvertedType;
}

const PFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsRequest* ConvertGetPlayFabIDsFromNintendoSwitchDeviceIdsRequestToPlayfab(TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsRequest* ConvertedType = new PFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsRequest{
		.nintendoSwitchDeviceIds = ConvertFStringArrayToPlayfab(Datatype->nintendoSwitchDeviceIds),
		.nintendoSwitchDeviceIdsCount = (uint32_t)Datatype->nintendoSwitchDeviceIds.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementNintendoSwitchPlayFabIdPair> ConvertNintendoSwitchPlayFabIdPairToUnreal(const PFAccountManagementNintendoSwitchPlayFabIdPair* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementNintendoSwitchPlayFabIdPair> ConvertedType = MakeShared<FPFAccountManagementNintendoSwitchPlayFabIdPair>(FPFAccountManagementNintendoSwitchPlayFabIdPair{
		.nintendoSwitchDeviceId = Datatype->nintendoSwitchDeviceId == nullptr ? FString() : FString(Datatype->nintendoSwitchDeviceId),
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId)
	});

	return ConvertedType;
}

const PFAccountManagementNintendoSwitchPlayFabIdPair* ConvertNintendoSwitchPlayFabIdPairToPlayfab(TSharedPtr<const FPFAccountManagementNintendoSwitchPlayFabIdPair> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementNintendoSwitchPlayFabIdPair* ConvertedType = new PFAccountManagementNintendoSwitchPlayFabIdPair{
		.nintendoSwitchDeviceId = ConvertFStringToCharPtr(Datatype->nintendoSwitchDeviceId),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsResult> ConvertGetPlayFabIDsFromNintendoSwitchDeviceIdsResultToUnreal(const PFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsResult> ConvertedType = MakeShared<FPFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsResult>(FPFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsResult{
		.data = ConvertPlayfabArrayToUnreal<PFAccountManagementNintendoSwitchPlayFabIdPair, FPFAccountManagementNintendoSwitchPlayFabIdPair>(Datatype->data, Datatype->dataCount, ConvertNintendoSwitchPlayFabIdPairToUnreal),
		.dataCount = Datatype->dataCount
	});

	return ConvertedType;
}

const PFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsResult* ConvertGetPlayFabIDsFromNintendoSwitchDeviceIdsResultToPlayfab(TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsResult* ConvertedType = new PFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsResult{
		.data = ConvertUnrealArrayToPlayfab<PFAccountManagementNintendoSwitchPlayFabIdPair, FPFAccountManagementNintendoSwitchPlayFabIdPair>(Datatype->data, ConvertNintendoSwitchPlayFabIdPairToPlayfab),
		.dataCount = (uint32_t)Datatype->data.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromPSNAccountIDsRequest> ConvertGetPlayFabIDsFromPSNAccountIDsRequestToUnreal(const PFAccountManagementGetPlayFabIDsFromPSNAccountIDsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromPSNAccountIDsRequest> ConvertedType = MakeShared<FPFAccountManagementGetPlayFabIDsFromPSNAccountIDsRequest>(FPFAccountManagementGetPlayFabIDsFromPSNAccountIDsRequest{
		.issuerId = TSharedPtr<const int32>(Datatype->issuerId),
		.PSNAccountIDs = ConvertCharArrayToUnreal(Datatype->PSNAccountIDs, Datatype->PSNAccountIDsCount),
		.PSNAccountIDsCount = Datatype->PSNAccountIDsCount
	});

	return ConvertedType;
}

const PFAccountManagementGetPlayFabIDsFromPSNAccountIDsRequest* ConvertGetPlayFabIDsFromPSNAccountIDsRequestToPlayfab(TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromPSNAccountIDsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetPlayFabIDsFromPSNAccountIDsRequest* ConvertedType = new PFAccountManagementGetPlayFabIDsFromPSNAccountIDsRequest{
		.issuerId = Datatype->issuerId ? new int32(*Datatype->issuerId) : nullptr,
		.PSNAccountIDs = ConvertFStringArrayToPlayfab(Datatype->PSNAccountIDs),
		.PSNAccountIDsCount = (uint32_t)Datatype->PSNAccountIDs.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementPSNAccountPlayFabIdPair> ConvertPSNAccountPlayFabIdPairToUnreal(const PFAccountManagementPSNAccountPlayFabIdPair* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementPSNAccountPlayFabIdPair> ConvertedType = MakeShared<FPFAccountManagementPSNAccountPlayFabIdPair>(FPFAccountManagementPSNAccountPlayFabIdPair{
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId),
		.PSNAccountId = Datatype->PSNAccountId == nullptr ? FString() : FString(Datatype->PSNAccountId)
	});

	return ConvertedType;
}

const PFAccountManagementPSNAccountPlayFabIdPair* ConvertPSNAccountPlayFabIdPairToPlayfab(TSharedPtr<const FPFAccountManagementPSNAccountPlayFabIdPair> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementPSNAccountPlayFabIdPair* ConvertedType = new PFAccountManagementPSNAccountPlayFabIdPair{
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId),
		.PSNAccountId = ConvertFStringToCharPtr(Datatype->PSNAccountId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromPSNAccountIDsResult> ConvertGetPlayFabIDsFromPSNAccountIDsResultToUnreal(const PFAccountManagementGetPlayFabIDsFromPSNAccountIDsResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromPSNAccountIDsResult> ConvertedType = MakeShared<FPFAccountManagementGetPlayFabIDsFromPSNAccountIDsResult>(FPFAccountManagementGetPlayFabIDsFromPSNAccountIDsResult{
		.data = ConvertPlayfabArrayToUnreal<PFAccountManagementPSNAccountPlayFabIdPair, FPFAccountManagementPSNAccountPlayFabIdPair>(Datatype->data, Datatype->dataCount, ConvertPSNAccountPlayFabIdPairToUnreal),
		.dataCount = Datatype->dataCount
	});

	return ConvertedType;
}

const PFAccountManagementGetPlayFabIDsFromPSNAccountIDsResult* ConvertGetPlayFabIDsFromPSNAccountIDsResultToPlayfab(TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromPSNAccountIDsResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetPlayFabIDsFromPSNAccountIDsResult* ConvertedType = new PFAccountManagementGetPlayFabIDsFromPSNAccountIDsResult{
		.data = ConvertUnrealArrayToPlayfab<PFAccountManagementPSNAccountPlayFabIdPair, FPFAccountManagementPSNAccountPlayFabIdPair>(Datatype->data, ConvertPSNAccountPlayFabIdPairToPlayfab),
		.dataCount = (uint32_t)Datatype->data.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromPSNOnlineIDsRequest> ConvertGetPlayFabIDsFromPSNOnlineIDsRequestToUnreal(const PFAccountManagementGetPlayFabIDsFromPSNOnlineIDsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromPSNOnlineIDsRequest> ConvertedType = MakeShared<FPFAccountManagementGetPlayFabIDsFromPSNOnlineIDsRequest>(FPFAccountManagementGetPlayFabIDsFromPSNOnlineIDsRequest{
		.issuerId = TSharedPtr<const int32>(Datatype->issuerId),
		.PSNOnlineIDs = ConvertCharArrayToUnreal(Datatype->PSNOnlineIDs, Datatype->PSNOnlineIDsCount),
		.PSNOnlineIDsCount = Datatype->PSNOnlineIDsCount
	});

	return ConvertedType;
}

const PFAccountManagementGetPlayFabIDsFromPSNOnlineIDsRequest* ConvertGetPlayFabIDsFromPSNOnlineIDsRequestToPlayfab(TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromPSNOnlineIDsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetPlayFabIDsFromPSNOnlineIDsRequest* ConvertedType = new PFAccountManagementGetPlayFabIDsFromPSNOnlineIDsRequest{
		.issuerId = Datatype->issuerId ? new int32(*Datatype->issuerId) : nullptr,
		.PSNOnlineIDs = ConvertFStringArrayToPlayfab(Datatype->PSNOnlineIDs),
		.PSNOnlineIDsCount = (uint32_t)Datatype->PSNOnlineIDs.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementPSNOnlinePlayFabIdPair> ConvertPSNOnlinePlayFabIdPairToUnreal(const PFAccountManagementPSNOnlinePlayFabIdPair* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementPSNOnlinePlayFabIdPair> ConvertedType = MakeShared<FPFAccountManagementPSNOnlinePlayFabIdPair>(FPFAccountManagementPSNOnlinePlayFabIdPair{
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId),
		.PSNOnlineId = Datatype->PSNOnlineId == nullptr ? FString() : FString(Datatype->PSNOnlineId)
	});

	return ConvertedType;
}

const PFAccountManagementPSNOnlinePlayFabIdPair* ConvertPSNOnlinePlayFabIdPairToPlayfab(TSharedPtr<const FPFAccountManagementPSNOnlinePlayFabIdPair> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementPSNOnlinePlayFabIdPair* ConvertedType = new PFAccountManagementPSNOnlinePlayFabIdPair{
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId),
		.PSNOnlineId = ConvertFStringToCharPtr(Datatype->PSNOnlineId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromPSNOnlineIDsResult> ConvertGetPlayFabIDsFromPSNOnlineIDsResultToUnreal(const PFAccountManagementGetPlayFabIDsFromPSNOnlineIDsResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromPSNOnlineIDsResult> ConvertedType = MakeShared<FPFAccountManagementGetPlayFabIDsFromPSNOnlineIDsResult>(FPFAccountManagementGetPlayFabIDsFromPSNOnlineIDsResult{
		.data = ConvertPlayfabArrayToUnreal<PFAccountManagementPSNOnlinePlayFabIdPair, FPFAccountManagementPSNOnlinePlayFabIdPair>(Datatype->data, Datatype->dataCount, ConvertPSNOnlinePlayFabIdPairToUnreal),
		.dataCount = Datatype->dataCount
	});

	return ConvertedType;
}

const PFAccountManagementGetPlayFabIDsFromPSNOnlineIDsResult* ConvertGetPlayFabIDsFromPSNOnlineIDsResultToPlayfab(TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromPSNOnlineIDsResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetPlayFabIDsFromPSNOnlineIDsResult* ConvertedType = new PFAccountManagementGetPlayFabIDsFromPSNOnlineIDsResult{
		.data = ConvertUnrealArrayToPlayfab<PFAccountManagementPSNOnlinePlayFabIdPair, FPFAccountManagementPSNOnlinePlayFabIdPair>(Datatype->data, ConvertPSNOnlinePlayFabIdPairToPlayfab),
		.dataCount = (uint32_t)Datatype->data.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromSteamIDsRequest> ConvertGetPlayFabIDsFromSteamIDsRequestToUnreal(const PFAccountManagementGetPlayFabIDsFromSteamIDsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromSteamIDsRequest> ConvertedType = MakeShared<FPFAccountManagementGetPlayFabIDsFromSteamIDsRequest>(FPFAccountManagementGetPlayFabIDsFromSteamIDsRequest{
		.steamStringIDs = ConvertCharArrayToUnreal(Datatype->steamStringIDs, Datatype->steamStringIDsCount),
		.steamStringIDsCount = Datatype->steamStringIDsCount
	});

	return ConvertedType;
}

const PFAccountManagementGetPlayFabIDsFromSteamIDsRequest* ConvertGetPlayFabIDsFromSteamIDsRequestToPlayfab(TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromSteamIDsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetPlayFabIDsFromSteamIDsRequest* ConvertedType = new PFAccountManagementGetPlayFabIDsFromSteamIDsRequest{
		.steamStringIDs = ConvertFStringArrayToPlayfab(Datatype->steamStringIDs),
		.steamStringIDsCount = (uint32_t)Datatype->steamStringIDs.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementSteamPlayFabIdPair> ConvertSteamPlayFabIdPairToUnreal(const PFAccountManagementSteamPlayFabIdPair* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementSteamPlayFabIdPair> ConvertedType = MakeShared<FPFAccountManagementSteamPlayFabIdPair>(FPFAccountManagementSteamPlayFabIdPair{
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId),
		.steamStringId = Datatype->steamStringId == nullptr ? FString() : FString(Datatype->steamStringId)
	});

	return ConvertedType;
}

const PFAccountManagementSteamPlayFabIdPair* ConvertSteamPlayFabIdPairToPlayfab(TSharedPtr<const FPFAccountManagementSteamPlayFabIdPair> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementSteamPlayFabIdPair* ConvertedType = new PFAccountManagementSteamPlayFabIdPair{
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId),
		.steamStringId = ConvertFStringToCharPtr(Datatype->steamStringId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromSteamIDsResult> ConvertGetPlayFabIDsFromSteamIDsResultToUnreal(const PFAccountManagementGetPlayFabIDsFromSteamIDsResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromSteamIDsResult> ConvertedType = MakeShared<FPFAccountManagementGetPlayFabIDsFromSteamIDsResult>(FPFAccountManagementGetPlayFabIDsFromSteamIDsResult{
		.data = ConvertPlayfabArrayToUnreal<PFAccountManagementSteamPlayFabIdPair, FPFAccountManagementSteamPlayFabIdPair>(Datatype->data, Datatype->dataCount, ConvertSteamPlayFabIdPairToUnreal),
		.dataCount = Datatype->dataCount
	});

	return ConvertedType;
}

const PFAccountManagementGetPlayFabIDsFromSteamIDsResult* ConvertGetPlayFabIDsFromSteamIDsResultToPlayfab(TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromSteamIDsResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetPlayFabIDsFromSteamIDsResult* ConvertedType = new PFAccountManagementGetPlayFabIDsFromSteamIDsResult{
		.data = ConvertUnrealArrayToPlayfab<PFAccountManagementSteamPlayFabIdPair, FPFAccountManagementSteamPlayFabIdPair>(Datatype->data, ConvertSteamPlayFabIdPairToPlayfab),
		.dataCount = (uint32_t)Datatype->data.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromSteamNamesRequest> ConvertGetPlayFabIDsFromSteamNamesRequestToUnreal(const PFAccountManagementGetPlayFabIDsFromSteamNamesRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromSteamNamesRequest> ConvertedType = MakeShared<FPFAccountManagementGetPlayFabIDsFromSteamNamesRequest>(FPFAccountManagementGetPlayFabIDsFromSteamNamesRequest{
		.steamNames = ConvertCharArrayToUnreal(Datatype->steamNames, Datatype->steamNamesCount),
		.steamNamesCount = Datatype->steamNamesCount
	});

	return ConvertedType;
}

const PFAccountManagementGetPlayFabIDsFromSteamNamesRequest* ConvertGetPlayFabIDsFromSteamNamesRequestToPlayfab(TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromSteamNamesRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetPlayFabIDsFromSteamNamesRequest* ConvertedType = new PFAccountManagementGetPlayFabIDsFromSteamNamesRequest{
		.steamNames = ConvertFStringArrayToPlayfab(Datatype->steamNames),
		.steamNamesCount = (uint32_t)Datatype->steamNames.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementSteamNamePlayFabIdPair> ConvertSteamNamePlayFabIdPairToUnreal(const PFAccountManagementSteamNamePlayFabIdPair* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementSteamNamePlayFabIdPair> ConvertedType = MakeShared<FPFAccountManagementSteamNamePlayFabIdPair>(FPFAccountManagementSteamNamePlayFabIdPair{
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId),
		.steamName = Datatype->steamName == nullptr ? FString() : FString(Datatype->steamName)
	});

	return ConvertedType;
}

const PFAccountManagementSteamNamePlayFabIdPair* ConvertSteamNamePlayFabIdPairToPlayfab(TSharedPtr<const FPFAccountManagementSteamNamePlayFabIdPair> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementSteamNamePlayFabIdPair* ConvertedType = new PFAccountManagementSteamNamePlayFabIdPair{
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId),
		.steamName = ConvertFStringToCharPtr(Datatype->steamName)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromSteamNamesResult> ConvertGetPlayFabIDsFromSteamNamesResultToUnreal(const PFAccountManagementGetPlayFabIDsFromSteamNamesResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromSteamNamesResult> ConvertedType = MakeShared<FPFAccountManagementGetPlayFabIDsFromSteamNamesResult>(FPFAccountManagementGetPlayFabIDsFromSteamNamesResult{
		.data = ConvertPlayfabArrayToUnreal<PFAccountManagementSteamNamePlayFabIdPair, FPFAccountManagementSteamNamePlayFabIdPair>(Datatype->data, Datatype->dataCount, ConvertSteamNamePlayFabIdPairToUnreal),
		.dataCount = Datatype->dataCount
	});

	return ConvertedType;
}

const PFAccountManagementGetPlayFabIDsFromSteamNamesResult* ConvertGetPlayFabIDsFromSteamNamesResultToPlayfab(TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromSteamNamesResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetPlayFabIDsFromSteamNamesResult* ConvertedType = new PFAccountManagementGetPlayFabIDsFromSteamNamesResult{
		.data = ConvertUnrealArrayToPlayfab<PFAccountManagementSteamNamePlayFabIdPair, FPFAccountManagementSteamNamePlayFabIdPair>(Datatype->data, ConvertSteamNamePlayFabIdPairToPlayfab),
		.dataCount = (uint32_t)Datatype->data.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromTwitchIDsRequest> ConvertGetPlayFabIDsFromTwitchIDsRequestToUnreal(const PFAccountManagementGetPlayFabIDsFromTwitchIDsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromTwitchIDsRequest> ConvertedType = MakeShared<FPFAccountManagementGetPlayFabIDsFromTwitchIDsRequest>(FPFAccountManagementGetPlayFabIDsFromTwitchIDsRequest{
		.twitchIds = ConvertCharArrayToUnreal(Datatype->twitchIds, Datatype->twitchIdsCount),
		.twitchIdsCount = Datatype->twitchIdsCount
	});

	return ConvertedType;
}

const PFAccountManagementGetPlayFabIDsFromTwitchIDsRequest* ConvertGetPlayFabIDsFromTwitchIDsRequestToPlayfab(TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromTwitchIDsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetPlayFabIDsFromTwitchIDsRequest* ConvertedType = new PFAccountManagementGetPlayFabIDsFromTwitchIDsRequest{
		.twitchIds = ConvertFStringArrayToPlayfab(Datatype->twitchIds),
		.twitchIdsCount = (uint32_t)Datatype->twitchIds.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementTwitchPlayFabIdPair> ConvertTwitchPlayFabIdPairToUnreal(const PFAccountManagementTwitchPlayFabIdPair* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementTwitchPlayFabIdPair> ConvertedType = MakeShared<FPFAccountManagementTwitchPlayFabIdPair>(FPFAccountManagementTwitchPlayFabIdPair{
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId),
		.twitchId = Datatype->twitchId == nullptr ? FString() : FString(Datatype->twitchId)
	});

	return ConvertedType;
}

const PFAccountManagementTwitchPlayFabIdPair* ConvertTwitchPlayFabIdPairToPlayfab(TSharedPtr<const FPFAccountManagementTwitchPlayFabIdPair> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementTwitchPlayFabIdPair* ConvertedType = new PFAccountManagementTwitchPlayFabIdPair{
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId),
		.twitchId = ConvertFStringToCharPtr(Datatype->twitchId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromTwitchIDsResult> ConvertGetPlayFabIDsFromTwitchIDsResultToUnreal(const PFAccountManagementGetPlayFabIDsFromTwitchIDsResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromTwitchIDsResult> ConvertedType = MakeShared<FPFAccountManagementGetPlayFabIDsFromTwitchIDsResult>(FPFAccountManagementGetPlayFabIDsFromTwitchIDsResult{
		.data = ConvertPlayfabArrayToUnreal<PFAccountManagementTwitchPlayFabIdPair, FPFAccountManagementTwitchPlayFabIdPair>(Datatype->data, Datatype->dataCount, ConvertTwitchPlayFabIdPairToUnreal),
		.dataCount = Datatype->dataCount
	});

	return ConvertedType;
}

const PFAccountManagementGetPlayFabIDsFromTwitchIDsResult* ConvertGetPlayFabIDsFromTwitchIDsResultToPlayfab(TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromTwitchIDsResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetPlayFabIDsFromTwitchIDsResult* ConvertedType = new PFAccountManagementGetPlayFabIDsFromTwitchIDsResult{
		.data = ConvertUnrealArrayToPlayfab<PFAccountManagementTwitchPlayFabIdPair, FPFAccountManagementTwitchPlayFabIdPair>(Datatype->data, ConvertTwitchPlayFabIdPairToPlayfab),
		.dataCount = (uint32_t)Datatype->data.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromXboxLiveIDsRequest> ConvertGetPlayFabIDsFromXboxLiveIDsRequestToUnreal(const PFAccountManagementGetPlayFabIDsFromXboxLiveIDsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromXboxLiveIDsRequest> ConvertedType = MakeShared<FPFAccountManagementGetPlayFabIDsFromXboxLiveIDsRequest>(FPFAccountManagementGetPlayFabIDsFromXboxLiveIDsRequest{
		.sandbox = Datatype->sandbox == nullptr ? FString() : FString(Datatype->sandbox),
		.xboxLiveAccountIDs = ConvertCharArrayToUnreal(Datatype->xboxLiveAccountIDs, Datatype->xboxLiveAccountIDsCount),
		.xboxLiveAccountIDsCount = Datatype->xboxLiveAccountIDsCount
	});

	return ConvertedType;
}

const PFAccountManagementGetPlayFabIDsFromXboxLiveIDsRequest* ConvertGetPlayFabIDsFromXboxLiveIDsRequestToPlayfab(TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromXboxLiveIDsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetPlayFabIDsFromXboxLiveIDsRequest* ConvertedType = new PFAccountManagementGetPlayFabIDsFromXboxLiveIDsRequest{
		.sandbox = ConvertFStringToCharPtr(Datatype->sandbox),
		.xboxLiveAccountIDs = ConvertFStringArrayToPlayfab(Datatype->xboxLiveAccountIDs),
		.xboxLiveAccountIDsCount = (uint32_t)Datatype->xboxLiveAccountIDs.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementXboxLiveAccountPlayFabIdPair> ConvertXboxLiveAccountPlayFabIdPairToUnreal(const PFAccountManagementXboxLiveAccountPlayFabIdPair* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementXboxLiveAccountPlayFabIdPair> ConvertedType = MakeShared<FPFAccountManagementXboxLiveAccountPlayFabIdPair>(FPFAccountManagementXboxLiveAccountPlayFabIdPair{
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId),
		.xboxLiveAccountId = Datatype->xboxLiveAccountId == nullptr ? FString() : FString(Datatype->xboxLiveAccountId)
	});

	return ConvertedType;
}

const PFAccountManagementXboxLiveAccountPlayFabIdPair* ConvertXboxLiveAccountPlayFabIdPairToPlayfab(TSharedPtr<const FPFAccountManagementXboxLiveAccountPlayFabIdPair> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementXboxLiveAccountPlayFabIdPair* ConvertedType = new PFAccountManagementXboxLiveAccountPlayFabIdPair{
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId),
		.xboxLiveAccountId = ConvertFStringToCharPtr(Datatype->xboxLiveAccountId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromXboxLiveIDsResult> ConvertGetPlayFabIDsFromXboxLiveIDsResultToUnreal(const PFAccountManagementGetPlayFabIDsFromXboxLiveIDsResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromXboxLiveIDsResult> ConvertedType = MakeShared<FPFAccountManagementGetPlayFabIDsFromXboxLiveIDsResult>(FPFAccountManagementGetPlayFabIDsFromXboxLiveIDsResult{
		.data = ConvertPlayfabArrayToUnreal<PFAccountManagementXboxLiveAccountPlayFabIdPair, FPFAccountManagementXboxLiveAccountPlayFabIdPair>(Datatype->data, Datatype->dataCount, ConvertXboxLiveAccountPlayFabIdPairToUnreal),
		.dataCount = Datatype->dataCount
	});

	return ConvertedType;
}

const PFAccountManagementGetPlayFabIDsFromXboxLiveIDsResult* ConvertGetPlayFabIDsFromXboxLiveIDsResultToPlayfab(TSharedPtr<const FPFAccountManagementGetPlayFabIDsFromXboxLiveIDsResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetPlayFabIDsFromXboxLiveIDsResult* ConvertedType = new PFAccountManagementGetPlayFabIDsFromXboxLiveIDsResult{
		.data = ConvertUnrealArrayToPlayfab<PFAccountManagementXboxLiveAccountPlayFabIdPair, FPFAccountManagementXboxLiveAccountPlayFabIdPair>(Datatype->data, ConvertXboxLiveAccountPlayFabIdPairToPlayfab),
		.dataCount = (uint32_t)Datatype->data.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementLinkAndroidDeviceIDRequest> ConvertLinkAndroidDeviceIDRequestToUnreal(const PFAccountManagementLinkAndroidDeviceIDRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementLinkAndroidDeviceIDRequest> ConvertedType = MakeShared<FPFAccountManagementLinkAndroidDeviceIDRequest>(FPFAccountManagementLinkAndroidDeviceIDRequest{
		.androidDevice = Datatype->androidDevice == nullptr ? FString() : FString(Datatype->androidDevice),
		.androidDeviceId = Datatype->androidDeviceId == nullptr ? FString() : FString(Datatype->androidDeviceId),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.forceLink = TSharedPtr<const bool>(Datatype->forceLink),
		.OS = Datatype->OS == nullptr ? FString() : FString(Datatype->OS)
	});

	return ConvertedType;
}

const PFAccountManagementLinkAndroidDeviceIDRequest* ConvertLinkAndroidDeviceIDRequestToPlayfab(TSharedPtr<const FPFAccountManagementLinkAndroidDeviceIDRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementLinkAndroidDeviceIDRequest* ConvertedType = new PFAccountManagementLinkAndroidDeviceIDRequest{
		.androidDevice = ConvertFStringToCharPtr(Datatype->androidDevice),
		.androidDeviceId = ConvertFStringToCharPtr(Datatype->androidDeviceId),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.forceLink = Datatype->forceLink ? new bool(*Datatype->forceLink) : nullptr,
		.OS = ConvertFStringToCharPtr(Datatype->OS)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementLinkAppleRequest> ConvertLinkAppleRequestToUnreal(const PFAccountManagementLinkAppleRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementLinkAppleRequest> ConvertedType = MakeShared<FPFAccountManagementLinkAppleRequest>(FPFAccountManagementLinkAppleRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.forceLink = TSharedPtr<const bool>(Datatype->forceLink),
		.identityToken = Datatype->identityToken == nullptr ? FString() : FString(Datatype->identityToken)
	});

	return ConvertedType;
}

const PFAccountManagementLinkAppleRequest* ConvertLinkAppleRequestToPlayfab(TSharedPtr<const FPFAccountManagementLinkAppleRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementLinkAppleRequest* ConvertedType = new PFAccountManagementLinkAppleRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.forceLink = Datatype->forceLink ? new bool(*Datatype->forceLink) : nullptr,
		.identityToken = ConvertFStringToCharPtr(Datatype->identityToken)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementClientLinkBattleNetAccountRequest> ConvertClientLinkBattleNetAccountRequestToUnreal(const PFAccountManagementClientLinkBattleNetAccountRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementClientLinkBattleNetAccountRequest> ConvertedType = MakeShared<FPFAccountManagementClientLinkBattleNetAccountRequest>(FPFAccountManagementClientLinkBattleNetAccountRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.forceLink = TSharedPtr<const bool>(Datatype->forceLink),
		.identityToken = Datatype->identityToken == nullptr ? FString() : FString(Datatype->identityToken)
	});

	return ConvertedType;
}

const PFAccountManagementClientLinkBattleNetAccountRequest* ConvertClientLinkBattleNetAccountRequestToPlayfab(TSharedPtr<const FPFAccountManagementClientLinkBattleNetAccountRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementClientLinkBattleNetAccountRequest* ConvertedType = new PFAccountManagementClientLinkBattleNetAccountRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.forceLink = Datatype->forceLink ? new bool(*Datatype->forceLink) : nullptr,
		.identityToken = ConvertFStringToCharPtr(Datatype->identityToken)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementLinkCustomIDRequest> ConvertLinkCustomIDRequestToUnreal(const PFAccountManagementLinkCustomIDRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementLinkCustomIDRequest> ConvertedType = MakeShared<FPFAccountManagementLinkCustomIDRequest>(FPFAccountManagementLinkCustomIDRequest{
		.customId = Datatype->customId == nullptr ? FString() : FString(Datatype->customId),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.forceLink = TSharedPtr<const bool>(Datatype->forceLink)
	});

	return ConvertedType;
}

const PFAccountManagementLinkCustomIDRequest* ConvertLinkCustomIDRequestToPlayfab(TSharedPtr<const FPFAccountManagementLinkCustomIDRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementLinkCustomIDRequest* ConvertedType = new PFAccountManagementLinkCustomIDRequest{
		.customId = ConvertFStringToCharPtr(Datatype->customId),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.forceLink = Datatype->forceLink ? new bool(*Datatype->forceLink) : nullptr
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementLinkFacebookAccountRequest> ConvertLinkFacebookAccountRequestToUnreal(const PFAccountManagementLinkFacebookAccountRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementLinkFacebookAccountRequest> ConvertedType = MakeShared<FPFAccountManagementLinkFacebookAccountRequest>(FPFAccountManagementLinkFacebookAccountRequest{
		.accessToken = Datatype->accessToken == nullptr ? FString() : FString(Datatype->accessToken),
		.authenticationToken = Datatype->authenticationToken == nullptr ? FString() : FString(Datatype->authenticationToken),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.forceLink = TSharedPtr<const bool>(Datatype->forceLink)
	});

	return ConvertedType;
}

const PFAccountManagementLinkFacebookAccountRequest* ConvertLinkFacebookAccountRequestToPlayfab(TSharedPtr<const FPFAccountManagementLinkFacebookAccountRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementLinkFacebookAccountRequest* ConvertedType = new PFAccountManagementLinkFacebookAccountRequest{
		.accessToken = ConvertFStringToCharPtr(Datatype->accessToken),
		.authenticationToken = ConvertFStringToCharPtr(Datatype->authenticationToken),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.forceLink = Datatype->forceLink ? new bool(*Datatype->forceLink) : nullptr
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementLinkFacebookInstantGamesIdRequest> ConvertLinkFacebookInstantGamesIdRequestToUnreal(const PFAccountManagementLinkFacebookInstantGamesIdRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementLinkFacebookInstantGamesIdRequest> ConvertedType = MakeShared<FPFAccountManagementLinkFacebookInstantGamesIdRequest>(FPFAccountManagementLinkFacebookInstantGamesIdRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.facebookInstantGamesSignature = Datatype->facebookInstantGamesSignature == nullptr ? FString() : FString(Datatype->facebookInstantGamesSignature),
		.forceLink = TSharedPtr<const bool>(Datatype->forceLink)
	});

	return ConvertedType;
}

const PFAccountManagementLinkFacebookInstantGamesIdRequest* ConvertLinkFacebookInstantGamesIdRequestToPlayfab(TSharedPtr<const FPFAccountManagementLinkFacebookInstantGamesIdRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementLinkFacebookInstantGamesIdRequest* ConvertedType = new PFAccountManagementLinkFacebookInstantGamesIdRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.facebookInstantGamesSignature = ConvertFStringToCharPtr(Datatype->facebookInstantGamesSignature),
		.forceLink = Datatype->forceLink ? new bool(*Datatype->forceLink) : nullptr
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementLinkGameCenterAccountRequest> ConvertLinkGameCenterAccountRequestToUnreal(const PFAccountManagementLinkGameCenterAccountRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementLinkGameCenterAccountRequest> ConvertedType = MakeShared<FPFAccountManagementLinkGameCenterAccountRequest>(FPFAccountManagementLinkGameCenterAccountRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.forceLink = TSharedPtr<const bool>(Datatype->forceLink),
		.gameCenterId = Datatype->gameCenterId == nullptr ? FString() : FString(Datatype->gameCenterId),
		.publicKeyUrl = Datatype->publicKeyUrl == nullptr ? FString() : FString(Datatype->publicKeyUrl),
		.salt = Datatype->salt == nullptr ? FString() : FString(Datatype->salt),
		.signature = Datatype->signature == nullptr ? FString() : FString(Datatype->signature),
		.timestamp = Datatype->timestamp == nullptr ? FString() : FString(Datatype->timestamp)
	});

	return ConvertedType;
}

const PFAccountManagementLinkGameCenterAccountRequest* ConvertLinkGameCenterAccountRequestToPlayfab(TSharedPtr<const FPFAccountManagementLinkGameCenterAccountRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementLinkGameCenterAccountRequest* ConvertedType = new PFAccountManagementLinkGameCenterAccountRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.forceLink = Datatype->forceLink ? new bool(*Datatype->forceLink) : nullptr,
		.gameCenterId = ConvertFStringToCharPtr(Datatype->gameCenterId),
		.publicKeyUrl = ConvertFStringToCharPtr(Datatype->publicKeyUrl),
		.salt = ConvertFStringToCharPtr(Datatype->salt),
		.signature = ConvertFStringToCharPtr(Datatype->signature),
		.timestamp = ConvertFStringToCharPtr(Datatype->timestamp)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementLinkGoogleAccountRequest> ConvertLinkGoogleAccountRequestToUnreal(const PFAccountManagementLinkGoogleAccountRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementLinkGoogleAccountRequest> ConvertedType = MakeShared<FPFAccountManagementLinkGoogleAccountRequest>(FPFAccountManagementLinkGoogleAccountRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.forceLink = TSharedPtr<const bool>(Datatype->forceLink),
		.serverAuthCode = Datatype->serverAuthCode == nullptr ? FString() : FString(Datatype->serverAuthCode)
	});

	return ConvertedType;
}

const PFAccountManagementLinkGoogleAccountRequest* ConvertLinkGoogleAccountRequestToPlayfab(TSharedPtr<const FPFAccountManagementLinkGoogleAccountRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementLinkGoogleAccountRequest* ConvertedType = new PFAccountManagementLinkGoogleAccountRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.forceLink = Datatype->forceLink ? new bool(*Datatype->forceLink) : nullptr,
		.serverAuthCode = ConvertFStringToCharPtr(Datatype->serverAuthCode)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementLinkGooglePlayGamesServicesAccountRequest> ConvertLinkGooglePlayGamesServicesAccountRequestToUnreal(const PFAccountManagementLinkGooglePlayGamesServicesAccountRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementLinkGooglePlayGamesServicesAccountRequest> ConvertedType = MakeShared<FPFAccountManagementLinkGooglePlayGamesServicesAccountRequest>(FPFAccountManagementLinkGooglePlayGamesServicesAccountRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.forceLink = TSharedPtr<const bool>(Datatype->forceLink),
		.serverAuthCode = Datatype->serverAuthCode == nullptr ? FString() : FString(Datatype->serverAuthCode)
	});

	return ConvertedType;
}

const PFAccountManagementLinkGooglePlayGamesServicesAccountRequest* ConvertLinkGooglePlayGamesServicesAccountRequestToPlayfab(TSharedPtr<const FPFAccountManagementLinkGooglePlayGamesServicesAccountRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementLinkGooglePlayGamesServicesAccountRequest* ConvertedType = new PFAccountManagementLinkGooglePlayGamesServicesAccountRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.forceLink = Datatype->forceLink ? new bool(*Datatype->forceLink) : nullptr,
		.serverAuthCode = ConvertFStringToCharPtr(Datatype->serverAuthCode)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementLinkIOSDeviceIDRequest> ConvertLinkIOSDeviceIDRequestToUnreal(const PFAccountManagementLinkIOSDeviceIDRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementLinkIOSDeviceIDRequest> ConvertedType = MakeShared<FPFAccountManagementLinkIOSDeviceIDRequest>(FPFAccountManagementLinkIOSDeviceIDRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.deviceId = Datatype->deviceId == nullptr ? FString() : FString(Datatype->deviceId),
		.deviceModel = Datatype->deviceModel == nullptr ? FString() : FString(Datatype->deviceModel),
		.forceLink = TSharedPtr<const bool>(Datatype->forceLink),
		.OS = Datatype->OS == nullptr ? FString() : FString(Datatype->OS)
	});

	return ConvertedType;
}

const PFAccountManagementLinkIOSDeviceIDRequest* ConvertLinkIOSDeviceIDRequestToPlayfab(TSharedPtr<const FPFAccountManagementLinkIOSDeviceIDRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementLinkIOSDeviceIDRequest* ConvertedType = new PFAccountManagementLinkIOSDeviceIDRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.deviceId = ConvertFStringToCharPtr(Datatype->deviceId),
		.deviceModel = ConvertFStringToCharPtr(Datatype->deviceModel),
		.forceLink = Datatype->forceLink ? new bool(*Datatype->forceLink) : nullptr,
		.OS = ConvertFStringToCharPtr(Datatype->OS)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementLinkKongregateAccountRequest> ConvertLinkKongregateAccountRequestToUnreal(const PFAccountManagementLinkKongregateAccountRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementLinkKongregateAccountRequest> ConvertedType = MakeShared<FPFAccountManagementLinkKongregateAccountRequest>(FPFAccountManagementLinkKongregateAccountRequest{
		.authTicket = Datatype->authTicket == nullptr ? FString() : FString(Datatype->authTicket),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.forceLink = TSharedPtr<const bool>(Datatype->forceLink),
		.kongregateId = Datatype->kongregateId == nullptr ? FString() : FString(Datatype->kongregateId)
	});

	return ConvertedType;
}

const PFAccountManagementLinkKongregateAccountRequest* ConvertLinkKongregateAccountRequestToPlayfab(TSharedPtr<const FPFAccountManagementLinkKongregateAccountRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementLinkKongregateAccountRequest* ConvertedType = new PFAccountManagementLinkKongregateAccountRequest{
		.authTicket = ConvertFStringToCharPtr(Datatype->authTicket),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.forceLink = Datatype->forceLink ? new bool(*Datatype->forceLink) : nullptr,
		.kongregateId = ConvertFStringToCharPtr(Datatype->kongregateId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementClientLinkNintendoServiceAccountRequest> ConvertClientLinkNintendoServiceAccountRequestToUnreal(const PFAccountManagementClientLinkNintendoServiceAccountRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementClientLinkNintendoServiceAccountRequest> ConvertedType = MakeShared<FPFAccountManagementClientLinkNintendoServiceAccountRequest>(FPFAccountManagementClientLinkNintendoServiceAccountRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.forceLink = TSharedPtr<const bool>(Datatype->forceLink),
		.identityToken = Datatype->identityToken == nullptr ? FString() : FString(Datatype->identityToken)
	});

	return ConvertedType;
}

const PFAccountManagementClientLinkNintendoServiceAccountRequest* ConvertClientLinkNintendoServiceAccountRequestToPlayfab(TSharedPtr<const FPFAccountManagementClientLinkNintendoServiceAccountRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementClientLinkNintendoServiceAccountRequest* ConvertedType = new PFAccountManagementClientLinkNintendoServiceAccountRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.forceLink = Datatype->forceLink ? new bool(*Datatype->forceLink) : nullptr,
		.identityToken = ConvertFStringToCharPtr(Datatype->identityToken)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementClientLinkNintendoSwitchDeviceIdRequest> ConvertClientLinkNintendoSwitchDeviceIdRequestToUnreal(const PFAccountManagementClientLinkNintendoSwitchDeviceIdRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementClientLinkNintendoSwitchDeviceIdRequest> ConvertedType = MakeShared<FPFAccountManagementClientLinkNintendoSwitchDeviceIdRequest>(FPFAccountManagementClientLinkNintendoSwitchDeviceIdRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.forceLink = TSharedPtr<const bool>(Datatype->forceLink),
		.nintendoSwitchDeviceId = Datatype->nintendoSwitchDeviceId == nullptr ? FString() : FString(Datatype->nintendoSwitchDeviceId)
	});

	return ConvertedType;
}

const PFAccountManagementClientLinkNintendoSwitchDeviceIdRequest* ConvertClientLinkNintendoSwitchDeviceIdRequestToPlayfab(TSharedPtr<const FPFAccountManagementClientLinkNintendoSwitchDeviceIdRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementClientLinkNintendoSwitchDeviceIdRequest* ConvertedType = new PFAccountManagementClientLinkNintendoSwitchDeviceIdRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.forceLink = Datatype->forceLink ? new bool(*Datatype->forceLink) : nullptr,
		.nintendoSwitchDeviceId = ConvertFStringToCharPtr(Datatype->nintendoSwitchDeviceId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementLinkOpenIdConnectRequest> ConvertLinkOpenIdConnectRequestToUnreal(const PFAccountManagementLinkOpenIdConnectRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementLinkOpenIdConnectRequest> ConvertedType = MakeShared<FPFAccountManagementLinkOpenIdConnectRequest>(FPFAccountManagementLinkOpenIdConnectRequest{
		.connectionId = Datatype->connectionId == nullptr ? FString() : FString(Datatype->connectionId),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.forceLink = TSharedPtr<const bool>(Datatype->forceLink),
		.idToken = Datatype->idToken == nullptr ? FString() : FString(Datatype->idToken)
	});

	return ConvertedType;
}

const PFAccountManagementLinkOpenIdConnectRequest* ConvertLinkOpenIdConnectRequestToPlayfab(TSharedPtr<const FPFAccountManagementLinkOpenIdConnectRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementLinkOpenIdConnectRequest* ConvertedType = new PFAccountManagementLinkOpenIdConnectRequest{
		.connectionId = ConvertFStringToCharPtr(Datatype->connectionId),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.forceLink = Datatype->forceLink ? new bool(*Datatype->forceLink) : nullptr,
		.idToken = ConvertFStringToCharPtr(Datatype->idToken)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementClientLinkPSNAccountRequest> ConvertClientLinkPSNAccountRequestToUnreal(const PFAccountManagementClientLinkPSNAccountRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementClientLinkPSNAccountRequest> ConvertedType = MakeShared<FPFAccountManagementClientLinkPSNAccountRequest>(FPFAccountManagementClientLinkPSNAccountRequest{
		.authCode = Datatype->authCode == nullptr ? FString() : FString(Datatype->authCode),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.forceLink = TSharedPtr<const bool>(Datatype->forceLink),
		.issuerId = TSharedPtr<const int32>(Datatype->issuerId),
		.redirectUri = Datatype->redirectUri == nullptr ? FString() : FString(Datatype->redirectUri)
	});

	return ConvertedType;
}

const PFAccountManagementClientLinkPSNAccountRequest* ConvertClientLinkPSNAccountRequestToPlayfab(TSharedPtr<const FPFAccountManagementClientLinkPSNAccountRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementClientLinkPSNAccountRequest* ConvertedType = new PFAccountManagementClientLinkPSNAccountRequest{
		.authCode = ConvertFStringToCharPtr(Datatype->authCode),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.forceLink = Datatype->forceLink ? new bool(*Datatype->forceLink) : nullptr,
		.issuerId = Datatype->issuerId ? new int32(*Datatype->issuerId) : nullptr,
		.redirectUri = ConvertFStringToCharPtr(Datatype->redirectUri)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementLinkSteamAccountRequest> ConvertLinkSteamAccountRequestToUnreal(const PFAccountManagementLinkSteamAccountRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementLinkSteamAccountRequest> ConvertedType = MakeShared<FPFAccountManagementLinkSteamAccountRequest>(FPFAccountManagementLinkSteamAccountRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.forceLink = TSharedPtr<const bool>(Datatype->forceLink),
		.steamTicket = Datatype->steamTicket == nullptr ? FString() : FString(Datatype->steamTicket),
		.ticketIsServiceSpecific = TSharedPtr<const bool>(Datatype->ticketIsServiceSpecific)
	});

	return ConvertedType;
}

const PFAccountManagementLinkSteamAccountRequest* ConvertLinkSteamAccountRequestToPlayfab(TSharedPtr<const FPFAccountManagementLinkSteamAccountRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementLinkSteamAccountRequest* ConvertedType = new PFAccountManagementLinkSteamAccountRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.forceLink = Datatype->forceLink ? new bool(*Datatype->forceLink) : nullptr,
		.steamTicket = ConvertFStringToCharPtr(Datatype->steamTicket),
		.ticketIsServiceSpecific = Datatype->ticketIsServiceSpecific ? new bool(*Datatype->ticketIsServiceSpecific) : nullptr
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementLinkTwitchAccountRequest> ConvertLinkTwitchAccountRequestToUnreal(const PFAccountManagementLinkTwitchAccountRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementLinkTwitchAccountRequest> ConvertedType = MakeShared<FPFAccountManagementLinkTwitchAccountRequest>(FPFAccountManagementLinkTwitchAccountRequest{
		.accessToken = Datatype->accessToken == nullptr ? FString() : FString(Datatype->accessToken),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.forceLink = TSharedPtr<const bool>(Datatype->forceLink)
	});

	return ConvertedType;
}

const PFAccountManagementLinkTwitchAccountRequest* ConvertLinkTwitchAccountRequestToPlayfab(TSharedPtr<const FPFAccountManagementLinkTwitchAccountRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementLinkTwitchAccountRequest* ConvertedType = new PFAccountManagementLinkTwitchAccountRequest{
		.accessToken = ConvertFStringToCharPtr(Datatype->accessToken),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.forceLink = Datatype->forceLink ? new bool(*Datatype->forceLink) : nullptr
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementClientLinkXboxAccountRequest> ConvertClientLinkXboxAccountRequestToUnreal(const PFAccountManagementClientLinkXboxAccountRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementClientLinkXboxAccountRequest> ConvertedType = MakeShared<FPFAccountManagementClientLinkXboxAccountRequest>(FPFAccountManagementClientLinkXboxAccountRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.forceLink = TSharedPtr<const bool>(Datatype->forceLink),
#if defined(PF_GDK_AVAILABLE) && defined(PF_UE_GDK_SUPPORT)
		.user = Datatype->user == nullptr ? FGDKUserHandle() : FGDKUserHandle(Datatype->user)
#elif defined(PF_GDK_AVAILABLE)
		.user = Datatype->user == nullptr ? XUserHandle() : Datatype->user
#else
		.xboxToken = Datatype->xboxToken == nullptr ? FString() : FString(Datatype->xboxToken)
#endif
	});

	return ConvertedType;
}

const PFAccountManagementClientLinkXboxAccountRequest* ConvertClientLinkXboxAccountRequestToPlayfab(TSharedPtr<const FPFAccountManagementClientLinkXboxAccountRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementClientLinkXboxAccountRequest* ConvertedType = new PFAccountManagementClientLinkXboxAccountRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.forceLink = Datatype->forceLink ? new bool(*Datatype->forceLink) : nullptr,
#if defined(PF_GDK_AVAILABLE)
		.user = Datatype->user
#else
		.xboxToken = ConvertFStringToCharPtr(Datatype->xboxToken)
#endif
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementRemoveContactEmailRequest> ConvertRemoveContactEmailRequestToUnreal(const PFAccountManagementRemoveContactEmailRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementRemoveContactEmailRequest> ConvertedType = MakeShared<FPFAccountManagementRemoveContactEmailRequest>(FPFAccountManagementRemoveContactEmailRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount
	});

	return ConvertedType;
}

const PFAccountManagementRemoveContactEmailRequest* ConvertRemoveContactEmailRequestToPlayfab(TSharedPtr<const FPFAccountManagementRemoveContactEmailRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementRemoveContactEmailRequest* ConvertedType = new PFAccountManagementRemoveContactEmailRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementReportPlayerClientRequest> ConvertReportPlayerClientRequestToUnreal(const PFAccountManagementReportPlayerClientRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementReportPlayerClientRequest> ConvertedType = MakeShared<FPFAccountManagementReportPlayerClientRequest>(FPFAccountManagementReportPlayerClientRequest{
		.comment = Datatype->comment == nullptr ? FString() : FString(Datatype->comment),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.reporteeId = Datatype->reporteeId == nullptr ? FString() : FString(Datatype->reporteeId)
	});

	return ConvertedType;
}

const PFAccountManagementReportPlayerClientRequest* ConvertReportPlayerClientRequestToPlayfab(TSharedPtr<const FPFAccountManagementReportPlayerClientRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementReportPlayerClientRequest* ConvertedType = new PFAccountManagementReportPlayerClientRequest{
		.comment = ConvertFStringToCharPtr(Datatype->comment),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.reporteeId = ConvertFStringToCharPtr(Datatype->reporteeId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementReportPlayerClientResult> ConvertReportPlayerClientResultToUnreal(const PFAccountManagementReportPlayerClientResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementReportPlayerClientResult> ConvertedType = MakeShared<FPFAccountManagementReportPlayerClientResult>(FPFAccountManagementReportPlayerClientResult{
		.submissionsRemaining = Datatype->submissionsRemaining
	});

	return ConvertedType;
}

const PFAccountManagementReportPlayerClientResult* ConvertReportPlayerClientResultToPlayfab(TSharedPtr<const FPFAccountManagementReportPlayerClientResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementReportPlayerClientResult* ConvertedType = new PFAccountManagementReportPlayerClientResult{
		.submissionsRemaining = Datatype->submissionsRemaining
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementSendAccountRecoveryEmailRequest> ConvertSendAccountRecoveryEmailRequestToUnreal(const PFAccountManagementSendAccountRecoveryEmailRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementSendAccountRecoveryEmailRequest> ConvertedType = MakeShared<FPFAccountManagementSendAccountRecoveryEmailRequest>(FPFAccountManagementSendAccountRecoveryEmailRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.email = Datatype->email == nullptr ? FString() : FString(Datatype->email),
		.emailTemplateId = Datatype->emailTemplateId == nullptr ? FString() : FString(Datatype->emailTemplateId),
		.titleId = Datatype->titleId == nullptr ? FString() : FString(Datatype->titleId)
	});

	return ConvertedType;
}

const PFAccountManagementSendAccountRecoveryEmailRequest* ConvertSendAccountRecoveryEmailRequestToPlayfab(TSharedPtr<const FPFAccountManagementSendAccountRecoveryEmailRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementSendAccountRecoveryEmailRequest* ConvertedType = new PFAccountManagementSendAccountRecoveryEmailRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.email = ConvertFStringToCharPtr(Datatype->email),
		.emailTemplateId = ConvertFStringToCharPtr(Datatype->emailTemplateId),
		.titleId = ConvertFStringToCharPtr(Datatype->titleId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementUnlinkAndroidDeviceIDRequest> ConvertUnlinkAndroidDeviceIDRequestToUnreal(const PFAccountManagementUnlinkAndroidDeviceIDRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementUnlinkAndroidDeviceIDRequest> ConvertedType = MakeShared<FPFAccountManagementUnlinkAndroidDeviceIDRequest>(FPFAccountManagementUnlinkAndroidDeviceIDRequest{
		.androidDeviceId = Datatype->androidDeviceId == nullptr ? FString() : FString(Datatype->androidDeviceId),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount
	});

	return ConvertedType;
}

const PFAccountManagementUnlinkAndroidDeviceIDRequest* ConvertUnlinkAndroidDeviceIDRequestToPlayfab(TSharedPtr<const FPFAccountManagementUnlinkAndroidDeviceIDRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementUnlinkAndroidDeviceIDRequest* ConvertedType = new PFAccountManagementUnlinkAndroidDeviceIDRequest{
		.androidDeviceId = ConvertFStringToCharPtr(Datatype->androidDeviceId),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementUnlinkAppleRequest> ConvertUnlinkAppleRequestToUnreal(const PFAccountManagementUnlinkAppleRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementUnlinkAppleRequest> ConvertedType = MakeShared<FPFAccountManagementUnlinkAppleRequest>(FPFAccountManagementUnlinkAppleRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount
	});

	return ConvertedType;
}

const PFAccountManagementUnlinkAppleRequest* ConvertUnlinkAppleRequestToPlayfab(TSharedPtr<const FPFAccountManagementUnlinkAppleRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementUnlinkAppleRequest* ConvertedType = new PFAccountManagementUnlinkAppleRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementClientUnlinkBattleNetAccountRequest> ConvertClientUnlinkBattleNetAccountRequestToUnreal(const PFAccountManagementClientUnlinkBattleNetAccountRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementClientUnlinkBattleNetAccountRequest> ConvertedType = MakeShared<FPFAccountManagementClientUnlinkBattleNetAccountRequest>(FPFAccountManagementClientUnlinkBattleNetAccountRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount
	});

	return ConvertedType;
}

const PFAccountManagementClientUnlinkBattleNetAccountRequest* ConvertClientUnlinkBattleNetAccountRequestToPlayfab(TSharedPtr<const FPFAccountManagementClientUnlinkBattleNetAccountRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementClientUnlinkBattleNetAccountRequest* ConvertedType = new PFAccountManagementClientUnlinkBattleNetAccountRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementUnlinkCustomIDRequest> ConvertUnlinkCustomIDRequestToUnreal(const PFAccountManagementUnlinkCustomIDRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementUnlinkCustomIDRequest> ConvertedType = MakeShared<FPFAccountManagementUnlinkCustomIDRequest>(FPFAccountManagementUnlinkCustomIDRequest{
		.customId = Datatype->customId == nullptr ? FString() : FString(Datatype->customId),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount
	});

	return ConvertedType;
}

const PFAccountManagementUnlinkCustomIDRequest* ConvertUnlinkCustomIDRequestToPlayfab(TSharedPtr<const FPFAccountManagementUnlinkCustomIDRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementUnlinkCustomIDRequest* ConvertedType = new PFAccountManagementUnlinkCustomIDRequest{
		.customId = ConvertFStringToCharPtr(Datatype->customId),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementUnlinkFacebookAccountRequest> ConvertUnlinkFacebookAccountRequestToUnreal(const PFAccountManagementUnlinkFacebookAccountRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementUnlinkFacebookAccountRequest> ConvertedType = MakeShared<FPFAccountManagementUnlinkFacebookAccountRequest>(FPFAccountManagementUnlinkFacebookAccountRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount
	});

	return ConvertedType;
}

const PFAccountManagementUnlinkFacebookAccountRequest* ConvertUnlinkFacebookAccountRequestToPlayfab(TSharedPtr<const FPFAccountManagementUnlinkFacebookAccountRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementUnlinkFacebookAccountRequest* ConvertedType = new PFAccountManagementUnlinkFacebookAccountRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementUnlinkFacebookInstantGamesIdRequest> ConvertUnlinkFacebookInstantGamesIdRequestToUnreal(const PFAccountManagementUnlinkFacebookInstantGamesIdRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementUnlinkFacebookInstantGamesIdRequest> ConvertedType = MakeShared<FPFAccountManagementUnlinkFacebookInstantGamesIdRequest>(FPFAccountManagementUnlinkFacebookInstantGamesIdRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.facebookInstantGamesId = Datatype->facebookInstantGamesId == nullptr ? FString() : FString(Datatype->facebookInstantGamesId)
	});

	return ConvertedType;
}

const PFAccountManagementUnlinkFacebookInstantGamesIdRequest* ConvertUnlinkFacebookInstantGamesIdRequestToPlayfab(TSharedPtr<const FPFAccountManagementUnlinkFacebookInstantGamesIdRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementUnlinkFacebookInstantGamesIdRequest* ConvertedType = new PFAccountManagementUnlinkFacebookInstantGamesIdRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.facebookInstantGamesId = ConvertFStringToCharPtr(Datatype->facebookInstantGamesId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementUnlinkGameCenterAccountRequest> ConvertUnlinkGameCenterAccountRequestToUnreal(const PFAccountManagementUnlinkGameCenterAccountRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementUnlinkGameCenterAccountRequest> ConvertedType = MakeShared<FPFAccountManagementUnlinkGameCenterAccountRequest>(FPFAccountManagementUnlinkGameCenterAccountRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount
	});

	return ConvertedType;
}

const PFAccountManagementUnlinkGameCenterAccountRequest* ConvertUnlinkGameCenterAccountRequestToPlayfab(TSharedPtr<const FPFAccountManagementUnlinkGameCenterAccountRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementUnlinkGameCenterAccountRequest* ConvertedType = new PFAccountManagementUnlinkGameCenterAccountRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementUnlinkGoogleAccountRequest> ConvertUnlinkGoogleAccountRequestToUnreal(const PFAccountManagementUnlinkGoogleAccountRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementUnlinkGoogleAccountRequest> ConvertedType = MakeShared<FPFAccountManagementUnlinkGoogleAccountRequest>(FPFAccountManagementUnlinkGoogleAccountRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount
	});

	return ConvertedType;
}

const PFAccountManagementUnlinkGoogleAccountRequest* ConvertUnlinkGoogleAccountRequestToPlayfab(TSharedPtr<const FPFAccountManagementUnlinkGoogleAccountRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementUnlinkGoogleAccountRequest* ConvertedType = new PFAccountManagementUnlinkGoogleAccountRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementUnlinkGooglePlayGamesServicesAccountRequest> ConvertUnlinkGooglePlayGamesServicesAccountRequestToUnreal(const PFAccountManagementUnlinkGooglePlayGamesServicesAccountRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementUnlinkGooglePlayGamesServicesAccountRequest> ConvertedType = MakeShared<FPFAccountManagementUnlinkGooglePlayGamesServicesAccountRequest>(FPFAccountManagementUnlinkGooglePlayGamesServicesAccountRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount
	});

	return ConvertedType;
}

const PFAccountManagementUnlinkGooglePlayGamesServicesAccountRequest* ConvertUnlinkGooglePlayGamesServicesAccountRequestToPlayfab(TSharedPtr<const FPFAccountManagementUnlinkGooglePlayGamesServicesAccountRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementUnlinkGooglePlayGamesServicesAccountRequest* ConvertedType = new PFAccountManagementUnlinkGooglePlayGamesServicesAccountRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementUnlinkIOSDeviceIDRequest> ConvertUnlinkIOSDeviceIDRequestToUnreal(const PFAccountManagementUnlinkIOSDeviceIDRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementUnlinkIOSDeviceIDRequest> ConvertedType = MakeShared<FPFAccountManagementUnlinkIOSDeviceIDRequest>(FPFAccountManagementUnlinkIOSDeviceIDRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.deviceId = Datatype->deviceId == nullptr ? FString() : FString(Datatype->deviceId)
	});

	return ConvertedType;
}

const PFAccountManagementUnlinkIOSDeviceIDRequest* ConvertUnlinkIOSDeviceIDRequestToPlayfab(TSharedPtr<const FPFAccountManagementUnlinkIOSDeviceIDRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementUnlinkIOSDeviceIDRequest* ConvertedType = new PFAccountManagementUnlinkIOSDeviceIDRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.deviceId = ConvertFStringToCharPtr(Datatype->deviceId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementUnlinkKongregateAccountRequest> ConvertUnlinkKongregateAccountRequestToUnreal(const PFAccountManagementUnlinkKongregateAccountRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementUnlinkKongregateAccountRequest> ConvertedType = MakeShared<FPFAccountManagementUnlinkKongregateAccountRequest>(FPFAccountManagementUnlinkKongregateAccountRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount
	});

	return ConvertedType;
}

const PFAccountManagementUnlinkKongregateAccountRequest* ConvertUnlinkKongregateAccountRequestToPlayfab(TSharedPtr<const FPFAccountManagementUnlinkKongregateAccountRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementUnlinkKongregateAccountRequest* ConvertedType = new PFAccountManagementUnlinkKongregateAccountRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementClientUnlinkNintendoServiceAccountRequest> ConvertClientUnlinkNintendoServiceAccountRequestToUnreal(const PFAccountManagementClientUnlinkNintendoServiceAccountRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementClientUnlinkNintendoServiceAccountRequest> ConvertedType = MakeShared<FPFAccountManagementClientUnlinkNintendoServiceAccountRequest>(FPFAccountManagementClientUnlinkNintendoServiceAccountRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount
	});

	return ConvertedType;
}

const PFAccountManagementClientUnlinkNintendoServiceAccountRequest* ConvertClientUnlinkNintendoServiceAccountRequestToPlayfab(TSharedPtr<const FPFAccountManagementClientUnlinkNintendoServiceAccountRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementClientUnlinkNintendoServiceAccountRequest* ConvertedType = new PFAccountManagementClientUnlinkNintendoServiceAccountRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementClientUnlinkNintendoSwitchDeviceIdRequest> ConvertClientUnlinkNintendoSwitchDeviceIdRequestToUnreal(const PFAccountManagementClientUnlinkNintendoSwitchDeviceIdRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementClientUnlinkNintendoSwitchDeviceIdRequest> ConvertedType = MakeShared<FPFAccountManagementClientUnlinkNintendoSwitchDeviceIdRequest>(FPFAccountManagementClientUnlinkNintendoSwitchDeviceIdRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.nintendoSwitchDeviceId = Datatype->nintendoSwitchDeviceId == nullptr ? FString() : FString(Datatype->nintendoSwitchDeviceId)
	});

	return ConvertedType;
}

const PFAccountManagementClientUnlinkNintendoSwitchDeviceIdRequest* ConvertClientUnlinkNintendoSwitchDeviceIdRequestToPlayfab(TSharedPtr<const FPFAccountManagementClientUnlinkNintendoSwitchDeviceIdRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementClientUnlinkNintendoSwitchDeviceIdRequest* ConvertedType = new PFAccountManagementClientUnlinkNintendoSwitchDeviceIdRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.nintendoSwitchDeviceId = ConvertFStringToCharPtr(Datatype->nintendoSwitchDeviceId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementUnlinkOpenIdConnectRequest> ConvertUnlinkOpenIdConnectRequestToUnreal(const PFAccountManagementUnlinkOpenIdConnectRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementUnlinkOpenIdConnectRequest> ConvertedType = MakeShared<FPFAccountManagementUnlinkOpenIdConnectRequest>(FPFAccountManagementUnlinkOpenIdConnectRequest{
		.connectionId = Datatype->connectionId == nullptr ? FString() : FString(Datatype->connectionId),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount
	});

	return ConvertedType;
}

const PFAccountManagementUnlinkOpenIdConnectRequest* ConvertUnlinkOpenIdConnectRequestToPlayfab(TSharedPtr<const FPFAccountManagementUnlinkOpenIdConnectRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementUnlinkOpenIdConnectRequest* ConvertedType = new PFAccountManagementUnlinkOpenIdConnectRequest{
		.connectionId = ConvertFStringToCharPtr(Datatype->connectionId),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementClientUnlinkPSNAccountRequest> ConvertClientUnlinkPSNAccountRequestToUnreal(const PFAccountManagementClientUnlinkPSNAccountRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementClientUnlinkPSNAccountRequest> ConvertedType = MakeShared<FPFAccountManagementClientUnlinkPSNAccountRequest>(FPFAccountManagementClientUnlinkPSNAccountRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount
	});

	return ConvertedType;
}

const PFAccountManagementClientUnlinkPSNAccountRequest* ConvertClientUnlinkPSNAccountRequestToPlayfab(TSharedPtr<const FPFAccountManagementClientUnlinkPSNAccountRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementClientUnlinkPSNAccountRequest* ConvertedType = new PFAccountManagementClientUnlinkPSNAccountRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementUnlinkSteamAccountRequest> ConvertUnlinkSteamAccountRequestToUnreal(const PFAccountManagementUnlinkSteamAccountRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementUnlinkSteamAccountRequest> ConvertedType = MakeShared<FPFAccountManagementUnlinkSteamAccountRequest>(FPFAccountManagementUnlinkSteamAccountRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount
	});

	return ConvertedType;
}

const PFAccountManagementUnlinkSteamAccountRequest* ConvertUnlinkSteamAccountRequestToPlayfab(TSharedPtr<const FPFAccountManagementUnlinkSteamAccountRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementUnlinkSteamAccountRequest* ConvertedType = new PFAccountManagementUnlinkSteamAccountRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementUnlinkTwitchAccountRequest> ConvertUnlinkTwitchAccountRequestToUnreal(const PFAccountManagementUnlinkTwitchAccountRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementUnlinkTwitchAccountRequest> ConvertedType = MakeShared<FPFAccountManagementUnlinkTwitchAccountRequest>(FPFAccountManagementUnlinkTwitchAccountRequest{
		.accessToken = Datatype->accessToken == nullptr ? FString() : FString(Datatype->accessToken),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount
	});

	return ConvertedType;
}

const PFAccountManagementUnlinkTwitchAccountRequest* ConvertUnlinkTwitchAccountRequestToPlayfab(TSharedPtr<const FPFAccountManagementUnlinkTwitchAccountRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementUnlinkTwitchAccountRequest* ConvertedType = new PFAccountManagementUnlinkTwitchAccountRequest{
		.accessToken = ConvertFStringToCharPtr(Datatype->accessToken),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementClientUnlinkXboxAccountRequest> ConvertClientUnlinkXboxAccountRequestToUnreal(const PFAccountManagementClientUnlinkXboxAccountRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementClientUnlinkXboxAccountRequest> ConvertedType = MakeShared<FPFAccountManagementClientUnlinkXboxAccountRequest>(FPFAccountManagementClientUnlinkXboxAccountRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount
	});

	return ConvertedType;
}

const PFAccountManagementClientUnlinkXboxAccountRequest* ConvertClientUnlinkXboxAccountRequestToPlayfab(TSharedPtr<const FPFAccountManagementClientUnlinkXboxAccountRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementClientUnlinkXboxAccountRequest* ConvertedType = new PFAccountManagementClientUnlinkXboxAccountRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementClientUpdateAvatarUrlRequest> ConvertClientUpdateAvatarUrlRequestToUnreal(const PFAccountManagementClientUpdateAvatarUrlRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementClientUpdateAvatarUrlRequest> ConvertedType = MakeShared<FPFAccountManagementClientUpdateAvatarUrlRequest>(FPFAccountManagementClientUpdateAvatarUrlRequest{
		.imageUrl = Datatype->imageUrl == nullptr ? FString() : FString(Datatype->imageUrl)
	});

	return ConvertedType;
}

const PFAccountManagementClientUpdateAvatarUrlRequest* ConvertClientUpdateAvatarUrlRequestToPlayfab(TSharedPtr<const FPFAccountManagementClientUpdateAvatarUrlRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementClientUpdateAvatarUrlRequest* ConvertedType = new PFAccountManagementClientUpdateAvatarUrlRequest{
		.imageUrl = ConvertFStringToCharPtr(Datatype->imageUrl)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementUpdateUserTitleDisplayNameRequest> ConvertUpdateUserTitleDisplayNameRequestToUnreal(const PFAccountManagementUpdateUserTitleDisplayNameRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementUpdateUserTitleDisplayNameRequest> ConvertedType = MakeShared<FPFAccountManagementUpdateUserTitleDisplayNameRequest>(FPFAccountManagementUpdateUserTitleDisplayNameRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.displayName = Datatype->displayName == nullptr ? FString() : FString(Datatype->displayName)
	});

	return ConvertedType;
}

const PFAccountManagementUpdateUserTitleDisplayNameRequest* ConvertUpdateUserTitleDisplayNameRequestToPlayfab(TSharedPtr<const FPFAccountManagementUpdateUserTitleDisplayNameRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementUpdateUserTitleDisplayNameRequest* ConvertedType = new PFAccountManagementUpdateUserTitleDisplayNameRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.displayName = ConvertFStringToCharPtr(Datatype->displayName)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementUpdateUserTitleDisplayNameResult> ConvertUpdateUserTitleDisplayNameResultToUnreal(const PFAccountManagementUpdateUserTitleDisplayNameResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementUpdateUserTitleDisplayNameResult> ConvertedType = MakeShared<FPFAccountManagementUpdateUserTitleDisplayNameResult>(FPFAccountManagementUpdateUserTitleDisplayNameResult{
		.displayName = Datatype->displayName == nullptr ? FString() : FString(Datatype->displayName)
	});

	return ConvertedType;
}

const PFAccountManagementUpdateUserTitleDisplayNameResult* ConvertUpdateUserTitleDisplayNameResultToPlayfab(TSharedPtr<const FPFAccountManagementUpdateUserTitleDisplayNameResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementUpdateUserTitleDisplayNameResult* ConvertedType = new PFAccountManagementUpdateUserTitleDisplayNameResult{
		.displayName = ConvertFStringToCharPtr(Datatype->displayName)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementBanRequest> ConvertBanRequestToUnreal(const PFAccountManagementBanRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementBanRequest> ConvertedType = MakeShared<FPFAccountManagementBanRequest>(FPFAccountManagementBanRequest{
		.durationInHours = TSharedPtr<const uint32>(Datatype->durationInHours),
		.IPAddress = Datatype->IPAddress == nullptr ? FString() : FString(Datatype->IPAddress),
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId),
		.reason = Datatype->reason == nullptr ? FString() : FString(Datatype->reason),
		.userFamilyType = MakeShared<FPFAccountManagementUserFamilyType>(ConvertUserFamilyTypeToUnreal(Datatype->userFamilyType))
	});

	return ConvertedType;
}

const PFAccountManagementBanRequest* ConvertBanRequestToPlayfab(TSharedPtr<const FPFAccountManagementBanRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementBanRequest* ConvertedType = new PFAccountManagementBanRequest{
		.durationInHours = Datatype->durationInHours ? new uint32(*Datatype->durationInHours) : nullptr,
		.IPAddress = ConvertFStringToCharPtr(Datatype->IPAddress),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId),
		.reason = ConvertFStringToCharPtr(Datatype->reason),
		.userFamilyType = new PFAccountManagementUserFamilyType(ConvertUserFamilyTypeToPlayfab(Datatype->userFamilyType))
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementBanUsersRequest> ConvertBanUsersRequestToUnreal(const PFAccountManagementBanUsersRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementBanUsersRequest> ConvertedType = MakeShared<FPFAccountManagementBanUsersRequest>(FPFAccountManagementBanUsersRequest{
		.bans = ConvertPlayfabArrayToUnreal<PFAccountManagementBanRequest, FPFAccountManagementBanRequest>(Datatype->bans, Datatype->bansCount, ConvertBanRequestToUnreal),
		.bansCount = Datatype->bansCount,
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount
	});

	return ConvertedType;
}

const PFAccountManagementBanUsersRequest* ConvertBanUsersRequestToPlayfab(TSharedPtr<const FPFAccountManagementBanUsersRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementBanUsersRequest* ConvertedType = new PFAccountManagementBanUsersRequest{
		.bans = ConvertUnrealArrayToPlayfab<PFAccountManagementBanRequest, FPFAccountManagementBanRequest>(Datatype->bans, ConvertBanRequestToPlayfab),
		.bansCount = (uint32_t)Datatype->bans.Num(),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementBanInfo> ConvertBanInfoToUnreal(const PFAccountManagementBanInfo* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementBanInfo> ConvertedType = MakeShared<FPFAccountManagementBanInfo>(FPFAccountManagementBanInfo{
		.active = Datatype->active,
		.banId = Datatype->banId == nullptr ? FString() : FString(Datatype->banId),
		.created = ConvertTimeToUnreal(Datatype->created),
		.expires = ConvertTimeToUnreal(Datatype->expires),
		.IPAddress = Datatype->IPAddress == nullptr ? FString() : FString(Datatype->IPAddress),
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId),
		.reason = Datatype->reason == nullptr ? FString() : FString(Datatype->reason),
		.userFamilyType = Datatype->userFamilyType == nullptr ? FString() : FString(Datatype->userFamilyType)
	});

	return ConvertedType;
}

const PFAccountManagementBanInfo* ConvertBanInfoToPlayfab(TSharedPtr<const FPFAccountManagementBanInfo> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementBanInfo* ConvertedType = new PFAccountManagementBanInfo{
		.active = Datatype->active,
		.banId = ConvertFStringToCharPtr(Datatype->banId),
		.created = ConvertFDateTimeToPlayfab(Datatype->created),
		.expires = ConvertFDateTimeToPlayfab(Datatype->expires),
		.IPAddress = ConvertFStringToCharPtr(Datatype->IPAddress),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId),
		.reason = ConvertFStringToCharPtr(Datatype->reason),
		.userFamilyType = ConvertFStringToCharPtr(Datatype->userFamilyType)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementBanUsersResult> ConvertBanUsersResultToUnreal(const PFAccountManagementBanUsersResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementBanUsersResult> ConvertedType = MakeShared<FPFAccountManagementBanUsersResult>(FPFAccountManagementBanUsersResult{
		.banData = ConvertPlayfabArrayToUnreal<PFAccountManagementBanInfo, FPFAccountManagementBanInfo>(Datatype->banData, Datatype->banDataCount, ConvertBanInfoToUnreal),
		.banDataCount = Datatype->banDataCount
	});

	return ConvertedType;
}

const PFAccountManagementBanUsersResult* ConvertBanUsersResultToPlayfab(TSharedPtr<const FPFAccountManagementBanUsersResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementBanUsersResult* ConvertedType = new PFAccountManagementBanUsersResult{
		.banData = ConvertUnrealArrayToPlayfab<PFAccountManagementBanInfo, FPFAccountManagementBanInfo>(Datatype->banData, ConvertBanInfoToPlayfab),
		.banDataCount = (uint32_t)Datatype->banData.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementDeletePlayerRequest> ConvertDeletePlayerRequestToUnreal(const PFAccountManagementDeletePlayerRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementDeletePlayerRequest> ConvertedType = MakeShared<FPFAccountManagementDeletePlayerRequest>(FPFAccountManagementDeletePlayerRequest{
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId)
	});

	return ConvertedType;
}

const PFAccountManagementDeletePlayerRequest* ConvertDeletePlayerRequestToPlayfab(TSharedPtr<const FPFAccountManagementDeletePlayerRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementDeletePlayerRequest* ConvertedType = new PFAccountManagementDeletePlayerRequest{
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetServerCustomIDsFromPlayFabIDsRequest> ConvertGetServerCustomIDsFromPlayFabIDsRequestToUnreal(const PFAccountManagementGetServerCustomIDsFromPlayFabIDsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetServerCustomIDsFromPlayFabIDsRequest> ConvertedType = MakeShared<FPFAccountManagementGetServerCustomIDsFromPlayFabIDsRequest>(FPFAccountManagementGetServerCustomIDsFromPlayFabIDsRequest{
		.playFabIDs = ConvertCharArrayToUnreal(Datatype->playFabIDs, Datatype->playFabIDsCount),
		.playFabIDsCount = Datatype->playFabIDsCount
	});

	return ConvertedType;
}

const PFAccountManagementGetServerCustomIDsFromPlayFabIDsRequest* ConvertGetServerCustomIDsFromPlayFabIDsRequestToPlayfab(TSharedPtr<const FPFAccountManagementGetServerCustomIDsFromPlayFabIDsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetServerCustomIDsFromPlayFabIDsRequest* ConvertedType = new PFAccountManagementGetServerCustomIDsFromPlayFabIDsRequest{
		.playFabIDs = ConvertFStringArrayToPlayfab(Datatype->playFabIDs),
		.playFabIDsCount = (uint32_t)Datatype->playFabIDs.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementServerCustomIDPlayFabIDPair> ConvertServerCustomIDPlayFabIDPairToUnreal(const PFAccountManagementServerCustomIDPlayFabIDPair* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementServerCustomIDPlayFabIDPair> ConvertedType = MakeShared<FPFAccountManagementServerCustomIDPlayFabIDPair>(FPFAccountManagementServerCustomIDPlayFabIDPair{
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId),
		.serverCustomId = Datatype->serverCustomId == nullptr ? FString() : FString(Datatype->serverCustomId)
	});

	return ConvertedType;
}

const PFAccountManagementServerCustomIDPlayFabIDPair* ConvertServerCustomIDPlayFabIDPairToPlayfab(TSharedPtr<const FPFAccountManagementServerCustomIDPlayFabIDPair> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementServerCustomIDPlayFabIDPair* ConvertedType = new PFAccountManagementServerCustomIDPlayFabIDPair{
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId),
		.serverCustomId = ConvertFStringToCharPtr(Datatype->serverCustomId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetServerCustomIDsFromPlayFabIDsResult> ConvertGetServerCustomIDsFromPlayFabIDsResultToUnreal(const PFAccountManagementGetServerCustomIDsFromPlayFabIDsResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetServerCustomIDsFromPlayFabIDsResult> ConvertedType = MakeShared<FPFAccountManagementGetServerCustomIDsFromPlayFabIDsResult>(FPFAccountManagementGetServerCustomIDsFromPlayFabIDsResult{
		.data = ConvertPlayfabArrayToUnreal<PFAccountManagementServerCustomIDPlayFabIDPair, FPFAccountManagementServerCustomIDPlayFabIDPair>(Datatype->data, Datatype->dataCount, ConvertServerCustomIDPlayFabIDPairToUnreal),
		.dataCount = Datatype->dataCount
	});

	return ConvertedType;
}

const PFAccountManagementGetServerCustomIDsFromPlayFabIDsResult* ConvertGetServerCustomIDsFromPlayFabIDsResultToPlayfab(TSharedPtr<const FPFAccountManagementGetServerCustomIDsFromPlayFabIDsResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetServerCustomIDsFromPlayFabIDsResult* ConvertedType = new PFAccountManagementGetServerCustomIDsFromPlayFabIDsResult{
		.data = ConvertUnrealArrayToPlayfab<PFAccountManagementServerCustomIDPlayFabIDPair, FPFAccountManagementServerCustomIDPlayFabIDPair>(Datatype->data, ConvertServerCustomIDPlayFabIDPairToPlayfab),
		.dataCount = (uint32_t)Datatype->data.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetUserAccountInfoRequest> ConvertGetUserAccountInfoRequestToUnreal(const PFAccountManagementGetUserAccountInfoRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetUserAccountInfoRequest> ConvertedType = MakeShared<FPFAccountManagementGetUserAccountInfoRequest>(FPFAccountManagementGetUserAccountInfoRequest{
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId)
	});

	return ConvertedType;
}

const PFAccountManagementGetUserAccountInfoRequest* ConvertGetUserAccountInfoRequestToPlayfab(TSharedPtr<const FPFAccountManagementGetUserAccountInfoRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetUserAccountInfoRequest* ConvertedType = new PFAccountManagementGetUserAccountInfoRequest{
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetUserAccountInfoResult> ConvertGetUserAccountInfoResultToUnreal(const PFAccountManagementGetUserAccountInfoResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetUserAccountInfoResult> ConvertedType = MakeShared<FPFAccountManagementGetUserAccountInfoResult>(FPFAccountManagementGetUserAccountInfoResult{
		.userInfo = ConvertUserAccountInfoToUnreal(Datatype->userInfo)
	});

	return ConvertedType;
}

const PFAccountManagementGetUserAccountInfoResult* ConvertGetUserAccountInfoResultToPlayfab(TSharedPtr<const FPFAccountManagementGetUserAccountInfoResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetUserAccountInfoResult* ConvertedType = new PFAccountManagementGetUserAccountInfoResult{
		.userInfo = ConvertUserAccountInfoToPlayfab(Datatype->userInfo)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetUserBansRequest> ConvertGetUserBansRequestToUnreal(const PFAccountManagementGetUserBansRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetUserBansRequest> ConvertedType = MakeShared<FPFAccountManagementGetUserBansRequest>(FPFAccountManagementGetUserBansRequest{
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId)
	});

	return ConvertedType;
}

const PFAccountManagementGetUserBansRequest* ConvertGetUserBansRequestToPlayfab(TSharedPtr<const FPFAccountManagementGetUserBansRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetUserBansRequest* ConvertedType = new PFAccountManagementGetUserBansRequest{
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetUserBansResult> ConvertGetUserBansResultToUnreal(const PFAccountManagementGetUserBansResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetUserBansResult> ConvertedType = MakeShared<FPFAccountManagementGetUserBansResult>(FPFAccountManagementGetUserBansResult{
		.banData = ConvertPlayfabArrayToUnreal<PFAccountManagementBanInfo, FPFAccountManagementBanInfo>(Datatype->banData, Datatype->banDataCount, ConvertBanInfoToUnreal),
		.banDataCount = Datatype->banDataCount
	});

	return ConvertedType;
}

const PFAccountManagementGetUserBansResult* ConvertGetUserBansResultToPlayfab(TSharedPtr<const FPFAccountManagementGetUserBansResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetUserBansResult* ConvertedType = new PFAccountManagementGetUserBansResult{
		.banData = ConvertUnrealArrayToPlayfab<PFAccountManagementBanInfo, FPFAccountManagementBanInfo>(Datatype->banData, ConvertBanInfoToPlayfab),
		.banDataCount = (uint32_t)Datatype->banData.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementServerLinkBattleNetAccountRequest> ConvertServerLinkBattleNetAccountRequestToUnreal(const PFAccountManagementServerLinkBattleNetAccountRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementServerLinkBattleNetAccountRequest> ConvertedType = MakeShared<FPFAccountManagementServerLinkBattleNetAccountRequest>(FPFAccountManagementServerLinkBattleNetAccountRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.forceLink = TSharedPtr<const bool>(Datatype->forceLink),
		.identityToken = Datatype->identityToken == nullptr ? FString() : FString(Datatype->identityToken),
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId)
	});

	return ConvertedType;
}

const PFAccountManagementServerLinkBattleNetAccountRequest* ConvertServerLinkBattleNetAccountRequestToPlayfab(TSharedPtr<const FPFAccountManagementServerLinkBattleNetAccountRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementServerLinkBattleNetAccountRequest* ConvertedType = new PFAccountManagementServerLinkBattleNetAccountRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.forceLink = Datatype->forceLink ? new bool(*Datatype->forceLink) : nullptr,
		.identityToken = ConvertFStringToCharPtr(Datatype->identityToken),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementServerLinkNintendoServiceAccountRequest> ConvertServerLinkNintendoServiceAccountRequestToUnreal(const PFAccountManagementServerLinkNintendoServiceAccountRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementServerLinkNintendoServiceAccountRequest> ConvertedType = MakeShared<FPFAccountManagementServerLinkNintendoServiceAccountRequest>(FPFAccountManagementServerLinkNintendoServiceAccountRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.forceLink = TSharedPtr<const bool>(Datatype->forceLink),
		.identityToken = Datatype->identityToken == nullptr ? FString() : FString(Datatype->identityToken),
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId)
	});

	return ConvertedType;
}

const PFAccountManagementServerLinkNintendoServiceAccountRequest* ConvertServerLinkNintendoServiceAccountRequestToPlayfab(TSharedPtr<const FPFAccountManagementServerLinkNintendoServiceAccountRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementServerLinkNintendoServiceAccountRequest* ConvertedType = new PFAccountManagementServerLinkNintendoServiceAccountRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.forceLink = Datatype->forceLink ? new bool(*Datatype->forceLink) : nullptr,
		.identityToken = ConvertFStringToCharPtr(Datatype->identityToken),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementLinkNintendoServiceAccountSubjectRequest> ConvertLinkNintendoServiceAccountSubjectRequestToUnreal(const PFAccountManagementLinkNintendoServiceAccountSubjectRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementLinkNintendoServiceAccountSubjectRequest> ConvertedType = MakeShared<FPFAccountManagementLinkNintendoServiceAccountSubjectRequest>(FPFAccountManagementLinkNintendoServiceAccountSubjectRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.forceLink = TSharedPtr<const bool>(Datatype->forceLink),
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId),
		.subject = Datatype->subject == nullptr ? FString() : FString(Datatype->subject)
	});

	return ConvertedType;
}

const PFAccountManagementLinkNintendoServiceAccountSubjectRequest* ConvertLinkNintendoServiceAccountSubjectRequestToPlayfab(TSharedPtr<const FPFAccountManagementLinkNintendoServiceAccountSubjectRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementLinkNintendoServiceAccountSubjectRequest* ConvertedType = new PFAccountManagementLinkNintendoServiceAccountSubjectRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.forceLink = Datatype->forceLink ? new bool(*Datatype->forceLink) : nullptr,
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId),
		.subject = ConvertFStringToCharPtr(Datatype->subject)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementServerLinkNintendoSwitchDeviceIdRequest> ConvertServerLinkNintendoSwitchDeviceIdRequestToUnreal(const PFAccountManagementServerLinkNintendoSwitchDeviceIdRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementServerLinkNintendoSwitchDeviceIdRequest> ConvertedType = MakeShared<FPFAccountManagementServerLinkNintendoSwitchDeviceIdRequest>(FPFAccountManagementServerLinkNintendoSwitchDeviceIdRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.forceLink = TSharedPtr<const bool>(Datatype->forceLink),
		.nintendoSwitchDeviceId = Datatype->nintendoSwitchDeviceId == nullptr ? FString() : FString(Datatype->nintendoSwitchDeviceId),
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId)
	});

	return ConvertedType;
}

const PFAccountManagementServerLinkNintendoSwitchDeviceIdRequest* ConvertServerLinkNintendoSwitchDeviceIdRequestToPlayfab(TSharedPtr<const FPFAccountManagementServerLinkNintendoSwitchDeviceIdRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementServerLinkNintendoSwitchDeviceIdRequest* ConvertedType = new PFAccountManagementServerLinkNintendoSwitchDeviceIdRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.forceLink = Datatype->forceLink ? new bool(*Datatype->forceLink) : nullptr,
		.nintendoSwitchDeviceId = ConvertFStringToCharPtr(Datatype->nintendoSwitchDeviceId),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementServerLinkPSNAccountRequest> ConvertServerLinkPSNAccountRequestToUnreal(const PFAccountManagementServerLinkPSNAccountRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementServerLinkPSNAccountRequest> ConvertedType = MakeShared<FPFAccountManagementServerLinkPSNAccountRequest>(FPFAccountManagementServerLinkPSNAccountRequest{
		.authCode = Datatype->authCode == nullptr ? FString() : FString(Datatype->authCode),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.forceLink = TSharedPtr<const bool>(Datatype->forceLink),
		.issuerId = TSharedPtr<const int32>(Datatype->issuerId),
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId),
		.redirectUri = Datatype->redirectUri == nullptr ? FString() : FString(Datatype->redirectUri)
	});

	return ConvertedType;
}

const PFAccountManagementServerLinkPSNAccountRequest* ConvertServerLinkPSNAccountRequestToPlayfab(TSharedPtr<const FPFAccountManagementServerLinkPSNAccountRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementServerLinkPSNAccountRequest* ConvertedType = new PFAccountManagementServerLinkPSNAccountRequest{
		.authCode = ConvertFStringToCharPtr(Datatype->authCode),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.forceLink = Datatype->forceLink ? new bool(*Datatype->forceLink) : nullptr,
		.issuerId = Datatype->issuerId ? new int32(*Datatype->issuerId) : nullptr,
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId),
		.redirectUri = ConvertFStringToCharPtr(Datatype->redirectUri)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementLinkPSNIdRequest> ConvertLinkPSNIdRequestToUnreal(const PFAccountManagementLinkPSNIdRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementLinkPSNIdRequest> ConvertedType = MakeShared<FPFAccountManagementLinkPSNIdRequest>(FPFAccountManagementLinkPSNIdRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.forceLink = TSharedPtr<const bool>(Datatype->forceLink),
		.issuerId = TSharedPtr<const int32>(Datatype->issuerId),
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId),
		.PSNUserId = Datatype->PSNUserId == nullptr ? FString() : FString(Datatype->PSNUserId)
	});

	return ConvertedType;
}

const PFAccountManagementLinkPSNIdRequest* ConvertLinkPSNIdRequestToPlayfab(TSharedPtr<const FPFAccountManagementLinkPSNIdRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementLinkPSNIdRequest* ConvertedType = new PFAccountManagementLinkPSNIdRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.forceLink = Datatype->forceLink ? new bool(*Datatype->forceLink) : nullptr,
		.issuerId = Datatype->issuerId ? new int32(*Datatype->issuerId) : nullptr,
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId),
		.PSNUserId = ConvertFStringToCharPtr(Datatype->PSNUserId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementLinkServerCustomIdRequest> ConvertLinkServerCustomIdRequestToUnreal(const PFAccountManagementLinkServerCustomIdRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementLinkServerCustomIdRequest> ConvertedType = MakeShared<FPFAccountManagementLinkServerCustomIdRequest>(FPFAccountManagementLinkServerCustomIdRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.forceLink = TSharedPtr<const bool>(Datatype->forceLink),
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId),
		.serverCustomId = Datatype->serverCustomId == nullptr ? FString() : FString(Datatype->serverCustomId)
	});

	return ConvertedType;
}

const PFAccountManagementLinkServerCustomIdRequest* ConvertLinkServerCustomIdRequestToPlayfab(TSharedPtr<const FPFAccountManagementLinkServerCustomIdRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementLinkServerCustomIdRequest* ConvertedType = new PFAccountManagementLinkServerCustomIdRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.forceLink = Datatype->forceLink ? new bool(*Datatype->forceLink) : nullptr,
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId),
		.serverCustomId = ConvertFStringToCharPtr(Datatype->serverCustomId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementLinkSteamIdRequest> ConvertLinkSteamIdRequestToUnreal(const PFAccountManagementLinkSteamIdRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementLinkSteamIdRequest> ConvertedType = MakeShared<FPFAccountManagementLinkSteamIdRequest>(FPFAccountManagementLinkSteamIdRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.forceLink = TSharedPtr<const bool>(Datatype->forceLink),
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId),
		.steamId = Datatype->steamId == nullptr ? FString() : FString(Datatype->steamId)
	});

	return ConvertedType;
}

const PFAccountManagementLinkSteamIdRequest* ConvertLinkSteamIdRequestToPlayfab(TSharedPtr<const FPFAccountManagementLinkSteamIdRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementLinkSteamIdRequest* ConvertedType = new PFAccountManagementLinkSteamIdRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.forceLink = Datatype->forceLink ? new bool(*Datatype->forceLink) : nullptr,
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId),
		.steamId = ConvertFStringToCharPtr(Datatype->steamId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementServerLinkXboxAccountRequest> ConvertServerLinkXboxAccountRequestToUnreal(const PFAccountManagementServerLinkXboxAccountRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementServerLinkXboxAccountRequest> ConvertedType = MakeShared<FPFAccountManagementServerLinkXboxAccountRequest>(FPFAccountManagementServerLinkXboxAccountRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.forceLink = TSharedPtr<const bool>(Datatype->forceLink),
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId),
		.xboxToken = Datatype->xboxToken == nullptr ? FString() : FString(Datatype->xboxToken)
	});

	return ConvertedType;
}

const PFAccountManagementServerLinkXboxAccountRequest* ConvertServerLinkXboxAccountRequestToPlayfab(TSharedPtr<const FPFAccountManagementServerLinkXboxAccountRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementServerLinkXboxAccountRequest* ConvertedType = new PFAccountManagementServerLinkXboxAccountRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.forceLink = Datatype->forceLink ? new bool(*Datatype->forceLink) : nullptr,
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId),
		.xboxToken = ConvertFStringToCharPtr(Datatype->xboxToken)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementLinkXboxIdRequest> ConvertLinkXboxIdRequestToUnreal(const PFAccountManagementLinkXboxIdRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementLinkXboxIdRequest> ConvertedType = MakeShared<FPFAccountManagementLinkXboxIdRequest>(FPFAccountManagementLinkXboxIdRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.forceLink = TSharedPtr<const bool>(Datatype->forceLink),
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId),
		.sandbox = Datatype->sandbox == nullptr ? FString() : FString(Datatype->sandbox),
		.xboxId = Datatype->xboxId == nullptr ? FString() : FString(Datatype->xboxId)
	});

	return ConvertedType;
}

const PFAccountManagementLinkXboxIdRequest* ConvertLinkXboxIdRequestToPlayfab(TSharedPtr<const FPFAccountManagementLinkXboxIdRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementLinkXboxIdRequest* ConvertedType = new PFAccountManagementLinkXboxIdRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.forceLink = Datatype->forceLink ? new bool(*Datatype->forceLink) : nullptr,
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId),
		.sandbox = ConvertFStringToCharPtr(Datatype->sandbox),
		.xboxId = ConvertFStringToCharPtr(Datatype->xboxId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementRevokeAllBansForUserRequest> ConvertRevokeAllBansForUserRequestToUnreal(const PFAccountManagementRevokeAllBansForUserRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementRevokeAllBansForUserRequest> ConvertedType = MakeShared<FPFAccountManagementRevokeAllBansForUserRequest>(FPFAccountManagementRevokeAllBansForUserRequest{
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId)
	});

	return ConvertedType;
}

const PFAccountManagementRevokeAllBansForUserRequest* ConvertRevokeAllBansForUserRequestToPlayfab(TSharedPtr<const FPFAccountManagementRevokeAllBansForUserRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementRevokeAllBansForUserRequest* ConvertedType = new PFAccountManagementRevokeAllBansForUserRequest{
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementRevokeAllBansForUserResult> ConvertRevokeAllBansForUserResultToUnreal(const PFAccountManagementRevokeAllBansForUserResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementRevokeAllBansForUserResult> ConvertedType = MakeShared<FPFAccountManagementRevokeAllBansForUserResult>(FPFAccountManagementRevokeAllBansForUserResult{
		.banData = ConvertPlayfabArrayToUnreal<PFAccountManagementBanInfo, FPFAccountManagementBanInfo>(Datatype->banData, Datatype->banDataCount, ConvertBanInfoToUnreal),
		.banDataCount = Datatype->banDataCount
	});

	return ConvertedType;
}

const PFAccountManagementRevokeAllBansForUserResult* ConvertRevokeAllBansForUserResultToPlayfab(TSharedPtr<const FPFAccountManagementRevokeAllBansForUserResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementRevokeAllBansForUserResult* ConvertedType = new PFAccountManagementRevokeAllBansForUserResult{
		.banData = ConvertUnrealArrayToPlayfab<PFAccountManagementBanInfo, FPFAccountManagementBanInfo>(Datatype->banData, ConvertBanInfoToPlayfab),
		.banDataCount = (uint32_t)Datatype->banData.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementRevokeBansRequest> ConvertRevokeBansRequestToUnreal(const PFAccountManagementRevokeBansRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementRevokeBansRequest> ConvertedType = MakeShared<FPFAccountManagementRevokeBansRequest>(FPFAccountManagementRevokeBansRequest{
		.banIds = ConvertCharArrayToUnreal(Datatype->banIds, Datatype->banIdsCount),
		.banIdsCount = Datatype->banIdsCount
	});

	return ConvertedType;
}

const PFAccountManagementRevokeBansRequest* ConvertRevokeBansRequestToPlayfab(TSharedPtr<const FPFAccountManagementRevokeBansRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementRevokeBansRequest* ConvertedType = new PFAccountManagementRevokeBansRequest{
		.banIds = ConvertFStringArrayToPlayfab(Datatype->banIds),
		.banIdsCount = (uint32_t)Datatype->banIds.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementRevokeBansResult> ConvertRevokeBansResultToUnreal(const PFAccountManagementRevokeBansResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementRevokeBansResult> ConvertedType = MakeShared<FPFAccountManagementRevokeBansResult>(FPFAccountManagementRevokeBansResult{
		.banData = ConvertPlayfabArrayToUnreal<PFAccountManagementBanInfo, FPFAccountManagementBanInfo>(Datatype->banData, Datatype->banDataCount, ConvertBanInfoToUnreal),
		.banDataCount = Datatype->banDataCount
	});

	return ConvertedType;
}

const PFAccountManagementRevokeBansResult* ConvertRevokeBansResultToPlayfab(TSharedPtr<const FPFAccountManagementRevokeBansResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementRevokeBansResult* ConvertedType = new PFAccountManagementRevokeBansResult{
		.banData = ConvertUnrealArrayToPlayfab<PFAccountManagementBanInfo, FPFAccountManagementBanInfo>(Datatype->banData, ConvertBanInfoToPlayfab),
		.banDataCount = (uint32_t)Datatype->banData.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementSendCustomAccountRecoveryEmailRequest> ConvertSendCustomAccountRecoveryEmailRequestToUnreal(const PFAccountManagementSendCustomAccountRecoveryEmailRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementSendCustomAccountRecoveryEmailRequest> ConvertedType = MakeShared<FPFAccountManagementSendCustomAccountRecoveryEmailRequest>(FPFAccountManagementSendCustomAccountRecoveryEmailRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.email = Datatype->email == nullptr ? FString() : FString(Datatype->email),
		.emailTemplateId = Datatype->emailTemplateId == nullptr ? FString() : FString(Datatype->emailTemplateId),
		.username = Datatype->username == nullptr ? FString() : FString(Datatype->username)
	});

	return ConvertedType;
}

const PFAccountManagementSendCustomAccountRecoveryEmailRequest* ConvertSendCustomAccountRecoveryEmailRequestToPlayfab(TSharedPtr<const FPFAccountManagementSendCustomAccountRecoveryEmailRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementSendCustomAccountRecoveryEmailRequest* ConvertedType = new PFAccountManagementSendCustomAccountRecoveryEmailRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.email = ConvertFStringToCharPtr(Datatype->email),
		.emailTemplateId = ConvertFStringToCharPtr(Datatype->emailTemplateId),
		.username = ConvertFStringToCharPtr(Datatype->username)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementSendEmailFromTemplateRequest> ConvertSendEmailFromTemplateRequestToUnreal(const PFAccountManagementSendEmailFromTemplateRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementSendEmailFromTemplateRequest> ConvertedType = MakeShared<FPFAccountManagementSendEmailFromTemplateRequest>(FPFAccountManagementSendEmailFromTemplateRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.emailTemplateId = Datatype->emailTemplateId == nullptr ? FString() : FString(Datatype->emailTemplateId),
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId)
	});

	return ConvertedType;
}

const PFAccountManagementSendEmailFromTemplateRequest* ConvertSendEmailFromTemplateRequestToPlayfab(TSharedPtr<const FPFAccountManagementSendEmailFromTemplateRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementSendEmailFromTemplateRequest* ConvertedType = new PFAccountManagementSendEmailFromTemplateRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.emailTemplateId = ConvertFStringToCharPtr(Datatype->emailTemplateId),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementServerUnlinkBattleNetAccountRequest> ConvertServerUnlinkBattleNetAccountRequestToUnreal(const PFAccountManagementServerUnlinkBattleNetAccountRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementServerUnlinkBattleNetAccountRequest> ConvertedType = MakeShared<FPFAccountManagementServerUnlinkBattleNetAccountRequest>(FPFAccountManagementServerUnlinkBattleNetAccountRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId)
	});

	return ConvertedType;
}

const PFAccountManagementServerUnlinkBattleNetAccountRequest* ConvertServerUnlinkBattleNetAccountRequestToPlayfab(TSharedPtr<const FPFAccountManagementServerUnlinkBattleNetAccountRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementServerUnlinkBattleNetAccountRequest* ConvertedType = new PFAccountManagementServerUnlinkBattleNetAccountRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementServerUnlinkNintendoServiceAccountRequest> ConvertServerUnlinkNintendoServiceAccountRequestToUnreal(const PFAccountManagementServerUnlinkNintendoServiceAccountRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementServerUnlinkNintendoServiceAccountRequest> ConvertedType = MakeShared<FPFAccountManagementServerUnlinkNintendoServiceAccountRequest>(FPFAccountManagementServerUnlinkNintendoServiceAccountRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId)
	});

	return ConvertedType;
}

const PFAccountManagementServerUnlinkNintendoServiceAccountRequest* ConvertServerUnlinkNintendoServiceAccountRequestToPlayfab(TSharedPtr<const FPFAccountManagementServerUnlinkNintendoServiceAccountRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementServerUnlinkNintendoServiceAccountRequest* ConvertedType = new PFAccountManagementServerUnlinkNintendoServiceAccountRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementServerUnlinkNintendoSwitchDeviceIdRequest> ConvertServerUnlinkNintendoSwitchDeviceIdRequestToUnreal(const PFAccountManagementServerUnlinkNintendoSwitchDeviceIdRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementServerUnlinkNintendoSwitchDeviceIdRequest> ConvertedType = MakeShared<FPFAccountManagementServerUnlinkNintendoSwitchDeviceIdRequest>(FPFAccountManagementServerUnlinkNintendoSwitchDeviceIdRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.nintendoSwitchDeviceId = Datatype->nintendoSwitchDeviceId == nullptr ? FString() : FString(Datatype->nintendoSwitchDeviceId),
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId)
	});

	return ConvertedType;
}

const PFAccountManagementServerUnlinkNintendoSwitchDeviceIdRequest* ConvertServerUnlinkNintendoSwitchDeviceIdRequestToPlayfab(TSharedPtr<const FPFAccountManagementServerUnlinkNintendoSwitchDeviceIdRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementServerUnlinkNintendoSwitchDeviceIdRequest* ConvertedType = new PFAccountManagementServerUnlinkNintendoSwitchDeviceIdRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.nintendoSwitchDeviceId = ConvertFStringToCharPtr(Datatype->nintendoSwitchDeviceId),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementServerUnlinkPSNAccountRequest> ConvertServerUnlinkPSNAccountRequestToUnreal(const PFAccountManagementServerUnlinkPSNAccountRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementServerUnlinkPSNAccountRequest> ConvertedType = MakeShared<FPFAccountManagementServerUnlinkPSNAccountRequest>(FPFAccountManagementServerUnlinkPSNAccountRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId)
	});

	return ConvertedType;
}

const PFAccountManagementServerUnlinkPSNAccountRequest* ConvertServerUnlinkPSNAccountRequestToPlayfab(TSharedPtr<const FPFAccountManagementServerUnlinkPSNAccountRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementServerUnlinkPSNAccountRequest* ConvertedType = new PFAccountManagementServerUnlinkPSNAccountRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementUnlinkServerCustomIdRequest> ConvertUnlinkServerCustomIdRequestToUnreal(const PFAccountManagementUnlinkServerCustomIdRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementUnlinkServerCustomIdRequest> ConvertedType = MakeShared<FPFAccountManagementUnlinkServerCustomIdRequest>(FPFAccountManagementUnlinkServerCustomIdRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId),
		.serverCustomId = Datatype->serverCustomId == nullptr ? FString() : FString(Datatype->serverCustomId)
	});

	return ConvertedType;
}

const PFAccountManagementUnlinkServerCustomIdRequest* ConvertUnlinkServerCustomIdRequestToPlayfab(TSharedPtr<const FPFAccountManagementUnlinkServerCustomIdRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementUnlinkServerCustomIdRequest* ConvertedType = new PFAccountManagementUnlinkServerCustomIdRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId),
		.serverCustomId = ConvertFStringToCharPtr(Datatype->serverCustomId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementUnlinkSteamIdRequest> ConvertUnlinkSteamIdRequestToUnreal(const PFAccountManagementUnlinkSteamIdRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementUnlinkSteamIdRequest> ConvertedType = MakeShared<FPFAccountManagementUnlinkSteamIdRequest>(FPFAccountManagementUnlinkSteamIdRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId)
	});

	return ConvertedType;
}

const PFAccountManagementUnlinkSteamIdRequest* ConvertUnlinkSteamIdRequestToPlayfab(TSharedPtr<const FPFAccountManagementUnlinkSteamIdRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementUnlinkSteamIdRequest* ConvertedType = new PFAccountManagementUnlinkSteamIdRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementServerUnlinkXboxAccountRequest> ConvertServerUnlinkXboxAccountRequestToUnreal(const PFAccountManagementServerUnlinkXboxAccountRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementServerUnlinkXboxAccountRequest> ConvertedType = MakeShared<FPFAccountManagementServerUnlinkXboxAccountRequest>(FPFAccountManagementServerUnlinkXboxAccountRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId)
	});

	return ConvertedType;
}

const PFAccountManagementServerUnlinkXboxAccountRequest* ConvertServerUnlinkXboxAccountRequestToPlayfab(TSharedPtr<const FPFAccountManagementServerUnlinkXboxAccountRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementServerUnlinkXboxAccountRequest* ConvertedType = new PFAccountManagementServerUnlinkXboxAccountRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementServerUpdateAvatarUrlRequest> ConvertServerUpdateAvatarUrlRequestToUnreal(const PFAccountManagementServerUpdateAvatarUrlRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementServerUpdateAvatarUrlRequest> ConvertedType = MakeShared<FPFAccountManagementServerUpdateAvatarUrlRequest>(FPFAccountManagementServerUpdateAvatarUrlRequest{
		.imageUrl = Datatype->imageUrl == nullptr ? FString() : FString(Datatype->imageUrl),
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId)
	});

	return ConvertedType;
}

const PFAccountManagementServerUpdateAvatarUrlRequest* ConvertServerUpdateAvatarUrlRequestToPlayfab(TSharedPtr<const FPFAccountManagementServerUpdateAvatarUrlRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementServerUpdateAvatarUrlRequest* ConvertedType = new PFAccountManagementServerUpdateAvatarUrlRequest{
		.imageUrl = ConvertFStringToCharPtr(Datatype->imageUrl),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementUpdateBanRequest> ConvertUpdateBanRequestToUnreal(const PFAccountManagementUpdateBanRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementUpdateBanRequest> ConvertedType = MakeShared<FPFAccountManagementUpdateBanRequest>(FPFAccountManagementUpdateBanRequest{
		.active = TSharedPtr<const bool>(Datatype->active),
		.banId = Datatype->banId == nullptr ? FString() : FString(Datatype->banId),
		.expires = ConvertTimeToUnreal(Datatype->expires),
		.IPAddress = Datatype->IPAddress == nullptr ? FString() : FString(Datatype->IPAddress),
		.permanent = TSharedPtr<const bool>(Datatype->permanent),
		.reason = Datatype->reason == nullptr ? FString() : FString(Datatype->reason),
		.userFamilyType = MakeShared<FPFAccountManagementUserFamilyType>(ConvertUserFamilyTypeToUnreal(Datatype->userFamilyType))
	});

	return ConvertedType;
}

const PFAccountManagementUpdateBanRequest* ConvertUpdateBanRequestToPlayfab(TSharedPtr<const FPFAccountManagementUpdateBanRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementUpdateBanRequest* ConvertedType = new PFAccountManagementUpdateBanRequest{
		.active = Datatype->active ? new bool(*Datatype->active) : nullptr,
		.banId = ConvertFStringToCharPtr(Datatype->banId),
		.expires = ConvertFDateTimeToPlayfab(Datatype->expires),
		.IPAddress = ConvertFStringToCharPtr(Datatype->IPAddress),
		.permanent = Datatype->permanent ? new bool(*Datatype->permanent) : nullptr,
		.reason = ConvertFStringToCharPtr(Datatype->reason),
		.userFamilyType = new PFAccountManagementUserFamilyType(ConvertUserFamilyTypeToPlayfab(Datatype->userFamilyType))
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementUpdateBansRequest> ConvertUpdateBansRequestToUnreal(const PFAccountManagementUpdateBansRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementUpdateBansRequest> ConvertedType = MakeShared<FPFAccountManagementUpdateBansRequest>(FPFAccountManagementUpdateBansRequest{
		.bans = ConvertPlayfabArrayToUnreal<PFAccountManagementUpdateBanRequest, FPFAccountManagementUpdateBanRequest>(Datatype->bans, Datatype->bansCount, ConvertUpdateBanRequestToUnreal),
		.bansCount = Datatype->bansCount
	});

	return ConvertedType;
}

const PFAccountManagementUpdateBansRequest* ConvertUpdateBansRequestToPlayfab(TSharedPtr<const FPFAccountManagementUpdateBansRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementUpdateBansRequest* ConvertedType = new PFAccountManagementUpdateBansRequest{
		.bans = ConvertUnrealArrayToPlayfab<PFAccountManagementUpdateBanRequest, FPFAccountManagementUpdateBanRequest>(Datatype->bans, ConvertUpdateBanRequestToPlayfab),
		.bansCount = (uint32_t)Datatype->bans.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementUpdateBansResult> ConvertUpdateBansResultToUnreal(const PFAccountManagementUpdateBansResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementUpdateBansResult> ConvertedType = MakeShared<FPFAccountManagementUpdateBansResult>(FPFAccountManagementUpdateBansResult{
		.banData = ConvertPlayfabArrayToUnreal<PFAccountManagementBanInfo, FPFAccountManagementBanInfo>(Datatype->banData, Datatype->banDataCount, ConvertBanInfoToUnreal),
		.banDataCount = Datatype->banDataCount
	});

	return ConvertedType;
}

const PFAccountManagementUpdateBansResult* ConvertUpdateBansResultToPlayfab(TSharedPtr<const FPFAccountManagementUpdateBansResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementUpdateBansResult* ConvertedType = new PFAccountManagementUpdateBansResult{
		.banData = ConvertUnrealArrayToPlayfab<PFAccountManagementBanInfo, FPFAccountManagementBanInfo>(Datatype->banData, ConvertBanInfoToPlayfab),
		.banDataCount = (uint32_t)Datatype->banData.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetTitlePlayersFromXboxLiveIDsRequest> ConvertGetTitlePlayersFromXboxLiveIDsRequestToUnreal(const PFAccountManagementGetTitlePlayersFromXboxLiveIDsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetTitlePlayersFromXboxLiveIDsRequest> ConvertedType = MakeShared<FPFAccountManagementGetTitlePlayersFromXboxLiveIDsRequest>(FPFAccountManagementGetTitlePlayersFromXboxLiveIDsRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.sandbox = Datatype->sandbox == nullptr ? FString() : FString(Datatype->sandbox),
		.titleId = Datatype->titleId == nullptr ? FString() : FString(Datatype->titleId),
		.xboxLiveIds = ConvertCharArrayToUnreal(Datatype->xboxLiveIds, Datatype->xboxLiveIdsCount),
		.xboxLiveIdsCount = Datatype->xboxLiveIdsCount
	});

	return ConvertedType;
}

const PFAccountManagementGetTitlePlayersFromXboxLiveIDsRequest* ConvertGetTitlePlayersFromXboxLiveIDsRequestToPlayfab(TSharedPtr<const FPFAccountManagementGetTitlePlayersFromXboxLiveIDsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetTitlePlayersFromXboxLiveIDsRequest* ConvertedType = new PFAccountManagementGetTitlePlayersFromXboxLiveIDsRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.sandbox = ConvertFStringToCharPtr(Datatype->sandbox),
		.titleId = ConvertFStringToCharPtr(Datatype->titleId),
		.xboxLiveIds = ConvertFStringArrayToPlayfab(Datatype->xboxLiveIds),
		.xboxLiveIdsCount = (uint32_t)Datatype->xboxLiveIds.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementGetTitlePlayersFromProviderIDsResponse> ConvertGetTitlePlayersFromProviderIDsResponseToUnreal(const PFAccountManagementGetTitlePlayersFromProviderIDsResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementGetTitlePlayersFromProviderIDsResponse> ConvertedType = MakeShared<FPFAccountManagementGetTitlePlayersFromProviderIDsResponse>(FPFAccountManagementGetTitlePlayersFromProviderIDsResponse{
		.titlePlayerAccounts = ConvertPlayfabMapToUnreal<PFEntityLineageDictionaryEntry, FPFEntityLineage, PFEntityLineage>(Datatype->titlePlayerAccounts, Datatype->titlePlayerAccountsCount, ConvertEntityLineageToUnreal),
		.titlePlayerAccountsCount = Datatype->titlePlayerAccountsCount
	});

	return ConvertedType;
}

const PFAccountManagementGetTitlePlayersFromProviderIDsResponse* ConvertGetTitlePlayersFromProviderIDsResponseToPlayfab(TSharedPtr<const FPFAccountManagementGetTitlePlayersFromProviderIDsResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementGetTitlePlayersFromProviderIDsResponse* ConvertedType = new PFAccountManagementGetTitlePlayersFromProviderIDsResponse{
		.titlePlayerAccounts = ConvertUnrealMapToPlayfab<PFEntityLineageDictionaryEntry, FPFEntityLineage, PFEntityLineage>(Datatype->titlePlayerAccounts, ConvertEntityLineageToPlayfab),
		.titlePlayerAccountsCount = (uint32_t)Datatype->titlePlayerAccounts.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementSetDisplayNameRequest> ConvertSetDisplayNameRequestToUnreal(const PFAccountManagementSetDisplayNameRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementSetDisplayNameRequest> ConvertedType = MakeShared<FPFAccountManagementSetDisplayNameRequest>(FPFAccountManagementSetDisplayNameRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.displayName = Datatype->displayName == nullptr ? FString() : FString(Datatype->displayName),
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.expectedVersion = TSharedPtr<const int32>(Datatype->expectedVersion)
	});

	return ConvertedType;
}

const PFAccountManagementSetDisplayNameRequest* ConvertSetDisplayNameRequestToPlayfab(TSharedPtr<const FPFAccountManagementSetDisplayNameRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementSetDisplayNameRequest* ConvertedType = new PFAccountManagementSetDisplayNameRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.displayName = ConvertFStringToCharPtr(Datatype->displayName),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.expectedVersion = Datatype->expectedVersion ? new int32(*Datatype->expectedVersion) : nullptr
	};

	return ConvertedType;
}

TSharedPtr<const FPFAccountManagementSetDisplayNameResponse> ConvertSetDisplayNameResponseToUnreal(const PFAccountManagementSetDisplayNameResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFAccountManagementSetDisplayNameResponse> ConvertedType = MakeShared<FPFAccountManagementSetDisplayNameResponse>(FPFAccountManagementSetDisplayNameResponse{
		.operationResult = MakeShared<FPFOperationTypes>(ConvertOperationTypesToUnreal(Datatype->operationResult)),
		.versionNumber = TSharedPtr<const int32>(Datatype->versionNumber)
	});

	return ConvertedType;
}

const PFAccountManagementSetDisplayNameResponse* ConvertSetDisplayNameResponseToPlayfab(TSharedPtr<const FPFAccountManagementSetDisplayNameResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFAccountManagementSetDisplayNameResponse* ConvertedType = new PFAccountManagementSetDisplayNameResponse{
		.operationResult = new PFOperationTypes(ConvertOperationTypesToPlayfab(Datatype->operationResult)),
		.versionNumber = Datatype->versionNumber ? new int32(*Datatype->versionNumber) : nullptr
	};

	return ConvertedType;
}
