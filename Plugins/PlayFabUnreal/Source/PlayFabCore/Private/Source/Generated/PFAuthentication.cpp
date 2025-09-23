#include "PFAuthentication.h"

#if 0
bool PLAYFABCORE_API FPFAuthenticationLoginWithAndroidDeviceIDAsync(
	_In_ FPFServiceConfigHandle contextHandle,
	_In_ const FPFAuthenticationLoginWithAndroidDeviceIDRequest request,
	_Inout_ FOnPFAuthenticationLoginCompleteDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFAuthenticationLoginWithAndroidDeviceIDAsyncTask>(contextHandle, request, delegate);
	return true;
}
#endif


#if HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABCORE_API FPFAuthenticationLoginWithAppleAsync(
	_In_ FPFServiceConfigHandle contextHandle,
	_In_ const FPFAuthenticationLoginWithAppleRequest request,
	_Inout_ FOnPFAuthenticationLoginCompleteDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFAuthenticationLoginWithAppleAsyncTask>(contextHandle, request, delegate);
	return true;
}
#endif


#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABCORE_API FPFAuthenticationLoginWithBattleNetAsync(
	_In_ FPFServiceConfigHandle contextHandle,
	_In_ const FPFAuthenticationLoginWithBattleNetRequest request,
	_Inout_ FOnPFAuthenticationLoginCompleteDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFAuthenticationLoginWithBattleNetAsyncTask>(contextHandle, request, delegate);
	return true;
}
#endif


bool PLAYFABCORE_API FPFAuthenticationLoginWithCustomIDAsync(
	_In_ FPFServiceConfigHandle contextHandle,
	_In_ const FPFAuthenticationLoginWithCustomIDRequest request,
	_Inout_ FOnPFAuthenticationLoginCompleteDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFAuthenticationLoginWithCustomIDAsyncTask>(contextHandle, request, delegate);
	return true;
}


#if 0
bool PLAYFABCORE_API FPFAuthenticationLoginWithEmailAddressAsync(
	_In_ FPFServiceConfigHandle contextHandle,
	_In_ const FPFAuthenticationLoginWithEmailAddressRequest request,
	_Inout_ FOnPFAuthenticationLoginCompleteDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFAuthenticationLoginWithEmailAddressAsyncTask>(contextHandle, request, delegate);
	return true;
}
#endif


#if HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_IOS
bool PLAYFABCORE_API FPFAuthenticationLoginWithFacebookAsync(
	_In_ FPFServiceConfigHandle contextHandle,
	_In_ const FPFAuthenticationLoginWithFacebookRequest request,
	_Inout_ FOnPFAuthenticationLoginCompleteDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFAuthenticationLoginWithFacebookAsyncTask>(contextHandle, request, delegate);
	return true;
}
#endif


#if 0
bool PLAYFABCORE_API FPFAuthenticationLoginWithFacebookInstantGamesIdAsync(
	_In_ FPFServiceConfigHandle contextHandle,
	_In_ const FPFAuthenticationLoginWithFacebookInstantGamesIdRequest request,
	_Inout_ FOnPFAuthenticationLoginCompleteDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFAuthenticationLoginWithFacebookInstantGamesIdAsyncTask>(contextHandle, request, delegate);
	return true;
}
#endif


#if HC_PLATFORM == HC_PLATFORM_IOS
bool PLAYFABCORE_API FPFAuthenticationLoginWithGameCenterAsync(
	_In_ FPFServiceConfigHandle contextHandle,
	_In_ const FPFAuthenticationLoginWithGameCenterRequest request,
	_Inout_ FOnPFAuthenticationLoginCompleteDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFAuthenticationLoginWithGameCenterAsyncTask>(contextHandle, request, delegate);
	return true;
}
#endif


#if HC_PLATFORM == HC_PLATFORM_ANDROID
bool PLAYFABCORE_API FPFAuthenticationLoginWithGoogleAccountAsync(
	_In_ FPFServiceConfigHandle contextHandle,
	_In_ const FPFAuthenticationLoginWithGoogleAccountRequest request,
	_Inout_ FOnPFAuthenticationLoginCompleteDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFAuthenticationLoginWithGoogleAccountAsyncTask>(contextHandle, request, delegate);
	return true;
}
#endif


