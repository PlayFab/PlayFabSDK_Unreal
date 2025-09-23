// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include "CoreMinimal.h"
#include "PFGameSaveFilesTypes.h"
#include "PFLocalUser.h"

/// <summary>
/// Initializes the PlayFab Game Save library instance.
/// </summary>
/// <remarks>
/// This will internally call PFInitialize(nullptr) if it hasn't been called already by the
/// title. If control of PFCore background work is needed, the title should explicitly call
/// PFInitialize and PFUninitialize.
/// </remarks>
/// <returns>Result code for this API operation.</returns>
bool PLAYFABGAMESAVE_API FPFGameSaveFilesInitialize(
    _In_ FPFGameSaveInitArgs* args
) noexcept;

/// <summary>
/// Delegate called when a FPFGameSaveFilesAddUserWithUiAsync operation is complete.
/// </summary>
DECLARE_DELEGATE_OneParam(
    FPFGameSaveFilesAddUserWithUiAsyncComplete,
    bool /* succeeded */
);

/// <summary>
/// Adds a user to the game save system.
/// This downloads save state from the cloud as needed, and might trigger these UI callbacks:
///     PFGameSaveFilesUiProgressCallback, 
///     PFGameSaveFilesUiSyncFailedCallback, 
///     PFGameSaveFilesUiActiveDeviceContentionCallback,
///     PFGameSaveFilesUiConflictCallback,
///     PFGameSaveFilesUiOutOfStorageCallback
/// 
/// See PFGameSaveFilesSetUiCallbacks for more detail.
/// PFGameSaveFilesInitialize must be called prior.
/// 
/// On Xbox and Windows platforms, stock UI is provided by the system.
/// </summary>
/// <param name="localUserHandle">Local user to add.</param>
/// <param name="options">Options to use when adding the user.</param>
/// <param name="userAddedDelegate">A delegate that gets called upon completion.</param>
/// <returns>
/// To retrieve the result of a call to PFGameSaveFilesAddUserWithUiAsync, call 
/// PFGameSaveFilesAddUserWithUiResult. After this call completes, you can call 
/// PFGameSaveFilesGetFolder to get the root folder of the game save files 
/// and folders for this user.  All the root folder's files and subfolders will 
/// be synchronized with the cloud.
/// 
/// This can only be called once per user, typically before showing the game's main menu.
/// To re-trigger the download the same user, call PFGameSaveFilesUninitializeAsync and wait 
/// for it to complete first
/// </returns>
bool PLAYFABGAMESAVE_API FPFGameSaveFilesAddUserWithUiAsync(
    _In_ FPFLocalUserHandle localUserHandle,
    _In_ FPFGameSaveFilesAddUserOptions options,
    _In_ FPFGameSaveFilesAddUserWithUiAsyncComplete userAddedDelegate
) noexcept;

/// <summary>
/// Returns the root folder of the game save files and folders for this user.
/// All its files and subfolders will be synchronized with the cloud.
/// The user must be added first using FPFGameSaveFilesAddUserWithUiAsync.
/// </summary>
/// <param name="localUserHandle">Local user whose game save folder to return.</param>
/// <param name="folder">The save game folder for the provided user.</param>
bool PLAYFABGAMESAVE_API FPFGameSaveFilesGetFolder(
    _In_ FPFLocalUserHandle localUserHandle,
    _Out_ FString& folder
) noexcept;

/// <summary>
/// Delegate called when a FPFGameSaveFilesUploadWithUiAsync operation is complete.
/// </summary>
DECLARE_DELEGATE_OneParam(
    FPFGameSaveFilesUploadWithUiAsyncComplete,
    bool /* succeeded */
);

/// <summary>
/// Uploads the all files and folders in the folder returned by PFGameSaveFilesGetFolder().
/// The user must be added first.
/// 
/// On non-Windows platforms, the upload happens in the same process as the game and 
/// might trigger UI these callbacks:
///    PFGameSaveFilesUiProgressCallback,
///    PFGameSaveFilesUiSyncFailedCallback
/// 
/// On Xbox and Windows platforms, the upload is done out of process and stock UI is 
/// provided by the system.  Calling this API is optional on Xbox and Windows platforms as the 
/// upload will automatically happen when the game isn't running.
/// </summary>
/// <param name="localUserHandle">Local user whose game save files and folders to upload.</param>
/// <param name="option">Option to use when uploading the files and folders.</param>
/// <param name="uploadCompleteDelegate">A delegate that will be called when the upload completes.</param>
/// <returns>
/// To retrieve the result of a call to PFGameSaveFilesUploadWithUiAsync, call PFGameSaveFilesUploadWithUiResult.
/// </returns>
bool PLAYFABGAMESAVE_API FPFGameSaveFilesUploadWithUiAsync(
    _In_ FPFLocalUserHandle localUserHandle,
    _In_ FPFGameSaveFilesUploadOption option,
    _In_ FPFGameSaveFilesUploadWithUiAsyncComplete uploadCompleteDelegate
) noexcept;


