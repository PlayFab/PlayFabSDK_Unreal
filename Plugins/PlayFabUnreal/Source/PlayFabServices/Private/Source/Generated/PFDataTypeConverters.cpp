// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFDataTypeConverters.h"

TSharedPtr<const FPFDataAbortFileUploadsRequest> ConvertAbortFileUploadsRequestToUnreal(const PFDataAbortFileUploadsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFDataAbortFileUploadsRequest> ConvertedType = MakeShared<FPFDataAbortFileUploadsRequest>(FPFDataAbortFileUploadsRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.fileNames = ConvertCharArrayToUnreal(Datatype->fileNames, Datatype->fileNamesCount),
		.fileNamesCount = Datatype->fileNamesCount,
		.profileVersion = TSharedPtr<const int32>(Datatype->profileVersion)
	});

	return ConvertedType;
}

const PFDataAbortFileUploadsRequest* ConvertAbortFileUploadsRequestToPlayfab(TSharedPtr<const FPFDataAbortFileUploadsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFDataAbortFileUploadsRequest* ConvertedType = new PFDataAbortFileUploadsRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.fileNames = ConvertFStringArrayToPlayfab(Datatype->fileNames),
		.fileNamesCount = (uint32_t)Datatype->fileNames.Num(),
		.profileVersion = Datatype->profileVersion ? new int32(*Datatype->profileVersion) : nullptr
	};

	return ConvertedType;
}

TSharedPtr<const FPFDataAbortFileUploadsResponse> ConvertAbortFileUploadsResponseToUnreal(const PFDataAbortFileUploadsResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFDataAbortFileUploadsResponse> ConvertedType = MakeShared<FPFDataAbortFileUploadsResponse>(FPFDataAbortFileUploadsResponse{
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.profileVersion = Datatype->profileVersion
	});

	return ConvertedType;
}

const PFDataAbortFileUploadsResponse* ConvertAbortFileUploadsResponseToPlayfab(TSharedPtr<const FPFDataAbortFileUploadsResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFDataAbortFileUploadsResponse* ConvertedType = new PFDataAbortFileUploadsResponse{
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.profileVersion = Datatype->profileVersion
	};

	return ConvertedType;
}

TSharedPtr<const FPFDataDeleteFilesRequest> ConvertDeleteFilesRequestToUnreal(const PFDataDeleteFilesRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFDataDeleteFilesRequest> ConvertedType = MakeShared<FPFDataDeleteFilesRequest>(FPFDataDeleteFilesRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.fileNames = ConvertCharArrayToUnreal(Datatype->fileNames, Datatype->fileNamesCount),
		.fileNamesCount = Datatype->fileNamesCount,
		.profileVersion = TSharedPtr<const int32>(Datatype->profileVersion)
	});

	return ConvertedType;
}

const PFDataDeleteFilesRequest* ConvertDeleteFilesRequestToPlayfab(TSharedPtr<const FPFDataDeleteFilesRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFDataDeleteFilesRequest* ConvertedType = new PFDataDeleteFilesRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.fileNames = ConvertFStringArrayToPlayfab(Datatype->fileNames),
		.fileNamesCount = (uint32_t)Datatype->fileNames.Num(),
		.profileVersion = Datatype->profileVersion ? new int32(*Datatype->profileVersion) : nullptr
	};

	return ConvertedType;
}

TSharedPtr<const FPFDataDeleteFilesResponse> ConvertDeleteFilesResponseToUnreal(const PFDataDeleteFilesResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFDataDeleteFilesResponse> ConvertedType = MakeShared<FPFDataDeleteFilesResponse>(FPFDataDeleteFilesResponse{
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.profileVersion = Datatype->profileVersion
	});

	return ConvertedType;
}

const PFDataDeleteFilesResponse* ConvertDeleteFilesResponseToPlayfab(TSharedPtr<const FPFDataDeleteFilesResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFDataDeleteFilesResponse* ConvertedType = new PFDataDeleteFilesResponse{
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.profileVersion = Datatype->profileVersion
	};

	return ConvertedType;
}

TSharedPtr<const FPFDataFinalizeFileUploadsRequest> ConvertFinalizeFileUploadsRequestToUnreal(const PFDataFinalizeFileUploadsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFDataFinalizeFileUploadsRequest> ConvertedType = MakeShared<FPFDataFinalizeFileUploadsRequest>(FPFDataFinalizeFileUploadsRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.fileNames = ConvertCharArrayToUnreal(Datatype->fileNames, Datatype->fileNamesCount),
		.fileNamesCount = Datatype->fileNamesCount,
		.profileVersion = Datatype->profileVersion
	});

	return ConvertedType;
}

