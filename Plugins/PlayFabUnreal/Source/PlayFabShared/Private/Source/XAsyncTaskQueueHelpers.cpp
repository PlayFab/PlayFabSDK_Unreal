#include "XAsyncTaskQueueHelpers.h"
//#if WITH_GRDK
//#include "GDKThreadCheck.h"
#include "HAL/Event.h"
#include "HAL/PlatformProcess.h"
#include "HAL/PlatformMisc.h"
#include "Containers/Ticker.h"
#include "Templates/UniquePtr.h"

#if HC_PLATFORM_IS_PLAYSTATION

#define INFINITE						0xFFFFFFFF  // Infinite timeout
#define ERROR_INVALID_PARAMETER			87L    // dderror
#define ERROR_INVALID_FUNCTION			1L    // dderror
HRESULT HRESULT_FROM_WIN32(unsigned long x) { return (HRESULT)(x) <= 0 ? (HRESULT)(x) : (HRESULT)(((x) & 0x0000FFFF) | (FACILITY_WIN32 << 16) | 0x80000000); }

#endif

FXAsyncBlock::FXAsyncBlock(void* InUserData, FXAsyncBlockDelegate InDelegate, XTaskQueueHandle TaskQueue)
	: UserData(InUserData)
	, Delegate(MoveTemp(InDelegate))
{
	// init to zero
	AsyncBlock = XAsyncBlock{ 0 };

	// default to our generic queue
	AsyncBlock.queue = TaskQueue ? TaskQueue : FXAsyncTaskQueue::GetGenericQueue();
	AsyncBlock.context = this;

	// wrap the delegate with AsyncBlock callback
	if (Delegate)
	{
		AsyncBlock.callback = [](XAsyncBlock* InnerBlock)
			{
				// get our wrapper object
				((FXAsyncBlock*)InnerBlock->context)->DelegateWrapper();
			};
	}
}



FXAsyncBlock::~FXAsyncBlock()
{
	if (XAsyncGetStatus(&AsyncBlock, false) == E_PENDING)
	{
		UE_LOG(LogPlayFabUnreal, Warning, TEXT("[FXAsyncBlock::~FXAsyncBlock] AsyncBlock still pending for task. Cancelling and firing callback."));
		XAsyncCancel(&AsyncBlock);
	}
}

void FXAsyncBlock::DelegateWrapper()
{
	// call the delegate
	if (Delegate)
	{
		Delegate(this);
	}
}

XAsyncBlock* FXAsyncBlock::GetInnerBlockForAPI()
{
	return &AsyncBlock;
}

void* FXAsyncBlock::GetUserData()
{
	return UserData;
}

HRESULT FXAsyncBlock::GetStatus()
{
	return XAsyncGetStatus(&AsyncBlock, false);
}



class FThreadPoolTaskQueue : public FXAsyncTaskQueue
{
public:
	FThreadPoolTaskQueue()
		: FXAsyncTaskQueue(XTaskQueueDispatchMode::ThreadPool, XTaskQueueDispatchMode::Manual)
	{
		TickHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateLambda([this](float)
			{
				XTaskQueueDispatch(Queue, XTaskQueuePort::Completion, 0);
				return true;
			}));
	}

	~FThreadPoolTaskQueue()
	{
		FTSTicker::GetCoreTicker().RemoveTicker(TickHandle);
	}

private:
	FTSTicker::FDelegateHandle TickHandle;
};




class FBackgroundTaskQueue : public FXAsyncTaskQueue
{
public:
	FBackgroundTaskQueue()
		: FXAsyncTaskQueue(XTaskQueueDispatchMode::ThreadPool, XTaskQueueDispatchMode::ThreadPool)
	{
	}
};





static bool bIsTornDown = false;
static TUniquePtr<FThreadPoolTaskQueue> GThreadPoolTaskQueue;
static TUniquePtr<FBackgroundTaskQueue> GBackgroundTaskQueue;

