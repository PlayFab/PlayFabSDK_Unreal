# This script downloads the private platform components of the Unified SDK plugin, for the platforms the user has access to.
# The binaries and header files are pulled from our NuGet feeds at https://dev.azure.com/PlayFabPrivate/. You can
# find the NuGet config files in the Platforms/[APlatform] folder.
# The private source code is pulled from our Git repositories as submodules.

# Prerequesites: download NuGet.exe and add its path to the PATH environment variable. Have git installed.

param (
	[Parameter(Mandatory=$true)]
	[validateset("Switch", "PlayStation")]
	[string]$Platform
)

$unifiedSdkNugetFileName = ""
$unifiedSdkNugetVersion = ""

function Set-NuGetPackageInfo($localPath, $unifiedSdkFileName, $unifiedSdkVersion)
{
    $packagesXml = Get-Content $localPath\packages.config".xml"
    $packagesXml = $packagesXml -replace "##UNIFIEDSDK##", $unifiedSdkFileName
    $packagesXml = $packagesXml -replace "##UNIFIEDSDK_VERSION##", $unifiedSdkVersion
    Set-Content -Path $localPath\packages.config -Value $packagesXml
}

if ($Platform -eq "Switch")
{
    Write-Host "Select Nintendo Switch Unified SDK version..."
    Write-Host "    1: SDK 2.3.1"
    while($True)
    {
        Write-Host -NoNewline "> "
        $inputString = ""
        while ($true)
        {
            $key = $Host.UI.RawUI.ReadKey()
            if ($key.VirtualKeyCode -eq 13) # Enter key
            {
                break
            }
            $inputString += $key.Character
        }
        $Selection = $inputString
        Write-Host ""
        if ($Selection -eq '1')
        {
            $unifiedSdkNugetFileName = "Microsoft.PlayFab.UnifiedSDK.Cpp.Switch-20.5.21"
            $unifiedSdkNugetVersion = "2.3.1"
            break
        }
        Write-Host "Unknown input"
    }
	Write-Host "Downloading Nintendo Switch Unified SDK NuGet packages..."
    Write-Host $unifiedSdkNugetFileName". Unified SDK version="$unifiedSdkNugetVersion
    Write-Host "If you want to use a higher version of the Unified SDK, please check out our private repositories and follow https://learn.microsoft.com/en-us/gaming/playfab/features/multiplayer/networking/party-unreal-engine-oss-obtaining-playfab-party-libraries"
    $localPath = ".\Platforms\Switch"
    Set-NuGetPackageInfo $localPath $unifiedSdkNugetFileName $unifiedSdkNugetVersion
	nuget.exe restore $localPath -ConfigFile $localPath\nuget.config -PackagesDirectory $localPath
	Write-Host "Downloaded Nintendo Switch Unified SDK NuGet packages."

    Write-Host "Select Nintendo Switch 2 Unified SDK version..."
    Write-Host "    1: SDK 2.3.1 (Switch2-20.5.21)"
    while($True)
    {
        Write-Host -NoNewline "> "
        $inputString = ""
        while ($true)
        {
            $key = $Host.UI.RawUI.ReadKey()
            if ($key.VirtualKeyCode -eq 13) # Enter key
            {
                break
            }
            $inputString += $key.Character
        }
        $Selection = $inputString
        Write-Host ""
        if ($Selection -eq '1')
        {
            $unifiedSdkNugetFileName = "Microsoft.PlayFab.UnifiedSDK.Cpp.Switch2-20.5.21"
            $unifiedSdkNugetVersion = "2.3.1"
            break
        }
        Write-Host "Unknown input"
    }
	Write-Host "Downloading Nintendo Switch 2 Unified SDK NuGet packages..."
    Write-Host $unifiedSdkNugetFileName". Unified SDK version="$unifiedSdkNugetVersion
    Write-Host "If you want to use a higher version of the Unified SDK, please checkout to our private repositories and follow https://learn.microsoft.com/en-us/gaming/playfab/features/multiplayer/networking/party-unreal-engine-oss-obtaining-playfab-party-libraries"
    $localPath = ".\Platforms\Switch2"
    Set-NuGetPackageInfo $localPath $unifiedSdkNugetFileName $unifiedSdkNugetVersion
	nuget.exe restore $localPath -ConfigFile $localPath\nuget.config -PackagesDirectory $localPath
	Write-Host "Downloaded Nintendo Switch 2 Unified SDK NuGet packages."

	$sharedBuildCs = "Source\PlayFabShared\PlayFabShared.Build.cs"
	if ((Test-Path $sharedBuildCs) -and (Select-String -Path $sharedBuildCs -Pattern 'HC_PLATFORM_NINTENDO_SWITCH' -SimpleMatch -Quiet))
	{
		Write-Host "Switch patch already applied to $sharedBuildCs; skipping git apply."
	}
	else
	{
		Write-Host "Updating git submodules for private platforms..."
		git submodule update --recursive --init Source/PlayFabCore/PlatformSpecific/Switch

		Write-Host "Patching Switch platforms patch..."
		git apply --reject --whitespace=fix Source/PlayFabCore/PlatformSpecific/Switch/switch.patch
	}
}
elseif ($Platform -eq "PlayStation")
{
	Write-Host "Select PlayStation 5 Unified SDK version..."
	Write-Host "    1: SDK 2.3.0"
	while($True)
	{
		Write-Host -NoNewline "> "
		$inputString = ""
		while ($true)
		{
			$key = $Host.UI.RawUI.ReadKey()
			if ($key.VirtualKeyCode -eq 13) # Enter key
			{
				break
			}
			$inputString += $key.Character
		}
		$Selection = $inputString
		Write-Host ""
		if ($Selection -eq '1')
		{
			$unifiedSdkNugetFileName = "Microsoft.PlayFab.UnifiedSDK.Cpp.PS5-12.000"
			$unifiedSdkNugetVersion = "2.3.0"
			break
		}
		Write-Host "Unknown input"
	}
	Write-Host "Downloading PlayStation 5 Unified SDK NuGet package..."
	Write-Host $unifiedSdkNugetFileName". Unified SDK version="$unifiedSdkNugetVersion
	$localPath = ".\Platforms\PS5"
	Set-NuGetPackageInfo $localPath $unifiedSdkNugetFileName $unifiedSdkNugetVersion
	nuget.exe restore $localPath -ConfigFile $localPath\nuget.config -PackagesDirectory $localPath
	Write-Host "Downloaded PlayStation 5 Unified SDK NuGet package."

	Write-Host "Select PlayStation 4 Unified SDK version..."
	Write-Host "    1: SDK 2.3.0"
	while($True)
	{
		Write-Host -NoNewline "> "
		$inputString = ""
		while ($true)
		{
			$key = $Host.UI.RawUI.ReadKey()
			if ($key.VirtualKeyCode -eq 13) # Enter key
			{
				break
			}
			$inputString += $key.Character
		}
		$Selection = $inputString
		Write-Host ""
		if ($Selection -eq '1')
		{
			$unifiedSdkNugetFileName = "Microsoft.PlayFab.UnifiedSDK.Cpp.PS4-12.500"
			$unifiedSdkNugetVersion = "2.3.0"
			break
		}
		Write-Host "Unknown input"
	}
	Write-Host "Downloading PlayStation 4 Unified SDK NuGet package..."
	Write-Host $unifiedSdkNugetFileName". Unified SDK version="$unifiedSdkNugetVersion
	$localPath = ".\Platforms\PS4"
	Set-NuGetPackageInfo $localPath $unifiedSdkNugetFileName $unifiedSdkNugetVersion
	nuget.exe restore $localPath -ConfigFile $localPath\nuget.config -PackagesDirectory $localPath
	Write-Host "Downloaded PlayStation 4 Unified SDK NuGet package."

	Write-Host "Updating git submodules for private platforms..."
	git submodule update --recursive --init Source/PlayFabCore/PlatformSpecific/PlayStation

	$sharedBuildCs = "Source\PlayFabShared\PlayFabShared.Build.cs"
	if ((Test-Path $sharedBuildCs) -and (Select-String -Path $sharedBuildCs -Pattern 'HC_PLATFORM_NINTENDO_SWITCH' -SimpleMatch -Quiet))
	{
		Write-Error "Cannot apply PlayStation patch: the Switch patch is already applied to $sharedBuildCs. The PlayStation patch's line offsets will not match and will produce .rej files. To recover: revert the Switch patch's changes (e.g. ``git checkout -- Source\PlayFabShared\PlayFabShared.Build.cs Source\PlayFabUnreal\PlayFabUnreal.Build.cs``), then run ``SetUpPrivate.ps1 -Platform PlayStation`` first, followed by ``SetUpPrivate.ps1 -Platform Switch``."
		exit 1
	}
	if ((Test-Path $sharedBuildCs) -and (Select-String -Path $sharedBuildCs -Pattern 'HC_PLATFORM_IS_PLAYSTATION' -SimpleMatch -Quiet))
	{
		Write-Host "PlayStation patch already applied to $sharedBuildCs; skipping git apply."
	}
	else
	{
		Write-Host "Patching PlayStation platforms patch..."
		git apply --reject --whitespace=fix Source/PlayFabCore/PlatformSpecific/PlayStation/playstation.patch
	}
}
