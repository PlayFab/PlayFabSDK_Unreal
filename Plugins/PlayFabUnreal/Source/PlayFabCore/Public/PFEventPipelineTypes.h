#pragma once

typedef TSharedPtr<struct PFEventPipeline> FPFEventPipelineHandle;

/// <summary>
/// Event to be uploaded to PlayFab.
/// </summary>
struct FPFEvent
{
	/// <summary>
	/// Entity associated with the event. If null, the event will apply to the calling entity.
	/// </summary>
	_Maybenull_ TSharedPtr<FPFEntityKey const> entity;

	/// <summary>
	/// The namespace in which the event is defined.
	/// </summary>
	_Null_terminated_ FString eventNamespace;

	/// <summary>
	/// The name of the event.
	/// </summary>
	_Null_terminated_ FString name;

	/// <summary>
	/// Client assigned identifier associated with event. Not required but may be useful for tracking or tracing.
	/// If a clientId is not provided, the SDK will automatically assign one.
	/// </summary>
	_Maybenull_ _Null_terminated_ FString clientId;

	/// <summary>
	/// Arbitrary JSON data associated with the event.
	/// </summary>
	_Null_terminated_ FString payloadJson;
};

/// <summary>
/// Event that has been uploaded to PlayFab. Associates the service assigned ID with the clientId provided when the event was emitted.
/// </summary>
struct FPFUploadedEvent
{
	/// <summary>
	/// Id assigned by the client prior to the event being uploaded.
	/// </summary>
	_Null_terminated_ FString clientId;

	/// <summary>
	/// Unique Id assigned by the PlayFab server for the event.
	/// </summary>
	_Null_terminated_ FString serviceId;
};

/// <summary>
/// Configuration struct that defines the properties required for using Telemetry Key.
/// </summary>
struct FPFEventPipelineTelemetryKeyConfig
{
	/// <summary>
	/// The Key created to send PlayFab event requests without an associated entity.
	/// </summary>
	_Null_terminated_ FString telemetryKey;

	/// <summary>
	/// Service Config to be used with telemetry key.
	/// </summary>
	FPFServiceConfigHandle serviceConfigHandle;
};

/// <summary>
/// Defines the Event Pipeline configuration.
/// </summary>
struct FPFEventPipelineConfig
{
	/// <summary>
	/// The maximum number events that will be batched before writing them to PlayFab. If sent null, default value will be used (5 for Telemetry / 5 for PlayStream).
	/// </summary>
	_Maybenull_ TSharedPtr<uint32> maxEventsPerBatch;

	/// <summary>
	/// The maximum time the pipeline will wait before sending out an incomplete batch. If sent null, default value will be used (3 for Telemetry / 3 for PlayStream).
	/// </summary>
	_Maybenull_ TSharedPtr<uint32> maxWaitTimeInSeconds;

	/// <summary>
	/// How long the pipeline will wait to read from the event buffer again after emptying it. If sent null, default value will be used (10 for Telemetry / 10 for PlayStream).
	/// </summary>
	_Maybenull_ TSharedPtr<uint32> pollDelayInMs;

	/// <summary>
	/// The event pipeline will send events using GZIP compression with the level specified. If sent null, no compression will be made.
	/// </summary>
	_Maybenull_ TSharedPtr<HCCompressionLevel> compressionLevel;

	/// <summary>
	/// The event pipeline will retry sending events that failed due to lost connection. If sent null, default behavior will be to retry (true) (not available for PlayStream).
	/// </summary>
	_Maybenull_ TSharedPtr<bool> retryOnDisconnect;

	/// <summary>
	/// The limit of the amount of events in the pipeline's buffer. If sent null, default value will be used (1024 for either type).
	/// </summary>
	_Maybenull_ TSharedPtr<uint32> bufferSize;
};

/// <summary>
/// Delegate for handling the event when a batch of events is successfully uploaded.
/// </summary>
/// <param name="context">Pointer to user-defined data passed to the event handler.</param>
/// <param name="uploadedEvents">Array of pointers to the uploaded events.</param>
/// <param name="eventCount">Number of events in the uploadedEvents array.</param>
DECLARE_DELEGATE_ThreeParams(FPFEventPipelineBatchUploadSucceededEventDelegate, TSharedPtr<void>, TArray<TSharedPtr<const FPFUploadedEvent>>, SIZE_T);

/// <summary>
/// Delegate for handling the event when a batch of events fails to upload.
/// </summary>
/// <param name="context">Pointer to user-defined data passed to the event handler.</param>
/// <param name="result">HRESULT indicating the reason for the failure.</param>
/// <param name="errorMessage">String containing the error message.</param>
/// <param name="failedEvents">Array of pointers to the events that failed to upload.</param>
/// <param name="eventCount">Number of events in the failedEvents array.</param>
DECLARE_DELEGATE_FiveParams(FPFEventPipelineBatchUploadFailedEventDelegate, TSharedPtr<void>, HRESULT, FString, TArray<TSharedPtr<const FPFEvent>>, SIZE_T);
