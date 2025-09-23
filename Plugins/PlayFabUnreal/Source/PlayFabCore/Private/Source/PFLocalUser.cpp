#include "PFLocalUser.h"
#include "LocalUserAsyncTasks.h"
#include <playfab/core/PFLocalUser.h>
#include <playfab/core/PFAuthentication.h>
#include "ResultMacros.h"

#if defined(PF_UE_GDK_SUPPORT) && defined(PF_GDK_AVAILABLE)
bool PLAYFABCORE_API FPFLocalUserCreateHandleWithXboxUser(
    _In_ FPFServiceConfigHandle serviceConfigHandle,
    _In_ FGDKUserHandle user,
    _In_opt_ TSharedPtr<void> customContext,
    _Out_ FPFLocalUserHandle& localUserHandle
) noexcept
{
    RETURN_FALSE_IF_NULL(serviceConfigHandle);
    RETURN_FALSE_IF_NULL(user);

    PFLocalUserHandle handle;
    RETURN_FALSE_IF_FAILED(PFLocalUserCreateHandleWithXboxUser(serviceConfigHandle.Get(), user, customContext.Get(), &handle));
    *reinterpret_cast<PFLocalUserHandle*>(&localUserHandle) = handle;

    return true;
}
#elif defined(PF_GDK_AVAILABLE)
bool PLAYFABCORE_API FPFLocalUserCreateHandleWithXboxUser(
    _In_ FPFServiceConfigHandle serviceConfigHandle,
    _In_ XUserHandle user,
    _In_opt_ TSharedPtr<void> customContext,
    _Out_ FPFLocalUserHandle& localUserHandle
) noexcept
{
    RETURN_FALSE_IF_NULL(serviceConfigHandle);
    RETURN_FALSE_IF_NULL(user);

    PFLocalUserHandle handle;
    RETURN_FALSE_IF_FAILED(PFLocalUserCreateHandleWithXboxUser(serviceConfigHandle.Get(), user, customContext.Get(), &handle));
    *reinterpret_cast<PFLocalUserHandle*>(&localUserHandle) = handle;

    return true;
}
#endif

HRESULT CALLBACK UnrealLocalUserLoginHandler(
    _In_ PFLocalUserHandle localUserHandle,
    _In_ PFServiceConfigHandle serviceConfigHandle,
    _In_opt_ PFEntityHandle existingEntityHandle,
    _Inout_ XAsyncBlock * async
)
{
    TArray<char> localId;
    size_t localIdSize;
    RETURN_IF_FAILED(PFLocalUserGetLocalIdSize(localUserHandle, &localIdSize));

    localId.Reserve(localIdSize);
    RETURN_IF_FAILED(PFLocalUserGetLocalId(localUserHandle, localIdSize, localId.GetData(), nullptr));

    PFAuthenticationLoginWithCustomIDRequest request{};

    request.customId = localId.GetData();

    if (existingEntityHandle == nullptr)
    {
        request.createAccount = true;
        return PFAuthenticationLoginWithCustomIDAsync(serviceConfigHandle, &request, async);
    }
    else
    {
        request.createAccount = false;
        return PFAuthenticationReLoginWithCustomIDAsync(existingEntityHandle, &request, async);
    }
}

bool PLAYFABCORE_API FPFLocalUserCreateHandleWithPersistedLocalId(
    _In_ FPFServiceConfigHandle serviceConfigHandle,
    _In_ FString& persistedLocalId,
    _In_opt_ TSharedPtr<void> customContext,
    _Out_ FPFLocalUserHandle& localUserHandle
) noexcept
{
    RETURN_FALSE_IF_NULL(serviceConfigHandle);
    RETURN_FALSE_IF_EMPTY(persistedLocalId);

    PFLocalUserHandle handle;
    RETURN_FALSE_IF_FAILED(PFLocalUserCreateHandleWithPersistedLocalId(serviceConfigHandle.Get(), TCHAR_TO_ANSI(*persistedLocalId), UnrealLocalUserLoginHandler, customContext.Get(), &handle));
    *reinterpret_cast<PFLocalUserHandle*>(&localUserHandle) = handle;

    return true;
}

bool PLAYFABCORE_API FPFLocalUserDuplicateHandle(
    _In_ FPFLocalUserHandle localUserHandle,
    _Out_ FPFLocalUserHandle& duplicatedHandle
) noexcept
{
    RETURN_FALSE_IF_NULL(localUserHandle);

    PFLocalUserHandle handle;
    RETURN_FALSE_IF_FAILED(PFLocalUserDuplicateHandle(localUserHandle.Get(), &handle));
    *reinterpret_cast<PFLocalUserHandle*>(&duplicatedHandle) = handle;

    return true;
}

bool PLAYFABCORE_API FPFLocalUserCloseHandle(
    _In_ FPFLocalUserHandle localUserHandle
) noexcept
{
    RETURN_FALSE_IF_NULL(localUserHandle);

    PFLocalUserCloseHandle(localUserHandle.Get());
    return true;
}

bool PLAYFABCORE_API FPFLocalUserGetLocalId(
    _In_ FPFLocalUserHandle localUserHandle,
    _Out_ FString& localUserId
) noexcept
{
    RETURN_FALSE_IF_NULL(localUserHandle);

    TArray<char> localId;
    size_t localIdSize;
    RETURN_FALSE_IF_FAILED(PFLocalUserGetLocalIdSize(localUserHandle.Get(), &localIdSize));

    localId.Reserve(localIdSize);
    RETURN_FALSE_IF_FAILED(PFLocalUserGetLocalId(localUserHandle.Get(), localIdSize, localId.GetData(), nullptr));

    localUserId = localId.GetData();

    return true;
}

bool PLAYFABCORE_API FPFLocalUserGetCustomContext(
    _In_ FPFLocalUserHandle localUserHandle,
    _Out_ TSharedPtr<void> customContext
) noexcept
{
    RETURN_FALSE_IF_NULL(localUserHandle);

    RETURN_FALSE_IF_FAILED(PFLocalUserGetCustomContext(localUserHandle.Get(), reinterpret_cast<void**>(customContext.Get())));
    return true;
}

bool PLAYFABCORE_API FPFLocalUserTryGetEntityHandle(
    _In_ FPFLocalUserHandle localUserHandle,
    _Out_ FPFEntityHandle& entityHandle
) noexcept
{
    RETURN_FALSE_IF_NULL(localUserHandle);

    PFEntityHandle handle;
    RETURN_FALSE_IF_FAILED(PFLocalUserTryGetEntityHandle(localUserHandle.Get(), &handle));
    entityHandle = *reinterpret_cast<FPFEntityHandle*>(&handle);

    return true;
}

bool PLAYFABCORE_API FPFLocalUserLoginAsync(
    _In_ FPFLocalUserHandle localUserHandle,
    _In_ bool createAccount,
    _In_ FOnPFAuthenticationLoginCompleteDelegate delegate
) noexcept
{
    RETURN_FALSE_IF_NULL(localUserHandle);

    FXAsyncTaskManager* taskManager = FXAsyncTaskManagerSingleton::Get().GetTaskManagerRunnable();
    taskManager->AddTask<LocalUserLoginAsyncTask>(localUserHandle, createAccount, delegate);
    return true;
}