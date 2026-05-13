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
	Write-Host $unifiedSdkNugetFileName". Downloaded Unified SDK version="$unifiedSdkNugetVersion
	$localPath = ".\Platforms\PS5"
	Set-NuGetPackageInfo $localPath $unifiedSdkNugetFileName $unifiedSdkNugetVersion
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
	Write-Host "Downloading PlayStation 4 Unified SDK NuGet package..."
	Write-Host $unifiedSdkNugetFileName". Downloaded Unified SDK version="$unifiedSdkNugetVersion
	$localPath = ".\Platforms\PS4"
	Set-NuGetPackageInfo $localPath $unifiedSdkNugetFileName $unifiedSdkNugetVersion
	nuget.exe restore $localPath -ConfigFile $localPath\nuget.config -PackagesDirectory $localPath

	Write-Host "Updating git submodules for private platforms..."
	git submodule update --recursive --init Source/PlayFabCore/PlatformSpecific/PlayStation

	Write-Host "Patching PlayStation platforms patch..."
	git apply --reject --whitespace=fix Source/PlayFabCore/PlatformSpecific/PlayStation/playstation.patch
}
