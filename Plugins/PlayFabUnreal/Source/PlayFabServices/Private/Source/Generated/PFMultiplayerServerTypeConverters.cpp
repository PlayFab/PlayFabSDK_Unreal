// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFMultiplayerServerTypeConverters.h"

const FPFMultiplayerServerAzureVmSize ConvertAzureVmSizeToUnreal(const PFMultiplayerServerAzureVmSize* enumVal)
{
	if (enumVal == nullptr) {
		return FPFMultiplayerServerAzureVmSize::Standard_A1;
	}

	switch(*enumVal)
	{
	case PFMultiplayerServerAzureVmSize::Standard_A1: return FPFMultiplayerServerAzureVmSize::Standard_A1;
	case PFMultiplayerServerAzureVmSize::Standard_A2: return FPFMultiplayerServerAzureVmSize::Standard_A2;
	case PFMultiplayerServerAzureVmSize::Standard_A3: return FPFMultiplayerServerAzureVmSize::Standard_A3;
	case PFMultiplayerServerAzureVmSize::Standard_A4: return FPFMultiplayerServerAzureVmSize::Standard_A4;
	case PFMultiplayerServerAzureVmSize::Standard_A1_v2: return FPFMultiplayerServerAzureVmSize::Standard_A1_v2;
	case PFMultiplayerServerAzureVmSize::Standard_A2_v2: return FPFMultiplayerServerAzureVmSize::Standard_A2_v2;
	case PFMultiplayerServerAzureVmSize::Standard_A4_v2: return FPFMultiplayerServerAzureVmSize::Standard_A4_v2;
	case PFMultiplayerServerAzureVmSize::Standard_A8_v2: return FPFMultiplayerServerAzureVmSize::Standard_A8_v2;
	case PFMultiplayerServerAzureVmSize::Standard_D1_v2: return FPFMultiplayerServerAzureVmSize::Standard_D1_v2;
	case PFMultiplayerServerAzureVmSize::Standard_D2_v2: return FPFMultiplayerServerAzureVmSize::Standard_D2_v2;
	case PFMultiplayerServerAzureVmSize::Standard_D3_v2: return FPFMultiplayerServerAzureVmSize::Standard_D3_v2;
	case PFMultiplayerServerAzureVmSize::Standard_D4_v2: return FPFMultiplayerServerAzureVmSize::Standard_D4_v2;
	case PFMultiplayerServerAzureVmSize::Standard_D5_v2: return FPFMultiplayerServerAzureVmSize::Standard_D5_v2;
	case PFMultiplayerServerAzureVmSize::Standard_D2_v3: return FPFMultiplayerServerAzureVmSize::Standard_D2_v3;
	case PFMultiplayerServerAzureVmSize::Standard_D4_v3: return FPFMultiplayerServerAzureVmSize::Standard_D4_v3;
	case PFMultiplayerServerAzureVmSize::Standard_D8_v3: return FPFMultiplayerServerAzureVmSize::Standard_D8_v3;
	case PFMultiplayerServerAzureVmSize::Standard_D16_v3: return FPFMultiplayerServerAzureVmSize::Standard_D16_v3;
	case PFMultiplayerServerAzureVmSize::Standard_F1: return FPFMultiplayerServerAzureVmSize::Standard_F1;
	case PFMultiplayerServerAzureVmSize::Standard_F2: return FPFMultiplayerServerAzureVmSize::Standard_F2;
	case PFMultiplayerServerAzureVmSize::Standard_F4: return FPFMultiplayerServerAzureVmSize::Standard_F4;
	case PFMultiplayerServerAzureVmSize::Standard_F8: return FPFMultiplayerServerAzureVmSize::Standard_F8;
	case PFMultiplayerServerAzureVmSize::Standard_F16: return FPFMultiplayerServerAzureVmSize::Standard_F16;
	case PFMultiplayerServerAzureVmSize::Standard_F2s_v2: return FPFMultiplayerServerAzureVmSize::Standard_F2s_v2;
	case PFMultiplayerServerAzureVmSize::Standard_F4s_v2: return FPFMultiplayerServerAzureVmSize::Standard_F4s_v2;
	case PFMultiplayerServerAzureVmSize::Standard_F8s_v2: return FPFMultiplayerServerAzureVmSize::Standard_F8s_v2;
	case PFMultiplayerServerAzureVmSize::Standard_F16s_v2: return FPFMultiplayerServerAzureVmSize::Standard_F16s_v2;
	case PFMultiplayerServerAzureVmSize::Standard_D2as_v4: return FPFMultiplayerServerAzureVmSize::Standard_D2as_v4;
	case PFMultiplayerServerAzureVmSize::Standard_D4as_v4: return FPFMultiplayerServerAzureVmSize::Standard_D4as_v4;
	case PFMultiplayerServerAzureVmSize::Standard_D8as_v4: return FPFMultiplayerServerAzureVmSize::Standard_D8as_v4;
	case PFMultiplayerServerAzureVmSize::Standard_D16as_v4: return FPFMultiplayerServerAzureVmSize::Standard_D16as_v4;
	case PFMultiplayerServerAzureVmSize::Standard_D2a_v4: return FPFMultiplayerServerAzureVmSize::Standard_D2a_v4;
	case PFMultiplayerServerAzureVmSize::Standard_D4a_v4: return FPFMultiplayerServerAzureVmSize::Standard_D4a_v4;
	case PFMultiplayerServerAzureVmSize::Standard_D8a_v4: return FPFMultiplayerServerAzureVmSize::Standard_D8a_v4;
	case PFMultiplayerServerAzureVmSize::Standard_D16a_v4: return FPFMultiplayerServerAzureVmSize::Standard_D16a_v4;
	case PFMultiplayerServerAzureVmSize::Standard_D2ads_v5: return FPFMultiplayerServerAzureVmSize::Standard_D2ads_v5;
	case PFMultiplayerServerAzureVmSize::Standard_D4ads_v5: return FPFMultiplayerServerAzureVmSize::Standard_D4ads_v5;
	case PFMultiplayerServerAzureVmSize::Standard_D8ads_v5: return FPFMultiplayerServerAzureVmSize::Standard_D8ads_v5;
	case PFMultiplayerServerAzureVmSize::Standard_D16ads_v5: return FPFMultiplayerServerAzureVmSize::Standard_D16ads_v5;
	case PFMultiplayerServerAzureVmSize::Standard_D2ads_v6: return FPFMultiplayerServerAzureVmSize::Standard_D2ads_v6;
	case PFMultiplayerServerAzureVmSize::Standard_D4ads_v6: return FPFMultiplayerServerAzureVmSize::Standard_D4ads_v6;
	case PFMultiplayerServerAzureVmSize::Standard_D8ads_v6: return FPFMultiplayerServerAzureVmSize::Standard_D8ads_v6;
	case PFMultiplayerServerAzureVmSize::Standard_D16ads_v6: return FPFMultiplayerServerAzureVmSize::Standard_D16ads_v6;
	case PFMultiplayerServerAzureVmSize::Standard_E2a_v4: return FPFMultiplayerServerAzureVmSize::Standard_E2a_v4;
	case PFMultiplayerServerAzureVmSize::Standard_E4a_v4: return FPFMultiplayerServerAzureVmSize::Standard_E4a_v4;
	case PFMultiplayerServerAzureVmSize::Standard_E8a_v4: return FPFMultiplayerServerAzureVmSize::Standard_E8a_v4;
	case PFMultiplayerServerAzureVmSize::Standard_E16a_v4: return FPFMultiplayerServerAzureVmSize::Standard_E16a_v4;
	case PFMultiplayerServerAzureVmSize::Standard_E2as_v4: return FPFMultiplayerServerAzureVmSize::Standard_E2as_v4;
	case PFMultiplayerServerAzureVmSize::Standard_E4as_v4: return FPFMultiplayerServerAzureVmSize::Standard_E4as_v4;
	case PFMultiplayerServerAzureVmSize::Standard_E8as_v4: return FPFMultiplayerServerAzureVmSize::Standard_E8as_v4;
	case PFMultiplayerServerAzureVmSize::Standard_E16as_v4: return FPFMultiplayerServerAzureVmSize::Standard_E16as_v4;
	case PFMultiplayerServerAzureVmSize::Standard_D2s_v3: return FPFMultiplayerServerAzureVmSize::Standard_D2s_v3;
	case PFMultiplayerServerAzureVmSize::Standard_D4s_v3: return FPFMultiplayerServerAzureVmSize::Standard_D4s_v3;
	case PFMultiplayerServerAzureVmSize::Standard_D8s_v3: return FPFMultiplayerServerAzureVmSize::Standard_D8s_v3;
	case PFMultiplayerServerAzureVmSize::Standard_D16s_v3: return FPFMultiplayerServerAzureVmSize::Standard_D16s_v3;
	case PFMultiplayerServerAzureVmSize::Standard_DS1_v2: return FPFMultiplayerServerAzureVmSize::Standard_DS1_v2;
	case PFMultiplayerServerAzureVmSize::Standard_DS2_v2: return FPFMultiplayerServerAzureVmSize::Standard_DS2_v2;
	case PFMultiplayerServerAzureVmSize::Standard_DS3_v2: return FPFMultiplayerServerAzureVmSize::Standard_DS3_v2;
	case PFMultiplayerServerAzureVmSize::Standard_DS4_v2: return FPFMultiplayerServerAzureVmSize::Standard_DS4_v2;
	case PFMultiplayerServerAzureVmSize::Standard_DS5_v2: return FPFMultiplayerServerAzureVmSize::Standard_DS5_v2;
	case PFMultiplayerServerAzureVmSize::Standard_NC4as_T4_v3: return FPFMultiplayerServerAzureVmSize::Standard_NC4as_T4_v3;
	case PFMultiplayerServerAzureVmSize::Standard_D2d_v4: return FPFMultiplayerServerAzureVmSize::Standard_D2d_v4;
	case PFMultiplayerServerAzureVmSize::Standard_D4d_v4: return FPFMultiplayerServerAzureVmSize::Standard_D4d_v4;
	case PFMultiplayerServerAzureVmSize::Standard_D8d_v4: return FPFMultiplayerServerAzureVmSize::Standard_D8d_v4;
	case PFMultiplayerServerAzureVmSize::Standard_D16d_v4: return FPFMultiplayerServerAzureVmSize::Standard_D16d_v4;
	case PFMultiplayerServerAzureVmSize::Standard_D2ds_v4: return FPFMultiplayerServerAzureVmSize::Standard_D2ds_v4;
	case PFMultiplayerServerAzureVmSize::Standard_D4ds_v4: return FPFMultiplayerServerAzureVmSize::Standard_D4ds_v4;
	case PFMultiplayerServerAzureVmSize::Standard_D8ds_v4: return FPFMultiplayerServerAzureVmSize::Standard_D8ds_v4;
	case PFMultiplayerServerAzureVmSize::Standard_D16ds_v4: return FPFMultiplayerServerAzureVmSize::Standard_D16ds_v4;
	case PFMultiplayerServerAzureVmSize::Standard_HB120_16rs_v3: return FPFMultiplayerServerAzureVmSize::Standard_HB120_16rs_v3;
	case PFMultiplayerServerAzureVmSize::Standard_HB120_32rs_v3: return FPFMultiplayerServerAzureVmSize::Standard_HB120_32rs_v3;
	case PFMultiplayerServerAzureVmSize::Standard_HB120_64rs_v3: return FPFMultiplayerServerAzureVmSize::Standard_HB120_64rs_v3;
	case PFMultiplayerServerAzureVmSize::Standard_HB120_96rs_v3: return FPFMultiplayerServerAzureVmSize::Standard_HB120_96rs_v3;
	case PFMultiplayerServerAzureVmSize::Standard_HB120rs_v3: return FPFMultiplayerServerAzureVmSize::Standard_HB120rs_v3;
	case PFMultiplayerServerAzureVmSize::Standard_D2d_v5: return FPFMultiplayerServerAzureVmSize::Standard_D2d_v5;
	case PFMultiplayerServerAzureVmSize::Standard_D4d_v5: return FPFMultiplayerServerAzureVmSize::Standard_D4d_v5;
	case PFMultiplayerServerAzureVmSize::Standard_D8d_v5: return FPFMultiplayerServerAzureVmSize::Standard_D8d_v5;
	case PFMultiplayerServerAzureVmSize::Standard_D16d_v5: return FPFMultiplayerServerAzureVmSize::Standard_D16d_v5;
	case PFMultiplayerServerAzureVmSize::Standard_D32d_v5: return FPFMultiplayerServerAzureVmSize::Standard_D32d_v5;
	case PFMultiplayerServerAzureVmSize::Standard_D2ds_v5: return FPFMultiplayerServerAzureVmSize::Standard_D2ds_v5;
	case PFMultiplayerServerAzureVmSize::Standard_D4ds_v5: return FPFMultiplayerServerAzureVmSize::Standard_D4ds_v5;
	case PFMultiplayerServerAzureVmSize::Standard_D8ds_v5: return FPFMultiplayerServerAzureVmSize::Standard_D8ds_v5;
	case PFMultiplayerServerAzureVmSize::Standard_D16ds_v5: return FPFMultiplayerServerAzureVmSize::Standard_D16ds_v5;
	case PFMultiplayerServerAzureVmSize::Standard_D32ds_v5: return FPFMultiplayerServerAzureVmSize::Standard_D32ds_v5;
	default:
	return FPFMultiplayerServerAzureVmSize::Standard_A1;
	}
}

