//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "PlayFabSocket.h"
#include "PlayFabSocketSubsystem.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FPlayFabSocketReceiveBoundsTest,
	"PlayFab.OSS.Socket.Receive.Bounds",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabSocketReceiveBoundsTest::RunTest(const FString&)
{
	FPlayFabSocketSubsystem Subsystem;
	FPlayFabSocket Socket(nullptr, TEXT("ReceiveBoundsTest"), NAME_None);
	Socket.SocketSubsystem = &Subsystem;
	TSharedRef<FInternetAddr> Source = Subsystem.CreateInternetAddr();
	uint8 Buffer[] = { 0xAA, 0xAA, 0xAA, 0xAA };
	int32 BytesRead = 99;

	Socket.AddNewPendingData(7, TArray<uint8>{ 1, 2, 3 });
	TestFalse(TEXT("An oversized datagram is rejected"), Socket.RecvFrom(Buffer + 1, 2, BytesRead, *Source));
	TestEqual(TEXT("An oversized datagram reports no bytes copied"), BytesRead, 0);
	TestEqual(TEXT("An oversized datagram reports a size error"), Subsystem.GetLastErrorCode(), SE_EMSGSIZE);
	uint32 SourceId = 0;
	Source->GetIp(SourceId);
	TestEqual(TEXT("Size errors identify the actual sender, not a stale connection"), SourceId, static_cast<uint32>(7));
	TestEqual(TEXT("Size errors preserve the sender port"), Source->GetPort(), 7);
	for (uint8 Byte : Buffer)
	{
		TestEqual(TEXT("Rejection leaves the entire destination and canaries intact"), Byte, static_cast<uint8>(0xAA));
	}

	uint32 PendingSize = 99;
	TestFalse(TEXT("The oversized datagram is consumed"), Socket.HasPendingData(PendingSize));

	Socket.AddNewPendingData(8, TArray<uint8>{ 4, 5 });
	TestTrue(TEXT("An exact-fit datagram is received"), Socket.RecvFrom(Buffer + 1, 2, BytesRead, *Source));
	TestEqual(TEXT("Exact-fit byte count"), BytesRead, 2);
	TestEqual(TEXT("First payload byte"), Buffer[1], static_cast<uint8>(4));
	TestEqual(TEXT("Last payload byte"), Buffer[2], static_cast<uint8>(5));
	TestEqual(TEXT("Leading canary"), Buffer[0], static_cast<uint8>(0xAA));
	TestEqual(TEXT("Trailing canary"), Buffer[3], static_cast<uint8>(0xAA));
	TestEqual(TEXT("Success clears the previous size error"), Subsystem.GetLastErrorCode(), SE_NO_ERROR);
	Source->GetIp(SourceId);
	TestEqual(TEXT("The source endpoint is preserved"), SourceId, static_cast<uint32>(8));

	Socket.AddNewPendingData(9, TArray<uint8>{ 6 });
	TestTrue(TEXT("A smaller datagram is received"), Socket.RecvFrom(Buffer + 1, 2, BytesRead, *Source));
	TestEqual(TEXT("Smaller datagram byte count"), BytesRead, 1);
	TestEqual(TEXT("Smaller datagram payload"), Buffer[1], static_cast<uint8>(6));
	TestEqual(TEXT("Bytes beyond the payload remain unchanged"), Buffer[2], static_cast<uint8>(5));

	BytesRead = 99;
	TestFalse(TEXT("An empty queue reports no packet"), Socket.RecvFrom(Buffer, sizeof(Buffer), BytesRead, *Source));
	TestEqual(TEXT("An empty queue resets the byte count"), BytesRead, 0);

	Socket.AddNewPendingData(10, TArray<uint8>{ 7 });
	TestFalse(TEXT("A null destination is rejected"), Socket.RecvFrom(nullptr, 1, BytesRead, *Source));
	TestEqual(TEXT("A null destination reports invalid arguments"), Subsystem.GetLastErrorCode(), SE_EINVAL);
	TestFalse(TEXT("A negative capacity is rejected"), Socket.RecvFrom(Buffer, -1, BytesRead, *Source));
	TestFalse(TEXT("A zero capacity is rejected"), Socket.RecvFrom(Buffer, 0, BytesRead, *Source));
	TestEqual(TEXT("Invalid buffers report no bytes copied"), BytesRead, 0);
	TestTrue(TEXT("Invalid buffers do not consume the pending packet"), Socket.HasPendingData(PendingSize));
	TestTrue(TEXT("A valid retry receives the pending packet"), Socket.RecvFrom(Buffer, sizeof(Buffer), BytesRead, *Source));
	TestEqual(TEXT("Retry payload"), Buffer[0], static_cast<uint8>(7));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FPlayFabSocketSendBoundsTest,
	"PlayFab.OSS.Socket.Send.Bounds",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabSocketSendBoundsTest::RunTest(const FString&)
{
	FPlayFabSocketSubsystem Subsystem;
	FPlayFabSocket Socket(nullptr, TEXT("SendBoundsTest"), NAME_None);
	Socket.SocketSubsystem = &Subsystem;
	TSharedRef<FInternetAddr> Destination = Subsystem.CreateInternetAddr();
	uint8 Byte = 1;
	int32 BytesSent = 99;

	TestFalse(TEXT("A negative send count is rejected before SDK conversion"), Socket.SendTo(&Byte, -1, BytesSent, *Destination));
	TestEqual(TEXT("An invalid send reports no bytes sent"), BytesSent, 0);
	TestEqual(TEXT("A negative count reports invalid arguments"), Subsystem.GetLastErrorCode(), SE_EINVAL);

	BytesSent = 99;
	TestFalse(TEXT("A null nonempty send buffer is rejected"), Socket.SendTo(nullptr, 1, BytesSent, *Destination));
	TestEqual(TEXT("A null buffer reports no bytes sent"), BytesSent, 0);
	TestEqual(TEXT("A null buffer reports invalid arguments"), Subsystem.GetLastErrorCode(), SE_EINVAL);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FPlayFabSocketMessageBoundsTest,
	"PlayFab.OSS.Socket.Message.Bounds",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabSocketMessageBoundsTest::RunTest(const FString&)
{
	AddExpectedMessage(TEXT("Dropping invalid packet"), ELogVerbosity::Warning, EAutomationExpectedMessageFlags::Contains, 3);
	FPlayFabSocketSubsystem Subsystem;
	Party::PartyEndpointMessageReceivedStateChange Change{};
	uint8 Byte = 1;

	// Rejected messages must never dereference the sender or read the claimed payload.
	int32 SenderStorage = 0;
	Change.senderEndpoint = reinterpret_cast<Party::PartyEndpoint*>(&SenderStorage);
	Change.messageBuffer = &Byte;
	Change.messageSize = static_cast<uint32>(MAX_int32) + 1u;
	Subsystem.OnEndpointMessageReceived(&Change);

	Change.messageBuffer = nullptr;
	Change.messageSize = 1;
	Subsystem.OnEndpointMessageReceived(&Change);

	Change.senderEndpoint = nullptr;
	Change.messageBuffer = &Byte;
	Subsystem.OnEndpointMessageReceived(&Change);
	return true;
}

#endif
