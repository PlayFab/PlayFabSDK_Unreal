#pragma once

//-----------------------------------------------------------------------------
// Hooks for platform specific behavior
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Memory (optional on all platforms)
//-----------------------------------------------------------------------------


/// <summary>
/// A callback invoked every time a new memory buffer must be dynamically allocated by the library.
/// This callback is optionally installed by calling PFMemSetFunctions()
/// 
/// The callback must allocate and return a pointer to a contiguous block of memory of the 
/// specified size that will remain valid until the app's corresponding PFMemFreeFunction 
/// callback is invoked to release it.
/// 
/// Every non-null pointer returned by this method will be subsequently passed to the corresponding
/// PFMemFreeFunction callback once the memory is no longer needed.
/// </summary>
/// <returns>A pointer to an allocated block of memory of the specified size, or a null 
/// pointer if allocation failed.</returns>
/// <param name="size">The size of the allocation to be made. This value will never be zero.</param>
/// <param name="memoryTypeId">An opaque identifier representing the internal category of
/// memory being allocated. This value should be ignored.</param>
DECLARE_DELEGATE_TwoParams(FPFMemAllocFunctionDelegate, SIZE_T, uint32_t);

/// <summary>
/// A callback invoked every time a previously allocated memory buffer is no longer needed by 
/// the library and can be freed. This callback is optionally installed by calling PFMemSetFunctions()
///
/// The callback is invoked whenever the library has finished using a memory buffer previously 
/// returned by the app's corresponding PFMemAllocFunction such that the application can free the
/// memory buffer.
/// </summary>
/// <param name="pointer">The pointer to the memory buffer previously allocated. This value will
/// never be a null pointer.</param>
/// <param name="memoryTypeId">An opaque identifier representing the internal category of
/// memory being allocated. This value should be ignored.</param>
DECLARE_DELEGATE_TwoParams(FPFMemFreeFunctionDelegate, TSharedPtr<void> pointer, uint32_t);

/// <summary>
/// Struct encapsulating memory hooks.
/// </summary>
/// <remarks>
/// Both hooks must be set at the same time.
/// </remarks>
typedef struct FPFMemoryHooks
{
	/// <summary>
	/// Custom allocation hook.
	/// </summary>
	FPFMemAllocFunctionDelegate alloc;

	/// <summary>
	/// Custom free hook.
	/// </summary>
	FPFMemFreeFunctionDelegate free;
} FPFMemoryHooks;

//-----------------------------------------------------------------------------
// Storage. Required on some platforms, see online documentation for more details.
//-----------------------------------------------------------------------------

/// <summary>
/// Read from storage event handler. Should implement an <see cref="XAsyncProvider"/>.
/// </summary>
/// <param name="context">Optional pointer to data used by the event handler.</param>
/// <param name="key">Identifies the data being written. Typically a filepath.</param>
/// <param name="async">XAsyncBlock for the operation.</param>
/// <remarks>
/// This event handler will be invoked when PlayFab needs to read data from storage.
/// The XAsyncBlock should be completed with data size (in bytes) that was read.
/// All arguments are owned by the SDK and are guaranteed to be valid until the operation is complete (except context).
/// </remarks>
DECLARE_DELEGATE_TwoParams(FPFPlatformLocalStorageReadDelegate, TSharedPtr<void>, FString);

/// <summary>
/// Write to storage event handler. Should implement an <see cref="XAsyncProvider"/>.
/// </summary>
/// <param name="context">Optional pointer to data used by the event handler.</param>
/// <param name="key">Identifies the data being written. Typically a filepath.</param>
/// <param name="dataSize">The size (in bytes) of the data.</param>
/// <param name="data">The data to write.</param>
/// <param name="async">XAsyncBlock for the operation.</param>
/// <remarks>
/// This event handler will be invoked when PlayFab needs to write data to storage.
/// All arguments are owned by the SDK and are guaranteed to be valid until the operation is complete (except context).
/// </remarks>
DECLARE_DELEGATE_FourParams(FPFPlatformLocalStorageWriteDelegate, TSharedPtr<void>, FString, SIZE_T, TSharedPtr<void const>);

/// <summary>
/// Write from storage event handler. Should implement an <see cref="XAsyncProvider"/>.
/// </summary>
/// <param name="context">Optional pointer to data used by the event handler.</param>
/// <param name="key">Identifies the data being written. Typically a filepath.</param>
/// <param name="async">XAsyncBlock for the operation.</param>
/// <remarks>
/// This event handler will be invoked when PlayFab needs to clear data from storage.
/// All arguments are owned by the SDK and are guaranteed to be valid until the operation is complete (except context).
/// </remarks>
DECLARE_DELEGATE_TwoParams(FPFPlatformLocalStorageClearDelegate, TSharedPtr<void>, FString);

/// <summary>
/// Struct encapsulating the storage hooks.
/// </summary>
/// <remarks>
/// All 3 handlers must be set at the same time.
/// </remarks>
typedef struct FPFLocalStorageHooks
{
	/// <summary>
	/// Custom read hook.
	/// </summary>
	FPFPlatformLocalStorageReadDelegate read;

	/// <summary>
	/// Custom write hook.
	/// </summary>
	FPFPlatformLocalStorageWriteDelegate write;

	/// <summary>
	/// Custom clear hook.
	/// </summary>
	FPFPlatformLocalStorageClearDelegate clear;

	/// <summary>
	/// (Optional) Client context that will be passed to storage hooks.
	/// </summary>
	_Maybenull_ TSharedPtr<void> context;
} FPFLocalStorageHooks;