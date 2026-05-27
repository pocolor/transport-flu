#pragma once

#include "tf/core.hpp"

namespace tf {
    class Shader {
    public:
        Shader(const str& vertexSrc, const str& fragmentSrc);
        ~Shader();

        void bind() const;
        void unbind() const;

        void uploadUniform(const str& name, f32 value);
        void uploadUniform(const str& name, vec2 value);
        void uploadUniform(const str& name, vec3 value);
        void uploadUniform(const str& name, vec4 value);
        void uploadUniform(const str& name, const mat3& value);
        void uploadUniform(const str& name, const mat4& value);

    private:
        RendererID m_rendererID;
    };
}
