//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

#include "Interfaces/OnlineSessionInterface.h"

namespace PlayFabSessionJoin
{
    using FResult = EOnJoinSessionCompleteResult::Type;

    enum class EResolution
    {
        PlayFabOnly,
        Native,
        MissingNativeResult,
        InvalidSession
    };

    void AssociateNativeResults(
        TArray<FOnlineSessionSearchResult>& PlayFabResults,
        const TArray<FOnlineSessionSearchResult>& NativeResults);
    EResolution ResolveSteamSession(
        const FOnlineSessionSearchResult& DesiredSession,
        bool bDedicatedServer,
        FOnlineSessionSearchResult& OutNativeSession);

    class FState
    {
    public:
        void Begin(bool bRequireNative);
        TOptional<FResult> CompletePlayFab(FResult Result);
        TOptional<FResult> CompleteNative(FResult Result);
        TOptional<FResult> Cancel();
        TOptional<FResult> CompleteRollback();
        bool IsJoining() const { return Stage == EStage::Joining; }
        bool IsRollingBack() const { return Stage == EStage::Rollback; }

    private:
        TOptional<FResult> TryComplete();

        enum class EStage { Idle, Joining, Rollback, Complete };
        EStage Stage = EStage::Idle;
        TOptional<FResult> PlayFabResult;
        TOptional<FResult> NativeResult;
        FResult FailureResult = EOnJoinSessionCompleteResult::UnknownError;
    };
}
