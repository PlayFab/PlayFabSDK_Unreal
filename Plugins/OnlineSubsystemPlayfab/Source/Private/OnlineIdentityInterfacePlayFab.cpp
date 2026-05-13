//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "OnlineIdentityInterfacePlayFab.h"
#include "OnlineSubsystemPlayFab.h"
#include "PlayFabLobby.h"
#include "PlayFabHelpers.h"

#include "Serialization/JsonWriter.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonTypes.h"
#include "Serialization/JsonSerializer.h"

#include "HttpModule.h"
#include "OnlineSubsystem.h"
#include "SocketSubsystem.h"

#include "PFCore.h"
#include "PFAuthentication.h"

#if defined(OSS_PLAYFAB_PLAYSTATION)
THIRD_PARTY_INCLUDES_START
#include <playfab/core/PFCorePS.h>
THIRD_PARTY_INCLUDES_END
#endif
#include "PFEntity.h"
#include "PFServiceConfig.h"
#include "PFLocalUser.h"
#include "Generated/PFAuthentication.h"

#define OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE IOnlineSubsystem* NativeSubsystem = IOnlineSubsystem::GetByPlatform();  IOnlineIdentityPtr NativeIdentityInterface = NativeSubsystem ? NativeSubsystem->GetIdentityInterface() : nullptr; if (NativeIdentityInterface)

static constexpr float AuthCoolDownTime = 3.0f;

FOnlineIdentityPlayFab::FOnlineIdentityPlayFab(class FOnlineSubsystemPlayFab* InSubsystem) : 
	OSSPlayFab(InSubsystem),
	TimeSinceLastAuth(AuthCoolDownTime) // Don't wait on the cool down to auth on the very first go
{
	check(OSSPlayFab);
}

FOnlineIdentityPlayFab::~FOnlineIdentityPlayFab()
{
	OSSPlayFab = nullptr;

	CleanUpAuthDelegates();
	CleanUpLocalUsers();
}

bool FOnlineIdentityPlayFab::Login(int32 LocalUserNum, const FOnlineAccountCredentials& AccountCredentials)
{
	UE_LOG_ONLINE_IDENTITY(Verbose, TEXT("FOnlineIdentityPlayFab::Login"));

	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		return NativeIdentityInterface->Login(LocalUserNum, AccountCredentials);
	}
	
	return false;
}

bool FOnlineIdentityPlayFab::Logout(int32 LocalUserNum)
{
	UE_LOG_ONLINE_IDENTITY(Verbose, TEXT("FOnlineIdentityPlayFab::Logout"));

	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		return NativeIdentityInterface->Logout(LocalUserNum);
	}

	return false;
}

bool FOnlineIdentityPlayFab::AutoLogin(int32 LocalUserNum)
{
	return Login(LocalUserNum, FOnlineAccountCredentials());
}

TSharedPtr<FUserOnlineAccount> FOnlineIdentityPlayFab::GetUserAccount(const FUniqueNetId& UserId) const
{
	UE_LOG_ONLINE_IDENTITY(Verbose, TEXT("FOnlineIdentityPlayFab::GetUserAccount"));

	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		return NativeIdentityInterface->GetUserAccount(UserId);
	}

	return nullptr;
}

TArray<TSharedPtr<FUserOnlineAccount> > FOnlineIdentityPlayFab::GetAllUserAccounts() const
{
	UE_LOG_ONLINE_IDENTITY(Verbose, TEXT("FOnlineIdentityPlayFab::GetAllUserAccounts"));

	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		return NativeIdentityInterface->GetAllUserAccounts();
	}

	return TArray<TSharedPtr<FUserOnlineAccount>>();
}

TSharedPtr<const FUniqueNetId> FOnlineIdentityPlayFab::GetUniquePlayerId(int32 LocalUserNum) const
{
	UE_LOG_ONLINE_IDENTITY(Verbose, TEXT("FOnlineIdentityPlayFab::GetUniquePlayerId"));

	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		return NativeIdentityInterface->GetUniquePlayerId(LocalUserNum);
	}

	return nullptr;
}

TSharedPtr<const FUniqueNetId> FOnlineIdentityPlayFab::GetSponsorUniquePlayerId(int32 LocalUserNum) const
{
	UE_LOG_ONLINE_IDENTITY(Verbose, TEXT("FOnlineIdentityPlayFab::GetSponsorUniquePlayerId"));

	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		return NativeIdentityInterface->GetSponsorUniquePlayerId(LocalUserNum);
	}

	return nullptr;
}

TSharedPtr<const FUniqueNetId> FOnlineIdentityPlayFab::CreateUniquePlayerId(uint8* Bytes, int32 Size)
{
	UE_LOG_ONLINE_IDENTITY(Verbose, TEXT("FOnlineIdentityPlayFab::CreateUniquePlayerId"));

	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		return NativeIdentityInterface->CreateUniquePlayerId(Bytes, Size);
	}

	return nullptr;
}

TSharedPtr<const FUniqueNetId> FOnlineIdentityPlayFab::CreateUniquePlayerId(const FString& Str)
{
	UE_LOG_ONLINE_IDENTITY(Verbose, TEXT("FOnlineIdentityPlayFab::CreateUniquePlayerId"));

	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		return NativeIdentityInterface->CreateUniquePlayerId(Str);
	}

	return nullptr;
}

ELoginStatus::Type FOnlineIdentityPlayFab::GetLoginStatus(int32 LocalUserNum) const
{
	UE_LOG_ONLINE_IDENTITY(Verbose, TEXT("FOnlineIdentityPlayFab::GetLoginStatus"));

	// Only report LoggedIn once the PlayFab user has been fully authenticated
	// (i.e., present in LocalPlayFabUsers or ServerEntity). This ensures titles
	// can rely on GetLoginStatus to know when session APIs are safe to call,
	// rather than seeing the native platform's early "logged in" status.
	if (IsRunningDedicatedServer())
	{
		if (ServerEntity.IsValid())
		{
			return ELoginStatus::LoggedIn;
		}
	}
	else if (LocalUserNum < LocalPlayFabUsers.Num() && LocalPlayFabUsers[LocalUserNum].IsValid())
	{
		return ELoginStatus::LoggedIn;
	}

	return ELoginStatus::NotLoggedIn;
}

ELoginStatus::Type FOnlineIdentityPlayFab::GetLoginStatus(const FUniqueNetId& UserId) const
{
	UE_LOG_ONLINE_IDENTITY(Verbose, TEXT("FOnlineIdentityPlayFab::GetLoginStatus"));

	// Only report LoggedIn once the PlayFab user has been fully authenticated.
	// Check PlayFab local users by platform ID string lookup.
	TSharedPtr<FPlayFabUser> LocalUser = const_cast<FOnlineIdentityPlayFab*>(this)->GetPartyLocalUserFromPlatformIdString(UserId.ToString());
	if (LocalUser.IsValid())
	{
		return ELoginStatus::LoggedIn;
	}

	return ELoginStatus::NotLoggedIn;
}

FString FOnlineIdentityPlayFab::GetPlayerNickname(int32 LocalUserNum) const
{
	UE_LOG_ONLINE_IDENTITY(Verbose, TEXT("FOnlineIdentityPlayFab::GetPlayerNickname"));

	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		return NativeIdentityInterface->GetPlayerNickname(LocalUserNum);
	}

	return TEXT("");
}

