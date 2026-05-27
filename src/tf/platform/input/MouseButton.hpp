#pragma once

#include "tf/core.hpp"

#include <GLFW/glfw3.h>

namespace tf::mouse_button {
    constexpr i32 _1 = GLFW_MOUSE_BUTTON_1;
    constexpr i32 _2 = GLFW_MOUSE_BUTTON_2;
    constexpr i32 _3 = GLFW_MOUSE_BUTTON_3;
    constexpr i32 _4 = GLFW_MOUSE_BUTTON_4;
    constexpr i32 _5 = GLFW_MOUSE_BUTTON_5;
    constexpr i32 _6 = GLFW_MOUSE_BUTTON_6;
    constexpr i32 _7 = GLFW_MOUSE_BUTTON_7;
    constexpr i32 _8 = GLFW_MOUSE_BUTTON_8;

    constexpr i32 Last = GLFW_MOUSE_BUTTON_LAST;
    constexpr i32 Left = GLFW_MOUSE_BUTTON_LEFT;
    constexpr i32 Right = GLFW_MOUSE_BUTTON_RIGHT;
    constexpr i32 Middle = GLFW_MOUSE_BUTTON_MIDDLE;
}
