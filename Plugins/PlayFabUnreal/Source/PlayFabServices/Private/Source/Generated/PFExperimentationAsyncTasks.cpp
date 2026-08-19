// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFExperimentationAsyncTasks.h"

FGetTreatmentAssignmentAsyncTask::FGetTreatmentAssignmentAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFExperimentationGetTreatmentAssignmentRequest InRequest,
	const FOnGetTreatmentAssignmentCompleted& InDelegate)
	: FXAsyncTask(TEXT("FGetTreatmentAssignmentAsyncTask")),
	EntityHandle(EntityHandle),
	Request(InRequest),
	Delegate(InDelegate)
{
};

void FGetTreatmentAssignmentAsyncTask::DoWork()
{
	const PFExperimentationGetTreatmentAssignmentRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(Request.customTags),
		.customTagsCount = (uint32_t)Request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Request.entity)
	};
	HResult = PFExperimentationGetTreatmentAssignmentAsync(EntityHandle.Get(), &RequestType, *mAsyncBlock);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFExperimentationGetTreatmentAssignmentResult{ .ErrorMessage = ErrorMessage }, false);
	}
};

void FGetTreatmentAssignmentAsyncTask::ProcessResults()
{
	size_t ResultSize = 0;
	HResult = PFExperimentationGetTreatmentAssignmentGetResultSize(*mAsyncBlock, &ResultSize);
	if (HResult != S_OK)
	{
		Delegate.Execute(FPFExperimentationGetTreatmentAssignmentResult{ .ErrorMessage = FString::Printf(TEXT("GetResultSize failure: 0x%08X"), static_cast<uint32>(HResult)) }, false);
		return;
	}

	PFExperimentationGetTreatmentAssignmentResult *Result = {};
	TArray<uint8> BufferArray;
	BufferArray.Reserve(ResultSize);
	HResult = PFExperimentationGetTreatmentAssignmentGetResult(*mAsyncBlock, ResultSize, BufferArray.GetData(), &Result, nullptr);
	if (HResult != S_OK)
	{
		FString ErrorMessage = FString::Printf(TEXT("GetResult failure: 0x%08X"), static_cast<uint32>(HResult));
		Delegate.Execute(FPFExperimentationGetTreatmentAssignmentResult{ .ErrorMessage = ErrorMessage }, false);
		return;
	}

	TSharedPtr<const FPFExperimentationGetTreatmentAssignmentResult> ResultType = ConvertGetTreatmentAssignmentResultToUnreal(Result);

	Delegate.Execute(*ResultType, true);
}

