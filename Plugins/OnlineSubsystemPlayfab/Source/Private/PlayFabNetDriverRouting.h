//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

namespace Party
{
	class PartyNetwork;
}

class UPlayFabNetDriver;

namespace PlayFabNetDriverRouting
{
	UPlayFabNetDriver* Get(Party::PartyNetwork* Network);
	void Link(Party::PartyNetwork* Network, UPlayFabNetDriver* NetDriver);
	void Unlink(Party::PartyNetwork* Network, UPlayFabNetDriver* NetDriver);
	void Reset();
}
