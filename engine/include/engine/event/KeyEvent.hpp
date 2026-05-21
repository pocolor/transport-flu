#pragma once

#include "engine/event/Event.hpp"

#include <sstream>

namespace engine {
    class KeyEvent : public Event {
    public:
        int getKeyCode() const { return m_keyCode; }

        EVENT_CLASS_CATEGORY(EventCategory::Input | EventCategory::Keyboard)
    protected:
        explicit KeyEvent(const int keyCode) : m_keyCode(keyCode) {}
        const int m_keyCode;
    };

    class KeyPressedEvent : public KeyEvent {
    public:
        explicit KeyPressedEvent(const int keycode)
            : KeyEvent(keycode) {}

        std::string toString() const override {
            std::stringstream ss;
            ss << "KeyPressedEvent: keycode=" << m_keyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)
    };

    class KeyRepeatEvent : public KeyEvent {
    public:
        KeyRepeatEvent(const int keycode)
            : KeyEvent(keycode) {}

        std::string toString() const override {
            std::stringstream ss;
            ss << "KeyRepeatEvent: keycode=" << m_keyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)
    };

    class KeyReleasedEvent : public KeyEvent {
    public:
        explicit KeyReleasedEvent(const int keycode)
            : KeyEvent(keycode) {}

        std::string toString() const override {
            std::stringstream ss;
            ss << "KeyReleasedEvent: keycode=" << m_keyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };
}