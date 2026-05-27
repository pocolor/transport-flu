#include "tf/pch.hpp"

#include "Time.hpp"

namespace tf {
    GLFWwindow* Time::s_handle = nullptr;
    f32 Time::s_deltaTime;
    f32 Time::s_lastTime;

    void Time::onUpdate() {
        f32 time = (f32) glfwGetTime();
        s_deltaTime = time - s_lastTime;
        s_lastTime = time;
    }
}
