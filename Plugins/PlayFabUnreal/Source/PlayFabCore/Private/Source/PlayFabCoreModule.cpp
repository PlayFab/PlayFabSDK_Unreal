#include "PlayFabCoreModule.h"
#include "Modules/ModuleManager.h"
#include "Logging.h"
#include "XAsyncTaskQueueHelpers.h"
#include "TypeWrappers.h"
#ifdef PF_UE_GDK_SUPPORT
#include "GDKRuntimeModule.h"
#endif
#ifdef PF_GDK_AVAILABLE
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
#if defined(PF_UE_GDK_SUPPORT)
	IGDKRuntimeModule* GDKRuntimeModule = IGDKRuntimeModule::TryGet();
	if (!GDKRuntimeModule || !GDKRuntimeModule->IsAvailable())
	{
		// The GDKRuntimeModule should have been initialize before this point so if it hasn't then assume it's not going to (Steam) and call XGameRuntimeInitialize ourselves.
		InitializeXGameRuntime();
	}
#elif defined(PF_GDK_AVAILABLE)
	// If UE GDK Integration doesn't exist, we need to explicitly initialize XGameRuntime
	InitializeXGameRuntime();
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
	FXAsyncTaskQueue::PlatformTearDown();

#if HC_PLATFORM == HC_PLATFORM_NINTENDO_SWITCH
	PlayFabCoreSwitch::ShutdownPlatform();
#endif

#if defined(PF_UE_GDK_SUPPORT)
	IGDKRuntimeModule* GDKRuntimeModule = IGDKRuntimeModule::TryGet();
	if (!GDKRuntimeModule || !GDKRuntimeModule->IsAvailable())
	{
		XGameRuntimeUninitialize();
	}
#elif defined(PF_GDK_AVAILABLE)
	// If UE GDK Integration doesn't exist, we need to explicitly uninitialize XGameRuntime
	XGameRuntimeUninitialize();
#endif
}

#if defined(PF_GDK_AVAILABLE) || defined(PF_UE_GDK_SUPPORT)
void FPlayFabCore::InitializeXGameRuntime()
{
	HRESULT hr = XGameRuntimeInitialize();

	if (FAILED(hr)) {
		UE_LOG(LogPlayFabUnreal, Fatal, TEXT("Failed to initialize XGameRuntime. HRESULT: 0x%08X"), hr);
		FPlatformMisc::RequestExit(true);
	}
	else
	{
		UE_LOG(LogPlayFabUnreal, Log, TEXT("XGameRuntime initialized successfully"));
	}
}
#endif // PF_GDK_AVAILABLE || PF_UE_GDK_SUPPORT
