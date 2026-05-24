#pragma once

#include "engine/memory/Ref.hpp"
#include "engine/memory/RefCounted.hpp"

#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

#include <vector>

namespace engine {
    class VertexArray : public RefCounted {
    public:
        VertexArray();
        ~VertexArray() override;

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
