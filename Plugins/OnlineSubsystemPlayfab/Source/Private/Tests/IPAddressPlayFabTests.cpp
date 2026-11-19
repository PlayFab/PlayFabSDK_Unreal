//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "IPAddressPlayFab.h"
#include "OnlineSubsystemPlayFabPrivate.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FPlayFabAddressBoundsTest,
	"PlayFab.OSS.Address.Bounds",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabAddressBoundsTest::RunTest(const FString&)
{
	FInternetAddrPlayFab Address;
	bool bIsValid = false;
	const FString EndpointOnly = FString(PLAYFAB_URL_PREFIX) + TEXT("42");
	TArray<TCHAR> Buffer;
	Buffer.Append(*EndpointOnly, EndpointOnly.Len() + 1);
	Buffer.Add(TEXT('9'));
	Buffer.Add(TEXT('\0'));
	Address.SetIp(Buffer.GetData(), bIsValid);
	TestTrue(TEXT("An endpoint without an explicit port is valid"), bIsValid);
	uint32 EndpointId = 0;
	Address.GetIp(EndpointId);
	TestEqual(TEXT("All endpoint digits are preserved"), EndpointId, static_cast<uint32>(42));
	TestEqual(TEXT("An omitted port defaults to the endpoint, not bytes beyond the terminator"), Address.GetPort(), 42);

	const FString WithPort = EndpointOnly + TEXT(":7");
	Address.SetIp(*WithPort, bIsValid);
	TestTrue(TEXT("An explicit port remains supported"), bIsValid);
	TestEqual(TEXT("The explicit port is preserved"), Address.GetPort(), 7);

	Address.SetIp(nullptr, bIsValid);
	TestFalse(TEXT("A null address is rejected"), bIsValid);
	Address.SetIp(PLAYFAB_URL_PREFIX, bIsValid);
	TestFalse(TEXT("An empty endpoint is rejected"), bIsValid);
	return true;
}

#endif
