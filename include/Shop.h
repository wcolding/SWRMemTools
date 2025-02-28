#pragma once
#include "Models.h"

namespace SWRMemTools {

#pragma pack(push)
#pragma pack(1)
    struct ShopEntry {
        char globalId;
        char seriesId;
        char requiredRaces;
        char itemType;
        int cost;
        int modelId;
        char* displayText;
    };

    struct Shop {
        ShopEntry entries[42];
    };
#pragma pack(pop)

    enum class ShopItemFlags {
        ProgressivePart = 0x20,
        Hidden          = 0x40,
        Purchased       = 0x80
    };

    inline char operator|=(char& a, ShopItemFlags b) {
        return a = a | static_cast<int>(b);
    }

    inline char operator|(ShopItemFlags a, ShopItemFlags b) {
        return static_cast<int>(a) | static_cast<int>(b);
    }

    inline char operator&(char a, ShopItemFlags b) {
        return a & static_cast<int>(b);
    }

    class ShopManager {
    public:
        ShopManager(Shop* shop);
        void SetModel(int index, ShopModel model);

    private:
        Shop* _shop;
    };
}