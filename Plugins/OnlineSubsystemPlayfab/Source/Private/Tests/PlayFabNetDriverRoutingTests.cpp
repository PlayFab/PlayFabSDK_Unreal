//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "PlayFabNetDriver.h"
#include "PlayFabNetDriverRouting.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FPlayFabNetDriverRoutingRelinkTest,
	"PlayFab.OSS.NetDriverRouting.RelinkRemovesOldNetwork",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabNetDriverRoutingRelinkTest::RunTest(const FString&)
{
	UPlayFabNetDriver* NetDriver = NewObject<UPlayFabNetDriver>();
	int32 FirstNetworkStorage = 0;
	int32 SecondNetworkStorage = 0;
	Party::PartyNetwork* FirstNetwork = reinterpret_cast<Party::PartyNetwork*>(&FirstNetworkStorage);
	Party::PartyNetwork* SecondNetwork = reinterpret_cast<Party::PartyNetwork*>(&SecondNetworkStorage);

	PlayFabNetDriverRouting::Reset();
	PlayFabNetDriverRouting::Link(FirstNetwork, NetDriver);
	PlayFabNetDriverRouting::Link(SecondNetwork, NetDriver);

	TestNull(TEXT("Relinking removes the driver's previous network route"), PlayFabNetDriverRouting::Get(FirstNetwork));
	TestEqual(TEXT("Relinking records the new network route"), PlayFabNetDriverRouting::Get(SecondNetwork), NetDriver);
	PlayFabNetDriverRouting::Reset();
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FPlayFabNetDriverRoutingUnlinkTest,
	"PlayFab.OSS.NetDriverRouting.UnlinkRequiresMatchingDriver",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabNetDriverRoutingUnlinkTest::RunTest(const FString&)
{
	UPlayFabNetDriver* LinkedNetDriver = NewObject<UPlayFabNetDriver>();
	UPlayFabNetDriver* OtherNetDriver = NewObject<UPlayFabNetDriver>();
	int32 NetworkStorage = 0;
	Party::PartyNetwork* Network = reinterpret_cast<Party::PartyNetwork*>(&NetworkStorage);

	PlayFabNetDriverRouting::Reset();
	PlayFabNetDriverRouting::Link(Network, LinkedNetDriver);
	PlayFabNetDriverRouting::Unlink(Network, OtherNetDriver);
	TestEqual(TEXT("A different driver cannot remove the route"), PlayFabNetDriverRouting::Get(Network), LinkedNetDriver);

	PlayFabNetDriverRouting::Unlink(Network, LinkedNetDriver);
	TestNull(TEXT("The matching driver removes the route"), PlayFabNetDriverRouting::Get(Network));
	PlayFabNetDriverRouting::Reset();
	return true;
}

#endif
