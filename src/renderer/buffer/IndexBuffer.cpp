#include "engine/renderer/buffer/IndexBuffer.hpp"

#include "glad/glad.h"

namespace engine {
    IndexBuffer::IndexBuffer(const uint32_t *indices, const std::size_t count) : m_count(count) {
        glGenBuffers(1, &m_rendererID);
        bind();

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
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
