#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
THIRD_PARTY_INCLUDES_START
#include "httpClient/pal.h"
THIRD_PARTY_INCLUDES_END

class PLAYFABCORE_API FPlayFabCore : public FDefaultModuleImpl
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
