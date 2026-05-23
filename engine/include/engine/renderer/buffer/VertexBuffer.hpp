#pragma once

#include <cstdint>

#include "BufferLayout.hpp"

namespace engine {
    class VertexBuffer {
    public:
        VertexBuffer(const float* vertices, std::size_t size);
        ~VertexBuffer();

        void bind() const;
        void unbind() const;

        [[nodiscard]] const BufferLayout& getLayout() const { return m_layout; }
        void setLayout(const BufferLayout& layout) { m_layout = layout; }

    private:
        uint32_t m_rendererID;
        BufferLayout m_layout = {};
    };
}
