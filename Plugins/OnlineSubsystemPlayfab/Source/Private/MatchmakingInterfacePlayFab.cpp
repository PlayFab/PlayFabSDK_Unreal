//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "MatchmakingInterfacePlayFab.h"
#include "OnlineSubsystemPlayFab.h"
#include "OnlineSessionInterfacePlayFab.h"
#include "OnlineIdentityInterfacePlayFab.h"
#include "PlayFabHelpers.h"
#include "PlayFabUtils.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

namespace
{
	template <typename DelegateType, typename ResultType>
	void DispatchGroupResult(FOnlineSubsystemPlayFab* Subsystem, DelegateType Completion, ResultType Result)
	{
		auto Dispatch = [Completion = MoveTemp(Completion), Result = MoveTemp(Result)]() mutable
		{
			Completion.ExecuteIfBound(Result);
		};
		if (Subsystem)
		{
			Subsystem->ExecuteNextTick(MoveTemp(Dispatch));
		}
		else
		{
			Dispatch();
		}
	}
}

FOnlineError FMatchmakingInterfacePlayFab::MakeGroupMatchmakingError(EOnlineErrorResult Result, const FString& Code)
{
	return FOnlineError::CreateError(TEXT("PlayFab.Matchmaking"), Result, Code);
}

void FMatchmakingInterfacePlayFab::CompleteGroupTicketRequest(
	FOnlineSubsystemPlayFab* Subsystem, const TSharedPtr<FPlayFabGroupMatchmakingCallbacks>& Callbacks,
	FName SessionName, const FString& TicketId, const FOnlineError& Error)
{
	if (!Callbacks.IsValid())
	{
		return;
	}
	if (!Error.WasSuccessful())
	{
		Callbacks->Error = Error;
	}
	if (Callbacks->bTicketResultDispatched)
	{
		return;
	}
	Callbacks->bTicketResultDispatched = true;
	if (Callbacks->bJoining)
	{
		FPlayFabGroupTicketJoinedResult Result;
		Result.ResultSessionName = SessionName;
		Result.bWasSuccessful = Error.WasSuccessful();
		Result.Error = Error;
		DispatchGroupResult(Subsystem, MoveTemp(Callbacks->TicketJoined), MoveTemp(Result));
	}
	else
	{
		FPlayFabGroupTicketCreatedResult Result;
		Result.ResultSessionName = SessionName;
		Result.bWasSuccessful = Error.WasSuccessful();
		Result.TicketId = Error.WasSuccessful() ? TicketId : FString();
		Result.Error = Error;
		DispatchGroupResult(Subsystem, MoveTemp(Callbacks->TicketCreated), MoveTemp(Result));
	}
}

void FMatchmakingInterfacePlayFab::CompleteGroupMatchmaking(
	FOnlineSubsystemPlayFab* Subsystem, const TSharedPtr<FPlayFabGroupMatchmakingCallbacks>& Callbacks,
	FName SessionName, bool bSucceeded, const FOnlineError& Error)
{
	FPlayFabMatchmakingCompleteResult Result;
	Result.ResultSessionName = SessionName;
	Result.bWasSuccessful = bSucceeded;
	Result.Error = Error;
	DispatchGroupResult(Subsystem, MoveTemp(Callbacks->Completion), MoveTemp(Result));
}

bool FMatchmakingInterfacePlayFab::CreateGroupMatchmakingTicket(
	const FUniqueNetIdRef& LocalUserId, FName ResultSessionName, const TArray<FUniqueNetIdRef>& ExpectedMembers,
	const FPlayFabGroupMatchmakingRequest& Request, FOnPlayFabGroupTicketCreated TicketCreatedCompletion,
	FOnPlayFabMatchmakingComplete MatchmakingCompletion)
{
	const TSharedRef<FPlayFabGroupMatchmakingCallbacks> Callbacks = MakeShared<FPlayFabGroupMatchmakingCallbacks>();
	Callbacks->TicketCreated = MoveTemp(TicketCreatedCompletion);
	Callbacks->Completion = MoveTemp(MatchmakingCompletion);
	return StartGroupMatchmaking(LocalUserId, ResultSessionName, ExpectedMembers, FString(), Request, Callbacks);
}

bool FMatchmakingInterfacePlayFab::JoinGroupMatchmakingTicket(
	const FUniqueNetIdRef& LocalUserId, FName ResultSessionName, const FString& TicketId,
	const FPlayFabGroupMatchmakingRequest& Request, FOnPlayFabGroupTicketJoined TicketJoinedCompletion,
	FOnPlayFabMatchmakingComplete MatchmakingCompletion)
{
	const TSharedRef<FPlayFabGroupMatchmakingCallbacks> Callbacks = MakeShared<FPlayFabGroupMatchmakingCallbacks>();
	Callbacks->bJoining = true;
	Callbacks->TicketJoined = MoveTemp(TicketJoinedCompletion);
	Callbacks->Completion = MoveTemp(MatchmakingCompletion);
	return StartGroupMatchmaking(LocalUserId, ResultSessionName, {}, TicketId, Request, Callbacks);
}

