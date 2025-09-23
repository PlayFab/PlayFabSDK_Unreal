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
/// FPFPlayerDataManagementClientDeletePlayerCustomPropertiesRequest data model. Deletes custom properties
/// for the specified player. The list of provided property names must be non-empty.
/// </summary>
struct PLAYFABSERVICES_API FPFPlayerDataManagementClientDeletePlayerCustomPropertiesRequest
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
	/// (Optional) Optional field used for concurrency control. One can ensure that the delete operation
	/// will only be performed if the player's properties have not been updated by any other clients since
	/// the last version.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> expectedPropertiesVersion;

	/// <summary>
	/// A list of property names denoting which properties should be deleted.
	/// </summary>
	const TArray<FString> propertyNames;

	/// <summary>
	/// Count of propertyNames
	/// </summary>
	uint32 propertyNamesCount;
};

/// <summary>
/// FPFPlayerDataManagementDeletedPropertyDetails data model.
/// </summary>
struct PLAYFABSERVICES_API FPFPlayerDataManagementDeletedPropertyDetails
{
	/// <summary>
	/// (Optional) The name of the property which was requested to be deleted.
	/// </summary>
	_Maybenull_ const FString name;

	/// <summary>
	/// Indicates whether or not the property was deleted. If false, no property with that name existed.
	/// </summary>
	bool wasDeleted;
};

/// <summary>
/// FPFPlayerDataManagementClientDeletePlayerCustomPropertiesResult data model.
/// </summary>
struct PLAYFABSERVICES_API FPFPlayerDataManagementClientDeletePlayerCustomPropertiesResult
{
	/// <summary>
	/// (Optional) The list of properties requested to be deleted.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFPlayerDataManagementDeletedPropertyDetails>> deletedProperties;

	/// <summary>
	/// Count of deletedProperties
	/// </summary>
	uint32 deletedPropertiesCount;

	/// <summary>
	/// Indicates the current version of a player's properties that have been set. This is incremented after
	/// updates and deletes. This version can be provided in update and delete calls for concurrency control.
	/// </summary>
	int32 propertiesVersion;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFPlayerDataManagementClientGetPlayerCustomPropertyRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFPlayerDataManagementClientGetPlayerCustomPropertyRequest
{
	/// <summary>
	/// Specific property name to search for in the player's properties.
	/// </summary>
	const FString propertyName;
};

/// <summary>
/// FPFPlayerDataManagementCustomPropertyDetails data model.
/// </summary>
struct PLAYFABSERVICES_API FPFPlayerDataManagementCustomPropertyDetails
{
	/// <summary>
	/// (Optional) The custom property's name.
	/// </summary>
	_Maybenull_ const FString name;

	/// <summary>
	/// (Optional) The custom property's value.
	/// </summary>
	FPFJsonObject value;
};

/// <summary>
/// FPFPlayerDataManagementClientGetPlayerCustomPropertyResult data model.
/// </summary>
struct PLAYFABSERVICES_API FPFPlayerDataManagementClientGetPlayerCustomPropertyResult
{
	/// <summary>
	/// Indicates the current version of a player's properties that have been set. This is incremented after
	/// updates and deletes. This version can be provided in update and delete calls for concurrency control.
	/// </summary>
	int32 propertiesVersion;

	/// <summary>
	/// (Optional) Player specific property and its corresponding value.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFPlayerDataManagementCustomPropertyDetails> property;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFPlayerDataManagementGetUserDataRequest data model. Data is stored as JSON key-value pairs. Every
/// time the data is updated via any source, the version counter is incremented. If the Version parameter
/// is provided, then this call will only return data if the current version on the system is greater
/// than the value provided. If the Keys parameter is provided, the data object returned will only contain
/// the data specific to the indicated Keys. Otherwise, the full set of custom user data will be returned.
/// </summary>
struct PLAYFABSERVICES_API FPFPlayerDataManagementGetUserDataRequest
{
	/// <summary>
	/// (Optional) The version that currently exists according to the caller. The call will return the data
	/// for all of the keys if the version in the system is greater than this.
	/// </summary>
	_Maybenull_ TSharedPtr<const uint32> ifChangedFromDataVersion;

