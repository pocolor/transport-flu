#pragma once

#include "tf/core.hpp"

#include "ShaderDataType.hpp"

#include "tf/memory/RefCounted.hpp"

#include <glad/glad.h>

namespace tf {
    struct BufferElement {
        str name;
        ShaderDataType type = ShaderDataType::None;
        i32 size = 0;
        std::size_t offset = 0;
        bool normalized = false;

        BufferElement(ShaderDataType type, const str& name, bool normalized = false)
            : name(name), type(type), size(getShaderDataTypeSize(type)), normalized(normalized) {}

        i32 getComponentCount() const { return getShaderDataTypeComponentCount(type); }
        GLenum getComponentType() const { return getShaderDataTypeComponentType(type); }
    };

    class BufferLayout {
    public:
        BufferLayout(std::initializer_list<BufferElement> elements)
            : m_elements(elements) {
            calcOffsetsAndStrides();
        }

        const std::vector<BufferElement>& getElements() const { return m_elements; }
        i32 getStride() const { return m_stride; }

        auto begin() { return m_elements.begin(); }
        auto end() { return m_elements.end(); }

        auto begin() const { return m_elements.begin(); }
        auto end() const { return m_elements.end(); }

    private:
        void calcOffsetsAndStrides() {
            std::size_t offset = 0;
            m_stride = 0;
            for (auto& element : m_elements) {
                element.offset = offset;
                offset += element.size;
                m_stride += element.size;
            }
        }

    private:
        std::vector<BufferElement> m_elements = {};
        i32 m_stride = 0;
    };

    class VertexBuffer : public RefCounted {
    public:
        VertexBuffer(const f32* vertices, u32 size);
        ~VertexBuffer() override;

        void bind() const;
        void unbind() const;

        const BufferLayout& getLayout() const { return m_layout; }
        void setLayout(const BufferLayout& layout) { m_layout = layout; }

    private:
        RendererID m_rendererID;
        BufferLayout m_layout = {};
    };

    class IndexBuffer : public RefCounted {
    public:
        IndexBuffer(const u32* indices, u32 count);
        ~IndexBuffer() override;

        void bind() const;
        void unbind() const;

        u32 getCount() const { return m_count; }

    private:
        RendererID m_rendererID;
        u32 m_count;
    };
}