#if HC_PLATFORM == HC_PLATFORM_ANDROID
bool PLAYFABCORE_API FPFAuthenticationLoginWithGooglePlayGamesServicesAsync(
	_In_ FPFServiceConfigHandle contextHandle,
	_In_ const FPFAuthenticationLoginWithGooglePlayGamesServicesRequest request,
	_Inout_ FOnPFAuthenticationLoginCompleteDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFAuthenticationLoginWithGooglePlayGamesServicesAsyncTask>(contextHandle, request, delegate);
	return true;
}
#endif


#if 0
bool PLAYFABCORE_API FPFAuthenticationLoginWithIOSDeviceIDAsync(
	_In_ FPFServiceConfigHandle contextHandle,
	_In_ const FPFAuthenticationLoginWithIOSDeviceIDRequest request,
	_Inout_ FOnPFAuthenticationLoginCompleteDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFAuthenticationLoginWithIOSDeviceIDAsyncTask>(contextHandle, request, delegate);
	return true;
}
#endif


#if 0
bool PLAYFABCORE_API FPFAuthenticationLoginWithKongregateAsync(
	_In_ FPFServiceConfigHandle contextHandle,
	_In_ const FPFAuthenticationLoginWithKongregateRequest request,
	_Inout_ FOnPFAuthenticationLoginCompleteDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFAuthenticationLoginWithKongregateAsyncTask>(contextHandle, request, delegate);
	return true;
}
#endif


#if HC_PLATFORM == HC_PLATFORM_NINTENDO_SWITCH
bool PLAYFABCORE_API FPFAuthenticationLoginWithNintendoServiceAccountAsync(
	_In_ FPFServiceConfigHandle contextHandle,
	_In_ const FPFAuthenticationLoginWithNintendoServiceAccountRequest request,
	_Inout_ FOnPFAuthenticationLoginCompleteDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFAuthenticationLoginWithNintendoServiceAccountAsyncTask>(contextHandle, request, delegate);
	return true;
}
#endif


#if 0
bool PLAYFABCORE_API FPFAuthenticationLoginWithNintendoSwitchDeviceIdAsync(
	_In_ FPFServiceConfigHandle contextHandle,
	_In_ const FPFAuthenticationLoginWithNintendoSwitchDeviceIdRequest request,
	_Inout_ FOnPFAuthenticationLoginCompleteDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFAuthenticationLoginWithNintendoSwitchDeviceIdAsyncTask>(contextHandle, request, delegate);
	return true;
}
#endif


bool PLAYFABCORE_API FPFAuthenticationLoginWithOpenIdConnectAsync(
	_In_ FPFServiceConfigHandle contextHandle,
	_In_ const FPFAuthenticationLoginWithOpenIdConnectRequest request,
	_Inout_ FOnPFAuthenticationLoginCompleteDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFAuthenticationLoginWithOpenIdConnectAsyncTask>(contextHandle, request, delegate);
	return true;
}


#if 0
bool PLAYFABCORE_API FPFAuthenticationLoginWithPlayFabAsync(
	_In_ FPFServiceConfigHandle contextHandle,
	_In_ const FPFAuthenticationLoginWithPlayFabRequest request,
	_Inout_ FOnPFAuthenticationLoginCompleteDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFAuthenticationLoginWithPlayFabAsyncTask>(contextHandle, request, delegate);
	return true;
}
#endif


#if HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_4 || HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_5
bool PLAYFABCORE_API FPFAuthenticationLoginWithPSNAsync(
	_In_ FPFServiceConfigHandle contextHandle,
	_In_ const FPFAuthenticationLoginWithPSNRequest request,
	_Inout_ FOnPFAuthenticationLoginCompleteDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFAuthenticationLoginWithPSNAsyncTask>(contextHandle, request, delegate);
	return true;
}
#endif


