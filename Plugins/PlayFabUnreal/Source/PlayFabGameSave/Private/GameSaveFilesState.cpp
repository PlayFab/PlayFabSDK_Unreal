#include "GameSaveFilesState.h"

GameSaveFilesState& GameSaveFilesState::Get()
{
    static GameSaveFilesState state;
    return state;
}