#include "LocalUserAsyncTasks.h"
#include "Generated/PFAuthenticationTypeConverters.h"
#include <playfab/core/PFLocalUser.h>

LocalUserLoginAsyncTask::LocalUserLoginAsyncTask(
    FPFLocalUserHandle localUserHandle,
    bool createAccount,
    FOnPFAuthenticationLoginCompleteDelegate delegate
) :
    FXAsyncTask{ TEXT("LocalUserLoginAsyncTask") },
    m_localUser{ LocalUser::Duplicate(localUserHandle) },
    m_delegate{ delegate }
{
}

void LocalUserLoginAsyncTask::DoWork()
{
    HRESULT hr = PFLocalUserLoginAsync(m_localUser.Handle().Get(), m_createAccount, *mAsyncBlock);
    if (FAILED(hr))
    {
        m_delegate.ExecuteIfBound(nullptr, nullptr, false);
    }
}

void LocalUserLoginAsyncTask::ProcessResults()
{
    TArray<uint8> bufferArray;
    uint64 resultSize = 0;

    HRESULT hr = PFLocalUserLoginGetResultSize(*mAsyncBlock, &resultSize);

    if (SUCCEEDED(hr))
    {
        bufferArray.Reserve(resultSize);

        PFEntityHandle entityHandle{ nullptr };
        PFAuthenticationLoginResult const* loginResult{ nullptr };
        hr = PFLocalUserLoginGetResult(*mAsyncBlock, &entityHandle, resultSize, bufferArray.GetData(), &loginResult, nullptr);

        if (SUCCEEDED(hr))
        {
            TSharedPtr<const FPFAuthenticationLoginResult> ResultType = ConvertLoginResultToUnreal(loginResult);

            FPFEntityHandle* entityHandlePtr = reinterpret_cast<FPFEntityHandle*>(&entityHandle);
            m_delegate.ExecuteIfBound(ResultType.Get(), entityHandlePtr, true);
        }
        else
        {
            m_delegate.ExecuteIfBound(nullptr, nullptr, false);
        }
    }
    else
    {
        m_delegate.ExecuteIfBound(nullptr, nullptr, false);
    }
}