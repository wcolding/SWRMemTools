#include <catch2/catch_test_macros.hpp>

#include "Save.h"
#include "Utils.h"
#include <algorithm>

using namespace SWRMemTools;

TEST_CASE("SaveManager functions work") {
	SaveData save;
	SaveManager sm(&save);
	sm.InitializeSaveData();

	SECTION("Can check if save is ready") {
		SaveManager nullSaveManager(nullptr);
		REQUIRE(nullSaveManager.isSaveReady() == false);
		REQUIRE(sm.isSaveReady() == true);
	}

	SECTION("Initialize function works") {
		REQUIRE(save.amateurUnlocks == 1);
		REQUIRE(save.semiproUnlocks == 0);
		REQUIRE(save.galacticUnlocks == 0);
		REQUIRE(save.invitationalUnlocks == 0);
		REQUIRE(save.money == 3000);
	}

	SECTION("GiveMoney works") {
		sm.GiveMoney(200);
		REQUIRE(save.money == 3200);
		sm.GiveMoney(60);
		REQUIRE(save.money == 3260);
	}

	SECTION("GivePitDroid works") {
		sm.GivePitDroid();
		sm.GivePitDroid();
		REQUIRE(save.pitDroids == 2);
	}

	SECTION("Give Racer works") {
		sm.GiveRacer(RacerUnlocks::BolesRoor);
		sm.GiveRacer(RacerUnlocks::FudSang);
		REQUIRE((sm.apRacerUnlocks & RacerUnlocks::Sebulba) == 0);
		REQUIRE((sm.apRacerUnlocks & RacerUnlocks::BolesRoor) != 0);
		REQUIRE((sm.apRacerUnlocks & RacerUnlocks::FudSang) != 0);
	}

	SECTION("Give Courses works") {
		sm.GiveAmateurCourse();
		REQUIRE(sm.GetCircuitUnlocks(AMATEUR_CIRCUIT) == 0b00000011);

		sm.GiveSemiproCourse();
		sm.GiveSemiproCourse();
		REQUIRE(sm.GetCircuitUnlocks(SEMIPRO_CIRCUIT) == 0b00000011);

		sm.GiveGalacticCourse();
		sm.GiveGalacticCourse();
		sm.GiveGalacticCourse();
		REQUIRE(sm.GetCircuitUnlocks(GALACTIC_CIRCUIT) == 0b00000111);

		sm.GiveInvitationalCourse();
		REQUIRE(sm.GetCircuitUnlocks(INVITATIONAL_CIRCUIT) == 0b00000001);

		REQUIRE(save.galacticUnlocks == 0b00000111);
	}

	SECTION("Give Parts") {
		sm.GiveTractionPart();
		REQUIRE(save.tractionLevel == 1);
		sm.GiveTractionPart(3);
		REQUIRE(save.tractionLevel == 3);
		sm.GiveTractionPart();
		REQUIRE(save.tractionLevel == 4);

		save.tractionHealth = 0x10;
		REQUIRE(sm.GetPartHealth(TRACTION_PART) == static_cast<char>(0x10));
		sm.GiveTractionPart(8);
		REQUIRE(save.tractionLevel == 5);
		REQUIRE(sm.GetPartHealth(TRACTION_PART) == static_cast<char>(0xFF));
		
		sm.GiveTractionPart(2);
		REQUIRE(save.tractionLevel == 5);

		sm.GiveTurningPart(1);
		sm.GiveAccelerationPart(2);
		sm.GiveTopSpeedPart(3);
		sm.GiveAirbrakePart(4);
		sm.GiveCoolingPart(5);
		sm.GiveRepairPart(1);

		REQUIRE(save.turningLevel == 1);
		REQUIRE(save.accelerationLevel == 2);
		REQUIRE(save.topSpeedLevel == 3);
		REQUIRE(save.airbrakeLevel == 4);
		REQUIRE(save.coolingLevel == 5);
		REQUIRE(save.repairLevel == 1);

		REQUIRE(sm.GetPartLevel(AIR_BRAKE_PART) == 4);
		REQUIRE(sm.GetPartLevel(COOLING_PART) == 5);
		sm.GiveAirbrakePart();
		REQUIRE(sm.GetPartLevel(AIR_BRAKE_PART) == 5);

		REQUIRE(sm.GetPartLevel(10) == -1);
	}

	SECTION("Get Racer Unlock Locations") {
		auto checks = sm.GetRacerUnlockLocations();
		REQUIRE(checks.empty() == true);

		save.racerUnlocks |= RacerUnlocks::BenQuadrinaros;
		checks = sm.GetRacerUnlockLocations();
		REQUIRE(checks.size() == 1);

		save.racerUnlocks |= RacerUnlocks::NevaKee;
		checks = sm.GetRacerUnlockLocations();
		REQUIRE(checks.size() == 2);

		auto res = std::find(checks.begin(), checks.end(), RacerUnlocks::BenQuadrinaros);
		REQUIRE_FALSE(res == checks.end());
		res = std::find(checks.begin(), checks.end(), RacerUnlocks::NevaKee);
		REQUIRE_FALSE(res == checks.end());
		res = std::find(checks.begin(), checks.end(), RacerUnlocks::Gasgano);
		REQUIRE(res == checks.end());

		save.racerUnlocks |= RacerUnlocks::BullseyeNavior;
		checks = sm.GetRacerUnlockLocations();
		REQUIRE(checks.size() == 3);
		res = std::find(checks.begin(), checks.end(), RacerUnlocks::BullseyeNavior);
		REQUIRE_FALSE(res == checks.end());
	}

	SECTION("Set/Get Partial Seed") {
		sm.SetPartialSeed(ConvertToPartialSeed("0123456789101112"));
		REQUIRE(sm.GetPartialSeed() == 1234567);

		sm.SetPartialSeed(ConvertToPartialSeed("7777444499993333"));
		REQUIRE(sm.GetPartialSeed() == 77774444);
	}

	SECTION("Check completed courses") {
		save.coursesCompleted = 0x01;
		REQUIRE(sm.GetCompletedCourseCount() == 1);
		sm.SetCourseAsCompleted(0);
		REQUIRE(sm.GetCompletedCourseCount() == 1);
		sm.SetCourseAsCompleted(2);
		REQUIRE(save.coursesCompleted == 0x05);
		REQUIRE(sm.GetCompletedCourseCount() == 2);
	}
}