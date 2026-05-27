#pragma once

#include "glm/glm.hpp"

#include "engine/object/Transform.hpp"

namespace engine {
    class Camera {
    public:
        Camera();
        virtual ~Camera() = default;

        virtual void setTransform(const Transform& transform);

        const Transform& getTransform() const { return m_transform; }
        const glm::mat4& getProjectionMatrix() const { return m_projectionMatrix; }
        const glm::mat4& getViewMatrix() const { return m_viewMatrix; }
        const glm::mat4& getViewProjectionMatrix() const { return m_viewProjectionMatrix; }

    protected:
        Transform m_transform;

        glm::mat4 m_projectionMatrix;
        glm::mat4 m_viewMatrix = glm::mat4(1.0f);
        glm::mat4 m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
    };
}
