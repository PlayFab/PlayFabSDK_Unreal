// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlayFabUnreal.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/Paths.h"
#include "HAL/PlatformProcess.h"
#include <vector>
#include <XAsync.h>
#include <Modules/ModuleManager.h>

#define LOCTEXT_NAMESPACE "FPlayFabUnrealModule"

void FPlayFabUnrealModule::StartupModule()
{
}

void FPlayFabUnrealModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FPlayFabUnrealModule, PlayFabUnreal)