FString FOnlineIdentityPlayFab::GetPlayerNickname(const FUniqueNetId& UserId) const
{
	UE_LOG_ONLINE_IDENTITY(Verbose, TEXT("FOnlineIdentityPlayFab::GetPlayerNickname"));

	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		// Don't forward PlayFab-type IDs to native interface (causes GDK type assertion)
		if (UserId.GetType() != PLAYFAB_SUBSYSTEM)
		{
			return NativeIdentityInterface->GetPlayerNickname(UserId);
		}
	}

	return TEXT("");
}

FString FOnlineIdentityPlayFab::GetAuthToken(int32 LocalUserNum) const
{
	UE_LOG_ONLINE_IDENTITY(Verbose, TEXT("FOnlineIdentityPlayFab::GetAuthToken"));

	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		return NativeIdentityInterface->GetAuthToken(LocalUserNum);
	}

	return TEXT("");
}

void FOnlineIdentityPlayFab::RevokeAuthToken(const FUniqueNetId& UserId, const FOnRevokeAuthTokenCompleteDelegate& Delegate)
{
	UE_LOG_ONLINE_IDENTITY(Verbose, TEXT("FOnlineIdentityPlayFab::RevokeAuthToken"));

	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		NativeIdentityInterface->RevokeAuthToken(UserId, Delegate);
	}
}

void FOnlineIdentityPlayFab::GetUserPrivilege(const FUniqueNetId& LocalUserId, EUserPrivileges::Type Privilege, const FOnGetUserPrivilegeCompleteDelegate& Delegate, EShowPrivilegeResolveUI ShowResolveUI)
{
	UE_LOG_ONLINE_IDENTITY(Verbose, TEXT("FOnlineIdentityPlayFab::GetUserPrivilege"));

	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		NativeIdentityInterface->GetUserPrivilege(LocalUserId, Privilege, Delegate, ShowResolveUI);
	}
}

FPlatformUserId FOnlineIdentityPlayFab::GetPlatformUserIdFromUniqueNetId(const FUniqueNetId& UniqueNetId) const
{
	UE_LOG_ONLINE_IDENTITY(Verbose, TEXT("FOnlineIdentityPlayFab::GetPlatformUserIdFromUniqueNetId"));

	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		return NativeIdentityInterface->GetPlatformUserIdFromUniqueNetId(UniqueNetId);
	}

	return PLATFORMUSERID_NONE;
}

FString FOnlineIdentityPlayFab::GetAuthType() const
{
	UE_LOG_ONLINE_IDENTITY(Verbose, TEXT("FOnlineIdentityPlayFab::GetAuthType"));

	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		return NativeIdentityInterface->GetAuthType();
	}

	return TEXT("PlayFabParty");
}

void FOnlineIdentityPlayFab::Tick(float DeltaTime)
{
	TimeSinceLastAuth += DeltaTime;
	
	// Auth all players once at start or after resume
	if (bAuthAllUsers == true)
	{
		// The native identity interface may not be constructed yet
		OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
		{
			UE_LOG_ONLINE(Verbose, TEXT("FOnlineIdentityPlayFab::Tick: Native identity interface initialized, registering auth delegates and doing initial user auth"));

			if (bRegisterAuthDelegates)
			{
				RegisterAuthDelegates();
			}

			// Dedicated servers authenticate separately via TryAuthenticateUsers()
			if (!IsRunningDedicatedServer())
			{
				for (const auto& User : NativeIdentityInterface->GetAllUserAccounts())
				{
					FString PlatformUserIdStr;
					User->GetUserAttribute(USER_ATTR_ID, PlatformUserIdStr);
					UsersToAuth.Add(PlatformUserIdStr);
				}
#if defined(OSS_PLAYFAB_WIN64) || defined(OSS_PLAYFAB_PLAYSTATION)
				if (OSSPlayFab->bForceAutoLogin && !IsNativePlatformSubsystemGDK())
				{
					UE_LOG_ONLINE_IDENTITY(Verbose, TEXT("AutoLogin"));
					AutoLogin(0);
				}
#endif
			}

			bAuthAllUsers = false;
		}
	}

	// Don't bother trying to auth users while PlayFab is not initialized and ready
	if (OSSPlayFab && OSSPlayFab->bPartyInitialized)
	{
		TryAuthenticateUsers();
	}
}

void FOnlineIdentityPlayFab::OnAppSuspend()
{
	UE_LOG_ONLINE_IDENTITY(Verbose, TEXT("FOnlineIdentityPlayFab::OnAppSuspend"));
	
	CleanUpLocalUsers();
}

void FOnlineIdentityPlayFab::OnAppResume()
{
	UE_LOG_ONLINE_IDENTITY(Verbose, TEXT("FOnlineIdentityPlayFab::OnAppResume"));

	bAuthAllUsers = true;
}

void FOnlineIdentityPlayFab::RegisterAuthDelegates()
{
	UE_LOG_ONLINE_IDENTITY(Verbose, TEXT("FOnlineIdentityPlayFab::RegisterAuthDelegates"));

	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		for (int32 i = 0; i < MAX_LOCAL_PLAYERS; ++i)
		{
			FDelegateHandle NewHandle = NativeIdentityInterface->AddOnLoginStatusChangedDelegate_Handle(i, FOnLoginStatusChangedDelegate::CreateRaw(this, &FOnlineIdentityPlayFab::OnLoginStatusChanged));
			LoginStatusChangedDelegateHandles.Add(NewHandle);
		}

		for (int32 i = 0; i < MAX_LOCAL_PLAYERS; ++i)
		{
			FDelegateHandle NewHandle = NativeIdentityInterface->AddOnLoginCompleteDelegate_Handle(i, FOnLoginCompleteDelegate::CreateRaw(this, &FOnlineIdentityPlayFab::OnLoginComplete));
			LoginCompleteDelegateHandles.Add(NewHandle);
		}

		for (int32 i = 0; i < MAX_LOCAL_PLAYERS; ++i)
		{
			FDelegateHandle NewHandle = NativeIdentityInterface->AddOnLogoutCompleteDelegate_Handle(i, FOnLogoutCompleteDelegate::CreateRaw(this, &FOnlineIdentityPlayFab::OnLogoutComplete));
			LogoutCompleteDelegateHandles.Add(NewHandle);
		}
	}

	bRegisterAuthDelegates = false;
}

void FOnlineIdentityPlayFab::CleanUpAuthDelegates()
{
	UE_LOG_ONLINE_IDENTITY(Verbose, TEXT("FOnlineIdentityPlayFab::CleanUpAuthDelegates"));

	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		for (int32 i = 0; i < LoginStatusChangedDelegateHandles.Num(); ++i)
		{
			NativeIdentityInterface->ClearOnLoginStatusChangedDelegate_Handle(i, LoginStatusChangedDelegateHandles[i]);
		}

		for (int32 i = 0; i < LoginCompleteDelegateHandles.Num(); ++i)
		{
			NativeIdentityInterface->ClearOnLoginCompleteDelegate_Handle(i, LoginCompleteDelegateHandles[i]);
		}

		for (int32 i = 0; i < LogoutCompleteDelegateHandles.Num(); ++i)
		{
			NativeIdentityInterface->ClearOnLogoutCompleteDelegate_Handle(i, LogoutCompleteDelegateHandles[i]);
		}

		LoginStatusChangedDelegateHandles.Empty();
		LoginCompleteDelegateHandles.Empty();
		LogoutCompleteDelegateHandles.Empty();
	}

	bRegisterAuthDelegates = true;
}

