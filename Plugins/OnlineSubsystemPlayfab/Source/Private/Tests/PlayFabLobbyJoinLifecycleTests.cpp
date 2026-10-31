//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "MatchmakingInterfacePlayFab.h"
#include "OnlineSessionInterfacePlayFab.h"
#include "OnlineSubsystemPlayFab.h"

namespace
{
    class FJoinTestLobby : public FPlayFabLobby
    {
    public:
        explicit FJoinTestLobby(FOnlineSubsystemPlayFab* Subsystem) : FPlayFabLobby(Subsystem) {}

        HRESULT LeaveResult = S_OK;
        int32 LeaveRequests = 0;

    protected:
        HRESULT RequestLobbyLeave(PFLobbyHandle) override
        {
            ++LeaveRequests;
            return LeaveResult;
        }
    };
}

class FPlayFabLobbyJoinTestAccessor
{
public:
    static void Initialize(FOnlineSubsystemPlayFab& Subsystem, const TSharedRef<FJoinTestLobby>& Lobby)
    {
        Subsystem.PlayFabLobbyInterface = Lobby;
        Subsystem.MatchmakingInterface = MakeShared<FMatchmakingInterfacePlayFab, ESPMode::ThreadSafe>(&Subsystem);
        Subsystem.SessionInterface = MakeShared<FOnlineSessionPlayFab, ESPMode::ThreadSafe>(&Subsystem);
    }

    static void Finish(FOnlineSubsystemPlayFab& Subsystem)
    {
        Subsystem.SessionInterface.Reset();
        Subsystem.MatchmakingInterface.Reset();
        Subsystem.PlayFabLobbyInterface.Reset();
    }

    static PFLobbyHandle Track(FPlayFabLobby& Lobby, const FPlayFabSessionStatePtr& State, bool bCompleted = false)
    {
        const PFLobbyHandle Handle = reinterpret_cast<PFLobbyHandle>(State.Get());
        Lobby.LobbySessionMap.Add(Handle, State->SessionName);
        FPlayFabLobby::FJoinLobbyOperation& Operation =
            Lobby.JoinLobbyOperations.Add(Handle, {State->SessionName, State});
        Operation.bCompleted = bCompleted;
        Operation.bJoined = bCompleted;
        return Handle;
    }

    static bool IsMapped(const FPlayFabLobby& Lobby, PFLobbyHandle Handle)
    {
        return Lobby.LobbySessionMap.Contains(Handle);
    }

    static bool HasOperation(const FPlayFabLobby& Lobby, PFLobbyHandle Handle)
    {
        return Lobby.JoinLobbyOperations.Contains(Handle);
    }

    static bool IsLeavePending(const FPlayFabLobby& Lobby, PFLobbyHandle Handle)
    {
        return Lobby.JoinLobbyOperations.FindChecked(Handle).bLeavePending;
    }

    static void RetryCleanup(FPlayFabLobby& Lobby, PFLobbyHandle Handle)
    {
        Lobby.JoinLobbyOperations.FindChecked(Handle).NextCleanupAttemptSeconds = 0.0;
        Lobby.ProcessAbandonedLobbyJoins();
    }
};

namespace
{
    struct FJoinTestContext
    {
        FOnlineSubsystemPlayFab Subsystem{FName(TEXT("LobbyJoinLifecycleTest"))};
        TSharedRef<FJoinTestLobby> Lobby = MakeShared<FJoinTestLobby>(&Subsystem);
        FOnlineSessionPlayFabPtr Sessions;
        int32 LobbyCompletions = 0;
        int32 JoinCompletions = 0;
        int32 DestroyCompletions = 0;

        FJoinTestContext()
        {
            FPlayFabLobbyJoinTestAccessor::Initialize(Subsystem, Lobby);
            Sessions = Subsystem.GetSessionInterfacePlayFab();
            Lobby->AddOnJoinLobbyCompletedDelegate_Handle(FOnJoinLobbyCompletedDelegate::CreateLambda(
                [this](FName, EOnJoinSessionCompleteResult::Type) { ++LobbyCompletions; }));
            Sessions->AddOnJoinSessionCompleteDelegate_Handle(FOnJoinSessionCompleteDelegate::CreateLambda(
                [this](FName, EOnJoinSessionCompleteResult::Type) { ++JoinCompletions; }));
            Sessions->AddOnDestroySessionCompleteDelegate_Handle(FOnDestroySessionCompleteDelegate::CreateLambda(
                [this](FName, bool) { ++DestroyCompletions; }));
        }

