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
/// ModerationStatus enum.
/// </summary>
enum class FPFCatalogModerationStatus : uint32
{
	Unknown,
	AwaitingModeration,
	Approved,
	Rejected
};

/// <summary>
/// DisplayPropertyType enum.
/// </summary>
enum class FPFCatalogDisplayPropertyType : uint32
{
	None,
	QueryDateTime,
	QueryDouble,
	QueryString,
	SearchString
};

/// <summary>
/// PublishResult enum.
/// </summary>
enum class FPFCatalogPublishResult : uint32
{
	Unknown,
	Pending,
	Succeeded,
	Failed,
	Canceled
};

/// <summary>
/// ConcernCategory enum.
/// </summary>
enum class FPFCatalogConcernCategory : uint32
{
	None,
	OffensiveContent,
	ChildExploitation,
	MalwareOrVirus,
	PrivacyConcerns,
	MisleadingApp,
	PoorPerformance,
	ReviewResponse,
	SpamAdvertising,
	Profanity
};

/// <summary>
/// HelpfulnessVote enum.
/// </summary>
enum class FPFCatalogHelpfulnessVote : uint32
{
	None,
	UnHelpful,
	Helpful
};

/// <summary>
/// FPFCatalogCatalogAlternateId data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogCatalogAlternateId
{
	/// <summary>
	/// (Optional) Type of the alternate ID.
	/// </summary>
	_Maybenull_ const FString type;

	/// <summary>
	/// (Optional) Value of the alternate ID.
	/// </summary>
	_Maybenull_ const FString value;
};

/// <summary>
/// FPFCatalogContent data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogContent
{
	/// <summary>
	/// (Optional) The content unique ID.
	/// </summary>
	_Maybenull_ const FString id;

	/// <summary>
	/// (Optional) The maximum client version that this content is compatible with. Client Versions can
	/// be up to 3 segments separated by periods(.) and each segment can have a maximum value of 65535.
	/// </summary>
	_Maybenull_ const FString maxClientVersion;

	/// <summary>
	/// (Optional) The minimum client version that this content is compatible with. Client Versions can
	/// be up to 3 segments separated by periods(.) and each segment can have a maximum value of 65535.
	/// </summary>
	_Maybenull_ const FString minClientVersion;

	/// <summary>
	/// (Optional) The list of tags that are associated with this content. Tags must be defined in the Catalog
	/// Config before being used in content.
	/// </summary>
	_Maybenull_ const TArray<FString> tags;

	/// <summary>
	/// Count of tags
	/// </summary>
	uint32 tagsCount;

	/// <summary>
	/// (Optional) The client-defined type of the content. Content Types must be defined in the Catalog
	/// Config before being used.
	/// </summary>
	_Maybenull_ const FString type;

	/// <summary>
	/// (Optional) The Azure CDN URL for retrieval of the catalog item binary content.
	/// </summary>
	_Maybenull_ const FString url;
};

/// <summary>
/// FPFCatalogDeepLink data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogDeepLink
{
	/// <summary>
	/// (Optional) Target platform for this deep link.
	/// </summary>
	_Maybenull_ const FString platform;

	/// <summary>
	/// (Optional) The deep link for this platform.
	/// </summary>
	_Maybenull_ const FString url;
};

/// <summary>
/// FPFCatalogImage data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogImage
{
	/// <summary>
	/// (Optional) The image unique ID.
	/// </summary>
	_Maybenull_ const FString id;

	/// <summary>
	/// (Optional) The client-defined tag associated with this image. Tags must be defined in the Catalog
	/// Config before being used in images.
	/// </summary>
	_Maybenull_ const FString tag;

	/// <summary>
	/// (Optional) Images can be defined as either a "thumbnail" or "screenshot". There can only be one
	/// "thumbnail" image per item.
	/// </summary>
	_Maybenull_ const FString type;

	/// <summary>
	/// (Optional) The URL for retrieval of the image.
	/// </summary>
	_Maybenull_ const FString url;
};

/// <summary>
/// FPFCatalogCatalogPriceAmount data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogCatalogPriceAmount
{
	/// <summary>
	/// The amount of the price.
	/// </summary>
	int32 amount;

	/// <summary>
	/// (Optional) The Item Id of the price.
	/// </summary>
	_Maybenull_ const FString itemId;
};

/// <summary>
/// FPFCatalogCatalogPrice data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogCatalogPrice
{
	/// <summary>
	/// (Optional) The amounts of the catalog item price. Each price can have up to 15 item amounts.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFCatalogCatalogPriceAmount>> amounts;

	/// <summary>
	/// Count of amounts
	/// </summary>
	uint32 amountsCount;

	/// <summary>
	/// (Optional) The per-unit amount this price can be used to purchase.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> unitAmount;

	/// <summary>
	/// (Optional) The per-unit duration this price can be used to purchase. The maximum duration is 100
	/// years.
	/// </summary>
	_Maybenull_ TSharedPtr<const double> unitDurationInSeconds;
};

/// <summary>
/// FPFCatalogCatalogPriceOptions data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogCatalogPriceOptions
{
	/// <summary>
	/// (Optional) Prices of the catalog item. An item can have up to 15 prices.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFCatalogCatalogPrice>> prices;

	/// <summary>
	/// Count of prices
	/// </summary>
	uint32 pricesCount;
};

/// <summary>
/// FPFCatalogCatalogItemReference data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogCatalogItemReference
{
	/// <summary>
	/// (Optional) The amount of the catalog item.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> amount;

	/// <summary>
	/// (Optional) The unique ID of the catalog item.
	/// </summary>
	_Maybenull_ const FString id;

	/// <summary>
	/// (Optional) The prices the catalog item can be purchased for.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogCatalogPriceOptions> priceOptions;
};

/// <summary>
/// FPFCatalogKeywordSet data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogKeywordSet
{
	/// <summary>
	/// (Optional) A list of localized keywords.
	/// </summary>
	_Maybenull_ const TArray<FString> values;

	/// <summary>
	/// Count of values
	/// </summary>
	uint32 valuesCount;
};

/// <summary>
/// FPFCatalogModerationState data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogModerationState
{
	/// <summary>
	/// (Optional) The date and time this moderation state was last updated.
	/// </summary>
	_Maybenull_ TSharedPtr<const FDateTime> lastModifiedDate;

	/// <summary>
	/// (Optional) The current stated reason for the associated item being moderated.
	/// </summary>
	_Maybenull_ const FString reason;

	/// <summary>
	/// (Optional) The current moderation status for the associated item.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogModerationStatus> status;
};

