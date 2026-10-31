#pragma once

#include "CoreMinimal.h"
#include "Async/AsyncWork.h"
#include "Async/Async.h"
#include "XAsyncTaskQueueHelpers.h"
#include "XAsyncTaskManager.h"
#include "XAsyncTask.h"
#include "PFCoreTypes.h"
#include "PFInitRefCount.h"
THIRD_PARTY_INCLUDES_START
#include <playfab/core/PFEntity.h>
#include <playfab/core/PFCore.h>
THIRD_PARTY_INCLUDES_END

class PLAYFABCORE_API FPFUninitializeAsyncTask : public FXAsyncTask
{
public:
	FPFUninitializeAsyncTask(
		FPFInitRefCount& refCount,
		FOnPFUninitializeDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	void CompleteWithResult(HRESULT hr);

	FPFInitRefCount* refCount;
	FOnPFUninitializeDelegate delegate;
};