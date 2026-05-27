#include "tf/pch.hpp"

#include "Input.hpp"

namespace tf {
    GLFWwindow* Input::s_handle = nullptr;
    bool Input::s_keysDown[];
    bool Input::s_mouseButtonsDown[];
    f32 Input::s_mousePositionX;
    f32 Input::s_mousePositionY;
    f32 Input::s_mouseDeltaPositionX;
    f32 Input::s_mouseDeltaPositionY;
    f32 Input::s_mouseWheel;
    f32 Input::s_mouseDeltaWheel;
    f32 Input::s_mousePendingWheel;

    static constexpr i32 s_validKeys[] = {
        key::Space,
        key::Apostrophe,
        key::Comma,
        key::Minus,
        key::Dot,
        key::Slash,
        key::_0,
        key::_1,
        key::_2,
        key::_3,
        key::_4,
        key::_5,
        key::_6,
        key::_7,
        key::_8,
        key::_9,
        key::Semicolon,
        key::Equal,
        key::A,
        key::B,
        key::C,
        key::D,
        key::E,
        key::F,
        key::G,
        key::H,
        key::I,
        key::J,
        key::K,
        key::L,
        key::M,
        key::N,
        key::O,
        key::P,
        key::Q,
        key::R,
        key::S,
        key::T,
        key::U,
        key::V,
        key::W,
        key::X,
        key::Y,
        key::Z,
        key::LeftBracket,
        key::Backslash,
        key::RightBracket,
        key::GraveAccent,
        key::Escape,
        key::Enter,
        key::Tab,
        key::Backspace,
        key::Insert,
        key::Delete,
        key::ArrowRight,
        key::ArrowLeft,
        key::ArrowDown,
        key::ArrowUp,
        key::PageUp,
        key::PageDown,
        key::Home,
        key::End,
        key::CapsLock,
        key::ScrollLock,
        key::NumLock,
        key::PrintScreen,
        key::Pause,
        key::F1,
        key::F2,
        key::F3,
        key::F4,
        key::F5,
        key::F6,
        key::F7,
        key::F8,
        key::F9,
        key::F10,
        key::F11,
        key::F12,
        key::F13,
        key::F14,
        key::F15,
        key::F16,
        key::F17,
        key::F18,
        key::F19,
        key::F20,
        key::F21,
        key::F22,
        key::F23,
        key::F24,
        key::F25,
        key::KP_0,
        key::KP_1,
        key::KP_2,
        key::KP_3,
        key::KP_4,
        key::KP_5,
        key::KP_6,
        key::KP_7,
        key::KP_8,
        key::KP_9,
        key::KP_Decimal,
        key::KP_Divide,
        key::KP_Multiply,
        key::KP_Subtract,
        key::KP_Add,
        key::KP_Enter,
        key::KP_Equal,
        key::LeftShift,
        key::LeftControl,
        key::LeftAlt,
        key::LeftSuper,
        key::RightShift,
        key::RightControl,
        key::RightAlt,
        key::RightSuper,
        key::Menu,
    };

    static constexpr i32 s_validMouseButtons[] = {
        mouse_button::_1,
        mouse_button::_2,
        mouse_button::_3,
        mouse_button::_4,
        mouse_button::_5,
        mouse_button::_6,
        mouse_button::_7,
        mouse_button::_8,
    };

    void Input::init() {
        glfwSetScrollCallback(s_handle, scrollCallback);

        double x, y;
        glfwGetCursorPos(s_handle, &x, &y);
        s_mousePositionX = (f32)x;
        s_mousePositionY = (f32)y;

        for (i32 k = 0; k < key::Last + 1; ++k) {
            s_keysDown[k] = false;
        }

        for (i32 m = 0; m < mouse_button::Last + 1; ++m) {
            s_keysDown[m] = false;
        }
    }

    void Input::onUpdate() {
        glfwPollEvents();

        for (i32 k : s_validKeys) {
            i32 state = glfwGetKey(s_handle, k);
            s_keysDown[k] = state == GLFW_PRESS || state == GLFW_REPEAT;
        }

        for (i32 m : s_validMouseButtons) {
            i32 state = glfwGetMouseButton(s_handle, m);
            s_mouseButtonsDown[m] = state == GLFW_PRESS || state == GLFW_REPEAT;
        }

        f64 xPos, yPos;
        glfwGetCursorPos(s_handle, &xPos, &yPos);

        f32 x = (f32)xPos, y = (f32)yPos;

        s_mouseDeltaPositionX = x - s_mousePositionX;
        s_mouseDeltaPositionY = y - s_mousePositionY;
        s_mousePositionX = x;
        s_mousePositionY = y;

        s_mouseDeltaWheel = s_mousePendingWheel;
        s_mouseWheel += s_mouseDeltaWheel;
        s_mousePendingWheel = 0.0;
    }

    void Input::scrollCallback(GLFWwindow* handle, double xOffset, double yOffset) {
        s_mousePendingWheel += (f32) yOffset;
    }
}
