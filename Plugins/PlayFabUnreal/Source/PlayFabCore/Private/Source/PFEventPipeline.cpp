#include "PFEventPipeline.h"

static FPFEventPipelineBatchUploadSucceededEventDelegate EventPipelineBatchUploadedEventDelegate;

static FPFEventPipelineBatchUploadFailedEventDelegate EventPipelineBatchFailedEventDelegate;

TSharedPtr<const FPFUploadedEvent> ConvertPFUploadedEventToUnreal(const PFUploadedEvent* Datatype)
{
	TSharedPtr<const FPFUploadedEvent> ConvertedType = MakeShared<FPFUploadedEvent>(FPFUploadedEvent{
		.clientId = FString(Datatype->clientId),
		.serviceId = FString(Datatype->serviceId)
	});

	return ConvertedType;
}

TSharedPtr<const FPFEvent> ConvertPFEventToUnreal(const PFEvent* Datatype)
{

	PFEntityKey const* entityKey = Datatype->entity;

	const FPFEntityKey fpfEntityKey = {
		.id = FString(entityKey->id),
		.type = FString(entityKey->type)
	};

	TSharedPtr<const FPFEvent> ConvertedType = MakeShared<FPFEvent>(FPFEvent{
		.entity = MakeShared<FPFEntityKey>(fpfEntityKey),
		.eventNamespace = FString(Datatype->eventNamespace),
		.name = FString(Datatype->name),
		.clientId = FString(Datatype->clientId),
		.payloadJson = FString(Datatype->payloadJson)
	});

	return ConvertedType;
}

static void CALLBACK OnBatchUploadedHandler(void* context, PFUploadedEvent const* const* events, size_t eventsCount)
{
	TSharedPtr<void> contextRef = MakeShareable(context, [](void*) {});
	TArray<TSharedPtr<const FPFUploadedEvent>> eventsRef = ConvertPlayfabArrayToUnreal(events, eventsCount, ConvertPFUploadedEventToUnreal);

	EventPipelineBatchUploadedEventDelegate.ExecuteIfBound(contextRef, eventsRef, eventsCount);
}

static void CALLBACK OnBatchUploadFailedHandler(void* context, HRESULT hr, const char* errorMessage, PFEvent const* const* events, size_t eventsCount)
{
	TSharedPtr<void> contextRef = MakeShareable(context, [](void*) {});
	FString errorMessageFStr = FString(errorMessage);
	TArray<TSharedPtr<const FPFEvent>> eventsRef = ConvertPlayfabArrayToUnreal(events, eventsCount, ConvertPFEventToUnreal);

	EventPipelineBatchFailedEventDelegate.ExecuteIfBound(contextRef, hr, errorMessage, eventsRef, eventsCount);
}

bool PLAYFABCORE_API FPFEventPipelineCreateTelemetryPipelineHandleWithKey(
	_In_ TSharedPtr<FPFEventPipelineTelemetryKeyConfig> eventPipelineTelemetryKeyConfig,
	_In_opt_ FPFEventPipelineBatchUploadSucceededEventDelegate eventPipelineBatchUploadedEventDelegate,
	_In_opt_ FPFEventPipelineBatchUploadFailedEventDelegate eventPipelineBatchFailedEventDelegate,
	_In_opt_ TSharedPtr<void> handlerContext,
	_Out_ FPFEventPipelineHandle& eventPipelineHandle
) noexcept
{
	RETURN_FALSE_IF_NULL(eventPipelineTelemetryKeyConfig);

	const FPFEventPipelineTelemetryKeyConfig* fpfTelemetryKeyConfig = eventPipelineTelemetryKeyConfig.Get();

	auto telemetryKeyConverted = StringCast<ANSICHAR>(*fpfTelemetryKeyConfig->telemetryKey);

	PFEventPipelineTelemetryKeyConfig pfTelemetryKeyConfig = {
		.telemetryKey = telemetryKeyConverted.Get(),
		.serviceConfigHandle = fpfTelemetryKeyConfig->serviceConfigHandle.Get(),
	};

	PFEventPipelineHandle handle;
	HRESULT hr = PFEventPipelineCreateTelemetryPipelineHandleWithKey(
		&pfTelemetryKeyConfig,
		FXAsyncTaskQueue::GetGenericQueue(),
		&OnBatchUploadedHandler,
		&OnBatchUploadFailedHandler,
		handlerContext.Get(),
		&handle
	);

	if (FAILED(hr))
	{
		return false;
	}

	// We should assign/override delegates/handle only when Pipeline creation is successful
	*reinterpret_cast<PFEventPipelineHandle*>(&eventPipelineHandle) = handle;
	EventPipelineBatchUploadedEventDelegate = eventPipelineBatchUploadedEventDelegate;
	EventPipelineBatchFailedEventDelegate = eventPipelineBatchFailedEventDelegate;

	return true;
}