/// <summary>
/// FPFCatalogRating data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogRating
{
	/// <summary>
	/// (Optional) The average rating for this item.
	/// </summary>
	_Maybenull_ TSharedPtr<const float> average;

	/// <summary>
	/// (Optional) The total count of 1 star ratings for this item.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> count1Star;

	/// <summary>
	/// (Optional) The total count of 2 star ratings for this item.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> count2Star;

	/// <summary>
	/// (Optional) The total count of 3 star ratings for this item.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> count3Star;

	/// <summary>
	/// (Optional) The total count of 4 star ratings for this item.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> count4Star;

	/// <summary>
	/// (Optional) The total count of 5 star ratings for this item.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> count5Star;

	/// <summary>
	/// (Optional) The total count of ratings for this item.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> totalCount;
};

/// <summary>
/// FPFCatalogRealMoneyPriceDetails data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogRealMoneyPriceDetails
{
	/// <summary>
	/// (Optional) The 'AppleAppStore' price amount per CurrencyCode. 'USD' supported only.
	/// </summary>
	_Maybenull_ TMap<const FString, int32> appleAppStorePrices;

	/// <summary>
	/// Count of appleAppStorePrices
	/// </summary>
	uint32 appleAppStorePricesCount;

	/// <summary>
	/// (Optional) The 'GooglePlay' price amount per CurrencyCode. 'USD' supported only.
	/// </summary>
	_Maybenull_ TMap<const FString, int32> googlePlayPrices;

	/// <summary>
	/// Count of googlePlayPrices
	/// </summary>
	uint32 googlePlayPricesCount;

	/// <summary>
	/// (Optional) The 'MicrosoftStore' price amount per CurrencyCode. 'USD' supported only.
	/// </summary>
	_Maybenull_ TMap<const FString, int32> microsoftStorePrices;

	/// <summary>
	/// Count of microsoftStorePrices
	/// </summary>
	uint32 microsoftStorePricesCount;

	/// <summary>
	/// (Optional) The 'NintendoEShop' price amount per CurrencyCode. 'USD' supported only.
	/// </summary>
	_Maybenull_ TMap<const FString, int32> nintendoEShopPrices;

	/// <summary>
	/// Count of nintendoEShopPrices
	/// </summary>
	uint32 nintendoEShopPricesCount;

	/// <summary>
	/// (Optional) The 'PlayStationStore' price amount per CurrencyCode. 'USD' supported only.
	/// </summary>
	_Maybenull_ TMap<const FString, int32> playStationStorePrices;

	/// <summary>
	/// Count of playStationStorePrices
	/// </summary>
	uint32 playStationStorePricesCount;

	/// <summary>
	/// (Optional) The 'Steam' price amount per CurrencyCode. 'USD' supported only.
	/// </summary>
	_Maybenull_ TMap<const FString, int32> steamPrices;

	/// <summary>
	/// Count of steamPrices
	/// </summary>
	uint32 steamPricesCount;
};

/// <summary>
/// FPFCatalogFilterOptions data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogFilterOptions
{
	/// <summary>
	/// (Optional) The OData filter utilized. Mutually exclusive with 'IncludeAllItems'. More info about
	/// Filter Complexity limits can be found here: https://learn.microsoft.com/en-us/gaming/playfab/features/economy-v2/catalog/search#limits.
	/// </summary>
	_Maybenull_ const FString filter;

	/// <summary>
	/// (Optional) The flag that overrides the filter and allows for returning all catalog items. Mutually
	/// exclusive with 'Filter'.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> includeAllItems;
};

/// <summary>
/// FPFCatalogPermissions data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogPermissions
{
	/// <summary>
	/// (Optional) The list of ids of Segments that the a player can be in to purchase from the store. When
	/// a value is provided, the player must be in at least one of the segments listed for the purchase to
	/// be allowed.
	/// </summary>
	_Maybenull_ const TArray<FString> segmentIds;

	/// <summary>
	/// Count of segmentIds
	/// </summary>
	uint32 segmentIdsCount;
};

/// <summary>
/// FPFCatalogCatalogPriceAmountOverride data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogCatalogPriceAmountOverride
{
	/// <summary>
	/// (Optional) The exact value that should be utilized in the override.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> fixedValue;

	/// <summary>
	/// (Optional) The id of the item this override should utilize.
	/// </summary>
	_Maybenull_ const FString itemId;

	/// <summary>
	/// (Optional) The multiplier that will be applied to the base Catalog value to determine what value
	/// should be utilized in the override.
	/// </summary>
	_Maybenull_ TSharedPtr<const double> multiplier;
};

/// <summary>
/// FPFCatalogCatalogPriceOverride data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogCatalogPriceOverride
{
	/// <summary>
	/// (Optional) The currency amounts utilized in the override for a singular price.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFCatalogCatalogPriceAmountOverride>> amounts;

	/// <summary>
	/// Count of amounts
	/// </summary>
	uint32 amountsCount;
};

/// <summary>
/// FPFCatalogCatalogPriceOptionsOverride data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogCatalogPriceOptionsOverride
{
	/// <summary>
	/// (Optional) The prices utilized in the override.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFCatalogCatalogPriceOverride>> prices;

	/// <summary>
	/// Count of prices
	/// </summary>
	uint32 pricesCount;
};

/// <summary>
/// FPFCatalogStoreDetails data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogStoreDetails
{
	/// <summary>
	/// (Optional) The options for the filter in filter-based stores. These options are mutually exclusive
	/// with item references.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogFilterOptions> filterOptions;

	/// <summary>
	/// (Optional) The permissions that control which players can purchase from the store.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogPermissions> permissions;

	/// <summary>
	/// (Optional) The global prices utilized in the store. These options are mutually exclusive with price
	/// options in item references.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogCatalogPriceOptionsOverride> priceOptionsOverride;
};

