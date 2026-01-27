#include "Save.h"

#include <cmath>
#include <algorithm>

namespace SWRMemTools {
    SaveManager::SaveManager(SaveData** saveDataPtr) {
        onlineSavePtr = saveDataPtr;
        onlineSave = nullptr;
    }

    bool SaveManager::isSaveReady() {
        if (onlineSavePtr == nullptr)
            return false;

        onlineSave = *onlineSavePtr;
        if (onlineSave == nullptr)
            return false;
        
        return true;
    }

    SaveData* SaveManager::GetCurrentSavePtr() {
        if (isSaveReady())
        {
            if (isOffline)
                SyncOfflineSaveData();
            return onlineSave;
        }
        
        isOffline = true;
        return offlineSave;
    }

    void SaveManager::SyncOfflineSaveData() {
        if (isSaveReady()) {
            onlineSave->amateurUnlocks |= offlineSave->amateurUnlocks;
            onlineSave->semiproUnlocks |= offlineSave->semiproUnlocks;
            onlineSave->galacticUnlocks |= offlineSave->galacticUnlocks;
            onlineSave->invitationalUnlocks |= offlineSave->invitationalUnlocks;

            onlineSave->tractionLevel += offlineSave->tractionLevel;
            onlineSave->tractionHealth = offlineSave->tractionHealth;

            onlineSave->turningLevel += offlineSave->turningLevel;
            onlineSave->turningHealth = offlineSave->turningHealth;

            onlineSave->accelerationLevel += offlineSave->accelerationLevel;
            onlineSave->accelerationHealth = offlineSave->accelerationHealth;

            onlineSave->topSpeedLevel += offlineSave->topSpeedLevel;
            onlineSave->topSpeedHealth = offlineSave->topSpeedHealth;

            onlineSave->airbrakeLevel += offlineSave->airbrakeLevel;
            onlineSave->airbrakeHealth = offlineSave->airbrakeHealth;

            onlineSave->coolingLevel += offlineSave->coolingLevel;
            onlineSave->coolingHealth = offlineSave->coolingHealth;

            onlineSave->repairLevel += offlineSave->repairLevel;
            onlineSave->repairHealth = offlineSave->repairHealth;

            onlineSave->amateurRacePlacements |= offlineSave->amateurRacePlacements;
            onlineSave->semiproRacePlacements |= offlineSave->semiproRacePlacements;
            onlineSave->galacticRacePlacements |= offlineSave->galacticRacePlacements;
            onlineSave->invitationalRacePlacements |= offlineSave->invitationalRacePlacements;
            onlineSave->coursesCompleted |= offlineSave->coursesCompleted;

            // Reset offline values
            offlineSave->tractionLevel = 0;
            offlineSave->turningLevel = 0;
            offlineSave->accelerationLevel = 0;
            offlineSave->topSpeedLevel = 0;
            offlineSave->airbrakeLevel = 0;
            offlineSave->coolingLevel = 0;
            offlineSave->repairLevel = 0;

            isOffline = false;
        }
    }

    void SaveManager::InitializeSaveData() {
        SaveData* _saveData = GetCurrentSavePtr();
            
        _saveData->coursesCompleted = 0;
        _saveData->amateurUnlocks = 1;
        _saveData->semiproUnlocks = 0;
        _saveData->galacticUnlocks = 0;
        _saveData->invitationalUnlocks = 0;
        _saveData->progressivePasses = 0;
        _saveData->racerUnlocks = 0;
        _saveData->money = 400;
        _saveData->cutscenesBitfield = 0xFFFFFFFF;
        _saveData->pitDroids = 1;

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

        _saveData->amateurRacePlacements = 0;
        _saveData->semiproRacePlacements = 0;
        _saveData->galacticRacePlacements = 0;
        _saveData->invitationalRacePlacements = 0;
    }
    
    void SaveManager::ResetSaveData() {
        SaveData* _saveData = GetCurrentSavePtr();

        _saveData->racerUnlocks = 0;

        _saveData->tractionLevel = 0;
        _saveData->turningLevel = 0;
        _saveData->accelerationLevel = 0;
        _saveData->topSpeedLevel = 0;
        _saveData->airbrakeLevel = 0;
        _saveData->coolingLevel = 0;
        _saveData->repairLevel = 0;

        _saveData->amateurUnlocks = 1;
        _saveData->semiproUnlocks = 0;
        _saveData->galacticUnlocks = 0;
        _saveData->invitationalUnlocks = 0;

        amateurCoursesReceived = 1;
        semiproCoursesReceived = 0;
        galacticCoursesReceived = 0;
        invitationalCoursesReceived = 0; 

        semiproPassReceived = false;
        galacticPassReceived = false;
        invitationalPassReceived = false;
    }

