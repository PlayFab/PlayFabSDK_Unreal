// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFCloudScriptTypeConverters.h"

const FPFCloudScriptCloudScriptRevisionOption ConvertCloudScriptRevisionOptionToUnreal(const PFCloudScriptCloudScriptRevisionOption* enumVal)
{
	if (enumVal == nullptr) {
		return FPFCloudScriptCloudScriptRevisionOption::Live;
	}

	switch(*enumVal)
	{
	case PFCloudScriptCloudScriptRevisionOption::Live: return FPFCloudScriptCloudScriptRevisionOption::Live;
	case PFCloudScriptCloudScriptRevisionOption::Latest: return FPFCloudScriptCloudScriptRevisionOption::Latest;
	case PFCloudScriptCloudScriptRevisionOption::Specific: return FPFCloudScriptCloudScriptRevisionOption::Specific;
	default:
	return FPFCloudScriptCloudScriptRevisionOption::Live;
	}
}

const PFCloudScriptCloudScriptRevisionOption ConvertCloudScriptRevisionOptionToPlayfab(TSharedPtr<const FPFCloudScriptCloudScriptRevisionOption> enumVal)
{
	if (!enumVal.IsValid()) {
		return PFCloudScriptCloudScriptRevisionOption::Live;
	}

	switch(*enumVal)
	{
	case FPFCloudScriptCloudScriptRevisionOption::Live: return PFCloudScriptCloudScriptRevisionOption::Live;
	case FPFCloudScriptCloudScriptRevisionOption::Latest: return PFCloudScriptCloudScriptRevisionOption::Latest;
	case FPFCloudScriptCloudScriptRevisionOption::Specific: return PFCloudScriptCloudScriptRevisionOption::Specific;
	default:
	return PFCloudScriptCloudScriptRevisionOption::Live;
	}
}

TSharedPtr<const FPFCloudScriptExecuteCloudScriptRequest> ConvertExecuteCloudScriptRequestToUnreal(const PFCloudScriptExecuteCloudScriptRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCloudScriptExecuteCloudScriptRequest> ConvertedType = MakeShared<FPFCloudScriptExecuteCloudScriptRequest>(FPFCloudScriptExecuteCloudScriptRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.functionName = Datatype->functionName == nullptr ? FString() : FString(Datatype->functionName),
		.functionParameter = FPFJsonObject{ .stringValue = FString(Datatype->functionParameter.stringValue) },
		.generatePlayStreamEvent = TSharedPtr<const bool>(Datatype->generatePlayStreamEvent),
		.revisionSelection = MakeShared<FPFCloudScriptCloudScriptRevisionOption>(ConvertCloudScriptRevisionOptionToUnreal(Datatype->revisionSelection)),
		.specificRevision = TSharedPtr<const int32>(Datatype->specificRevision)
	});

	return ConvertedType;
}

const PFCloudScriptExecuteCloudScriptRequest* ConvertExecuteCloudScriptRequestToPlayfab(TSharedPtr<const FPFCloudScriptExecuteCloudScriptRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCloudScriptExecuteCloudScriptRequest* ConvertedType = new PFCloudScriptExecuteCloudScriptRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.functionName = ConvertFStringToCharPtr(Datatype->functionName),
		.functionParameter = PFJsonObject{ .stringValue = ConvertFStringToCharPtr(Datatype->functionParameter.stringValue) },
		.generatePlayStreamEvent = Datatype->generatePlayStreamEvent ? new bool(*Datatype->generatePlayStreamEvent) : nullptr,
		.revisionSelection = new PFCloudScriptCloudScriptRevisionOption(ConvertCloudScriptRevisionOptionToPlayfab(Datatype->revisionSelection)),
		.specificRevision = Datatype->specificRevision ? new int32(*Datatype->specificRevision) : nullptr
	};

	return ConvertedType;
}

TSharedPtr<const FPFCloudScriptScriptExecutionError> ConvertScriptExecutionErrorToUnreal(const PFCloudScriptScriptExecutionError* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCloudScriptScriptExecutionError> ConvertedType = MakeShared<FPFCloudScriptScriptExecutionError>(FPFCloudScriptScriptExecutionError{
		.error = Datatype->error == nullptr ? FString() : FString(Datatype->error),
		.message = Datatype->message == nullptr ? FString() : FString(Datatype->message),
		.stackTrace = Datatype->stackTrace == nullptr ? FString() : FString(Datatype->stackTrace)
	});

	return ConvertedType;
}

