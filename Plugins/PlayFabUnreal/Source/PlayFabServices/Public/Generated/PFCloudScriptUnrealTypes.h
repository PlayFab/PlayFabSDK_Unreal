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
/// CloudScriptRevisionOption enum.
/// </summary>
enum class FPFCloudScriptCloudScriptRevisionOption : uint32
{
	Live,
	Latest,
	Specific
};

/// <summary>
/// FPFCloudScriptExecuteCloudScriptRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCloudScriptExecuteCloudScriptRequest
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
	/// The name of the CloudScript function to execute.
	/// </summary>
	const FString functionName;

	/// <summary>
	/// (Optional) Object that is passed in to the function as the first argument.
	/// </summary>
	FPFJsonObject functionParameter;

	/// <summary>
	/// (Optional) Generate a 'player_executed_cloudscript' PlayStream event containing the results of the
	/// function execution and other contextual information. This event will show up in the PlayStream debugger
	/// console for the player in Game Manager.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> generatePlayStreamEvent;

	/// <summary>
	/// (Optional) Option for which revision of the CloudScript to execute. 'Latest' executes the most recently
	/// created revision, 'Live' executes the current live, published revision, and 'Specific' executes the
	/// specified revision. The default value is 'Specific', if the SpeificRevision parameter is specified,
	/// otherwise it is 'Live'.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCloudScriptCloudScriptRevisionOption> revisionSelection;

	/// <summary>
	/// (Optional) The specivic revision to execute, when RevisionSelection is set to 'Specific'.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> specificRevision;
};

/// <summary>
/// FPFCloudScriptScriptExecutionError data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCloudScriptScriptExecutionError
{
	/// <summary>
	/// (Optional) Error code, such as CloudScriptNotFound, JavascriptException, CloudScriptFunctionArgumentSizeExceeded,
	/// CloudScriptAPIRequestCountExceeded, CloudScriptAPIRequestError, or CloudScriptHTTPRequestError.
	/// </summary>
	_Maybenull_ const FString error;

	/// <summary>
	/// (Optional) Details about the error.
	/// </summary>
	_Maybenull_ const FString message;

	/// <summary>
	/// (Optional) Point during the execution of the script at which the error occurred, if any.
	/// </summary>
	_Maybenull_ const FString stackTrace;
};

/// <summary>
/// FPFCloudScriptLogStatement data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCloudScriptLogStatement
{
	/// <summary>
	/// (Optional) Optional object accompanying the message as contextual information.
	/// </summary>
	FPFJsonObject data;

	/// <summary>
	/// (Optional) 'Debug', 'Info', or 'Error'.
	/// </summary>
	_Maybenull_ const FString level;

	/// <summary>
	/// (Optional) Message property.
	/// </summary>
	_Maybenull_ const FString message;
};

