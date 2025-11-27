#include "PFGameSaveFilesUi.h"
#include "GameSaveFilesState.h"
#include <playfab/gamesave/PFGameSaveFilesUi.h>
#include "ResultMacros.h"

void CALLBACK GameSaveFilesUiProgressCallback(
    _In_ PFLocalUserHandle localUserHandle,
    _In_ PFGameSaveFilesSyncState syncState,
    _In_ void* /*context*/
) noexcept
{
    if (localUserHandle == nullptr)
    {
        UE_LOG(LogPlayFabUnreal, Warning, TEXT("GameSaveFilesUiProgressCallback: localUserHandle is null"));
        return;
    }

    FPFLocalUserHandle localUserHandleWrapper;
    *reinterpret_cast<PFLocalUserHandle*>(&localUserHandleWrapper) = localUserHandle;

    GameSaveFilesState::Get().progressDelegate.ExecuteIfBound(localUserHandleWrapper, static_cast<FPFGameSaveFilesSyncState>(syncState));
}

void CALLBACK GameSaveFilesUiSyncFailedCallback(
    _In_ PFLocalUserHandle localUserHandle,
    _In_ PFGameSaveFilesSyncState syncState,
    _In_ HRESULT error,
    _In_ void* /*context*/
) noexcept
{
    if (localUserHandle == nullptr)
    {
        UE_LOG(LogPlayFabUnreal, Warning, TEXT("GameSaveFilesUiSyncFailedCallback: localUserHandle is null"));
        return;
    }

    FPFLocalUserHandle localUserHandleWrapper;
    *reinterpret_cast<PFLocalUserHandle*>(&localUserHandleWrapper) = localUserHandle;
    
    GameSaveFilesState::Get().syncFailedDelegate.ExecuteIfBound(localUserHandleWrapper, static_cast<FPFGameSaveFilesSyncState>(syncState), static_cast<int32>(error));
}

void CALLBACK GameSaveFilesUiActiveDeviceContentionCallback(
    _In_ PFLocalUserHandle localUserHandle,
    _In_ PFGameSaveDescriptor* _localGameSave,
    _In_ PFGameSaveDescriptor* _remoteGameSave,
    _In_ void* /*context*/
) noexcept
{
    FPFGameSaveDescriptor localGameSave{};
    localGameSave.time = _localGameSave->time;
    localGameSave.totalBytes = _localGameSave->totalBytes;
    localGameSave.uploadedBytes = _localGameSave->totalBytes;
    localGameSave.deviceType = _localGameSave->deviceType;

    FPFGameSaveDescriptor remoteGameSave{};
    remoteGameSave.time = _remoteGameSave->time;
    remoteGameSave.totalBytes = _remoteGameSave->totalBytes;
    remoteGameSave.uploadedBytes = _remoteGameSave->totalBytes;
    remoteGameSave.deviceType = _remoteGameSave->deviceType;

    if (localUserHandle == nullptr)
    {
        UE_LOG(LogPlayFabUnreal, Warning, TEXT("GameSaveFilesUiActiveDeviceContentionCallback: localUserHandle is null"));
        return;
    }

    FPFLocalUserHandle localUserHandleWrapper;
    *reinterpret_cast<PFLocalUserHandle*>(&localUserHandleWrapper) = localUserHandle;
    
    GameSaveFilesState::Get().activeDeviceContentionDelegate.ExecuteIfBound(localUserHandleWrapper, &localGameSave, &remoteGameSave);
}

void CALLBACK GameSaveFilesUiConflictCallback(
    _In_ PFLocalUserHandle localUserHandle,
    _In_ PFGameSaveDescriptor* _localGameSave,
    _In_ PFGameSaveDescriptor* _remoteGameSave,
    _In_ void* /*context*/
) noexcept
{
    FPFGameSaveDescriptor localGameSave{};
    localGameSave.time = _localGameSave->time;
    localGameSave.totalBytes = _localGameSave->totalBytes;
    localGameSave.uploadedBytes = _localGameSave->totalBytes;
    localGameSave.deviceType = _localGameSave->deviceType;

    FPFGameSaveDescriptor remoteGameSave{};
    remoteGameSave.time = _remoteGameSave->time;
    remoteGameSave.totalBytes = _remoteGameSave->totalBytes;
    remoteGameSave.uploadedBytes = _remoteGameSave->totalBytes;
    remoteGameSave.deviceType = _remoteGameSave->deviceType;

    if (localUserHandle == nullptr)
    {
        UE_LOG(LogPlayFabUnreal, Warning, TEXT("GameSaveFilesUiConflictCallback: localUserHandle is null"));
        return;
    }

    FPFLocalUserHandle localUserHandleWrapper;
    *reinterpret_cast<PFLocalUserHandle*>(&localUserHandleWrapper) = localUserHandle;
    
    GameSaveFilesState::Get().conflictDelegate.ExecuteIfBound(localUserHandleWrapper, &localGameSave, &remoteGameSave);
}

