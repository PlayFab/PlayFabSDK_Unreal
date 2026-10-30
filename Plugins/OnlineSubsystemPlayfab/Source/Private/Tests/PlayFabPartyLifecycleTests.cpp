//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "Async/Async.h"
#include "PlayFabPartyLifecycle.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FPlayFabPartyInitializationOwnershipTest,
    "PlayFab.OSS.Party.Lifecycle.ConnectivityDefersToOwner",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabPartyInitializationOwnershipTest::RunTest(const FString&)
{
    PlayFabPartyLifecycle::FState State;
    bool bInitialized = false;
    int32 InitializeCount = 0;
    auto Initialize = [&]()
    {
        ++InitializeCount;
        State.TryInitialize(bInitialized, [&]() { ++InitializeCount; return true; });
        return true;
    };

    Async(EAsyncExecution::Thread, [&]()
    {
        State.NotifyConnectivityChanged();
        State.NotifyConnectivityChanged();
    }).Wait();
    TestEqual(TEXT("Worker notifications do not enter the SDK"), InitializeCount, 0);
    TestFalse(TEXT("Worker notifications do not publish readiness"), bInitialized);

    State.TryInitialize(bInitialized, Initialize);
    TestTrue(TEXT("Startup publishes successful initialization"), bInitialized);
    TestTrue(TEXT("The initial connectivity notification is pending"), State.ConsumeConnectivityChanged());
    State.TryInitialize(bInitialized, Initialize);
    TestFalse(TEXT("Repeated notifications are coalesced"), State.ConsumeConnectivityChanged());
    TestEqual(TEXT("Startup, reentry and connectivity initialize the SDK once"), InitializeCount, 1);
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FPlayFabPartyInitializationRetryTest,
    "PlayFab.OSS.Party.Lifecycle.FailureCanRetry",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabPartyInitializationRetryTest::RunTest(const FString&)
{
    PlayFabPartyLifecycle::FState State;
    bool bInitialized = false;
    int32 InitializeCount = 0;
    int32 CleanupCount = 0;
    State.TryInitialize(bInitialized, [&]() { ++InitializeCount; return false; });
    TestFalse(TEXT("Failure does not publish readiness"), bInitialized);
    State.Cleanup(bInitialized, [&]() { ++CleanupCount; });
    TestEqual(TEXT("Failed initialization does not clean up an unowned SDK"), CleanupCount, 0);

    State.NotifyConnectivityChanged();
    TestTrue(TEXT("A later connectivity event permits retry"), State.ConsumeConnectivityChanged());
    State.TryInitialize(bInitialized, [&]() { ++InitializeCount; return true; });
    State.TryInitialize(bInitialized, [&]() { ++InitializeCount; return true; });
    TestTrue(TEXT("Retry publishes readiness"), bInitialized);
    TestEqual(TEXT("Only failure and the successful retry reach the SDK"), InitializeCount, 2);
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FPlayFabPartySuspendResumeTest,
    "PlayFab.OSS.Party.Lifecycle.SuspendBlocksConnectivity",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabPartySuspendResumeTest::RunTest(const FString&)
{
    PlayFabPartyLifecycle::FState State;
    bool bInitialized = false;
    int32 InitializeCount = 0;
    int32 CleanupCount = 0;
    auto Initialize = [&]() { ++InitializeCount; return true; };
    State.TryInitialize(bInitialized, Initialize);
    State.Suspend();
    State.Cleanup(bInitialized, [&]()
    {
        ++CleanupCount;
        TestFalse(TEXT("Readiness is revoked before cleanup"), bInitialized);
        State.TryInitialize(bInitialized, Initialize);
        State.NotifyConnectivityChanged();
    });
    State.Cleanup(bInitialized, [&]() { ++CleanupCount; });
    TestFalse(TEXT("Connectivity cannot request initialization during suspend"), State.ConsumeConnectivityChanged());
    State.TryInitialize(bInitialized, Initialize);
    TestEqual(TEXT("Suspend cleans up once"), CleanupCount, 1);
    TestEqual(TEXT("Cleanup and suspended connectivity cannot reinitialize"), InitializeCount, 1);
    TestTrue(TEXT("Current resume is accepted"), State.Resume(State.GetGeneration()));
    State.TryInitialize(bInitialized, Initialize);
    TestEqual(TEXT("Resume initializes once"), InitializeCount, 2);
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FPlayFabPartyStaleResumeTest,
    "PlayFab.OSS.Party.Lifecycle.StaleResumeCannotRestart",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabPartyStaleResumeTest::RunTest(const FString&)
{
    PlayFabPartyLifecycle::FState State;
    bool bInitialized = false;
    int32 InitializeCount = 0;
    State.Suspend();
    const uint64 FirstResume = State.GetGeneration();
    State.Suspend();
    TestFalse(TEXT("Earlier resume completion cannot undo a later suspend"), State.Resume(FirstResume));
    State.TryInitialize(bInitialized, [&]() { ++InitializeCount; return true; });
    TestEqual(TEXT("Old resume leaves initialization suspended"), InitializeCount, 0);
    TestTrue(TEXT("Latest resume is accepted"), State.Resume(State.GetGeneration()));
    State.TryInitialize(bInitialized, [&]() { ++InitializeCount; return true; });
    TestEqual(TEXT("Current resume can initialize"), InitializeCount, 1);
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FPlayFabPartyShutdownOwnershipTest,
    "PlayFab.OSS.Party.Lifecycle.ShutdownRejectsLateWork",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabPartyShutdownOwnershipTest::RunTest(const FString&)
{
    PlayFabPartyLifecycle::FState State;
    bool bInitialized = false;
    int32 InitializeCount = 0;
    int32 CleanupCount = 0;
    State.TryInitialize(bInitialized, [&]() { ++InitializeCount; return true; });
    const uint64 ResumeGeneration = State.GetGeneration();
    State.NotifyConnectivityChanged();
    State.BeginShutdown();
    Async(EAsyncExecution::Thread, [&]() { State.NotifyConnectivityChanged(); }).Wait();
    TestFalse(TEXT("Late callback cannot request SDK work after shutdown"), State.ConsumeConnectivityChanged());
    TestFalse(TEXT("Pending resume is invalidated"), State.Resume(ResumeGeneration));
    TestFalse(TEXT("Even a new resume cannot undo shutdown"), State.Resume(State.GetGeneration()));
    State.Cleanup(bInitialized, [&]()
    {
        ++CleanupCount;
        State.TryInitialize(bInitialized, [&]() { ++InitializeCount; return true; });
    });
    State.BeginShutdown();
    State.Cleanup(bInitialized, [&]() { ++CleanupCount; });
    State.TryInitialize(bInitialized, [&]() { ++InitializeCount; return true; });
    TestEqual(TEXT("Shutdown cleans up the owned SDK once"), CleanupCount, 1);
    TestEqual(TEXT("Late work never reinitializes"), InitializeCount, 1);
    TestFalse(TEXT("Shutdown leaves Party unavailable"), bInitialized);
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FPlayFabPartyConnectivityOwnershipTest,
    "PlayFab.OSS.Party.Lifecycle.ConnectivityIsInstanceOwned",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabPartyConnectivityOwnershipTest::RunTest(const FString&)
{
    PlayFabPartyLifecycle::FState Old;
    PlayFabPartyLifecycle::FState Replacement;
    Old.NotifyConnectivityChanged();
    Old.BeginShutdown();
    Old.NotifyConnectivityChanged();
    TestFalse(TEXT("Old callbacks cannot signal another subsystem"), Replacement.ConsumeConnectivityChanged());
    TestFalse(TEXT("Old callbacks cannot resurrect the old subsystem"), Old.ConsumeConnectivityChanged());
    Replacement.NotifyConnectivityChanged();
    TestTrue(TEXT("Replacement consumes its own callback"), Replacement.ConsumeConnectivityChanged());
    TestFalse(TEXT("One notification is consumed once"), Replacement.ConsumeConnectivityChanged());
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FPlayFabPartyConnectivityQueryRetryTest,
    "PlayFab.OSS.Party.Lifecycle.ConnectivityQueryFailureRetriesWithoutNotification",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabPartyConnectivityQueryRetryTest::RunTest(const FString&)
{
    PlayFabPartyLifecycle::FState State;
    bool bInitialized = false;
    int32 QueryCount = 0;
    int32 InitializeCount = 0;
    auto Tick = [&](float DeltaTime)
    {
        if (!State.ConsumeConnectivityChanged(DeltaTime))
        {
            return;
        }
        ++QueryCount;
        if (QueryCount == 1)
        {
            State.ScheduleConnectivityQueryRetry();
            return;
        }
        State.ResetConnectivityQueryRetry();
        State.TryInitialize(bInitialized, [&]() { ++InitializeCount; return true; });
    };

    State.NotifyConnectivityChanged();
    Tick(0.0f);
    TestEqual(TEXT("The initial notification queries readiness"), QueryCount, 1);
    TestFalse(TEXT("A failed readiness query cannot initialize Party"), bInitialized);
    Tick(0.5f);
    TestEqual(TEXT("A failed query does not retry every frame"), QueryCount, 1);
    Tick(0.5f);
    TestEqual(TEXT("Readiness is retried without another notification"), QueryCount, 2);
    TestTrue(TEXT("The successful retry initializes Party"), bInitialized);
    Tick(60.0f);
    TestEqual(TEXT("A successful query cancels further retries"), QueryCount, 2);
    TestEqual(TEXT("Recovery initializes Party exactly once"), InitializeCount, 1);
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FPlayFabPartyConnectivityQueryBackoffTest,
    "PlayFab.OSS.Party.Lifecycle.ConnectivityQueryRetryBackoff",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabPartyConnectivityQueryBackoffTest::RunTest(const FString&)
{
    PlayFabPartyLifecycle::FState State;
    for (const float Delay : {1.0f, 2.0f, 4.0f, 8.0f, 16.0f, 30.0f, 30.0f})
    {
        State.ScheduleConnectivityQueryRetry();
        TestFalse(TEXT("A failed query waits for its backoff"), State.ConsumeConnectivityChanged(Delay * 0.5f));
        TestTrue(TEXT("Retry becomes due at the capped exponential delay"), State.ConsumeConnectivityChanged(Delay * 0.5f));
        TestFalse(TEXT("Each scheduled retry is consumed once"), State.ConsumeConnectivityChanged());
    }

    State.ScheduleConnectivityQueryRetry();
    Async(EAsyncExecution::Thread, [&]() { State.NotifyConnectivityChanged(); }).Wait();
    TestTrue(TEXT("Fresh connectivity hints bypass the retry delay"), State.ConsumeConnectivityChanged());
    State.ScheduleConnectivityQueryRetry();
    State.ResetConnectivityQueryRetry();
    TestFalse(TEXT("A successful direct query cancels a pending retry"), State.ConsumeConnectivityChanged(60.0f));
    State.ScheduleConnectivityQueryRetry();
    TestFalse(TEXT("Success resets the backoff to its initial delay"), State.ConsumeConnectivityChanged(0.5f));
    TestTrue(TEXT("The next failure retries after one second"), State.ConsumeConnectivityChanged(0.5f));
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FPlayFabPartyConnectivityQueryRetryLifecycleTest,
    "PlayFab.OSS.Party.Lifecycle.ConnectivityQueryRetryRespectsLifecycle",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabPartyConnectivityQueryRetryLifecycleTest::RunTest(const FString&)
{
    PlayFabPartyLifecycle::FState State;
    State.ScheduleConnectivityQueryRetry();
    State.Suspend();
    State.ScheduleConnectivityQueryRetry();
    State.NotifyConnectivityChanged();
    TestFalse(TEXT("Suspend blocks retries and connectivity notifications"), State.ConsumeConnectivityChanged(60.0f));
    TestTrue(TEXT("The current resume is accepted"), State.Resume(State.GetGeneration()));
    TestFalse(TEXT("Resume cannot consume a pre-suspend retry"), State.ConsumeConnectivityChanged(60.0f));
    State.ScheduleConnectivityQueryRetry();
    TestFalse(TEXT("Suspend resets the retry backoff"), State.ConsumeConnectivityChanged(0.5f));
    TestTrue(TEXT("A resumed query failure retries after one second"), State.ConsumeConnectivityChanged(0.5f));

    State.ScheduleConnectivityQueryRetry();
    State.BeginShutdown();
    State.ScheduleConnectivityQueryRetry();
    State.NotifyConnectivityChanged();
    TestFalse(TEXT("Shutdown blocks old retries and late notifications"), State.ConsumeConnectivityChanged(60.0f));
    return true;
}

#endif