/// <summary>
/// FPFCloudScriptExecuteCloudScriptResult data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCloudScriptExecuteCloudScriptResult
{
	/// <summary>
	/// Number of PlayFab API requests issued by the CloudScript function.
	/// </summary>
	int32 aPIRequestsIssued;

	/// <summary>
	/// (Optional) Information about the error, if any, that occurred during execution.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCloudScriptScriptExecutionError> error;

	/// <summary>
	/// ExecutionTimeSeconds property.
	/// </summary>
	double executionTimeSeconds;

	/// <summary>
	/// (Optional) The name of the function that executed.
	/// </summary>
	_Maybenull_ const FString functionName;

	/// <summary>
	/// (Optional) The object returned from the CloudScript function, if any.
	/// </summary>
	FPFJsonObject functionResult;

	/// <summary>
	/// (Optional) Flag indicating if the FunctionResult was too large and was subsequently dropped from
	/// this event. This only occurs if the total event size is larger than 350KB.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> functionResultTooLarge;

	/// <summary>
	/// Number of external HTTP requests issued by the CloudScript function.
	/// </summary>
	int32 httpRequestsIssued;

	/// <summary>
	/// (Optional) Entries logged during the function execution. These include both entries logged in the
	/// function code using log.info() and log.error() and error entries for API and HTTP request failures.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFCloudScriptLogStatement>> logs;

	/// <summary>
	/// Count of logs
	/// </summary>
	uint32 logsCount;

	/// <summary>
	/// (Optional) Flag indicating if the logs were too large and were subsequently dropped from this event.
	/// This only occurs if the total event size is larger than 350KB after the FunctionResult was removed.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> logsTooLarge;

	/// <summary>
	/// MemoryConsumedBytes property.
	/// </summary>
	uint32 memoryConsumedBytes;

	/// <summary>
	/// Processor time consumed while executing the function. This does not include time spent waiting on
	/// API calls or HTTP requests.
	/// </summary>
	double processorTimeSeconds;

	/// <summary>
	/// The revision of the CloudScript that executed.
	/// </summary>
	int32 revision;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFCloudScriptExecuteCloudScriptServerRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCloudScriptExecuteCloudScriptServerRequest
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
	/// The name of the CloudScript function to execute.
	/// </summary>
	const FString functionName;

	/// <summary>
	/// (Optional) Object that is passed in to the function as the first argument.
	/// </summary>
	FPFJsonObject functionParameter;

	/// <summary>
	/// (Optional) Generate a 'player_executed_cloudscript' PlayStream event containing the results of the
	/// function execution and other contextual information. This event will show up in the PlayStream debugger
	/// console for the player in Game Manager.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> generatePlayStreamEvent;

	/// <summary>
	/// The unique user identifier for the player on whose behalf the script is being run.
	/// </summary>
	const FString playFabId;

	/// <summary>
	/// (Optional) Option for which revision of the CloudScript to execute. 'Latest' executes the most recently
	/// created revision, 'Live' executes the current live, published revision, and 'Specific' executes the
	/// specified revision. The default value is 'Specific', if the SpeificRevision parameter is specified,
	/// otherwise it is 'Live'.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCloudScriptCloudScriptRevisionOption> revisionSelection;

	/// <summary>
	/// (Optional) The specivic revision to execute, when RevisionSelection is set to 'Specific'.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> specificRevision;
};

/// <summary>
/// FPFCloudScriptExecuteEntityCloudScriptRequest data model. Executes CloudScript with the entity profile
/// that is defined in the request.
/// </summary>
struct PLAYFABSERVICES_API FPFCloudScriptExecuteEntityCloudScriptRequest
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
	/// (Optional) The optional entity to perform this action on. Defaults to the currently logged in entity.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// The name of the CloudScript function to execute.
	/// </summary>
	const FString functionName;

	/// <summary>
	/// (Optional) Object that is passed in to the function as the first argument.
	/// </summary>
	FPFJsonObject functionParameter;

	/// <summary>
	/// (Optional) Generate a 'entity_executed_cloudscript' PlayStream event containing the results of the
	/// function execution and other contextual information. This event will show up in the PlayStream debugger
	/// console for the player in Game Manager.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> generatePlayStreamEvent;

	/// <summary>
	/// (Optional) Option for which revision of the CloudScript to execute. 'Latest' executes the most recently
	/// created revision, 'Live' executes the current live, published revision, and 'Specific' executes the
	/// specified revision. The default value is 'Specific', if the SpecificRevision parameter is specified,
	/// otherwise it is 'Live'.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCloudScriptCloudScriptRevisionOption> revisionSelection;

	/// <summary>
	/// (Optional) The specific revision to execute, when RevisionSelection is set to 'Specific'.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> specificRevision;
};

/// <summary>
/// FPFCloudScriptExecuteFunctionRequest data model. Executes an Azure Function with the profile of the
/// entity that is defined in the request.
/// </summary>
struct PLAYFABSERVICES_API FPFCloudScriptExecuteFunctionRequest
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
	/// (Optional) The optional entity to perform this action on. Defaults to the currently logged in entity.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// The name of the CloudScript function to execute.
	/// </summary>
	const FString functionName;

	/// <summary>
	/// (Optional) Object that is passed in to the function as the FunctionArgument field of the FunctionExecutionContext
	/// data structure.
	/// </summary>
	FPFJsonObject functionParameter;

	/// <summary>
	/// (Optional) Generate a 'entity_executed_cloudscript_function' PlayStream event containing the results
	/// of the function execution and other contextual information. This event will show up in the PlayStream
	/// debugger console for the player in Game Manager.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> generatePlayStreamEvent;
};

