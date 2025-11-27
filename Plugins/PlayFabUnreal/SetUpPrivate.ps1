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
    Write-Host "Switch is not supported yet for Unified SDK."
}
elseif ($Platform -eq "PlayStation")
{
    $Selection = ''
    if (-not $Version -eq '')
    {
        $Selection = $Version
    }
	Write-Host "Select PlayStation 5 Unified SDK version..."
	Write-Host "    1: SDK 2.0.9-prerelease"
    Write-Host "    2: SDK 2.0.10-prerelease"
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
            $unifiedSdkNugetFileName = "Microsoft.PlayFab.UnifiedSDK.Cpp.PS5-11.000"
            $unifiedSdkNugetVersion = "2.0.9-prerelease"
            break
        }
        if ($Selection -eq '2')
        {
            $unifiedSdkNugetFileName = "Microsoft.PlayFab.UnifiedSDK.Cpp.PS5-11.000"
            $unifiedSdkNugetVersion = "2.0.10-prerelease"
            break
        }
        Write-Host "Unknown input"
    }
	Write-Host "Downloading PlayStation 5 Unified SDK NuGet packages..."
    Write-Host $unifiedSdkNugetFileName". Downloaded Unified SDK version="$unifiedSdkNugetVersion
    Write-Host "If you want to use a higher version of the Unified SDK, please checkout to our private repositories and follow https://learn.microsoft.com/en-us/gaming/playfab/features/multiplayer/networking/party-unreal-engine-oss-obtaining-playfab-party-libraries"
    $localPath = ".\Platforms\PS5"
    Set-NuGetPackageInfo $localPath $unifiedSdkNugetFileName $unifiedSdkNugetVersion
	nuget.exe restore $localPath -ConfigFile $localPath\nuget.config -PackagesDirectory $localPath

	# Write-Host "Updating git submodules for private platforms..."
	# git submodule update --recursive --init Source/PlatformSpecific/PlayStation

	Write-Host "Patching PlayStation platforms patch..."
	git apply --reject --whitespace=fix Source/PlayFabCore/PlatformSpecific/PlayStation/playstation.patch
}
