//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

#include "Interfaces/OnlineIdentityInterface.h"
#include "OnlineSubsystemPlayFabPackage.h"
#include "OnlineSubsystemPlayFabDefines.h"
#include "OnlineSubsystemPlayFabTypes.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Misc/DateTime.h"
#include "Dom/JsonObject.h"

#include "PFCore.h"
#include "PFCoreUnrealTypes.h"

#include <vector>
#include <string>

using namespace Party;

/**
 * Delegate used on the completion of FOnlineIdentityPlayFab::AuthenticateUser().
 *
 * @param LocalUserNum the controller number of the associated user that made the request
 * @param bWasSuccessful true if authentication was successful, false if there was an error
 * @param PlatformUserIdStr user identifier returned from the service.
 * @param ErrorStr string representing the error condition
 */
DECLARE_MULTICAST_DELEGATE_FourParams(FOnAuthenticateUserComplete, int32 /*LocalUserNum*/, bool /*bWasSuccessful*/, const FString& /*PlatformUserIdStr*/, const FString& /*ErrorStr*/);
typedef FOnAuthenticateUserComplete::FDelegate FOnAuthenticateUserCompleteDelegate;

struct UserAuthRequestData
{
	FHttpRequestPtr m_HTTPRequest;
};

class ONLINESUBSYSTEMPLAYFAB_API FPlayFabUser
{
public:
	FPlayFabUser
	(
		const FString& PlatformUserIdStrIn,
		const FPFEntityHandle EntityHandleIn,
		TSharedPtr<const FPFEntityKey> EntityKeyIn,
		PartyLocalUser* LocalUserIn
	) :
		PlatformUserIdStr(PlatformUserIdStrIn),
		LocalUser(LocalUserIn),
		EntityIdStr(TCHAR_TO_UTF8(*EntityKeyIn.Get()->id)),
		EntityTypeStr(TCHAR_TO_UTF8(*EntityKeyIn.Get()->type)),
		EntityHandle(EntityHandleIn)
	{
	}

	const FString& GetPlatformUserId() const { return PlatformUserIdStr; }
	const FString& GetEntityToken() const { return EntityToken; }
	const FString& GetEntityId() const { return EntityId; }
	const FString& GetEntityType() const { return EntityType; }
	const FString& GetSessionTicket() const { return SessionTicket; }
	const FString& GetPlayFabId() const { return PlayFabId; }
	const FDateTime& GetEntityTokenUpdateTime() const { return EntityTokenUpdateTime; }
	PartyLocalUser* GetPartyLocalUser() const { return LocalUser; }
	PFEntityKey GetEntityKey() const { return PFEntityKey{ EntityIdStr.c_str(), EntityTypeStr.c_str() }; }

	/**
	 * Returns the user's current PlayFab entity handle.
	 * Important: Entity handles may be refreshed during re-authentication (e.g., Steam
	 * AutoLogin triggering a second auth). Do not cache this value — always call
	 * GetEntityHandle() when you need it. Subscribe to OnLoginStatusChanged if you
	 * need to be notified when re-authentication occurs.
	 */
	FPFEntityHandle GetEntityHandle() const{ return EntityHandle; }

	void SetEntityHandle(const FPFEntityHandle& NewHandle) { EntityHandle = NewHandle; }

	void UpdateEntityToken(const FString& NewEntityToken);

	void SetNewEntityTokenUpdateTime();

private:
	FString PlatformUserIdStr;
	FString EntityToken;
	FString EntityId;
	FString EntityType;
	FString SessionTicket;
	PartyLocalUser* LocalUser = nullptr;
	std::string EntityIdStr;
	std::string EntityTypeStr;
	FString PlayFabId;
	FDateTime EntityTokenUpdateTime;
	FPFEntityHandle EntityHandle;
};

