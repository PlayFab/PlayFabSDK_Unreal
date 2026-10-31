//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"

#if !UE_BUILD_SHIPPING
namespace PlayFabPartyConfig
{
	bool ShouldUseDebugConnectivityPreservationMode(bool bConfigValueFound, bool bConfiguredValue);
	bool ShouldUseDebugConnectivityPreservationMode();
}
#endif