#pragma once

#include <utility>

#include <GLFW/glfw3.h>

#include "engine/input/Key.hpp"
#include "engine/input/MouseButton.hpp"

namespace engine {
    class Input {
    public:
        static bool isKeyPressed(Key key);
        static bool isMouseButtonDown(MouseButton button);
        static bool isMouseButtonLeftDown();
        static bool isMouseButtonRightDown();
        static std::pair<float, float> getMousePosition();
        static float getMouseX();
        static float getMouseY();

        static void setWindow(GLFWwindow* window) { s_window = window; }

    private:
        static GLFWwindow* s_window;
    };
}
