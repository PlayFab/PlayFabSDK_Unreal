// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFExperimentationTypeConverters.h"

TSharedPtr<const FPFExperimentationGetTreatmentAssignmentRequest> ConvertGetTreatmentAssignmentRequestToUnreal(const PFExperimentationGetTreatmentAssignmentRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFExperimentationGetTreatmentAssignmentRequest> ConvertedType = MakeShared<FPFExperimentationGetTreatmentAssignmentRequest>(FPFExperimentationGetTreatmentAssignmentRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity)
	});

	return ConvertedType;
}

const PFExperimentationGetTreatmentAssignmentRequest* ConvertGetTreatmentAssignmentRequestToPlayfab(TSharedPtr<const FPFExperimentationGetTreatmentAssignmentRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFExperimentationGetTreatmentAssignmentRequest* ConvertedType = new PFExperimentationGetTreatmentAssignmentRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity)
	};

	return ConvertedType;
}

TSharedPtr<const FPFExperimentationGetTreatmentAssignmentResult> ConvertGetTreatmentAssignmentResultToUnreal(const PFExperimentationGetTreatmentAssignmentResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFExperimentationGetTreatmentAssignmentResult> ConvertedType = MakeShared<FPFExperimentationGetTreatmentAssignmentResult>(FPFExperimentationGetTreatmentAssignmentResult{
		.treatmentAssignment = ConvertTreatmentAssignmentToUnreal(Datatype->treatmentAssignment)
	});

	return ConvertedType;
}

const PFExperimentationGetTreatmentAssignmentResult* ConvertGetTreatmentAssignmentResultToPlayfab(TSharedPtr<const FPFExperimentationGetTreatmentAssignmentResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFExperimentationGetTreatmentAssignmentResult* ConvertedType = new PFExperimentationGetTreatmentAssignmentResult{
		.treatmentAssignment = ConvertTreatmentAssignmentToPlayfab(Datatype->treatmentAssignment)
	};

	return ConvertedType;
}
