#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
THIRD_PARTY_INCLUDES_START
#include "httpClient/pal.h"
#include <httpClient/httpClient.h>
#include <httpClient/async.h>
THIRD_PARTY_INCLUDES_END

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
