// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include "CoreMinimal.h"
#if PLATFORM_WINDOWS || (defined(PLATFORM_XSX) && PLATFORM_XSX) || (defined(PLATFORM_XB1) && PLATFORM_XB1)
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/AllowWindowsPlatformAtomics.h"
#endif
THIRD_PARTY_INCLUDES_START
#include <playfab/gamesave/PFGameSaveFilesTypes.h>
THIRD_PARTY_INCLUDES_END
#if PLATFORM_WINDOWS || (defined(PLATFORM_XSX) && PLATFORM_XSX) || (defined(PLATFORM_XB1) && PLATFORM_XB1)
#include "Windows/HideWindowsPlatformAtomics.h"
#include "Windows/HideWindowsPlatformTypes.h"
#endif

/// <summary>
/// Options to use when initializing the game save system.
/// </summary>
enum class FPFGameSaveInitOptions : uint32
{
    /// <summary>
    /// Other options might be added in future release
    /// </summary>
    None = 0x00, 
};

DEFINE_ENUM_FLAG_OPERATORS(FPFGameSaveInitOptions);

/// <summary>
/// Init args used by PFGameSave
/// </summary>
typedef struct FPFGameSaveInitArgs
{
    /// <summary>
    /// Options from PFGameSaveInitOptions to use when initializing the game save system.
    /// Set to PFGameSaveInitOptions::None for default behavior.
    /// </summary>
    uint64 options;

    /// <summary>
    /// On some platforms, the game can store save files in various locations (e.g. My Docs, local app data, etc)
    /// On those platforms, this lets the game specify where save files are stored.
    /// This should be the root folder of where the game save files are stored.
    /// All its files and subfolders will be synchronized with the cloud.
    /// </summary>
    FString saveFolder;

} FPFGameSaveInitArgs;

/// <summary>
/// Options to use when adding a user to the game save system.
/// </summary>
enum class FPFGameSaveFilesAddUserOptions : uint32
{
    /// <summary>
    /// Default behavior
    /// </summary>
    None = 0x00, 

    /// <summary>
    /// Sync using the most recently verified prior cloud save state (a previously loaded save
    /// that was later replaced by a newer upload). Use when you suspect the latest upload is bad
    /// (e.g. load failure, failed integrity/version check, crash during or immediately after save).
    /// If no such prior state exists this behaves like None and the current latest is kept.
    /// </summary>
    RollbackToLastKnownGood = 0x01,

    /// <summary>
    /// Sync using the save state that was kept aside (the "losing" choice) from the most recent
    /// conflict resolution; falls back to the latest save if none exists.
    /// </summary>
    RollbackToLastConflict = 0x02,
};

DEFINE_ENUM_FLAG_OPERATORS(FPFGameSaveFilesAddUserOptions);

/// <summary>
/// Outcome of an FPFGameSaveFilesAddUserWithUiAsync operation.
///
/// Branch on this value to decide how to proceed. It collapses every possible
/// end state of the operation (success online, success offline, user cancel, and
/// failure) into the small set of cases a game actually needs to handle.
/// </summary>
enum class FPFGameSaveFilesAddUserResult : uint32
{
    /// <summary>
    /// The user was added and is connected to the cloud. Saves will sync.
    /// Proceed to play online.
    /// </summary>
    Success = 0,

    /// <summary>
    /// The user was added but is in offline mode (the user chose "Use Offline"
    /// on a sync-failure prompt, or another device became the active device).
    /// A local save folder is available, but saves will not sync until reconnected.
    /// Detectable afterwards via FPFGameSaveFilesIsConnectedToCloud (the isConnectedToCloud out-param is false).
    /// Proceed to play with local saves and inform the player.
    /// </summary>
    SuccessOffline,

    /// <summary>
    /// The user cancelled (chose Cancel, or "Quit game" on out-of-process platforms),
    /// or the operation was otherwise aborted by the user. The user was NOT added and
    /// there is no save folder. Do not allow play; return to a safe menu.
    /// </summary>
    Cancelled,

    /// <summary>
    /// The operation failed for a reason other than user cancellation (for example
    /// invalid arguments, wrong call sequence, or a service/storage error). The user
    /// was NOT added. The completion delegate's errorMessage carries the HRESULT as a
    /// hex string; handle the sync-failed delegate for the raw HRESULT as an int32.
    /// </summary>
    Failed,
};

/// <summary>
/// Sync state of the game save system
/// </summary>
enum class FPFGameSaveFilesSyncState : uint32
{
    /// <summary>
    /// Not started
    /// </summary>
    NotStarted = 0,

    /// <summary>
    /// Preparing for download
    /// </summary>
    PreparingForDownload,

    /// <summary>
    /// Downloading
    /// </summary>
    Downloading,

    /// <summary>
    /// Preparing for upload
    /// </summary>
    PreparingForUpload,

    /// <summary>
    /// Uploading
    /// </summary>
    Uploading,

    /// <summary>
    /// Sync complete
    /// </summary>
    SyncComplete,
};

/// <summary>
/// Options to use when uploading game save files
/// </summary>
enum class FPFGameSaveFilesUploadOption : uint32
{
    /// <summary>
    /// Default behavior
    /// The device will be kept active after the upload
    /// </summary>
    KeepDeviceActive = 0,

    /// <summary>
    /// Release the device as active.
    /// After this, this device can no longer be used to upload game save files.
    /// To upload again on the same session, call PFGameSaveUninitializeAsync and wait for it to complete.
    /// </summary>
    ReleaseDeviceAsActive
};

/// <summary>
/// Outcome of an FPFGameSaveFilesUploadWithUiAsync operation.
///
/// Branch on this value to decide how to proceed. Unlike AddUser, an upload cannot
/// enter offline mode (uploading while offline fails), so there is no offline case.
/// </summary>
enum class FPFGameSaveFilesUploadResult : uint32
{
    /// <summary>
    /// The upload completed and the save data is synced to the cloud.
    /// </summary>
    Success = 0,

    /// <summary>
    /// The user cancelled the upload (chose Cancel on the progress or sync-failure UI,
    /// or "Quit game" on out-of-process platforms). The upload did not complete.
    /// </summary>
    Cancelled,

    /// <summary>
    /// The upload failed for a reason other than user cancellation (for example the
    /// device is offline / disconnected from cloud, a transient network failure, the
    /// device is no longer the active device, or wrong call sequence). The completion
    /// delegate's errorMessage carries the HRESULT as a hex string; handle the
    /// sync-failed delegate for the raw HRESULT as an int32.
    /// </summary>
    Failed,
};

/// <summary>
/// Active device metadata
/// </summary>
typedef struct FPFGameSaveDescriptor
{
    /// <summary>
    /// Relevant time of the descriptor (can differ depending upon state and usage)
    /// </summary>
    time_t time;

    /// <summary>
    /// total bytes of the save
    /// </summary>
    uint64 totalBytes;

    /// <summary>
    /// size of the pending upload, if any.
    /// </summary>
    uint64 uploadedBytes;

    /// <summary>
    /// Device Type
    /// </summary>
    FString deviceType;

} FPFGameSaveDescriptor;
