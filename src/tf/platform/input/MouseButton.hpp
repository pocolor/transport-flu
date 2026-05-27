#pragma once

#include "tf/core.hpp"

// borrowed from glfw3.h

namespace tf::mouse_button {
    constexpr i32 _1 = 0;
    constexpr i32 _2 = 1;
    constexpr i32 _3 = 2;
    constexpr i32 _4 = 3;
    constexpr i32 _5 = 4;
    constexpr i32 _6 = 5;
    constexpr i32 _7 = 6;
    constexpr i32 _8 = 7;

    constexpr i32 Last = _8;
    constexpr i32 Left = _1;
    constexpr i32 Right = _2;
    constexpr i32 Middle = _3;
}