class ONLINESUBSYSTEMPLAYFAB_API FOnlineIdentityPlayFab:
	public IOnlineIdentity,
	public TSharedFromThis<FOnlineIdentityPlayFab, ESPMode::ThreadSafe>
{
PACKAGE_SCOPE:

	/** Constructor
	 *
	 * @param InSubsystem The owner of this identity interface.
	 */
	explicit FOnlineIdentityPlayFab(class FOnlineSubsystemPlayFab* InSubsystem);

	/** Reference to the owning subsystem */
	class FOnlineSubsystemPlayFab* OSSPlayFab = nullptr;

public:

	virtual ~FOnlineIdentityPlayFab();

	/**
	 * Delegate used on the completion of FOnlineIdentityPlayFab::AuthenticateUser().
	 *
	 * @param LocalUserNum the controller number of the associated user that made the request
	 * @param bWasSuccessful true if authentication was successful, false if there was an error
	 * @param PlatformUserIdStr user identifier returned from the service.
	 * @param ErrorStr string representing the error condition
	 */
	DEFINE_ONLINE_PLAYER_DELEGATE_THREE_PARAM(MAX_LOCAL_PLAYERS, OnAuthenticateUserComplete, bool /*bWasSuccessful*/, const FString& /*PlatformUserIdStr*/, const FString& /*ErrorStr*/);

	// IOnlineIdentity
	virtual bool Login(int32 LocalUserNum, const FOnlineAccountCredentials& AccountCredentials) override;
	virtual bool Logout(int32 LocalUserNum) override;
	virtual bool AutoLogin(int32 LocalUserNum) override;
	virtual TSharedPtr<FUserOnlineAccount> GetUserAccount(const FUniqueNetId& UserId) const override;
	virtual TArray<TSharedPtr<FUserOnlineAccount> > GetAllUserAccounts() const override;
	virtual TSharedPtr<const FUniqueNetId> GetUniquePlayerId(int32 LocalUserNum) const override;
	virtual TSharedPtr<const FUniqueNetId> GetSponsorUniquePlayerId(int32 LocalUserNum) const override;
	virtual TSharedPtr<const FUniqueNetId> CreateUniquePlayerId(uint8* Bytes, int32 Size) override;
	virtual TSharedPtr<const FUniqueNetId> CreateUniquePlayerId(const FString& Str) override;
	virtual ELoginStatus::Type GetLoginStatus(int32 LocalUserNum) const override;
	virtual ELoginStatus::Type GetLoginStatus(const FUniqueNetId& UserId) const override;
	virtual FString GetPlayerNickname(int32 LocalUserNum) const override;
	virtual FString GetPlayerNickname(const FUniqueNetId& UserId) const override;
	virtual FString GetAuthToken(int32 LocalUserNum) const override;
	virtual void RevokeAuthToken(const FUniqueNetId& UserId, const FOnRevokeAuthTokenCompleteDelegate& Delegate) override;
	virtual void GetUserPrivilege(const FUniqueNetId& UserId, EUserPrivileges::Type Privilege, const FOnGetUserPrivilegeCompleteDelegate& Delegate, EShowPrivilegeResolveUI ShowResolveUI) override;
	virtual FPlatformUserId GetPlatformUserIdFromUniqueNetId(const FUniqueNetId& UniqueNetId) const override;
	virtual FString GetAuthType() const override;

	UserAuthRequestData* GetUserAuthRequestData(const FString& PlatformUserIdStr)
	{
		if (UserAuthRequestsInFlight.Contains(PlatformUserIdStr))
		{
			return &UserAuthRequestsInFlight[PlatformUserIdStr];
		}

		return nullptr;
	}

	const FString GetUserPlatformIdStrFromRequest(FHttpRequestPtr HttpRequest)
	{
		for (auto& Elem : UserAuthRequestsInFlight)
		{
			const UserAuthRequestData& ReqData = Elem.Value;
			if (ReqData.m_HTTPRequest.Get() == HttpRequest.Get())
			{
				return Elem.Key;
			}
		}

		return FString();
	}

	UserAuthRequestData* GetUserAuthRequestDataFromRequest(FHttpRequestPtr HttpRequest)
	{
		for (auto& Elem : UserAuthRequestsInFlight)
		{
			const UserAuthRequestData& ReqData = Elem.Value;
			if (ReqData.m_HTTPRequest.Get() == HttpRequest.Get())
			{
				return &Elem.Value;
			}
		}

		return nullptr;
	}

	void Tick(float DeltaTime);
	void OnAppSuspend();
	void OnAppResume();
	void TryAuthenticateUsers();
	void CleanUpLocalUsers();

	PartyLocalUser* GetFirstPartyLocalUser();

	TSharedPtr<FPlayFabUser> GetPartyLocalUserFromPlatformId(const FUniqueNetId& PlatformNetId);
	TSharedPtr<FPlayFabUser> GetPartyLocalUserFromPlatformIdString(const FString& PlatformNetIdStr, int32* Index = nullptr);
	TSharedPtr<FPlayFabUser> GetPartyLocalUserFromEntityIdString(const FString& EntityIdString);

	const TArray<TSharedPtr<FPlayFabUser>>& GetAllPartyLocalUsers() const
	{
		return LocalPlayFabUsers;
	}

	/** Returns the server entity if this is a dedicated server and auth has completed, nullptr otherwise. */
	TSharedPtr<FPlayFabUser> GetServerEntity() const
	{
		return ServerEntity;
	}

	bool IsUserLocal(const PFEntityKey& UserEntityKey);
	const TArray<PFEntityKey> GetLocalUserEntityKeys() const;
	PFEntityHandle GetLocalUserEntityHandleFromEntityKey(const PFEntityKey* EntityKey);
	TSharedPtr<FPlayFabUser> GetPartyLocalUserFromEntityHandle(const PFEntityHandle EntityHandle);

	/**
	 * Asynchronously acquires the local user's Xbox Live token (XToken). The token is fetched fresh
	 * per call (rather than cached at user creation) so it is never stale/expired and the caller
	 * cannot observe an unset token. OnComplete is always invoked on the game thread with
	 * (bSuccess, XToken). On non-GDK platforms there is no XToken, so OnComplete is invoked with
	 * (false, empty). The token is currently consumed by friend lobby search to resolve the user's
	 * Xbox friends list, but is not specific to that use.
	 */
	void GetLocalUserXTokenAsync(const FString& PlatformUserIdStr, TFunction<void(bool, FString)> OnComplete);

protected:
	bool AuthenticateUser(const FString& UserPlatformIdStr);
    void Auth_PFAuthRequestComplete(bool bSucceeded, const FString& UserPlatformIdStr, FPFEntityHandle handle);

	void CreateLocalUser(const FString& UserPlatformIdStr, const FPFEntityHandle EntityHandle);
	void RemoveLocalUser(const FString& PlatformUserIdStr);

private:
	TArray<TSharedPtr<FPlayFabUser>> LocalPlayFabUsers;
	TSharedPtr<FPlayFabUser> ServerEntity;
	TSet<FString> UsersToAuth;
	TMap<FString, UserAuthRequestData> UserAuthRequestsInFlight;
	bool bRegisterAuthDelegates = true;
	bool bAuthAllUsers = true;
	float TimeSinceLastAuth = 0.0f;
	// Consecutive failed authentication attempts, tracked per platform user id so failures for one
	// user don't penalize others. Drives exponential backoff and the retry cap so a persistently
	// rejected token cannot flood PlayFab's rate limiter.
	TMap<FString, int32> AuthFailureCountsByUser;
	// Current cooldown the auth gate enforces. Grows with the failing user's count and resets on success.
	float CurrentAuthCoolDownTime = 0.0f;

    FPFLocalUserHandle LocalUserHandle{ nullptr };

    /*PFServiceConfigHandle m_serviceConfigHandle{ nullptr };*/

	TArray<FDelegateHandle> LoginStatusChangedDelegateHandles;
	TArray<FDelegateHandle> LoginCompleteDelegateHandles;
	TArray<FDelegateHandle> LogoutCompleteDelegateHandles;

	// Guard to prevent OnLoginStatusChanged from re-queuing a user for auth
	// when we fire the delegate ourselves during re-auth completion.
	bool bFiringReAuthLoginStatusChanged = false;

	void RegisterAuthDelegates();
	void CleanUpAuthDelegates();

	void OnLoginStatusChanged(int32 LocalUserNum, ELoginStatus::Type OldStatus, ELoginStatus::Type NewStatus, const FUniqueNetId& NewId);
	void OnLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error);
	void OnLogoutComplete(int32 LocalUserNum, bool bWasSuccessful);

