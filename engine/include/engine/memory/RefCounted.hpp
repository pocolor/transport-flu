#pragma once

#include <atomic>

namespace engine::memory {
    class RefCounted {
        template <typename T>
        requires(std::is_base_of_v<RefCounted, T>)
        friend class Ref;

    protected:
        virtual ~RefCounted() = default;

    private:
        std::atomic_int32_t m_refCount = 0;
    };
}
