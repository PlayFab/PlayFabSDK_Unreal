#include "PFServiceConfig.h"

bool PLAYFABCORE_API FPFServiceConfigCreateHandle(
	_In_z_ FString apiEndpoint,
	_In_z_ FString playFabTitleId,
	_Out_ FPFServiceConfigHandle& serviceConfigHandle
) noexcept
{
	FTCHARToUTF8 ConvertedEndpoint(*apiEndpoint);
	char* apiEndpointCStr = new char[ConvertedEndpoint.Length() + 1];
	FMemory::Memcpy(apiEndpointCStr, ConvertedEndpoint.Get(), ConvertedEndpoint.Length());
	apiEndpointCStr[ConvertedEndpoint.Length()] = '\0';

	FTCHARToUTF8 ConvertedTitleId(*playFabTitleId);
	char* titleIdCStr = new char[ConvertedTitleId.Length() + 1];
	FMemory::Memcpy(titleIdCStr, ConvertedTitleId.Get(), ConvertedTitleId.Length());
	titleIdCStr[ConvertedTitleId.Length()] = '\0';

	PFServiceConfigHandle handle;
	RETURN_FALSE_IF_FAILED(PFServiceConfigCreateHandle(apiEndpointCStr, titleIdCStr, &handle));
	*reinterpret_cast<PFServiceConfigHandle*>(&serviceConfigHandle) = handle;

	return true;
}

bool PLAYFABCORE_API FPFServiceConfigDuplicateHandle(
	FPFServiceConfigHandle handle,
	FPFServiceConfigHandle& duplicatedHandle
) noexcept
{
	RETURN_FALSE_IF_NULL(handle);

	PFServiceConfigHandle configHandle;
	RETURN_FALSE_IF_FAILED(PFServiceConfigDuplicateHandle(handle.Get(), &configHandle));
	*reinterpret_cast<PFServiceConfigHandle*>(&duplicatedHandle) = configHandle;

	return true;
}

bool PLAYFABCORE_API FPFServiceConfigCloseHandle(
	FPFServiceConfigHandle handle
) noexcept
{
	RETURN_FALSE_IF_NULL(handle);

	PFServiceConfigCloseHandle(handle.Get());

	return true;
}

bool PLAYFABCORE_API FPFServiceConfigGetAPIEndpointSize(
	_In_  FPFServiceConfigHandle handle,
	_Out_ TSharedPtr<SIZE_T> apiEndpointSize
) noexcept
{
	RETURN_FALSE_IF_NULL(handle);

	size_t* apiEndpointSizePtr = apiEndpointSize.Get();

	RETURN_FALSE_IF_FAILED(PFServiceConfigGetAPIEndpointSize(handle.Get(), apiEndpointSizePtr));

	return true;
}

bool PLAYFABCORE_API FPFServiceConfigGetAPIEndpoint(
	_In_ FPFServiceConfigHandle handle,
	_In_ SIZE_T apiEndpointSize,
	_Out_writes_(apiEndpointSize) FString apiEndpoint,
	_Out_opt_ TSharedPtr<SIZE_T> apiEndpointUsed
) noexcept
{
	RETURN_FALSE_IF_NULL(handle);
	RETURN_FALSE_IF_NULL(apiEndpointSize);

	const char* converted = StringCast<ANSICHAR>(*apiEndpoint).Get();
	char* apiEndpointCStr = new char[apiEndpointSize];
	FCStringAnsi::Strncpy(apiEndpointCStr, converted, apiEndpointSize);

	size_t* apiEndpointUsedPtr = apiEndpointUsed.Get();

	RETURN_FALSE_IF_FAILED(PFServiceConfigGetAPIEndpoint(handle.Get(), apiEndpointSize, apiEndpointCStr, apiEndpointUsedPtr));

	return true;
}

bool PLAYFABCORE_API FPFServiceConfigGetTitleIdSize(
	_In_  FPFServiceConfigHandle handle,
	_Out_ TSharedPtr<SIZE_T> titleIdSize
) noexcept
{
	RETURN_FALSE_IF_NULL(handle);

	size_t* titleIdSizePtr = titleIdSize.Get();

	RETURN_FALSE_IF_FAILED(PFServiceConfigGetTitleIdSize(handle.Get(), titleIdSizePtr));

	return true;
}

bool PLAYFABCORE_API FPFServiceConfigGetTitleId(
	_In_ FPFServiceConfigHandle handle,
	_In_ SIZE_T titleIdSize,
	_Out_writes_(titleIdSize) FString titleId,
	_Out_opt_ TSharedPtr<SIZE_T> titleIdUsed
) noexcept
{
	RETURN_FALSE_IF_NULL(handle);

	const char* converted = StringCast<ANSICHAR>(*titleId).Get();
	char* titleIdCStr = new char[titleIdSize];
	FCStringAnsi::Strncpy(titleIdCStr, converted, titleIdSize);

	size_t* titleIdUsedPtr = titleIdUsed.Get();

	RETURN_FALSE_IF_FAILED(PFServiceConfigGetTitleId(handle.Get(), titleIdSize, titleIdCStr, titleIdUsedPtr));

	return true;
}
