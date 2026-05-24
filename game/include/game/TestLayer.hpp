#pragma once

#include "engine/layer/Layer.hpp"

#include "engine/renderer/Renderer.hpp"
#include "engine/renderer/RenderCommand.hpp"
#include "engine/renderer/Shader.hpp"
#include "engine/renderer/buffer/VertexBuffer.hpp"

#include "engine/renderer/camera/OrthographicCamera.hpp"

#include "engine/memory/Ref.hpp"

class TestLayer : public engine::Layer {
public:
    TestLayer():
        Layer("TestLayer"),
        m_camera(-2.0f, 2.0f, -1.0f, 1.0f) {}
    ~TestLayer() override = default;

    void onAttach() override {
        using namespace engine;

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

uniform mat4 u_ViewProjectionMatrix;

out vec3 v_Position;

void main() {
    v_Position = a_Position;
    gl_Position = u_ViewProjectionMatrix * vec4(a_Position, 1.0);
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

    void onUpdate() override {
        using namespace engine;

        RenderCommand::setClearColor({1, 0, 1, 1});
        RenderCommand::clear();

        Renderer::beginScene();

        m_shader->bind();
        m_shader->uploadUniformMat4("u_ViewProjectionMatrix", m_camera.getViewProjectionMatrix());
        Renderer::submit(m_vertexArray);

        Renderer::endScene();
    }

private:
    std::unique_ptr<engine::Shader> m_shader;
    engine::Ref<engine::VertexArray> m_vertexArray;

    engine::OrthographicCamera m_camera;
};