#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABCORE_API FPFAuthenticationLoginWithSteamAsync(
	_In_ FPFServiceConfigHandle contextHandle,
	_In_ const FPFAuthenticationLoginWithSteamRequest request,
	_Inout_ FOnPFAuthenticationLoginCompleteDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFAuthenticationLoginWithSteamAsyncTask>(contextHandle, request, delegate);
	return true;
}
#endif


#if 0
bool PLAYFABCORE_API FPFAuthenticationLoginWithTwitchAsync(
	_In_ FPFServiceConfigHandle contextHandle,
	_In_ const FPFAuthenticationLoginWithTwitchRequest request,
	_Inout_ FOnPFAuthenticationLoginCompleteDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFAuthenticationLoginWithTwitchAsyncTask>(contextHandle, request, delegate);
	return true;
}
#endif


#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABCORE_API FPFAuthenticationLoginWithXboxAsync(
	_In_ FPFServiceConfigHandle contextHandle,
	_In_ const FPFAuthenticationLoginWithXboxRequest request,
	_Inout_ FOnPFAuthenticationLoginCompleteDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFAuthenticationLoginWithXboxAsyncTask>(contextHandle, request, delegate);
	return true;
}
#endif


#if 0
bool PLAYFABCORE_API FPFAuthenticationRegisterPlayFabUserAsync(
	_In_ FPFServiceConfigHandle contextHandle,
	_In_ const FPFAuthenticationRegisterPlayFabUserRequest request,
	_Inout_ FOnRegisterPlayFabUserDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFAuthenticationRegisterPlayFabUserAsyncTask>(contextHandle, request, delegate);
	return true;
}
#endif


#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABCORE_API FPFAuthenticationServerLoginWithAndroidDeviceIDAsync(
	_In_ FPFServiceConfigHandle contextHandle,
	_In_z_ const FString secretKey,
	_In_ const FPFAuthenticationServerLoginWithAndroidDeviceIDRequest request,
	_Inout_ FOnPFAuthenticationServerLoginCompleteDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFAuthenticationServerLoginWithAndroidDeviceIDAsyncTask>(contextHandle, secretKey, request, delegate);
	return true;
}
#endif


#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABCORE_API FPFAuthenticationServerLoginWithBattleNetAsync(
	_In_ FPFServiceConfigHandle contextHandle,
	_In_z_ const FString secretKey,
	_In_ const FPFAuthenticationServerLoginWithBattleNetRequest request,
	_Inout_ FOnPFAuthenticationServerLoginCompleteDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFAuthenticationServerLoginWithBattleNetAsyncTask>(contextHandle, secretKey, request, delegate);
	return true;
}
#endif


#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABCORE_API FPFAuthenticationServerLoginWithCustomIDAsync(
	_In_ FPFServiceConfigHandle contextHandle,
	_In_z_ const FString secretKey,
	_In_ const FPFAuthenticationServerLoginWithCustomIDRequest request,
	_Inout_ FOnPFAuthenticationServerLoginCompleteDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFAuthenticationServerLoginWithCustomIDAsyncTask>(contextHandle, secretKey, request, delegate);
	return true;
}
#endif


#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABCORE_API FPFAuthenticationServerLoginWithIOSDeviceIDAsync(
	_In_ FPFServiceConfigHandle contextHandle,
	_In_z_ const FString secretKey,
	_In_ const FPFAuthenticationServerLoginWithIOSDeviceIDRequest request,
	_Inout_ FOnPFAuthenticationServerLoginCompleteDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFAuthenticationServerLoginWithIOSDeviceIDAsyncTask>(contextHandle, secretKey, request, delegate);
	return true;
}
#endif


#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABCORE_API FPFAuthenticationServerLoginWithPSNAsync(
	_In_ FPFServiceConfigHandle contextHandle,
	_In_z_ const FString secretKey,
	_In_ const FPFAuthenticationServerLoginWithPSNRequest request,
	_Inout_ FOnPFAuthenticationServerLoginCompleteDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFAuthenticationServerLoginWithPSNAsyncTask>(contextHandle, secretKey, request, delegate);
	return true;
}
#endif


