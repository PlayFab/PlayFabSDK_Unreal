#pragma once

#if defined(PF_GDK_AVAILABLE) || defined(PF_UE_GDK_SUPPORT)

#include "Async/AsyncWork.h"
#include "Async/Async.h"
#include "XAsyncTaskQueueHelpers.h"
#include "XAsyncTaskManager.h"
#include "XAsyncTask.h"
#include "PFServiceConfigTypes.h"
#include "Xbox/PFAuthenticationTypes_Xbox.h"
#include "Generated/PFAuthenticationUnrealTypes.h"

class FPFAuthenticationLoginWithXUserAsyncTask : public FXAsyncTask
{
public:
    FPFAuthenticationLoginWithXUserAsyncTask(
        FPFServiceConfigHandle serviceConfigHandle,
        const FPFAuthenticationLoginWithXUserRequest request,
        FOnPFAuthenticationLoginCompleteDelegate delegate
    );

    void DoWork() override;

    void ProcessResults() override;

private:
	FPFServiceConfigHandle serviceConfigHandle;

	const FPFAuthenticationLoginWithXUserRequest request;

    FOnPFAuthenticationLoginCompleteDelegate delegate;
};

#endif