const PFCloudScriptScriptExecutionError* ConvertScriptExecutionErrorToPlayfab(TSharedPtr<const FPFCloudScriptScriptExecutionError> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCloudScriptScriptExecutionError* ConvertedType = new PFCloudScriptScriptExecutionError{
		.error = ConvertFStringToCharPtr(Datatype->error),
		.message = ConvertFStringToCharPtr(Datatype->message),
		.stackTrace = ConvertFStringToCharPtr(Datatype->stackTrace)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCloudScriptLogStatement> ConvertLogStatementToUnreal(const PFCloudScriptLogStatement* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCloudScriptLogStatement> ConvertedType = MakeShared<FPFCloudScriptLogStatement>(FPFCloudScriptLogStatement{
		.data = FPFJsonObject{ .stringValue = FString(Datatype->data.stringValue) },
		.level = Datatype->level == nullptr ? FString() : FString(Datatype->level),
		.message = Datatype->message == nullptr ? FString() : FString(Datatype->message)
	});

	return ConvertedType;
}

const PFCloudScriptLogStatement* ConvertLogStatementToPlayfab(TSharedPtr<const FPFCloudScriptLogStatement> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCloudScriptLogStatement* ConvertedType = new PFCloudScriptLogStatement{
		.data = PFJsonObject{ .stringValue = ConvertFStringToCharPtr(Datatype->data.stringValue) },
		.level = ConvertFStringToCharPtr(Datatype->level),
		.message = ConvertFStringToCharPtr(Datatype->message)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCloudScriptExecuteCloudScriptResult> ConvertExecuteCloudScriptResultToUnreal(const PFCloudScriptExecuteCloudScriptResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCloudScriptExecuteCloudScriptResult> ConvertedType = MakeShared<FPFCloudScriptExecuteCloudScriptResult>(FPFCloudScriptExecuteCloudScriptResult{
		.aPIRequestsIssued = Datatype->aPIRequestsIssued,
		.error = ConvertScriptExecutionErrorToUnreal(Datatype->error),
		.executionTimeSeconds = Datatype->executionTimeSeconds,
		.functionName = Datatype->functionName == nullptr ? FString() : FString(Datatype->functionName),
		.functionResult = FPFJsonObject{ .stringValue = FString(Datatype->functionResult.stringValue) },
		.functionResultTooLarge = TSharedPtr<const bool>(Datatype->functionResultTooLarge),
		.httpRequestsIssued = Datatype->httpRequestsIssued,
		.logs = ConvertPlayfabArrayToUnreal<PFCloudScriptLogStatement, FPFCloudScriptLogStatement>(Datatype->logs, Datatype->logsCount, ConvertLogStatementToUnreal),
		.logsCount = Datatype->logsCount,
		.logsTooLarge = TSharedPtr<const bool>(Datatype->logsTooLarge),
		.memoryConsumedBytes = Datatype->memoryConsumedBytes,
		.processorTimeSeconds = Datatype->processorTimeSeconds,
		.revision = Datatype->revision
	});

	return ConvertedType;
}

const PFCloudScriptExecuteCloudScriptResult* ConvertExecuteCloudScriptResultToPlayfab(TSharedPtr<const FPFCloudScriptExecuteCloudScriptResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCloudScriptExecuteCloudScriptResult* ConvertedType = new PFCloudScriptExecuteCloudScriptResult{
		.aPIRequestsIssued = Datatype->aPIRequestsIssued,
		.error = ConvertScriptExecutionErrorToPlayfab(Datatype->error),
		.executionTimeSeconds = Datatype->executionTimeSeconds,
		.functionName = ConvertFStringToCharPtr(Datatype->functionName),
		.functionResult = PFJsonObject{ .stringValue = ConvertFStringToCharPtr(Datatype->functionResult.stringValue) },
		.functionResultTooLarge = Datatype->functionResultTooLarge ? new bool(*Datatype->functionResultTooLarge) : nullptr,
		.httpRequestsIssued = Datatype->httpRequestsIssued,
		.logs = ConvertUnrealArrayToPlayfab<PFCloudScriptLogStatement, FPFCloudScriptLogStatement>(Datatype->logs, ConvertLogStatementToPlayfab),
		.logsCount = (uint32_t)Datatype->logs.Num(),
		.logsTooLarge = Datatype->logsTooLarge ? new bool(*Datatype->logsTooLarge) : nullptr,
		.memoryConsumedBytes = Datatype->memoryConsumedBytes,
		.processorTimeSeconds = Datatype->processorTimeSeconds,
		.revision = Datatype->revision
	};

	return ConvertedType;
}

TSharedPtr<const FPFCloudScriptExecuteCloudScriptServerRequest> ConvertExecuteCloudScriptServerRequestToUnreal(const PFCloudScriptExecuteCloudScriptServerRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCloudScriptExecuteCloudScriptServerRequest> ConvertedType = MakeShared<FPFCloudScriptExecuteCloudScriptServerRequest>(FPFCloudScriptExecuteCloudScriptServerRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.functionName = Datatype->functionName == nullptr ? FString() : FString(Datatype->functionName),
		.functionParameter = FPFJsonObject{ .stringValue = FString(Datatype->functionParameter.stringValue) },
		.generatePlayStreamEvent = TSharedPtr<const bool>(Datatype->generatePlayStreamEvent),
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId),
		.revisionSelection = MakeShared<FPFCloudScriptCloudScriptRevisionOption>(ConvertCloudScriptRevisionOptionToUnreal(Datatype->revisionSelection)),
		.specificRevision = TSharedPtr<const int32>(Datatype->specificRevision)
	});

	return ConvertedType;
}

const PFCloudScriptExecuteCloudScriptServerRequest* ConvertExecuteCloudScriptServerRequestToPlayfab(TSharedPtr<const FPFCloudScriptExecuteCloudScriptServerRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCloudScriptExecuteCloudScriptServerRequest* ConvertedType = new PFCloudScriptExecuteCloudScriptServerRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.functionName = ConvertFStringToCharPtr(Datatype->functionName),
		.functionParameter = PFJsonObject{ .stringValue = ConvertFStringToCharPtr(Datatype->functionParameter.stringValue) },
		.generatePlayStreamEvent = Datatype->generatePlayStreamEvent ? new bool(*Datatype->generatePlayStreamEvent) : nullptr,
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId),
		.revisionSelection = new PFCloudScriptCloudScriptRevisionOption(ConvertCloudScriptRevisionOptionToPlayfab(Datatype->revisionSelection)),
		.specificRevision = Datatype->specificRevision ? new int32(*Datatype->specificRevision) : nullptr
	};

	return ConvertedType;
}

