// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.


#include "Generated/PFEventsTypeConverters.h"


const FPFEventsDataConnectionErrorState ConvertDataConnectionErrorStateToUnreal(const PFEventsDataConnectionErrorState* enumVal)
{
	if (enumVal == nullptr) {
		return FPFEventsDataConnectionErrorState::OK;
	}

	switch(*enumVal)
	{
	case PFEventsDataConnectionErrorState::OK: return FPFEventsDataConnectionErrorState::OK;
	case PFEventsDataConnectionErrorState::Error: return FPFEventsDataConnectionErrorState::Error;
	default:
	return FPFEventsDataConnectionErrorState::OK;
	}
}

const PFEventsDataConnectionErrorState ConvertDataConnectionErrorStateToPlayfab(TSharedPtr<const FPFEventsDataConnectionErrorState> enumVal)
{
	if (!enumVal.IsValid()) {
		return PFEventsDataConnectionErrorState::OK;
	}

	switch(*enumVal)
	{
	case FPFEventsDataConnectionErrorState::OK: return PFEventsDataConnectionErrorState::OK;
	case FPFEventsDataConnectionErrorState::Error: return PFEventsDataConnectionErrorState::Error;
	default:
	return PFEventsDataConnectionErrorState::OK;
	}
}

const FPFEventsDataConnectionType ConvertDataConnectionTypeToUnreal(const PFEventsDataConnectionType* enumVal)
{
	if (enumVal == nullptr) {
		return FPFEventsDataConnectionType::AzureBlobStorage;
	}

	switch(*enumVal)
	{
	case PFEventsDataConnectionType::AzureBlobStorage: return FPFEventsDataConnectionType::AzureBlobStorage;
	case PFEventsDataConnectionType::AzureDataExplorer: return FPFEventsDataConnectionType::AzureDataExplorer;
	case PFEventsDataConnectionType::FabricKQL: return FPFEventsDataConnectionType::FabricKQL;
	default:
	return FPFEventsDataConnectionType::AzureBlobStorage;
	}
}

const PFEventsDataConnectionType ConvertDataConnectionTypeToPlayfab(TSharedPtr<const FPFEventsDataConnectionType> enumVal)
{
	if (!enumVal.IsValid()) {
		return PFEventsDataConnectionType::AzureBlobStorage;
	}

	switch(*enumVal)
	{
	case FPFEventsDataConnectionType::AzureBlobStorage: return PFEventsDataConnectionType::AzureBlobStorage;
	case FPFEventsDataConnectionType::AzureDataExplorer: return PFEventsDataConnectionType::AzureDataExplorer;
	case FPFEventsDataConnectionType::FabricKQL: return PFEventsDataConnectionType::FabricKQL;
	default:
	return PFEventsDataConnectionType::AzureBlobStorage;
	}
}

TSharedPtr<const FPFEventsDeleteDataConnectionRequest> ConvertDeleteDataConnectionRequestToUnreal(const PFEventsDeleteDataConnectionRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFEventsDeleteDataConnectionRequest> ConvertedType = MakeShared<FPFEventsDeleteDataConnectionRequest>(FPFEventsDeleteDataConnectionRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name)
	});

	return ConvertedType;
}

const PFEventsDeleteDataConnectionRequest* ConvertDeleteDataConnectionRequestToPlayfab(TSharedPtr<const FPFEventsDeleteDataConnectionRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFEventsDeleteDataConnectionRequest* ConvertedType = new PFEventsDeleteDataConnectionRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.name = ConvertFStringToCharPtr(Datatype->name)
	};

	return ConvertedType;
}

TSharedPtr<const FPFEventsDeleteDataConnectionResponse> ConvertDeleteDataConnectionResponseToUnreal(const PFEventsDeleteDataConnectionResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFEventsDeleteDataConnectionResponse> ConvertedType = MakeShared<FPFEventsDeleteDataConnectionResponse>(FPFEventsDeleteDataConnectionResponse{
		.wasDeleted = Datatype->wasDeleted
	});

	return ConvertedType;
}

