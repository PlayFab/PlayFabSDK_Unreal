//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#if defined(OSS_PLAYFAB_GDK_SUPPORT)
#include "OnlineExternalUIInterfacePlayFab.h"
#include "Interfaces/OnlineFriendsInterface.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "GDKTaskQueueHelpers.h"
#include "OnlineSessionInterfacePlayFab.h"
#include "OnlineSubsystemPlayFabTypes.h"

#include "Windows/AllowWindowsPlatformTypes.h"
THIRD_PARTY_INCLUDES_START
#include <XGameUI.h>
#include <xsapi-c/multiplayer_activity_c.h>
THIRD_PARTY_INCLUDES_END
#include "Windows/HideWindowsPlatformTypes.h"

namespace
{
	struct FSessionInvitePickerContext
	{
		TWeakPtr<FOnlineExternalUIPlayFab, ESPMode::ThreadSafe> ExternalUI;
		int32 LocalUserNum = 0;
		FName SessionName = NAME_None;
	};

	struct FSessionInviteErrorDialogContext
	{
		TWeakPtr<FOnlineExternalUIPlayFab, ESPMode::ThreadSafe> ExternalUI;
	};
}

#if defined(OSS_PLAYFAB_GDK)
bool FOnlineExternalUIPlayFab::ShowInviteUI(int32 InLocalUserNum, FName InSessionName)
{
	return ShowInviteUIGDK(InLocalUserNum, InSessionName);
}
#endif // OSS_PLAYFAB_GDK

bool FOnlineExternalUIPlayFab::ShowInviteUIGDK(int32 InLocalUserNum, FName InSessionName)
{
	UE_LOG_ONLINE_EXTERNALUI(Verbose, TEXT("FOnlineExternalUIPlayFab::ShowInviteUI()"));

	const IOnlineSessionPtr SessionInterface = OSSPlayFab ? OSSPlayFab->GetSessionInterface() : nullptr;
	if (!SessionInterface.IsValid())
	{
		UE_LOG_ONLINE_EXTERNALUI(Warning, TEXT("FOnlineExternalUIPlayFab::ShowInviteUI: Session interface is invalid"));
		return false;
	}

	const FNamedOnlineSession* NamedSession = SessionInterface->GetNamedSession(InSessionName);
	if (NamedSession == nullptr)
	{
		UE_LOG_ONLINE_EXTERNALUI(Warning, TEXT("FOnlineExternalUIPlayFab::ShowInviteUI: Session %s does not exist"), *InSessionName.ToString());
		return false;
	}

	// Presence sessions are published as the user's Xbox activity; other sessions need an explicit payload.
	const bool bInviteThroughMultiplayerActivity = NamedSession->SessionSettings.bUsesPresence;
	if (!bInviteThroughMultiplayerActivity)
	{
		IOnlineFriendsPtr FriendsInterface = OSSPlayFab ? OSSPlayFab->GetFriendsInterface() : nullptr;
		if (!FriendsInterface.IsValid())
		{
			UE_LOG_ONLINE_EXTERNALUI(Warning, TEXT("FOnlineExternalUIPlayFab::ShowInviteUI: Friends interface is invalid"));
			return false;
		}

		const FString ListName = EFriendsLists::ToString(EFriendsLists::Default);
		const TWeakPtr<FOnlineExternalUIPlayFab, ESPMode::ThreadSafe> WeakThis = AsShared();
		const FOnReadFriendsListComplete ReadComplete = FOnReadFriendsListComplete::CreateLambda(
			[WeakThis, InSessionName](int32 LocalUserNum, bool bWasSuccessful, const FString& CompletedListName, const FString& ErrorStr)
			{
				if (const TSharedPtr<FOnlineExternalUIPlayFab, ESPMode::ThreadSafe> This = WeakThis.Pin())
				{
					This->HandleReadFriendsForSessionInvite(LocalUserNum, bWasSuccessful, CompletedListName, ErrorStr, InSessionName);
				}
			});

		if (!FriendsInterface->ReadFriendsList(InLocalUserNum, ListName, ReadComplete))
		{
			UE_LOG_ONLINE_EXTERNALUI(Warning, TEXT("FOnlineExternalUIPlayFab::ShowInviteUI: Failed to start reading the friends list"));
			return false;
		}

		return true;
	}

	XAsyncBlock* pNewAsyncBlock = new XAsyncBlock();
	ZeroMemory(pNewAsyncBlock, sizeof(*pNewAsyncBlock));
	pNewAsyncBlock->context = this;
	pNewAsyncBlock->queue = FGDKAsyncTaskQueue::GetGenericQueue();

	pNewAsyncBlock->callback = [](XAsyncBlock* async)
	{
		bool bSuccess = false;

		TUniquePtr<XAsyncBlock> AsyncBlock(async);
		if (FOnlineExternalUIPlayFab* pThis = static_cast<FOnlineExternalUIPlayFab*>(AsyncBlock->context))
		{
			HRESULT Hr = XGameUiShowMultiplayerActivityGameInviteResult(async);
			if (SUCCEEDED(Hr))
			{
				bSuccess = true;
			}
			else
			{
				UE_LOG_ONLINE_EXTERNALUI(Warning, TEXT("FOnlineSessionPlayFab::HandleReadFriendsComplete: XAsyncGetStatus: result 0x%08x"), Hr);
			}
			
			pThis->HandleShowInviteUIComplete(bSuccess);
		}
	};

	FGDKUserHandle RequestedUser = IGDKRuntimeModule::Get().GetUserHandleByPlatformId(FPlatformMisc::GetPlatformUserForUserIndex(InLocalUserNum));
	HRESULT Hr = XGameUiShowMultiplayerActivityGameInviteAsync(pNewAsyncBlock, RequestedUser);
	if (FAILED(Hr))
	{
		UE_LOG_ONLINE_EXTERNALUI(Warning, TEXT("FOnlineExternalUIPlayFab::HandleReadFriendsComplete: Couldn't show system player picker UI for InLocalUserNum %d."), InLocalUserNum);
		delete pNewAsyncBlock;

		HandleShowInviteUIComplete(false);
		return false;
	}

	TriggerOnExternalUIChangeDelegates(true);
	return true;
}