TSharedPtr<const FPFCloudScriptExecuteEntityCloudScriptRequest> ConvertExecuteEntityCloudScriptRequestToUnreal(const PFCloudScriptExecuteEntityCloudScriptRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCloudScriptExecuteEntityCloudScriptRequest> ConvertedType = MakeShared<FPFCloudScriptExecuteEntityCloudScriptRequest>(FPFCloudScriptExecuteEntityCloudScriptRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.functionName = Datatype->functionName == nullptr ? FString() : FString(Datatype->functionName),
		.functionParameter = FPFJsonObject{ .stringValue = FString(Datatype->functionParameter.stringValue) },
		.generatePlayStreamEvent = TSharedPtr<const bool>(Datatype->generatePlayStreamEvent),
		.revisionSelection = MakeShared<FPFCloudScriptCloudScriptRevisionOption>(ConvertCloudScriptRevisionOptionToUnreal(Datatype->revisionSelection)),
		.specificRevision = TSharedPtr<const int32>(Datatype->specificRevision)
	});

	return ConvertedType;
}

const PFCloudScriptExecuteEntityCloudScriptRequest* ConvertExecuteEntityCloudScriptRequestToPlayfab(TSharedPtr<const FPFCloudScriptExecuteEntityCloudScriptRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCloudScriptExecuteEntityCloudScriptRequest* ConvertedType = new PFCloudScriptExecuteEntityCloudScriptRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.functionName = ConvertFStringToCharPtr(Datatype->functionName),
		.functionParameter = PFJsonObject{ .stringValue = ConvertFStringToCharPtr(Datatype->functionParameter.stringValue) },
		.generatePlayStreamEvent = Datatype->generatePlayStreamEvent ? new bool(*Datatype->generatePlayStreamEvent) : nullptr,
		.revisionSelection = new PFCloudScriptCloudScriptRevisionOption(ConvertCloudScriptRevisionOptionToPlayfab(Datatype->revisionSelection)),
		.specificRevision = Datatype->specificRevision ? new int32(*Datatype->specificRevision) : nullptr
	};

	return ConvertedType;
}

