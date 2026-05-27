#pragma once

#include "tf/core.hpp"

#include "tf/event/Event.hpp"

namespace tf {
    class Layer {
    public:
        explicit Layer(const str& name) : m_name(name) {}
        virtual ~Layer() = default;

        virtual void onAttach() {}
        virtual void onDetach() {}
        virtual void onUpdate() {}
        virtual void onEvent(Event& event) {}

        const str& getName() { return m_name; }

    protected:
        str m_name;
    };
}