        ~FJoinTestContext()
        {
            Sessions.Reset();
            FPlayFabLobbyJoinTestAccessor::Finish(Subsystem);
        }

        FPlayFabSessionStatePtr AddState()
        {
            const FName Name(TEXT("GameSession"));
            const auto NamedSession = MakeShared<FNamedOnlineSession, ESPMode::ThreadSafe>(Name, FOnlineSessionSettings{});
            NamedSession->SessionInfo = MakeShared<FOnlineSessionInfoPlayFab>();
            NamedSession->bHosting = true;
            const auto State = Sessions->TryAddSessionState(Name, NamedSession);
            check(State.IsValid());
            State->bSteamJoin = true;
            State->bUsesNativeSession = false;
            State->SteamJoinCompletion.Begin(true);
            return State;
        }
    };

    void DeliverJoin(FPlayFabLobby& Lobby, PFLobbyHandle Handle, HRESULT Result = S_OK)
    {
        PFLobbyJoinLobbyCompletedStateChange Event{};
        Event.lobby = Handle;
        Event.result = Result;
        Lobby.HandleJoinLobbyCompleted(Event);
    }

    void DeliverLeave(FPlayFabLobby& Lobby, PFLobbyHandle Handle)
    {
        PFLobbyLeaveLobbyCompletedStateChange Event{};
        Event.lobby = Handle;
        Lobby.HandleLeaveLobbyCompleted(Event);
    }
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FPlayFabRemovedLobbyJoinTest,
    "PlayFab.OSS.Session.SteamJoin.LobbyCompletion.RemovalOwnsLateCleanup",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabRemovedLobbyJoinTest::RunTest(const FString&)
{
    for (bool bJoinSucceeded : {false, true})
    {
        FJoinTestContext Context;
        auto State = Context.AddState();
        const auto Handle = FPlayFabLobbyJoinTestAccessor::Track(*Context.Lobby, State);
        Context.Sessions->RemoveNamedSession(State->SessionName);
        TestFalse(TEXT("Removal detaches the old lobby before cancellation callbacks"),
            FPlayFabLobbyJoinTestAccessor::IsMapped(*Context.Lobby, Handle));
        TestEqual(TEXT("Removal completes cancellation once"), Context.JoinCompletions, 1);
        TestEqual(TEXT("Pending join waits for the SDK result before cleanup"), Context.Lobby->LeaveRequests, 0);
        State.Reset();

        DeliverJoin(*Context.Lobby, Handle, bJoinSucceeded ? S_OK : E_FAIL);
        DeliverJoin(*Context.Lobby, Handle, bJoinSucceeded ? S_OK : E_FAIL);
        TestEqual(TEXT("Late join cannot reach lobby completion delegates"), Context.LobbyCompletions, 0);
        TestEqual(TEXT("Late join cannot complete the public join twice"), Context.JoinCompletions, 1);
        TestEqual(TEXT("Only a successful abandoned join needs leave"), Context.Lobby->LeaveRequests, bJoinSucceeded ? 1 : 0);
        if (bJoinSucceeded)
        {
            DeliverLeave(*Context.Lobby, Handle);
            DeliverJoin(*Context.Lobby, Handle);
            TestEqual(TEXT("Completion after cleanup cannot request another leave"), Context.Lobby->LeaveRequests, 1);
        }
        TestFalse(TEXT("Terminal cleanup releases join ownership"),
            FPlayFabLobbyJoinTestAccessor::HasOperation(*Context.Lobby, Handle));
    }
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FPlayFabReplacementLobbyJoinTest,
    "PlayFab.OSS.Session.SteamJoin.LobbyCompletion.PreservesReplacement",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabReplacementLobbyJoinTest::RunTest(const FString&)
{
    FJoinTestContext Context;
    const auto OldState = Context.AddState();
    const auto OldHandle = FPlayFabLobbyJoinTestAccessor::Track(*Context.Lobby, OldState);
    Context.Sessions->RemoveNamedSession(OldState->SessionName);
    const auto Replacement = Context.AddState();
    const auto ReplacementInfo = Replacement->NamedSession->SessionInfo;
    const auto NewHandle = FPlayFabLobbyJoinTestAccessor::Track(*Context.Lobby, Replacement);

    DeliverJoin(*Context.Lobby, OldHandle);
    DeliverLeave(*Context.Lobby, OldHandle);
    PFLobbyDisconnectedStateChange Disconnect{};
    Disconnect.lobby = OldHandle;
    Context.Lobby->HandleLobbyDisconnected(Disconnect);
    TestTrue(TEXT("Old callbacks preserve the replacement registry entry"),
        Context.Sessions->GetSessionStatePtr(Replacement->SessionName) == Replacement);
    TestTrue(TEXT("Old callbacks cannot overwrite replacement session info"),
        Replacement->NamedSession->SessionInfo == ReplacementInfo);
    TestTrue(TEXT("Old callbacks preserve the replacement's host flag"), Replacement->NamedSession->bHosting);
    TestTrue(TEXT("Replacement join remains active"), Replacement->SteamJoinCompletion.IsJoining());
    TestTrue(TEXT("Replacement lobby mapping is untouched"),
        FPlayFabLobbyJoinTestAccessor::IsMapped(*Context.Lobby, NewHandle));
    TestEqual(TEXT("Old callbacks cannot notify a replacement join"), Context.LobbyCompletions, 0);
    TestEqual(TEXT("Only the old lobby is cleaned up"), Context.Lobby->LeaveRequests, 1);
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FPlayFabDuplicateLobbyJoinTest,
    "PlayFab.OSS.Session.SteamJoin.LobbyCompletion.IgnoresDuplicateAndInactiveResults",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabDuplicateLobbyJoinTest::RunTest(const FString&)
{
    for (int32 Stage = 0; Stage < 4; ++Stage)
    {
        FJoinTestContext Context;
        const auto State = Context.AddState();
        if (Stage == 0)
        {
            State->SteamJoinCompletion = PlayFabSessionJoin::FState{};
        }
        else
        {
            State->SteamJoinCompletion.CompletePlayFab(EOnJoinSessionCompleteResult::Success);
            if (Stage > 1)
            {
                State->SteamJoinCompletion.CompleteNative(Stage == 2
                    ? EOnJoinSessionCompleteResult::Success : EOnJoinSessionCompleteResult::SessionIsFull);
            }
        }
        const auto Info = State->NamedSession->SessionInfo;
        const auto Handle = FPlayFabLobbyJoinTestAccessor::Track(*Context.Lobby, State, Stage != 0);
        DeliverJoin(*Context.Lobby, Handle, Stage == 0 ? E_FAIL : S_OK);
        DeliverJoin(*Context.Lobby, Handle);
        TestTrue(TEXT("Ignored completion cannot overwrite session info"), State->NamedSession->SessionInfo == Info);
        TestEqual(TEXT("Ignored completion cannot dispatch lobby delegates"), Context.LobbyCompletions, 0);
        TestEqual(TEXT("Ignored completion cannot dispatch public join delegates"), Context.JoinCompletions, 0);
        TestEqual(TEXT("A duplicate must not leave the valid joined lobby"), Context.Lobby->LeaveRequests, 0);
    }

    FJoinTestContext Context;
    const auto State = Context.AddState();
    const auto Handle = FPlayFabLobbyJoinTestAccessor::Track(*Context.Lobby, State);
    AddExpectedError(TEXT("Failed to join lobby. ErrorCode="), EAutomationExpectedErrorFlags::Contains, 1);
    DeliverJoin(*Context.Lobby, Handle, E_FAIL);
    DeliverJoin(*Context.Lobby, Handle);
    TestEqual(TEXT("An active SDK completion is forwarded once"), Context.LobbyCompletions, 1);
    TestEqual(TEXT("Public join still waits for the native operation"), Context.JoinCompletions, 0);
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FPlayFabDestroyPendingLobbyJoinTest,
    "PlayFab.OSS.Session.SteamJoin.LobbyCompletion.ExistingDestroyOwnsCleanup",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabDestroyPendingLobbyJoinTest::RunTest(const FString&)
{
    FJoinTestContext Context;
    const auto State = Context.AddState();
    const auto Handle = FPlayFabLobbyJoinTestAccessor::Track(*Context.Lobby, State);
    TestTrue(TEXT("Destroy starts the normal leave operation"), Context.Sessions->DestroySession(State->SessionName));
    DeliverJoin(*Context.Lobby, Handle);
    TestEqual(TEXT("Late join does not duplicate a pending leave"), Context.Lobby->LeaveRequests, 1);
    TestTrue(TEXT("Normal destruction retains its mapping until leave completion"),
        FPlayFabLobbyJoinTestAccessor::IsMapped(*Context.Lobby, Handle));
    DeliverLeave(*Context.Lobby, Handle);
    TestEqual(TEXT("Pending destruction completes normally"), Context.DestroyCompletions, 1);
    TestEqual(TEXT("Cancelled join completes once after destruction"), Context.JoinCompletions, 1);
    TestFalse(TEXT("Destroyed session is removed"), Context.Sessions->GetSessionStatePtr(State->SessionName).IsValid());
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FPlayFabCompletedLobbyRemovalTest,
    "PlayFab.OSS.Session.SteamJoin.LobbyCompletion.RemovalAfterPlayFabSuccess",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabCompletedLobbyRemovalTest::RunTest(const FString&)
{
    FJoinTestContext Context;
    const auto State = Context.AddState();
    State->SteamJoinCompletion.CompletePlayFab(EOnJoinSessionCompleteResult::Success);
    const auto Handle = FPlayFabLobbyJoinTestAccessor::Track(*Context.Lobby, State, true);
    Context.Sessions->RemoveNamedSession(State->SessionName);
    TestEqual(TEXT("Removal cleans an already joined PlayFab lobby immediately"), Context.Lobby->LeaveRequests, 1);
    DeliverJoin(*Context.Lobby, Handle);
    TestEqual(TEXT("Duplicate PlayFab completion cannot duplicate cleanup"), Context.Lobby->LeaveRequests, 1);
    TestEqual(TEXT("Cancellation has one public result"), Context.JoinCompletions, 1);
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FPlayFabAbandonedLobbyCleanupTest,
    "PlayFab.OSS.Session.SteamJoin.LobbyCompletion.CleanupFailureRetainsOwnership",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabAbandonedLobbyCleanupTest::RunTest(const FString&)
{
    for (bool bRecover : {false, true})
    {
        FJoinTestContext Context;
        const auto State = Context.AddState();
        const auto Handle = FPlayFabLobbyJoinTestAccessor::Track(*Context.Lobby, State);
        Context.Sessions->RemoveNamedSession(State->SessionName);
        Context.Lobby->LeaveResult = E_FAIL;
        AddExpectedError(TEXT("FPlayFabLobby::CleanupDetachedLobby: PFLobbyLeave failed"),
            EAutomationExpectedErrorFlags::Contains, bRecover ? 1 : 3);
        if (!bRecover)
        {
            AddExpectedError(TEXT("cleanup exhausted 3 attempts"), EAutomationExpectedErrorFlags::Contains, 1);
        }
        DeliverJoin(*Context.Lobby, Handle);
        TestFalse(TEXT("Failed leave is not recorded as pending success"),
            FPlayFabLobbyJoinTestAccessor::IsLeavePending(*Context.Lobby, Handle));
        TestTrue(TEXT("Cleanup failure retains the abandoned operation"),
            FPlayFabLobbyJoinTestAccessor::HasOperation(*Context.Lobby, Handle));
        if (bRecover)
        {
            Context.Lobby->LeaveResult = S_OK;
        }
        FPlayFabLobbyJoinTestAccessor::RetryCleanup(*Context.Lobby, Handle);
        FPlayFabLobbyJoinTestAccessor::RetryCleanup(*Context.Lobby, Handle);
        FPlayFabLobbyJoinTestAccessor::RetryCleanup(*Context.Lobby, Handle);
        TestEqual(TEXT("Cleanup retries are bounded and stop after acceptance"),
            Context.Lobby->LeaveRequests, bRecover ? 2 : 3);
        TestEqual(TEXT("Pending leave reflects the actual SDK request result"),
            FPlayFabLobbyJoinTestAccessor::IsLeavePending(*Context.Lobby, Handle), bRecover);
        TestFalse(TEXT("Cleanup never restores the old session-name mapping"),
            FPlayFabLobbyJoinTestAccessor::IsMapped(*Context.Lobby, Handle));
        TestEqual(TEXT("Cleanup retries cannot repeat public cancellation"), Context.JoinCompletions, 1);
        if (bRecover)
        {
            DeliverLeave(*Context.Lobby, Handle);
            TestFalse(TEXT("Successful cleanup releases ownership"),
                FPlayFabLobbyJoinTestAccessor::HasOperation(*Context.Lobby, Handle));
        }
    }
    return true;
}

#endif
