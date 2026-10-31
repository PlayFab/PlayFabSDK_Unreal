//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

namespace PlayFabMatchmakingCompletion
{
    class FState
    {
    public:
        bool Begin()
        {
            if (Stage != EStage::Idle)
            {
                return false;
            }
            Stage = EStage::Ticket;
            return true;
        }

        bool BeginParty()
        {
            if (Stage != EStage::Ticket)
            {
                return false;
            }
            Stage = EStage::Party;
            return true;
        }

        bool BeginEndpoint()
        {
            if (Stage != EStage::Party)
            {
                return false;
            }
            Stage = EStage::Endpoint;
            return true;
        }

        bool TryComplete()
        {
            if (!IsInProgress())
            {
                return false;
            }
            Stage = EStage::Complete;
            return true;
        }

        bool IsInProgress() const { return Stage != EStage::Idle && Stage != EStage::Complete; }

    private:
        enum class EStage { Idle, Ticket, Party, Endpoint, Complete };
        EStage Stage = EStage::Idle;
    };
}
