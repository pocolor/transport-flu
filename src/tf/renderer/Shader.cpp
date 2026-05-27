#include "tf/pch.hpp"

#include "Shader.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

namespace tf {
    Shader::Shader(const str& vertexSrc, const str& fragmentSrc) {
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* source = vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if(isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, infoLog.data());

			glDeleteShader(vertexShader);

			TF_ENGINE_CRITICAL("Vertex shader compilation failed: {0}", infoLog.data());
			TF_DEBUGBREAK();

			return;
		}

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		source = fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, infoLog.data());

			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);

			TF_ENGINE_CRITICAL("Index shader compilation failed: {0}", infoLog.data());
			TF_DEBUGBREAK();

			return;
		}

		m_rendererID = glCreateProgram();

		glAttachShader(m_rendererID, vertexShader);
		glAttachShader(m_rendererID, fragmentShader);

		glLinkProgram(m_rendererID);

		GLint isLinked = 0;
		glGetProgramiv(m_rendererID, GL_LINK_STATUS, (int*) &isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_rendererID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_rendererID, maxLength, &maxLength, infoLog.data());

			glDeleteProgram(m_rendererID);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			TF_ENGINE_CRITICAL("Shader linking failed: {0}", infoLog.data());
			TF_DEBUGBREAK();

			return;
		}

		glDetachShader(m_rendererID, vertexShader);
		glDetachShader(m_rendererID, fragmentShader);
    }

    Shader::~Shader() {
        glDeleteProgram(m_rendererID);
    }

    void Shader::bind() const {
        glUseProgram(m_rendererID);
    }

    void Shader::unbind() const {
        glUseProgram(0);
    }

	void Shader::uploadUniform(const str& name, f32 value) {
    	i32 location = glGetUniformLocation(m_rendererID, name.c_str());
    	glUniform1f(location, value);
    }

	void Shader::uploadUniform(const str& name, vec2 value) {
    	i32 location = glGetUniformLocation(m_rendererID, name.c_str());
    	glUniform2f(location, value.x, value.y);
    }

	void Shader::uploadUniform(const str& name, vec3 value) {
    	i32 location = glGetUniformLocation(m_rendererID, name.c_str());
    	glUniform3f(location, value.x, value.y, value.z);
    }

	void Shader::uploadUniform(const str& name, vec4 value) {
    	i32 location = glGetUniformLocation(m_rendererID, name.c_str());
    	glUniform4f(location, value.x, value.y, value.z, value.w);
    }

	void Shader::uploadUniform(const str& name, const mat3& value) {
    	i32 location = glGetUniformLocation(m_rendererID, name.c_str());
    	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }

    void Shader::uploadUniform(const str& name, const mat4& value) {
    	i32 location = glGetUniformLocation(m_rendererID, name.c_str());
	    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }
}
