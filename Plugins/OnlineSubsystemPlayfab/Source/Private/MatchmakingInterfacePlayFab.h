//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

#include "OnlineDelegateMacros.h"
#include "OnlineSubsystemPlayFabPackage.h"
#include "PlayFabLobby.h"
#include "OnlineMatchmakingInterfacePlayFab.h"

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnMatchmakingTicketCompleted, bool, FName, TSharedPtr<FPlayFabSessionState>);
typedef FOnMatchmakingTicketCompleted::FDelegate FOnMatchmakingTicketCompletedDelegate;

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnPlayFabTicketCancellationComplete, FName, bool, TSharedPtr<FPlayFabSessionState>);
typedef FOnPlayFabTicketCancellationComplete::FDelegate FOnPlayFabTicketCancellationCompleteDelegate;

struct FPlayFabGroupMatchmakingCallbacks
{
	bool bJoining = false;
	bool bTicketResultDispatched = false;
	FOnPlayFabGroupTicketCreated TicketCreated;
	FOnPlayFabGroupTicketJoined TicketJoined;
	FOnPlayFabMatchmakingComplete Completion;
	FOnlineError Error = FOnlineError::Success();
};

class FMatchmakingInterfacePlayFab : public IOnlineMatchmakingPlayFab
{
PACKAGE_SCOPE:
	class FOnlineSubsystemPlayFab* OSSPlayFab = nullptr;
public:
	FMatchmakingInterfacePlayFab(FOnlineSubsystemPlayFab* InOSSPlayFab);
	virtual ~FMatchmakingInterfacePlayFab();
	void Shutdown();

	virtual bool CreateGroupMatchmakingTicket(
		const FUniqueNetIdRef& LocalUserId, FName ResultSessionName,
		const TArray<FUniqueNetIdRef>& ExpectedMembers, const FPlayFabGroupMatchmakingRequest& Request,
		FOnPlayFabGroupTicketCreated TicketCreatedCompletion, FOnPlayFabMatchmakingComplete MatchmakingCompletion) override;
	virtual bool JoinGroupMatchmakingTicket(
		const FUniqueNetIdRef& LocalUserId, FName ResultSessionName, const FString& TicketId,
		const FPlayFabGroupMatchmakingRequest& Request, FOnPlayFabGroupTicketJoined TicketJoinedCompletion,
		FOnPlayFabMatchmakingComplete MatchmakingCompletion) override;

	bool CreateMatchMakingTicket(const TArray< TSharedRef<const FUniqueNetId> >& LocalPlayers, 
		FName SessionName, 
		const FOnlineSessionSettings& NewSessionSettings, 
		TSharedRef<FOnlineSessionSearch>& SearchSettings);
	bool CancelMatchmakingTicket(const FName& SessionName, bool bNotifyFailure = true);

	void DoWork();

PACKAGE_SCOPE:
	DEFINE_ONLINE_DELEGATE_THREE_PARAM(OnMatchmakingTicketCompleted, bool, FName, TSharedPtr<FPlayFabSessionState>);
	DEFINE_ONLINE_DELEGATE_THREE_PARAM(OnPlayFabTicketCancellationComplete, FName, bool, TSharedPtr<FPlayFabSessionState>);

	/**
	 * Matchmaking related APIs
	 */
	bool AddMatchmakingTicket(FName SessionName, const FOnlineMatchmakingTicketInfoPtr& TicketInfo);
	bool RemoveMatchmakingTicket(FName SessionName, const FOnlineMatchmakingTicketInfoPtr& ExpectedTicket);
	bool GetMatchmakingTicket(const FName SessionName, FOnlineMatchmakingTicketInfoPtr& OutTicketInfo) const;
	bool GetMatchmakingTicketFromPlayFabTicket(const PFMatchmakingTicketHandle MatchTicket, FName& OutSessionName, FOnlineMatchmakingTicketInfoPtr& OutTicketInfo) const;
	void SetTicketState(const FName SessionName, const EOnlinePlayFabMatchmakingState::Type State);

	void OnJoinArrangedLobbyCompleted(FName SessionName, bool bSucceeded, FOnlineMatchmakingTicketInfoPtr ExpectedTicket);

private:
	// Per-instance SDK entry points allow deterministic lifecycle tests.
	decltype(&PFMatchmakingTicketCancel) CancelTicket = &PFMatchmakingTicketCancel;
	decltype(&PFMultiplayerDestroyMatchmakingTicket) DestroyTicket = &PFMultiplayerDestroyMatchmakingTicket;
	bool StartGroupMatchmaking(
		const FUniqueNetIdRef& LocalUserId, FName SessionName, const TArray<FUniqueNetIdRef>& ExpectedMembers,
		const FString& TicketId, const FPlayFabGroupMatchmakingRequest& Request,
		const TSharedRef<FPlayFabGroupMatchmakingCallbacks>& Callbacks);
	bool NotifyGroupTicketReady(const FOnlineMatchmakingTicketInfoPtr& Ticket);
	static FOnlineError MakeGroupMatchmakingError(EOnlineErrorResult Result, const FString& Code);
	static void CompleteGroupTicketRequest(
		FOnlineSubsystemPlayFab* Subsystem, const TSharedPtr<FPlayFabGroupMatchmakingCallbacks>& Callbacks,
		FName SessionName, const FString& TicketId, const FOnlineError& Error);
	static void CompleteGroupMatchmaking(
		FOnlineSubsystemPlayFab* Subsystem, const TSharedPtr<FPlayFabGroupMatchmakingCallbacks>& Callbacks,
		FName SessionName, bool bSucceeded, const FOnlineError& Error);
	void HandleMatchmakingTicketStatusChanged(const PFMatchmakingTicketStatusChangedStateChange& StateChange);
	void HandleMatchmakingTicketCompleted(const PFMatchmakingTicketCompletedStateChange& StateChange);
	void OnMatchmakingStatusChanged(FName SessionName, const FOnlineMatchmakingTicketInfoPtr& Ticket);
	void CompleteMatchmakingTicket(FName SessionName, const FOnlineMatchmakingTicketInfoPtr& Ticket, bool bSucceeded);
	void CompleteMatchmakingCancellation(FName SessionName, const FOnlineMatchmakingTicketInfoPtr& Ticket);
	void DestroyMatchmakingTicket(const FOnlineMatchmakingTicketInfoPtr& Ticket);

	typedef TMap<FName, FOnlineMatchmakingTicketInfoPtr> TicketInfoMap;
	mutable FCriticalSection TicketsLock;
	TicketInfoMap MatchmakingTickets;
	bool bShuttingDown = false;

	friend class FPlayFabMatchmakingTestAccessor;
	friend class FPlayFabGroupMatchmakingTestAccessor;
	friend class FOnlineSessionPlayFab;
};
