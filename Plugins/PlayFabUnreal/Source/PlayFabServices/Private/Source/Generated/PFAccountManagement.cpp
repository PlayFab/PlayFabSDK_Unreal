#include "PFAccountManagement.h"

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientAddOrUpdateContactEmailAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementAddOrUpdateContactEmailRequest* request,
	_Inout_ FOnClientAddOrUpdateContactEmailCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientAddOrUpdateContactEmailAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientAddUsernamePasswordAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementAddUsernamePasswordRequest* request,
	_Inout_ FOnClientAddUsernamePasswordCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientAddUsernamePasswordAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

bool PLAYFABSERVICES_API FPFAccountManagementClientGetAccountInfoAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementGetAccountInfoRequest* request,
	_Inout_ FOnClientGetAccountInfoCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientGetAccountInfoAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFAccountManagementClientGetPlayerCombinedInfoAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementGetPlayerCombinedInfoRequest* request,
	_Inout_ FOnClientGetPlayerCombinedInfoCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientGetPlayerCombinedInfoAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFAccountManagementClientGetPlayerProfileAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementGetPlayerProfileRequest* request,
	_Inout_ FOnClientGetPlayerProfileCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientGetPlayerProfileAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFAccountManagementClientGetPlayFabIDsFromBattleNetAccountIdsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsRequest* request,
	_Inout_ FOnClientGetPlayFabIDsFromBattleNetAccountIdsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientGetPlayFabIDsFromBattleNetAccountIdsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientGetPlayFabIDsFromFacebookIDsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromFacebookIDsRequest* request,
	_Inout_ FOnClientGetPlayFabIDsFromFacebookIDsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientGetPlayFabIDsFromFacebookIDsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientGetPlayFabIDsFromFacebookInstantGamesIdsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsRequest* request,
	_Inout_ FOnClientGetPlayFabIDsFromFacebookInstantGamesIdsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientGetPlayFabIDsFromFacebookInstantGamesIdsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientGetPlayFabIDsFromGameCenterIDsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromGameCenterIDsRequest* request,
	_Inout_ FOnClientGetPlayFabIDsFromGameCenterIDsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientGetPlayFabIDsFromGameCenterIDsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientGetPlayFabIDsFromGoogleIDsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromGoogleIDsRequest* request,
	_Inout_ FOnClientGetPlayFabIDsFromGoogleIDsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientGetPlayFabIDsFromGoogleIDsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientGetPlayFabIDsFromGooglePlayGamesPlayerIDsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromGooglePlayGamesPlayerIDsRequest* request,
	_Inout_ FOnClientGetPlayFabIDsFromGooglePlayGamesPlayerIDsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientGetPlayFabIDsFromGooglePlayGamesPlayerIDsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientGetPlayFabIDsFromKongregateIDsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromKongregateIDsRequest* request,
	_Inout_ FOnClientGetPlayFabIDsFromKongregateIDsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientGetPlayFabIDsFromKongregateIDsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_NINTENDO_SWITCH || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientGetPlayFabIDsFromNintendoServiceAccountIdsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsRequest* request,
	_Inout_ FOnClientGetPlayFabIDsFromNintendoServiceAccountIdsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientGetPlayFabIDsFromNintendoServiceAccountIdsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientGetPlayFabIDsFromNintendoSwitchDeviceIdsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsRequest* request,
	_Inout_ FOnClientGetPlayFabIDsFromNintendoSwitchDeviceIdsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientGetPlayFabIDsFromNintendoSwitchDeviceIdsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if 0
bool PLAYFABSERVICES_API FPFAccountManagementClientGetPlayFabIDsFromOpenIdSubjectIdentifiersAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromOpenIdsRequest* request,
	_Inout_ FOnClientGetPlayFabIDsFromOpenIdSubjectIdentifiersCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientGetPlayFabIDsFromOpenIdSubjectIdentifiersAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_4 || HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_5 || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientGetPlayFabIDsFromPSNAccountIDsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromPSNAccountIDsRequest* request,
	_Inout_ FOnClientGetPlayFabIDsFromPSNAccountIDsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientGetPlayFabIDsFromPSNAccountIDsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

