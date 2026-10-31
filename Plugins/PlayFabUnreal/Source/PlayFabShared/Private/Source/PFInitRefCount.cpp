#include "PFInitRefCount.h"
#include "Logging.h"

FPFInitRefCount::FPFInitRefCount(const FString& InName)
	: Name(InName)
{
}

bool FPFInitRefCount::Acquire(TFunctionRef<bool()> InitFunction)
{
	FScopeLock ScopeLock(&Lock);

	if (Count > 0)
	{
		++Count;
		return true;
	}

	if (!InitFunction())
	{
		return false;
	}

	Count = 1;
	return true;
}

FPFInitRefCount::EReleaseResult FPFInitRefCount::BeginRelease()
{
	FScopeLock ScopeLock(&Lock);

	if (Count <= 0)
	{
		return EReleaseResult::NotInitialized;
	}

	return --Count == 0 ? EReleaseResult::NeedsUninitialize : EReleaseResult::StillReferenced;
}

void FPFInitRefCount::AbortRelease()
{
	FScopeLock ScopeLock(&Lock);

	++Count;
	UE_LOG(LogPlayFabUnreal, Warning, TEXT("%s uninitialization failed; the initialization reference has been restored."), *Name);
}

bool FPFInitRefCount::Release(TFunctionRef<bool()> UninitFunction)
{
	switch (BeginRelease())
	{
	case EReleaseResult::NeedsUninitialize:
		if (!UninitFunction())
		{
			AbortRelease();
			return false;
		}
		return true;

	case EReleaseResult::StillReferenced:
		return true;

	default:
		LogUnbalancedRelease();
		return false;
	}
}

bool FPFInitRefCount::ReleaseAsync(TFunctionRef<void()> BeginTeardown, TFunctionRef<void(bool)> OnNoTeardown)
{
	switch (BeginRelease())
	{
	case EReleaseResult::NeedsUninitialize:
		BeginTeardown();
		return true;

	case EReleaseResult::StillReferenced:
		OnNoTeardown(true);
		return true;

	default:
		LogUnbalancedRelease();
		OnNoTeardown(false);
		return false;
	}
}

void FPFInitRefCount::LogUnbalancedRelease() const
{
	UE_LOG(LogPlayFabUnreal, Warning, TEXT("%s is not initialized; unbalanced uninitialize call."), *Name);
}
