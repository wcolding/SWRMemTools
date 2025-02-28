#pragma once

namespace SWRMemTools {
    enum class ShopModel : int {
        Jabba = 0x71,
        Watto = 0x6E,
        Ithorian = 0xF4,
        PitDroid = 0x6D,
        Dewback = 0x6F,

        Traction2 = 0xCD,
        Traction3 = 0xCE,
        Traction4 = 0xE6,
        Traction5 = 0xF1,
        Traction6 = 0xF2,

        Turning2 = 0x33,
        Turning3 = 0x34,
        Turning4 = 0x35,
        Turning5 = 0x36,
        Turning6 = 0xF0,

        Acceleration2 = 0xC7,
        Acceleration3 = 0xC8,
        Acceleration4 = 0xC9,
        Acceleration5 = 0xCA,
        Acceleration6 = 0xCB,

        TopSpeed2 = 0xAA,
        TopSpeed3 = 0xAB,
        TopSpeed4 = 0xAC,
        TopSpeed5 = 0xAD,
        TopSpeed6 = 0xAE,

        AirBrake2 = 0x9E,
        AirBrake3 = 0x9F,
        AirBrake4 = 0xA0,
        AirBrake5 = 0xA1,
        AirBrake6 = 0xA2,

        Cooling2 = 0xA4,
        Cooling3 = 0xA5,
        Cooling4 = 0xA6,
        Cooling5 = 0xA7,
        Cooling6 = 0xA8,

        Repair2 = 0xEB,
        Repair3 = 0xED,
        Repair4 = 0xEE,
        Repair5 = 0xEF,
        Repair6 = 0xF3,

        Anakin = 0x57,
        Teemto = 0x56,
        Sebulba = 0x5B,
        Ratts = 0x5D,
        Aldar = 0x69,
        Mawhonic = 0x59,
        Bumpy = 0x60,
        Wan = 0x63,
        Mars = 0x5C,
        Ebe = 0x5F,
        Dud = 0x62,
        Gasgano = 0x58,
        Clegg = 0x61,
        Elan = 0x64,
        Neva = 0x67,
        Bozzie = 0x6A,
        Boles = 0x6B,
        Ody = 0x5A,
        Fud = 0x66,
        Ben = 0x5E,
        Slide = 0x68,
        Toy = 0x65,
        Bullseye = 0x6C
    };

    inline bool operator==(int a, ShopModel b) {
        return a == static_cast<int>(b);
    }
}