#if defined(OSS_PLAYFAB_WIN64)
	bool AuthenticateUserSteam(const FString& PlatformUserIdStr, FPFServiceConfigHandle ServiceConfigHandle);
#endif // OSS_PLAYFAB_WIN64
#if defined(OSS_PLAYFAB_GDK_SUPPORT)
	bool AuthenticateUserGDK(const FString& PlatformUserIdStr, FPFServiceConfigHandle ServiceConfigHandle);
#endif // OSS_PLAYFAB_GDK_SUPPORT
#if defined(OSS_PLAYFAB_PLAYSTATION)
	bool AuthenticateUserPlayStation(const FString& PlatformUserIdStr, FPFServiceConfigHandle ServiceConfigHandle);
#endif // OSS_PLAYFAB_PLAYSTATION
#if defined(OSS_PLAYFAB_SWITCH)
	bool AuthenticateUserSwitch(const FString& PlatformUserIdStr, FPFServiceConfigHandle ServiceConfigHandle);
#endif // OSS_PLAYFAB_SWITCH
	bool AuthenticateServerWithSecretKey();
	bool bServerAuthInFlight = false;
	bool bServerAuthenticated = false;
	bool bServerAuthFailed = false;
	bool AuthenticateUserByPlatform(const FString& UserPlatformId);

