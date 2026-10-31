//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "Templates/Atomic.h"

namespace PlayFabPartyLifecycle
{
    class FState
    {
    public:
        // Platform callbacks only signal; all SDK work belongs to the game thread.
        void NotifyConnectivityChanged()
        {
            bConnectivityChanged.Store(true);
        }

        bool ConsumeConnectivityChanged(float DeltaTime = 0.0f)
        {
            check(IsInGameThread());
            const bool bChanged = bConnectivityChanged.Exchange(false);
            if (bSuspended || bShuttingDown)
            {
                return false;
            }

            if (bConnectivityQueryRetryPending)
            {
                ConnectivityQueryRetryRemainingSeconds = FMath::Max(0.0f, ConnectivityQueryRetryRemainingSeconds - DeltaTime);
            }
            if (!bChanged && (!bConnectivityQueryRetryPending || ConnectivityQueryRetryRemainingSeconds > 0.0f))
            {
                return false;
            }

            bConnectivityQueryRetryPending = false;
            return true;
        }

        void ScheduleConnectivityQueryRetry()
        {
            check(IsInGameThread());
            if (bSuspended || bShuttingDown)
            {
                return;
            }

            bConnectivityQueryRetryPending = true;
            ConnectivityQueryRetryRemainingSeconds = ConnectivityQueryRetryDelaySeconds;
            ConnectivityQueryRetryDelaySeconds = FMath::Min(ConnectivityQueryRetryDelaySeconds * 2.0f, MaxConnectivityQueryRetryDelaySeconds);
        }

        void ResetConnectivityQueryRetry()
        {
            check(IsInGameThread());
            bConnectivityQueryRetryPending = false;
            ConnectivityQueryRetryRemainingSeconds = 0.0f;
            ConnectivityQueryRetryDelaySeconds = InitialConnectivityQueryRetryDelaySeconds;
        }

        template <typename InitializeFunction>
        void TryInitialize(bool& bInitialized, InitializeFunction&& Initialize)
        {
            check(IsInGameThread());
            if (bInitialized || bSuspended || bShuttingDown || bTransitionInProgress)
            {
                return;
            }

            TGuardValue<bool> Transition(bTransitionInProgress, true);
            bInitialized = Initialize();
        }

        template <typename CleanupFunction>
        void Cleanup(bool& bInitialized, CleanupFunction&& CleanUp)
        {
            check(IsInGameThread());
            check(!bTransitionInProgress);
            if (!bInitialized)
            {
                return;
            }

            TGuardValue<bool> Transition(bTransitionInProgress, true);
            bInitialized = false;
            CleanUp();
        }

        void Suspend()
        {
            check(IsInGameThread());
            bSuspended = true;
            ++Generation;
            ResetConnectivityQueryRetry();
        }

        bool Resume(uint64 ExpectedGeneration)
        {
            check(IsInGameThread());
            if (bShuttingDown || ExpectedGeneration != Generation)
            {
                return false;
            }

            bSuspended = false;
            return true;
        }

        void BeginShutdown()
        {
            check(IsInGameThread());
            bShuttingDown = true;
            ++Generation;
            bConnectivityChanged.Store(false);
            ResetConnectivityQueryRetry();
        }

        uint64 GetGeneration() const { return Generation; }
        bool IsShuttingDown() const { return bShuttingDown; }

    private:
        static constexpr float InitialConnectivityQueryRetryDelaySeconds = 1.0f;
        static constexpr float MaxConnectivityQueryRetryDelaySeconds = 30.0f;

        TAtomic<bool> bConnectivityChanged{false};
        bool bConnectivityQueryRetryPending = false;
        float ConnectivityQueryRetryRemainingSeconds = 0.0f;
        float ConnectivityQueryRetryDelaySeconds = InitialConnectivityQueryRetryDelaySeconds;
        bool bSuspended = false;
        bool bShuttingDown = false;
        bool bTransitionInProgress = false;
        uint64 Generation = 0;
    };
}
