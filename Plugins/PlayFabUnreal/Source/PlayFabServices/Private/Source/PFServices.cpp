#include "PFServices.h"

#if HC_PLATFORM_IS_PLAYSTATION
bool PLAYFABSERVICES_API FPFServicesInitialize() noexcept
{
	HRESULT hr = PFServicesInitialize();

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFServicesInitialize() noexcept
{
	HRESULT hr = PFServicesInitialize(FXAsyncTaskQueue::GetGenericQueue());

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_ANDROID
bool PLAYFABSERVICES_API FPFServicesInitialize(
	_In_ HCInitArgs* initArgs
) noexcept
{
	HRESULT hr = PFServicesInitialize(FXAsyncTaskQueue::GetGenericQueue(), initArgs);

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}
#endif

bool PLAYFABSERVICES_API FPFServicesUninitializeAsync(
	_Inout_ FOnPFServicesUninitializeDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFServicesUninitializeAsyncTask>(delegate);
	return true;
}