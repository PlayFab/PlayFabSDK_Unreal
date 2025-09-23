// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once
#include "PFUnrealTypes.h"
#include "PFPushNotificationsUnrealTypes.h"
#include "PFTypeConverters.h"
#include "PFCoreTypeConverters.h"

#pragma push_macro("IN")
#undef IN
	
TSharedPtr<const FPFPushNotificationsAdvancedPushPlatformMsg> ConvertAdvancedPushPlatformMsgToUnreal(const PFPushNotificationsAdvancedPushPlatformMsg* Datatype);
const PFPushNotificationsAdvancedPushPlatformMsg* ConvertAdvancedPushPlatformMsgToPlayfab(TSharedPtr<const FPFPushNotificationsAdvancedPushPlatformMsg> Datatype);
	
TSharedPtr<const FPFPushNotificationsPushNotificationPackage> ConvertPushNotificationPackageToUnreal(const PFPushNotificationsPushNotificationPackage* Datatype);
const PFPushNotificationsPushNotificationPackage* ConvertPushNotificationPackageToPlayfab(TSharedPtr<const FPFPushNotificationsPushNotificationPackage> Datatype);
	
TSharedPtr<const FPFPushNotificationsSendPushNotificationRequest> ConvertSendPushNotificationRequestToUnreal(const PFPushNotificationsSendPushNotificationRequest* Datatype);
const PFPushNotificationsSendPushNotificationRequest* ConvertSendPushNotificationRequestToPlayfab(TSharedPtr<const FPFPushNotificationsSendPushNotificationRequest> Datatype);
	
TSharedPtr<const FPFPushNotificationsSendPushNotificationFromTemplateRequest> ConvertSendPushNotificationFromTemplateRequestToUnreal(const PFPushNotificationsSendPushNotificationFromTemplateRequest* Datatype);
const PFPushNotificationsSendPushNotificationFromTemplateRequest* ConvertSendPushNotificationFromTemplateRequestToPlayfab(TSharedPtr<const FPFPushNotificationsSendPushNotificationFromTemplateRequest> Datatype);


#pragma pop_macro("IN")