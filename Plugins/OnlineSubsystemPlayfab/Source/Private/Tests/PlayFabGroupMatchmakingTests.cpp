//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "MatchmakingInterfacePlayFab.h"
#include "OnlineSessionInterfacePlayFab.h"
#include "OnlineSubsystemPlayFab.h"

class FPlayFabGroupMatchmakingTestAccessor
{
public:
    struct FLobby
    {
        PFEntityKey Member{"remote-entity", ENTITY_TYPE_TITLE_PLAYER};
        uint32_t MemberCount = 1;
        mutable int32 MemberReads = 0;
        mutable int32 PropertyReads = 0;
    };

    struct FNativeTicket
    {
        mutable int32 CancelRequests = 0;
        mutable int32 Destructions = 0;
    };

    static PFLobbyHandle MockLobby(FOnlineSessionPlayFab& Sessions, FLobby& Lobby)
    {
        Sessions.GetLobbyMembers = [](PFLobbyHandle Handle, uint32_t* Count, const PFEntityKey** Members) noexcept -> HRESULT
        {
            const auto& Data = *reinterpret_cast<const FLobby*>(Handle);
            ++Data.MemberReads;
            *Count = Data.MemberCount;
            *Members = Data.MemberCount ? &Data.Member : nullptr;
            return S_OK;
        };
        Sessions.GetLobbyMemberProperty = [](PFLobbyHandle Handle, const PFEntityKey*, const char*, const char** Value) noexcept -> HRESULT
        {
            ++reinterpret_cast<const FLobby*>(Handle)->PropertyReads;
            *Value = "remote-platform-user";
            return S_OK;
        };
        return reinterpret_cast<PFLobbyHandle>(&Lobby);
    }

    static void FailNativeCancellation(
        FMatchmakingInterfacePlayFab& Interface, const FOnlineMatchmakingTicketInfoPtr& Ticket, FNativeTicket& Native)
    {
        Ticket->PlayFabMatchTicket = reinterpret_cast<PFMatchmakingTicketHandle>(&Native);
        Interface.CancelTicket = [](PFMatchmakingTicketHandle Handle) noexcept -> HRESULT
        {
            ++reinterpret_cast<const FNativeTicket*>(Handle)->CancelRequests;
            return E_FAIL;
        };
        Interface.DestroyTicket = [](PFMultiplayerHandle, PFMatchmakingTicketHandle Handle) noexcept -> HRESULT
        {
            ++reinterpret_cast<const FNativeTicket*>(Handle)->Destructions;
            return S_OK;
        };
    }

    static void Abort(FOnlineSessionPlayFab& Sessions, const FPlayFabSessionStatePtr& State)
    {
        Sessions.AbortMatchmaking(State);
    }

    static void Initialize(FOnlineSubsystemPlayFab& Subsystem)
    {
        Subsystem.PlayFabLobbyInterface = MakeShared<FPlayFabLobby, ESPMode::ThreadSafe>(&Subsystem);
        Subsystem.MatchmakingInterface = MakeShared<FMatchmakingInterfacePlayFab, ESPMode::ThreadSafe>(&Subsystem);
        Subsystem.SessionInterface = MakeShared<FOnlineSessionPlayFab, ESPMode::ThreadSafe>(&Subsystem);
    }

    static void Finish(FOnlineSubsystemPlayFab& Subsystem)
    {
        Subsystem.SessionInterface.Reset();
        Subsystem.MatchmakingInterface.Reset();
        Subsystem.PlayFabLobbyInterface.Reset();
    }

    static void Pump(FOnlineSubsystemPlayFab& Subsystem)
    {
        Subsystem.FOnlineSubsystemImpl::Tick(0.0f);
    }

    static FOnlineMatchmakingTicketInfoPtr Prepare(
        FOnlineSubsystemPlayFab& Subsystem, FName Name, bool bJoining,
        const TSharedRef<FPlayFabGroupMatchmakingCallbacks>& Callbacks)
    {
        FOnlineSessionSettings Settings;
        Settings.NumPublicConnections = 4;
        Settings.bUseLobbiesVoiceChatIfAvailable = false;
        Settings.Set(FName(TEXT("GroupTestSetting")), FString(TEXT("retained")), EOnlineDataAdvertisementType::ViaOnlineService);
        const FPlayFabSessionStatePtr State = Subsystem.SessionInterface->TryAddSessionState(
            Name, MakeShared<FNamedOnlineSession, ESPMode::ThreadSafe>(Name, Settings));
        State->MatchmakingCompletion.Begin();
        State->NetworkFlowType = ENetworkFlowType::Matchmaking;
        State->GroupMatchmaking = Callbacks;
        Callbacks->bJoining = bJoining;
        const FOnlineMatchmakingTicketInfoPtr Ticket = MakeShared<FOnlineMatchmakingTicketInfo>();
        Ticket->SessionName = Name;
        Ticket->SessionState = State;
        Ticket->TicketId = TEXT("shared-group-ticket");
        Ticket->MatchmakingState = EOnlinePlayFabMatchmakingState::CreatingTicket;
        Ticket->SessionSettings = Settings;
        Subsystem.MatchmakingInterface->AddMatchmakingTicket(Name, Ticket);
        return Ticket;
    }