bool PLAYFABCORE_API FPFEventPipelineCreateTelemetryPipelineHandleWithEntity(
	_In_ FPFEntityHandle entityHandle,
	_In_opt_ FPFEventPipelineBatchUploadSucceededEventDelegate eventPipelineBatchUploadedEventDelegate,
	_In_opt_ FPFEventPipelineBatchUploadFailedEventDelegate eventPipelineBatchFailedEventDelegate,
	_In_opt_ TSharedPtr<void> handlerContext,
	_Out_ FPFEventPipelineHandle& eventPipelineHandle
) noexcept
{
	RETURN_FALSE_IF_NULL(entityHandle);

	PFEventPipelineHandle handle;
	HRESULT hr = PFEventPipelineCreateTelemetryPipelineHandleWithEntity(
		entityHandle.Get(),
		FXAsyncTaskQueue::GetGenericQueue(),
		&OnBatchUploadedHandler,
		&OnBatchUploadFailedHandler,
		handlerContext.Get(),
		&handle
	);

	if (FAILED(hr))
	{
		return false;
	}

	// We should assign/override delegates/handle only when Pipeline creation is successful
	*reinterpret_cast<PFEventPipelineHandle*>(&eventPipelineHandle) = handle;
	EventPipelineBatchUploadedEventDelegate = eventPipelineBatchUploadedEventDelegate;
	EventPipelineBatchFailedEventDelegate = eventPipelineBatchFailedEventDelegate;

	return true;
}

bool PLAYFABCORE_API FPFEventPipelineCreatePlayStreamPipelineHandle(
	_In_ FPFEntityHandle entityHandle,
	_In_opt_ FPFEventPipelineBatchUploadSucceededEventDelegate eventPipelineBatchUploadedEventDelegate,
	_In_opt_ FPFEventPipelineBatchUploadFailedEventDelegate eventPipelineBatchFailedEventDelegate,
	_In_opt_ TSharedPtr<void> handlerContext,
	_Out_ FPFEventPipelineHandle& eventPipelineHandle
) noexcept
{
	RETURN_FALSE_IF_NULL(entityHandle);

	PFEventPipelineHandle handle;
	HRESULT hr = PFEventPipelineCreatePlayStreamPipelineHandle(
		entityHandle.Get(),
		FXAsyncTaskQueue::GetGenericQueue(),
		&OnBatchUploadedHandler,
		&OnBatchUploadFailedHandler,
		handlerContext.Get(),
		&handle
	);

	if (FAILED(hr))
	{
		return false;
	}

	// We should assign/override delegates/handle only when Pipeline creation is successful
	*reinterpret_cast<PFEventPipelineHandle*>(&eventPipelineHandle) = handle;
	EventPipelineBatchUploadedEventDelegate = eventPipelineBatchUploadedEventDelegate;
	EventPipelineBatchFailedEventDelegate = eventPipelineBatchFailedEventDelegate;

	return true;
}

bool PLAYFABCORE_API FPFEventPipelineDuplicateHandle(
	_In_ FPFEventPipelineHandle eventPipelineHandle,
	_In_ FPFEventPipelineHandle& duplicatedEventPipelineHandle
) noexcept
{
	RETURN_FALSE_IF_NULL(eventPipelineHandle);

	PFEventPipelineHandle duplicatedHandle;
	HRESULT hr = PFEventPipelineDuplicateHandle(eventPipelineHandle.Get(), &duplicatedHandle);

	if (FAILED(hr))
	{
		return false;
	}

	*reinterpret_cast<PFEventPipelineHandle*>(&duplicatedEventPipelineHandle) = duplicatedHandle;

	return true;
}

