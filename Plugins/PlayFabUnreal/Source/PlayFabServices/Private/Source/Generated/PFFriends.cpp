#include "PFFriends.h"

bool PLAYFABSERVICES_API FPFFriendsClientAddFriendAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFFriendsClientAddFriendRequest* request,
	_Inout_ FOnClientAddFriendCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientAddFriendAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFFriendsClientGetFriendsListAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFFriendsClientGetFriendsListRequest* request,
	_Inout_ FOnClientGetFriendsListCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientGetFriendsListAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFFriendsClientRemoveFriendAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFFriendsClientRemoveFriendRequest* request,
	_Inout_ FOnClientRemoveFriendCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientRemoveFriendAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

bool PLAYFABSERVICES_API FPFFriendsClientSetFriendTagsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFFriendsClientSetFriendTagsRequest* request,
	_Inout_ FOnClientSetFriendTagsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FClientSetFriendTagsAsyncTask>(EntityHandle, *request, delegate);
	return true;
}

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFFriendsServerAddFriendAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFFriendsServerAddFriendRequest* request,
	_Inout_ FOnServerAddFriendCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerAddFriendAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFFriendsServerGetFriendsListAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFFriendsServerGetFriendsListRequest* request,
	_Inout_ FOnServerGetFriendsListCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerGetFriendsListAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFFriendsServerRemoveFriendAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFFriendsServerRemoveFriendRequest* request,
	_Inout_ FOnServerRemoveFriendCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerRemoveFriendAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
bool PLAYFABSERVICES_API FPFFriendsServerSetFriendTagsAsync(
	_In_ FPFEntityHandle TitleEntityHandle,
	_In_ const FPFFriendsServerSetFriendTagsRequest* request,
	_Inout_ FOnServerSetFriendTagsCompleted delegate
) noexcept
{
	FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
	taskManager->AddTask<FServerSetFriendTagsAsyncTask>(TitleEntityHandle, *request, delegate);
	return true;
}
#endif