void FOnlineExternalUIPlayFab::HandleReadFriendsForSessionInvite(int32 LocalUserNum, bool bWasSuccessful, const FString& ListName, const FString& ErrorStr, FName SessionName)
{
	if (!bWasSuccessful)
	{
		UE_LOG_ONLINE_EXTERNALUI(Warning, TEXT("FOnlineExternalUIPlayFab::ShowInviteUI: Failed to read friends list: %s"), *ErrorStr);
		HandleShowInviteUIComplete(false);
		return;
	}

	IOnlineFriendsPtr FriendsInterface = OSSPlayFab ? OSSPlayFab->GetFriendsInterface() : nullptr;
	if (!FriendsInterface.IsValid())
	{
		UE_LOG_ONLINE_EXTERNALUI(Warning, TEXT("FOnlineExternalUIPlayFab::ShowInviteUI: Friends interface became invalid"));
		HandleShowInviteUIComplete(false);
		return;
	}

	TArray<TSharedRef<FOnlineFriend>> Friends;
	if (!FriendsInterface->GetFriendsList(LocalUserNum, ListName, Friends))
	{
		UE_LOG_ONLINE_EXTERNALUI(Warning, TEXT("FOnlineExternalUIPlayFab::ShowInviteUI: Failed to get the cached friends list"));
		HandleShowInviteUIComplete(false);
		return;
	}

	if (!ShowSessionInvitePlayerPickerGDK(LocalUserNum, SessionName, Friends))
	{
		HandleShowInviteUIComplete(false);
	}
}

