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
    Write-Host "Select Switch SDK version..."
    Write-Host "    1: SDK 14.3.0-shipping"
    Write-Host "    2: SDK 14.3.0-logging"
    Write-Host "    3: SDK 15.3.2-shipping"
    Write-Host "    4: SDK 15.3.2-logging"
    Write-Host "    5: SDK 16.2.0-shipping"
    Write-Host "    6: SDK 16.2.0-logging"
    Write-Host "    7: SDK 16.2.3-shipping"
    Write-Host "    8: SDK 16.2.3-logging"
    Write-Host "    9: SDK 18.3.1-shipping"
    Write-Host "    10: SDK 18.3.1-logging"
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
            $partyNugetFileName = "Microsoft.PlayFab.PlayFabParty.Cpp.Switch-14.3.0-shipping"
            $partyNugetVersion = "1.8.3"
            $mlpNugetFileName = "Microsoft.PlayFab.Multiplayer.Cpp.Switch-14.3.0-shipping"
            $mlpNugetVersion = "1.6.1"
            break
        }
        elseif ($Selection -eq '2')
        {
            $partyNugetFileName = "Microsoft.PlayFab.PlayFabParty.Cpp.Switch-14.3.0-logging"
            $partyNugetVersion = "1.8.3"
            $mlpNugetFileName = "Microsoft.PlayFab.Multiplayer.Cpp.Switch-14.3.0-logging"
            $mlpNugetVersion = "1.6.1"
            break
        }
        elseif ($Selection -eq '3')
        {
            $partyNugetFileName = "Microsoft.PlayFab.PlayFabParty.Cpp.Switch-15.3.2-shipping"
            $partyNugetVersion = "1.8.5"
            $mlpNugetFileName = "Microsoft.PlayFab.Multiplayer.Cpp.Switch-15.3.2-shipping"
            $mlpNugetVersion = "1.6.2"
            break
        }
        elseif ($Selection -eq '4')
        {
            $partyNugetFileName = "Microsoft.PlayFab.PlayFabParty.Cpp.Switch-15.3.2-logging"
            $partyNugetVersion = "1.8.5"
            $mlpNugetFileName = "Microsoft.PlayFab.Multiplayer.Cpp.Switch-15.3.2-logging"
            $mlpNugetVersion = "1.6.2"
            break
        }
        elseif ($Selection -eq '5')
        {
            $partyNugetFileName = "Microsoft.PlayFab.PlayFabParty.Cpp.Switch-16.2.0-shipping"
            $partyNugetVersion = "1.8.11"
            $mlpNugetFileName = "Microsoft.PlayFab.Multiplayer.Cpp.Switch-16.2.0-shipping"
            $mlpNugetVersion = "1.6.2"
            break
        }
        elseif ($Selection -eq '6')
        {
            $partyNugetFileName = "Microsoft.PlayFab.PlayFabParty.Cpp.Switch-16.2.0-logging"
            $partyNugetVersion = "1.8.11"
            $mlpNugetFileName = "Microsoft.PlayFab.Multiplayer.Cpp.Switch-16.2.0-logging"
            $mlpNugetVersion = "1.6.2"
            break
        }
        elseif ($Selection -eq '7')
        {
            $partyNugetFileName = "Microsoft.PlayFab.PlayFabParty.Cpp.Switch-16.2.3-shipping"
            $partyNugetVersion = "1.9.5"
            $mlpNugetFileName = "Microsoft.PlayFab.Multiplayer.Cpp.Switch-16.2.3-shipping"
            $mlpNugetVersion = "1.7.2"
            break
        }
        elseif ($Selection -eq '8')
        {
            $partyNugetFileName = "Microsoft.PlayFab.PlayFabParty.Cpp.Switch-16.2.3-logging"
            $partyNugetVersion = "1.9.5"
            $mlpNugetFileName = "Microsoft.PlayFab.Multiplayer.Cpp.Switch-16.2.3-logging"
            $mlpNugetVersion = "1.7.2"
            break
        }
        elseif ($Selection -eq '9')
        {
            $partyNugetFileName = "Microsoft.PlayFab.PlayFabParty.Cpp.Switch-18.3.2-shipping"
            $partyNugetVersion = "1.10.9"
            $mlpNugetFileName = "Microsoft.PlayFab.Multiplayer.Cpp.Switch-18.3.2-shipping"
            $mlpNugetVersion = "1.7.9"
            break
        }
        elseif ($Selection -eq '10')
        {
            $partyNugetFileName = "Microsoft.PlayFab.PlayFabParty.Cpp.Switch-18.3.2-logging"
            $partyNugetVersion = "1.10.9"
            $mlpNugetFileName = "Microsoft.PlayFab.Multiplayer.Cpp.Switch-18.3.2-logging"
            $mlpNugetVersion = "1.7.9"
            break
        }
        Write-Host "Unknown input"
    }
	Write-Host "Downloading Switch Party and Multiplayer NuGet packages..."
    Write-Host $partyNugetFileName". Downloaded Party SDK version="$partyNugetVersion
    Write-Host $mlpNugetFileName". Downloaded Multiplayer SDK version="$mlpNugetVersion
    Write-Host "If you want to use a higher version of Party and Multiplayer SDK, please checkout to our private repositories and follow https://learn.microsoft.com/en-us/gaming/playfab/features/multiplayer/networking/party-unreal-engine-oss-obtaining-playfab-party-libraries"
	$localPath = ".\Platforms\Switch"
    Set-NuGetPackageInfo $localPath $partyNugetFileName $partyNugetVersion $mlpNugetFileName $mlpNugetVersion
	nuget.exe restore $localPath -ConfigFile $localPath\nuget.config -PackagesDirectory $localPath

	Write-Host "Updating git submodules for private platforms..."
	git submodule update --recursive --init Source/PlatformSpecific/Switch
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
	Write-Host "Downloading PlayStation 5 UnifiedSDK NuGet package..."
	Write-Host $unifiedSdkNugetFileName". Downloaded UnifiedSDK version="$unifiedSdkNugetVersion
	$localPath = ".\Platforms\PS5"
	Set-UnifiedSDKPackageInfo $localPath $unifiedSdkNugetFileName $unifiedSdkNugetVersion
	nuget.exe restore $localPath -ConfigFile $localPath\nuget.config -PackagesDirectory $localPath

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
	Write-Host "Downloading PlayStation 4 UnifiedSDK NuGet package..."
	Write-Host $unifiedSdkNugetFileName". Downloaded UnifiedSDK version="$unifiedSdkNugetVersion
	$localPath = ".\Platforms\PS4"
	Set-UnifiedSDKPackageInfo $localPath $unifiedSdkNugetFileName $unifiedSdkNugetVersion
	nuget.exe restore $localPath -ConfigFile $localPath\nuget.config -PackagesDirectory $localPath

	Write-Host "Updating git submodules for private platforms..."
	git submodule update --recursive --init Source/PlatformSpecific/PlayStation

	Write-Host "Patching PlayStation platforms patch..."
	git apply --reject --whitespace=fix Source/PlatformSpecific/PlayStation/playstation.patch
}
