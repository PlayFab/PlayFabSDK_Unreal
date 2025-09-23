#include "PFGameSaveFiles.h"
#include "GameSaveFilesAsyncTasks.h"
#include "GameSaveFilesState.h"
#include <playfab/core/PFCore.h>
#include <playfab/gamesave/PFGameSaveFiles.h>
#include "ResultMacros.h"

bool PLAYFABGAMESAVE_API FPFGameSaveFilesInitialize(
    _In_ FPFGameSaveInitArgs* args
) noexcept
{
    PFGameSaveInitArgs cArgs{};
    cArgs.options = args->options;
    cArgs.saveFolder = TCHAR_TO_UTF8(*args->saveFolder);

    RETURN_FALSE_IF_FAILED(PFGameSaveFilesInitialize(&cArgs));

    return true;
}

bool PLAYFABGAMESAVE_API FPFGameSaveFilesAddUserWithUiAsync(
    _In_ FPFLocalUserHandle localUserHandle,
    _In_ FPFGameSaveFilesAddUserOptions options,
    _In_ FPFGameSaveFilesAddUserWithUiAsyncComplete delegate
) noexcept
{
    FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
    taskManager->AddTask<GameSaveFilesAddUserAsyncTask>(localUserHandle, options, delegate);
    return true;
}

bool PLAYFABGAMESAVE_API FPFGameSaveFilesGetFolder(
    _In_ FPFLocalUserHandle localUserHandle,
    _Out_ FString& folder
) noexcept
{
    TArray<char> folderBuffer;
    size_t folderSize;
    RETURN_FALSE_IF_FAILED(PFGameSaveFilesGetFolderSize(localUserHandle.Get(), &folderSize));

    folderBuffer.Reserve(folderSize);
    RETURN_FALSE_IF_FAILED(PFGameSaveFilesGetFolder(localUserHandle.Get(), folderSize, folderBuffer.GetData(), nullptr));

    folder = folderBuffer.GetData();

    return true;
}

bool PLAYFABGAMESAVE_API FPFGameSaveFilesUploadWithUiAsync(
    _In_ FPFLocalUserHandle localUserHandle,
    _In_ FPFGameSaveFilesUploadOption option,
    _In_ FPFGameSaveFilesUploadWithUiAsyncComplete delegate
) noexcept
{
    FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
    taskManager->AddTask<GameSaveFilesUploadWithUIAsyncTask>(localUserHandle, option, delegate);
    return true;
}

bool PLAYFABGAMESAVE_API FPFGameSaveFilesGetRemainingQuota(
    _In_ FPFLocalUserHandle localUserHandle,
    _Out_ int64* remainingQuota
) noexcept
{
    RETURN_FALSE_IF_FAILED(PFGameSaveFilesGetRemainingQuota(localUserHandle.Get(), remainingQuota));
    return true;
}

bool PLAYFABGAMESAVE_API FPFGameSaveFilesIsConnectedToCloud(
    _In_ FPFLocalUserHandle localUserHandle,
    _Out_ bool* isConnectedToCloud
) noexcept
{
    RETURN_FALSE_IF_FAILED(PFGameSaveFilesIsConnectedToCloud(localUserHandle.Get(), isConnectedToCloud));
    return false;

}

void CALLBACK GameSaveFilesActiveDeviceChangedCallback(
    PFLocalUserHandle localUserHandle,
    PFGameSaveDescriptor* _activeDevice,
    void* context
)
{
    auto& state = GameSaveFilesState::Get();
    FPFGameSaveDescriptor activeDevice{};
    activeDevice.time = _activeDevice->time;
    activeDevice.totalBytes = _activeDevice->totalBytes;
    activeDevice.uploadedBytes = _activeDevice->totalBytes;
    activeDevice.deviceType = _activeDevice->deviceType;

    FPFLocalUserHandle* entityHandlePtr = reinterpret_cast<FPFLocalUserHandle*>(&localUserHandle);
    state.activeDeviceChangedDelegate.ExecuteIfBound(*entityHandlePtr, &activeDevice);
}

bool PLAYFABGAMESAVE_API FPFGameSaveFilesSetActiveDeviceChangedDelegate(
    _In_ FPFGameSaveFilesActiveDeviceChangedDelegate delegate
) noexcept
{
    GameSaveFilesState::Get().activeDeviceChangedDelegate = delegate;
    return true;
}

bool PLAYFABGAMESAVE_API FPFGameSaveFilesUninitializeAsync(
    _In_ FPFGameSaveFilesUninitializeComplete delegate
) noexcept
{
    return false;
}