	/// <summary>
	/// (Optional) List of unique keys to load from.
	/// </summary>
	_Maybenull_ const TArray<FString> keys;

	/// <summary>
	/// Count of keys
	/// </summary>
	uint32 keysCount;

	/// <summary>
	/// (Optional) Unique PlayFab identifier of the user to load data for. Optional, defaults to yourself
	/// if not set. When specified to a PlayFab id of another player, then this will only return public keys
	/// for that account.
	/// </summary>
	_Maybenull_ const FString playFabId;
};

/// <summary>
/// FPFPlayerDataManagementClientGetUserDataResult data model.
/// </summary>
struct PLAYFABSERVICES_API FPFPlayerDataManagementClientGetUserDataResult
{
	/// <summary>
	/// (Optional) User specific data for this title.
	/// </summary>
	_Maybenull_ TMap<const FString, TSharedPtr<const FPFUserDataRecord>> data;

	/// <summary>
	/// Count of data
	/// </summary>
	uint32 dataCount;

	/// <summary>
	/// Indicates the current version of the data that has been set. This is incremented with every set
	/// call for that type of data (read-only, internal, etc). This version can be provided in Get calls
	/// to find updated data.
	/// </summary>
	uint32 dataVersion;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFPlayerDataManagementClientListPlayerCustomPropertiesResult data model.
/// </summary>
struct PLAYFABSERVICES_API FPFPlayerDataManagementClientListPlayerCustomPropertiesResult
{
	/// <summary>
	/// (Optional) Player specific properties and their corresponding values for this title.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFPlayerDataManagementCustomPropertyDetails>> properties;

	/// <summary>
	/// Count of properties
	/// </summary>
	uint32 propertiesCount;

	/// <summary>
	/// Indicates the current version of a player's properties that have been set. This is incremented after
	/// updates and deletes. This version can be provided in update and delete calls for concurrency control.
	/// </summary>
	int32 propertiesVersion;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFPlayerDataManagementUpdateProperty data model.
/// </summary>
struct PLAYFABSERVICES_API FPFPlayerDataManagementUpdateProperty
{
	/// <summary>
	/// Name of the custom property. Can contain Unicode letters and digits. They are limited in size.
	/// </summary>
	const FString name;

	/// <summary>
	/// Value of the custom property. Limited to booleans, numbers, and strings.
	/// </summary>
	FPFJsonObject value;
};

/// <summary>
/// FPFPlayerDataManagementClientUpdatePlayerCustomPropertiesRequest data model. Performs an additive
/// update of the custom properties for the specified player. In updating the player's custom properties,
/// properties which already exist will have their values overwritten. No other properties will be changed
/// apart from those specified in the call.
/// </summary>
struct PLAYFABSERVICES_API FPFPlayerDataManagementClientUpdatePlayerCustomPropertiesRequest
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
	/// (Optional) Optional field used for concurrency control. One can ensure that the update operation
	/// will only be performed if the player's properties have not been updated by any other clients since
	/// last the version.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> expectedPropertiesVersion;

	/// <summary>
	/// Collection of properties to be set for a player.
	/// </summary>
	TArray<TSharedPtr<const FPFPlayerDataManagementUpdateProperty>> properties;