const PFMultiplayerServerAzureVmSize ConvertAzureVmSizeToPlayfab(TSharedPtr<const FPFMultiplayerServerAzureVmSize> enumVal)
{
	if (!enumVal.IsValid()) {
		return PFMultiplayerServerAzureVmSize::Standard_A1;
	}

	switch(*enumVal)
	{
	case FPFMultiplayerServerAzureVmSize::Standard_A1: return PFMultiplayerServerAzureVmSize::Standard_A1;
	case FPFMultiplayerServerAzureVmSize::Standard_A2: return PFMultiplayerServerAzureVmSize::Standard_A2;
	case FPFMultiplayerServerAzureVmSize::Standard_A3: return PFMultiplayerServerAzureVmSize::Standard_A3;
	case FPFMultiplayerServerAzureVmSize::Standard_A4: return PFMultiplayerServerAzureVmSize::Standard_A4;
	case FPFMultiplayerServerAzureVmSize::Standard_A1_v2: return PFMultiplayerServerAzureVmSize::Standard_A1_v2;
	case FPFMultiplayerServerAzureVmSize::Standard_A2_v2: return PFMultiplayerServerAzureVmSize::Standard_A2_v2;
	case FPFMultiplayerServerAzureVmSize::Standard_A4_v2: return PFMultiplayerServerAzureVmSize::Standard_A4_v2;
	case FPFMultiplayerServerAzureVmSize::Standard_A8_v2: return PFMultiplayerServerAzureVmSize::Standard_A8_v2;
	case FPFMultiplayerServerAzureVmSize::Standard_D1_v2: return PFMultiplayerServerAzureVmSize::Standard_D1_v2;
	case FPFMultiplayerServerAzureVmSize::Standard_D2_v2: return PFMultiplayerServerAzureVmSize::Standard_D2_v2;
	case FPFMultiplayerServerAzureVmSize::Standard_D3_v2: return PFMultiplayerServerAzureVmSize::Standard_D3_v2;
	case FPFMultiplayerServerAzureVmSize::Standard_D4_v2: return PFMultiplayerServerAzureVmSize::Standard_D4_v2;
	case FPFMultiplayerServerAzureVmSize::Standard_D5_v2: return PFMultiplayerServerAzureVmSize::Standard_D5_v2;
	case FPFMultiplayerServerAzureVmSize::Standard_D2_v3: return PFMultiplayerServerAzureVmSize::Standard_D2_v3;
	case FPFMultiplayerServerAzureVmSize::Standard_D4_v3: return PFMultiplayerServerAzureVmSize::Standard_D4_v3;
	case FPFMultiplayerServerAzureVmSize::Standard_D8_v3: return PFMultiplayerServerAzureVmSize::Standard_D8_v3;
	case FPFMultiplayerServerAzureVmSize::Standard_D16_v3: return PFMultiplayerServerAzureVmSize::Standard_D16_v3;
	case FPFMultiplayerServerAzureVmSize::Standard_F1: return PFMultiplayerServerAzureVmSize::Standard_F1;
	case FPFMultiplayerServerAzureVmSize::Standard_F2: return PFMultiplayerServerAzureVmSize::Standard_F2;
	case FPFMultiplayerServerAzureVmSize::Standard_F4: return PFMultiplayerServerAzureVmSize::Standard_F4;
	case FPFMultiplayerServerAzureVmSize::Standard_F8: return PFMultiplayerServerAzureVmSize::Standard_F8;
	case FPFMultiplayerServerAzureVmSize::Standard_F16: return PFMultiplayerServerAzureVmSize::Standard_F16;
	case FPFMultiplayerServerAzureVmSize::Standard_F2s_v2: return PFMultiplayerServerAzureVmSize::Standard_F2s_v2;
	case FPFMultiplayerServerAzureVmSize::Standard_F4s_v2: return PFMultiplayerServerAzureVmSize::Standard_F4s_v2;
	case FPFMultiplayerServerAzureVmSize::Standard_F8s_v2: return PFMultiplayerServerAzureVmSize::Standard_F8s_v2;
	case FPFMultiplayerServerAzureVmSize::Standard_F16s_v2: return PFMultiplayerServerAzureVmSize::Standard_F16s_v2;
	case FPFMultiplayerServerAzureVmSize::Standard_D2as_v4: return PFMultiplayerServerAzureVmSize::Standard_D2as_v4;
	case FPFMultiplayerServerAzureVmSize::Standard_D4as_v4: return PFMultiplayerServerAzureVmSize::Standard_D4as_v4;
	case FPFMultiplayerServerAzureVmSize::Standard_D8as_v4: return PFMultiplayerServerAzureVmSize::Standard_D8as_v4;
	case FPFMultiplayerServerAzureVmSize::Standard_D16as_v4: return PFMultiplayerServerAzureVmSize::Standard_D16as_v4;
	case FPFMultiplayerServerAzureVmSize::Standard_D2a_v4: return PFMultiplayerServerAzureVmSize::Standard_D2a_v4;
	case FPFMultiplayerServerAzureVmSize::Standard_D4a_v4: return PFMultiplayerServerAzureVmSize::Standard_D4a_v4;
	case FPFMultiplayerServerAzureVmSize::Standard_D8a_v4: return PFMultiplayerServerAzureVmSize::Standard_D8a_v4;
	case FPFMultiplayerServerAzureVmSize::Standard_D16a_v4: return PFMultiplayerServerAzureVmSize::Standard_D16a_v4;
	case FPFMultiplayerServerAzureVmSize::Standard_D2ads_v5: return PFMultiplayerServerAzureVmSize::Standard_D2ads_v5;
	case FPFMultiplayerServerAzureVmSize::Standard_D4ads_v5: return PFMultiplayerServerAzureVmSize::Standard_D4ads_v5;
	case FPFMultiplayerServerAzureVmSize::Standard_D8ads_v5: return PFMultiplayerServerAzureVmSize::Standard_D8ads_v5;
	case FPFMultiplayerServerAzureVmSize::Standard_D16ads_v5: return PFMultiplayerServerAzureVmSize::Standard_D16ads_v5;
	case FPFMultiplayerServerAzureVmSize::Standard_D2ads_v6: return PFMultiplayerServerAzureVmSize::Standard_D2ads_v6;
	case FPFMultiplayerServerAzureVmSize::Standard_D4ads_v6: return PFMultiplayerServerAzureVmSize::Standard_D4ads_v6;
	case FPFMultiplayerServerAzureVmSize::Standard_D8ads_v6: return PFMultiplayerServerAzureVmSize::Standard_D8ads_v6;
	case FPFMultiplayerServerAzureVmSize::Standard_D16ads_v6: return PFMultiplayerServerAzureVmSize::Standard_D16ads_v6;
	case FPFMultiplayerServerAzureVmSize::Standard_E2a_v4: return PFMultiplayerServerAzureVmSize::Standard_E2a_v4;
	case FPFMultiplayerServerAzureVmSize::Standard_E4a_v4: return PFMultiplayerServerAzureVmSize::Standard_E4a_v4;
	case FPFMultiplayerServerAzureVmSize::Standard_E8a_v4: return PFMultiplayerServerAzureVmSize::Standard_E8a_v4;
	case FPFMultiplayerServerAzureVmSize::Standard_E16a_v4: return PFMultiplayerServerAzureVmSize::Standard_E16a_v4;
	case FPFMultiplayerServerAzureVmSize::Standard_E2as_v4: return PFMultiplayerServerAzureVmSize::Standard_E2as_v4;
	case FPFMultiplayerServerAzureVmSize::Standard_E4as_v4: return PFMultiplayerServerAzureVmSize::Standard_E4as_v4;
	case FPFMultiplayerServerAzureVmSize::Standard_E8as_v4: return PFMultiplayerServerAzureVmSize::Standard_E8as_v4;
	case FPFMultiplayerServerAzureVmSize::Standard_E16as_v4: return PFMultiplayerServerAzureVmSize::Standard_E16as_v4;
	case FPFMultiplayerServerAzureVmSize::Standard_D2s_v3: return PFMultiplayerServerAzureVmSize::Standard_D2s_v3;
	case FPFMultiplayerServerAzureVmSize::Standard_D4s_v3: return PFMultiplayerServerAzureVmSize::Standard_D4s_v3;
	case FPFMultiplayerServerAzureVmSize::Standard_D8s_v3: return PFMultiplayerServerAzureVmSize::Standard_D8s_v3;
	case FPFMultiplayerServerAzureVmSize::Standard_D16s_v3: return PFMultiplayerServerAzureVmSize::Standard_D16s_v3;
	case FPFMultiplayerServerAzureVmSize::Standard_DS1_v2: return PFMultiplayerServerAzureVmSize::Standard_DS1_v2;
	case FPFMultiplayerServerAzureVmSize::Standard_DS2_v2: return PFMultiplayerServerAzureVmSize::Standard_DS2_v2;
	case FPFMultiplayerServerAzureVmSize::Standard_DS3_v2: return PFMultiplayerServerAzureVmSize::Standard_DS3_v2;
	case FPFMultiplayerServerAzureVmSize::Standard_DS4_v2: return PFMultiplayerServerAzureVmSize::Standard_DS4_v2;
	case FPFMultiplayerServerAzureVmSize::Standard_DS5_v2: return PFMultiplayerServerAzureVmSize::Standard_DS5_v2;
	case FPFMultiplayerServerAzureVmSize::Standard_NC4as_T4_v3: return PFMultiplayerServerAzureVmSize::Standard_NC4as_T4_v3;
	case FPFMultiplayerServerAzureVmSize::Standard_D2d_v4: return PFMultiplayerServerAzureVmSize::Standard_D2d_v4;
	case FPFMultiplayerServerAzureVmSize::Standard_D4d_v4: return PFMultiplayerServerAzureVmSize::Standard_D4d_v4;
	case FPFMultiplayerServerAzureVmSize::Standard_D8d_v4: return PFMultiplayerServerAzureVmSize::Standard_D8d_v4;
	case FPFMultiplayerServerAzureVmSize::Standard_D16d_v4: return PFMultiplayerServerAzureVmSize::Standard_D16d_v4;
	case FPFMultiplayerServerAzureVmSize::Standard_D2ds_v4: return PFMultiplayerServerAzureVmSize::Standard_D2ds_v4;
	case FPFMultiplayerServerAzureVmSize::Standard_D4ds_v4: return PFMultiplayerServerAzureVmSize::Standard_D4ds_v4;
	case FPFMultiplayerServerAzureVmSize::Standard_D8ds_v4: return PFMultiplayerServerAzureVmSize::Standard_D8ds_v4;
	case FPFMultiplayerServerAzureVmSize::Standard_D16ds_v4: return PFMultiplayerServerAzureVmSize::Standard_D16ds_v4;
	case FPFMultiplayerServerAzureVmSize::Standard_HB120_16rs_v3: return PFMultiplayerServerAzureVmSize::Standard_HB120_16rs_v3;
	case FPFMultiplayerServerAzureVmSize::Standard_HB120_32rs_v3: return PFMultiplayerServerAzureVmSize::Standard_HB120_32rs_v3;
	case FPFMultiplayerServerAzureVmSize::Standard_HB120_64rs_v3: return PFMultiplayerServerAzureVmSize::Standard_HB120_64rs_v3;
	case FPFMultiplayerServerAzureVmSize::Standard_HB120_96rs_v3: return PFMultiplayerServerAzureVmSize::Standard_HB120_96rs_v3;
	case FPFMultiplayerServerAzureVmSize::Standard_HB120rs_v3: return PFMultiplayerServerAzureVmSize::Standard_HB120rs_v3;
	case FPFMultiplayerServerAzureVmSize::Standard_D2d_v5: return PFMultiplayerServerAzureVmSize::Standard_D2d_v5;
	case FPFMultiplayerServerAzureVmSize::Standard_D4d_v5: return PFMultiplayerServerAzureVmSize::Standard_D4d_v5;
	case FPFMultiplayerServerAzureVmSize::Standard_D8d_v5: return PFMultiplayerServerAzureVmSize::Standard_D8d_v5;
	case FPFMultiplayerServerAzureVmSize::Standard_D16d_v5: return PFMultiplayerServerAzureVmSize::Standard_D16d_v5;
	case FPFMultiplayerServerAzureVmSize::Standard_D32d_v5: return PFMultiplayerServerAzureVmSize::Standard_D32d_v5;
	case FPFMultiplayerServerAzureVmSize::Standard_D2ds_v5: return PFMultiplayerServerAzureVmSize::Standard_D2ds_v5;
	case FPFMultiplayerServerAzureVmSize::Standard_D4ds_v5: return PFMultiplayerServerAzureVmSize::Standard_D4ds_v5;
	case FPFMultiplayerServerAzureVmSize::Standard_D8ds_v5: return PFMultiplayerServerAzureVmSize::Standard_D8ds_v5;
	case FPFMultiplayerServerAzureVmSize::Standard_D16ds_v5: return PFMultiplayerServerAzureVmSize::Standard_D16ds_v5;
	case FPFMultiplayerServerAzureVmSize::Standard_D32ds_v5: return PFMultiplayerServerAzureVmSize::Standard_D32ds_v5;
	default:
	return PFMultiplayerServerAzureVmSize::Standard_A1;
	}
}

