#pragma once

#include "tf/core.hpp"

#include "buffer/VertexArray.hpp"
#include "tf/memory/Ref.hpp"

namespace tf {
    class RenderCommand {
    public:
        RenderCommand() = delete;

        static void setClearColor(const vec4& color);
        static void clear();
        static void drawIndexed(const Ref<VertexArray>& vertexArray);
    };
}
