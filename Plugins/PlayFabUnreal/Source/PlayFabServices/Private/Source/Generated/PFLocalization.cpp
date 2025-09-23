#include "PFLocalization.h"

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFLocalizationGetLanguageListAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFLocalizationGetLanguageListRequest* request,
	_Inout_ FOnGetLanguageListCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FGetLanguageListAsyncTask>(EntityHandle, *request, delegate);
	return true;
}
#endif

