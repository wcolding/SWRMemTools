#pragma once
#pragma pack(push)
#pragma pack(1)

namespace SWRMemTools {
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

    enum RacerUnlocks : int {
        None            = 0x00000000,
        AnakinSkywalker = 0x00000001,
        TeemtoPagalies  = 0x00000002,
        Sebulba         = 0x00000004,
        RattsTyerell    = 0x00000008,
        AldarBeedo      = 0x00000010,
        Mawhonic        = 0x00000020,
        ArkBumpyRoose   = 0x00000040,
        WanSandage      = 0x00000080,
        MarsGuo         = 0x00000100,
        EbeEndocott     = 0x00000200,
        DudBolt         = 0x00000400,
        Gasgano         = 0x00000800,
        CleggHoldfast   = 0x00001000,
        ElanMak         = 0x00002000,
        NevaKee         = 0x00004000,
        BozzieBaranta   = 0x00008000,
        BolesRoor       = 0x00010000,
        OdyMandrell     = 0x00020000,
        FudSang         = 0x00040000,
        BenQuadrinaros  = 0x00080000,
        SlideParamita   = 0x00100000,
        ToyDampner      = 0x00200000,
        BullseyeNavior  = 0x00400000
    };

    inline RacerUnlocks operator|=(RacerUnlocks& a, RacerUnlocks b) {
        return a = static_cast<RacerUnlocks>(static_cast<int>(a) | static_cast<int>(b));
    }

    class SaveManager {
    public:
        SaveManager(SWR_SaveData* saveData);
        void InitializeSaveData();
        void GiveMoney(int amount);
        void GivePitDroid();
        void GiveRacer(RacerUnlocks racer);
        void GiveAmateurCourse();
        void GiveSemiproCourse();
        void GiveGalacticCourse();
        void GiveInvitationalCourse();
        void GiveTractionPart(int level = -1);
        void GiveTurningPart(int level = -1);
        void GiveAccelerationPart(int level = -1);
        void GiveTopSpeedPart(int level = -1);
        void GiveAirbrakePart(int level = -1);
        void GiveCoolingPart(int level = -1);
        void GiveRepairPart(int level = -1);

        bool isSaveReady();

        RacerUnlocks apRacerUnlocks = RacerUnlocks::None;
        
    private:
        SWR_SaveData* _saveData;

        int amateurCoursesReceived = 1;
        int semiproCoursesReceived = 0;
        int galacticCoursesReceived = 0;
        int invitationalCoursesReceived = 0;

        void RecalculateCourseUnlockFlags();
    };
}