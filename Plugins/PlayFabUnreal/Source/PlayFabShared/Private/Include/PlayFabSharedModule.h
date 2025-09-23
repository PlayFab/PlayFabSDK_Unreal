#pragma once

#include "CoreMinimal.h"
#include "Windows/WindowsHWrapper.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "UObject/ObjectMacros.h"
#include "XAsyncTaskQueueHelpers.h"
#include "Logging.h"
#include "XAsyncTask.h"
#include "XAsyncTaskManager.h"
THIRD_PARTY_INCLUDES_START
#include "httpClient/pal.h"
THIRD_PARTY_INCLUDES_END

class PLAYFABSHARED_API FPlayFabShared : public FDefaultModuleImpl
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
