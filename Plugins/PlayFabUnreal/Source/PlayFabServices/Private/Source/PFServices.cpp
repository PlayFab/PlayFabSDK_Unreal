#include "PFServices.h"
#include "PFCore.h"
#include "PFInitRefCount.h"
#include "Logging.h"
#include "Templates/Function.h"

namespace
{
	FPFInitRefCount& GetServicesInitRefCount()
	{
		static FPFInitRefCount RefCount(TEXT("PlayFab Services"));
		return RefCount;
	}

	bool PFServicesInitializeRefCounted(TFunctionRef<HRESULT()> initFunction)
	{
		return GetServicesInitRefCount().Acquire([&initFunction]()
			{
				HRESULT hr = initFunction();

				if (FAILED(hr))
				{
					UE_LOG(LogPlayFabUnreal, Error, TEXT("FPFServicesInitialize: PFServicesInitialize failed: 0x%08X"), hr);
					return false;
				}

				return true;
			});
	}
}

#if HC_PLATFORM_IS_PLAYSTATION
bool PLAYFABSERVICES_API FPFServicesInitialize() noexcept
{
	return PFServicesInitializeRefCounted([]() { return PFServicesInitialize(); });
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFServicesInitialize() noexcept
{
	return PFServicesInitializeRefCounted([]() { return PFServicesInitialize(FXAsyncTaskQueue::GetGenericQueue()); });
}
#endif

#if HC_PLATFORM == HC_PLATFORM_ANDROID
bool PLAYFABSERVICES_API FPFServicesInitialize(
	_In_ HCInitArgs* initArgs
) noexcept
{
	return PFServicesInitializeRefCounted([initArgs]() { return PFServicesInitialize(FXAsyncTaskQueue::GetGenericQueue(), initArgs); });
}
#endif

bool PLAYFABSERVICES_API FPFServicesUninitializeAsync(
	_Inout_ FOnPFServicesUninitializeDelegate delegate
) noexcept
{
	return GetServicesInitRefCount().ReleaseAsync(
		[&delegate]()
		{
			FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
			taskManager->AddTask<FPFServicesUninitializeAsyncTask>(GetServicesInitRefCount(), delegate);
		},
		[&delegate](bool bSucceeded) { delegate.ExecuteIfBound(bSucceeded); });
}