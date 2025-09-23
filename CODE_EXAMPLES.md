# PlayFab Unreal Engine Plugin - Code Examples

This document provides detailed implementation examples for the PlayFab Unreal Engine Plugin. These examples complement the [Getting Started Guide](GETTING_STARTED.md) with comprehensive code samples and configuration details.

## Sample Configuration

### Xbox Authentication Configuration

If you're using Xbox authentication (GDK/Xbox platforms), you'll also need to add Xbox-specific configuration to your `DefaultEngine.ini`:

```ini
[/Script/WindowsTargetPlatform.WindowsTargetSettings]
TitleId=YOUR_XBOX_TITLE_ID
PrimaryServiceConfigId=YOUR_PRIMARY_SERVICE_CONFIG_ID
ProductId=YOUR_PRODUCT_ID
ContentId=YOUR_CONTENT_ID
PackageName=YOUR_PACKAGE_NAME
StoreId=YOUR_STORE_ID
DefaultDisplayName=YOUR_GAME_DISPLAY_NAME
PublisherName=YOUR_PUBLISHER_NAME
PublisherDisplayName=YOUR_PUBLISHER_DISPLAY_NAME
EKBID=YOUR_EKBID
MSAAppId=YOUR_MSA_APP_ID
```

**Note**: Replace the placeholder values with your actual Xbox Live configuration from your Xbox Partner Center. These values are required for Xbox authentication to work properly.

### Required Header File

Make sure to include the PlayFabUnreal header in your game classes:

````cpp
#include "PlayFabUnreal.h"
````

This should allow you to call any PlayFab APIs.

## Basic Usage

### 1. Initialize PlayFab Services

In your game's initialization code (typically in your GameMode constructor or `BeginPlay`):

````cpp
#include "PlayFabUnreal.h"

void AYourGameMode::InitializePlayFab()
{
    // Initialize PlayFab Services
    HRESULT hr = FPFServicesInitialize();
    
    // Create service config handle
    TSharedRef<FPFServiceConfigHandle> serviceConfigHandle = MakeShared<FPFServiceConfigHandle>();
    
    bool succeeded = FPFServiceConfigCreateHandle(
        "https://YOUR_TITLE_ID.playfabapi.com",
        "YOUR_TITLE_ID",
        serviceConfigHandle);
    
    if (succeeded)
    {
        UE_LOG(LogTemp, Log, TEXT("PlayFab Services initialized successfully"));
        // Store the service config handle for later use
        this->ServiceConfigHandle = serviceConfigHandle;
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to initialize PlayFab Services"));
    }
}
````

### 2. Authentication Examples

#### Option A: Xbox Authentication (Recommended for Console/GDK builds)

For Xbox/GDK platforms, use Xbox User authentication:

````cpp
#ifdef PF_UE_GDK_SUPPORT
#include "GDKRuntimeModule.h"

void AYourGameMode::LoginWithXboxUser()
{
    // Get Xbox user handles
    auto userHandles = IGDKRuntimeModule::Get().GetAllUserHandles();
    if (userHandles.IsEmpty())
    {
        UE_LOG(LogTemp, Error, TEXT("No XUser available for PlayFab login"));
        return;
    }

    // Create PlayFab local user with Xbox authentication
    bool succeeded = FPFLocalUserCreateHandleWithXboxUser(
        ServiceConfigHandle.Get(), 
        userHandles[0], 
        nullptr, 
        &LocalUserHandle);
    
    if (!succeeded)
    {
        UE_LOG(LogTemp, Error, TEXT("Unable to create PlayFab LocalUser with Xbox auth"));
        return;
    }

    // Perform login
    succeeded = FPFLocalUserLoginAsync(
        LocalUserHandle,
        true, // createAccount
        FOnPFAuthenticationLoginCompleteDelegate::CreateLambda([this](
            const FPFAuthenticationLoginResult* loginResult, 
            FPFEntityHandle* handle, 
            bool bWasSuccessful)
        {
            if (bWasSuccessful)
            {
                UE_LOG(LogTemp, Log, TEXT("Xbox login successful! PlayFab ID: %s"), 
                       *FString(loginResult->playFabId));
                
                // Store entity handle for API calls
                this->EntityHandle = *handle;
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Xbox login failed"));
            }
        }));
        
    if (!succeeded)
    {
        UE_LOG(LogTemp, Error, TEXT("Synchronous failure on FPFLocalUserLoginAsync"));
    }
}
#endif
````

