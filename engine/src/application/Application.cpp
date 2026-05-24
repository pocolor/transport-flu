#include "engine/application/Application.hpp"

#include "engine/event/EventDispatcher.hpp"
#include "engine/Logger.hpp"

#include "glad/glad.h"

#include <memory>
#include <ranges>

#include "engine/renderer/buffer/VertexArray.hpp"
#include "engine/renderer/buffer/IndexBuffer.hpp"
#include "engine/renderer/RenderCommand.hpp"
#include "engine/renderer/Renderer.hpp"

namespace engine {
    Application::Application() {
        m_window.setEventCallback(BIND_EVENT_FN(Application::onEvent));

        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f,
        };

        Ref<VertexBuffer> vertexBuffer = Ref(new VertexBuffer(vertices, sizeof(vertices)));

        BufferLayout layout = {
            { ShaderDataType::Float3, "a_Position" },
        };

        vertexBuffer->setLayout(layout);

        unsigned int indices[] = { 0, 1, 2 };
        Ref<IndexBuffer> indexBuffer = Ref(new IndexBuffer(indices, 3));

        m_vertexArray = Ref(new VertexArray());
        m_vertexArray->addVertexBuffer(vertexBuffer);
        m_vertexArray->setIndexBuffer(indexBuffer);

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
            RenderCommand::setClearColor({1, 0, 1, 1});
            RenderCommand::clear();

            Renderer::beginScene();

            m_shader->bind();
            Renderer::submit(m_vertexArray);

            Renderer::endScene();

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
