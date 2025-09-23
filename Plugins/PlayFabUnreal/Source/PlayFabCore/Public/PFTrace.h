// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include "CoreMinimal.h"
THIRD_PARTY_INCLUDES_START
#include <playfab/core/PFTrace.h>
THIRD_PARTY_INCLUDES_END

extern "C"
{
bool PLAYFABCORE_API FPFTraceEnableTraceToFile(
	_In_z_ FString traceFileDirectory
) noexcept;
}