void FOnlineIdentityPlayFab::OnLoginStatusChanged(int32 LocalUserNum, ELoginStatus::Type OldStatus, ELoginStatus::Type NewStatus, const FUniqueNetId& NewId)
{
	UE_LOG_ONLINE_IDENTITY(Verbose, TEXT("FOnlineIdentityPlayFab::OnLoginStatusChanged"));

	// Skip if this was triggered by our own re-auth notification to avoid re-queuing
	if (bFiringReAuthLoginStatusChanged)
	{
		return;
	}

	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		if (NewId.IsValid())
		{
			FString PlatformUserIdStr = NewId.ToString();
			if (NewStatus == ELoginStatus::LoggedIn)
			{
				UsersToAuth.Add(PlatformUserIdStr);
			}
			else if (NewStatus == ELoginStatus::NotLoggedIn)
			{
				// Clean up the PlayFab local user
				RemoveLocalUser(PlatformUserIdStr);
			}
		}
	}
}

void FOnlineIdentityPlayFab::OnLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error)
{
	UE_LOG_ONLINE_IDENTITY(Verbose, TEXT("FOnlineIdentityPlayFab::OnLoginComplete"));

	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		if (bWasSuccessful && UserId.IsValid())
		{
			UsersToAuth.Add(UserId.ToString());
		}
	}
}

void FOnlineIdentityPlayFab::OnLogoutComplete(int32 LocalUserNum, bool bWasSuccessful)
{
	UE_LOG_ONLINE_IDENTITY(Verbose, TEXT("FOnlineIdentityPlayFab::OnLogoutComplete"));

	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		// Clean up the PlayFab local user
		if (bWasSuccessful)
		{
			TSharedPtr<const FUniqueNetId> UserId = NativeIdentityInterface->GetUniquePlayerId(LocalUserNum);
			if (UserId.IsValid())
			{
				FString PlatformUserIdStr = UserId->ToString();
				RemoveLocalUser(PlatformUserIdStr);
			}
		}
	}
}

void FOnlineIdentityPlayFab::TryAuthenticateUsers()
{
	// Dedicated server auth is handled separately from player auth
	if (IsRunningDedicatedServer())
	{
		if (!bServerAuthInFlight && !bServerAuthenticated && !bServerAuthFailed)
		{
			if (!AuthenticateServerWithSecretKey())
			{
				bServerAuthFailed = true;
			}
		}
		return;
	}

	// Update any users that need to update their tokens
	for (TSharedPtr<FPlayFabUser> LocalUser : LocalPlayFabUsers)
	{
		if (FDateTime::Now() > LocalUser->GetEntityTokenUpdateTime())
		{
			UsersToAuth.Add(LocalUser->GetPlatformUserId());
		}
	}
	
	// Only try to auth if we have waited long enough and have users that need it
	if (TimeSinceLastAuth > AuthCoolDownTime && UsersToAuth.Num() != 0)
	{
		for (const FString& PlatformUserIdStr : UsersToAuth)
		{
			AuthenticateUser(PlatformUserIdStr);
		}
	}
}

void FOnlineIdentityPlayFab::CleanUpLocalUsers()
{
	UE_LOG_ONLINE_IDENTITY(Verbose, TEXT("FOnlineIdentityPlayFab::CleanUpLocalUsers"));

	LocalPlayFabUsers.Empty();
	ServerEntity.Reset();

	UsersToAuth.Empty();
	UserAuthRequestsInFlight.Empty();
	bServerAuthFailed = false;
}

bool FOnlineIdentityPlayFab::AuthenticateUser(const FString& PlatformUserIdStr)
{
	// Only if not already in flight for this user
	if (UserAuthRequestsInFlight.Contains(PlatformUserIdStr))
	{
		return false;
	}

	bool bAuthStarted = AuthenticateUserByPlatform(PlatformUserIdStr);

	if (bAuthStarted && !UserAuthRequestsInFlight.Contains(PlatformUserIdStr))
	{
		UserAuthRequestData MetaData;
		UserAuthRequestsInFlight.Add(PlatformUserIdStr, MetaData);
	}

	return bAuthStarted;
}

#if defined(OSS_PLAYFAB_WIN64)
bool FOnlineIdentityPlayFab::AuthenticateUserSteam(const FString& PlatformUserIdStr, FPFServiceConfigHandle ServiceConfigHandle)
{
	if (!FPFLocalUserCreateHandleWithSteamUser(ServiceConfigHandle, nullptr, LocalUserHandle))
	{
		UE_LOG_ONLINE(Error, TEXT("FOnlineIdentityPlayFab:FPFLocalUserCreateHandleWithSteamUser was unable to create PlayFab LocalUser"));
		return false;
	}

	return FPFLocalUserLoginAsync(
		LocalUserHandle,
		true,
		FOnPFAuthenticationLoginCompleteDelegate::CreateLambda([this, PlatformUserIdStr](const FPFAuthenticationLoginResult* lognResults, FPFEntityHandle* entityHandle, bool bWasSuccessful)
			{
				const FPFEntityHandle EntityHandle = entityHandle ? *entityHandle : nullptr;
				Auth_PFAuthRequestComplete(bWasSuccessful, PlatformUserIdStr, EntityHandle);
				UE_LOG(LogTemp, Display, TEXT("LoginWithSteam Complete"));
			})
	);
}
#endif // OSS_PLAYFAB_WIN64

#if defined(OSS_PLAYFAB_GDK_SUPPORT)
bool FOnlineIdentityPlayFab::AuthenticateUserGDK(const FString& PlatformUserIdStr, FPFServiceConfigHandle ServiceConfigHandle)
{
	int64 xuid = FCString::Atoi64(*PlatformUserIdStr);
	FGDKUserHandle XboxUser = IGDKRuntimeModule::Get().GetUserHandleByXUserId(xuid);

	if (!FPFLocalUserCreateHandleWithXboxUser(ServiceConfigHandle, XboxUser, nullptr, LocalUserHandle))
	{
		UE_LOG_ONLINE(Error, TEXT("FOnlineIdentityPlayFab:FPFLocalUserCreateHandleWithXboxUser was unable to create PlayFab LocalUser"));
		return false;
	}

	return FPFLocalUserLoginAsync(
		LocalUserHandle,
		true,
		FOnPFAuthenticationLoginCompleteDelegate::CreateLambda([this, PlatformUserIdStr](const FPFAuthenticationLoginResult* lognResults, FPFEntityHandle* entityHandle, bool bWasSuccessful)
			{
				const FPFEntityHandle EntityHandle = entityHandle ? *entityHandle : nullptr;
				Auth_PFAuthRequestComplete(bWasSuccessful, PlatformUserIdStr, EntityHandle);
				UE_LOG(LogTemp, Display, TEXT("LoginWithXbox Complete"));
			})
	);
}
#endif // OSS_PLAYFAB_GDK_SUPPORT

