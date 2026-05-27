#pragma once

#include <string>
#include <map>

#include "glm/glm.hpp"

namespace engine {
    class Shader {
    public:
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader();

        void bind() const;
        void unbind() const;

        void uploadUniformMat4(const std::string& name, const glm::mat4& matrix);

    private:
        std::map<std::string, int> m_uniformLocations;
        uint32_t m_rendererID;
    };
}
