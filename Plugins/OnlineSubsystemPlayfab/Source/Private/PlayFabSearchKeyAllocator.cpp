//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "PlayFabSearchKeyAllocator.h"
#include "OnlineSubsystemPlayFabPrivate.h"
#include "OnlineSubsystem.h"
#include "Misc/ConfigCacheIni.h"

namespace
{
	const TCHAR* SearchKeyConfigSection = TEXT("OnlineSubsystemPlayFab");
}

bool FDynamicSearchKeyAllocator::IsNumberType(EOnlineKeyValuePairDataType::Type Type) const
{
	// Int32 and Bool both live in the "number_key" space (bools are stored as 0/1).
	return Type != EOnlineKeyValuePairDataType::String;
}

FString FDynamicSearchKeyAllocator::MakeKeyName(EOnlineKeyValuePairDataType::Type Type, int32 KeyNumber) const
{
	const FString& Prefix = IsNumberType(Type) ? SEARCH_KEY_PREFIX_NUMBER : SEARCH_KEY_PREFIX_STRING;
	return FString::Printf(TEXT("%skey%d"), *Prefix, KeyNumber);
}

bool FDynamicSearchKeyAllocator::TryReserveKey(EOnlineKeyValuePairDataType::Type Type, int32 KeyNumber)
{
	TBitArray<>& Used = IsNumberType(Type) ? UsedNumberKeys : UsedStringKeys;
	const int32 MaxRange = IsNumberType(Type) ? MaxNumberKeyRange : MaxStringKeyRange;
	if (KeyNumber < 1 || KeyNumber > MaxRange)
	{
		return false;
	}
	const int32 Index = KeyNumber - 1;
	if (Used[Index])
	{
		return false;
	}
	Used[Index] = true;
	return true;
}

int32 FDynamicSearchKeyAllocator::AllocateNextFreeKey(EOnlineKeyValuePairDataType::Type Type)
{
	TBitArray<>& Used = IsNumberType(Type) ? UsedNumberKeys : UsedStringKeys;
	const int32 MaxRange = IsNumberType(Type) ? MaxNumberKeyRange : MaxStringKeyRange;
	// string_key1-4 are reserved for platform data; skip them in the string space.
	const int32 StartKey = IsNumberType(Type) ? 1 : (ReservedStringKeyCount + 1);
	for (int32 KeyNumber = StartKey; KeyNumber <= MaxRange; ++KeyNumber)
	{
		if (!Used[KeyNumber - 1])
		{
			Used[KeyNumber - 1] = true;
			return KeyNumber;
		}
	}
	return INDEX_NONE;
}

void FDynamicSearchKeyAllocator::Assign(const FString& SettingName, EOnlineKeyValuePairDataType::Type Type, int32 KeyNumber)
{
	const FString SearchKey = MakeKeyName(Type, KeyNumber);
	// Key the setting->key map on a normalized (lower-case) name so lookups and the
	// default-suppression check are consistently case-insensitive. The original-cased
	// name is preserved in KeyToSetting for the read/decode path.
	SettingToSearchKey.Add(SettingName.ToLower(), SearchKey);
	KeyToSetting.Add(SearchKey, FSettingKeyType{ SettingName, Type });
}