    void SaveManager::GiveMoney(int amount) {
        SaveData* _saveData = GetCurrentSavePtr();
        _saveData->money += amount;
    }

    void SaveManager::GivePitDroid() {
        SaveData* _saveData = GetCurrentSavePtr();
        _saveData->pitDroids++;
    }

    void SaveManager::GiveRacer(RacerUnlocks racer) {
        apRacerUnlocks |= racer;
    }

    void SaveManager::RecalculateCourseUnlockFlags() {
        SaveData* _saveData = GetCurrentSavePtr();
        _saveData->amateurUnlocks |= static_cast<char>(pow(2, amateurCoursesReceived) - 1);
        _saveData->semiproUnlocks |= static_cast<char>(pow(2, semiproCoursesReceived) - 1);
        _saveData->galacticUnlocks |= static_cast<char>(pow(2, galacticCoursesReceived) - 1);
        _saveData->invitationalUnlocks |= static_cast<char>(pow(2, invitationalCoursesReceived) - 1);
    }

    void SaveManager::GiveAmateurCourse() {
        amateurCoursesReceived++;
        RecalculateCourseUnlockFlags();
    }

    void SaveManager::GiveSemiproCourse() {
        semiproCoursesReceived++;
        RecalculateCourseUnlockFlags();
    }

    void SaveManager::GiveGalacticCourse() {
        galacticCoursesReceived++;
        RecalculateCourseUnlockFlags();
    }

    void SaveManager::GiveInvitationalCourse() {
        invitationalCoursesReceived++;
        RecalculateCourseUnlockFlags();
    }


    void SaveManager::GiveCircuitPass(int circuit) {
        SaveData* _saveData = GetCurrentSavePtr();
        int next;

        switch (circuit) {
        case SEMIPRO_CIRCUIT:
            if (!semiproPassReceived)
            {
                semiproPassReceived = true;
                GiveSemiproCourse();
            }
            break;
        case GALACTIC_CIRCUIT:
            if (!galacticPassReceived)
            {
                galacticPassReceived = true;
                GiveGalacticCourse();
            }
            break;
        case INVITATIONAL_CIRCUIT:
            if (!invitationalPassReceived)
            {
                invitationalPassReceived = true;
                GiveInvitationalCourse();
            }
            break;
        case PROGRESSIVE_CIRCUIT:
            if (!semiproPassReceived)
            {
                GiveCircuitPass(SEMIPRO_CIRCUIT);
                break;
            }

            if (!galacticPassReceived)
            {
                GiveCircuitPass(GALACTIC_CIRCUIT);
                break;
            }

            if (!invitationalPassReceived)
            {
                GiveCircuitPass(INVITATIONAL_CIRCUIT);
                break;
            }
            break;
        default:
            break;
        }
    }

    bool GivePart(char& part, int level) {
        if (level == PROGRESSIVE_PART) {
            level = part + 1;
        }
        
        level = std::clamp(level, 0, 5);
        if (part < level) {
            part = level;
            return true;
        }

        return false;
    }

    void SaveManager::GiveTractionPart(int level) {
        SaveData* _saveData = GetCurrentSavePtr();
        if (GivePart(_saveData->tractionLevel, level)) {
            _saveData->tractionHealth = 0xFF;
        }
    }

    void SaveManager::GiveTurningPart(int level) {
        SaveData* _saveData = GetCurrentSavePtr();
        if (GivePart(_saveData->turningLevel, level)) {
            _saveData->turningHealth = 0xFF;
        }
    }

    void SaveManager::GiveAccelerationPart(int level) {
        SaveData* _saveData = GetCurrentSavePtr();
        if (GivePart(_saveData->accelerationLevel, level)) {
            _saveData->accelerationHealth = 0xFF;
        }
    }

    void SaveManager::GiveTopSpeedPart(int level) {
        SaveData* _saveData = GetCurrentSavePtr();
        if (GivePart(_saveData->topSpeedLevel, level)) {
            _saveData->topSpeedHealth = 0xFF;
        }
    }

