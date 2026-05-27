#pragma once

#include <atomic>

#include "RefCounted.hpp"

namespace engine {
    template <typename T>
    requires(std::is_base_of_v<RefCounted, T>)
    class Ref {
    public:
        Ref() : m_reference(nullptr) {}
        Ref(std::nullptr_t) : m_reference(nullptr) {}
        explicit Ref(T* t) : m_reference(t) { incCount(); }
        Ref(const Ref& other) : m_reference(other.m_reference) { incCount(); }
        Ref(Ref&& other) noexcept : m_reference(other.m_reference) { other.m_reference = nullptr; }
        ~Ref() { decCount(); }

        template <typename ... Args>
        static Ref create(Args&& ... args) {
            return Ref(new T(std::forward<Args>(args)...));
        }

        T* get() { return m_reference; }
        const T* get() const { return m_reference; }

        void reset(T* reference = nullptr) {
            if (m_reference != reference) {
                decCount();
                m_reference = reference;
                incCount();
            }
        }

        Ref& operator=(const Ref& other) {
            if (this == &other)
                return *this;

            other.incCount();
            decCount();

            m_reference = other.m_reference;
            return *this;
        }

        Ref& operator=(Ref&& other) noexcept {
            if (this == &other)
                return *this;

            decCount();

            m_reference = other.m_reference;
            other.m_reference = nullptr;

            return *this;
        }

        template <typename T2>
        requires(std::is_base_of_v<T2, T> || std::is_base_of_v<T, T2>)
        Ref<T2> as() const { return Ref<T2>(dynamic_cast<T2*>(m_reference)); }

        template <typename T2>
        requires(std::is_base_of_v<T, T2>)
        Ref& operator=(const Ref<T2>& other) {
            if (m_reference == other.m_reference)
                return *this;

            other.incCount();
            decCount();

            m_reference = other.m_reference;
            return *this;
        }

        template <typename T2>
        Ref& operator=(Ref<T2>&& other) {
            decCount();

            m_reference = other.m_reference;
            other.m_reference = nullptr;
            return *this;
        }

        T* operator->() { return m_reference; }
        const T* operator->() const { return m_reference; }

        T& operator*() { return *m_reference; }
        const T& operator*() const { return *m_reference; }

        operator bool() noexcept { return m_reference != nullptr; }
        operator bool() const noexcept { return m_reference != nullptr; }

        bool operator==(const Ref &other) const noexcept { return m_reference == other.m_reference; }
        bool operator!=(const Ref &other) const noexcept { return m_reference != other.m_reference; }

    private:
        void incCount() const {
            if (m_reference) {
                m_reference->m_refCount.fetch_add(1, std::memory_order_relaxed);
            }
        }

        void decCount() {
            if (m_reference) {
                if (m_reference->m_refCount.fetch_sub(1, std::memory_order_acq_rel) == 1) {
                    delete m_reference;
                    m_reference = nullptr;
                }
            }
        }

    private:
        T* m_reference;
    };
}
