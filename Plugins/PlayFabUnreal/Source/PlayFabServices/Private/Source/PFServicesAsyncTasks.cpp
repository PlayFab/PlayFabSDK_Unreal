#include "PFServicesAsyncTasks.h"
#include "Logging.h"

FPFServicesUninitializeAsyncTask::FPFServicesUninitializeAsyncTask(
	FPFInitRefCount& refCount,
	FOnPFServicesUninitializeDelegate delegate)
	: FXAsyncTask(TEXT("FPFServicesUninitializeAsyncTask")),
	refCount(&refCount),
	delegate(delegate)
{
}

void FPFServicesUninitializeAsyncTask::DoWork()
{
	HRESULT hr = PFServicesUninitializeAsync(*mAsyncBlock);

	if (FAILED(hr))
	{
		CompleteWithResult(hr);
	}
}

void FPFServicesUninitializeAsyncTask::ProcessResults()
{
	CompleteWithResult(mAsyncBlock->GetStatus());
}

void FPFServicesUninitializeAsyncTask::CompleteWithResult(HRESULT hr)
{
	const bool bSucceeded = SUCCEEDED(hr) || hr == E_PF_SERVICES_NOT_INITIALIZED;

	if (!bSucceeded)
	{
		refCount->AbortRelease();
		UE_LOG(LogPlayFabUnreal, Warning, TEXT("FPFServicesUninitializeAsyncTask: PFServicesUninitializeAsync failed: 0x%08X"), hr);
	}

	delegate.ExecuteIfBound(bSucceeded);
}
