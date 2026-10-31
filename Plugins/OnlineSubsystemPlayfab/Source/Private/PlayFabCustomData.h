#pragma once

#include "CoreMinimal.h"
#include "Misc/ConfigCacheIni.h"
#include "PlayFabSDKIncludes.h"

namespace PlayFabCustomData
{
	inline constexpr ANSICHAR ChannelKey[] = "Channel";
	inline constexpr ANSICHAR ChannelValue[] = "CustomData";

	inline constexpr TCHAR ConfigSection[] = TEXT("OnlineSubsystemPlayFab");
	inline constexpr TCHAR EnabledKey[] = TEXT("bEnableCustomDataEndpoint");

	inline bool IsEnabled(const FConfigFile& Config)
	{
		bool bEnabled = false;
		Config.GetBool(ConfigSection, EnabledKey, bEnabled);
		return bEnabled;
	}

	inline bool IsEnabled(FConfigCacheIni& Config, const FString& Filename)
	{
		bool bEnabled = false;
		Config.GetBool(ConfigSection, EnabledKey, bEnabled, Filename);
		return bEnabled;
	}

	inline bool IsCustomChannelValue(const Party::PartyDataBuffer& Value)
	{
		return Value.buffer != nullptr &&
			Value.bufferByteCount == sizeof(ChannelValue) &&
			FMemory::Memcmp(Value.buffer, ChannelValue, sizeof(ChannelValue)) == 0;
	}

	inline bool IsCustomEndpoint(Party::PartyEndpoint* Endpoint)
	{
		if (!Endpoint)
		{
			return false;
		}

		Party::PartyDataBuffer Value{};
		return PARTY_SUCCEEDED(Endpoint->GetSharedProperty(ChannelKey, &Value)) && IsCustomChannelValue(Value);
	}

	inline bool IsReceivedOnEndpoint(const Party::PartyEndpointMessageReceivedStateChange& StateChange, const Party::PartyLocalEndpoint* Endpoint)
	{
		for (uint32 Index = 0; Endpoint && Index < StateChange.receiverEndpointCount; ++Index)
		{
			if (StateChange.receiverEndpoints[Index] == Endpoint)
			{
				return true;
			}
		}
		return false;
	}

	inline bool IsMessageForNetwork(const Party::PartyEndpointMessageReceivedStateChange& StateChange, const Party::PartyNetwork* Network)
	{
		return Network != nullptr && StateChange.network == Network;
	}

	inline bool CopyPayload(const Party::PartyEndpointMessageReceivedStateChange& StateChange, TArray<uint8>& OutPayload)
	{
		if (!StateChange.messageBuffer || StateChange.messageSize == 0)
		{
			return false;
		}

		const uint8* Buffer = static_cast<const uint8*>(StateChange.messageBuffer);
		OutPayload = TArray<uint8>(Buffer, StateChange.messageSize);
		return true;
	}

	enum class ESendAction
	{
		Reject,
		SucceedWithoutSend,
		Send
	};

	inline ESendAction GetSendAction(bool bHasLocalEndpoint, int32 PayloadSize, int32 RecipientCount)
	{
		if (!bHasLocalEndpoint || PayloadSize <= 0)
		{
			return ESendAction::Reject;
		}
		return RecipientCount > 0 ? ESendAction::Send : ESendAction::SucceedWithoutSend;
	}
}