const FPFMultiplayerServerProtocolType ConvertProtocolTypeToUnreal(const PFMultiplayerServerProtocolType* enumVal)
{
	if (enumVal == nullptr) {
		return FPFMultiplayerServerProtocolType::TCP;
	}

	switch(*enumVal)
	{
	case PFMultiplayerServerProtocolType::TCP: return FPFMultiplayerServerProtocolType::TCP;
	case PFMultiplayerServerProtocolType::UDP: return FPFMultiplayerServerProtocolType::UDP;
	default:
	return FPFMultiplayerServerProtocolType::TCP;
	}
}

const PFMultiplayerServerProtocolType ConvertProtocolTypeToPlayfab(TSharedPtr<const FPFMultiplayerServerProtocolType> enumVal)
{
	if (!enumVal.IsValid()) {
		return PFMultiplayerServerProtocolType::TCP;
	}

	switch(*enumVal)
	{
	case FPFMultiplayerServerProtocolType::TCP: return PFMultiplayerServerProtocolType::TCP;
	case FPFMultiplayerServerProtocolType::UDP: return PFMultiplayerServerProtocolType::UDP;
	default:
	return PFMultiplayerServerProtocolType::TCP;
	}
}

TSharedPtr<const FPFMultiplayerServerDeleteSecretRequest> ConvertDeleteSecretRequestToUnreal(const PFMultiplayerServerDeleteSecretRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFMultiplayerServerDeleteSecretRequest> ConvertedType = MakeShared<FPFMultiplayerServerDeleteSecretRequest>(FPFMultiplayerServerDeleteSecretRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name)
	});

	return ConvertedType;
}

