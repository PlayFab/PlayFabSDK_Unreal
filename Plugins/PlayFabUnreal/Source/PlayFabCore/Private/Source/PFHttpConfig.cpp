#include "PFHttpConfig.h"

bool PLAYFABCORE_API FPFSetHttpRetrySettings(
	_In_ const TSharedPtr<FPFHttpRetrySettings>& settings
) noexcept
{
	const FPFHttpRetrySettings* fpfSettings = settings.Get();

	const PFHttpRetrySettings pfSettings = {
		.allowRetry = fpfSettings->allowRetry,
		.minimumRetryDelayInSeconds = fpfSettings->minimumRetryDelayInSeconds,
		.timeoutWindowInSeconds = fpfSettings->timeoutWindowInSeconds
	};

	HRESULT hr = PFSetHttpRetrySettings(&pfSettings);

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool PLAYFABCORE_API FPFGetHttpRetrySettings(
	_Out_ TSharedPtr<FPFHttpRetrySettings> settings
) noexcept
{
	PFHttpRetrySettings pfSettings;

	HRESULT hr = PFGetHttpRetrySettings(&pfSettings);

	if (FAILED(hr))
	{
		return false;
	}

	const FPFHttpRetrySettings fpfSettings = {
		.allowRetry = pfSettings.allowRetry,
		.minimumRetryDelayInSeconds = pfSettings.minimumRetryDelayInSeconds,
		.timeoutWindowInSeconds = pfSettings.timeoutWindowInSeconds
	};

	settings = MakeShared<FPFHttpRetrySettings>(fpfSettings);

	return true;
}

#if HC_PLATFORM != HC_PLATFORM_GDK
bool PLAYFABCORE_API FPFSetHttpSettings(
	_In_ const TSharedPtr<FPFHttpSettings>& settings
) noexcept
{
	const FPFHttpSettings* fpfSettings = settings.Get();

	const PFHttpSettings pfSettings = {
		.requestResponseCompression = fpfSettings->requestResponseCompression
	};

	HRESULT hr = PFSetHttpSettings(&pfSettings);

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool PLAYFABCORE_API FPFGetHttpSettings(
	_Out_ TSharedPtr<FPFHttpSettings> settings
) noexcept
{
	PFHttpSettings pfSettings;

	HRESULT hr = PFGetHttpSettings(&pfSettings);

	if (FAILED(hr))
	{
		return false;
	}

	const FPFHttpSettings fpfSettings = {
		.requestResponseCompression = pfSettings.requestResponseCompression
	};

	settings = MakeShared<FPFHttpSettings>(fpfSettings);

	return true;
}
#endif