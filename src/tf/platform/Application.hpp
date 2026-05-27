#pragma once

#include "tf/core.hpp"

#include "Window.hpp"

#include "tf/event/Event.hpp"
#include "tf/event/ApplicationEvent.hpp"
#include "tf/renderer/layer/LayerStack.hpp"

namespace tf {
    class Application {
    public:
        Application();
        ~Application();

        void run();

        Window& getWindow() { return m_window; }
        LayerStack& getLayerStack() { return m_layerStack; }

    private:
        void onEvent(Event& event);
        bool onWindowClose(WindowCloseEvent& event);

        bool m_running = false;
        Window m_window;
        LayerStack m_layerStack;
    };
}
