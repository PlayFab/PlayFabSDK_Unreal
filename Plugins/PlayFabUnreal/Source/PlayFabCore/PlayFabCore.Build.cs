using System;
using System.IO;
using System.Linq;
using System.Reflection;
using UnrealBuildBase;
using UnrealBuildTool;
using static PlayFabShared.PlayFabGDKUtilities;

public class PlayFabCore : ModuleRules
{
    #region PlayFab GDK Utilities
    /// <summary>
    /// Shared utilities for GDK detection and fallback mechanisms across all PlayFab Build.cs files
    /// NOTE: This region should be copied identically to all Build.cs files
    /// </summary>

    // Because GDK platform determination relies on a type, GDKExports" that only exists in GDK enabled builds of the UE, we use reflection to dynamically
    // look for the existence of the GDKExports type and expose the needed methods here via MethodInfo.
    public static class GDKExports
    {
        private static Type ReflectedType;
        private static MethodInfo GetCurrentGSDKDirMethodInfo = null;
        private static MethodInfo GetGDKVersionNumberMethodInfo = null;
        private static bool IsAvailable = false;

        static GDKExports()
        {
            try
            {
                ReflectedType = FindType();
                if (ReflectedType != null)
                {
                    GetCurrentGSDKDirMethodInfo = ReflectedType.GetMethod("GetCurrentGSDKDir", BindingFlags.Static | BindingFlags.Public | BindingFlags.FlattenHierarchy);
                    GetGDKVersionNumberMethodInfo = ReflectedType.GetMethod("GetGDKVersionNumber", BindingFlags.Static | BindingFlags.Public | BindingFlags.FlattenHierarchy);
                    IsAvailable = GetCurrentGSDKDirMethodInfo != null && GetGDKVersionNumberMethodInfo != null;
                }
            }
            catch
            {
                IsAvailable = false;
            }
        }

        private static Type FindType()
        {
            try
            {
                return AppDomain.CurrentDomain.GetAssemblies()
                        .FirstOrDefault(x => x.GetName().Name.Equals("UnrealBuildTool"))
                        ?.GetTypes()
                        ?.FirstOrDefault(x => x.Name.Equals("GDKExports"));
            }
            catch
            {
                return null;
            }
        }

        public static string GetCurrentGSDKDir()
        {
            if (!IsAvailable)
                throw new InvalidOperationException("GDKExports is not available. This engine build does not have GDK support.");

            try
            {
                string result = (string)GetCurrentGSDKDirMethodInfo.Invoke(null, null);
                if (string.IsNullOrEmpty(result))
                    throw new InvalidOperationException("GDK path is not configured or GDK is not installed.");
                return result;
            }
            catch (Exception ex)
            {
                throw new InvalidOperationException($"Failed to get GDK directory: {ex.Message}", ex);
            }
        }

        public static int GetGDKVersionNumber()
        {
            if (!IsAvailable)
                throw new InvalidOperationException("GDKExports is not available. This engine build does not have GDK support.");

            try
            {
                int? result = (int?)GetGDKVersionNumberMethodInfo.Invoke(null, null);
                if (!result.HasValue)
                    throw new InvalidOperationException("GDK version could not be determined.");
                return result.Value;
            }
            catch (Exception ex)
            {
                throw new InvalidOperationException($"Failed to get GDK version: {ex.Message}", ex);
            }
        }

        public static bool IsGDKAvailable => IsAvailable;
    }

    // Fallback GDK detection using environment variables
    public static class GDKFallback
    {
        public static string GetGDKPath()
        {
			string gdkPath = Environment.GetEnvironmentVariable("GameDKCoreLatest") ?? Environment.GetEnvironmentVariable("GameDKXboxLatest");

			if (string.IsNullOrEmpty(gdkPath))
            {
				throw new InvalidOperationException("GameDKCoreLatest and/or GameDKXboxLatest environment variables are not set. Please ensure GDK is correctly installed.");
			}

			if (!Directory.Exists(gdkPath))
            {
                throw new DirectoryNotFoundException($"GDK directory does not exist: {gdkPath}. Please verify GDK installation.");
            }

            return gdkPath;
        }

