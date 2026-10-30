//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "OnlineSubsystemNames.h"
#include "OnlineSubsystemPlayFabPrivate.h"
#include "OnlineSubsystemPlayFabTypes.h"
#include "PlayFabSessionJoin.h"
#include "OnlineSessionInterfacePlayFab.h"

namespace
{
    class FNativeSessionInfoForJoinTest : public FOnlineSessionInfo
    {
    public:
        FNativeSessionInfoForJoinTest(const FString& Id, FName Type = STEAM_SUBSYSTEM)
            : SessionId(FUniqueNetIdString::Create(Id, Type))
        {
        }

        const uint8* GetBytes() const override { return nullptr; }
        int32 GetSize() const override { return 0; }
        bool IsValid() const override { return true; }
        FString ToString() const override { return SessionId->ToString(); }
        FString ToDebugString() const override { return ToString(); }
        const FUniqueNetId& GetSessionId() const override { return *SessionId; }

    private:
        FUniqueNetIdStringRef SessionId;
    };

    FOnlineSessionSearchResult MakePlayFabResult(const FString& NativeId, const FString& Platform = PLATFORM_MODEL_WIN64)
    {
        FOnlineSessionSearchResult Result;
        const auto Info = MakeShared<FOnlineSessionInfoPlayFab>();
        Info->SetSessionId(TEXT("playfab-lobby"));
        Info->ConnectionString = TEXT("connection");
        Info->SetNativeSessionIdString(NativeId);
        Info->SetNativePlatform(Platform);
        Result.Session.SessionInfo = Info;
        return Result;
    }

