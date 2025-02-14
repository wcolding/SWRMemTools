#include "Save.h"

SaveManager::SaveManager(SWR_SaveData* saveData) {
    _saveData = saveData;
}

void SaveManager::InitializeSaveData() {
    _saveData->racesCompleted = 0;
    _saveData->amateurUnlocks = 1;
    _saveData->semiproUnlocks = 0;
    _saveData->galacticUnlocks = 0;
    _saveData->invitationalUnlocks = 0;
    _saveData->progressivePasses = 0;
    _saveData->racerUnlocks = 0;
    _saveData->money = 3000;
    _saveData->cutscenesBitfield = 0xFFFFFFFF;
    _saveData->pitDroids = 0;

    _saveData->tractionLevel = 0;
    _saveData->turningLevel = 0;
    _saveData->accelerationLevel = 0;
    _saveData->topSpeedLevel = 0;
    _saveData->airbrakeLevel = 0;
    _saveData->coolingLevel = 0;
    _saveData->repairLevel = 0;

    _saveData->tractionHealth = 0xFF;
    _saveData->turningHealth = 0xFF;
    _saveData->accelerationHealth = 0xFF;
    _saveData->topSpeedHealth = 0xFF;
    _saveData->airbrakeHealth = 0xFF;
    _saveData->coolingHealth = 0xFF;
    _saveData->repairHealth = 0xFF;
}

void SaveManager::GiveMoney(int amount) {
    _saveData->money += amount;
}

void SaveManager::GivePitDroid() {
    _saveData->pitDroids++;
}