        public static int GetGDKVersion()
        {
            string gdkPath = GetGDKPath(); // This will throw if path is invalid

            try
            {
                // Extract version from path like "C:\Program Files (x86)\Microsoft GDK\251000\"
                // Split by directory separator and find the numeric part
                string[] pathParts = gdkPath.TrimEnd('\\', '/').Split('\\', '/');

                for (int i = pathParts.Length - 1; i >= 0; i--)
                {
                    if (int.TryParse(pathParts[i], out int version))
                    {
                        return version;
                    }
                }

                throw new InvalidOperationException($"Could not extract GDK version from path: {gdkPath}. Expected path format: 'C:\\Program Files (x86)\\Microsoft GDK\\[VERSION]\\'");
            }
            catch (Exception ex) when (!(ex is InvalidOperationException))
            {
                throw new InvalidOperationException($"Failed to parse GDK version from path: {gdkPath}. Error: {ex.Message}", ex);
            }
        }
    }

    public static class PlayFabGDKUtilities
    {
        /// <summary>
        /// Helper method to get GDK path using the fallback pattern (try GDKExports first, then environment variables)
        /// </summary>
        /// <param name="moduleName">Name of the calling module for logging purposes</param>
        /// <returns>The GDK path</returns>
        public static string GetGDKPathWithFallback(string moduleName)
        {
            try
            {
                if (GDKExports.IsGDKAvailable)
                {
                    return GDKExports.GetCurrentGSDKDir();
                }
                else
                {
                    throw new InvalidOperationException("GDK not available via reflection, trying fallback method");
                }
            }
            catch
            {
                try
                {
                    // Fallback to environment variable detection
                    string gdkPath = GDKFallback.GetGDKPath();
                    Console.WriteLine($"{moduleName}: Using GDK fallback detection - Path: {gdkPath}");
                    return gdkPath;
                }
                catch (Exception fallbackEx)
                {
                    throw new InvalidOperationException($"{moduleName}: Neither GDK nor fallback detection available: {fallbackEx.Message}");
                }
            }
        }

        /// <summary>
        /// Helper method to get GDK version using the fallback pattern (try GDKExports first, then environment variables)
        /// </summary>
        /// <param name="moduleName">Name of the calling module for logging purposes</param>
        /// <returns>The GDK version number</returns>
        public static int GetGDKVersionWithFallback(string moduleName)
        {
            try
            {
                if (GDKExports.IsGDKAvailable)
                {
                    return GDKExports.GetGDKVersionNumber();
                }
                else
                {
                    throw new InvalidOperationException("GDK not available via reflection, trying fallback method");
                }
            }
            catch
            {
                try
                {
                    // Fallback to environment variable detection
                    int gdkVersion = GDKFallback.GetGDKVersion();
                    Console.WriteLine($"{moduleName}: Using GDK fallback detection - Version: {gdkVersion}");
                    return gdkVersion;
                }
                catch (Exception fallbackEx)
                {
                    throw new InvalidOperationException($"{moduleName}: Neither GDK nor fallback detection available: {fallbackEx.Message}");
                }
            }
        }
    }
    #endregion

    private class NuGetPackageLoader
    {
        public class NuGetPackageInformation
        {
            public string UnifiedSDKPackagePath = string.Empty;
        }

        // If want specific version to use, can specify the version in the packages.config file.
        public void ParsingNuGetPackage(ref string PlatformDir, ref NuGetPackageInformation PackageInfo)
        {
            string[] Lines = System.IO.File.ReadAllLines(Path.Combine(PlatformDir, "packages.config"));
            foreach (string Line in Lines)
            {
                Int32 BeginOfString = Line.IndexOf("Microsoft.PlayFab", 0);
                if (BeginOfString > -1)
                {
                    Int32 EndOfString = Line.IndexOf("\"", BeginOfString);
                    string Id = Line.Substring(BeginOfString, EndOfString - BeginOfString);

                    const string versionString = "version=\"";
                    BeginOfString = Line.IndexOf(versionString, 0);
                    if (BeginOfString > -1)
                    {
                        BeginOfString += versionString.Length;
                        EndOfString = Line.IndexOf("\"", BeginOfString);
                        string Version = Line.Substring(BeginOfString, EndOfString - BeginOfString);

                        if (Id.IndexOf("UnifiedSDK", 0) > -1)
                        {
                            PackageInfo.UnifiedSDKPackagePath = Id + "." + Version;
                        }
                        else
                        {
                            throw new BuildException("Unknown package id in package.config file.");
                        }
                    }
                }
            }
            if (PackageInfo.UnifiedSDKPackagePath.Length == 0)
            {
                throw new BuildException("Can't find PlayFab Unified SDK package infomation in package.config file.");
            }

            LogPlayFabCore($"Unified SDK={PackageInfo.UnifiedSDKPackagePath}");
        }
    }

