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
/// EffectType enum.
/// </summary>
enum class FPFProfilesEffectType : uint32
{
	Allow,
	Deny
};

/// <summary>
/// FPFProfilesGetEntityProfileRequest data model. Given an entity type and entity identifier will retrieve
/// the profile from the entity store. If the profile being retrieved is the caller's, then the read operation
/// is consistent, if not it is an inconsistent read. An inconsistent read means that we do not guarantee
/// all committed writes have occurred before reading the profile, allowing for a stale read. If consistency
/// is important the Version Number on the result can be used to compare which version of the profile
/// any reader has.
/// </summary>
struct PLAYFABSERVICES_API FPFProfilesGetEntityProfileRequest
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
	/// (Optional) Determines whether the objects will be returned as an escaped JSON string or as a un-escaped
	/// JSON object. Default is JSON string.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> dataAsObject;

	/// <summary>
	/// (Optional) The optional entity to perform this action on. Defaults to the currently logged in entity.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;
};

/// <summary>
/// FPFProfilesEntityProfileFileMetadata data model. An entity file's meta data. To get a download URL
/// call File/GetFiles API.
/// </summary>
struct PLAYFABSERVICES_API FPFProfilesEntityProfileFileMetadata
{
	/// <summary>
	/// (Optional) Checksum value for the file, can be used to check if the file on the server has changed.
	/// </summary>
	_Maybenull_ const FString checksum;

	/// <summary>
	/// (Optional) Name of the file.
	/// </summary>
	_Maybenull_ const FString fileName;

	/// <summary>
	/// Last UTC time the file was modified.
	/// </summary>
	FDateTime lastModified;

	/// <summary>
	/// Storage service's reported byte count.
	/// </summary>
	int32 size;
};

/// <summary>
/// FPFProfilesEntityDataObject data model. An entity object and its associated meta data.
/// </summary>
struct PLAYFABSERVICES_API FPFProfilesEntityDataObject
{
	/// <summary>
	/// (Optional) Un-escaped JSON object, if DataAsObject is true.
	/// </summary>
	FPFJsonObject dataObject;

	/// <summary>
	/// (Optional) Escaped string JSON body of the object, if DataAsObject is default or false.
	/// </summary>
	_Maybenull_ const FString escapedDataObject;

	/// <summary>
	/// (Optional) Name of this object.
	/// </summary>
	_Maybenull_ const FString objectName;
};

/// <summary>
/// FPFProfilesEntityPermissionStatement data model.
/// </summary>
struct PLAYFABSERVICES_API FPFProfilesEntityPermissionStatement
{
	/// <summary>
	/// The action this statement effects. May be 'Read', 'Write' or '*' for both read and write.
	/// </summary>
	const FString action;

	/// <summary>
	/// (Optional) A comment about the statement. Intended solely for bookkeeping and debugging.
	/// </summary>
	_Maybenull_ const FString comment;

	/// <summary>
	/// (Optional) Additional conditions to be applied for entity resources.
	/// </summary>
	FPFJsonObject condition;

	/// <summary>
	/// The effect this statement will have. It may be either Allow or Deny.
	/// </summary>
	FPFProfilesEffectType effect;

	/// <summary>
	/// The principal this statement will effect.
	/// </summary>
	FPFJsonObject principal;

	/// <summary>
	/// The resource this statements effects. Similar to 'pfrn:data--title![Title ID]/Profile/*'.
	/// </summary>
	const FString resource;
};

/// <summary>
/// FPFEntityStatisticValue data model.
/// </summary>
struct PLAYFABSERVICES_API FPFEntityStatisticValue
{
	/// <summary>
	/// (Optional) Metadata associated with the Statistic.
	/// </summary>
	_Maybenull_ const FString metadata;

	/// <summary>
	/// (Optional) Statistic name.
	/// </summary>
	_Maybenull_ const FString name;

	/// <summary>
	/// (Optional) Statistic scores.
	/// </summary>
	_Maybenull_ const TArray<FString> scores;

	/// <summary>
	/// Count of scores
	/// </summary>
	uint32 scoresCount;

