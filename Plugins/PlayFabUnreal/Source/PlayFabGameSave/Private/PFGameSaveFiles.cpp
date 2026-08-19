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

    // Use StringCast instead of TCHAR_TO_UTF8 to avoid dangling pointer
    auto ConvertedSaveFolder = StringCast<UTF8CHAR>(*args->saveFolder);
    cArgs.saveFolder = reinterpret_cast<const char*>(ConvertedSaveFolder.Get());

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

    folderBuffer.SetNumUninitialized(folderSize);
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
    _Out_ int64_t* remainingQuota
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
    return true;
}

void CALLBACK GameSaveFilesActiveDeviceChangedCallback(
    PFLocalUserHandle localUserHandle,
    PFGameSaveDescriptor* _activeDevice,
    void* context
)
{
    auto& state = GameSaveFilesState::Get();
    if (localUserHandle == nullptr || _activeDevice == nullptr)
    {
        UE_LOG(LogPlayFabUnreal, Warning, TEXT("GameSaveFilesActiveDeviceChangedCallback: localUserHandle or active device descriptor is null"));
        return;
    }

    FPFGameSaveDescriptor activeDevice{};
    activeDevice.time = _activeDevice->time;
    activeDevice.totalBytes = _activeDevice->totalBytes;
    activeDevice.uploadedBytes = _activeDevice->uploadedBytes;
    activeDevice.deviceType = _activeDevice->deviceType;

    // The native PFLocalUserHandle is a single raw pointer, but FPFLocalUserHandle is a
    // TSharedPtr (wider). Default-construct the wrapper (null ref-controller) and overwrite
    // only the object pointer, so copies/destruction stay safe no-ops. Never reinterpret the
    // address of the raw handle as an FPFLocalUserHandle*.
    FPFLocalUserHandle localUserHandleWrapper;
    *reinterpret_cast<PFLocalUserHandle*>(&localUserHandleWrapper) = localUserHandle;
    state.activeDeviceChangedDelegate.ExecuteIfBound(localUserHandleWrapper, &activeDevice);
}

bool PLAYFABGAMESAVE_API FPFGameSaveFilesSetActiveDeviceChangedDelegate(
    _In_ FPFGameSaveFilesActiveDeviceChangedDelegate delegate
) noexcept
{
    auto& state = GameSaveFilesState::Get();
    FPFGameSaveFilesActiveDeviceChangedDelegate previousDelegate = state.activeDeviceChangedDelegate;
    state.activeDeviceChangedDelegate = delegate;

    // Register the native callback so the delegate actually fires. Use the generic queue so
    // the callback is dispatched on the game thread, matching the async completion paths.
    HRESULT hr = PFGameSaveFilesSetActiveDeviceChangedCallback(
        FXAsyncTaskQueue::GetGenericQueue(),
        &GameSaveFilesActiveDeviceChangedCallback,
        nullptr);
    if (FAILED(hr))
    {
        // Registration failed; restore the prior delegate so a failed call leaves state unchanged.
        state.activeDeviceChangedDelegate = previousDelegate;
        return false;
    }

    return true;
}

bool PLAYFABGAMESAVE_API FPFGameSaveFilesUninitializeAsync(
    _In_ FPFGameSaveFilesUninitializeComplete delegate
) noexcept
{
    FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
    taskManager->AddTask<GameSaveFilesUninitializeAsyncTask>(delegate);
    return true;
}

bool PLAYFABGAMESAVE_API FPFGameSaveFilesResetCloudAsync(
    _In_ FPFLocalUserHandle localUserHandle,
    _In_ FPFGameSaveFilesResetCloudAsyncComplete delegate
) noexcept
{
    FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
    taskManager->AddTask<GameSaveFilesResetCloudAsyncTask>(localUserHandle, delegate);
    return true;
}

bool PLAYFABGAMESAVE_API FPFGameSaveFilesSetSaveDescriptionAsync(
    _In_ FPFLocalUserHandle localUserHandle,
    _In_ const FString& description,
    _In_ FPFGameSaveFilesSetSaveDescriptionAsyncComplete delegate
) noexcept
{
    FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
    taskManager->AddTask<GameSaveFilesSetSaveDescriptionAsyncTask>(localUserHandle, description, delegate);
    return true;
}