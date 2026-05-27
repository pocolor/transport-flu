#pragma once

#include "tf/core.hpp"

#include "buffer/VertexArray.hpp"

#include "tf/memory/Ref.hpp"

namespace tf {
    class Renderer {
    public:
        Renderer() = delete;

        static void beginScene();
        static void endScene();

        static void submit(const Ref<VertexArray>& vertexArray);
    };
}
