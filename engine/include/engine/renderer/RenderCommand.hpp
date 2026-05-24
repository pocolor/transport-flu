#pragma once
#include "buffer/VertexArray.hpp"
#include "engine/memory/Ref.hpp"

#include "glm/glm.hpp"

namespace engine {
    class RenderCommand {
    public:
        RenderCommand() = delete;

        static void setClearColor(const glm::vec4& color);
        static void clear();
        static void drawIndexed(const Ref<VertexArray>& vertexArray);
    };
}
