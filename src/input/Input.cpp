#include "engine/input/Input.hpp"

#include "engine/input/MouseButton.hpp"

namespace engine {
    GLFWwindow* Input::s_window;

    bool Input::isKeyPressed(const Key key) {
        // GLFW_RELEASE is 0
        // GLFW_PRESS is 1
        // GLFW_REPEAT is 2
        return glfwGetKey(s_window, (int) key);
    }

    bool Input::isMouseButtonDown(const MouseButton button) {
        // GLFW_RELEASE is 0
        // GLFW_PRESS is 1
        return glfwGetMouseButton(s_window, (int) button);
    }

    bool Input::isMouseButtonLeftDown() {
        // GLFW_RELEASE is 0
        // GLFW_PRESS is 1
        return glfwGetMouseButton(s_window, (int) MouseButton::Left);
    }

    bool Input::isMouseButtonRightDown() {
        // GLFW_RELEASE is 0
        // GLFW_PRESS is 1
        return glfwGetMouseButton(s_window, (int) MouseButton::Right);
    }

    std::pair<float, float> Input::getMousePosition() {
        double x, y;
        glfwGetCursorPos(s_window, &x, &y);
        return {(float) x, (float) y};
    }

    float Input::getMouseX() {
        double x, y;
        glfwGetCursorPos(s_window, &x, &y);
        return (float) x;
    }

    float Input::getMouseY() {
        double x, y;
        glfwGetCursorPos(s_window, &x, &y);
        return (float) y;
    }
}
