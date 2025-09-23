// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#include "CoreMinimal.h"
#include "Async/AsyncWork.h"
#include "Async/Async.h"
#include "XAsyncTaskQueueHelpers.h"
#include "XAsyncTaskManager.h"
#include "XAsyncTask.h"
#include "PFEntity.h"
#include "PFServiceConfig.h"
#include "Generated/PFAuthenticationUnrealTypes.h"
#include "Generated/PFAuthenticationTypeConverters.h"
THIRD_PARTY_INCLUDES_START
#include <playfab/core/PFEntity.h>
#include <playfab/core/PFAuthentication.h>
THIRD_PARTY_INCLUDES_END

#if 0

class PLAYFABCORE_API FPFAuthenticationLoginWithAndroidDeviceIDAsyncTask : public FXAsyncTask
{
public:
	FPFAuthenticationLoginWithAndroidDeviceIDAsyncTask(
		FPFServiceConfigHandle serviceConfigHandle,
		const FPFAuthenticationLoginWithAndroidDeviceIDRequest request,
		FOnPFAuthenticationLoginCompleteDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFServiceConfigHandle serviceConfigHandle;

	const FPFAuthenticationLoginWithAndroidDeviceIDRequest request;

	FOnPFAuthenticationLoginCompleteDelegate delegate;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC

class PLAYFABCORE_API FPFAuthenticationLoginWithAppleAsyncTask : public FXAsyncTask
{
public:
	FPFAuthenticationLoginWithAppleAsyncTask(
		FPFServiceConfigHandle serviceConfigHandle,
		const FPFAuthenticationLoginWithAppleRequest request,
		FOnPFAuthenticationLoginCompleteDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFServiceConfigHandle serviceConfigHandle;

	const FPFAuthenticationLoginWithAppleRequest request;

	FOnPFAuthenticationLoginCompleteDelegate delegate;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK

class PLAYFABCORE_API FPFAuthenticationLoginWithBattleNetAsyncTask : public FXAsyncTask
{
public:
	FPFAuthenticationLoginWithBattleNetAsyncTask(
		FPFServiceConfigHandle serviceConfigHandle,
		const FPFAuthenticationLoginWithBattleNetRequest request,
		FOnPFAuthenticationLoginCompleteDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFServiceConfigHandle serviceConfigHandle;

	const FPFAuthenticationLoginWithBattleNetRequest request;

	FOnPFAuthenticationLoginCompleteDelegate delegate;
};

#endif


class PLAYFABCORE_API FPFAuthenticationLoginWithCustomIDAsyncTask : public FXAsyncTask
{
public:
	FPFAuthenticationLoginWithCustomIDAsyncTask(
		FPFServiceConfigHandle serviceConfigHandle,
		const FPFAuthenticationLoginWithCustomIDRequest request,
		FOnPFAuthenticationLoginCompleteDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFServiceConfigHandle serviceConfigHandle;

	const FPFAuthenticationLoginWithCustomIDRequest request;

	FOnPFAuthenticationLoginCompleteDelegate delegate;
};


#if 0

class PLAYFABCORE_API FPFAuthenticationLoginWithEmailAddressAsyncTask : public FXAsyncTask
{
public:
	FPFAuthenticationLoginWithEmailAddressAsyncTask(
		FPFServiceConfigHandle serviceConfigHandle,
		const FPFAuthenticationLoginWithEmailAddressRequest request,
		FOnPFAuthenticationLoginCompleteDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFServiceConfigHandle serviceConfigHandle;

	const FPFAuthenticationLoginWithEmailAddressRequest request;

	FOnPFAuthenticationLoginCompleteDelegate delegate;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_IOS

class PLAYFABCORE_API FPFAuthenticationLoginWithFacebookAsyncTask : public FXAsyncTask
{
public:
	FPFAuthenticationLoginWithFacebookAsyncTask(
		FPFServiceConfigHandle serviceConfigHandle,
		const FPFAuthenticationLoginWithFacebookRequest request,
		FOnPFAuthenticationLoginCompleteDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFServiceConfigHandle serviceConfigHandle;

	const FPFAuthenticationLoginWithFacebookRequest request;

	FOnPFAuthenticationLoginCompleteDelegate delegate;
};

#endif

#if 0

class PLAYFABCORE_API FPFAuthenticationLoginWithFacebookInstantGamesIdAsyncTask : public FXAsyncTask
{
public:
	FPFAuthenticationLoginWithFacebookInstantGamesIdAsyncTask(
		FPFServiceConfigHandle serviceConfigHandle,
		const FPFAuthenticationLoginWithFacebookInstantGamesIdRequest request,
		FOnPFAuthenticationLoginCompleteDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFServiceConfigHandle serviceConfigHandle;

	const FPFAuthenticationLoginWithFacebookInstantGamesIdRequest request;

	FOnPFAuthenticationLoginCompleteDelegate delegate;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_IOS

class PLAYFABCORE_API FPFAuthenticationLoginWithGameCenterAsyncTask : public FXAsyncTask
{
public:
	FPFAuthenticationLoginWithGameCenterAsyncTask(
		FPFServiceConfigHandle serviceConfigHandle,
		const FPFAuthenticationLoginWithGameCenterRequest request,
		FOnPFAuthenticationLoginCompleteDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFServiceConfigHandle serviceConfigHandle;

	const FPFAuthenticationLoginWithGameCenterRequest request;

	FOnPFAuthenticationLoginCompleteDelegate delegate;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_ANDROID

class PLAYFABCORE_API FPFAuthenticationLoginWithGoogleAccountAsyncTask : public FXAsyncTask
{
public:
	FPFAuthenticationLoginWithGoogleAccountAsyncTask(
		FPFServiceConfigHandle serviceConfigHandle,
		const FPFAuthenticationLoginWithGoogleAccountRequest request,
		FOnPFAuthenticationLoginCompleteDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFServiceConfigHandle serviceConfigHandle;

	const FPFAuthenticationLoginWithGoogleAccountRequest request;

	FOnPFAuthenticationLoginCompleteDelegate delegate;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_ANDROID

class PLAYFABCORE_API FPFAuthenticationLoginWithGooglePlayGamesServicesAsyncTask : public FXAsyncTask
{
public:
	FPFAuthenticationLoginWithGooglePlayGamesServicesAsyncTask(
		FPFServiceConfigHandle serviceConfigHandle,
		const FPFAuthenticationLoginWithGooglePlayGamesServicesRequest request,
		FOnPFAuthenticationLoginCompleteDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFServiceConfigHandle serviceConfigHandle;

	const FPFAuthenticationLoginWithGooglePlayGamesServicesRequest request;

	FOnPFAuthenticationLoginCompleteDelegate delegate;
};

#endif

#if 0

class PLAYFABCORE_API FPFAuthenticationLoginWithIOSDeviceIDAsyncTask : public FXAsyncTask
{
public:
	FPFAuthenticationLoginWithIOSDeviceIDAsyncTask(
		FPFServiceConfigHandle serviceConfigHandle,
		const FPFAuthenticationLoginWithIOSDeviceIDRequest request,
		FOnPFAuthenticationLoginCompleteDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFServiceConfigHandle serviceConfigHandle;

	const FPFAuthenticationLoginWithIOSDeviceIDRequest request;

	FOnPFAuthenticationLoginCompleteDelegate delegate;
};

#endif

#if 0

class PLAYFABCORE_API FPFAuthenticationLoginWithKongregateAsyncTask : public FXAsyncTask
{
public:
	FPFAuthenticationLoginWithKongregateAsyncTask(
		FPFServiceConfigHandle serviceConfigHandle,
		const FPFAuthenticationLoginWithKongregateRequest request,
		FOnPFAuthenticationLoginCompleteDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFServiceConfigHandle serviceConfigHandle;

	const FPFAuthenticationLoginWithKongregateRequest request;

	FOnPFAuthenticationLoginCompleteDelegate delegate;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_NINTENDO_SWITCH

class PLAYFABCORE_API FPFAuthenticationLoginWithNintendoServiceAccountAsyncTask : public FXAsyncTask
{
public:
	FPFAuthenticationLoginWithNintendoServiceAccountAsyncTask(
		FPFServiceConfigHandle serviceConfigHandle,
		const FPFAuthenticationLoginWithNintendoServiceAccountRequest request,
		FOnPFAuthenticationLoginCompleteDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFServiceConfigHandle serviceConfigHandle;

	const FPFAuthenticationLoginWithNintendoServiceAccountRequest request;

	FOnPFAuthenticationLoginCompleteDelegate delegate;
};

#endif

#if 0

class PLAYFABCORE_API FPFAuthenticationLoginWithNintendoSwitchDeviceIdAsyncTask : public FXAsyncTask
{
public:
	FPFAuthenticationLoginWithNintendoSwitchDeviceIdAsyncTask(
		FPFServiceConfigHandle serviceConfigHandle,
		const FPFAuthenticationLoginWithNintendoSwitchDeviceIdRequest request,
		FOnPFAuthenticationLoginCompleteDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFServiceConfigHandle serviceConfigHandle;

	const FPFAuthenticationLoginWithNintendoSwitchDeviceIdRequest request;

	FOnPFAuthenticationLoginCompleteDelegate delegate;
};

#endif


class PLAYFABCORE_API FPFAuthenticationLoginWithOpenIdConnectAsyncTask : public FXAsyncTask
{
public:
	FPFAuthenticationLoginWithOpenIdConnectAsyncTask(
		FPFServiceConfigHandle serviceConfigHandle,
		const FPFAuthenticationLoginWithOpenIdConnectRequest request,
		FOnPFAuthenticationLoginCompleteDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFServiceConfigHandle serviceConfigHandle;

	const FPFAuthenticationLoginWithOpenIdConnectRequest request;

	FOnPFAuthenticationLoginCompleteDelegate delegate;
};


#if 0

class PLAYFABCORE_API FPFAuthenticationLoginWithPlayFabAsyncTask : public FXAsyncTask
{
public:
	FPFAuthenticationLoginWithPlayFabAsyncTask(
		FPFServiceConfigHandle serviceConfigHandle,
		const FPFAuthenticationLoginWithPlayFabRequest request,
		FOnPFAuthenticationLoginCompleteDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFServiceConfigHandle serviceConfigHandle;

	const FPFAuthenticationLoginWithPlayFabRequest request;

	FOnPFAuthenticationLoginCompleteDelegate delegate;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_4 || HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_5

class PLAYFABCORE_API FPFAuthenticationLoginWithPSNAsyncTask : public FXAsyncTask
{
public:
	FPFAuthenticationLoginWithPSNAsyncTask(
		FPFServiceConfigHandle serviceConfigHandle,
		const FPFAuthenticationLoginWithPSNRequest request,
		FOnPFAuthenticationLoginCompleteDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFServiceConfigHandle serviceConfigHandle;

	const FPFAuthenticationLoginWithPSNRequest request;

	FOnPFAuthenticationLoginCompleteDelegate delegate;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

class PLAYFABCORE_API FPFAuthenticationLoginWithSteamAsyncTask : public FXAsyncTask
{
public:
	FPFAuthenticationLoginWithSteamAsyncTask(
		FPFServiceConfigHandle serviceConfigHandle,
		const FPFAuthenticationLoginWithSteamRequest request,
		FOnPFAuthenticationLoginCompleteDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFServiceConfigHandle serviceConfigHandle;

	const FPFAuthenticationLoginWithSteamRequest request;

	FOnPFAuthenticationLoginCompleteDelegate delegate;
};

#endif

#if 0

class PLAYFABCORE_API FPFAuthenticationLoginWithTwitchAsyncTask : public FXAsyncTask
{
public:
	FPFAuthenticationLoginWithTwitchAsyncTask(
		FPFServiceConfigHandle serviceConfigHandle,
		const FPFAuthenticationLoginWithTwitchRequest request,
		FOnPFAuthenticationLoginCompleteDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFServiceConfigHandle serviceConfigHandle;

	const FPFAuthenticationLoginWithTwitchRequest request;

	FOnPFAuthenticationLoginCompleteDelegate delegate;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

class PLAYFABCORE_API FPFAuthenticationLoginWithXboxAsyncTask : public FXAsyncTask
{
public:
	FPFAuthenticationLoginWithXboxAsyncTask(
		FPFServiceConfigHandle serviceConfigHandle,
		const FPFAuthenticationLoginWithXboxRequest request,
		FOnPFAuthenticationLoginCompleteDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFServiceConfigHandle serviceConfigHandle;

	const FPFAuthenticationLoginWithXboxRequest request;

	FOnPFAuthenticationLoginCompleteDelegate delegate;
};

#endif

#if 0

class PLAYFABCORE_API FPFAuthenticationRegisterPlayFabUserAsyncTask : public FXAsyncTask
{
public:
	FPFAuthenticationRegisterPlayFabUserAsyncTask(
		FPFServiceConfigHandle serviceConfigHandle,
		const FPFAuthenticationRegisterPlayFabUserRequest request,
		FOnRegisterPlayFabUserDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFServiceConfigHandle serviceConfigHandle;

	const FPFAuthenticationRegisterPlayFabUserRequest request;

	FOnRegisterPlayFabUserDelegate delegate;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK

class PLAYFABCORE_API FPFAuthenticationServerLoginWithAndroidDeviceIDAsyncTask : public FXAsyncTask
{
public:
	FPFAuthenticationServerLoginWithAndroidDeviceIDAsyncTask(
		FPFServiceConfigHandle serviceConfigHandle,
		const FString secretKey,
		const FPFAuthenticationServerLoginWithAndroidDeviceIDRequest request,
		FOnPFAuthenticationServerLoginCompleteDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFServiceConfigHandle serviceConfigHandle;

	const FString secretKey;

	const FPFAuthenticationServerLoginWithAndroidDeviceIDRequest request;

	FOnPFAuthenticationServerLoginCompleteDelegate delegate;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK

class PLAYFABCORE_API FPFAuthenticationServerLoginWithBattleNetAsyncTask : public FXAsyncTask
{
public:
	FPFAuthenticationServerLoginWithBattleNetAsyncTask(
		FPFServiceConfigHandle serviceConfigHandle,
		const FString secretKey,
		const FPFAuthenticationServerLoginWithBattleNetRequest request,
		FOnPFAuthenticationServerLoginCompleteDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFServiceConfigHandle serviceConfigHandle;

	const FString secretKey;

	const FPFAuthenticationServerLoginWithBattleNetRequest request;

	FOnPFAuthenticationServerLoginCompleteDelegate delegate;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK

class PLAYFABCORE_API FPFAuthenticationServerLoginWithCustomIDAsyncTask : public FXAsyncTask
{
public:
	FPFAuthenticationServerLoginWithCustomIDAsyncTask(
		FPFServiceConfigHandle serviceConfigHandle,
		const FString secretKey,
		const FPFAuthenticationServerLoginWithCustomIDRequest request,
		FOnPFAuthenticationServerLoginCompleteDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFServiceConfigHandle serviceConfigHandle;

	const FString secretKey;

	const FPFAuthenticationServerLoginWithCustomIDRequest request;

	FOnPFAuthenticationServerLoginCompleteDelegate delegate;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK

class PLAYFABCORE_API FPFAuthenticationServerLoginWithIOSDeviceIDAsyncTask : public FXAsyncTask
{
public:
	FPFAuthenticationServerLoginWithIOSDeviceIDAsyncTask(
		FPFServiceConfigHandle serviceConfigHandle,
		const FString secretKey,
		const FPFAuthenticationServerLoginWithIOSDeviceIDRequest request,
		FOnPFAuthenticationServerLoginCompleteDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFServiceConfigHandle serviceConfigHandle;

	const FString secretKey;

	const FPFAuthenticationServerLoginWithIOSDeviceIDRequest request;

	FOnPFAuthenticationServerLoginCompleteDelegate delegate;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK

class PLAYFABCORE_API FPFAuthenticationServerLoginWithPSNAsyncTask : public FXAsyncTask
{
public:
	FPFAuthenticationServerLoginWithPSNAsyncTask(
		FPFServiceConfigHandle serviceConfigHandle,
		const FString secretKey,
		const FPFAuthenticationServerLoginWithPSNRequest request,
		FOnPFAuthenticationServerLoginCompleteDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFServiceConfigHandle serviceConfigHandle;

	const FString secretKey;

	const FPFAuthenticationServerLoginWithPSNRequest request;

	FOnPFAuthenticationServerLoginCompleteDelegate delegate;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

class PLAYFABCORE_API FPFAuthenticationServerLoginWithServerCustomIdAsyncTask : public FXAsyncTask
{
public:
	FPFAuthenticationServerLoginWithServerCustomIdAsyncTask(
		FPFServiceConfigHandle serviceConfigHandle,
		const FString secretKey,
		const FPFAuthenticationLoginWithServerCustomIdRequest request,
		FOnPFAuthenticationServerLoginCompleteDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFServiceConfigHandle serviceConfigHandle;

	const FString secretKey;

	const FPFAuthenticationLoginWithServerCustomIdRequest request;

	FOnPFAuthenticationServerLoginCompleteDelegate delegate;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

class PLAYFABCORE_API FPFAuthenticationServerLoginWithSteamIdAsyncTask : public FXAsyncTask
{
public:
	FPFAuthenticationServerLoginWithSteamIdAsyncTask(
		FPFServiceConfigHandle serviceConfigHandle,
		const FString secretKey,
		const FPFAuthenticationLoginWithSteamIdRequest request,
		FOnPFAuthenticationServerLoginCompleteDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFServiceConfigHandle serviceConfigHandle;

	const FString secretKey;

	const FPFAuthenticationLoginWithSteamIdRequest request;

	FOnPFAuthenticationServerLoginCompleteDelegate delegate;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

class PLAYFABCORE_API FPFAuthenticationServerLoginWithXboxAsyncTask : public FXAsyncTask
{
public:
	FPFAuthenticationServerLoginWithXboxAsyncTask(
		FPFServiceConfigHandle serviceConfigHandle,
		const FString secretKey,
		const FPFAuthenticationServerLoginWithXboxRequest request,
		FOnPFAuthenticationServerLoginCompleteDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFServiceConfigHandle serviceConfigHandle;

	const FString secretKey;

	const FPFAuthenticationServerLoginWithXboxRequest request;

	FOnPFAuthenticationServerLoginCompleteDelegate delegate;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

class PLAYFABCORE_API FPFAuthenticationServerLoginWithXboxIdAsyncTask : public FXAsyncTask
{
public:
	FPFAuthenticationServerLoginWithXboxIdAsyncTask(
		FPFServiceConfigHandle serviceConfigHandle,
		const FString secretKey,
		const FPFAuthenticationLoginWithXboxIdRequest request,
		FOnPFAuthenticationServerLoginCompleteDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFServiceConfigHandle serviceConfigHandle;

	const FString secretKey;

	const FPFAuthenticationLoginWithXboxIdRequest request;

	FOnPFAuthenticationServerLoginCompleteDelegate delegate;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

class PLAYFABCORE_API FPFAuthenticationAuthenticateGameServerWithCustomIdAsyncTask : public FXAsyncTask
{
public:
	FPFAuthenticationAuthenticateGameServerWithCustomIdAsyncTask(
		FPFEntityHandle entityHandle,
		const FPFAuthenticationAuthenticateCustomIdRequest request,
		FOnAuthenticateGameServerWithCustomIdDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFEntityHandle entityHandle;

	const FPFAuthenticationAuthenticateCustomIdRequest request;

	FOnAuthenticateGameServerWithCustomIdDelegate delegate;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

class PLAYFABCORE_API FPFAuthenticationDeleteAsyncTask : public FXAsyncTask
{
public:
	FPFAuthenticationDeleteAsyncTask(
		FPFEntityHandle entityHandle,
		const FPFAuthenticationDeleteRequest request,
		FOnDeleteDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFEntityHandle entityHandle;

	const FPFAuthenticationDeleteRequest request;

	FOnDeleteDelegate delegate;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

class PLAYFABCORE_API FPFAuthenticationGetEntityAsyncTask : public FXAsyncTask
{
public:
	FPFAuthenticationGetEntityAsyncTask(
		FPFEntityHandle entityHandle,
		const FPFAuthenticationGetEntityRequest request,
		FOnGetEntityDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFEntityHandle entityHandle;

	const FPFAuthenticationGetEntityRequest request;

	FOnGetEntityDelegate delegate;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

class PLAYFABCORE_API FPFAuthenticationGetEntityWithSecretKeyAsyncTask : public FXAsyncTask
{
public:
	FPFAuthenticationGetEntityWithSecretKeyAsyncTask(
		FPFServiceConfigHandle serviceConfigHandle,
		const FString secretKey,
		const FPFAuthenticationGetEntityRequest request,
		FOnGetEntityWithSecretKeyDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFServiceConfigHandle serviceConfigHandle;

	const FString secretKey;

	const FPFAuthenticationGetEntityRequest request;

	FOnGetEntityWithSecretKeyDelegate delegate;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC

class PLAYFABCORE_API FPFAuthenticationValidateEntityTokenAsyncTask : public FXAsyncTask
{
public:
	FPFAuthenticationValidateEntityTokenAsyncTask(
		FPFEntityHandle entityHandle,
		const FPFAuthenticationValidateEntityTokenRequest request,
		FOnValidateEntityTokenDelegate delegate
	);

	void DoWork() override;

	void ProcessResults() override;

private:

	FPFEntityHandle entityHandle;

	const FPFAuthenticationValidateEntityTokenRequest request;

	FOnValidateEntityTokenDelegate delegate;
};

#endif