void CALLBACK GameSaveFilesUiOutOfStorageCallback(
    _In_ PFLocalUserHandle localUserHandle,
    _In_ uint64_t requiredBytes,
    _In_ void* /*context*/
) noexcept
{
    if (localUserHandle == nullptr)
    {
        UE_LOG(LogPlayFabUnreal, Warning, TEXT("GameSaveFilesUiOutOfStorageCallback: localUserHandle is null"));
        return;
    }

    FPFLocalUserHandle localUserHandleWrapper;
    *reinterpret_cast<PFLocalUserHandle*>(&localUserHandleWrapper) = localUserHandle;
    
    GameSaveFilesState::Get().outOfStorageDelegate.ExecuteIfBound(localUserHandleWrapper, requiredBytes);
}

bool PLAYFABGAMESAVE_API FPFGameSaveFilesSetUiDelegates(
    _In_ FPFGameSaveFilesUiProgressDelegate progressDelegate,
    _In_ FPFGameSaveFilesUiSyncFailedDelegate syncFailedDelegate,
    _In_ FPFGameSaveFilesUiActiveDeviceContentionDelegate activeDeviceContentionDelegate,
    _In_ FPFGameSaveFilesUiConflictDelegate conflictDelegate,
    _In_ FPFGameSaveFilesUiOutOfStorageDelegate outOfStorageDelegate
) noexcept
{
    auto& state = GameSaveFilesState::Get();

    state.progressDelegate = progressDelegate;
    state.syncFailedDelegate = syncFailedDelegate;
    state.activeDeviceContentionDelegate = activeDeviceContentionDelegate;
    state.conflictDelegate = conflictDelegate;
    state.outOfStorageDelegate = outOfStorageDelegate;

    PFGameSaveUICallbacks callbacks{};
    callbacks.progressCallback = GameSaveFilesUiProgressCallback;
    callbacks.syncFailedCallback = GameSaveFilesUiSyncFailedCallback;
    callbacks.activeDeviceContentionCallback = GameSaveFilesUiActiveDeviceContentionCallback;
    callbacks.conflictCallback = GameSaveFilesUiConflictCallback;
    callbacks.outOfStorageCallback = GameSaveFilesUiOutOfStorageCallback;

    RETURN_FALSE_IF_FAILED(PFGameSaveFilesSetUiCallbacks(&callbacks));

    return true;
}

bool PLAYFABGAMESAVE_API FPFGameSaveFilesUiProgressGetProgress(
    _In_ FPFLocalUserHandle localUserHandle,
    _Out_opt_ FPFGameSaveFilesSyncState* syncState,
    _Out_opt_ uint64* current,
    _Out_opt_ uint64* total
) noexcept
{
    PFGameSaveFilesSyncState cSyncState{};
    RETURN_FALSE_IF_FAILED(PFGameSaveFilesUiProgressGetProgress(localUserHandle.Get(), &cSyncState, reinterpret_cast<uint64_t*>(current), reinterpret_cast<uint64_t*>(total)));
    *syncState = static_cast<FPFGameSaveFilesSyncState>(cSyncState);

    return true;
}

bool PLAYFABGAMESAVE_API FPFGameSaveFilesSetUiProgressResponse(
    _In_ FPFLocalUserHandle localUserHandle,
    _In_ FPFGameSaveFilesUiProgressUserAction action
)
{
    RETURN_FALSE_IF_FAILED(PFGameSaveFilesSetUiProgressResponse(localUserHandle.Get(), static_cast<PFGameSaveFilesUiProgressUserAction>(action)));
    return true;
}

bool PLAYFABGAMESAVE_API FPFGameSaveFilesSetUiSyncFailedResponse(
    _In_ FPFLocalUserHandle localUserHandle,
    _In_ FPFGameSaveFilesUiSyncFailedUserAction action
) noexcept
{
    RETURN_FALSE_IF_FAILED(PFGameSaveFilesSetUiSyncFailedResponse(localUserHandle.Get(), static_cast<PFGameSaveFilesUiSyncFailedUserAction>(action)));
    return true;
}

bool PLAYFABGAMESAVE_API FPFGameSaveFilesSetUiActiveDeviceContentionResponse(
    _In_ FPFLocalUserHandle localUserHandle,
    _In_ FPFGameSaveFilesUiActiveDeviceContentionUserAction action
) noexcept
{
    RETURN_FALSE_IF_FAILED(PFGameSaveFilesSetUiActiveDeviceContentionResponse(localUserHandle.Get(), static_cast<PFGameSaveFilesUiActiveDeviceContentionUserAction>(action)));
    return true;
}

bool PLAYFABGAMESAVE_API FPFGameSaveFilesSetUiConflictResponse(
    _In_ FPFLocalUserHandle localUserHandle,
    _In_ FPFGameSaveFilesUiConflictUserAction action
) noexcept
{
    RETURN_FALSE_IF_FAILED(PFGameSaveFilesSetUiConflictResponse(localUserHandle.Get(), static_cast<PFGameSaveFilesUiConflictUserAction>(action)));
    return true;
}

bool PLAYFABGAMESAVE_API FPFGameSaveFilesSetUiOutOfStorageResponse(
    _In_ FPFLocalUserHandle localUserHandle,
    _In_ FPFGameSaveFilesUiOutOfStorageUserAction action
) noexcept
{
    RETURN_FALSE_IF_FAILED(PFGameSaveFilesSetUiOutOfStorageResponse(localUserHandle.Get(), static_cast<PFGameSaveFilesUiOutOfStorageUserAction>(action)));
    return true;
}