#### Option B: Custom ID Authentication (Fallback for Win64)

For platforms without Xbox integration:

````cpp
void AYourGameMode::LoginWithCustomId()
{
    FString customId = TEXT("UniquePlayerIdentifier123");
    
    // Create PlayFab local user with custom ID
    bool succeeded = FPFLocalUserCreateHandleWithPersistedLocalId(
        ServiceConfigHandle.Get(), 
        customId, 
        nullptr, 
        &LocalUserHandle);
    
    if (!succeeded)
    {
        UE_LOG(LogTemp, Error, TEXT("Unable to create PlayFab LocalUser with custom ID"));
        return;
    }

    // Perform login
    succeeded = FPFLocalUserLoginAsync(
        LocalUserHandle,
        true, // createAccount
        FOnPFAuthenticationLoginCompleteDelegate::CreateLambda([this](
            const FPFAuthenticationLoginResult* loginResult, 
            FPFEntityHandle* handle, 
            bool bWasSuccessful)
        {
            if (bWasSuccessful)
            {
                UE_LOG(LogTemp, Log, TEXT("Custom ID login successful! PlayFab ID: %s"), 
                       *FString(loginResult->playFabId));
                
                // Store entity handle for API calls
                this->EntityHandle = *handle;
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Custom ID login failed"));
            }
        }));
        
    if (!succeeded)
    {
        UE_LOG(LogTemp, Error, TEXT("Synchronous failure on FPFLocalUserLoginAsync"));
    }
}
````

### 3. Using PlayFab Services

Once authenticated, you can use various PlayFab services. Here are examples using the Unreal-specific FPF* APIs:

#### Player Segments and Tags

````cpp
void AYourGameMode::GetPlayerTagsAndSegments(const FPFAuthenticationLoginResult* loginResult)
{
    // Get Player Tags
    FPFSegmentsGetPlayerTagsRequest tagsRequest = {
        .playFabId = loginResult->playFabId
    };

    FPFSegmentsClientGetPlayerTagsAsync(EntityHandle, &tagsRequest, 
        FOnClientGetPlayerTagsCompleted::CreateLambda([](const FPFSegmentsGetPlayerTagsResult& Result, bool Success)
        {
            if (Success)
            {
                UE_LOG(LogTemp, Log, TEXT("Tags count: %d"), Result.tagsCount);
                for (uint32 i = 0; i < Result.tagsCount; i++)
                {
                    UE_LOG(LogTemp, Log, TEXT("Tag: %s"), *Result.tags[i]);
                }
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to get player tags: %s"), *Result.ErrorMessage);
            }
        }));

    // Get Player Segments
    FPFSegmentsClientGetPlayerSegmentsAsync(EntityHandle, 
        FOnClientGetPlayerSegmentsCompleted::CreateLambda([](const FPFSegmentsGetPlayerSegmentsResult& Result, bool Success)
        {
            if (Success)
            {
                UE_LOG(LogTemp, Log, TEXT("Segments count: %d"), Result.segmentsCount);
                for (uint32 i = 0; i < Result.segmentsCount; i++)
                {
                    UE_LOG(LogTemp, Log, TEXT("Segment ID: %s"), *Result.segments[i]->id);
                    UE_LOG(LogTemp, Log, TEXT("Segment Name: %s"), *Result.segments[i]->name);
                }
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to get player segments: %s"), *Result.ErrorMessage);
            }
        }));
}
````

### 4. Using PlayFab Game Saves (Xbox/GDK Only)