/// <summary>
/// FPFCatalogCatalogItem data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogCatalogItem
{
	/// <summary>
	/// (Optional) The alternate IDs associated with this item. An alternate ID can be set to 'FriendlyId'
	/// or any of the supported marketplace names.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFCatalogCatalogAlternateId>> alternateIds;

	/// <summary>
	/// Count of alternateIds
	/// </summary>
	uint32 alternateIdsCount;

	/// <summary>
	/// (Optional) The set of content/files associated with this item. Up to 100 files can be added to an
	/// item.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFCatalogContent>> contents;

	/// <summary>
	/// Count of contents
	/// </summary>
	uint32 contentsCount;

	/// <summary>
	/// (Optional) The client-defined type of the item.
	/// </summary>
	_Maybenull_ const FString contentType;

	/// <summary>
	/// (Optional) The date and time when this item was created.
	/// </summary>
	_Maybenull_ TSharedPtr<const FDateTime> creationDate;

	/// <summary>
	/// (Optional) The ID of the creator of this catalog item.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> creatorEntity;

	/// <summary>
	/// (Optional) The set of platform specific deep links for this item.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFCatalogDeepLink>> deepLinks;

	/// <summary>
	/// Count of deepLinks
	/// </summary>
	uint32 deepLinksCount;

	/// <summary>
	/// (Optional) The Stack Id that will be used as default for this item in Inventory when an explicit
	/// one is not provided. This DefaultStackId can be a static stack id or '{guid}', which will generate
	/// a unique stack id for the item. If null, Inventory's default stack id will be used.
	/// </summary>
	_Maybenull_ const FString defaultStackId;

	/// <summary>
	/// (Optional) A dictionary of localized descriptions. Key is language code and localized string is
	/// the value. The NEUTRAL locale is required. Descriptions have a 10000 character limit per country
	/// code.
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> description;

	/// <summary>
	/// Count of description
	/// </summary>
	uint32 descriptionCount;

	/// <summary>
	/// (Optional) Game specific properties for display purposes. This is an arbitrary JSON blob. The Display
	/// Properties field has a 10000 byte limit per item.
	/// </summary>
	FPFJsonObject displayProperties;

	/// <summary>
	/// (Optional) The user provided version of the item for display purposes. Maximum character length
	/// of 50.
	/// </summary>
	_Maybenull_ const FString displayVersion;

	/// <summary>
	/// (Optional) The date of when the item will cease to be available. If not provided then the product
	/// will be available indefinitely.
	/// </summary>
	_Maybenull_ TSharedPtr<const FDateTime> endDate;

	/// <summary>
	/// (Optional) The current ETag value that can be used for optimistic concurrency in the If-None-Match
	/// header.
	/// </summary>
	_Maybenull_ const FString eTag;

	/// <summary>
	/// (Optional) The unique ID of the item.
	/// </summary>
	_Maybenull_ const FString id;

	/// <summary>
	/// (Optional) The images associated with this item. Images can be thumbnails or screenshots. Up to
	/// 100 images can be added to an item. Only .png, .jpg, .gif, and .bmp file types can be uploaded.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFCatalogImage>> images;

	/// <summary>
	/// Count of images
	/// </summary>
	uint32 imagesCount;

	/// <summary>
	/// (Optional) Indicates if the item is hidden.
	/// </summary>
	_Maybenull_ TSharedPtr<const bool> isHidden;

	/// <summary>
	/// (Optional) The item references associated with this item. For example, the items in a Bundle/Store/Subscription.
	/// Every item can have up to 50 item references.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFCatalogCatalogItemReference>> itemReferences;

	/// <summary>
	/// Count of itemReferences
	/// </summary>
	uint32 itemReferencesCount;

	/// <summary>
	/// (Optional) A dictionary of localized keywords. Key is language code and localized list of keywords
	/// is the value. Keywords have a 50 character limit per keyword and up to 32 keywords can be added per
	/// country code.
	/// </summary>
	_Maybenull_ TMap<const FString, TSharedPtr<const FPFCatalogKeywordSet>> keywords;

	/// <summary>
	/// Count of keywords
	/// </summary>
	uint32 keywordsCount;

	/// <summary>
	/// (Optional) The date and time this item was last updated.
	/// </summary>
	_Maybenull_ TSharedPtr<const FDateTime> lastModifiedDate;

	/// <summary>
	/// (Optional) The moderation state for this item.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogModerationState> moderation;

	/// <summary>
	/// (Optional) The platforms supported by this item.
	/// </summary>
	_Maybenull_ const TArray<FString> platforms;

	/// <summary>
	/// Count of platforms
	/// </summary>
	uint32 platformsCount;

	/// <summary>
	/// (Optional) The prices the item can be purchased for.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogCatalogPriceOptions> priceOptions;

	/// <summary>
	/// (Optional) Rating summary for this item.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogRating> rating;

	/// <summary>
	/// (Optional) The real price the item was purchased for per marketplace.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogRealMoneyPriceDetails> realMoneyPriceDetails;

	/// <summary>
	/// (Optional) The date of when the item will be available. If not provided then the product will appear
	/// immediately.
	/// </summary>
	_Maybenull_ TSharedPtr<const FDateTime> startDate;

	/// <summary>
	/// (Optional) Optional details for stores items.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogStoreDetails> storeDetails;

	/// <summary>
	/// (Optional) The list of tags that are associated with this item. Up to 32 tags can be added to an
	/// item.
	/// </summary>
	_Maybenull_ const TArray<FString> tags;

	/// <summary>
	/// Count of tags
	/// </summary>
	uint32 tagsCount;

	/// <summary>
	/// (Optional) A dictionary of localized titles. Key is language code and localized string is the value.
	/// The NEUTRAL locale is required. Titles have a 512 character limit per country code.
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> title;

	/// <summary>
	/// Count of title
	/// </summary>
	uint32 titleCount;

	/// <summary>
	/// (Optional) The high-level type of the item. The following item types are supported: bundle, catalogItem,
	/// currency, store, ugc, subscription.
	/// </summary>
	_Maybenull_ const FString type;
};

/// <summary>
/// FPFCatalogCreateDraftItemRequest data model. The item will not be published to the public catalog
/// until the PublishItem API is called for the item.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogCreateDraftItemRequest
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
	/// (Optional) Metadata describing the new catalog item to be created.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogCatalogItem> item;

	/// <summary>
	/// Whether the item should be published immediately. This value is optional, defaults to false.
	/// </summary>
	bool publish;
};