bool FMatchmakingInterfacePlayFab::StartGroupMatchmaking(
	const FUniqueNetIdRef& LocalUserId, FName SessionName, const TArray<FUniqueNetIdRef>& ExpectedMembers,
	const FString& TicketId, const FPlayFabGroupMatchmakingRequest& Request,
	const TSharedRef<FPlayFabGroupMatchmakingCallbacks>& Callbacks)
{
	check(IsInGameThread());
	auto Reject = [&](EOnlineErrorResult Result, const FString& Code)
	{
		UE_LOG_ONLINE(Error, TEXT("Group matchmaking request for '%s' rejected: %s"), *SessionName.ToString(), *Code);
		const FOnlineError Error = MakeGroupMatchmakingError(Result, Code);
		CompleteGroupTicketRequest(OSSPlayFab, Callbacks, SessionName, FString(), Error);
		CompleteGroupMatchmaking(OSSPlayFab, Callbacks, SessionName, false, Error);
		return false;
	};
	if (bShuttingDown || !OSSPlayFab)
	{
		return Reject(EOnlineErrorResult::MissingInterface, TEXT("SubsystemUnavailable"));
	}
	if (SessionName.IsNone() || !LocalUserId->IsValid() ||
		(Callbacks->bJoining ? TicketId.IsEmpty() : ExpectedMembers.IsEmpty()) ||
		Request.TimeoutInSeconds <= 0 || Request.TimeoutInSeconds > 3600 ||
		Request.SessionSettings.NumPublicConnections < static_cast<int32>(PFLobbyMaxMemberCountLowerLimit) ||
		Request.SessionSettings.NumPublicConnections > static_cast<int32>(PFLobbyMaxMemberCountUpperLimit) ||
		ExpectedMembers.Num() > Request.SessionSettings.NumPublicConnections)
	{
		return Reject(EOnlineErrorResult::InvalidParams, TEXT("InvalidRequest"));
	}
	const FString QueueName = Request.QueueName.IsEmpty() ? TEXT("Default") : Request.QueueName;
	if (QueueName.TrimStartAndEnd().IsEmpty())
	{
		return Reject(EOnlineErrorResult::InvalidParams, TEXT("InvalidQueue"));
	}
	const FString Attributes = Request.LocalUserAttributesJson.IsEmpty() ? TEXT("{}") : Request.LocalUserAttributesJson;
	TSharedPtr<FJsonObject> AttributesObject;
	if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Attributes), AttributesObject) || !AttributesObject.IsValid())
	{
		return Reject(EOnlineErrorResult::InvalidParams, TEXT("InvalidAttributesJson"));
	}
	TSet<FString> SeenMembers;
	for (const FUniqueNetIdRef& Member : ExpectedMembers)
	{
		const FString MemberId = Member->ToString().ToLower();
		if (!Member->IsValid() || SeenMembers.Contains(MemberId))
		{
			return Reject(EOnlineErrorResult::InvalidParams, TEXT("InvalidOrDuplicateMember"));
		}
		SeenMembers.Add(MemberId);
	}
	if (!Callbacks->bJoining && !SeenMembers.Contains(LocalUserId->ToString().ToLower()))
	{
		return Reject(EOnlineErrorResult::InvalidParams, TEXT("RequestingUserMissingFromRoster"));
	}

	const FOnlineIdentityPlayFabPtr Identity = OSSPlayFab->GetIdentityInterfacePlayFab();
	const FOnlineSessionPlayFabPtr Sessions = OSSPlayFab->GetSessionInterfacePlayFab();
	if (!Identity.IsValid() || !Sessions.IsValid() || !OSSPlayFab->GetMultiplayerHandle())
	{
		return Reject(EOnlineErrorResult::MissingInterface, TEXT("InterfacesNotReady"));
	}
	FOnlineMatchmakingTicketInfoPtr ExistingTicket;
	if (Sessions->GetSessionStatePtr(SessionName).IsValid() || GetMatchmakingTicket(SessionName, ExistingTicket))
	{
		return Reject(EOnlineErrorResult::AlreadyPending, TEXT("SessionOrTicketAlreadyExists"));
	}
	const TSharedPtr<FPlayFabUser> RequestingUser = Identity->GetPartyLocalUserFromPlatformId(*LocalUserId);
	if (!RequestingUser.IsValid() || !RequestingUser->GetEntityHandle().IsValid())
	{
		return Reject(EOnlineErrorResult::InvalidUser, TEXT("LocalUserNotAuthenticated"));
	}
	const PFEntityKey RequestingEntity = RequestingUser->GetEntityKey();
	if (!RequestingEntity.id || RequestingEntity.id[0] == '\0' || !RequestingEntity.type ||
		FCStringAnsi::Strcmp(RequestingEntity.type, ENTITY_TYPE_TITLE_PLAYER) != 0)
	{
		return Reject(EOnlineErrorResult::InvalidUser, TEXT("InvalidLocalEntity"));
	}

	TArray<PFEntityHandle> LocalEntities;
	TArray<FString> RemoteIds;
	TArray<FString> RemoteTypes;
	TSet<FString> SeenEntities;
	if (Callbacks->bJoining)
	{
		LocalEntities.Add(RequestingUser->GetEntityHandle().Get());
	}
	for (const FUniqueNetIdRef& Member : ExpectedMembers)
	{
		FString EntityId;
		FString EntityType;
		const TSharedPtr<FPlayFabUser> LocalMember = Identity->GetPartyLocalUserFromPlatformId(*Member);
		if (LocalMember.IsValid())
		{
			if (!LocalMember->GetEntityHandle().IsValid())
			{
				return Reject(EOnlineErrorResult::InvalidUser, TEXT("LocalMemberNotAuthenticated"));
			}
			const PFEntityKey Entity = LocalMember->GetEntityKey();
			if (!Entity.id || !Entity.type || FCStringAnsi::Strcmp(Entity.type, ENTITY_TYPE_TITLE_PLAYER) != 0)
			{
				return Reject(EOnlineErrorResult::InvalidUser, TEXT("InvalidLocalEntity"));
			}
			EntityId = UTF8_TO_TCHAR(Entity.id);
			EntityType = UTF8_TO_TCHAR(Entity.type);
			LocalEntities.Add(LocalMember->GetEntityHandle().Get());
		}
		else if (Sessions->GetPlayFabEntityKeyForPlatformUser(*Member, EntityId, EntityType))
		{
			RemoteIds.Add(EntityId);
			RemoteTypes.Add(EntityType);
		}
		else
		{
			return Reject(EOnlineErrorResult::InvalidUser, TEXT("RemoteMemberNotResolved"));
		}
		const FString EntityIdentity = (EntityType + TEXT(":") + EntityId).ToLower();
		if (EntityId.IsEmpty() || EntityType.IsEmpty() || SeenEntities.Contains(EntityIdentity))
		{
			return Reject(EOnlineErrorResult::InvalidUser, TEXT("InvalidOrDuplicateEntity"));
		}
		SeenEntities.Add(EntityIdentity);
	}
	FNamedOnlineSessionRef NamedSession = MakeShared<FNamedOnlineSession, ESPMode::ThreadSafe>(SessionName, Request.SessionSettings);
	NamedSession->HostingPlayerNum = INDEX_NONE;
	NamedSession->OwningUserId = FUniqueNetIdPlayFab::Create(*LocalUserId);
	NamedSession->LocalOwnerId = NamedSession->OwningUserId;
	const FPlayFabSessionStatePtr State = Sessions->TryAddSessionState(SessionName, NamedSession);
	if (!State.IsValid())
	{
		return Reject(EOnlineErrorResult::AlreadyPending, TEXT("SessionAlreadyExists"));
	}
	if (!State->MatchmakingCompletion.Begin())
	{
		Sessions->RemoveNamedSession(SessionName);
		return Reject(EOnlineErrorResult::AlreadyPending, TEXT("OperationAlreadyStarted"));
	}
	State->bUsesNativeSession = false;
	State->NetworkFlowType = ENetworkFlowType::Matchmaking;

	TArray<std::string> RemoteIdUtf8;
	TArray<std::string> RemoteTypeUtf8;
	RemoteIdUtf8.Reserve(RemoteIds.Num());
	RemoteTypeUtf8.Reserve(RemoteTypes.Num());
	for (int32 Index = 0; Index < RemoteIds.Num(); ++Index)
	{
		RemoteIdUtf8.Emplace(TCHAR_TO_UTF8(*RemoteIds[Index]));
		RemoteTypeUtf8.Emplace(TCHAR_TO_UTF8(*RemoteTypes[Index]));
	}
	TArray<PFEntityKey> RemoteEntities;
	for (int32 Index = 0; Index < RemoteIds.Num(); ++Index)
	{
		RemoteEntities.Add({RemoteIdUtf8[Index].c_str(), RemoteTypeUtf8[Index].c_str()});
	}
	UTF8StringList LocalAttributes;
	for (int32 Index = 0; Index < LocalEntities.Num(); ++Index)
	{
		LocalAttributes.Add(Attributes);
	}
	const std::string QueueUtf8 = TCHAR_TO_UTF8(*QueueName);
	const std::string TicketUtf8 = TCHAR_TO_UTF8(*TicketId);
	const PFMatchmakingTicketConfiguration Configuration{
		static_cast<uint32_t>(Request.TimeoutInSeconds), QueueUtf8.c_str(),
		static_cast<uint32_t>(RemoteEntities.Num()), RemoteEntities.GetData()};
	PFMatchmakingTicketHandle Handle = nullptr;
	const HRESULT Hr = Callbacks->bJoining
		? PFMultiplayerJoinMatchmakingTicketFromIdWithEntityHandles(OSSPlayFab->GetMultiplayerHandle(),
			LocalEntities.Num(), LocalEntities.GetData(), LocalAttributes.GetData(), TicketUtf8.c_str(), QueueUtf8.c_str(), nullptr, &Handle)
		: PFMultiplayerCreateMatchmakingTicketWithEntityHandles(OSSPlayFab->GetMultiplayerHandle(),
			LocalEntities.Num(), LocalEntities.GetData(), LocalAttributes.GetData(), &Configuration, nullptr, &Handle);
	const FOnlineMatchmakingTicketInfoPtr Ticket = MakeShared<FOnlineMatchmakingTicketInfo>();
	Ticket->PlayFabMatchTicket = Handle;
	Ticket->SessionState = State;
	Ticket->SessionName = SessionName;
	Ticket->SessionSettings = Request.SessionSettings;
	Ticket->QueueName = QueueName;
	Ticket->TicketId = TicketId;
	Ticket->GiveUpAfterTimeInSeconds = Request.TimeoutInSeconds;
	Ticket->SearchingPlayerNetId = FUniqueNetIdPlayFab::Create(*LocalUserId);
	Ticket->SetHostUser(RequestingUser);
	Ticket->MatchmakingState = EOnlinePlayFabMatchmakingState::CreatingTicket;
	if (FAILED(Hr) || !Handle || !AddMatchmakingTicket(SessionName, Ticket))
	{
		DestroyMatchmakingTicket(Ticket);
		State->MatchmakingCompletion.TryComplete();
		Sessions->RemoveNamedSession(SessionName);
		return Reject(FAILED(Hr) ? EOnlineErrorResult::RequestFailure : EOnlineErrorResult::InvalidResults,
			FString::Printf(TEXT("StartTicket.0x%08x"), Hr));
	}
	State->GroupMatchmaking = Callbacks;
	return true;
}