void FXAsyncTaskQueue::PlatformTearDown()
{
	check(!bIsTornDown);
	bIsTornDown = true;

	// destroy our task queues
	GThreadPoolTaskQueue.Reset();
	GBackgroundTaskQueue.Reset();
}

XTaskQueueHandle FXAsyncTaskQueue::GetGenericQueue()
{
	check(!bIsTornDown);

	if (!GThreadPoolTaskQueue.IsValid())
	{
		GThreadPoolTaskQueue = MakeUnique<FThreadPoolTaskQueue>();
	}

	return GThreadPoolTaskQueue->GetQueue();
}

XTaskQueueHandle FXAsyncTaskQueue::GetBackgroundTaskQueue()
{
	check(!bIsTornDown);

	if (!GBackgroundTaskQueue.IsValid())
	{
		GBackgroundTaskQueue = MakeUnique<FBackgroundTaskQueue>();
	}

	return GBackgroundTaskQueue->GetQueue();
}






FXAsyncTaskQueue::FXAsyncTaskQueue(XTaskQueueDispatchMode InWorkDispatchMode, XTaskQueueDispatchMode InCompletionDispatchMode)
	: WorkDispatchMode(InWorkDispatchMode)
	, CompletionDispatchMode(InCompletionDispatchMode)
{
	HRESULT hResult = XTaskQueueCreate(WorkDispatchMode, CompletionDispatchMode, &Queue);
	checkf(SUCCEEDED(hResult), TEXT("XTaskQueueCreate failed: 0x%x"), hResult);
}

FXAsyncTaskQueue::~FXAsyncTaskQueue()
{
	CancelPendingTasksAndDestroyQueue();
}

void FXAsyncTaskQueue::CancelPendingTasksAndDestroyQueue()
{
	if (Queue != nullptr)
	{
		// add a terminiation marker into the queue that sets an event when it has completed
		FEvent* QueueTerminated = FPlatformProcess::GetSynchEventFromPool(false);
		XTaskQueueTerminate(Queue, false, (void*)QueueTerminated, [](void* Context)
			{
				((FEvent*)Context)->Trigger();
			});

		// keep dispatching the queue until it has terminated
		do
		{
			// dispatch any outstanding work
			if (WorkDispatchMode == XTaskQueueDispatchMode::Manual)
			{
				XTaskQueueDispatch(Queue, XTaskQueuePort::Work, INFINITE);
			}

			// dispatch any outstanding completion - including the termination callback
			if (CompletionDispatchMode == XTaskQueueDispatchMode::Manual)
			{
				XTaskQueueDispatch(Queue, XTaskQueuePort::Completion, INFINITE);
			}

		} while (!QueueTerminated->Wait(0));

		// clean up
		FPlatformProcess::ReturnSynchEventToPool(QueueTerminated);
		XTaskQueueCloseHandle(Queue);
		Queue = nullptr;
	}
}

HRESULT FXAsyncTaskQueue::BlockUntilComplete(XAsyncBlock& AsyncBlock) const
{
	check(Queue);

	HRESULT hResult;

	// wait until the block is complete, with special handling for game thread
	while ((hResult = XAsyncGetStatus(&AsyncBlock, false)) == E_PENDING)
	{
		if (IsInGameThread())
		{
			FPlatformMisc::PumpMessagesOutsideMainLoop();
		}

		// dispatch any outstanding work (NB. attempting a dispatch on a non-Manual queue will result in an XError callback for illegal access)
		if (WorkDispatchMode == XTaskQueueDispatchMode::Manual)
		{
			XTaskQueueDispatch(Queue, XTaskQueuePort::Work, 0);
		}

		// dispatch any outstanding completion
		if (CompletionDispatchMode == XTaskQueueDispatchMode::Manual)
		{
			XTaskQueueDispatch(Queue, XTaskQueuePort::Completion, 0);
		}
	}

	return hResult;
}










