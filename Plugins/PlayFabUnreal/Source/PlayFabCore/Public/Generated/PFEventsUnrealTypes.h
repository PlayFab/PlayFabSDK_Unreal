// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once
#include "Generated/PFCoreUnrealTypes.h"
#include "PFEntity.h"
#include "PFServiceConfig.h"


/// <summary>
/// FPFEventsDataConnectionErrorState enum.
/// </summary>
enum class FPFEventsDataConnectionErrorState : uint32_t
{
	OK,
	Error
};

/// <summary>
/// FPFEventsDataConnectionType enum.
/// </summary>
enum class FPFEventsDataConnectionType : uint32_t
{
	AzureBlobStorage,
	AzureDataExplorer,
	FabricKQL
};



struct FPFEventsDeleteDataConnectionRequest
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
	/// The name of the data connection to delete.
	/// </summary>
	const FString name;

};



struct FPFEventsDeleteDataConnectionResponse
{
	/// <summary>
	/// Indicates whether or not the connection was deleted as part of the request.
	/// </summary>
	bool wasDeleted;

};



struct FPFEventsGetDataConnectionRequest
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
	/// The name of the data connection to retrieve.
	/// </summary>
	const FString name;

};



struct FPFEventsDataConnectionAzureBlobSettings
{
	/// <summary>
	/// (Optional) Name of the storage account.
	/// </summary>
	_Maybenull_ const FString accountName;

	/// <summary>
	/// (Optional) Name of the container.
	/// </summary>
	_Maybenull_ const FString containerName;

	/// <summary>
	/// (Optional) Azure Entra Tenant Id.
	/// </summary>
	_Maybenull_ const FString tenantId;

};



struct FPFEventsDataConnectionAzureDataExplorerSettings
{
	/// <summary>
	/// (Optional) The URI of the ADX cluster.
	/// </summary>
	_Maybenull_ const FString clusterUri;

	/// <summary>
	/// (Optional) The database to write to.
	/// </summary>
	_Maybenull_ const FString database;

	/// <summary>
	/// (Optional) The table to write to.
	/// </summary>
	_Maybenull_ const FString table;

};



struct FPFEventsDataConnectionFabricKQLSettings
{
	/// <summary>
	/// (Optional) The URI of the Fabric cluster.
	/// </summary>
	_Maybenull_ const FString clusterUri;

	/// <summary>
	/// (Optional) The database to write to.
	/// </summary>
	_Maybenull_ const FString database;

	/// <summary>
	/// (Optional) The table to write to.
	/// </summary>
	_Maybenull_ const FString table;

};



struct FPFEventsDataConnectionSettings
{
	/// <summary>
	/// (Optional) Settings if the type of connection is AzureBlobStorage.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEventsDataConnectionAzureBlobSettings> azureBlobSettings;

	/// <summary>
	/// (Optional) Settings if the type of connection is AzureDataExplorer.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEventsDataConnectionAzureDataExplorerSettings> azureDataExplorerSettings;

	/// <summary>
	/// (Optional) Settings if the type of connection is FabricKQL.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEventsDataConnectionFabricKQLSettings> azureFabricKQLSettings;

};



struct FPFEventsDataConnectionStatusDetails
{
	/// <summary>
	/// (Optional) The name of the error affecting the data connection, if any.
	/// </summary>
	_Maybenull_ const FString error;

	/// <summary>
	/// (Optional) A description of the error affecting the data connection, if any. This may be empty for
	/// some errors.
	/// </summary>
	_Maybenull_ const FString errorMessage;

	/// <summary>
	/// (Optional) The most recent time of the error affecting the data connection, if any.
	/// </summary>
	_Maybenull_ TSharedPtr<const FDateTime> mostRecentErrorTime;

	/// <summary>
	/// (Optional) Indicates if the connection is in a normal state or error state.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEventsDataConnectionErrorState> state;

};



struct FPFEventsDataConnectionDetails
{
	/// <summary>
	/// Settings of the data connection.
	/// </summary>
	TSharedPtr<const FPFEventsDataConnectionSettings> connectionSettings;

	/// <summary>
	/// Whether or not the connection is currently active.
	/// </summary>
	bool isActive;

	/// <summary>
	/// The name of the data connection.
	/// </summary>
	const FString name;

	/// <summary>
	/// (Optional) Current status of the data connection, if any.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEventsDataConnectionStatusDetails> status;

	/// <summary>
	/// The type of data connection.
	/// </summary>
	FPFEventsDataConnectionType type;

};



struct FPFEventsGetDataConnectionResponse
{
	/// <summary>
	/// (Optional) The details of the queried Data Connection.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEventsDataConnectionDetails> dataConnection;

};



struct FPFEventsListDataConnectionsRequest
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

};



struct FPFEventsListDataConnectionsResponse
{
	/// <summary>
	/// (Optional) The list of existing Data Connections.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFEventsDataConnectionDetails>> dataConnections;

