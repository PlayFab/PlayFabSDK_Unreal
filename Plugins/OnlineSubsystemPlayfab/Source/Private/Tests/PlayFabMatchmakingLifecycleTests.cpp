//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "MatchmakingInterfacePlayFab.h"
#include "PlayFabMatchmakingCompletion.h"
#include "OnlineSessionInterfacePlayFab.h"
#include "OnlineSubsystemPlayFab.h"

class FPlayFabMatchmakingTestAccessor
{
public:
    static void InitializeSessionTest(FOnlineSubsystemPlayFab& Subsystem)
    {
        Subsystem.PlayFabLobbyInterface = MakeShared<FPlayFabLobby, ESPMode::ThreadSafe>(&Subsystem);
        Subsystem.MatchmakingInterface = MakeShared<FMatchmakingInterfacePlayFab, ESPMode::ThreadSafe>(&Subsystem);
        Subsystem.SessionInterface = MakeShared<FOnlineSessionPlayFab, ESPMode::ThreadSafe>(&Subsystem);
    }

    static void FinishSessionTest(FOnlineSubsystemPlayFab& Subsystem)
    {
        Subsystem.SessionInterface.Reset();
        Subsystem.MatchmakingInterface.Reset();
        Subsystem.PlayFabLobbyInterface.Reset();
    }

    static void Complete(FMatchmakingInterfacePlayFab& Interface, FName Name, const FOnlineMatchmakingTicketInfoPtr& Ticket, bool bSuccess)
    {
        Interface.CompleteMatchmakingTicket(Name, Ticket, bSuccess);
    }

    static void Cancel(FMatchmakingInterfacePlayFab& Interface, FName Name, const FOnlineMatchmakingTicketInfoPtr& Ticket)
    {
        Interface.CompleteMatchmakingCancellation(Name, Ticket);
    }

    static void DeliverInactiveEvents(FMatchmakingInterfacePlayFab& Interface)
    {
        PFMatchmakingTicketStatusChangedStateChange Status{};
        PFMatchmakingTicketCompletedStateChange Complete{};
        Interface.HandleMatchmakingTicketStatusChanged(Status);
        Interface.HandleMatchmakingTicketCompleted(Complete);
    }

    static PFLobbyHandle PrepareHostUpdates(FPlayFabLobby& Lobby, const FPlayFabSessionStatePtr& State)
    {
        const PFLobbyHandle Handle = reinterpret_cast<PFLobbyHandle>(&Lobby);
        Lobby.LobbySessionMap.Add(Handle, State->SessionName);
        Lobby.UpdateLobbyOperations.Add(1, {1, true, {}, State});
        Lobby.UpdateLobbyOperations.Add(2, {1, true,
            FOnUpdateLobbyCompletedDelegate::CreateSP(State.ToSharedRef(), &FPlayFabSessionState::OnUpdateSession_Matchmaking), State});
        return Handle;
    }

    static void CompleteHostUpdate(FPlayFabLobby& Lobby, PFLobbyHandle Handle, int OperationId)
    {
        Lobby.CompleteLobbyUpdate(OperationId, Handle);
    }