const PFDataFinalizeFileUploadsRequest* ConvertFinalizeFileUploadsRequestToPlayfab(TSharedPtr<const FPFDataFinalizeFileUploadsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFDataFinalizeFileUploadsRequest* ConvertedType = new PFDataFinalizeFileUploadsRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.fileNames = ConvertFStringArrayToPlayfab(Datatype->fileNames),
		.fileNamesCount = (uint32_t)Datatype->fileNames.Num(),
		.profileVersion = Datatype->profileVersion
	};

	return ConvertedType;
}

TSharedPtr<const FPFDataGetFileMetadata> ConvertGetFileMetadataToUnreal(const PFDataGetFileMetadata* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFDataGetFileMetadata> ConvertedType = MakeShared<FPFDataGetFileMetadata>(FPFDataGetFileMetadata{
		.checksum = Datatype->checksum == nullptr ? FString() : FString(Datatype->checksum),
		.downloadUrl = Datatype->downloadUrl == nullptr ? FString() : FString(Datatype->downloadUrl),
		.fileName = Datatype->fileName == nullptr ? FString() : FString(Datatype->fileName),
		.lastModified = FDateTime::FromUnixTimestamp((int64)Datatype->lastModified),
		.size = Datatype->size
	});

	return ConvertedType;
}

const PFDataGetFileMetadata* ConvertGetFileMetadataToPlayfab(TSharedPtr<const FPFDataGetFileMetadata> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFDataGetFileMetadata* ConvertedType = new PFDataGetFileMetadata{
		.checksum = ConvertFStringToCharPtr(Datatype->checksum),
		.downloadUrl = ConvertFStringToCharPtr(Datatype->downloadUrl),
		.fileName = ConvertFStringToCharPtr(Datatype->fileName),
		.lastModified = Datatype->lastModified.ToUnixTimestamp(),
		.size = Datatype->size
	};

	return ConvertedType;
}

TSharedPtr<const FPFDataFinalizeFileUploadsResponse> ConvertFinalizeFileUploadsResponseToUnreal(const PFDataFinalizeFileUploadsResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFDataFinalizeFileUploadsResponse> ConvertedType = MakeShared<FPFDataFinalizeFileUploadsResponse>(FPFDataFinalizeFileUploadsResponse{
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.metadata = ConvertPlayfabMapToUnreal<PFDataGetFileMetadataDictionaryEntry, FPFDataGetFileMetadata, PFDataGetFileMetadata>(Datatype->metadata, Datatype->metadataCount, ConvertGetFileMetadataToUnreal),
		.metadataCount = Datatype->metadataCount,
		.profileVersion = Datatype->profileVersion
	});

	return ConvertedType;
}

const PFDataFinalizeFileUploadsResponse* ConvertFinalizeFileUploadsResponseToPlayfab(TSharedPtr<const FPFDataFinalizeFileUploadsResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFDataFinalizeFileUploadsResponse* ConvertedType = new PFDataFinalizeFileUploadsResponse{
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.metadata = ConvertUnrealMapToPlayfab<PFDataGetFileMetadataDictionaryEntry, FPFDataGetFileMetadata, PFDataGetFileMetadata>(Datatype->metadata, ConvertGetFileMetadataToPlayfab),
		.metadataCount = (uint32_t)Datatype->metadata.Num(),
		.profileVersion = Datatype->profileVersion
	};

	return ConvertedType;
}

TSharedPtr<const FPFDataGetFilesRequest> ConvertGetFilesRequestToUnreal(const PFDataGetFilesRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFDataGetFilesRequest> ConvertedType = MakeShared<FPFDataGetFilesRequest>(FPFDataGetFilesRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity)
	});

	return ConvertedType;
}

const PFDataGetFilesRequest* ConvertGetFilesRequestToPlayfab(TSharedPtr<const FPFDataGetFilesRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFDataGetFilesRequest* ConvertedType = new PFDataGetFilesRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity)
	};

	return ConvertedType;
}