const PFMultiplayerServerDeleteSecretRequest* ConvertDeleteSecretRequestToPlayfab(TSharedPtr<const FPFMultiplayerServerDeleteSecretRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFMultiplayerServerDeleteSecretRequest* ConvertedType = new PFMultiplayerServerDeleteSecretRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.name = ConvertFStringToCharPtr(Datatype->name)
	};

	return ConvertedType;
}

TSharedPtr<const FPFMultiplayerServerListBuildAliasesRequest> ConvertListBuildAliasesRequestToUnreal(const PFMultiplayerServerListBuildAliasesRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFMultiplayerServerListBuildAliasesRequest> ConvertedType = MakeShared<FPFMultiplayerServerListBuildAliasesRequest>(FPFMultiplayerServerListBuildAliasesRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.pageSize = TSharedPtr<const int32>(Datatype->pageSize),
		.skipToken = Datatype->skipToken == nullptr ? FString() : FString(Datatype->skipToken)
	});

	return ConvertedType;
}

const PFMultiplayerServerListBuildAliasesRequest* ConvertListBuildAliasesRequestToPlayfab(TSharedPtr<const FPFMultiplayerServerListBuildAliasesRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFMultiplayerServerListBuildAliasesRequest* ConvertedType = new PFMultiplayerServerListBuildAliasesRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.pageSize = Datatype->pageSize ? new int32(*Datatype->pageSize) : nullptr,
		.skipToken = ConvertFStringToCharPtr(Datatype->skipToken)
	};

	return ConvertedType;
}

TSharedPtr<const FPFMultiplayerServerBuildSelectionCriterion> ConvertBuildSelectionCriterionToUnreal(const PFMultiplayerServerBuildSelectionCriterion* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFMultiplayerServerBuildSelectionCriterion> ConvertedType = MakeShared<FPFMultiplayerServerBuildSelectionCriterion>(FPFMultiplayerServerBuildSelectionCriterion{
		.buildWeightDistribution = ConvertUintMapToUnreal(Datatype->buildWeightDistribution, Datatype->buildWeightDistributionCount),
		.buildWeightDistributionCount = Datatype->buildWeightDistributionCount
	});

	return ConvertedType;
}

