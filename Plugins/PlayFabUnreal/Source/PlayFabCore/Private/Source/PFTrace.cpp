#include "PFTrace.h"

bool PLAYFABCORE_API FPFTraceEnableTraceToFile(
	_In_z_ FString traceFileDirectory
) noexcept
{
	const char* traceFileDirectoryCStr = StringCast<ANSICHAR>(*traceFileDirectory).Get();

	HRESULT hr = PFTraceEnableTraceToFile(traceFileDirectoryCStr);

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}
