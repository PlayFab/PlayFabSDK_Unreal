#pragma once

#include "CoreMinimal.h"
#ifdef PF_GDK_AVAILABLE
#include "Windows/WindowsHWrapper.h"
#endif
#include "CoreTypes.h"
#include "Templates/Function.h"
#include "Templates/SharedPointer.h"
#include "Tasks/Task.h"
#include "Logging.h"
#if PLATFORM_WINDOWS || (defined(PLATFORM_XSX) && PLATFORM_XSX) || (defined(PLATFORM_XB1) && PLATFORM_XB1)
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/AllowWindowsPlatformAtomics.h"
#endif
THIRD_PARTY_INCLUDES_START
#include <httpClient/pal.h>
#include <XTaskQueue.h>
#include <XAsync.h>
THIRD_PARTY_INCLUDES_END
#if PLATFORM_WINDOWS || (defined(PLATFORM_XSX) && PLATFORM_XSX) || (defined(PLATFORM_XB1) && PLATFORM_XB1)
#include "Windows/HideWindowsPlatformAtomics.h"
#include "Windows/HideWindowsPlatformTypes.h"
#endif

/*	Wrapper for XAsyncBlock that allows capture variables in the lambda

	If lifetime management is not required, using XAsyncTask() is recommended instead
*/
typedef TFunction<void(class FXAsyncBlock*)> FXAsyncBlockDelegate;

class PLAYFABSHARED_API FXAsyncBlock
{
public:
	FXAsyncBlock(void* UserData, FXAsyncBlockDelegate Delegate, XTaskQueueHandle TaskQueue = nullptr);

	~FXAsyncBlock();

	HRESULT GetStatus();

	XAsyncBlock* GetInnerBlockForAPI();
	void* GetUserData();
	operator XAsyncBlock* () { return GetInnerBlockForAPI(); }

protected:
	XAsyncBlock AsyncBlock;
	void* UserData;
	FXAsyncBlockDelegate Delegate;

	void DelegateWrapper();
};



/*
	Wrapper for XTaskQueueHandle that manages clean shutdown automatically

	This can be used when a separate, custom task queue is required. In most cases FXAsyncTaskQueue::GetGenericQueue() should be sufficient
*/
class PLAYFABSHARED_API FXAsyncTaskQueue
{
public:
	FXAsyncTaskQueue(XTaskQueueDispatchMode WorkDispatchMode = XTaskQueueDispatchMode::ThreadPool, XTaskQueueDispatchMode CompletionDispatchMode = XTaskQueueDispatchMode::ThreadPool);
	~FXAsyncTaskQueue();

	FORCEINLINE XTaskQueueHandle GetQueue() const { return Queue; }
	HRESULT BlockUntilComplete(XAsyncBlock& AsyncBlock) const;
	void CancelPendingTasksAndDestroyQueue();


	// access to common task queues
	static XTaskQueueHandle GetGenericQueue();			// completion callbacks happen on the game thread
	static XTaskQueueHandle GetBackgroundTaskQueue();	// completion callbacks happen on a background thread

	// internal use - shutdown the queue system
	static void PlatformInit();
	static void PlatformTearDown();

protected:
	XTaskQueueDispatchMode WorkDispatchMode;
	XTaskQueueDispatchMode CompletionDispatchMode;
	XTaskQueueHandle Queue;
};



/* Helper class for executing simple XAsync tasks locally. This is expected to be created on the stack.
   (Use LocalTask() for an easier to use equivalent.)

	FLocalTaskBlock Block;
	if (SUCCEEDED( XUserAddAsync( XUserAddOptions::None, Block ) ) )
	{
		AsyncBlock.BlockUntilComplete();

		FUserHandle User;
		XUserAddResult(Block, User.GetInitReference());
	}
*/
class PLAYFABSHARED_API FLocalTaskBlock
{
public:
	FLocalTaskBlock();
	~FLocalTaskBlock();

	operator XAsyncBlock* () { return &AsyncBlock; }

	HRESULT BlockUntilComplete();
	HRESULT GetStatus();

protected:
	XAsyncBlock AsyncBlock;
	FXAsyncTaskQueue Queue;
};



