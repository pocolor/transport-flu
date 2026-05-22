#include "engine/application/Application.hpp"

#include "engine/event/EventDispatcher.hpp"
#include "engine/Logger.hpp"

#include "glad/glad.h"

namespace engine {
    Application::Application() {
        m_window->setEventCallback(BIND_EVENT_FN(Application::onEvent));
    }

    Application::~Application() {
        delete m_window;
    }

    void Application::run() {
        onStart();

        m_running = true;
        while (m_running) {
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            m_window->onUpdate();
        }

        onStop();
    }

    void Application::onEvent(Event& event) {
        TF_ENGINE_TRACE("{}", event.toString());

        EventDispatcher dispatcher(event);
        dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::onWindowClose));
    }

    bool Application::onWindowClose(WindowCloseEvent &event) {
        m_running = false;
        return true;
    }
}