/// <summary>
/// FPFCatalogCreateDraftItemResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogCreateDraftItemResponse
{
	/// <summary>
	/// (Optional) Updated metadata describing the catalog item just created.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogCatalogItem> item;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFCatalogUploadInfo data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogUploadInfo
{
	/// <summary>
	/// (Optional) Name of the file to be uploaded.
	/// </summary>
	_Maybenull_ const FString fileName;
};

/// <summary>
/// FPFCatalogCreateUploadUrlsRequest data model. Upload URLs point to Azure Blobs; clients must follow
/// the Microsoft Azure Storage Blob Service REST API pattern for uploading content. The response contains
/// upload URLs and IDs for each file. The IDs and URLs returned must be added to the item metadata and
/// committed using the CreateDraftItem or UpdateDraftItem Item APIs.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogCreateUploadUrlsRequest
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
	/// (Optional) Description of the files to be uploaded by the client.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFCatalogUploadInfo>> files;

	/// <summary>
	/// Count of files
	/// </summary>
	uint32 filesCount;
};

/// <summary>
/// FPFCatalogUploadUrlMetadata data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogUploadUrlMetadata
{
	/// <summary>
	/// (Optional) Name of the file for which this upload URL was requested.
	/// </summary>
	_Maybenull_ const FString fileName;

	/// <summary>
	/// (Optional) Unique ID for the binary content to be uploaded to the target URL.
	/// </summary>
	_Maybenull_ const FString id;

	/// <summary>
	/// (Optional) URL for the binary content to be uploaded to.
	/// </summary>
	_Maybenull_ const FString url;
};

/// <summary>
/// FPFCatalogCreateUploadUrlsResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogCreateUploadUrlsResponse
{
	/// <summary>
	/// (Optional) List of URLs metadata for the files to be uploaded by the client.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFCatalogUploadUrlMetadata>> uploadUrls;

	/// <summary>
	/// Count of uploadUrls
	/// </summary>
	uint32 uploadUrlsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFCatalogDeleteEntityItemReviewsRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogDeleteEntityItemReviewsRequest
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
	/// (Optional) The entity to perform this action on.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;
};

/// <summary>
/// FPFCatalogDeleteItemRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogDeleteItemRequest
{
	/// <summary>
	/// (Optional) An alternate ID associated with this item.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogCatalogAlternateId> alternateId;

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
	/// (Optional) The entity to perform this action on.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) The unique ID of the item.
	/// </summary>
	_Maybenull_ const FString id;
};

/// <summary>
/// FPFCatalogGetCatalogConfigRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogGetCatalogConfigRequest
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
};

/// <summary>
/// FPFCatalogCatalogSpecificConfig data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogCatalogSpecificConfig
{
	/// <summary>
	/// (Optional) The set of content types that will be used for validation. Each content type can have
	/// a maximum character length of 40 and up to 128 types can be listed.
	/// </summary>
	_Maybenull_ const TArray<FString> contentTypes;

	/// <summary>
	/// Count of contentTypes
	/// </summary>
	uint32 contentTypesCount;

	/// <summary>
	/// (Optional) The set of tags that will be used for validation. Each tag can have a maximum character
	/// length of 32 and up to 1024 tags can be listed.
	/// </summary>
	_Maybenull_ const TArray<FString> tags;

	/// <summary>
	/// Count of tags
	/// </summary>
	uint32 tagsCount;
};

/// <summary>
/// FPFCatalogDeepLinkFormat data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogDeepLinkFormat
{
	/// <summary>
	/// (Optional) The format of the deep link to return. The format should contain '{id}' to represent
	/// where the item ID should be placed.
	/// </summary>
	_Maybenull_ const FString format;

	/// <summary>
	/// (Optional) The target platform for the deep link.
	/// </summary>
	_Maybenull_ const FString platform;
};

/// <summary>
/// FPFCatalogDisplayPropertyIndexInfo data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogDisplayPropertyIndexInfo
{
	/// <summary>
	/// (Optional) The property name in the 'DisplayProperties' property to be indexed.
	/// </summary>
	_Maybenull_ const FString name;

	/// <summary>
	/// (Optional) The type of the property to be indexed.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogDisplayPropertyType> type;
};

/// <summary>
/// FPFCatalogFileConfig data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogFileConfig
{
	/// <summary>
	/// (Optional) The set of content types that will be used for validation. Each content type can have
	/// a maximum character length of 40 and up to 128 types can be listed.
	/// </summary>
	_Maybenull_ const TArray<FString> contentTypes;

	/// <summary>
	/// Count of contentTypes
	/// </summary>
	uint32 contentTypesCount;

	/// <summary>
	/// (Optional) The set of tags that will be used for validation. Each tag can have a maximum character
	/// length of 32 and up to 1024 tags can be listed.
	/// </summary>
	_Maybenull_ const TArray<FString> tags;

	/// <summary>
	/// Count of tags
	/// </summary>
	uint32 tagsCount;
};

/// <summary>
/// FPFCatalogImageConfig data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogImageConfig
{
	/// <summary>
	/// (Optional) The set of tags that will be used for validation. Each tag can have a maximum character
	/// length of 32 and up to 1024 tags can be listed.
	/// </summary>
	_Maybenull_ const TArray<FString> tags;

	/// <summary>
	/// Count of tags
	/// </summary>
	uint32 tagsCount;
};

/// <summary>
/// FPFCatalogCategoryRatingConfig data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogCategoryRatingConfig
{
	/// <summary>
	/// (Optional) Name of the category.
	/// </summary>
	_Maybenull_ const FString name;
};

/// <summary>
/// FPFCatalogReviewConfig data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogReviewConfig
{
	/// <summary>
	/// (Optional) A set of categories that can be applied toward ratings and reviews.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFCatalogCategoryRatingConfig>> categoryRatings;

	/// <summary>
	/// Count of categoryRatings
	/// </summary>
	uint32 categoryRatingsCount;
};

/// <summary>
/// FPFCatalogUserGeneratedContentSpecificConfig data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogUserGeneratedContentSpecificConfig
{
	/// <summary>
	/// (Optional) The set of content types that will be used for validation.
	/// </summary>
	_Maybenull_ const TArray<FString> contentTypes;

	/// <summary>
	/// Count of contentTypes
	/// </summary>
	uint32 contentTypesCount;

	/// <summary>
	/// (Optional) The set of tags that will be used for validation.
	/// </summary>
	_Maybenull_ const TArray<FString> tags;

	/// <summary>
	/// Count of tags
	/// </summary>
	uint32 tagsCount;
};