/* Simple wrapper for XAsync task execution. Returns the result from InitFunction, so S_OK means the async task has started successfully

	XAsyncTask(
		[]( XAsyncBlock* Block )
		{
			return XUserAddAsync( XUserAddOptions::None, Block );
		},
		[]( XAsyncBlock* Block )
		{
			FUserHandle User;
			XUserAddResult(Block, User.GetInitReference());
		}
	);

*/
PLAYFABSHARED_API HRESULT XAsyncTask(TFunction<HRESULT(XAsyncBlock*)> InitFunction, TFunction<void(XAsyncBlock*)> ResultFunction = nullptr, XTaskQueueHandle TaskQueue = nullptr);




/* Simple wrapper for XAsync task execution that can be monitored via a helper class. Returns the result from InitFunction, so S_OK means the async task has started successfully

	FXAsyncTaskMonitor MyTask;
	XAsyncTask(
		MyTask,
		[]( XAsyncBlock* Block )
		{
			return XUserAddAsync( XUserAddOptions::None, Block );
		},
		[]( XAsyncBlock* Block )
		{
			FUserHandle User;
			XUserAddResult(Block, User.GetInitReference());
		}
	);
	MyTask.TryCancel(true);

*/
PLAYFABSHARED_API HRESULT XAsyncTask(class FXAsyncTaskMonitor& OutAsyncTaskMonitor, TFunction<HRESULT(XAsyncBlock*)> InitFunction, TFunction<void(XAsyncBlock*)> ResultFunction = nullptr, XTaskQueueHandle TaskQueue = nullptr);




/* Simple wrapper for local task execution. Blocks until the task is completed. Returns the result from InitFunction or ResultFunction

	LocalTask(
		[]( XAsyncBlock* Block )
		{
			return XUserAddAsync( XUserAddOptions::None, Block );
		},
		[]( XAsyncBlock* Block )
		{
			FUserHandle User;
			return XUserAddResult(Block, User.GetInitReference());
		}
	);

*/
PLAYFABSHARED_API HRESULT LocalTask(TFunction<HRESULT(XAsyncBlock*)> InitFunction, TFunction<HRESULT(XAsyncBlock*)> ResultFunction = nullptr);


/* Simple UE::Task wrapper for task execution. Task result contains the result from InitFunction or ResultFunction

 FTask Task = LaunchTask(
		UE_SOURCE_LOCATION,
		[]( XAsyncBlock* Block )
		{
			return XUserAddAsync( XUserAddOptions::None, Block );
		},
		[]( XAsyncBlock* Block )
		{
			FUserHandle User;
			return XUserAddResult(Block, User.GetInitReference());
		}
	);
*/
typedef UE::Tasks::TTask<HRESULT> FTask;

// launches a task for asynchronous execution
// returns a trivially relocatable instance that can be used to wait for task completion or to obtain task execution result
PLAYFABSHARED_API FTask LaunchTask(
	const TCHAR* DebugName,
	TUniqueFunction<HRESULT(XAsyncBlock*)> InitFunction,
	TUniqueFunction<HRESULT(XAsyncBlock*)> ResultFunction,
	UE::Tasks::ETaskPriority Priority = UE::Tasks::ETaskPriority::Normal);

PLAYFABSHARED_API FTask LaunchTask(
	const TCHAR* DebugName,
	class FXAsyncTaskMonitor& OutAsyncTaskMonitor,
	TUniqueFunction<HRESULT(XAsyncBlock*)> InitFunction,
	TUniqueFunction<HRESULT(XAsyncBlock*)> ResultFunction,
	UE::Tasks::ETaskPriority Priority = UE::Tasks::ETaskPriority::Normal);







/* Helper allowing cancellation from XAsyncTask() and LaunchTask() */
class PLAYFABSHARED_API FXAsyncTaskMonitor
{
public:
	// Attempt to cancel the task. Note that the ResultFunction callback will be called and the API function will likely return E_ABORT
	//  - When bWait is false, returns true if cancel request was made. 
	//  - When bWait is true it returns true if the task was successfully cancelled. This will happen before the ResultFunction is called
	//  - Returns false in all other failure cases, including if the task has already completed.
	bool TryCancel(bool bWait = true);

	// Determines if the task that we're monitoring is still valid. This will be true until the ResultFunction callback has completed
	bool IsValid() const;

protected:
	friend void Internal_InitAsyncTaskMonitor(FXAsyncTaskMonitor& TaskMonitor, TSharedPtr<FXAsyncBlock> Block);
	TWeakPtr<FXAsyncBlock> WeakBlock;
};




////#endif //WITH_GRDK
