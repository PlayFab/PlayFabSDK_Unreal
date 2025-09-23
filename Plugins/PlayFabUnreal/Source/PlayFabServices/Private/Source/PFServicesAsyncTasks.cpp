#include "PFServicesAsyncTasks.h"

FPFServicesUninitializeAsyncTask::FPFServicesUninitializeAsyncTask(
	FOnPFServicesUninitializeDelegate delegate)
	: FXAsyncTask(TEXT("FPFServicesUninitializeAsyncTask")),
	delegate(delegate)
{
}

void FPFServicesUninitializeAsyncTask::DoWork()
{
	HRESULT hr = PFServicesUninitializeAsync(*mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(false);
	}
}

void FPFServicesUninitializeAsyncTask::ProcessResults()
{
	delegate.ExecuteIfBound(true);
}
