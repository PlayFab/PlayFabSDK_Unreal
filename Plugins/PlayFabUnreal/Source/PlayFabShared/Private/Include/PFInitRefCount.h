#pragma once

#include "CoreMinimal.h"
#include "HAL/CriticalSection.h"
#include "Templates/Function.h"

/**
 * Reference count guarding a single initialize/uninitialize pair, so that balanced callers can
 * each initialize independently and the underlying teardown only runs once the last one releases.
 *
 * Each initialization API owns its own instance, typically a function-local static.
 */
class PLAYFABSHARED_API FPFInitRefCount
{
public:

	enum class EReleaseResult
	{
		/** Other references remain; the caller must NOT uninitialize. */
		StillReferenced,
		/** The count went 1 -> 0; the caller must uninitialize. */
		NeedsUninitialize,
		/** The count was already zero, meaning an unbalanced release. */
		NotInitialized
	};

	/**
	 * @param InName Identifies the guarded API in log messages, for example TEXT("PlayFab Core").
	 */
	explicit FPFInitRefCount(const FString& InName);

	FPFInitRefCount(const FPFInitRefCount&) = delete;
	FPFInitRefCount& operator=(const FPFInitRefCount&) = delete;

	/**
	 * Takes a reference, running InitFunction under the same lock when this is the first one, so a
	 * concurrent caller never observes the count as initialized while the initialization is still running.
	 *
	 * @param InitFunction Performs the underlying initialization. Returning false rolls the count back.
	 * @return True if the API is initialized and a reference is held by the caller.
	 */
	bool Acquire(TFunctionRef<bool()> InitFunction);

	/** Decrements the count and reports whether the caller owns the underlying teardown. */
	EReleaseResult BeginRelease();

	/** Rolls back a BeginRelease that returned NeedsUninitialize but whose teardown failed. */
	void AbortRelease();

	/**
	 * Releases a reference, running UninitFunction outside the lock only when this release owns the
	 * teardown. A false return from UninitFunction restores the reference via AbortRelease.
	 *
	 * Only usable when the teardown is synchronous. See ReleaseAsync for deferred teardowns.
	 *
	 * @return True if the API is torn down or still held by another reference; false on an
	 *         unbalanced release or a failed teardown.
	 */
	bool Release(TFunctionRef<bool()> UninitFunction);

	/**
	 * Releases a reference where the teardown completes after this call returns.
	 *
	 * @param BeginTeardown Invoked only when this release owns the teardown. It must start the
	 *                      teardown and, if that teardown ultimately fails, call AbortRelease.
	 * @param OnNoTeardown  Invoked on the paths where no teardown is started, with true when other
	 *                      references remain and false on an unbalanced release. Lets the caller
	 *                      complete its own delegate without duplicating this branching.
	 * @return True unless the release was unbalanced.
	 */
	bool ReleaseAsync(TFunctionRef<void()> BeginTeardown, TFunctionRef<void(bool)> OnNoTeardown);

private:

	void LogUnbalancedRelease() const;

	const FString Name;
	FCriticalSection Lock;
	int32 Count = 0;
};
