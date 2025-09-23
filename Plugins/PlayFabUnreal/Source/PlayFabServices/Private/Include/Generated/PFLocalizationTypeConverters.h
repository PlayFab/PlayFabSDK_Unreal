// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once
#include "PFUnrealTypes.h"
#include "PFLocalizationUnrealTypes.h"
#include "PFTypeConverters.h"
#include "PFCoreTypeConverters.h"

#pragma push_macro("IN")
#undef IN
	
TSharedPtr<const FPFLocalizationGetLanguageListRequest> ConvertGetLanguageListRequestToUnreal(const PFLocalizationGetLanguageListRequest* Datatype);
const PFLocalizationGetLanguageListRequest* ConvertGetLanguageListRequestToPlayfab(TSharedPtr<const FPFLocalizationGetLanguageListRequest> Datatype);
	
TSharedPtr<const FPFLocalizationGetLanguageListResponse> ConvertGetLanguageListResponseToUnreal(const PFLocalizationGetLanguageListResponse* Datatype);
const PFLocalizationGetLanguageListResponse* ConvertGetLanguageListResponseToPlayfab(TSharedPtr<const FPFLocalizationGetLanguageListResponse> Datatype);


#pragma pop_macro("IN")