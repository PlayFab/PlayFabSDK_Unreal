// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFLocalizationTypeConverters.h"

TSharedPtr<const FPFLocalizationGetLanguageListRequest> ConvertGetLanguageListRequestToUnreal(const PFLocalizationGetLanguageListRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFLocalizationGetLanguageListRequest> ConvertedType = MakeShared<FPFLocalizationGetLanguageListRequest>(FPFLocalizationGetLanguageListRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount
	});

	return ConvertedType;
}

const PFLocalizationGetLanguageListRequest* ConvertGetLanguageListRequestToPlayfab(TSharedPtr<const FPFLocalizationGetLanguageListRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFLocalizationGetLanguageListRequest* ConvertedType = new PFLocalizationGetLanguageListRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFLocalizationGetLanguageListResponse> ConvertGetLanguageListResponseToUnreal(const PFLocalizationGetLanguageListResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFLocalizationGetLanguageListResponse> ConvertedType = MakeShared<FPFLocalizationGetLanguageListResponse>(FPFLocalizationGetLanguageListResponse{
		.languageList = ConvertCharArrayToUnreal(Datatype->languageList, Datatype->languageListCount),
		.languageListCount = Datatype->languageListCount
	});

	return ConvertedType;
}

const PFLocalizationGetLanguageListResponse* ConvertGetLanguageListResponseToPlayfab(TSharedPtr<const FPFLocalizationGetLanguageListResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFLocalizationGetLanguageListResponse* ConvertedType = new PFLocalizationGetLanguageListResponse{
		.languageList = ConvertFStringArrayToPlayfab(Datatype->languageList),
		.languageListCount = (uint32_t)Datatype->languageList.Num()
	};

	return ConvertedType;
}