const PFEventsDeleteDataConnectionResponse* ConvertDeleteDataConnectionResponseToPlayfab(TSharedPtr<const FPFEventsDeleteDataConnectionResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFEventsDeleteDataConnectionResponse* ConvertedType = new PFEventsDeleteDataConnectionResponse{
		.wasDeleted = Datatype->wasDeleted
	};

	return ConvertedType;
}

TSharedPtr<const FPFEventsGetDataConnectionRequest> ConvertGetDataConnectionRequestToUnreal(const PFEventsGetDataConnectionRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFEventsGetDataConnectionRequest> ConvertedType = MakeShared<FPFEventsGetDataConnectionRequest>(FPFEventsGetDataConnectionRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name)
	});

	return ConvertedType;
}

const PFEventsGetDataConnectionRequest* ConvertGetDataConnectionRequestToPlayfab(TSharedPtr<const FPFEventsGetDataConnectionRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFEventsGetDataConnectionRequest* ConvertedType = new PFEventsGetDataConnectionRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.name = ConvertFStringToCharPtr(Datatype->name)
	};

	return ConvertedType;
}

TSharedPtr<const FPFEventsDataConnectionAzureBlobSettings> ConvertDataConnectionAzureBlobSettingsToUnreal(const PFEventsDataConnectionAzureBlobSettings* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFEventsDataConnectionAzureBlobSettings> ConvertedType = MakeShared<FPFEventsDataConnectionAzureBlobSettings>(FPFEventsDataConnectionAzureBlobSettings{
		.accountName = Datatype->accountName == nullptr ? FString() : FString(Datatype->accountName),
		.containerName = Datatype->containerName == nullptr ? FString() : FString(Datatype->containerName),
		.tenantId = Datatype->tenantId == nullptr ? FString() : FString(Datatype->tenantId)
	});

	return ConvertedType;
}

