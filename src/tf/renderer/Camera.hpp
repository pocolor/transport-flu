#pragma once

#include "tf/core.hpp"

namespace tf {
    class Camera {
    public:
        explicit Camera(const mat4& projectionMatrix) : m_projectionMatrix(projectionMatrix) {}
        ~Camera() = default;

        const mat4& getProjectionMatrix() const { return m_projectionMatrix; }
        const mat4& getViewMatrix() const { return m_viewMatrix; }
        const mat4& getViewProjectionMatrix() const { return m_viewProjectionMatrix; }

    private:
        mat4 m_projectionMatrix;
        mat4 m_viewMatrix = mat4(1.0f);
        mat4 m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
    };
}
