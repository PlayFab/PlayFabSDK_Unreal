using System;
using System.IO;
using System.Linq;
using System.Reflection;
using UnrealBuildTool;

public class PlayFabGameSave : ModuleRules
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

    private static void LogPlayFabGameSave(string message)
    {
        Console.WriteLine($"[PlayFabGameSave] {message}");
    }

    public PlayFabGameSave(ReadOnlyTargetRules Target) : base(Target)
    {
        LogPlayFabGameSave($"Loading module for target: {Target.Name}, Platform: {Target.Platform}, Configuration: {Target.Configuration}");
        LogPlayFabGameSave($"Module directory: {ModuleDirectory}");
        
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateIncludePaths.AddRange(
            new string[] {
                Path.Combine(ModuleDirectory, "Private"),
            }
        );

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core", // Ensure the Core module is included
				"CoreUObject",
                "Engine",
                "InputCore",
                "Projects",
                "PlayFabShared",
                "PlayFabCore"
				// ... add other public dependencies that you statically link with here ...
			}
        );
        
        LogPlayFabGameSave($"Added dependencies: {string.Join(", ", PublicDependencyModuleNames)}");

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
        );

        ConfigureForPlatform(Target);
    }
    private void ConfigureForPlatform(ReadOnlyTargetRules Target)
    {
        LogPlayFabGameSave($"Configuring for platform: {Target.Platform}");
        
        // GDK Platform
        if (Target.Platform.ToString() == "WinGDK" || Target.Platform.ToString() == "XSX")
        {
            LogPlayFabGameSave("Using GDK platform configuration");
            ConfigureForGDKPlatform();
            return;
        }

        // Windows Platform
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            LogPlayFabGameSave("Using Windows platform configuration");
            ConfigureForWindowsPlatform();
            return;
        }

        throw new PlatformNotSupportedException(Target.Platform.ToString() + " is not supported.");
    }

    private void ConfigureForWindowsPlatform()
    {
        // Try using real GDK first, fall back to environment variables
        string gdkPath = PlayFabGDKUtilities.GetGDKPathWithFallback("PlayFabGameSave");

        if (string.IsNullOrEmpty(gdkPath))
        {
            throw new InvalidOperationException("GDK path is invalid. Please ensure GDK is correctly installed.");
        }

        string LibPath = Path.Combine(gdkPath, @"windows\lib\x64");
        string IncludePath = Path.Combine(gdkPath, @"windows\include");

        PublicIncludePaths.Add(IncludePath);

        PublicAdditionalLibraries.Add(Path.Combine(LibPath, "LibHttpClient.GDK.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(LibPath, "PlayFabCore.GDK.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(LibPath, "PlayFabGameSave.GDK.lib"));
    }

    private void ConfigureForGDKPlatform()
    {
        // Try using real GDK first, fall back to environment variables
        string gdkPath = PlayFabGDKUtilities.GetGDKPathWithFallback("PlayFabGameSave");

        if (string.IsNullOrEmpty(gdkPath))
        {
            throw new InvalidOperationException("GDK path is invalid. Please ensure GDK is correctly installed.");
        }

        string IncludePath = Path.Combine(gdkPath, @"windows\include");
        PublicIncludePaths.Add(IncludePath);
    }
}
