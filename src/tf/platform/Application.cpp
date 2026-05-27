#include "tf/pch.hpp"

#include "Application.hpp"

#include "tf/event/EventDispatcher.hpp"

#include <ranges>

#include "Time.hpp"
#include "input/Input.hpp"

namespace tf {
    Application::Application() {
        m_window.setEventCallback(BIND_EVENT_FN(Application::onEvent));

        Time::setHandle(m_window.getHandle());
        Input::setHandle(m_window.getHandle());
    }

    Application::~Application() = default;

    void Application::run() {
        m_running = true;
        while (m_running) {
            Time::onUpdate();
            Input::onUpdate();

            for (Layer* layer : m_layerStack) {
                layer->onUpdate();
            }

            m_window.onUpdate();
        }
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

    bool Application::onWindowClose(WindowCloseEvent& event) {
        m_running = false;
        return true;
    }
}
