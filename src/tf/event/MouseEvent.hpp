#pragma once

#include "tf/core.hpp"

#include "Event.hpp"

#include <sstream>

namespace tf {
    class MouseMovedEvent : public Event {
    public:
        explicit MouseMovedEvent(vec2 pos)
            : m_pos(pos) {}

        vec2 getPos() const { return m_pos; }

        str toString() const override {
            std::stringstream ss;
            ss << "MouseMovedEvent: x=" << m_pos.x << ", y=" << m_pos.y;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved);
        EVENT_CLASS_CATEGORY(EventCategory::Input | EventCategory::Mouse)
    private:
        const vec2 m_pos;
    };

    class MouseScrolledEvent : public Event {
    public:
        explicit MouseScrolledEvent(vec2 offset)
            : m_offset(offset) {}

        vec2 getOffset() const { return m_offset; }

        str toString() const override {
            std::stringstream ss;
            ss << "MouseScrolledEvent: xOffset=" << m_offset.x << ", yOffset=" << m_offset.y;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseScrolled);
        EVENT_CLASS_CATEGORY(EventCategory::Input | EventCategory::Mouse)
    private:
        const vec2 m_offset;
    };

    class MouseButtonEvent : public Event {
    public:
        i32 getMouseButton() const { return m_button; }

        EVENT_CLASS_CATEGORY(EventCategory::Input | EventCategory::Mouse)
    protected:
        explicit MouseButtonEvent(i32 button)
            : m_button(button) {}

        const i32 m_button;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent {
    public:
        explicit MouseButtonPressedEvent(i32 button)
            : MouseButtonEvent(button) {}

        str toString() const override {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: button=" << m_button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonPressed);
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent {
    public:
        explicit MouseButtonReleasedEvent(i32 button)
            : MouseButtonEvent(button) {}

        str toString() const override {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: button=" << m_button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonReleased);
    };
}