//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "OnlineKeyValuePair.h"

// Deterministic, config-aware allocator that maps session setting names to PlayFab
// lobby search keys ("string_keyN" / "number_keyN").
//
// Cross-client correctness: the mapping must be identical on every client and game
// version so that search filtering (write) and search-result decoding (read) round
// trip. Allocation is therefore a pure function of shared inputs, in priority order:
//   1. Fixed platform keys (string_key1-4) - reserved, never handed out.
//   2. Ini config [OnlineSubsystemPlayFab] - authoritative overrides.
//   3. Built-in default assignments - guarantee back-compat when no ini is present.
//   4. Deterministic freed-pool fill - stable (name-sorted) assignment of remaining
//      slots for settings not covered above.
class FDynamicSearchKeyAllocator
{
public:
	struct FSettingKeyType
	{
		FString SettingName;
		EOnlineKeyValuePairDataType::Type Type = EOnlineKeyValuePairDataType::Empty;
	};

	// A built-in default assignment (setting -> key number, within its type space).
	struct FDefaultAssignment
	{
		FName SettingKey;
		int32 KeyNumber = 0;
		EOnlineKeyValuePairDataType::Type Type = EOnlineKeyValuePairDataType::Empty;
	};

	FDynamicSearchKeyAllocator() = default;

	// Builds the bidirectional mapping from the provided built-in defaults plus any
	// ini overrides. Safe to call more than once (rebuilds from scratch).
	void Initialize(const FDefaultAssignment* Defaults, int32 DefaultsCount);

	// Write path: resolve a setting name to its raw search key + type.
	bool GetKeyForSetting(const FString& SettingName, FString& OutSearchKey, EOnlineKeyValuePairDataType::Type& OutType) const;

	// Read path: resolve a raw search key back to its setting name + type.
	const FSettingKeyType* FindSetting(const FString& SearchKey) const;

private:
	// A parsed ini override: the developer's original-cased setting name plus its target
	// key number and type. The override map is keyed by the lower-cased name so entries
	// de-duplicate case-insensitively (and match the normalized lookups used elsewhere),
	// while the original casing is retained here for the read/decode path.
	struct FConfigOverride
	{
		FString SettingName;
		int32 KeyNumber = 0;
		EOnlineKeyValuePairDataType::Type Type = EOnlineKeyValuePairDataType::Empty;
	};

	FString MakeKeyName(EOnlineKeyValuePairDataType::Type Type, int32 KeyNumber) const;
	bool IsNumberType(EOnlineKeyValuePairDataType::Type Type) const;
	void Assign(const FString& SettingName, EOnlineKeyValuePairDataType::Type Type, int32 KeyNumber);
	bool TryReserveKey(EOnlineKeyValuePairDataType::Type Type, int32 KeyNumber);
	int32 AllocateNextFreeKey(EOnlineKeyValuePairDataType::Type Type);
	void LoadIniOverrides(TMap<FString, FConfigOverride>& OutOverrides) const;

	// Highest key number the backend accepts for each space (configurable so that a
	// future backend key-range expansion can be adopted without code changes).
	int32 MaxStringKeyRange = 30;
	int32 MaxNumberKeyRange = 30;

	// string_key1-4 are reserved for platform data and never dynamically allocated.
	static constexpr int32 ReservedStringKeyCount = 4;

	TMap<FString, FString> SettingToSearchKey;      // setting name  -> raw key
	TMap<FString, FSettingKeyType> KeyToSetting;    // raw key       -> {setting, type}

	TBitArray<> UsedStringKeys;
	TBitArray<> UsedNumberKeys;
};
