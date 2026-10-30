//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

#include "Templates/SharedPointer.h"

namespace PlayFabVoiceInitialization
{
	inline bool IsEnabled(bool bConfigValueFound, bool bConfiguredEnabled)
	{
		return !bConfigValueFound || bConfiguredEnabled;
	}

	template <typename VoiceInterfaceType, ESPMode Mode>
	TSharedPtr<VoiceInterfaceType, Mode> Initialize(TSharedPtr<VoiceInterfaceType, Mode> VoiceInterface)
	{
		if (!VoiceInterface.IsValid() || !VoiceInterface->Init())
		{
			return nullptr;
		}

		return VoiceInterface;
	}
}