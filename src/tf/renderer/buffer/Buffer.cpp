#include "Buffer.hpp"

#include "glad/glad.h"

namespace tf {
    VertexBuffer::VertexBuffer(const f32 *vertices, const u32 size) {
        glGenBuffers(1, &m_rendererID);
        bind();

        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer() {
        glDeleteBuffers(1, &m_rendererID);
    }

    void VertexBuffer::bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
    }

    void VertexBuffer::unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    IndexBuffer::IndexBuffer(const u32 *indices, u32 count) : m_count(count) {
        glGenBuffers(1, &m_rendererID);
        bind();

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(u32), indices, GL_STATIC_DRAW);
    }

    IndexBuffer::~IndexBuffer() {
        glDeleteBuffers(1, &m_rendererID);
    }

    void IndexBuffer::bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
    }

    void IndexBuffer::unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
