#include "PFCoreAsyncTasks.h"

FPFUninitializeAsyncTask::FPFUninitializeAsyncTask(
	FOnPFUninitializeDelegate delegate)
	: FXAsyncTask(TEXT("FPFUninitializeAsyncTask")),
	delegate(delegate)
{
}

void FPFUninitializeAsyncTask::DoWork()
{
	HRESULT hr = PFUninitializeAsync(*mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(false);
	}
}

void FPFUninitializeAsyncTask::ProcessResults()
{
	delegate.ExecuteIfBound(true);
}
