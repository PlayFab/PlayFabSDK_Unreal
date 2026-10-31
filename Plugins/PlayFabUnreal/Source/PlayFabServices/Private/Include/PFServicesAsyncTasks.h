#pragma once

#include "CoreMinimal.h"
#include "Async/AsyncWork.h"
#include "Async/Async.h"
#include "XAsyncTaskQueueHelpers.h"
#include "XAsyncTaskManager.h"
#include "XAsyncTask.h"
#include "PFServicesTypes.h"
#include "PFInitRefCount.h"
THIRD_PARTY_INCLUDES_START
#include <playfab/services/PFServices.h>
THIRD_PARTY_INCLUDES_END

class PLAYFABSERVICES_API FPFServicesUninitializeAsyncTask : public FXAsyncTask
{
public:
	FPFServicesUninitializeAsyncTask(
		FPFInitRefCount& refCount,
		FOnPFServicesUninitializeDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	void CompleteWithResult(HRESULT hr);

	FPFInitRefCount* refCount;
	FOnPFServicesUninitializeDelegate delegate;
};