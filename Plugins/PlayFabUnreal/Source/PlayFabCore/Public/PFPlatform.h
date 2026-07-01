// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include "CoreMinimal.h"
#include "XAsyncTaskQueueHelpers.h"
#include "PFPlatformTypes.h"
#if PLATFORM_WINDOWS || (defined(PLATFORM_XSX) && PLATFORM_XSX) || (defined(PLATFORM_XB1) && PLATFORM_XB1)
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/AllowWindowsPlatformAtomics.h"
#endif
THIRD_PARTY_INCLUDES_START
#include <playfab/core/PFPlatform.h>
THIRD_PARTY_INCLUDES_END
#if PLATFORM_WINDOWS || (defined(PLATFORM_XSX) && PLATFORM_XSX) || (defined(PLATFORM_XB1) && PLATFORM_XB1)
#include "Windows/HideWindowsPlatformAtomics.h"
#include "Windows/HideWindowsPlatformTypes.h"
#endif

extern "C"
{

/// <summary>
/// Optionally sets the memory hook functions to allow callers to control route memory 
/// allocations to their own memory manager. This must be called before PFInitialize() 
/// and can not be called again once memory hooks have been set.
///
/// This method allows the application to install custom memory allocation routines in order 
/// to service all requests for new memory buffers instead of using default allocation routines.
/// </summary>
/// <param name="hooks">Custom memory hooks to be used by the SDK.</param>
/// <returns>HRESULT return code for this API operation.</returns>
/// <remarks>
/// Must be called before PFInitialize.
/// </remarks>
bool PLAYFABCORE_API FPFMemSetFunctions(
	_In_ TSharedPtr<FPFMemoryHooks> hooks
) noexcept;

/// <summary>
/// Gets the memory hook functions to allow callers to control route memory allocations to their 
/// own memory manager. This method allows the application get the default memory allocation routines.
/// This can be used along with PFMemSetFunctions() to monitor all memory allocations.
/// </summary>
/// <param name="hooks">Struct to be populated with the current memory hooks. Defaults will be returned
/// if custom hooks weren't previously set.</param>
/// <returns>HRESULT return code for this API operation.</returns>
bool PLAYFABCORE_API FPFMemGetFunctions(
	_Out_ TSharedPtr<FPFMemoryHooks> hooks
) noexcept;

#if HC_PLATFORM != HC_PLATFORM_GDK
/// <summary>
/// Determines if custom memory functions are being used.
/// </summary>
/// <param name="isUsingCustomMemoryFunctions">Indicates if custom memory functions are in use.</param>
/// <returns>HRESULT return code for this API operation.</returns>
bool PLAYFABCORE_API FPFMemIsUsingCustomMemoryFunctions(
	_Out_ TSharedPtr<bool> isUsingCustomMemoryFunctions
) noexcept;
#endif

//-----------------------------------------------------------------------------
// Storage. Required on some platforms, see online documentation for more details.
//-----------------------------------------------------------------------------

/// <summary>
/// Sets the storage event handlers. If custom storage handlers are not set, a default implementation
/// based on cstdio and std::fstream objects will be used. 
/// </summary>
/// <param name="hooks">Custom local storage hooks to be used by the SDK.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// Must be called before PFInitialize.
/// </remarks>
bool PLAYFABCORE_API FPFPlatformLocalStorageSetHandlers(
	_In_ TSharedPtr<FPFLocalStorageHooks> hooks
) noexcept;
}
