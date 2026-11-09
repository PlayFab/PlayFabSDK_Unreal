#pragma once

#include "CoreMinimal.h"
#include "Logging.h"

namespace PlayFabResultBuffer
{
	inline bool TryAllocate(size_t Size, TArray<uint8>& Buffer)
	{
		if (Size > static_cast<size_t>(MAX_int32))
		{
			UE_LOG(LogPlayFabUnreal, Warning, TEXT("PlayFab result buffer size %llu exceeds TArray capacity"), static_cast<unsigned long long>(Size));
			return false;
		}

		Buffer.SetNumUninitialized(static_cast<int32>(Size));
		return true;
	}
}