FLocalTaskBlock::FLocalTaskBlock()
	: AsyncBlock(XAsyncBlock{ 0 })
	, Queue(XTaskQueueDispatchMode::ThreadPool, XTaskQueueDispatchMode::Manual)
{
	AsyncBlock.queue = Queue.GetQueue();
}

FLocalTaskBlock::~FLocalTaskBlock()
{
	check(XAsyncGetStatus(&AsyncBlock, false) != E_PENDING);
}

HRESULT FLocalTaskBlock::BlockUntilComplete()
{
	return Queue.BlockUntilComplete(AsyncBlock);
}

HRESULT FLocalTaskBlock::GetStatus()
{
	return XAsyncGetStatus(&AsyncBlock, false);
}





bool FXAsyncTaskMonitor::TryCancel(bool bWait)
{
	TSharedPtr<FXAsyncBlock> PinnedBlock = WeakBlock.Pin();
	if (PinnedBlock.IsValid())
	{
		XAsyncBlock* AsyncBlock = PinnedBlock->GetInnerBlockForAPI();
		HRESULT hResult = XAsyncGetStatus(AsyncBlock, false);
		if (hResult == E_PENDING)
		{
			XAsyncCancel(AsyncBlock);

			if (bWait)
			{
				while (hResult == E_PENDING)
				{
					if (IsInGameThread())
					{
						FPlatformMisc::PumpMessagesOutsideMainLoop();
					}

					hResult = XAsyncGetStatus(AsyncBlock, false);
				}
			}

			return true;
		}
	}

	return false;
}

bool FXAsyncTaskMonitor::IsValid() const
{
	return WeakBlock.IsValid() && WeakBlock.Pin().IsValid();
}


void Internal_InitAsyncTaskMonitor(FXAsyncTaskMonitor& TaskMonitor, TSharedPtr<FXAsyncBlock> Block)
{
	TaskMonitor.WeakBlock = Block;
}





HRESULT XAsyncTask(TFunction<HRESULT(XAsyncBlock*)> InitFunction, TFunction<void(XAsyncBlock*)> ResultFunction, XTaskQueueHandle TaskQueue)
{
	FXAsyncTaskMonitor UnusedMonitor;
	return XAsyncTask(UnusedMonitor, MoveTemp(InitFunction), MoveTemp(ResultFunction), TaskQueue);
}

HRESULT XAsyncTask(FXAsyncTaskMonitor& OutAsyncTaskMonitor, TFunction<HRESULT(XAsyncBlock*)> InitFunction, TFunction<void(XAsyncBlock*)> ResultFunction, XTaskQueueHandle TaskQueue)
{
	// sanity check parameters
	if (InitFunction == nullptr)
	{
		Internal_InitAsyncTaskMonitor(OutAsyncTaskMonitor, nullptr);
		return ERROR_INVALID_PARAMETER;
	}

	// callback context
	struct FContext
	{
		TSharedPtr<FXAsyncBlock> TaskBlock;
	};
	FContext* Context = new FContext();

	// completion callback
	auto OnTaskComplete = [ResultFunction](FXAsyncBlock* TaskBlock)
		{
			FContext* Context = (FContext*)TaskBlock->GetUserData();
			check(TaskBlock == Context->TaskBlock.Get());

			if (ResultFunction)
			{
				ResultFunction(*TaskBlock);
			}

			delete Context;
		};

	// create the async task block and try to get started
	Context->TaskBlock = MakeShared<FXAsyncBlock>(Context, OnTaskComplete, TaskQueue);
	Internal_InitAsyncTaskMonitor(OutAsyncTaskMonitor, Context->TaskBlock);

	HRESULT hResult = InitFunction(Context->TaskBlock->GetInnerBlockForAPI());
	if (FAILED(hResult))
	{
		delete Context;
	}

	return hResult;
}



