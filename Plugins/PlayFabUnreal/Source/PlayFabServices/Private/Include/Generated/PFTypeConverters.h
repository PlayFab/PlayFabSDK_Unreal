// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once
#include "PFUnrealTypes.h"
#include <playfab/services/PFServices.h>

#pragma push_macro("IN")
#undef IN

const FPFOperationTypes ConvertOperationTypesToUnreal(const PFOperationTypes* enumVal);
const PFOperationTypes ConvertOperationTypesToPlayfab(TSharedPtr<const FPFOperationTypes> enumVal);

const FPFEventType ConvertEventTypeToUnreal(const PFEventType* enumVal);
const PFEventType ConvertEventTypeToPlayfab(TSharedPtr<const FPFEventType> enumVal);

const FPFResetInterval ConvertResetIntervalToUnreal(const PFResetInterval* enumVal);
const PFResetInterval ConvertResetIntervalToPlayfab(TSharedPtr<const FPFResetInterval> enumVal);
	
TSharedPtr<const FPFVersionConfiguration> ConvertVersionConfigurationToUnreal(const PFVersionConfiguration* Datatype);
const PFVersionConfiguration* ConvertVersionConfigurationToPlayfab(TSharedPtr<const FPFVersionConfiguration> Datatype);


#pragma pop_macro("IN")