const PFMultiplayerServerBuildSelectionCriterion* ConvertBuildSelectionCriterionToPlayfab(TSharedPtr<const FPFMultiplayerServerBuildSelectionCriterion> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFMultiplayerServerBuildSelectionCriterion* ConvertedType = new PFMultiplayerServerBuildSelectionCriterion{
		.buildWeightDistribution = ConvertUintMapToPlayfab(Datatype->buildWeightDistribution),
		.buildWeightDistributionCount = (uint32_t)Datatype->buildWeightDistribution.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFMultiplayerServerBuildAliasDetailsResponse> ConvertBuildAliasDetailsResponseToUnreal(const PFMultiplayerServerBuildAliasDetailsResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFMultiplayerServerBuildAliasDetailsResponse> ConvertedType = MakeShared<FPFMultiplayerServerBuildAliasDetailsResponse>(FPFMultiplayerServerBuildAliasDetailsResponse{
		.aliasId = Datatype->aliasId == nullptr ? FString() : FString(Datatype->aliasId),
		.aliasName = Datatype->aliasName == nullptr ? FString() : FString(Datatype->aliasName),
		.buildSelectionCriteria = ConvertPlayfabArrayToUnreal<PFMultiplayerServerBuildSelectionCriterion, FPFMultiplayerServerBuildSelectionCriterion>(Datatype->buildSelectionCriteria, Datatype->buildSelectionCriteriaCount, ConvertBuildSelectionCriterionToUnreal),
		.buildSelectionCriteriaCount = Datatype->buildSelectionCriteriaCount
	});

	return ConvertedType;
}

const PFMultiplayerServerBuildAliasDetailsResponse* ConvertBuildAliasDetailsResponseToPlayfab(TSharedPtr<const FPFMultiplayerServerBuildAliasDetailsResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFMultiplayerServerBuildAliasDetailsResponse* ConvertedType = new PFMultiplayerServerBuildAliasDetailsResponse{
		.aliasId = ConvertFStringToCharPtr(Datatype->aliasId),
		.aliasName = ConvertFStringToCharPtr(Datatype->aliasName),
		.buildSelectionCriteria = ConvertUnrealArrayToPlayfab<PFMultiplayerServerBuildSelectionCriterion, FPFMultiplayerServerBuildSelectionCriterion>(Datatype->buildSelectionCriteria, ConvertBuildSelectionCriterionToPlayfab),
		.buildSelectionCriteriaCount = (uint32_t)Datatype->buildSelectionCriteria.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFMultiplayerServerListBuildAliasesResponse> ConvertListBuildAliasesResponseToUnreal(const PFMultiplayerServerListBuildAliasesResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFMultiplayerServerListBuildAliasesResponse> ConvertedType = MakeShared<FPFMultiplayerServerListBuildAliasesResponse>(FPFMultiplayerServerListBuildAliasesResponse{
		.buildAliases = ConvertPlayfabArrayToUnreal<PFMultiplayerServerBuildAliasDetailsResponse, FPFMultiplayerServerBuildAliasDetailsResponse>(Datatype->buildAliases, Datatype->buildAliasesCount, ConvertBuildAliasDetailsResponseToUnreal),
		.buildAliasesCount = Datatype->buildAliasesCount,
		.pageSize = Datatype->pageSize,
		.skipToken = Datatype->skipToken == nullptr ? FString() : FString(Datatype->skipToken)
	});

	return ConvertedType;
}

const PFMultiplayerServerListBuildAliasesResponse* ConvertListBuildAliasesResponseToPlayfab(TSharedPtr<const FPFMultiplayerServerListBuildAliasesResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFMultiplayerServerListBuildAliasesResponse* ConvertedType = new PFMultiplayerServerListBuildAliasesResponse{
		.buildAliases = ConvertUnrealArrayToPlayfab<PFMultiplayerServerBuildAliasDetailsResponse, FPFMultiplayerServerBuildAliasDetailsResponse>(Datatype->buildAliases, ConvertBuildAliasDetailsResponseToPlayfab),
		.buildAliasesCount = (uint32_t)Datatype->buildAliases.Num(),
		.pageSize = Datatype->pageSize,
		.skipToken = ConvertFStringToCharPtr(Datatype->skipToken)
	};

	return ConvertedType;
}

TSharedPtr<const FPFMultiplayerServerListBuildSummariesRequest> ConvertListBuildSummariesRequestToUnreal(const PFMultiplayerServerListBuildSummariesRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFMultiplayerServerListBuildSummariesRequest> ConvertedType = MakeShared<FPFMultiplayerServerListBuildSummariesRequest>(FPFMultiplayerServerListBuildSummariesRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.pageSize = TSharedPtr<const int32>(Datatype->pageSize),
		.skipToken = Datatype->skipToken == nullptr ? FString() : FString(Datatype->skipToken)
	});

	return ConvertedType;
}

const PFMultiplayerServerListBuildSummariesRequest* ConvertListBuildSummariesRequestToPlayfab(TSharedPtr<const FPFMultiplayerServerListBuildSummariesRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFMultiplayerServerListBuildSummariesRequest* ConvertedType = new PFMultiplayerServerListBuildSummariesRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.pageSize = Datatype->pageSize ? new int32(*Datatype->pageSize) : nullptr,
		.skipToken = ConvertFStringToCharPtr(Datatype->skipToken)
	};

	return ConvertedType;
}

TSharedPtr<const FPFMultiplayerServerCurrentServerStats> ConvertCurrentServerStatsToUnreal(const PFMultiplayerServerCurrentServerStats* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFMultiplayerServerCurrentServerStats> ConvertedType = MakeShared<FPFMultiplayerServerCurrentServerStats>(FPFMultiplayerServerCurrentServerStats{
		.active = Datatype->active,
		.propping = Datatype->propping,
		.standingBy = Datatype->standingBy,
		.total = Datatype->total
	});

	return ConvertedType;
}

const PFMultiplayerServerCurrentServerStats* ConvertCurrentServerStatsToPlayfab(TSharedPtr<const FPFMultiplayerServerCurrentServerStats> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFMultiplayerServerCurrentServerStats* ConvertedType = new PFMultiplayerServerCurrentServerStats{
		.active = Datatype->active,
		.propping = Datatype->propping,
		.standingBy = Datatype->standingBy,
		.total = Datatype->total
	};

	return ConvertedType;
}

TSharedPtr<const FPFMultiplayerServerDynamicStandbyThreshold> ConvertDynamicStandbyThresholdToUnreal(const PFMultiplayerServerDynamicStandbyThreshold* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFMultiplayerServerDynamicStandbyThreshold> ConvertedType = MakeShared<FPFMultiplayerServerDynamicStandbyThreshold>(FPFMultiplayerServerDynamicStandbyThreshold{
		.multiplier = Datatype->multiplier,
		.triggerThresholdPercentage = Datatype->triggerThresholdPercentage
	});

	return ConvertedType;
}

const PFMultiplayerServerDynamicStandbyThreshold* ConvertDynamicStandbyThresholdToPlayfab(TSharedPtr<const FPFMultiplayerServerDynamicStandbyThreshold> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFMultiplayerServerDynamicStandbyThreshold* ConvertedType = new PFMultiplayerServerDynamicStandbyThreshold{
		.multiplier = Datatype->multiplier,
		.triggerThresholdPercentage = Datatype->triggerThresholdPercentage
	};

	return ConvertedType;
}

TSharedPtr<const FPFMultiplayerServerDynamicStandbySettings> ConvertDynamicStandbySettingsToUnreal(const PFMultiplayerServerDynamicStandbySettings* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFMultiplayerServerDynamicStandbySettings> ConvertedType = MakeShared<FPFMultiplayerServerDynamicStandbySettings>(FPFMultiplayerServerDynamicStandbySettings{
		.dynamicFloorMultiplierThresholds = ConvertPlayfabArrayToUnreal<PFMultiplayerServerDynamicStandbyThreshold, FPFMultiplayerServerDynamicStandbyThreshold>(Datatype->dynamicFloorMultiplierThresholds, Datatype->dynamicFloorMultiplierThresholdsCount, ConvertDynamicStandbyThresholdToUnreal),
		.dynamicFloorMultiplierThresholdsCount = Datatype->dynamicFloorMultiplierThresholdsCount,
		.isEnabled = Datatype->isEnabled,
		.rampDownSeconds = TSharedPtr<const int32>(Datatype->rampDownSeconds)
	});

	return ConvertedType;
}

const PFMultiplayerServerDynamicStandbySettings* ConvertDynamicStandbySettingsToPlayfab(TSharedPtr<const FPFMultiplayerServerDynamicStandbySettings> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFMultiplayerServerDynamicStandbySettings* ConvertedType = new PFMultiplayerServerDynamicStandbySettings{
		.dynamicFloorMultiplierThresholds = ConvertUnrealArrayToPlayfab<PFMultiplayerServerDynamicStandbyThreshold, FPFMultiplayerServerDynamicStandbyThreshold>(Datatype->dynamicFloorMultiplierThresholds, ConvertDynamicStandbyThresholdToPlayfab),
		.dynamicFloorMultiplierThresholdsCount = (uint32_t)Datatype->dynamicFloorMultiplierThresholds.Num(),
		.isEnabled = Datatype->isEnabled,
		.rampDownSeconds = Datatype->rampDownSeconds ? new int32(*Datatype->rampDownSeconds) : nullptr
	};

	return ConvertedType;
}

TSharedPtr<const FPFMultiplayerServerSchedule> ConvertScheduleToUnreal(const PFMultiplayerServerSchedule* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFMultiplayerServerSchedule> ConvertedType = MakeShared<FPFMultiplayerServerSchedule>(FPFMultiplayerServerSchedule{
		.description = Datatype->description == nullptr ? FString() : FString(Datatype->description),
		.endTime = FDateTime::FromUnixTimestamp((int64)Datatype->endTime),
		.isDisabled = Datatype->isDisabled,
		.isRecurringWeekly = Datatype->isRecurringWeekly,
		.startTime = FDateTime::FromUnixTimestamp((int64)Datatype->startTime),
		.targetStandby = Datatype->targetStandby
	});

	return ConvertedType;
}

const PFMultiplayerServerSchedule* ConvertScheduleToPlayfab(TSharedPtr<const FPFMultiplayerServerSchedule> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFMultiplayerServerSchedule* ConvertedType = new PFMultiplayerServerSchedule{
		.description = ConvertFStringToCharPtr(Datatype->description),
		.endTime = Datatype->endTime.ToUnixTimestamp(),
		.isDisabled = Datatype->isDisabled,
		.isRecurringWeekly = Datatype->isRecurringWeekly,
		.startTime = Datatype->startTime.ToUnixTimestamp(),
		.targetStandby = Datatype->targetStandby
	};

	return ConvertedType;
}

TSharedPtr<const FPFMultiplayerServerScheduledStandbySettings> ConvertScheduledStandbySettingsToUnreal(const PFMultiplayerServerScheduledStandbySettings* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFMultiplayerServerScheduledStandbySettings> ConvertedType = MakeShared<FPFMultiplayerServerScheduledStandbySettings>(FPFMultiplayerServerScheduledStandbySettings{
		.isEnabled = Datatype->isEnabled,
		.scheduleList = ConvertPlayfabArrayToUnreal<PFMultiplayerServerSchedule, FPFMultiplayerServerSchedule>(Datatype->scheduleList, Datatype->scheduleListCount, ConvertScheduleToUnreal),
		.scheduleListCount = Datatype->scheduleListCount
	});

	return ConvertedType;
}

const PFMultiplayerServerScheduledStandbySettings* ConvertScheduledStandbySettingsToPlayfab(TSharedPtr<const FPFMultiplayerServerScheduledStandbySettings> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFMultiplayerServerScheduledStandbySettings* ConvertedType = new PFMultiplayerServerScheduledStandbySettings{
		.isEnabled = Datatype->isEnabled,
		.scheduleList = ConvertUnrealArrayToPlayfab<PFMultiplayerServerSchedule, FPFMultiplayerServerSchedule>(Datatype->scheduleList, ConvertScheduleToPlayfab),
		.scheduleListCount = (uint32_t)Datatype->scheduleList.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFMultiplayerServerBuildRegion> ConvertBuildRegionToUnreal(const PFMultiplayerServerBuildRegion* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFMultiplayerServerBuildRegion> ConvertedType = MakeShared<FPFMultiplayerServerBuildRegion>(FPFMultiplayerServerBuildRegion{
		.currentServerStats = ConvertCurrentServerStatsToUnreal(Datatype->currentServerStats),
		.dynamicStandbySettings = ConvertDynamicStandbySettingsToUnreal(Datatype->dynamicStandbySettings),
		.isAssetReplicationComplete = Datatype->isAssetReplicationComplete,
		.maxServers = Datatype->maxServers,
		.multiplayerServerCountPerVm = TSharedPtr<const int32>(Datatype->multiplayerServerCountPerVm),
		.region = Datatype->region == nullptr ? FString() : FString(Datatype->region),
		.scheduledStandbySettings = ConvertScheduledStandbySettingsToUnreal(Datatype->scheduledStandbySettings),
		.standbyServers = Datatype->standbyServers,
		.status = Datatype->status == nullptr ? FString() : FString(Datatype->status),
		.vmSize = MakeShared<FPFMultiplayerServerAzureVmSize>(ConvertAzureVmSizeToUnreal(Datatype->vmSize))
	});

	return ConvertedType;
}

const PFMultiplayerServerBuildRegion* ConvertBuildRegionToPlayfab(TSharedPtr<const FPFMultiplayerServerBuildRegion> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFMultiplayerServerBuildRegion* ConvertedType = new PFMultiplayerServerBuildRegion{
		.currentServerStats = ConvertCurrentServerStatsToPlayfab(Datatype->currentServerStats),
		.dynamicStandbySettings = ConvertDynamicStandbySettingsToPlayfab(Datatype->dynamicStandbySettings),
		.isAssetReplicationComplete = Datatype->isAssetReplicationComplete,
		.maxServers = Datatype->maxServers,
		.multiplayerServerCountPerVm = Datatype->multiplayerServerCountPerVm ? new int32(*Datatype->multiplayerServerCountPerVm) : nullptr,
		.region = ConvertFStringToCharPtr(Datatype->region),
		.scheduledStandbySettings = ConvertScheduledStandbySettingsToPlayfab(Datatype->scheduledStandbySettings),
		.standbyServers = Datatype->standbyServers,
		.status = ConvertFStringToCharPtr(Datatype->status),
		.vmSize = new PFMultiplayerServerAzureVmSize(ConvertAzureVmSizeToPlayfab(Datatype->vmSize))
	};

	return ConvertedType;
}

TSharedPtr<const FPFMultiplayerServerBuildSummary> ConvertBuildSummaryToUnreal(const PFMultiplayerServerBuildSummary* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFMultiplayerServerBuildSummary> ConvertedType = MakeShared<FPFMultiplayerServerBuildSummary>(FPFMultiplayerServerBuildSummary{
		.buildId = Datatype->buildId == nullptr ? FString() : FString(Datatype->buildId),
		.buildName = Datatype->buildName == nullptr ? FString() : FString(Datatype->buildName),
		.creationTime = ConvertTimeToUnreal(Datatype->creationTime),
		.metadata = ConvertCharMapToUnreal(Datatype->metadata, Datatype->metadataCount),
		.metadataCount = Datatype->metadataCount,
		.regionConfigurations = ConvertPlayfabArrayToUnreal<PFMultiplayerServerBuildRegion, FPFMultiplayerServerBuildRegion>(Datatype->regionConfigurations, Datatype->regionConfigurationsCount, ConvertBuildRegionToUnreal),
		.regionConfigurationsCount = Datatype->regionConfigurationsCount
	});

	return ConvertedType;
}

const PFMultiplayerServerBuildSummary* ConvertBuildSummaryToPlayfab(TSharedPtr<const FPFMultiplayerServerBuildSummary> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFMultiplayerServerBuildSummary* ConvertedType = new PFMultiplayerServerBuildSummary{
		.buildId = ConvertFStringToCharPtr(Datatype->buildId),
		.buildName = ConvertFStringToCharPtr(Datatype->buildName),
		.creationTime = ConvertFDateTimeToPlayfab(Datatype->creationTime),
		.metadata = ConvertFStringMapToPlayfab(Datatype->metadata),
		.metadataCount = (uint32_t)Datatype->metadata.Num(),
		.regionConfigurations = ConvertUnrealArrayToPlayfab<PFMultiplayerServerBuildRegion, FPFMultiplayerServerBuildRegion>(Datatype->regionConfigurations, ConvertBuildRegionToPlayfab),
		.regionConfigurationsCount = (uint32_t)Datatype->regionConfigurations.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFMultiplayerServerListBuildSummariesResponse> ConvertListBuildSummariesResponseToUnreal(const PFMultiplayerServerListBuildSummariesResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFMultiplayerServerListBuildSummariesResponse> ConvertedType = MakeShared<FPFMultiplayerServerListBuildSummariesResponse>(FPFMultiplayerServerListBuildSummariesResponse{
		.buildSummaries = ConvertPlayfabArrayToUnreal<PFMultiplayerServerBuildSummary, FPFMultiplayerServerBuildSummary>(Datatype->buildSummaries, Datatype->buildSummariesCount, ConvertBuildSummaryToUnreal),
		.buildSummariesCount = Datatype->buildSummariesCount,
		.pageSize = Datatype->pageSize,
		.skipToken = Datatype->skipToken == nullptr ? FString() : FString(Datatype->skipToken)
	});

	return ConvertedType;
}

const PFMultiplayerServerListBuildSummariesResponse* ConvertListBuildSummariesResponseToPlayfab(TSharedPtr<const FPFMultiplayerServerListBuildSummariesResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFMultiplayerServerListBuildSummariesResponse* ConvertedType = new PFMultiplayerServerListBuildSummariesResponse{
		.buildSummaries = ConvertUnrealArrayToPlayfab<PFMultiplayerServerBuildSummary, FPFMultiplayerServerBuildSummary>(Datatype->buildSummaries, ConvertBuildSummaryToPlayfab),
		.buildSummariesCount = (uint32_t)Datatype->buildSummaries.Num(),
		.pageSize = Datatype->pageSize,
		.skipToken = ConvertFStringToCharPtr(Datatype->skipToken)
	};

	return ConvertedType;
}

TSharedPtr<const FPFMultiplayerServerListQosServersForTitleRequest> ConvertListQosServersForTitleRequestToUnreal(const PFMultiplayerServerListQosServersForTitleRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFMultiplayerServerListQosServersForTitleRequest> ConvertedType = MakeShared<FPFMultiplayerServerListQosServersForTitleRequest>(FPFMultiplayerServerListQosServersForTitleRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.includeAllRegions = TSharedPtr<const bool>(Datatype->includeAllRegions),
		.routingPreference = Datatype->routingPreference == nullptr ? FString() : FString(Datatype->routingPreference)
	});

	return ConvertedType;
}

const PFMultiplayerServerListQosServersForTitleRequest* ConvertListQosServersForTitleRequestToPlayfab(TSharedPtr<const FPFMultiplayerServerListQosServersForTitleRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFMultiplayerServerListQosServersForTitleRequest* ConvertedType = new PFMultiplayerServerListQosServersForTitleRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.includeAllRegions = Datatype->includeAllRegions ? new bool(*Datatype->includeAllRegions) : nullptr,
		.routingPreference = ConvertFStringToCharPtr(Datatype->routingPreference)
	};

	return ConvertedType;
}

TSharedPtr<const FPFMultiplayerServerQosServer> ConvertQosServerToUnreal(const PFMultiplayerServerQosServer* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFMultiplayerServerQosServer> ConvertedType = MakeShared<FPFMultiplayerServerQosServer>(FPFMultiplayerServerQosServer{
		.region = Datatype->region == nullptr ? FString() : FString(Datatype->region),
		.serverUrl = Datatype->serverUrl == nullptr ? FString() : FString(Datatype->serverUrl)
	});

	return ConvertedType;
}

const PFMultiplayerServerQosServer* ConvertQosServerToPlayfab(TSharedPtr<const FPFMultiplayerServerQosServer> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFMultiplayerServerQosServer* ConvertedType = new PFMultiplayerServerQosServer{
		.region = ConvertFStringToCharPtr(Datatype->region),
		.serverUrl = ConvertFStringToCharPtr(Datatype->serverUrl)
	};

	return ConvertedType;
}

TSharedPtr<const FPFMultiplayerServerListQosServersForTitleResponse> ConvertListQosServersForTitleResponseToUnreal(const PFMultiplayerServerListQosServersForTitleResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFMultiplayerServerListQosServersForTitleResponse> ConvertedType = MakeShared<FPFMultiplayerServerListQosServersForTitleResponse>(FPFMultiplayerServerListQosServersForTitleResponse{
		.pageSize = Datatype->pageSize,
		.qosServers = ConvertPlayfabArrayToUnreal<PFMultiplayerServerQosServer, FPFMultiplayerServerQosServer>(Datatype->qosServers, Datatype->qosServersCount, ConvertQosServerToUnreal),
		.qosServersCount = Datatype->qosServersCount,
		.skipToken = Datatype->skipToken == nullptr ? FString() : FString(Datatype->skipToken)
	});

	return ConvertedType;
}

const PFMultiplayerServerListQosServersForTitleResponse* ConvertListQosServersForTitleResponseToPlayfab(TSharedPtr<const FPFMultiplayerServerListQosServersForTitleResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFMultiplayerServerListQosServersForTitleResponse* ConvertedType = new PFMultiplayerServerListQosServersForTitleResponse{
		.pageSize = Datatype->pageSize,
		.qosServers = ConvertUnrealArrayToPlayfab<PFMultiplayerServerQosServer, FPFMultiplayerServerQosServer>(Datatype->qosServers, ConvertQosServerToPlayfab),
		.qosServersCount = (uint32_t)Datatype->qosServers.Num(),
		.skipToken = ConvertFStringToCharPtr(Datatype->skipToken)
	};

	return ConvertedType;
}

TSharedPtr<const FPFMultiplayerServerListSecretSummariesRequest> ConvertListSecretSummariesRequestToUnreal(const PFMultiplayerServerListSecretSummariesRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFMultiplayerServerListSecretSummariesRequest> ConvertedType = MakeShared<FPFMultiplayerServerListSecretSummariesRequest>(FPFMultiplayerServerListSecretSummariesRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.pageSize = TSharedPtr<const int32>(Datatype->pageSize),
		.skipToken = Datatype->skipToken == nullptr ? FString() : FString(Datatype->skipToken)
	});

	return ConvertedType;
}

const PFMultiplayerServerListSecretSummariesRequest* ConvertListSecretSummariesRequestToPlayfab(TSharedPtr<const FPFMultiplayerServerListSecretSummariesRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFMultiplayerServerListSecretSummariesRequest* ConvertedType = new PFMultiplayerServerListSecretSummariesRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.pageSize = Datatype->pageSize ? new int32(*Datatype->pageSize) : nullptr,
		.skipToken = ConvertFStringToCharPtr(Datatype->skipToken)
	};

	return ConvertedType;
}

TSharedPtr<const FPFMultiplayerServerSecretSummary> ConvertSecretSummaryToUnreal(const PFMultiplayerServerSecretSummary* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFMultiplayerServerSecretSummary> ConvertedType = MakeShared<FPFMultiplayerServerSecretSummary>(FPFMultiplayerServerSecretSummary{
		.expirationDate = ConvertTimeToUnreal(Datatype->expirationDate),
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name),
		.version = Datatype->version == nullptr ? FString() : FString(Datatype->version)
	});

	return ConvertedType;
}

const PFMultiplayerServerSecretSummary* ConvertSecretSummaryToPlayfab(TSharedPtr<const FPFMultiplayerServerSecretSummary> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFMultiplayerServerSecretSummary* ConvertedType = new PFMultiplayerServerSecretSummary{
		.expirationDate = ConvertFDateTimeToPlayfab(Datatype->expirationDate),
		.name = ConvertFStringToCharPtr(Datatype->name),
		.version = ConvertFStringToCharPtr(Datatype->version)
	};

	return ConvertedType;
}

TSharedPtr<const FPFMultiplayerServerListSecretSummariesResponse> ConvertListSecretSummariesResponseToUnreal(const PFMultiplayerServerListSecretSummariesResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFMultiplayerServerListSecretSummariesResponse> ConvertedType = MakeShared<FPFMultiplayerServerListSecretSummariesResponse>(FPFMultiplayerServerListSecretSummariesResponse{
		.pageSize = Datatype->pageSize,
		.secretSummaries = ConvertPlayfabArrayToUnreal<PFMultiplayerServerSecretSummary, FPFMultiplayerServerSecretSummary>(Datatype->secretSummaries, Datatype->secretSummariesCount, ConvertSecretSummaryToUnreal),
		.secretSummariesCount = Datatype->secretSummariesCount,
		.skipToken = Datatype->skipToken == nullptr ? FString() : FString(Datatype->skipToken)
	});

	return ConvertedType;
}

const PFMultiplayerServerListSecretSummariesResponse* ConvertListSecretSummariesResponseToPlayfab(TSharedPtr<const FPFMultiplayerServerListSecretSummariesResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFMultiplayerServerListSecretSummariesResponse* ConvertedType = new PFMultiplayerServerListSecretSummariesResponse{
		.pageSize = Datatype->pageSize,
		.secretSummaries = ConvertUnrealArrayToPlayfab<PFMultiplayerServerSecretSummary, FPFMultiplayerServerSecretSummary>(Datatype->secretSummaries, ConvertSecretSummaryToPlayfab),
		.secretSummariesCount = (uint32_t)Datatype->secretSummaries.Num(),
		.skipToken = ConvertFStringToCharPtr(Datatype->skipToken)
	};

	return ConvertedType;
}

TSharedPtr<const FPFMultiplayerServerBuildAliasParams> ConvertBuildAliasParamsToUnreal(const PFMultiplayerServerBuildAliasParams* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFMultiplayerServerBuildAliasParams> ConvertedType = MakeShared<FPFMultiplayerServerBuildAliasParams>(FPFMultiplayerServerBuildAliasParams{
		.aliasId = Datatype->aliasId == nullptr ? FString() : FString(Datatype->aliasId)
	});

	return ConvertedType;
}

const PFMultiplayerServerBuildAliasParams* ConvertBuildAliasParamsToPlayfab(TSharedPtr<const FPFMultiplayerServerBuildAliasParams> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFMultiplayerServerBuildAliasParams* ConvertedType = new PFMultiplayerServerBuildAliasParams{
		.aliasId = ConvertFStringToCharPtr(Datatype->aliasId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFMultiplayerServerRequestMultiplayerServerRequest> ConvertRequestMultiplayerServerRequestToUnreal(const PFMultiplayerServerRequestMultiplayerServerRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFMultiplayerServerRequestMultiplayerServerRequest> ConvertedType = MakeShared<FPFMultiplayerServerRequestMultiplayerServerRequest>(FPFMultiplayerServerRequestMultiplayerServerRequest{
		.buildAliasParams = ConvertBuildAliasParamsToUnreal(Datatype->buildAliasParams),
		.buildId = Datatype->buildId == nullptr ? FString() : FString(Datatype->buildId),
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.initialPlayers = ConvertCharArrayToUnreal(Datatype->initialPlayers, Datatype->initialPlayersCount),
		.initialPlayersCount = Datatype->initialPlayersCount,
		.preferredRegions = ConvertCharArrayToUnreal(Datatype->preferredRegions, Datatype->preferredRegionsCount),
		.preferredRegionsCount = Datatype->preferredRegionsCount,
		.sessionCookie = Datatype->sessionCookie == nullptr ? FString() : FString(Datatype->sessionCookie),
		.sessionId = Datatype->sessionId == nullptr ? FString() : FString(Datatype->sessionId)
	});

	return ConvertedType;
}

const PFMultiplayerServerRequestMultiplayerServerRequest* ConvertRequestMultiplayerServerRequestToPlayfab(TSharedPtr<const FPFMultiplayerServerRequestMultiplayerServerRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFMultiplayerServerRequestMultiplayerServerRequest* ConvertedType = new PFMultiplayerServerRequestMultiplayerServerRequest{
		.buildAliasParams = ConvertBuildAliasParamsToPlayfab(Datatype->buildAliasParams),
		.buildId = ConvertFStringToCharPtr(Datatype->buildId),
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.initialPlayers = ConvertFStringArrayToPlayfab(Datatype->initialPlayers),
		.initialPlayersCount = (uint32_t)Datatype->initialPlayers.Num(),
		.preferredRegions = ConvertFStringArrayToPlayfab(Datatype->preferredRegions),
		.preferredRegionsCount = (uint32_t)Datatype->preferredRegions.Num(),
		.sessionCookie = ConvertFStringToCharPtr(Datatype->sessionCookie),
		.sessionId = ConvertFStringToCharPtr(Datatype->sessionId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFMultiplayerServerConnectedPlayer> ConvertConnectedPlayerToUnreal(const PFMultiplayerServerConnectedPlayer* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFMultiplayerServerConnectedPlayer> ConvertedType = MakeShared<FPFMultiplayerServerConnectedPlayer>(FPFMultiplayerServerConnectedPlayer{
		.playerId = Datatype->playerId == nullptr ? FString() : FString(Datatype->playerId)
	});

	return ConvertedType;
}

const PFMultiplayerServerConnectedPlayer* ConvertConnectedPlayerToPlayfab(TSharedPtr<const FPFMultiplayerServerConnectedPlayer> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFMultiplayerServerConnectedPlayer* ConvertedType = new PFMultiplayerServerConnectedPlayer{
		.playerId = ConvertFStringToCharPtr(Datatype->playerId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFMultiplayerServerPort> ConvertPortToUnreal(const PFMultiplayerServerPort* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFMultiplayerServerPort> ConvertedType = MakeShared<FPFMultiplayerServerPort>(FPFMultiplayerServerPort{
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name),
		.num = Datatype->num,
		.protocol = ConvertProtocolTypeToUnreal(&Datatype->protocol)
	});

	return ConvertedType;
}

const PFMultiplayerServerPort* ConvertPortToPlayfab(TSharedPtr<const FPFMultiplayerServerPort> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFMultiplayerServerPort* ConvertedType = new PFMultiplayerServerPort{
		.name = ConvertFStringToCharPtr(Datatype->name),
		.num = Datatype->num,
		.protocol = ConvertProtocolTypeToPlayfab(MakeShared<FPFMultiplayerServerProtocolType>(Datatype->protocol))
	};

	return ConvertedType;
}

TSharedPtr<const FPFMultiplayerServerPublicIpAddress> ConvertPublicIpAddressToUnreal(const PFMultiplayerServerPublicIpAddress* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFMultiplayerServerPublicIpAddress> ConvertedType = MakeShared<FPFMultiplayerServerPublicIpAddress>(FPFMultiplayerServerPublicIpAddress{
		.fQDN = Datatype->fQDN == nullptr ? FString() : FString(Datatype->fQDN),
		.ipAddress = Datatype->ipAddress == nullptr ? FString() : FString(Datatype->ipAddress),
		.routingType = Datatype->routingType == nullptr ? FString() : FString(Datatype->routingType)
	});

	return ConvertedType;
}

const PFMultiplayerServerPublicIpAddress* ConvertPublicIpAddressToPlayfab(TSharedPtr<const FPFMultiplayerServerPublicIpAddress> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFMultiplayerServerPublicIpAddress* ConvertedType = new PFMultiplayerServerPublicIpAddress{
		.fQDN = ConvertFStringToCharPtr(Datatype->fQDN),
		.ipAddress = ConvertFStringToCharPtr(Datatype->ipAddress),
		.routingType = ConvertFStringToCharPtr(Datatype->routingType)
	};

	return ConvertedType;
}

TSharedPtr<const FPFMultiplayerServerRequestMultiplayerServerResponse> ConvertRequestMultiplayerServerResponseToUnreal(const PFMultiplayerServerRequestMultiplayerServerResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFMultiplayerServerRequestMultiplayerServerResponse> ConvertedType = MakeShared<FPFMultiplayerServerRequestMultiplayerServerResponse>(FPFMultiplayerServerRequestMultiplayerServerResponse{
		.buildId = Datatype->buildId == nullptr ? FString() : FString(Datatype->buildId),
		.connectedPlayers = ConvertPlayfabArrayToUnreal<PFMultiplayerServerConnectedPlayer, FPFMultiplayerServerConnectedPlayer>(Datatype->connectedPlayers, Datatype->connectedPlayersCount, ConvertConnectedPlayerToUnreal),
		.connectedPlayersCount = Datatype->connectedPlayersCount,
		.fQDN = Datatype->fQDN == nullptr ? FString() : FString(Datatype->fQDN),
		.iPV4Address = Datatype->iPV4Address == nullptr ? FString() : FString(Datatype->iPV4Address),
		.lastStateTransitionTime = ConvertTimeToUnreal(Datatype->lastStateTransitionTime),
		.ports = ConvertPlayfabArrayToUnreal<PFMultiplayerServerPort, FPFMultiplayerServerPort>(Datatype->ports, Datatype->portsCount, ConvertPortToUnreal),
		.portsCount = Datatype->portsCount,
		.publicIPV4Addresses = ConvertPlayfabArrayToUnreal<PFMultiplayerServerPublicIpAddress, FPFMultiplayerServerPublicIpAddress>(Datatype->publicIPV4Addresses, Datatype->publicIPV4AddressesCount, ConvertPublicIpAddressToUnreal),
		.publicIPV4AddressesCount = Datatype->publicIPV4AddressesCount,
		.region = Datatype->region == nullptr ? FString() : FString(Datatype->region),
		.serverId = Datatype->serverId == nullptr ? FString() : FString(Datatype->serverId),
		.sessionId = Datatype->sessionId == nullptr ? FString() : FString(Datatype->sessionId),
		.state = Datatype->state == nullptr ? FString() : FString(Datatype->state),
		.vmId = Datatype->vmId == nullptr ? FString() : FString(Datatype->vmId)
	});

	return ConvertedType;
}

const PFMultiplayerServerRequestMultiplayerServerResponse* ConvertRequestMultiplayerServerResponseToPlayfab(TSharedPtr<const FPFMultiplayerServerRequestMultiplayerServerResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFMultiplayerServerRequestMultiplayerServerResponse* ConvertedType = new PFMultiplayerServerRequestMultiplayerServerResponse{
		.buildId = ConvertFStringToCharPtr(Datatype->buildId),
		.connectedPlayers = ConvertUnrealArrayToPlayfab<PFMultiplayerServerConnectedPlayer, FPFMultiplayerServerConnectedPlayer>(Datatype->connectedPlayers, ConvertConnectedPlayerToPlayfab),
		.connectedPlayersCount = (uint32_t)Datatype->connectedPlayers.Num(),
		.fQDN = ConvertFStringToCharPtr(Datatype->fQDN),
		.iPV4Address = ConvertFStringToCharPtr(Datatype->iPV4Address),
		.lastStateTransitionTime = ConvertFDateTimeToPlayfab(Datatype->lastStateTransitionTime),
		.ports = ConvertUnrealArrayToPlayfab<PFMultiplayerServerPort, FPFMultiplayerServerPort>(Datatype->ports, ConvertPortToPlayfab),
		.portsCount = (uint32_t)Datatype->ports.Num(),
		.publicIPV4Addresses = ConvertUnrealArrayToPlayfab<PFMultiplayerServerPublicIpAddress, FPFMultiplayerServerPublicIpAddress>(Datatype->publicIPV4Addresses, ConvertPublicIpAddressToPlayfab),
		.publicIPV4AddressesCount = (uint32_t)Datatype->publicIPV4Addresses.Num(),
		.region = ConvertFStringToCharPtr(Datatype->region),
		.serverId = ConvertFStringToCharPtr(Datatype->serverId),
		.sessionId = ConvertFStringToCharPtr(Datatype->sessionId),
		.state = ConvertFStringToCharPtr(Datatype->state),
		.vmId = ConvertFStringToCharPtr(Datatype->vmId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFMultiplayerServerPartyInvitationConfiguration> ConvertPartyInvitationConfigurationToUnreal(const PFMultiplayerServerPartyInvitationConfiguration* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFMultiplayerServerPartyInvitationConfiguration> ConvertedType = MakeShared<FPFMultiplayerServerPartyInvitationConfiguration>(FPFMultiplayerServerPartyInvitationConfiguration{
		.entityKeys = ConvertPlayfabArrayToUnreal<PFEntityKey, FPFEntityKey>(Datatype->entityKeys, Datatype->entityKeysCount, ConvertEntityKeyToUnreal),
		.entityKeysCount = Datatype->entityKeysCount,
		.identifier = Datatype->identifier == nullptr ? FString() : FString(Datatype->identifier),
		.revocability = Datatype->revocability == nullptr ? FString() : FString(Datatype->revocability)
	});

	return ConvertedType;
}

const PFMultiplayerServerPartyInvitationConfiguration* ConvertPartyInvitationConfigurationToPlayfab(TSharedPtr<const FPFMultiplayerServerPartyInvitationConfiguration> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFMultiplayerServerPartyInvitationConfiguration* ConvertedType = new PFMultiplayerServerPartyInvitationConfiguration{
		.entityKeys = ConvertUnrealArrayToPlayfab<PFEntityKey, FPFEntityKey>(Datatype->entityKeys, ConvertEntityKeyToPlayfab),
		.entityKeysCount = (uint32_t)Datatype->entityKeys.Num(),
		.identifier = ConvertFStringToCharPtr(Datatype->identifier),
		.revocability = ConvertFStringToCharPtr(Datatype->revocability)
	};

	return ConvertedType;
}

TSharedPtr<const FPFMultiplayerServerPartyNetworkConfiguration> ConvertPartyNetworkConfigurationToUnreal(const PFMultiplayerServerPartyNetworkConfiguration* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFMultiplayerServerPartyNetworkConfiguration> ConvertedType = MakeShared<FPFMultiplayerServerPartyNetworkConfiguration>(FPFMultiplayerServerPartyNetworkConfiguration{
		.directPeerConnectivityOptions = Datatype->directPeerConnectivityOptions == nullptr ? FString() : FString(Datatype->directPeerConnectivityOptions),
		.maxDevices = Datatype->maxDevices,
		.maxDevicesPerUser = Datatype->maxDevicesPerUser,
		.maxEndpointsPerDevice = Datatype->maxEndpointsPerDevice,
		.maxUsers = Datatype->maxUsers,
		.maxUsersPerDevice = Datatype->maxUsersPerDevice,
		.partyInvitationConfiguration = ConvertPartyInvitationConfigurationToUnreal(Datatype->partyInvitationConfiguration)
	});

	return ConvertedType;
}

const PFMultiplayerServerPartyNetworkConfiguration* ConvertPartyNetworkConfigurationToPlayfab(TSharedPtr<const FPFMultiplayerServerPartyNetworkConfiguration> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFMultiplayerServerPartyNetworkConfiguration* ConvertedType = new PFMultiplayerServerPartyNetworkConfiguration{
		.directPeerConnectivityOptions = ConvertFStringToCharPtr(Datatype->directPeerConnectivityOptions),
		.maxDevices = Datatype->maxDevices,
		.maxDevicesPerUser = Datatype->maxDevicesPerUser,
		.maxEndpointsPerDevice = Datatype->maxEndpointsPerDevice,
		.maxUsers = Datatype->maxUsers,
		.maxUsersPerDevice = Datatype->maxUsersPerDevice,
		.partyInvitationConfiguration = ConvertPartyInvitationConfigurationToPlayfab(Datatype->partyInvitationConfiguration)
	};

	return ConvertedType;
}

TSharedPtr<const FPFMultiplayerServerRequestPartyServiceRequest> ConvertRequestPartyServiceRequestToUnreal(const PFMultiplayerServerRequestPartyServiceRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFMultiplayerServerRequestPartyServiceRequest> ConvertedType = MakeShared<FPFMultiplayerServerRequestPartyServiceRequest>(FPFMultiplayerServerRequestPartyServiceRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.networkConfiguration = ConvertPartyNetworkConfigurationToUnreal(Datatype->networkConfiguration),
		.partyId = Datatype->partyId == nullptr ? FString() : FString(Datatype->partyId),
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId),
		.preferredRegions = ConvertCharArrayToUnreal(Datatype->preferredRegions, Datatype->preferredRegionsCount),
		.preferredRegionsCount = Datatype->preferredRegionsCount
	});

	return ConvertedType;
}

const PFMultiplayerServerRequestPartyServiceRequest* ConvertRequestPartyServiceRequestToPlayfab(TSharedPtr<const FPFMultiplayerServerRequestPartyServiceRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFMultiplayerServerRequestPartyServiceRequest* ConvertedType = new PFMultiplayerServerRequestPartyServiceRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.networkConfiguration = ConvertPartyNetworkConfigurationToPlayfab(Datatype->networkConfiguration),
		.partyId = ConvertFStringToCharPtr(Datatype->partyId),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId),
		.preferredRegions = ConvertFStringArrayToPlayfab(Datatype->preferredRegions),
		.preferredRegionsCount = (uint32_t)Datatype->preferredRegions.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFMultiplayerServerRequestPartyServiceResponse> ConvertRequestPartyServiceResponseToUnreal(const PFMultiplayerServerRequestPartyServiceResponse* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFMultiplayerServerRequestPartyServiceResponse> ConvertedType = MakeShared<FPFMultiplayerServerRequestPartyServiceResponse>(FPFMultiplayerServerRequestPartyServiceResponse{
		.invitationId = Datatype->invitationId == nullptr ? FString() : FString(Datatype->invitationId),
		.partyId = Datatype->partyId == nullptr ? FString() : FString(Datatype->partyId),
		.serializedNetworkDescriptor = Datatype->serializedNetworkDescriptor == nullptr ? FString() : FString(Datatype->serializedNetworkDescriptor)
	});

	return ConvertedType;
}

const PFMultiplayerServerRequestPartyServiceResponse* ConvertRequestPartyServiceResponseToPlayfab(TSharedPtr<const FPFMultiplayerServerRequestPartyServiceResponse> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFMultiplayerServerRequestPartyServiceResponse* ConvertedType = new PFMultiplayerServerRequestPartyServiceResponse{
		.invitationId = ConvertFStringToCharPtr(Datatype->invitationId),
		.partyId = ConvertFStringToCharPtr(Datatype->partyId),
		.serializedNetworkDescriptor = ConvertFStringToCharPtr(Datatype->serializedNetworkDescriptor)
	};

	return ConvertedType;
}

TSharedPtr<const FPFMultiplayerServerSecret> ConvertSecretToUnreal(const PFMultiplayerServerSecret* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFMultiplayerServerSecret> ConvertedType = MakeShared<FPFMultiplayerServerSecret>(FPFMultiplayerServerSecret{
		.expirationDate = ConvertTimeToUnreal(Datatype->expirationDate),
		.name = Datatype->name == nullptr ? FString() : FString(Datatype->name),
		.value = Datatype->value == nullptr ? FString() : FString(Datatype->value)
	});

	return ConvertedType;
}

const PFMultiplayerServerSecret* ConvertSecretToPlayfab(TSharedPtr<const FPFMultiplayerServerSecret> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFMultiplayerServerSecret* ConvertedType = new PFMultiplayerServerSecret{
		.expirationDate = ConvertFDateTimeToPlayfab(Datatype->expirationDate),
		.name = ConvertFStringToCharPtr(Datatype->name),
		.value = ConvertFStringToCharPtr(Datatype->value)
	};

	return ConvertedType;
}

TSharedPtr<const FPFMultiplayerServerUploadSecretRequest> ConvertUploadSecretRequestToUnreal(const PFMultiplayerServerUploadSecretRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFMultiplayerServerUploadSecretRequest> ConvertedType = MakeShared<FPFMultiplayerServerUploadSecretRequest>(FPFMultiplayerServerUploadSecretRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.forceUpdate = TSharedPtr<const bool>(Datatype->forceUpdate),
		.gameSecret = ConvertSecretToUnreal(Datatype->gameSecret)
	});

	return ConvertedType;
}

const PFMultiplayerServerUploadSecretRequest* ConvertUploadSecretRequestToPlayfab(TSharedPtr<const FPFMultiplayerServerUploadSecretRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFMultiplayerServerUploadSecretRequest* ConvertedType = new PFMultiplayerServerUploadSecretRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.forceUpdate = Datatype->forceUpdate ? new bool(*Datatype->forceUpdate) : nullptr,
		.gameSecret = ConvertSecretToPlayfab(Datatype->gameSecret)
	};

	return ConvertedType;
}