	/// <summary>
	/// Statistic version.
	/// </summary>
	int32 version;
};

/// <summary>
/// FPFProfilesEntityProfileBody data model.
/// </summary>
struct PLAYFABSERVICES_API FPFProfilesEntityProfileBody
{
	/// <summary>
	/// (Optional) Avatar URL for the entity.
	/// </summary>
	_Maybenull_ const FString avatarUrl;

	/// <summary>
	/// The creation time of this profile in UTC.
	/// </summary>
	FDateTime created;

	/// <summary>
	/// (Optional) The display name of the entity. This field may serve different purposes for different
	/// entity types. i.e.: for a title player account it could represent the display name of the player,
	/// whereas on a character it could be character's name.
	/// </summary>
	_Maybenull_ const FString displayName;

	/// <summary>
	/// (Optional) The entity id and type.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) The chain of responsibility for this entity. Use Lineage.
	/// </summary>
	_Maybenull_ const FString entityChain;

	/// <summary>
	/// (Optional) The experiment variants of this profile.
	/// </summary>
	_Maybenull_ const TArray<FString> experimentVariants;

	/// <summary>
	/// Count of experimentVariants
	/// </summary>
	uint32 experimentVariantsCount;

	/// <summary>
	/// (Optional) The files on this profile.
	/// </summary>
	_Maybenull_ TMap<const FString, TSharedPtr<const FPFProfilesEntityProfileFileMetadata>> files;

	/// <summary>
	/// Count of files
	/// </summary>
	uint32 filesCount;

	/// <summary>
	/// (Optional) The language on this profile.
	/// </summary>
	_Maybenull_ const FString language;

	/// <summary>
	/// (Optional) The lineage of this profile.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityLineage> lineage;

	/// <summary>
	/// (Optional) The objects on this profile.
	/// </summary>
	_Maybenull_ TMap<const FString, TSharedPtr<const FPFProfilesEntityDataObject>> objects;

	/// <summary>
	/// Count of objects
	/// </summary>
	uint32 objectsCount;

	/// <summary>
	/// (Optional) The permissions that govern access to this entity profile and its properties. Only includes
	/// permissions set on this profile, not global statements from titles and namespaces.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFProfilesEntityPermissionStatement>> permissions;

	/// <summary>
	/// Count of permissions
	/// </summary>
	uint32 permissionsCount;

	/// <summary>
	/// (Optional) The statistics on this profile.
	/// </summary>
	_Maybenull_ TMap<const FString, TSharedPtr<const FPFEntityStatisticValue>> statistics;

	/// <summary>
	/// Count of statistics
	/// </summary>
	uint32 statisticsCount;

	/// <summary>
	/// The version number of the profile in persistent storage at the time of the read. Used for optional
	/// optimistic concurrency during update.
	/// </summary>
	int32 versionNumber;
};

/// <summary>
/// FPFProfilesGetEntityProfileResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFProfilesGetEntityProfileResponse
{
	/// <summary>
	/// (Optional) Entity profile.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFProfilesEntityProfileBody> profile;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFProfilesGetEntityProfilesRequest data model. Given a set of entity types and entity identifiers
/// will retrieve all readable profiles properties for the caller. Profiles that the caller is not allowed
/// to read will silently not be included in the results.
/// </summary>
struct PLAYFABSERVICES_API FPFProfilesGetEntityProfilesRequest
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
	/// (Optional) Determines whether the objects will be returned as an escaped JSON string or as a un-escaped
	/// JSON object. Default is JSON string.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> dataAsObject;

	/// <summary>
	/// Entity keys of the profiles to load. Must be between 1 and 25.
	/// </summary>
	TArray<TSharedPtr<const FPFEntityKey>> entities;

	/// <summary>
	/// Count of entities
	/// </summary>
	uint32 entitiesCount;
};

