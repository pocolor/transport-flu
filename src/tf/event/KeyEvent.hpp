#pragma once

#include "tf/core.hpp"

#include "Event.hpp"

#include <sstream>

namespace tf {
    class KeyEvent : public Event {
    public:
        i32 getKeyCode() const { return m_keyCode; }

        EVENT_CLASS_CATEGORY(EventCategory::Input | EventCategory::Keyboard)
    protected:
        explicit KeyEvent(i32 keyCode) : m_keyCode(keyCode) {}
        const i32 m_keyCode;
    };

    class KeyPressedEvent : public KeyEvent {
    public:
        explicit KeyPressedEvent(i32 keycode)
            : KeyEvent(keycode) {}

        str toString() const override {
            std::stringstream ss;
            ss << "KeyPressedEvent: keycode=" << m_keyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)
    };

    class KeyRepeatEvent : public KeyEvent {
    public:
        explicit KeyRepeatEvent(i32 keycode)
            : KeyEvent(keycode) {}

        str toString() const override {
            std::stringstream ss;
            ss << "KeyRepeatEvent: keycode=" << m_keyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)
    };

    class KeyReleasedEvent : public KeyEvent {
    public:
        explicit KeyReleasedEvent(i32 keycode)
            : KeyEvent(keycode) {}

        str toString() const override {
            std::stringstream ss;
            ss << "KeyReleasedEvent: keycode=" << m_keyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };
}