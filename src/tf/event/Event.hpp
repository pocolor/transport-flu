#pragma once

#include "tf/core.hpp"

#include <functional>

namespace tf {
    enum class EventType : u8 {
        None,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus,
        KeyPressed, KeyRepeat, KeyReleased,
        MouseButtonPressed, MouseButtonReleased,
        MouseMoved, MouseScrolled,
    };

    enum class EventCategory : u8 {
        None = 0,
        Application = 1 << 0,
        Input = 1 << 1,
        Keyboard = 1 << 2,
        Mouse = 1 << 3,
        MouseButton = 1 << 4,
        Game = 1 << 5,
    };

    using EventCategoryFlags = u8;

    inline bool operator&(const EventCategoryFlags lhs, const EventCategory rhs) {
        return lhs & (u8)rhs;
    }
    inline bool operator&(const EventCategory lhs, const EventCategoryFlags rhs) {
        return (u8)lhs & rhs;
    }
    inline bool operator|(const EventCategory lhs, const EventCategory rhs) {
        return (u8)lhs | (u8)rhs;
    }

#define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::type; } \
    virtual EventType getType() const override { return getStaticType(); } \
    virtual str getName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual EventCategoryFlags getCategoryFlags() const override { return (EventCategoryFlags)(category); }

    class Event {
        friend class EventDispatcher;

    public:
        virtual ~Event() = default;

        bool isHandled() const { return m_handled; }
        virtual EventType getType() const = 0;
        virtual str getName() const = 0;
        virtual EventCategoryFlags getCategoryFlags() const = 0;

        virtual str toString() const { return getName(); }

        bool isInCategory(const EventCategory category) const { return getCategoryFlags() & category; }
    protected:
        bool m_handled = false;
    };

    using EventCallbackFn = std::function<void(Event&)>;
}
