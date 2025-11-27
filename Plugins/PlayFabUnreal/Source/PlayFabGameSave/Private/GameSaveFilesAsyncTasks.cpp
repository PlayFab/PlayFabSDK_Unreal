#include "GameSaveFilesAsyncTasks.h"
#include <playfab/gamesave/PFGameSaveFiles.h>

GameSaveFilesAddUserAsyncTask::GameSaveFilesAddUserAsyncTask(
    FPFLocalUserHandle localUserHandle,
    FPFGameSaveFilesAddUserOptions options,
    FPFGameSaveFilesAddUserWithUiAsyncComplete delegate
) :
    FXAsyncTask{ TEXT("GameSaveFilesAddUserAsyncTask") },
    m_localUser{ LocalUser::Duplicate(localUserHandle)},
    m_options{ options },
    m_delegate{ delegate }
{
}

void GameSaveFilesAddUserAsyncTask::DoWork()
{
    HRESULT hr = PFGameSaveFilesAddUserWithUiAsync(m_localUser.Handle().Get(), static_cast<PFGameSaveFilesAddUserOptions>(m_options), *mAsyncBlock);
    if (FAILED(hr))
    {
        m_delegate.ExecuteIfBound(false);
    }
}

void GameSaveFilesAddUserAsyncTask::ProcessResults()
{
    HRESULT hr = PFGameSaveFilesAddUserWithUiResult(*mAsyncBlock);
    m_delegate.ExecuteIfBound(SUCCEEDED(hr));
}

GameSaveFilesUploadWithUIAsyncTask::GameSaveFilesUploadWithUIAsyncTask(
    FPFLocalUserHandle localUserHandle,
    FPFGameSaveFilesUploadOption options,
    FPFGameSaveFilesUploadWithUiAsyncComplete delegate
) :
    FXAsyncTask{ TEXT("GameSaveFilesAddUserAsyncTask") },
    m_localUser{ LocalUser::Duplicate(localUserHandle) },
    m_options{ options },
    m_delegate{ delegate }
{
}

void GameSaveFilesUploadWithUIAsyncTask::DoWork()
{
    HRESULT hr = PFGameSaveFilesUploadWithUiAsync(m_localUser.Handle().Get(), static_cast<PFGameSaveFilesUploadOption>(m_options), *mAsyncBlock);
    if (FAILED(hr))
    {
        m_delegate.ExecuteIfBound(false);
    }
}

void GameSaveFilesUploadWithUIAsyncTask::ProcessResults()
{
    HRESULT hr = PFGameSaveFilesUploadWithUiResult(*mAsyncBlock);
    m_delegate.ExecuteIfBound(SUCCEEDED(hr));
}

GameSaveFilesUninitializeAsyncTask::GameSaveFilesUninitializeAsyncTask(
    FPFGameSaveFilesUninitializeComplete delegate
) :
    FXAsyncTask{ TEXT("GameSaveFilesUninitializeAsyncTask") },
    m_delegate{ delegate }
{
}

void GameSaveFilesUninitializeAsyncTask::DoWork()
{
    HRESULT hr = PFGameSaveFilesUninitializeAsync(*mAsyncBlock);
    if (FAILED(hr))
    {
        m_delegate.ExecuteIfBound(false);
    }
}

void GameSaveFilesUninitializeAsyncTask::ProcessResults()
{
    HRESULT hr = PFGameSaveFilesUninitializeResult(*mAsyncBlock);
    m_delegate.ExecuteIfBound(SUCCEEDED(hr));
}