#include "engine/renderer/buffer/VertexBuffer.hpp"

#include "glad/glad.h"

namespace engine {
    VertexBuffer::VertexBuffer(const float *vertices, const std::size_t size) {
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
}
