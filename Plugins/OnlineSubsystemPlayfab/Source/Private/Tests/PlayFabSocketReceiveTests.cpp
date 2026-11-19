//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "PlayFabSocket.h"
#include "PlayFabSocketSubsystem.h"
#include "PlayFabPartyNetwork.h"

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
	TestEqual(TEXT("Success preserves the previous error, matching the existing socket contract"), Subsystem.GetLastErrorCode(), SE_EMSGSIZE);
	Source->GetIp(SourceId);
	TestEqual(TEXT("The source endpoint is preserved"), SourceId, static_cast<uint32>(8));

	Socket.AddNewPendingData(9, TArray<uint8>{ 6 });
	TestTrue(TEXT("A smaller datagram is received"), Socket.RecvFrom(Buffer + 1, 2, BytesRead, *Source));
	TestEqual(TEXT("Smaller datagram byte count"), BytesRead, 1);
	TestEqual(TEXT("Smaller datagram payload"), Buffer[1], static_cast<uint8>(6));
	TestEqual(TEXT("Bytes beyond the payload remain unchanged"), Buffer[2], static_cast<uint8>(5));

	BytesRead = 99;
	Subsystem.LastSocketError = SE_ECONNRESET;
	TestFalse(TEXT("An empty queue reports no packet"), Socket.RecvFrom(Buffer, sizeof(Buffer), BytesRead, *Source));
	TestEqual(TEXT("An empty queue resets the byte count"), BytesRead, 0);
	TestEqual(TEXT("An empty queue retains its existing no-error result"), Subsystem.GetLastErrorCode(), SE_NO_ERROR);

	Socket.AddNewPendingData(10, TArray<uint8>{ 7 });
	BytesRead = 99;
	Subsystem.LastSocketError = SE_ECONNRESET;
	Source->SetIp(123);
	Source->SetPort(456);
	TestFalse(TEXT("A zero capacity is rejected"), Socket.RecvFrom(Buffer, 0, BytesRead, *Source));
	TestEqual(TEXT("Zero capacity preserves the caller's byte count"), BytesRead, 99);
	TestEqual(TEXT("Zero capacity preserves its original no-error result"), Subsystem.GetLastErrorCode(), SE_NO_ERROR);
	Source->GetIp(SourceId);
	TestEqual(TEXT("Zero capacity leaves the source address unchanged"), SourceId, static_cast<uint32>(123));
	TestEqual(TEXT("Zero capacity leaves the source port unchanged"), Source->GetPort(), 456);
	TestFalse(TEXT("A null zero-capacity buffer uses the same legacy path"), Socket.RecvFrom(nullptr, 0, BytesRead, *Source));
	TestEqual(TEXT("A null zero-capacity buffer preserves the caller's byte count"), BytesRead, 99);
	TestTrue(TEXT("Zero capacity does not consume the pending packet"), Socket.HasPendingData(PendingSize));

	TestFalse(TEXT("A null destination is rejected"), Socket.RecvFrom(nullptr, 1, BytesRead, *Source));
	TestEqual(TEXT("A rejected buffer does not introduce a new socket error code"), Subsystem.GetLastErrorCode(), SE_NO_ERROR);
	TestEqual(TEXT("A null destination reports no bytes copied"), BytesRead, 0);
	TestFalse(TEXT("A negative capacity is rejected"), Socket.RecvFrom(Buffer, -1, BytesRead, *Source));
	TestEqual(TEXT("A negative capacity does not introduce a new socket error code"), Subsystem.GetLastErrorCode(), SE_NO_ERROR);
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

	Subsystem.LastSocketError = SE_EMSGSIZE;
	TestFalse(TEXT("A missing OSS retains precedence over a negative count"), Socket.SendTo(&Byte, -1, BytesSent, *Destination));
	TestEqual(TEXT("An invalid send reports no bytes sent"), BytesSent, 0);
	TestEqual(TEXT("A missing OSS does not overwrite the previous error"), Subsystem.GetLastErrorCode(), SE_EMSGSIZE);

	BytesSent = 99;
	TestFalse(TEXT("A missing OSS retains precedence over a null nonempty buffer"), Socket.SendTo(nullptr, 1, BytesSent, *Destination));
	TestEqual(TEXT("A null buffer reports no bytes sent"), BytesSent, 0);
	TestEqual(TEXT("A null buffer with a missing OSS preserves the previous error"), Subsystem.GetLastErrorCode(), SE_EMSGSIZE);

	int32 OSSStorage = 0;
	Socket.OSSPlayFab = reinterpret_cast<FOnlineSubsystemPlayFab*>(&OSSStorage);
	Socket.SocketSubsystem = nullptr;
	TestFalse(TEXT("A missing socket subsystem retains precedence over a negative count"), Socket.SendTo(&Byte, -1, BytesSent, *Destination));
	TestEqual(TEXT("A missing socket subsystem does not overwrite the previous error"), Subsystem.GetLastErrorCode(), SE_EMSGSIZE);
	Socket.SocketSubsystem = &Subsystem;
	TestFalse(TEXT("A disconnected socket retains precedence over a negative count"), Socket.SendTo(&Byte, -1, BytesSent, *Destination));
	TestEqual(TEXT("A disconnected socket retains its existing error"), Subsystem.GetLastErrorCode(), SE_ENOTCONN);
	TestFalse(TEXT("A disconnected socket retains precedence over a null nonempty buffer"), Socket.SendTo(nullptr, 1, BytesSent, *Destination));
	TestEqual(TEXT("A disconnected null-buffer send retains its existing error"), Subsystem.GetLastErrorCode(), SE_ENOTCONN);

	TSharedPtr<FPlayFabPartyNetwork> Network = MakeShared<FPlayFabPartyNetwork>(
		nullptr, 2, 1, 1, 2, 1, Party::PartyDirectPeerConnectivityOptions::None, false);
	int32 LocalEndpointStorage = 0;
	int32 RemoteEndpointStorage = 0;
	// Invalid buffers must be rejected before either endpoint is used by the SDK.
	Network->LocalEndpoint = reinterpret_cast<Party::PartyLocalEndpoint*>(&LocalEndpointStorage);
	Socket.SetPartyNetwork(Network);
	Destination->SetIp(7);
	AddExpectedMessage(TEXT("FPlayFabPartyNetwork::GetEndpoint: Could not find Enpoint"), ELogVerbosity::Warning);
	TestFalse(TEXT("A missing peer retains precedence over an invalid buffer"), Socket.SendTo(nullptr, 1, BytesSent, *Destination));
	TestEqual(TEXT("A missing peer retains its original disconnected error"), Subsystem.GetLastErrorCode(), SE_ENOTCONN);
	Network->Endpoints.Add(7, reinterpret_cast<Party::PartyEndpoint*>(&RemoteEndpointStorage));
	AddExpectedMessage(TEXT("FPlayFabSocket::SendTo: Invalid send buffer"), ELogVerbosity::Warning, EAutomationExpectedMessageFlags::Contains, 2);
	TestFalse(TEXT("A connected negative-count send is rejected before the SDK call"), Socket.SendTo(&Byte, -1, BytesSent, *Destination));
	TestEqual(TEXT("A connected negative-count send retains the SDK send-failure code"), Subsystem.GetLastErrorCode(), SE_ECONNRESET);
	BytesSent = 99;
	TestFalse(TEXT("A connected null-buffer send is rejected before the SDK call"), Socket.SendTo(nullptr, 1, BytesSent, *Destination));
	TestEqual(TEXT("A rejected connected send reports no bytes sent"), BytesSent, 0);
	TestEqual(TEXT("A connected null-buffer send retains the SDK send-failure code"), Subsystem.GetLastErrorCode(), SE_ECONNRESET);

	Network->Endpoints[7] = Network->LocalEndpoint;
	TestFalse(TEXT("A self-send retains precedence over an invalid buffer"), Socket.SendTo(nullptr, 1, BytesSent, *Destination));
	TestEqual(TEXT("A self-send retains its original no-error result"), Subsystem.GetLastErrorCode(), SE_NO_ERROR);
	TestFalse(TEXT("A zero-length self-send remains on the original path"), Socket.SendTo(&Byte, 0, BytesSent, *Destination));
	TestEqual(TEXT("A zero-length self-send retains its original no-error result"), Subsystem.GetLastErrorCode(), SE_NO_ERROR);
	Network->LocalEndpoint = nullptr;
	Network->Endpoints.Reset();
	Socket.OSSPlayFab = nullptr;
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
