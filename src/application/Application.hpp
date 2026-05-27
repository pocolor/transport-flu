#pragma once

#include "engine/application/Window.hpp"
#include "engine/event/Event.hpp"
#include "engine/event/ApplicationEvent.hpp"
#include "engine/layer/LayerStack.hpp"

namespace engine {
    class Application {
    protected:
        Application();

    public:
        virtual ~Application();

        void run();

        virtual void onInit() {}
        virtual void onStart() {}
        virtual void onStop() {}
        virtual void onTerminate() {}

        [[nodiscard]] Window& getWindow() { return m_window; }
        [[nodiscard]] LayerStack& getLayerStack() { return m_layerStack; }

    private:
        void onEvent(Event& event);
        bool onWindowClose(WindowCloseEvent& event);

        bool m_running = false;
        Window m_window;
        LayerStack m_layerStack;
    };
}
