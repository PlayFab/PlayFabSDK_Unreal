//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "OnlineError.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystemPlayFabPackage.h"
#include "OnlineSubsystemTypes.h"

struct FPlayFabGroupMatchmakingRequest
{
	FString QueueName;
	int32 TimeoutInSeconds = 120;
	FString LocalUserAttributesJson;
	FOnlineSessionSettings SessionSettings;
};

struct FPlayFabGroupTicketCreatedResult
{
	bool bWasSuccessful = false;
	FName ResultSessionName;
	FString TicketId;
	FOnlineError Error;
};

struct FPlayFabGroupTicketJoinedResult
{
	bool bWasSuccessful = false;
	FName ResultSessionName;
	FOnlineError Error;
};

struct FPlayFabMatchmakingCompleteResult
{
	bool bWasSuccessful = false;
	FName ResultSessionName;
	FOnlineError Error;
};

DECLARE_DELEGATE_OneParam(FOnPlayFabGroupTicketCreated, const FPlayFabGroupTicketCreatedResult&);
DECLARE_DELEGATE_OneParam(FOnPlayFabGroupTicketJoined, const FPlayFabGroupTicketJoinedResult&);
DECLARE_DELEGATE_OneParam(FOnPlayFabMatchmakingComplete, const FPlayFabMatchmakingCompleteResult&);

/**
 * PlayFab-specific matchmaking operations that are not represented by IOnlineSession.
 *
 * These APIs create or join an active PlayFab matchmaking ticket. They do not prepare a ticket for
 * a later IOnlineSession::StartMatchmaking call. Calling StartMatchmaking afterward would create a
 * second ticket and conflicting named-session state.
 * Call these APIs on the game thread. Results are dispatched on a subsequent subsystem tick.
 * Calls on an interface retained after shutdown are rejected with synchronous failure callbacks.
 * Rejected requests report both the ticket-stage failure and the terminal failure.
 * Shutdown discards outstanding callbacks.
 * Removing or destroying the result session aborts a pending local operation, including Party
 * setup. Its Canceled/Aborted result does not confirm service-side cancellation and does not emit
 * OnCancelMatchmakingComplete. Local ticket destruction makes a best-effort service cancellation.
 */
class ONLINESUBSYSTEMPLAYFAB_API IOnlineMatchmakingPlayFab
{
public:
	virtual ~IOnlineMatchmakingPlayFab() = default;

	/**
	 * Creates and starts a matchmaking ticket for the supplied group.
	 *
	 * TicketCreatedCompletion reports when the ticket has been created and returns the ticket ID
	 * that should be shared with the expected remote members. The service initially keeps the ticket
	 * in WaitingForPlayers. After every expected member joins, it automatically advances to
	 * WaitingForMatch; no additional start call is required.
	 * ExpectedMembers is the complete platform-user roster, including LocalUserId. Remote members
	 * must be resolvable from current PlayFab lobby membership. Duplicate members are rejected.
	 * SessionSettings.NumPublicConnections must accommodate the complete match, not just this group.
	 *
	 * MatchmakingCompletion is independent from ticket creation. It reports the terminal result after
	 * PlayFab matchmaking and arranged-lobby processing complete. On success, ResultSessionName
	 * identifies the populated session that is ready for use.
	 */
	virtual bool CreateGroupMatchmakingTicket(
		const FUniqueNetIdRef& LocalUserId,
		FName ResultSessionName,
		const TArray<FUniqueNetIdRef>& ExpectedMembers,
		const FPlayFabGroupMatchmakingRequest& Request,
		FOnPlayFabGroupTicketCreated TicketCreatedCompletion,
		FOnPlayFabMatchmakingComplete MatchmakingCompletion) = 0;

	/**
	 * Joins an active group matchmaking ticket and starts local ticket processing.
	 *
	 * TicketJoinedCompletion reports whether the local member joined the ticket.
	 * MatchmakingCompletion later reports the terminal matchmaking and arranged-lobby result for
	 * this client. On success, ResultSessionName identifies the populated session ready for use.
	 * Use the creator's queue and compatible SessionSettings. Cancel either operation through
	 * IOnlineSession::CancelMatchmaking with ResultSessionName.
	 */
	virtual bool JoinGroupMatchmakingTicket(
		const FUniqueNetIdRef& LocalUserId,
		FName ResultSessionName,
		const FString& TicketId,
		const FPlayFabGroupMatchmakingRequest& Request,
		FOnPlayFabGroupTicketJoined TicketJoinedCompletion,
		FOnPlayFabMatchmakingComplete MatchmakingCompletion) = 0;
};

using IOnlineMatchmakingPlayFabPtr = TSharedPtr<IOnlineMatchmakingPlayFab, ESPMode::ThreadSafe>;
