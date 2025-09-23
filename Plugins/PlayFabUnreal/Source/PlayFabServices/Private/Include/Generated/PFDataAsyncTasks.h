// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#include "CoreMinimal.h"
#include "Async/AsyncWork.h"
#include "Async/Async.h"
#include "XAsyncTaskQueueHelpers.h"
#include "XAsyncTaskManager.h"
#include "XAsyncTask.h"
#include "PFEntity.h"
#include "PFServiceConfig.h"
#include "PFDataUnrealTypes.h"
#include "PFDataTypeConverters.h"

THIRD_PARTY_INCLUDES_START
#include <playfab/services/PFServices.h>
THIRD_PARTY_INCLUDES_END


/// <summary>
/// Abort pending file uploads to an entity's profile.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Aborts the pending upload of the requested files. See also FileDeleteFilesAsync, FileFinalizeFileUploadsAsync,
/// FileGetFilesAsync, FileInitiateFileUploadsAsync.
///
/// When the asynchronous task is complete, call <see cref="PFDataAbortFileUploadsGetResultSize"/> and
/// <see cref="PFDataAbortFileUploadsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FAbortFileUploadsAsyncTask : public FXAsyncTask
{
public:
	FAbortFileUploadsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFDataAbortFileUploadsRequest InRequest,
	const FOnAbortFileUploadsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFDataAbortFileUploadsRequest Request;
	
	FOnAbortFileUploadsCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Delete files on an entity's profile.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Deletes the requested files from the entity's profile. See also FileAbortFileUploadsAsync, FileFinalizeFileUploadsAsync,
/// FileGetFilesAsync, FileInitiateFileUploadsAsync.
///
/// When the asynchronous task is complete, call <see cref="PFDataDeleteFilesGetResultSize"/> and <see
/// cref="PFDataDeleteFilesGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FDeleteFilesAsyncTask : public FXAsyncTask
{
public:
	FDeleteFilesAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFDataDeleteFilesRequest InRequest,
	const FOnDeleteFilesCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFDataDeleteFilesRequest Request;
	
	FOnDeleteFilesCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Finalize file uploads to an entity's profile.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FFinalizeFileUploadsAsyncTask : public FXAsyncTask
{
public:
	FFinalizeFileUploadsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFDataFinalizeFileUploadsRequest InRequest,
	const FOnFinalizeFileUploadsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFDataFinalizeFileUploadsRequest Request;
	
	FOnFinalizeFileUploadsCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Retrieves file metadata from an entity's profile.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FGetFilesAsyncTask : public FXAsyncTask
{
public:
	FGetFilesAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFDataGetFilesRequest InRequest,
	const FOnGetFilesCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFDataGetFilesRequest Request;
	
	FOnGetFilesCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Retrieves objects from an entity's profile.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Gets JSON objects from an entity profile and returns it.  See also ObjectSetObjectsAsync.
///
/// When the asynchronous task is complete, call <see cref="PFDataGetObjectsGetResultSize"/> and <see
/// cref="PFDataGetObjectsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FGetObjectsAsyncTask : public FXAsyncTask
{
public:
	FGetObjectsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFDataGetObjectsRequest InRequest,
	const FOnGetObjectsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFDataGetObjectsRequest Request;
	
	FOnGetObjectsCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Initiates file uploads to an entity's profile.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FInitiateFileUploadsAsyncTask : public FXAsyncTask
{
public:
	FInitiateFileUploadsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFDataInitiateFileUploadsRequest InRequest,
	const FOnInitiateFileUploadsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFDataInitiateFileUploadsRequest Request;
	
	FOnInitiateFileUploadsCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Sets objects on an entity's profile.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FSetObjectsAsyncTask : public FXAsyncTask
{
public:
	FSetObjectsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFDataSetObjectsRequest InRequest,
	const FOnSetObjectsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFDataSetObjectsRequest Request;
	
	FOnSetObjectsCompleted Delegate;

	HRESULT HResult;
};

