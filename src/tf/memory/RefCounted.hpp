#pragma once

#include "tf/core.hpp"

#include <atomic>

namespace tf {
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
