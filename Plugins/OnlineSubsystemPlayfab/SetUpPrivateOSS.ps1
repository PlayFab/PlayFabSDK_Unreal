# This script downloads the private platform components of the OSS, for the platforms the user has access to.
# The binaries and header files are pulled from our NuGet feeds at https://dev.azure.com/PlayFabPrivate/. You can
# find the NuGet config files in the Platforms/[APlatform] folder.
# The private source code is pulled from our Git repositories as submodules.

# Prerequesites: download NuGet.exe and add its path to the PATH environment variable. Have git installed.

param (
	[Parameter(Mandatory=$true)]
	[validateset("Switch", "PlayStation")]
	[string]$Platform
)

$partyNugetFileName = ""
$partyNugetVersion = ""
$mlpNugetFileName = ""
$mlpNugetVersion = ""

function Set-NuGetPackageInfo($localPath, $partyFileName, $partyVersion, $mlpFileName, $mlpVersion)
{
    $packagesXml = Get-Content $localPath\packages.config".xml"
    $packagesXml = $packagesXml -replace "##PARTY##", $partyFileName
    $packagesXml = $packagesXml -replace "##PARTY_VERSION##", $partyVersion
    $packagesXml = $packagesXml -replace "##MULTIPLAYER##", $mlpFileName
    $packagesXml = $packagesXml -replace "##MULTIPLAYER_VERSION##", $mlpVersion
    Set-Content -Path $localPath\packages.config -Value $packagesXml
}

$unifiedSdkNugetFileName = ""
$unifiedSdkNugetVersion = ""

function Set-UnifiedSDKPackageInfo($localPath, $sdkFileName, $sdkVersion)
{
    $packagesXml = Get-Content $localPath\packages.config".xml"
    $packagesXml = $packagesXml -replace "##UNIFIED_SDK##", $sdkFileName
    $packagesXml = $packagesXml -replace "##UNIFIED_SDK_VERSION##", $sdkVersion
    Set-Content -Path $localPath\packages.config -Value $packagesXml
}

if ($Platform -eq "Switch")
{
    Write-Host "Select Switch Unified SDK version..."
    Write-Host "    1: SDK 2.3.1 (Switch-20.5.21)"
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
    Write-Host "Downloading Switch UnifiedSDK NuGet package $unifiedSdkNugetFileName (version $unifiedSdkNugetVersion)..."
    $localPath = ".\Platforms\Switch"
    Set-UnifiedSDKPackageInfo $localPath $unifiedSdkNugetFileName $unifiedSdkNugetVersion
    nuget.exe restore $localPath -ConfigFile $localPath\nuget.config -PackagesDirectory $localPath
    Write-Host "Downloaded Switch UnifiedSDK NuGet package."

    Write-Host "Select Switch2 Unified SDK version..."
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
    Write-Host "Downloading Switch2 UnifiedSDK NuGet package $unifiedSdkNugetFileName (version $unifiedSdkNugetVersion)..."
    $localPath = ".\Platforms\Switch2"
    Set-UnifiedSDKPackageInfo $localPath $unifiedSdkNugetFileName $unifiedSdkNugetVersion
    nuget.exe restore $localPath -ConfigFile $localPath\nuget.config -PackagesDirectory $localPath
    Write-Host "Downloaded Switch2 UnifiedSDK NuGet package."

    Write-Host "Updating git submodules for private platforms..."
    git submodule update --recursive --init Source/PlatformSpecific/Switch

    $buildCs = "Source\OnlineSubsystemPlayFab.Build.cs"
    if ((Test-Path $buildCs) -and (Select-String -Path $buildCs -Pattern 'libHttpClient.Switch.nrr' -SimpleMatch -Quiet))
    {
        Write-Host "Switch patch already applied to $buildCs; skipping git apply."
    }
    else
    {
        Write-Host "Patching Switch platforms patch..."
        git apply --reject --whitespace=fix Source/PlatformSpecific/Switch/switch.patch
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
	Write-Host "Downloading PlayStation 5 UnifiedSDK NuGet package $unifiedSdkNugetFileName (version $unifiedSdkNugetVersion)..."
	$localPath = ".\Platforms\PS5"
	Set-UnifiedSDKPackageInfo $localPath $unifiedSdkNugetFileName $unifiedSdkNugetVersion
	nuget.exe restore $localPath -ConfigFile $localPath\nuget.config -PackagesDirectory $localPath
	Write-Host "Downloaded PlayStation 5 UnifiedSDK NuGet package."

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
	Write-Host "Downloading PlayStation 4 UnifiedSDK NuGet package $unifiedSdkNugetFileName (version $unifiedSdkNugetVersion)..."
	$localPath = ".\Platforms\PS4"
	Set-UnifiedSDKPackageInfo $localPath $unifiedSdkNugetFileName $unifiedSdkNugetVersion
	nuget.exe restore $localPath -ConfigFile $localPath\nuget.config -PackagesDirectory $localPath
	Write-Host "Downloaded PlayStation 4 UnifiedSDK NuGet package."

	Write-Host "Updating git submodules for private platforms..."
	git submodule update --recursive --init Source/PlatformSpecific/PlayStation

	$buildCs = "Source\OnlineSubsystemPlayFab.Build.cs"
	if ((Test-Path $buildCs) -and (Select-String -Path $buildCs -Pattern 'libHttpClient.Switch.nrr' -SimpleMatch -Quiet))
	{
		Write-Error "Cannot apply PlayStation patch: the Switch patch is already applied to $buildCs. The PlayStation patch's line offsets will not match and will produce .rej files. To recover: revert $buildCs (e.g. ``git checkout -- $buildCs``), then run ``SetUpPrivateOSS.ps1 -Platform PlayStation`` first, followed by ``SetUpPrivateOSS.ps1 -Platform Switch``."
		exit 1
	}
	if ((Test-Path $buildCs) -and (Select-String -Path $buildCs -Pattern 'precompiled dependencies were not found for PS5' -SimpleMatch -Quiet))
	{
		Write-Host "PlayStation patch already applied to $buildCs; skipping git apply."
	}
	else
	{
		Write-Host "Patching PlayStation platforms patch..."
		git apply --reject --whitespace=fix Source/PlatformSpecific/PlayStation/playstation.patch
	}
}