bool FOnlineExternalUIPlayFab::ShowSessionInvitePlayerPickerGDK(int32 LocalUserNum, FName SessionName, const TArray<TSharedRef<FOnlineFriend>>& Friends)
{
	TArray<uint64> CandidateXuids;
	CandidateXuids.Reserve(Friends.Num());
	for (const TSharedRef<FOnlineFriend>& Friend : Friends)
	{
		uint64 Xuid = 0;
		if (LexTryParseString(Xuid, *Friend->GetUserId()->ToString()) && Xuid != 0)
		{
			CandidateXuids.AddUnique(Xuid);
		}
	}

	if (CandidateXuids.IsEmpty())
	{
		UE_LOG_ONLINE_EXTERNALUI(Warning, TEXT("FOnlineExternalUIPlayFab::ShowInviteUI: No inviteable friends were found"));
		return ShowInviteErrorDialogGDK("No Xbox friends are available to invite. Add a friend and try again.");
	}

	FGDKUserHandle RequestedUser = IGDKRuntimeModule::Get().GetUserHandleByPlatformId(FPlatformMisc::GetPlatformUserForUserIndex(LocalUserNum));

	TUniquePtr<FSessionInvitePickerContext> PickerContext = MakeUnique<FSessionInvitePickerContext>();
	PickerContext->ExternalUI = AsShared();
	PickerContext->LocalUserNum = LocalUserNum;
	PickerContext->SessionName = SessionName;

	TUniquePtr<XAsyncBlock> AsyncBlock = MakeUnique<XAsyncBlock>();
	ZeroMemory(AsyncBlock.Get(), sizeof(XAsyncBlock));
	AsyncBlock->queue = FGDKAsyncTaskQueue::GetGenericQueue();
	AsyncBlock->context = PickerContext.Get();
	AsyncBlock->callback = [](XAsyncBlock* Async)
	{
		TUniquePtr<XAsyncBlock> OwnedAsyncBlock(Async);
		TUniquePtr<FSessionInvitePickerContext> Context(static_cast<FSessionInvitePickerContext*>(Async->context));
		const TSharedPtr<FOnlineExternalUIPlayFab, ESPMode::ThreadSafe> ExternalUI = Context->ExternalUI.Pin();
		if (!ExternalUI.IsValid())
		{
			return;
		}

		uint32 SelectedPlayerCount = 0;
		HRESULT Hr = XGameUiShowPlayerPickerResultCount(Async, &SelectedPlayerCount);
		if (FAILED(Hr))
		{
			UE_LOG_ONLINE_EXTERNALUI(Warning, TEXT("FOnlineExternalUIPlayFab::ShowInviteUI: Failed to get player picker result count: 0x%08x"), Hr);
			ExternalUI->HandleShowInviteUIComplete(false);
			return;
		}

		if (SelectedPlayerCount == 0)
		{
			ExternalUI->HandleShowInviteUIComplete(true);
			return;
		}

		TArray<uint64> SelectedXuids;
		SelectedXuids.SetNumUninitialized(SelectedPlayerCount);
		uint32 SelectedPlayersUsed = 0;
		Hr = XGameUiShowPlayerPickerResult(Async, SelectedPlayerCount, SelectedXuids.GetData(), &SelectedPlayersUsed);
		if (FAILED(Hr))
		{
			UE_LOG_ONLINE_EXTERNALUI(Warning, TEXT("FOnlineExternalUIPlayFab::ShowInviteUI: Failed to get player picker results: 0x%08x"), Hr);
			ExternalUI->HandleShowInviteUIComplete(false);
			return;
		}

		TArray<TSharedRef<const FUniqueNetId>> RemoteUserIds;
		RemoteUserIds.Reserve(SelectedPlayersUsed);
		for (uint32 Index = 0; Index < SelectedPlayersUsed; ++Index)
		{
			RemoteUserIds.Add(FUniqueNetIdPlayFab::Create(LexToString(SelectedXuids[Index])));
		}

		const IOnlineSessionPtr SessionInterface = ExternalUI->OSSPlayFab ? ExternalUI->OSSPlayFab->GetSessionInterface() : nullptr;
		const bool bInviteStarted = SessionInterface.IsValid()
			&& SessionInterface->SendSessionInviteToFriends(Context->LocalUserNum, Context->SessionName, RemoteUserIds);
		ExternalUI->HandleShowInviteUIComplete(bInviteStarted);
	};

	const uint32 MaxSelectionCount = FMath::Min<uint32>(CandidateXuids.Num(), c_PFInviteMaxPlayerCount);
	const HRESULT Hr = XGameUiShowPlayerPickerAsync(
		AsyncBlock.Get(),
		RequestedUser,
		"Invite players",
		CandidateXuids.Num(),
		CandidateXuids.GetData(),
		0,
		nullptr,
		1,
		MaxSelectionCount);
	if (FAILED(Hr))
	{
		UE_LOG_ONLINE_EXTERNALUI(Warning, TEXT("FOnlineExternalUIPlayFab::ShowInviteUI: Failed to show player picker: 0x%08x"), Hr);
		return false;
	}

	(void)PickerContext.Release();
	(void)AsyncBlock.Release();
	TriggerOnExternalUIChangeDelegates(true);
	return true;
}

