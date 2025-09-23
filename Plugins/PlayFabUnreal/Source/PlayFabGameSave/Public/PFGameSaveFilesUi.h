// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include "CoreMinimal.h"
#include "PFLocalUser.h"
#include "PFGameSaveFilesTypes.h"

/// <summary>
/// Delegate called to relay progress of the current operation.
/// </summary>
/// <param name="localUserHandle">Local user handle.</param>
/// <param name="syncState">Sync state of the operation.</param>
DECLARE_DELEGATE_TwoParams(
    FPFGameSaveFilesUiProgressDelegate,
    FPFLocalUserHandle /* localUserHandle */,
    FPFGameSaveFilesSyncState /* syncState */
);

/// <summary>
/// Delegate called when syncing game save data fails.
/// </summary>
/// <param name="localUserHandle">Local user handle.</param>
/// <param name="syncState">Sync state of the operation.</param>
/// <param name="error">The failure error code.</param>
DECLARE_DELEGATE_ThreeParams(
    FPFGameSaveFilesUiSyncFailedDelegate,
    FPFLocalUserHandle /* localUserHandle */,
    FPFGameSaveFilesSyncState /* syncState */,
    int32 /* errorCode */
);

/// <summary>
/// Delegate called when there is contention for active device.
/// </summary>
/// <param name="localUserHandle">Local user handle.</param>
/// <param name="localGameSave">Descriptor of local save game.</param>
/// <param name="remoteGameSave">Descriptor of remote save game.</param>
DECLARE_DELEGATE_ThreeParams(
    FPFGameSaveFilesUiActiveDeviceContentionDelegate,
    FPFLocalUserHandle /* localUserHandle */,
    FPFGameSaveDescriptor* /* localGameSave */,
    FPFGameSaveDescriptor* /* removeGameSave */
);

/// <summary>
/// Delegate called when there is conflict between remote and local game save data.
/// </summary>
/// <param name="localUserHandle">Local user handle.</param>
/// <param name="localGameSave">Descriptor of local save game.</param>
/// <param name="remoteGameSave">Descriptor of remote save game.</param>
DECLARE_DELEGATE_ThreeParams(
    FPFGameSaveFilesUiConflictDelegate,
    FPFLocalUserHandle /* localUserHandle */,
    FPFGameSaveDescriptor* /*localGameSave*/,
    FPFGameSaveDescriptor* /*remoteGameSave*/
);

/// <summary>
/// Delegate called when the local device is out of storage space.
/// </summary>
/// <param name="localUserHandle">Local user handle.</param>
/// <param name="requiredBytes">Required bytes.</param>
DECLARE_DELEGATE_TwoParams(
    FPFGameSaveFilesUiOutOfStorageDelegate,
    FPFLocalUserHandle /* localUserHandle */,
    uint64 /* requiredBytes */
);

/// <summary>
/// Sets the UI delegate. These delegates get called during FPFGameSaveFilesAddUserWithUiAsync() or 
/// FPFGameSaveFilesUploadWithUiAsync().
/// 
/// FPFGameSaveFilesAddUserWithUiAsync() may trigger any UI callback while 
/// FPFGameSaveFilesUploadWithUiAsync() will only trigger FPFGameSaveFilesUiProgressCallback and/or 
/// FPFGameSaveFilesUiSyncFailedCallback.
/// 
/// On non-Windows platforms, setting these callbacks is required to trigger game rendered UI dialogs.
/// 
/// On Xbox and Windows platforms, file sync is done in out of process and stock UI is provided by the platform
/// however the title can set these callbacks to render custom UI dialogs as desired.
/// </summary>
/// <param name="progressDelegate">Callback for upload and download progress.</param>
/// <param name="syncFailedDelegate">Callback for sync failure.</param>
/// <param name="activeDeviceContentionDelegate">Callback for active device contention.</param>
/// <param name="conflictDelegate">Callback for conflict.</param>
/// <param name="outOfStorageDelegate">Callback for out of storage.</param>
bool PLAYFABGAMESAVE_API FPFGameSaveFilesSetUiDelegates(
    _In_ FPFGameSaveFilesUiProgressDelegate progressDelegate,
    _In_ FPFGameSaveFilesUiSyncFailedDelegate syncFailedDelegate,
    _In_ FPFGameSaveFilesUiActiveDeviceContentionDelegate activeDeviceContentionDelegate,
    _In_ FPFGameSaveFilesUiConflictDelegate conflictDelegate,
    _In_ FPFGameSaveFilesUiOutOfStorageDelegate outOfStorageDelegate
) noexcept;

/// <summary>
/// For use inside FPFGameSaveFilesUiProgressDelegate.
/// Get the progress of the current operation.
/// </summary>
/// <param name="localUserHandle">Local user handle.</param>
/// <param name="syncState">Sync state of the operation.</param>
/// <param name="current">Current progress.</param>
/// <param name="total">Total progress.</param>
bool PLAYFABGAMESAVE_API FPFGameSaveFilesUiProgressGetProgress(
    _In_ FPFLocalUserHandle localUserHandle,
    _Out_opt_ FPFGameSaveFilesSyncState* syncState,
    _Out_opt_ uint64* current,
    _Out_opt_ uint64* total
) noexcept;

/// <summary>The user action of the PFGameSaveFilesUiProgressCallback.</summary>
enum class FPFGameSaveFilesUiProgressUserAction : uint32
{
    /// <summary>
    /// Cancel the current operation.
    /// </summary>
    Cancel = 0
};