    FOnlineSessionSearchResult MakeNativeResult(const FString& Id, FName Type = STEAM_SUBSYSTEM)
    {
        FOnlineSessionSearchResult Result;
        Result.Session.SessionInfo = MakeShared<FNativeSessionInfoForJoinTest>(Id, Type);
        Result.Session.SessionSettings.bUseLobbiesIfAvailable = true;
        Result.Session.SessionSettings.bUsesPresence = true;
        return Result;
    }
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FPlayFabSteamJoinResolutionTest,
    "PlayFab.OSS.Session.SteamJoin.ResolvesOwnedNativeResult",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabSteamJoinResolutionTest::RunTest(const FString&)
{
    using namespace PlayFabSessionJoin;
    TArray<FOnlineSessionSearchResult> PlayFabResults = { MakePlayFabResult(TEXT("steam-lobby")) };
    TArray<FOnlineSessionSearchResult> NativeResults = { MakeNativeResult(TEXT("other")), MakeNativeResult(TEXT("steam-lobby")) };
    const auto ExpectedInfo = NativeResults[1].Session.SessionInfo;
    AssociateNativeResults(PlayFabResults, NativeResults);
    const FOnlineSessionSearchResult RetainedResult = PlayFabResults[0];
    NativeResults.Empty();
    PlayFabResults.Empty();

    FOnlineSessionSearchResult Resolved;
    TestTrue(TEXT("A retained PlayFab result resolves after the searches are released"),
        ResolveSteamSession(RetainedResult, false, Resolved) == EResolution::Native);
    TestTrue(TEXT("Resolution preserves the actual native SessionInfo object"), Resolved.Session.SessionInfo == ExpectedInfo);
    TestTrue(TEXT("Resolution does not forward PlayFab SessionInfo"), Resolved.Session.SessionInfo != RetainedResult.Session.SessionInfo);
    TestTrue(TEXT("Native settings are retained"), Resolved.Session.SessionSettings.bUseLobbiesIfAvailable);

    TArray<FOnlineSessionSearchResult> LaterSearch = { MakePlayFabResult(TEXT("different-lobby")) };
    AssociateNativeResults(LaterSearch, { MakeNativeResult(TEXT("different-lobby")) });
    TestTrue(TEXT("Another search does not invalidate a retained result"),
        ResolveSteamSession(RetainedResult, false, Resolved) == EResolution::Native);
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FPlayFabSteamJoinEligibilityTest,
    "PlayFab.OSS.Session.SteamJoin.PreservesPlayFabOnlyAndInvitePaths",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabSteamJoinEligibilityTest::RunTest(const FString&)
{
    using namespace PlayFabSessionJoin;
    FOnlineSessionSearchResult Resolved;
    TestTrue(TEXT("Server-created lobby needs no native result"),
        ResolveSteamSession(MakePlayFabResult(TEXT("")), false, Resolved) == EResolution::PlayFabOnly);
    TestTrue(TEXT("Cross-platform lobby needs no Steam result"),
        ResolveSteamSession(MakePlayFabResult(TEXT("native-id"), TEXT("OTHER")), false, Resolved) == EResolution::PlayFabOnly);
    TestTrue(TEXT("Dedicated server does not need a Steam local user"),
        ResolveSteamSession(MakePlayFabResult(TEXT("steam-id")), true, Resolved) == EResolution::PlayFabOnly);
    TestTrue(TEXT("Dedicated server accepts join settings without SessionInfo"),
        ResolveSteamSession(FOnlineSessionSearchResult(), true, Resolved) == EResolution::PlayFabOnly);
    TestTrue(TEXT("Client rejects invalid SessionInfo"),
        ResolveSteamSession(FOnlineSessionSearchResult(), false, Resolved) == EResolution::InvalidSession);

    const auto Invite = MakeNativeResult(TEXT("invite"));
    TestTrue(TEXT("Native invite result bypasses discovery"),
        ResolveSteamSession(Invite, false, Resolved) == EResolution::Native);
    TestTrue(TEXT("Native invite keeps its own SessionInfo"), Resolved.Session.SessionInfo == Invite.Session.SessionInfo);
    TestTrue(TEXT("Other native types are rejected"),
        ResolveSteamSession(MakeNativeResult(TEXT("id"), FName(TEXT("OTHER"))), false, Resolved) == EResolution::InvalidSession);
    TestTrue(TEXT("Missing required Steam result fails explicitly"),
        ResolveSteamSession(MakePlayFabResult(TEXT("missing")), false, Resolved) == EResolution::MissingNativeResult);

    TArray<FOnlineSessionSearchResult> Results = { MakePlayFabResult(TEXT("id")) };
    AssociateNativeResults(Results, { MakeNativeResult(TEXT("id"), FName(TEXT("OTHER"))) });
    TestTrue(TEXT("Matching strings cannot substitute another subsystem's SessionInfo"),
        ResolveSteamSession(Results[0], false, Resolved) == EResolution::MissingNativeResult);
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FPlayFabSteamSearchCompletionTest,
    "PlayFab.OSS.Session.SteamJoin.SearchWaitsForBothBackends",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabSteamSearchCompletionTest::RunTest(const FString&)
{
    using namespace PlayFabSessionJoin;
    for (bool bNativeFirst : { false, true })
    {
        FPlayFabFindSessionsOperation Operation;
        Operation.PlayFabSearch = MakeShared<FOnlineSessionSearch>();
        Operation.PlayFabSearch->SearchState = EOnlineAsyncTaskState::InProgress;
        Operation.PlayFabSearch->SearchResults.Add(MakePlayFabResult(TEXT("id")));
        Operation.NativeSearch = MakeShared<FOnlineSessionSearch>();
        Operation.NativeSearch->SearchResults.Add(MakeNativeResult(TEXT("id")));
        Operation.bPlayFabSuccess = true;
        Operation.bNativeSuccess = true;
        Operation.bNativeComplete = bNativeFirst;
        Operation.bPlayFabComplete = !bNativeFirst;
        Operation.bStarting = false;
        TestFalse(TEXT("First backend completion cannot publish search completion"), Operation.TryComplete().IsSet());
        Operation.bPlayFabComplete = true;
        Operation.bNativeComplete = true;
        Operation.bStarting = true;
        TestFalse(TEXT("Synchronous callbacks cannot publish completion before startup ends"), Operation.TryComplete().IsSet());
        Operation.bStarting = false;
        TestTrue(TEXT("Both backends complete the public search"), Operation.TryComplete().Get(false));
        TestTrue(TEXT("Final search state is done"), Operation.PlayFabSearch->SearchState == EOnlineAsyncTaskState::Done);
        FOnlineSessionSearchResult Resolved;
        TestTrue(TEXT("Immediate join after completion already has native data"),
            ResolveSteamSession(Operation.PlayFabSearch->SearchResults[0], false, Resolved) == EResolution::Native);
        TestFalse(TEXT("Duplicate search completion is suppressed"), Operation.TryComplete().IsSet());
    }

    FPlayFabFindSessionsOperation NativeFailure;
    NativeFailure.PlayFabSearch = MakeShared<FOnlineSessionSearch>();
    NativeFailure.PlayFabSearch->SearchResults.Add(MakePlayFabResult(TEXT("")));
    NativeFailure.bStarting = false;
    NativeFailure.bPlayFabComplete = true;
    NativeFailure.bPlayFabSuccess = true;
    TestTrue(TEXT("Native failure does not hide PlayFab-only results"), NativeFailure.TryComplete().Get(false));
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FPlayFabSteamJoinCompletionTest,
    "PlayFab.OSS.Session.SteamJoin.CompletesExactlyOnceInEitherOrder",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabSteamJoinCompletionTest::RunTest(const FString&)
{
    using namespace PlayFabSessionJoin;
    const auto Success = EOnJoinSessionCompleteResult::Success;
    for (bool bNativeFirst : { false, true })
    {
        FState State;
        State.Begin(true);
        const auto First = bNativeFirst ? State.CompleteNative(Success) : State.CompletePlayFab(Success);
        TestFalse(TEXT("First completion waits for the other subsystem"), First.IsSet());
        const auto Duplicate = bNativeFirst ? State.CompleteNative(Success) : State.CompletePlayFab(Success);
        TestFalse(TEXT("Duplicate first completion is ignored"), Duplicate.IsSet());
        const auto Final = bNativeFirst ? State.CompletePlayFab(Success) : State.CompleteNative(Success);
        TestTrue(TEXT("Both subsystems release completion"), Final.IsSet());
        TestTrue(TEXT("Both subsystems succeeded"), Final.Get(EOnJoinSessionCompleteResult::UnknownError) == Success);
        TestFalse(TEXT("Duplicate PlayFab result cannot complete again"), State.CompletePlayFab(Success).IsSet());
        TestFalse(TEXT("Duplicate native result cannot complete again"), State.CompleteNative(Success).IsSet());
        TestFalse(TEXT("Completed join cannot be cancelled"), State.Cancel().IsSet());
    }

    FState PlayFabOnly;
    PlayFabOnly.Begin(false);
    TestTrue(TEXT("PlayFab-only join does not wait for native completion"), PlayFabOnly.CompletePlayFab(Success).IsSet());
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FPlayFabSteamJoinRollbackTest,
    "PlayFab.OSS.Session.SteamJoin.FailureRollbackAndCancellation",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabSteamJoinRollbackTest::RunTest(const FString&)
{
    using namespace PlayFabSessionJoin;
    const auto Success = EOnJoinSessionCompleteResult::Success;
    const auto Failure = EOnJoinSessionCompleteResult::SessionIsFull;
    for (bool bNativeFails : { false, true })
    {
        FState State;
        State.Begin(true);
        TestFalse(TEXT("Failure waits for the other in-flight operation"),
            (bNativeFails ? State.CompleteNative(Failure) : State.CompletePlayFab(Failure)).IsSet());
        const auto Result = bNativeFails ? State.CompletePlayFab(Success) : State.CompleteNative(Success);
        TestTrue(TEXT("Original failure is preserved"), Result.Get(Success) == Failure);
        TestTrue(TEXT("Partial success requires rollback"), State.IsRollingBack());
        TestFalse(TEXT("Late success cannot complete a rollback"), State.CompleteNative(Success).IsSet());
        TestFalse(TEXT("Rollback cannot be replaced by cancellation"), State.Cancel().IsSet());
        TestTrue(TEXT("Rollback releases the failure once"), State.CompleteRollback().Get(Success) == Failure);
        TestFalse(TEXT("Duplicate cleanup cannot release completion twice"), State.CompleteRollback().IsSet());
    }

    FState Disconnected;
    Disconnected.Begin(true);
    Disconnected.CompletePlayFab(Success);
    TestFalse(TEXT("Lobby disconnect while native join is pending waits for native"), Disconnected.CompletePlayFab(Failure).IsSet());
    TestTrue(TEXT("A disconnected lobby cannot produce join success"), Disconnected.CompleteNative(Success).Get(Success) == Failure);

    FState Cancelled;
    Cancelled.Begin(true);
    TestTrue(TEXT("Pending join can be cancelled"), Cancelled.Cancel().IsSet());
    TestFalse(TEXT("Cancelled join ignores late native completion"), Cancelled.CompleteNative(Success).IsSet());
    TestFalse(TEXT("Cancelled join ignores late Party completion"), Cancelled.CompletePlayFab(Success).IsSet());
    TestFalse(TEXT("Cancellation is delivered once"), Cancelled.Cancel().IsSet());
    return true;
}

#endif
