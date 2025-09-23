// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFAuthenticationAsyncTasks.h"

#if 0

FPFAuthenticationLoginWithAndroidDeviceIDAsyncTask::FPFAuthenticationLoginWithAndroidDeviceIDAsyncTask(
	FPFServiceConfigHandle serviceConfigHandle,
	const FPFAuthenticationLoginWithAndroidDeviceIDRequest request,
	FOnPFAuthenticationLoginCompleteDelegate delegate)
	: FXAsyncTask(TEXT("FPFLoginWithAndroidDeviceIDAsyncTask")),
	serviceConfigHandle(serviceConfigHandle),
	request(request),
	delegate(delegate)
{
}

void FPFAuthenticationLoginWithAndroidDeviceIDAsyncTask::DoWork()
{
	const PFAuthenticationLoginWithAndroidDeviceIDRequest RequestType = {
		.androidDevice = ConvertFStringToCharPtr(request.androidDevice),
		.androidDeviceId = ConvertFStringToCharPtr(request.androidDeviceId),
		.createAccount = request.createAccount,
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(request.infoRequestParameters),
		.OS = ConvertFStringToCharPtr(request.OS),
		.playerSecret = ConvertFStringToCharPtr(request.playerSecret)
	};
	HRESULT hr = PFAuthenticationLoginWithAndroidDeviceIDAsync(serviceConfigHandle.Get(), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

void FPFAuthenticationLoginWithAndroidDeviceIDAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	uint64 resultSize = 0;

	HRESULT hr = PFAuthenticationLoginWithAndroidDeviceIDGetResultSize(*mAsyncBlock, &resultSize); 
	
	if (SUCCEEDED(hr))
	{ 
		bufferArray.Reserve(resultSize);

		PFAuthenticationLoginResult const* result;
		PFEntityHandle handle { nullptr };
		hr = PFAuthenticationLoginWithAndroidDeviceIDGetResult(*mAsyncBlock, &handle, resultSize, bufferArray.GetData(), &result, nullptr);

		if (SUCCEEDED(hr))
		{
			TSharedPtr<const FPFAuthenticationLoginResult> ResultType = ConvertLoginResultToUnreal(result);

			FPFEntityHandle* entityHandlePtr = reinterpret_cast<FPFEntityHandle*>(&handle);
			delegate.ExecuteIfBound(ResultType.Get(), entityHandlePtr, true);
		}
		else
		{
			delegate.ExecuteIfBound(nullptr, nullptr, false);	
		}
	}
	else
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

#endif


#if HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC

FPFAuthenticationLoginWithAppleAsyncTask::FPFAuthenticationLoginWithAppleAsyncTask(
	FPFServiceConfigHandle serviceConfigHandle,
	const FPFAuthenticationLoginWithAppleRequest request,
	FOnPFAuthenticationLoginCompleteDelegate delegate)
	: FXAsyncTask(TEXT("FPFLoginWithAppleAsyncTask")),
	serviceConfigHandle(serviceConfigHandle),
	request(request),
	delegate(delegate)
{
}

void FPFAuthenticationLoginWithAppleAsyncTask::DoWork()
{
	const PFAuthenticationLoginWithAppleRequest RequestType = {
		.createAccount = request.createAccount,
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.identityToken = ConvertFStringToCharPtr(request.identityToken),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(request.infoRequestParameters),
		.playerSecret = ConvertFStringToCharPtr(request.playerSecret)
	};
	HRESULT hr = PFAuthenticationLoginWithAppleAsync(serviceConfigHandle.Get(), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

void FPFAuthenticationLoginWithAppleAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	uint64 resultSize = 0;

	HRESULT hr = PFAuthenticationLoginWithAppleGetResultSize(*mAsyncBlock, &resultSize); 
	
	if (SUCCEEDED(hr))
	{ 
		bufferArray.Reserve(resultSize);

		PFAuthenticationLoginResult const* result;
		PFEntityHandle handle { nullptr };
		hr = PFAuthenticationLoginWithAppleGetResult(*mAsyncBlock, &handle, resultSize, bufferArray.GetData(), &result, nullptr);

		if (SUCCEEDED(hr))
		{
			TSharedPtr<const FPFAuthenticationLoginResult> ResultType = ConvertLoginResultToUnreal(result);

			FPFEntityHandle* entityHandlePtr = reinterpret_cast<FPFEntityHandle*>(&handle);
			delegate.ExecuteIfBound(ResultType.Get(), entityHandlePtr, true);
		}
		else
		{
			delegate.ExecuteIfBound(nullptr, nullptr, false);	
		}
	}
	else
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

#endif


#if HC_PLATFORM == HC_PLATFORM_GDK

FPFAuthenticationLoginWithBattleNetAsyncTask::FPFAuthenticationLoginWithBattleNetAsyncTask(
	FPFServiceConfigHandle serviceConfigHandle,
	const FPFAuthenticationLoginWithBattleNetRequest request,
	FOnPFAuthenticationLoginCompleteDelegate delegate)
	: FXAsyncTask(TEXT("FPFLoginWithBattleNetAsyncTask")),
	serviceConfigHandle(serviceConfigHandle),
	request(request),
	delegate(delegate)
{
}

void FPFAuthenticationLoginWithBattleNetAsyncTask::DoWork()
{
	const PFAuthenticationLoginWithBattleNetRequest RequestType = {
		.createAccount = request.createAccount,
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.identityToken = ConvertFStringToCharPtr(request.identityToken),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(request.infoRequestParameters),
		.playerSecret = ConvertFStringToCharPtr(request.playerSecret)
	};
	HRESULT hr = PFAuthenticationLoginWithBattleNetAsync(serviceConfigHandle.Get(), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

void FPFAuthenticationLoginWithBattleNetAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	uint64 resultSize = 0;

	HRESULT hr = PFAuthenticationLoginWithBattleNetGetResultSize(*mAsyncBlock, &resultSize); 
	
	if (SUCCEEDED(hr))
	{ 
		bufferArray.Reserve(resultSize);

		PFAuthenticationLoginResult const* result;
		PFEntityHandle handle { nullptr };
		hr = PFAuthenticationLoginWithBattleNetGetResult(*mAsyncBlock, &handle, resultSize, bufferArray.GetData(), &result, nullptr);

		if (SUCCEEDED(hr))
		{
			TSharedPtr<const FPFAuthenticationLoginResult> ResultType = ConvertLoginResultToUnreal(result);

			FPFEntityHandle* entityHandlePtr = reinterpret_cast<FPFEntityHandle*>(&handle);
			delegate.ExecuteIfBound(ResultType.Get(), entityHandlePtr, true);
		}
		else
		{
			delegate.ExecuteIfBound(nullptr, nullptr, false);	
		}
	}
	else
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

#endif



FPFAuthenticationLoginWithCustomIDAsyncTask::FPFAuthenticationLoginWithCustomIDAsyncTask(
	FPFServiceConfigHandle serviceConfigHandle,
	const FPFAuthenticationLoginWithCustomIDRequest request,
	FOnPFAuthenticationLoginCompleteDelegate delegate)
	: FXAsyncTask(TEXT("FPFLoginWithCustomIDAsyncTask")),
	serviceConfigHandle(serviceConfigHandle),
	request(request),
	delegate(delegate)
{
}

void FPFAuthenticationLoginWithCustomIDAsyncTask::DoWork()
{
	const PFAuthenticationLoginWithCustomIDRequest RequestType = {
		.createAccount = request.createAccount,
		.customId = ConvertFStringToCharPtr(request.customId),
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(request.infoRequestParameters),
		.playerSecret = ConvertFStringToCharPtr(request.playerSecret)
	};
	HRESULT hr = PFAuthenticationLoginWithCustomIDAsync(serviceConfigHandle.Get(), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

void FPFAuthenticationLoginWithCustomIDAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	uint64 resultSize = 0;

	HRESULT hr = PFAuthenticationLoginWithCustomIDGetResultSize(*mAsyncBlock, &resultSize); 
	
	if (SUCCEEDED(hr))
	{ 
		bufferArray.Reserve(resultSize);

		PFAuthenticationLoginResult const* result;
		PFEntityHandle handle { nullptr };
		hr = PFAuthenticationLoginWithCustomIDGetResult(*mAsyncBlock, &handle, resultSize, bufferArray.GetData(), &result, nullptr);

		if (SUCCEEDED(hr))
		{
			TSharedPtr<const FPFAuthenticationLoginResult> ResultType = ConvertLoginResultToUnreal(result);

			FPFEntityHandle* entityHandlePtr = reinterpret_cast<FPFEntityHandle*>(&handle);
			delegate.ExecuteIfBound(ResultType.Get(), entityHandlePtr, true);
		}
		else
		{
			delegate.ExecuteIfBound(nullptr, nullptr, false);	
		}
	}
	else
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}



#if 0

FPFAuthenticationLoginWithEmailAddressAsyncTask::FPFAuthenticationLoginWithEmailAddressAsyncTask(
	FPFServiceConfigHandle serviceConfigHandle,
	const FPFAuthenticationLoginWithEmailAddressRequest request,
	FOnPFAuthenticationLoginCompleteDelegate delegate)
	: FXAsyncTask(TEXT("FPFLoginWithEmailAddressAsyncTask")),
	serviceConfigHandle(serviceConfigHandle),
	request(request),
	delegate(delegate)
{
}

void FPFAuthenticationLoginWithEmailAddressAsyncTask::DoWork()
{
	const PFAuthenticationLoginWithEmailAddressRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.email = ConvertFStringToCharPtr(request.email),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(request.infoRequestParameters),
		.password = ConvertFStringToCharPtr(request.password)
	};
	HRESULT hr = PFAuthenticationLoginWithEmailAddressAsync(serviceConfigHandle.Get(), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

void FPFAuthenticationLoginWithEmailAddressAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	uint64 resultSize = 0;

	HRESULT hr = PFAuthenticationLoginWithEmailAddressGetResultSize(*mAsyncBlock, &resultSize); 
	
	if (SUCCEEDED(hr))
	{ 
		bufferArray.Reserve(resultSize);

		PFAuthenticationLoginResult const* result;
		PFEntityHandle handle { nullptr };
		hr = PFAuthenticationLoginWithEmailAddressGetResult(*mAsyncBlock, &handle, resultSize, bufferArray.GetData(), &result, nullptr);

		if (SUCCEEDED(hr))
		{
			TSharedPtr<const FPFAuthenticationLoginResult> ResultType = ConvertLoginResultToUnreal(result);

			FPFEntityHandle* entityHandlePtr = reinterpret_cast<FPFEntityHandle*>(&handle);
			delegate.ExecuteIfBound(ResultType.Get(), entityHandlePtr, true);
		}
		else
		{
			delegate.ExecuteIfBound(nullptr, nullptr, false);	
		}
	}
	else
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

#endif


#if HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_IOS

FPFAuthenticationLoginWithFacebookAsyncTask::FPFAuthenticationLoginWithFacebookAsyncTask(
	FPFServiceConfigHandle serviceConfigHandle,
	const FPFAuthenticationLoginWithFacebookRequest request,
	FOnPFAuthenticationLoginCompleteDelegate delegate)
	: FXAsyncTask(TEXT("FPFLoginWithFacebookAsyncTask")),
	serviceConfigHandle(serviceConfigHandle),
	request(request),
	delegate(delegate)
{
}

void FPFAuthenticationLoginWithFacebookAsyncTask::DoWork()
{
	const PFAuthenticationLoginWithFacebookRequest RequestType = {
		.accessToken = ConvertFStringToCharPtr(request.accessToken),
		.authenticationToken = ConvertFStringToCharPtr(request.authenticationToken),
		.createAccount = request.createAccount,
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(request.infoRequestParameters),
		.playerSecret = ConvertFStringToCharPtr(request.playerSecret)
	};
	HRESULT hr = PFAuthenticationLoginWithFacebookAsync(serviceConfigHandle.Get(), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

void FPFAuthenticationLoginWithFacebookAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	uint64 resultSize = 0;

	HRESULT hr = PFAuthenticationLoginWithFacebookGetResultSize(*mAsyncBlock, &resultSize); 
	
	if (SUCCEEDED(hr))
	{ 
		bufferArray.Reserve(resultSize);

		PFAuthenticationLoginResult const* result;
		PFEntityHandle handle { nullptr };
		hr = PFAuthenticationLoginWithFacebookGetResult(*mAsyncBlock, &handle, resultSize, bufferArray.GetData(), &result, nullptr);

		if (SUCCEEDED(hr))
		{
			TSharedPtr<const FPFAuthenticationLoginResult> ResultType = ConvertLoginResultToUnreal(result);

			FPFEntityHandle* entityHandlePtr = reinterpret_cast<FPFEntityHandle*>(&handle);
			delegate.ExecuteIfBound(ResultType.Get(), entityHandlePtr, true);
		}
		else
		{
			delegate.ExecuteIfBound(nullptr, nullptr, false);	
		}
	}
	else
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

#endif


#if 0

FPFAuthenticationLoginWithFacebookInstantGamesIdAsyncTask::FPFAuthenticationLoginWithFacebookInstantGamesIdAsyncTask(
	FPFServiceConfigHandle serviceConfigHandle,
	const FPFAuthenticationLoginWithFacebookInstantGamesIdRequest request,
	FOnPFAuthenticationLoginCompleteDelegate delegate)
	: FXAsyncTask(TEXT("FPFLoginWithFacebookInstantGamesIdAsyncTask")),
	serviceConfigHandle(serviceConfigHandle),
	request(request),
	delegate(delegate)
{
}

void FPFAuthenticationLoginWithFacebookInstantGamesIdAsyncTask::DoWork()
{
	const PFAuthenticationLoginWithFacebookInstantGamesIdRequest RequestType = {
		.createAccount = request.createAccount,
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.facebookInstantGamesSignature = ConvertFStringToCharPtr(request.facebookInstantGamesSignature),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(request.infoRequestParameters),
		.playerSecret = ConvertFStringToCharPtr(request.playerSecret)
	};
	HRESULT hr = PFAuthenticationLoginWithFacebookInstantGamesIdAsync(serviceConfigHandle.Get(), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

void FPFAuthenticationLoginWithFacebookInstantGamesIdAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	uint64 resultSize = 0;

	HRESULT hr = PFAuthenticationLoginWithFacebookInstantGamesIdGetResultSize(*mAsyncBlock, &resultSize); 
	
	if (SUCCEEDED(hr))
	{ 
		bufferArray.Reserve(resultSize);

		PFAuthenticationLoginResult const* result;
		PFEntityHandle handle { nullptr };
		hr = PFAuthenticationLoginWithFacebookInstantGamesIdGetResult(*mAsyncBlock, &handle, resultSize, bufferArray.GetData(), &result, nullptr);

		if (SUCCEEDED(hr))
		{
			TSharedPtr<const FPFAuthenticationLoginResult> ResultType = ConvertLoginResultToUnreal(result);

			FPFEntityHandle* entityHandlePtr = reinterpret_cast<FPFEntityHandle*>(&handle);
			delegate.ExecuteIfBound(ResultType.Get(), entityHandlePtr, true);
		}
		else
		{
			delegate.ExecuteIfBound(nullptr, nullptr, false);	
		}
	}
	else
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

#endif


#if HC_PLATFORM == HC_PLATFORM_IOS

FPFAuthenticationLoginWithGameCenterAsyncTask::FPFAuthenticationLoginWithGameCenterAsyncTask(
	FPFServiceConfigHandle serviceConfigHandle,
	const FPFAuthenticationLoginWithGameCenterRequest request,
	FOnPFAuthenticationLoginCompleteDelegate delegate)
	: FXAsyncTask(TEXT("FPFLoginWithGameCenterAsyncTask")),
	serviceConfigHandle(serviceConfigHandle),
	request(request),
	delegate(delegate)
{
}

void FPFAuthenticationLoginWithGameCenterAsyncTask::DoWork()
{
	const PFAuthenticationLoginWithGameCenterRequest RequestType = {
		.createAccount = request.createAccount,
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(request.infoRequestParameters),
		.playerId = ConvertFStringToCharPtr(request.playerId),
		.playerSecret = ConvertFStringToCharPtr(request.playerSecret),
		.publicKeyUrl = ConvertFStringToCharPtr(request.publicKeyUrl),
		.salt = ConvertFStringToCharPtr(request.salt),
		.signature = ConvertFStringToCharPtr(request.signature),
		.timestamp = ConvertFStringToCharPtr(request.timestamp)
	};
	HRESULT hr = PFAuthenticationLoginWithGameCenterAsync(serviceConfigHandle.Get(), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

void FPFAuthenticationLoginWithGameCenterAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	uint64 resultSize = 0;

	HRESULT hr = PFAuthenticationLoginWithGameCenterGetResultSize(*mAsyncBlock, &resultSize); 
	
	if (SUCCEEDED(hr))
	{ 
		bufferArray.Reserve(resultSize);

		PFAuthenticationLoginResult const* result;
		PFEntityHandle handle { nullptr };
		hr = PFAuthenticationLoginWithGameCenterGetResult(*mAsyncBlock, &handle, resultSize, bufferArray.GetData(), &result, nullptr);

		if (SUCCEEDED(hr))
		{
			TSharedPtr<const FPFAuthenticationLoginResult> ResultType = ConvertLoginResultToUnreal(result);

			FPFEntityHandle* entityHandlePtr = reinterpret_cast<FPFEntityHandle*>(&handle);
			delegate.ExecuteIfBound(ResultType.Get(), entityHandlePtr, true);
		}
		else
		{
			delegate.ExecuteIfBound(nullptr, nullptr, false);	
		}
	}
	else
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

#endif


#if HC_PLATFORM == HC_PLATFORM_ANDROID

FPFAuthenticationLoginWithGoogleAccountAsyncTask::FPFAuthenticationLoginWithGoogleAccountAsyncTask(
	FPFServiceConfigHandle serviceConfigHandle,
	const FPFAuthenticationLoginWithGoogleAccountRequest request,
	FOnPFAuthenticationLoginCompleteDelegate delegate)
	: FXAsyncTask(TEXT("FPFLoginWithGoogleAccountAsyncTask")),
	serviceConfigHandle(serviceConfigHandle),
	request(request),
	delegate(delegate)
{
}

void FPFAuthenticationLoginWithGoogleAccountAsyncTask::DoWork()
{
	const PFAuthenticationLoginWithGoogleAccountRequest RequestType = {
		.createAccount = request.createAccount,
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(request.infoRequestParameters),
		.playerSecret = ConvertFStringToCharPtr(request.playerSecret),
		.serverAuthCode = ConvertFStringToCharPtr(request.serverAuthCode),
		.setEmail = new bool(*request.setEmail)
	};
	HRESULT hr = PFAuthenticationLoginWithGoogleAccountAsync(serviceConfigHandle.Get(), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

void FPFAuthenticationLoginWithGoogleAccountAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	uint64 resultSize = 0;

	HRESULT hr = PFAuthenticationLoginWithGoogleAccountGetResultSize(*mAsyncBlock, &resultSize); 
	
	if (SUCCEEDED(hr))
	{ 
		bufferArray.Reserve(resultSize);

		PFAuthenticationLoginResult const* result;
		PFEntityHandle handle { nullptr };
		hr = PFAuthenticationLoginWithGoogleAccountGetResult(*mAsyncBlock, &handle, resultSize, bufferArray.GetData(), &result, nullptr);

		if (SUCCEEDED(hr))
		{
			TSharedPtr<const FPFAuthenticationLoginResult> ResultType = ConvertLoginResultToUnreal(result);

			FPFEntityHandle* entityHandlePtr = reinterpret_cast<FPFEntityHandle*>(&handle);
			delegate.ExecuteIfBound(ResultType.Get(), entityHandlePtr, true);
		}
		else
		{
			delegate.ExecuteIfBound(nullptr, nullptr, false);	
		}
	}
	else
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

#endif


#if HC_PLATFORM == HC_PLATFORM_ANDROID

FPFAuthenticationLoginWithGooglePlayGamesServicesAsyncTask::FPFAuthenticationLoginWithGooglePlayGamesServicesAsyncTask(
	FPFServiceConfigHandle serviceConfigHandle,
	const FPFAuthenticationLoginWithGooglePlayGamesServicesRequest request,
	FOnPFAuthenticationLoginCompleteDelegate delegate)
	: FXAsyncTask(TEXT("FPFLoginWithGooglePlayGamesServicesAsyncTask")),
	serviceConfigHandle(serviceConfigHandle),
	request(request),
	delegate(delegate)
{
}

void FPFAuthenticationLoginWithGooglePlayGamesServicesAsyncTask::DoWork()
{
	const PFAuthenticationLoginWithGooglePlayGamesServicesRequest RequestType = {
		.createAccount = request.createAccount,
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(request.infoRequestParameters),
		.playerSecret = ConvertFStringToCharPtr(request.playerSecret),
		.serverAuthCode = ConvertFStringToCharPtr(request.serverAuthCode)
	};
	HRESULT hr = PFAuthenticationLoginWithGooglePlayGamesServicesAsync(serviceConfigHandle.Get(), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

void FPFAuthenticationLoginWithGooglePlayGamesServicesAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	uint64 resultSize = 0;

	HRESULT hr = PFAuthenticationLoginWithGooglePlayGamesServicesGetResultSize(*mAsyncBlock, &resultSize); 
	
	if (SUCCEEDED(hr))
	{ 
		bufferArray.Reserve(resultSize);

		PFAuthenticationLoginResult const* result;
		PFEntityHandle handle { nullptr };
		hr = PFAuthenticationLoginWithGooglePlayGamesServicesGetResult(*mAsyncBlock, &handle, resultSize, bufferArray.GetData(), &result, nullptr);

		if (SUCCEEDED(hr))
		{
			TSharedPtr<const FPFAuthenticationLoginResult> ResultType = ConvertLoginResultToUnreal(result);

			FPFEntityHandle* entityHandlePtr = reinterpret_cast<FPFEntityHandle*>(&handle);
			delegate.ExecuteIfBound(ResultType.Get(), entityHandlePtr, true);
		}
		else
		{
			delegate.ExecuteIfBound(nullptr, nullptr, false);	
		}
	}
	else
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

#endif


#if 0

FPFAuthenticationLoginWithIOSDeviceIDAsyncTask::FPFAuthenticationLoginWithIOSDeviceIDAsyncTask(
	FPFServiceConfigHandle serviceConfigHandle,
	const FPFAuthenticationLoginWithIOSDeviceIDRequest request,
	FOnPFAuthenticationLoginCompleteDelegate delegate)
	: FXAsyncTask(TEXT("FPFLoginWithIOSDeviceIDAsyncTask")),
	serviceConfigHandle(serviceConfigHandle),
	request(request),
	delegate(delegate)
{
}

void FPFAuthenticationLoginWithIOSDeviceIDAsyncTask::DoWork()
{
	const PFAuthenticationLoginWithIOSDeviceIDRequest RequestType = {
		.createAccount = request.createAccount,
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.deviceId = ConvertFStringToCharPtr(request.deviceId),
		.deviceModel = ConvertFStringToCharPtr(request.deviceModel),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(request.infoRequestParameters),
		.OS = ConvertFStringToCharPtr(request.OS),
		.playerSecret = ConvertFStringToCharPtr(request.playerSecret)
	};
	HRESULT hr = PFAuthenticationLoginWithIOSDeviceIDAsync(serviceConfigHandle.Get(), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

void FPFAuthenticationLoginWithIOSDeviceIDAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	uint64 resultSize = 0;

	HRESULT hr = PFAuthenticationLoginWithIOSDeviceIDGetResultSize(*mAsyncBlock, &resultSize); 
	
	if (SUCCEEDED(hr))
	{ 
		bufferArray.Reserve(resultSize);

		PFAuthenticationLoginResult const* result;
		PFEntityHandle handle { nullptr };
		hr = PFAuthenticationLoginWithIOSDeviceIDGetResult(*mAsyncBlock, &handle, resultSize, bufferArray.GetData(), &result, nullptr);

		if (SUCCEEDED(hr))
		{
			TSharedPtr<const FPFAuthenticationLoginResult> ResultType = ConvertLoginResultToUnreal(result);

			FPFEntityHandle* entityHandlePtr = reinterpret_cast<FPFEntityHandle*>(&handle);
			delegate.ExecuteIfBound(ResultType.Get(), entityHandlePtr, true);
		}
		else
		{
			delegate.ExecuteIfBound(nullptr, nullptr, false);	
		}
	}
	else
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

#endif


#if 0

FPFAuthenticationLoginWithKongregateAsyncTask::FPFAuthenticationLoginWithKongregateAsyncTask(
	FPFServiceConfigHandle serviceConfigHandle,
	const FPFAuthenticationLoginWithKongregateRequest request,
	FOnPFAuthenticationLoginCompleteDelegate delegate)
	: FXAsyncTask(TEXT("FPFLoginWithKongregateAsyncTask")),
	serviceConfigHandle(serviceConfigHandle),
	request(request),
	delegate(delegate)
{
}

void FPFAuthenticationLoginWithKongregateAsyncTask::DoWork()
{
	const PFAuthenticationLoginWithKongregateRequest RequestType = {
		.authTicket = ConvertFStringToCharPtr(request.authTicket),
		.createAccount = request.createAccount,
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(request.infoRequestParameters),
		.kongregateId = ConvertFStringToCharPtr(request.kongregateId),
		.playerSecret = ConvertFStringToCharPtr(request.playerSecret)
	};
	HRESULT hr = PFAuthenticationLoginWithKongregateAsync(serviceConfigHandle.Get(), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

void FPFAuthenticationLoginWithKongregateAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	uint64 resultSize = 0;

	HRESULT hr = PFAuthenticationLoginWithKongregateGetResultSize(*mAsyncBlock, &resultSize); 
	
	if (SUCCEEDED(hr))
	{ 
		bufferArray.Reserve(resultSize);

		PFAuthenticationLoginResult const* result;
		PFEntityHandle handle { nullptr };
		hr = PFAuthenticationLoginWithKongregateGetResult(*mAsyncBlock, &handle, resultSize, bufferArray.GetData(), &result, nullptr);

		if (SUCCEEDED(hr))
		{
			TSharedPtr<const FPFAuthenticationLoginResult> ResultType = ConvertLoginResultToUnreal(result);

			FPFEntityHandle* entityHandlePtr = reinterpret_cast<FPFEntityHandle*>(&handle);
			delegate.ExecuteIfBound(ResultType.Get(), entityHandlePtr, true);
		}
		else
		{
			delegate.ExecuteIfBound(nullptr, nullptr, false);	
		}
	}
	else
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

#endif


#if HC_PLATFORM == HC_PLATFORM_NINTENDO_SWITCH

FPFAuthenticationLoginWithNintendoServiceAccountAsyncTask::FPFAuthenticationLoginWithNintendoServiceAccountAsyncTask(
	FPFServiceConfigHandle serviceConfigHandle,
	const FPFAuthenticationLoginWithNintendoServiceAccountRequest request,
	FOnPFAuthenticationLoginCompleteDelegate delegate)
	: FXAsyncTask(TEXT("FPFLoginWithNintendoServiceAccountAsyncTask")),
	serviceConfigHandle(serviceConfigHandle),
	request(request),
	delegate(delegate)
{
}

void FPFAuthenticationLoginWithNintendoServiceAccountAsyncTask::DoWork()
{
	const PFAuthenticationLoginWithNintendoServiceAccountRequest RequestType = {
		.createAccount = request.createAccount,
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.identityToken = ConvertFStringToCharPtr(request.identityToken),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(request.infoRequestParameters),
		.playerSecret = ConvertFStringToCharPtr(request.playerSecret)
	};
	HRESULT hr = PFAuthenticationLoginWithNintendoServiceAccountAsync(serviceConfigHandle.Get(), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

void FPFAuthenticationLoginWithNintendoServiceAccountAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	uint64 resultSize = 0;

	HRESULT hr = PFAuthenticationLoginWithNintendoServiceAccountGetResultSize(*mAsyncBlock, &resultSize); 
	
	if (SUCCEEDED(hr))
	{ 
		bufferArray.Reserve(resultSize);

		PFAuthenticationLoginResult const* result;
		PFEntityHandle handle { nullptr };
		hr = PFAuthenticationLoginWithNintendoServiceAccountGetResult(*mAsyncBlock, &handle, resultSize, bufferArray.GetData(), &result, nullptr);

		if (SUCCEEDED(hr))
		{
			TSharedPtr<const FPFAuthenticationLoginResult> ResultType = ConvertLoginResultToUnreal(result);

			FPFEntityHandle* entityHandlePtr = reinterpret_cast<FPFEntityHandle*>(&handle);
			delegate.ExecuteIfBound(ResultType.Get(), entityHandlePtr, true);
		}
		else
		{
			delegate.ExecuteIfBound(nullptr, nullptr, false);	
		}
	}
	else
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

#endif


#if 0

FPFAuthenticationLoginWithNintendoSwitchDeviceIdAsyncTask::FPFAuthenticationLoginWithNintendoSwitchDeviceIdAsyncTask(
	FPFServiceConfigHandle serviceConfigHandle,
	const FPFAuthenticationLoginWithNintendoSwitchDeviceIdRequest request,
	FOnPFAuthenticationLoginCompleteDelegate delegate)
	: FXAsyncTask(TEXT("FPFLoginWithNintendoSwitchDeviceIdAsyncTask")),
	serviceConfigHandle(serviceConfigHandle),
	request(request),
	delegate(delegate)
{
}

void FPFAuthenticationLoginWithNintendoSwitchDeviceIdAsyncTask::DoWork()
{
	const PFAuthenticationLoginWithNintendoSwitchDeviceIdRequest RequestType = {
		.createAccount = request.createAccount,
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(request.infoRequestParameters),
		.nintendoSwitchDeviceId = ConvertFStringToCharPtr(request.nintendoSwitchDeviceId),
		.playerSecret = ConvertFStringToCharPtr(request.playerSecret)
	};
	HRESULT hr = PFAuthenticationLoginWithNintendoSwitchDeviceIdAsync(serviceConfigHandle.Get(), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

void FPFAuthenticationLoginWithNintendoSwitchDeviceIdAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	uint64 resultSize = 0;

	HRESULT hr = PFAuthenticationLoginWithNintendoSwitchDeviceIdGetResultSize(*mAsyncBlock, &resultSize); 
	
	if (SUCCEEDED(hr))
	{ 
		bufferArray.Reserve(resultSize);

		PFAuthenticationLoginResult const* result;
		PFEntityHandle handle { nullptr };
		hr = PFAuthenticationLoginWithNintendoSwitchDeviceIdGetResult(*mAsyncBlock, &handle, resultSize, bufferArray.GetData(), &result, nullptr);

		if (SUCCEEDED(hr))
		{
			TSharedPtr<const FPFAuthenticationLoginResult> ResultType = ConvertLoginResultToUnreal(result);

			FPFEntityHandle* entityHandlePtr = reinterpret_cast<FPFEntityHandle*>(&handle);
			delegate.ExecuteIfBound(ResultType.Get(), entityHandlePtr, true);
		}
		else
		{
			delegate.ExecuteIfBound(nullptr, nullptr, false);	
		}
	}
	else
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

#endif



FPFAuthenticationLoginWithOpenIdConnectAsyncTask::FPFAuthenticationLoginWithOpenIdConnectAsyncTask(
	FPFServiceConfigHandle serviceConfigHandle,
	const FPFAuthenticationLoginWithOpenIdConnectRequest request,
	FOnPFAuthenticationLoginCompleteDelegate delegate)
	: FXAsyncTask(TEXT("FPFLoginWithOpenIdConnectAsyncTask")),
	serviceConfigHandle(serviceConfigHandle),
	request(request),
	delegate(delegate)
{
}

void FPFAuthenticationLoginWithOpenIdConnectAsyncTask::DoWork()
{
	const PFAuthenticationLoginWithOpenIdConnectRequest RequestType = {
		.connectionId = ConvertFStringToCharPtr(request.connectionId),
		.createAccount = request.createAccount,
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.idToken = ConvertFStringToCharPtr(request.idToken),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(request.infoRequestParameters),
		.playerSecret = ConvertFStringToCharPtr(request.playerSecret)
	};
	HRESULT hr = PFAuthenticationLoginWithOpenIdConnectAsync(serviceConfigHandle.Get(), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

void FPFAuthenticationLoginWithOpenIdConnectAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	uint64 resultSize = 0;

	HRESULT hr = PFAuthenticationLoginWithOpenIdConnectGetResultSize(*mAsyncBlock, &resultSize); 
	
	if (SUCCEEDED(hr))
	{ 
		bufferArray.Reserve(resultSize);

		PFAuthenticationLoginResult const* result;
		PFEntityHandle handle { nullptr };
		hr = PFAuthenticationLoginWithOpenIdConnectGetResult(*mAsyncBlock, &handle, resultSize, bufferArray.GetData(), &result, nullptr);

		if (SUCCEEDED(hr))
		{
			TSharedPtr<const FPFAuthenticationLoginResult> ResultType = ConvertLoginResultToUnreal(result);

			FPFEntityHandle* entityHandlePtr = reinterpret_cast<FPFEntityHandle*>(&handle);
			delegate.ExecuteIfBound(ResultType.Get(), entityHandlePtr, true);
		}
		else
		{
			delegate.ExecuteIfBound(nullptr, nullptr, false);	
		}
	}
	else
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}



#if 0

FPFAuthenticationLoginWithPlayFabAsyncTask::FPFAuthenticationLoginWithPlayFabAsyncTask(
	FPFServiceConfigHandle serviceConfigHandle,
	const FPFAuthenticationLoginWithPlayFabRequest request,
	FOnPFAuthenticationLoginCompleteDelegate delegate)
	: FXAsyncTask(TEXT("FPFLoginWithPlayFabAsyncTask")),
	serviceConfigHandle(serviceConfigHandle),
	request(request),
	delegate(delegate)
{
}

void FPFAuthenticationLoginWithPlayFabAsyncTask::DoWork()
{
	const PFAuthenticationLoginWithPlayFabRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(request.infoRequestParameters),
		.password = ConvertFStringToCharPtr(request.password),
		.username = ConvertFStringToCharPtr(request.username)
	};
	HRESULT hr = PFAuthenticationLoginWithPlayFabAsync(serviceConfigHandle.Get(), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

void FPFAuthenticationLoginWithPlayFabAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	uint64 resultSize = 0;

	HRESULT hr = PFAuthenticationLoginWithPlayFabGetResultSize(*mAsyncBlock, &resultSize); 
	
	if (SUCCEEDED(hr))
	{ 
		bufferArray.Reserve(resultSize);

		PFAuthenticationLoginResult const* result;
		PFEntityHandle handle { nullptr };
		hr = PFAuthenticationLoginWithPlayFabGetResult(*mAsyncBlock, &handle, resultSize, bufferArray.GetData(), &result, nullptr);

		if (SUCCEEDED(hr))
		{
			TSharedPtr<const FPFAuthenticationLoginResult> ResultType = ConvertLoginResultToUnreal(result);

			FPFEntityHandle* entityHandlePtr = reinterpret_cast<FPFEntityHandle*>(&handle);
			delegate.ExecuteIfBound(ResultType.Get(), entityHandlePtr, true);
		}
		else
		{
			delegate.ExecuteIfBound(nullptr, nullptr, false);	
		}
	}
	else
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

#endif


#if HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_4 || HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_5

FPFAuthenticationLoginWithPSNAsyncTask::FPFAuthenticationLoginWithPSNAsyncTask(
	FPFServiceConfigHandle serviceConfigHandle,
	const FPFAuthenticationLoginWithPSNRequest request,
	FOnPFAuthenticationLoginCompleteDelegate delegate)
	: FXAsyncTask(TEXT("FPFLoginWithPSNAsyncTask")),
	serviceConfigHandle(serviceConfigHandle),
	request(request),
	delegate(delegate)
{
}

void FPFAuthenticationLoginWithPSNAsyncTask::DoWork()
{
	const PFAuthenticationLoginWithPSNRequest RequestType = {
		.authCode = ConvertFStringToCharPtr(request.authCode),
		.createAccount = request.createAccount,
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(request.infoRequestParameters),
		.issuerId = new int32(*request.issuerId),
		.playerSecret = ConvertFStringToCharPtr(request.playerSecret),
		.redirectUri = ConvertFStringToCharPtr(request.redirectUri)
	};
	HRESULT hr = PFAuthenticationLoginWithPSNAsync(serviceConfigHandle.Get(), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

void FPFAuthenticationLoginWithPSNAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	uint64 resultSize = 0;

	HRESULT hr = PFAuthenticationLoginWithPSNGetResultSize(*mAsyncBlock, &resultSize); 
	
	if (SUCCEEDED(hr))
	{ 
		bufferArray.Reserve(resultSize);

		PFAuthenticationLoginResult const* result;
		PFEntityHandle handle { nullptr };
		hr = PFAuthenticationLoginWithPSNGetResult(*mAsyncBlock, &handle, resultSize, bufferArray.GetData(), &result, nullptr);

		if (SUCCEEDED(hr))
		{
			TSharedPtr<const FPFAuthenticationLoginResult> ResultType = ConvertLoginResultToUnreal(result);

			FPFEntityHandle* entityHandlePtr = reinterpret_cast<FPFEntityHandle*>(&handle);
			delegate.ExecuteIfBound(ResultType.Get(), entityHandlePtr, true);
		}
		else
		{
			delegate.ExecuteIfBound(nullptr, nullptr, false);	
		}
	}
	else
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

#endif


#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

FPFAuthenticationLoginWithSteamAsyncTask::FPFAuthenticationLoginWithSteamAsyncTask(
	FPFServiceConfigHandle serviceConfigHandle,
	const FPFAuthenticationLoginWithSteamRequest request,
	FOnPFAuthenticationLoginCompleteDelegate delegate)
	: FXAsyncTask(TEXT("FPFLoginWithSteamAsyncTask")),
	serviceConfigHandle(serviceConfigHandle),
	request(request),
	delegate(delegate)
{
}

void FPFAuthenticationLoginWithSteamAsyncTask::DoWork()
{
	const PFAuthenticationLoginWithSteamRequest RequestType = {
		.createAccount = request.createAccount,
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(request.infoRequestParameters),
		.playerSecret = ConvertFStringToCharPtr(request.playerSecret),
		.steamTicket = ConvertFStringToCharPtr(request.steamTicket),
		.ticketIsServiceSpecific = new bool(*request.ticketIsServiceSpecific)
	};
	HRESULT hr = PFAuthenticationLoginWithSteamAsync(serviceConfigHandle.Get(), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

void FPFAuthenticationLoginWithSteamAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	uint64 resultSize = 0;

	HRESULT hr = PFAuthenticationLoginWithSteamGetResultSize(*mAsyncBlock, &resultSize); 
	
	if (SUCCEEDED(hr))
	{ 
		bufferArray.Reserve(resultSize);

		PFAuthenticationLoginResult const* result;
		PFEntityHandle handle { nullptr };
		hr = PFAuthenticationLoginWithSteamGetResult(*mAsyncBlock, &handle, resultSize, bufferArray.GetData(), &result, nullptr);

		if (SUCCEEDED(hr))
		{
			TSharedPtr<const FPFAuthenticationLoginResult> ResultType = ConvertLoginResultToUnreal(result);

			FPFEntityHandle* entityHandlePtr = reinterpret_cast<FPFEntityHandle*>(&handle);
			delegate.ExecuteIfBound(ResultType.Get(), entityHandlePtr, true);
		}
		else
		{
			delegate.ExecuteIfBound(nullptr, nullptr, false);	
		}
	}
	else
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

#endif


#if 0

FPFAuthenticationLoginWithTwitchAsyncTask::FPFAuthenticationLoginWithTwitchAsyncTask(
	FPFServiceConfigHandle serviceConfigHandle,
	const FPFAuthenticationLoginWithTwitchRequest request,
	FOnPFAuthenticationLoginCompleteDelegate delegate)
	: FXAsyncTask(TEXT("FPFLoginWithTwitchAsyncTask")),
	serviceConfigHandle(serviceConfigHandle),
	request(request),
	delegate(delegate)
{
}

void FPFAuthenticationLoginWithTwitchAsyncTask::DoWork()
{
	const PFAuthenticationLoginWithTwitchRequest RequestType = {
		.accessToken = ConvertFStringToCharPtr(request.accessToken),
		.createAccount = request.createAccount,
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(request.infoRequestParameters),
		.playerSecret = ConvertFStringToCharPtr(request.playerSecret)
	};
	HRESULT hr = PFAuthenticationLoginWithTwitchAsync(serviceConfigHandle.Get(), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

void FPFAuthenticationLoginWithTwitchAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	uint64 resultSize = 0;

	HRESULT hr = PFAuthenticationLoginWithTwitchGetResultSize(*mAsyncBlock, &resultSize); 
	
	if (SUCCEEDED(hr))
	{ 
		bufferArray.Reserve(resultSize);

		PFAuthenticationLoginResult const* result;
		PFEntityHandle handle { nullptr };
		hr = PFAuthenticationLoginWithTwitchGetResult(*mAsyncBlock, &handle, resultSize, bufferArray.GetData(), &result, nullptr);

		if (SUCCEEDED(hr))
		{
			TSharedPtr<const FPFAuthenticationLoginResult> ResultType = ConvertLoginResultToUnreal(result);

			FPFEntityHandle* entityHandlePtr = reinterpret_cast<FPFEntityHandle*>(&handle);
			delegate.ExecuteIfBound(ResultType.Get(), entityHandlePtr, true);
		}
		else
		{
			delegate.ExecuteIfBound(nullptr, nullptr, false);	
		}
	}
	else
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

#endif


#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

FPFAuthenticationLoginWithXboxAsyncTask::FPFAuthenticationLoginWithXboxAsyncTask(
	FPFServiceConfigHandle serviceConfigHandle,
	const FPFAuthenticationLoginWithXboxRequest request,
	FOnPFAuthenticationLoginCompleteDelegate delegate)
	: FXAsyncTask(TEXT("FPFLoginWithXboxAsyncTask")),
	serviceConfigHandle(serviceConfigHandle),
	request(request),
	delegate(delegate)
{
}

void FPFAuthenticationLoginWithXboxAsyncTask::DoWork()
{
	const PFAuthenticationLoginWithXboxRequest RequestType = {
		.createAccount = request.createAccount,
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(request.infoRequestParameters),
		.playerSecret = ConvertFStringToCharPtr(request.playerSecret),
		.xboxToken = ConvertFStringToCharPtr(request.xboxToken)
	};
	HRESULT hr = PFAuthenticationLoginWithXboxAsync(serviceConfigHandle.Get(), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

void FPFAuthenticationLoginWithXboxAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	uint64 resultSize = 0;

	HRESULT hr = PFAuthenticationLoginWithXboxGetResultSize(*mAsyncBlock, &resultSize); 
	
	if (SUCCEEDED(hr))
	{ 
		bufferArray.Reserve(resultSize);

		PFAuthenticationLoginResult const* result;
		PFEntityHandle handle { nullptr };
		hr = PFAuthenticationLoginWithXboxGetResult(*mAsyncBlock, &handle, resultSize, bufferArray.GetData(), &result, nullptr);

		if (SUCCEEDED(hr))
		{
			TSharedPtr<const FPFAuthenticationLoginResult> ResultType = ConvertLoginResultToUnreal(result);

			FPFEntityHandle* entityHandlePtr = reinterpret_cast<FPFEntityHandle*>(&handle);
			delegate.ExecuteIfBound(ResultType.Get(), entityHandlePtr, true);
		}
		else
		{
			delegate.ExecuteIfBound(nullptr, nullptr, false);	
		}
	}
	else
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

#endif


#if 0

FPFAuthenticationRegisterPlayFabUserAsyncTask::FPFAuthenticationRegisterPlayFabUserAsyncTask(
	FPFServiceConfigHandle serviceConfigHandle,
	const FPFAuthenticationRegisterPlayFabUserRequest request,
	FOnRegisterPlayFabUserDelegate delegate)
	: FXAsyncTask(TEXT("FPFRegisterPlayFabUserAsyncTask")),
	serviceConfigHandle(serviceConfigHandle),
	request(request),
	delegate(delegate)
{
}

void FPFAuthenticationRegisterPlayFabUserAsyncTask::DoWork()
{
	const PFAuthenticationRegisterPlayFabUserRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.displayName = ConvertFStringToCharPtr(request.displayName),
		.email = ConvertFStringToCharPtr(request.email),
		.encryptedRequest = ConvertFStringToCharPtr(request.encryptedRequest),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(request.infoRequestParameters),
		.password = ConvertFStringToCharPtr(request.password),
		.playerSecret = ConvertFStringToCharPtr(request.playerSecret),
		.requireBothUsernameAndEmail = new bool(*request.requireBothUsernameAndEmail),
		.titleId = ConvertFStringToCharPtr(request.titleId),
		.username = ConvertFStringToCharPtr(request.username)
	};
	HRESULT hr = PFAuthenticationRegisterPlayFabUserAsync(serviceConfigHandle.Get(), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, false);
	}
}

void FPFAuthenticationRegisterPlayFabUserAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	uint64 resultSize = 0;

	HRESULT hr = PFAuthenticationRegisterPlayFabUserGetResultSize(*mAsyncBlock, &resultSize); 
	
	if (SUCCEEDED(hr))
	{ 
		bufferArray.Reserve(resultSize);

		uint64 bufferUsed = 0;
		PFAuthenticationRegisterPlayFabUserResult* result;
		hr = PFAuthenticationRegisterPlayFabUserGetResult(*mAsyncBlock, resultSize, bufferArray.GetData(), &result, &bufferUsed);

		if (SUCCEEDED(hr))
		{
			TSharedPtr<const FPFAuthenticationRegisterPlayFabUserResult> ResultType = ConvertRegisterPlayFabUserResultToUnreal(result);

			delegate.ExecuteIfBound(ResultType.Get(), true);
		}
		else
		{
			delegate.ExecuteIfBound(nullptr, false);	
		}
	}
	else
	{
		delegate.ExecuteIfBound(nullptr, false);
	}
}


#endif


#if HC_PLATFORM == HC_PLATFORM_GDK

FPFAuthenticationServerLoginWithAndroidDeviceIDAsyncTask::FPFAuthenticationServerLoginWithAndroidDeviceIDAsyncTask(
	FPFServiceConfigHandle serviceConfigHandle,
	const FString secretKey,
	const FPFAuthenticationServerLoginWithAndroidDeviceIDRequest request,
	FOnPFAuthenticationServerLoginCompleteDelegate delegate)
	: FXAsyncTask(TEXT("FPFServerLoginWithAndroidDeviceIDAsyncTask")),
	serviceConfigHandle(serviceConfigHandle),
	secretKey(secretKey),
	request(request),
	delegate(delegate)
{
}

void FPFAuthenticationServerLoginWithAndroidDeviceIDAsyncTask::DoWork()
{
	const PFAuthenticationServerLoginWithAndroidDeviceIDRequest RequestType = {
		.androidDevice = ConvertFStringToCharPtr(request.androidDevice),
		.androidDeviceId = ConvertFStringToCharPtr(request.androidDeviceId),
		.createAccount = request.createAccount,
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(request.infoRequestParameters),
		.OS = ConvertFStringToCharPtr(request.OS)
	};
	HRESULT hr = PFAuthenticationServerLoginWithAndroidDeviceIDAsync(serviceConfigHandle.Get(), ConvertFStringToCharPtr(secretKey), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

void FPFAuthenticationServerLoginWithAndroidDeviceIDAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	uint64 resultSize = 0;

	HRESULT hr = PFAuthenticationServerLoginWithAndroidDeviceIDGetResultSize(*mAsyncBlock, &resultSize); 
	
	if (SUCCEEDED(hr))
	{ 
		bufferArray.Reserve(resultSize);

		PFAuthenticationLoginResult const* result;
		PFAuthenticationEntityTokenResponse const* entityTokenResponse { nullptr };
		hr = PFAuthenticationServerLoginWithAndroidDeviceIDGetResult(*mAsyncBlock, &entityTokenResponse, resultSize, bufferArray.GetData(), &result, nullptr);

		if (SUCCEEDED(hr))
		{
			TSharedPtr<const FPFAuthenticationLoginResult> ResultType = ConvertLoginResultToUnreal(result);

			delegate.ExecuteIfBound(ResultType.Get(), &entityTokenResponse, true);
		}
		else
		{
			delegate.ExecuteIfBound(nullptr, nullptr, false);	
		}
	}
	else
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

#endif


#if HC_PLATFORM == HC_PLATFORM_GDK

FPFAuthenticationServerLoginWithBattleNetAsyncTask::FPFAuthenticationServerLoginWithBattleNetAsyncTask(
	FPFServiceConfigHandle serviceConfigHandle,
	const FString secretKey,
	const FPFAuthenticationServerLoginWithBattleNetRequest request,
	FOnPFAuthenticationServerLoginCompleteDelegate delegate)
	: FXAsyncTask(TEXT("FPFServerLoginWithBattleNetAsyncTask")),
	serviceConfigHandle(serviceConfigHandle),
	secretKey(secretKey),
	request(request),
	delegate(delegate)
{
}

void FPFAuthenticationServerLoginWithBattleNetAsyncTask::DoWork()
{
	const PFAuthenticationServerLoginWithBattleNetRequest RequestType = {
		.createAccount = request.createAccount,
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.identityToken = ConvertFStringToCharPtr(request.identityToken),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(request.infoRequestParameters)
	};
	HRESULT hr = PFAuthenticationServerLoginWithBattleNetAsync(serviceConfigHandle.Get(), ConvertFStringToCharPtr(secretKey), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

void FPFAuthenticationServerLoginWithBattleNetAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	uint64 resultSize = 0;

	HRESULT hr = PFAuthenticationServerLoginWithBattleNetGetResultSize(*mAsyncBlock, &resultSize); 
	
	if (SUCCEEDED(hr))
	{ 
		bufferArray.Reserve(resultSize);

		PFAuthenticationLoginResult const* result;
		PFAuthenticationEntityTokenResponse const* entityTokenResponse { nullptr };
		hr = PFAuthenticationServerLoginWithBattleNetGetResult(*mAsyncBlock, &entityTokenResponse, resultSize, bufferArray.GetData(), &result, nullptr);

		if (SUCCEEDED(hr))
		{
			TSharedPtr<const FPFAuthenticationLoginResult> ResultType = ConvertLoginResultToUnreal(result);

			delegate.ExecuteIfBound(ResultType.Get(), &entityTokenResponse, true);
		}
		else
		{
			delegate.ExecuteIfBound(nullptr, nullptr, false);	
		}
	}
	else
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

#endif


#if HC_PLATFORM == HC_PLATFORM_GDK

FPFAuthenticationServerLoginWithCustomIDAsyncTask::FPFAuthenticationServerLoginWithCustomIDAsyncTask(
	FPFServiceConfigHandle serviceConfigHandle,
	const FString secretKey,
	const FPFAuthenticationServerLoginWithCustomIDRequest request,
	FOnPFAuthenticationServerLoginCompleteDelegate delegate)
	: FXAsyncTask(TEXT("FPFServerLoginWithCustomIDAsyncTask")),
	serviceConfigHandle(serviceConfigHandle),
	secretKey(secretKey),
	request(request),
	delegate(delegate)
{
}

void FPFAuthenticationServerLoginWithCustomIDAsyncTask::DoWork()
{
	const PFAuthenticationServerLoginWithCustomIDRequest RequestType = {
		.createAccount = request.createAccount,
		.customId = ConvertFStringToCharPtr(request.customId),
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(request.infoRequestParameters)
	};
	HRESULT hr = PFAuthenticationServerLoginWithCustomIDAsync(serviceConfigHandle.Get(), ConvertFStringToCharPtr(secretKey), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

void FPFAuthenticationServerLoginWithCustomIDAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	uint64 resultSize = 0;

	HRESULT hr = PFAuthenticationServerLoginWithCustomIDGetResultSize(*mAsyncBlock, &resultSize); 
	
	if (SUCCEEDED(hr))
	{ 
		bufferArray.Reserve(resultSize);

		PFAuthenticationLoginResult const* result;
		PFAuthenticationEntityTokenResponse const* entityTokenResponse { nullptr };
		hr = PFAuthenticationServerLoginWithCustomIDGetResult(*mAsyncBlock, &entityTokenResponse, resultSize, bufferArray.GetData(), &result, nullptr);

		if (SUCCEEDED(hr))
		{
			TSharedPtr<const FPFAuthenticationLoginResult> ResultType = ConvertLoginResultToUnreal(result);

			delegate.ExecuteIfBound(ResultType.Get(), &entityTokenResponse, true);
		}
		else
		{
			delegate.ExecuteIfBound(nullptr, nullptr, false);	
		}
	}
	else
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

#endif


#if HC_PLATFORM == HC_PLATFORM_GDK

FPFAuthenticationServerLoginWithIOSDeviceIDAsyncTask::FPFAuthenticationServerLoginWithIOSDeviceIDAsyncTask(
	FPFServiceConfigHandle serviceConfigHandle,
	const FString secretKey,
	const FPFAuthenticationServerLoginWithIOSDeviceIDRequest request,
	FOnPFAuthenticationServerLoginCompleteDelegate delegate)
	: FXAsyncTask(TEXT("FPFServerLoginWithIOSDeviceIDAsyncTask")),
	serviceConfigHandle(serviceConfigHandle),
	secretKey(secretKey),
	request(request),
	delegate(delegate)
{
}

void FPFAuthenticationServerLoginWithIOSDeviceIDAsyncTask::DoWork()
{
	const PFAuthenticationServerLoginWithIOSDeviceIDRequest RequestType = {
		.createAccount = request.createAccount,
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.deviceId = ConvertFStringToCharPtr(request.deviceId),
		.deviceModel = ConvertFStringToCharPtr(request.deviceModel),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(request.infoRequestParameters),
		.OS = ConvertFStringToCharPtr(request.OS)
	};
	HRESULT hr = PFAuthenticationServerLoginWithIOSDeviceIDAsync(serviceConfigHandle.Get(), ConvertFStringToCharPtr(secretKey), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

void FPFAuthenticationServerLoginWithIOSDeviceIDAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	uint64 resultSize = 0;

	HRESULT hr = PFAuthenticationServerLoginWithIOSDeviceIDGetResultSize(*mAsyncBlock, &resultSize); 
	
	if (SUCCEEDED(hr))
	{ 
		bufferArray.Reserve(resultSize);

		PFAuthenticationLoginResult const* result;
		PFAuthenticationEntityTokenResponse const* entityTokenResponse { nullptr };
		hr = PFAuthenticationServerLoginWithIOSDeviceIDGetResult(*mAsyncBlock, &entityTokenResponse, resultSize, bufferArray.GetData(), &result, nullptr);

		if (SUCCEEDED(hr))
		{
			TSharedPtr<const FPFAuthenticationLoginResult> ResultType = ConvertLoginResultToUnreal(result);

			delegate.ExecuteIfBound(ResultType.Get(), &entityTokenResponse, true);
		}
		else
		{
			delegate.ExecuteIfBound(nullptr, nullptr, false);	
		}
	}
	else
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

#endif


#if HC_PLATFORM == HC_PLATFORM_GDK

FPFAuthenticationServerLoginWithPSNAsyncTask::FPFAuthenticationServerLoginWithPSNAsyncTask(
	FPFServiceConfigHandle serviceConfigHandle,
	const FString secretKey,
	const FPFAuthenticationServerLoginWithPSNRequest request,
	FOnPFAuthenticationServerLoginCompleteDelegate delegate)
	: FXAsyncTask(TEXT("FPFServerLoginWithPSNAsyncTask")),
	serviceConfigHandle(serviceConfigHandle),
	secretKey(secretKey),
	request(request),
	delegate(delegate)
{
}

void FPFAuthenticationServerLoginWithPSNAsyncTask::DoWork()
{
	const PFAuthenticationServerLoginWithPSNRequest RequestType = {
		.authCode = ConvertFStringToCharPtr(request.authCode),
		.createAccount = request.createAccount,
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(request.infoRequestParameters),
		.issuerId = new int32(*request.issuerId),
		.redirectUri = ConvertFStringToCharPtr(request.redirectUri)
	};
	HRESULT hr = PFAuthenticationServerLoginWithPSNAsync(serviceConfigHandle.Get(), ConvertFStringToCharPtr(secretKey), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

void FPFAuthenticationServerLoginWithPSNAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	uint64 resultSize = 0;

	HRESULT hr = PFAuthenticationServerLoginWithPSNGetResultSize(*mAsyncBlock, &resultSize); 
	
	if (SUCCEEDED(hr))
	{ 
		bufferArray.Reserve(resultSize);

		PFAuthenticationLoginResult const* result;
		PFAuthenticationEntityTokenResponse const* entityTokenResponse { nullptr };
		hr = PFAuthenticationServerLoginWithPSNGetResult(*mAsyncBlock, &entityTokenResponse, resultSize, bufferArray.GetData(), &result, nullptr);

		if (SUCCEEDED(hr))
		{
			TSharedPtr<const FPFAuthenticationLoginResult> ResultType = ConvertLoginResultToUnreal(result);

			delegate.ExecuteIfBound(ResultType.Get(), &entityTokenResponse, true);
		}
		else
		{
			delegate.ExecuteIfBound(nullptr, nullptr, false);	
		}
	}
	else
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

#endif


#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

FPFAuthenticationServerLoginWithServerCustomIdAsyncTask::FPFAuthenticationServerLoginWithServerCustomIdAsyncTask(
	FPFServiceConfigHandle serviceConfigHandle,
	const FString secretKey,
	const FPFAuthenticationLoginWithServerCustomIdRequest request,
	FOnPFAuthenticationServerLoginCompleteDelegate delegate)
	: FXAsyncTask(TEXT("FPFServerLoginWithServerCustomIdAsyncTask")),
	serviceConfigHandle(serviceConfigHandle),
	secretKey(secretKey),
	request(request),
	delegate(delegate)
{
}

void FPFAuthenticationServerLoginWithServerCustomIdAsyncTask::DoWork()
{
	const PFAuthenticationLoginWithServerCustomIdRequest RequestType = {
		.createAccount = request.createAccount,
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(request.infoRequestParameters),
		.playerSecret = ConvertFStringToCharPtr(request.playerSecret),
		.serverCustomId = ConvertFStringToCharPtr(request.serverCustomId)
	};
	HRESULT hr = PFAuthenticationServerLoginWithServerCustomIdAsync(serviceConfigHandle.Get(), ConvertFStringToCharPtr(secretKey), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

void FPFAuthenticationServerLoginWithServerCustomIdAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	uint64 resultSize = 0;

	HRESULT hr = PFAuthenticationServerLoginWithServerCustomIdGetResultSize(*mAsyncBlock, &resultSize); 
	
	if (SUCCEEDED(hr))
	{ 
		bufferArray.Reserve(resultSize);

		PFAuthenticationLoginResult const* result;
		PFAuthenticationEntityTokenResponse const* entityTokenResponse { nullptr };
		hr = PFAuthenticationServerLoginWithServerCustomIdGetResult(*mAsyncBlock, &entityTokenResponse, resultSize, bufferArray.GetData(), &result, nullptr);

		if (SUCCEEDED(hr))
		{
			TSharedPtr<const FPFAuthenticationLoginResult> ResultType = ConvertLoginResultToUnreal(result);

			delegate.ExecuteIfBound(ResultType.Get(), &entityTokenResponse, true);
		}
		else
		{
			delegate.ExecuteIfBound(nullptr, nullptr, false);	
		}
	}
	else
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

#endif


#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

FPFAuthenticationServerLoginWithSteamIdAsyncTask::FPFAuthenticationServerLoginWithSteamIdAsyncTask(
	FPFServiceConfigHandle serviceConfigHandle,
	const FString secretKey,
	const FPFAuthenticationLoginWithSteamIdRequest request,
	FOnPFAuthenticationServerLoginCompleteDelegate delegate)
	: FXAsyncTask(TEXT("FPFServerLoginWithSteamIdAsyncTask")),
	serviceConfigHandle(serviceConfigHandle),
	secretKey(secretKey),
	request(request),
	delegate(delegate)
{
}

void FPFAuthenticationServerLoginWithSteamIdAsyncTask::DoWork()
{
	const PFAuthenticationLoginWithSteamIdRequest RequestType = {
		.createAccount = request.createAccount,
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(request.infoRequestParameters),
		.steamId = ConvertFStringToCharPtr(request.steamId)
	};
	HRESULT hr = PFAuthenticationServerLoginWithSteamIdAsync(serviceConfigHandle.Get(), ConvertFStringToCharPtr(secretKey), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

void FPFAuthenticationServerLoginWithSteamIdAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	uint64 resultSize = 0;

	HRESULT hr = PFAuthenticationServerLoginWithSteamIdGetResultSize(*mAsyncBlock, &resultSize); 
	
	if (SUCCEEDED(hr))
	{ 
		bufferArray.Reserve(resultSize);

		PFAuthenticationLoginResult const* result;
		PFAuthenticationEntityTokenResponse const* entityTokenResponse { nullptr };
		hr = PFAuthenticationServerLoginWithSteamIdGetResult(*mAsyncBlock, &entityTokenResponse, resultSize, bufferArray.GetData(), &result, nullptr);

		if (SUCCEEDED(hr))
		{
			TSharedPtr<const FPFAuthenticationLoginResult> ResultType = ConvertLoginResultToUnreal(result);

			delegate.ExecuteIfBound(ResultType.Get(), &entityTokenResponse, true);
		}
		else
		{
			delegate.ExecuteIfBound(nullptr, nullptr, false);	
		}
	}
	else
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

#endif


#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

FPFAuthenticationServerLoginWithXboxAsyncTask::FPFAuthenticationServerLoginWithXboxAsyncTask(
	FPFServiceConfigHandle serviceConfigHandle,
	const FString secretKey,
	const FPFAuthenticationServerLoginWithXboxRequest request,
	FOnPFAuthenticationServerLoginCompleteDelegate delegate)
	: FXAsyncTask(TEXT("FPFServerLoginWithXboxAsyncTask")),
	serviceConfigHandle(serviceConfigHandle),
	secretKey(secretKey),
	request(request),
	delegate(delegate)
{
}

void FPFAuthenticationServerLoginWithXboxAsyncTask::DoWork()
{
	const PFAuthenticationServerLoginWithXboxRequest RequestType = {
		.createAccount = request.createAccount,
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(request.infoRequestParameters),
		.xboxToken = ConvertFStringToCharPtr(request.xboxToken)
	};
	HRESULT hr = PFAuthenticationServerLoginWithXboxAsync(serviceConfigHandle.Get(), ConvertFStringToCharPtr(secretKey), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

void FPFAuthenticationServerLoginWithXboxAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	uint64 resultSize = 0;

	HRESULT hr = PFAuthenticationServerLoginWithXboxGetResultSize(*mAsyncBlock, &resultSize); 
	
	if (SUCCEEDED(hr))
	{ 
		bufferArray.Reserve(resultSize);

		PFAuthenticationLoginResult const* result;
		PFAuthenticationEntityTokenResponse const* entityTokenResponse { nullptr };
		hr = PFAuthenticationServerLoginWithXboxGetResult(*mAsyncBlock, &entityTokenResponse, resultSize, bufferArray.GetData(), &result, nullptr);

		if (SUCCEEDED(hr))
		{
			TSharedPtr<const FPFAuthenticationLoginResult> ResultType = ConvertLoginResultToUnreal(result);

			delegate.ExecuteIfBound(ResultType.Get(), &entityTokenResponse, true);
		}
		else
		{
			delegate.ExecuteIfBound(nullptr, nullptr, false);	
		}
	}
	else
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

#endif


#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

FPFAuthenticationServerLoginWithXboxIdAsyncTask::FPFAuthenticationServerLoginWithXboxIdAsyncTask(
	FPFServiceConfigHandle serviceConfigHandle,
	const FString secretKey,
	const FPFAuthenticationLoginWithXboxIdRequest request,
	FOnPFAuthenticationServerLoginCompleteDelegate delegate)
	: FXAsyncTask(TEXT("FPFServerLoginWithXboxIdAsyncTask")),
	serviceConfigHandle(serviceConfigHandle),
	secretKey(secretKey),
	request(request),
	delegate(delegate)
{
}

void FPFAuthenticationServerLoginWithXboxIdAsyncTask::DoWork()
{
	const PFAuthenticationLoginWithXboxIdRequest RequestType = {
		.createAccount = request.createAccount,
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(request.infoRequestParameters),
		.sandbox = ConvertFStringToCharPtr(request.sandbox),
		.xboxId = ConvertFStringToCharPtr(request.xboxId)
	};
	HRESULT hr = PFAuthenticationServerLoginWithXboxIdAsync(serviceConfigHandle.Get(), ConvertFStringToCharPtr(secretKey), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

void FPFAuthenticationServerLoginWithXboxIdAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	uint64 resultSize = 0;

	HRESULT hr = PFAuthenticationServerLoginWithXboxIdGetResultSize(*mAsyncBlock, &resultSize); 
	
	if (SUCCEEDED(hr))
	{ 
		bufferArray.Reserve(resultSize);

		PFAuthenticationLoginResult const* result;
		PFAuthenticationEntityTokenResponse const* entityTokenResponse { nullptr };
		hr = PFAuthenticationServerLoginWithXboxIdGetResult(*mAsyncBlock, &entityTokenResponse, resultSize, bufferArray.GetData(), &result, nullptr);

		if (SUCCEEDED(hr))
		{
			TSharedPtr<const FPFAuthenticationLoginResult> ResultType = ConvertLoginResultToUnreal(result);

			delegate.ExecuteIfBound(ResultType.Get(), &entityTokenResponse, true);
		}
		else
		{
			delegate.ExecuteIfBound(nullptr, nullptr, false);	
		}
	}
	else
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

#endif


#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

FPFAuthenticationAuthenticateGameServerWithCustomIdAsyncTask::FPFAuthenticationAuthenticateGameServerWithCustomIdAsyncTask(
	FPFEntityHandle entityHandle,
	const FPFAuthenticationAuthenticateCustomIdRequest request,
	FOnAuthenticateGameServerWithCustomIdDelegate delegate)
	: FXAsyncTask(TEXT("FPFAuthenticateGameServerWithCustomIdAsyncTask")),
	entityHandle(entityHandle),
	request(request),
	delegate(delegate)
{
}

void FPFAuthenticationAuthenticateGameServerWithCustomIdAsyncTask::DoWork()
{
	const PFAuthenticationAuthenticateCustomIdRequest RequestType = {
		.customId = ConvertFStringToCharPtr(request.customId),
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num()
	};
	HRESULT hr = PFAuthenticationAuthenticateGameServerWithCustomIdAsync(entityHandle.Get(), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

void FPFAuthenticationAuthenticateGameServerWithCustomIdAsyncTask::ProcessResults()
{
	bool* newlyCreated { nullptr };
	PFEntityHandle handle { nullptr };
	HRESULT hr = PFAuthenticationAuthenticateGameServerWithCustomIdGetResult(*mAsyncBlock, &handle, newlyCreated);

	if (SUCCEEDED(hr))
	{
		FPFEntityHandle* entityHandlePtr = reinterpret_cast<FPFEntityHandle*>(&handle);
		delegate.ExecuteIfBound(entityHandlePtr, newlyCreated, true);
	}
	else
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);	
	}
}

#endif


#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

FPFAuthenticationDeleteAsyncTask::FPFAuthenticationDeleteAsyncTask(
	FPFEntityHandle entityHandle,
	const FPFAuthenticationDeleteRequest request,
	FOnDeleteDelegate delegate)
	: FXAsyncTask(TEXT("FPFDeleteAsyncTask")),
	entityHandle(entityHandle),
	request(request),
	delegate(delegate)
{
}

void FPFAuthenticationDeleteAsyncTask::DoWork()
{
	const PFAuthenticationDeleteRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(request.entity)
	};
	HRESULT hr = PFAuthenticationDeleteAsync(entityHandle.Get(), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(false);
	}
}

void FPFAuthenticationDeleteAsyncTask::ProcessResults()
{
	delegate.ExecuteIfBound(true);
}
	
#endif


#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

FPFAuthenticationGetEntityAsyncTask::FPFAuthenticationGetEntityAsyncTask(
	FPFEntityHandle entityHandle,
	const FPFAuthenticationGetEntityRequest request,
	FOnGetEntityDelegate delegate)
	: FXAsyncTask(TEXT("FPFGetEntityAsyncTask")),
	entityHandle(entityHandle),
	request(request),
	delegate(delegate)
{
}

void FPFAuthenticationGetEntityAsyncTask::DoWork()
{
	const PFAuthenticationGetEntityRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(request.entity)
	};
	HRESULT hr = PFAuthenticationGetEntityAsync(entityHandle.Get(), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, false);
	}
}

void FPFAuthenticationGetEntityAsyncTask::ProcessResults()
{
	PFEntityHandle handle { nullptr };
	HRESULT hr = PFAuthenticationGetEntityGetResult(*mAsyncBlock, &handle);

	if (SUCCEEDED(hr))
	{
		FPFEntityHandle* entityHandlePtr = reinterpret_cast<FPFEntityHandle*>(&handle);
		delegate.ExecuteIfBound(entityHandlePtr, true);
	}
	else
	{
		delegate.ExecuteIfBound(nullptr, false);	
	}
}

#endif


#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

FPFAuthenticationGetEntityWithSecretKeyAsyncTask::FPFAuthenticationGetEntityWithSecretKeyAsyncTask(
	FPFServiceConfigHandle serviceConfigHandle,
	const FString secretKey,
	const FPFAuthenticationGetEntityRequest request,
	FOnGetEntityWithSecretKeyDelegate delegate)
	: FXAsyncTask(TEXT("FPFGetEntityWithSecretKeyAsyncTask")),
	serviceConfigHandle(serviceConfigHandle),
	secretKey(secretKey),
	request(request),
	delegate(delegate)
{
}

void FPFAuthenticationGetEntityWithSecretKeyAsyncTask::DoWork()
{
	const PFAuthenticationGetEntityRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.entity = ConvertEntityKeyToPlayfab(request.entity)
	};
	HRESULT hr = PFAuthenticationGetEntityWithSecretKeyAsync(serviceConfigHandle.Get(), ConvertFStringToCharPtr(secretKey), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, false);
	}
}

void FPFAuthenticationGetEntityWithSecretKeyAsyncTask::ProcessResults()
{
	PFEntityHandle handle { nullptr };
	HRESULT hr = PFAuthenticationGetEntityWithSecretKeyGetResult(*mAsyncBlock, &handle);

	if (SUCCEEDED(hr))
	{
		FPFEntityHandle* entityHandlePtr = reinterpret_cast<FPFEntityHandle*>(&handle);
		delegate.ExecuteIfBound(entityHandlePtr, true);
	}
	else
	{
		delegate.ExecuteIfBound(nullptr, false);	
	}
}

#endif


#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

FPFAuthenticationValidateEntityTokenAsyncTask::FPFAuthenticationValidateEntityTokenAsyncTask(
	FPFEntityHandle entityHandle,
	const FPFAuthenticationValidateEntityTokenRequest request,
	FOnValidateEntityTokenDelegate delegate)
	: FXAsyncTask(TEXT("FPFValidateEntityTokenAsyncTask")),
	entityHandle(entityHandle),
	request(request),
	delegate(delegate)
{
}

void FPFAuthenticationValidateEntityTokenAsyncTask::DoWork()
{
	const PFAuthenticationValidateEntityTokenRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.entityToken = ConvertFStringToCharPtr(request.entityToken)
	};
	HRESULT hr = PFAuthenticationValidateEntityTokenAsync(entityHandle.Get(), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, false);
	}
}

void FPFAuthenticationValidateEntityTokenAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	uint64 resultSize = 0;

	HRESULT hr = PFAuthenticationValidateEntityTokenGetResultSize(*mAsyncBlock, &resultSize); 
	
	if (SUCCEEDED(hr))
	{ 
		bufferArray.Reserve(resultSize);

		uint64 bufferUsed = 0;
		PFAuthenticationValidateEntityTokenResponse* result;
		hr = PFAuthenticationValidateEntityTokenGetResult(*mAsyncBlock, resultSize, bufferArray.GetData(), &result, &bufferUsed);

		if (SUCCEEDED(hr))
		{
			TSharedPtr<const FPFAuthenticationValidateEntityTokenResponse> ResultType = ConvertValidateEntityTokenResponseToUnreal(result);

			delegate.ExecuteIfBound(ResultType.Get(), true);
		}
		else
		{
			delegate.ExecuteIfBound(nullptr, false);	
		}
	}
	else
	{
		delegate.ExecuteIfBound(nullptr, false);
	}
}


#endif

