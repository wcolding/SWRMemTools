#include <catch2/catch_test_macros.hpp>

#include "Shop.h"

using namespace SWRMemTools;

TEST_CASE("ShopManager functions work") {
    Shop shop;
    ShopManager sm(&shop);

    SECTION("Initialize works") {
        REQUIRE(shop.entries[0].requiredRaces == static_cast<char>(0xC0));
    }
}