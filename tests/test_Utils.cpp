#include <catch2/catch_test_macros.hpp>

#include "Utils.h"

using namespace SWRMemTools;

TEST_CASE("Partial seed conversion works") {
	unsigned long long partialA = ConvertToPartialSeed("0123456789101112");
	unsigned long long partialB = ConvertToPartialSeed("7777444499993333");

	REQUIRE(partialA == 1234567);
	REQUIRE(partialB == 77774444);
}