    static void DeliverOldArrangedLobby(FPlayFabLobby& Lobby, const FPlayFabSessionStatePtr& OldState)
    {
        const PFLobbyHandle Handle = reinterpret_cast<PFLobbyHandle>(&Lobby);
        const FOnlineMatchmakingTicketInfoPtr Ticket = MakeShared<FOnlineMatchmakingTicketInfo>();
        Ticket->SessionState = OldState;
        Lobby.LobbySessionMap.Add(Handle, OldState->SessionName);
        Lobby.PendingArrangedLobbies.Add(Handle, {Ticket, TEXT("old-host")});
        PFLobbyJoinArrangedLobbyCompletedStateChange Event{};
        Event.lobby = Handle;
        Event.result = E_FAIL;
        Lobby.HandleJoinArrangedLobbyCompleted(Event);
        Lobby.HandleJoinArrangedLobbyCompleted(Event);
    }
};

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FPlayFabMatchmakingRegistryTest,
    "PlayFab.OSS.Matchmaking.Lifecycle.RegistryPreservesReplacement",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabMatchmakingRegistryTest::RunTest(const FString&)
{
    FMatchmakingInterfacePlayFab Interface(nullptr);
    const FName Name(TEXT("GameSession"));
    const FOnlineMatchmakingTicketInfoPtr First = MakeShared<FOnlineMatchmakingTicketInfo>();
    const FOnlineMatchmakingTicketInfoPtr Replacement = MakeShared<FOnlineMatchmakingTicketInfo>();
    TestTrue(TEXT("First ticket is registered"), Interface.AddMatchmakingTicket(Name, First));
    TestFalse(TEXT("Registration cannot overwrite an active ticket"), Interface.AddMatchmakingTicket(Name, Replacement));
    TestFalse(TEXT("Wrong ticket cannot remove the current ticket"), Interface.RemoveMatchmakingTicket(Name, Replacement));
    TestTrue(TEXT("Expected ticket is removed"), Interface.RemoveMatchmakingTicket(Name, First));
    TestTrue(TEXT("Replacement is registered"), Interface.AddMatchmakingTicket(Name, Replacement));

    int32 Completions = 0;
    Interface.AddOnMatchmakingTicketCompletedDelegate_Handle(FOnMatchmakingTicketCompletedDelegate::CreateLambda(
        [&Completions](bool, FName, TSharedPtr<FPlayFabSessionState>) { ++Completions; }));
    Interface.OnJoinArrangedLobbyCompleted(Name, true, First);
    FOnlineMatchmakingTicketInfoPtr Found;
    TestTrue(TEXT("Old arranged-lobby callback leaves replacement registered"), Interface.GetMatchmakingTicket(Name, Found));
    TestTrue(TEXT("Replacement identity is preserved"), Found == Replacement);
    TestEqual(TEXT("Old callback cannot dispatch a terminal result"), Completions, 0);
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FPlayFabMatchmakingTerminalTest,
    "PlayFab.OSS.Matchmaking.Lifecycle.TerminalCallbacksAreIdempotent",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabMatchmakingTerminalTest::RunTest(const FString&)
{
    FMatchmakingInterfacePlayFab Interface(nullptr);
    const FName Name(TEXT("GameSession"));
    FOnlineMatchmakingTicketInfoPtr Ticket = MakeShared<FOnlineMatchmakingTicketInfo>();
    const FOnlineMatchmakingTicketInfoPtr Replacement = MakeShared<FOnlineMatchmakingTicketInfo>();
    Interface.AddMatchmakingTicket(Name, Ticket);
    int32 Completions = 0;
    int32 Cancellations = 0;
    Interface.AddOnMatchmakingTicketCompletedDelegate_Handle(FOnMatchmakingTicketCompletedDelegate::CreateLambda(
        [&](bool bSuccess, FName, TSharedPtr<FPlayFabSessionState>)
        {
            ++Completions;
            TestFalse(TEXT("Arranged-lobby failure is preserved"), bSuccess);
            TestTrue(TEXT("Completion may register a replacement reentrantly"), Interface.AddMatchmakingTicket(Name, Replacement));
        }));
    Interface.AddOnPlayFabTicketCancellationCompleteDelegate_Handle(FOnPlayFabTicketCancellationCompleteDelegate::CreateLambda(
        [&](FName, bool, TSharedPtr<FPlayFabSessionState>) { ++Cancellations; }));

    Interface.OnJoinArrangedLobbyCompleted(Name, false, Ticket);
    Interface.OnJoinArrangedLobbyCompleted(Name, true, Ticket);
    FPlayFabMatchmakingTestAccessor::Cancel(Interface, Name, Ticket);
    TestEqual(TEXT("Terminal callback fires once"), Completions, 1);
    TestEqual(TEXT("Late cancellation cannot win after terminal completion"), Cancellations, 0);
    FOnlineMatchmakingTicketInfoPtr Found;
    Interface.GetMatchmakingTicket(Name, Found);
    TestTrue(TEXT("Terminal cleanup does not remove the reentrant replacement"), Found == Replacement);

    FPlayFabMatchmakingTestAccessor::Cancel(Interface, Name, Replacement);
    FPlayFabMatchmakingTestAccessor::Complete(Interface, Name, Replacement, true);
    TestEqual(TEXT("Cancellation fires once"), Cancellations, 1);
    TestEqual(TEXT("Late success cannot win after cancellation"), Completions, 1);
    FPlayFabMatchmakingTestAccessor::DeliverInactiveEvents(Interface);
    TestEqual(TEXT("Inactive SDK events do not dispatch another result"), Completions, 1);
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FPlayFabMatchmakingShutdownTest,
    "PlayFab.OSS.Matchmaking.Lifecycle.ShutdownClearsWithoutCallbacks",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabMatchmakingShutdownTest::RunTest(const FString&)
{
    FMatchmakingInterfacePlayFab Interface(nullptr);
    const FName Name(TEXT("GameSession"));
    const FOnlineMatchmakingTicketInfoPtr Ticket = MakeShared<FOnlineMatchmakingTicketInfo>();
    Interface.AddMatchmakingTicket(Name, Ticket);
    int32 Completions = 0;
    Interface.AddOnMatchmakingTicketCompletedDelegate_Handle(FOnMatchmakingTicketCompletedDelegate::CreateLambda(
        [&](bool, FName, TSharedPtr<FPlayFabSessionState>) { ++Completions; }));
    Interface.Shutdown();
    Interface.Shutdown();
    FOnlineMatchmakingTicketInfoPtr Found;
    TestFalse(TEXT("Shutdown removes all ticket registrations"), Interface.GetMatchmakingTicket(Name, Found));
    TestFalse(TEXT("Shutdown rejects new registrations"), Interface.AddMatchmakingTicket(Name, Ticket));
    Interface.OnJoinArrangedLobbyCompleted(Name, true, Ticket);
    TestEqual(TEXT("Shutdown does not invoke title callbacks"), Completions, 0);
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FPlayFabMatchmakingPartyCompletionTest,
    "PlayFab.OSS.Matchmaking.Lifecycle.FinalCompletionSpansPartySetup",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabMatchmakingPartyCompletionTest::RunTest(const FString&)
{
    PlayFabMatchmakingCompletion::FState Host;
    TestFalse(TEXT("An operation that never started cannot complete"), Host.TryComplete());
    TestTrue(TEXT("An idle host operation can begin"), Host.Begin());
    TestTrue(TEXT("Matched ticket begins Party setup"), Host.BeginParty());
    TestFalse(TEXT("Repeated ticket result cannot begin Party twice"), Host.BeginParty());
    TestTrue(TEXT("First endpoint begins host publication"), Host.BeginEndpoint());
    TestFalse(TEXT("Repeated endpoint cannot publish or complete twice"), Host.BeginEndpoint());
    TestTrue(TEXT("Endpoint readiness is not terminal for the host"), Host.IsInProgress());
    TestTrue(TEXT("Host publication completes the current operation"), Host.TryComplete());
    TestFalse(TEXT("Repeated host publication cannot complete twice"), Host.TryComplete());
    TestFalse(TEXT("Terminal operation is not in progress"), Host.IsInProgress());

    PlayFabMatchmakingCompletion::FState Client;
    TestTrue(TEXT("An idle client operation can begin"), Client.Begin());
    Client.BeginParty();
    Client.BeginEndpoint();
    TestTrue(TEXT("Client endpoint can finish the current operation"), Client.TryComplete());
    TestFalse(TEXT("Late failure/cancellation cannot replace client success"), Client.TryComplete());

    PlayFabMatchmakingCompletion::FState Failure;
    TestTrue(TEXT("An idle operation can begin before failure"), Failure.Begin());
    TestTrue(TEXT("Failure/cancellation may finish before Party setup"), Failure.TryComplete());
    TestFalse(TEXT("Late match cannot start Party after cancellation"), Failure.BeginParty());
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FPlayFabMatchmakingBeginTest,
    "PlayFab.OSS.Matchmaking.Lifecycle.BeginRejectsActiveAndCompletedOperations",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabMatchmakingBeginTest::RunTest(const FString&)
{
    PlayFabMatchmakingCompletion::FState State;
    TestTrue(TEXT("An idle operation can begin"), State.Begin());
    TestFalse(TEXT("A pending ticket cannot begin again"), State.Begin());
    TestTrue(TEXT("Rejected begin preserves the ticket stage"), State.BeginParty());
    TestFalse(TEXT("Party setup cannot begin the operation again"), State.Begin());
    TestFalse(TEXT("Rejected begin does not reset Party setup to the ticket stage"), State.BeginParty());
    TestTrue(TEXT("Party setup can still advance to the endpoint stage"), State.BeginEndpoint());
    TestFalse(TEXT("Endpoint publication cannot begin the operation again"), State.Begin());
    TestFalse(TEXT("Rejected begin does not reset endpoint publication to the ticket stage"), State.BeginParty());
    TestTrue(TEXT("The operation can still complete"), State.TryComplete());
    TestFalse(TEXT("A completed operation cannot begin again"), State.Begin());
    TestFalse(TEXT("A rejected restart cannot reactivate a terminal operation"), State.IsInProgress());
    TestFalse(TEXT("A rejected restart cannot produce another terminal result"), State.TryComplete());

    PlayFabMatchmakingCompletion::FState Cancelled;
    TestTrue(TEXT("A separate idle operation can begin"), Cancelled.Begin());
    TestTrue(TEXT("Cancellation can complete before Party setup"), Cancelled.TryComplete());
    TestFalse(TEXT("Cancellation cannot be undone by another begin"), Cancelled.Begin());
    TestFalse(TEXT("A cancelled operation cannot enter Party setup"), Cancelled.BeginParty());
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FPlayFabMatchmakingSessionCompletionTest,
    "PlayFab.OSS.Matchmaking.Lifecycle.SessionCompletionRejectsOldAndDuplicateResults",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabMatchmakingSessionCompletionTest::RunTest(const FString&)
{
    FOnlineSubsystemPlayFab Subsystem(FName(TEXT("MatchmakingLifecycleTest")));
    FPlayFabMatchmakingTestAccessor::InitializeSessionTest(Subsystem);
    {
        FOnlineSessionPlayFabPtr Sessions = Subsystem.GetSessionInterfacePlayFab();
        const FName Name(TEXT("GameSession"));
        FOnlineSessionSettings Settings;
        const FPlayFabSessionStatePtr First = Sessions->TryAddSessionState(
            Name, MakeShared<FNamedOnlineSession, ESPMode::ThreadSafe>(Name, Settings));
        First->MatchmakingCompletion.Begin();
        First->MatchmakingCompletion.BeginParty();
        First->MatchmakingCompletion.BeginEndpoint();
        First->RetryJoinNetwork_Count = 2;

        int32 Completions = 0;
        int32 Cancellations = 0;
        bool bLastResult = false;
        FDelegateHandle CompletionHandle = Sessions->AddOnMatchmakingCompleteDelegate_Handle(FOnMatchmakingCompleteDelegate::CreateLambda(
            [&](FName, bool bSuccess) { ++Completions; bLastResult = bSuccess; }));
        FDelegateHandle CancellationHandle = Sessions->AddOnCancelMatchmakingCompleteDelegate_Handle(FOnCancelMatchmakingCompleteDelegate::CreateLambda(
            [&](FName, bool) { ++Cancellations; }));

        const FPlayFabLobbyPtr Lobby = Subsystem.GetPlayFabLobbyInterface();
        const PFLobbyHandle Handle = FPlayFabMatchmakingTestAccessor::PrepareHostUpdates(*Lobby, First);
        FPlayFabMatchmakingTestAccessor::CompleteHostUpdate(*Lobby, Handle, 1);
        TestEqual(TEXT("Nickname or unrelated lobby updates cannot report matchmaking success"), Completions, 0);
        FPlayFabMatchmakingTestAccessor::CompleteHostUpdate(*Lobby, Handle, 2);
        FPlayFabMatchmakingTestAccessor::CompleteHostUpdate(*Lobby, Handle, 2);
        First->OnUpdateSession_Matchmaking(Name, false);
        TestEqual(TEXT("Host lobby update produces one final result"), Completions, 1);
        TestTrue(TEXT("First terminal success is preserved"), bLastResult);
        TestEqual(TEXT("Final completion stops network retries"), First->RetryJoinNetwork_Count, 0);
        TestTrue(TEXT("Success preserves the Game session"), Sessions->GetSessionStatePtr(Name) == First);

        Sessions->RemoveNamedSession(Name);
        const FPlayFabSessionStatePtr Replacement = Sessions->TryAddSessionState(
            Name, MakeShared<FNamedOnlineSession, ESPMode::ThreadSafe>(Name, Settings));
        Replacement->MatchmakingCompletion.Begin();
        const FPlayFabSessionStatePtr Unregistered = MakeShared<FPlayFabSessionState>(
            Name, MakeShared<FNamedOnlineSession, ESPMode::ThreadSafe>(Name, Settings), false, &Subsystem);
        Unregistered->MatchmakingCompletion.Begin();
        TestFalse(TEXT("An unregistered operation cannot complete the replacement"), Sessions->TryCompleteMatchmaking(Unregistered, false));
        TestTrue(TEXT("Rejected completion does not mutate the unregistered operation"), Unregistered->MatchmakingCompletion.IsInProgress());
        TestTrue(TEXT("Rejected completion preserves the replacement session"), Sessions->GetSessionStatePtr(Name) == Replacement);
        TestTrue(TEXT("Rejected completion leaves the replacement active"), Replacement->MatchmakingCompletion.IsInProgress());
        TestEqual(TEXT("Rejected completion does not notify the title"), Completions, 1);
        int32 ArrangedCallbacks = 0;
        FDelegateHandle ArrangedHandle = Lobby->AddOnJoinArrangedLobbyCompletedDelegate_Handle(
            FOnJoinArrangedLobbyCompletedDelegate::CreateLambda([&](FName, bool) { ++ArrangedCallbacks; }));
        FPlayFabMatchmakingTestAccessor::DeliverOldArrangedLobby(*Lobby, First);
        TestEqual(TEXT("Old SDK lobby completion cannot reach a replacement ticket's delegates"), ArrangedCallbacks, 0);
        Lobby->ClearOnJoinArrangedLobbyCompletedDelegate_Handle(ArrangedHandle);
        Sessions->OnMatchmakingTicketCompleted(false, Name, First);
        Sessions->OnCancelMatchmakingComplete(Name, true, First);
        TestTrue(TEXT("Old callbacks cannot remove a replacement session"), Sessions->GetSessionStatePtr(Name) == Replacement);
        TestEqual(TEXT("Old ticket result is ignored"), Completions, 1);
        TestEqual(TEXT("Old cancellation is ignored"), Cancellations, 0);

        Sessions->OnMatchmakingTicketCompleted(false, Name, Replacement);
        Sessions->OnMatchmakingTicketCompleted(false, Name, Replacement);
        TestEqual(TEXT("Current failure produces one final result"), Completions, 2);
        TestFalse(TEXT("Current failure is reported"), bLastResult);
        TestFalse(TEXT("Failure removes the provisional Game session"), Sessions->GetSessionStatePtr(Name).IsValid());

        const FPlayFabSessionStatePtr Cancelled = Sessions->TryAddSessionState(
            Name, MakeShared<FNamedOnlineSession, ESPMode::ThreadSafe>(Name, Settings));
        Cancelled->MatchmakingCompletion.Begin();
        Sessions->OnCancelMatchmakingComplete(Name, true, Cancelled);
        Sessions->OnMatchmakingTicketCompleted(true, Name, Cancelled);
        TestEqual(TEXT("Cancellation reports once"), Cancellations, 1);
        TestEqual(TEXT("Match after cancellation cannot report success"), Completions, 2);
        TestFalse(TEXT("Cancellation removes the provisional session"), Sessions->GetSessionStatePtr(Name).IsValid());

        const FPlayFabSessionStatePtr HostFailure = Sessions->TryAddSessionState(
            Name, MakeShared<FNamedOnlineSession, ESPMode::ThreadSafe>(Name, Settings));
        HostFailure->MatchmakingCompletion.Begin();
        HostFailure->MatchmakingCompletion.BeginParty();
        HostFailure->MatchmakingCompletion.BeginEndpoint();
        HostFailure->OnUpdateSession_Matchmaking(Name, false);
        TestEqual(TEXT("Host publication failure reports a final result"), Completions, 3);
        TestFalse(TEXT("Host publication failure removes the Game session"), Sessions->GetSessionStatePtr(Name).IsValid());

        const FPlayFabSessionStatePtr Client = Sessions->TryAddSessionState(
            Name, MakeShared<FNamedOnlineSession, ESPMode::ThreadSafe>(Name, Settings));
        Client->MatchmakingCompletion.Begin();
        Client->MatchmakingCompletion.BeginParty();
        Client->NetworkId = TEXT("test-client-network");
        Client->NetworkFlowType = ENetworkFlowType::Matchmaking;
        Subsystem.TriggerOnPartyEndpointCreatedDelegates(true, Client->NetworkId, 1, false);
        Subsystem.TriggerOnPartyEndpointCreatedDelegates(true, Client->NetworkId, 2, false);
        TestEqual(TEXT("Local and remote endpoint notifications complete the client once"), Completions, 4);
        TestTrue(TEXT("Client endpoint reports success"), bLastResult);
        Sessions->RemoveNamedSession(Name);

        const FPlayFabSessionStatePtr Aborted = Sessions->TryAddSessionState(
            Name, MakeShared<FNamedOnlineSession, ESPMode::ThreadSafe>(Name, Settings));
        Aborted->MatchmakingCompletion.Begin();
        Aborted->RetryJoinNetwork_Count = 3;
        Sessions->RemoveNamedSession(Name);
        TestFalse(TEXT("Teardown invalidates matchmaking completion"), Aborted->MatchmakingCompletion.IsInProgress());
        TestEqual(TEXT("Teardown stops retries"), Aborted->RetryJoinNetwork_Count, 0);
        Sessions->OnMatchmakingTicketCompleted(true, Name, Aborted);
        TestEqual(TEXT("Teardown cannot be followed by terminal success"), Completions, 4);

        Sessions->ClearOnMatchmakingCompleteDelegate_Handle(CompletionHandle);
        Sessions->ClearOnCancelMatchmakingCompleteDelegate_Handle(CancellationHandle);
    }
    FPlayFabMatchmakingTestAccessor::FinishSessionTest(Subsystem);
    return true;
}

#endif