    private static void LogPlayFabCore(string message)
    {
        Console.WriteLine($"[PlayFabCore] {message}");
    }

    public PlayFabCore(ReadOnlyTargetRules Target) : base(Target)
    {
        LogPlayFabCore($"Loading module for target: {Target.Name}, Platform: {Target.Platform}, Configuration: {Target.Configuration}");
        LogPlayFabCore($"Module directory: {ModuleDirectory}");
        
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        bAllowConfidentialPlatformDefines = true;

        PublicIncludePathModuleNames.AddRange(
            new string[] {
                "Core",
                "CoreUObject",
                "Engine"
            }
        );

        PublicDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CoreUObject",
                "Engine",
                "PlayFabShared"
            }
        );
        
        LogPlayFabCore($"Added dependencies: {string.Join(", ", PublicDependencyModuleNames)}");

        PrivateIncludePaths.AddRange(
            new string[] {
                Path.Combine(ModuleDirectory, "Private/Include"),
                Path.Combine(ModuleDirectory, "Private/Include/Generated")
            }
        );

        PublicIncludePaths.AddRange(
            new string[] {
                // PlayFabShared Headers
                Path.Combine(ModuleDirectory, "../PlayFabShared/Private/Include"),

                // PlayFabCore Headers
                Path.Combine(ModuleDirectory, "../PlayFabCore/Public"),
                Path.Combine(ModuleDirectory, "../PlayFabCore/Public/Generated"),
                Path.Combine(ModuleDirectory, "../PlayFabCore/Private/Include"),
                Path.Combine(ModuleDirectory, "../PlayFabCore/Private/Include/Generated"),
                Path.Combine(ModuleDirectory, "../PlayFabCore/PlatformSpecific"),
            }
        );

        PublicSystemIncludePaths.AddRange(
            new string[] {
                Path.Combine(EngineDirectory, "Source/Runtime/Core/Public"),
                Path.Combine(EngineDirectory, "Source/Runtime/CoreUObject/Public"),
                Path.Combine(EngineDirectory, "Source/Runtime/Engine/Classes")
            }
        );

        ConfigureForPlatform(Target);
    }

    private void ConfigureForPlatform(ReadOnlyTargetRules Target)
    {
        LogPlayFabCore($"Configuring for platform: {Target.Platform}");
        
        // GDK Platform
        if (Target.Platform.ToString() == "WinGDK" || Target.Platform.ToString() == "XSX" || Target.Platform.ToString() == "XB1")
        {
            LogPlayFabCore("Using GDK platform configuration");
            ConfigureForGDKPlatform(Target.Platform.ToString() == "WinGDK" ? "windows" : "xbox");
            return;
        }

        // Switch / Switch2 Platform
        if (Target.Platform.ToString() == "Switch" || Target.Platform.ToString() == "Switch2")
        {
            LogPlayFabCore($"Using {Target.Platform} platform configuration");
            ConfigureForSwitchPlatform(Target.Platform.ToString());
            return;
        }

        // Windows Platform
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            LogPlayFabCore("Using Windows platform configuration");
            ConfigureForWindowsPlatform();
            return;
        }

        // PS4 Platform
        if (Target.Platform.ToString() == "PS4")
        {
            LogPlayFabCore("Using PlayStation 4 platform configuration");
            ConfigureForPlayStation4Platform();
            return;
        }

        // PS5 Platform
        if (Target.Platform.ToString() == "PS5")
        {
            LogPlayFabCore("Using PlayStation 5 platform configuration");
            ConfigureForPlayStation5Platform();
            return;
        }

        throw new PlatformNotSupportedException(Target.Platform.ToString() + " is not supported.");
    }

    private void ConfigureForWindowsPlatform()
    {
        LogPlayFabCore("Configuring PlayFabCore for Windows Platform");
        
        LogPlayFabCore("Adding platform definitions for Windows");
        PublicDefinitions.Add("HC_PLATFORM=HC_PLATFORM_GDK");
        PublicDefinitions.Add("HC_DATAMODEL=HC_DATAMODEL_LLP64");
        LogPlayFabCore("Added definitions: HC_PLATFORM=HC_PLATFORM_GDK, HC_DATAMODEL=HC_DATAMODEL_LLP64");

		// If Unreal GDK Flavor is installed
		MethodInfo IsGDKEditionValidFunction = System.Type.GetType("GRDK, UE5Rules", false)?.GetMethod("IsGDKEditionValid", BindingFlags.Public | BindingFlags.Static);
		bool bHasValidGDK = (IsGDKEditionValidFunction != null) && (bool)IsGDKEditionValidFunction.Invoke(null, null);
        
        if (bHasValidGDK)
        {
            LogPlayFabCore("Unreal GDK Flavor detected - adding GDK support");
            PublicIncludePathModuleNames.Add("GDKRuntime");
            PublicDependencyModuleNames.Add("XCurl");
            PublicDefinitions.Add("PF_UE_GDK_SUPPORT");
            PublicDefinitions.Add("WITH_GRDK");

            string gdkRuntimePath = Path.Combine(Unreal.EngineDirectory.ToString(), "Platforms", "GDK", "Source/Runtime/GDKRuntime/Public");
            PublicIncludePaths.Add(gdkRuntimePath);
            LogPlayFabCore($"Added GDK runtime include path: {gdkRuntimePath}");
            LogPlayFabCore("Added GDKRuntime module and XCurl dependency");
        }
        else
        {
            LogPlayFabCore("Unreal GDK Flavor not detected");
        }

        // Use the shared utility helper method
        LogPlayFabCore("Attempting to get GDK path using fallback method");
        string gdkPath = null;
        try
        {
            gdkPath = PlayFabGDKUtilities.GetGDKPathWithFallback("PlayFabCore");
            LogPlayFabCore($"Successfully obtained GDK path: {gdkPath}");
        }
        catch (Exception ex)
        {
            LogPlayFabCore($"Failed to get GDK path: {ex.Message}");
            throw;
        }

        if (gdkPath != null)
        {
            // PF_GDK_AVAILABLE indicates if GDK is installed, regardless if Unreal GDK flavor exists or not.
            PublicDefinitions.Add("PF_GDK_AVAILABLE");
            LogPlayFabCore("Added definition: PF_GDK_AVAILABLE");
            
            string LibPath = Path.Combine(gdkPath, @"windows\lib\x64");
            string IncludePath = Path.Combine(gdkPath, @"windows\include");
            
            LogPlayFabCore($"GDK Library path: {LibPath}");
            LogPlayFabCore($"GDK Include path: {IncludePath}");
            
            if (Directory.Exists(IncludePath))
            {
                PublicIncludePaths.Add(IncludePath);
                LogPlayFabCore($"Added GDK include path: {IncludePath}");
            }
            else
            {
                LogPlayFabCore($"WARNING: GDK include path does not exist: {IncludePath}");
            }

            // Import libs
            string libFile = Path.Combine(LibPath, "PlayFabCore.lib");
            if (File.Exists(libFile))
            {
                PublicAdditionalLibraries.Add(libFile);
                LogPlayFabCore($"Added GDK library: {libFile}");
            }
            else
            {
                LogPlayFabCore($"WARNING: GDK library file does not exist: {libFile}");
            }
        }
        else
        {
            LogPlayFabCore("WARNING: GDK path is null - GDK features will not be available");
        }
        
        LogPlayFabCore("Windows platform configuration completed");
    }

    private void ConfigureForGDKPlatform(string platform)
    {
        LogPlayFabCore("Configuring PlayFabCore for GDK Platform");

		PublicIncludePathModuleNames.Add("GDKRuntime");
		PublicDefinitions.Add("WITH_GRDK");
        
        // Try using real GDK first, fall back to environment variables
        string gdkPath = null;
        LogPlayFabCore("Attempting to get GDK path using reflection method");
        
        try
        {
            if (GDKExports.IsGDKAvailable)
            {
                LogPlayFabCore("GDK is available via reflection");
                gdkPath = GDKExports.GetCurrentGSDKDir();
                LogPlayFabCore($"GDK path from reflection: {gdkPath}");
            }
            else
            {
                LogPlayFabCore("GDK not available via reflection, trying fallback method");
                throw new InvalidOperationException("GDK not available via reflection, trying fallback method");
            }
        }
        catch (Exception ex)
        {
            LogPlayFabCore($"Reflection method failed: {ex.Message}");
            try
            {
                // Fallback to environment variable detection
                LogPlayFabCore("Attempting fallback GDK detection using environment variables");
                gdkPath = GDKFallback.GetGDKPath();
                LogPlayFabCore($"GDK path from fallback: {gdkPath}");
            }
            catch (Exception fallbackEx)
            {
                LogPlayFabCore($"Fallback detection failed: {fallbackEx.Message}");
                throw new InvalidOperationException($"PlayFabCore: Neither GDK nor fallback detection available: {fallbackEx.Message}");
            }
        }

        if (string.IsNullOrEmpty(gdkPath))
        {
            LogPlayFabCore("ERROR: GDK path is invalid");
            throw new InvalidOperationException("GDK path is invalid. Please ensure GDK is correctly installed.");
        }

        LogPlayFabCore($"Using GDK path: {gdkPath}");
        
        string IncludePath = Path.Combine(gdkPath, platform, @"include");
        LogPlayFabCore($"GDK include path: {IncludePath}");
        
        if (Directory.Exists(IncludePath))
        {
            PublicIncludePaths.Add(IncludePath);
            LogPlayFabCore($"Added GDK include path: {IncludePath}");
        }
        else
        {
            LogPlayFabCore($"WARNING: GDK include path does not exist: {IncludePath}");
        }

        PublicDefinitions.Add("PF_UE_GDK_SUPPORT");
        PublicDefinitions.Add("PF_GDK_AVAILABLE");
        LogPlayFabCore("Added definitions: PF_UE_GDK_SUPPORT, PF_GDK_AVAILABLE");
        
        LogPlayFabCore("GDK platform configuration completed");
    }

    private void ConfigureForSwitchPlatform(string platformFolder = "Switch")
    {
        NuGetPackageLoader.NuGetPackageInformation NugetPackageInfo = new NuGetPackageLoader.NuGetPackageInformation();
        NuGetPackageLoader NuGetLoader = new NuGetPackageLoader();
        string PlatformsPath = Path.Combine(ModuleDirectory, "../../", "Platforms", platformFolder);
        NuGetLoader.ParsingNuGetPackage(ref PlatformsPath, ref NugetPackageInfo);

        PublicSystemIncludePaths.Add(Path.Combine(PlatformsPath, NugetPackageInfo.UnifiedSDKPackagePath, "build", "native", "include"));

        // Switch2: re-include PlatformSpecific/Switch so its *.Switch.cpp files compile (UBT excludes folders named after other platforms).
        if (Target.Platform.ToString() == "Switch2")
        {
            ConditionalAddModuleDirectory(EpicGames.Core.DirectoryReference.Combine(
                new EpicGames.Core.DirectoryReference(ModuleDirectory), "PlatformSpecific", "Switch"));
        }
    }

    private void ConfigureForPlayStation4Platform()
    {
        NuGetPackageLoader.NuGetPackageInformation NugetPackageInfo = new NuGetPackageLoader.NuGetPackageInformation();
		NuGetPackageLoader NuGetLoader = new NuGetPackageLoader();
        string PluginPath = Path.Combine(ModuleDirectory, "../../");
        string PlatformsPath = Path.Combine(PluginPath, "Platforms", "PS4");
        NuGetLoader.ParsingNuGetPackage(ref PlatformsPath, ref NugetPackageInfo);
    }

    private void ConfigureForPlayStation5Platform()
    {
        NuGetPackageLoader.NuGetPackageInformation NugetPackageInfo = new NuGetPackageLoader.NuGetPackageInformation();
		NuGetPackageLoader NuGetLoader = new NuGetPackageLoader();
        string PluginPath = Path.Combine(ModuleDirectory, "../../");
        string PlatformsPath = Path.Combine(PluginPath, "Platforms", "PS5");
        NuGetLoader.ParsingNuGetPackage(ref PlatformsPath, ref NugetPackageInfo);
    }
}
