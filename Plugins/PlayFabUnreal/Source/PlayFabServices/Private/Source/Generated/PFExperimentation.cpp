#include "PFExperimentation.h"

bool PLAYFABSERVICES_API FPFExperimentationGetTreatmentAssignmentAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFExperimentationGetTreatmentAssignmentRequest* request,
	_Inout_ FOnGetTreatmentAssignmentCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FGetTreatmentAssignmentAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

