#pragma once

#include "tf/core.hpp"

#include <GLFW/glfw3.h>

namespace tf {
    class Time {
    public:
        Time() = delete;

        static f32 getDeltaTime() { return s_deltaTime; }

        static void init(GLFWwindow* handle) { s_handle = handle; }
        static void onUpdate();

    private:
        static GLFWwindow* s_handle;
        static f32 s_deltaTime;
        static f32 s_lastTime;
    };
}