bool FOnlineIdentityPlayFab::AuthenticateServerWithSecretKey()
{
#if defined(OSS_PLAYFAB_PLAYSTATION)
	// Server auth with secret key not supported on PlayStation.
	UE_LOG_ONLINE(Error, TEXT("FOnlineIdentityPlayFab::AuthenticateServerWithSecretKey: Not supported on PlayStation"));
	return false;
#else // OSS_PLAYFAB_PLAYSTATION
	FPFInitialize();

	FPFServiceConfigHandle ServiceConfigHandle;

	FString TitleIdStr = OSSPlayFab->GetAppId();
	FString PlayFabEndpoint = TEXT("https://");
	PlayFabEndpoint.Append(TitleIdStr);
	PlayFabEndpoint.Append(TEXT(".playfabapi.com"));

	if (!FPFServiceConfigCreateHandle(PlayFabEndpoint, TitleIdStr, ServiceConfigHandle))
	{
		UE_LOG_ONLINE(Error, TEXT("FOnlineIdentityPlayFab::AuthenticateServerWithSecretKey: FPFServiceConfigCreateHandle failed"));
		return false;
	}

	// TODO: Replace config/env-var secret key retrieval with a secure key store (e.g. Azure Key Vault, MPS) to avoid embedding secrets in config files or environment variables.
	FString TitleSecretKey;
	if (!GConfig->GetString(TEXT("OnlineSubsystemPlayFab"), TEXT("TitleSecretKey"), TitleSecretKey, GEngineIni) || TitleSecretKey.IsEmpty())
	{
		// Fallback to environment variable for cases where embedding the key in config is undesirable
		TitleSecretKey = FPlatformMisc::GetEnvironmentVariable(TEXT("PF_TITLE_SECRET_KEY"));
	}
	if (TitleSecretKey.IsEmpty())
	{
		UE_LOG_ONLINE(Error, TEXT("FOnlineIdentityPlayFab::AuthenticateServerWithSecretKey: TitleSecretKey not found in [OnlineSubsystemPlayFab] config or PF_TITLE_SECRET_KEY environment variable"));
		return false;
	}

	// Build a unique server address hash as a postfix for the custom ID
	FString AddressPostfix;
	{
		FString HostAddr = TEXT("unknown");
		bool bCanBindAll = false;
		if (ISocketSubsystem* SocketSub = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM))
		{
			TSharedRef<FInternetAddr> LocalAddr = SocketSub->GetLocalHostAddr(*GLog, bCanBindAll);
			HostAddr = LocalAddr->ToString(false);
		}
		int32 ServerPort = 7777; // UE default
		FParse::Value(FCommandLine::Get(), TEXT("Port="), ServerPort);
		FString RawAddress = FString::Printf(TEXT("%s:%d"), *HostAddr, ServerPort);
		uint32 AddrHash = GetTypeHash(RawAddress);
		AddressPostfix = FString::Printf(TEXT("%08X"), AddrHash);
	}

	FString ServerCustomIdPrefix;
	FString ServerCustomId;
	if (GConfig->GetString(TEXT("OnlineSubsystemPlayFab"), TEXT("ServerCustomId"), ServerCustomIdPrefix, GEngineIni) && !ServerCustomIdPrefix.IsEmpty())
	{
		ServerCustomId = FString::Printf(TEXT("%s_%s"), *ServerCustomIdPrefix, *AddressPostfix);
	}
	else
	{
		ServerCustomId = FString::Printf(TEXT("PlayFabServer_%s_%s"), *OSSPlayFab->GetAppId(), *AddressPostfix);
	}
	// customId must be 32-100 characters; pad if needed
	while (ServerCustomId.Len() < 32)
	{
		ServerCustomId.Append(TEXT("_pad"));
	}
	if (ServerCustomId.Len() > 100)
	{
		ServerCustomId.LeftInline(100);
	}

	bServerAuthInFlight = true;

    FPFAuthenticationGetEntityRequest Request{};
    Request.customTagsCount = 0;
	
	UE_LOG(LogTemp, Display, TEXT("FOnlineIdentityPlayFab: Step 1 - Getting title entity with secret key..."));

	return FPFAuthenticationGetEntityWithSecretKeyAsync(
		ServiceConfigHandle,
		TitleSecretKey,
		Request,
		FOnGetEntityWithSecretKeyDelegate::CreateLambda([this, ServerCustomId](FPFEntityHandle* EntityHandle, bool bWasSuccessful)
			{
				if (!bWasSuccessful || !EntityHandle)
				{
					bServerAuthInFlight = false;
					UE_LOG(LogTemp, Error, TEXT("FOnlineIdentityPlayFab: Step 1 FAILED - GetEntityWithSecretKey returned failure"));
					return;
				}

				// Diagnostic: log the entity type returned
				SIZE_T* KeySizePtr = static_cast<SIZE_T*>(FMemory::Malloc(sizeof(SIZE_T)));
				*KeySizePtr = 0;
				TSharedPtr<SIZE_T> KeySize = MakeShareable(KeySizePtr, [](SIZE_T* P) { FMemory::Free(P); });
				HRESULT hr = FPFEntityGetEntityKeySize(*EntityHandle, KeySize);
				if (SUCCEEDED(hr))
				{
					TSharedPtr<void> KeyBuffer = MakeShareable(FMemory::Malloc(*KeySize.Get()), [](void* P) { FMemory::Free(P); });
					TSharedPtr<const FPFEntityKey> EntityKey = MakeShareable(new FPFEntityKey);
					hr = FPFEntityGetEntityKey(*EntityHandle, *KeySize.Get(), KeyBuffer, EntityKey, nullptr);
					if (SUCCEEDED(hr))
					{
						UE_LOG(LogTemp, Display, TEXT("FOnlineIdentityPlayFab: Step 1 SUCCESS - Entity type='%s', id='%s'"),
							*EntityKey->type, *EntityKey->id);
					}
				}

				// Step 2: Use the title entity to create a game_server entity
				UE_LOG(LogTemp, Display, TEXT("FOnlineIdentityPlayFab: Step 2 - AuthenticateGameServerWithCustomId (customId='%s')..."), *ServerCustomId);

				FPFAuthenticationAuthenticateCustomIdRequest GameServerRequest;
				// Use const_cast + placement to set the const FString member
				const_cast<FString&>(GameServerRequest.customId) = ServerCustomId;
				GameServerRequest.customTagsCount = 0;

				bool bStarted = FPFAuthenticationAuthenticateGameServerWithCustomIdAsync(
					*EntityHandle,
					GameServerRequest,
					FOnAuthenticateGameServerWithCustomIdDelegate::CreateLambda([this](FPFEntityHandle* GameServerEntityHandle, bool* bNewlyCreated, bool bGameServerSuccess)
						{
							bServerAuthInFlight = false;
							if (bGameServerSuccess && GameServerEntityHandle)
							{
								bServerAuthenticated = true;
								UE_LOG(LogTemp, Display, TEXT("FOnlineIdentityPlayFab: Step 2 SUCCESS - game_server entity created (newlyCreated=%s)"),
									bNewlyCreated ? (*bNewlyCreated ? TEXT("true") : TEXT("false")) : TEXT("null"));

								// Diagnostic: log game_server entity type
								SIZE_T* GsKeySizePtr = static_cast<SIZE_T*>(FMemory::Malloc(sizeof(SIZE_T)));
								*GsKeySizePtr = 0;
								TSharedPtr<SIZE_T> GsKeySize = MakeShareable(GsKeySizePtr, [](SIZE_T* P) { FMemory::Free(P); });
								HRESULT gsHr = FPFEntityGetEntityKeySize(*GameServerEntityHandle, GsKeySize);
								if (SUCCEEDED(gsHr))
								{
									TSharedPtr<void> GsKeyBuffer = MakeShareable(FMemory::Malloc(*GsKeySize.Get()), [](void* P) { FMemory::Free(P); });
									TSharedPtr<const FPFEntityKey> GsEntityKey = MakeShareable(new FPFEntityKey);
									gsHr = FPFEntityGetEntityKey(*GameServerEntityHandle, *GsKeySize.Get(), GsKeyBuffer, GsEntityKey, nullptr);
									if (SUCCEEDED(gsHr))
									{
										UE_LOG(LogTemp, Display, TEXT("FOnlineIdentityPlayFab: game_server entity type='%s', id='%s'"),
											*GsEntityKey->type, *GsEntityKey->id);
									}
								}

								// Step 3: Get entity token and register with Multiplayer subsystem for lobby APIs
								FPFEntityHandle CapturedHandle = *GameServerEntityHandle;
								FPFEntityGetEntityTokenAsync(
									*GameServerEntityHandle,
									FOnEntityGetEntityTokenDelegate::CreateLambda([this, CapturedHandle](bool bTokenSuccess, FPFEntityToken const* EntityToken)
										{
											if (bTokenSuccess && EntityToken && !EntityToken->token.IsEmpty())
											{
												// Extract entity key for PFMultiplayerSetEntityToken
												SIZE_T* KeySizePtr = static_cast<SIZE_T*>(FMemory::Malloc(sizeof(SIZE_T)));
												*KeySizePtr = 0;
												TSharedPtr<SIZE_T> KeySize = MakeShareable(KeySizePtr, [](SIZE_T* P) { FMemory::Free(P); });
												HRESULT hr = FPFEntityGetEntityKeySize(CapturedHandle, KeySize);
												if (SUCCEEDED(hr))
												{
													TSharedPtr<void> KeyBuffer = MakeShareable(FMemory::Malloc(*KeySize.Get()), [](void* P) { FMemory::Free(P); });
													TSharedPtr<const FPFEntityKey> EntityKey = MakeShareable(new FPFEntityKey);
													hr = FPFEntityGetEntityKey(CapturedHandle, *KeySize.Get(), KeyBuffer, EntityKey, nullptr);
													if (SUCCEEDED(hr))
													{
														std::string entityIdStr = TCHAR_TO_UTF8(*EntityKey->id);
														std::string entityTypeStr = TCHAR_TO_UTF8(*EntityKey->type);
														PFEntityKey RawEntityKey{ entityIdStr.c_str(), entityTypeStr.c_str() };
														std::string tokenStr = TCHAR_TO_UTF8(*EntityToken->token);
														HRESULT setHr = PFMultiplayerSetEntityToken(
															OSSPlayFab->GetMultiplayerHandle(),
															&RawEntityKey,
															tokenStr.c_str()
														);
														if (SUCCEEDED(setHr))
														{
															UE_LOG(LogTemp, Display, TEXT("FOnlineIdentityPlayFab: Step 3 SUCCESS - Entity token registered with Multiplayer subsystem"));
														}
														else
														{
															UE_LOG(LogTemp, Error, TEXT("FOnlineIdentityPlayFab: Step 3 FAILED - PFMultiplayerSetEntityToken error: 0x%08x"), setHr);
														}
													}
												}
											}
											else
											{
												UE_LOG(LogTemp, Warning, TEXT("FOnlineIdentityPlayFab: Step 3 - Could not get entity token (success=%s, token=%s)"),
													bTokenSuccess ? TEXT("true") : TEXT("false"),
													(EntityToken && !EntityToken->token.IsEmpty()) ? TEXT("present") : TEXT("empty"));
											}

											Auth_PFAuthRequestComplete(true, TEXT("DedicatedServer"), CapturedHandle);
											UE_LOG(LogTemp, Display, TEXT("FOnlineIdentityPlayFab: Server authentication complete"));
										})
								);
							}
							else
							{
								UE_LOG(LogTemp, Error, TEXT("FOnlineIdentityPlayFab: Step 2 FAILED - AuthenticateGameServerWithCustomId returned failure"));
							}
						})
				);

				if (!bStarted)
				{
					bServerAuthInFlight = false;
					UE_LOG(LogTemp, Error, TEXT("FOnlineIdentityPlayFab: Step 2 FAILED - Could not start AuthenticateGameServerWithCustomId"));
				}
			})
	);
