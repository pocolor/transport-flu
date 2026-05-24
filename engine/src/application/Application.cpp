#include "engine/application/Application.hpp"

#include "engine/event/EventDispatcher.hpp"
#include "engine/Logger.hpp"

#include <ranges>

namespace engine {
    Application::Application() {
        m_window.setEventCallback(BIND_EVENT_FN(Application::onEvent));
    }

    Application::~Application() = default;

    void Application::run() {
        onStart();

        m_running = true;
        while (m_running) {
            for (Layer* layer : m_layerStack) {
                layer->onUpdate();
            }

            m_window.onUpdate();
        }

        onStop();
    }

    void Application::onEvent(Event& event) {
        TF_ENGINE_TRACE("{}", event.toString());

        EventDispatcher dispatcher(event);
        dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::onWindowClose));

        for (Layer* layer : std::views::reverse(m_layerStack)) {
            if (event.isHandled()) break;
            layer->onEvent(event);
        }
    }

    bool Application::onWindowClose(WindowCloseEvent &event) {
        m_running = false;
        return true;
    }
}
