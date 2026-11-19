//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "IPAddressPlayFab.h"
#include "OnlineSubsystemPlayFabPrivate.h"
#include "OnlineSubsystemPlayFabDefines.h"

FInternetAddrPlayFab::FInternetAddrPlayFab(uint32 InUniqueId) :
	EndpointId(InUniqueId),
	Port(InUniqueId)
{
}

FInternetAddrPlayFab::FInternetAddrPlayFab(const FInternetAddrPlayFab& Src) : 
	EndpointId(Src.EndpointId), 
	Port(Src.Port)
{
}

void FInternetAddrPlayFab::SetIp(uint32 InAddr)
{
	EndpointId = InAddr;
}

void FInternetAddrPlayFab::GetIp(uint32& OutAddr) const
{
	OutAddr = EndpointId;
}

void FInternetAddrPlayFab::SetPort(int32 InPort)
{
	Port = InPort;
}

void FInternetAddrPlayFab::GetPort(int32& OutPort) const
{
	OutPort = Port;
}

int32 FInternetAddrPlayFab::GetPort() const
{
	return Port;
}

FName FInternetAddrPlayFab::GetProtocolType() const
{
	return PLAYFAB_SUBSYSTEM;
}

TArray<uint8> FInternetAddrPlayFab::GetRawIp() const
{
	TArray<uint8> RawAddressArray;
	const uint8* RawData = reinterpret_cast<const uint8*>(&EndpointId);
	for (uint32 DataIndex = 0; DataIndex < sizeof(EndpointId); DataIndex++)
	{
		RawAddressArray.Add(RawData[DataIndex]);
	}

	return RawAddressArray;
}

void FInternetAddrPlayFab::SetRawIp(const TArray<uint8>& RawAddr)
{
	check(RawAddr.Num() == sizeof(EndpointId));
	if (RawAddr.Num() != sizeof(EndpointId))
	{
		return;
	}

	FMemory::Memcpy(&EndpointId, RawAddr.GetData(), sizeof(EndpointId));
	Port = EndpointId;
}

void FInternetAddrPlayFab::SetIp(const TCHAR* InAddr, bool& bIsValid)
{
	bIsValid = false;

	if (InAddr && FCString::Strncmp(InAddr, PLAYFAB_URL_PREFIX, FCString::Strlen(PLAYFAB_URL_PREFIX)) == 0)
	{
		const TCHAR* AddrStart = InAddr + UE_ARRAY_COUNT(PLAYFAB_URL_PREFIX) - 1;
		const TCHAR* PortSeparator = FCString::Strrchr(AddrStart, TEXT(':'));
		const FString PartyIdString = PortSeparator
			? FString(static_cast<int32>(PortSeparator - AddrStart), AddrStart)
			: FString(AddrStart);
		if (!PartyIdString.IsEmpty())
		{
			EndpointId = FCString::Atoi(*PartyIdString);
			Port = PortSeparator ? FCString::Atoi(PortSeparator + 1) : EndpointId;
			bIsValid = EndpointId != 0;
		}
	}
}

FString FInternetAddrPlayFab::ToString(bool bAppendPort) const
{
	if (bAppendPort)
	{
		return FString::Printf(TEXT("%s%d:%d"), PLAYFAB_URL_PREFIX, EndpointId, Port);
	}
	else
	{
		return FString::Printf(TEXT("%s%d"), PLAYFAB_URL_PREFIX, EndpointId);
	}
}

uint32 FInternetAddrPlayFab::GetTypeHash() const
{
	return GetConstTypeHash();
}

bool FInternetAddrPlayFab::IsValid() const
{
	return EndpointId != 0;
}

TSharedRef<FInternetAddr> FInternetAddrPlayFab::Clone() const
{
	return MakeShareable(new FInternetAddrPlayFab(*this));
}

uint32 FInternetAddrPlayFab::GetConstTypeHash() const
{
	return GetTypeHashHelper(ToString(true));
}

bool FInternetAddrPlayFab::operator!=(const FInternetAddrPlayFab& Other) const
{
	return !(FInternetAddrPlayFab::operator==(Other));
}

bool FInternetAddrPlayFab::operator==(const FInternetAddr& Other) const
{
	FInternetAddrPlayFab& PlayFabOther = (FInternetAddrPlayFab&)Other;
	return EndpointId == PlayFabOther.EndpointId;
}