TSharedPtr<const FPFDataGetFilesResponse> ConvertGetFilesResponseToUnreal(const PFDataGetFilesResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFDataGetFilesResponse> ConvertedType = MakeShared<FPFDataGetFilesResponse>(FPFDataGetFilesResponse{
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.metadata = ConvertPlayfabMapToUnreal<PFDataGetFileMetadataDictionaryEntry, FPFDataGetFileMetadata, PFDataGetFileMetadata>(Datatype->metadata, Datatype->metadataCount, ConvertGetFileMetadataToUnreal),
		.metadataCount = Datatype->metadataCount,
		.profileVersion = Datatype->profileVersion
	});

	return ConvertedType;
}

const PFDataGetFilesResponse* ConvertGetFilesResponseToPlayfab(TSharedPtr<const FPFDataGetFilesResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFDataGetFilesResponse* ConvertedType = new PFDataGetFilesResponse{
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.metadata = ConvertUnrealMapToPlayfab<PFDataGetFileMetadataDictionaryEntry, FPFDataGetFileMetadata, PFDataGetFileMetadata>(Datatype->metadata, ConvertGetFileMetadataToPlayfab),
		.metadataCount = (uint32_t)Datatype->metadata.Num(),
		.profileVersion = Datatype->profileVersion
	};

	return ConvertedType;
}

TSharedPtr<const FPFDataGetObjectsRequest> ConvertGetObjectsRequestToUnreal(const PFDataGetObjectsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFDataGetObjectsRequest> ConvertedType = MakeShared<FPFDataGetObjectsRequest>(FPFDataGetObjectsRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.escapeObject = TSharedPtr<const bool>(Datatype->escapeObject)
	});

	return ConvertedType;
}

const PFDataGetObjectsRequest* ConvertGetObjectsRequestToPlayfab(TSharedPtr<const FPFDataGetObjectsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFDataGetObjectsRequest* ConvertedType = new PFDataGetObjectsRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.escapeObject = Datatype->escapeObject ? new bool(*Datatype->escapeObject) : nullptr
	};

	return ConvertedType;
}

TSharedPtr<const FPFDataObjectResult> ConvertObjectResultToUnreal(const PFDataObjectResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFDataObjectResult> ConvertedType = MakeShared<FPFDataObjectResult>(FPFDataObjectResult{
		.dataObject = FPFJsonObject{ .stringValue = FString(Datatype->dataObject.stringValue) },
		.escapedDataObject = Datatype->escapedDataObject == nullptr ? FString() : FString(Datatype->escapedDataObject),
		.objectName = Datatype->objectName == nullptr ? FString() : FString(Datatype->objectName)
	});

	return ConvertedType;
}

const PFDataObjectResult* ConvertObjectResultToPlayfab(TSharedPtr<const FPFDataObjectResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFDataObjectResult* ConvertedType = new PFDataObjectResult{
		.dataObject = PFJsonObject{ .stringValue = ConvertFStringToCharPtr(Datatype->dataObject.stringValue) },
		.escapedDataObject = ConvertFStringToCharPtr(Datatype->escapedDataObject),
		.objectName = ConvertFStringToCharPtr(Datatype->objectName)
	};

	return ConvertedType;
}

TSharedPtr<const FPFDataGetObjectsResponse> ConvertGetObjectsResponseToUnreal(const PFDataGetObjectsResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFDataGetObjectsResponse> ConvertedType = MakeShared<FPFDataGetObjectsResponse>(FPFDataGetObjectsResponse{
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.objects = ConvertPlayfabMapToUnreal<PFDataObjectResultDictionaryEntry, FPFDataObjectResult, PFDataObjectResult>(Datatype->objects, Datatype->objectsCount, ConvertObjectResultToUnreal),
		.objectsCount = Datatype->objectsCount,
		.profileVersion = Datatype->profileVersion
	});

	return ConvertedType;
}

const PFDataGetObjectsResponse* ConvertGetObjectsResponseToPlayfab(TSharedPtr<const FPFDataGetObjectsResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFDataGetObjectsResponse* ConvertedType = new PFDataGetObjectsResponse{
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.objects = ConvertUnrealMapToPlayfab<PFDataObjectResultDictionaryEntry, FPFDataObjectResult, PFDataObjectResult>(Datatype->objects, ConvertObjectResultToPlayfab),
		.objectsCount = (uint32_t)Datatype->objects.Num(),
		.profileVersion = Datatype->profileVersion
	};

	return ConvertedType;
}

