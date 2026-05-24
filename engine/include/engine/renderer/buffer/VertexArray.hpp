#pragma once

#include "engine/memory/Ref.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

#include <vector>

namespace engine {
    class VertexArray {
    public:
        VertexArray();
        ~VertexArray();

        void bind() const;
        void unbind() const;

        void addVertexBuffer(const Ref<VertexBuffer>& buffer);
        void setIndexBuffer(const Ref<IndexBuffer>& buffer);

        const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const { return m_vertexBuffers; }
        const Ref<IndexBuffer>& getIndexBuffer() const { return m_indexBuffer; }

    private:
        uint32_t m_rendererID;
        std::vector<Ref<VertexBuffer>> m_vertexBuffers;
        Ref<IndexBuffer> m_indexBuffer;
    };
}
