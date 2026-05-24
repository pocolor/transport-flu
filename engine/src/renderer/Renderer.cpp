#include "engine/renderer/Renderer.hpp"

#include "engine/renderer/RenderCommand.hpp"

namespace engine {
    void Renderer::beginScene() {
    }

    void Renderer::endScene() {
    }

    void Renderer::submit(const Ref<VertexArray>& vertexArray) {
        vertexArray->bind();
        RenderCommand::drawIndexed(vertexArray);
    }
}
