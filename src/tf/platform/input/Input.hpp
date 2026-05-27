#pragma once

#include "tf/core.hpp"

#include <GLFW/glfw3.h>

namespace tf {
    class Input {
    public:
        static bool isKeyDown(i32 key);
        static bool isMouseButtonDown(i32 button);
        static vec2 getMousePosition();
        static vec2 getMouseDeltaPosition();
        static f32 getMouseWheel();
        static f32 getMouseDeltaWheel();

        static void setHandle(GLFWwindow* window) { s_handle = window; }

    private:
        static GLFWwindow* s_handle;
    };
}