TSharedPtr<const FPFDataInitiateFileUploadsRequest> ConvertInitiateFileUploadsRequestToUnreal(const PFDataInitiateFileUploadsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFDataInitiateFileUploadsRequest> ConvertedType = MakeShared<FPFDataInitiateFileUploadsRequest>(FPFDataInitiateFileUploadsRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.fileNames = ConvertCharArrayToUnreal(Datatype->fileNames, Datatype->fileNamesCount),
		.fileNamesCount = Datatype->fileNamesCount,
		.profileVersion = TSharedPtr<const int32>(Datatype->profileVersion)
	});

	return ConvertedType;
}

const PFDataInitiateFileUploadsRequest* ConvertInitiateFileUploadsRequestToPlayfab(TSharedPtr<const FPFDataInitiateFileUploadsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFDataInitiateFileUploadsRequest* ConvertedType = new PFDataInitiateFileUploadsRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.fileNames = ConvertFStringArrayToPlayfab(Datatype->fileNames),
		.fileNamesCount = (uint32_t)Datatype->fileNames.Num(),
		.profileVersion = Datatype->profileVersion ? new int32(*Datatype->profileVersion) : nullptr
	};

	return ConvertedType;
}

TSharedPtr<const FPFDataInitiateFileUploadMetadata> ConvertInitiateFileUploadMetadataToUnreal(const PFDataInitiateFileUploadMetadata* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFDataInitiateFileUploadMetadata> ConvertedType = MakeShared<FPFDataInitiateFileUploadMetadata>(FPFDataInitiateFileUploadMetadata{
		.fileName = Datatype->fileName == nullptr ? FString() : FString(Datatype->fileName),
		.uploadUrl = Datatype->uploadUrl == nullptr ? FString() : FString(Datatype->uploadUrl)
	});

	return ConvertedType;
}

const PFDataInitiateFileUploadMetadata* ConvertInitiateFileUploadMetadataToPlayfab(TSharedPtr<const FPFDataInitiateFileUploadMetadata> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFDataInitiateFileUploadMetadata* ConvertedType = new PFDataInitiateFileUploadMetadata{
		.fileName = ConvertFStringToCharPtr(Datatype->fileName),
		.uploadUrl = ConvertFStringToCharPtr(Datatype->uploadUrl)
	};

	return ConvertedType;
}

TSharedPtr<const FPFDataInitiateFileUploadsResponse> ConvertInitiateFileUploadsResponseToUnreal(const PFDataInitiateFileUploadsResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFDataInitiateFileUploadsResponse> ConvertedType = MakeShared<FPFDataInitiateFileUploadsResponse>(FPFDataInitiateFileUploadsResponse{
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.profileVersion = Datatype->profileVersion,
		.uploadDetails = ConvertPlayfabArrayToUnreal<PFDataInitiateFileUploadMetadata, FPFDataInitiateFileUploadMetadata>(Datatype->uploadDetails, Datatype->uploadDetailsCount, ConvertInitiateFileUploadMetadataToUnreal),
		.uploadDetailsCount = Datatype->uploadDetailsCount
	});

	return ConvertedType;
}

