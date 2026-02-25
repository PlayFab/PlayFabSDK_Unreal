# PlayFab Unreal Engine Plugin - Getting Started Guide

## Overview

The PlayFab Unreal Engine Plugin provides comprehensive integration with PlayFab's backend services for game developers. This plugin includes two main components:

- **PlayFabUnreal**: Core PlayFab functionality containing:
  - **PlayFab Core**: Authentication and event pipeline (telemetry) services
  - **PlayFab Services**: Game features including leaderboards, economy, player data, statistics, and catalog management
  - **PlayFab Game Saves**: Cross-platform cloud game saves functionality
- **OnlineSubsystemPlayfab**: PlayFab Party and Multiplayer networking integration

## Prerequisites

Before integrating the PlayFab Unreal Plugin into your project, ensure you have the following:

### Software Requirements
- **[Game Development Kit](https://learn.microsoft.com/en-us/gaming/gdk/) 2510 Update 1 or later**  installed with legacy layouts
- **Unreal Engine 5.7** (either public version or built from source)
- **PlayFab Account** with a configured title

### Platform Support
The plugin supports the following platforms:
- **Win64** (Windows)
- **WinGDK** (Windows)
- **XSX** (Xbox Series X)
- **XB1** (Xbox One)
- **PS5** *

\* PS5 Platform support is currently in Private Preview and is available only to select partners. To request access, please follow the official process outlined in this page: [Request access for secured SDKs and samples](https://review.learn.microsoft.com/en-us/gaming/playfab/sdks/request-access-for-sdks-samples?branch=main).

## Setup

### (GDK Platforms) Add 2510 GDK Support to UE 5.7

The PlayFab plugins require the 2510 GDK but Unreal Engine 5.7 does not support it out of the box so you'll need to make the following changes to `Engine\Platforms\GDK\Config\GDK_SDK.json`:
* Set `MaxVersion` to `251001` or above
* Set `MinVersion` to `251001` or below
* Set `MainVersion` somewhere in between like `251001`

### PlayFabUnreal Plugin Only

### 1. Copy Plugin Files

Copy the [`Plugins/PlayFabUnreal`](Plugins/PlayFabUnreal) folder from this repository to your game project's `Plugins` in the root directory. Your project structure should look like:

```
YourGameProject/
├── YourGameProject.uproject
├── Plugins/
│   └── PlayFabUnreal/
└── ...
```

### 2. Enable PlayFabUnreal Plugin

Add the following element to the `Plugins` key in your `.uproject` file:

````json
{
    "Name": "PlayFabUnreal",
    "Enabled": true
}
````

### 3. Add Module Dependencies

Add the following dependencies to your project's `.Build.cs` file:

````cpp
PrivateDependencyModuleNames.AddRange(new string[] {
    "PlayFabShared",
    "PlayFabCore",
    "PlayFabServices",          // If using PlayFab Services
    "PlayFabGameSave",          // If using PlayFab Game Saves
    "PlayFabUnreal",
});
````

### OnlineSubsystemPlayFab Plugin

### 1. Copy Plugin Files

Copy the entire [`Plugins`](Plugins) folder from this repository to your game project's root directory. Your project structure should look like:

```
YourGameProject/
├── YourGameProject.uproject
├── Plugins/
│   ├── OnlineSubsystemPlayfab/
│   └── PlayFabUnreal/
└── ...
```

### 2. Enable OnlineSubsystemPlayFab Plugin

Add the following element to the `Plugins` key in your `.uproject` file and remove any irrelevant platforms for your project:

````json
{
    "Name": "OnlineSubsystemPlayFab",
    "Enabled": true,
    "SupportedTargetPlatforms": [
        "XB1",
        "WinGDK",
        "XSX",
        "Win64"
    ],
    "PlatformAllowList": [
        "XB1",
        "WinGDK",
        "XSX",
        "Win64"
    ]
}
````

### 3. Configure Your Project

Add or update the following sections in your `DefaultEngine.ini` or platform's `Engine.ini`.
* Replace the INI sections in the config if they already exist (for example,`[Engine.GameEngine] NetDriverDefinitions`) with the ones presented in the following sections.
* Ensure you replace all `<REPLACE ME>` values with your data.

````ini
[OnlineSubsystemPlayFab] 
bEnabled=true 
PlayFabTitleID=<REPLACE ME with your PlayFab title ID> 
MaxDeviceCount=<REPLACE ME with your max player count (note: split screen is still 1 device). In the example of an 8 player game, this would be 8.> 
MaxDevicesPerUserCount=<REPLACE ME with your max player count per box (note: split screen is still 1 device) In the example of an 8 player game, this would be 1.> 
MaxEndpointsPerDeviceCount=<REPLACE ME with your max player count per box (note: split screen is still 1 device)  In the example of an 8 player game, this would be 1.> 
MaxUserCount=<REPLACE ME with your max player count (note: split screen is still 1 device)  In the example of an 8 player game, this would be 8.> 
MaxUsersPerDeviceCount=<REPLACE ME with your max player count per box (note: split screen is still 1 device)  In the example of an 8 player game, this would be 1.> 
DirectPeerConnectivityOptions=<REPLACE ME with your connectivity options, in the form of an array of strings. The default case corresponds to the following: 
+DirectPeerConnectivityOptions=AnyPlatformType 
+DirectPeerConnectivityOptions=AnyEntityLoginProvider. 
If you want to disable P2P and use cloud relay instead, set DirectPeerConnectivityOptions=None> 
bHasPlayFabVoiceEnabled=<REPLACE ME with true/false> 

[/Script/OnlineSubsystemPlayFab.PlayFabNetDriver] 
NetConnectionClassName="OnlineSubsystemPlayFab.PlayFabNetConnection" 
ReplicationDriverClassName="<REPLACE ME with your existing replication driver class name or skip if the game does not have a replication driver class (https://docs.unrealengine.com/5.7/en-US/replication-graph-in-unreal-engine/).>"
ConnectionTimeout=15.0 
InitialConnectTimeout=30.0 

[/Script/Engine.GameEngine] 
!NetDriverDefinitions=ClearArray 
+NetDriverDefinitions=(DefName="GameNetDriver",DriverClassName="/Script/OnlineSubsystemPlayFab.PlayFabNetDriver",DriverClassNameFallback="OnlineSubsystemUtils.IpNetDriver") 
````

### 4. Delete Legacy OnlineSubsystemPlayFab Plugin

If you're migrating from the legacy version of the OnlineSubsystemPlayFab plugin then you will need to delete the legacy files which would be at `Engine\Plugins\Online\OnlineSubsystemPlayFab`.

### Platform Specific Considerations

#### GDK

When developing games with the GDK, set up the platform services by updating the platform’s Engine.ini with:

````ini
[OnlineSubsystem]
DefaultPlatformService=PlayFab
NativePlatformService=GDK
````

To learn more about using the GDK with the Win64 platform, refer to [this page](https://dev.epicgames.com/documentation/en-us/unreal-engine/microsoft-gdk-plugins-for-unreal-engine) for details about the MSGamingRuntime plugin. 

#### Steam

If you're developing games for Win64 with Steam then update your platform services in the `WindowsEngine.ini` with:

````ini
[OnlineSubsystem]
DefaultPlatformService=PlayFab
NativePlatformService=Steam
````

#### Cross-platform

If your game uses PlayFab's cross-platform networking support, define which platforms you permit to connect.

````ini
[/Script/OnlineSubsystemUtils.OnlineEngineInterfaceImpl]
!CompatibleUniqueNetIdTypes=ClearArray
+CompatibleUniqueNetIdTypes=STEAM
+CompatibleUniqueNetIdTypes=GDK
````

All platforms allow VoIP by default. To disable VoIP for a specific platform, add the platform model name to your Unreal Engine configuration file as shown in the following example.

````ini
[OnlineSubsystemPlayFabVoiceChatDisabledPlatforms]
!Platforms=ClearArray
+Platforms=WIN64
+Platforms=STEAM
````

#### Single Package for Multiple Stores

Instead of creating multiple packages for different stores, a studio may prefer to have a single package that can be shipped in multiple stores and that typically requires slightly different settings. The OSS can support this through the `-PlayFabConfigOverridePrefix=<Prefix>` command line argument.

The minimal steps are as follows along with an example for Win64 with Steam and GDK. You can specify additional settings in the Engine.ini and you can specify additional ini files as well like Game.ini as long as they have the same prefix.
1. In your game's default or platform Engine.ini, `+AdditionalModulesToLoad=OnlineSubsystemPlayFab` under the`[OnlineSubsystem]` section.
    * Update `DefaultEngine.ini` with
        ```ini
        [OnlineSubsystem]
        +AdditionalModulesToLoad=OnlineSubsystemPlayFab
        ```
1. In your platform's Engine.ini, set `NativePlatformService` to your default value. 
    * Set `NativePlatformService=Steam` in `WindowsEngine.ini`  
1. Under OnlineSubsystemPlayFab/Config, create a `<Prefix>Engine.ini`.
    * Create the file `OnlineSubsystemPlayFab/Config/GDKEngine.ini`
1. In the newly created file, set `NativePlatformService` to another value.
    * Update `OnlineSubsystemPlayFab/Config/GDKEngine.ini` with
        ```ini
        [OnlineSubsystem]
        NativePlatformService=GDK
        ```
1. Cook and package your game as normal.
1. Running the game without the `PlayFabConfigOverridePrefix` argument will use the default settings as normal but running with the argument will apply those additional settings on top of the default.
    * `./ShooterGame.exe -PlayFabConfigOverridePrefix=GDK` will effectively set `NativePlatformService=GDK`

## Preprocessor Macros

The PlayFab Unreal plugin uses several preprocessor macros to conditionally compile features based on platform support and available authentication methods. Understanding these macros is crucial for writing platform-specific code.

### GDK Support Macros

#### `PF_UE_GDK_SUPPORT`

This macro indicates that Unreal Engine's GDK integration is available and supported. It's automatically defined when:
- The Unreal Engine build includes GDK support (WinGDK platform target available)
- The GDKRuntime module is accessible
- All GDK wrappers and integration features are available

This macro enables access to GDK-specific Unreal Engine features like the GDKRuntime module.

#### `PF_GDK_AVAILABLE`

This macro indicates that the Gaming Development Kit (GDK) is installed on the development machine. It's automatically defined when:
- GDK is detected on the system (either through UE reflection or environment variables)
- GDK libraries and headers are accessible for linking
- The system is capable of building GDK-enabled applications

This macro enables access to GDK libraries and functionality, regardless of Unreal Engine's GDK integration status.

### Macro Usage Patterns

These macros work together to provide different levels of GDK functionality:

````cpp
// Check if GDK is available on the system
#ifdef PF_GDK_AVAILABLE
    // Can use GDK libraries and PlayFab GDK features
    // Available on any system with GDK installed
#endif

// Check if Unreal Engine has GDK integration
#ifdef PF_UE_GDK_SUPPORT  
    // Can use Unreal's GDK modules like GDKRuntime
    // Only available when building with UE GDK support
    #include "GDKRuntimeModule.h"
    
    // Xbox authentication and GDK features
    auto userHandles = IGDKRuntimeModule::Get().GetAllUserHandles();
    if (!userHandles.IsEmpty())
    {
        // Xbox authentication available
        FPFLocalUserCreateHandleWithXboxUser(
            ServiceConfigHandle.Get(), 
            userHandles[0], 
            nullptr, 
            &LocalUserHandle);
    }
    else
    {
        // Fallback to custom ID authentication
        FPFLocalUserCreateHandleWithPersistedLocalId(
            ServiceConfigHandle.Get(), 
            customId, 
            nullptr, 
            &LocalUserHandle);
    }
#else
    // Fallback authentication (Custom ID, etc.)
    FPFLocalUserCreateHandleWithPersistedLocalId(
        ServiceConfigHandle.Get(), 
        customId, 
        nullptr, 
        &LocalUserHandle);
#endif
````

**Note**: `PF_UE_GDK_SUPPORT` requires `PF_GDK_AVAILABLE` to be meaningful, as Unreal's GDK integration depends on having GDK installed on the system. When `PF_UE_GDK_SUPPORT` is available, Xbox authentication can be used if Xbox user handles are available through the GDKRuntime module.

## Available Services

The PlayFab Unreal Plugin provides access to the following services:

- **Authentication**: Player login and identity management
- **Account Management**: Player account operations
- **Player Data**: Save and retrieve player-specific data
- **Statistics & Leaderboards**: Track and display player achievements
- **Inventory**: Manage virtual items and currencies
- **Friends**: Social features and friend lists
- **Groups**: Guild and clan functionality
- **Multiplayer**: Matchmaking and session management
- **Game Saves**: Cloud save functionality
- **Cloud Script**: Execute server-side logic
- **Catalog**: Game economy and item management

## Getting Started with Code

For detailed implementation examples, configuration samples, and step-by-step code walkthroughs, see the [Code Examples](CODE_EXAMPLES.md) document.

The code examples cover:
- Xbox and Custom ID authentication
- Service initialization and configuration
- PlayFab Game Saves implementation
- Event pipeline setup for telemetry
- Player data and statistics management
- Proper cleanup and resource management

## Additional Resources

- [PlayFab Documentation](https://docs.microsoft.com/gaming/playfab/)
- [PlayFab REST API Reference](https://docs.microsoft.com/rest/api/playfab/)
- [Unreal Engine GDK Documentation](https://docs.unrealengine.com/5.0/gdk/)

## Troubleshooting

### Common Issues

1. **Authentication Failures**: Verify your Title ID is correct in configuration
2. **Missing MicrosoftGame.config**: Ensure you've copied the config file for Win64 builds
3. **Game Saves Not Working**: Verify you're using WinGDK or Xbox platform targets
4. **Module Loading Errors**: Check that all required dependencies are listed in your Build.cs file
5. **No Xbox User Handles Found**: If `IGDKRuntimeModule::Get().GetAllUserHandles()` returns empty, check:
   - **Missing Xbox Configuration**: Ensure Xbox-specific configuration is properly set in your `DefaultEngine.ini` (see Code Examples for details)
   - **Wrong Sandbox**: If using a sandbox account, verify you're in the correct sandbox using the [XblPcSandbox utility](https://learn.microsoft.com/en-us/gaming/gdk/docs/tools/tools-services/live-pc-sandbox-switcher)
   - **Not Logged In**: Make sure you're logged in with your Xbox test account in both the Microsoft Store and Xbox app
   - **Missing GDK Support**: Ensure `PF_UE_GDK_SUPPORT` is defined, which indicates Unreal Engine's GDK integration is available

For additional support, refer to the PlayFab community forums and documentation.


#### Runtime dependency Party.dll is configured to be staged from X and Y

When using the PlayFab Online Subsystem, you may encounter the following runtime error: 

````
Runtime dependency 'Party.dll' is configured to be staged from 'C:\Program Files (x86)\Microsoft GDK\251001\GRDK\ExtensionLibraries\PlayFab.Party.Cpp\Redist\x64\Party.dll' and 'C:\Program Files (x86)\Microsoft GDK\251001\windows\bin\x64\Party.dll'
````

Some of these steps will be unnecessary once UE 5.7 officially supports the new GDK layout but until then you can make the following modifications if applicable to work around the issue.

* Disable `PlayFabParty` in `\Engine\Platforms\GDK\Plugins\Online\OnlineSubsystemGDK\OnlineSubsystemGDK.uplugin`: 

````json
{
    "Name": "PlayFabParty",
    "Enabled": false
}
````

* Disable `PlayFabParty` in your project's `.uplugin` file like in the previous point.
* Comment out the existing `PlayFabParty` dependency in `\Engine\Platforms\GDK\Plugins\Online\OnlineSubsystemGDK\Source\OnlineSubsystemGDK.Build.cs`:

````cs
if (Target.bCompileAgainstEngine)
{
    // PublicDependencyModuleNames.Add("PlayFabParty");
}
````

* Disable Unreal Engine's built-in PlayFab matchmaking if enabled by editing the platform's `Engine.ini` with:

````ini
[PlayFab]
EnablePlayfabMatchmaking=false
````

* Disable `PlayFabParty` if it's being enabled in one of your target files:
````cs
public class YourGameTarget_XSX : YourGame
{
    public YourGameTarget_XSX(TargetInfo Target) : base(Target)
    {
        EnablePlugins.AddRange(new string[]
        {
            "OnlineSubsystemGDK",
            // "PlayFabParty"
        });
    }
}
````

#### Plugin 'OnlineSubsystemPlayFab' failed to load
You may encounter the following error when launching the editor:

`Plugin 'OnlineSubsystemPlayFab' failed to load because module 'OnlineSubsystemPlayFab' could not be loaded. There may be an operating system error or the module may not be properly set up.`

The code will be updated in the future once the OnlineSubsystemGDK plugin has been made publicly available but until then you will need to make the following change.

Update the `OnlineSubsystemGDK` plugin’s `PlatformAllowList` field with `Win64` in `OnlineSubsystemPlayFab/OnlineSubsystemPlayFab.uplugin`:

````json
{
    "Name": "OnlineSubsystemGDK",
    "Enabled": true,
    "PlatformAllowList": [
        "XSX",
        "WinGDK",
        "XB1",
        "Win64"
    ]
}
````

#### Unhandled exception throw: read access violation - handle was nullptr
You may encounter this error if the GDKRuntime module is shutdown before OnlineSubsystemPlayFab. An example is if your project is configured to use `OnlineSubsystemSteam` and you have the `MSGamingRuntime` plugin enabled.

This will be addressed in an upcoming update to the PlayFab unified SDK in the GDK but until then you can enable the following lines in `FOnlineSubsystemPlayFab::IsEnabled()` to force the correct module load order:

````cpp
if (bEnabled)
{
	IGDKRuntimeModule::Get();
}
````