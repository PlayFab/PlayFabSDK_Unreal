// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#include "CoreMinimal.h"
#include "Async/AsyncWork.h"
#include "Async/Async.h"
#include "XAsyncTaskQueueHelpers.h"
#include "XAsyncTaskManager.h"
#include "XAsyncTask.h"
#include "PFEntity.h"
#include "PFServiceConfig.h"
#include "PFCatalogUnrealTypes.h"
#include "PFCatalogTypeConverters.h"

THIRD_PARTY_INCLUDES_START
#include <playfab/services/PFServices.h>
THIRD_PARTY_INCLUDES_END


/// <summary>
/// Creates a new item in the working catalog using provided metadata. Note: SAS tokens provided are
/// valid for 1 hour.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// The item will not be published to the public catalog until the PublishItem API is called for the
/// item.
///
/// When the asynchronous task is complete, call <see cref="PFCatalogCreateDraftItemGetResultSize"/>
/// and <see cref="PFCatalogCreateDraftItemGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FCreateDraftItemAsyncTask : public FXAsyncTask
{
public:
	FCreateDraftItemAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogCreateDraftItemRequest InRequest,
	const FOnCreateDraftItemCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFCatalogCreateDraftItemRequest Request;
	
	FOnCreateDraftItemCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Creates one or more upload URLs which can be used by the client to upload raw file data. Content
/// URls and uploaded content will be garbage collected after 24 hours if not attached to a draft or published
/// item. Detailed pricing info around uploading content can be found here: https://learn.microsoft.com/en-us/gaming/playfab/features/pricing/meters/catalog-meters
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FCreateUploadUrlsAsyncTask : public FXAsyncTask
{
public:
	FCreateUploadUrlsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogCreateUploadUrlsRequest InRequest,
	const FOnCreateUploadUrlsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFCatalogCreateUploadUrlsRequest Request;
	
	FOnCreateUploadUrlsCompleted Delegate;

	HRESULT HResult;
};


#if HC_PLATFORM == HC_PLATFORM_GDK

/// <summary>
/// Deletes all reviews, helpfulness votes, and ratings submitted by the entity specified.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows.
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_PROFILE_DOES_NOT_EXIST or any of the global PlayFab Service errors.
/// See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FDeleteEntityItemReviewsAsyncTask : public FXAsyncTask
{
public:
	FDeleteEntityItemReviewsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogDeleteEntityItemReviewsRequest InRequest,
	const FOnDeleteEntityItemReviewsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFCatalogDeleteEntityItemReviewsRequest Request;
	
	FOnDeleteEntityItemReviewsCompleted Delegate;

	HRESULT HResult;
};

#endif


/// <summary>
/// Removes an item from working catalog and all published versions from the public catalog.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_DATABASE_THROUGHPUT_EXCEEDED, E_PF_ITEM_NOT_FOUND or any of the global
/// PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FDeleteItemAsyncTask : public FXAsyncTask
{
public:
	FDeleteItemAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogDeleteItemRequest InRequest,
	const FOnDeleteItemCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFCatalogDeleteItemRequest Request;
	
	FOnDeleteItemCompleted Delegate;

	HRESULT HResult;
};


#if HC_PLATFORM == HC_PLATFORM_GDK

/// <summary>
/// Gets the configuration for the catalog. Only Title Entities can call this API. There is a limit of
/// 100 requests in 10 seconds for this API. More information about the Catalog Config can be found here:
/// https://learn.microsoft.com/en-us/gaming/playfab/features/economy-v2/settings
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows.
/// When the asynchronous task is complete, call <see cref="PFCatalogGetCatalogConfigGetResultSize"/>
/// and <see cref="PFCatalogGetCatalogConfigGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FGetCatalogConfigAsyncTask : public FXAsyncTask
{
public:
	FGetCatalogConfigAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogGetCatalogConfigRequest InRequest,
	const FOnGetCatalogConfigCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFCatalogGetCatalogConfigRequest Request;
	
	FOnGetCatalogConfigCompleted Delegate;

	HRESULT HResult;
};

#endif


/// <summary>
/// Retrieves an item from the working catalog. This item represents the current working state of the
/// item. GetDraftItem does not work off a cache of the Catalog and should be used when trying to get
/// recent item updates. However, please note that item references data is cached and may take a few moments
/// for changes to propagate. Note: SAS tokens provided are valid for 1 hour.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFCatalogGetDraftItemGetResultSize"/> and
/// <see cref="PFCatalogGetDraftItemGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FGetDraftItemAsyncTask : public FXAsyncTask
{
public:
	FGetDraftItemAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogGetDraftItemRequest InRequest,
	const FOnGetDraftItemCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFCatalogGetDraftItemRequest Request;
	
	FOnGetDraftItemCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Retrieves a paginated list of the items from the draft catalog. Up to 50 IDs can be retrieved in
/// a single request. GetDraftItems does not work off a cache of the Catalog and should be used when trying
/// to get recent item updates. Note: SAS tokens provided are valid for 1 hour.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFCatalogGetDraftItemsGetResultSize"/> and
/// <see cref="PFCatalogGetDraftItemsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FGetDraftItemsAsyncTask : public FXAsyncTask
{
public:
	FGetDraftItemsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogGetDraftItemsRequest InRequest,
	const FOnGetDraftItemsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFCatalogGetDraftItemsRequest Request;
	
	FOnGetDraftItemsCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Retrieves a paginated list of the items from the draft catalog created by the Entity. Up to 50 items
/// can be returned at once. You can use continuation tokens to paginate through results that return greater
/// than the limit. GetEntityDraftItems does not work off a cache of the Catalog and should be used when
/// trying to get recent item updates.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFCatalogGetEntityDraftItemsGetResultSize"/>
/// and <see cref="PFCatalogGetEntityDraftItemsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FGetEntityDraftItemsAsyncTask : public FXAsyncTask
{
public:
	FGetEntityDraftItemsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogGetEntityDraftItemsRequest InRequest,
	const FOnGetEntityDraftItemsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFCatalogGetEntityDraftItemsRequest Request;
	
	FOnGetEntityDraftItemsCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Gets the submitted review for the specified item by the authenticated entity. Individual ratings
/// and reviews data update in near real time with delays within a few seconds.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFCatalogGetEntityItemReviewGetResultSize"/>
/// and <see cref="PFCatalogGetEntityItemReviewGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FGetEntityItemReviewAsyncTask : public FXAsyncTask
{
public:
	FGetEntityItemReviewAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogGetEntityItemReviewRequest InRequest,
	const FOnGetEntityItemReviewCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFCatalogGetEntityItemReviewRequest Request;
	
	FOnGetEntityItemReviewCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Retrieves an item from the public catalog. GetItem does not work off a cache of the Catalog and should
/// be used when trying to get recent item updates. However, please note that item references data is
/// cached and may take a few moments for changes to propagate.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFCatalogGetItemGetResultSize"/> and <see
/// cref="PFCatalogGetItemGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FGetItemAsyncTask : public FXAsyncTask
{
public:
	FGetItemAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogGetItemRequest InRequest,
	const FOnGetItemCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFCatalogGetItemRequest Request;
	
	FOnGetItemCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Search for a given item and return a set of bundles and stores containing the item. Up to 50 items
/// can be returned at once. You can use continuation tokens to paginate through results that return greater
/// than the limit. This API is intended for tooling/automation scenarios and has a reduced RPS with Player
/// Entities limited to 30 requests in 300 seconds and Title Entities limited to 100 requests in 10 seconds.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Given an item, return a set of bundles and stores containing the item.
///
/// When the asynchronous task is complete, call <see cref="PFCatalogGetItemContainersGetResultSize"/>
/// and <see cref="PFCatalogGetItemContainersGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FGetItemContainersAsyncTask : public FXAsyncTask
{
public:
	FGetItemContainersAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogGetItemContainersRequest InRequest,
	const FOnGetItemContainersCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFCatalogGetItemContainersRequest Request;
	
	FOnGetItemContainersCompleted Delegate;

	HRESULT HResult;
};


#if HC_PLATFORM == HC_PLATFORM_GDK

/// <summary>
/// Gets the moderation state for an item, including the concern category and string reason. More information
/// about moderation states can be found here: https://learn.microsoft.com/en-us/gaming/playfab/features/economy-v2/ugc/moderation
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows.
/// When the asynchronous task is complete, call <see cref="PFCatalogGetItemModerationStateGetResultSize"/>
/// and <see cref="PFCatalogGetItemModerationStateGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FGetItemModerationStateAsyncTask : public FXAsyncTask
{
public:
	FGetItemModerationStateAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogGetItemModerationStateRequest InRequest,
	const FOnGetItemModerationStateCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFCatalogGetItemModerationStateRequest Request;
	
	FOnGetItemModerationStateCompleted Delegate;

	HRESULT HResult;
};

#endif


/// <summary>
/// Gets the status of a publish of an item.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFCatalogGetItemPublishStatusGetResultSize"/>
/// and <see cref="PFCatalogGetItemPublishStatusGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FGetItemPublishStatusAsyncTask : public FXAsyncTask
{
public:
	FGetItemPublishStatusAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogGetItemPublishStatusRequest InRequest,
	const FOnGetItemPublishStatusCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFCatalogGetItemPublishStatusRequest Request;
	
	FOnGetItemPublishStatusCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Get a paginated set of reviews associated with the specified item. Individual ratings and reviews
/// data update in near real time with delays within a few seconds.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFCatalogGetItemReviewsGetResultSize"/> and
/// <see cref="PFCatalogGetItemReviewsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FGetItemReviewsAsyncTask : public FXAsyncTask
{
public:
	FGetItemReviewsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogGetItemReviewsRequest InRequest,
	const FOnGetItemReviewsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFCatalogGetItemReviewsRequest Request;
	
	FOnGetItemReviewsCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Get a summary of all ratings and reviews associated with the specified item. Summary ratings data
/// is cached with update data coming within 15 minutes.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFCatalogGetItemReviewSummaryGetResultSize"/>
/// and <see cref="PFCatalogGetItemReviewSummaryGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FGetItemReviewSummaryAsyncTask : public FXAsyncTask
{
public:
	FGetItemReviewSummaryAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogGetItemReviewSummaryRequest InRequest,
	const FOnGetItemReviewSummaryCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFCatalogGetItemReviewSummaryRequest Request;
	
	FOnGetItemReviewSummaryCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Retrieves items from the public catalog. Up to 50 items can be returned at once. GetItems does not
/// work off a cache of the Catalog and should be used when trying to get recent item updates. However,
/// please note that item references data is cached and may take a few moments for changes to propagate.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFCatalogGetItemsGetResultSize"/> and <see
/// cref="PFCatalogGetItemsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FGetItemsAsyncTask : public FXAsyncTask
{
public:
	FGetItemsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogGetItemsRequest InRequest,
	const FOnGetItemsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFCatalogGetItemsRequest Request;
	
	FOnGetItemsCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Initiates a publish of an item from the working catalog to the public catalog. You can use the GetItemPublishStatus
/// API to track the state of the item publish.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FPublishDraftItemAsyncTask : public FXAsyncTask
{
public:
	FPublishDraftItemAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogPublishDraftItemRequest InRequest,
	const FOnPublishDraftItemCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFCatalogPublishDraftItemRequest Request;
	
	FOnPublishDraftItemCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Submit a report for an item, indicating in what way the item is inappropriate.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_DATABASE_THROUGHPUT_EXCEEDED, E_PF_ITEM_NOT_FOUND or any of the global
/// PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FReportItemAsyncTask : public FXAsyncTask
{
public:
	FReportItemAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogReportItemRequest InRequest,
	const FOnReportItemCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFCatalogReportItemRequest Request;
	
	FOnReportItemCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Submit a report for a review
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Submit a report for an inappropriate review, allowing the submitting user to specify their concern.
///
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_DATABASE_THROUGHPUT_EXCEEDED or any of the global PlayFab Service errors.
/// See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FReportItemReviewAsyncTask : public FXAsyncTask
{
public:
	FReportItemReviewAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogReportItemReviewRequest InRequest,
	const FOnReportItemReviewCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFCatalogReportItemReviewRequest Request;
	
	FOnReportItemReviewCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Creates or updates a review for the specified item. More information around the caching surrounding
/// item ratings and reviews can be found here: https://learn.microsoft.com/en-us/gaming/playfab/features/economy-v2/catalog/ratings#ratings-design-and-caching
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_DATABASE_THROUGHPUT_EXCEEDED, E_PF_ITEM_NOT_FOUND or any of the global
/// PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FReviewItemAsyncTask : public FXAsyncTask
{
public:
	FReviewItemAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogReviewItemRequest InRequest,
	const FOnReviewItemCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFCatalogReviewItemRequest Request;
	
	FOnReviewItemCompleted Delegate;

	HRESULT HResult;
};



/// <summary>
/// Executes a search against the public catalog using the provided search parameters and returns a set
/// of paginated results. SearchItems uses a cache of the catalog with item updates taking up to a few
/// minutes to propagate. You should use the GetItem API for when trying to immediately get recent item
/// updates. More information about the Search API can be found here: https://learn.microsoft.com/en-us/gaming/playfab/features/economy-v2/catalog/search
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFCatalogSearchItemsGetResultSize"/> and
/// <see cref="PFCatalogSearchItemsGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FSearchItemsAsyncTask : public FXAsyncTask
{
public:
	FSearchItemsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogSearchItemsRequest InRequest,
	const FOnSearchItemsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFCatalogSearchItemsRequest Request;
	
	FOnSearchItemsCompleted Delegate;

	HRESULT HResult;
};


#if HC_PLATFORM == HC_PLATFORM_GDK

/// <summary>
/// Sets the moderation state for an item, including the concern category and string reason. More information
/// about moderation states can be found here: https://learn.microsoft.com/en-us/gaming/playfab/features/economy-v2/ugc/moderation
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows.
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_DATABASE_THROUGHPUT_EXCEEDED, E_PF_ITEM_NOT_FOUND or any of the global
/// PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FSetItemModerationStateAsyncTask : public FXAsyncTask
{
public:
	FSetItemModerationStateAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogSetItemModerationStateRequest InRequest,
	const FOnSetItemModerationStateCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFCatalogSetItemModerationStateRequest Request;
	
	FOnSetItemModerationStateCompleted Delegate;

	HRESULT HResult;
};

#endif


/// <summary>
/// Submit a vote for a review, indicating whether the review was helpful or unhelpful.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_DATABASE_THROUGHPUT_EXCEEDED or any of the global PlayFab Service errors.
/// See doc page "Handling PlayFab Errors" for more details on error handling.
/// </remarks>
class PLAYFABSERVICES_API FSubmitItemReviewVoteAsyncTask : public FXAsyncTask
{
public:
	FSubmitItemReviewVoteAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogSubmitItemReviewVoteRequest InRequest,
	const FOnSubmitItemReviewVoteCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFCatalogSubmitItemReviewVoteRequest Request;
	
	FOnSubmitItemReviewVoteCompleted Delegate;

	HRESULT HResult;
};


#if HC_PLATFORM == HC_PLATFORM_GDK

/// <summary>
/// Submit a request to takedown one or more reviews.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
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
class PLAYFABSERVICES_API FTakedownItemReviewsAsyncTask : public FXAsyncTask
{
public:
	FTakedownItemReviewsAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogTakedownItemReviewsRequest InRequest,
	const FOnTakedownItemReviewsCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFCatalogTakedownItemReviewsRequest Request;
	
	FOnTakedownItemReviewsCompleted Delegate;

	HRESULT HResult;
};

#endif

#if HC_PLATFORM == HC_PLATFORM_GDK

/// <summary>
/// Updates the configuration for the catalog. Only Title Entities can call this API. There is a limit
/// of 10 requests in 10 seconds for this API. More information about the Catalog Config can be found
/// here: https://learn.microsoft.com/en-us/gaming/playfab/features/economy-v2/settings
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on Windows.
/// Call <see cref="XAsyncGetStatus"/> to get the status of the operation. If the service call is unsuccessful,
/// the async result will be E_PF_BILLING_INFORMATION_REQUIRED, E_PF_CATALOG_CONFIG_INVALID, E_PF_INVALID_ENTITY_TYPE
/// or any of the global PlayFab Service errors. See doc page "Handling PlayFab Errors" for more details
/// on error handling.
/// </remarks>
class PLAYFABSERVICES_API FUpdateCatalogConfigAsyncTask : public FXAsyncTask
{
public:
	FUpdateCatalogConfigAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogUpdateCatalogConfigRequest InRequest,
	const FOnUpdateCatalogConfigCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFCatalogUpdateCatalogConfigRequest Request;
	
	FOnUpdateCatalogConfigCompleted Delegate;

	HRESULT HResult;
};

#endif


/// <summary>
/// Update the metadata for an item in the working catalog. Note: SAS tokens provided are valid for 1
/// hour.
/// </summary>
/// <param name="entityHandle">FPFEntityHandle to use for authentication.</param>
/// <param name="request">Populated request object.</param>
/// <returns>Result code for this API operation.</returns>
/// <remarks>
/// This API is available on all platforms.
/// When the asynchronous task is complete, call <see cref="PFCatalogUpdateDraftItemGetResultSize"/>
/// and <see cref="PFCatalogUpdateDraftItemGetResult"/> to get the result.
/// </remarks>
class PLAYFABSERVICES_API FUpdateDraftItemAsyncTask : public FXAsyncTask
{
public:
	FUpdateDraftItemAsyncTask(
	_In_ FPFEntityHandle EntityHandle,
	FPFCatalogUpdateDraftItemRequest InRequest,
	const FOnUpdateDraftItemCompleted& InDelegate);

	virtual void DoWork() override;

	virtual void ProcessResults() override;

private:
	FPFEntityHandle EntityHandle;
	
	FPFCatalogUpdateDraftItemRequest Request;
	
	FOnUpdateDraftItemCompleted Delegate;

	HRESULT HResult;
};