bool FMatchmakingInterfacePlayFab::NotifyGroupTicketReady(const FOnlineMatchmakingTicketInfoPtr& Ticket)
{
	const FPlayFabSessionStatePtr State = Ticket->SessionState.Pin();
	if (!State.IsValid() || !State->GroupMatchmaking.IsValid() || State->GroupMatchmaking->bTicketResultDispatched)
	{
		return true;
	}
	if (Ticket->TicketId.IsEmpty())
	{
		const char* Id = nullptr;
		const HRESULT Hr = PFMatchmakingTicketGetTicketId(Ticket->PlayFabMatchTicket, &Id);
		if (FAILED(Hr) || !Id || Id[0] == '\0')
		{
			UE_LOG_ONLINE(Error, TEXT("Group ticket became ready without a valid ticket ID: 0x%08x"), Hr);
			CompleteGroupTicketRequest(OSSPlayFab, State->GroupMatchmaking, Ticket->SessionName, FString(),
				MakeGroupMatchmakingError(EOnlineErrorResult::InvalidResults, TEXT("MissingTicketId")));
			return false;
		}
		Ticket->TicketId = UTF8_TO_TCHAR(Id);
	}
	if (Ticket->MatchmakingState == EOnlinePlayFabMatchmakingState::CreatingTicket)
	{
		Ticket->MatchmakingState = EOnlinePlayFabMatchmakingState::TicketCreated;
	}
	CompleteGroupTicketRequest(OSSPlayFab, State->GroupMatchmaking, Ticket->SessionName, Ticket->TicketId, FOnlineError::Success());
	return true;
}