bool PLAYFABCORE_API FPFEventPipelineCloseHandle(
	_In_ FPFEventPipelineHandle eventPipelineHandle
) noexcept
{
	RETURN_FALSE_IF_NULL(eventPipelineHandle);

	PFEventPipelineCloseHandle(eventPipelineHandle.Get());

	return true;
}

bool PLAYFABCORE_API FPFEventPipelineEmitEvent(
	_In_ FPFEventPipelineHandle eventPipelineHandle,
	_In_ TSharedPtr<FPFEvent const> event
) noexcept
{
	RETURN_FALSE_IF_NULL(eventPipelineHandle);
	RETURN_FALSE_IF_NULL(event);

	const FPFEvent* fpfEvent = event.Get();

	const FPFEntityKey* entityKey = fpfEvent->entity.Get();

	auto entityIdConverted = StringCast<ANSICHAR>(*entityKey->id);
	auto entityTypeConverted = StringCast<ANSICHAR>(*entityKey->type);

	const PFEntityKey pfEntityKey = {
		.id = entityIdConverted.Get(),
		.type = entityTypeConverted.Get()
	};

	auto eventNamespaceConverted = StringCast<ANSICHAR>(*fpfEvent->eventNamespace);
	auto nameConverted = StringCast<ANSICHAR>(*fpfEvent->name);
	auto clientIdConverted = StringCast<ANSICHAR>(*fpfEvent->clientId);
	auto payloadJsonConverted = StringCast<ANSICHAR>(*fpfEvent->payloadJson);

	const PFEvent pfEvent
	{
		.entity = &pfEntityKey,
		.eventNamespace = eventNamespaceConverted.Get(),
		.name = nameConverted.Get(),
		.clientId = clientIdConverted.Get(),
		.payloadJson = payloadJsonConverted.Get(),
	};

	HRESULT hr = PFEventPipelineEmitEvent(eventPipelineHandle.Get(), &pfEvent);

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool PLAYFABCORE_API FPFEventPipelineAddUploadingEntity(
	_In_ FPFEventPipelineHandle eventPipelineHandle,
	_In_ FPFEntityHandle entityHandle
) noexcept
{
	RETURN_FALSE_IF_NULL(eventPipelineHandle);
	RETURN_FALSE_IF_NULL(entityHandle);

	HRESULT hr = PFEventPipelineAddUploadingEntity(eventPipelineHandle.Get(), entityHandle.Get());

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool PLAYFABCORE_API FPFEventPipelineRemoveUploadingEntity(
	_In_ FPFEventPipelineHandle eventPipelineHandle
) noexcept
{
	RETURN_FALSE_IF_NULL(eventPipelineHandle);

	HRESULT hr = PFEventPipelineRemoveUploadingEntity(eventPipelineHandle.Get());

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool PLAYFABCORE_API FPFEventPipelineUpdateConfiguration(
	_In_ FPFEventPipelineHandle eventPipelineHandle,
	_In_ FPFEventPipelineConfig eventPipelineConfig
) noexcept
{
	RETURN_FALSE_IF_NULL(eventPipelineHandle);

	PFEventPipelineConfig pfEventPipelineConfig = {
		.maxEventsPerBatch = eventPipelineConfig.maxEventsPerBatch.Get(),
		.maxWaitTimeInSeconds = eventPipelineConfig.maxWaitTimeInSeconds.Get(),
		.pollDelayInMs = eventPipelineConfig.pollDelayInMs.Get(),
		.compressionLevel = eventPipelineConfig.compressionLevel.Get(),
		.retryOnDisconnect = eventPipelineConfig.retryOnDisconnect.Get(),
		.bufferSize = reinterpret_cast<size_t*>(eventPipelineConfig.bufferSize.Get()),
	};

	HRESULT hr = PFEventPipelineUpdateConfiguration(eventPipelineHandle.Get(), pfEventPipelineConfig);

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}
