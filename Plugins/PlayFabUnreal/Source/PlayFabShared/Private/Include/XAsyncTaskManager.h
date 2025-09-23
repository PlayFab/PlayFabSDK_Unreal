#pragma once

#include "CoreMinimal.h"
#include "Async/AsyncWork.h"
#include "Async/Async.h"
#include "Templates/UniquePtr.h"
#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"
#include <memory>
#include "XAsyncTaskQueueHelpers.h"

/**
 * Class representing a manager for asynchronous tasks.
 */
class PLAYFABSHARED_API FXAsyncTaskManager : public FRunnable
{
private:

	FQueuedThreadPool* threadPool;
	bool running = true;

protected:

	FXAsyncTaskQueue tasksQueue;

public:
	/**
	* Constructor to initialize the async task manager.
	*/
	FXAsyncTaskManager() = default;

	/**
	* Destructor to clean up the async task manager.
	*/
	~FXAsyncTaskManager() = default;

	/**
	* Initialize the async task manager.
	* @return True if initialization was successful, false otherwise.
	*/
	bool Init() override;

	/**
	* Run the async task manager.
	* @return The exit code of the thread.
	*/
	uint32 Run() override;

	/**
	* Stop the async task manager.
	*/
	void Stop() override;

	/**
	* Exit the async task manager.
	*/
	virtual void Exit() override;

	/**
	* Add a new task to the async task manager.
	* @param InArgs - Arguments to be passed to the task constructor.
	*/
	template<typename TaskType, typename... Args>
	void AddTask(Args&&... args)
	{
		//TSharedPtr<FAsyncTask<TaskType>> task = MakeShared<FAsyncTask<TaskType>>(Forward<Args>(args)...);
		FAsyncTask<TaskType>* task = new FAsyncTask<TaskType>(Forward<Args>(args)...);
		//std::shared_ptr<FAsyncTask<TaskType>> task = std::make_shared<FAsyncTask<TaskType>>(std::forward<Args>(args)...);
		task->StartBackgroundTask(threadPool);
	}

	/**
	* Get the task queue handle.
	* @return The task queue handle.
	*/
	XTaskQueueHandle GetTaskQueue();
};

/**
 * Singleton class for managing the async task manager.
 */
class PLAYFABSHARED_API FXAsyncTaskManagerSingleton
{
public:
	/**
	* Get the singleton instance of the async task manager.
	* @return The singleton instance.
	*/
	static FXAsyncTaskManagerSingleton& Get()
	{
		static FXAsyncTaskManagerSingleton instance;
		return instance;
	}

	/**
	* Start the async task manager.
	*/
	void Initialize()
	{
		if (!mTaskManagerRunnable)
		{
			mTaskManagerRunnable = MakeUnique<FXAsyncTaskManager>();
			mTaskManagerThread = FRunnableThread::Create(mTaskManagerRunnable.Get(), TEXT("PlayFabUnrealTaskManagerThread"), 0, TPri_Normal);
		}
	}

	/**
	* Get the runnable instance of the async task manager.
	* Automatically initializes if not already initialized.
	* @return A pointer to the async task manager.
	*/
	FXAsyncTaskManager* GetTaskManagerRunnable()
	{
		if (!mTaskManagerRunnable)
		{
			Initialize();
		}
		return mTaskManagerRunnable.Get();
	}

	/**
	* Shutdown the async task manager thread.
	*/
	void Shutdown()
	{
		if (mTaskManagerThread)
		{
			mTaskManagerThread->Kill(true);
			delete mTaskManagerThread;
			mTaskManagerThread = nullptr;
			mTaskManagerRunnable.Reset();
		}
	}

private:
	FXAsyncTaskManagerSingleton() = default;
	~FXAsyncTaskManagerSingleton() = default;
	FXAsyncTaskManagerSingleton(const FXAsyncTaskManagerSingleton&) = delete;
	FXAsyncTaskManagerSingleton& operator=(const FXAsyncTaskManagerSingleton&) = delete;

	TUniquePtr<FXAsyncTaskManager> mTaskManagerRunnable;
	FRunnableThread* mTaskManagerThread = nullptr;
};