TSharedPtr<const FPFCloudScriptExecuteFunctionRequest> ConvertExecuteFunctionRequestToUnreal(const PFCloudScriptExecuteFunctionRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCloudScriptExecuteFunctionRequest> ConvertedType = MakeShared<FPFCloudScriptExecuteFunctionRequest>(FPFCloudScriptExecuteFunctionRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.entity = ConvertEntityKeyToUnreal(Datatype->entity),
		.functionName = Datatype->functionName == nullptr ? FString() : FString(Datatype->functionName),
		.functionParameter = FPFJsonObject{ .stringValue = FString(Datatype->functionParameter.stringValue) },
		.generatePlayStreamEvent = TSharedPtr<const bool>(Datatype->generatePlayStreamEvent)
	});

	return ConvertedType;
}

const PFCloudScriptExecuteFunctionRequest* ConvertExecuteFunctionRequestToPlayfab(TSharedPtr<const FPFCloudScriptExecuteFunctionRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCloudScriptExecuteFunctionRequest* ConvertedType = new PFCloudScriptExecuteFunctionRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(Datatype->entity),
		.functionName = ConvertFStringToCharPtr(Datatype->functionName),
		.functionParameter = PFJsonObject{ .stringValue = ConvertFStringToCharPtr(Datatype->functionParameter.stringValue) },
		.generatePlayStreamEvent = Datatype->generatePlayStreamEvent ? new bool(*Datatype->generatePlayStreamEvent) : nullptr
	};

	return ConvertedType;
}

TSharedPtr<const FPFCloudScriptFunctionExecutionError> ConvertFunctionExecutionErrorToUnreal(const PFCloudScriptFunctionExecutionError* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCloudScriptFunctionExecutionError> ConvertedType = MakeShared<FPFCloudScriptFunctionExecutionError>(FPFCloudScriptFunctionExecutionError{
		.error = Datatype->error == nullptr ? FString() : FString(Datatype->error),
		.message = Datatype->message == nullptr ? FString() : FString(Datatype->message),
		.stackTrace = Datatype->stackTrace == nullptr ? FString() : FString(Datatype->stackTrace)
	});

	return ConvertedType;
}