void FDynamicSearchKeyAllocator::LoadIniOverrides(TMap<FString, FConfigOverride>& OutOverrides) const
{
	if (GConfig == nullptr)
	{
		return;
	}

	auto ParseEntries = [&OutOverrides, this](const TArray<FString>& Entries, EOnlineKeyValuePairDataType::Type Type)
	{
		for (const FString& Entry : Entries)
		{
			// Format: "SETTINGNAME:KeyNumber" (e.g. "GAMEMODE:29").
			FString SettingName;
			FString KeyNumberString;
			if (!Entry.Split(TEXT(":"), &SettingName, &KeyNumberString))
			{
				// Malformed syntax is a developer config typo (no cross-version fallback path),
				// so surface it loudly: Error-level log for shipping visibility plus an ensure to
				// trip in dev builds. The entry is still skipped so init proceeds.
				UE_LOG_ONLINE(Error, TEXT("SearchKeyAllocator: malformed config entry '%s' (expected SETTING:number); ignoring"), *Entry);
				ensureMsgf(false, TEXT("SearchKeyAllocator: malformed search-key config entry '%s' (expected SETTING:number)"), *Entry);
				continue;
			}
			SettingName.TrimStartAndEndInline();
			KeyNumberString.TrimStartAndEndInline();
			const int32 KeyNumber = FCString::Atoi(*KeyNumberString);
			if (SettingName.IsEmpty() || KeyNumber <= 0)
			{
				UE_LOG_ONLINE(Error, TEXT("SearchKeyAllocator: invalid config entry '%s' (empty name or non-positive key); ignoring"), *Entry);
				ensureMsgf(false, TEXT("SearchKeyAllocator: invalid search-key config entry '%s' (empty name or non-positive key)"), *Entry);
				continue;
			}
			// Key by lower-case name so overrides de-duplicate case-insensitively and match the
			// normalized lookups used elsewhere; the original casing is kept in the value for the
			// read/decode path. A duplicate (same setting across entries/spaces) is almost always a
			// config mistake, so warn and let the last entry win deterministically.
			const FString NormalizedName = SettingName.ToLower();
			if (const FConfigOverride* Existing = OutOverrides.Find(NormalizedName))
			{
				UE_LOG_ONLINE(Warning, TEXT("SearchKeyAllocator: duplicate search-key override for setting '%s' (previously %s_key%d); using the last entry '%s'"),
					*SettingName, IsNumberType(Existing->Type) ? TEXT("number") : TEXT("string"), Existing->KeyNumber, *Entry);
			}
			OutOverrides.Add(NormalizedName, FConfigOverride{ SettingName, KeyNumber, Type });
		}
	};

	TArray<FString> StringKeyEntries;
	GConfig->GetArray(SearchKeyConfigSection, TEXT("SearchKeyString"), StringKeyEntries, GEngineIni);
	ParseEntries(StringKeyEntries, EOnlineKeyValuePairDataType::String);

	TArray<FString> NumberKeyEntries;
	GConfig->GetArray(SearchKeyConfigSection, TEXT("SearchKeyNumber"), NumberKeyEntries, GEngineIni);
	ParseEntries(NumberKeyEntries, EOnlineKeyValuePairDataType::Int32);
}