#endif // !OSS_PLAYFAB_PLAYSTATION
}

// Called after platform has appended its headers/body
bool FOnlineIdentityPlayFab::AuthenticateUserByPlatform(const FString& PlatformUserIdStr)
{
#if defined(OSS_PLAYFAB_PLAYSTATION)
	PFInitialize(nullptr);
#else // OSS_PLAYFAB_PLAYSTATION
	FPFInitialize();
#endif // !OSS_PLAYFAB_PLAYSTATION

	FPFServiceConfigHandle m_serviceConfigHandle;

	FString TitleIdStr = OSSPlayFab->GetAppId();
	std::string titleId(TCHAR_TO_UTF8(*TitleIdStr));

	FString PlayFabEndpoint = TEXT("https://");
	PlayFabEndpoint.Append(TitleIdStr);
	PlayFabEndpoint.Append(TEXT(".playfabapi.com"));

	if (!FPFServiceConfigCreateHandle(PlayFabEndpoint,
		TitleIdStr,
		m_serviceConfigHandle))
	{
		UE_LOG_ONLINE(Error, TEXT("[FOnlineIdentityPlayFab::FPFServiceConfigCreateHandle] failed"));
		return false;
	}

#ifdef OSS_PLAYFAB_SWITCH
	// TODO modify to use LocalUserHandle
	PFAuthenticationLoginWithNintendoServiceAccountRequest request = {};
	request.createAccount = true;		
	return FPFAuthenticationLoginWithNintendoServiceAccountAsync(
		m_serviceConfigHandle,
		request,
		FOnLoginWithNintendoServiceAccountDelegate::CreateLambda([this, PlatformUserIdStr](bool bWasSuccessful, const PFAuthenticationLoginResult* lognResults, PFEntityHandle* entityHandle)
			{
				const FPFEntityHandle EntityHandle = entityHandle ? *entityHandle : nullptr;
				Auth_PFAuthRequestComplete(bWasSuccessful, PlatformUserIdStr, EntityHandle);
				UE_LOG(LogTemp, Display, TEXT("LoginWithNintendoServiceAccount Complete"));
			})
	);
#elif defined(OSS_PLAYFAB_WIN64)
#if defined(OSS_PLAYFAB_GDK_SUPPORT)
	if (IsNativePlatformSubsystemGDK())
	{
		return AuthenticateUserGDK(PlatformUserIdStr, m_serviceConfigHandle);
	}

	return AuthenticateUserSteam(PlatformUserIdStr, m_serviceConfigHandle);
#else
	return AuthenticateUserSteam(PlatformUserIdStr, m_serviceConfigHandle);
#endif // OSS_PLAYFAB_GDK_SUPPORT
#elif defined(OSS_PLAYFAB_PLAYSTATION)
	return AuthenticateUserPlayStation(PlatformUserIdStr, m_serviceConfigHandle);
#elif defined(OSS_PLAYFAB_GDK)
	return AuthenticateUserGDK(PlatformUserIdStr, m_serviceConfigHandle);
#endif // OSS_PLAYFAB_SWITCH
}

