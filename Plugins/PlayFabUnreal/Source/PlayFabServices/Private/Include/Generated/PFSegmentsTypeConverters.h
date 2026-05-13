// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once
#include "PFUnrealTypes.h"
#include "PFSegmentsUnrealTypes.h"
#include "PFTypeConverters.h"
#include "PFCoreTypeConverters.h"

#pragma push_macro("IN")
#undef IN
	
TSharedPtr<const FPFSegmentsGetSegmentResult> ConvertGetSegmentResultToUnreal(const PFSegmentsGetSegmentResult* Datatype);
const PFSegmentsGetSegmentResult* ConvertGetSegmentResultToPlayfab(TSharedPtr<const FPFSegmentsGetSegmentResult> Datatype);
	
TSharedPtr<const FPFSegmentsGetPlayerSegmentsResult> ConvertGetPlayerSegmentsResultToUnreal(const PFSegmentsGetPlayerSegmentsResult* Datatype);
const PFSegmentsGetPlayerSegmentsResult* ConvertGetPlayerSegmentsResultToPlayfab(TSharedPtr<const FPFSegmentsGetPlayerSegmentsResult> Datatype);
	
TSharedPtr<const FPFSegmentsGetPlayerTagsRequest> ConvertGetPlayerTagsRequestToUnreal(const PFSegmentsGetPlayerTagsRequest* Datatype);
const PFSegmentsGetPlayerTagsRequest* ConvertGetPlayerTagsRequestToPlayfab(TSharedPtr<const FPFSegmentsGetPlayerTagsRequest> Datatype);
	
TSharedPtr<const FPFSegmentsGetPlayerTagsResult> ConvertGetPlayerTagsResultToUnreal(const PFSegmentsGetPlayerTagsResult* Datatype);
const PFSegmentsGetPlayerTagsResult* ConvertGetPlayerTagsResultToPlayfab(TSharedPtr<const FPFSegmentsGetPlayerTagsResult> Datatype);
	
TSharedPtr<const FPFSegmentsAddPlayerTagRequest> ConvertAddPlayerTagRequestToUnreal(const PFSegmentsAddPlayerTagRequest* Datatype);
const PFSegmentsAddPlayerTagRequest* ConvertAddPlayerTagRequestToPlayfab(TSharedPtr<const FPFSegmentsAddPlayerTagRequest> Datatype);
	
TSharedPtr<const FPFSegmentsGetAllSegmentsResult> ConvertGetAllSegmentsResultToUnreal(const PFSegmentsGetAllSegmentsResult* Datatype);
const PFSegmentsGetAllSegmentsResult* ConvertGetAllSegmentsResultToPlayfab(TSharedPtr<const FPFSegmentsGetAllSegmentsResult> Datatype);
	
TSharedPtr<const FPFSegmentsGetPlayersSegmentsRequest> ConvertGetPlayersSegmentsRequestToUnreal(const PFSegmentsGetPlayersSegmentsRequest* Datatype);
const PFSegmentsGetPlayersSegmentsRequest* ConvertGetPlayersSegmentsRequestToPlayfab(TSharedPtr<const FPFSegmentsGetPlayersSegmentsRequest> Datatype);
	
TSharedPtr<const FPFSegmentsRemovePlayerTagRequest> ConvertRemovePlayerTagRequestToUnreal(const PFSegmentsRemovePlayerTagRequest* Datatype);
const PFSegmentsRemovePlayerTagRequest* ConvertRemovePlayerTagRequestToPlayfab(TSharedPtr<const FPFSegmentsRemovePlayerTagRequest> Datatype);


#pragma pop_macro("IN")