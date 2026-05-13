// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFSegmentsTypeConverters.h"

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
		.segments = ConvertPlayfabArrayToUnreal<PFSegmentsGetSegmentResult, FPFSegmentsGetSegmentResult>(Datatype->segments, Datatype->segmentsCount, ConvertGetSegmentResultToUnreal),
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
		.segments = ConvertUnrealArrayToPlayfab<PFSegmentsGetSegmentResult, FPFSegmentsGetSegmentResult>(Datatype->segments, ConvertGetSegmentResultToPlayfab),
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
		.segments = ConvertPlayfabArrayToUnreal<PFSegmentsGetSegmentResult, FPFSegmentsGetSegmentResult>(Datatype->segments, Datatype->segmentsCount, ConvertGetSegmentResultToUnreal),
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
		.segments = ConvertUnrealArrayToPlayfab<PFSegmentsGetSegmentResult, FPFSegmentsGetSegmentResult>(Datatype->segments, ConvertGetSegmentResultToPlayfab),
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
