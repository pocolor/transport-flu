#pragma once

#include "engine/application/Window.hpp"
#include "engine/event/Event.hpp"
#include "engine/event/ApplicationEvent.hpp"
#include "engine/layer/LayerStack.hpp"

#include "engine/renderer/Shader.hpp"
#include "engine/renderer/buffer/VertexBuffer.hpp"
#include "engine/renderer/buffer/IndexBuffer.hpp"
#include "engine/renderer/buffer/VertexArray.hpp"

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

        // TMP
        std::unique_ptr<Shader> m_shader;
        std::unique_ptr<VertexArray> m_vertexArray;
        Ref<VertexBuffer> m_vertexBuffer;
        Ref<IndexBuffer> m_indexBuffer;
    };
}