	/// <summary>
	/// Count of properties
	/// </summary>
	uint32 propertiesCount;
};

/// <summary>
/// FPFPlayerDataManagementClientUpdatePlayerCustomPropertiesResult data model.
/// </summary>
struct PLAYFABSERVICES_API FPFPlayerDataManagementClientUpdatePlayerCustomPropertiesResult
{
	/// <summary>
	/// Indicates the current version of a player's properties that have been set. This is incremented after
	/// updates and deletes. This version can be provided in update and delete calls for concurrency control.
	/// </summary>
	int32 propertiesVersion;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFPlayerDataManagementClientUpdateUserDataRequest data model. This function performs an additive
/// update of the arbitrary strings containing the custom data for the user. In updating the custom data
/// object, keys which already exist in the object will have their values overwritten, while keys with
/// null values will be removed. New keys will be added, with the given values. No other key-value pairs
/// will be changed apart from those specified in the call.
/// </summary>
struct PLAYFABSERVICES_API FPFPlayerDataManagementClientUpdateUserDataRequest
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
	/// (Optional) Key-value pairs to be written to the custom data. Note that keys are trimmed of whitespace,
	/// are limited in size, and may not begin with a '!' character or be null.
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> data;

	/// <summary>
	/// Count of data
	/// </summary>
	uint32 dataCount;

	/// <summary>
	/// (Optional) Optional list of Data-keys to remove from UserData. Some SDKs cannot insert null-values
	/// into Data due to language constraints. Use this to delete the keys directly.
	/// </summary>
	_Maybenull_ const TArray<FString> keysToRemove;

	/// <summary>
	/// Count of keysToRemove
	/// </summary>
	uint32 keysToRemoveCount;

	/// <summary>
	/// (Optional) Permission to be applied to all user data keys written in this request. Defaults to "private"
	/// if not set. This is used for requests by one player for information about another player; those requests
	/// will only return Public keys.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFUserDataPermission> permission;
};

/// <summary>
/// FPFPlayerDataManagementUpdateUserDataResult data model.
/// </summary>
struct PLAYFABSERVICES_API FPFPlayerDataManagementUpdateUserDataResult
{
	/// <summary>
	/// Indicates the current version of the data that has been set. This is incremented with every set
	/// call for that type of data (read-only, internal, etc). This version can be provided in Get calls
	/// to find updated data.
	/// </summary>
	uint32 dataVersion;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFPlayerDataManagementServerDeletePlayerCustomPropertiesRequest data model. Deletes custom properties
/// for the specified player. The list of provided property names must be non-empty.
/// </summary>
struct PLAYFABSERVICES_API FPFPlayerDataManagementServerDeletePlayerCustomPropertiesRequest
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
	/// (Optional) Optional field used for concurrency control. One can ensure that the delete operation
	/// will only be performed if the player's properties have not been updated by any other clients since
	/// the last version.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> expectedPropertiesVersion;

	/// <summary>
	/// Unique PlayFab assigned ID of the user on whom the operation will be performed.
	/// </summary>
	const FString playFabId;

	/// <summary>
	/// A list of property names denoting which properties should be deleted.
	/// </summary>
	const TArray<FString> propertyNames;

	/// <summary>
	/// Count of propertyNames
	/// </summary>
	uint32 propertyNamesCount;
};

/// <summary>
/// FPFPlayerDataManagementServerDeletePlayerCustomPropertiesResult data model.
/// </summary>
struct PLAYFABSERVICES_API FPFPlayerDataManagementServerDeletePlayerCustomPropertiesResult
{
	/// <summary>
	/// (Optional) The list of properties requested to be deleted.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFPlayerDataManagementDeletedPropertyDetails>> deletedProperties;

	/// <summary>
	/// Count of deletedProperties
	/// </summary>
	uint32 deletedPropertiesCount;

	/// <summary>
	/// (Optional) PlayFab unique identifier of the user whose properties were deleted.
	/// </summary>
	_Maybenull_ const FString playFabId;

