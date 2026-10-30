//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "PlayFabPartyConfig.h"

#if !UE_BUILD_SHIPPING
#include "Misc/ConfigCacheIni.h"

namespace PlayFabPartyConfig
{
	bool ShouldUseDebugConnectivityPreservationMode(bool bConfigValueFound, bool bConfiguredValue)
	{
		return bConfigValueFound && bConfiguredValue;
	}

	bool ShouldUseDebugConnectivityPreservationMode()
	{
		bool bConfiguredValue = false;
		const bool bConfigValueFound = GConfig != nullptr && GConfig->GetBool(
			TEXT("OnlineSubsystemPlayFab"),
			TEXT("bUsePartyDebugConnectivityPreservationMode"),
			bConfiguredValue,
			GEngineIni);

		return ShouldUseDebugConnectivityPreservationMode(bConfigValueFound, bConfiguredValue);
	}
}
#endif