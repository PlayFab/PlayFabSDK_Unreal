//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "PlayFabSocket.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FPlayFabSocketSendMessageTimeoutConfigTest,
	"PlayFab.OSS.Socket.SendMessageTimeout.NormalizesConfiguredValue",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabSocketSendMessageTimeoutConfigTest::RunTest(const FString&)
{
	TestEqual(
		TEXT("Default timeout is preserved"),
		PlayFabSocketConfig::NormalizeSendMessageTimeoutMs(PlayFabSocketConfig::DefaultSendMessageTimeoutMs),
		static_cast<uint32>(PlayFabSocketConfig::DefaultSendMessageTimeoutMs));
	TestEqual(
		TEXT("Minimum timeout is preserved"),
		PlayFabSocketConfig::NormalizeSendMessageTimeoutMs(PlayFabSocketConfig::MinSendMessageTimeoutMs),
		static_cast<uint32>(PlayFabSocketConfig::MinSendMessageTimeoutMs));
	TestEqual(
		TEXT("Maximum timeout is preserved"),
		PlayFabSocketConfig::NormalizeSendMessageTimeoutMs(PlayFabSocketConfig::MaxSendMessageTimeoutMs),
		static_cast<uint32>(PlayFabSocketConfig::MaxSendMessageTimeoutMs));
	TestEqual(
		TEXT("Zero is clamped to a finite timeout"),
		PlayFabSocketConfig::NormalizeSendMessageTimeoutMs(0),
		static_cast<uint32>(PlayFabSocketConfig::MinSendMessageTimeoutMs));
	TestEqual(
		TEXT("Negative values are clamped without unsigned wraparound"),
		PlayFabSocketConfig::NormalizeSendMessageTimeoutMs(-1),
		static_cast<uint32>(PlayFabSocketConfig::MinSendMessageTimeoutMs));
	TestEqual(
		TEXT("Values above the maximum are clamped"),
		PlayFabSocketConfig::NormalizeSendMessageTimeoutMs(PlayFabSocketConfig::MaxSendMessageTimeoutMs + 1),
		static_cast<uint32>(PlayFabSocketConfig::MaxSendMessageTimeoutMs));
	return true;
}

#endif