//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "PlayFabVoiceInitialization.h"

namespace
{
	class FTestVoiceInterface
	{
	public:
		explicit FTestVoiceInterface(bool bInInitResult)
			: bInitResult(bInInitResult)
		{
		}

		bool Init()
		{
			++InitCallCount;
			return bInitResult;
		}

		int32 InitCallCount = 0;

	private:
		bool bInitResult;
	};
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FPlayFabVoiceEnabledConfigTest,
	"PlayFab.OSS.Voice.Initialization.ConfigPolicy",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabVoiceEnabledConfigTest::RunTest(const FString&)
{
	TestTrue(TEXT("Voice defaults to enabled when the setting is absent"), PlayFabVoiceInitialization::IsEnabled(false, true));
	TestTrue(TEXT("Voice remains enabled when configured true"), PlayFabVoiceInitialization::IsEnabled(true, true));
	TestFalse(TEXT("Voice is disabled when configured false"), PlayFabVoiceInitialization::IsEnabled(true, false));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FPlayFabVoiceSuccessfulInitializationTest,
	"PlayFab.OSS.Voice.Initialization.SuccessPublishesInterface",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabVoiceSuccessfulInitializationTest::RunTest(const FString&)
{
	TSharedPtr<FTestVoiceInterface, ESPMode::ThreadSafe> Candidate = MakeShared<FTestVoiceInterface, ESPMode::ThreadSafe>(true);
	const TSharedPtr<FTestVoiceInterface, ESPMode::ThreadSafe> Result = PlayFabVoiceInitialization::Initialize(Candidate);

	TestTrue(TEXT("Successful initialization publishes the candidate"), Result == Candidate);
	TestEqual(TEXT("Initialization is attempted once"), Candidate->InitCallCount, 1);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FPlayFabVoiceFailedInitializationTest,
	"PlayFab.OSS.Voice.Initialization.FailureDoesNotPublishInterface",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabVoiceFailedInitializationTest::RunTest(const FString&)
{
	TSharedPtr<FTestVoiceInterface, ESPMode::ThreadSafe> Candidate = MakeShared<FTestVoiceInterface, ESPMode::ThreadSafe>(false);
	const TSharedPtr<FTestVoiceInterface, ESPMode::ThreadSafe> Result = PlayFabVoiceInitialization::Initialize(Candidate);

	TestFalse(TEXT("Failed initialization does not publish the candidate"), Result.IsValid());
	TestEqual(TEXT("Initialization is attempted once"), Candidate->InitCallCount, 1);
	return true;
}

#endif