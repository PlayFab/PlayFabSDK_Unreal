//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#pragma once

#ifdef _MSC_VER
__pragma(warning(push))
__pragma(warning(disable: 4668)) /* 'symbol' is not defined as a preprocessor macro, replacing with '0' for 'directives' */
#endif // _MSC_VER

#if defined(OSS_PLAYFAB_GDK_SUPPORT)
#include "OnlineSubsystemGDKTypes.h"
#endif // OSS_PLAYFAB_GDK_SUPPORT