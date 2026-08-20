#include "PFEntityAsyncTasks.h"
#include "PFCoreTypeConverters.h"

FPFEntityGetEntityTokenAsyncTask::FPFEntityGetEntityTokenAsyncTask(
	FPFEntityHandle entityHandle,
	FOnEntityGetEntityTokenDelegate delegate)
	: FXAsyncTask(TEXT("FPFEntityGetEntityTokenAsyncTask")),
	entityHandle(entityHandle),
	delegate(delegate)
{
}

void FPFEntityGetEntityTokenAsyncTask::DoWork()
{
	HRESULT hr = PFEntityGetEntityTokenAsync(entityHandle.Get(), *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(false, nullptr);
	}
}

void FPFEntityGetEntityTokenAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	size_t resultSize = 0;

	HRESULT hr = PFEntityGetEntityTokenResultSize(*mAsyncBlock, &resultSize);

	if (SUCCEEDED(hr))
	{
		bufferArray.SetNumUninitialized(resultSize);

		PFEntityToken const* result;
		hr = PFEntityGetEntityTokenResult(*mAsyncBlock, resultSize, bufferArray.GetData(), &result, nullptr);

		if (SUCCEEDED(hr))
		{
			FPFEntityToken entityToken{
				UTF8_TO_TCHAR(result->token),
				ConvertTimeToUnreal(result->expiration)
			};
			delegate.ExecuteIfBound(true, &entityToken);
		}
		else
		{
			delegate.ExecuteIfBound(false, nullptr);
		}
	}
	else
	{
		delegate.ExecuteIfBound(false, nullptr);
	}
}
