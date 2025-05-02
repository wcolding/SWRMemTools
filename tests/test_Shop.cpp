#include <catch2/catch_test_macros.hpp>

#include "Shop.h"
#include "Save.h"

using namespace SWRMemTools;

TEST_CASE("ShopManager functions work") {
    Shop shop;
    ShopManager sm(&shop);

    SECTION("Initialize works") {
        REQUIRE(shop.entries[0].requiredRaces == static_cast<char>(0xC0));
    }

    SECTION("SetModel works") {
         sm.SetModel(2, ShopModel::Watto);
         REQUIRE(shop.entries[2].modelId == ShopModel::Watto);
         sm.SetModel(2, ShopModel::Dewback);
         REQUIRE(shop.entries[2].modelId == ShopModel::Dewback);
    }

    SECTION("Progressive functions work") {
        SaveData save;
        SaveData* savePtr = &save;
        SaveManager svMan(&savePtr);

        svMan.InitializeSaveData();
        REQUIRE(svMan.GetPartLevel(TRACTION_PART) == 0);
        sm.SetProgressiveItemModel(2, TRACTION_PART, svMan.GetPartLevel(TRACTION_PART));
        REQUIRE(shop.entries[2].modelId == ShopModel::Traction2);
        
        svMan.GiveTractionPart();
        sm.SetProgressiveItemModel(2, TRACTION_PART, svMan.GetPartLevel(TRACTION_PART));
        REQUIRE(shop.entries[2].modelId == ShopModel::Traction3);

        svMan.GiveCoolingPart(4);
        sm.SetProgressiveItemModel(3, COOLING_PART, svMan.GetPartLevel(COOLING_PART));
        REQUIRE(shop.entries[3].modelId == ShopModel::Cooling6);
    }

    SECTION("SetItem functions work") {
        sm.SetAPItem(12);
        REQUIRE(shop.entries[12].itemType == 7);
        REQUIRE(shop.entries[12].modelId == ShopModel::Jabba);
    }

    SECTION("Can get available shop checks") {
        for (int i = 0; i < 42; i++) {
            shop.entries[i].requiredRaces = 2;
        }
        REQUIRE(sm.GetAvailableShopChecks(2) == 42);
        REQUIRE(sm.GetAvailableShopChecks(0) == 0);

        shop.entries[4].requiredRaces |= ShopItemFlags::Purchased;
        REQUIRE(sm.GetAvailableShopChecks(2) == 41);
    }
}