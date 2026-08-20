#pragma once

#include "PFGameSaveFiles.h"
#include "Async/AsyncWork.h"
#include "Async/Async.h"
#include "XAsyncTaskQueueHelpers.h"
#include "XAsyncTaskManager.h"
#include "XAsyncTask.h"
#include "TypeWrappers.h"

class GameSaveFilesAddUserAsyncTask : public FXAsyncTask
{
public:
    GameSaveFilesAddUserAsyncTask(
        FPFLocalUserHandle localUserHandle,
        FPFGameSaveFilesAddUserOptions options,
        FPFGameSaveFilesAddUserWithUiAsyncComplete delegate
    );

    void DoWork() override;

    void ProcessResults() override;

private:
    LocalUser m_localUser;
    FPFGameSaveFilesAddUserOptions m_options;
    FPFGameSaveFilesAddUserWithUiAsyncComplete m_delegate;
};


class GameSaveFilesUploadWithUIAsyncTask : public FXAsyncTask
{
public:
    GameSaveFilesUploadWithUIAsyncTask(
        FPFLocalUserHandle localUserHandle,
        FPFGameSaveFilesUploadOption options,
        FPFGameSaveFilesUploadWithUiAsyncComplete delegate
    );

    void DoWork() override;

    void ProcessResults() override;

private:
    LocalUser m_localUser;
    FPFGameSaveFilesUploadOption m_options;
    FPFGameSaveFilesUploadWithUiAsyncComplete m_delegate;
};

class GameSaveFilesResetCloudAsyncTask : public FXAsyncTask
{
public:
    GameSaveFilesResetCloudAsyncTask(
        FPFLocalUserHandle localUserHandle,
        FPFGameSaveFilesResetCloudAsyncComplete delegate
    );

    void DoWork() override;

    void ProcessResults() override;

private:
    LocalUser m_localUser;
    FPFGameSaveFilesResetCloudAsyncComplete m_delegate;
};

class GameSaveFilesSetSaveDescriptionAsyncTask : public FXAsyncTask
{
public:
    GameSaveFilesSetSaveDescriptionAsyncTask(
        FPFLocalUserHandle localUserHandle,
        const FString& description,
        FPFGameSaveFilesSetSaveDescriptionAsyncComplete delegate
    );

    void DoWork() override;

    void ProcessResults() override;

private:
    LocalUser m_localUser;
    FString m_description;
    FPFGameSaveFilesSetSaveDescriptionAsyncComplete m_delegate;
};

class GameSaveFilesUninitializeAsyncTask : public FXAsyncTask
{
public:
    GameSaveFilesUninitializeAsyncTask(
        FPFGameSaveFilesUninitializeComplete delegate
    );

    void DoWork() override;

    void ProcessResults() override;

private:
    FPFGameSaveFilesUninitializeComplete m_delegate;
};