void FOnlineIdentityPlayFab::Auth_PFAuthRequestComplete(bool bSucceeded, const FString& UserPlatformIdStr, FPFEntityHandle handle)
{
	UE_LOG(LogTemp, Display, TEXT("Auth_PFAuthRequestComplete In"));
	if (bSucceeded)
	{
		int32 Index;
		TSharedPtr<FPlayFabUser> LocalUser = GetPartyLocalUserFromPlatformIdString(UserPlatformIdStr, &Index);
		if (LocalUser)
		{
			// Re-auth completed - update entity handle in case it changed (e.g., Steam AutoLogin
			// triggering a second auth that creates a new entity handle via the SDK)
			LocalUser->SetEntityHandle(handle);
			LocalUser->SetNewEntityTokenUpdateTime();
			TriggerOnAuthenticateUserCompleteDelegates(Index, true, UserPlatformIdStr, TEXT(""));

			// Notify titles that a re-auth occurred so they can react (e.g., re-fetch entity handles).
			// Use a guard flag to prevent our own OnLoginStatusChanged handler from re-queuing
			// this user for another auth cycle.
			TSharedPtr<const FUniqueNetId> UserId = GetUniquePlayerId(Index);
			if (UserId.IsValid())
			{
				bFiringReAuthLoginStatusChanged = true;
				TriggerOnLoginStatusChangedDelegates(Index, ELoginStatus::LoggedIn, ELoginStatus::LoggedIn, *UserId);
				bFiringReAuthLoginStatusChanged = false;
			}
			UE_LOG(LogTemp, Display, TEXT("TriggerOnAuthenticateUserCompleteDelegates true"));
		}
		else
		{
			// Verify returned values
			// Create a new user if we don't already have one
			CreateLocalUser(UserPlatformIdStr, handle);
		}

		TimeSinceLastAuth = 0.0f;
		UsersToAuth.Remove(UserPlatformIdStr);
	}

	// Remove the in flight data
	UserAuthRequestsInFlight.Remove(UserPlatformIdStr);
}

void FOnlineIdentityPlayFab::CreateLocalUser(const FString& UserPlatformIdStr, const FPFEntityHandle EntityHandle)
{
	UE_LOG_ONLINE_IDENTITY(Verbose, TEXT("FOnlineIdentityPlayFab::CreateLocalUser"));
	UE_LOG(LogTemp, Display, TEXT("FOnlineIdentityPlayFab::CreateLocalUser"));

	PartyLocalUser* NewPartyLocalUser = nullptr;
	PartyError Err;

	// Create a local user object
	Err = PartyManager::GetSingleton().CreateLocalUser(
		EntityHandle.Get(),				// User id
		&NewPartyLocalUser				// OUT local user object
	);

	if (PARTY_FAILED(Err))
	{
		UE_LOG_ONLINE(Warning, TEXT("FOnlineSubsystemPlayFab PartyManager::CreateLocalUser failed: %s"), *GetPartyErrorMessage(Err));
		UE_LOG(LogTemp, Display, TEXT("FOnlineIdentityPlayFab::CreateLocalUser failed"));
		return;
	}

	// To make FPlayFabUser we need EntityKey for future mapping
	SIZE_T* bufferSizePtr = static_cast<SIZE_T*>(FMemory::Malloc(sizeof(SIZE_T)));
	*bufferSizePtr = 0;
	TSharedPtr<SIZE_T> bufferSize = MakeShareable(bufferSizePtr, [](SIZE_T* P) { FMemory::Free(P); });
	HRESULT hr = FPFEntityGetEntityKeySize(EntityHandle, bufferSize);
	if (FAILED(hr))
	{
		UE_LOG_ONLINE(Warning, TEXT("FOnlineSubsystemPlayFab::CreateLocalUser FPFEntityGetEntityKeySize failed: 0x%x"), hr);
		return;
	}

	TSharedPtr<void> entityKeyBuffer = MakeShareable(FMemory::Malloc(*bufferSize.Get()), [](void* P) { FMemory::Free(P); });
	TSharedPtr<const FPFEntityKey> EntityKeyptr = MakeShareable(new FPFEntityKey);

	hr = FPFEntityGetEntityKey(EntityHandle, *bufferSize.Get(), entityKeyBuffer, EntityKeyptr, nullptr);
	if (FAILED(hr))
	{
		UE_LOG_ONLINE(Warning, TEXT("FOnlineSubsystemPlayFab::CreateLocalUser FPFEntityGetEntityKey failed: 0x%x"), hr);
		return;
	}

	TSharedPtr<FPlayFabUser> NewLocalUser = MakeShared<FPlayFabUser>(UserPlatformIdStr, EntityHandle, EntityKeyptr, NewPartyLocalUser);

	// Store server entity separately from player entities
	if (IsRunningDedicatedServer() && UserPlatformIdStr == TEXT("DedicatedServer"))
	{
		ServerEntity = NewLocalUser;
		UE_LOG_ONLINE_IDENTITY(Verbose, TEXT("FOnlineIdentityPlayFab::CreateLocalUser: Stored server entity (type=%s, id=%s)"), *EntityKeyptr->type, *EntityKeyptr->id);
	}
	else
	{
		LocalPlayFabUsers.Add(NewLocalUser);
	}

	int32 LocalUserNum = IsRunningDedicatedServer() && UserPlatformIdStr == TEXT("DedicatedServer") ? 0 : LocalPlayFabUsers.Num() - 1;
	TriggerOnAuthenticateUserCompleteDelegates(LocalUserNum, true, UserPlatformIdStr, TEXT(""));
	UE_LOG(LogTemp, Display, TEXT("TriggerOnAuthenticateUserCompleteDelegates:true"));

	// Listening to invite is best effort TODO
	OSSPlayFab->GetPlayFabLobbyInterface()->RegisterForInvites_PlayFabMultiplayer(EntityHandle.Get());
}

