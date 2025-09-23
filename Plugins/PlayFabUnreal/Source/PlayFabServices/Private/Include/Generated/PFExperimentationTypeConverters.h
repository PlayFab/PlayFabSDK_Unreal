// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once
#include "PFUnrealTypes.h"
#include "PFExperimentationUnrealTypes.h"
#include "PFTypeConverters.h"
#include "PFCoreTypeConverters.h"

#pragma push_macro("IN")
#undef IN
	
TSharedPtr<const FPFExperimentationGetTreatmentAssignmentRequest> ConvertGetTreatmentAssignmentRequestToUnreal(const PFExperimentationGetTreatmentAssignmentRequest* Datatype);
const PFExperimentationGetTreatmentAssignmentRequest* ConvertGetTreatmentAssignmentRequestToPlayfab(TSharedPtr<const FPFExperimentationGetTreatmentAssignmentRequest> Datatype);
	
TSharedPtr<const FPFExperimentationGetTreatmentAssignmentResult> ConvertGetTreatmentAssignmentResultToUnreal(const PFExperimentationGetTreatmentAssignmentResult* Datatype);
const PFExperimentationGetTreatmentAssignmentResult* ConvertGetTreatmentAssignmentResultToPlayfab(TSharedPtr<const FPFExperimentationGetTreatmentAssignmentResult> Datatype);


#pragma pop_macro("IN")