/// <summary>
/// Sets the user response for the FPFGameSaveFilesUiProgressDelegate.
/// This can be called inside or outside of the callback.  The state machine won't progress until the 
/// the user chooses a response, or the async API is canceled.
/// </summary>
/// <param name="localUserHandle">Local user handle.</param>
/// <param name="action">The user action.</param>
bool PLAYFABGAMESAVE_API FPFGameSaveFilesSetUiProgressResponse(
    _In_ FPFLocalUserHandle localUserHandle,
    _In_ FPFGameSaveFilesUiProgressUserAction action
);

/// <summary>The user action of the PFGameSaveFilesUiSyncFailedCallback.</summary>
enum class FPFGameSaveFilesUiSyncFailedUserAction : uint32
{
    /// <summary>
    /// Cancel the current operation.
    /// </summary>
    Cancel = 0,

    /// <summary>
    /// Retry the current operation.
    /// </summary>
    Retry,

    /// <summary>
    /// Treat the user as disconnected from cloud.
    /// This action may only be only be set during FPFGameSaveFilesAddUserWithUiAsync()
    /// 
    /// If FPFGameSaveFilesAddUserWithUiAsync() was called without network access and 
    /// the user chooses PFGameSaveFilesUiSyncFailedUserAction::UseOffline in the FPFGameSaveFilesUiSyncFailedCallback
    /// then the user considered is disconnected from cloud.
    /// 
    /// When the user is disconnected from cloud, FPFGameSaveFilesAddUserWithUiAsync() can be called again if you want to try to 
    /// make the user connected to cloud. 
    /// It will show the failure UI again if the network is still offline.  No need to re-init gamesave but you can if desired.
    /// 
    /// While the user is disconnected from cloud, FPFGameSaveFilesUploadWithUiAsync() will not do anything but return 
    /// E_PF_GAMESAVE_DISCONNECTED_FROM_CLOUD in the async completion if even if there's network access.
    /// </summary>
    UseOffline
};

/// <summary>
/// Sets the user response for the FPFGameSaveFilesUiSyncFailedDelegate.
/// This can be called inside or outside of the callback.  The state machine won't progress until the 
/// the user chooses a response, or the async API is canceled.
/// </summary>
/// <param name="localUserHandle">Local user handle.</param>
/// <param name="action">The user action.</param>
bool PLAYFABGAMESAVE_API FPFGameSaveFilesSetUiSyncFailedResponse(
    _In_ FPFLocalUserHandle localUserHandle,
    _In_ FPFGameSaveFilesUiSyncFailedUserAction action
) noexcept;

/// <summary>The user action of the PFGameSaveFilesUiActiveDeviceContentionCallback.</summary>
enum class FPFGameSaveFilesUiActiveDeviceContentionUserAction : uint32
{
    /// <summary>
    /// Cancel the current operation.
    /// </summary>
    Cancel = 0,

    /// <summary>
    /// Retry the current operation.
    /// </summary>
    Retry,

    /// <summary>
    /// Sync the last saved data.  This makes the local device active.
    /// 
    /// After this, the remote device will not be able to upload since it is no longer the active device.
    /// This prevents unsynchronized progression from multiple devices 
    /// </summary>
    SyncLastSavedData,
};

/// <summary>
/// Sets the user response for the FPFGameSaveFilesUiActiveDeviceContentionDelegate.
/// This can be called inside or outside of the callback.  The state machine won't progress until the 
/// the user chooses a response, or the async API is canceled.
/// </summary>
/// <param name="localUserHandle">Local user handle.</param>
/// <param name="action">The user action.</param>
bool PLAYFABGAMESAVE_API FPFGameSaveFilesSetUiActiveDeviceContentionResponse(
    _In_ FPFLocalUserHandle localUserHandle,
    _In_ FPFGameSaveFilesUiActiveDeviceContentionUserAction action
) noexcept;

/// <summary>The user action of the PFGameSaveFilesUiConflictCallback.</summary>
enum class FPFGameSaveFilesUiConflictUserAction : uint32
{
    /// <summary>
    /// Cancel the current operation.
    /// </summary>
    Cancel = 0,

    /// <summary>
    /// Take the local version.
    /// </summary>
    TakeLocal,

    /// <summary>
    /// Take the remote version.
    /// </summary>
    TakeRemote,
};

/// <summary>
/// Sets the user response for the PFGameSaveFilesUiConflictDelegate.
/// This can be called inside or outside of the callback.  The state machine won't progress until the 
/// the user chooses a response, or the async API is canceled.
/// </summary>
/// <param name="localUserHandle">Local user handle.</param>
/// <param name="action">The user action.</param>
bool PLAYFABGAMESAVE_API FPFGameSaveFilesSetUiConflictResponse(
    _In_ FPFLocalUserHandle localUserHandle,
    _In_ FPFGameSaveFilesUiConflictUserAction action
) noexcept;

/// <summary>The user action of the PFGameSaveFilesUiOutOfStorageCallback.</summary>
enum class FPFGameSaveFilesUiOutOfStorageUserAction : uint32
{
    /// <summary>
    /// Cancel the current operation.
    /// </summary>
    Cancel = 0,

    /// <summary>
    /// Local storage space was cleared, so retry
    /// </summary>
    Retry
};

/// <summary>
/// Sets the user response for the PFGameSaveFilesUiOutOfStorageDelegate.
/// This can be called inside or outside of the callback.  The state machine won't progress until the 
/// the user chooses a response, or the async API is canceled.
/// </summary>
/// <param name="localUserHandle">Local user handle.</param>
/// <param name="action">The user action.</param>
bool PLAYFABGAMESAVE_API FPFGameSaveFilesSetUiOutOfStorageResponse(
    _In_ FPFLocalUserHandle localUserHandle,
    _In_ FPFGameSaveFilesUiOutOfStorageUserAction action
) noexcept;