void FOnlineIdentityPlayFab::RemoveLocalUser(const FString& PlatformUserIdStr)
{
	UE_LOG_ONLINE_IDENTITY(Verbose, TEXT("FOnlineIdentityPlayFab::RemoveLocalUser"));

	if (PlatformUserIdStr.IsEmpty() == false)
	{
		UserAuthRequestsInFlight.Remove(PlatformUserIdStr);
		UsersToAuth.Remove(PlatformUserIdStr);

		// Check if this is the server entity
		if (ServerEntity.IsValid() && ServerEntity->GetPlatformUserId().Compare(PlatformUserIdStr, ESearchCase::IgnoreCase) == 0)
		{
			PartyError Err = PartyManager::GetSingleton().DestroyLocalUser(ServerEntity->GetPartyLocalUser(), nullptr);
			if (PARTY_FAILED(Err))
			{
				UE_LOG_ONLINE(Warning, TEXT("FOnlineSubsystemPlayFab::DestroyLocalUser (server) failed: %s"), *GetPartyErrorMessage(Err));
			}
			OSSPlayFab->GetPlayFabLobbyInterface()->UnregisterForInvites_PlayFabMultiplayer(ServerEntity->GetEntityHandle().Get());
			ServerEntity.Reset();
			bServerAuthenticated = false;
			return;
		}

		for (int32 i = 0; i < LocalPlayFabUsers.Num(); ++i)
		{
			TSharedPtr<FPlayFabUser> LocalUser = LocalPlayFabUsers[i];
			if (LocalUser->GetPlatformUserId().Compare(PlatformUserIdStr, ESearchCase::IgnoreCase) == 0)
			{
				PartyError Err = PartyManager::GetSingleton().DestroyLocalUser(LocalUser->GetPartyLocalUser(), nullptr);
				if (PARTY_FAILED(Err))
				{
					UE_LOG_ONLINE(Warning, TEXT("FOnlineSubsystemPlayFab::DestroyLocalUser failed: %s"), *GetPartyErrorMessage(Err));
				}
				else
				{
					LocalPlayFabUsers.Remove(LocalUser);
				}

				// Stop Listening to invite is best effort
				OSSPlayFab->GetPlayFabLobbyInterface()->UnregisterForInvites_PlayFabMultiplayer(LocalUser->GetEntityHandle().Get());

				break;
			}
		}
	}
}

TSharedPtr<FPlayFabUser> FOnlineIdentityPlayFab::GetPartyLocalUserFromPlatformId(const FUniqueNetId& PlatformNetId)
{
	return GetPartyLocalUserFromPlatformIdString(PlatformNetId.ToString());
}

TSharedPtr<FPlayFabUser> FOnlineIdentityPlayFab::GetPartyLocalUserFromPlatformIdString(const FString& PlatformNetIdStr, int32* Index)
{
	int32 UserIndex = 0;
	if (!PlatformNetIdStr.IsEmpty())
	{
		// Check server entity
		if (ServerEntity.IsValid() && ServerEntity->GetPlatformUserId().Compare(PlatformNetIdStr, ESearchCase::IgnoreCase) == 0)
		{
			if (Index)
			{
				*Index = 0;
			}
			return ServerEntity;
		}

		for (TSharedPtr<FPlayFabUser> LocalUser : LocalPlayFabUsers)
		{
			if (LocalUser->GetPlatformUserId().Compare(PlatformNetIdStr, ESearchCase::IgnoreCase) == 0)
			{
				if (Index)
				{
					*Index = UserIndex;
				}
				return LocalUser;
			}
			++UserIndex;
		}
	}

	if (Index)
	{
		*Index = INDEX_NONE;
	}

	return nullptr;
}

TSharedPtr<FPlayFabUser> FOnlineIdentityPlayFab::GetPartyLocalUserFromEntityIdString(const FString& EntityIdString)
{
	if (EntityIdString.IsEmpty() == false)
	{
		// Check server entity
		if (ServerEntity.IsValid() && ServerEntity->GetEntityId().Compare(EntityIdString, ESearchCase::IgnoreCase) == 0)
		{
			return ServerEntity;
		}

		for (TSharedPtr<FPlayFabUser> LocalUser : LocalPlayFabUsers)
		{
			if (LocalUser->GetEntityId().Compare(EntityIdString, ESearchCase::IgnoreCase) == 0)
			{
				return LocalUser;
			}
		}
	}

	return nullptr;
}

bool FOnlineIdentityPlayFab::IsUserLocal(const PFEntityKey& UserEntityKey)
{
	// Check server entity first
	if (ServerEntity.IsValid())
	{
		const PFEntityKey ServerKey = ServerEntity->GetEntityKey();
		if (FCString::Strcmp(UTF8_TO_TCHAR(ServerKey.id), UTF8_TO_TCHAR(UserEntityKey.id)) == 0 &&
			FCString::Strcmp(UTF8_TO_TCHAR(ServerKey.type), UTF8_TO_TCHAR(UserEntityKey.type)) == 0)
		{
			return true;
		}
	}

	for (TSharedPtr<FPlayFabUser> LocalUser : LocalPlayFabUsers)
	{
		if ((FCString::Strcmp(UTF8_TO_TCHAR(LocalUser->GetEntityKey().id), UTF8_TO_TCHAR(UserEntityKey.id)) == 0) && 
			(FCString::Strcmp(UTF8_TO_TCHAR(LocalUser->GetEntityKey().type), UTF8_TO_TCHAR(UserEntityKey.type)) == 0))
		{
			return true;
		}
	}
	return false;
}

const TArray<PFEntityKey> FOnlineIdentityPlayFab::GetLocalUserEntityKeys() const
{
	TArray<PFEntityKey> EntityKeys;

	for (TSharedPtr<FPlayFabUser> LocalUser : LocalPlayFabUsers)
	{
		if (LocalUser.IsValid())
		{
			EntityKeys.Emplace(LocalUser->GetEntityKey());
		}
	}

	return EntityKeys;
}

PFEntityHandle FOnlineIdentityPlayFab::GetLocalUserEntityHandleFromEntityKey(const PFEntityKey* EntityKey)
{
	PFEntityHandle EntityHandle = nullptr;

	if (EntityKey != nullptr)
	{
		// Check server entity first
		if (ServerEntity.IsValid())
		{
			const PFEntityKey ServerKey = ServerEntity->GetEntityKey();
			if (FCStringAnsi::Strcmp(ServerKey.id, EntityKey->id) == 0 &&
				FCStringAnsi::Strcmp(ServerKey.type, EntityKey->type) == 0)
			{
				return ServerEntity->GetEntityHandle().Get();
			}
		}

		for (const TSharedPtr<FPlayFabUser>& LocalUser : LocalPlayFabUsers)
		{
			if (!LocalUser.IsValid())
			{
				continue;
			}

			const PFEntityKey UserKey = LocalUser->GetEntityKey();
			if (FCStringAnsi::Strcmp(UserKey.id, EntityKey->id) == 0 &&
				FCStringAnsi::Strcmp(UserKey.type, EntityKey->type) == 0)
			{
				EntityHandle = LocalUser->GetEntityHandle().Get();
			}
		}
	}

    return EntityHandle;
}

