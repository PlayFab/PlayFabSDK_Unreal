// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include "CoreMinimal.h"
#include "XAsyncTaskManager.h"
#include "PFCoreUnrealTypes.h"
#include "PFEntity.h"
#include "PFServiceConfig.h"
#include "PFCoreTypeConverters.h"
#include "PFEventPipelineTypes.h"
#if PLATFORM_WINDOWS || (defined(PLATFORM_XSX) && PLATFORM_XSX) || (defined(PLATFORM_XB1) && PLATFORM_XB1)
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/AllowWindowsPlatformAtomics.h"
#endif
THIRD_PARTY_INCLUDES_START
#include <playfab/core/PFEventPipeline.h>
THIRD_PARTY_INCLUDES_END
#if PLATFORM_WINDOWS || (defined(PLATFORM_XSX) && PLATFORM_XSX) || (defined(PLATFORM_XB1) && PLATFORM_XB1)
#include "Windows/HideWindowsPlatformAtomics.h"
#include "Windows/HideWindowsPlatformTypes.h"
#endif

extern "C"
{

/// <summary>
/// Creates an event pipeline to upload Telemetry events using a Telemetry Key.
/// </summary>
/// <param name="eventPipelineTelemetryKeyConfig">The Configuration to use if telemetry key logging will be used.</param>
/// <param name="eventPipelineBatchUploadedEventHandler">Optional handler that will be invoked when a batch of events is uploaded.</param>
/// <param name="eventPipelineBatchFailedEventHandler">Optional handler that will be invoked when uploading a batch of events fails.</param>
/// <param name="handlerContext">Optional pointer to data used by the event handlers.</param>
/// <param name="eventPipelineHandle">Handle to the created pipeline. Needs to be closed with PFEventPipelineCloseHandle when it isn't needed.</param>
/// <returns>Result code for this API operation.  Possible values are S_OK, E_INVALIDARG, E_PF_NOT_INITIALIZED or E_FAIL.</returns>
bool PLAYFABCORE_API FPFEventPipelineCreateTelemetryPipelineHandleWithKey(
	_In_ TSharedPtr<FPFEventPipelineTelemetryKeyConfig> eventPipelineTelemetryKeyConfig,
	_In_opt_ FPFEventPipelineBatchUploadSucceededEventDelegate eventPipelineBatchUploadedEventDelegate,
	_In_opt_ FPFEventPipelineBatchUploadFailedEventDelegate eventPipelineBatchFailedEventDelegate,
	_In_opt_ TSharedPtr<void> handlerContext,
	_Out_ FPFEventPipelineHandle& eventPipelineHandle
) noexcept;

/// <summary>
/// Creates an event pipeline to upload Telemetry events using an Entity.
/// </summary>
/// <param name="entityHandle">The Entity whose token will be used to make the PlayFab service requests in the background.</param>
/// <param name="queue">The async queue where background work will be scheduled and where event callbacks will be invoked.</param>
/// <param name="eventPipelineBatchUploadedEventHandler">Optional handler that will be invoked when a batch of events is uploaded.</param>
/// <param name="eventPipelineBatchFailedEventHandler">Optional handler that will be invoked when uploading a batch of events fails.</param>
/// <param name="handlerContext">Optional pointer to data used by the event handlers.</param>
/// <param name="eventPipelineHandle">Handle to the created pipeline. Needs to be closed with PFEventPipelineCloseHandle when it isn't needed.</param>
/// <returns>Result code for this API operation.  Possible values are S_OK, E_INVALIDARG, E_PF_NOT_INITIALIZED or E_FAIL.</returns>
bool PLAYFABCORE_API FPFEventPipelineCreateTelemetryPipelineHandleWithEntity(
	_In_ FPFEntityHandle entityHandle,
	_In_opt_ FPFEventPipelineBatchUploadSucceededEventDelegate eventPipelineBatchUploadedEventDelegate,
	_In_opt_ FPFEventPipelineBatchUploadFailedEventDelegate eventPipelineBatchFailedEventDelegate,
	_In_opt_ TSharedPtr<void> handlerContext,
	_Out_ FPFEventPipelineHandle& eventPipelineHandle
) noexcept;

/// <summary>
/// Creates an event pipeline to upload PlayStream events using an Entity.
/// </summary>
/// <param name="entityHandle">The Entity whose token will be used to make the PlayFab service requests in the background.</param>
/// <param name="queue">The async queue where background work will be scheduled and where event callbacks will be invoked.</param>
/// <param name="eventPipelineBatchUploadedEventHandler">Optional handler that will be invoked when a batch of events is uploaded.</param>
/// <param name="eventPipelineBatchFailedEventHandler">Optional handler that will be invoked when uploading a batch of events fails.</param>
/// <param name="handlerContext">Optional pointer to data used by the event handlers.</param>
/// <param name="eventPipelineHandle">Handle to the created pipeline. Needs to be closed with PFEventPipelineCloseHandle when it isn't needed.</param>
/// <returns>Result code for this API operation.  Possible values are S_OK, E_INVALIDARG, E_PF_NOT_INITIALIZED or E_FAIL.</returns>
bool PLAYFABCORE_API FPFEventPipelineCreatePlayStreamPipelineHandle(
	_In_ FPFEntityHandle entityHandle,
	_In_opt_ FPFEventPipelineBatchUploadSucceededEventDelegate eventPipelineBatchUploadedEventDelegate,
	_In_opt_ FPFEventPipelineBatchUploadFailedEventDelegate eventPipelineBatchFailedEventDelegate,
	_In_opt_ TSharedPtr<void> handlerContext,
	_Out_ FPFEventPipelineHandle& eventPipelineHandle
) noexcept;

/// <summary>
/// Duplicates a FPFEventPipelineHandle.
/// </summary>
/// <param name="eventPipelineHandle">EventPipeline handle to duplicate.</param>
/// <param name="duplicatedHandle">The duplicated handle.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// Both the duplicated handle and the original handle need to be closed with PFEventPipelineCloseHandle when they are no longer needed.
/// </remarks>
bool PLAYFABCORE_API FPFEventPipelineDuplicateHandle(
	_In_ FPFEventPipelineHandle eventPipelineHandle,
	_In_ FPFEventPipelineHandle& duplicatedEventPipelineHandle
) noexcept;

/// <summary>
/// Closes a FPFEventPipelineHandle.
/// </summary>
/// <param name="eventPipelineHandle">EventPipeline handle to close.</param>
/// <returns>Result code for this API operation.</returns>
bool PLAYFABCORE_API FPFEventPipelineCloseHandle(
	_In_ FPFEventPipelineHandle eventPipelineHandle
) noexcept;

/// <summary>
/// Adds a event to a pipelines buffer to be uploaded. The API will return synchronously and the event
/// will be uploaded in the background based on the pipeline configuration.
/// </summary>
/// <param name="eventPipelineHandle">The EventPipeline to submit the event to.</param>
/// <param name="event">Event to upload.</param>
/// <returns>Result code for this API operation. Possible values are S_OK, E_PF_NOT_INITIALIZED, or E_FAIL.</returns>
bool PLAYFABCORE_API FPFEventPipelineEmitEvent(
	_In_ FPFEventPipelineHandle eventPipelineHandle,
	_In_ TSharedPtr<FPFEvent const> event
) noexcept;

/// <summary>
/// Adds an entity to an existing pipeline. All events emitted will be linked to this entity.
/// </summary>
/// <param name="eventPipelineHandle">The existing EventPipeline handle to add the uploading entity.</param>
/// <param name="entityHandle">The Entity whose token will be used to make the PlayFab service requests in the background.</param>
/// <returns>Result code for this API operation. Possible values are S_OK, E_PF_NOT_INITIALIZED or E_FAIL.</returns>
bool PLAYFABCORE_API FPFEventPipelineAddUploadingEntity(
	_In_ FPFEventPipelineHandle eventPipelineHandle,
	_In_ FPFEntityHandle entityHandle
) noexcept;

/// <summary>
/// Remove an entity from an existing pipeline. If a valid Telemetry Key Configuration was added at pipeline creation
/// it will switch to it.
/// </summary>
/// <param name="eventPipelineHandle">The existing EventPipeline handle to remove the uploading entity.</param>
/// <returns>Result code for this API operation. Possible values are S_OK, E_PF_NOT_INITIALIZED, or E_FAIL.</returns>
bool PLAYFABCORE_API FPFEventPipelineRemoveUploadingEntity(
	_In_ FPFEventPipelineHandle eventPipelineHandle
) noexcept;

/// <summary>
/// Update an existing pipeline configuration.
/// </summary>
/// <param name="eventPipelineHandle">The existing EventPipeline handle to add the uploading entity.</param>
/// <param name="eventPipelineConfig">Struct that contains the new configuration of the event pipeline.</param>
/// <returns>Result code for this API operation. Possible values are S_OK, E_PF_NOT_INITIALIZED, or E_FAIL.</returns>
bool PLAYFABCORE_API FPFEventPipelineUpdateConfiguration(
	_In_ FPFEventPipelineHandle eventPipelineHandle,
	_In_ FPFEventPipelineConfig eventPipelineConfig
) noexcept;
}