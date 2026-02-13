using System.IO;
using UnrealBuildTool;
using System;
using System.Reflection;
using UnrealBuildBase;
using System.Linq;

public class PlayFabUnreal : ModuleRules
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

            LogPlayFabUnreal($"Unified SDK={PackageInfo.UnifiedSDKPackagePath}");
        }
    }

    private static void LogPlayFabUnreal(string message)
    {
        Console.WriteLine($"[PlayFabUnreal] {message}");
    }

    public PlayFabUnreal(ReadOnlyTargetRules Target) : base(Target)
    {
        LogPlayFabUnreal($"Loading module for target: {Target.Name}, Platform: {Target.Platform}, Configuration: {Target.Configuration}");
        LogPlayFabUnreal($"Module directory: {ModuleDirectory}");
        
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateIncludePaths.AddRange(
            new string[] {
                Path.Combine(ModuleDirectory, "Private"),
            }
        );

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore",
                "Projects",
                "LibHttpClient",
                "PlayFabShared",
                "PlayFabCore",
                "PlayFabServices",
                "PlayFabGameSave"
            }
        );
        
        LogPlayFabUnreal($"Added dependencies: {string.Join(", ", PublicDependencyModuleNames)}");

        // Common public include paths
        PublicIncludePaths.AddRange(
            new string[] {
                Path.Combine(ModuleDirectory, "Public"),

                // PlayFabShared Headers
                Path.Combine(ModuleDirectory, "../PlayFabShared/Private/Include"),

                // PlayFabCore Headers
                Path.Combine(ModuleDirectory, "../PlayFabCore/Public"),
                Path.Combine(ModuleDirectory, "../PlayFabCore/Public/Generated"),
                Path.Combine(ModuleDirectory, "../PlayFabCore/Private/Include"),
                Path.Combine(ModuleDirectory, "../PlayFabCore/Private/Include/Generated"),
                Path.Combine(ModuleDirectory, "../PlayFabCore/PlatformSpecific"),

                // PlayFabServices Headers
                Path.Combine(ModuleDirectory, "../PlayFabServices/Public"),
                Path.Combine(ModuleDirectory, "../PlayFabServices/Public/Generated"),
                Path.Combine(ModuleDirectory, "../PlayFabServices/Private/Include"),
                Path.Combine(ModuleDirectory, "../PlayFabServices/Private/Include/Generated"),

                // PlayFabGameSave Headers
                Path.Combine(ModuleDirectory, "../PlayFabGameSave/Public")
            }
        );

        ConfigureForPlatform(Target);
    }

    private void ConfigureForPlatform(ReadOnlyTargetRules Target)
    {
        LogPlayFabUnreal($"Configuring for platform: {Target.Platform}");
        
        // GDK Platform
        if (Target.Platform.ToString() == "WinGDK" || Target.Platform.ToString() == "XSX" || Target.Platform.ToString() == "XB1")
        {
            LogPlayFabUnreal("Using GDK platform configuration");
            ConfigureForGDKPlatform(Target.Platform.ToString() == "WinGDK" ? "windows" : "xbox");
            return;
        }

		// Switch Platform
		if (Target.Platform.ToString() == "Switch")
        {
            LogPlayFabUnreal("Using Switch platform configuration");
            ConfigureForSwitchPlatform();
            return;
        }

        // Windows Platform
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            LogPlayFabUnreal("Using Windows platform configuration");
            ConfigureForWindowsPlatform();
            return;
        }

        // PS4 Platform
        if (Target.Platform.ToString() == "PS4")
        {
            LogPlayFabUnreal("Using PlayStation 4 platform configuration");
            ConfigureForPlayStation4Platform();
            return;
        }

        // PS5 Platform
        if (Target.Platform.ToString() == "PS5")
        {
            LogPlayFabUnreal("Using PlayStation 5 platform configuration");
            ConfigureForPlayStation5Platform();
            return;
        }

        throw new PlatformNotSupportedException(Target.Platform.ToString() + " is not supported.");
    }

    private void ConfigureForWindowsPlatform()
    {
        // Use the shared utility helper methods
        string gdkPath = PlayFabGDKUtilities.GetGDKPathWithFallback("PlayFabUnreal");
        int gdkVersion = PlayFabGDKUtilities.GetGDKVersionWithFallback("PlayFabUnreal");

        // Verify the version meets requirements
        if (gdkVersion < 251000)
        {
            throw new BuildException("GDK version {0} is too old. Version 251000 or higher is required.", gdkVersion);
        }

        string BinPath = Path.Combine(gdkPath, @"windows\bin\x64");
        string LibPath = Path.Combine(gdkPath, @"windows\lib\x64");
        string IncludePath = Path.Combine(gdkPath, @"windows\include");

		MethodInfo IsGDKEditionValidFunction = System.Type.GetType("GRDK, UE5Rules", false)?.GetMethod("IsGDKEditionValid", BindingFlags.Public | BindingFlags.Static);
		bool bHasValidGDK = (IsGDKEditionValidFunction != null) && (bool)IsGDKEditionValidFunction.Invoke(null, null);

		if (bHasValidGDK)
        {
            // Loading XCurl from legacy folder structure (GRDK)
            PublicDependencyModuleNames.Add("GDKRuntime");
            PublicDependencyModuleNames.Add("XCurl");
            PublicIncludePaths.Add(Path.Combine(Unreal.EngineDirectory.ToString(), "Platforms", "GDK", "Source/Runtime/GDKRuntime/Public"));
        }
        else
        {
            // Loading XCurl from new folder structure (windows)
            RuntimeDependencies.Add("$(BinaryOutputDir)/XCurl.dll", Path.Combine(BinPath, "XCurl.dll"), StagedFileType.SystemNonUFS);
            RuntimeDependencies.Add("$(BinaryOutputDir)/XCurl.pdb", Path.Combine(BinPath, "XCurl.pdb"), StagedFileType.DebugNonUFS);
            PublicAdditionalLibraries.Add(Path.Combine(LibPath, "XCurl.lib"));
        }

        // Includes
        PublicIncludePaths.Add(IncludePath);

        // Binaries
        RuntimeDependencies.Add("$(BinaryOutputDir)/libHttpClient.dll", Path.Combine(BinPath, "libHttpClient.dll"), StagedFileType.SystemNonUFS);
        RuntimeDependencies.Add("$(BinaryOutputDir)/libHttpClient.pdb", Path.Combine(BinPath, "libHttpClient.pdb"), StagedFileType.DebugNonUFS);
        RuntimeDependencies.Add("$(BinaryOutputDir)/PlayFabCore.dll", Path.Combine(BinPath, "PlayFabCore.dll"), StagedFileType.SystemNonUFS);
        RuntimeDependencies.Add("$(BinaryOutputDir)/PlayFabCore.pdb", Path.Combine(BinPath, "PlayFabCore.pdb"), StagedFileType.DebugNonUFS);
        RuntimeDependencies.Add("$(BinaryOutputDir)/PlayFabServices.dll", Path.Combine(BinPath, "PlayFabServices.dll"), StagedFileType.SystemNonUFS);
        RuntimeDependencies.Add("$(BinaryOutputDir)/PlayFabServices.pdb", Path.Combine(BinPath, "PlayFabServices.pdb"), StagedFileType.DebugNonUFS);
        RuntimeDependencies.Add("$(BinaryOutputDir)/PlayFabGameSave.dll", Path.Combine(BinPath, "PlayFabGameSave.dll"), StagedFileType.SystemNonUFS);
        RuntimeDependencies.Add("$(BinaryOutputDir)/PlayFabGameSave.pdb", Path.Combine(BinPath, "PlayFabGameSave.pdb"), StagedFileType.DebugNonUFS);
        RuntimeDependencies.Add("$(BinaryOutputDir)/xgameruntime.dll", Path.Combine(BinPath, "xgameruntime.dll"), StagedFileType.SystemNonUFS);
        RuntimeDependencies.Add("$(BinaryOutputDir)/xgameruntime.pdb", Path.Combine(BinPath, "xgameruntime.pdb"), StagedFileType.DebugNonUFS);

        // Import libs
        PublicAdditionalLibraries.Add(Path.Combine(LibPath, "libHttpClient.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(LibPath, "xgameruntime.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(LibPath, "PlayFabCore.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(LibPath, "PlayFabServices.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(LibPath, "PlayFabGameSave.lib"));

        // Copy MicrosoftGame.config for Win64 builds
        string ProjectRoot = Path.GetFullPath(Path.Combine(ModuleDirectory, "../../../.."));
        string MicrosoftGameConfigPath = Path.Combine(ProjectRoot, "MicrosoftGame.config");

        if (File.Exists(MicrosoftGameConfigPath))
        {
            RuntimeDependencies.Add("$(BinaryOutputDir)/MicrosoftGame.config", MicrosoftGameConfigPath, StagedFileType.SystemNonUFS);
        }
    }

    private void ConfigureForGDKPlatform(string platform)
    {
        int GDKVersionNumber = PlayFabGDKUtilities.GetGDKVersionWithFallback("PlayFabUnreal");

        if (GDKVersionNumber < 251000)
        {
            throw new BuildException("GDK version {0} is too old. Version 251000 or higher is required.", GDKVersionNumber);
        }
        else
        {
            string GDKLatest = PlayFabGDKUtilities.GetGDKPathWithFallback("PlayFabUnreal");

            if (string.IsNullOrEmpty(GDKLatest))
            {
                throw new InvalidOperationException("GDKLatest path is invalid. Please ensure GDK is correctly installed.");
            }

			string BinPath = Path.Combine(GDKLatest, platform, @"bin\x64");
            string LibPath = Path.Combine(GDKLatest, platform, @"lib\x64");
            string IncludePath = Path.Combine(GDKLatest, platform, @"include");

            // Includes
            PublicIncludePaths.Add(IncludePath);

            // Binaries
            RuntimeDependencies.Add("$(BinaryOutputDir)/libHttpClient.dll", Path.Combine(BinPath, "libHttpClient.dll"), StagedFileType.SystemNonUFS);
            RuntimeDependencies.Add("$(BinaryOutputDir)/libHttpClient.pdb", Path.Combine(BinPath, "libHttpClient.pdb"), StagedFileType.DebugNonUFS);
            RuntimeDependencies.Add("$(BinaryOutputDir)/PlayFabCore.dll", Path.Combine(BinPath, "PlayFabCore.dll"), StagedFileType.SystemNonUFS);
            RuntimeDependencies.Add("$(BinaryOutputDir)/PlayFabCore.pdb", Path.Combine(BinPath, "PlayFabCore.pdb"), StagedFileType.DebugNonUFS);
            RuntimeDependencies.Add("$(BinaryOutputDir)/PlayFabServices.dll", Path.Combine(BinPath, "PlayFabServices.dll"), StagedFileType.SystemNonUFS);
            RuntimeDependencies.Add("$(BinaryOutputDir)/PlayFabServices.pdb", Path.Combine(BinPath, "PlayFabServices.pdb"), StagedFileType.DebugNonUFS);
            RuntimeDependencies.Add("$(BinaryOutputDir)/PlayFabGameSave.dll", Path.Combine(BinPath, "PlayFabGameSave.dll"), StagedFileType.SystemNonUFS);
            RuntimeDependencies.Add("$(BinaryOutputDir)/PlayFabGameSave.pdb", Path.Combine(BinPath, "PlayFabGameSave.pdb"), StagedFileType.DebugNonUFS);

            // Import libs
            PublicAdditionalLibraries.Add(Path.Combine(LibPath, "libHttpClient.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(LibPath, "xgameruntime.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(LibPath, "PlayFabCore.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(LibPath, "PlayFabServices.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(LibPath, "PlayFabGameSave.lib"));
        }
    }

    private void ConfigureForSwitchPlatform()
    {
        string PluginPath = Path.Combine(ModuleDirectory, "../../");
        string PlatformsPath = Path.Combine(PluginPath, "Platforms", "Switch");
        string LibPath = Path.Combine(PlatformsPath, "lib");
        string IncludePath = Path.Combine(PlatformsPath, "include");

        PublicIncludePaths.Add(IncludePath);

        PublicAdditionalLibraries.Add(Path.Combine(LibPath, "libHttpClient.a"));
        PublicAdditionalLibraries.Add(Path.Combine(LibPath, "libPlayFabCore.a"));
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