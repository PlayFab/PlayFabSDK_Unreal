#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#if PLATFORM_WINDOWS || (defined(PLATFORM_XSX) && PLATFORM_XSX) || (defined(PLATFORM_XB1) && PLATFORM_XB1)
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/AllowWindowsPlatformAtomics.h"
#endif
THIRD_PARTY_INCLUDES_START
#include "httpClient/pal.h"
#include <httpClient/httpClient.h>
#include <httpClient/async.h>
THIRD_PARTY_INCLUDES_END
#if PLATFORM_WINDOWS || (defined(PLATFORM_XSX) && PLATFORM_XSX) || (defined(PLATFORM_XB1) && PLATFORM_XB1)
#include "Windows/HideWindowsPlatformAtomics.h"
#include "Windows/HideWindowsPlatformTypes.h"
#endif

class PLAYFABCORE_API FPlayFabCore : public FDefaultModuleImpl
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
#if defined(PF_GDK_AVAILABLE) || defined(PF_UE_GDK_SUPPORT)
	void InitializeXGameRuntime();
#endif // PF_GDK_AVAILABLE || PF_UE_GDK_SUPPORT
};
