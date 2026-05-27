#include "tf/pch.hpp"

#include "Renderer.hpp"
#include "RenderCommand.hpp"

namespace tf {
    void Renderer::beginScene() {
    }

    void Renderer::endScene() {
    }

    void Renderer::submit(const Ref<VertexArray>& vertexArray) {
        vertexArray->bind();
        RenderCommand::drawIndexed(vertexArray);
    }
}
