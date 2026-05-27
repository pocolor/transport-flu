#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"

namespace engine {
    struct Transform {
        glm::vec3 position;
        glm::quat rotation;
        glm::vec3 scale = glm::vec3(1.0f);
    };
}
