// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once
#include "PFUnrealTypes.h"

#pragma push_macro("IN")
#undef IN

/// <summary>
/// FPFDataAbortFileUploadsRequest data model. Aborts the pending upload of the requested files.
/// </summary>
struct PLAYFABSERVICES_API FPFDataAbortFileUploadsRequest
{
	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// The entity to perform this action on.
	/// </summary>
	TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// Names of the files to have their pending uploads aborted.
	/// </summary>
	const TArray<FString> fileNames;

	/// <summary>
	/// Count of fileNames
	/// </summary>
	uint32 fileNamesCount;

	/// <summary>
	/// (Optional) The expected version of the profile, if set and doesn't match the current version of
	/// the profile the operation will not be performed.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> profileVersion;
};

/// <summary>
/// FPFDataAbortFileUploadsResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFDataAbortFileUploadsResponse
{
	/// <summary>
	/// (Optional) The entity id and type.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// The current version of the profile, can be used for concurrency control during updates.
	/// </summary>
	int32 profileVersion;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFDataDeleteFilesRequest data model. Deletes the requested files from the entity's profile.
/// </summary>
struct PLAYFABSERVICES_API FPFDataDeleteFilesRequest
{
	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// The entity to perform this action on.
	/// </summary>
	TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// Names of the files to be deleted.
	/// </summary>
	const TArray<FString> fileNames;

	/// <summary>
	/// Count of fileNames
	/// </summary>
	uint32 fileNamesCount;

	/// <summary>
	/// (Optional) The expected version of the profile, if set and doesn't match the current version of
	/// the profile the operation will not be performed.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> profileVersion;
};

/// <summary>
/// FPFDataDeleteFilesResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFDataDeleteFilesResponse
{
	/// <summary>
	/// (Optional) The entity id and type.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// The current version of the profile, can be used for concurrency control during updates.
	/// </summary>
	int32 profileVersion;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFDataFinalizeFileUploadsRequest data model. Finalizes the upload of the requested files. Verifies
/// that the files have been successfully uploaded and moves the file pointers from pending to live.
/// </summary>
struct PLAYFABSERVICES_API FPFDataFinalizeFileUploadsRequest
{
	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// The entity to perform this action on.
	/// </summary>
	TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// Names of the files to be finalized. Restricted to a-Z, 0-9, '(', ')', '_', '-' and '.'.
	/// </summary>
	const TArray<FString> fileNames;

	/// <summary>
	/// Count of fileNames
	/// </summary>
	uint32 fileNamesCount;

	/// <summary>
	/// The current version of the profile, can be used for concurrency control during updates.
	/// </summary>
	int32 profileVersion;
};

/// <summary>
/// FPFDataGetFileMetadata data model.
/// </summary>
struct PLAYFABSERVICES_API FPFDataGetFileMetadata
{
	/// <summary>
	/// (Optional) Checksum value for the file, can be used to check if the file on the server has changed.
	/// </summary>
	_Maybenull_ const FString checksum;

	/// <summary>
	/// (Optional) Download URL where the file can be retrieved.
	/// </summary>
	_Maybenull_ const FString downloadUrl;

	/// <summary>
	/// (Optional) Name of the file.
	/// </summary>
	_Maybenull_ const FString fileName;

	/// <summary>
	/// Last UTC time the file was modified.
	/// </summary>
	FDateTime lastModified;

	/// <summary>
	/// Storage service's reported byte count.
	/// </summary>
	int32 size;
};

/// <summary>
/// FPFDataFinalizeFileUploadsResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFDataFinalizeFileUploadsResponse
{
	/// <summary>
	/// (Optional) The entity id and type.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) Collection of metadata for the entity's files.
	/// </summary>
	_Maybenull_ TMap<const FString, TSharedPtr<const FPFDataGetFileMetadata>> metadata;

	/// <summary>
	/// Count of metadata
	/// </summary>
	uint32 metadataCount;

	/// <summary>
	/// The current version of the profile, can be used for concurrency control during updates.
	/// </summary>
	int32 profileVersion;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFDataGetFilesRequest data model. Returns URLs that may be used to download the files for a profile
/// for a limited length of time. Only returns files that have been successfully uploaded, files that
/// are still pending will either return the old value, if it exists, or nothing.
/// </summary>
struct PLAYFABSERVICES_API FPFDataGetFilesRequest
{
	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// The entity to perform this action on.
	/// </summary>
	TSharedPtr<const FPFEntityKey> entity;
};

/// <summary>
/// FPFDataGetFilesResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFDataGetFilesResponse
{
	/// <summary>
	/// (Optional) The entity id and type.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) Collection of metadata for the entity's files.
	/// </summary>
	_Maybenull_ TMap<const FString, TSharedPtr<const FPFDataGetFileMetadata>> metadata;

	/// <summary>
	/// Count of metadata
	/// </summary>
	uint32 metadataCount;

	/// <summary>
	/// The current version of the profile, can be used for concurrency control during updates.
	/// </summary>
	int32 profileVersion;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFDataGetObjectsRequest data model. Gets JSON objects from an entity profile and returns it. .
/// </summary>
struct PLAYFABSERVICES_API FPFDataGetObjectsRequest
{
	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// The entity to perform this action on.
	/// </summary>
	TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) Determines whether the object will be returned as an escaped JSON string or as a un-escaped
	/// JSON object. Default is JSON object.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> escapeObject;
};

/// <summary>
/// FPFDataObjectResult data model.
/// </summary>
struct PLAYFABSERVICES_API FPFDataObjectResult
{
	/// <summary>
	/// (Optional) Un-escaped JSON object, if EscapeObject false or default.
	/// </summary>
	FPFJsonObject dataObject;

	/// <summary>
	/// (Optional) Escaped string JSON body of the object, if EscapeObject is true.
	/// </summary>
	_Maybenull_ const FString escapedDataObject;

	/// <summary>
	/// (Optional) Name of the object. Restricted to a-Z, 0-9, '(', ')', '_', '-' and '.'.
	/// </summary>
	_Maybenull_ const FString objectName;
};

/// <summary>
/// FPFDataGetObjectsResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFDataGetObjectsResponse
{
	/// <summary>
	/// (Optional) The entity id and type.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) Requested objects that the calling entity has access to.
	/// </summary>
	_Maybenull_ TMap<const FString, TSharedPtr<const FPFDataObjectResult>> objects;

	/// <summary>
	/// Count of objects
	/// </summary>
	uint32 objectsCount;

	/// <summary>
	/// The current version of the profile, can be used for concurrency control during updates.
	/// </summary>
	int32 profileVersion;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFDataInitiateFileUploadsRequest data model. Returns URLs that may be used to upload the files for
/// a profile 5 minutes. After using the upload calls FinalizeFileUploads must be called to move the file
/// status from pending to live.
/// </summary>
struct PLAYFABSERVICES_API FPFDataInitiateFileUploadsRequest
{
	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// The entity to perform this action on.
	/// </summary>
	TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// Names of the files to be set. Restricted to a-Z, 0-9, '(', ')', '_', '-' and '.'.
	/// </summary>
	const TArray<FString> fileNames;

	/// <summary>
	/// Count of fileNames
	/// </summary>
	uint32 fileNamesCount;

	/// <summary>
	/// (Optional) The expected version of the profile, if set and doesn't match the current version of
	/// the profile the operation will not be performed.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> profileVersion;
};

/// <summary>
/// FPFDataInitiateFileUploadMetadata data model.
/// </summary>
struct PLAYFABSERVICES_API FPFDataInitiateFileUploadMetadata
{
	/// <summary>
	/// (Optional) Name of the file.
	/// </summary>
	_Maybenull_ const FString fileName;

	/// <summary>
	/// (Optional) Location the data should be sent to via an HTTP PUT operation.
	/// </summary>
	_Maybenull_ const FString uploadUrl;
};

/// <summary>
/// FPFDataInitiateFileUploadsResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFDataInitiateFileUploadsResponse
{
	/// <summary>
	/// (Optional) The entity id and type.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// The current version of the profile, can be used for concurrency control during updates.
	/// </summary>
	int32 profileVersion;

	/// <summary>
	/// (Optional) Collection of file names and upload urls.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFDataInitiateFileUploadMetadata>> uploadDetails;

	/// <summary>
	/// Count of uploadDetails
	/// </summary>
	uint32 uploadDetailsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFDataSetObject data model.
/// </summary>
struct PLAYFABSERVICES_API FPFDataSetObject
{
	/// <summary>
	/// (Optional) Body of the object to be saved. If empty and DeleteObject is true object will be deleted
	/// if it exists, or no operation will occur if it does not exist. Only one of Object or EscapedDataObject
	/// fields may be used.
	/// </summary>
	FPFJsonObject dataObject;

	/// <summary>
	/// (Optional) Flag to indicate that this object should be deleted. Both DataObject and EscapedDataObject
	/// must not be set as well.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> deleteObject;

	/// <summary>
	/// (Optional) Body of the object to be saved as an escaped JSON string. If empty and DeleteObject is
	/// true object will be deleted if it exists, or no operation will occur if it does not exist. Only one
	/// of DataObject or EscapedDataObject fields may be used.
	/// </summary>
	_Maybenull_ const FString escapedDataObject;

	/// <summary>
	/// Name of object. Restricted to a-Z, 0-9, '(', ')', '_', '-' and '.'.
	/// </summary>
	const FString objectName;
};

/// <summary>
/// FPFDataSetObjectsRequest data model. Sets JSON objects on the requested entity profile. May include
/// a version number to be used to perform optimistic concurrency operations during update. If the current
/// version differs from the version in the request the request will be ignored. If no version is set
/// on the request then the value will always be updated if the values differ. Using the version value
/// does not guarantee a write though, ConcurrentEditError may still occur if multiple clients are attempting
/// to update the same profile. .
/// </summary>
struct PLAYFABSERVICES_API FPFDataSetObjectsRequest
{
	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// The entity to perform this action on.
	/// </summary>
	TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) Optional field used for concurrency control. By specifying the previously returned value
	/// of ProfileVersion from GetProfile API, you can ensure that the object set will only be performed
	/// if the profile has not been updated by any other clients since the version you last loaded.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> expectedProfileVersion;

	/// <summary>
	/// Collection of objects to set on the profile.
	/// </summary>
	TArray<TSharedPtr<const FPFDataSetObject>> objects;

	/// <summary>
	/// Count of objects
	/// </summary>
	uint32 objectsCount;
};

/// <summary>
/// FPFDataSetObjectInfo data model.
/// </summary>
struct PLAYFABSERVICES_API FPFDataSetObjectInfo
{
	/// <summary>
	/// (Optional) Name of the object.
	/// </summary>
	_Maybenull_ const FString objectName;

	/// <summary>
	/// (Optional) Optional reason to explain why the operation was the result that it was.
	/// </summary>
	_Maybenull_ const FString operationReason;

	/// <summary>
	/// (Optional) Indicates which operation was completed, either Created, Updated, Deleted or None.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFOperationTypes> setResult;
};

/// <summary>
/// FPFDataSetObjectsResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFDataSetObjectsResponse
{
	/// <summary>
	/// New version of the entity profile.
	/// </summary>
	int32 profileVersion;

	/// <summary>
	/// (Optional) New version of the entity profile.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFDataSetObjectInfo>> setResults;

	/// <summary>
	/// Count of setResults
	/// </summary>
	uint32 setResultsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

// Delegates Declarations

DECLARE_DELEGATE_TwoParams(FOnAbortFileUploadsCompleted, const FPFDataAbortFileUploadsResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnDeleteFilesCompleted, const FPFDataDeleteFilesResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnFinalizeFileUploadsCompleted, const FPFDataFinalizeFileUploadsResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnGetFilesCompleted, const FPFDataGetFilesResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnGetObjectsCompleted, const FPFDataGetObjectsResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnInitiateFileUploadsCompleted, const FPFDataInitiateFileUploadsResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnSetObjectsCompleted, const FPFDataSetObjectsResponse&, bool);

#pragma pop_macro("IN")