FMatchmakingInterfacePlayFab::FMatchmakingInterfacePlayFab(FOnlineSubsystemPlayFab* InOSSPlayFab) :
	OSSPlayFab(InOSSPlayFab)
{
	UE_LOG_ONLINE(Verbose, TEXT("FMatchmakingInterfacePlayFab::FMatchmakingInterfacePlayFab: Constructor"));
}

FMatchmakingInterfacePlayFab::~FMatchmakingInterfacePlayFab()
{
	Shutdown();
}

void FMatchmakingInterfacePlayFab::Shutdown()
{
	if (bShuttingDown)
	{
		return;
	}
	bShuttingDown = true;

	TArray<FOnlineMatchmakingTicketInfoPtr> Tickets;
	{
		FScopeLock ScopeLock(&TicketsLock);
		MatchmakingTickets.GenerateValueArray(Tickets);
		MatchmakingTickets.Empty();
	}
	for (const FOnlineMatchmakingTicketInfoPtr& Ticket : Tickets)
	{
		DestroyMatchmakingTicket(Ticket);
	}
	OnMatchmakingTicketCompletedDelegates.Clear();
	OnPlayFabTicketCancellationCompleteDelegates.Clear();
	OSSPlayFab = nullptr;
}

bool FMatchmakingInterfacePlayFab::CreateMatchMakingTicket(const TArray< TSharedRef<const FUniqueNetId> >& LocalPlayers, FName SessionName, const FOnlineSessionSettings& NewSessionSettings, TSharedRef<FOnlineSessionSearch>& SearchSettings)
{
	UE_LOG_ONLINE(Verbose, TEXT("CreateMatchMakingTicket"));

	if (bShuttingDown || LocalPlayers.IsEmpty())
	{
		UE_LOG_ONLINE(Error, TEXT("CreateMatchMakingTicket rejected: shutdown or no local players."));
		return false;
	}

	IOnlineIdentityPtr IdentityIntPtr = OSSPlayFab->GetIdentityInterface();
	if (!IdentityIntPtr.IsValid())
	{
		UE_LOG_ONLINE(Error, TEXT("CreateMatchMakingTicket Identity Interface is invalid"));
		return false;
	}

	FOnlineMatchmakingTicketInfoPtr MatchmakingTicketPtr;
	if (GetMatchmakingTicket(SessionName, MatchmakingTicketPtr))
	{
		UE_LOG_ONLINE(Error, TEXT("CreateMatchMakingTicket MatchmakingTicket already exists, cancel the existing ticket and retry!"));
		return false;
	}

	FOnlineIdentityPlayFab* PlayFabIdentityInt = static_cast<FOnlineIdentityPlayFab*>(IdentityIntPtr.Get());
	TSharedPtr<FPlayFabUser> FirstUser = PlayFabIdentityInt->GetPartyLocalUserFromPlatformId(LocalPlayers[0].Get());
	if (FirstUser == nullptr)
	{
		UE_LOG_ONLINE(Error, TEXT("CreateMatchMakingTicket GetPartyLocalUserFromPlatformId returned empty user!"));
		return false;
	}

	TArray<PFEntityHandle> LocalEntityHandles;
	for (int32 i = 0; i < LocalPlayers.Num(); ++i)
	{
		TSharedPtr<FPlayFabUser> LocalUser = PlayFabIdentityInt->GetPartyLocalUserFromPlatformId(LocalPlayers[i].Get());
		if (LocalUser == nullptr)
		{
			UE_LOG_ONLINE(Error, TEXT("CreateMatchMakingTicket GetPartyLocalUserFromPlatformId returned empty user for %s!"), *LocalPlayers[i]->ToDebugString());
			return false;
		}

		FPFEntityHandle EntityHandle = LocalUser->GetEntityHandle();
		LocalEntityHandles.Add(EntityHandle.Get());
	}

	FString QueueName;
	if (!SearchSettings->QuerySettings.Get(SETTING_MATCH_QUEUENAME, QueueName)) 
	{
		QueueName = TEXT("Default");
	}

	std::string QueueNameStr = TCHAR_TO_UTF8(*QueueName);

	// If the timeout is negative we set the max timeout from the service side, which is 1 hour.
	const uint32_t ticketTimeoutInSeconds = (SearchSettings->TimeoutInSeconds < 0) ? 3600 : static_cast<uint32_t>(SearchSettings->TimeoutInSeconds);

	PFMatchmakingTicketConfiguration MatchConfig =
	{
		ticketTimeoutInSeconds,
		QueueNameStr.c_str(),
		0,
		nullptr
	};

	FString UserAttributes;
	if (!SearchSettings->QuerySettings.Get(SETTING_MATCH_ATTRIBUTES_KEY, UserAttributes))
	{
		// PlayFab OSS expects the UserAttributes to be part of SearchSettings, however the GDK OSS reads the value from FOnlineSessionSetting.
		// hence read the values from FOnlineSessionSetting if we don't see any attributes populated in SearchSettings
		const FOnlineSessionSetting* AttributesSetting = NewSessionSettings.Settings.Find(SETTING_MATCH_ATTRIBUTES_KEY);
		if (AttributesSetting)
		{
			AttributesSetting->Data.GetValue(UserAttributes);
		}
		else
		{
			UserAttributes = TEXT("");
		}
	}

	// Now convert the json to char** string to pass onto CreateMatchmakingTicket API
	UTF8StringList UserAttributesStr;
	for (auto Iterator : LocalEntityHandles)
	{
		UserAttributesStr.Add(UserAttributes);
	}

	PFMatchmakingTicketHandle MatchTicket;
	HRESULT Hr = PFMultiplayerCreateMatchmakingTicketWithEntityHandles(
		OSSPlayFab->GetMultiplayerHandle(),
		LocalEntityHandles.Num(),
		LocalEntityHandles.GetData(),
		UserAttributesStr.GetData(),
		&MatchConfig,
		nullptr,
		&MatchTicket);
	if (FAILED(Hr))
	{
		UE_LOG_ONLINE(Error, TEXT("FMatchmakingInterfacePlayFab::PFMultiplayerCreateMatchmakingTicket failed: Error code [0x%08x], Error message:%s"), Hr, *GetMultiplayerErrorMessage(Hr));
		return false;
	}

	MatchmakingTicketPtr = MakeShared<FOnlineMatchmakingTicketInfo>();

	MatchmakingTicketPtr->MatchmakingState = EOnlinePlayFabMatchmakingState::CreatingTicket;
	MatchmakingTicketPtr->SessionName = SessionName;
	MatchmakingTicketPtr->QueueName = QueueName;
	MatchmakingTicketPtr->SessionSearch = SearchSettings;
	MatchmakingTicketPtr->SessionSettings = NewSessionSettings;
	MatchmakingTicketPtr->PlayFabMatchTicket = MatchTicket;
	MatchmakingTicketPtr->SetHostUser(FirstUser);
	MatchmakingTicketPtr->SearchingPlayerNetId = FUniqueNetIdPlayFab::Create(LocalPlayers[0].Get());
	MatchmakingTicketPtr->SessionState = OSSPlayFab->GetSessionInterfacePlayFab()->GetSessionStatePtr(SessionName);

	if (!AddMatchmakingTicket(SessionName, MatchmakingTicketPtr))
	{
		UE_LOG_ONLINE(Error, TEXT("CreateMatchMakingTicket registration rejected for '%s': an existing ticket is registered or matchmaking is shutting down."), *SessionName.ToString());
		DestroyMatchmakingTicket(MatchmakingTicketPtr);
		return false;
	}

	return true;
}

