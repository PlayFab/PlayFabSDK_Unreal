//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "CoreMinimal.h"

#if WITH_DEV_AUTOMATION_TESTS && !UE_BUILD_SHIPPING

#include "Misc/AutomationTest.h"
#include "PlayFabPartyConfig.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FPlayFabPartyDebugConnectivityConfigTest,
	"PlayFab.OSS.Party.Config.DebugConnectivityPreservationIsOptIn",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabPartyDebugConnectivityConfigTest::RunTest(const FString&)
{
	TestFalse(
		TEXT("Missing config leaves debug connectivity preservation disabled"),
		PlayFabPartyConfig::ShouldUseDebugConnectivityPreservationMode(false, false));
	TestFalse(
		TEXT("Explicit false leaves debug connectivity preservation disabled"),
		PlayFabPartyConfig::ShouldUseDebugConnectivityPreservationMode(true, false));
	TestTrue(
		TEXT("Explicit true enables debug connectivity preservation"),
		PlayFabPartyConfig::ShouldUseDebugConnectivityPreservationMode(true, true));
	return true;
}

#endif