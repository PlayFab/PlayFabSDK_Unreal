// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#include "CoreMinimal.h"
#include "Async/AsyncWork.h"
#include "Async/Async.h"
#include "XAsyncTaskQueueHelpers.h"
#include "XAsyncTaskManager.h"
#include "XAsyncTask.h"
#include "PFEntity.h"
#include "PFServiceConfig.h"
#include "Generated/PFEventsUnrealTypes.h"
#include "Generated/PFEventsTypeConverters.h"
THIRD_PARTY_INCLUDES_START
#include <playfab/core/PFEntity.h>
#include <playfab/core/PFEvents.h>
THIRD_PARTY_INCLUDES_END

#if 0

class PLAYFABCORE_API FPFEventsDeleteDataConnectionAsyncTask : public FXAsyncTask
{
public:
	FPFEventsDeleteDataConnectionAsyncTask(
		FPFEntityHandle entityHandle,
		const FPFEventsDeleteDataConnectionRequest request,
		FOnDeleteDataConnectionDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFEntityHandle entityHandle;

	const FPFEventsDeleteDataConnectionRequest request;

	FOnDeleteDataConnectionDelegate delegate;
};

#endif

#if 0

class PLAYFABCORE_API FPFEventsGetDataConnectionAsyncTask : public FXAsyncTask
{
public:
	FPFEventsGetDataConnectionAsyncTask(
		FPFEntityHandle entityHandle,
		const FPFEventsGetDataConnectionRequest request,
		FOnGetDataConnectionDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFEntityHandle entityHandle;

	const FPFEventsGetDataConnectionRequest request;

	FOnGetDataConnectionDelegate delegate;
};

#endif

#if 0

class PLAYFABCORE_API FPFEventsListDataConnectionsAsyncTask : public FXAsyncTask
{
public:
	FPFEventsListDataConnectionsAsyncTask(
		FPFEntityHandle entityHandle,
		const FPFEventsListDataConnectionsRequest request,
		FOnListDataConnectionsDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFEntityHandle entityHandle;

	const FPFEventsListDataConnectionsRequest request;

	FOnListDataConnectionsDelegate delegate;
};

#endif

#if 0

class PLAYFABCORE_API FPFEventsSetDataConnectionAsyncTask : public FXAsyncTask
{
public:
	FPFEventsSetDataConnectionAsyncTask(
		FPFEntityHandle entityHandle,
		const FPFEventsSetDataConnectionRequest request,
		FOnSetDataConnectionDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFEntityHandle entityHandle;

	const FPFEventsSetDataConnectionRequest request;

	FOnSetDataConnectionDelegate delegate;
};

#endif

#if 0

class PLAYFABCORE_API FPFEventsSetDataConnectionActiveAsyncTask : public FXAsyncTask
{
public:
	FPFEventsSetDataConnectionActiveAsyncTask(
		FPFEntityHandle entityHandle,
		const FPFEventsSetDataConnectionActiveRequest request,
		FOnSetDataConnectionActiveDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFEntityHandle entityHandle;

	const FPFEventsSetDataConnectionActiveRequest request;

	FOnSetDataConnectionActiveDelegate delegate;
};

#endif


class PLAYFABCORE_API FPFEventsWriteEventsAsyncTask : public FXAsyncTask
{
public:
	FPFEventsWriteEventsAsyncTask(
		FPFEntityHandle entityHandle,
		const FPFEventsWriteEventsRequest request,
		FOnWriteEventsDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFEntityHandle entityHandle;

	const FPFEventsWriteEventsRequest request;

	FOnWriteEventsDelegate delegate;
};



class PLAYFABCORE_API FPFEventsWriteTelemetryEventsAsyncTask : public FXAsyncTask
{
public:
	FPFEventsWriteTelemetryEventsAsyncTask(
		FPFEntityHandle entityHandle,
		const FPFEventsWriteEventsRequest request,
		FOnWriteTelemetryEventsDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFEntityHandle entityHandle;

	const FPFEventsWriteEventsRequest request;

	FOnWriteTelemetryEventsDelegate delegate;
};