bool FMatchmakingInterfacePlayFab::CancelMatchmakingTicket(const FName& SessionName, bool bNotifyFailure)
{
	if (bShuttingDown)
	{
		UE_LOG_ONLINE(Error, TEXT("CancelMatchmakingTicket rejected during shutdown."));
		return false;
	}

	FOnlineMatchmakingTicketInfoPtr MatchmakingTicketPtr;
	if (!GetMatchmakingTicket(SessionName, MatchmakingTicketPtr) || !MatchmakingTicketPtr.IsValid())
	{
		UE_LOG_ONLINE(Error, TEXT("FMatchmakingInterfacePlayFab::CancelMatchmakingTicket failed: Cannot find ticket for session: %s"), *SessionName.ToString());
		if (bNotifyFailure)
		{
			TriggerOnPlayFabTicketCancellationCompleteDelegates(SessionName, false, OSSPlayFab->GetSessionInterfacePlayFab()->GetSessionStatePtr(SessionName));
		}
		return false;
	}

	HRESULT Hr = CancelTicket(MatchmakingTicketPtr->PlayFabMatchTicket);
	if (FAILED(Hr))
	{
		UE_LOG_ONLINE(Error, TEXT("FMatchmakingInterfacePlayFab::PFMatchmakingTicketCancel failed. ErrorCode=[0x%08x]"), Hr);
		if (bNotifyFailure)
		{
			TriggerOnPlayFabTicketCancellationCompleteDelegates(SessionName, false, MatchmakingTicketPtr->SessionState.Pin());
		}
		return false;
	}

	return true;
}

void FMatchmakingInterfacePlayFab::DoWork()
{
	if (bShuttingDown)
	{
		return;
	}

	uint32 StateChangeCount = 0u;
	const PFMatchmakingStateChange* const* StateChanges = nullptr;

	HRESULT Hr = PFMultiplayerStartProcessingMatchmakingStateChanges(OSSPlayFab->GetMultiplayerHandle(), &StateChangeCount, &StateChanges);
	if (FAILED(Hr))
	{
		UE_LOG_ONLINE(Error, TEXT("FMatchmakingInterfacePlayFab::DoWork::StartProcessingStateChanges failed. ErrorCode=[0x%08x], Error message %s"), Hr, *GetMultiplayerErrorMessage(Hr));
		return;
	}

	for (uint32 i = 0; i < StateChangeCount; ++i)
	{
		const PFMatchmakingStateChange& StateChange = *StateChanges[i];

		switch (StateChange.stateChangeType)
		{
			case PFMatchmakingStateChangeType::TicketStatusChanged:
			{
				HandleMatchmakingTicketStatusChanged(static_cast<const PFMatchmakingTicketStatusChangedStateChange&>(StateChange));
				break;
			}
			case PFMatchmakingStateChangeType::TicketCompleted:
			{
				HandleMatchmakingTicketCompleted(static_cast<const PFMatchmakingTicketCompletedStateChange&>(StateChange));
				break;
			}
			default:
			{
				UE_LOG_ONLINE(Verbose, TEXT("Received PlayFab Unhandled(%u) event in FMatchmakingInterfacePlayFab"), StateChange.stateChangeType);
				break;
			}
		}
	}
	Hr = PFMultiplayerFinishProcessingMatchmakingStateChanges(OSSPlayFab->GetMultiplayerHandle(), StateChangeCount, StateChanges);
	if (FAILED(Hr))
	{
		UE_LOG_ONLINE(Error, TEXT("FMatchmakingInterfacePlayFab::DoWork::PFMultiplayerFinishProcessingMatchmakingStateChanges failed. ErrorCode=[0x%08x], Error message:%s"), Hr, *GetMultiplayerErrorMessage(Hr));
	}
}

