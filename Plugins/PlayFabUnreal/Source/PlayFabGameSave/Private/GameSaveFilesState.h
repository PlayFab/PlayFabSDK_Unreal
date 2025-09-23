#pragma once

#include "PFGameSaveFilesTypes.h"
#include "PFGameSaveFiles.h"
#include "PFGameSaveFilesUi.h"

struct GameSaveFilesState
{
    GameSaveFilesState(GameSaveFilesState&) = delete;
    GameSaveFilesState operator=(GameSaveFilesState&) = delete;
    ~GameSaveFilesState() = default;

    static GameSaveFilesState& Get();

    FPFGameSaveFilesActiveDeviceChangedDelegate activeDeviceChangedDelegate;
    FPFGameSaveFilesUiProgressDelegate progressDelegate;
    FPFGameSaveFilesUiSyncFailedDelegate syncFailedDelegate;
    FPFGameSaveFilesUiActiveDeviceContentionDelegate activeDeviceContentionDelegate;
    FPFGameSaveFilesUiConflictDelegate conflictDelegate;
    FPFGameSaveFilesUiOutOfStorageDelegate outOfStorageDelegate;

private:
    GameSaveFilesState() = default;
};