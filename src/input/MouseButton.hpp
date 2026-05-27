#pragma once

// borrowed from glfw3.h

namespace engine {
    enum class MouseButton : int {
        _1 = 0,
        _2 = 1,
        _3 = 2,
        _4 = 3,
        _5 = 4,
        _6 = 5,
        _7 = 6,
        _8 = 7,

        Last = _8,
        Left = _1,
        Right = _2,
        Middle = _3,
    };
}