/// <summary>
/// Returns the amount of data available to store save data in bytes using the PFGameSaveFiles API.
/// Going over quota will return a negative number and cause the service to block the upload.
/// </summary>
/// <param name="localUserHandle">Local user whose quota to return.</param>
/// <param name="remainingQuota">The amount of data available to store save data in bytes.
/// Going over quota will return a negative number and cause the service to block the upload
/// </param>
/// <returns>Result code for this API operation. 
/// If called when disconnected from cloud, it will return E_PF_GAMESAVE_DISCONNECTED_FROM_CLOUD.
/// </returns>
bool PLAYFABGAMESAVE_API FPFGameSaveFilesGetRemainingQuota(
    _In_ FPFLocalUserHandle localUserHandle,
    _Out_ int64* remainingQuota
) noexcept;

/// <summary>
/// Returns if the user is connected to cloud.
/// 
/// The user can be disconnected to cloud when calling PFGameSaveFilesAddUserWithUiAsync() without network access and 
/// the user chooses PFGameSaveFilesUiSyncFailedUserAction::UseOffline in the PFGameSaveFilesUiSyncFailedCallback.
/// The user can also be disconnected to cloud at anytime if another device is becomes the active device.
/// 
/// When the disconnected from cloud, PFGameSaveFilesAddUserWithUiAsync() can be called again if you want to try connect to the cloud.
/// It will show the failure UI again if the network is still offline.  No need to re-init gamesave but you can if desired.
/// 
/// While the disconnected from cloud, PFGameSaveFilesUploadWithUiAsync() will not do anything but return E_PF_GAMESAVE_DISCONNECTED_FROM_CLOUD 
/// in the async completion if even if there's network access.
/// </summary>
/// <param name="localUserHandle">Local user whose quota to return.</param>
/// <param name="isConnectedToCloud">Set to true if the user is connected to cloud</param>
/// <returns>Result code for this API operation.</returns>
bool PLAYFABGAMESAVE_API FPFGameSaveFilesIsConnectedToCloud(
    _In_ FPFLocalUserHandle localUserHandle,
    _Out_ bool* isConnectedToCloud
) noexcept;

/// <summary>
/// Callback for when the active device changes
/// </summary>
/// <param name="localUserHandle">Local user handle.</param>
/// <param name="activeDevice">Active device metadata.</param>
/// <param name="context">Context passed to the callback.</param>
DECLARE_DELEGATE_TwoParams(
    FPFGameSaveFilesActiveDeviceChangedDelegate,
    FPFLocalUserHandle /* localUserHandle */,
    FPFGameSaveDescriptor* /* activeDevice */
);

/// <summary>
/// Sets the active device changed callback.
/// When this callback is triggered, it means the user moved to another device so 
/// this title should return to main menu
/// </summary>
/// <param name="callbackQueue">The async queue the callback should be invoked on.</param>
/// <param name="callback">The callback to be invoked when the active device changes.</param>
/// <param name="context">The context to be passed to the callback.</param>
/// <returns>Result code for this API operation.</returns>
bool PLAYFABGAMESAVE_API FPFGameSaveFilesSetActiveDeviceChangedDelegate(
    _In_ FPFGameSaveFilesActiveDeviceChangedDelegate delegate
) noexcept;

/// <summary>
/// Delegate called when a FPFGameSaveFilesUninitializeAsync operation is complete. 
/// </summary>
DECLARE_DELEGATE_OneParam(
    FPFGameSaveFilesUninitializeComplete,
    bool /* succeeded */
);

/// <summary>
/// Cleanup PlayFab Game Save library instance.
/// </summary>
/// <param name="delegate">A delegate to be invoked upon compeltion.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// To retrieve the result of a call to PFGameSaveFilesUninitializeAsync, call PFGameSaveFilesUninitializeResult.
/// This will internally call PFUninitializeAsync() if PFGameSaveInitialize() needed 
/// to call PFInitialize() internally.
/// </remarks>
bool PLAYFABGAMESAVE_API FPFGameSaveFilesUninitializeAsync(
    _In_ FPFGameSaveFilesUninitializeComplete delegate
) noexcept;
