#pragma once

#include "engine/application/Window.hpp"
#include "engine/event/Event.hpp"
#include "engine/event/ApplicationEvent.hpp"

namespace engine {
    class Application {
    protected:
        Application();

    public:
        virtual ~Application();

        virtual void onInit() {}
        virtual void onStart() {}
        virtual void onStop() {}
        virtual void onTerminate() {}

        void run();

        [[nodiscard]] Window& getWindow() const { return *m_window; }

    private:
        void onEvent(Event& event);
        bool onWindowClose(WindowCloseEvent& event);

        Window* m_window = new Window;
        bool m_running = false;
    };
}
