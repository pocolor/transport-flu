#pragma once

#include <cstdint>

#include "engine/memory/RefCounted.hpp"

namespace engine {
    class IndexBuffer : public RefCounted {
    public:
        IndexBuffer(const uint32_t* indices, std::size_t count);
        ~IndexBuffer() override;

        void bind() const;
        void unbind() const;

        std::size_t getCount() const { return m_count; }

    private:
        uint32_t m_rendererID;
        std::size_t m_count;
    };
}
