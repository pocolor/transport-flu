#pragma once

#include <cstdint>

namespace engine {
    class IndexBuffer {
    public:
        IndexBuffer(const uint32_t* indices, std::size_t count);
        ~IndexBuffer();

        void bind() const;
        void unbind() const;

        std::size_t getCount() const { return m_count; }

    private:
        uint32_t m_rendererID;
        std::size_t m_count;
    };
}
