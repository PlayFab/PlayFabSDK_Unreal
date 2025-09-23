// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if !defined(__cplusplus)
#error C++11 required
#endif

#pragma once

#include "CoreMinimal.h"
#include "XAsyncTaskManager.h"
#include "PFCatalogAsyncTasks.h"

THIRD_PARTY_INCLUDES_START
#include <playfab/services/PFServices.h>
THIRD_PARTY_INCLUDES_END

extern "C"
{
/// <summary>
/// Creates a new item in the working catalog using provided metadata. Note: SAS tokens provided are
/// valid for 1 hour.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// The item will not be published to the public catalog until the PublishItem API is called for the
/// item.
///
/// When the asynchronous task is complete, call <see cref="PFCatalogCreateDraftItemGetResultSize"/>
/// and <see cref="PFCatalogCreateDraftItemGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFCatalogCreateDraftItemAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogCreateDraftItemRequest* request,
	_Inout_ FOnCreateDraftItemCompleted delegate
) noexcept;

/// <summary>
/// Creates one or more upload URLs which can be used by the client to upload raw file data. Content
/// URls and uploaded content will be garbage collected after 24 hours if not attached to a draft or published
/// item. Detailed pricing info around uploading content can be found here: https://learn.microsoft.com/en-us/gaming/playfab/features/pricing/meters/catalog-meters
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Upload URLs point to Azure Blobs; clients must follow the Microsoft Azure Storage Blob Service REST
/// API pattern for uploading content. The response contains upload URLs and IDs for each file. The IDs
/// and URLs returned must be added to the item metadata and committed using the CreateDraftItem or UpdateDraftItem
/// Item APIs.
///
/// When the asynchronous task is complete, call <see cref="PFCatalogCreateUploadUrlsGetResultSize"/>
/// and <see cref="PFCatalogCreateUploadUrlsGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFCatalogCreateUploadUrlsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogCreateUploadUrlsRequest* request,
	_Inout_ FOnCreateUploadUrlsCompleted delegate
) noexcept;

/// <summary>
/// Deletes all reviews, helpfulness votes, and ratings submitted by the entity specified.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows.
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_PROFILE_DOES_NOT_EXIST or any of the global PlayFab Service errors.
/// See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFCatalogDeleteEntityItemReviewsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogDeleteEntityItemReviewsRequest* request,
	_Inout_ FOnDeleteEntityItemReviewsCompleted delegate
) noexcept;
#endif

/// <summary>
/// Removes an item from working catalog and all published versions from the public catalog.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_DATABASE_THROUGHPUT_EXCEEDED, E_PF_ITEM_NOT_FOUND or any of the global
/// PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
bool PLAYFABSERVICES_API FPFCatalogDeleteItemAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogDeleteItemRequest* request,
	_Inout_ FOnDeleteItemCompleted delegate
) noexcept;

/// <summary>
/// Gets the configuration for the catalog. Only Title Entities can call this API. There is a limit of
/// 100 requests in 10 seconds for this API. More information about the Catalog Config can be found here:
/// https://learn.microsoft.com/en-us/gaming/playfab/features/economy-v2/settings
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows.
/// When the asynchronous task is complete, call <see cref="PFCatalogGetCatalogConfigGetResultSize"/>
/// and <see cref="PFCatalogGetCatalogConfigGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFCatalogGetCatalogConfigAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogGetCatalogConfigRequest* request,
	_Inout_ FOnGetCatalogConfigCompleted delegate
) noexcept;
#endif

/// <summary>
/// Retrieves an item from the working catalog. This item represents the current working state of the
/// item. GetDraftItem does not work off a cache of the Catalog and should be used when trying to get
/// recent item updates. However, please note that item references data is cached and may take a few moments
/// for changes to propagate. Note: SAS tokens provided are valid for 1 hour.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFCatalogGetDraftItemGetResultSize"/> and
/// <see cref="PFCatalogGetDraftItemGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFCatalogGetDraftItemAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogGetDraftItemRequest* request,
	_Inout_ FOnGetDraftItemCompleted delegate
) noexcept;

/// <summary>
/// Retrieves a paginated list of the items from the draft catalog. Up to 50 IDs can be retrieved in
/// a single request. GetDraftItems does not work off a cache of the Catalog and should be used when trying
/// to get recent item updates. Note: SAS tokens provided are valid for 1 hour.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFCatalogGetDraftItemsGetResultSize"/> and
/// <see cref="PFCatalogGetDraftItemsGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFCatalogGetDraftItemsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogGetDraftItemsRequest* request,
	_Inout_ FOnGetDraftItemsCompleted delegate
) noexcept;

/// <summary>
/// Retrieves a paginated list of the items from the draft catalog created by the Entity. Up to 50 items
/// can be returned at once. You can use continuation tokens to paginate through results that return greater
/// than the limit. GetEntityDraftItems does not work off a cache of the Catalog and should be used when
/// trying to get recent item updates.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFCatalogGetEntityDraftItemsGetResultSize"/>
/// and <see cref="PFCatalogGetEntityDraftItemsGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFCatalogGetEntityDraftItemsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogGetEntityDraftItemsRequest* request,
	_Inout_ FOnGetEntityDraftItemsCompleted delegate
) noexcept;

