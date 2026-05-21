#pragma once

#include "engine/event/Event.hpp"

#include <sstream>

namespace engine {
    class MouseMovedEvent : public Event {
    public:
        MouseMovedEvent(const float x, const float y)
            : m_x(x), m_y(y) {}

        float getX() const { return m_x; }
        float getY() const { return m_y; }

        std::string toString() const override {
            std::stringstream ss;
            ss << "MouseMovedEvent: x=" << m_x << ", y=" << m_y;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved);
        EVENT_CLASS_CATEGORY(EventCategory::Input | EventCategory::Mouse)
    private:
        const float m_x, m_y;
    };

    class MouseScrolledEvent : public Event {
    public:
        MouseScrolledEvent(const float xOffset, const float yOffset)
            : m_xOffset(xOffset), m_yOffset(yOffset) {}

        float getXOffset() const { return m_xOffset; }
        float getYOffset() const { return m_yOffset; }

        std::string toString() const override {
            std::stringstream ss;
            ss << "MouseScrolledEvent: xOffset=" << m_xOffset << ", yOffset=" << m_yOffset;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseScrolled);
        EVENT_CLASS_CATEGORY(EventCategory::Input | EventCategory::Mouse)
    private:
        const float m_xOffset, m_yOffset;
    };

    class MouseButtonEvent : public Event {
    public:
        int getMouseButton() const { return m_button; }

        EVENT_CLASS_CATEGORY(EventCategory::Input | EventCategory::Mouse)
    protected:
        explicit MouseButtonEvent(const int button)
            : m_button(button) {}

        const int m_button;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent {
    public:
        explicit MouseButtonPressedEvent(const int button)
            : MouseButtonEvent(button) {}

        std::string toString() const override {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: button=" << m_button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonPressed);
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent {
    public:
        explicit MouseButtonReleasedEvent(const int button)
            : MouseButtonEvent(button) {}

        std::string toString() const override {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: button=" << m_button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonReleased);
    };
}