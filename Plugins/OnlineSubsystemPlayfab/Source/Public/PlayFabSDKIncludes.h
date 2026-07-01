//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"

#if PLATFORM_WINDOWS || (defined(PLATFORM_XSX) && PLATFORM_XSX) || (defined(PLATFORM_XB1) && PLATFORM_XB1)
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/AllowWindowsPlatformAtomics.h"
#endif
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
#define PFMULTIPLAYER_INCLUDE_SERVER_APIS
#include <PFLobby.h>

using namespace Party;
THIRD_PARTY_INCLUDES_END
#if PLATFORM_WINDOWS || (defined(PLATFORM_XSX) && PLATFORM_XSX) || (defined(PLATFORM_XB1) && PLATFORM_XB1)
#include "Windows/HideWindowsPlatformAtomics.h"
#include "Windows/HideWindowsPlatformTypes.h"
#endif

#include <PFCore.h>
#include <PFAuthentication.h>
#include <PFEntity.h>
#include <PFServiceConfig.h>
#include <PFLocalUser.h>
#include <PFCoreUnrealTypes.h>