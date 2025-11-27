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

#if defined(USE_PFCORE_SDK)
#include "PFCore.h"
#include "PFAuthentication.h"
#include "PFEntity.h"
#include "PFServiceConfig.h"
#include "PFLocalUser.h"
#endif // USE_PFCORE_SDK

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

	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		return NativeIdentityInterface->GetLoginStatus(LocalUserNum);
	}

	return ELoginStatus::NotLoggedIn;
}

ELoginStatus::Type FOnlineIdentityPlayFab::GetLoginStatus(const FUniqueNetId& UserId) const
{
	UE_LOG_ONLINE_IDENTITY(Verbose, TEXT("FOnlineIdentityPlayFab::GetLoginStatus"));

	OSS_PLAYFAB_GET_NATIVE_IDENTITY_INTERFACE
	{
		return NativeIdentityInterface->GetLoginStatus(UserId);
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
		return NativeIdentityInterface->GetPlayerNickname(UserId);
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

	UsersToAuth.Empty();
	UserAuthRequestsInFlight.Empty();
}

bool FOnlineIdentityPlayFab::AuthenticateUser(const FString& PlatformUserIdStr)
{
	// Only if not already in flight for this user
	if (UserAuthRequestsInFlight.Contains(PlatformUserIdStr))
	{
		return false;
	}

	const bool bAppliedPlatformData = ApplyPlatformHTTPRequestData(PlatformUserIdStr, API::Url, API::PostVerb);

	if (bAppliedPlatformData && !UserAuthRequestsInFlight.Contains(PlatformUserIdStr))
	{
		UserAuthRequestData MetaData;
		UserAuthRequestsInFlight.Add(PlatformUserIdStr, MetaData);
	}

	return bAppliedPlatformData;
}

#if defined(OSS_PLAYFAB_WIN64)
void FOnlineIdentityPlayFab::FinishRequestSteam(const FString& PlatformUserIdStr, TSharedPtr<FJsonObject> RequestBodyJson, FPFServiceConfigHandle ServiceConfigHandle)
{
	// TODO modify to use LocalUserHandle
	FString SteamToken = RequestBodyJson->GetStringField(TEXT("SteamTicket"));
	auto strSteamToken = StringCast<UTF8CHAR>(*SteamToken);
	bool bTicketIsServiceSpecific = true;
	TSharedPtr<const bool> ticketIsServiceSpecific = MakeShareable(new bool(bTicketIsServiceSpecific));
	FPFAuthenticationLoginWithSteamRequest request = {
		.createAccount = true,
		.steamTicket = SteamToken,
		.ticketIsServiceSpecific = ticketIsServiceSpecific,
	};

	FPFAuthenticationLoginWithSteamAsync(
		ServiceConfigHandle,
		request,
		FOnPFAuthenticationLoginCompleteDelegate::CreateLambda([this, PlatformUserIdStr](const FPFAuthenticationLoginResult* lognResults, FPFEntityHandle* entityHandle, bool bWasSuccessful)
			{
				// TODO check login results
				Auth_PFAuthRequestComplete(bWasSuccessful, PlatformUserIdStr, *entityHandle);
				UE_LOG(LogTemp, Display, TEXT("LoginWithSteam Complete"));
			})
	);
}
#endif // OSS_PLAYFAB_WIN64

#if defined(OSS_PLAYFAB_GDK_SUPPORT)
void FOnlineIdentityPlayFab::FinishRequestGDK(const FString& PlatformUserIdStr, FPFServiceConfigHandle ServiceConfigHandle)
{
	int64 xuid = FCString::Atoi64(*PlatformUserIdStr);
	FGDKUserHandle XboxUser = IGDKRuntimeModule::Get().GetUserHandleByXUserId(xuid);

	if (!FPFLocalUserCreateHandleWithXboxUser(ServiceConfigHandle, XboxUser, nullptr, LocalUserHandle))
	{
		UE_LOG_ONLINE(Error, TEXT("FOnlineIdentityPlayFab:FPFLocalUserCreateHandleWithXboxUser was unable to create PlayFab LocalUser"));
		return;
	}

	FPFLocalUserLoginAsync(
		LocalUserHandle,
		true,
		FOnPFAuthenticationLoginCompleteDelegate::CreateLambda([this, PlatformUserIdStr](const FPFAuthenticationLoginResult* lognResults, FPFEntityHandle* entityHandle, bool bWasSuccessful)
			{
				Auth_PFAuthRequestComplete(bWasSuccessful, PlatformUserIdStr, *entityHandle);
				UE_LOG(LogTemp, Display, TEXT("LoginWithXbox Complete"));
			})
	);
}
#endif // OSS_PLAYFAB_GDK_SUPPORT

// Called after platform has appended its headers/body
void FOnlineIdentityPlayFab::FinishRequest(bool bPlatformDataSuccess, const FString& PlatformUserIdStr, TMap<FString, FString> PlatformHeaders, TSharedPtr<FJsonObject> RequestBodyJson)
{
	if (bPlatformDataSuccess)
	{
		if (!RequestBodyJson.IsValid())
		{
			UE_LOG_ONLINE(Error, TEXT("FOnlineIdentityPlayFab::FinishRequest: RequestBodyJson is null"));
			return;
		}

#if defined(USE_PFCORE_SDK)
		
		FPFInitialize();

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
			return;
		}

#ifdef OSS_PLAYFAB_SWITCH
		// TODO modify to use LocalUserHandle
		PFAuthenticationLoginWithNintendoServiceAccountRequest request = {};
		request.createAccount = true;		
		FPFAuthenticationLoginWithNintendoServiceAccountAsync(
			m_serviceConfigHandle,
			request,
			FOnLoginWithNintendoServiceAccountDelegate::CreateLambda([this, PlatformUserIdStr](bool bWasSuccessful, const PFAuthenticationLoginResult* lognResults, PFEntityHandle* entityHandle)
				{
					Auth_PFAuthRequestComplete(bWasSuccessful, PlatformUserIdStr, *entityHandle);
					UE_LOG(LogTemp, Display, TEXT("LoginWithNintendoServiceAccount Complete"));
				})
		);
#elif defined(OSS_PLAYFAB_WIN64)
#if defined(OSS_PLAYFAB_GDK_SUPPORT)
		if (IsNativePlatformSubsystemGDK())
		{
			FinishRequestGDK(PlatformUserIdStr, m_serviceConfigHandle);
		}
		else
		{
			FinishRequestSteam(PlatformUserIdStr, RequestBodyJson, m_serviceConfigHandle);
		}
#else
		FinishRequestSteam(PlatformUserIdStr, RequestBodyJson, m_serviceConfigHandle);
#endif // OSS_PLAYFAB_GDK_SUPPORT
#elif defined(OSS_PLAYFAB_PLAYSTATION)
		
#elif defined(OSS_PLAYFAB_GDK)
		FinishRequestGDK(PlatformUserIdStr, m_serviceConfigHandle);
#endif // OSS_PLAYFAB_SWITCH
#else // USE_PFCORE_SDK
			// PlayFab auth request
		FHttpRequestPtr httpRequest = FHttpModule::Get().CreateRequest();

		UserAuthRequestData* RequestInFlight = GetUserAuthRequestData(PlatformUserIdStr);
		if (RequestInFlight != nullptr)
		{
			RequestInFlight->m_HTTPRequest = httpRequest;

			RequestInFlight->m_HTTPRequest->OnProcessRequestComplete().BindRaw(this, &FOnlineIdentityPlayFab::Auth_HttpRequestComplete);
			FString TitleIdStr = OSSPlayFab->GetAppId();

			// Add all platform headers
			for (const auto& kvPair : PlatformHeaders)
			{
				RequestInFlight->m_HTTPRequest->SetHeader(kvPair.Key, kvPair.Value);
			}
			// Build up the rest of the request body
			RequestBodyJson->SetBoolField(TEXT("CreateAccount"), true);
			RequestBodyJson->SetStringField(TEXT("TitleId"), TitleIdStr);

			// Serialize request body
			FString RequestBodySerialized;
			TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBodySerialized);
			FJsonSerializer::Serialize(RequestBodyJson.ToSharedRef(), Writer);

#ifdef OSS_PLAYFAB_SWITCH
			const FString LoginApi = "LoginWithNintendoServiceAccount";
#elif defined(OSS_PLAYFAB_PLAYSTATION)
			const FString LoginApi = "LoginWithPSN";
#endif // OSS_PLAYFAB_SWITCH

			const FString URI = FString::Printf(TEXT("https://%s.playfabapi.com/Client/%s"), *TitleIdStr, *LoginApi);

			RequestInFlight->m_HTTPRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
			RequestInFlight->m_HTTPRequest->SetURL(URI);
			RequestInFlight->m_HTTPRequest->SetVerb(API::PostVerb);
			RequestInFlight->m_HTTPRequest->SetContentAsString(RequestBodySerialized); // gets copied internally
			RequestInFlight->m_HTTPRequest->ProcessRequest();
		}
#endif // USE_PFCORE_SDK
	}
	else
	{
		// Remove the in flight data
		UserAuthRequestsInFlight.Remove(PlatformUserIdStr);
	}
}

