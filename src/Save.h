#pragma once
#pragma pack(push)
#pragma pack(1)

struct SWR_SaveData {
public:
	char profileName[0x14];    // shortened from vanilla game to 16 characters + null + padding
	int racesCompleted;
	unsigned long long apPartialSeed;
private:
	char unk_00[0x02];
	unsigned short profileId;
public:
	char selectedRacer;
	char amateurUnlocks;
    char semiproUnlocks;
    char galacticUnlocks;
    char invitationalUnlocks;
	char progressivePasses;    // unk_01 being used to track progressive passes
	unsigned long long racePlacements;
private:
	char unk_02[0x02];
public:
	unsigned int racerUnlocks;
	int money;
	int cutscenesBitfield;
	char pitDroids;
    
    char tractionLevel;
    char turningLevel;
    char accelerationLevel;
    char topSpeedLevel;
    char airbrakeLevel;
    char coolingLevel;
    char repairLevel;

    char tractionHealth;
    char turningHealth;
    char accelerationHealth;
    char topSpeedHealth;
    char airbrakeHealth;
    char coolingHealth;
    char repairHealth;
private:
	char pad;
}; 
static_assert(sizeof(SWR_SaveData) == 0x50, "RacerSaveData resized!");

#pragma pack(pop)

class SaveManager {
public:
    SaveManager(SWR_SaveData* saveData);
    void InitializeSaveData();
    void GiveMoney(int amount);
    void GivePitDroid();
    
private:
    SWR_SaveData* _saveData;
};