/// <summary>
/// FPFCatalogCatalogConfig data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogCatalogConfig
{
	/// <summary>
	/// (Optional) A list of player entity keys that will have admin permissions. There is a maximum of
	/// 64 entities that can be added.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFEntityKey>> adminEntities;

	/// <summary>
	/// Count of adminEntities
	/// </summary>
	uint32 adminEntitiesCount;

	/// <summary>
	/// (Optional) The set of configuration that only applies to catalog items.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogCatalogSpecificConfig> catalog;

	/// <summary>
	/// (Optional) A list of deep link formats. Up to 10 can be added.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFCatalogDeepLinkFormat>> deepLinkFormats;

	/// <summary>
	/// Count of deepLinkFormats
	/// </summary>
	uint32 deepLinkFormatsCount;

	/// <summary>
	/// (Optional) A list of display properties to index. Up to 5 mappings can be added per Display Property
	/// Type. More info on display properties can be found here: https://learn.microsoft.com/en-us/gaming/playfab/features/economy-v2/catalog/content-types-tags-and-properties#displayproperties.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFCatalogDisplayPropertyIndexInfo>> displayPropertyIndexInfos;

	/// <summary>
	/// Count of displayPropertyIndexInfos
	/// </summary>
	uint32 displayPropertyIndexInfosCount;

	/// <summary>
	/// (Optional) The set of configuration that only applies to Files.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogFileConfig> file;

	/// <summary>
	/// (Optional) The set of configuration that only applies to Images.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogImageConfig> image;

	/// <summary>
	/// Flag defining whether catalog is enabled.
	/// </summary>
	bool isCatalogEnabled;

	/// <summary>
	/// (Optional) A list of Platforms that can be applied to catalog items. Each platform can have a maximum
	/// character length of 40 and up to 128 platforms can be listed.
	/// </summary>
	_Maybenull_ const TArray<FString> platforms;

	/// <summary>
	/// Count of platforms
	/// </summary>
	uint32 platformsCount;

	/// <summary>
	/// (Optional) The set of configuration that only applies to Ratings and Reviews.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogReviewConfig> review;

	/// <summary>
	/// (Optional) A set of player entity keys that are allowed to review content. There is a maximum of
	/// 128 entities that can be added.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFEntityKey>> reviewerEntities;

	/// <summary>
	/// Count of reviewerEntities
	/// </summary>
	uint32 reviewerEntitiesCount;

	/// <summary>
	/// (Optional) The set of configuration that only applies to user generated contents.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogUserGeneratedContentSpecificConfig> userGeneratedContent;
};