	/// <summary>
	/// Indicates the current version of a player's properties that have been set. This is incremented after
	/// updates and deletes. This version can be provided in update and delete calls for concurrency control.
	/// </summary>
	int32 propertiesVersion;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFPlayerDataManagementServerGetPlayerCustomPropertyRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFPlayerDataManagementServerGetPlayerCustomPropertyRequest
{
	/// <summary>
	/// Unique PlayFab assigned ID of the user on whom the operation will be performed.
	/// </summary>
	const FString playFabId;

	/// <summary>
	/// Specific property name to search for in the player's properties.
	/// </summary>
	const FString propertyName;
};

/// <summary>
/// FPFPlayerDataManagementServerGetPlayerCustomPropertyResult data model.
/// </summary>
struct PLAYFABSERVICES_API FPFPlayerDataManagementServerGetPlayerCustomPropertyResult
{
	/// <summary>
	/// (Optional) PlayFab unique identifier of the user whose properties are being returned.
	/// </summary>
	_Maybenull_ const FString playFabId;

	/// <summary>
	/// Indicates the current version of a player's properties that have been set. This is incremented after
	/// updates and deletes. This version can be provided in update and delete calls for concurrency control.
	/// </summary>
	int32 propertiesVersion;

	/// <summary>
	/// (Optional) Player specific property and its corresponding value.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFPlayerDataManagementCustomPropertyDetails> property;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFPlayerDataManagementServerGetUserDataResult data model.
/// </summary>
struct PLAYFABSERVICES_API FPFPlayerDataManagementServerGetUserDataResult
{
	/// <summary>
	/// (Optional) User specific data for this title.
	/// </summary>
	_Maybenull_ TMap<const FString, TSharedPtr<const FPFUserDataRecord>> data;

	/// <summary>
	/// Count of data
	/// </summary>
	uint32 dataCount;

	/// <summary>
	/// Indicates the current version of the data that has been set. This is incremented with every set
	/// call for that type of data (read-only, internal, etc). This version can be provided in Get calls
	/// to find updated data.
	/// </summary>
	uint32 dataVersion;

	/// <summary>
	/// (Optional) PlayFab unique identifier of the user whose custom data is being returned.
	/// </summary>
	_Maybenull_ const FString playFabId;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFPlayerDataManagementListPlayerCustomPropertiesRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFPlayerDataManagementListPlayerCustomPropertiesRequest
{
	/// <summary>
	/// Unique PlayFab assigned ID of the user on whom the operation will be performed.
	/// </summary>
	const FString playFabId;
};

/// <summary>
/// FPFPlayerDataManagementServerListPlayerCustomPropertiesResult data model.
/// </summary>
struct PLAYFABSERVICES_API FPFPlayerDataManagementServerListPlayerCustomPropertiesResult
{
	/// <summary>
	/// (Optional) PlayFab unique identifier of the user whose properties are being returned.
	/// </summary>
	_Maybenull_ const FString playFabId;

	/// <summary>
	/// (Optional) Player specific properties and their corresponding values for this title.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFPlayerDataManagementCustomPropertyDetails>> properties;

	/// <summary>
	/// Count of properties
	/// </summary>
	uint32 propertiesCount;

	/// <summary>
	/// Indicates the current version of a player's properties that have been set. This is incremented after
	/// updates and deletes. This version can be provided in update and delete calls for concurrency control.
	/// </summary>
	int32 propertiesVersion;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFPlayerDataManagementServerUpdatePlayerCustomPropertiesRequest data model. Performs an additive
/// update of the custom properties for the specified player. In updating the player's custom properties,
/// properties which already exist will have their values overwritten. No other properties will be changed
/// apart from those specified in the call.
/// </summary>
struct PLAYFABSERVICES_API FPFPlayerDataManagementServerUpdatePlayerCustomPropertiesRequest
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
	/// (Optional) Optional field used for concurrency control. One can ensure that the update operation
	/// will only be performed if the player's properties have not been updated by any other clients since
	/// last the version.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> expectedPropertiesVersion;

	/// <summary>
	/// Unique PlayFab assigned ID of the user on whom the operation will be performed.
	/// </summary>
	const FString playFabId;

