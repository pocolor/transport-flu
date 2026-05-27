#pragma once

#include "engine/event/Event.hpp"

#include <cstdint>
#include <sstream>

namespace engine {
    class WindowCloseEvent : public Event {
    public:
        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategory::Application)
    };

    class WindowResizeEvent : public Event {
    public:
        WindowResizeEvent(const uint32_t width, const uint32_t height, const bool fullscreen)
            : m_width(width), m_height(height), m_fullscreen(fullscreen) {}

        std::string toString() const override {
            std::stringstream ss;
            ss << "WindowResizeEvent: width=" << m_width <<
                    ", height=" << m_height <<
                    ", fullscreen=" << m_fullscreen;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(EventCategory::Application)

    private:
        const uint32_t m_width, m_height;
        const bool m_fullscreen;
    };

    class WindowFocusEvent : public Event {
    public:
        EVENT_CLASS_TYPE(WindowFocus)
        EVENT_CLASS_CATEGORY(EventCategory::Application)
    };

    class WindowLostFocusEvent : public Event {
    public:
        EVENT_CLASS_TYPE(WindowLostFocus)
        EVENT_CLASS_CATEGORY(EventCategory::Application)
    };
}