    void SaveManager::GiveAirbrakePart(int level) {
        SaveData* _saveData = GetCurrentSavePtr();
        if (GivePart(_saveData->airbrakeLevel, level)) {
            _saveData->airbrakeHealth = 0xFF;
        }
    }

    void SaveManager::GiveCoolingPart(int level) {
        SaveData* _saveData = GetCurrentSavePtr();
        if (GivePart(_saveData->coolingLevel, level)) {
            _saveData->coolingHealth = 0xFF;
        }
    }

    void SaveManager::GiveRepairPart(int level) {
        SaveData* _saveData = GetCurrentSavePtr();
        if (GivePart(_saveData->repairLevel, level)) {
            _saveData->repairHealth = 0xFF;
        }
    }

    int SaveManager::GetPartLevel(int part) {
        SaveData* _saveData = GetCurrentSavePtr();
        if ((part < TRACTION_PART) || (part > REPAIR_PART))
            return -1;

        auto ptr = &_saveData->tractionLevel + part;
        return static_cast<int>(*ptr);
    }

    int SaveManager::GetCircuitUnlocks(int circuit) {
        SaveData* _saveData = GetCurrentSavePtr();
        if ((circuit < AMATEUR_CIRCUIT) || (circuit > INVITATIONAL_CIRCUIT))
            return 0;

        auto ptr = &_saveData->amateurUnlocks + circuit;
        return static_cast<int>(*ptr);
    }

    int SaveManager::GetPartHealth(int part) {
        SaveData* _saveData = GetCurrentSavePtr();
        if ((part < TRACTION_PART) || (part > REPAIR_PART))
            return -1;

        auto ptr = &_saveData->tractionHealth + part;
        return static_cast<int>(*ptr);
    }

    std::vector<RacerUnlocks> SaveManager::GetRacerUnlockLocations() {
        std::vector<RacerUnlocks> checks;
        SaveData* _saveData = GetCurrentSavePtr();
        
        for (int i = 1; i < static_cast<int>(RacerUnlocks::BullseyeNavior) << 1; i <<= 1) {
            if (_saveData->racerUnlocks & i) {
                checks.push_back(static_cast<RacerUnlocks>(i));
            }
        }
        
        return checks;
    }

    void SaveManager::SetPartialSeed(unsigned long long partialSeed) {
        if (onlineSave != nullptr)
            onlineSave->apPartialSeed = partialSeed;
    }

    unsigned long long SaveManager::GetPartialSeed() {
        if (onlineSave != nullptr)
            return onlineSave->apPartialSeed;
        
        return 0;
    }

    void SaveManager::SetCourseAsCompleted(int circuit, int index) {
        SaveData* _saveData = GetCurrentSavePtr();
        int flag = 1 << ((circuit * 7) + index);
        _saveData->coursesCompleted |= flag;

        int placement = 0b11 << (index * 2);
        
        switch (circuit) {
        case AMATEUR_CIRCUIT:
            _saveData->amateurRacePlacements |= placement;
            break;
        case SEMIPRO_CIRCUIT:
            _saveData->semiproRacePlacements |= placement;
            break;
        case GALACTIC_CIRCUIT:
            _saveData->galacticRacePlacements |= placement;
            break;
        case INVITATIONAL_CIRCUIT:
            _saveData->invitationalRacePlacements |= placement;
            break;
        default:
            break;
        }
    }

    int SaveManager::GetCompletedCourseBitfield() {
        SaveData* _saveData = GetCurrentSavePtr();
        return _saveData->coursesCompleted;
    }

    int SaveManager::GetCompletedCourseCount() {
        SaveData* _saveData = GetCurrentSavePtr();
        int count = 0;
        int flag;

        for (int i = 0; i < 25; i++)
        {
            flag = 1 << i;
            if ((_saveData->coursesCompleted & flag) != 0)
                count++;
        }

        return count;
    }

    int SaveManager::GetFirstLockedCircuit() {
        SaveData* _saveData = GetCurrentSavePtr();
        for (int i = 0; i < 4; i++) {
            auto unlocksPtr = &_saveData->amateurUnlocks + i; 
            if (*unlocksPtr == 0)
                return i;
        }

        return NO_CIRCUIT;
    }
}