const PFEventsDataConnectionAzureBlobSettings* ConvertDataConnectionAzureBlobSettingsToPlayfab(TSharedPtr<const FPFEventsDataConnectionAzureBlobSettings> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFEventsDataConnectionAzureBlobSettings* ConvertedType = new PFEventsDataConnectionAzureBlobSettings{
		.accountName = ConvertFStringToCharPtr(Datatype->accountName),
		.containerName = ConvertFStringToCharPtr(Datatype->containerName),
		.tenantId = ConvertFStringToCharPtr(Datatype->tenantId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFEventsDataConnectionAzureDataExplorerSettings> ConvertDataConnectionAzureDataExplorerSettingsToUnreal(const PFEventsDataConnectionAzureDataExplorerSettings* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFEventsDataConnectionAzureDataExplorerSettings> ConvertedType = MakeShared<FPFEventsDataConnectionAzureDataExplorerSettings>(FPFEventsDataConnectionAzureDataExplorerSettings{
		.clusterUri = Datatype->clusterUri == nullptr ? FString() : FString(Datatype->clusterUri),
		.database = Datatype->database == nullptr ? FString() : FString(Datatype->database),
		.table = Datatype->table == nullptr ? FString() : FString(Datatype->table)
	});

	return ConvertedType;
}

const PFEventsDataConnectionAzureDataExplorerSettings* ConvertDataConnectionAzureDataExplorerSettingsToPlayfab(TSharedPtr<const FPFEventsDataConnectionAzureDataExplorerSettings> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFEventsDataConnectionAzureDataExplorerSettings* ConvertedType = new PFEventsDataConnectionAzureDataExplorerSettings{
		.clusterUri = ConvertFStringToCharPtr(Datatype->clusterUri),
		.database = ConvertFStringToCharPtr(Datatype->database),
		.table = ConvertFStringToCharPtr(Datatype->table)
	};

	return ConvertedType;
}

TSharedPtr<const FPFEventsDataConnectionFabricKQLSettings> ConvertDataConnectionFabricKQLSettingsToUnreal(const PFEventsDataConnectionFabricKQLSettings* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFEventsDataConnectionFabricKQLSettings> ConvertedType = MakeShared<FPFEventsDataConnectionFabricKQLSettings>(FPFEventsDataConnectionFabricKQLSettings{
		.clusterUri = Datatype->clusterUri == nullptr ? FString() : FString(Datatype->clusterUri),
		.database = Datatype->database == nullptr ? FString() : FString(Datatype->database),
		.table = Datatype->table == nullptr ? FString() : FString(Datatype->table)
	});

	return ConvertedType;
}

const PFEventsDataConnectionFabricKQLSettings* ConvertDataConnectionFabricKQLSettingsToPlayfab(TSharedPtr<const FPFEventsDataConnectionFabricKQLSettings> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFEventsDataConnectionFabricKQLSettings* ConvertedType = new PFEventsDataConnectionFabricKQLSettings{
		.clusterUri = ConvertFStringToCharPtr(Datatype->clusterUri),
		.database = ConvertFStringToCharPtr(Datatype->database),
		.table = ConvertFStringToCharPtr(Datatype->table)
	};

	return ConvertedType;
}

TSharedPtr<const FPFEventsDataConnectionSettings> ConvertDataConnectionSettingsToUnreal(const PFEventsDataConnectionSettings* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFEventsDataConnectionSettings> ConvertedType = MakeShared<FPFEventsDataConnectionSettings>(FPFEventsDataConnectionSettings{
		.azureBlobSettings = ConvertDataConnectionAzureBlobSettingsToUnreal(Datatype->azureBlobSettings),
		.azureDataExplorerSettings = ConvertDataConnectionAzureDataExplorerSettingsToUnreal(Datatype->azureDataExplorerSettings),
		.azureFabricKQLSettings = ConvertDataConnectionFabricKQLSettingsToUnreal(Datatype->azureFabricKQLSettings)
	});

	return ConvertedType;
}

const PFEventsDataConnectionSettings* ConvertDataConnectionSettingsToPlayfab(TSharedPtr<const FPFEventsDataConnectionSettings> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFEventsDataConnectionSettings* ConvertedType = new PFEventsDataConnectionSettings{
		.azureBlobSettings = ConvertDataConnectionAzureBlobSettingsToPlayfab(Datatype->azureBlobSettings),
		.azureDataExplorerSettings = ConvertDataConnectionAzureDataExplorerSettingsToPlayfab(Datatype->azureDataExplorerSettings),
		.azureFabricKQLSettings = ConvertDataConnectionFabricKQLSettingsToPlayfab(Datatype->azureFabricKQLSettings)
	};

	return ConvertedType;
}

TSharedPtr<const FPFEventsDataConnectionStatusDetails> ConvertDataConnectionStatusDetailsToUnreal(const PFEventsDataConnectionStatusDetails* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFEventsDataConnectionStatusDetails> ConvertedType = MakeShared<FPFEventsDataConnectionStatusDetails>(FPFEventsDataConnectionStatusDetails{
		.error = Datatype->error == nullptr ? FString() : FString(Datatype->error),
		.errorMessage = Datatype->errorMessage == nullptr ? FString() : FString(Datatype->errorMessage),
		.mostRecentErrorTime = ConvertTimeToUnreal(Datatype->mostRecentErrorTime),
		.state = MakeShared<FPFEventsDataConnectionErrorState>(ConvertDataConnectionErrorStateToUnreal(Datatype->state))
	});

	return ConvertedType;
}

const PFEventsDataConnectionStatusDetails* ConvertDataConnectionStatusDetailsToPlayfab(TSharedPtr<const FPFEventsDataConnectionStatusDetails> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFEventsDataConnectionStatusDetails* ConvertedType = new PFEventsDataConnectionStatusDetails{
		.error = ConvertFStringToCharPtr(Datatype->error),
		.errorMessage = ConvertFStringToCharPtr(Datatype->errorMessage),
		.mostRecentErrorTime = ConvertFDateTimeToPlayfab(Datatype->mostRecentErrorTime),
		.state = new PFEventsDataConnectionErrorState(ConvertDataConnectionErrorStateToPlayfab(Datatype->state))
	};

	return ConvertedType;
}

TSharedPtr<const FPFEventsDataConnectionDetails> ConvertDataConnectionDetailsToUnreal(const PFEventsDataConnectionDetails* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFEventsDataConnectionDetails> ConvertedType = MakeShared<FPFEventsDataConnectionDetails>(FPFEventsDataConnectionDetails{
		.connectionSettings = ConvertDataConnectionSettingsToUnreal(Datatype->connectionSettings),
		.isActive = Datatype->isActive,
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name),
		.status = ConvertDataConnectionStatusDetailsToUnreal(Datatype->status),
		.type = ConvertDataConnectionTypeToUnreal(&Datatype->type)
	});

	return ConvertedType;
}

const PFEventsDataConnectionDetails* ConvertDataConnectionDetailsToPlayfab(TSharedPtr<const FPFEventsDataConnectionDetails> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFEventsDataConnectionDetails* ConvertedType = new PFEventsDataConnectionDetails{
		.connectionSettings = ConvertDataConnectionSettingsToPlayfab(Datatype->connectionSettings),
		.isActive = Datatype->isActive,
		.name = ConvertFStringToCharPtr(Datatype->name),
		.status = ConvertDataConnectionStatusDetailsToPlayfab(Datatype->status),
		.type = ConvertDataConnectionTypeToPlayfab(MakeShared<FPFEventsDataConnectionType>(Datatype->type))
	};

	return ConvertedType;
}

TSharedPtr<const FPFEventsGetDataConnectionResponse> ConvertGetDataConnectionResponseToUnreal(const PFEventsGetDataConnectionResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFEventsGetDataConnectionResponse> ConvertedType = MakeShared<FPFEventsGetDataConnectionResponse>(FPFEventsGetDataConnectionResponse{
		.dataConnection = ConvertDataConnectionDetailsToUnreal(Datatype->dataConnection)
	});

	return ConvertedType;
}

const PFEventsGetDataConnectionResponse* ConvertGetDataConnectionResponseToPlayfab(TSharedPtr<const FPFEventsGetDataConnectionResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFEventsGetDataConnectionResponse* ConvertedType = new PFEventsGetDataConnectionResponse{
		.dataConnection = ConvertDataConnectionDetailsToPlayfab(Datatype->dataConnection)
	};

	return ConvertedType;
}

TSharedPtr<const FPFEventsListDataConnectionsRequest> ConvertListDataConnectionsRequestToUnreal(const PFEventsListDataConnectionsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFEventsListDataConnectionsRequest> ConvertedType = MakeShared<FPFEventsListDataConnectionsRequest>(FPFEventsListDataConnectionsRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount
	});

	return ConvertedType;
}

const PFEventsListDataConnectionsRequest* ConvertListDataConnectionsRequestToPlayfab(TSharedPtr<const FPFEventsListDataConnectionsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFEventsListDataConnectionsRequest* ConvertedType = new PFEventsListDataConnectionsRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFEventsListDataConnectionsResponse> ConvertListDataConnectionsResponseToUnreal(const PFEventsListDataConnectionsResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFEventsListDataConnectionsResponse> ConvertedType = MakeShared<FPFEventsListDataConnectionsResponse>(FPFEventsListDataConnectionsResponse{
		.dataConnections = ConvertPlayfabArrayToUnreal<PFEventsDataConnectionDetails, FPFEventsDataConnectionDetails>(Datatype->dataConnections, Datatype->dataConnectionsCount, ConvertDataConnectionDetailsToUnreal),
		.dataConnectionsCount = Datatype->dataConnectionsCount
	});

	return ConvertedType;
}

const PFEventsListDataConnectionsResponse* ConvertListDataConnectionsResponseToPlayfab(TSharedPtr<const FPFEventsListDataConnectionsResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFEventsListDataConnectionsResponse* ConvertedType = new PFEventsListDataConnectionsResponse{
		.dataConnections = ConvertUnrealArrayToPlayfab<PFEventsDataConnectionDetails, FPFEventsDataConnectionDetails>(Datatype->dataConnections, ConvertDataConnectionDetailsToPlayfab),
		.dataConnectionsCount = (uint32_t)Datatype->dataConnections.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFEventsSetDataConnectionRequest> ConvertSetDataConnectionRequestToUnreal(const PFEventsSetDataConnectionRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFEventsSetDataConnectionRequest> ConvertedType = MakeShared<FPFEventsSetDataConnectionRequest>(FPFEventsSetDataConnectionRequest{
		.connectionSettings = ConvertDataConnectionSettingsToUnreal(Datatype->connectionSettings),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.isActive = Datatype->isActive,
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name),
		.type = ConvertDataConnectionTypeToUnreal(&Datatype->type)
	});

	return ConvertedType;
}

const PFEventsSetDataConnectionRequest* ConvertSetDataConnectionRequestToPlayfab(TSharedPtr<const FPFEventsSetDataConnectionRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFEventsSetDataConnectionRequest* ConvertedType = new PFEventsSetDataConnectionRequest{
		.connectionSettings = ConvertDataConnectionSettingsToPlayfab(Datatype->connectionSettings),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.isActive = Datatype->isActive,
		.name = ConvertFStringToCharPtr(Datatype->name),
		.type = ConvertDataConnectionTypeToPlayfab(MakeShared<FPFEventsDataConnectionType>(Datatype->type))
	};

	return ConvertedType;
}

TSharedPtr<const FPFEventsSetDataConnectionResponse> ConvertSetDataConnectionResponseToUnreal(const PFEventsSetDataConnectionResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFEventsSetDataConnectionResponse> ConvertedType = MakeShared<FPFEventsSetDataConnectionResponse>(FPFEventsSetDataConnectionResponse{
		.dataConnection = ConvertDataConnectionDetailsToUnreal(Datatype->dataConnection)
	});

	return ConvertedType;
}

const PFEventsSetDataConnectionResponse* ConvertSetDataConnectionResponseToPlayfab(TSharedPtr<const FPFEventsSetDataConnectionResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFEventsSetDataConnectionResponse* ConvertedType = new PFEventsSetDataConnectionResponse{
		.dataConnection = ConvertDataConnectionDetailsToPlayfab(Datatype->dataConnection)
	};

	return ConvertedType;
}

TSharedPtr<const FPFEventsSetDataConnectionActiveRequest> ConvertSetDataConnectionActiveRequestToUnreal(const PFEventsSetDataConnectionActiveRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFEventsSetDataConnectionActiveRequest> ConvertedType = MakeShared<FPFEventsSetDataConnectionActiveRequest>(FPFEventsSetDataConnectionActiveRequest{
		.active = Datatype->active,
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name)
	});

	return ConvertedType;
}

const PFEventsSetDataConnectionActiveRequest* ConvertSetDataConnectionActiveRequestToPlayfab(TSharedPtr<const FPFEventsSetDataConnectionActiveRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFEventsSetDataConnectionActiveRequest* ConvertedType = new PFEventsSetDataConnectionActiveRequest{
		.active = Datatype->active,
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.name = ConvertFStringToCharPtr(Datatype->name)
	};

	return ConvertedType;
}

TSharedPtr<const FPFEventsSetDataConnectionActiveResponse> ConvertSetDataConnectionActiveResponseToUnreal(const PFEventsSetDataConnectionActiveResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFEventsSetDataConnectionActiveResponse> ConvertedType = MakeShared<FPFEventsSetDataConnectionActiveResponse>(FPFEventsSetDataConnectionActiveResponse{
		.dataConnection = ConvertDataConnectionDetailsToUnreal(Datatype->dataConnection),
		.wasUpdated = Datatype->wasUpdated
	});

	return ConvertedType;
}

const PFEventsSetDataConnectionActiveResponse* ConvertSetDataConnectionActiveResponseToPlayfab(TSharedPtr<const FPFEventsSetDataConnectionActiveResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFEventsSetDataConnectionActiveResponse* ConvertedType = new PFEventsSetDataConnectionActiveResponse{
		.dataConnection = ConvertDataConnectionDetailsToPlayfab(Datatype->dataConnection),
		.wasUpdated = Datatype->wasUpdated
	};

	return ConvertedType;
}

TSharedPtr<const FPFEventsEventContents> ConvertEventContentsToUnreal(const PFEventsEventContents* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFEventsEventContents> ConvertedType = MakeShared<FPFEventsEventContents>(FPFEventsEventContents{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.eventNamespace = Datatype->eventNamespace == nullptr ? FString() : FString(Datatype->eventNamespace),
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name),
		.originalId = Datatype->originalId == nullptr ? FString() : FString(Datatype->originalId),
		.originalTimestamp = ConvertTimeToUnreal(Datatype->originalTimestamp),
		.payload = FPFJsonObject{ .stringValue = FString(Datatype->payload.stringValue) },
		.payloadJSON = Datatype->payloadJSON == nullptr ? FString() : FString(Datatype->payloadJSON)
	});

	return ConvertedType;
}

const PFEventsEventContents* ConvertEventContentsToPlayfab(TSharedPtr<const FPFEventsEventContents> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFEventsEventContents* ConvertedType = new PFEventsEventContents{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.eventNamespace = ConvertFStringToCharPtr(Datatype->eventNamespace),
		.name = ConvertFStringToCharPtr(Datatype->name),
		.originalId = ConvertFStringToCharPtr(Datatype->originalId),
		.originalTimestamp = ConvertFDateTimeToPlayfab(Datatype->originalTimestamp),
		.payload = PFJsonObject{ .stringValue = ConvertFStringToCharPtr(Datatype->payload.stringValue) },
		.payloadJSON = ConvertFStringToCharPtr(Datatype->payloadJSON)
	};

	return ConvertedType;
}

TSharedPtr<const FPFEventsWriteEventsRequest> ConvertWriteEventsRequestToUnreal(const PFEventsWriteEventsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFEventsWriteEventsRequest> ConvertedType = MakeShared<FPFEventsWriteEventsRequest>(FPFEventsWriteEventsRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.events = ConvertPlayfabArrayToUnreal<PFEventsEventContents, FPFEventsEventContents>(Datatype->events, Datatype->eventsCount, ConvertEventContentsToUnreal),
		.eventsCount = Datatype->eventsCount
	});

	return ConvertedType;
}

