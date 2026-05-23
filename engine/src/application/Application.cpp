#include "engine/application/Application.hpp"

#include "engine/event/EventDispatcher.hpp"
#include "engine/Logger.hpp"

#include "glad/glad.h"

#include <memory>
#include <ranges>

namespace engine {
    Application::Application() {
        m_window.setEventCallback(BIND_EVENT_FN(Application::onEvent));

        glGenVertexArrays(1, &m_vertexArray);
        glBindVertexArray(m_vertexArray);

        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f,
        };

        m_vertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

        unsigned int indices[] = { 0, 1, 2 };
        m_indexBuffer = std::make_unique<IndexBuffer>(indices, 3);

        std::string vertexSrc = R"(
#version 330 core

layout (location = 0) in vec3 a_Position;

out vec3 v_Position;

void main() {
    v_Position = a_Position;
    gl_Position = vec4(a_Position, 1.0);
}
)";

        std::string fragmentSrc = R"(
#version 330 core

in vec3 v_Position;

layout (location = 0) out vec4 color;

void main() {
    color = vec4(v_Position * 0.5 + 0.5, 1.0);
}
)";

        m_shader = std::make_unique<Shader>(vertexSrc, fragmentSrc);
    }

    Application::~Application() = default;

    void Application::run() {
        onStart();

        m_running = true;
        while (m_running) {
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            m_shader->bind();
            glBindVertexArray(m_vertexArray);
            glDrawElements(GL_TRIANGLES, (int32_t) m_indexBuffer->getCount(), GL_UNSIGNED_INT, nullptr);

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
