#pragma once

#include <cstdint>

#include "BufferLayout.hpp"
#include "engine/memory/RefCounted.hpp"

namespace engine {
    class VertexBuffer : public RefCounted {
    public:
        VertexBuffer(const float* vertices, std::size_t size);
        ~VertexBuffer() override;

        void bind() const;
        void unbind() const;

        [[nodiscard]] const BufferLayout& getLayout() const { return m_layout; }
        void setLayout(const BufferLayout& layout) { m_layout = layout; }

    private:
        uint32_t m_rendererID;
        BufferLayout m_layout = {};
    };
}
