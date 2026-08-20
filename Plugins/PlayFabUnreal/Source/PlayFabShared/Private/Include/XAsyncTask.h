#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Templates/SharedPointer.h"
#include "Async/AsyncWork.h"
#include "Containers/Ticker.h"
#include "XAsyncTaskQueueHelpers.h"

#ifndef PACKAGE_SCOPE
#define PACKAGE_SCOPE public
#endif

typedef TSharedPtr<FXAsyncBlock> FXAsyncBlockPtr;

/**
 * Class representing an asynchronous task.
 */
class PLAYFABSHARED_API FXAsyncTask : public FNonAbandonableTask
{
PACKAGE_SCOPE:
	TArray<FXAsyncBlockPtr> mAsyncBlocks;
	FXAsyncBlockPtr mAsyncBlock;
	FString mAsyncTaskName;
	FTSTicker::FDelegateHandle mTickHandle;
	// Queue this task's async-block completion runs on. nullptr => shared generic queue
	// (game-thread completion). See the constructor doc for why GameSave overrides this.
	XTaskQueueHandle mTaskQueue = nullptr;

protected:
	FXAsyncTask() = delete;

	/**
	* Constructor to initialize the async task with a name.
	* @param InAsyncTaskName - The name of the async task.
	* @param InTaskQueue - Optional XTaskQueue to run this task's async-block completion on.
	*                      Defaults to nullptr, which uses the shared generic queue (completion
	*                      pumped on the game thread via the core ticker) — unchanged behavior
	*                      for all existing tasks. Pass FXAsyncTaskQueue::GetBackgroundTaskQueue()
	*                      to complete on an MTA thread-pool worker instead (required for the
	*                      GameSave WithUi tasks, whose completion makes blocking cross-process
	*                      calls that must NOT run on the game thread or they deadlock the modal
	*                      sync-UX handshake with the out-of-process GRTS provider).
	*/
	explicit FXAsyncTask(const FString& asyncTaskName, XTaskQueueHandle InTaskQueue = nullptr);

	/**
	 * Destructor for the FXAsyncTask class.
	 * This destructor ensures that any resources held by the async task are properly released.
	 */
	virtual ~FXAsyncTask();

	/**
	* Create a new async block for an async call.
	* @param UserData - User data to be passed to the async block.
	* @param Delegate - Delegate to be called when the async block is processed.
	* @return A shared pointer to the created async block.
	*/
	FXAsyncBlockPtr CreateAsyncBlock(void* userData, FXAsyncBlockDelegate delegate);

	/**
	* Remove an async block from the list of async blocks.
	* @param InAsyncBlock - The async block to be removed.
	*/
	void RemoveAsyncBlock(FXAsyncBlockPtr asyncBlock);

	/**
	* Find an async block by its inner block.
	* @param asyncBlock - The inner block to search for.
	* @return A shared pointer to the found async block, or nullptr if not found.
	*/
	FXAsyncBlockPtr FindAsyncBlock(XAsyncBlock* asyncBlock);

	/**
	* Create a new async block with default parameters.
	* @return A shared pointer to the created async block.
	*/
	FXAsyncBlockPtr CreateAsyncBlock();

	/**
	* Perform the work of the async task.
	* This method should be overridden by derived classes to perform the actual work.
	*/
	virtual void DoWork() = 0;

	/**
	* Process the results of the async task.
	* This method should be overridden by derived classes to handle the results.
	*/
	virtual void ProcessResults() = 0;

public:
	/**
	* Get the stat ID for this async task.
	* @return The stat ID.
	*/
	TStatId GetStatId() const;
};
