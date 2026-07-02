//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "OnlineSubsystemPlayFabModule.h"
#include "CoreMinimal.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/Paths.h"
#include "Misc/CommandLine.h"
#include "Modules/ModuleManager.h"
#include "OnlineSubsystemModule.h"
#include "OnlineSubsystemNames.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemPlayFab.h"
#include "PlayFabHelpers.h"
#include "HAL/PlatformProcess.h"
#include "HAL/FileManager.h"

IMPLEMENT_MODULE(FOnlineSubsystemPlayFabModule, OnlineSubsystemPlayFab);

 // Class responsible for creating instance(s) of the subsystem
class FOnlineFactoryPlayFab : public IOnlineFactory
{

private:

	// Single instantiation of the PlayFab interface
	FOnlineSubsystemPlayFabPtr& GetSingleton() const
	{
		static FOnlineSubsystemPlayFabPtr PlayFabSingleton;
		return PlayFabSingleton;
	}

	virtual void DestroySubsystem()
	{
		FOnlineSubsystemPlayFabPtr& PlayFabSingleton = GetSingleton();
		if (PlayFabSingleton.IsValid())
		{
			PlayFabSingleton->Shutdown();
			PlayFabSingleton.Reset();
		}
	}

public:

	FOnlineFactoryPlayFab() {}
	virtual ~FOnlineFactoryPlayFab() 
	{
		DestroySubsystem();
	}

	virtual IOnlineSubsystemPtr CreateSubsystem(FName InstanceName) override
	{
		FOnlineSubsystemPlayFabPtr& PlayFabSingleton = GetSingleton();
		if (PlayFabSingleton.IsValid())
		{
			UE_LOG_ONLINE(Warning, TEXT("Can't create more than one instance of PlayFab online subsystem!"));
			return nullptr;
		}

		PlayFabSingleton = MakeShared<FOnlineSubsystemPlayFab, ESPMode::ThreadSafe>(InstanceName);
		if (PlayFabSingleton->IsEnabled())
		{
			if (!PlayFabSingleton->Init())
			{
				UE_LOG_ONLINE(Warning, TEXT("PlayFab API failed to initialize!"));
				DestroySubsystem();
				return nullptr;
			}
		}
		else
		{
			UE_LOG_ONLINE(Warning, TEXT("PlayFab API disabled!"));
			DestroySubsystem();
			return nullptr;
		}

		return PlayFabSingleton;
	}
};

void FOnlineSubsystemPlayFabModule::StartupModule()
{
	// Check if we should apply any config overrides specified by the command line
	FString PlayFabConfigOverridePrefix;
	if (FParse::Value(FCommandLine::Get(), TEXT("PlayFabConfigOverridePrefix="), PlayFabConfigOverridePrefix))
	{
		const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("OnlineSubsystemPlayFab"));
		const FString PluginConfigDir = FPaths::GetPath(Plugin->GetDescriptorFileName()) / TEXT("Config/");

		int32 ConfigsFound = 0;
		TArray<FString> PluginConfigs;
		IFileManager::Get().FindFiles(PluginConfigs, *PluginConfigDir, TEXT("ini"));
		for (const FString& ConfigFile : PluginConfigs)
		{
			if (!ConfigFile.StartsWith(PlayFabConfigOverridePrefix, ESearchCase::IgnoreCase))
			{
				continue;
			}

			// Remove the prefix from the config file to get the usable name.
			FString RenamedConfigFile(ConfigFile);
			RenamedConfigFile.ReplaceInline(*PlayFabConfigOverridePrefix, TEXT(""), ESearchCase::IgnoreCase);

			// Use GetConfigFilename to find the proper config file to combine into, since it manages command line overrides and path sanitization
			FString PluginConfigFilename = GConfig->GetConfigFilename(*FPaths::GetBaseFilename(RenamedConfigFile));
			FConfigFile* FoundConfig = GConfig->FindConfigFile(PluginConfigFilename);
			if (FoundConfig != nullptr)
			{
				FoundConfig->Branch->AddDynamicLayerToHierarchy(FPaths::Combine(PluginConfigDir, ConfigFile));
				ConfigsFound++;
			}
		}

		if (ConfigsFound == 0)
		{
			UE_LOG_ONLINE(Warning, TEXT("[FOnlineSubsystemPlayFabModule::StartupModule] No configuration overrides found but the PlayFabConfigOverridePrefix command line argument was specified!"));
		}
	}

	// Create and register our singleton factory with the main online subsystem for easy access
	PlayFabFactory = new FOnlineFactoryPlayFab();

	FOnlineSubsystemModule& OSS = FModuleManager::GetModuleChecked<FOnlineSubsystemModule>("OnlineSubsystem");
	OSS.RegisterPlatformService(PLAYFAB_SUBSYSTEM, PlayFabFactory);
}

void FOnlineSubsystemPlayFabModule::ShutdownModule()
{
	FOnlineSubsystemModule& OSS = FModuleManager::GetModuleChecked<FOnlineSubsystemModule>("OnlineSubsystem");
	OSS.UnregisterPlatformService(PLAYFAB_SUBSYSTEM);

	delete PlayFabFactory;
	PlayFabFactory = nullptr;
}