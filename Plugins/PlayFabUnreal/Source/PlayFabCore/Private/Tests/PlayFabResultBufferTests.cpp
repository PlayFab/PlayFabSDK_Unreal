#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "PlayFabResultBuffer.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FPlayFabResultBufferBoundsTest,
	"PlayFab.Core.ResultBuffer.Bounds",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabResultBufferBoundsTest::RunTest(const FString&)
{
	TArray<uint8> Buffer;
	TestTrue(TEXT("An empty result buffer is representable"), PlayFabResultBuffer::TryAllocate(0, Buffer));
	TestEqual(TEXT("Empty result length"), Buffer.Num(), 0);
	TestTrue(TEXT("A small result allocates its full advertised capacity"), PlayFabResultBuffer::TryAllocate(16, Buffer));
	TestEqual(TEXT("Result length matches SDK capacity"), Buffer.Num(), 16);

	TestFalse(TEXT("A size beyond int32 is rejected before allocation"), PlayFabResultBuffer::TryAllocate(static_cast<size_t>(MAX_int32) + 1, Buffer));
	TestFalse(TEXT("A maximum size_t cannot wrap into an allocation size"), PlayFabResultBuffer::TryAllocate(TNumericLimits<size_t>::Max(), Buffer));
	TestEqual(TEXT("Rejected sizes do not resize the buffer"), Buffer.Num(), 16);
	return true;
}

#endif
