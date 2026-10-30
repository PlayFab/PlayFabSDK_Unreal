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
    m_createAccount{ createAccount },
    m_delegate{ delegate }
{
}

void LocalUserLoginAsyncTask::DoWork()
{
    HRESULT hr = PFLocalUserLoginAsync(m_localUser.Handle().Get(), m_createAccount, *mAsyncBlock);
    if (FAILED(hr))
    {
        m_delegate.ExecuteIfBound(nullptr, nullptr, FString::Printf(TEXT("DoWork failure: 0x%08X"), static_cast<uint32>(hr)), false);
        m_localUser = LocalUser::Wrap(nullptr);
    }
}

void LocalUserLoginAsyncTask::ProcessResults()
{
    TArray<uint8> bufferArray;
    size_t resultSize = 0;

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

            *reinterpret_cast<PFEntityHandle*>(&m_entityHandle) = entityHandle;
            m_delegate.ExecuteIfBound(ResultType.Get(), &m_entityHandle, FString(), true);
        }
        else
        {
            m_delegate.ExecuteIfBound(nullptr, nullptr, FString::Printf(TEXT("GetResult failure: 0x%08X"), static_cast<uint32>(hr)), false);
        }
    }
    else
    {
        m_delegate.ExecuteIfBound(nullptr, nullptr, FString::Printf(TEXT("GetResultSize failure: 0x%08X"), static_cast<uint32>(hr)), false);
    }

    m_localUser = LocalUser::Wrap(nullptr);
}