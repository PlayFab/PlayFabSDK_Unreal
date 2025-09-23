// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once
#include "PFUnrealTypes.h"
#include "PFDataUnrealTypes.h"
#include "PFTypeConverters.h"
#include "PFCoreTypeConverters.h"

#pragma push_macro("IN")
#undef IN
	
TSharedPtr<const FPFDataAbortFileUploadsRequest> ConvertAbortFileUploadsRequestToUnreal(const PFDataAbortFileUploadsRequest* Datatype);
const PFDataAbortFileUploadsRequest* ConvertAbortFileUploadsRequestToPlayfab(TSharedPtr<const FPFDataAbortFileUploadsRequest> Datatype);
	
TSharedPtr<const FPFDataAbortFileUploadsResponse> ConvertAbortFileUploadsResponseToUnreal(const PFDataAbortFileUploadsResponse* Datatype);
const PFDataAbortFileUploadsResponse* ConvertAbortFileUploadsResponseToPlayfab(TSharedPtr<const FPFDataAbortFileUploadsResponse> Datatype);
	
TSharedPtr<const FPFDataDeleteFilesRequest> ConvertDeleteFilesRequestToUnreal(const PFDataDeleteFilesRequest* Datatype);
const PFDataDeleteFilesRequest* ConvertDeleteFilesRequestToPlayfab(TSharedPtr<const FPFDataDeleteFilesRequest> Datatype);
	
TSharedPtr<const FPFDataDeleteFilesResponse> ConvertDeleteFilesResponseToUnreal(const PFDataDeleteFilesResponse* Datatype);
const PFDataDeleteFilesResponse* ConvertDeleteFilesResponseToPlayfab(TSharedPtr<const FPFDataDeleteFilesResponse> Datatype);
	
TSharedPtr<const FPFDataFinalizeFileUploadsRequest> ConvertFinalizeFileUploadsRequestToUnreal(const PFDataFinalizeFileUploadsRequest* Datatype);
const PFDataFinalizeFileUploadsRequest* ConvertFinalizeFileUploadsRequestToPlayfab(TSharedPtr<const FPFDataFinalizeFileUploadsRequest> Datatype);
	
TSharedPtr<const FPFDataGetFileMetadata> ConvertGetFileMetadataToUnreal(const PFDataGetFileMetadata* Datatype);
const PFDataGetFileMetadata* ConvertGetFileMetadataToPlayfab(TSharedPtr<const FPFDataGetFileMetadata> Datatype);
	
TSharedPtr<const FPFDataFinalizeFileUploadsResponse> ConvertFinalizeFileUploadsResponseToUnreal(const PFDataFinalizeFileUploadsResponse* Datatype);
const PFDataFinalizeFileUploadsResponse* ConvertFinalizeFileUploadsResponseToPlayfab(TSharedPtr<const FPFDataFinalizeFileUploadsResponse> Datatype);
	
TSharedPtr<const FPFDataGetFilesRequest> ConvertGetFilesRequestToUnreal(const PFDataGetFilesRequest* Datatype);
const PFDataGetFilesRequest* ConvertGetFilesRequestToPlayfab(TSharedPtr<const FPFDataGetFilesRequest> Datatype);
	
TSharedPtr<const FPFDataGetFilesResponse> ConvertGetFilesResponseToUnreal(const PFDataGetFilesResponse* Datatype);
const PFDataGetFilesResponse* ConvertGetFilesResponseToPlayfab(TSharedPtr<const FPFDataGetFilesResponse> Datatype);
	
TSharedPtr<const FPFDataGetObjectsRequest> ConvertGetObjectsRequestToUnreal(const PFDataGetObjectsRequest* Datatype);
const PFDataGetObjectsRequest* ConvertGetObjectsRequestToPlayfab(TSharedPtr<const FPFDataGetObjectsRequest> Datatype);
	
TSharedPtr<const FPFDataObjectResult> ConvertObjectResultToUnreal(const PFDataObjectResult* Datatype);
const PFDataObjectResult* ConvertObjectResultToPlayfab(TSharedPtr<const FPFDataObjectResult> Datatype);
	
TSharedPtr<const FPFDataGetObjectsResponse> ConvertGetObjectsResponseToUnreal(const PFDataGetObjectsResponse* Datatype);
const PFDataGetObjectsResponse* ConvertGetObjectsResponseToPlayfab(TSharedPtr<const FPFDataGetObjectsResponse> Datatype);
	
TSharedPtr<const FPFDataInitiateFileUploadsRequest> ConvertInitiateFileUploadsRequestToUnreal(const PFDataInitiateFileUploadsRequest* Datatype);
const PFDataInitiateFileUploadsRequest* ConvertInitiateFileUploadsRequestToPlayfab(TSharedPtr<const FPFDataInitiateFileUploadsRequest> Datatype);
	
TSharedPtr<const FPFDataInitiateFileUploadMetadata> ConvertInitiateFileUploadMetadataToUnreal(const PFDataInitiateFileUploadMetadata* Datatype);
const PFDataInitiateFileUploadMetadata* ConvertInitiateFileUploadMetadataToPlayfab(TSharedPtr<const FPFDataInitiateFileUploadMetadata> Datatype);
	
TSharedPtr<const FPFDataInitiateFileUploadsResponse> ConvertInitiateFileUploadsResponseToUnreal(const PFDataInitiateFileUploadsResponse* Datatype);
const PFDataInitiateFileUploadsResponse* ConvertInitiateFileUploadsResponseToPlayfab(TSharedPtr<const FPFDataInitiateFileUploadsResponse> Datatype);
	
TSharedPtr<const FPFDataSetObject> ConvertSetObjectToUnreal(const PFDataSetObject* Datatype);
const PFDataSetObject* ConvertSetObjectToPlayfab(TSharedPtr<const FPFDataSetObject> Datatype);
	
TSharedPtr<const FPFDataSetObjectsRequest> ConvertSetObjectsRequestToUnreal(const PFDataSetObjectsRequest* Datatype);
const PFDataSetObjectsRequest* ConvertSetObjectsRequestToPlayfab(TSharedPtr<const FPFDataSetObjectsRequest> Datatype);
	
TSharedPtr<const FPFDataSetObjectInfo> ConvertSetObjectInfoToUnreal(const PFDataSetObjectInfo* Datatype);
const PFDataSetObjectInfo* ConvertSetObjectInfoToPlayfab(TSharedPtr<const FPFDataSetObjectInfo> Datatype);
	
TSharedPtr<const FPFDataSetObjectsResponse> ConvertSetObjectsResponseToUnreal(const PFDataSetObjectsResponse* Datatype);
const PFDataSetObjectsResponse* ConvertSetObjectsResponseToPlayfab(TSharedPtr<const FPFDataSetObjectsResponse> Datatype);


#pragma pop_macro("IN")