    static void Ready(FMatchmakingInterfacePlayFab& Interface, const FOnlineMatchmakingTicketInfoPtr& Ticket)
    {
        Interface.NotifyGroupTicketReady(Ticket);
    }

    static void Complete(FMatchmakingInterfacePlayFab& Interface, FName Name, const FOnlineMatchmakingTicketInfoPtr& Ticket, bool bSuccess)
    {
        Interface.CompleteMatchmakingTicket(Name, Ticket, bSuccess);
    }

    static void Cancel(FMatchmakingInterfacePlayFab& Interface, FName Name, const FOnlineMatchmakingTicketInfoPtr& Ticket)
    {
        Interface.CompleteMatchmakingCancellation(Name, Ticket);
    }
};

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FPlayFabGroupMatchmakingRejectionTest,
    "PlayFab.OSS.Matchmaking.Group.RejectionsAreTypedAndAsynchronous",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabGroupMatchmakingRejectionTest::RunTest(const FString&)
{
    FOnlineSubsystemPlayFab Subsystem(FName(TEXT("GroupRejectionTest")));
    FPlayFabGroupMatchmakingTestAccessor::Initialize(Subsystem);
    {
        const IOnlineMatchmakingPlayFabPtr Interface = Subsystem.GetPlayFabMatchmakingInterface();
        TestTrue(TEXT("The public accessor exposes the implementation"), Interface.IsValid());
        const FUniqueNetIdRef User = FUniqueNetIdPlayFab::Create(TEXT("local-platform-user"));
        const FName Name(TEXT("GroupGame"));
        FPlayFabGroupMatchmakingRequest Request;
        Request.SessionSettings.NumPublicConnections = 4;
        int32 Early = 0;
        int32 Final = 0;
        FOnPlayFabGroupTicketCreated Created = FOnPlayFabGroupTicketCreated::CreateLambda(
            [&](const FPlayFabGroupTicketCreatedResult& Result)
            {
                ++Early;
                TestFalse(TEXT("Rejected creation reports failure"), Result.bWasSuccessful);
                TestFalse(TEXT("Rejected creation carries an error"), Result.Error.WasSuccessful());
                TestTrue(TEXT("Rejected creation has no transferable ticket ID"), Result.TicketId.IsEmpty());
                TestEqual(TEXT("The result preserves its session name"), Result.ResultSessionName, Name);
            });
        FOnPlayFabMatchmakingComplete Completed = FOnPlayFabMatchmakingComplete::CreateLambda(
            [&](const FPlayFabMatchmakingCompleteResult& Result)
            {
                ++Final;
                TestEqual(TEXT("The ticket-stage result precedes its terminal result"), Early, Final);
                TestFalse(TEXT("The rejected request has a terminal failure"), Result.bWasSuccessful);
                TestFalse(TEXT("The terminal result carries an error"), Result.Error.WasSuccessful());
            });

        AddExpectedError(TEXT("Group matchmaking request for 'GroupGame' rejected:"), EAutomationExpectedErrorFlags::Contains, 8);
        TestFalse(TEXT("An empty roster is rejected"), Interface->CreateGroupMatchmakingTicket(User, Name, {}, Request, Created, Completed));
        Request.TimeoutInSeconds = 0;
        TestFalse(TEXT("An invalid timeout is rejected"), Interface->CreateGroupMatchmakingTicket(User, Name, {User}, Request, Created, Completed));
        Request.TimeoutInSeconds = 120;
        Request.LocalUserAttributesJson = TEXT("{");
        TestFalse(TEXT("Malformed attributes are rejected"), Interface->CreateGroupMatchmakingTicket(User, Name, {User}, Request, Created, Completed));
        Request.LocalUserAttributesJson.Reset();
        Request.SessionSettings.NumPublicConnections = 0;
        TestFalse(TEXT("An invalid lobby capacity is rejected"), Interface->CreateGroupMatchmakingTicket(User, Name, {User}, Request, Created, Completed));
        Request.SessionSettings.NumPublicConnections = 4;
        TestFalse(TEXT("A duplicate roster member is rejected"), Interface->CreateGroupMatchmakingTicket(User, Name, {User, User}, Request, Created, Completed));
        TestFalse(TEXT("A creator missing from the roster is rejected"), Interface->CreateGroupMatchmakingTicket(
            User, Name, {FUniqueNetIdPlayFab::Create(TEXT("remote-platform-user"))}, Request, Created, Completed));
        Request.QueueName = TEXT(" ");
        TestFalse(TEXT("A whitespace-only queue is rejected"), Interface->CreateGroupMatchmakingTicket(User, Name, {User}, Request, Created, Completed));
        Request.QueueName.Reset();
        TestFalse(TEXT("Unavailable authentication interfaces are rejected"), Interface->CreateGroupMatchmakingTicket(User, Name, {User}, Request, Created, Completed));
        TestEqual(TEXT("Rejections do not execute callbacks inline"), Early + Final, 0);
        FPlayFabGroupMatchmakingTestAccessor::Pump(Subsystem);
        TestEqual(TEXT("Each rejection reports one ticket-stage failure"), Early, 8);
        TestEqual(TEXT("Each rejection reports one terminal failure"), Final, 8);
        TestFalse(TEXT("Rejected requests cannot create provisional sessions"), Subsystem.GetSessionInterfacePlayFab()->GetSessionStatePtr(Name).IsValid());

        int32 Joins = 0;
        AddExpectedError(TEXT("Group matchmaking request for 'GroupGame' rejected:"), EAutomationExpectedErrorFlags::Contains, 1);
        TestFalse(TEXT("An empty ticket ID is rejected"), Interface->JoinGroupMatchmakingTicket(
            User, Name, FString(), Request,
            FOnPlayFabGroupTicketJoined::CreateLambda([&](const FPlayFabGroupTicketJoinedResult& Result)
            {
                ++Joins;
                TestFalse(TEXT("Rejected joins carry an error"), Result.Error.WasSuccessful());
            }), {}));
        FPlayFabGroupMatchmakingTestAccessor::Pump(Subsystem);
        TestEqual(TEXT("Join rejection invokes its typed callback once"), Joins, 1);
    }
    FPlayFabGroupMatchmakingTestAccessor::Finish(Subsystem);
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FPlayFabGroupMatchmakingCompletionTest,
    "PlayFab.OSS.Matchmaking.Group.TicketAcceptanceIsSeparateFromFinalCompletion",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabGroupMatchmakingCompletionTest::RunTest(const FString&)
{
    for (const bool bJoining : {false, true})
    {
        FOnlineSubsystemPlayFab Subsystem(FName(TEXT("GroupCompletionTest")));
        FPlayFabGroupMatchmakingTestAccessor::Initialize(Subsystem);
        {
            const FName Name(TEXT("GroupGame"));
            const auto Callbacks = MakeShared<FPlayFabGroupMatchmakingCallbacks>();
            int32 Early = 0;
            int32 Final = 0;
            int32 Legacy = 0;
            Callbacks->TicketCreated = FOnPlayFabGroupTicketCreated::CreateLambda(
                [&](const FPlayFabGroupTicketCreatedResult& Result)
                {
                    ++Early;
                    TestTrue(TEXT("Creation returns the confirmed shared ticket ID"), Result.bWasSuccessful && Result.TicketId == TEXT("shared-group-ticket"));
                });
            Callbacks->TicketJoined = FOnPlayFabGroupTicketJoined::CreateLambda(
                [&](const FPlayFabGroupTicketJoinedResult& Result)
                {
                    ++Early;
                    TestTrue(TEXT("Join acceptance is successful"), Result.bWasSuccessful);
                });
            Callbacks->Completion = FOnPlayFabMatchmakingComplete::CreateLambda(
                [&](const FPlayFabMatchmakingCompleteResult& Result)
                {
                    ++Final;
                    TestEqual(TEXT("Acceptance precedes terminal completion"), Early, 1);
                    TestTrue(TEXT("The final result reports a ready session"), Result.bWasSuccessful && Result.Error.WasSuccessful());
                });
            const FOnlineMatchmakingTicketInfoPtr Ticket = FPlayFabGroupMatchmakingTestAccessor::Prepare(Subsystem, Name, bJoining, Callbacks);
            const FOnlineSessionPlayFabPtr Sessions = Subsystem.GetSessionInterfacePlayFab();
            FDelegateHandle LegacyHandle = Sessions->AddOnMatchmakingCompleteDelegate_Handle(
                FOnMatchmakingCompleteDelegate::CreateLambda([&](FName, bool) { ++Legacy; }));
            FPlayFabGroupMatchmakingTestAccessor::Ready(*Subsystem.GetMatchmakingInterface(), Ticket);
            FPlayFabGroupMatchmakingTestAccessor::Ready(*Subsystem.GetMatchmakingInterface(), Ticket);
            FPlayFabGroupMatchmakingTestAccessor::Pump(Subsystem);
            TestEqual(TEXT("Repeated readiness reports acceptance once"), Early, 1);
            TestTrue(TEXT("Confirmed acceptance advances the internal ticket state"),
                Ticket->MatchmakingState == EOnlinePlayFabMatchmakingState::TicketCreated);
            TestEqual(TEXT("Ticket acceptance is not final matchmaking success"), Final, 0);

            FPlayFabGroupMatchmakingTestAccessor::Complete(*Subsystem.GetMatchmakingInterface(), Name, Ticket, true);
            const FPlayFabSessionStatePtr State = Sessions->GetSessionStatePtr(Name);
            TestTrue(TEXT("Arranged-lobby completion leaves Party setup pending"), State->MatchmakingCompletion.IsInProgress());
            State->NetworkId = TEXT("group-client-network");
            Subsystem.TriggerOnPartyEndpointCreatedDelegates(true, State->NetworkId, 1, false);
            Subsystem.TriggerOnPartyEndpointCreatedDelegates(true, State->NetworkId, 2, false);
            FPlayFabGroupMatchmakingTestAccessor::Pump(Subsystem);
            TestEqual(TEXT("Party readiness produces one terminal result"), Final, 1);
            TestEqual(TEXT("Group operations do not broadcast unrelated solo results"), Legacy, 0);
            FString Setting;
            TestTrue(TEXT("Caller session settings survive the operation"),
                State->NamedSession->SessionSettings.Get(FName(TEXT("GroupTestSetting")), Setting) && Setting == TEXT("retained"));
            TestEqual(TEXT("The caller's match capacity is retained"), State->NamedSession->SessionSettings.NumPublicConnections, 4);
            Sessions->ClearOnMatchmakingCompleteDelegate_Handle(LegacyHandle);
            Sessions->RemoveNamedSession(Name);
        }
        FPlayFabGroupMatchmakingTestAccessor::Finish(Subsystem);
    }
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FPlayFabGroupMatchmakingCancellationTest,
    "PlayFab.OSS.Matchmaking.Group.CancellationAndStaleEventsCompleteOnce",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabGroupMatchmakingCancellationTest::RunTest(const FString&)
{
    FOnlineSubsystemPlayFab Subsystem(FName(TEXT("GroupCancellationTest")));
    FPlayFabGroupMatchmakingTestAccessor::Initialize(Subsystem);
    {
        const FName Name(TEXT("GroupGame"));
        const auto Callbacks = MakeShared<FPlayFabGroupMatchmakingCallbacks>();
        int32 Early = 0;
        int32 Final = 0;
        int32 Cancellations = 0;
        Callbacks->TicketCreated = FOnPlayFabGroupTicketCreated::CreateLambda(
            [&](const FPlayFabGroupTicketCreatedResult& Result)
            {
                ++Early;
                TestFalse(TEXT("Cancellation before creation cannot return a ticket ID"), Result.bWasSuccessful || !Result.TicketId.IsEmpty());
                TestTrue(TEXT("Cancellation has a typed reason"), Result.Error.GetErrorResult() == EOnlineErrorResult::Canceled);
            });
        const FOnlineSessionPlayFabPtr Sessions = Subsystem.GetSessionInterfacePlayFab();
        Callbacks->Completion = FOnPlayFabMatchmakingComplete::CreateLambda(
            [&](const FPlayFabMatchmakingCompleteResult& Result)
            {
                ++Final;
                TestEqual(TEXT("Early cancellation precedes terminal cancellation"), Early, 1);
                TestTrue(TEXT("Terminal cancellation preserves its reason"), !Result.bWasSuccessful && Result.Error.GetErrorResult() == EOnlineErrorResult::Canceled);
                TestFalse(TEXT("Session cleanup precedes the callback"), Sessions->GetSessionStatePtr(Name).IsValid());
                FOnlineMatchmakingTicketInfoPtr Found;
                TestFalse(TEXT("Ticket cleanup precedes the callback"), Subsystem.GetMatchmakingInterface()->GetMatchmakingTicket(Name, Found));
            });
        FDelegateHandle Handle = Sessions->AddOnCancelMatchmakingCompleteDelegate_Handle(
            FOnCancelMatchmakingCompleteDelegate::CreateLambda([&](FName, bool bSuccess) { Cancellations += bSuccess ? 1 : 0; }));
        const auto Ticket = FPlayFabGroupMatchmakingTestAccessor::Prepare(Subsystem, Name, false, Callbacks);
        FPlayFabGroupMatchmakingTestAccessor::Cancel(*Subsystem.GetMatchmakingInterface(), Name, Ticket);
        FPlayFabGroupMatchmakingTestAccessor::Complete(*Subsystem.GetMatchmakingInterface(), Name, Ticket, true);
        FPlayFabGroupMatchmakingTestAccessor::Pump(Subsystem);
        TestEqual(TEXT("Pending creation fails once"), Early, 1);
        TestEqual(TEXT("Cancellation completes once"), Final, 1);
        TestEqual(TEXT("The existing cancellation delegate is preserved"), Cancellations, 1);

        const auto ReplacementCallbacks = MakeShared<FPlayFabGroupMatchmakingCallbacks>();
        int32 ReplacementResults = 0;
        ReplacementCallbacks->Completion = FOnPlayFabMatchmakingComplete::CreateLambda(
            [&](const FPlayFabMatchmakingCompleteResult&) { ++ReplacementResults; });
        const auto Replacement = FPlayFabGroupMatchmakingTestAccessor::Prepare(Subsystem, Name, true, ReplacementCallbacks);
        Subsystem.GetMatchmakingInterface()->OnJoinArrangedLobbyCompleted(Name, false, Ticket);
        FPlayFabGroupMatchmakingTestAccessor::Pump(Subsystem);
        FOnlineMatchmakingTicketInfoPtr Found;
        TestTrue(TEXT("An old completion cannot remove a replacement ticket"),
            Subsystem.GetMatchmakingInterface()->GetMatchmakingTicket(Name, Found) && Found == Replacement);
        TestEqual(TEXT("An old completion cannot finish the replacement"), ReplacementResults, 0);
        Sessions->RemoveNamedSession(Name);
        FPlayFabGroupMatchmakingTestAccessor::Pump(Subsystem);
        TestEqual(TEXT("Explicit teardown completes the replacement once"), ReplacementResults, 1);
        Sessions->ClearOnCancelMatchmakingCompleteDelegate_Handle(Handle);
    }
    FPlayFabGroupMatchmakingTestAccessor::Finish(Subsystem);
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FPlayFabGroupMatchmakingFailureTest,
    "PlayFab.OSS.Matchmaking.Group.FailuresPreserveAcceptanceAndCompleteOnce",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabGroupMatchmakingFailureTest::RunTest(const FString&)
{
    for (const bool bAccepted : {false, true})
    {
        FOnlineSubsystemPlayFab Subsystem(FName(TEXT("GroupFailureTest")));
        FPlayFabGroupMatchmakingTestAccessor::Initialize(Subsystem);
        {
            const FName Name(TEXT("GroupGame"));
            const auto Callbacks = MakeShared<FPlayFabGroupMatchmakingCallbacks>();
            int32 Early = 0;
            int32 Final = 0;
            Callbacks->TicketJoined = FOnPlayFabGroupTicketJoined::CreateLambda(
                [&](const FPlayFabGroupTicketJoinedResult& Result)
                {
                    ++Early;
                    TestEqual(TEXT("The early result reflects whether the ticket was accepted"), Result.bWasSuccessful, bAccepted);
                });
            Callbacks->Completion = FOnPlayFabMatchmakingComplete::CreateLambda(
                [&](const FPlayFabMatchmakingCompleteResult& Result)
                {
                    ++Final;
                    TestEqual(TEXT("The early result precedes terminal failure"), Early, 1);
                    TestTrue(TEXT("A failed ticket carries a terminal request error"),
                        !Result.bWasSuccessful && Result.Error.GetErrorResult() == EOnlineErrorResult::RequestFailure);
                    TestFalse(TEXT("A failed operation cleans up before its callback"),
                        Subsystem.GetSessionInterfacePlayFab()->GetSessionStatePtr(Name).IsValid());
                });
            const auto Ticket = FPlayFabGroupMatchmakingTestAccessor::Prepare(Subsystem, Name, true, Callbacks);
            if (bAccepted)
            {
                FPlayFabGroupMatchmakingTestAccessor::Ready(*Subsystem.GetMatchmakingInterface(), Ticket);
            }
            FPlayFabGroupMatchmakingTestAccessor::Complete(*Subsystem.GetMatchmakingInterface(), Name, Ticket, false);
            FPlayFabGroupMatchmakingTestAccessor::Complete(*Subsystem.GetMatchmakingInterface(), Name, Ticket, false);
            FPlayFabGroupMatchmakingTestAccessor::Pump(Subsystem);
            TestEqual(TEXT("Ticket failure cannot deliver a second early result"), Early, 1);
            TestEqual(TEXT("Ticket failure completes once"), Final, 1);
        }
        FPlayFabGroupMatchmakingTestAccessor::Finish(Subsystem);
    }
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FPlayFabGroupMatchmakingShutdownTest,
    "PlayFab.OSS.Matchmaking.Group.RetainedInterfaceRejectsAfterShutdown",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabGroupMatchmakingShutdownTest::RunTest(const FString&)
{
    FOnlineSubsystemPlayFab Subsystem(FName(TEXT("GroupShutdownTest")));
    FPlayFabGroupMatchmakingTestAccessor::Initialize(Subsystem);
    {
        const IOnlineMatchmakingPlayFabPtr Interface = Subsystem.GetPlayFabMatchmakingInterface();
        Subsystem.GetMatchmakingInterface()->Shutdown();
        int32 Early = 0;
        int32 Final = 0;
        AddExpectedError(TEXT("Group matchmaking request for 'GroupGame' rejected: SubsystemUnavailable"),
            EAutomationExpectedErrorFlags::Contains, 1);
        TestFalse(TEXT("A retained interface rejects requests after shutdown"), Interface->JoinGroupMatchmakingTicket(
            FUniqueNetIdPlayFab::Create(TEXT("local-platform-user")), FName(TEXT("GroupGame")), TEXT("old-ticket"), {},
            FOnPlayFabGroupTicketJoined::CreateLambda([&](const FPlayFabGroupTicketJoinedResult& Result)
            {
                ++Early;
                TestTrue(TEXT("The ticket-stage rejection identifies shutdown"),
                    Result.Error.GetErrorResult() == EOnlineErrorResult::MissingInterface);
            }),
            FOnPlayFabMatchmakingComplete::CreateLambda([&](const FPlayFabMatchmakingCompleteResult& Result)
            {
                ++Final;
                TestEqual(TEXT("Shutdown preserves early-before-terminal ordering"), Early, 1);
                TestFalse(TEXT("Shutdown cannot report success"), Result.bWasSuccessful);
            })));
        TestEqual(TEXT("Without an owner tick, shutdown rejects the ticket synchronously"), Early, 1);
        TestEqual(TEXT("Without an owner tick, shutdown rejects the operation synchronously"), Final, 1);
    }
    FPlayFabGroupMatchmakingTestAccessor::Finish(Subsystem);
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FPlayFabGroupMatchmakingMemberResolutionTest,
    "PlayFab.OSS.Matchmaking.Group.CachedMembersAreNotCurrentMembership",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabGroupMatchmakingMemberResolutionTest::RunTest(const FString&)
{
    FOnlineSubsystemPlayFab Subsystem(FName(TEXT("GroupMemberResolutionTest")));
    FPlayFabGroupMatchmakingTestAccessor::Initialize(Subsystem);
    {
        const FOnlineSessionPlayFabPtr Sessions = Subsystem.GetSessionInterfacePlayFab();
        const FName Name(TEXT("SquadSession"));
        FOnlineSessionSettings Settings;
        const auto State = Sessions->TryAddSessionState(Name, MakeShared<FNamedOnlineSession, ESPMode::ThreadSafe>(Name, Settings));
        State->EntityPlatformIdMapping.Add(TEXT("stale-entity"), TEXT("remote-platform-user"));
        FString EntityId(TEXT("old"));
        FString EntityType(TEXT("old"));
        TestFalse(TEXT("A cached mapping without a current lobby cannot resolve a member"),
            Sessions->GetPlayFabEntityKeyForPlatformUser(*FUniqueNetIdPlayFab::Create(TEXT("remote-platform-user")), EntityId, EntityType));
        TestTrue(TEXT("Unresolved members do not return stale output identities"), EntityId.IsEmpty() && EntityType.IsEmpty());
        Sessions->RemoveNamedSession(Name);
    }
    FPlayFabGroupMatchmakingTestAccessor::Finish(Subsystem);
    return true;
}

namespace
{
    class FNativeSessionInfoForGroupTest : public FOnlineSessionInfo
    {
    public:
        const uint8* GetBytes() const override { return nullptr; }
        int32 GetSize() const override { return 0; }
        bool IsValid() const override { return true; }
        FString ToString() const override { return SessionId->ToString(); }
        FString ToDebugString() const override { return ToString(); }
        const FUniqueNetId& GetSessionId() const override { return *SessionId; }

    private:
        FUniqueNetIdStringRef SessionId = FUniqueNetIdString::Create(TEXT("native-lobby"), FName(TEXT("Native")));
    };
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FPlayFabGroupMatchmakingNativeLobbyTest,
    "PlayFab.OSS.Matchmaking.Group.NativeBackedLobbiesResolveCurrentMembers",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabGroupMatchmakingNativeLobbyTest::RunTest(const FString&)
{
    for (bool bUsesNativeSession : {false, true})
    {
        FOnlineSubsystemPlayFab Subsystem(FName(TEXT("GroupNativeLobbyTest")));
        FPlayFabGroupMatchmakingTestAccessor::Initialize(Subsystem);
        {
            const auto Sessions = Subsystem.GetSessionInterfacePlayFab();
            const FName Name(TEXT("SquadSession"));
            const auto State = Sessions->TryAddSessionState(
                Name, MakeShared<FNamedOnlineSession, ESPMode::ThreadSafe>(Name, FOnlineSessionSettings()));
            State->bUsesNativeSession = bUsesNativeSession;
            State->NamedSession->SessionState = EOnlineSessionState::Pending;
            FPlayFabGroupMatchmakingTestAccessor::FLobby Lobby;
            const auto Info = MakeShared<FOnlineSessionInfoPlayFab>();
            Info->LobbyHandle = FPlayFabGroupMatchmakingTestAccessor::MockLobby(*Sessions, Lobby);
            State->NamedSession->SessionInfo = Info;
            const auto User = FUniqueNetIdPlayFab::Create(TEXT("remote-platform-user"));
            FString EntityId;
            FString EntityType;
            TestTrue(TEXT("A current PlayFab member resolves regardless of native-session use"),
                Sessions->GetPlayFabEntityKeyForPlatformUser(*User, EntityId, EntityType));
            TestEqual(TEXT("Resolution returns the live entity"), EntityId, FString(TEXT("remote-entity")));
            TestEqual(TEXT("Resolution returns the live entity type"), EntityType, FString(UTF8_TO_TCHAR(ENTITY_TYPE_TITLE_PLAYER)));
            TestEqual(TEXT("Resolution reads live members"), Lobby.MemberReads, 1);
            TestEqual(TEXT("Resolution reads the member's platform identity"), Lobby.PropertyReads, 1);

            State->EntityPlatformIdMapping.Add(TEXT("remote-entity"), TEXT("remote-platform-user"));
            Lobby.MemberCount = 0;
            TestFalse(TEXT("Departed members cannot resolve through a cached mapping"),
                Sessions->GetPlayFabEntityKeyForPlatformUser(*User, EntityId, EntityType));
            TestTrue(TEXT("Departed members clear prior outputs"), EntityId.IsEmpty() && EntityType.IsEmpty());
            Lobby.MemberCount = 1;
            State->NamedSession->SessionState = EOnlineSessionState::Destroying;
            TestFalse(TEXT("Destroying lobbies remain ineligible"),
                Sessions->GetPlayFabEntityKeyForPlatformUser(*User, EntityId, EntityType));
            State->NamedSession->SessionState = EOnlineSessionState::Pending;
            Info->LobbyHandle = nullptr;
            TestFalse(TEXT("PlayFab session information without a lobby remains ineligible"),
                Sessions->GetPlayFabEntityKeyForPlatformUser(*User, EntityId, EntityType));
            State->NamedSession->SessionInfo = MakeShared<FNativeSessionInfoForGroupTest>();
            TestFalse(TEXT("Native-only information is rejected before the PlayFab cast"),
                Sessions->GetPlayFabEntityKeyForPlatformUser(*User, EntityId, EntityType));
            State->NamedSession->SessionInfo.Reset();
            TestFalse(TEXT("Missing session information remains ineligible"),
                Sessions->GetPlayFabEntityKeyForPlatformUser(*User, EntityId, EntityType));
            TestEqual(TEXT("Ineligible sessions never reach the SDK"), Lobby.MemberReads, 2);
            Sessions->RemoveNamedSession(Name);
        }
        FPlayFabGroupMatchmakingTestAccessor::Finish(Subsystem);
    }
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FPlayFabGroupMatchmakingAbortCancellationFailureTest,
    "PlayFab.OSS.Matchmaking.Group.AbortReleasesTicketsWhenCancellationFails",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabGroupMatchmakingAbortCancellationFailureTest::RunTest(const FString&)
{
    for (bool bAccepted : {false, true})
    {
        FOnlineSubsystemPlayFab Subsystem(FName(TEXT("GroupAbortFailureTest")));
        FPlayFabGroupMatchmakingTestAccessor::Initialize(Subsystem);
        {
            const auto Sessions = Subsystem.GetSessionInterfacePlayFab();
            const auto Matchmaking = Subsystem.GetMatchmakingInterface();
            const FName Name(TEXT("GroupGame"));
            const auto Callbacks = MakeShared<FPlayFabGroupMatchmakingCallbacks>();
            int32 Early = 0;
            int32 Final = 0;
            int32 CancellationCallbacks = 0;
            FOnlineMatchmakingTicketInfoPtr Replacement;
            Callbacks->TicketCreated = FOnPlayFabGroupTicketCreated::CreateLambda(
                [&](const FPlayFabGroupTicketCreatedResult& Result)
                {
                    ++Early;
                    TestEqual(TEXT("Abort preserves an earlier acceptance"), Result.bWasSuccessful, bAccepted);
                    if (!bAccepted)
                    {
                        TestTrue(TEXT("Abort before acceptance reports local cancellation"),
                            Result.Error.GetErrorResult() == EOnlineErrorResult::Canceled && Result.TicketId.IsEmpty());
                    }
                });
            Callbacks->Completion = FOnPlayFabMatchmakingComplete::CreateLambda(
                [&](const FPlayFabMatchmakingCompleteResult& Result)
                {
                    ++Final;
                    TestEqual(TEXT("Ticket-stage completion precedes local abort"), Early, 1);
                    TestTrue(TEXT("Local abort is a canceled failure, not service cancellation success"),
                        !Result.bWasSuccessful && Result.Error.GetErrorResult() == EOnlineErrorResult::Canceled);
                    TestFalse(TEXT("The old session is removed before callbacks"), Sessions->GetSessionStatePtr(Name).IsValid());
                    FOnlineMatchmakingTicketInfoPtr Found;
                    TestFalse(TEXT("The old ticket is removed before callbacks"), Matchmaking->GetMatchmakingTicket(Name, Found));
                    Replacement = FPlayFabGroupMatchmakingTestAccessor::Prepare(
                        Subsystem, Name, false, MakeShared<FPlayFabGroupMatchmakingCallbacks>());
                });
            FDelegateHandle Handle = Sessions->AddOnCancelMatchmakingCompleteDelegate_Handle(
                FOnCancelMatchmakingCompleteDelegate::CreateLambda([&](FName, bool) { ++CancellationCallbacks; }));
            const auto Ticket = FPlayFabGroupMatchmakingTestAccessor::Prepare(Subsystem, Name, false, Callbacks);
            const auto OldState = Sessions->GetSessionStatePtr(Name);
            FPlayFabGroupMatchmakingTestAccessor::FNativeTicket Native;
            FPlayFabGroupMatchmakingTestAccessor::FailNativeCancellation(*Matchmaking, Ticket, Native);
            if (bAccepted)
            {
                FPlayFabGroupMatchmakingTestAccessor::Ready(*Matchmaking, Ticket);
                FPlayFabGroupMatchmakingTestAccessor::Pump(Subsystem);
            }
            AddExpectedError(TEXT("PFMatchmakingTicketCancel failed"), EAutomationExpectedErrorFlags::Contains, 1);
            Sessions->RemoveNamedSession(Name);
            FPlayFabGroupMatchmakingTestAccessor::Abort(*Sessions, OldState);
            FPlayFabGroupMatchmakingTestAccessor::Pump(Subsystem);
            TestEqual(TEXT("Service cancellation is attempted once"), Native.CancelRequests, 1);
            TestEqual(TEXT("Cancellation failure cannot prevent local ticket destruction"), Native.Destructions, 1);
            TestTrue(TEXT("Local destruction clears the native handle"), Ticket->PlayFabMatchTicket == nullptr);
            TestEqual(TEXT("The ticket-stage callback is delivered once"), Early, 1);
            TestEqual(TEXT("The terminal callback is delivered once"), Final, 1);
            TestEqual(TEXT("Local abort emits no explicit-cancellation delegate"), CancellationCallbacks, 0);
            Matchmaking->OnJoinArrangedLobbyCompleted(Name, true, Ticket);
            FPlayFabGroupMatchmakingTestAccessor::Pump(Subsystem);
            FOnlineMatchmakingTicketInfoPtr Found;
            TestTrue(TEXT("A late old result cannot remove the reentrant replacement"),
                Matchmaking->GetMatchmakingTicket(Name, Found) && Found == Replacement);
            Sessions->RemoveNamedSession(Name);
            Sessions->ClearOnCancelMatchmakingCompleteDelegate_Handle(Handle);
        }
        FPlayFabGroupMatchmakingTestAccessor::Finish(Subsystem);
    }
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FPlayFabGroupMatchmakingPartyAbortTest,
    "PlayFab.OSS.Matchmaking.Group.AbortDuringPartySetupCompletesWithoutTicket",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabGroupMatchmakingPartyAbortTest::RunTest(const FString&)
{
    for (bool bJoining : {false, true})
    {
        FOnlineSubsystemPlayFab Subsystem(FName(TEXT("GroupPartyAbortTest")));
        FPlayFabGroupMatchmakingTestAccessor::Initialize(Subsystem);
        {
            const auto Sessions = Subsystem.GetSessionInterfacePlayFab();
            const auto Matchmaking = Subsystem.GetMatchmakingInterface();
            const FName Name(TEXT("GroupGame"));
            const auto Callbacks = MakeShared<FPlayFabGroupMatchmakingCallbacks>();
            int32 Early = 0;
            int32 Final = 0;
            int32 CancellationCallbacks = 0;
            Callbacks->TicketCreated = FOnPlayFabGroupTicketCreated::CreateLambda(
                [&](const FPlayFabGroupTicketCreatedResult& Result) { ++Early; TestTrue(TEXT("Creation was accepted"), Result.bWasSuccessful); });
            Callbacks->TicketJoined = FOnPlayFabGroupTicketJoined::CreateLambda(
                [&](const FPlayFabGroupTicketJoinedResult& Result) { ++Early; TestTrue(TEXT("Join was accepted"), Result.bWasSuccessful); });
            Callbacks->Completion = FOnPlayFabMatchmakingComplete::CreateLambda(
                [&](const FPlayFabMatchmakingCompleteResult& Result)
                {
                    ++Final;
                    TestEqual(TEXT("Acceptance still precedes terminal abort"), Early, 1);
                    TestTrue(TEXT("Party-stage abort preserves local cancellation"),
                        !Result.bWasSuccessful && Result.Error.GetErrorResult() == EOnlineErrorResult::Canceled);
                    TestFalse(TEXT("Party-stage abort removes the session before completion"),
                        Sessions->GetSessionStatePtr(Name).IsValid());
                });
            FDelegateHandle Handle = Sessions->AddOnCancelMatchmakingCompleteDelegate_Handle(
                FOnCancelMatchmakingCompleteDelegate::CreateLambda([&](FName, bool) { ++CancellationCallbacks; }));
            const auto Ticket = FPlayFabGroupMatchmakingTestAccessor::Prepare(Subsystem, Name, bJoining, Callbacks);
            FPlayFabGroupMatchmakingTestAccessor::Ready(*Matchmaking, Ticket);
            FPlayFabGroupMatchmakingTestAccessor::Pump(Subsystem);
            FPlayFabGroupMatchmakingTestAccessor::Complete(*Matchmaking, Name, Ticket, true);
            const auto State = Sessions->GetSessionStatePtr(Name);
            FOnlineMatchmakingTicketInfoPtr Found;
            TestFalse(TEXT("The arranged-lobby result has already removed the ticket"), Matchmaking->GetMatchmakingTicket(Name, Found));
            TestTrue(TEXT("Final Party readiness is still pending"), State.IsValid() && State->MatchmakingCompletion.IsInProgress());
            Sessions->RemoveNamedSession(Name);
            FPlayFabGroupMatchmakingTestAccessor::Abort(*Sessions, State);
            Matchmaking->OnJoinArrangedLobbyCompleted(Name, true, Ticket);
            FPlayFabGroupMatchmakingTestAccessor::Pump(Subsystem);
            TestEqual(TEXT("Party-stage teardown does not repeat acceptance"), Early, 1);
            TestEqual(TEXT("Party-stage teardown completes once without a ticket"), Final, 1);
            TestEqual(TEXT("Party-stage abort emits no explicit-cancellation delegate"), CancellationCallbacks, 0);
            Sessions->ClearOnCancelMatchmakingCompleteDelegate_Handle(Handle);
        }
        FPlayFabGroupMatchmakingTestAccessor::Finish(Subsystem);
    }
    return true;
}

#endif
