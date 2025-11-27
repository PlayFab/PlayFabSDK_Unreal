// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFEventsAsyncTasks.h"

#if 0

FPFEventsDeleteDataConnectionAsyncTask::FPFEventsDeleteDataConnectionAsyncTask(
	FPFEntityHandle entityHandle,
	const FPFEventsDeleteDataConnectionRequest request,
	FOnDeleteDataConnectionDelegate delegate)
	: FXAsyncTask(TEXT("FPFDeleteDataConnectionAsyncTask")),
	entityHandle(entityHandle),
	request(request),
	delegate(delegate)
{
}

void FPFEventsDeleteDataConnectionAsyncTask::DoWork()
{
	const PFEventsDeleteDataConnectionRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.name = ConvertFStringToCharPtr(request.name)
	};
	HRESULT hr = PFEventsDeleteDataConnectionAsync(entityHandle.Get(), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, false);
	}
}

void FPFEventsDeleteDataConnectionAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	size_t resultSize = 0;

	HRESULT hr = PFEventsDeleteDataConnectionGetResultSize(*mAsyncBlock, &resultSize); 
	
	if (SUCCEEDED(hr))
	{ 
		bufferArray.Reserve(resultSize);

		PFEntityHandle handle { nullptr };
		hr = PFEventsDeleteDataConnectionGetResult(*mAsyncBlock, handle, resultSize, bufferArray.GetData(), &result, nullptr);

		if (SUCCEEDED(hr))
		{
			TSharedPtr<const FPFEventsDeleteDataConnectionResponse> ResultType = ConvertDeleteDataConnectionResponseToUnreal(&result);

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


#if 0

FPFEventsGetDataConnectionAsyncTask::FPFEventsGetDataConnectionAsyncTask(
	FPFEntityHandle entityHandle,
	const FPFEventsGetDataConnectionRequest request,
	FOnGetDataConnectionDelegate delegate)
	: FXAsyncTask(TEXT("FPFGetDataConnectionAsyncTask")),
	entityHandle(entityHandle),
	request(request),
	delegate(delegate)
{
}

void FPFEventsGetDataConnectionAsyncTask::DoWork()
{
	const PFEventsGetDataConnectionRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.name = ConvertFStringToCharPtr(request.name)
	};
	HRESULT hr = PFEventsGetDataConnectionAsync(entityHandle.Get(), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, false);
	}
}

void FPFEventsGetDataConnectionAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	size_t resultSize = 0;

	HRESULT hr = PFEventsGetDataConnectionGetResultSize(*mAsyncBlock, &resultSize); 
	
	if (SUCCEEDED(hr))
	{ 
		bufferArray.Reserve(resultSize);

		size_t bufferUsed = 0;
		PFEventsGetDataConnectionResponse* result;
		hr = PFEventsGetDataConnectionGetResult(*mAsyncBlock, resultSize, bufferArray.GetData(), &result, &bufferUsed);

		if (SUCCEEDED(hr))
		{
			TSharedPtr<const FPFEventsGetDataConnectionResponse> ResultType = ConvertGetDataConnectionResponseToUnreal(result);

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


#if 0

FPFEventsListDataConnectionsAsyncTask::FPFEventsListDataConnectionsAsyncTask(
	FPFEntityHandle entityHandle,
	const FPFEventsListDataConnectionsRequest request,
	FOnListDataConnectionsDelegate delegate)
	: FXAsyncTask(TEXT("FPFListDataConnectionsAsyncTask")),
	entityHandle(entityHandle),
	request(request),
	delegate(delegate)
{
}

void FPFEventsListDataConnectionsAsyncTask::DoWork()
{
	const PFEventsListDataConnectionsRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num()
	};
	HRESULT hr = PFEventsListDataConnectionsAsync(entityHandle.Get(), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, false);
	}
}

void FPFEventsListDataConnectionsAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	size_t resultSize = 0;

	HRESULT hr = PFEventsListDataConnectionsGetResultSize(*mAsyncBlock, &resultSize); 
	
	if (SUCCEEDED(hr))
	{ 
		bufferArray.Reserve(resultSize);

		size_t bufferUsed = 0;
		PFEventsListDataConnectionsResponse* result;
		hr = PFEventsListDataConnectionsGetResult(*mAsyncBlock, resultSize, bufferArray.GetData(), &result, &bufferUsed);

		if (SUCCEEDED(hr))
		{
			TSharedPtr<const FPFEventsListDataConnectionsResponse> ResultType = ConvertListDataConnectionsResponseToUnreal(result);

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


#if 0

FPFEventsSetDataConnectionAsyncTask::FPFEventsSetDataConnectionAsyncTask(
	FPFEntityHandle entityHandle,
	const FPFEventsSetDataConnectionRequest request,
	FOnSetDataConnectionDelegate delegate)
	: FXAsyncTask(TEXT("FPFSetDataConnectionAsyncTask")),
	entityHandle(entityHandle),
	request(request),
	delegate(delegate)
{
}

void FPFEventsSetDataConnectionAsyncTask::DoWork()
{
	const PFEventsSetDataConnectionRequest RequestType = {
		.connectionSettings = ConvertDataConnectionSettingsToPlayfab(request.connectionSettings),
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.isActive = request.isActive,
		.name = ConvertFStringToCharPtr(request.name),
		.type = ConvertDataConnectionTypeToPlayfab(MakeShared<FPFEventsDataConnectionType>(request.type))
	};
	HRESULT hr = PFEventsSetDataConnectionAsync(entityHandle.Get(), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, false);
	}
}

void FPFEventsSetDataConnectionAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	size_t resultSize = 0;

	HRESULT hr = PFEventsSetDataConnectionGetResultSize(*mAsyncBlock, &resultSize); 
	
	if (SUCCEEDED(hr))
	{ 
		bufferArray.Reserve(resultSize);

		size_t bufferUsed = 0;
		PFEventsSetDataConnectionResponse* result;
		hr = PFEventsSetDataConnectionGetResult(*mAsyncBlock, resultSize, bufferArray.GetData(), &result, &bufferUsed);

		if (SUCCEEDED(hr))
		{
			TSharedPtr<const FPFEventsSetDataConnectionResponse> ResultType = ConvertSetDataConnectionResponseToUnreal(result);

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


#if 0

FPFEventsSetDataConnectionActiveAsyncTask::FPFEventsSetDataConnectionActiveAsyncTask(
	FPFEntityHandle entityHandle,
	const FPFEventsSetDataConnectionActiveRequest request,
	FOnSetDataConnectionActiveDelegate delegate)
	: FXAsyncTask(TEXT("FPFSetDataConnectionActiveAsyncTask")),
	entityHandle(entityHandle),
	request(request),
	delegate(delegate)
{
}

void FPFEventsSetDataConnectionActiveAsyncTask::DoWork()
{
	const PFEventsSetDataConnectionActiveRequest RequestType = {
		.active = request.active,
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.name = ConvertFStringToCharPtr(request.name)
	};
	HRESULT hr = PFEventsSetDataConnectionActiveAsync(entityHandle.Get(), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, false);
	}
}

void FPFEventsSetDataConnectionActiveAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	size_t resultSize = 0;

	HRESULT hr = PFEventsSetDataConnectionActiveGetResultSize(*mAsyncBlock, &resultSize); 
	
	if (SUCCEEDED(hr))
	{ 
		bufferArray.Reserve(resultSize);

		size_t bufferUsed = 0;
		PFEventsSetDataConnectionActiveResponse* result;
		hr = PFEventsSetDataConnectionActiveGetResult(*mAsyncBlock, resultSize, bufferArray.GetData(), &result, &bufferUsed);

		if (SUCCEEDED(hr))
		{
			TSharedPtr<const FPFEventsSetDataConnectionActiveResponse> ResultType = ConvertSetDataConnectionActiveResponseToUnreal(result);

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



FPFEventsWriteEventsAsyncTask::FPFEventsWriteEventsAsyncTask(
	FPFEntityHandle entityHandle,
	const FPFEventsWriteEventsRequest request,
	FOnWriteEventsDelegate delegate)
	: FXAsyncTask(TEXT("FPFWriteEventsAsyncTask")),
	entityHandle(entityHandle),
	request(request),
	delegate(delegate)
{
}

void FPFEventsWriteEventsAsyncTask::DoWork()
{
	const PFEventsWriteEventsRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.events = ConvertUnrealArrayToPlayfab<PFEventsEventContents, FPFEventsEventContents>(request.events, ConvertEventContentsToPlayfab),
		.eventsCount = (uint32_t)request.events.Num()
	};
	HRESULT hr = PFEventsWriteEventsAsync(entityHandle.Get(), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, false);
	}
}

void FPFEventsWriteEventsAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	size_t resultSize = 0;

	HRESULT hr = PFEventsWriteEventsGetResultSize(*mAsyncBlock, &resultSize); 
	
	if (SUCCEEDED(hr))
	{ 
		bufferArray.Reserve(resultSize);

		size_t bufferUsed = 0;
		PFEventsWriteEventsResponse* result;
		hr = PFEventsWriteEventsGetResult(*mAsyncBlock, resultSize, bufferArray.GetData(), &result, &bufferUsed);

		if (SUCCEEDED(hr))
		{
			TSharedPtr<const FPFEventsWriteEventsResponse> ResultType = ConvertWriteEventsResponseToUnreal(result);

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





FPFEventsWriteTelemetryEventsAsyncTask::FPFEventsWriteTelemetryEventsAsyncTask(
	FPFEntityHandle entityHandle,
	const FPFEventsWriteEventsRequest request,
	FOnWriteTelemetryEventsDelegate delegate)
	: FXAsyncTask(TEXT("FPFWriteTelemetryEventsAsyncTask")),
	entityHandle(entityHandle),
	request(request),
	delegate(delegate)
{
}

void FPFEventsWriteTelemetryEventsAsyncTask::DoWork()
{
	const PFEventsWriteEventsRequest RequestType = {
		.customTags = ConvertFStringMapToPlayfab(request.customTags),
		.customTagsCount = (uint32_t)request.customTags.Num(),
		.events = ConvertUnrealArrayToPlayfab<PFEventsEventContents, FPFEventsEventContents>(request.events, ConvertEventContentsToPlayfab),
		.eventsCount = (uint32_t)request.events.Num()
	};
	HRESULT hr = PFEventsWriteTelemetryEventsAsync(entityHandle.Get(), &RequestType, *mAsyncBlock);

	if (FAILED(hr))
	{
		delegate.ExecuteIfBound(nullptr, false);
	}
}

void FPFEventsWriteTelemetryEventsAsyncTask::ProcessResults()
{
	TArray<uint8> bufferArray;
	size_t resultSize = 0;

	HRESULT hr = PFEventsWriteTelemetryEventsGetResultSize(*mAsyncBlock, &resultSize); 
	
	if (SUCCEEDED(hr))
	{ 
		bufferArray.Reserve(resultSize);

		size_t bufferUsed = 0;
		PFEventsWriteEventsResponse* result;
		hr = PFEventsWriteTelemetryEventsGetResult(*mAsyncBlock, resultSize, bufferArray.GetData(), &result, &bufferUsed);

		if (SUCCEEDED(hr))
		{
			TSharedPtr<const FPFEventsWriteEventsResponse> ResultType = ConvertWriteEventsResponseToUnreal(result);

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



