#include "PlayFabSharedModule.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_MODULE(FPlayFabShared, PlayFabShared);

void FPlayFabShared::StartupModule()
{
}

void FPlayFabShared::ShutdownModule()
{
	// Cleanup threads and resources when module shuts down
	FXAsyncTaskManagerSingleton::Get().Shutdown();
}