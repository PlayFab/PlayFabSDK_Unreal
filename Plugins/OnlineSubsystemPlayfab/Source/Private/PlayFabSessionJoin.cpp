//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "PlayFabSessionJoin.h"
#include "OnlineSubsystemPlayFabTypes.h"
#include "OnlineSubsystemNames.h"
#include "OnlineSubsystemPlayFabDefines.h"
#include "OnlineSubsystemPlayFabPrivate.h"

namespace PlayFabSessionJoin
{
    namespace
    {
        bool Succeeded(FResult Result)
        {
            return Result == EOnJoinSessionCompleteResult::Success ||
                Result == EOnJoinSessionCompleteResult::AlreadyInSession;
        }
    }

    void AssociateNativeResults(
        TArray<FOnlineSessionSearchResult>& PlayFabResults,
        const TArray<FOnlineSessionSearchResult>& NativeResults)
    {
        for (FOnlineSessionSearchResult& Result : PlayFabResults)
        {
            if (!Result.Session.SessionInfo.IsValid() ||
                Result.Session.SessionInfo->GetSessionId().GetType() != PLAYFAB_SUBSYSTEM)
            {
                continue;
            }

            const auto Info = StaticCastSharedPtr<FOnlineSessionInfoPlayFab>(Result.Session.SessionInfo);
            Info->NativeSessionSearchResult.Reset();
            if (Info->GetNativePlatform() != PLATFORM_MODEL_WIN64 || Info->GetNativeSessionIdString().IsEmpty())
            {
                continue;
            }

            const FOnlineSessionSearchResult* NativeResult = NativeResults.FindByPredicate(
                [&Info](const FOnlineSessionSearchResult& Candidate)
                {
                    return Candidate.Session.SessionInfo.IsValid() &&
                        Candidate.Session.SessionInfo->IsValid() &&
                        Candidate.Session.SessionInfo->GetSessionId().GetType() == STEAM_SUBSYSTEM &&
                        Candidate.GetSessionIdStr() == Info->GetNativeSessionIdString();
                });
            if (NativeResult)
            {
                Info->NativeSessionSearchResult = MakeShared<FOnlineSessionSearchResult>(*NativeResult);
            }
        }
    }

    EResolution ResolveSteamSession(
        const FOnlineSessionSearchResult& DesiredSession,
        bool bDedicatedServer,
        FOnlineSessionSearchResult& OutNativeSession)
    {
        if (bDedicatedServer)
        {
            return EResolution::PlayFabOnly;
        }
        if (!DesiredSession.Session.SessionInfo.IsValid() || !DesiredSession.Session.SessionInfo->IsValid())
        {
            return EResolution::InvalidSession;
        }

        const FName Type = DesiredSession.Session.SessionInfo->GetSessionId().GetType();
        if (Type == STEAM_SUBSYSTEM)
        {
            OutNativeSession = DesiredSession;
            return EResolution::Native;
        }
        if (Type != PLAYFAB_SUBSYSTEM)
        {
            return EResolution::InvalidSession;
        }

        const auto Info = StaticCastSharedPtr<FOnlineSessionInfoPlayFab>(DesiredSession.Session.SessionInfo);
        if (Info->GetNativeSessionIdString().IsEmpty() || Info->GetNativePlatform() != PLATFORM_MODEL_WIN64)
        {
            return EResolution::PlayFabOnly;
        }

        const auto& NativeResult = Info->NativeSessionSearchResult;
        if (!NativeResult.IsValid() || !NativeResult->Session.SessionInfo.IsValid() ||
            !NativeResult->Session.SessionInfo->IsValid() ||
            NativeResult->Session.SessionInfo->GetSessionId().GetType() != STEAM_SUBSYSTEM ||
            NativeResult->GetSessionIdStr() != Info->GetNativeSessionIdString())
        {
            return EResolution::MissingNativeResult;
        }

        OutNativeSession = *NativeResult;
        return EResolution::Native;
    }

    void FState::Begin(bool bRequireNative)
    {
        Stage = EStage::Joining;
        PlayFabResult.Reset();
        NativeResult.Reset();
        if (!bRequireNative)
        {
            NativeResult = EOnJoinSessionCompleteResult::Success;
        }
    }

    TOptional<FResult> FState::CompletePlayFab(FResult Result)
    {
        // A lobby disconnect can invalidate Party success while the native join is still pending.
        if (!IsJoining() || (PlayFabResult.IsSet() &&
            (!Succeeded(PlayFabResult.GetValue()) || Succeeded(Result))))
        {
            return {};
        }
        PlayFabResult = Result;
        return TryComplete();
    }

    TOptional<FResult> FState::CompleteNative(FResult Result)
    {
        if (!IsJoining() || NativeResult.IsSet())
        {
            return {};
        }
        NativeResult = Result;
        return TryComplete();
    }

    TOptional<FResult> FState::TryComplete()
    {
        if (!PlayFabResult.IsSet() || !NativeResult.IsSet())
        {
            return {};
        }
        if (Succeeded(PlayFabResult.GetValue()) && Succeeded(NativeResult.GetValue()))
        {
            Stage = EStage::Complete;
            return EOnJoinSessionCompleteResult::Success;
        }
        FailureResult = Succeeded(PlayFabResult.GetValue()) ? NativeResult.GetValue() : PlayFabResult.GetValue();
        Stage = EStage::Rollback;
        return FailureResult;
    }

    TOptional<FResult> FState::Cancel()
    {
        if (!IsJoining())
        {
            return {};
        }
        Stage = EStage::Complete;
        return EOnJoinSessionCompleteResult::UnknownError;
    }

    TOptional<FResult> FState::CompleteRollback()
    {
        if (!IsRollingBack())
        {
            return {};
        }
        Stage = EStage::Complete;
        return FailureResult;
    }
}
