#pragma once

#include "glm/glm.hpp"

namespace engine {
    class OrthographicCamera {
    public:
        OrthographicCamera(float left, float right, float bottom, float top);

        void setPosition(const glm::vec3& position) { m_position = position; calculateViewMatrix(); }
        const glm::vec3& getPosition() const { return m_position; }

        void setRotationZ(const float rotationZ) { m_rotationZ = rotationZ; calculateViewMatrix(); }
        float getRotationZ() const { return m_rotationZ; }

        const glm::mat4& getProjectionMatrix() const { return m_projectionMatrix; }
        const glm::mat4& getViewMatrix() const { return m_viewMatrix; }
        const glm::mat4& getViewProjectionMatrix() const { return m_viewProjectionMatrix; }

    private:
        void calculateViewMatrix();

    private:
        glm::mat4 m_projectionMatrix;
        glm::mat4 m_viewMatrix = glm::mat4(1.0f);
        glm::mat4 m_viewProjectionMatrix;

        glm::vec3 m_position = glm::vec3(0.0f);
        float m_rotationZ = 0.0f;
    };
}
