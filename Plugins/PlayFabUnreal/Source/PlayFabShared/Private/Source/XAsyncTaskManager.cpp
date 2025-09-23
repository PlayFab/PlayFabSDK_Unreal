#include "XAsyncTaskManager.h"
#include "Misc/ScopeLock.h"

bool FXAsyncTaskManager::Init()
{
	threadPool = FQueuedThreadPool::Allocate();
	threadPool->Create(4, 128 * 1024, TPri_Normal);
	return true;
}

uint32 FXAsyncTaskManager::Run()
{
	while (running)
	{
		// Process tasks
		FPlatformProcess::Sleep(0.01f); // Sleep to prevent 100% CPU usage
	}
	return 0;
}

void FXAsyncTaskManager::Stop()
{
	running = false;
	threadPool->Destroy();
	delete threadPool;
}

void FXAsyncTaskManager::Exit()
{
	// Cleanup logic here
}

XTaskQueueHandle FXAsyncTaskManager::GetTaskQueue() 
{
	return tasksQueue.GetQueue();
}