const PFCloudScriptFunctionExecutionError* ConvertFunctionExecutionErrorToPlayfab(TSharedPtr<const FPFCloudScriptFunctionExecutionError> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCloudScriptFunctionExecutionError* ConvertedType = new PFCloudScriptFunctionExecutionError{
		.error = ConvertFStringToCharPtr(Datatype->error),
		.message = ConvertFStringToCharPtr(Datatype->message),
		.stackTrace = ConvertFStringToCharPtr(Datatype->stackTrace)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCloudScriptExecuteFunctionResult> ConvertExecuteFunctionResultToUnreal(const PFCloudScriptExecuteFunctionResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCloudScriptExecuteFunctionResult> ConvertedType = MakeShared<FPFCloudScriptExecuteFunctionResult>(FPFCloudScriptExecuteFunctionResult{
		.error = ConvertFunctionExecutionErrorToUnreal(Datatype->error),
		.executionTimeMilliseconds = Datatype->executionTimeMilliseconds,
		.functionName = Datatype->functionName == nullptr ? FString() : FString(Datatype->functionName),
		.functionResult = FPFJsonObject{ .stringValue = FString(Datatype->functionResult.stringValue) },
		.functionResultSize = TSharedPtr<const int32>(Datatype->functionResultSize),
		.functionResultTooLarge = TSharedPtr<const bool>(Datatype->functionResultTooLarge)
	});

	return ConvertedType;
}

const PFCloudScriptExecuteFunctionResult* ConvertExecuteFunctionResultToPlayfab(TSharedPtr<const FPFCloudScriptExecuteFunctionResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCloudScriptExecuteFunctionResult* ConvertedType = new PFCloudScriptExecuteFunctionResult{
		.error = ConvertFunctionExecutionErrorToPlayfab(Datatype->error),
		.executionTimeMilliseconds = Datatype->executionTimeMilliseconds,
		.functionName = ConvertFStringToCharPtr(Datatype->functionName),
		.functionResult = PFJsonObject{ .stringValue = ConvertFStringToCharPtr(Datatype->functionResult.stringValue) },
		.functionResultSize = Datatype->functionResultSize ? new int32(*Datatype->functionResultSize) : nullptr,
		.functionResultTooLarge = Datatype->functionResultTooLarge ? new bool(*Datatype->functionResultTooLarge) : nullptr
	};

	return ConvertedType;
}

TSharedPtr<const FPFCloudScriptListFunctionsRequest> ConvertListFunctionsRequestToUnreal(const PFCloudScriptListFunctionsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCloudScriptListFunctionsRequest> ConvertedType = MakeShared<FPFCloudScriptListFunctionsRequest>(FPFCloudScriptListFunctionsRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount
	});

	return ConvertedType;
}

const PFCloudScriptListFunctionsRequest* ConvertListFunctionsRequestToPlayfab(TSharedPtr<const FPFCloudScriptListFunctionsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCloudScriptListFunctionsRequest* ConvertedType = new PFCloudScriptListFunctionsRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFCloudScriptEventHubFunctionModel> ConvertEventHubFunctionModelToUnreal(const PFCloudScriptEventHubFunctionModel* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCloudScriptEventHubFunctionModel> ConvertedType = MakeShared<FPFCloudScriptEventHubFunctionModel>(FPFCloudScriptEventHubFunctionModel{
		.connectionString = Datatype->connectionString == nullptr ? FString() : FString(Datatype->connectionString),
		.eventHubName = Datatype->eventHubName == nullptr ? FString() : FString(Datatype->eventHubName),
		.functionName = Datatype->functionName == nullptr ? FString() : FString(Datatype->functionName)
	});

	return ConvertedType;
}

const PFCloudScriptEventHubFunctionModel* ConvertEventHubFunctionModelToPlayfab(TSharedPtr<const FPFCloudScriptEventHubFunctionModel> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCloudScriptEventHubFunctionModel* ConvertedType = new PFCloudScriptEventHubFunctionModel{
		.connectionString = ConvertFStringToCharPtr(Datatype->connectionString),
		.eventHubName = ConvertFStringToCharPtr(Datatype->eventHubName),
		.functionName = ConvertFStringToCharPtr(Datatype->functionName)
	};

	return ConvertedType;
}

TSharedPtr<const FPFCloudScriptListEventHubFunctionsResult> ConvertListEventHubFunctionsResultToUnreal(const PFCloudScriptListEventHubFunctionsResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCloudScriptListEventHubFunctionsResult> ConvertedType = MakeShared<FPFCloudScriptListEventHubFunctionsResult>(FPFCloudScriptListEventHubFunctionsResult{
		.functions = ConvertPlayfabArrayToUnreal<PFCloudScriptEventHubFunctionModel, FPFCloudScriptEventHubFunctionModel>(Datatype->functions, Datatype->functionsCount, ConvertEventHubFunctionModelToUnreal),
		.functionsCount = Datatype->functionsCount
	});

	return ConvertedType;
}

const PFCloudScriptListEventHubFunctionsResult* ConvertListEventHubFunctionsResultToPlayfab(TSharedPtr<const FPFCloudScriptListEventHubFunctionsResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCloudScriptListEventHubFunctionsResult* ConvertedType = new PFCloudScriptListEventHubFunctionsResult{
		.functions = ConvertUnrealArrayToPlayfab<PFCloudScriptEventHubFunctionModel, FPFCloudScriptEventHubFunctionModel>(Datatype->functions, ConvertEventHubFunctionModelToPlayfab),
		.functionsCount = (uint32_t)Datatype->functions.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFCloudScriptRegisterEventHubFunctionRequest> ConvertRegisterEventHubFunctionRequestToUnreal(const PFCloudScriptRegisterEventHubFunctionRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFCloudScriptRegisterEventHubFunctionRequest> ConvertedType = MakeShared<FPFCloudScriptRegisterEventHubFunctionRequest>(FPFCloudScriptRegisterEventHubFunctionRequest{
		.connectionString = Datatype->connectionString == nullptr ? FString() : FString(Datatype->connectionString),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.eventHubName = Datatype->eventHubName == nullptr ? FString() : FString(Datatype->eventHubName),
		.functionName = Datatype->functionName == nullptr ? FString() : FString(Datatype->functionName)
	});

	return ConvertedType;
}

const PFCloudScriptRegisterEventHubFunctionRequest* ConvertRegisterEventHubFunctionRequestToPlayfab(TSharedPtr<const FPFCloudScriptRegisterEventHubFunctionRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFCloudScriptRegisterEventHubFunctionRequest* ConvertedType = new PFCloudScriptRegisterEventHubFunctionRequest{
		.connectionString = ConvertFStringToCharPtr(Datatype->connectionString),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.eventHubName = ConvertFStringToCharPtr(Datatype->eventHubName),
		.functionName = ConvertFStringToCharPtr(Datatype->functionName)
	};

	return ConvertedType;
}
