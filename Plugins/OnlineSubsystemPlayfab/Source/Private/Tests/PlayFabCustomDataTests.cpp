#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "PlayFabCustomData.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FPlayFabCustomDataConfigurationTest,
	"PlayFab.OSS.CustomData.Configuration",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabCustomDataConfigurationTest::RunTest(const FString&)
{
	FConfigFile MissingConfig;
	TestFalse(TEXT("The endpoint is disabled when the option is absent"), PlayFabCustomData::IsEnabled(MissingConfig));

	FConfigFile EnabledConfig;
	EnabledConfig.ProcessInputFileContents(TEXT("[OnlineSubsystemPlayFab]\nbEnableCustomDataEndpoint=true\n"), TEXT("CustomDataEnabledTest.ini"));
	TestTrue(TEXT("The v1 opt-in setting enables the endpoint"), PlayFabCustomData::IsEnabled(EnabledConfig));

	FConfigFile DisabledConfig;
	DisabledConfig.ProcessInputFileContents(TEXT("[OnlineSubsystemPlayFab]\nbEnableCustomDataEndpoint=false\n"), TEXT("CustomDataDisabledTest.ini"));
	TestFalse(TEXT("An explicit false setting disables the endpoint"), PlayFabCustomData::IsEnabled(DisabledConfig));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FPlayFabCustomDataChannelValueTest,
	"PlayFab.OSS.CustomData.ChannelValue",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabCustomDataChannelValueTest::RunTest(const FString&)
{
	PartyDataBuffer Matching{ const_cast<ANSICHAR*>(PlayFabCustomData::ChannelValue), static_cast<uint32>(sizeof(PlayFabCustomData::ChannelValue)) };
	ANSICHAR OtherValue[] = "Other";
	PartyDataBuffer Other{ OtherValue, static_cast<uint32>(sizeof(OtherValue)) };
	PartyDataBuffer Missing{};

	TestTrue(TEXT("The v1 custom endpoint tag is recognized"), PlayFabCustomData::IsCustomChannelValue(Matching));
	TestFalse(TEXT("Another endpoint tag is not recognized"), PlayFabCustomData::IsCustomChannelValue(Other));
	TestFalse(TEXT("A missing endpoint tag is not recognized"), PlayFabCustomData::IsCustomChannelValue(Missing));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FPlayFabCustomDataMessageRoutingTest,
	"PlayFab.OSS.CustomData.MessageRouting",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabCustomDataMessageRoutingTest::RunTest(const FString&)
{
	PartyLocalEndpoint* CustomEndpoint = reinterpret_cast<PartyLocalEndpoint*>(1);
	PartyLocalEndpoint* NormalEndpoint = reinterpret_cast<PartyLocalEndpoint*>(2);
	PartyLocalEndpoint* Receivers[] = { NormalEndpoint, CustomEndpoint };
	PartyEndpointMessageReceivedStateChange StateChange{};
	StateChange.receiverEndpointCount = UE_ARRAY_COUNT(Receivers);
	StateChange.receiverEndpoints = Receivers;

	TestTrue(TEXT("Messages targeting the custom endpoint use the custom path"), PlayFabCustomData::IsReceivedOnEndpoint(StateChange, CustomEndpoint));
	TestFalse(TEXT("Messages not targeting an endpoint do not use its path"), PlayFabCustomData::IsReceivedOnEndpoint(StateChange, reinterpret_cast<PartyLocalEndpoint*>(3)));
	TestFalse(TEXT("A missing local endpoint never claims a message"), PlayFabCustomData::IsReceivedOnEndpoint(StateChange, nullptr));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FPlayFabCustomDataNetworkIsolationTest,
	"PlayFab.OSS.CustomData.NetworkIsolation",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabCustomDataNetworkIsolationTest::RunTest(const FString&)
{
	PartyNetwork* FirstNetwork = reinterpret_cast<PartyNetwork*>(1);
	PartyNetwork* SecondNetwork = reinterpret_cast<PartyNetwork*>(2);
	PartyEndpointMessageReceivedStateChange StateChange{};
	StateChange.network = FirstNetwork;

	TestTrue(TEXT("The owning named-session network accepts its message"), PlayFabCustomData::IsMessageForNetwork(StateChange, FirstNetwork));
	TestFalse(TEXT("Another named-session network rejects the message"), PlayFabCustomData::IsMessageForNetwork(StateChange, SecondNetwork));
	TestFalse(TEXT("A missing named-session network rejects the message"), PlayFabCustomData::IsMessageForNetwork(StateChange, nullptr));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FPlayFabCustomDataPayloadOwnershipTest,
	"PlayFab.OSS.CustomData.PayloadOwnership",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabCustomDataPayloadOwnershipTest::RunTest(const FString&)
{
	uint8 PartyBuffer[] = { 1, 2, 3 };
	PartyEndpointMessageReceivedStateChange StateChange{};
	StateChange.messageBuffer = PartyBuffer;
	StateChange.messageSize = UE_ARRAY_COUNT(PartyBuffer);

	TArray<uint8> Payload;
	TestTrue(TEXT("A valid Party payload is copied"), PlayFabCustomData::CopyPayload(StateChange, Payload));
	PartyBuffer[0] = 9;
	TestEqual(TEXT("The queued payload owns its bytes after the Party callback"), Payload[0], static_cast<uint8>(1));

	StateChange.messageBuffer = nullptr;
	TestFalse(TEXT("A missing Party payload is rejected"), PlayFabCustomData::CopyPayload(StateChange, Payload));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FPlayFabCustomDataSendPolicyTest,
	"PlayFab.OSS.CustomData.SendPolicy",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabCustomDataSendPolicyTest::RunTest(const FString&)
{
	TestEqual(TEXT("No local endpoint rejects the send"), PlayFabCustomData::GetSendAction(false, 1, 1), PlayFabCustomData::ESendAction::Reject);
	TestEqual(TEXT("An empty payload rejects the send"), PlayFabCustomData::GetSendAction(true, 0, 1), PlayFabCustomData::ESendAction::Reject);
	TestEqual(TEXT("No recipients is a successful no-op like v1"), PlayFabCustomData::GetSendAction(true, 1, 0), PlayFabCustomData::ESendAction::SucceedWithoutSend);
	TestEqual(TEXT("A valid endpoint, payload, and recipient sends"), PlayFabCustomData::GetSendAction(true, 1, 1), PlayFabCustomData::ESendAction::Send);
	return true;
}

#endif
