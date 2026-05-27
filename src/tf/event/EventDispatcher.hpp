#pragma once

#include "tf/core.hpp"

#include "Event.hpp"

#include <functional>

namespace tf {
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

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)