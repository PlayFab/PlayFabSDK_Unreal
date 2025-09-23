// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#include "CoreMinimal.h"
#include "Async/AsyncWork.h"
#include "Async/Async.h"
#include "XAsyncTaskQueueHelpers.h"
#include "XAsyncTaskManager.h"
#include "XAsyncTask.h"
#include "PFEntity.h"
#include "PFServiceConfig.h"
#include "PFLocalizationUnrealTypes.h"
#include "PFLocalizationTypeConverters.h"

THIRD_PARTY_INCLUDES_START
#include <playfab/services/PFServices.h>
THIRD_PARTY_INCLUDES_END

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

/// <summary>
/// Retrieves the list of allowed languages, only accessible by title entities
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows, Linux, and macOS.
/// When the asynchronous task is complete, call <see cref="PFLocalizationGetLanguageListGetResultSize"/>
/// and <see cref="PFLocalizationGetLanguageListGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FGetLanguageListAsyncTask : public FXAsyncTask
{
public:
	FGetLanguageListAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFLocalizationGetLanguageListRequest InRequest,
	const FOnGetLanguageListCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFLocalizationGetLanguageListRequest Request;
	
	FOnGetLanguageListCompleted Delegate;

	HRESULT HResult;
};

#endif
