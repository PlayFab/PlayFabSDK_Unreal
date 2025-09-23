#include "PFEntity.h"

bool PLAYFABCORE_API FPFEntityDuplicateHandle(
	_In_ FPFEntityHandle entityHandle,
	_Out_ FPFEntityHandle& duplicatedEntityHandle
) noexcept
{
	RETURN_FALSE_IF_NULL(entityHandle);

	PFEntityHandle duplicatedHandle;
	HRESULT hr = PFEntityDuplicateHandle(entityHandle.Get(), &duplicatedHandle);
	*reinterpret_cast<PFEntityHandle*>(&duplicatedEntityHandle) = duplicatedHandle;

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool PLAYFABCORE_API FPFEntityCloseHandle(
	_In_ FPFEntityHandle entityHandle
) noexcept
{
	RETURN_FALSE_IF_NULL(entityHandle);

	PFEntityCloseHandle(entityHandle.Get());

	return true;
}

bool PLAYFABCORE_API FPFEntityGetEntityTokenAsync(
	_In_ FPFEntityHandle entityHandle,
	_Inout_ FOnEntityGetEntityTokenDelegate delegate
) noexcept
{
	RETURN_FALSE_IF_NULL(entityHandle);

	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFEntityGetEntityTokenAsyncTask>(entityHandle, delegate);
	return true;
}

#if HC_PLATFORM == HC_PLATFORM_MAC || HC_PLATFORM == HC_PLATFORM_LINUX
bool PLAYFABCORE_API FPFEntityGetSecretKeySize(
	_In_  FPFEntityHandle handle,
	_Out_ TSharedPtr<SIZE_T> secretKeySize
) noexcept
{
	RETURN_FALSE_IF_NULL(handle);

	HRESULT hr = PFEntityGetSecretKeySize(handle, secretKeySize.Get());

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool PLAYFABCORE_API FPFEntityGetSecretKey(
	_In_ FPFEntityHandle handle,
	_In_ SIZE_T secretKeySize,
	_Out_writes_(secretKeySize) FString secretKey,
	_Out_opt_ TSharedPtr<SIZE_T> secretKeyUsed
) noexcept
{
	RETURN_FALSE_IF_NULL(handle);

	const char* converted = StringCast<ANSICHAR>(*secretKey).Get();
	char* secretKeyBuffer = new char[secretKeySize];
	FCStringAnsi::Strncpy(secretKeyBuffer, converted, secretKeySize);

	HRESULT hr = PFEntityGetSecretKey(handle, secretKeySize, secretKeyBuffer, secretKeyUsed.Get());

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}
#endif

bool PLAYFABCORE_API FPFEntityGetEntityKeySize(
	_In_ FPFEntityHandle entityHandle,
	_Out_ TSharedPtr<SIZE_T> bufferSize
) noexcept
{
	RETURN_FALSE_IF_NULL(entityHandle);

	HRESULT hr = PFEntityGetEntityKeySize(entityHandle.Get(), bufferSize.Get());

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool PLAYFABCORE_API FPFEntityGetEntityKey(
	_In_ FPFEntityHandle entityHandle,
	_In_ SIZE_T bufferSize,
	_Out_writes_bytes_to_(bufferSize, *bufferUsed) TSharedPtr<void> buffer,
	_Outptr_ TSharedPtr<const FPFEntityKey>& entityKey,
	_Out_opt_ TSharedPtr<SIZE_T> bufferUsed
) noexcept
{
	RETURN_FALSE_IF_NULL(entityHandle);

	PFEntityKey const* pfEntityKey{};

	HRESULT hr = PFEntityGetEntityKey(entityHandle.Get(), bufferSize, buffer.Get(), &pfEntityKey, bufferUsed.Get());

	if (FAILED(hr))
	{
		return false;
	}

	entityKey = ConvertEntityKeyToUnreal(pfEntityKey);

	return true;
}

bool PLAYFABCORE_API FPFEntityIsTitlePlayer(
	_In_ FPFEntityHandle entityHandle,
	_Out_ TSharedPtr<bool> isTitlePlayer
) noexcept
{
	RETURN_FALSE_IF_NULL(entityHandle);

	HRESULT hr = PFEntityIsTitlePlayer(entityHandle.Get(), isTitlePlayer.Get());

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool PLAYFABCORE_API FPFEntityGetAPIEndpointSize(
	_In_  FPFEntityHandle entityHandle,
	_Out_ TSharedPtr<SIZE_T> apiEndpointSize
) noexcept
{
	RETURN_FALSE_IF_NULL(entityHandle);

	HRESULT hr = PFEntityGetAPIEndpointSize(entityHandle.Get(), apiEndpointSize.Get());

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool PLAYFABCORE_API FPFEntityGetAPIEndpoint(
	_In_ FPFEntityHandle entityHandle,
	_In_ SIZE_T apiEndpointSize,
	_Out_writes_(apiEndpointSize) FString apiEndpoint,
	_Out_opt_ TSharedPtr<SIZE_T> apiEndpointUsed
) noexcept
{
	RETURN_FALSE_IF_NULL(entityHandle);

	const char* converted = StringCast<ANSICHAR>(*apiEndpoint).Get();
	char* apiEndpointBuffer = new char[apiEndpointSize];
	FCStringAnsi::Strncpy(apiEndpointBuffer, converted, apiEndpointSize);

	HRESULT hr = PFEntityGetAPIEndpoint(entityHandle.Get(), apiEndpointSize, apiEndpointBuffer, apiEndpointUsed.Get());

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

static FPFEntityTokenExpiredDelegate EntityTokenExpiredDelegate;

static void CALLBACK OnPFEntityTokenExpiredEvent(void* context, const PFEntityKey* entityKey)
{
	TSharedPtr<void> contextRef = MakeShareable(context);

	const FPFEntityKey fpfEntityKey = {
		.id = FString(entityKey->id),
		.type = FString(entityKey->type)
	};

	TSharedPtr<const FPFEntityKey> fpfEntityKeyRef = MakeShared<FPFEntityKey>(fpfEntityKey);

	EntityTokenExpiredDelegate.ExecuteIfBound(contextRef, fpfEntityKeyRef);
}

bool PLAYFABCORE_API FPFEntityRegisterTokenExpiredEventHandler(
	_In_opt_ TSharedPtr<void> context,
	_In_ FPFEntityTokenExpiredDelegate delegate,
	_Out_ TSharedPtr<FPFRegistrationToken> token
) noexcept
{
	EntityTokenExpiredDelegate = delegate;

	HRESULT hr = PFEntityRegisterTokenExpiredEventHandler(
		FXAsyncTaskQueue::GetGenericQueue(),
		context.Get(),
		&OnPFEntityTokenExpiredEvent,
		token.Get()
	);

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool PLAYFABCORE_API FPFEntityUnregisterTokenExpiredEventHandler(
	_In_ FPFRegistrationToken token
) noexcept
{
	PFEntityUnregisterTokenExpiredEventHandler(token);

	return true;
}

static FPFEntityTokenRefreshedDelegate EntityTokenRefreshedDelegate;

static void CALLBACK OnPFEntityTokenRefrehedEvent(void* context, const PFEntityKey* entityKey, const PFEntityToken* newToken)
{
	TSharedPtr<void> contextRef = MakeShareable(context);

	const FPFEntityKey fpfEntityKey = {
		.id = UTF8_TO_TCHAR(entityKey->id),
		.type = UTF8_TO_TCHAR(entityKey->type)
	};

	TSharedPtr<const FPFEntityKey> fpfEntityKeyRef = MakeShared<FPFEntityKey>(fpfEntityKey);

	const FPFEntityToken fpfEntityToken = {
		.token = UTF8_TO_TCHAR(newToken->token),
		.expiration = ConvertTimeToUnreal(newToken->expiration)
	};

	TSharedPtr<const FPFEntityToken> fpfEntityTokenRef = MakeShared<FPFEntityToken>(fpfEntityToken);

	EntityTokenRefreshedDelegate.ExecuteIfBound(contextRef, fpfEntityKeyRef, fpfEntityTokenRef);
}

bool PLAYFABCORE_API FPFEntityRegisterTokenRefreshedEventHandler(
	_In_opt_ TSharedPtr<void> context,
	_In_ FPFEntityTokenRefreshedDelegate delegate,
	_Out_ TSharedPtr<FPFRegistrationToken> token
) noexcept
{
	EntityTokenRefreshedDelegate = delegate;

	HRESULT hr = PFEntityRegisterTokenRefreshedEventHandler(
		FXAsyncTaskQueue::GetGenericQueue(),
		context.Get(),
		&OnPFEntityTokenRefrehedEvent,
		token.Get()
	);

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool PLAYFABCORE_API FPFEntityUnregisterTokenRefreshedEventHandler(
	_In_ FPFRegistrationToken token
) noexcept
{
	PFEntityUnregisterTokenRefreshedEventHandler(token);

	return true;
}