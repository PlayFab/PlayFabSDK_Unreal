// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#include "CoreMinimal.h"
#include "Async/AsyncWork.h"
#include "Async/Async.h"
#include "XAsyncTaskQueueHelpers.h"
#include "XAsyncTaskManager.h"
#include "XAsyncTask.h"
#include "PFEntity.h"
#include "PFServiceConfig.h"
#include "PFExperimentationUnrealTypes.h"
#include "PFExperimentationTypeConverters.h"

THIRD_PARTY_INCLUDES_START
#include <playfab/services/PFServices.h>
THIRD_PARTY_INCLUDES_END


/// <summary>
/// Gets the treatment assignments for a player for every running experiment in the title.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFExperimentationGetTreatmentAssignmentGetResultSize"/>
/// and <see cref="PFExperimentationGetTreatmentAssignmentGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FGetTreatmentAssignmentAsyncTask : public FXAsyncTask
{
public:
	FGetTreatmentAssignmentAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFExperimentationGetTreatmentAssignmentRequest InRequest,
	const FOnGetTreatmentAssignmentCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFExperimentationGetTreatmentAssignmentRequest Request;
	
	FOnGetTreatmentAssignmentCompleted Delegate;

	HRESULT HResult;
};