void FDynamicSearchKeyAllocator::Initialize(const FDefaultAssignment* Defaults, int32 DefaultsCount)
{
	SettingToSearchKey.Reset();
	KeyToSetting.Reset();

	if (GConfig != nullptr)
	{
		GConfig->GetInt(SearchKeyConfigSection, TEXT("SearchKeyMaxStringRange"), MaxStringKeyRange, GEngineIni);
		GConfig->GetInt(SearchKeyConfigSection, TEXT("SearchKeyMaxNumberRange"), MaxNumberKeyRange, GEngineIni);
	}
	MaxStringKeyRange = FMath::Clamp(MaxStringKeyRange, ReservedStringKeyCount + 1, 4096);
	MaxNumberKeyRange = FMath::Clamp(MaxNumberKeyRange, 1, 4096);

	UsedStringKeys.Init(false, MaxStringKeyRange);
	UsedNumberKeys.Init(false, MaxNumberKeyRange);

	// 1. Reserve the fixed platform string keys (string_key1-4).
	for (int32 KeyNumber = 1; KeyNumber <= ReservedStringKeyCount; ++KeyNumber)
	{
		UsedStringKeys[KeyNumber - 1] = true;
	}

	// Build a lookup of default setting name -> declared type so that an override which
	// targets a known built-in setting preserves that setting's type (notably Bool, which
	// shares the number-key space with Int32 but must round-trip as 1/0). Keyed lower-case
	// for case-insensitive matching.
	TMap<FString, EOnlineKeyValuePairDataType::Type> DefaultTypeBySetting;
	DefaultTypeBySetting.Reserve(DefaultsCount);
	for (int32 i = 0; i < DefaultsCount; ++i)
	{
		DefaultTypeBySetting.Add(Defaults[i].SettingKey.ToString().ToLower(), Defaults[i].Type);
	}

	// 2. Ini overrides are authoritative - apply them first so they win any conflict.
	TMap<FString, FConfigOverride> Overrides;
	LoadIniOverrides(Overrides);

	// Apply overrides in a deterministic order (not TMap iteration order): when two entries
	// target the same key number, the first after this stable sort reserves it and wins, so
	// the resulting mapping is identical across clients.
	struct FOverrideEntry
	{
		FString SettingName;
		int32 KeyNumber = 0;
		EOnlineKeyValuePairDataType::Type Type = EOnlineKeyValuePairDataType::Empty;
	};
	TArray<FOverrideEntry> SortedOverrides;
	SortedOverrides.Reserve(Overrides.Num());
	for (const auto& OverridePair : Overrides)
	{
		const FConfigOverride& Override = OverridePair.Value;
		EOnlineKeyValuePairDataType::Type Type = Override.Type;
		// OverridePair.Key is already lower-cased, matching DefaultTypeBySetting's keys.
		if (const EOnlineKeyValuePairDataType::Type* DefaultType = DefaultTypeBySetting.Find(OverridePair.Key))
		{
			Type = *DefaultType;
		}
		SortedOverrides.Add(FOverrideEntry{ Override.SettingName, Override.KeyNumber, Type });
	}
	SortedOverrides.Sort([this](const FOverrideEntry& A, const FOverrideEntry& B)
	{
		const bool bANumber = IsNumberType(A.Type);
		const bool bBNumber = IsNumberType(B.Type);
		if (bANumber != bBNumber)
		{
			return bANumber; // group by key space first for a stable, well-defined order
		}
		if (A.KeyNumber != B.KeyNumber)
		{
			return A.KeyNumber < B.KeyNumber;
		}
		return A.SettingName < B.SettingName;
	});
	for (const FOverrideEntry& Override : SortedOverrides)
	{
		if (TryReserveKey(Override.Type, Override.KeyNumber))
		{
			Assign(Override.SettingName, Override.Type, Override.KeyNumber);
		}
		else
		{
			// Out-of-range or already-taken keys have a legitimate cross-version fallback (the
			// displaced/unassigned setting is re-homed deterministically), so this stays a skip
			// rather than a hard failure. Escalated to Error-level so config drift is visible.
			UE_LOG_ONLINE(Error, TEXT("SearchKeyAllocator: config key %s:%d for '%s' is out of range or already in use; skipping"),
				IsNumberType(Override.Type) ? TEXT("number") : TEXT("string"), Override.KeyNumber, *Override.SettingName);
		}
	}

	// 3. Built-in defaults fill any setting not already overridden, at their default
	//    key number when free (preserves legacy behavior for back-compat).
	TArray<const FDefaultAssignment*> Deferred;
	for (int32 i = 0; i < DefaultsCount; ++i)
	{
		const FDefaultAssignment& Default = Defaults[i];
		const FString SettingName = Default.SettingKey.ToString();
		if (SettingToSearchKey.Contains(SettingName.ToLower()))
		{
			continue; // overridden by config (case-insensitive setting-name match)
		}
		if (TryReserveKey(Default.Type, Default.KeyNumber))
		{
			Assign(SettingName, Default.Type, Default.KeyNumber);
		}
		else
		{
			// Default slot taken (e.g. by a config override) - assign deterministically later.
			Deferred.Add(&Defaults[i]);
		}
	}

	// 4. Deterministic freed-pool fill for any deferred defaults. Sort by setting name
	//    so the assignment is stable and identical across clients.
	Deferred.Sort([](const FDefaultAssignment& A, const FDefaultAssignment& B)
	{
		return A.SettingKey.ToString() < B.SettingKey.ToString();
	});
	for (const FDefaultAssignment* Default : Deferred)
	{
		const int32 KeyNumber = AllocateNextFreeKey(Default->Type);
		if (KeyNumber != INDEX_NONE)
		{
			Assign(Default->SettingKey.ToString(), Default->Type, KeyNumber);
		}
		else
		{
			UE_LOG_ONLINE(Warning, TEXT("SearchKeyAllocator: no free %s key available for setting '%s'"),
				IsNumberType(Default->Type) ? TEXT("number") : TEXT("string"), *Default->SettingKey.ToString());
		}
	}
}

bool FDynamicSearchKeyAllocator::GetKeyForSetting(const FString& SettingName, FString& OutSearchKey, EOnlineKeyValuePairDataType::Type& OutType) const
{
	// SettingToSearchKey is keyed by normalized (lower-case) name, so this lookup is
	// case-insensitive and matches the normalization used when assignments are stored.
	if (const FString* Key = SettingToSearchKey.Find(SettingName.ToLower()))
	{
		OutSearchKey = *Key;
		if (const FSettingKeyType* Found = KeyToSetting.Find(OutSearchKey))
		{
			OutType = Found->Type;
		}
		return true;
	}
	return false;
}

const FDynamicSearchKeyAllocator::FSettingKeyType* FDynamicSearchKeyAllocator::FindSetting(const FString& SearchKey) const
{
	return KeyToSetting.Find(SearchKey);
}
