#if defined(PF_GDK_AVAILABLE) || defined(PF_UE_GDK_SUPPORT)

#include "Xbox/PFAuthentication_Xbox.h"

bool PLAYFABCORE_API FPFAuthenticationLoginWithXUserAsync(
	_In_ FPFServiceConfigHandle serviceConfigHandle,
	_In_ const FPFAuthenticationLoginWithXUserRequest request,
	_Inout_ FOnPFAuthenticationLoginCompleteDelegate delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FPFAuthenticationLoginWithXUserAsyncTask>(serviceConfigHandle, request, delegate);
	return true;
}

#endif
