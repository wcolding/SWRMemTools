#include <catch2/catch_test_macros.hpp>

#include "../src/Save.h"

TEST_CASE("SaveManager functions work") {
	SWR_SaveData save;
	SaveManager sm(&save);
	sm.InitializeSaveData();

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

	SECTION("GiveCourse") {
		sm.GiveAmateurCourse();
		REQUIRE(save.amateurUnlocks == 0b00000011);

		sm.GiveSemiproCourse();
		sm.GiveSemiproCourse();
		REQUIRE(save.semiproUnlocks == 0b00000011);

		sm.GiveGalacticCourse();
		sm.GiveGalacticCourse();
		sm.GiveGalacticCourse();
		REQUIRE(save.galacticUnlocks == 0b00000111);

		sm.GiveInvitationalCourse();
		REQUIRE(save.invitationalUnlocks == 0b00000001);

		REQUIRE(save.galacticUnlocks == 0b00000111);
	}
}