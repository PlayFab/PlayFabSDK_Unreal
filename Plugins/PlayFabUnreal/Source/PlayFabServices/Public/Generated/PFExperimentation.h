// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include "CoreMinimal.h"
#include "XAsyncTaskManager.h"
#include "PFExperimentationAsyncTasks.h"

THIRD_PARTY_INCLUDES_START
#include <playfab/services/PFServices.h>
THIRD_PARTY_INCLUDES_END

extern "C"
{
/// <summary>
/// Gets the treatment assignments for a player for every running experiment in the title.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFExperimentationGetTreatmentAssignmentGetResultSize"/>
/// and <see cref="PFExperimentationGetTreatmentAssignmentGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFExperimentationGetTreatmentAssignmentAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFExperimentationGetTreatmentAssignmentRequest* request,
	_Inout_ FOnGetTreatmentAssignmentCompleted delegate
) noexcept;

}
