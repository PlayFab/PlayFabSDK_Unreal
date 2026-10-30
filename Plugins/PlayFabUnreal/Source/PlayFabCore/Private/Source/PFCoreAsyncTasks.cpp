#include "PFCoreAsyncTasks.h"

FPFUninitializeAsyncTask::FPFUninitializeAsyncTask(
	FPFInitRefCount& refCount,
	FOnPFUninitializeDelegate delegate)
	: FXAsyncTask(TEXT("FPFUninitializeAsyncTask")),
	refCount(&refCount),
	delegate(delegate)
{
}

void FPFUninitializeAsyncTask::DoWork()
{
	HRESULT hr = PFUninitializeAsync(*mAsyncBlock);

	if (FAILED(hr))
	{
		CompleteWithResult(hr);
	}
}

void FPFUninitializeAsyncTask::ProcessResults()
{
	CompleteWithResult(mAsyncBlock->GetStatus());
}

void FPFUninitializeAsyncTask::CompleteWithResult(HRESULT hr)
{
	const bool bSucceeded = SUCCEEDED(hr) || hr == E_PF_CORE_NOT_INITIALIZED;

	if (!bSucceeded)
	{
		refCount->AbortRelease();
		UE_LOG(LogPlayFabUnreal, Warning, TEXT("FPFUninitializeAsyncTask: PFUninitializeAsync failed: 0x%08X"), hr);
	}

	delegate.ExecuteIfBound(bSucceeded);
}
