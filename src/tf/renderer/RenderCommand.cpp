#include "tf/pch.hpp"

#include "RenderCommand.hpp"

#include <glad/glad.h>

namespace tf {
    void RenderCommand::setClearColor(const vec4& color) {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void RenderCommand::clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RenderCommand::drawIndexed(const Ref<VertexArray>& vertexArray) {
        glDrawElements(
            GL_TRIANGLES,
            vertexArray->getIndexBuffer()->getCount(),
            GL_UNSIGNED_INT,
            nullptr);
    }
}