bool PLAYFABSERVICES_API FPFAccountManagementClientGetPlayFabIDsFromPSNOnlineIDsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromPSNOnlineIDsRequest* request,
	_Inout_ FOnClientGetPlayFabIDsFromPSNOnlineIDsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientGetPlayFabIDsFromPSNOnlineIDsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientGetPlayFabIDsFromSteamIDsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromSteamIDsRequest* request,
	_Inout_ FOnClientGetPlayFabIDsFromSteamIDsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientGetPlayFabIDsFromSteamIDsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

bool PLAYFABSERVICES_API FPFAccountManagementClientGetPlayFabIDsFromSteamNamesAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromSteamNamesRequest* request,
	_Inout_ FOnClientGetPlayFabIDsFromSteamNamesCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientGetPlayFabIDsFromSteamNamesAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientGetPlayFabIDsFromTwitchIDsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromTwitchIDsRequest* request,
	_Inout_ FOnClientGetPlayFabIDsFromTwitchIDsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientGetPlayFabIDsFromTwitchIDsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientGetPlayFabIDsFromXboxLiveIDsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromXboxLiveIDsRequest* request,
	_Inout_ FOnClientGetPlayFabIDsFromXboxLiveIDsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientGetPlayFabIDsFromXboxLiveIDsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientLinkAndroidDeviceIDAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementLinkAndroidDeviceIDRequest* request,
	_Inout_ FOnClientLinkAndroidDeviceIDCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientLinkAndroidDeviceIDAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientLinkAppleAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementLinkAppleRequest* request,
	_Inout_ FOnClientLinkAppleCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientLinkAppleAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFAccountManagementClientLinkBattleNetAccountAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementClientLinkBattleNetAccountRequest* request,
	_Inout_ FOnClientLinkBattleNetAccountCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientLinkBattleNetAccountAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

bool PLAYFABSERVICES_API FPFAccountManagementClientLinkCustomIDAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementLinkCustomIDRequest* request,
	_Inout_ FOnClientLinkCustomIDCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientLinkCustomIDAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientLinkFacebookAccountAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementLinkFacebookAccountRequest* request,
	_Inout_ FOnClientLinkFacebookAccountCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientLinkFacebookAccountAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientLinkFacebookInstantGamesIdAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementLinkFacebookInstantGamesIdRequest* request,
	_Inout_ FOnClientLinkFacebookInstantGamesIdCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientLinkFacebookInstantGamesIdAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientLinkGameCenterAccountAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementLinkGameCenterAccountRequest* request,
	_Inout_ FOnClientLinkGameCenterAccountCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientLinkGameCenterAccountAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientLinkGoogleAccountAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementLinkGoogleAccountRequest* request,
	_Inout_ FOnClientLinkGoogleAccountCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientLinkGoogleAccountAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientLinkGooglePlayGamesServicesAccountAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementLinkGooglePlayGamesServicesAccountRequest* request,
	_Inout_ FOnClientLinkGooglePlayGamesServicesAccountCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientLinkGooglePlayGamesServicesAccountAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientLinkIOSDeviceIDAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementLinkIOSDeviceIDRequest* request,
	_Inout_ FOnClientLinkIOSDeviceIDCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientLinkIOSDeviceIDAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientLinkKongregateAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementLinkKongregateAccountRequest* request,
	_Inout_ FOnClientLinkKongregateCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientLinkKongregateAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_NINTENDO_SWITCH || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientLinkNintendoServiceAccountAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementClientLinkNintendoServiceAccountRequest* request,
	_Inout_ FOnClientLinkNintendoServiceAccountCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientLinkNintendoServiceAccountAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientLinkNintendoSwitchDeviceIdAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementClientLinkNintendoSwitchDeviceIdRequest* request,
	_Inout_ FOnClientLinkNintendoSwitchDeviceIdCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientLinkNintendoSwitchDeviceIdAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

bool PLAYFABSERVICES_API FPFAccountManagementClientLinkOpenIdConnectAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementLinkOpenIdConnectRequest* request,
	_Inout_ FOnClientLinkOpenIdConnectCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientLinkOpenIdConnectAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