	/// <summary>
	/// Collection of properties to be set for a player.
	/// </summary>
	TArray<TSharedPtr<const FPFPlayerDataManagementUpdateProperty>> properties;

	/// <summary>
	/// Count of properties
	/// </summary>
	uint32 propertiesCount;
};

/// <summary>
/// FPFPlayerDataManagementServerUpdatePlayerCustomPropertiesResult data model.
/// </summary>
struct PLAYFABSERVICES_API FPFPlayerDataManagementServerUpdatePlayerCustomPropertiesResult
{
	/// <summary>
	/// (Optional) PlayFab unique identifier of the user whose properties were updated.
	/// </summary>
	_Maybenull_ const FString playFabId;

	/// <summary>
	/// Indicates the current version of a player's properties that have been set. This is incremented after
	/// updates and deletes. This version can be provided in update and delete calls for concurrency control.
	/// </summary>
	int32 propertiesVersion;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFPlayerDataManagementServerUpdateUserDataRequest data model. This function performs an additive
/// update of the arbitrary JSON object containing the custom data for the user. In updating the custom
/// data object, keys which already exist in the object will have their values overwritten, while keys
/// with null values will be removed. No other key-value pairs will be changed apart from those specified
/// in the call.
/// </summary>
struct PLAYFABSERVICES_API FPFPlayerDataManagementServerUpdateUserDataRequest
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
	/// (Optional) Key-value pairs to be written to the custom data. Note that keys are trimmed of whitespace,
	/// are limited in size, and may not begin with a '!' character or be null.
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> data;

	/// <summary>
	/// Count of data
	/// </summary>
	uint32 dataCount;

	/// <summary>
	/// (Optional) Optional list of Data-keys to remove from UserData. Some SDKs cannot insert null-values
	/// into Data due to language constraints. Use this to delete the keys directly.
	/// </summary>
	_Maybenull_ const TArray<FString> keysToRemove;

	/// <summary>
	/// Count of keysToRemove
	/// </summary>
	uint32 keysToRemoveCount;

	/// <summary>
	/// (Optional) Permission to be applied to all user data keys written in this request. Defaults to "private"
	/// if not set.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFUserDataPermission> permission;

	/// <summary>
	/// Unique PlayFab assigned ID of the user on whom the operation will be performed.
	/// </summary>
	const FString playFabId;
};

/// <summary>
/// FPFPlayerDataManagementUpdateUserInternalDataRequest data model. This function performs an additive
/// update of the arbitrary JSON object containing the custom data for the user. In updating the custom
/// data object, keys which already exist in the object will have their values overwritten, keys with
/// null values will be removed. No other key-value pairs will be changed apart from those specified in
/// the call.
/// </summary>
struct PLAYFABSERVICES_API FPFPlayerDataManagementUpdateUserInternalDataRequest
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
	/// (Optional) Key-value pairs to be written to the custom data. Note that keys are trimmed of whitespace,
	/// are limited in size, and may not begin with a '!' character or be null.
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> data;

	/// <summary>
	/// Count of data
	/// </summary>
	uint32 dataCount;

	/// <summary>
	/// (Optional) Optional list of Data-keys to remove from UserData. Some SDKs cannot insert null-values
	/// into Data due to language constraints. Use this to delete the keys directly.
	/// </summary>
	_Maybenull_ const TArray<FString> keysToRemove;

	/// <summary>
	/// Count of keysToRemove
	/// </summary>
	uint32 keysToRemoveCount;

