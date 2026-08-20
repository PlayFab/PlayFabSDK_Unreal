//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "OnlineSubsystemPlayFabModule.h"
#include "CoreMinimal.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/Paths.h"
#include "Misc/CommandLine.h"
#include "Modules/ModuleManager.h"
#include "PlayFabHelpers.h"
#include "OnlineSubsystemImpl.h"
#include "OnlineSubsystemModule.h"
#include "OnlineSubsystemNames.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemPlayFab.h"
#include "PlayFabCoreModule.h"
#include "PlayFabHelpers.h"
#include "HAL/PlatformProcess.h"
#include "HAL/FileManager.h"

#if WITH_EDITOR && OSS_PLAYFAB_GDK_SUPPORT
#include "GDKRuntimeModule.h"
#endif // WITH_EDITOR && OSS_PLAYFAB_GDK_SUPPORT

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

#if WITH_EDITOR && OSS_PLAYFAB_GDK_SUPPORT

typedef TWeakPtr<FOnlineSubsystemPlayFab, ESPMode::ThreadSafe> FOnlineSubsystemPlayFabWeakPtr;

// Return a mock PF OSS for the editor instance so that the real PF OSS can be used for the PIE session.
class FMockOnlineSubsystemPlayFab : public FOnlineSubsystemImpl
{
public:
	FMockOnlineSubsystemPlayFab(FName InstanceName) : FOnlineSubsystemImpl(PLAYFAB_SUBSYSTEM, InstanceName)
	{
	}

	virtual FText GetOnlineServiceName() const override
	{
		return FText::GetEmpty();
	}

	virtual FString GetAppId() const override
	{
		return TEXT("");
	}

	IOnlineSessionPtr GetSessionInterface() const
	{
		return nullptr;
	}

	IOnlineFriendsPtr GetFriendsInterface() const
	{
		return nullptr;
	}
	bool Init()
	{
		return true;
	}
};

class FOnlineFactoryPlayFab_ForPIE : public IOnlineFactory
{

private:

	FOnlineSubsystemPlayFabWeakPtr& GetWeakSingleton() const
	{
		static FOnlineSubsystemPlayFabWeakPtr PlayFabSingleton;
		return PlayFabSingleton;
	}

	virtual void DestroySubsystem()
	{
		FOnlineSubsystemPlayFabWeakPtr& PlayFabSingleton = GetWeakSingleton();
		if (PlayFabSingleton.IsValid())
		{
			PlayFabSingleton.Pin()->Shutdown();
			PlayFabSingleton.Reset();
		}
	}

	void OnInitForPIE()
	{
		FOnlineSubsystemPlayFabWeakPtr& PlayFabSingleton = GetWeakSingleton();
		if (PlayFabSingleton.IsValid() && PlayFabSingleton.Pin()->IsEnabled())
		{
			if (!PlayFabSingleton.Pin()->Init())
			{
				UE_LOG_ONLINE(Warning, TEXT("PlayFab API failed to initialize for PIE!"));
				DestroySubsystem();
			}
		}
	}

	void OnTeardownForPIE()
	{
		DestroySubsystem();
	}

public:

	FOnlineFactoryPlayFab_ForPIE()
	{
		IGDKRuntimeModule::Get().GetOnInitForPIE().AddRaw(this, &FOnlineFactoryPlayFab_ForPIE::OnInitForPIE);
		IGDKRuntimeModule::Get().GetOnTeardownForPIE().AddRaw(this, &FOnlineFactoryPlayFab_ForPIE::OnTeardownForPIE);
	}

	virtual ~FOnlineFactoryPlayFab_ForPIE()
	{
		DestroySubsystem();

		if (IGDKRuntimeModule* GDKRuntime = IGDKRuntimeModule::TryGet())
		{
			GDKRuntime->GetOnInitForPIE().RemoveAll(this);
			GDKRuntime->GetOnTeardownForPIE().RemoveAll(this);
		}
	}

	virtual IOnlineSubsystemPtr CreateSubsystem(FName InstanceName) override
	{
		if (InstanceName == FOnlineSubsystemImpl::DefaultInstanceName)
		{
			UE_LOG_ONLINE(Warning, TEXT("PlayFab OSS only available during PIE when running in the editor - returning mock OSS instead"));
			return MakeShared<FMockOnlineSubsystemPlayFab, ESPMode::ThreadSafe>(InstanceName);
		}

		FOnlineSubsystemPlayFabWeakPtr& PlayFabSingleton = GetWeakSingleton();
		if (PlayFabSingleton.IsValid())
		{
			UE_LOG_ONLINE(Warning, TEXT("Can't create more than one instance of PlayFab online subsystem!"));
			return nullptr;
		}

		FOnlineSubsystemPlayFabPtr NewInstance = MakeShared<FOnlineSubsystemPlayFab, ESPMode::ThreadSafe>(InstanceName);
		PlayFabSingleton = NewInstance;

		if (NewInstance->IsEnabled())
		{
			if (!NewInstance->Init())
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

		return NewInstance;
	}
};

#endif // WITH_EDITOR && OSS_PLAYFAB_GDK_SUPPORT

void FOnlineSubsystemPlayFabModule::StartupModule()
{
	FModuleManager::LoadModuleChecked<FPlayFabCore>(TEXT("PlayFabCore"));

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
#if WITH_EDITOR && OSS_PLAYFAB_GDK_SUPPORT
	// Steam OSS does not support PIE so just fallback to the normal factory if the native platform isn't GDK.
	if (IsNativePlatformSubsystemGDK())
	{
		PlayFabFactory = new FOnlineFactoryPlayFab_ForPIE();
	}
	else
	{
		PlayFabFactory = new FOnlineFactoryPlayFab();
	}
#else
	PlayFabFactory = new FOnlineFactoryPlayFab();
#endif // WITH_EDITOR && OSS_PLAYFAB_GDK_SUPPORT

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