//--------------------------------------------------------------------------------------
// Advanced Technology Group (ATG)
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

using UnrealBuildTool;
using System;
using System.IO;
using System.Reflection;
using System.Linq;
using System.Diagnostics;
using System.Threading;

public class OnlineSubsystemPlayFab : ModuleRules
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

	private static bool VerboseVOIPLoggingEnabled = false;
	private static bool VerbosePacketLevelLoggingEnabled = false;

	private static void LogOnlineSubsystemPlayFab(string format, params object[] args)
	{
		Console.WriteLine($"[OSS PlayFab] {format}", args);
	}

	public OnlineSubsystemPlayFab(ReadOnlyTargetRules Target) : base(Target)
	{
		// We don't want to try and load when doing project gen
		if (Target.bGenerateProjectFiles)
		{
			PrecompileForTargets = PrecompileTargetsType.None;
			return;
		}

		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		// Common Public Module Dependencies
		PublicDependencyModuleNames.AddRange(
		new string[] {
				"OnlineSubsystemUtils",
		});

		// Common Private Module Dependencies
		PrivateDependencyModuleNames.AddRange(
			new string[] {
				"Core",
				"CoreUObject",
				"NetCore",
				"Engine",
				"Sockets",
				"Voice",
				"AudioMixer",
				"OnlineSubsystem",
				"Json",
				"PacketHandler",
				"Projects",
				"HTTP"
			}
		);

		// PlayFab Unreal Plugin modules
		PrivateDependencyModuleNames.AddRange(new string[] { "PlayFabShared", "PlayFabCore", "PlayFabUnreal" });

		// Common Definitions
		PublicDefinitions.Add(String.Format("OSS_PLAYFAB_{0}=1", Target.Platform.ToString().ToUpper()));
		PublicDefinitions.Add("PLAYFAB_SUBSYSTEM=FName(TEXT(\"PLAYFAB\"))");
		PrivateDefinitions.Add("ONLINESUBSYSTEMPLAYFAB_PACKAGE=1");

		// For debugging purposes
		PublicDefinitions.Add("OSS_PLAYFAB_VERBOSE_VOIP_LOGGING=" + (VerboseVOIPLoggingEnabled ? "1" : "0"));
		PublicDefinitions.Add("OSS_PLAYFAB_VERBOSE_PACKET_LEVEL_LOGGING=" + (VerbosePacketLevelLoggingEnabled ? "1" : "0"));

		ConfigureForPlatform();
	}

	private void ConfigureForPlatform()
	{
		// Because platform determination relies on types that only exist in builds that have the platform enabled, we use reflection to dynamically 
		// look for the existence of the platform's field on the UnrealPlatformGroup type.

		LogOnlineSubsystemPlayFab("Configuring for Target Platform: " + Target.Platform.ToString());

		// GDK
		bool bFound = UnrealPlatformGroup.TryParse("GDK", out UnrealPlatformGroup Group);
		if (bFound)
		{
			LogOnlineSubsystemPlayFab("Found UnrealPlatformGroup: " + Group.ToString());
			if (Target.Platform.IsInGroup(Group))
			{
				LogOnlineSubsystemPlayFab("Target Platform: " + Target.Platform.ToString() + " is in UnrealPlatformGroup " + Group.ToString());
				ConfigureForGDKPlatform();
				return;
			}
		}

		//Switch
		if (Target.Platform.ToString() == "Switch")
		{
			ConfigureForSwitchPlatform();
			return;

		}

		//Win64
		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			ConfigureForWindowsPlatform();
			return;
		}

		//PS4
		if (Target.Platform.ToString() == "PS4")
		{
			ConfigureForPlayStation4Platform();
			return;
		}

		//PS5
		if (Target.Platform.ToString() == "PS5")
		{
			ConfigureForPlayStation5Platform();
			return;
		}

		throw new PlatformNotSupportedException(Target.Platform.ToString() + " is not supported.");
	}

	private class NuGetPackageLoader
	{
		public class NuGetPackageInformation
		{
			public string PartyPackagePath = string.Empty;
			public string MultiplayerPackagePath = string.Empty;
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

						if (Id.IndexOf("Party", 0) > -1)
						{
							PackageInfo.PartyPackagePath = Id + "." + Version;
						}
						else if (Id.IndexOf("Multiplayer", 0) > -1)
						{
							PackageInfo.MultiplayerPackagePath = Id + "." + Version;
						}
						else
						{
							throw new BuildException("Unknown package id in package.config file.");
						}
					}
				}
			}
			if (PackageInfo.PartyPackagePath.Length == 0 && PackageInfo.MultiplayerPackagePath.Length == 0)
			{
				throw new BuildException("Can't find Party and Multiplayer package infomation in package.config file.");
			}
			LogOnlineSubsystemPlayFab("OnlineSubsystemPlayFab: Party={0}", PackageInfo.PartyPackagePath);
			LogOnlineSubsystemPlayFab("OnlineSubsystemPlayFab: Multiplayer={0}", PackageInfo.MultiplayerPackagePath);
		}
	}

	//GDK
	private void ConfigureForGDKPlatform()
	{
		PublicDependencyModuleNames.Add("Core");
		PublicDependencyModuleNames.Add("OnlineSubsystemGDK");
		PublicDefinitions.Add("USE_PFCORE_SDK=1");

		PublicDefinitions.Add("OSS_PLAYFAB_GDK=1");
		PublicDefinitions.Add("OSS_PLAYFAB_GDK_SUPPORT=1");

		if (Target.Platform == UnrealTargetPlatform.Parse("WinGDK"))
		{
			PublicDefinitions.Add("OSS_PLAYFAB_IS_PC=1");
		}

		PrivateDefinitions.Add("ONLINESUBSYSTEMGDK_PACKAGE=1");

		string GDKLatest = GDKExports.GetCurrentGSDKDir();
		string BinPath = Path.Combine(GDKLatest, @"windows\bin\x64");
		string LibPath = Path.Combine(GDKLatest, @"windows\lib\x64");
		string IncludePath = Path.Combine(GDKLatest, @"windows\include");
		string PFCoreIncludePath = Path.Combine(IncludePath, "playfab", "core");
		string PFPartyIncludePath = Path.Combine(IncludePath, "playfab", "party");
		string PFMLPIncludePath = Path.Combine(IncludePath, "playfab", "multiplayer");

		PublicSystemIncludePaths.AddRange(
			new string[] {
				PFCoreIncludePath,
				PFPartyIncludePath,
				PFMLPIncludePath,
			}
		);

		PublicSystemLibraries.Add(Path.Combine(LibPath, "Party.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(LibPath, "PlayFabMultiplayer.lib"));

		RuntimeDependencies.Add("$(TargetOutputDir)/Party.dll", Path.Combine(BinPath, "Party.dll"), StagedFileType.SystemNonUFS);
		RuntimeDependencies.Add("$(TargetOutputDir)/Party.pdb", Path.Combine(BinPath, "Party.pdb"), StagedFileType.DebugNonUFS);
		RuntimeDependencies.Add("$(TargetOutputDir)/PlayFabMultiplayer.dll", Path.Combine(BinPath, "PlayFabMultiplayer.dll"), StagedFileType.SystemNonUFS);
		RuntimeDependencies.Add("$(TargetOutputDir)/PlayFabMultiplayer.pdb", Path.Combine(BinPath, "PlayFabMultiplayer.pdb"), StagedFileType.DebugNonUFS);

		LogOnlineSubsystemPlayFab("Copy Party.dll from {0}: TargetOutputDir", BinPath);

		PublicSystemLibraries.Add(Path.Combine(LibPath, "PartyXboxLive.lib"));
		RuntimeDependencies.Add("$(TargetOutputDir)/PartyXboxLive.dll", Path.Combine(BinPath, "PartyXboxLive.dll"), StagedFileType.SystemNonUFS);
		RuntimeDependencies.Add("$(TargetOutputDir)/PartyXboxLive.pdb", Path.Combine(BinPath, "PartyXboxLive.pdb"), StagedFileType.DebugNonUFS);
	}

	//Switch
	private void ConfigureForSwitchPlatform()
	{
		PublicDependencyModuleNames.Add("OnlineSubsystemSwitch");

		string PlatformDir = Path.Combine(PluginDirectory, "Platforms", "Switch");

		if (!Directory.Exists(PlatformDir))
		{
			throw new BuildException("PlayFab precompiled dependencies were not found.");
		}

		// Find the MLP and Party library names under the PlatformDir.
		NuGetPackageLoader NuGetLoader = new NuGetPackageLoader();
		NuGetPackageLoader.NuGetPackageInformation NugetPackageInfo = new NuGetPackageLoader.NuGetPackageInformation();
		NuGetLoader.ParsingNuGetPackage(ref PlatformDir, ref NugetPackageInfo);

		// Load Party binaries.
		string PartyIncludePath = Path.Combine(PlatformDir, NugetPackageInfo.PartyPackagePath, "build", "native", "include");
		string PartyLibraryPath = Path.Combine(PlatformDir, NugetPackageInfo.PartyPackagePath, "build", "native", "lib", "NX64", "release");

		if (!Directory.Exists(PartyIncludePath) ||
			!Directory.Exists(PartyLibraryPath))
		{
			throw new BuildException("PlayFab Party precompiled dependencies were not found.");
		}

		string PartyNroPath = Path.Combine(PartyLibraryPath, "Party.nro");
		string PartyNrrPath = Path.Combine(PartyLibraryPath, "Party.nrr");
		string PartyNrsPath = Path.Combine(PartyLibraryPath, "Party.nrs");

		if (!File.Exists(PartyNroPath) || !File.Exists(PartyNrrPath) || !File.Exists(PartyNrsPath))
		{
			throw new BuildException("Party.nro/.nrr/.nrs not found in: " + PartyLibraryPath);
		}

		PublicSystemIncludePaths.Add(PartyIncludePath);
		PublicAdditionalLibraries.Add(PartyNrsPath);
		RuntimeDependencies.Add("Binaries/Switch/Party.nro", PartyNroPath, StagedFileType.SystemNonUFS);

		// Load Multiplayer binaries
		string MultiplayerIncludePath = Path.Combine(PlatformDir, NugetPackageInfo.MultiplayerPackagePath, "build", "native", "include");
		string MultiplayerLibraryPath = Path.Combine(PlatformDir, NugetPackageInfo.MultiplayerPackagePath, "build", "native", "lib", "NX64", "release");

		if (!Directory.Exists(MultiplayerIncludePath) ||
			!Directory.Exists(MultiplayerLibraryPath))
		{
			throw new BuildException("PlayFab Multiplayer precompiled dependencies were not found.");
		}

		string MpNroPath = Path.Combine(MultiplayerLibraryPath, "libPlayFabMultiplayer.nro");
		string MpNrrPath = Path.Combine(MultiplayerLibraryPath, "libPlayFabMultiplayer.nrr");
		string MpNrsPath = Path.Combine(MultiplayerLibraryPath, "libPlayFabMultiplayer.nrs");

		if (!File.Exists(MpNroPath) || !File.Exists(MpNrrPath) || !File.Exists(MpNrsPath))
		{
			throw new BuildException("libPlayFabMultiplayer.nro/.nrr/.nrs not found in: " + MultiplayerLibraryPath);
		}

		PublicSystemIncludePaths.Add(MultiplayerIncludePath);
		PublicAdditionalLibraries.Add(MpNrsPath);
		RuntimeDependencies.Add("Binaries/Switch/libPlayFabMultiplayer.nro", MpNroPath, StagedFileType.SystemNonUFS);

		// Load Nintendo SDK dependencies.
		string NintendoSdkRoot = Environment.GetEnvironmentVariable("NINTENDO_SDK_ROOT");
		if (string.IsNullOrWhiteSpace(NintendoSdkRoot))
		{
			throw new BuildException("NINTENDO_SDK_ROOT environment variable is not set.");
		}

		string configuration = (Target.Configuration == UnrealTargetConfiguration.Shipping || Target.Configuration == UnrealTargetConfiguration.Test)
			? "Release"
			: "Develop";

		string WebSocketLibPath = Path.Combine(NintendoSdkRoot, "Libraries/NX-NXFP2-a64", configuration, "libnn_websocket.a");

		if (!File.Exists(WebSocketLibPath))
		{
			throw new BuildException($"libnn_websocket.a not found at: {WebSocketLibPath}");
		}

		PublicAdditionalLibraries.Add(WebSocketLibPath);
	}

	//Windows
	private void ConfigureForWindowsPlatform()
	{
		PublicDefinitions.Add("OSS_PLAYFAB_IS_PC=1");
		PublicDefinitions.Add("USE_PFCORE_SDK=1");

		// If Unreal GDK Flavor is installed
		MethodInfo IsGDKEditionValidFunction = System.Type.GetType("GRDK, UE5Rules", false)?.GetMethod("IsGDKEditionValid", BindingFlags.Public | BindingFlags.Static);
		bool bHasValidGDK = (IsGDKEditionValidFunction != null) && (bool)IsGDKEditionValidFunction.Invoke(null, null);

		if (bHasValidGDK)
		{
			LogOnlineSubsystemPlayFab("Unreal GDK Flavor detected - adding GDK support");
			PublicDependencyModuleNames.Add("OnlineSubsystemGDK");
			PrivateDependencyModuleNames.Add("GDKRuntime");
            PrivateDependencyModuleNames.Add("XSAPI");
			PublicDefinitions.Add("OSS_PLAYFAB_GDK_SUPPORT=1");
			PrivateDefinitions.Add("ONLINESUBSYSTEMGDK_PACKAGE=1");
		}
		else
		{
			LogOnlineSubsystemPlayFab("Unreal GDK Flavor not detected");
		}

		// Use the shared utility helper method
		LogOnlineSubsystemPlayFab("Attempting to get GDK path using fallback method");
		string gdkPath = null;
		try
		{
			gdkPath = PlayFabGDKUtilities.GetGDKPathWithFallback("OnlineSubsystemPlayFab");
			LogOnlineSubsystemPlayFab($"Successfully obtained GDK path: {gdkPath}");
		}
		catch (Exception ex)
		{
			LogOnlineSubsystemPlayFab($"Failed to get GDK path: {ex.Message}");
			throw;
		}

		string BinPath = Path.Combine(gdkPath, @"windows\bin\x64");
		string LibPath = Path.Combine(gdkPath, @"windows\lib\x64");
		string IncludePath = Path.Combine(gdkPath, @"windows\include");
		string PFCoreIncludePath = Path.Combine(IncludePath, "playfab", "core");
		string PFPartyIncludePath = Path.Combine(IncludePath, "playfab", "party");
		string PFMLPIncludePath = Path.Combine(IncludePath, "playfab", "multiplayer");

		PublicSystemIncludePaths.AddRange(
			new string[] {
				IncludePath,
				PFCoreIncludePath,
				PFPartyIncludePath,
				PFMLPIncludePath
			}
		);

		PublicSystemLibraries.Add(Path.Combine(LibPath, "Party.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(LibPath, "PlayFabMultiplayer.lib"));

		RuntimeDependencies.Add("$(TargetOutputDir)/Party.dll", Path.Combine(BinPath, "Party.dll"), StagedFileType.SystemNonUFS);
		RuntimeDependencies.Add("$(TargetOutputDir)/Party.pdb", Path.Combine(BinPath, "Party.pdb"), StagedFileType.DebugNonUFS);
		RuntimeDependencies.Add("$(TargetOutputDir)/PlayFabMultiplayer.dll", Path.Combine(BinPath, "PlayFabMultiplayer.dll"), StagedFileType.SystemNonUFS);
		RuntimeDependencies.Add("$(TargetOutputDir)/PlayFabMultiplayer.pdb", Path.Combine(BinPath, "PlayFabMultiplayer.pdb"), StagedFileType.DebugNonUFS);

		LogOnlineSubsystemPlayFab("Copy Party.dll from {0}: TargetOutputDir", BinPath);

		PublicSystemLibraries.Add(Path.Combine(LibPath, "PartyXboxLive.lib"));
		RuntimeDependencies.Add("$(TargetOutputDir)/PartyXboxLive.dll", Path.Combine(BinPath, "PartyXboxLive.dll"), StagedFileType.SystemNonUFS);
		RuntimeDependencies.Add("$(TargetOutputDir)/PartyXboxLive.pdb", Path.Combine(BinPath, "PartyXboxLive.pdb"), StagedFileType.DebugNonUFS);
	}

	//PS4
	private void ConfigureForPlayStation4Platform()
	{
		NuGetPackageLoader.NuGetPackageInformation NugetPackageInfo = new NuGetPackageLoader.NuGetPackageInformation();
		NuGetPackageLoader NuGetLoader = new NuGetPackageLoader();
		string PlatformDir = Path.Combine(PluginDirectory, "Platforms", "PS4");
		NuGetLoader.ParsingNuGetPackage(ref PlatformDir, ref NugetPackageInfo);

		PublicDependencyModuleNames.Add("OnlineSubsystemPS4");

		bAllowConfidentialPlatformDefines = true;
		PublicDefinitions.Add("OSS_PLAYFAB_PLAYSTATION=1");
	}

	//PS5
	private void ConfigureForPlayStation5Platform()
	{
		NuGetPackageLoader.NuGetPackageInformation NugetPackageInfo = new NuGetPackageLoader.NuGetPackageInformation();
		NuGetPackageLoader NuGetLoader = new NuGetPackageLoader();
		string PlatformDir = Path.Combine(PluginDirectory, "Platforms", "PS5");
		NuGetLoader.ParsingNuGetPackage(ref PlatformDir, ref NugetPackageInfo);

		PublicDependencyModuleNames.Add("OnlineSubsystemPS5");

		bAllowConfidentialPlatformDefines = true;
		PublicDefinitions.Add("OSS_PLAYFAB_PLAYSTATION=1");
	}
}
