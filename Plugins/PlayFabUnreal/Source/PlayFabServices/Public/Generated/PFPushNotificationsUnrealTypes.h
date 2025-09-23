// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once
#include "PFUnrealTypes.h"

#pragma push_macro("IN")
#undef IN

/// <summary>
/// FPFPushNotificationsAdvancedPushPlatformMsg data model.
/// </summary>
struct PLAYFABSERVICES_API FPFPushNotificationsAdvancedPushPlatformMsg
{
	/// <summary>
	/// (Optional) Stops GoogleCloudMessaging notifications from including both notification and data properties
	/// and instead only sends the data property.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> gCMDataOnly;

	/// <summary>
	/// The Json the platform should receive.
	/// </summary>
	const FString json;

	/// <summary>
	/// The platform that should receive the Json.
	/// </summary>
	FPFPushNotificationPlatform platform;
};

/// <summary>
/// FPFPushNotificationsPushNotificationPackage data model.
/// </summary>
struct PLAYFABSERVICES_API FPFPushNotificationsPushNotificationPackage
{
	/// <summary>
	/// Numerical badge to display on App icon (iOS only).
	/// </summary>
	int32 badge;

	/// <summary>
	/// (Optional) This must be a JSON formatted object. For use with developer-created custom Push Notification
	/// plugins.
	/// </summary>
	_Maybenull_ const FString customData;

	/// <summary>
	/// (Optional) Icon file to display with the message (Not supported for iOS).
	/// </summary>
	_Maybenull_ const FString icon;

	/// <summary>
	/// Content of the message (all platforms).
	/// </summary>
	const FString message;

	/// <summary>
	/// (Optional) Sound file to play with the message (all platforms).
	/// </summary>
	_Maybenull_ const FString sound;

	/// <summary>
	/// Title/Subject of the message. Not supported for iOS.
	/// </summary>
	const FString title;
};

/// <summary>
/// FPFPushNotificationsSendPushNotificationRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFPushNotificationsSendPushNotificationRequest
{
	/// <summary>
	/// (Optional) Allows you to provide precisely formatted json to target devices. This is an advanced
	/// feature, allowing you to deliver to custom plugin logic, fields, or functionality not natively supported
	/// by PlayFab.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFPushNotificationsAdvancedPushPlatformMsg>> advancedPlatformDelivery;

	/// <summary>
	/// Count of advancedPlatformDelivery
	/// </summary>
	uint32 advancedPlatformDeliveryCount;

	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// (Optional) Text of message to send.
	/// </summary>
	_Maybenull_ const FString message;

	/// <summary>
	/// (Optional) Defines all possible push attributes like message, title, icon, etc. Some parameters
	/// are device specific - please see the PushNotificationPackage documentation for details.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFPushNotificationsPushNotificationPackage> package;

	/// <summary>
	/// PlayFabId of the recipient of the push notification.
	/// </summary>
	const FString recipient;

	/// <summary>
	/// (Optional) Subject of message to send (may not be displayed in all platforms).
	/// </summary>
	_Maybenull_ const FString subject;

	/// <summary>
	/// (Optional) Target Platforms that should receive the Message or Package. If omitted, we will send
	/// to all available platforms.
	/// </summary>
	_Maybenull_ const TArray<FPFPushNotificationPlatform> targetPlatforms;

	/// <summary>
	/// Count of targetPlatforms
	/// </summary>
	uint32 targetPlatformsCount;
};

/// <summary>
/// FPFPushNotificationsSendPushNotificationFromTemplateRequest data model. Represents the request for
/// sending a push notification template to a recipient.
/// </summary>
struct PLAYFABSERVICES_API FPFPushNotificationsSendPushNotificationFromTemplateRequest
{
	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;

	/// <summary>
	/// Id of the push notification template.
	/// </summary>
	const FString pushNotificationTemplateId;

	/// <summary>
	/// PlayFabId of the push notification recipient.
	/// </summary>
	const FString recipient;
};

// Delegates Declarations

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerSendPushNotificationCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerSendPushNotificationFromTemplateCompleted, const FString&, bool);
#endif

#pragma pop_macro("IN")