/// <summary>
/// FPFProfilesGetEntityProfilesResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFProfilesGetEntityProfilesResponse
{
	/// <summary>
	/// (Optional) Entity profiles.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFProfilesEntityProfileBody>> profiles;

	/// <summary>
	/// Count of profiles
	/// </summary>
	uint32 profilesCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFProfilesGetTitlePlayersFromMasterPlayerAccountIdsRequest data model. Given a master player account
/// id (PlayFab ID), returns all title player accounts associated with it.
/// </summary>
struct PLAYFABSERVICES_API FPFProfilesGetTitlePlayersFromMasterPlayerAccountIdsRequest
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
	/// Master player account ids.
	/// </summary>
	const TArray<FString> masterPlayerAccountIds;

	/// <summary>
	/// Count of masterPlayerAccountIds
	/// </summary>
	uint32 masterPlayerAccountIdsCount;

	/// <summary>
	/// (Optional) Id of title to get players from.
	/// </summary>
	_Maybenull_ const FString titleId;
};

/// <summary>
/// FPFProfilesGetTitlePlayersFromMasterPlayerAccountIdsResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFProfilesGetTitlePlayersFromMasterPlayerAccountIdsResponse
{
	/// <summary>
	/// (Optional) Optional id of title to get players from, required if calling using a master_player_account.
	/// </summary>
	_Maybenull_ const FString titleId;

	/// <summary>
	/// (Optional) Dictionary of master player ids mapped to title player entity keys and id pairs.
	/// </summary>
	_Maybenull_ TMap<const FString, TSharedPtr<const FPFEntityKey>> titlePlayerAccounts;

	/// <summary>
	/// Count of titlePlayerAccounts
	/// </summary>
	uint32 titlePlayerAccountsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFProfilesSetProfileLanguageRequest data model. Given an entity profile, will update its language
/// to the one passed in if the profile's version is equal to the one passed in.
/// </summary>
struct PLAYFABSERVICES_API FPFProfilesSetProfileLanguageRequest
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
	/// (Optional) The optional entity to perform this action on. Defaults to the currently logged in entity.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) The expected version of a profile to perform this update on.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> expectedVersion;

	/// <summary>
	/// (Optional) The language to set on the given entity. Deletes the profile's language if passed in
	/// a null string.
	/// </summary>
	_Maybenull_ const FString language;
};

/// <summary>
/// FPFProfilesSetProfileLanguageResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFProfilesSetProfileLanguageResponse
{
	/// <summary>
	/// (Optional) The type of operation that occured on the profile's language.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFOperationTypes> operationResult;

	/// <summary>
	/// (Optional) The updated version of the profile after the language update.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> versionNumber;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFProfilesSetEntityProfilePolicyRequest data model. This will set the access policy statements on
/// the given entity profile. This is not additive, any existing statements will be replaced with the
/// statements in this request.
/// </summary>
struct PLAYFABSERVICES_API FPFProfilesSetEntityProfilePolicyRequest
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
	/// The entity to perform this action on.
	/// </summary>
	TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// The statements to include in the access policy.
	/// </summary>
	TArray<TSharedPtr<const FPFProfilesEntityPermissionStatement>> statements;

	/// <summary>
	/// Count of statements
	/// </summary>
	uint32 statementsCount;
};

/// <summary>
/// FPFProfilesSetEntityProfilePolicyResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFProfilesSetEntityProfilePolicyResponse
{
	/// <summary>
	/// (Optional) The permissions that govern access to this entity profile and its properties. Only includes
	/// permissions set on this profile, not global statements from titles and namespaces.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFProfilesEntityPermissionStatement>> permissions;

	/// <summary>
	/// Count of permissions
	/// </summary>
	uint32 permissionsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

// Delegates Declarations

DECLARE_DELEGATE_TwoParams(FOnGetProfileCompleted, const FPFProfilesGetEntityProfileResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnGetProfilesCompleted, const FPFProfilesGetEntityProfilesResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnGetTitlePlayersFromMasterPlayerAccountIdsCompleted, const FPFProfilesGetTitlePlayersFromMasterPlayerAccountIdsResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnSetProfileLanguageCompleted, const FPFProfilesSetProfileLanguageResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnSetProfilePolicyCompleted, const FPFProfilesSetEntityProfilePolicyResponse&, bool);

#pragma pop_macro("IN")