bool FOnlineExternalUIPlayFab::ShowInviteErrorDialogGDK(const char* ContentText)
{
	TUniquePtr<FSessionInviteErrorDialogContext> DialogContext = MakeUnique<FSessionInviteErrorDialogContext>();
	DialogContext->ExternalUI = AsShared();

	TUniquePtr<XAsyncBlock> AsyncBlock = MakeUnique<XAsyncBlock>();
	ZeroMemory(AsyncBlock.Get(), sizeof(XAsyncBlock));
	AsyncBlock->queue = FGDKAsyncTaskQueue::GetGenericQueue();
	AsyncBlock->context = DialogContext.Get();
	AsyncBlock->callback = [](XAsyncBlock* Async)
	{
		TUniquePtr<XAsyncBlock> OwnedAsyncBlock(Async);
		TUniquePtr<FSessionInviteErrorDialogContext> Context(static_cast<FSessionInviteErrorDialogContext*>(Async->context));
		const TSharedPtr<FOnlineExternalUIPlayFab, ESPMode::ThreadSafe> ExternalUI = Context->ExternalUI.Pin();
		if (!ExternalUI.IsValid())
		{
			return;
		}

		XGameUiMessageDialogButton SelectedButton = XGameUiMessageDialogButton::First;
		const HRESULT Hr = XGameUiShowMessageDialogResult(Async, &SelectedButton);
		if (FAILED(Hr))
		{
			UE_LOG_ONLINE_EXTERNALUI(Warning, TEXT("FOnlineExternalUIPlayFab::ShowInviteUI: Failed to get invite error dialog result: 0x%08x"), Hr);
		}

		ExternalUI->HandleShowInviteUIComplete(false);
	};

	const HRESULT Hr = XGameUiShowMessageDialogAsync(
		AsyncBlock.Get(),
		"Unable to invite players",
		ContentText,
		"OK",
		nullptr,
		nullptr,
		XGameUiMessageDialogButton::First,
		XGameUiMessageDialogButton::First);
	if (FAILED(Hr))
	{
		UE_LOG_ONLINE_EXTERNALUI(Warning, TEXT("FOnlineExternalUIPlayFab::ShowInviteUI: Failed to show invite error dialog: 0x%08x"), Hr);
		return false;
	}

	(void)DialogContext.Release();
	(void)AsyncBlock.Release();
	TriggerOnExternalUIChangeDelegates(true);
	return true;
}
#endif // OSS_PLAYFAB_GDK_SUPPORT