public:
	//OnLoginChanged
	virtual FDelegateHandle AddOnLoginChangedDelegate_Handle(const FOnLoginChangedDelegate& Delegate) override;
	virtual void ClearOnLoginChangedDelegate_Handle(FDelegateHandle& Handle) override;
	virtual void TriggerOnLoginChangedDelegates(int32 LocalUserNum) override;

	//OnLoginStatusChanged
	virtual FDelegateHandle AddOnLoginStatusChangedDelegate_Handle(int32 LocalUserNum, const FOnLoginStatusChangedDelegate& Delegate) override;
	virtual void ClearOnLoginStatusChangedDelegate_Handle(int32 LocalUserNum, FDelegateHandle& Handle) override;
	virtual void TriggerOnLoginStatusChangedDelegates(int32 LocalUserNum, ELoginStatus::Type OldStatus, ELoginStatus::Type NewStatus, const FUniqueNetId& NewId) override;

	//OnControllerPairingChanged
	virtual FDelegateHandle AddOnControllerPairingChangedDelegate_Handle(const FOnControllerPairingChangedDelegate& Delegate) override;
	virtual void ClearOnControllerPairingChangedDelegate_Handle(FDelegateHandle& Handle) override;
	virtual void TriggerOnControllerPairingChangedDelegates(int LocalUserNum, FControllerPairingChangedUserInfo PreviousUser, FControllerPairingChangedUserInfo NewUser) override;

	//OnLoginComplete
	virtual FDelegateHandle AddOnLoginCompleteDelegate_Handle(int32 LocalUserNum, const FOnLoginCompleteDelegate& Delegate) override;
	virtual void ClearOnLoginCompleteDelegate_Handle(int32 LocalUserNum, FDelegateHandle& Handle) override;
	virtual void TriggerOnLoginCompleteDelegates(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error) override;

	//OnLogoutComplete
	virtual FDelegateHandle AddOnLogoutCompleteDelegate_Handle(int32 LocalUserNum, const FOnLogoutCompleteDelegate& Delegate) override;
	virtual void ClearOnLogoutCompleteDelegate_Handle(int32 LocalUserNum, FDelegateHandle& Handle) override;
	virtual void TriggerOnLogoutCompleteDelegates(int32 LocalUserNum, bool bWasSuccessful) override;

	//OnLoginFlowLogout
	virtual FDelegateHandle AddOnLoginFlowLogoutDelegate_Handle(const FOnLoginFlowLogoutDelegate& Delegate) override;
	virtual void ClearOnLoginFlowLogoutDelegate_Handle(FDelegateHandle& Handle) override;
	virtual void TriggerOnLoginFlowLogoutDelegates(const TArray<FString>& LoginDomains) override;
};

typedef TSharedPtr<class FOnlineIdentityPlayFab, ESPMode::ThreadSafe> FOnlineIdentityPlayFabPtr;