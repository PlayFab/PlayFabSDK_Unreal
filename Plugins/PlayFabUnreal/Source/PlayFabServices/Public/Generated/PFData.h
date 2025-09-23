// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include "CoreMinimal.h"
#include "XAsyncTaskManager.h"
#include "PFDataAsyncTasks.h"

THIRD_PARTY_INCLUDES_START
#include <playfab/services/PFServices.h>
THIRD_PARTY_INCLUDES_END

extern "C"
{
/// <summary>
/// Abort pending file uploads to an entity's profile.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Aborts the pending upload of the requested files. See also FileDeleteFilesAsync, FileFinalizeFileUploadsAsync,
/// FileGetFilesAsync, FileInitiateFileUploadsAsync.
///
/// When the asynchronous task is complete, call <see cref="PFDataAbortFileUploadsGetResultSize"/> and
/// <see cref="PFDataAbortFileUploadsGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFDataAbortFileUploadsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFDataAbortFileUploadsRequest* request,
	_Inout_ FOnAbortFileUploadsCompleted delegate
) noexcept;

/// <summary>
/// Delete files on an entity's profile.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Deletes the requested files from the entity's profile. See also FileAbortFileUploadsAsync, FileFinalizeFileUploadsAsync,
/// FileGetFilesAsync, FileInitiateFileUploadsAsync.
///
/// When the asynchronous task is complete, call <see cref="PFDataDeleteFilesGetResultSize"/> and <see
/// cref="PFDataDeleteFilesGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFDataDeleteFilesAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFDataDeleteFilesRequest* request,
	_Inout_ FOnDeleteFilesCompleted delegate
) noexcept;

/// <summary>
/// Finalize file uploads to an entity's profile.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Finalizes the upload of the requested files. Verifies that the files have been successfully uploaded
/// and moves the file pointers from pending to live. See also FileAbortFileUploadsAsync, FileDeleteFilesAsync,
/// FileGetFilesAsync, FileInitiateFileUploadsAsync.
///
/// When the asynchronous task is complete, call <see cref="PFDataFinalizeFileUploadsGetResultSize"/>
/// and <see cref="PFDataFinalizeFileUploadsGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFDataFinalizeFileUploadsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFDataFinalizeFileUploadsRequest* request,
	_Inout_ FOnFinalizeFileUploadsCompleted delegate
) noexcept;

/// <summary>
/// Retrieves file metadata from an entity's profile.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Returns URLs that may be used to download the files for a profile for a limited length of time. Only
/// returns files that have been successfully uploaded, files that are still pending will either return
/// the old value, if it exists, or nothing. See also FileAbortFileUploadsAsync, FileDeleteFilesAsync,
/// FileFinalizeFileUploadsAsync, FileInitiateFileUploadsAsync.
///
/// When the asynchronous task is complete, call <see cref="PFDataGetFilesGetResultSize"/> and <see cref="PFDataGetFilesGetResult"/>
/// to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFDataGetFilesAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFDataGetFilesRequest* request,
	_Inout_ FOnGetFilesCompleted delegate
) noexcept;

/// <summary>
/// Retrieves objects from an entity's profile.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Gets JSON objects from an entity profile and returns it.  See also ObjectSetObjectsAsync.
///
/// When the asynchronous task is complete, call <see cref="PFDataGetObjectsGetResultSize"/> and <see
/// cref="PFDataGetObjectsGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFDataGetObjectsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFDataGetObjectsRequest* request,
	_Inout_ FOnGetObjectsCompleted delegate
) noexcept;

/// <summary>
/// Initiates file uploads to an entity's profile.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Returns URLs that may be used to upload the files for a profile 5 minutes. After using the upload
/// calls FinalizeFileUploads must be called to move the file status from pending to live. See also FileAbortFileUploadsAsync,
/// FileDeleteFilesAsync, FileFinalizeFileUploadsAsync, FileGetFilesAsync.
///
/// When the asynchronous task is complete, call <see cref="PFDataInitiateFileUploadsGetResultSize"/>
/// and <see cref="PFDataInitiateFileUploadsGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFDataInitiateFileUploadsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFDataInitiateFileUploadsRequest* request,
	_Inout_ FOnInitiateFileUploadsCompleted delegate
) noexcept;

/// <summary>
/// Sets objects on an entity's profile.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Sets JSON objects on the requested entity profile. May include a version number to be used to perform
/// optimistic concurrency operations during update. If the current version differs from the version in
/// the request the request will be ignored. If no version is set on the request then the value will always
/// be updated if the values differ. Using the version value does not guarantee a write though, ConcurrentEditError
/// may still occur if multiple clients are attempting to update the same profile.  See also ObjectGetObjectsAsync.
///
/// When the asynchronous task is complete, call <see cref="PFDataSetObjectsGetResultSize"/> and <see
/// cref="PFDataSetObjectsGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFDataSetObjectsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFDataSetObjectsRequest* request,
	_Inout_ FOnSetObjectsCompleted delegate
) noexcept;

}
