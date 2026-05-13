# Usage: .\SetUpPrivatePlatforms.ps1 -Platform PlayStation

param (
	[Parameter(Mandatory=$true)]
	[ValidateSet("Switch", "PlayStation")]
	[string]$Platform
)

$scriptRoot = $PSScriptRoot

# Set up PlayFabUnreal plugin
Write-Host "========================================"
Write-Host "Setting up PlayFabUnreal ($Platform)..."
Write-Host "========================================"
Push-Location "$scriptRoot\Plugins\PlayFabUnreal"
try {
	& ".\SetUpPrivate.ps1" -Platform $Platform
}
finally {
	Pop-Location
}

# Set up OnlineSubsystemPlayfab plugin
Write-Host "========================================"
Write-Host "Setting up OnlineSubsystemPlayfab ($Platform)..."
Write-Host "========================================"
Push-Location "$scriptRoot\Plugins\OnlineSubsystemPlayfab"
try {
	& ".\SetUpPrivateOSS.ps1" -Platform $Platform
}
finally {
	Pop-Location
}

Write-Host "========================================"
Write-Host "Setup complete!"
Write-Host "========================================"
