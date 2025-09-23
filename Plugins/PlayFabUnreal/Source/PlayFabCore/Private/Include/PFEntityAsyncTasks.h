#pragma once

#include "CoreMinimal.h"
#include "Async/AsyncWork.h"
#include "Async/Async.h"
#include "XAsyncTaskQueueHelpers.h"
#include "XAsyncTaskManager.h"
#include "XAsyncTask.h"
#include "PFEntityTypes.h"
THIRD_PARTY_INCLUDES_START
#include <playfab/core/PFEntity.h>
THIRD_PARTY_INCLUDES_END

DECLARE_DELEGATE_TwoParams(FOnEntityGetEntityTokenDelegate, bool, FPFEntityToken const*);

class PLAYFABCORE_API FPFEntityGetEntityTokenAsyncTask : public FXAsyncTask
{
public:
	FPFEntityGetEntityTokenAsyncTask(
		_In_ FPFEntityHandle entityHandle,
		_Inout_ FOnEntityGetEntityTokenDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFEntityHandle entityHandle;

	FOnEntityGetEntityTokenDelegate delegate;
};