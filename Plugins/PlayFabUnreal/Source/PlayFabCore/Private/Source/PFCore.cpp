#include "PFCore.h"

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABCORE_API FPFInitialize() noexcept
{
	HRESULT hr = PFInitialize(FXAsyncTaskQueue::GetGenericQueue());

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_ANDROID
bool PLAYFABCORE_API FPFInitialize(
	_In_ JavaVM* javaVm,
	_In_ jobject applicationContext
) noexcept
{
	HRESULT hr = PFInitialize(FXAsyncTaskQueue::GetGenericQueue(), javaVm, applicationContext);

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}
#endif

bool PLAYFABCORE_API FPFUninitializeAsync(
	_Inout_ FOnPFUninitializeDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFUninitializeAsyncTask>(delegate);
	return true;
}