#if defined(USE_PFCORE_SDK)
void FOnlineIdentityPlayFab::Auth_PFAuthRequestComplete(bool bSucceeded, const FString& UserPlatformIdStr, FPFEntityHandle handle)
{
	UE_LOG(LogTemp, Display, TEXT("Auth_PFAuthRequestComplete In"));
	if (bSucceeded)
	{
		int32 Index;
		TSharedPtr<FPlayFabUser> LocalUser = GetPartyLocalUserFromPlatformIdString(UserPlatformIdStr, &Index);
		if (LocalUser)
		{
			LocalUser->SetNewEntityTokenUpdateTime();
			TriggerOnAuthenticateUserCompleteDelegates(Index, true, UserPlatformIdStr, TEXT(""));
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
#else // USE_PFCORE_SDK

void FOnlineIdentityPlayFab::Auth_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	const FString& PlatformUserIdStr = GetUserPlatformIdStrFromRequest(HttpRequest);

	FString ResponseStr;
	FString ErrorStr;

	if (bSucceeded && HttpResponse.IsValid())
	{
		ResponseStr = HttpResponse->GetContentAsString();

		// Deserialize response
		TSharedPtr<FJsonObject> HttpResponseJSON = nullptr;
		TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(ResponseStr);
		if (FJsonSerializer::Deserialize(JsonReader, HttpResponseJSON))
		{
			const TSharedPtr<FJsonObject>* JsonData = nullptr;
			if (HttpResponseJSON->TryGetObjectField(TEXT("data"), JsonData))
			{
				const TSharedPtr<FJsonObject>* JsonEntityTokenData = nullptr;
				if ((*JsonData)->TryGetObjectField(TEXT("EntityToken"), JsonEntityTokenData))
				{
					FString EntityTokenStr;
					FString TokenExpirationStr;

					if ((*JsonEntityTokenData)->TryGetStringField(TEXT("EntityToken"), EntityTokenStr) && (*JsonEntityTokenData)->TryGetStringField(TEXT("TokenExpiration"), TokenExpirationStr))
					{
						const TSharedPtr<FJsonObject>* JsonEntity = nullptr;
						if ((*JsonEntityTokenData)->TryGetObjectField(TEXT("Entity"), JsonEntity))
						{
							FString EntityIdStr, EntityTypeStr;
							if ((*JsonEntity)->TryGetStringField(TEXT("Id"), EntityIdStr) && (*JsonEntity)->TryGetStringField(TEXT("Type"), EntityTypeStr))
							{
								UE_LOG_ONLINE(
									Verbose,
									TEXT("[FOnlineIdentityPlayFab::Auth_HttpRequestComplete] Platform User %s authenticated with EntityId %s, Token %s, and Expiration %s"),
									*PlatformUserIdStr,
									*EntityIdStr,
									*EntityTokenStr,
									*TokenExpirationStr
								);

								int32 Index;
								TSharedPtr<FPlayFabUser> LocalUser = GetPartyLocalUserFromPlatformIdString(PlatformUserIdStr, &Index);
								if (LocalUser)
								{
									// Update an existing user if we already have one
									LocalUser->UpdateEntityToken(EntityTokenStr);
									TriggerOnAuthenticateUserCompleteDelegates(Index, true, PlatformUserIdStr, TEXT(""));
								}
								else
								{
									// Obtain the SessionTicket from the PlayFab auth response for use in any subsequent requests demanding the X-Authorization header.
									FString SessionTicketStr = "";
									if ((*JsonData)->TryGetStringField(TEXT("SessionTicket"), SessionTicketStr) == false)
									{
										ErrorStr = SessionTicketStr.IsEmpty() ? TEXT("SessionTicket data is empty") : TEXT("Failed to parse SessionTicket data");

										UE_LOG_ONLINE(Error, TEXT("[FOnlineIdentityPlayFab::Auth_HttpRequestComplete] %s"), *ErrorStr);
										TriggerOnAuthenticateUserCompleteDelegates(0, false, PlatformUserIdStr, ErrorStr);
									}

									FString PlayFabIdStr = "";
									if ((*JsonData)->TryGetStringField(TEXT("PlayFabId"), PlayFabIdStr) == false)
									{
										ErrorStr = PlayFabIdStr.IsEmpty() ? TEXT("PlayFabId data is empty") : TEXT("Failed to parse PlayFabId data");

										UE_LOG_ONLINE(Error, TEXT("[FOnlineIdentityPlayFab::Auth_HttpRequestComplete] %s"), *ErrorStr);
										TriggerOnAuthenticateUserCompleteDelegates(0, false, PlatformUserIdStr, ErrorStr);
									}

									// Create a new user if we don't already have one
									CreateLocalUser(PlatformUserIdStr, EntityIdStr, EntityTypeStr, SessionTicketStr, EntityTokenStr, TokenExpirationStr, PlayFabIdStr);
								}

								TimeSinceLastAuth = 0.0f;
								UsersToAuth.Remove(PlatformUserIdStr);
							}
							else
							{
								// MS_ATG_PNF: in error cases, the user will re-auth on the next attempt
								UE_LOG_ONLINE(Error, TEXT("[FOnlineIdentityPlayFab::Auth_HttpRequestComplete] Failed to parse EntityId data"));
								TriggerOnAuthenticateUserCompleteDelegates(0, false, PlatformUserIdStr, TEXT("Failed to parse EntityId data"));
							}
						}
						else
						{
							// MS_ATG_PNF: in error cases, the user will re-auth on the next attempt
							UE_LOG_ONLINE(Error, TEXT("[FOnlineIdentityPlayFab::Auth_HttpRequestComplete] Failed to parse Entity data"));
							TriggerOnAuthenticateUserCompleteDelegates(0, false, PlatformUserIdStr, TEXT("Failed to parse Entity data"));
						}
					}
					else
					{
						// MS_ATG_PNF: in error cases, the user will re-auth on the next attempt
						UE_LOG_ONLINE(Error, TEXT("[FOnlineIdentityPlayFab::Auth_HttpRequestComplete] Failed to parse EntityToken data"));
						TriggerOnAuthenticateUserCompleteDelegates(0, false, PlatformUserIdStr, TEXT("Failed to parse EntityToken data"));
					}
				}
				else
				{
					// MS_ATG_PNF: in error cases, the user will re-auth on the next attempt
					UE_LOG_ONLINE(Error, TEXT("[FOnlineIdentityPlayFab::Auth_HttpRequestComplete] Failed to parse EntityToken data"));
					TriggerOnAuthenticateUserCompleteDelegates(0, false, PlatformUserIdStr, TEXT("Failed to parse EntityToken data"));
				}
			}
			else
			{
				// MS_ATG_PNF: in error cases, the user will re-auth on the next attempt
				UE_LOG_ONLINE(Error, TEXT("[FOnlineIdentityPlayFab::Auth_HttpRequestComplete] Failed to parse JSON data"));
				TriggerOnAuthenticateUserCompleteDelegates(0, false, PlatformUserIdStr, TEXT("Failed to parse JSON data"));
			}
		}
		else
		{
			// MS_ATG_PNF: in error cases, the user will re-auth on the next attempt
			UE_LOG_ONLINE(Error, TEXT("[FOnlineIdentityPlayFab::Auth_HttpRequestComplete] Failed to deserialize response"));
			TriggerOnAuthenticateUserCompleteDelegates(0, false, PlatformUserIdStr, TEXT("Failed to deserialize response"));
		}
	}

	// Remove the in flight data
	UserAuthRequestsInFlight.Remove(PlatformUserIdStr);
}
#endif // USE_PFCORE_SDK

#if defined(USE_PFCORE_SDK)
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
	// TODO use TArray instead
	TSharedPtr<SIZE_T> bufferSize = MakeShareable(new SIZE_T(0));
	HRESULT hr = FPFEntityGetEntityKeySize(EntityHandle, bufferSize);
	if (FAILED(hr))
	{
		UE_LOG_ONLINE(Warning, TEXT("FOnlineSubsystemPlayFab::CreateLocalUser FPFEntityGetEntityKeySize failed: 0x%x"), hr);
		return;
	}

	TSharedPtr<void> entityKeyBuffer = MakeShareable(new char[*bufferSize.Get()]);
	TSharedPtr<const FPFEntityKey> EntityKeyptr = MakeShareable(new FPFEntityKey);

	hr = FPFEntityGetEntityKey(EntityHandle, *bufferSize.Get(), entityKeyBuffer, EntityKeyptr, nullptr);
	if (FAILED(hr))
	{
		UE_LOG_ONLINE(Warning, TEXT("FOnlineSubsystemPlayFab::CreateLocalUser FPFEntityGetEntityKey failed: 0x%x"), hr);
		return;
	}

	TSharedPtr<FPlayFabUser> NewLocalUser = MakeShared<FPlayFabUser>(UserPlatformIdStr, EntityHandle, EntityKeyptr, NewPartyLocalUser);

	int32 LocalUserNum = LocalPlayFabUsers.Add(NewLocalUser);
	TriggerOnAuthenticateUserCompleteDelegates(LocalUserNum, true, UserPlatformIdStr, TEXT(""));
	UE_LOG(LogTemp, Display, TEXT("TriggerOnAuthenticateUserCompleteDelegates:true"));

	// Listening to invite is best effort TODO
	OSSPlayFab->GetPlayFabLobbyInterface()->RegisterForInvites_PlayFabMultiplayer(EntityHandle.Get());
}
#else // USE_PFCORE_SDK

void FOnlineIdentityPlayFab::CreateLocalUser(const FString& PlatformUserIdStr, const FString& EntityId, const FString& EntityType, const FString& SessionTicket, const FString& EntityToken, const FString& TokenExpiration, const FString& PlayFabId)
{
	UE_LOG_ONLINE_IDENTITY(Verbose, TEXT("FOnlineIdentityPlayFab::CreateLocalUser"));

	PartyLocalUser* NewPartyLocalUser = nullptr;
	PartyError Err;

	// Create a local user object
	Err = PartyManager::GetSingleton().CreateLocalUser(
		TCHAR_TO_UTF8(*EntityId),		// User id
		TCHAR_TO_UTF8(*EntityToken),	// User entity token
		&NewPartyLocalUser				// OUT local user object
	);

	if (PARTY_FAILED(Err))
	{
		UE_LOG_ONLINE(Warning, TEXT("FOnlineSubsystemPlayFab PartyManager::CreateLocalUser failed: %s"), *GetPartyErrorMessage(Err));
		return;
	}
	
	TSharedPtr<FPlayFabUser> NewLocalUser = MakeShared<FPlayFabUser>(PlatformUserIdStr, EntityToken, EntityId, EntityType, SessionTicket, NewPartyLocalUser, PlayFabId);

	PFEntityKey EntityKey = NewLocalUser->GetEntityKey();
	HRESULT hr = PFMultiplayerSetEntityToken(
		OSSPlayFab->GetMultiplayerHandle(), // Multiplayer Handle 
		&EntityKey,							// EntityKey
		TCHAR_TO_UTF8(*EntityToken)  		// User entity token
	);

	if (FAILED(hr))
	{
		UE_LOG_ONLINE(Warning, TEXT("FOnlineSubsystemPlayFab MultiplayerManager::GetSingleton().SetEntityToken failed: 0x%x"), hr);
		PartyManager::GetSingleton().DestroyLocalUser(NewPartyLocalUser, nullptr);
		return;
	}
	int32 LocalUserNum = LocalPlayFabUsers.Add(NewLocalUser);
	TriggerOnAuthenticateUserCompleteDelegates(LocalUserNum, true, PlatformUserIdStr, TEXT(""));

	// Listening to invite is best effort
	OSSPlayFab->GetPlayFabLobbyInterface()->RegisterForInvites_PlayFabMultiplayer(EntityKey);
}
#endif //USE_PFCORE_SDK

void FOnlineIdentityPlayFab::RemoveLocalUser(const FString& PlatformUserIdStr)
{
	UE_LOG_ONLINE_IDENTITY(Verbose, TEXT("FOnlineIdentityPlayFab::RemoveLocalUser"));

	if (PlatformUserIdStr.IsEmpty() == false)
	{
		UserAuthRequestsInFlight.Remove(PlatformUserIdStr);
		UsersToAuth.Remove(PlatformUserIdStr);

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
				// TODO: Unregister from invites using EntityHandle
				//OSSPlayFab->GetPlayFabLobbyInterface()->UnregisterForInvites_PlayFabMultiplayer(LocalUser->GetEntityKey());

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

#if defined(USE_PFCORE_SDK)
PFEntityHandle FOnlineIdentityPlayFab::GetLocalUserEntityHandleFromEntityKey(const PFEntityKey* EntityKey)
{
	PFEntityHandle EntityHandle = nullptr;

	if (EntityKey != nullptr)
	{
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
#endif // USE_PFCORE_SDK

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