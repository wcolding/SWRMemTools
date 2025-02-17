#include <catch2/catch_test_macros.hpp>

TEST_CASE("Tests are compiled 32bit") {
	REQUIRE(sizeof(size_t) == 4);
}