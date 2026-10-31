//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"

namespace PlayFabSocketSelection
{
	template <typename SocketType, typename NetworkType, typename GetNetworkType>
	SocketType* SelectSocket(
		const TArray<SocketType*>& ActiveSockets,
		SocketType* LinkedSocket,
		NetworkType* TargetNetwork,
		GetNetworkType GetNetwork)
	{
		if (LinkedSocket && ActiveSockets.Contains(LinkedSocket) &&
			(!TargetNetwork || GetNetwork(LinkedSocket) == TargetNetwork))
		{
			return LinkedSocket;
		}

		for (int32 SocketIndex = ActiveSockets.Num() - 1; SocketIndex >= 0; --SocketIndex)
		{
			SocketType* Socket = ActiveSockets[SocketIndex];
			if (Socket && (!TargetNetwork || GetNetwork(Socket) == TargetNetwork))
			{
				return Socket;
			}
		}

		return nullptr;
	}
}