#pragma once

#include "engine/event/Event.hpp"

#include <functional>

namespace engine {
    class EventDispatcher {
        template<typename T>
        using EventFn = std::function<bool(T&)>;
    public:
        explicit EventDispatcher(Event& event)
            : m_event(event) {}

        template<typename T>
        bool dispatch(EventFn<T> func) {
            if (m_event.getType() == T::getStaticType()) {
                m_event.m_handled = func(*(T*)&m_event);
                return true;
            }
            return false;
        }
    private:
        Event& m_event;
    };
}