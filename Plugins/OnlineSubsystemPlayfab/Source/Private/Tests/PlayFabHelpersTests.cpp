//--------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "PlayFabHelpers.h"

namespace
{
	class FTestHttpResponse final : public IHttpResponse
	{
	public:
		FTestHttpResponse()
		{
			const FTCHARToUTF8 ConvertedContent(*ContentString);
			Content.Append(reinterpret_cast<const uint8*>(ConvertedContent.Get()), ConvertedContent.Length());
		}

		virtual const FString& GetURL() const override { return Url; }
		virtual const FString& GetEffectiveURL() const override { return Url; }
		virtual EHttpRequestStatus::Type GetStatus() const override { return EHttpRequestStatus::Succeeded; }
		virtual EHttpFailureReason GetFailureReason() const override { return EHttpFailureReason::None; }
		virtual FString GetURLParameter(const FString&) const override { return FString(); }
		virtual FString GetHeader(const FString& HeaderName) const override
		{
			return HeaderName.Equals(TEXT("X-RequestId"), ESearchCase::CaseSensitive) ? RequestId : FString();
		}
		virtual TArray<FString> GetAllHeaders() const override { return { FString::Printf(TEXT("X-RequestId: %s"), *RequestId) }; }
		virtual FString GetContentType() const override { return TEXT("application/json"); }
		virtual uint64 GetContentLength() const override { return Content.Num(); }
		virtual const TArray<uint8>& GetContent() const override { return Content; }
		virtual TArray<uint8> TakeContent() override { return MoveTemp(Content); }
		virtual int32 GetResponseCode() const override { return 400; }
		virtual FString GetContentAsString() const override { return ContentString; }
		virtual FUtf8StringView GetContentAsUtf8StringView() const override
		{
			return FUtf8StringView(reinterpret_cast<const UTF8CHAR*>(Content.GetData()), Content.Num());
		}

	private:
		FString Url = TEXT("https://test.playfabapi.com/test");
		FString RequestId = TEXT("test-request-id");
		FString ContentString = TEXT("{\"secret\":\"must-not-appear-at-error\"}");
		TArray<uint8> Content;
	};
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FPlayFabInvalidRestResponseTest,
	"PlayFab.OSS.Helpers.RestResponse.InvalidResponseFails",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabInvalidRestResponseTest::RunTest(const FString&)
{
	TMap<FString, FString> EntityIdMapping;

	AddExpectedError(TEXT("ParseDataObjectFromPlayFabResponse failed: HttpResponse was invalid"), EAutomationExpectedErrorFlags::Contains, 1);
	TestFalse(
		TEXT("An invalid HTTP response fails parsing"),
		ParseTitleAccountIDsFromPlatformIDsResponse(nullptr, EntityIdMapping));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FPlayFabFailedRestResponseDiagnosticsTest,
	"PlayFab.OSS.Helpers.RestResponse.FailureDiagnosticsExcludeBody",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FPlayFabFailedRestResponseDiagnosticsTest::RunTest(const FString&)
{
	TMap<FString, FString> EntityIdMapping;
	FHttpResponsePtr HttpResponse = MakeShared<FTestHttpResponse, ESPMode::ThreadSafe>();

	AddExpectedErrorPlain(
		TEXT("ParseDataObjectFromPlayFabResponse failed. Url:https://test.playfabapi.com/test, ResponseCode:400, RequestId:test-request-id"),
		EAutomationExpectedErrorFlags::Contains,
		1);
	TestFalse(
		TEXT("A failed HTTP response fails parsing without logging its body at Error"),
		ParseTitleAccountIDsFromPlatformIDsResponse(HttpResponse, EntityIdMapping));
	return true;
}

#endif