#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABCORE_API FPFAuthenticationServerLoginWithServerCustomIdAsync(
	_In_ FPFServiceConfigHandle contextHandle,
	_In_z_ const FString secretKey,
	_In_ const FPFAuthenticationLoginWithServerCustomIdRequest request,
	_Inout_ FOnPFAuthenticationServerLoginCompleteDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFAuthenticationServerLoginWithServerCustomIdAsyncTask>(contextHandle, secretKey, request, delegate);
	return true;
}
#endif


#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABCORE_API FPFAuthenticationServerLoginWithSteamIdAsync(
	_In_ FPFServiceConfigHandle contextHandle,
	_In_z_ const FString secretKey,
	_In_ const FPFAuthenticationLoginWithSteamIdRequest request,
	_Inout_ FOnPFAuthenticationServerLoginCompleteDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFAuthenticationServerLoginWithSteamIdAsyncTask>(contextHandle, secretKey, request, delegate);
	return true;
}
#endif


#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABCORE_API FPFAuthenticationServerLoginWithXboxAsync(
	_In_ FPFServiceConfigHandle contextHandle,
	_In_z_ const FString secretKey,
	_In_ const FPFAuthenticationServerLoginWithXboxRequest request,
	_Inout_ FOnPFAuthenticationServerLoginCompleteDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFAuthenticationServerLoginWithXboxAsyncTask>(contextHandle, secretKey, request, delegate);
	return true;
}
#endif


#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABCORE_API FPFAuthenticationServerLoginWithXboxIdAsync(
	_In_ FPFServiceConfigHandle contextHandle,
	_In_z_ const FString secretKey,
	_In_ const FPFAuthenticationLoginWithXboxIdRequest request,
	_Inout_ FOnPFAuthenticationServerLoginCompleteDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFAuthenticationServerLoginWithXboxIdAsyncTask>(contextHandle, secretKey, request, delegate);
	return true;
}
#endif


#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABCORE_API FPFAuthenticationAuthenticateGameServerWithCustomIdAsync(
	_In_ FPFEntityHandle contextHandle,
	_In_ const FPFAuthenticationAuthenticateCustomIdRequest request,
	_Inout_ FOnAuthenticateGameServerWithCustomIdDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFAuthenticationAuthenticateGameServerWithCustomIdAsyncTask>(contextHandle, request, delegate);
	return true;
}
#endif


#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABCORE_API FPFAuthenticationDeleteAsync(
	_In_ FPFEntityHandle contextHandle,
	_In_ const FPFAuthenticationDeleteRequest request,
	_Inout_ FOnDeleteDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFAuthenticationDeleteAsyncTask>(contextHandle, request, delegate);
	return true;
}
#endif


#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABCORE_API FPFAuthenticationGetEntityAsync(
	_In_ FPFEntityHandle contextHandle,
	_In_ const FPFAuthenticationGetEntityRequest request,
	_Inout_ FOnGetEntityDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFAuthenticationGetEntityAsyncTask>(contextHandle, request, delegate);
	return true;
}
#endif


#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABCORE_API FPFAuthenticationGetEntityWithSecretKeyAsync(
	_In_ FPFServiceConfigHandle contextHandle,
	_In_z_ const FString secretKey,
	_In_ const FPFAuthenticationGetEntityRequest request,
	_Inout_ FOnGetEntityWithSecretKeyDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFAuthenticationGetEntityWithSecretKeyAsyncTask>(contextHandle, secretKey, request, delegate);
	return true;
}
#endif


#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABCORE_API FPFAuthenticationValidateEntityTokenAsync(
	_In_ FPFEntityHandle contextHandle,
	_In_ const FPFAuthenticationValidateEntityTokenRequest request,
	_Inout_ FOnValidateEntityTokenDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFAuthenticationValidateEntityTokenAsyncTask>(contextHandle, request, delegate);
	return true;
}
#endif


