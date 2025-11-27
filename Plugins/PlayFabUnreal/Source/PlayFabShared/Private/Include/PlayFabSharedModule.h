#pragma once

#include "CoreMinimal.h"
#ifdef PF_GDK_AVAILABLE
#include "Windows/WindowsHWrapper.h"
#endif
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "UObject/ObjectMacros.h"
THIRD_PARTY_INCLUDES_START
#include "httpClient/pal.h"
#include <httpClient/httpClient.h>
#include <httpClient/async.h>
THIRD_PARTY_INCLUDES_END
#include "XAsyncTaskQueueHelpers.h"
#include "Logging.h"
#include "XAsyncTask.h"
#include "XAsyncTaskManager.h"

class PLAYFABSHARED_API FPlayFabShared : public FDefaultModuleImpl
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