const PFEventsWriteEventsRequest* ConvertWriteEventsRequestToPlayfab(TSharedPtr<const FPFEventsWriteEventsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFEventsWriteEventsRequest* ConvertedType = new PFEventsWriteEventsRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.events = ConvertUnrealArrayToPlayfab<PFEventsEventContents, FPFEventsEventContents>(Datatype->events, ConvertEventContentsToPlayfab),
		.eventsCount = (uint32_t)Datatype->events.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFEventsWriteEventsResponse> ConvertWriteEventsResponseToUnreal(const PFEventsWriteEventsResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFEventsWriteEventsResponse> ConvertedType = MakeShared<FPFEventsWriteEventsResponse>(FPFEventsWriteEventsResponse{
		.assignedEventIds = ConvertCharArrayToUnreal(Datatype->assignedEventIds, Datatype->assignedEventIdsCount),
		.assignedEventIdsCount = Datatype->assignedEventIdsCount
	});

	return ConvertedType;
}

const PFEventsWriteEventsResponse* ConvertWriteEventsResponseToPlayfab(TSharedPtr<const FPFEventsWriteEventsResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFEventsWriteEventsResponse* ConvertedType = new PFEventsWriteEventsResponse{
		.assignedEventIds = ConvertFStringArrayToPlayfab(Datatype->assignedEventIds),
		.assignedEventIdsCount = (uint32_t)Datatype->assignedEventIds.Num()
	};

	return ConvertedType;
}

