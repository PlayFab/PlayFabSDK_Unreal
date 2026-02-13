#include "PlayFabGameSaveModule.h"
#include "Modules/ModuleManager.h"
#include "TypeWrappers.h"

IMPLEMENT_MODULE(FPlayFabGameSave, PlayFabGameSave);

#if !IS_MONOLITHIC
// Define the log category for TypeWrappers. Normally this is defined in PlayFabCoreModule but this needs to be redefined in non-monolithic builds.
DEFINE_LOG_CATEGORY(LogPlayFabTypeWrappers);
#endif // !IS_MONOLITHIC

void FPlayFabGameSave::StartupModule()
{
}

void FPlayFabGameSave::ShutdownModule()
{
}