````cpp
#ifdef PF_UE_GDK_SUPPORT
void AYourGameMode::InitializeGameSaves()
{
    // Initialize Game Save system
    FPFGameSaveInitArgs gameSaveInitArgs{};
    bool succeeded = FPFGameSaveFilesInitialize(&gameSaveInitArgs);
    
    if (!succeeded)
    {
        UE_LOG(LogTemp, Error, TEXT("Unable to initialize PFGameSaveFiles"));
        return;
    }

    // Set up UI delegates for save conflicts and progress
    succeeded = FPFGameSaveFilesSetUiDelegates(
        FPFGameSaveFilesUiProgressDelegate::CreateUObject(this, &AYourGameMode::OnGameSaveProgress),
        FPFGameSaveFilesUiSyncFailedDelegate::CreateUObject(this, &AYourGameMode::OnGameSaveSyncFailed),
        FPFGameSaveFilesUiActiveDeviceContentionDelegate::CreateUObject(this, &AYourGameMode::OnGameSaveDeviceContention),
        FPFGameSaveFilesUiConflictDelegate::CreateUObject(this, &AYourGameMode::OnGameSaveConflict),
        FPFGameSaveFilesUiOutOfStorageDelegate::CreateUObject(this, &AYourGameMode::OnGameSaveOutOfStorage)
    );

    // Add user to game save system
    succeeded = FPFGameSaveFilesAddUserWithUiAsync(
        LocalUserHandle,
        FPFGameSaveFilesAddUserOptions::None,
        FPFGameSaveFilesAddUserWithUiAsyncComplete::CreateLambda([this](bool succeeded)
        {
            if (succeeded)
            {
                UE_LOG(LogTemp, Log, TEXT("User added to game save system"));
                SaveGameData(); // Save some initial data
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to add user to game save system"));
            }
        }));
}

void AYourGameMode::SaveGameData()
{
    // Get the game save folder
    FString gameSaveFolder;
    bool succeeded = FPFGameSaveFilesGetFolder(LocalUserHandle, gameSaveFolder);
    if (!succeeded)
    {
        UE_LOG(LogTemp, Error, TEXT("Unable to get PFGameSave folder"));
        return;
    }

    // Write save data to file
    FString filename = TEXT("PlayerData");
    FString saveData = TEXT("{ \"playerLevel\": 5, \"score\": 1000 }");
    FString fullFilePath = FString::Printf(TEXT("%s/%s.sav"), *gameSaveFolder, *filename);
    
    succeeded = FFileHelper::SaveStringToFile(saveData, *fullFilePath);
    if (!succeeded)
    {
        UE_LOG(LogTemp, Error, TEXT("Unable to write local save game data"));
        return;
    }

    // Upload to cloud
    succeeded = FPFGameSaveFilesUploadWithUiAsync(
        LocalUserHandle,
        FPFGameSaveFilesUploadOption::KeepDeviceActive,
        FPFGameSaveFilesUploadWithUiAsyncComplete::CreateLambda([](bool succeeded)
        {
            if (succeeded)
            {
                UE_LOG(LogTemp, Log, TEXT("Successfully uploaded save data to cloud"));
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to upload save data"));
            }
        })
    );
}

// Game Save delegate implementations
void AYourGameMode::OnGameSaveProgress(FPFLocalUserHandle user, FPFGameSaveFilesSyncState state)
{
    UE_LOG(LogTemp, Log, TEXT("Game save progress: state=%d"), static_cast<int>(state));
}

void AYourGameMode::OnGameSaveSyncFailed(FPFLocalUserHandle user, FPFGameSaveFilesSyncState state, int32 errorCode)
{
    UE_LOG(LogTemp, Error, TEXT("Game save sync failed: state=%d, error=%d"), static_cast<int>(state), errorCode);
}

void AYourGameMode::OnGameSaveDeviceContention(FPFLocalUserHandle user, FPFGameSaveDescriptor* local, FPFGameSaveDescriptor* remote)
{
    UE_LOG(LogTemp, Warning, TEXT("Game save device contention detected, resolving with sync"));
    FPFGameSaveFilesSetUiActiveDeviceContentionResponse(user, FPFGameSaveFilesUiActiveDeviceContentionUserAction::SyncLastSavedData);
}

void AYourGameMode::OnGameSaveConflict(FPFLocalUserHandle user, FPFGameSaveDescriptor* local, FPFGameSaveDescriptor* remote)
{
    UE_LOG(LogTemp, Warning, TEXT("Game save conflict detected"));
}