TSharedPtr<FPlayFabUser> FOnlineIdentityPlayFab::GetPartyLocalUserFromEntityHandle(const PFEntityHandle EntityHandle)
{
	if (EntityHandle != nullptr)
	{
		// Check server entity
		if (ServerEntity.IsValid() && ServerEntity->GetEntityHandle().Get() == EntityHandle)
		{
			return ServerEntity;
		}

		for (const TSharedPtr<FPlayFabUser>& LocalUser : LocalPlayFabUsers)
		{
			if (!LocalUser.IsValid())
			{
				continue;
			}

			const PFEntityHandle UserEntityHandle = LocalUser->GetEntityHandle().Get();
			if (UserEntityHandle == EntityHandle)
			{
				return LocalUser;
			}
		}
	}

	return nullptr;
}

FDelegateHandle FOnlineIdentityPlayFab::AddOnLoginChangedDelegate_Handle(const FOnLoginChangedDelegate& Delegate)
{
	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		return NativeIdentityInterface->AddOnLoginChangedDelegate_Handle(Delegate);
	}

	return FDelegateHandle();
}

void FOnlineIdentityPlayFab::ClearOnLoginChangedDelegate_Handle(FDelegateHandle& Handle)
{
	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		return NativeIdentityInterface->ClearOnLoginChangedDelegate_Handle(Handle);
	}
}

void FOnlineIdentityPlayFab::TriggerOnLoginChangedDelegates(int32 LocalUserNum)
{
	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		return NativeIdentityInterface->TriggerOnLoginChangedDelegates(LocalUserNum);
	}
}

FDelegateHandle FOnlineIdentityPlayFab::AddOnLoginStatusChangedDelegate_Handle(int32 LocalUserNum, const FOnLoginStatusChangedDelegate& Delegate)
{
	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		return NativeIdentityInterface->AddOnLoginStatusChangedDelegate_Handle(LocalUserNum, Delegate);
	}

	return FDelegateHandle();
}

void FOnlineIdentityPlayFab::ClearOnLoginStatusChangedDelegate_Handle(int32 LocalUserNum, FDelegateHandle& Handle)
{
	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		return NativeIdentityInterface->ClearOnLoginStatusChangedDelegate_Handle(LocalUserNum, Handle);
	}
}

void FOnlineIdentityPlayFab::TriggerOnLoginStatusChangedDelegates(int32 LocalUserNum, ELoginStatus::Type OldStatus, ELoginStatus::Type NewStatus, const FUniqueNetId& NewId)
{
	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		return NativeIdentityInterface->TriggerOnLoginStatusChangedDelegates(LocalUserNum, OldStatus, NewStatus, NewId);
	}
}

FDelegateHandle FOnlineIdentityPlayFab::AddOnControllerPairingChangedDelegate_Handle(const FOnControllerPairingChangedDelegate& Delegate)
{
	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		return NativeIdentityInterface->AddOnControllerPairingChangedDelegate_Handle(Delegate);
	}

	return FDelegateHandle();
}

void FOnlineIdentityPlayFab::ClearOnControllerPairingChangedDelegate_Handle(FDelegateHandle& Handle)
{
	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		return NativeIdentityInterface->ClearOnControllerPairingChangedDelegate_Handle(Handle);
	}
}

void FOnlineIdentityPlayFab::TriggerOnControllerPairingChangedDelegates(int LocalUserNum, FControllerPairingChangedUserInfo PreviousUser, FControllerPairingChangedUserInfo NewUser)
{
	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		return NativeIdentityInterface->TriggerOnControllerPairingChangedDelegates(LocalUserNum, PreviousUser, NewUser);
	}
}

FDelegateHandle FOnlineIdentityPlayFab::AddOnLoginCompleteDelegate_Handle(int32 LocalUserNum, const FOnLoginCompleteDelegate& Delegate)
{
	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		return NativeIdentityInterface->AddOnLoginCompleteDelegate_Handle(LocalUserNum, Delegate);
	}

	return FDelegateHandle();
}

void FOnlineIdentityPlayFab::ClearOnLoginCompleteDelegate_Handle(int32 LocalUserNum, FDelegateHandle& Handle)
{
	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		return NativeIdentityInterface->ClearOnLoginCompleteDelegate_Handle(LocalUserNum, Handle);
	}
}

void FOnlineIdentityPlayFab::TriggerOnLoginCompleteDelegates(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error)
{
	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		return NativeIdentityInterface->TriggerOnLoginCompleteDelegates(LocalUserNum, bWasSuccessful, UserId, Error);
	}
}

FDelegateHandle FOnlineIdentityPlayFab::AddOnLogoutCompleteDelegate_Handle(int32 LocalUserNum, const FOnLogoutCompleteDelegate& Delegate)
{
	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		return NativeIdentityInterface->AddOnLogoutCompleteDelegate_Handle(LocalUserNum, Delegate);
	}

	return FDelegateHandle();
}

void FOnlineIdentityPlayFab::ClearOnLogoutCompleteDelegate_Handle(int32 LocalUserNum, FDelegateHandle& Handle)
{
	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		return NativeIdentityInterface->ClearOnLogoutCompleteDelegate_Handle(LocalUserNum, Handle);
	}
}

void FOnlineIdentityPlayFab::TriggerOnLogoutCompleteDelegates(int32 LocalUserNum, bool bWasSuccessful)
{
	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		return NativeIdentityInterface->TriggerOnLogoutCompleteDelegates(LocalUserNum, bWasSuccessful);
	}
}

FDelegateHandle FOnlineIdentityPlayFab::AddOnLoginFlowLogoutDelegate_Handle(const FOnLoginFlowLogoutDelegate& Delegate)
{
	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		return NativeIdentityInterface->AddOnLoginFlowLogoutDelegate_Handle(Delegate);
	}

	return FDelegateHandle();
}

void FOnlineIdentityPlayFab::ClearOnLoginFlowLogoutDelegate_Handle(FDelegateHandle& Handle)
{
	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		return NativeIdentityInterface->ClearOnLoginFlowLogoutDelegate_Handle(Handle);
	}
}

void FOnlineIdentityPlayFab::TriggerOnLoginFlowLogoutDelegates(const TArray<FString>& LoginDomains)
{
	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		return NativeIdentityInterface->TriggerOnLoginFlowLogoutDelegates(LoginDomains);
	}
}

PartyLocalUser* FOnlineIdentityPlayFab::GetFirstPartyLocalUser()
{
	if (LocalPlayFabUsers.Num() > 0)
	{
		return LocalPlayFabUsers[0]->GetPartyLocalUser();
	}

	return nullptr;
}

void FPlayFabUser::UpdateEntityToken(const FString& NewEntityToken)
{
	UE_LOG_ONLINE_IDENTITY(Verbose, TEXT("FOnlineIdentityPlayFab::UpdateEntityToken"));

	if (NewEntityToken.IsEmpty() == false)
	{
		if (LocalUser)
		{
			PartyError Err = LocalUser->UpdateEntityToken(TCHAR_TO_UTF8(*NewEntityToken));
			if (PARTY_FAILED(Err))
			{
				UE_LOG_ONLINE(Warning, TEXT("FPlayFabPartyUser::UpdateEntityToken failed: %s"), *GetPartyErrorMessage(Err));
			}
			else
			{
				EntityToken = NewEntityToken;
				SetNewEntityTokenUpdateTime();
			}
		}
	}
}

void FPlayFabUser::SetNewEntityTokenUpdateTime()
{
	EntityTokenUpdateTime = FDateTime::Now() + FTimespan::FromHours(12.0f);
}