	/// <summary>
	/// Unique PlayFab assigned ID of the user on whom the operation will be performed.
	/// </summary>
	const FString playFabId;
};

// Delegates Declarations

DECLARE_DELEGATE_TwoParams(FOnClientDeletePlayerCustomPropertiesCompleted, const FPFPlayerDataManagementClientDeletePlayerCustomPropertiesResult&, bool);

DECLARE_DELEGATE_TwoParams(FOnClientGetPlayerCustomPropertyCompleted, const FPFPlayerDataManagementClientGetPlayerCustomPropertyResult&, bool);

DECLARE_DELEGATE_TwoParams(FOnClientGetUserDataCompleted, const FPFPlayerDataManagementClientGetUserDataResult&, bool);

DECLARE_DELEGATE_TwoParams(FOnClientGetUserPublisherDataCompleted, const FPFPlayerDataManagementClientGetUserDataResult&, bool);

DECLARE_DELEGATE_TwoParams(FOnClientGetUserPublisherReadOnlyDataCompleted, const FPFPlayerDataManagementClientGetUserDataResult&, bool);

DECLARE_DELEGATE_TwoParams(FOnClientGetUserReadOnlyDataCompleted, const FPFPlayerDataManagementClientGetUserDataResult&, bool);

DECLARE_DELEGATE_TwoParams(FOnClientListPlayerCustomPropertiesCompleted, const FPFPlayerDataManagementClientListPlayerCustomPropertiesResult&, bool);

DECLARE_DELEGATE_TwoParams(FOnClientUpdatePlayerCustomPropertiesCompleted, const FPFPlayerDataManagementClientUpdatePlayerCustomPropertiesResult&, bool);

DECLARE_DELEGATE_TwoParams(FOnClientUpdateUserDataCompleted, const FPFPlayerDataManagementUpdateUserDataResult&, bool);

DECLARE_DELEGATE_TwoParams(FOnClientUpdateUserPublisherDataCompleted, const FPFPlayerDataManagementUpdateUserDataResult&, bool);

#if HC_PLATFORM == HC_PLATFORM_GDK
DECLARE_DELEGATE_TwoParams(FOnServerDeletePlayerCustomPropertiesCompleted, const FPFPlayerDataManagementServerDeletePlayerCustomPropertiesResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK
DECLARE_DELEGATE_TwoParams(FOnServerGetPlayerCustomPropertyCompleted, const FPFPlayerDataManagementServerGetPlayerCustomPropertyResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerGetUserDataCompleted, const FPFPlayerDataManagementServerGetUserDataResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerGetUserInternalDataCompleted, const FPFPlayerDataManagementServerGetUserDataResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerGetUserPublisherDataCompleted, const FPFPlayerDataManagementServerGetUserDataResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerGetUserPublisherInternalDataCompleted, const FPFPlayerDataManagementServerGetUserDataResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerGetUserPublisherReadOnlyDataCompleted, const FPFPlayerDataManagementServerGetUserDataResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerGetUserReadOnlyDataCompleted, const FPFPlayerDataManagementServerGetUserDataResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK
DECLARE_DELEGATE_TwoParams(FOnServerListPlayerCustomPropertiesCompleted, const FPFPlayerDataManagementServerListPlayerCustomPropertiesResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK
DECLARE_DELEGATE_TwoParams(FOnServerUpdatePlayerCustomPropertiesCompleted, const FPFPlayerDataManagementServerUpdatePlayerCustomPropertiesResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerUpdateUserDataCompleted, const FPFPlayerDataManagementUpdateUserDataResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerUpdateUserInternalDataCompleted, const FPFPlayerDataManagementUpdateUserDataResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerUpdateUserPublisherDataCompleted, const FPFPlayerDataManagementUpdateUserDataResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerUpdateUserPublisherInternalDataCompleted, const FPFPlayerDataManagementUpdateUserDataResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerUpdateUserPublisherReadOnlyDataCompleted, const FPFPlayerDataManagementUpdateUserDataResult&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK || HC_PLATFORM == HC_PLATFORM_LINUX || HC_PLATFORM == HC_PLATFORM_MAC
DECLARE_DELEGATE_TwoParams(FOnServerUpdateUserReadOnlyDataCompleted, const FPFPlayerDataManagementUpdateUserDataResult&, bool);
#endif

#pragma pop_macro("IN")