// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFTitleDataManagementTypeConverters.h"

TSharedPtr<const FPFTitleDataManagementGetPublisherDataRequest> ConvertGetPublisherDataRequestToUnreal(const PFTitleDataManagementGetPublisherDataRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFTitleDataManagementGetPublisherDataRequest> ConvertedType = MakeShared<FPFTitleDataManagementGetPublisherDataRequest>(FPFTitleDataManagementGetPublisherDataRequest{
		.keys = ConvertCharArrayToUnreal(Datatype->keys, Datatype->keysCount),
		.keysCount = Datatype->keysCount
	});

	return ConvertedType;
}

const PFTitleDataManagementGetPublisherDataRequest* ConvertGetPublisherDataRequestToPlayfab(TSharedPtr<const FPFTitleDataManagementGetPublisherDataRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFTitleDataManagementGetPublisherDataRequest* ConvertedType = new PFTitleDataManagementGetPublisherDataRequest{
		.keys = ConvertFStringArrayToPlayfab(Datatype->keys),
		.keysCount = (uint32_t)Datatype->keys.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFTitleDataManagementGetPublisherDataResult> ConvertGetPublisherDataResultToUnreal(const PFTitleDataManagementGetPublisherDataResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFTitleDataManagementGetPublisherDataResult> ConvertedType = MakeShared<FPFTitleDataManagementGetPublisherDataResult>(FPFTitleDataManagementGetPublisherDataResult{
		.data = ConvertCharMapToUnreal(Datatype->data, Datatype->dataCount),
		.dataCount = Datatype->dataCount
	});

	return ConvertedType;
}

const PFTitleDataManagementGetPublisherDataResult* ConvertGetPublisherDataResultToPlayfab(TSharedPtr<const FPFTitleDataManagementGetPublisherDataResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFTitleDataManagementGetPublisherDataResult* ConvertedType = new PFTitleDataManagementGetPublisherDataResult{
		.data = ConvertFStringMapToPlayfab(Datatype->data),
		.dataCount = (uint32_t)Datatype->data.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFTitleDataManagementGetTimeResult> ConvertGetTimeResultToUnreal(const PFTitleDataManagementGetTimeResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFTitleDataManagementGetTimeResult> ConvertedType = MakeShared<FPFTitleDataManagementGetTimeResult>(FPFTitleDataManagementGetTimeResult{
		.time = FDateTime::FromUnixTimestamp((int64)Datatype->time)
	});

	return ConvertedType;
}

const PFTitleDataManagementGetTimeResult* ConvertGetTimeResultToPlayfab(TSharedPtr<const FPFTitleDataManagementGetTimeResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFTitleDataManagementGetTimeResult* ConvertedType = new PFTitleDataManagementGetTimeResult{
		.time = Datatype->time.ToUnixTimestamp()
	};

	return ConvertedType;
}

TSharedPtr<const FPFTitleDataManagementGetTitleDataRequest> ConvertGetTitleDataRequestToUnreal(const PFTitleDataManagementGetTitleDataRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFTitleDataManagementGetTitleDataRequest> ConvertedType = MakeShared<FPFTitleDataManagementGetTitleDataRequest>(FPFTitleDataManagementGetTitleDataRequest{
		.keys = ConvertCharArrayToUnreal(Datatype->keys, Datatype->keysCount),
		.keysCount = Datatype->keysCount,
		.overrideLabel = Datatype->overrideLabel == nullptr ? FString() : FString(Datatype->overrideLabel)
	});

	return ConvertedType;
}

const PFTitleDataManagementGetTitleDataRequest* ConvertGetTitleDataRequestToPlayfab(TSharedPtr<const FPFTitleDataManagementGetTitleDataRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFTitleDataManagementGetTitleDataRequest* ConvertedType = new PFTitleDataManagementGetTitleDataRequest{
		.keys = ConvertFStringArrayToPlayfab(Datatype->keys),
		.keysCount = (uint32_t)Datatype->keys.Num(),
		.overrideLabel = ConvertFStringToCharPtr(Datatype->overrideLabel)
	};

	return ConvertedType;
}

TSharedPtr<const FPFTitleDataManagementGetTitleDataResult> ConvertGetTitleDataResultToUnreal(const PFTitleDataManagementGetTitleDataResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFTitleDataManagementGetTitleDataResult> ConvertedType = MakeShared<FPFTitleDataManagementGetTitleDataResult>(FPFTitleDataManagementGetTitleDataResult{
		.data = ConvertCharMapToUnreal(Datatype->data, Datatype->dataCount),
		.dataCount = Datatype->dataCount
	});

	return ConvertedType;
}

const PFTitleDataManagementGetTitleDataResult* ConvertGetTitleDataResultToPlayfab(TSharedPtr<const FPFTitleDataManagementGetTitleDataResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFTitleDataManagementGetTitleDataResult* ConvertedType = new PFTitleDataManagementGetTitleDataResult{
		.data = ConvertFStringMapToPlayfab(Datatype->data),
		.dataCount = (uint32_t)Datatype->data.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFTitleDataManagementGetTitleNewsRequest> ConvertGetTitleNewsRequestToUnreal(const PFTitleDataManagementGetTitleNewsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFTitleDataManagementGetTitleNewsRequest> ConvertedType = MakeShared<FPFTitleDataManagementGetTitleNewsRequest>(FPFTitleDataManagementGetTitleNewsRequest{
		.count = TSharedPtr<const int32>(Datatype->count)
	});

	return ConvertedType;
}

const PFTitleDataManagementGetTitleNewsRequest* ConvertGetTitleNewsRequestToPlayfab(TSharedPtr<const FPFTitleDataManagementGetTitleNewsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFTitleDataManagementGetTitleNewsRequest* ConvertedType = new PFTitleDataManagementGetTitleNewsRequest{
		.count = Datatype->count ? new int32(*Datatype->count) : nullptr
	};

	return ConvertedType;
}

TSharedPtr<const FPFTitleDataManagementTitleNewsItem> ConvertTitleNewsItemToUnreal(const PFTitleDataManagementTitleNewsItem* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFTitleDataManagementTitleNewsItem> ConvertedType = MakeShared<FPFTitleDataManagementTitleNewsItem>(FPFTitleDataManagementTitleNewsItem{
		.body = Datatype->body == nullptr ? FString() : FString(Datatype->body),
		.newsId = Datatype->newsId == nullptr ? FString() : FString(Datatype->newsId),
		.timestamp = FDateTime::FromUnixTimestamp((int64)Datatype->timestamp),
		.title = Datatype->title == nullptr ? FString() : FString(Datatype->title)
	});

	return ConvertedType;
}

const PFTitleDataManagementTitleNewsItem* ConvertTitleNewsItemToPlayfab(TSharedPtr<const FPFTitleDataManagementTitleNewsItem> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFTitleDataManagementTitleNewsItem* ConvertedType = new PFTitleDataManagementTitleNewsItem{
		.body = ConvertFStringToCharPtr(Datatype->body),
		.newsId = ConvertFStringToCharPtr(Datatype->newsId),
		.timestamp = Datatype->timestamp.ToUnixTimestamp(),
		.title = ConvertFStringToCharPtr(Datatype->title)
	};

	return ConvertedType;
}

TSharedPtr<const FPFTitleDataManagementGetTitleNewsResult> ConvertGetTitleNewsResultToUnreal(const PFTitleDataManagementGetTitleNewsResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFTitleDataManagementGetTitleNewsResult> ConvertedType = MakeShared<FPFTitleDataManagementGetTitleNewsResult>(FPFTitleDataManagementGetTitleNewsResult{
		.news = ConvertPlayfabArrayToUnreal(Datatype->news, Datatype->newsCount, ConvertTitleNewsItemToUnreal),
		.newsCount = Datatype->newsCount
	});

	return ConvertedType;
}

const PFTitleDataManagementGetTitleNewsResult* ConvertGetTitleNewsResultToPlayfab(TSharedPtr<const FPFTitleDataManagementGetTitleNewsResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFTitleDataManagementGetTitleNewsResult* ConvertedType = new PFTitleDataManagementGetTitleNewsResult{
		.news = ConvertUnrealArrayToPlayfab(Datatype->news, ConvertTitleNewsItemToPlayfab),
		.newsCount = (uint32_t)Datatype->news.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFTitleDataManagementSetPublisherDataRequest> ConvertSetPublisherDataRequestToUnreal(const PFTitleDataManagementSetPublisherDataRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFTitleDataManagementSetPublisherDataRequest> ConvertedType = MakeShared<FPFTitleDataManagementSetPublisherDataRequest>(FPFTitleDataManagementSetPublisherDataRequest{
		.key = Datatype->key == nullptr ? FString() : FString(Datatype->key),
		.value = Datatype->value == nullptr ? FString() : FString(Datatype->value)
	});

	return ConvertedType;
}

const PFTitleDataManagementSetPublisherDataRequest* ConvertSetPublisherDataRequestToPlayfab(TSharedPtr<const FPFTitleDataManagementSetPublisherDataRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFTitleDataManagementSetPublisherDataRequest* ConvertedType = new PFTitleDataManagementSetPublisherDataRequest{
		.key = ConvertFStringToCharPtr(Datatype->key),
		.value = ConvertFStringToCharPtr(Datatype->value)
	};

	return ConvertedType;
}

TSharedPtr<const FPFTitleDataManagementSetTitleDataRequest> ConvertSetTitleDataRequestToUnreal(const PFTitleDataManagementSetTitleDataRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFTitleDataManagementSetTitleDataRequest> ConvertedType = MakeShared<FPFTitleDataManagementSetTitleDataRequest>(FPFTitleDataManagementSetTitleDataRequest{
		.key = Datatype->key == nullptr ? FString() : FString(Datatype->key),
		.value = Datatype->value == nullptr ? FString() : FString(Datatype->value)
	});

	return ConvertedType;
}

const PFTitleDataManagementSetTitleDataRequest* ConvertSetTitleDataRequestToPlayfab(TSharedPtr<const FPFTitleDataManagementSetTitleDataRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFTitleDataManagementSetTitleDataRequest* ConvertedType = new PFTitleDataManagementSetTitleDataRequest{
		.key = ConvertFStringToCharPtr(Datatype->key),
		.value = ConvertFStringToCharPtr(Datatype->value)
	};

	return ConvertedType;
}
