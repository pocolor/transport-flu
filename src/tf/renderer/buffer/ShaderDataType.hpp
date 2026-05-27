#pragma once

#include "tf/core.hpp"

#include <glad/glad.h>

namespace tf {
    enum class ShaderDataType : u8 {
        None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, UInt, UInt2, UInt3, UInt4, Bool
    };

    static int getShaderDataTypeSize(ShaderDataType type) {
        switch (type) {
            case ShaderDataType::Float:    return 4;
            case ShaderDataType::Float2:   return 4 * 2;
            case ShaderDataType::Float3:   return 4 * 3;
            case ShaderDataType::Float4:   return 4 * 4;
            case ShaderDataType::Mat3:     return 4 * 3 * 3;
            case ShaderDataType::Mat4:     return 4 * 4 * 4;
            case ShaderDataType::Int:      return 4;
            case ShaderDataType::Int2:     return 4 * 2;
            case ShaderDataType::Int3:     return 4 * 3;
            case ShaderDataType::Int4:     return 4 * 4;
            case ShaderDataType::UInt:     return 4;
            case ShaderDataType::UInt2:    return 4 * 2;
            case ShaderDataType::UInt3:    return 4 * 3;
            case ShaderDataType::UInt4:    return 4 * 4;
            case ShaderDataType::Bool:     return 1;
            default:
                TF_ENGINE_ERROR("Unknown ShaderDataType!");
                TF_DEBUGBREAK();
                return 0;
        }
    }

    static i32 getShaderDataTypeComponentCount(ShaderDataType type) {
        switch (type) {
            case ShaderDataType::Float:    return 1;
            case ShaderDataType::Float2:   return 2;
            case ShaderDataType::Float3:   return 3;
            case ShaderDataType::Float4:   return 4;
            case ShaderDataType::Mat3:     return 3 * 3;
            case ShaderDataType::Mat4:     return 4 * 4;
            case ShaderDataType::Int:      return 1;
            case ShaderDataType::Int2:     return 2;
            case ShaderDataType::Int3:     return 3;
            case ShaderDataType::Int4:     return 4;
            case ShaderDataType::UInt:     return 1;
            case ShaderDataType::UInt2:    return 2;
            case ShaderDataType::UInt3:    return 3;
            case ShaderDataType::UInt4:    return 4;
            case ShaderDataType::Bool:     return 1;
            default:
                TF_ENGINE_ERROR("Unknown ShaderDataType!");
                TF_DEBUGBREAK();
                return 0;
        }
    }

    static GLenum getShaderDataTypeComponentType(ShaderDataType type) {
        switch (type) {
            case ShaderDataType::Float:
            case ShaderDataType::Float2:
            case ShaderDataType::Float3:
            case ShaderDataType::Float4:
            case ShaderDataType::Mat3:
            case ShaderDataType::Mat4:     return GL_FLOAT;
            case ShaderDataType::Int:
            case ShaderDataType::Int2:
            case ShaderDataType::Int3:
            case ShaderDataType::Int4:     return GL_INT;
            case ShaderDataType::UInt:
            case ShaderDataType::UInt2:
            case ShaderDataType::UInt3:
            case ShaderDataType::UInt4:    return GL_UNSIGNED_INT;
            case ShaderDataType::Bool:     return GL_BOOL;
            default:
                TF_ENGINE_ERROR("Unknown ShaderDataType!");
                TF_DEBUGBREAK();
                return 0;
        }
    }
}
