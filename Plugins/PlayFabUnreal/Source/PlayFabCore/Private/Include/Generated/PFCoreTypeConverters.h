// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once
#include "Generated/PFCoreUnrealTypes.h"
#include <playfab/core/PFCore.h>

#pragma push_macro("IN")
#undef IN

PLAYFABCORE_API const FPFTitleActivationStatus ConvertTitleActivationStatusToUnreal(const PFTitleActivationStatus* enumVal);
PLAYFABCORE_API const PFTitleActivationStatus ConvertTitleActivationStatusToPlayfab(TSharedPtr<const FPFTitleActivationStatus> enumVal);
PLAYFABCORE_API const FPFCurrency ConvertCurrencyToUnreal(const PFCurrency* enumVal);
PLAYFABCORE_API const PFCurrency ConvertCurrencyToPlayfab(TSharedPtr<const FPFCurrency> enumVal);
PLAYFABCORE_API const FPFUserOrigination ConvertUserOriginationToUnreal(const PFUserOrigination* enumVal);
PLAYFABCORE_API const PFUserOrigination ConvertUserOriginationToPlayfab(TSharedPtr<const FPFUserOrigination> enumVal);
PLAYFABCORE_API const FPFUserDataPermission ConvertUserDataPermissionToUnreal(const PFUserDataPermission* enumVal);
PLAYFABCORE_API const PFUserDataPermission ConvertUserDataPermissionToPlayfab(TSharedPtr<const FPFUserDataPermission> enumVal);
PLAYFABCORE_API const FPFEmailVerificationStatus ConvertEmailVerificationStatusToUnreal(const PFEmailVerificationStatus* enumVal);
PLAYFABCORE_API const PFEmailVerificationStatus ConvertEmailVerificationStatusToPlayfab(TSharedPtr<const FPFEmailVerificationStatus> enumVal);
PLAYFABCORE_API const FPFLoginIdentityProvider ConvertLoginIdentityProviderToUnreal(const PFLoginIdentityProvider* enumVal);
PLAYFABCORE_API const PFLoginIdentityProvider ConvertLoginIdentityProviderToPlayfab(TSharedPtr<const FPFLoginIdentityProvider> enumVal);
PLAYFABCORE_API const FPFContinentCode ConvertContinentCodeToUnreal(const PFContinentCode* enumVal);
PLAYFABCORE_API const PFContinentCode ConvertContinentCodeToPlayfab(TSharedPtr<const FPFContinentCode> enumVal);
PLAYFABCORE_API const FPFCountryCode ConvertCountryCodeToUnreal(const PFCountryCode* enumVal);
PLAYFABCORE_API const PFCountryCode ConvertCountryCodeToPlayfab(TSharedPtr<const FPFCountryCode> enumVal);
PLAYFABCORE_API const FPFSubscriptionProviderStatus ConvertSubscriptionProviderStatusToUnreal(const PFSubscriptionProviderStatus* enumVal);
PLAYFABCORE_API const PFSubscriptionProviderStatus ConvertSubscriptionProviderStatusToPlayfab(TSharedPtr<const FPFSubscriptionProviderStatus> enumVal);
PLAYFABCORE_API const FPFPushNotificationPlatform ConvertPushNotificationPlatformToUnreal(const PFPushNotificationPlatform* enumVal);
PLAYFABCORE_API const PFPushNotificationPlatform ConvertPushNotificationPlatformToPlayfab(TSharedPtr<const FPFPushNotificationPlatform> enumVal);
PLAYFABCORE_API TSharedPtr<const FPFItemInstance> ConvertItemInstanceToUnreal(const PFItemInstance* Datatype);
PLAYFABCORE_API const PFItemInstance* ConvertItemInstanceToPlayfab(TSharedPtr<const FPFItemInstance> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFUserAndroidDeviceInfo> ConvertUserAndroidDeviceInfoToUnreal(const PFUserAndroidDeviceInfo* Datatype);
PLAYFABCORE_API const PFUserAndroidDeviceInfo* ConvertUserAndroidDeviceInfoToPlayfab(TSharedPtr<const FPFUserAndroidDeviceInfo> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFUserAppleIdInfo> ConvertUserAppleIdInfoToUnreal(const PFUserAppleIdInfo* Datatype);
PLAYFABCORE_API const PFUserAppleIdInfo* ConvertUserAppleIdInfoToPlayfab(TSharedPtr<const FPFUserAppleIdInfo> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFUserBattleNetInfo> ConvertUserBattleNetInfoToUnreal(const PFUserBattleNetInfo* Datatype);
PLAYFABCORE_API const PFUserBattleNetInfo* ConvertUserBattleNetInfoToPlayfab(TSharedPtr<const FPFUserBattleNetInfo> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFUserCustomIdInfo> ConvertUserCustomIdInfoToUnreal(const PFUserCustomIdInfo* Datatype);
PLAYFABCORE_API const PFUserCustomIdInfo* ConvertUserCustomIdInfoToPlayfab(TSharedPtr<const FPFUserCustomIdInfo> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFUserFacebookInfo> ConvertUserFacebookInfoToUnreal(const PFUserFacebookInfo* Datatype);
PLAYFABCORE_API const PFUserFacebookInfo* ConvertUserFacebookInfoToPlayfab(TSharedPtr<const FPFUserFacebookInfo> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFUserFacebookInstantGamesIdInfo> ConvertUserFacebookInstantGamesIdInfoToUnreal(const PFUserFacebookInstantGamesIdInfo* Datatype);
PLAYFABCORE_API const PFUserFacebookInstantGamesIdInfo* ConvertUserFacebookInstantGamesIdInfoToPlayfab(TSharedPtr<const FPFUserFacebookInstantGamesIdInfo> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFUserGameCenterInfo> ConvertUserGameCenterInfoToUnreal(const PFUserGameCenterInfo* Datatype);
PLAYFABCORE_API const PFUserGameCenterInfo* ConvertUserGameCenterInfoToPlayfab(TSharedPtr<const FPFUserGameCenterInfo> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFUserGoogleInfo> ConvertUserGoogleInfoToUnreal(const PFUserGoogleInfo* Datatype);
PLAYFABCORE_API const PFUserGoogleInfo* ConvertUserGoogleInfoToPlayfab(TSharedPtr<const FPFUserGoogleInfo> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFUserGooglePlayGamesInfo> ConvertUserGooglePlayGamesInfoToUnreal(const PFUserGooglePlayGamesInfo* Datatype);
PLAYFABCORE_API const PFUserGooglePlayGamesInfo* ConvertUserGooglePlayGamesInfoToPlayfab(TSharedPtr<const FPFUserGooglePlayGamesInfo> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFUserIosDeviceInfo> ConvertUserIosDeviceInfoToUnreal(const PFUserIosDeviceInfo* Datatype);
PLAYFABCORE_API const PFUserIosDeviceInfo* ConvertUserIosDeviceInfoToPlayfab(TSharedPtr<const FPFUserIosDeviceInfo> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFUserKongregateInfo> ConvertUserKongregateInfoToUnreal(const PFUserKongregateInfo* Datatype);
PLAYFABCORE_API const PFUserKongregateInfo* ConvertUserKongregateInfoToPlayfab(TSharedPtr<const FPFUserKongregateInfo> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFUserNintendoSwitchAccountIdInfo> ConvertUserNintendoSwitchAccountIdInfoToUnreal(const PFUserNintendoSwitchAccountIdInfo* Datatype);
PLAYFABCORE_API const PFUserNintendoSwitchAccountIdInfo* ConvertUserNintendoSwitchAccountIdInfoToPlayfab(TSharedPtr<const FPFUserNintendoSwitchAccountIdInfo> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFUserNintendoSwitchDeviceIdInfo> ConvertUserNintendoSwitchDeviceIdInfoToUnreal(const PFUserNintendoSwitchDeviceIdInfo* Datatype);
PLAYFABCORE_API const PFUserNintendoSwitchDeviceIdInfo* ConvertUserNintendoSwitchDeviceIdInfoToPlayfab(TSharedPtr<const FPFUserNintendoSwitchDeviceIdInfo> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFUserOpenIdInfo> ConvertUserOpenIdInfoToUnreal(const PFUserOpenIdInfo* Datatype);
PLAYFABCORE_API const PFUserOpenIdInfo* ConvertUserOpenIdInfoToPlayfab(TSharedPtr<const FPFUserOpenIdInfo> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFUserPrivateAccountInfo> ConvertUserPrivateAccountInfoToUnreal(const PFUserPrivateAccountInfo* Datatype);
PLAYFABCORE_API const PFUserPrivateAccountInfo* ConvertUserPrivateAccountInfoToPlayfab(TSharedPtr<const FPFUserPrivateAccountInfo> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFUserPsnInfo> ConvertUserPsnInfoToUnreal(const PFUserPsnInfo* Datatype);
PLAYFABCORE_API const PFUserPsnInfo* ConvertUserPsnInfoToPlayfab(TSharedPtr<const FPFUserPsnInfo> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFUserServerCustomIdInfo> ConvertUserServerCustomIdInfoToUnreal(const PFUserServerCustomIdInfo* Datatype);
PLAYFABCORE_API const PFUserServerCustomIdInfo* ConvertUserServerCustomIdInfoToPlayfab(TSharedPtr<const FPFUserServerCustomIdInfo> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFUserSteamInfo> ConvertUserSteamInfoToUnreal(const PFUserSteamInfo* Datatype);
PLAYFABCORE_API const PFUserSteamInfo* ConvertUserSteamInfoToPlayfab(TSharedPtr<const FPFUserSteamInfo> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFUserTitleInfo> ConvertUserTitleInfoToUnreal(const PFUserTitleInfo* Datatype);
PLAYFABCORE_API const PFUserTitleInfo* ConvertUserTitleInfoToPlayfab(TSharedPtr<const FPFUserTitleInfo> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFUserTwitchInfo> ConvertUserTwitchInfoToUnreal(const PFUserTwitchInfo* Datatype);
PLAYFABCORE_API const PFUserTwitchInfo* ConvertUserTwitchInfoToPlayfab(TSharedPtr<const FPFUserTwitchInfo> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFUserXboxInfo> ConvertUserXboxInfoToUnreal(const PFUserXboxInfo* Datatype);
PLAYFABCORE_API const PFUserXboxInfo* ConvertUserXboxInfoToPlayfab(TSharedPtr<const FPFUserXboxInfo> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFUserAccountInfo> ConvertUserAccountInfoToUnreal(const PFUserAccountInfo* Datatype);
PLAYFABCORE_API const PFUserAccountInfo* ConvertUserAccountInfoToPlayfab(TSharedPtr<const FPFUserAccountInfo> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFCharacterResult> ConvertCharacterResultToUnreal(const PFCharacterResult* Datatype);
PLAYFABCORE_API const PFCharacterResult* ConvertCharacterResultToPlayfab(TSharedPtr<const FPFCharacterResult> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFUserDataRecord> ConvertUserDataRecordToUnreal(const PFUserDataRecord* Datatype);
PLAYFABCORE_API const PFUserDataRecord* ConvertUserDataRecordToPlayfab(TSharedPtr<const FPFUserDataRecord> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFVirtualCurrencyRechargeTime> ConvertVirtualCurrencyRechargeTimeToUnreal(const PFVirtualCurrencyRechargeTime* Datatype);
PLAYFABCORE_API const PFVirtualCurrencyRechargeTime* ConvertVirtualCurrencyRechargeTimeToPlayfab(TSharedPtr<const FPFVirtualCurrencyRechargeTime> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFPlayerProfileViewConstraints> ConvertPlayerProfileViewConstraintsToUnreal(const PFPlayerProfileViewConstraints* Datatype);
PLAYFABCORE_API const PFPlayerProfileViewConstraints* ConvertPlayerProfileViewConstraintsToPlayfab(TSharedPtr<const FPFPlayerProfileViewConstraints> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFAdCampaignAttributionModel> ConvertAdCampaignAttributionModelToUnreal(const PFAdCampaignAttributionModel* Datatype);
PLAYFABCORE_API const PFAdCampaignAttributionModel* ConvertAdCampaignAttributionModelToPlayfab(TSharedPtr<const FPFAdCampaignAttributionModel> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFContactEmailInfoModel> ConvertContactEmailInfoModelToUnreal(const PFContactEmailInfoModel* Datatype);
PLAYFABCORE_API const PFContactEmailInfoModel* ConvertContactEmailInfoModelToPlayfab(TSharedPtr<const FPFContactEmailInfoModel> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFLinkedPlatformAccountModel> ConvertLinkedPlatformAccountModelToUnreal(const PFLinkedPlatformAccountModel* Datatype);
PLAYFABCORE_API const PFLinkedPlatformAccountModel* ConvertLinkedPlatformAccountModelToPlayfab(TSharedPtr<const FPFLinkedPlatformAccountModel> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFLocationModel> ConvertLocationModelToUnreal(const PFLocationModel* Datatype);
PLAYFABCORE_API const PFLocationModel* ConvertLocationModelToPlayfab(TSharedPtr<const FPFLocationModel> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFSubscriptionModel> ConvertSubscriptionModelToUnreal(const PFSubscriptionModel* Datatype);
PLAYFABCORE_API const PFSubscriptionModel* ConvertSubscriptionModelToPlayfab(TSharedPtr<const FPFSubscriptionModel> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFMembershipModel> ConvertMembershipModelToUnreal(const PFMembershipModel* Datatype);
PLAYFABCORE_API const PFMembershipModel* ConvertMembershipModelToPlayfab(TSharedPtr<const FPFMembershipModel> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFPushNotificationRegistrationModel> ConvertPushNotificationRegistrationModelToUnreal(const PFPushNotificationRegistrationModel* Datatype);
PLAYFABCORE_API const PFPushNotificationRegistrationModel* ConvertPushNotificationRegistrationModelToPlayfab(TSharedPtr<const FPFPushNotificationRegistrationModel> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFStatisticModel> ConvertStatisticModelToUnreal(const PFStatisticModel* Datatype);
PLAYFABCORE_API const PFStatisticModel* ConvertStatisticModelToPlayfab(TSharedPtr<const FPFStatisticModel> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFTagModel> ConvertTagModelToUnreal(const PFTagModel* Datatype);
PLAYFABCORE_API const PFTagModel* ConvertTagModelToPlayfab(TSharedPtr<const FPFTagModel> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFValueToDateModel> ConvertValueToDateModelToUnreal(const PFValueToDateModel* Datatype);
PLAYFABCORE_API const PFValueToDateModel* ConvertValueToDateModelToPlayfab(TSharedPtr<const FPFValueToDateModel> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFPlayerProfileModel> ConvertPlayerProfileModelToUnreal(const PFPlayerProfileModel* Datatype);
PLAYFABCORE_API const PFPlayerProfileModel* ConvertPlayerProfileModelToPlayfab(TSharedPtr<const FPFPlayerProfileModel> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFGetPlayerCombinedInfoRequestParams> ConvertGetPlayerCombinedInfoRequestParamsToUnreal(const PFGetPlayerCombinedInfoRequestParams* Datatype);
PLAYFABCORE_API const PFGetPlayerCombinedInfoRequestParams* ConvertGetPlayerCombinedInfoRequestParamsToPlayfab(TSharedPtr<const FPFGetPlayerCombinedInfoRequestParams> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFCharacterInventory> ConvertCharacterInventoryToUnreal(const PFCharacterInventory* Datatype);
PLAYFABCORE_API const PFCharacterInventory* ConvertCharacterInventoryToPlayfab(TSharedPtr<const FPFCharacterInventory> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFStatisticValue> ConvertStatisticValueToUnreal(const PFStatisticValue* Datatype);
PLAYFABCORE_API const PFStatisticValue* ConvertStatisticValueToPlayfab(TSharedPtr<const FPFStatisticValue> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFGetPlayerCombinedInfoResultPayload> ConvertGetPlayerCombinedInfoResultPayloadToUnreal(const PFGetPlayerCombinedInfoResultPayload* Datatype);
PLAYFABCORE_API const PFGetPlayerCombinedInfoResultPayload* ConvertGetPlayerCombinedInfoResultPayloadToPlayfab(TSharedPtr<const FPFGetPlayerCombinedInfoResultPayload> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFVariable> ConvertVariableToUnreal(const PFVariable* Datatype);
PLAYFABCORE_API const PFVariable* ConvertVariableToPlayfab(TSharedPtr<const FPFVariable> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFTreatmentAssignment> ConvertTreatmentAssignmentToUnreal(const PFTreatmentAssignment* Datatype);
PLAYFABCORE_API const PFTreatmentAssignment* ConvertTreatmentAssignmentToPlayfab(TSharedPtr<const FPFTreatmentAssignment> Datatype);

PLAYFABCORE_API TSharedPtr<const FPFEntityLineage> ConvertEntityLineageToUnreal(const PFEntityLineage* Datatype);
PLAYFABCORE_API const PFEntityLineage* ConvertEntityLineageToPlayfab(TSharedPtr<const FPFEntityLineage> Datatype);

// Array converters for classes
template <typename T, typename U>
TArray<TSharedPtr<const U>> ConvertPlayfabArrayToUnreal(const T* const* Array, int32 ArraySize, TSharedPtr<const U> (*ConvertFunc)(const T*))
{
	TArray<TSharedPtr<const U>> ConvertedArray;
	ConvertedArray.Reserve(ArraySize);

	if (Array == nullptr)
	{
		return ConvertedArray;
	}

	for (int32 i = 0; i < ArraySize; ++i)
	{
		TSharedPtr<const U> ConvertedItem = ConvertFunc(Array[i]);
		ConvertedArray.Add(ConvertedItem);
	}
	return ConvertedArray;
}

template <typename T, typename U>
const T* const* ConvertUnrealArrayToPlayfab(TArray<TSharedPtr<const U>> Array, const T* (*ConvertFunc)(TSharedPtr<const U>))
{
	TArray<const T*> ConvertedArray;
	ConvertedArray.Reserve(Array.Num());

	if (Array.Num() == 0)
	{
		return nullptr;
	}

	for (int32 i = 0; i < Array.Num(); ++i)
	{
		const T* ConvertedItem = ConvertFunc(Array[i]);
		ConvertedArray.Add(ConvertedItem);
	}
	return ConvertedArray.GetData();
}

// Array converters for enums
template <typename T, typename U>
const TArray<U> ConvertPlayfabEnumArrayToUnreal(T const* Array, int32 ArraySize, const U (*ConvertFunc)(const T*))
{
	TArray<U> ConvertedArray;
	ConvertedArray.Reserve(ArraySize);

	if (Array == nullptr)
	{
		return ConvertedArray;
	}

	for (int32 i = 0; i < ArraySize; ++i)
	{
		const U ConvertedItem = ConvertFunc(&Array[i]);
		ConvertedArray.Add(ConvertedItem);
	}
	return ConvertedArray;
}

template <typename T, typename U>
T const* ConvertUnrealEnumArrayToPlayfab(const TArray<U> Array, const T (*ConvertFunc)(TSharedPtr<const U>))
{
	TArray<T> ConvertedArray;
	ConvertedArray.Reserve(Array.Num());

	if (Array.Num() == 0)
	{
		return nullptr;
	}

	for (int32 i = 0; i < Array.Num(); ++i)
	{
		const T ConvertedItem = ConvertFunc(MakeShared<U>(Array[i]));
		ConvertedArray.Add(ConvertedItem);
	}
	return ConvertedArray.GetData();
}

PLAYFABCORE_API TArray<FString> ConvertCharArrayToUnreal(const char* const* Array, int32 ArraySize);
PLAYFABCORE_API const char* const* ConvertFStringArrayToPlayfab(const TArray<FString> Array);

PLAYFABCORE_API TArray<FDateTime> ConvertTimeArrayToUnreal(const time_t* const* Array, int32 ArraySize);
PLAYFABCORE_API const time_t* const* ConvertFDateTimeArrayToPlayfab(TArray<FDateTime> Array);

// Map converter for classes
template <typename T, typename U, typename V> // DictionaryEntry, UnrealType, PlayFabType
TMap<const FString, TSharedPtr<const U>> ConvertPlayfabMapToUnreal(const T* Map, int32 MapSize, TSharedPtr<const U> (*ConvertFunc)(const V*))
{
	TMap<const FString, TSharedPtr<const U>> ConvertedMap;

	if (Map == nullptr)
	{
		return ConvertedMap;
	}

	for (int32 i = 0; i < MapSize; ++i)
	{
		TSharedPtr<const U> ConvertedValue = ConvertFunc(Map[i].value);
		ConvertedMap.Add(FString(Map[i].key), ConvertedValue);
	}
	return ConvertedMap;
}

template <typename T, typename U, typename V> // DictionaryEntry, UnrealType, PlayFabType
const T* ConvertUnrealMapToPlayfab(TMap<const FString, TSharedPtr<const U>> Map, const V* (*ConvertFunc)(TSharedPtr<const U>))
{
	TArray<T> ConvertedMap;
	ConvertedMap.Reserve(Map.Num());

	if (Map.Num() == 0)
	{
		return nullptr;
	}

	for (auto Pair = Map.CreateConstIterator(); Pair; ++Pair)
	{
		FTCHARToUTF8 Converted(*Pair.Key());
        char* ConvertedString = new char[Converted.Length() + 1];
        FMemory::Memcpy(ConvertedString, Converted.Get(), Converted.Length());
        ConvertedString[Converted.Length()] = '\0';

		T ConvertedItem{
			.key = ConvertedString,
			.value = ConvertFunc(Pair.Value())
		};
		ConvertedMap.Add(ConvertedItem);
	}
	return ConvertedMap.GetData();
}

PLAYFABCORE_API const char* ConvertFStringToCharPtr(const FString UnrealString);

PLAYFABCORE_API TMap<const FString, uint32> ConvertUintMapToUnreal(const PFUint32DictionaryEntry* Map, int32 MapSize);
PLAYFABCORE_API const PFUint32DictionaryEntry* ConvertUintMapToPlayfab(TMap<const FString, uint32> Map);

PLAYFABCORE_API TMap<const FString, int32> ConvertIntMapToUnreal(const PFInt32DictionaryEntry* Map, int32 MapSize);
PLAYFABCORE_API const PFInt32DictionaryEntry* ConvertIntMapToPlayfab(TMap<const FString, int32> Map);

PLAYFABCORE_API TMap<const FString, const FString> ConvertCharMapToUnreal(const PFStringDictionaryEntry* Map, int32 MapSize);
PLAYFABCORE_API const PFStringDictionaryEntry* ConvertFStringMapToPlayfab(TMap<const FString, const FString> Map);

PLAYFABCORE_API TMap<const FString, const FDateTime> ConvertTimeMapToUnreal(const PFDateTimeDictionaryEntry* Map, int32 MapSize);
PLAYFABCORE_API const PFDateTimeDictionaryEntry* ConvertFDateTimeMapToPlayfab(TMap<const FString, const FDateTime> Map);

// for optional time_t
PLAYFABCORE_API const time_t* ConvertFDateTimeToPlayfab(TSharedPtr<const FDateTime> Time);
PLAYFABCORE_API TSharedPtr<const FDateTime> ConvertTimeToUnreal(const time_t* Time);

PLAYFABCORE_API TSharedPtr<const FPFEntityKey> ConvertEntityKeyToUnreal(const PFEntityKey* Datatype);
PLAYFABCORE_API const PFEntityKey* ConvertEntityKeyToPlayfab(TSharedPtr<const FPFEntityKey> Datatype);

#pragma pop_macro("IN")