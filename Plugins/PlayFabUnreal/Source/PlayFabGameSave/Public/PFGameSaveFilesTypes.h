// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include "CoreMinimal.h"
THIRD_PARTY_INCLUDES_START
#include <playfab/gamesave/PFGameSaveFilesTypes.h>
THIRD_PARTY_INCLUDES_END

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

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
    /// <summary>
    /// On some platforms, the game can store save files in various locations (e.g. My Docs, local app data, etc)
    /// On those platforms, this lets the game specify where save files are stored.
    /// This should be the root folder of where the game save files are stored.
    /// All its files and subfolders will be synchronized with the cloud.
    /// </summary>
    FString saveFolder;
#endif

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
};

DEFINE_ENUM_FLAG_OPERATORS(FPFGameSaveFilesAddUserOptions);

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
