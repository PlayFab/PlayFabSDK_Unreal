// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once
#include "PFUnrealTypes.h"

#pragma push_macro("IN")
#undef IN

/// <summary>
/// FPFExperimentationGetTreatmentAssignmentRequest data model. Given a title player or a title entity
/// token, returns the treatment variants and variables assigned to the entity across all running experiments.
/// </summary>
struct PLAYFABSERVICES_API FPFExperimentationGetTreatmentAssignmentRequest
{
	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// (Optional) The optional entity to perform this action on. Defaults to the currently logged in entity.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;
};

/// <summary>
/// FPFExperimentationGetTreatmentAssignmentResult data model.
/// </summary>
struct PLAYFABSERVICES_API FPFExperimentationGetTreatmentAssignmentResult
{
	/// <summary>
	/// (Optional) Treatment assignment for the entity.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFTreatmentAssignment> treatmentAssignment;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

// Delegates Declarations

DECLARE_DELEGATE_TwoParams(FOnGetTreatmentAssignmentCompleted, const FPFExperimentationGetTreatmentAssignmentResult&, bool);

#pragma pop_macro("IN")