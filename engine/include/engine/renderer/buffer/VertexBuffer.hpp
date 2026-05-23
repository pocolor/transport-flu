#pragma once

#include <cstdint>

namespace engine {
    class VertexBuffer {
    public:
        VertexBuffer(const float* vertices, std::size_t size);
        ~VertexBuffer();

        void bind() const;
        void unbind() const;

    private:
        uint32_t m_rendererID;
    };
}
