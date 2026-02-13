//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"

THIRD_PARTY_INCLUDES_START
#if defined(OSS_PLAYFAB_SWITCH) || defined(OSS_PLAYFAB_PLAYSTATION)
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#include <PartyPal.h>
#include <PFMultiplayerPal.h>
#else
#ifndef HRESULT
typedef long HRESULT;
#endif
#endif

// Undefine Windows SendMessage macro to prevent conflict with Party::SendMessage
#ifndef NOUSER
#define NOUSER
#endif

#include <Party.h>
#include <PartyTypes.h>

#if defined(OSS_PLAYFAB_GDK_SUPPORT)
#include "PartyXboxLive.h"
#endif // OSS_PLAYFAB_GDK_SUPPORT

#include <PFEntityKey.h>
#include <PFMultiplayer.h>
#include <PFMatchmaking.h> 
#include <PFLobby.h>

#include <PFCore.h>
#include <PFAuthentication.h>
#include <PFEntity.h>
#include <PFServiceConfig.h>
#include <PFLocalUser.h>
#include <PFCoreUnrealTypes.h>

using namespace Party;
THIRD_PARTY_INCLUDES_END