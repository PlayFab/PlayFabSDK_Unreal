#include "PFCore.h"
#include "PFInitRefCount.h"
#include "Logging.h"
#include "Templates/Function.h"

namespace
{
	FPFInitRefCount& GetCoreInitRefCount()
	{
		static FPFInitRefCount RefCount(TEXT("PlayFab Core"));
		return RefCount;
	}

	bool PFInitializeRefCounted(TFunctionRef<HRESULT()> initFunction)
	{
		return GetCoreInitRefCount().Acquire([&initFunction]()
			{
				HRESULT hr = initFunction();

				if (FAILED(hr))
				{
					UE_LOG(LogPlayFabUnreal, Error, TEXT("FPFInitialize: PFInitialize failed: 0x%08X"), hr);
					return false;
				}

				return true;
			});
	}
}

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABCORE_API FPFInitialize() noexcept
{
	return PFInitializeRefCounted([]() { return PFInitialize(FXAsyncTaskQueue::GetGenericQueue()); });
}
#endif

#if HC_PLATFORM == HC_PLATFORM_ANDROID
bool PLAYFABCORE_API FPFInitialize(
	_In_ JavaVM* javaVm,
	_In_ jobject applicationContext
) noexcept
{
	return PFInitializeRefCounted([javaVm, applicationContext]() { return PFInitialize(FXAsyncTaskQueue::GetGenericQueue(), javaVm, applicationContext); });
}
#endif

bool PLAYFABCORE_API FPFUninitializeAsync(
	_Inout_ FOnPFUninitializeDelegate delegate
) noexcept
{
	return GetCoreInitRefCount().ReleaseAsync(
		[&delegate]()
		{
			FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
			taskManager->AddTask<FPFUninitializeAsyncTask>(GetCoreInitRefCount(), delegate);
		},
		[&delegate](bool bSucceeded) { delegate.ExecuteIfBound(bSucceeded); });
}

bool PLAYFABCORE_API FPFUninitialize() noexcept
{
	return GetCoreInitRefCount().Release([]()
		{
			HRESULT hr = LocalTask(
				[](XAsyncBlock* asyncBlock) { return PFUninitializeAsync(asyncBlock); }
			);

			if (FAILED(hr) && hr != E_PF_CORE_NOT_INITIALIZED)
			{
				UE_LOG(LogPlayFabUnreal, Warning, TEXT("FPFUninitialize: PFUninitializeAsync failed: 0x%08X"), hr);
				return false;
			}

			return true;
		});
}
