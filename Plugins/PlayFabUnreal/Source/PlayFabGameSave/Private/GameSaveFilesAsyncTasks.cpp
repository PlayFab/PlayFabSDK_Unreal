#include "GameSaveFilesAsyncTasks.h"
#include "GameSaveFilesState.h"
#include <playfab/gamesave/PFGameSaveFiles.h>

GameSaveFilesAddUserAsyncTask::GameSaveFilesAddUserAsyncTask(
    FPFLocalUserHandle localUserHandle,
    FPFGameSaveFilesAddUserOptions options,
    FPFGameSaveFilesAddUserWithUiAsyncComplete delegate
) :
    FXAsyncTask{ TEXT("GameSaveFilesAddUserAsyncTask"), FXAsyncTaskQueue::GetBackgroundTaskQueue() },
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
        // Synchronous kickoff failure (e.g. invalid args, wrong state). Not a user cancel.
        // DoWork runs on a worker thread, whereas ProcessResults (the async completion path)
        // fires on the game thread. Dispatch this failure to the game thread so the completion
        // delegate is always invoked on the same thread.
        FString errorMessage = FString::Printf(TEXT("0x%08X"), static_cast<uint32>(hr));
        AsyncTask(ENamedThreads::GameThread, [delegate = m_delegate, errorMessage]()
        {
            delegate.ExecuteIfBound(FPFGameSaveFilesAddUserResult::Failed, errorMessage);
        });
    }
}

void GameSaveFilesAddUserAsyncTask::ProcessResults()
{
    HRESULT hr = PFGameSaveFilesAddUserWithUiResult(*mAsyncBlock);

    if (SUCCEEDED(hr))
    {
        // Added successfully. Distinguish online from offline so the title can branch
        // without a separate query. Offline occurs when the user chose "Use Offline"
        // or another device became active.
        bool isConnectedToCloud = false;
        PFGameSaveFilesIsConnectedToCloud(m_localUser.Handle().Get(), &isConnectedToCloud);

        m_delegate.ExecuteIfBound(
            isConnectedToCloud ? FPFGameSaveFilesAddUserResult::Success
                               : FPFGameSaveFilesAddUserResult::SuccessOffline,
            FString());
    }
    else if (hr == E_PF_GAMESAVE_USER_CANCELLED)
    {
        // User backed out (Cancel, or "Quit game" on out-of-process platforms).
        // This is not a sync failure, so the sync-failed delegate is intentionally not fired.
        m_delegate.ExecuteIfBound(FPFGameSaveFilesAddUserResult::Cancelled, FString());
    }
    else
    {
        // Genuine failure. Fire the sync-failed delegate so titles can handle the specific
        // scenario (it receives the raw HRESULT as an int32).
        GameSaveFilesState::Get().syncFailedDelegate.ExecuteIfBound(
            m_localUser.Handle(),
            FPFGameSaveFilesSyncState::Downloading,
            static_cast<int32>(hr));

        FString errorMessage = FString::Printf(TEXT("0x%08X"), static_cast<uint32>(hr));
        m_delegate.ExecuteIfBound(FPFGameSaveFilesAddUserResult::Failed, errorMessage);
    }
}

GameSaveFilesUploadWithUIAsyncTask::GameSaveFilesUploadWithUIAsyncTask(
    FPFLocalUserHandle localUserHandle,
    FPFGameSaveFilesUploadOption options,
    FPFGameSaveFilesUploadWithUiAsyncComplete delegate
) :
    FXAsyncTask{ TEXT("GameSaveFilesUploadWithUIAsyncTask"), FXAsyncTaskQueue::GetBackgroundTaskQueue() },
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
        // Synchronous kickoff failure (e.g. user not added, wrong state). Not a user cancel.
        // Dispatch to the game thread so the completion delegate fires on the same thread as
        // the async completion path (ProcessResults).
        FString errorMessage = FString::Printf(TEXT("0x%08X"), static_cast<uint32>(hr));
        AsyncTask(ENamedThreads::GameThread, [delegate = m_delegate, errorMessage]()
        {
            delegate.ExecuteIfBound(FPFGameSaveFilesUploadResult::Failed, errorMessage);
        });
    }
}

void GameSaveFilesUploadWithUIAsyncTask::ProcessResults()
{
    HRESULT hr = PFGameSaveFilesUploadWithUiResult(*mAsyncBlock);

    if (SUCCEEDED(hr))
    {
        m_delegate.ExecuteIfBound(FPFGameSaveFilesUploadResult::Success, FString());
    }
    else if (hr == E_PF_GAMESAVE_USER_CANCELLED)
    {
        // User cancelled the upload (Cancel on progress/sync-failure UI, or "Quit game"
        // on out-of-process platforms). Not a sync failure, so the sync-failed delegate
        // is intentionally not fired.
        m_delegate.ExecuteIfBound(FPFGameSaveFilesUploadResult::Cancelled, FString());
    }
    else
    {
        // Genuine failure. Fire the sync-failed delegate so titles can handle the specific
        // scenario (it receives the raw HRESULT as an int32).
        GameSaveFilesState::Get().syncFailedDelegate.ExecuteIfBound(
            m_localUser.Handle(),
            FPFGameSaveFilesSyncState::Uploading,
            static_cast<int32>(hr));

        FString errorMessage = FString::Printf(TEXT("0x%08X"), static_cast<uint32>(hr));
        m_delegate.ExecuteIfBound(FPFGameSaveFilesUploadResult::Failed, errorMessage);
    }
}