void FMatchmakingInterfacePlayFab::HandleMatchmakingTicketStatusChanged(const PFMatchmakingTicketStatusChangedStateChange& StateChange)
{
	FName SessionName;
	FOnlineMatchmakingTicketInfoPtr Ticket;
	if (!GetMatchmakingTicketFromPlayFabTicket(StateChange.ticket, SessionName, Ticket))
	{
		UE_LOG_ONLINE(Verbose, TEXT("Ignoring status change for an inactive matchmaking ticket."));
		return;
	}

	PFMatchmakingTicketStatus Status{};
	HRESULT Hr = PFMatchmakingTicketGetStatus(StateChange.ticket, &Status);
	UE_LOG_ONLINE(Verbose, TEXT("FMatchmakingInterfacePlayFab::HandleMatchmakingTicketStatusChanged(%u) event: for ticket (%p), Status: (%u). ErrorCode=[0x%08x], Error message:%s"), StateChange.stateChangeType, StateChange.ticket, Status, Hr, *GetMultiplayerErrorMessage(Hr));

	if (FAILED(Hr))
	{
		UE_LOG_ONLINE(Error, TEXT("Could not read matchmaking ticket status: 0x%08x"), Hr);
		Ticket->MatchmakingState = EOnlinePlayFabMatchmakingState::Failed;
	}
	else if ((Status == PFMatchmakingTicketStatus::WaitingForPlayers ||
		Status == PFMatchmakingTicketStatus::WaitingForMatch || Status == PFMatchmakingTicketStatus::Matched) &&
		!NotifyGroupTicketReady(Ticket))
	{
		Ticket->MatchmakingState = EOnlinePlayFabMatchmakingState::Failed;
	}
	OnMatchmakingStatusChanged(SessionName, Ticket);
}

void FMatchmakingInterfacePlayFab::HandleMatchmakingTicketCompleted(const PFMatchmakingTicketCompletedStateChange& StateChange)
{
	FOnlineMatchmakingTicketInfoPtr Ticket;
	FName SessionName;
	PFMatchmakingTicketHandle PlayFabMatchTicket = StateChange.ticket;

	if (!GetMatchmakingTicketFromPlayFabTicket(PlayFabMatchTicket, SessionName, Ticket))
	{
		UE_LOG_ONLINE(Verbose, TEXT("Ignoring completion for an inactive matchmaking ticket."));
		return;
	}

	if (Ticket->MatchmakingState == EOnlinePlayFabMatchmakingState::JoiningArrangedLobby ||
		Ticket->MatchmakingState == EOnlinePlayFabMatchmakingState::JoinArrangedLobbyCompleted)
	{
		UE_LOG_ONLINE(Verbose, TEXT("Ignoring duplicate matchmaking ticket completion."));
		return;
	}

	PFMatchmakingTicketStatus Status{};
	HRESULT Hr = PFMatchmakingTicketGetStatus(StateChange.ticket, &Status);
	UE_LOG_ONLINE(Verbose, TEXT("Matchmaking ticket completion status %u, result 0x%08x"), Status, Hr);

	if (FAILED(Hr))
	{
		UE_LOG_ONLINE(Error, TEXT("Could not read matchmaking ticket status: 0x%08x"), Hr);
		Ticket->MatchmakingState = EOnlinePlayFabMatchmakingState::Failed;
	}
	else if (SUCCEEDED(StateChange.result))
	{
		if (Status == PFMatchmakingTicketStatus::Matched)
		{
			const PFMatchmakingMatchDetails* MatchDetails = nullptr;
			Hr = PFMatchmakingTicketGetMatch(PlayFabMatchTicket, &MatchDetails);
			if (FAILED(Hr) || !MatchDetails)
			{
				UE_LOG_ONLINE(Error, TEXT("FMatchmakingInterfacePlayFab::HandleMatchmakingTicketCompleted PFMatchmakingTicketGetMatch failed. ErrorCode=[0x%08x], Error message %s"), Hr, *GetMultiplayerErrorMessage(Hr));
				Ticket->MatchmakingState = EOnlinePlayFabMatchmakingState::Failed;
			}
			else
			{
				Ticket->PlayFabMatchmakingDetails = MatchDetails;
				Ticket->MatchmakingState = NotifyGroupTicketReady(Ticket)
					? EOnlinePlayFabMatchmakingState::MatchFound : EOnlinePlayFabMatchmakingState::Failed;
				const FPlayFabSessionStatePtr State = Ticket->SessionState.Pin();
				if (State.IsValid() && State->GroupMatchmaking.IsValid() &&
					MatchDetails->memberCount > static_cast<uint32_t>(Ticket->SessionSettings.NumPublicConnections))
				{
					UE_LOG_ONLINE(Error, TEXT("Group match exceeds the requested session capacity."));
					State->GroupMatchmaking->Error = MakeGroupMatchmakingError(EOnlineErrorResult::InvalidResults, TEXT("MatchExceedsSessionCapacity"));
					Ticket->MatchmakingState = EOnlinePlayFabMatchmakingState::Failed;
				}
			}
		}
		else if (Status == PFMatchmakingTicketStatus::Canceled)
		{
			UE_LOG_ONLINE(Verbose, TEXT("MatchmakingTicketResult::Canceled, Error code:[0x%08x],Error message %s"), StateChange.result, *GetMultiplayerErrorMessage(StateChange.result));
			Ticket->MatchmakingState = EOnlinePlayFabMatchmakingState::Cancelled;
		}
		else
		{
			UE_LOG_ONLINE(Error, TEXT("MatchmakingTicketResult::Failed, Error code:[0x%08x],Error message %s"), StateChange.result, *GetMultiplayerErrorMessage(StateChange.result));
			Ticket->MatchmakingState = EOnlinePlayFabMatchmakingState::Failed;
		}
	}
	else
	{
		if (Status == PFMatchmakingTicketStatus::Canceled)
		{
			UE_LOG_ONLINE(Verbose, TEXT("MatchmakingTicketResult::Canceled, Error code:[0x%08x],Error message %s"), StateChange.result, *GetMultiplayerErrorMessage(StateChange.result));
			Ticket->MatchmakingState = EOnlinePlayFabMatchmakingState::Cancelled;
		}
		else
		{
			UE_LOG_ONLINE(Error, TEXT("PFMatchmakingTicketCompletedStateChange Failed, Error code:[0x%08x],Error message %s"), StateChange.result, *GetMultiplayerErrorMessage(StateChange.result));
			Ticket->MatchmakingState = EOnlinePlayFabMatchmakingState::Failed;
		}
	}

	OnMatchmakingStatusChanged(SessionName, Ticket);
}

