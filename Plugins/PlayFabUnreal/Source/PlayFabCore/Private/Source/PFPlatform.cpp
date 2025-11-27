#include "PFPlatform.h"

static FPFMemAllocFunctionDelegate MemAllocFunctionDelegate;

static void* CALLBACK OnMemAllocFunctionEvent(size_t size, uint32_t memoryTypeId)
{
	MemAllocFunctionDelegate.ExecuteIfBound(size, memoryTypeId);

	return nullptr;
}

static FPFMemFreeFunctionDelegate MemFreeFunctionDelegate;

static void CALLBACK OnMemFreeFunctionEvent(void* pointer, uint32_t memoryTypeId)
{
	TSharedPtr<void> pointerRef = MakeShareable(pointer, [](void*) {});

	MemFreeFunctionDelegate.ExecuteIfBound(pointerRef, memoryTypeId);
}

bool PLAYFABCORE_API FPFMemSetFunctions(
	_In_ TSharedPtr<FPFMemoryHooks> hooks
) noexcept
{
	PFMemoryHooks playFabHooks{ OnMemAllocFunctionEvent, OnMemFreeFunctionEvent };

	HRESULT hr = PFMemSetFunctions(&playFabHooks);

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool PLAYFABCORE_API FPFMemGetFunctions(
	_Out_ PFMemoryHooks* hooks
) noexcept
{
	HRESULT hr = PFMemGetFunctions(hooks);

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

#if HC_PLATFORM != HC_PLATFORM_GDK
bool PLAYFABCORE_API FPFMemIsUsingCustomMemoryFunctions(
	_Out_ TSharedPtr<bool> isUsingCustomMemoryFunctions
) noexcept
{
	bool* isUsingCustomMemoryFunctionsPtr = isUsingCustomMemoryFunctions.Get();

	HRESULT hr = PFMemIsUsingCustomMemoryFunctions(isUsingCustomMemoryFunctionsPtr);

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}
#endif

static FPFPlatformLocalStorageReadDelegate PlatformLocalStorageReadDelegate;

static HRESULT CALLBACK OnPlatformLocalStorageReadEvent(void* context, const char* key, XAsyncBlock* async)
{
	TSharedPtr<void> contextPtr = MakeShareable(context, [](void*) {});
	FString keyStr = UTF8_TO_TCHAR(key);

	PlatformLocalStorageReadDelegate.ExecuteIfBound(contextPtr, keyStr);

	return S_OK;
}

static FPFPlatformLocalStorageWriteDelegate PlatformLocalStorageWriteDelegate;

static HRESULT CALLBACK OnPlatformLocalStorageWriteEvent(void* context, const char* key, size_t dataSize, void const* data, XAsyncBlock* async)
{
	TSharedPtr<void> contextRef = MakeShareable(context, [](void*) {});
	FString keyStr = UTF8_TO_TCHAR(key);
	TSharedPtr<void const> dataRef = MakeShareable(data, [](const void*) {});

	PlatformLocalStorageWriteDelegate.ExecuteIfBound(contextRef, keyStr, dataSize, dataRef);

	return S_OK;
}

static FPFPlatformLocalStorageClearDelegate PlatformLocalStorageClearDelegate;

static HRESULT CALLBACK OnPlatformLocalStorageClearEvent(void* context, const char* key, XAsyncBlock* async)
{
	TSharedPtr<void> contextPtr = MakeShareable(context, [](void*) {});
	FString keyStr = UTF8_TO_TCHAR(key);

	PlatformLocalStorageClearDelegate.ExecuteIfBound(contextPtr, keyStr);

	return S_OK;
}

bool PLAYFABCORE_API FPFPlatformLocalStorageSetHandlers(
	_In_ TSharedPtr<FPFLocalStorageHooks> hooks
) noexcept
{
	PlatformLocalStorageReadDelegate = hooks->read;
	PlatformLocalStorageWriteDelegate = hooks->write;
	PlatformLocalStorageClearDelegate = hooks->clear;

	PFLocalStorageHooks playFabHooks{
		FXAsyncTaskQueue::GetGenericQueue(),
		&OnPlatformLocalStorageReadEvent,
		&OnPlatformLocalStorageWriteEvent,
		&OnPlatformLocalStorageClearEvent,
		hooks->context.Get()
	};

	HRESULT hr = PFPlatformLocalStorageSetHandlers(&playFabHooks);

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}
