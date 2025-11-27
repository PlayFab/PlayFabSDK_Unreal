#pragma once

#include "PFLocalUser.h"
#include "Async/AsyncWork.h"
#include "Async/Async.h"
#include "XAsyncTaskQueueHelpers.h"
#include "XAsyncTaskManager.h"
#include "XAsyncTask.h"
#include "TypeWrappers.h"

class LocalUserLoginAsyncTask : public FXAsyncTask
{
public:
    LocalUserLoginAsyncTask(
        FPFLocalUserHandle localUserHandle,
        bool createAccount,
        FOnPFAuthenticationLoginCompleteDelegate delegate
    );

    void DoWork() override;

    void ProcessResults() override;

private:
    LocalUser m_localUser;
    bool m_createAccount;
    FOnPFAuthenticationLoginCompleteDelegate m_delegate;
    FPFEntityHandle m_entityHandle;
};