#if HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_4 || HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_5 || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientLinkPSNAccountAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementClientLinkPSNAccountRequest* request,
	_Inout_ FOnClientLinkPSNAccountCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientLinkPSNAccountAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientLinkSteamAccountAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementLinkSteamAccountRequest* request,
	_Inout_ FOnClientLinkSteamAccountCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientLinkSteamAccountAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientLinkTwitchAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementClientLinkTwitchAccountRequest* request,
	_Inout_ FOnClientLinkTwitchCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientLinkTwitchAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientLinkXboxAccountAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementClientLinkXboxAccountRequest* request,
	_Inout_ FOnClientLinkXboxAccountCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientLinkXboxAccountAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientRemoveContactEmailAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementRemoveContactEmailRequest* request,
	_Inout_ FOnClientRemoveContactEmailCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientRemoveContactEmailAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

bool PLAYFABSERVICES_API FPFAccountManagementClientReportPlayerAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementReportPlayerClientRequest* request,
	_Inout_ FOnClientReportPlayerCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientReportPlayerAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientSendAccountRecoveryEmailAsync(
	_In_ FPFServiceConfigHandle ServiceConfigHandle,
	_In_ const FPFAccountManagementSendAccountRecoveryEmailRequest* request,
	_Inout_ FOnClientSendAccountRecoveryEmailCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientSendAccountRecoveryEmailAsyncTask>(ServiceConfigHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientUnlinkAndroidDeviceIDAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementUnlinkAndroidDeviceIDRequest* request,
	_Inout_ FOnClientUnlinkAndroidDeviceIDCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientUnlinkAndroidDeviceIDAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientUnlinkAppleAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementUnlinkAppleRequest* request,
	_Inout_ FOnClientUnlinkAppleCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientUnlinkAppleAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFAccountManagementClientUnlinkBattleNetAccountAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementClientUnlinkBattleNetAccountRequest* request,
	_Inout_ FOnClientUnlinkBattleNetAccountCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientUnlinkBattleNetAccountAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

bool PLAYFABSERVICES_API FPFAccountManagementClientUnlinkCustomIDAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementUnlinkCustomIDRequest* request,
	_Inout_ FOnClientUnlinkCustomIDCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientUnlinkCustomIDAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientUnlinkFacebookAccountAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementClientUnlinkFacebookAccountRequest* request,
	_Inout_ FOnClientUnlinkFacebookAccountCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientUnlinkFacebookAccountAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientUnlinkFacebookInstantGamesIdAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementClientUnlinkFacebookInstantGamesIdRequest* request,
	_Inout_ FOnClientUnlinkFacebookInstantGamesIdCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientUnlinkFacebookInstantGamesIdAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_IOS || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientUnlinkGameCenterAccountAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementUnlinkGameCenterAccountRequest* request,
	_Inout_ FOnClientUnlinkGameCenterAccountCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientUnlinkGameCenterAccountAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientUnlinkGoogleAccountAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementUnlinkGoogleAccountRequest* request,
	_Inout_ FOnClientUnlinkGoogleAccountCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientUnlinkGoogleAccountAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_ANDROID || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientUnlinkGooglePlayGamesServicesAccountAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementUnlinkGooglePlayGamesServicesAccountRequest* request,
	_Inout_ FOnClientUnlinkGooglePlayGamesServicesAccountCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientUnlinkGooglePlayGamesServicesAccountAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientUnlinkIOSDeviceIDAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementUnlinkIOSDeviceIDRequest* request,
	_Inout_ FOnClientUnlinkIOSDeviceIDCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientUnlinkIOSDeviceIDAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientUnlinkKongregateAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementUnlinkKongregateAccountRequest* request,
	_Inout_ FOnClientUnlinkKongregateCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientUnlinkKongregateAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_NINTENDO_SWITCH || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientUnlinkNintendoServiceAccountAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementClientUnlinkNintendoServiceAccountRequest* request,
	_Inout_ FOnClientUnlinkNintendoServiceAccountCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientUnlinkNintendoServiceAccountAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientUnlinkNintendoSwitchDeviceIdAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementClientUnlinkNintendoSwitchDeviceIdRequest* request,
	_Inout_ FOnClientUnlinkNintendoSwitchDeviceIdCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientUnlinkNintendoSwitchDeviceIdAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

bool PLAYFABSERVICES_API FPFAccountManagementClientUnlinkOpenIdConnectAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementUnlinkOpenIdConnectRequest* request,
	_Inout_ FOnClientUnlinkOpenIdConnectCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientUnlinkOpenIdConnectAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

#if HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_4 || HC_PLATFORM == HC_PLATFORM_SONY_PLAYSTATION_5 || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientUnlinkPSNAccountAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementClientUnlinkPSNAccountRequest* request,
	_Inout_ FOnClientUnlinkPSNAccountCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientUnlinkPSNAccountAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientUnlinkSteamAccountAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementUnlinkSteamAccountRequest* request,
	_Inout_ FOnClientUnlinkSteamAccountCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientUnlinkSteamAccountAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientUnlinkTwitchAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementClientUnlinkTwitchAccountRequest* request,
	_Inout_ FOnClientUnlinkTwitchCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientUnlinkTwitchAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientUnlinkXboxAccountAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementClientUnlinkXboxAccountRequest* request,
	_Inout_ FOnClientUnlinkXboxAccountCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientUnlinkXboxAccountAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

bool PLAYFABSERVICES_API FPFAccountManagementClientUpdateAvatarUrlAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementClientUpdateAvatarUrlRequest* request,
	_Inout_ FOnClientUpdateAvatarUrlCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientUpdateAvatarUrlAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementClientUpdateUserTitleDisplayNameAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementUpdateUserTitleDisplayNameRequest* request,
	_Inout_ FOnClientUpdateUserTitleDisplayNameCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientUpdateUserTitleDisplayNameAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

#if 0
bool PLAYFABSERVICES_API FPFAccountManagementServerAddOrUpdateContactEmailAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementServerAddOrUpdateContactEmailRequest* request,
	_Inout_ FOnServerAddOrUpdateContactEmailCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerAddOrUpdateContactEmailAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerBanUsersAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementBanUsersRequest* request,
	_Inout_ FOnServerBanUsersCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerBanUsersAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerDeletePlayerAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementDeletePlayerRequest* request,
	_Inout_ FOnServerDeletePlayerCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerDeletePlayerAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerGetPlayerCombinedInfoAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementGetPlayerCombinedInfoRequest* request,
	_Inout_ FOnServerGetPlayerCombinedInfoCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerGetPlayerCombinedInfoAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerGetPlayerProfileAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementGetPlayerProfileRequest* request,
	_Inout_ FOnServerGetPlayerProfileCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerGetPlayerProfileAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFAccountManagementServerGetPlayFabIDsFromBattleNetAccountIdsAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromBattleNetAccountIdsRequest* request,
	_Inout_ FOnServerGetPlayFabIDsFromBattleNetAccountIdsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerGetPlayFabIDsFromBattleNetAccountIdsAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerGetPlayFabIDsFromFacebookIDsAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromFacebookIDsRequest* request,
	_Inout_ FOnServerGetPlayFabIDsFromFacebookIDsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerGetPlayFabIDsFromFacebookIDsAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerGetPlayFabIDsFromFacebookInstantGamesIdsAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromFacebookInstantGamesIdsRequest* request,
	_Inout_ FOnServerGetPlayFabIDsFromFacebookInstantGamesIdsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerGetPlayFabIDsFromFacebookInstantGamesIdsAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerGetPlayFabIDsFromNintendoServiceAccountIdsAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromNintendoServiceAccountIdsRequest* request,
	_Inout_ FOnServerGetPlayFabIDsFromNintendoServiceAccountIdsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerGetPlayFabIDsFromNintendoServiceAccountIdsAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerGetPlayFabIDsFromNintendoSwitchDeviceIdsAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromNintendoSwitchDeviceIdsRequest* request,
	_Inout_ FOnServerGetPlayFabIDsFromNintendoSwitchDeviceIdsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerGetPlayFabIDsFromNintendoSwitchDeviceIdsAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if 0
bool PLAYFABSERVICES_API FPFAccountManagementServerGetPlayFabIDsFromOpenIdSubjectIdentifiersAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromOpenIdsRequest* request,
	_Inout_ FOnServerGetPlayFabIDsFromOpenIdSubjectIdentifiersCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerGetPlayFabIDsFromOpenIdSubjectIdentifiersAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerGetPlayFabIDsFromPSNAccountIDsAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromPSNAccountIDsRequest* request,
	_Inout_ FOnServerGetPlayFabIDsFromPSNAccountIDsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerGetPlayFabIDsFromPSNAccountIDsAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFAccountManagementServerGetPlayFabIDsFromPSNOnlineIDsAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromPSNOnlineIDsRequest* request,
	_Inout_ FOnServerGetPlayFabIDsFromPSNOnlineIDsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerGetPlayFabIDsFromPSNOnlineIDsAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerGetPlayFabIDsFromSteamIDsAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromSteamIDsRequest* request,
	_Inout_ FOnServerGetPlayFabIDsFromSteamIDsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerGetPlayFabIDsFromSteamIDsAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFAccountManagementServerGetPlayFabIDsFromSteamNamesAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromSteamNamesRequest* request,
	_Inout_ FOnServerGetPlayFabIDsFromSteamNamesCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerGetPlayFabIDsFromSteamNamesAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerGetPlayFabIDsFromTwitchIDsAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromTwitchIDsRequest* request,
	_Inout_ FOnServerGetPlayFabIDsFromTwitchIDsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerGetPlayFabIDsFromTwitchIDsAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerGetPlayFabIDsFromXboxLiveIDsAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementGetPlayFabIDsFromXboxLiveIDsRequest* request,
	_Inout_ FOnServerGetPlayFabIDsFromXboxLiveIDsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerGetPlayFabIDsFromXboxLiveIDsAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerGetServerCustomIDsFromPlayFabIDsAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementGetServerCustomIDsFromPlayFabIDsRequest* request,
	_Inout_ FOnServerGetServerCustomIDsFromPlayFabIDsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerGetServerCustomIDsFromPlayFabIDsAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerGetUserAccountInfoAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementGetUserAccountInfoRequest* request,
	_Inout_ FOnServerGetUserAccountInfoCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerGetUserAccountInfoAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerGetUserBansAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementGetUserBansRequest* request,
	_Inout_ FOnServerGetUserBansCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerGetUserBansAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFAccountManagementServerLinkBattleNetAccountAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementServerLinkBattleNetAccountRequest* request,
	_Inout_ FOnServerLinkBattleNetAccountCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerLinkBattleNetAccountAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerLinkNintendoServiceAccountAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementServerLinkNintendoServiceAccountRequest* request,
	_Inout_ FOnServerLinkNintendoServiceAccountCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerLinkNintendoServiceAccountAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerLinkNintendoServiceAccountSubjectAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementLinkNintendoServiceAccountSubjectRequest* request,
	_Inout_ FOnServerLinkNintendoServiceAccountSubjectCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerLinkNintendoServiceAccountSubjectAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerLinkNintendoSwitchDeviceIdAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementServerLinkNintendoSwitchDeviceIdRequest* request,
	_Inout_ FOnServerLinkNintendoSwitchDeviceIdCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerLinkNintendoSwitchDeviceIdAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerLinkPSNAccountAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementServerLinkPSNAccountRequest* request,
	_Inout_ FOnServerLinkPSNAccountCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerLinkPSNAccountAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFAccountManagementServerLinkPSNIdAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementLinkPSNIdRequest* request,
	_Inout_ FOnServerLinkPSNIdCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerLinkPSNIdAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerLinkServerCustomIdAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementLinkServerCustomIdRequest* request,
	_Inout_ FOnServerLinkServerCustomIdCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerLinkServerCustomIdAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerLinkSteamIdAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementLinkSteamIdRequest* request,
	_Inout_ FOnServerLinkSteamIdCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerLinkSteamIdAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if 0
bool PLAYFABSERVICES_API FPFAccountManagementServerLinkTwitchAccountAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementServerLinkTwitchAccountRequest* request,
	_Inout_ FOnServerLinkTwitchAccountCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerLinkTwitchAccountAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerLinkXboxAccountAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementServerLinkXboxAccountRequest* request,
	_Inout_ FOnServerLinkXboxAccountCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerLinkXboxAccountAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if 0
bool PLAYFABSERVICES_API FPFAccountManagementServerLinkXboxIdAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementLinkXboxIdRequest* request,
	_Inout_ FOnServerLinkXboxIdCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerLinkXboxIdAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerRevokeAllBansForUserAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementRevokeAllBansForUserRequest* request,
	_Inout_ FOnServerRevokeAllBansForUserCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerRevokeAllBansForUserAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerRevokeBansAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementRevokeBansRequest* request,
	_Inout_ FOnServerRevokeBansCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerRevokeBansAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerSendCustomAccountRecoveryEmailAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementSendCustomAccountRecoveryEmailRequest* request,
	_Inout_ FOnServerSendCustomAccountRecoveryEmailCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerSendCustomAccountRecoveryEmailAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerSendEmailFromTemplateAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementSendEmailFromTemplateRequest* request,
	_Inout_ FOnServerSendEmailFromTemplateCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerSendEmailFromTemplateAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFAccountManagementServerUnlinkBattleNetAccountAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementServerUnlinkBattleNetAccountRequest* request,
	_Inout_ FOnServerUnlinkBattleNetAccountCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerUnlinkBattleNetAccountAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if 0
bool PLAYFABSERVICES_API FPFAccountManagementServerUnlinkFacebookAccountAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementServerUnlinkFacebookAccountRequest* request,
	_Inout_ FOnServerUnlinkFacebookAccountCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerUnlinkFacebookAccountAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if 0
bool PLAYFABSERVICES_API FPFAccountManagementServerUnlinkFacebookInstantGamesIdAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementServerUnlinkFacebookInstantGamesIdRequest* request,
	_Inout_ FOnServerUnlinkFacebookInstantGamesIdCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerUnlinkFacebookInstantGamesIdAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerUnlinkNintendoServiceAccountAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementServerUnlinkNintendoServiceAccountRequest* request,
	_Inout_ FOnServerUnlinkNintendoServiceAccountCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerUnlinkNintendoServiceAccountAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerUnlinkNintendoSwitchDeviceIdAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementServerUnlinkNintendoSwitchDeviceIdRequest* request,
	_Inout_ FOnServerUnlinkNintendoSwitchDeviceIdCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerUnlinkNintendoSwitchDeviceIdAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerUnlinkPSNAccountAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementServerUnlinkPSNAccountRequest* request,
	_Inout_ FOnServerUnlinkPSNAccountCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerUnlinkPSNAccountAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerUnlinkServerCustomIdAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementUnlinkServerCustomIdRequest* request,
	_Inout_ FOnServerUnlinkServerCustomIdCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerUnlinkServerCustomIdAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerUnlinkSteamIdAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementUnlinkSteamIdRequest* request,
	_Inout_ FOnServerUnlinkSteamIdCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerUnlinkSteamIdAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if 0
bool PLAYFABSERVICES_API FPFAccountManagementServerUnlinkTwitchAccountAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementServerUnlinkTwitchAccountRequest* request,
	_Inout_ FOnServerUnlinkTwitchAccountCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerUnlinkTwitchAccountAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerUnlinkXboxAccountAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementServerUnlinkXboxAccountRequest* request,
	_Inout_ FOnServerUnlinkXboxAccountCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerUnlinkXboxAccountAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerUpdateAvatarUrlAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementServerUpdateAvatarUrlRequest* request,
	_Inout_ FOnServerUpdateAvatarUrlCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerUpdateAvatarUrlAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementServerUpdateBansAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFAccountManagementUpdateBansRequest* request,
	_Inout_ FOnServerUpdateBansCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerUpdateBansAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFAccountManagementGetTitlePlayersFromXboxLiveIDsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementGetTitlePlayersFromXboxLiveIDsRequest* request,
	_Inout_ FOnGetTitlePlayersFromXboxLiveIDsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FGetTitlePlayersFromXboxLiveIDsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

bool PLAYFABSERVICES_API FPFAccountManagementSetDisplayNameAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFAccountManagementSetDisplayNameRequest* request,
	_Inout_ FOnSetDisplayNameCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FSetDisplayNameAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