const PFDataInitiateFileUploadsResponse* ConvertInitiateFileUploadsResponseToPlayfab(TSharedPtr<const FPFDataInitiateFileUploadsResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFDataInitiateFileUploadsResponse* ConvertedType = new PFDataInitiateFileUploadsResponse{
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.profileVersion = Datatype->profileVersion,
		.uploadDetails = ConvertUnrealArrayToPlayfab<PFDataInitiateFileUploadMetadata, FPFDataInitiateFileUploadMetadata>(Datatype->uploadDetails, ConvertInitiateFileUploadMetadataToPlayfab),
		.uploadDetailsCount = (uint32_t)Datatype->uploadDetails.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFDataSetObject> ConvertSetObjectToUnreal(const PFDataSetObject* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFDataSetObject> ConvertedType = MakeShared<FPFDataSetObject>(FPFDataSetObject{
		.dataObject = FPFJsonObject{ .stringValue = FString(Datatype->dataObject.stringValue) },
		.deleteObject = TSharedPtr<const bool>(Datatype->deleteObject),
		.escapedDataObject = Datatype->escapedDataObject == nullptr ? FString() : FString(Datatype->escapedDataObject),
		.objectName = Datatype->objectName == nullptr ? FString() : FString(Datatype->objectName)
	});

	return ConvertedType;
}

const PFDataSetObject* ConvertSetObjectToPlayfab(TSharedPtr<const FPFDataSetObject> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFDataSetObject* ConvertedType = new PFDataSetObject{
		.dataObject = PFJsonObject{ .stringValue = ConvertFStringToCharPtr(Datatype->dataObject.stringValue) },
		.deleteObject = Datatype->deleteObject ? new bool(*Datatype->deleteObject) : nullptr,
		.escapedDataObject = ConvertFStringToCharPtr(Datatype->escapedDataObject),
		.objectName = ConvertFStringToCharPtr(Datatype->objectName)
	};

	return ConvertedType;
}

TSharedPtr<const FPFDataSetObjectsRequest> ConvertSetObjectsRequestToUnreal(const PFDataSetObjectsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFDataSetObjectsRequest> ConvertedType = MakeShared<FPFDataSetObjectsRequest>(FPFDataSetObjectsRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.expectedProfileVersion = TSharedPtr<const int32>(Datatype->expectedProfileVersion),
		.objects = ConvertPlayfabArrayToUnreal<PFDataSetObject, FPFDataSetObject>(Datatype->objects, Datatype->objectsCount, ConvertSetObjectToUnreal),
		.objectsCount = Datatype->objectsCount
	});

	return ConvertedType;
}

const PFDataSetObjectsRequest* ConvertSetObjectsRequestToPlayfab(TSharedPtr<const FPFDataSetObjectsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFDataSetObjectsRequest* ConvertedType = new PFDataSetObjectsRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.expectedProfileVersion = Datatype->expectedProfileVersion ? new int32(*Datatype->expectedProfileVersion) : nullptr,
		.objects = ConvertUnrealArrayToPlayfab<PFDataSetObject, FPFDataSetObject>(Datatype->objects, ConvertSetObjectToPlayfab),
		.objectsCount = (uint32_t)Datatype->objects.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFDataSetObjectInfo> ConvertSetObjectInfoToUnreal(const PFDataSetObjectInfo* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFDataSetObjectInfo> ConvertedType = MakeShared<FPFDataSetObjectInfo>(FPFDataSetObjectInfo{
		.objectName = Datatype->objectName == nullptr ? FString() : FString(Datatype->objectName),
		.operationReason = Datatype->operationReason == nullptr ? FString() : FString(Datatype->operationReason),
		.setResult = MakeShared<FPFOperationTypes>(ConvertOperationTypesToUnreal(Datatype->setResult))
	});

	return ConvertedType;
}

const PFDataSetObjectInfo* ConvertSetObjectInfoToPlayfab(TSharedPtr<const FPFDataSetObjectInfo> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFDataSetObjectInfo* ConvertedType = new PFDataSetObjectInfo{
		.objectName = ConvertFStringToCharPtr(Datatype->objectName),
		.operationReason = ConvertFStringToCharPtr(Datatype->operationReason),
		.setResult = new PFOperationTypes(ConvertOperationTypesToPlayfab(Datatype->setResult))
	};

	return ConvertedType;
}

TSharedPtr<const FPFDataSetObjectsResponse> ConvertSetObjectsResponseToUnreal(const PFDataSetObjectsResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFDataSetObjectsResponse> ConvertedType = MakeShared<FPFDataSetObjectsResponse>(FPFDataSetObjectsResponse{
		.profileVersion = Datatype->profileVersion,
		.setResults = ConvertPlayfabArrayToUnreal<PFDataSetObjectInfo, FPFDataSetObjectInfo>(Datatype->setResults, Datatype->setResultsCount, ConvertSetObjectInfoToUnreal),
		.setResultsCount = Datatype->setResultsCount
	});

	return ConvertedType;
}

const PFDataSetObjectsResponse* ConvertSetObjectsResponseToPlayfab(TSharedPtr<const FPFDataSetObjectsResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFDataSetObjectsResponse* ConvertedType = new PFDataSetObjectsResponse{
		.profileVersion = Datatype->profileVersion,
		.setResults = ConvertUnrealArrayToPlayfab<PFDataSetObjectInfo, FPFDataSetObjectInfo>(Datatype->setResults, ConvertSetObjectInfoToPlayfab),
		.setResultsCount = (uint32_t)Datatype->setResults.Num()
	};

	return ConvertedType;
}
