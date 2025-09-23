#pragma once

#if defined(PF_GDK_AVAILABLE) || defined(PF_UE_GDK_SUPPORT)

#include "Xbox/PFAuthenticationAsyncTasks_Xbox.h"
#include <PFAuthenticationTypeConverters.h>

FPFAuthenticationLoginWithXUserAsyncTask::FPFAuthenticationLoginWithXUserAsyncTask(
	FPFServiceConfigHandle serviceConfigHandle,
	const FPFAuthenticationLoginWithXUserRequest request,
	FOnPFAuthenticationLoginCompleteDelegate delegate)
	: FXAsyncTask(TEXT("FPFAuthenticationLoginWithXUserAsyncTask")),
	serviceConfigHandle(serviceConfigHandle),
	request(request),
	delegate(delegate)
{
}

void FPFAuthenticationLoginWithXUserAsyncTask::DoWork()
{
	const PFAuthenticationLoginWithXUserRequest RequestType = {
		.createAccount = request.createAccount,
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.infoRequestParameters = ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(request.infoRequestParameters),
		.playerSecret = ConvertFStringToCharPtr(request.playerSecret),
		.user = request.user
	};

	HRESULT hr = PFAuthenticationLoginWithXUserAsync(serviceConfigHandle.Get(), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, nullptr, false);
	}
}

void FPFAuthenticationLoginWithXUserAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	uint64 resultSize = 0;

	HRESULT hr = PFAuthenticationLoginWithXUserGetResultSize(*mAsyncBlock, &resultSize);

	if (SUCCEEDED(hr))
	{
		bufferArray.Reserve(resultSize);

		PFAuthenticationLoginResult const* result;
		PFEntityHandle handle{ nullptr };
		hr = PFAuthenticationLoginWithXUserGetResult(*mAsyncBlock, &handle, resultSize, bufferArray.GetData(), &result, nullptr);

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
