#pragma once

#include "tf/core.hpp"

#include "Buffer.hpp"

#include "tf/memory/Ref.hpp"
#include "tf/memory/RefCounted.hpp"

#include <vector>

namespace tf {
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
        RendererID m_rendererID;
        std::vector<Ref<VertexBuffer>> m_vertexBuffers;
        Ref<IndexBuffer> m_indexBuffer;
    };
}