void FMatchmakingInterfacePlayFab::OnMatchmakingStatusChanged(FName SessionName, const FOnlineMatchmakingTicketInfoPtr& Ticket)
{
	if (!Ticket.IsValid() || Ticket->bTerminalCallbackDispatched)
	{
		return;
	}

	switch (Ticket->MatchmakingState)
	{
		case EOnlinePlayFabMatchmakingState::TicketCreated:
		{
			break;
		}
		case EOnlinePlayFabMatchmakingState::MatchFound:
		{
			auto SessionInterface = OSSPlayFab->GetSessionInterfacePlayFab();
			FNamedOnlineSessionPtr ExistingNamedSession = SessionInterface->GetNamedSessionPtr(SessionName);
			if (!ExistingNamedSession.IsValid())
			{
				UE_LOG_ONLINE_SESSION(Log, TEXT("MatchFound but NamedSession for '%s' is missing; aborting."), *SessionName.ToString());
				CompleteMatchmakingTicket(SessionName, Ticket, false);
				return;
			}

			Ticket->MatchmakingState = EOnlinePlayFabMatchmakingState::JoiningArrangedLobby;
			Ticket->OnJoinArrangedLobbyCompleteDelegateHandle =
				OSSPlayFab->GetPlayFabLobbyInterface()->AddOnJoinArrangedLobbyCompletedDelegate_Handle(
					FOnJoinArrangedLobbyCompletedDelegate::CreateRaw(this, &FMatchmakingInterfacePlayFab::OnJoinArrangedLobbyCompleted, Ticket));

			if (!OSSPlayFab->GetPlayFabLobbyInterface()->JoinArrangedLobby(SessionName, Ticket))
			{
				UE_LOG_ONLINE_SESSION(Log, TEXT("Failed JoinArrangedLobby operation"));
				CompleteMatchmakingTicket(SessionName, Ticket, false);
				return;
			}
			break;
		}
		case EOnlinePlayFabMatchmakingState::Cancelled:
		{
			UE_LOG_ONLINE(Verbose, TEXT("FMatchmakingInterfacePlayFab::OnMatchmakingStatusChanged Cancelled"));
			CompleteMatchmakingCancellation(SessionName, Ticket);
			return;
		}
		case EOnlinePlayFabMatchmakingState::Failed:
		{
			UE_LOG_ONLINE(Verbose, TEXT("FMatchmakingInterfacePlayFab::OnMatchmakingStatusChanged Failed"));
			CompleteMatchmakingTicket(SessionName, Ticket, false);
			return;
		}
		case EOnlinePlayFabMatchmakingState::JoiningArrangedLobby:
		{
			break;
		}
		case EOnlinePlayFabMatchmakingState::JoinArrangedLobbyCompleted:
		{
			return;
		}
	}
}

void FMatchmakingInterfacePlayFab::OnJoinArrangedLobbyCompleted(FName SessionName, bool bSucceeded, FOnlineMatchmakingTicketInfoPtr ExpectedTicket)
{
	FOnlineMatchmakingTicketInfoPtr Ticket;
	if (!GetMatchmakingTicket(SessionName, Ticket) || Ticket != ExpectedTicket)
	{
		UE_LOG_ONLINE(Verbose, TEXT("Ignoring arranged-lobby completion for an inactive or replaced ticket."));
		return;
	}
	Ticket->MatchmakingState = EOnlinePlayFabMatchmakingState::JoinArrangedLobbyCompleted;
	CompleteMatchmakingTicket(SessionName, Ticket, bSucceeded);
}

bool FMatchmakingInterfacePlayFab::AddMatchmakingTicket(FName SessionName, const FOnlineMatchmakingTicketInfoPtr& InTicketInfo)
{
	FScopeLock ScopeLock(&TicketsLock);
	if (bShuttingDown || !InTicketInfo.IsValid() || MatchmakingTickets.Contains(SessionName))
	{
		return false;
	}
	MatchmakingTickets.Add(SessionName, InTicketInfo);
	return true;
}