/// <summary>
/// Gets the submitted review for the specified item by the authenticated entity. Individual ratings
/// and reviews data update in near real time with delays within a few seconds.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFCatalogGetEntityItemReviewGetResultSize"/>
/// and <see cref="PFCatalogGetEntityItemReviewGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFCatalogGetEntityItemReviewAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogGetEntityItemReviewRequest* request,
	_Inout_ FOnGetEntityItemReviewCompleted delegate
) noexcept;

/// <summary>
/// Retrieves an item from the public catalog. GetItem does not work off a cache of the Catalog and should
/// be used when trying to get recent item updates. However, please note that item references data is
/// cached and may take a few moments for changes to propagate.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFCatalogGetItemGetResultSize"/> and <see
/// cref="PFCatalogGetItemGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFCatalogGetItemAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogGetItemRequest* request,
	_Inout_ FOnGetItemCompleted delegate
) noexcept;

/// <summary>
/// Search for a given item and return a set of bundles and stores containing the item. Up to 50 items
/// can be returned at once. You can use continuation tokens to paginate through results that return greater
/// than the limit. This API is intended for tooling/automation scenarios and has a reduced RPS with Player
/// Entities limited to 30 requests in 300 seconds and Title Entities limited to 100 requests in 10 seconds.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Given an item, return a set of bundles and stores containing the item.
///
/// When the asynchronous task is complete, call <see cref="PFCatalogGetItemContainersGetResultSize"/>
/// and <see cref="PFCatalogGetItemContainersGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFCatalogGetItemContainersAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogGetItemContainersRequest* request,
	_Inout_ FOnGetItemContainersCompleted delegate
) noexcept;

/// <summary>
/// Gets the moderation state for an item, including the concern category and string reason. More information
/// about moderation states can be found here: https://learn.microsoft.com/en-us/gaming/playfab/features/economy-v2/ugc/moderation
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows.
/// When the asynchronous task is complete, call <see cref="PFCatalogGetItemModerationStateGetResultSize"/>
/// and <see cref="PFCatalogGetItemModerationStateGetResult"/> to get the result.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFCatalogGetItemModerationStateAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogGetItemModerationStateRequest* request,
	_Inout_ FOnGetItemModerationStateCompleted delegate
) noexcept;
#endif

/// <summary>
/// Gets the status of a publish of an item.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFCatalogGetItemPublishStatusGetResultSize"/>
/// and <see cref="PFCatalogGetItemPublishStatusGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFCatalogGetItemPublishStatusAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogGetItemPublishStatusRequest* request,
	_Inout_ FOnGetItemPublishStatusCompleted delegate
) noexcept;

/// <summary>
/// Get a paginated set of reviews associated with the specified item. Individual ratings and reviews
/// data update in near real time with delays within a few seconds.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFCatalogGetItemReviewsGetResultSize"/> and
/// <see cref="PFCatalogGetItemReviewsGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFCatalogGetItemReviewsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogGetItemReviewsRequest* request,
	_Inout_ FOnGetItemReviewsCompleted delegate
) noexcept;

/// <summary>
/// Get a summary of all ratings and reviews associated with the specified item. Summary ratings data
/// is cached with update data coming within 15 minutes.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFCatalogGetItemReviewSummaryGetResultSize"/>
/// and <see cref="PFCatalogGetItemReviewSummaryGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFCatalogGetItemReviewSummaryAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogGetItemReviewSummaryRequest* request,
	_Inout_ FOnGetItemReviewSummaryCompleted delegate
) noexcept;

/// <summary>
/// Retrieves items from the public catalog. Up to 50 items can be returned at once. GetItems does not
/// work off a cache of the Catalog and should be used when trying to get recent item updates. However,
/// please note that item references data is cached and may take a few moments for changes to propagate.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFCatalogGetItemsGetResultSize"/> and <see
/// cref="PFCatalogGetItemsGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFCatalogGetItemsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogGetItemsRequest* request,
	_Inout_ FOnGetItemsCompleted delegate
) noexcept;

/// <summary>
/// Initiates a publish of an item from the working catalog to the public catalog. You can use the GetItemPublishStatus
/// API to track the state of the item publish.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// The call kicks off a workflow to publish the item to the public catalog. The Publish Status API should
/// be used to monitor the publish job.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_DATABASE_THROUGHPUT_EXCEEDED, E_PF_ITEM_NOT_FOUND or any of the global
/// PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
bool PLAYFABSERVICES_API FPFCatalogPublishDraftItemAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogPublishDraftItemRequest* request,
	_Inout_ FOnPublishDraftItemCompleted delegate
) noexcept;

