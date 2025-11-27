#include "PFTrace.h"

bool PLAYFABCORE_API FPFTraceEnableTraceToFile(
	_In_z_ FString traceFileDirectory
) noexcept
{
	// Fix dangling pointer by managing StringCast lifetime properly
	auto convertedString = StringCast<ANSICHAR>(*traceFileDirectory);
	const char* traceFileDirectoryCStr = convertedString.Get();

	HRESULT hr = PFTraceEnableTraceToFile(traceFileDirectoryCStr);

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}
