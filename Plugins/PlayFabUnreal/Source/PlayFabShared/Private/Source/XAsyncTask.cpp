#include "XAsyncTask.h"

FXAsyncTask::FXAsyncTask(const FString& asyncTaskName, XTaskQueueHandle InTaskQueue)
	: mAsyncTaskName(asyncTaskName)
	, mTaskQueue(InTaskQueue)
{
	mAsyncBlock = CreateAsyncBlock();
}

FXAsyncTask::~FXAsyncTask()
{
	for (FXAsyncBlockPtr asyncBlockLocal : mAsyncBlocks)
	{
		checkf(!asyncBlockLocal.IsValid() || XAsyncGetStatus(asyncBlockLocal->GetInnerBlockForAPI(), false) != E_PENDING,
			TEXT("[FOnlineAsyncTaskGDK::~FOnlineAsyncTaskGDK] AsyncBlock still pending on AsyncTask destruction for task %s"), *mAsyncTaskName);
	}
}

FXAsyncBlockPtr FXAsyncTask::CreateAsyncBlock(void* userData, FXAsyncBlockDelegate delegate)
{
	// Run completion on this task's queue (mTaskQueue). nullptr keeps the historical behavior
	// (generic queue => game-thread completion) for every task that doesn't opt in.
	FXAsyncBlockPtr localAsyncBlock = MakeShared<FXAsyncBlock>(userData, delegate, mTaskQueue);
	mAsyncBlocks.Add(localAsyncBlock);
	return localAsyncBlock;
}

void FXAsyncTask::RemoveAsyncBlock(FXAsyncBlockPtr asyncBlock)
{
	if (asyncBlock.IsValid())
	{
		mAsyncBlocks.Remove(asyncBlock);
	}
}

FXAsyncBlockPtr FXAsyncTask::FindAsyncBlock(XAsyncBlock* asyncBlock)
{
	for (FXAsyncBlockPtr asyncBlockPtr : mAsyncBlocks)
	{
		if (asyncBlockPtr->GetInnerBlockForAPI() == asyncBlock)
		{
			return asyncBlockPtr;
		}
	}

	return nullptr;
}

FXAsyncBlockPtr FXAsyncTask::CreateAsyncBlock()
{
	return CreateAsyncBlock(nullptr, [this](FXAsyncBlock* LambdaAsyncBlock) {
		ProcessResults();
	});
}

TStatId FXAsyncTask::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(FXAsyncTask, STATGROUP_ThreadPoolAsyncTasks);
}