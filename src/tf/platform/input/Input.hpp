#pragma once

#include "tf/core.hpp"

#include "Key.hpp"
#include "MouseButton.hpp"

#include <GLFW/glfw3.h>

namespace tf {
    class Input {
    public:
        static bool isKeyDown(i32 key) { TF_ENGINE_ASSERT(key >= 0 && key <= key::Last); return s_keysDown[key]; }
        static bool isMouseButtonDown(i32 button) { TF_ENGINE_ASSERT(button >= 0 && button <= mouse_button::Last); return s_mouseButtonsDown[button]; }
        static f32 getMousePositionX() { return s_mousePositionX; }
        static f32 getMousePositionY() { return s_mousePositionY; }
        static vec2 getMousePosition() { return { getMousePositionX(), getMousePositionY() }; }
        static f32 getMouseDeltaPositionX() { return s_mouseDeltaPositionX; }
        static f32 getMouseDeltaPositionY() { return s_mouseDeltaPositionY; }
        static vec2 getMouseDeltaPosition() { return { getMouseDeltaPositionX(), getMouseDeltaPositionY() }; }
        static f32 getMouseWheel() { return s_mouseWheel; }
        static f32 getMouseDeltaWheel() { return s_mouseDeltaWheel; }

        static void init(GLFWwindow* handle);
        static void onUpdate();

    private:
        static void scrollCallback(GLFWwindow* handle, double xOffset, double yOffset);

    private:
        static GLFWwindow* s_handle;
        static bool s_keysDown[key::Last + 1];
        static bool s_mouseButtonsDown[mouse_button::Last + 1];
        static f32 s_mousePositionX;
        static f32 s_mousePositionY;
        static f32 s_mouseDeltaPositionX;
        static f32 s_mouseDeltaPositionY;
        static f32 s_mouseWheel;
        static f32 s_mouseDeltaWheel;
        static f32 s_mousePendingWheel;
    };
}
