using System;
using System.IO;
using System.Linq;
using System.Reflection;
using UnrealBuildTool;

public class PlayFabServices : ModuleRules
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
            string gdkPath = Environment.GetEnvironmentVariable("GameDKLatest");

            if (string.IsNullOrEmpty(gdkPath))
            {
                throw new InvalidOperationException("GameDKLatest environment variable is not set. Please ensure GDK is correctly installed.");
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

            LogPlayFabServices($"Unified SDK={PackageInfo.UnifiedSDKPackagePath}");
        }
    }

    private static void LogPlayFabServices(string message)
    {
        Console.WriteLine($"[PlayFabServices] {message}");
    }

    public PlayFabServices(ReadOnlyTargetRules Target) : base(Target)
    {
        LogPlayFabServices($"Loading module for target: {Target.Name}, Platform: {Target.Platform}, Configuration: {Target.Configuration}");
        LogPlayFabServices($"Module directory: {ModuleDirectory}");
        
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore",
                "Projects",
                "PlayFabShared",
                "PlayFabCore",
            }
        );
        
        LogPlayFabServices($"Added dependencies: {string.Join(", ", PublicDependencyModuleNames)}");

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
            }
        );

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

                // PlayFabServices Headers
                Path.Combine(ModuleDirectory, "../PlayFabServices/Public"),
                Path.Combine(ModuleDirectory, "../PlayFabServices/Public/Generated"),
                Path.Combine(ModuleDirectory, "../PlayFabServices/Private/Include"),
                Path.Combine(ModuleDirectory, "../PlayFabServices/Private/Include/Generated"),
            }
        );

        ConfigureForPlatform(Target);
    }

    private void ConfigureForPlatform(ReadOnlyTargetRules Target)
    {
        LogPlayFabServices($"Configuring for platform: {Target.Platform}");
        
        // GDK Platform
        if (Target.Platform.ToString() == "WinGDK" || Target.Platform.ToString() == "XSX" || Target.Platform.ToString() == "XB1")
        {
            LogPlayFabServices("Using GDK platform configuration");
            ConfigureForGDKPlatform();
            return;
        }

        // Switch Platform
        if (Target.Platform.ToString() == "Switch")
        {
            LogPlayFabServices("Using Switch platform configuration");
            ConfigureForSwitchPlatform();
            return;
        }

        // Windows Platform
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            LogPlayFabServices("Using Windows platform configuration");
            ConfigureForWindowsPlatform();
            return;
        }

        // PS4 Platform
        if (Target.Platform.ToString() == "PS4")
        {
            LogPlayFabServices("Using PlayStation 4 platform configuration");
            ConfigureForPlayStation4Platform();
            return;
        }

        // PS5 Platform
        if (Target.Platform.ToString() == "PS5")
        {
            LogPlayFabServices("Using PlayStation 5 platform configuration");
            ConfigureForPlayStation5Platform();
            return;
        }

        throw new PlatformNotSupportedException(Target.Platform.ToString() + " is not supported.");
    }

    private void ConfigureForWindowsPlatform()
    {
        // Try using real GDK first, fall back to environment variables
        string gdkPath = PlayFabGDKUtilities.GetGDKPathWithFallback("PlayFabServices");

        if (string.IsNullOrEmpty(gdkPath))
        {
            throw new InvalidOperationException("GDK path is invalid. Please ensure GDK is correctly installed.");
        }

        string LibPath = Path.Combine(gdkPath, @"windows\lib\x64");
        string IncludePath = Path.Combine(gdkPath, @"windows\include");

        PublicIncludePaths.Add(IncludePath);

        PublicAdditionalLibraries.Add(Path.Combine(LibPath, "LibHttpClient.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(LibPath, "PlayFabCore.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(LibPath, "PlayFabServices.lib"));
    }

    private void ConfigureForGDKPlatform()
    {
        // Try using real GDK first, fall back to environment variables
        string gdkPath = PlayFabGDKUtilities.GetGDKPathWithFallback("PlayFabServices");

        if (string.IsNullOrEmpty(gdkPath))
        {
            throw new InvalidOperationException("GDK path is invalid. Please ensure GDK is correctly installed.");
        }

        string IncludePath = Path.Combine(gdkPath, @"windows\include");
        PublicIncludePaths.Add(IncludePath);
    }

    private void ConfigureForSwitchPlatform()
    {
        string PluginPath = Path.Combine(ModuleDirectory, "../../");
        string PlatformsPath = Path.Combine(PluginPath, "Platforms", "Switch");
        string LibPath = Path.Combine(PlatformsPath, "lib");
        string IncludePath = Path.Combine(PlatformsPath, "include");

        PublicIncludePaths.Add(IncludePath);
        PublicAdditionalLibraries.Add(Path.Combine(LibPath, "libPlayFabServices.a"));
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
