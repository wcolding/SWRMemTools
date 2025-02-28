#include "Shop.h"

namespace SWRMemTools{
    ShopManager::ShopManager(Shop* shop) {
        _shop = shop;

        // Hide starting item entries in shop
        for (int i = 0; i < 6; i++) {
            _shop->entries[i * 6].requiredRaces = ShopItemFlags::Hidden | ShopItemFlags::Purchased;
        }
    }

    void ShopManager::SetModel(int index, ShopModel model) {
        if ((index < 0) || (index > 41))
            return;

        _shop->entries[index].modelId = static_cast<int>(model);
    }
}