HRESULT LocalTask(TFunction<HRESULT(XAsyncBlock*)> InitFunction, TFunction<HRESULT(XAsyncBlock*)> ResultFunction)
{
	// sanity check parameters
	if (InitFunction == nullptr)
	{
		return ERROR_INVALID_PARAMETER;
	}

	// run the local task
	FLocalTaskBlock Block;
	HRESULT hResult = InitFunction(Block);
	if (SUCCEEDED(hResult))
	{
		hResult = Block.BlockUntilComplete();
		if (SUCCEEDED(hResult) && ResultFunction)
		{
			hResult = ResultFunction(Block);
		}
	}

	return hResult;
}



namespace XPrivate
{
	class FTaskContext
	{
	public:
		FTaskContext();
		void Init(TUniqueFunction<HRESULT(XAsyncBlock*)> InitFunction);
		HRESULT Complete(TUniqueFunction<HRESULT(XAsyncBlock*)> ResultFunction);
		UE::Tasks::FTaskEvent AsyncCompleted;

		HRESULT hResult;
		TSharedPtr<FXAsyncBlock> AsyncBlock;
	};


	FTaskContext::FTaskContext()
		: AsyncCompleted(UE_SOURCE_LOCATION)
		, hResult(HRESULT_FROM_WIN32(ERROR_INVALID_FUNCTION))
	{
		// prepare the async task block
		AsyncBlock = MakeShared<FXAsyncBlock>(
			nullptr,
			[this](FXAsyncBlock* TaskBlock)
			{
				AsyncCompleted.Trigger();
			},
			FXAsyncTaskQueue::GetBackgroundTaskQueue() // always use background task queue: we know the completion callback just sets the trigger, so no need to manage that from the gamethread
		);
	}

	void FTaskContext::Init(TUniqueFunction<HRESULT(XAsyncBlock*)> InitFunction)
	{
		// init callback - if it fails then trigger immediately
		hResult = InitFunction(AsyncBlock->GetInnerBlockForAPI());
		if (FAILED(hResult))
		{
			AsyncCompleted.Trigger();
		}
	}

	HRESULT FTaskContext::Complete(TUniqueFunction<HRESULT(XAsyncBlock*)> ResultFunction)
	{
		// completion callback - only call if the init callback succeeded
		if (SUCCEEDED(hResult) && ResultFunction)
		{
			hResult = ResultFunction(AsyncBlock->GetInnerBlockForAPI());
		}
		return hResult;
	}
}


FTask LaunchTask(const TCHAR* DebugName, TUniqueFunction<HRESULT(XAsyncBlock*)> InitFunction, TUniqueFunction<HRESULT(XAsyncBlock*)> ResultFunction, UE::Tasks::ETaskPriority Priority)
{
	FXAsyncTaskMonitor UnusedMonitor;
	return LaunchTask(DebugName, UnusedMonitor, MoveTemp(InitFunction), MoveTemp(ResultFunction), Priority);
}

FTask LaunchTask(const TCHAR* DebugName, FXAsyncTaskMonitor& OutAsyncTaskMonitor, TUniqueFunction<HRESULT(XAsyncBlock*)> InitFunction, TUniqueFunction<HRESULT(XAsyncBlock*)> ResultFunction, UE::Tasks::ETaskPriority Priority)
{
	TUniquePtr<XPrivate::FTaskContext> Context = MakeUnique<XPrivate::FTaskContext>();
	Internal_InitAsyncTaskMonitor(OutAsyncTaskMonitor, Context->AsyncBlock);

	// run init
	Context->Init(MoveTemp(InitFunction));

	// run result task after init & the context completion
	return Launch(DebugName,
		[Context = MoveTemp(Context), ResultFunction = MoveTemp(ResultFunction)]() mutable
		{
			return Context->Complete(MoveTemp(ResultFunction));
		},
		Context->AsyncCompleted,
		Priority
	);
}


//#endif //WITH_GRDK
