#include "Shop.h"

#include <vector>

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

    std::vector<std::vector<ShopModel>> progressiveItemModels = {
        { ShopModel::Traction2, ShopModel::Traction3, ShopModel::Traction4, ShopModel::Traction5, ShopModel::Traction6 },
        { ShopModel::Turning2, ShopModel::Turning3, ShopModel::Turning4, ShopModel::Turning5, ShopModel::Turning6 },
        { ShopModel::Acceleration2, ShopModel::Acceleration3, ShopModel::Acceleration4, ShopModel::Acceleration5, ShopModel::Acceleration6 },
        { ShopModel::TopSpeed2, ShopModel::TopSpeed3, ShopModel::TopSpeed4, ShopModel::TopSpeed5, ShopModel::TopSpeed6 },
        { ShopModel::AirBrake2, ShopModel::AirBrake3, ShopModel::AirBrake4, ShopModel::AirBrake5, ShopModel::AirBrake6 },
        { ShopModel::Cooling2, ShopModel::Cooling3, ShopModel::Cooling4, ShopModel::Cooling5, ShopModel::Cooling6 },
        { ShopModel::Repair2, ShopModel::Repair3, ShopModel::Repair4, ShopModel::Repair5, ShopModel::Repair6 }
    };
    
    void ShopManager::SetProgressiveItemModel(int index, int partType, int partLevel) {
        if ((partType < 0) || (partType > 6))
            return;

        if ((partLevel < 0) || (partLevel > 4))
            return;

        SetModel(index, progressiveItemModels[partType][partLevel]);
    }

    void ShopManager::SetAPItem(int index) {
        if ((index < 0) || (index > 41))
            return;

        _shop->entries[index].itemType = 7;
        _shop->entries[index].seriesId = 0;
        SetModel(index, ShopModel::Jabba);
    }

    int ShopManager::GetAvailableShopChecks(int coursesCompleted) {
        int count = 0;

        for (auto entry : _shop->entries) {
            if ((entry.requiredRaces & ShopItemFlags::Purchased) == 0) {
                int maskedrequiredRaces = entry.requiredRaces & 0x1F;
                if (maskedrequiredRaces <= coursesCompleted) {
                    count++;
                }
            }
        }

        return count;
    }
}