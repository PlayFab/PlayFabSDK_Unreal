#pragma once

/// <summary>
/// Struct the defines retry settings for PlayFab HTTP requests.
/// </summary>
struct FPFHttpRetrySettings
{
	/// <summary>
	/// Controls whether the SDK should automatically retry select errors. There are certain errors that will never be
	/// handled internally and will always be returned directly to the client. Default value is 'true'.
	/// </summary>
	bool allowRetry;

	/// <summary>
	/// The minimum number of seconds the SDK will wait after an HTTP failure before retrying the call. 
	/// The default and minimum value is 2 seconds.
	/// </summary>
	uint32_t minimumRetryDelayInSeconds;

	/// <summary>
	/// The maximum number of seconds the SDK will attempt to retry an HTTP request before returning to the client.
	/// The default value is 20 seconds.
	/// </summary>
	uint32_t timeoutWindowInSeconds;
};

/// <summary>
/// Struct that defines generic Http settings for PlayFab HTTP requests.
/// Currently holds settings to enable gzip compression on all sdk responses.
/// </summary>
struct FPFHttpSettings
{
	/// <summary>
	/// Controls whether the SDK currently requests that incoming responses be compressed. 
	/// Response compression is enabled by specifying the Accept-Encoding Header as "application/gzip".
	/// In order to decompress a compressed response provided by an API endpoint PFHCHttpCallResponseSetGzipCompressed 
	/// must be called prior to calling PFHCHttpCallPerformAsync.
	/// </summary>
	bool requestResponseCompression;
};