bool FMatchmakingInterfacePlayFab::RemoveMatchmakingTicket(FName SessionName, const FOnlineMatchmakingTicketInfoPtr& ExpectedTicket)
{
	FOnlineMatchmakingTicketInfoPtr Ticket;
	{
		FScopeLock ScopeLock(&TicketsLock);
		const FOnlineMatchmakingTicketInfoPtr* Found = MatchmakingTickets.Find(SessionName);
		if (!Found || !ExpectedTicket.IsValid() || *Found != ExpectedTicket)
		{
			return false;
		}
		Ticket = *Found;
		MatchmakingTickets.Remove(SessionName);
	}
	DestroyMatchmakingTicket(Ticket);
	return true;
}

void FMatchmakingInterfacePlayFab::CompleteMatchmakingTicket(FName SessionName, const FOnlineMatchmakingTicketInfoPtr& Ticket, bool bSucceeded)
{
	if (!Ticket.IsValid() || Ticket->bTerminalCallbackDispatched || !RemoveMatchmakingTicket(SessionName, Ticket))
	{
		return;
	}
	Ticket->bTerminalCallbackDispatched = true;
	const FPlayFabSessionStatePtr State = Ticket->SessionState.Pin();
	if (State.IsValid() && State->GroupMatchmaking.IsValid() && !bSucceeded)
	{
		const FOnlineError Error = State->GroupMatchmaking->Error.WasSuccessful()
			? MakeGroupMatchmakingError(EOnlineErrorResult::RequestFailure, TEXT("MatchmakingFailed"))
			: State->GroupMatchmaking->Error;
		CompleteGroupTicketRequest(OSSPlayFab, State->GroupMatchmaking, SessionName, FString(), Error);
	}
	TriggerOnMatchmakingTicketCompletedDelegates(bSucceeded, SessionName, Ticket->SessionState.Pin());
}

void FMatchmakingInterfacePlayFab::CompleteMatchmakingCancellation(FName SessionName, const FOnlineMatchmakingTicketInfoPtr& Ticket)
{
	if (!Ticket.IsValid() || Ticket->bTerminalCallbackDispatched || !RemoveMatchmakingTicket(SessionName, Ticket))
	{
		return;
	}
	Ticket->bTerminalCallbackDispatched = true;
	const FPlayFabSessionStatePtr State = Ticket->SessionState.Pin();
	if (State.IsValid())
	{
		CompleteGroupTicketRequest(OSSPlayFab, State->GroupMatchmaking, SessionName, FString(),
			MakeGroupMatchmakingError(EOnlineErrorResult::Canceled, TEXT("Canceled")));
	}
	TriggerOnPlayFabTicketCancellationCompleteDelegates(SessionName, true, Ticket->SessionState.Pin());
}

void FMatchmakingInterfacePlayFab::DestroyMatchmakingTicket(const FOnlineMatchmakingTicketInfoPtr& Ticket)
{
	if (Ticket->OnJoinArrangedLobbyCompleteDelegateHandle.IsValid())
	{
		OSSPlayFab->GetPlayFabLobbyInterface()->ClearOnJoinArrangedLobbyCompletedDelegate_Handle(Ticket->OnJoinArrangedLobbyCompleteDelegateHandle);
		Ticket->OnJoinArrangedLobbyCompleteDelegateHandle.Reset();
	}
	if (Ticket->PlayFabMatchTicket)
	{
		HRESULT Hr = DestroyTicket(OSSPlayFab->GetMultiplayerHandle(), Ticket->PlayFabMatchTicket);
		if (FAILED(Hr))
		{
			UE_LOG_ONLINE(Error, TEXT("PFMultiplayerDestroyMatchmakingTicket failed: 0x%08x"), Hr);
		}
		Ticket->PlayFabMatchTicket = nullptr;
		Ticket->PlayFabMatchmakingDetails = nullptr;
	}
}

bool FMatchmakingInterfacePlayFab::GetMatchmakingTicket(const FName SessionName, FOnlineMatchmakingTicketInfoPtr& OutTicketInfo) const
{
	FScopeLock ScopeLock(&TicketsLock);

	const FOnlineMatchmakingTicketInfoPtr* FoundTicket = MatchmakingTickets.Find(SessionName);

	if (FoundTicket)
	{
		OutTicketInfo = *FoundTicket;
	}

	return (FoundTicket != nullptr);
}

bool FMatchmakingInterfacePlayFab::GetMatchmakingTicketFromPlayFabTicket(const PFMatchmakingTicketHandle MatchTicket, FName& OutSessionName, FOnlineMatchmakingTicketInfoPtr& OutTicketInfo) const
{
	FScopeLock ScopeLock(&TicketsLock);
	for (auto Iterator : MatchmakingTickets)
	{
		FName SessionName = Iterator.Key;
		FOnlineMatchmakingTicketInfoPtr Ticket = Iterator.Value;
		if (!Ticket.IsValid())
		{
			continue;
		}
		if (Ticket->PlayFabMatchTicket == MatchTicket)
		{
			OutSessionName = SessionName;
			OutTicketInfo = Ticket;
			return true;
		}
	}

	return false;
}

void FMatchmakingInterfacePlayFab::SetTicketState(const FName SessionName, const EOnlinePlayFabMatchmakingState::Type State)
{
	FOnlineMatchmakingTicketInfoPtr MatchmakingTicketPtr;
	GetMatchmakingTicket(SessionName, MatchmakingTicketPtr);

	if (MatchmakingTicketPtr.IsValid())
	{
		MatchmakingTicketPtr->MatchmakingState = State;
	}
}
