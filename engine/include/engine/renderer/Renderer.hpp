#pragma once

#include "buffer/VertexArray.hpp"
#include "engine/memory/Ref.hpp"

namespace engine {
    class Renderer {
    public:
        Renderer() = delete;

        static void beginScene();
        static void endScene();

        static void submit(const Ref<VertexArray>& vertexArray);
    };
}
