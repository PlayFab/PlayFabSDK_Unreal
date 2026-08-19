#include "PlayFabCoreModule.h"
#include "Modules/ModuleManager.h"
#include "Logging.h"
#include "XAsyncTaskQueueHelpers.h"
#include "XAsyncTaskManager.h"
#include "TypeWrappers.h"
#ifdef PF_UE_GDK_SUPPORT
#include "GDKRuntimeModule.h"
#endif
#if defined(PF_GDK_AVAILABLE) && !defined(PF_UE_GDK_SUPPORT)
#include <XGameRuntimeInit.h>
#endif
#if HC_PLATFORM_IS_PLAYSTATION
#include "PlayStation/PlayFabCoreModule.PS.h"
#endif
#if HC_PLATFORM == HC_PLATFORM_NINTENDO_SWITCH
#include "Switch/PlayFabCoreModule.Switch.h"
#endif

IMPLEMENT_MODULE(FPlayFabCore, PlayFabCore);

// Define the log category for TypeWrappers
DEFINE_LOG_CATEGORY(LogPlayFabTypeWrappers);

void FPlayFabCore::StartupModule()
{
	if (IsRunningCommandlet())
	{
		return;
	}

#if defined(PF_UE_GDK_SUPPORT)
	IGDKRuntimeModule::Get();
	EnsureXGameRuntimeInitialized();

#if WITH_EDITOR
	if (IGDKRuntimeModule* GDKRuntimeModule = IGDKRuntimeModule::TryGet())
	{
		GDKRuntimeModule->GetOnInitForPIE().AddRaw(this, &FPlayFabCore::OnInitForPIE);
		GDKRuntimeModule->GetOnTeardownForPIE().AddRaw(this, &FPlayFabCore::OnTeardownForPIE);
	}
#endif // WITH_EDITOR
#elif defined(PF_GDK_AVAILABLE)
	EnsureXGameRuntimeInitialized();
#endif

#if HC_PLATFORM_IS_PLAYSTATION
	PlayFabCorePS::InitializePlatform();
#endif

#if HC_PLATFORM == HC_PLATFORM_NINTENDO_SWITCH
	PlayFabCoreSwitch::InitializePlatform();
#endif

}

void FPlayFabCore::ShutdownModule()
{
	if (IsRunningCommandlet())
	{
		return;
	}

	FXAsyncTaskQueue::PlatformTearDown();

#if HC_PLATFORM == HC_PLATFORM_NINTENDO_SWITCH
	PlayFabCoreSwitch::ShutdownPlatform();
#endif

#if defined(PF_UE_GDK_SUPPORT)
#if WITH_EDITOR
	if (IGDKRuntimeModule* GDKRuntimeModule = IGDKRuntimeModule::TryGet())
	{
		GDKRuntimeModule->GetOnInitForPIE().RemoveAll(this);
		GDKRuntimeModule->GetOnTeardownForPIE().RemoveAll(this);
	}
#endif // WITH_EDITOR
	if (bXGameRuntimeInitialized)
	{
		TeardownGDKEnvironment();
		bXGameRuntimeInitialized = false;
	}
#elif defined(PF_GDK_AVAILABLE)
	// If UE GDK Integration doesn't exist, we need to explicitly uninitialize XGameRuntime
	if (bXGameRuntimeInitialized)
	{
		XGameRuntimeUninitialize();
		bXGameRuntimeInitialized = false;
	}
#endif
}

#if defined(PF_GDK_AVAILABLE) || defined(PF_UE_GDK_SUPPORT)
void FPlayFabCore::EnsureXGameRuntimeInitialized()
{
	if (bXGameRuntimeInitialized)
	{
		return;
	}

#if defined(PF_UE_GDK_SUPPORT)
	if (!SetupGDKEnvironment())
	{
		UE_LOG(LogPlayFabUnreal, Fatal, TEXT("Failed to initialize the GDK environment"));
		FPlatformMisc::RequestExit(true);
		return;
	}
#else
	HRESULT hr = XGameRuntimeInitialize();

	if (FAILED(hr)) {
		UE_LOG(LogPlayFabUnreal, Fatal, TEXT("Failed to initialize XGameRuntime. HRESULT: 0x%08X"), hr);
		FPlatformMisc::RequestExit(true);
		return;
	}
#endif

	bXGameRuntimeInitialized = true;
	UE_LOG(LogPlayFabUnreal, Log, TEXT("XGameRuntime initialized successfully"));
}
#endif // PF_GDK_AVAILABLE || PF_UE_GDK_SUPPORT

#if defined(PF_UE_GDK_SUPPORT) && WITH_EDITOR
void FPlayFabCore::OnTeardownForPIE()
{
	FXAsyncTaskManagerSingleton::Get().Shutdown();
	FXAsyncTaskQueue::PlatformTearDown();
	if (bXGameRuntimeInitialized)
	{
		TeardownGDKEnvironment();
		bXGameRuntimeInitialized = false;
	}
}

void FPlayFabCore::OnInitForPIE()
{
	EnsureXGameRuntimeInitialized();
	FXAsyncTaskQueue::PlatformInit();
}
#endif // PF_UE_GDK_SUPPORT && WITH_EDITOR
