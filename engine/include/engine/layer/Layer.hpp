#pragma once

#include "engine/event/Event.hpp"

namespace engine {
    class Layer {
    public:
        explicit Layer(const std::string& name);
        virtual ~Layer();

        virtual void onAttach() {}
        virtual void onDetach() {}
        virtual void onUpdate() {}
        virtual void onEvent(Event& event) {}

        const std::string& getName() { return m_name; }

    protected:
        std::string m_name;
    };
}
