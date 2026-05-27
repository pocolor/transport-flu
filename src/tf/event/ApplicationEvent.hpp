#pragma once

#include "tf/core.hpp"

#include "Event.hpp"

#include <sstream>

namespace tf {
    class WindowCloseEvent : public Event {
    public:
        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategory::Application)
    };

    class WindowResizeEvent : public Event {
    public:
        WindowResizeEvent(u32 width, u32 height, bool fullscreen)
            : m_width(width), m_height(height), m_fullscreen(fullscreen) {}

        str toString() const override {
            std::stringstream ss;
            ss << "WindowResizeEvent: width=" << m_width <<
                    ", height=" << m_height <<
                    ", fullscreen=" << m_fullscreen;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(EventCategory::Application)

    private:
        const u32 m_width, m_height;
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