GameSaveFilesResetCloudAsyncTask::GameSaveFilesResetCloudAsyncTask(
    FPFLocalUserHandle localUserHandle,
    FPFGameSaveFilesResetCloudAsyncComplete delegate
) :
    FXAsyncTask{ TEXT("GameSaveFilesResetCloudAsyncTask"), FXAsyncTaskQueue::GetBackgroundTaskQueue() },
    m_localUser{ LocalUser::Duplicate(localUserHandle) },
    m_delegate{ delegate }
{
}

void GameSaveFilesResetCloudAsyncTask::DoWork()
{
    HRESULT hr = PFGameSaveFilesResetCloudAsync(m_localUser.Handle().Get(), *mAsyncBlock);
    if (FAILED(hr))
    {
        // Dispatch to the game thread so the completion delegate fires on the same thread as
        // the async completion path (ProcessResults).
        FString errorMessage = FString::Printf(TEXT("0x%08X"), static_cast<uint32>(hr));
        AsyncTask(ENamedThreads::GameThread, [delegate = m_delegate, errorMessage]()
        {
            delegate.ExecuteIfBound(false, errorMessage);
        });
    }
}

void GameSaveFilesResetCloudAsyncTask::ProcessResults()
{
    HRESULT hr = PFGameSaveFilesResetCloudResult(*mAsyncBlock);
    if (FAILED(hr))
    {
        FString errorMessage = FString::Printf(TEXT("0x%08X"), static_cast<uint32>(hr));
        m_delegate.ExecuteIfBound(false, errorMessage);
    }
    else
    {
        m_delegate.ExecuteIfBound(true, FString());
    }
}

GameSaveFilesSetSaveDescriptionAsyncTask::GameSaveFilesSetSaveDescriptionAsyncTask(
    FPFLocalUserHandle localUserHandle,
    const FString& description,
    FPFGameSaveFilesSetSaveDescriptionAsyncComplete delegate
) :
    FXAsyncTask{ TEXT("GameSaveFilesSetSaveDescriptionAsyncTask"), FXAsyncTaskQueue::GetBackgroundTaskQueue() },
    m_localUser{ LocalUser::Duplicate(localUserHandle) },
    m_description{ description },
    m_delegate{ delegate }
{
}

void GameSaveFilesSetSaveDescriptionAsyncTask::DoWork()
{
    auto ConvertedDescription = StringCast<UTF8CHAR>(*m_description);
    HRESULT hr = PFGameSaveFilesSetSaveDescriptionAsync(m_localUser.Handle().Get(), reinterpret_cast<const char*>(ConvertedDescription.Get()), *mAsyncBlock);
    if (FAILED(hr))
    {
        // Dispatch to the game thread so the completion delegate fires on the same thread as
        // the async completion path (ProcessResults).
        FString errorMessage = FString::Printf(TEXT("0x%08X"), static_cast<uint32>(hr));
        AsyncTask(ENamedThreads::GameThread, [delegate = m_delegate, errorMessage]()
        {
            delegate.ExecuteIfBound(false, errorMessage);
        });
    }
}

void GameSaveFilesSetSaveDescriptionAsyncTask::ProcessResults()
{
    HRESULT hr = PFGameSaveFilesSetSaveDescriptionResult(*mAsyncBlock);
    if (FAILED(hr))
    {
        FString errorMessage = FString::Printf(TEXT("0x%08X"), static_cast<uint32>(hr));
        m_delegate.ExecuteIfBound(false, errorMessage);
    }
    else
    {
        m_delegate.ExecuteIfBound(true, FString());
    }
}

GameSaveFilesUninitializeAsyncTask::GameSaveFilesUninitializeAsyncTask(
    FPFGameSaveFilesUninitializeComplete delegate
) :
    FXAsyncTask{ TEXT("GameSaveFilesUninitializeAsyncTask"), FXAsyncTaskQueue::GetBackgroundTaskQueue() },
    m_delegate{ delegate }
{
}

void GameSaveFilesUninitializeAsyncTask::DoWork()
{
    HRESULT hr = PFGameSaveFilesUninitializeAsync(*mAsyncBlock);
    if (FAILED(hr))
    {
        // Dispatch to the game thread so the completion delegate fires on the same thread as
        // the async completion path (ProcessResults).
        AsyncTask(ENamedThreads::GameThread, [delegate = m_delegate]()
        {
            delegate.ExecuteIfBound(false);
        });
    }
}

void GameSaveFilesUninitializeAsyncTask::ProcessResults()
{
    HRESULT hr = PFGameSaveFilesUninitializeResult(*mAsyncBlock);
    m_delegate.ExecuteIfBound(SUCCEEDED(hr));
}