/// <summary>
/// FPFCloudScriptFunctionExecutionError data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCloudScriptFunctionExecutionError
{
	/// <summary>
	/// (Optional) Error code, such as CloudScriptAzureFunctionsExecutionTimeLimitExceeded, CloudScriptAzureFunctionsArgumentSizeExceeded,
	/// CloudScriptAzureFunctionsReturnSizeExceeded or CloudScriptAzureFunctionsHTTPRequestError.
	/// </summary>
	_Maybenull_ const FString error;

	/// <summary>
	/// (Optional) Details about the error.
	/// </summary>
	_Maybenull_ const FString message;

	/// <summary>
	/// (Optional) Point during the execution of the function at which the error occurred, if any.
	/// </summary>
	_Maybenull_ const FString stackTrace;
};

/// <summary>
/// FPFCloudScriptExecuteFunctionResult data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCloudScriptExecuteFunctionResult
{
	/// <summary>
	/// (Optional) Error from the CloudScript Azure Function.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCloudScriptFunctionExecutionError> error;

	/// <summary>
	/// The amount of time the function took to execute.
	/// </summary>
	int32 executionTimeMilliseconds;

	/// <summary>
	/// (Optional) The name of the function that executed.
	/// </summary>
	_Maybenull_ const FString functionName;

	/// <summary>
	/// (Optional) The object returned from the function, if any.
	/// </summary>
	FPFJsonObject functionResult;

	/// <summary>
	/// (Optional) The size in bytes of the object returned from the function, if any.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> functionResultSize;

	/// <summary>
	/// (Optional) Flag indicating if the FunctionResult was too large and was subsequently dropped from
	/// this event.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> functionResultTooLarge;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFCloudScriptListFunctionsRequest data model. A title can have many functions, ListHttpFunctions
/// will return a list of all the currently registered HTTP triggered functions for a given title.
/// </summary>
struct PLAYFABSERVICES_API FPFCloudScriptListFunctionsRequest
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

/// <summary>
/// FPFCloudScriptEventHubFunctionModel data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCloudScriptEventHubFunctionModel
{
	/// <summary>
	/// (Optional) The connection string for the event hub.
	/// </summary>
	_Maybenull_ const FString connectionString;

	/// <summary>
	/// (Optional) The name of the event hub that triggers the Azure Function.
	/// </summary>
	_Maybenull_ const FString eventHubName;

	/// <summary>
	/// (Optional) The name the function was registered under.
	/// </summary>
	_Maybenull_ const FString functionName;
};

/// <summary>
/// FPFCloudScriptListEventHubFunctionsResult data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCloudScriptListEventHubFunctionsResult
{
	/// <summary>
	/// (Optional) The list of EventHub triggered functions that are currently registered for the title.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFCloudScriptEventHubFunctionModel>> functions;

	/// <summary>
	/// Count of functions
	/// </summary>
	uint32 functionsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFCloudScriptRegisterEventHubFunctionRequest data model. A title can have many functions, RegisterEventHubFunction
/// associates a function name with an event hub name and connection string.
/// </summary>
struct PLAYFABSERVICES_API FPFCloudScriptRegisterEventHubFunctionRequest
{
	/// <summary>
	/// A connection string for the namespace of the event hub for the Azure Function.
	/// </summary>
	const FString connectionString;

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
	/// The name of the event hub for the Azure Function.
	/// </summary>
	const FString eventHubName;

	/// <summary>
	/// The name of the function to register.
	/// </summary>
	const FString functionName;
};

// Delegates Declarations

DECLARE_DELEGATE_TwoParams(FOnClientExecuteCloudScriptCompleted, const FPFCloudScriptExecuteCloudScriptResult&, bool);

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerExecuteCloudScriptCompleted, const FPFCloudScriptExecuteCloudScriptResult&, bool);
#endif

DECLARE_DELEGATE_TwoParams(FOnExecuteEntityCloudScriptCompleted, const FPFCloudScriptExecuteCloudScriptResult&, bool);

DECLARE_DELEGATE_TwoParams(FOnExecuteFunctionCompleted, const FPFCloudScriptExecuteFunctionResult&, bool);

#if 0
DECLARE_DELEGATE_TwoParams(FOnListEventHubFunctionsCompleted, const FPFCloudScriptListEventHubFunctionsResult&, bool);
#endif

#if 0
DECLARE_DELEGATE_TwoParams(FOnRegisterEventHubFunctionCompleted, const FString&, bool);
#endif

#pragma pop_macro("IN")