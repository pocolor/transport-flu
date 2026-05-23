#pragma once

#include "ShaderDataType.hpp"

#include <cstdint>
#include <initializer_list>
#include <vector>
#include <string>

namespace engine {
    struct BufferElement {
        std::string name;
        ShaderDataType type = ShaderDataType::None;
        int32_t size = 0;
        std::size_t offset = 0;
        bool normalized = false;

        BufferElement(const ShaderDataType type, const std::string& name, const bool normalized = false)
            : name(name), type(type), size(getShaderDataTypeSize(type)), normalized(normalized) {}

        [[nodiscard]] int32_t getComponentCount() const { return getShaderDataTypeComponentCount(type); }
        [[nodiscard]] GLenum getComponentType() const { return getShaderDataTypeComponentType(type); }
    };

    class BufferLayout {
    public:
        BufferLayout(std::initializer_list<BufferElement> elements)
            : m_elements(elements) {
            calcOffsetsAndStrides();
        }

        [[nodiscard]] const std::vector<BufferElement>& getElements() const { return m_elements; }
        [[nodiscard]] int32_t getStride() const { return m_stride; }

        auto begin() { return m_elements.begin(); }
        auto end() { return m_elements.end(); }

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
        int32_t m_stride = 0;
    };
}
