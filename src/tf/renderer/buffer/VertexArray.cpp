#include "tf/pch.hpp"

#include "VertexArray.hpp"

#include <glad/glad.h>

namespace tf {
    VertexArray::VertexArray() {
        glGenVertexArrays(1, &m_rendererID);
        glBindVertexArray(m_rendererID);
    }

    VertexArray::~VertexArray() {
        glDeleteVertexArrays(1, &m_rendererID);
    }

    void VertexArray::bind() const {
        glBindVertexArray(m_rendererID);
    }

    void VertexArray::unbind() const {
        glBindVertexArray(0);
    }

    void VertexArray::addVertexBuffer(const Ref<VertexBuffer>& buffer) {
        TF_ENGINE_ASSERT_M(!buffer->getLayout().getElements().empty(), "VertexBuffer has no layout!");

        glBindVertexArray(m_rendererID);
        buffer->bind();
        i32 index = 0;
        BufferLayout layout = buffer->getLayout();
        for (const auto& element : layout) {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(
                index,
                element.getComponentCount(),
                element.getComponentType(),
                element.normalized ? GL_TRUE : GL_FALSE,
                layout.getStride(),
                (const void*)element.offset);
            ++index;
        }
        m_vertexBuffers.push_back(buffer);
    }

    void VertexArray::setIndexBuffer(const Ref<IndexBuffer>& buffer) {
        glBindVertexArray(m_rendererID);
        buffer->bind();
        m_indexBuffer = buffer;
    }
}
