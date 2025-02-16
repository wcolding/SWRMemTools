#include <catch2/catch_test_macros.hpp>

#include "../src/Save.h"

TEST_CASE("SaveManager initialize works") {
	SWR_SaveData save;
	SaveManager sm(&save);
	sm.InitializeSaveData();

	REQUIRE(save.amateurUnlocks == 1);
	REQUIRE(save.semiproUnlocks == 0);
	REQUIRE(save.galacticUnlocks == 0);
	REQUIRE(save.invitationalUnlocks == 0);
	REQUIRE(save.money == 3000);
}