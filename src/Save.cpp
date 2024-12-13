#include "Save.h"

SaveManager::SaveManager(SWR_SaveData* save) {
    _save = save;
}

void SaveManager::GiveMoney(int amount) {
    _save->money += amount;
}

void SaveManager::GivePitDroid() {
    _save->pitDroids++;
}