/// <summary>
/// FPFCatalogGetCatalogConfigResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogGetCatalogConfigResponse
{
	/// <summary>
	/// (Optional) The catalog configuration.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogCatalogConfig> config;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFCatalogGetDraftItemRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogGetDraftItemRequest
{
	/// <summary>
	/// (Optional) An alternate ID associated with this item.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogCatalogAlternateId> alternateId;

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
	/// (Optional) The entity to perform this action on.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) The unique ID of the item.
	/// </summary>
	_Maybenull_ const FString id;
};

/// <summary>
/// FPFCatalogGetDraftItemResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogGetDraftItemResponse
{
	/// <summary>
	/// (Optional) Full metadata of the catalog item requested.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogCatalogItem> item;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFCatalogGetDraftItemsRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogGetDraftItemsRequest
{
	/// <summary>
	/// (Optional) List of item alternate IDs.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFCatalogCatalogAlternateId>> alternateIds;

	/// <summary>
	/// Count of alternateIds
	/// </summary>
	uint32 alternateIdsCount;

	/// <summary>
	/// (Optional) An opaque token used to retrieve the next page of items created by the caller, if any
	/// are available. Should be null on initial request.
	/// </summary>
	_Maybenull_ const FString continuationToken;

	/// <summary>
	/// (Optional) Number of items to retrieve. This value is optional. Default value is 10.
	/// </summary>
	_Maybenull_ TSharedPtr<const int32> count;

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
	/// (Optional) The entity to perform this action on.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) List of Item Ids.
	/// </summary>
	_Maybenull_ const TArray<FString> ids;

	/// <summary>
	/// Count of ids
	/// </summary>
	uint32 idsCount;
};

/// <summary>
/// FPFCatalogGetDraftItemsResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogGetDraftItemsResponse
{
	/// <summary>
	/// (Optional) An opaque token used to retrieve the next page of items, if any are available.
	/// </summary>
	_Maybenull_ const FString continuationToken;

	/// <summary>
	/// (Optional) A set of items created by the entity.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFCatalogCatalogItem>> items;

	/// <summary>
	/// Count of items
	/// </summary>
	uint32 itemsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFCatalogGetEntityDraftItemsRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogGetEntityDraftItemsRequest
{
	/// <summary>
	/// (Optional) An opaque token used to retrieve the next page of items created by the caller, if any
	/// are available. Should be null on initial request.
	/// </summary>
	_Maybenull_ const FString continuationToken;

	/// <summary>
	/// Number of items to retrieve. This value is optional. Default value is 10.
	/// </summary>
	int32 count;

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
	/// (Optional) The entity to perform this action on.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) OData Filter to refine the items returned. CatalogItem properties 'type' can be used
	/// in the filter. For example: "type eq 'ugc'".
	/// </summary>
	_Maybenull_ const FString filter;
};

/// <summary>
/// FPFCatalogGetEntityDraftItemsResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogGetEntityDraftItemsResponse
{
	/// <summary>
	/// (Optional) An opaque token used to retrieve the next page of items, if any are available.
	/// </summary>
	_Maybenull_ const FString continuationToken;

	/// <summary>
	/// (Optional) A set of items created by the entity.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFCatalogCatalogItem>> items;

	/// <summary>
	/// Count of items
	/// </summary>
	uint32 itemsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFCatalogGetEntityItemReviewRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogGetEntityItemReviewRequest
{
	/// <summary>
	/// (Optional) An alternate ID associated with this item.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogCatalogAlternateId> alternateId;

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
	/// (Optional) The entity to perform this action on.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) The unique ID of the item.
	/// </summary>
	_Maybenull_ const FString id;
};

/// <summary>
/// FPFCatalogReview data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogReview
{
	/// <summary>
	/// (Optional) The star rating associated with each selected category in this review.
	/// </summary>
	_Maybenull_ TMap<const FString, int32> categoryRatings;

	/// <summary>
	/// Count of categoryRatings
	/// </summary>
	uint32 categoryRatingsCount;

	/// <summary>
	/// The number of negative helpfulness votes for this review.
	/// </summary>
	int32 helpfulNegative;

	/// <summary>
	/// The number of positive helpfulness votes for this review.
	/// </summary>
	int32 helpfulPositive;

	/// <summary>
	/// Indicates whether the review author has the item installed.
	/// </summary>
	bool isInstalled;

	/// <summary>
	/// (Optional) The ID of the item being reviewed.
	/// </summary>
	_Maybenull_ const FString itemId;

	/// <summary>
	/// (Optional) The version of the item being reviewed.
	/// </summary>
	_Maybenull_ const FString itemVersion;

	/// <summary>
	/// (Optional) The locale for which this review was submitted in.
	/// </summary>
	_Maybenull_ const FString locale;

	/// <summary>
	/// Star rating associated with this review.
	/// </summary>
	int32 rating;

	/// <summary>
	/// (Optional) The ID of the author of the review.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> reviewerEntity;

	/// <summary>
	/// (Optional) The ID of the review.
	/// </summary>
	_Maybenull_ const FString reviewId;

	/// <summary>
	/// (Optional) The full text of this review.
	/// </summary>
	_Maybenull_ const FString reviewText;

	/// <summary>
	/// The date and time this review was last submitted.
	/// </summary>
	FDateTime submitted;

	/// <summary>
	/// (Optional) The title of this review.
	/// </summary>
	_Maybenull_ const FString title;
};

/// <summary>
/// FPFCatalogGetEntityItemReviewResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogGetEntityItemReviewResponse
{
	/// <summary>
	/// (Optional) The review the entity submitted for the requested item.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogReview> review;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFCatalogGetItemRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogGetItemRequest
{
	/// <summary>
	/// (Optional) An alternate ID associated with this item.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogCatalogAlternateId> alternateId;

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
	/// (Optional) The entity to perform this action on.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) The unique ID of the item.
	/// </summary>
	_Maybenull_ const FString id;
};

/// <summary>
/// FPFCatalogGetItemResponse data model. Get item result.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogGetItemResponse
{
	/// <summary>
	/// (Optional) The item result.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogCatalogItem> item;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFCatalogGetItemContainersRequest data model. Given an item, return a set of bundles and stores
/// containing the item.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogGetItemContainersRequest
{
	/// <summary>
	/// (Optional) An alternate ID associated with this item.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogCatalogAlternateId> alternateId;

	/// <summary>
	/// (Optional) An opaque token used to retrieve the next page of items in the inventory, if any are
	/// available. Should be null on initial request.
	/// </summary>
	_Maybenull_ const FString continuationToken;

	/// <summary>
	/// Number of items to retrieve. This value is optional. Default value is 10.
	/// </summary>
	int32 count;

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
	/// (Optional) The entity to perform this action on.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) The unique ID of the item.
	/// </summary>
	_Maybenull_ const FString id;
};

/// <summary>
/// FPFCatalogGetItemContainersResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogGetItemContainersResponse
{
	/// <summary>
	/// (Optional) List of Bundles and Stores containing the requested items.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFCatalogCatalogItem>> containers;

	/// <summary>
	/// Count of containers
	/// </summary>
	uint32 containersCount;

	/// <summary>
	/// (Optional) An opaque token used to retrieve the next page of items, if any are available.
	/// </summary>
	_Maybenull_ const FString continuationToken;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFCatalogGetItemModerationStateRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogGetItemModerationStateRequest
{
	/// <summary>
	/// (Optional) An alternate ID associated with this item.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogCatalogAlternateId> alternateId;

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
	/// (Optional) The unique ID of the item.
	/// </summary>
	_Maybenull_ const FString id;
};

/// <summary>
/// FPFCatalogGetItemModerationStateResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogGetItemModerationStateResponse
{
	/// <summary>
	/// (Optional) The current moderation state for the requested item.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogModerationState> state;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFCatalogGetItemPublishStatusRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogGetItemPublishStatusRequest
{
	/// <summary>
	/// (Optional) An alternate ID associated with this item.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogCatalogAlternateId> alternateId;

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
	/// (Optional) The entity to perform this action on.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) The unique ID of the item.
	/// </summary>
	_Maybenull_ const FString id;
};

/// <summary>
/// FPFCatalogGetItemPublishStatusResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogGetItemPublishStatusResponse
{
	/// <summary>
	/// (Optional) High level status of the published item.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogPublishResult> result;

	/// <summary>
	/// (Optional) Descriptive message about the current status of the publish.
	/// </summary>
	_Maybenull_ const FString statusMessage;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFCatalogGetItemReviewsRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogGetItemReviewsRequest
{
	/// <summary>
	/// (Optional) An alternate ID associated with this item.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogCatalogAlternateId> alternateId;

	/// <summary>
	/// (Optional) An opaque token used to retrieve the next page of items, if any are available.
	/// </summary>
	_Maybenull_ const FString continuationToken;

	/// <summary>
	/// Number of items to retrieve. This value is optional. Default value is 10.
	/// </summary>
	int32 count;

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
	/// (Optional) The unique ID of the item.
	/// </summary>
	_Maybenull_ const FString id;

	/// <summary>
	/// (Optional) An OData orderBy used to order the results of the query. Possible values are Helpfulness,
	/// Rating, and Submitted (For example: "Submitted desc").
	/// </summary>
	_Maybenull_ const FString orderBy;
};

/// <summary>
/// FPFCatalogGetItemReviewsResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogGetItemReviewsResponse
{
	/// <summary>
	/// (Optional) An opaque token used to retrieve the next page of items, if any are available.
	/// </summary>
	_Maybenull_ const FString continuationToken;

	/// <summary>
	/// (Optional) The paginated set of results.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFCatalogReview>> reviews;

	/// <summary>
	/// Count of reviews
	/// </summary>
	uint32 reviewsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFCatalogGetItemReviewSummaryRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogGetItemReviewSummaryRequest
{
	/// <summary>
	/// (Optional) An alternate ID associated with this item.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogCatalogAlternateId> alternateId;

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
	/// (Optional) The unique ID of the item.
	/// </summary>
	_Maybenull_ const FString id;
};

/// <summary>
/// FPFCatalogGetItemReviewSummaryResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogGetItemReviewSummaryResponse
{
	/// <summary>
	/// (Optional) The least favorable review for this item.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogReview> leastFavorableReview;

	/// <summary>
	/// (Optional) The most favorable review for this item.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogReview> mostFavorableReview;

	/// <summary>
	/// (Optional) The summary of ratings associated with this item.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogRating> rating;

	/// <summary>
	/// The total number of reviews associated with this item.
	/// </summary>
	int32 reviewsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFCatalogGetItemsRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogGetItemsRequest
{
	/// <summary>
	/// (Optional) List of item alternate IDs.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFCatalogCatalogAlternateId>> alternateIds;

	/// <summary>
	/// Count of alternateIds
	/// </summary>
	uint32 alternateIdsCount;

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
	/// (Optional) The entity to perform this action on.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) List of Item Ids.
	/// </summary>
	_Maybenull_ const TArray<FString> ids;

	/// <summary>
	/// Count of ids
	/// </summary>
	uint32 idsCount;
};

/// <summary>
/// FPFCatalogGetItemsResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogGetItemsResponse
{
	/// <summary>
	/// (Optional) Metadata of set of items.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFCatalogCatalogItem>> items;

	/// <summary>
	/// Count of items
	/// </summary>
	uint32 itemsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFCatalogPublishDraftItemRequest data model. The call kicks off a workflow to publish the item to
/// the public catalog. The Publish Status API should be used to monitor the publish job.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogPublishDraftItemRequest
{
	/// <summary>
	/// (Optional) An alternate ID associated with this item.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogCatalogAlternateId> alternateId;

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
	/// (Optional) The entity to perform this action on.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) ETag of the catalog item to published from the working catalog to the public catalog.
	/// Used for optimistic concurrency. If the provided ETag does not match the ETag in the current working
	/// catalog, the request will be rejected. If not provided, the current version of the document in the
	/// working catalog will be published.
	/// </summary>
	_Maybenull_ const FString eTag;

	/// <summary>
	/// (Optional) The unique ID of the item.
	/// </summary>
	_Maybenull_ const FString id;
};

/// <summary>
/// FPFCatalogReportItemRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogReportItemRequest
{
	/// <summary>
	/// (Optional) An alternate ID associated with this item.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogCatalogAlternateId> alternateId;

	/// <summary>
	/// (Optional) Category of concern for this report.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogConcernCategory> concernCategory;

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
	/// (Optional) The entity to perform this action on.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) The unique ID of the item.
	/// </summary>
	_Maybenull_ const FString id;

	/// <summary>
	/// (Optional) The string reason for this report.
	/// </summary>
	_Maybenull_ const FString reason;
};

/// <summary>
/// FPFCatalogReportItemReviewRequest data model. Submit a report for an inappropriate review, allowing
/// the submitting user to specify their concern.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogReportItemReviewRequest
{
	/// <summary>
	/// (Optional) An alternate ID of the item associated with the review.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogCatalogAlternateId> alternateId;

	/// <summary>
	/// (Optional) The reason this review is being reported.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogConcernCategory> concernCategory;

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
	/// (Optional) The entity to perform this action on.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) The string ID of the item associated with the review.
	/// </summary>
	_Maybenull_ const FString itemId;

	/// <summary>
	/// (Optional) The string reason for this report.
	/// </summary>
	_Maybenull_ const FString reason;

	/// <summary>
	/// (Optional) The ID of the review to submit a report for.
	/// </summary>
	_Maybenull_ const FString reviewId;
};

/// <summary>
/// FPFCatalogReviewItemRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogReviewItemRequest
{
	/// <summary>
	/// (Optional) An alternate ID associated with this item.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogCatalogAlternateId> alternateId;

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
	/// (Optional) The entity to perform this action on.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) The unique ID of the item.
	/// </summary>
	_Maybenull_ const FString id;

	/// <summary>
	/// (Optional) The review to submit.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogReview> review;
};

/// <summary>
/// FPFCatalogStoreReference data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogStoreReference
{
	/// <summary>
	/// (Optional) An alternate ID of the store.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogCatalogAlternateId> alternateId;

	/// <summary>
	/// (Optional) The unique ID of the store.
	/// </summary>
	_Maybenull_ const FString id;
};

/// <summary>
/// FPFCatalogSearchItemsRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogSearchItemsRequest
{
	/// <summary>
	/// (Optional) An opaque token used to retrieve the next page of items, if any are available.
	/// </summary>
	_Maybenull_ const FString continuationToken;

	/// <summary>
	/// Number of items to retrieve. This value is optional. Maximum page size is 50. Default value is 10.
	/// </summary>
	int32 count;

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
	/// (Optional) The entity to perform this action on.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) An OData filter used to refine the search query (For example: "type eq 'ugc'"). More
	/// info about Filter Complexity limits can be found here: https://learn.microsoft.com/en-us/gaming/playfab/features/economy-v2/catalog/search#limits.
	/// </summary>
	_Maybenull_ const FString filter;

	/// <summary>
	/// (Optional) The locale to be returned in the result.
	/// </summary>
	_Maybenull_ const FString language;

	/// <summary>
	/// (Optional) An OData orderBy used to order the results of the search query. For example: "rating/average
	/// asc" .
	/// </summary>
	_Maybenull_ const FString orderBy;

	/// <summary>
	/// (Optional) The text to search for.
	/// </summary>
	_Maybenull_ const FString search;

	/// <summary>
	/// (Optional) An OData select query option used to augment the search results. If not defined, the
	/// default search result metadata will be returned.
	/// </summary>
	_Maybenull_ const FString select;

	/// <summary>
	/// (Optional) The store to restrict the search request to.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogStoreReference> store;
};

/// <summary>
/// FPFCatalogSearchItemsResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogSearchItemsResponse
{
	/// <summary>
	/// (Optional) An opaque token used to retrieve the next page of items, if any are available.
	/// </summary>
	_Maybenull_ const FString continuationToken;

	/// <summary>
	/// (Optional) The paginated set of results for the search query.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFCatalogCatalogItem>> items;

	/// <summary>
	/// Count of items
	/// </summary>
	uint32 itemsCount;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

/// <summary>
/// FPFCatalogSetItemModerationStateRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogSetItemModerationStateRequest
{
	/// <summary>
	/// (Optional) An alternate ID associated with this item.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogCatalogAlternateId> alternateId;

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
	/// (Optional) The unique ID of the item.
	/// </summary>
	_Maybenull_ const FString id;

	/// <summary>
	/// (Optional) The reason for the moderation state change for the associated item.
	/// </summary>
	_Maybenull_ const FString reason;

	/// <summary>
	/// (Optional) The status to set for the associated item.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogModerationStatus> status;
};

/// <summary>
/// FPFCatalogSubmitItemReviewVoteRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogSubmitItemReviewVoteRequest
{
	/// <summary>
	/// (Optional) An alternate ID of the item associated with the review.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogCatalogAlternateId> alternateId;

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
	/// (Optional) The entity to perform this action on.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFEntityKey> entity;

	/// <summary>
	/// (Optional) The string ID of the item associated with the review.
	/// </summary>
	_Maybenull_ const FString itemId;

	/// <summary>
	/// (Optional) The ID of the review to submit a helpfulness vote for.
	/// </summary>
	_Maybenull_ const FString reviewId;

	/// <summary>
	/// (Optional) The helpfulness vote of the review.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogHelpfulnessVote> vote;
};

/// <summary>
/// FPFCatalogReviewTakedown data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogReviewTakedown
{
	/// <summary>
	/// (Optional) An alternate ID associated with this item.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogCatalogAlternateId> alternateId;

	/// <summary>
	/// (Optional) The ID of the item associated with the review to take down.
	/// </summary>
	_Maybenull_ const FString itemId;

	/// <summary>
	/// (Optional) The ID of the review to take down.
	/// </summary>
	_Maybenull_ const FString reviewId;
};

/// <summary>
/// FPFCatalogTakedownItemReviewsRequest data model. Submit a request to takedown one or more reviews,
/// removing them from public view. Authors will still be able to see their reviews after being taken
/// down.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogTakedownItemReviewsRequest
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
	/// (Optional) The set of reviews to take down.
	/// </summary>
	_Maybenull_ TArray<TSharedPtr<const FPFCatalogReviewTakedown>> reviews;

	/// <summary>
	/// Count of reviews
	/// </summary>
	uint32 reviewsCount;
};

/// <summary>
/// FPFCatalogUpdateCatalogConfigRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogUpdateCatalogConfigRequest
{
	/// <summary>
	/// (Optional) The updated catalog configuration.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogCatalogConfig> config;

	/// <summary>
	/// (Optional) The optional custom tags associated with the request (e.g. build number, external trace
	/// identifiers, etc.).
	/// </summary>
	_Maybenull_ TMap<const FString, const FString> customTags;

	/// <summary>
	/// Count of customTags
	/// </summary>
	uint32 customTagsCount;
};

/// <summary>
/// FPFCatalogUpdateDraftItemRequest data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogUpdateDraftItemRequest
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
	/// (Optional) Updated metadata describing the catalog item to be updated.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogCatalogItem> item;

	/// <summary>
	/// Whether the item should be published immediately. This value is optional, defaults to false.
	/// </summary>
	bool publish;
};

/// <summary>
/// FPFCatalogUpdateDraftItemResponse data model.
/// </summary>
struct PLAYFABSERVICES_API FPFCatalogUpdateDraftItemResponse
{
	/// <summary>
	/// (Optional) Updated metadata describing the catalog item just updated.
	/// </summary>
	_Maybenull_ TSharedPtr<const FPFCatalogCatalogItem> item;

	/// <summary>
	/// Error message, if any.
	/// </summary>
	FString ErrorMessage;
};

// Delegates Declarations

DECLARE_DELEGATE_TwoParams(FOnCreateDraftItemCompleted, const FPFCatalogCreateDraftItemResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnCreateUploadUrlsCompleted, const FPFCatalogCreateUploadUrlsResponse&, bool);

#if HC_PLATFORM == HC_PLATFORM_GDK
DECLARE_DELEGATE_TwoParams(FOnDeleteEntityItemReviewsCompleted, const FString&, bool);
#endif

DECLARE_DELEGATE_TwoParams(FOnDeleteItemCompleted, const FString&, bool);

#if HC_PLATFORM == HC_PLATFORM_GDK
DECLARE_DELEGATE_TwoParams(FOnGetCatalogConfigCompleted, const FPFCatalogGetCatalogConfigResponse&, bool);
#endif

DECLARE_DELEGATE_TwoParams(FOnGetDraftItemCompleted, const FPFCatalogGetDraftItemResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnGetDraftItemsCompleted, const FPFCatalogGetDraftItemsResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnGetEntityDraftItemsCompleted, const FPFCatalogGetEntityDraftItemsResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnGetEntityItemReviewCompleted, const FPFCatalogGetEntityItemReviewResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnGetItemCompleted, const FPFCatalogGetItemResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnGetItemContainersCompleted, const FPFCatalogGetItemContainersResponse&, bool);

#if HC_PLATFORM == HC_PLATFORM_GDK
DECLARE_DELEGATE_TwoParams(FOnGetItemModerationStateCompleted, const FPFCatalogGetItemModerationStateResponse&, bool);
#endif

DECLARE_DELEGATE_TwoParams(FOnGetItemPublishStatusCompleted, const FPFCatalogGetItemPublishStatusResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnGetItemReviewsCompleted, const FPFCatalogGetItemReviewsResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnGetItemReviewSummaryCompleted, const FPFCatalogGetItemReviewSummaryResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnGetItemsCompleted, const FPFCatalogGetItemsResponse&, bool);

DECLARE_DELEGATE_TwoParams(FOnPublishDraftItemCompleted, const FString&, bool);

DECLARE_DELEGATE_TwoParams(FOnReportItemCompleted, const FString&, bool);

DECLARE_DELEGATE_TwoParams(FOnReportItemReviewCompleted, const FString&, bool);

DECLARE_DELEGATE_TwoParams(FOnReviewItemCompleted, const FString&, bool);

DECLARE_DELEGATE_TwoParams(FOnSearchItemsCompleted, const FPFCatalogSearchItemsResponse&, bool);

#if HC_PLATFORM == HC_PLATFORM_GDK
DECLARE_DELEGATE_TwoParams(FOnSetItemModerationStateCompleted, const FString&, bool);
#endif

DECLARE_DELEGATE_TwoParams(FOnSubmitItemReviewVoteCompleted, const FString&, bool);

#if HC_PLATFORM == HC_PLATFORM_GDK
DECLARE_DELEGATE_TwoParams(FOnTakedownItemReviewsCompleted, const FString&, bool);
#endif

#if HC_PLATFORM == HC_PLATFORM_GDK
DECLARE_DELEGATE_TwoParams(FOnUpdateCatalogConfigCompleted, const FString&, bool);
#endif

DECLARE_DELEGATE_TwoParams(FOnUpdateDraftItemCompleted, const FPFCatalogUpdateDraftItemResponse&, bool);

#pragma pop_macro("IN")