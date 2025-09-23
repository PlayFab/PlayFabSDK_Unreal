#include "PlayFabCoreModule.h"
#include "Modules/ModuleManager.h"
#include "Logging.h"
#ifdef PF_GDK_AVAILABLE
#include <XGameRuntimeInit.h>
#endif

IMPLEMENT_MODULE(FPlayFabCore, PlayFabCore);

void FPlayFabCore::StartupModule()
{
// If UE GDK Integration doesn't exist, we need to explicitly initialize XGameRuntime
#if defined(PF_GDK_AVAILABLE)
	HRESULT hr = XGameRuntimeInitialize();

	if (FAILED(hr)) {
		UE_LOG(LogPlayFabUnreal, Fatal, TEXT("Failed to initialize XGameRuntime. HRESULT: 0x%08X"), hr);
		FPlatformMisc::RequestExit(true);
	}
	else
	{
		UE_LOG(LogPlayFabUnreal, Log, TEXT("XGameRuntime initialized successfully"));
	}
#endif
}

void FPlayFabCore::ShutdownModule()
{
// If UE GDK Integration doesn't exist, we need to explicitly uninitialize XGameRuntime
#if defined(PF_GDK_AVAILABLE)
	XGameRuntimeUninitialize();
#endif
}