void AYourGameMode::OnGameSaveOutOfStorage(FPFLocalUserHandle user, uint64 bytesRequired)
{
    UE_LOG(LogTemp, Error, TEXT("Game save out of storage: %llu bytes required"), bytesRequired);
}
#endif
````

#### Event Pipeline (Telemetry)

````cpp
void AYourGameMode::SetupEventPipeline()
{
    TSharedRef<FPFEventPipelineHandle> eventPipelineHandle = MakeShared<FPFEventPipelineHandle>();

    FPFEventPipelineTelemetryKeyConfig telemetryKeyConfig{
        "YOUR_TELEMETRY_KEY_HERE",  // Get this from PlayFab dashboard
        ServiceConfigHandle.Get(),
    };

    TSharedRef<FPFEventPipelineTelemetryKeyConfig> telemetryKeyConfigRef = 
        MakeShared<FPFEventPipelineTelemetryKeyConfig>(telemetryKeyConfig);

    // Set up success and failure delegates
    FPFEventPipelineBatchUploadSucceededEventDelegate successDelegate = 
        FPFEventPipelineBatchUploadSucceededEventDelegate::CreateLambda([](
            TSharedPtr<void> context, 
            TArray<TSharedPtr<const FPFUploadedEvent>> events, 
            SIZE_T eventsCount)
        {
            UE_LOG(LogTemp, Log, TEXT("Events uploaded successfully: %d events"), eventsCount);
        });

    FPFEventPipelineBatchUploadFailedEventDelegate failureDelegate = 
        FPFEventPipelineBatchUploadFailedEventDelegate::CreateLambda([](
            TSharedPtr<void> context, 
            HRESULT hr, 
            FString errorMessage, 
            TArray<TSharedPtr<const FPFEvent>> events, 
            SIZE_T eventsCount)
        {
            UE_LOG(LogTemp, Error, TEXT("Events upload failed: %s"), *errorMessage);
        });

    // Create the event pipeline
    FPFEventPipelineCreateTelemetryPipelineHandleWithKey(
        telemetryKeyConfigRef,
        successDelegate,
        failureDelegate,
        nullptr,
        eventPipelineHandle
    );

    // Store for later use
    this->EventPipelineHandle = eventPipelineHandle;
}

void AYourGameMode::SendTelemetryEvent(const FString& EventName, const FString& EventData)
{
    if (!EventPipelineHandle.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("Event pipeline not initialized"));
        return;
    }

    FPFEntityKey entityKey{
        .id = TEXT("testUnrealPlayer"),
        .type = TEXT("external")
    };

    FPFEvent telemetryEvent{
        MakeShared<FPFEntityKey>(entityKey),
        TEXT("custom.playfab.events.PlayFab.Test.UnrealSample"),
        EventName,
        FGuid::NewGuid().ToString(),
        EventData
    };

    FPFEventPipelineEmitEvent(EventPipelineHandle.Get(), MakeShared<FPFEvent>(telemetryEvent));
}
````

### 5. Cleanup

Don't forget to properly clean up PlayFab handles and uninitialize services in your destructors:

````cpp
// In your GameMode destructor or EndPlay
AYourGameMode::~AYourGameMode()
{
    if (LocalUserHandle)
    {
        FPFLocalUserCloseHandle(LocalUserHandle);
        LocalUserHandle = nullptr;
    }
    if (EntityHandle)
    {
        FPFEntityCloseHandle(EntityHandle);
        EntityHandle = nullptr;
    }
    if (ServiceConfigHandle.IsValid())
    {
        FPFServiceConfigCloseHandle(ServiceConfigHandle.Get());
        ServiceConfigHandle.Reset();
    }
    
    // Uninitialize PlayFab Services
    FPFServicesUninitialize();
}
````

## Additional Examples

For more advanced usage patterns and specific API examples, refer to:
- [PlayFab Documentation](https://docs.microsoft.com/gaming/playfab/)
- [PlayFab REST API Reference](https://docs.microsoft.com/rest/api/playfab/)
- [Unreal Engine GDK Documentation](https://docs.unrealengine.com/5.0/gdk/)