	/// <summary>
	/// Count of dataConnections
	/// </summary>
	uint32 dataConnectionsCount;

};



struct FPFEventsSetDataConnectionRequest
{
	/// <summary>
	/// Settings of the data connection.
	/// </summary>
	TSharedPtr<const FPFEventsDataConnectionSettings> connectionSettings;

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
	/// Whether or not the connection is currently active.
	/// </summary>
	bool isActive;

	/// <summary>
	/// The name of the data connection to update or create.
	/// </summary>
	const FString name;

	/// <summary>
	/// The type of data connection.
	/// </summary>
	FPFEventsDataConnectionType type;

};



struct FPFEventsSetDataConnectionResponse
{
	/// <summary>
	/// (Optional) The details of the Data Connection to be created or updated.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEventsDataConnectionDetails> dataConnection;

};



struct FPFEventsSetDataConnectionActiveRequest
{
	/// <summary>
	/// Whether to set the data connection to active (true) or deactivated (false).
	/// </summary>
	bool active;

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
	/// The name of the data connection to update.
	/// </summary>
	const FString name;

};



struct FPFEventsSetDataConnectionActiveResponse
{
	/// <summary>
	/// (Optional) The most current details about the data connection that was to be updated.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEventsDataConnectionDetails> dataConnection;

	/// <summary>
	/// Indicates whether or not the data connection was updated. If false, the data connection was already
	/// in the desired state.
	/// </summary>
	bool wasUpdated;

};



struct FPFEventsEventContents
{
	/// <summary>
	/// (Optional) The optional custom tags associated with the event (e.g. build number, external trace
	/// identifiers, etc.). Before an event is written, this collection and the base request custom tags
	/// will be merged, but not overriden. This enables the caller to specify static tags and per event tags.
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// (Optional) Entity associated with the event. If null, the event will apply to the calling entity.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// The namespace in which the event is defined. Allowed namespaces can vary by API.
	/// </summary>
	const FString eventNamespace;

	/// <summary>
	/// The name of this event.
	/// </summary>
	const FString name;

	/// <summary>
	/// (Optional) The original unique identifier associated with this event before it was posted to PlayFab.
	/// The value might differ from the EventId value, which is assigned when the event is received by the
	/// server.
	/// </summary>
	_Maybenull_ const FString originalId;

	/// <summary>
	/// (Optional) The time (in UTC) associated with this event when it occurred. If specified, this value
	/// is stored in the OriginalTimestamp property of the PlayStream event.
	/// </summary>
	_Maybenull_ TSharedPtr<const FDateTime> originalTimestamp;

	/// <summary>
	/// (Optional) Arbitrary data associated with the event. Only one of Payload or PayloadJSON is allowed.
	/// </summary>
	FPFJsonObject payload;

	/// <summary>
	/// (Optional) Arbitrary data associated with the event, represented as a JSON serialized string. Only
	/// one of Payload or PayloadJSON is allowed.
	/// </summary>
	_Maybenull_ const FString payloadJSON;

};



struct FPFEventsWriteEventsRequest
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
	/// The collection of events to write. Up to 200 events can be written per request.
	/// </summary>
	TArray<TSharedPtr<const FPFEventsEventContents>> events;

	/// <summary>
	/// Count of events
	/// </summary>
	uint32 eventsCount;

};



struct FPFEventsWriteEventsResponse
{
	/// <summary>
	/// (Optional) The unique identifiers assigned by the server to the events, in the same order as the
	/// events in the request. Only returned if FlushToPlayStream option is true.
	/// </summary>
	_Maybenull_ const TArray<FString> assignedEventIds;

	/// <summary>
	/// Count of assignedEventIds
	/// </summary>
	uint32 assignedEventIdsCount;

};

// Delegates Declarations

#if 0
DECLARE_DELEGATE_TwoParams(FOnDeleteDataConnectionDelegate, const FPFEventsDeleteDataConnectionResponse*, bool);
#endif

#if 0
DECLARE_DELEGATE_TwoParams(FOnGetDataConnectionDelegate, const FPFEventsGetDataConnectionResponse*, bool);
#endif

#if 0
DECLARE_DELEGATE_TwoParams(FOnListDataConnectionsDelegate, const FPFEventsListDataConnectionsResponse*, bool);
#endif

#if 0
DECLARE_DELEGATE_TwoParams(FOnSetDataConnectionDelegate, const FPFEventsSetDataConnectionResponse*, bool);
#endif

#if 0
DECLARE_DELEGATE_TwoParams(FOnSetDataConnectionActiveDelegate, const FPFEventsSetDataConnectionActiveResponse*, bool);
#endif

DECLARE_DELEGATE_TwoParams(FOnWriteEventsDelegate, const FPFEventsWriteEventsResponse*, bool);

DECLARE_DELEGATE_TwoParams(FOnWriteTelemetryEventsDelegate, const FPFEventsWriteEventsResponse*, bool);