/// <summary>
/// Submit a report for an item, indicating in what way the item is inappropriate.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_DATABASE_THROUGHPUT_EXCEEDED, E_PF_ITEM_NOT_FOUND or any of the global
/// PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
bool PLAYFABSERVICES_API FPFCatalogReportItemAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogReportItemRequest* request,
	_Inout_ FOnReportItemCompleted delegate
) noexcept;

/// <summary>
/// Submit a report for a review
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Submit a report for an inappropriate review, allowing the submitting user to specify their concern.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_DATABASE_THROUGHPUT_EXCEEDED or any of the global PlayFab Service errors.
/// See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
bool PLAYFABSERVICES_API FPFCatalogReportItemReviewAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogReportItemReviewRequest* request,
	_Inout_ FOnReportItemReviewCompleted delegate
) noexcept;

/// <summary>
/// Creates or updates a review for the specified item. More information around the caching surrounding
/// item ratings and reviews can be found here: https://learn.microsoft.com/en-us/gaming/playfab/features/economy-v2/catalog/ratings#ratings-design-and-caching
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_DATABASE_THROUGHPUT_EXCEEDED, E_PF_ITEM_NOT_FOUND or any of the global
/// PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
bool PLAYFABSERVICES_API FPFCatalogReviewItemAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogReviewItemRequest* request,
	_Inout_ FOnReviewItemCompleted delegate
) noexcept;

/// <summary>
/// Executes a search against the public catalog using the provided search parameters and returns a set
/// of paginated results. SearchItems uses a cache of the catalog with item updates taking up to a few
/// minutes to propagate. You should use the GetItem API for when trying to immediately get recent item
/// updates. More information about the Search API can be found here: https://learn.microsoft.com/en-us/gaming/playfab/features/economy-v2/catalog/search
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFCatalogSearchItemsGetResultSize"/> and
/// <see cref="PFCatalogSearchItemsGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFCatalogSearchItemsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogSearchItemsRequest* request,
	_Inout_ FOnSearchItemsCompleted delegate
) noexcept;

/// <summary>
/// Sets the moderation state for an item, including the concern category and string reason. More information
/// about moderation states can be found here: https://learn.microsoft.com/en-us/gaming/playfab/features/economy-v2/ugc/moderation
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows.
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_DATABASE_THROUGHPUT_EXCEEDED, E_PF_ITEM_NOT_FOUND or any of the global
/// PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFCatalogSetItemModerationStateAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogSetItemModerationStateRequest* request,
	_Inout_ FOnSetItemModerationStateCompleted delegate
) noexcept;
#endif

/// <summary>
/// Submit a vote for a review, indicating whether the review was helpful or unhelpful.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_DATABASE_THROUGHPUT_EXCEEDED or any of the global PlayFab Service errors.
/// See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
bool PLAYFABSERVICES_API FPFCatalogSubmitItemReviewVoteAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogSubmitItemReviewVoteRequest* request,
	_Inout_ FOnSubmitItemReviewVoteCompleted delegate
) noexcept;

/// <summary>
/// Submit a request to takedown one or more reviews.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows.
/// Submit a request to takedown one or more reviews, removing them from public view. Authors will still
/// be able to see their reviews after being taken down.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_DATABASE_THROUGHPUT_EXCEEDED, E_PF_ITEM_NOT_FOUND or any of the global
/// PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFCatalogTakedownItemReviewsAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogTakedownItemReviewsRequest* request,
	_Inout_ FOnTakedownItemReviewsCompleted delegate
) noexcept;
#endif

/// <summary>
/// Updates the configuration for the catalog. Only Title Entities can call this API. There is a limit
/// of 10 requests in 10 seconds for this API. More information about the Catalog Config can be found
/// here: https://learn.microsoft.com/en-us/gaming/playfab/features/economy-v2/settings
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows.
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_BILLING_INFORMATION_REQUIRED, E_PF_CATALOG_CONFIG_INVALID, E_PF_INVALID_ENTITY_TYPE
/// or any of the global PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details
/// on error handling.
/// </remarks>
#if HC_PLATFORM == HC_PLATFORM_GDK
bool PLAYFABSERVICES_API FPFCatalogUpdateCatalogConfigAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogUpdateCatalogConfigRequest* request,
	_Inout_ FOnUpdateCatalogConfigCompleted delegate
) noexcept;
#endif

/// <summary>
/// Update the metadata for an item in the working catalog. Note: SAS tokens provided are valid for 1
/// hour.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <param name="async">XAsyncBlock for the async operation.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFCatalogUpdateDraftItemGetResultSize"/>
/// and <see cref="PFCatalogUpdateDraftItemGetResult"/> to get the result.
/// </remarks>
bool PLAYFABSERVICES_API FPFCatalogUpdateDraftItemAsync(
	_In_ FPFEntityHandle EntityHandle,
	_In_ const FPFCatalogUpdateDraftItemRequest* request,
	_Inout_ FOnUpdateDraftItemCompleted delegate
) noexcept;

}
