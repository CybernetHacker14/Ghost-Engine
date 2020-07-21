#include "gtpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

namespace Ghost {
	OpenGLShader::OpenGLShader()
	{
		m_RendererID = glCreateProgram();
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	bool OpenGLShader::Compile(const std::string& source, const ShaderType type)
	{
		GLuint shaderID = 0;
		const GLchar* shaderSource = source.c_str();
		GLint isCompiled = 0;

		switch (type) {
			case ShaderType::None:
			{
				GT_CORE_FATAL("ShaderType::None is currently not supported");
				return false;
			}
			case ShaderType::VertexShader:
			{
				shaderID = glCreateShader(GL_VERTEX_SHADER);

				glShaderSource(shaderID, 1, &shaderSource, nullptr);
				glCompileShader(shaderID);
				glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);

				if (isCompiled == GL_FALSE) {
					glDeleteShader(shaderID);
					GT_CORE_FATAL("Vertex Shader compilation failure!");
					GT_CORE_ASSERT(false, "Vertex Shader could not be compiled");
					return false;
				}
				else {
					glAttachShader(m_RendererID, shaderID);
					m_ShaderIDMap[type] = shaderID;
					return true;
				}
			}
			case ShaderType::FragmentShader:
			{
				shaderID = glCreateShader(GL_FRAGMENT_SHADER);

				glShaderSource(shaderID, 1, &shaderSource, nullptr);
				glCompileShader(shaderID);
				glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);

				if (isCompiled == GL_FALSE) {
					glDeleteShader(shaderID);
					GT_CORE_FATAL("Fragment Shader compilation failure!");
					GT_CORE_ASSERT(false, "Fragment Shader could not be compiled");
					return false;
				}
				else {
					glAttachShader(m_RendererID, shaderID);
					m_ShaderIDMap[type] = shaderID;
					return true;
				}
			}
		}
	}

	bool OpenGLShader::Link()
	{
		glLinkProgram(m_RendererID);

		GLint isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)&isLinked);

		if (isLinked == GL_FALSE) {
			// Delete Program
			glDeleteProgram(m_RendererID);
			// Delete Shaders
			glDeleteShader(m_ShaderIDMap[ShaderType::VertexShader]);
			glDeleteShader(m_ShaderIDMap[ShaderType::FragmentShader]);

			GT_CORE_FATAL("Shader link failure!");
			GT_CORE_ASSERT(false, "Shader program couldn't be linked");
			return false;
		}
		else {
			// Detach shaders after a successful link
			glDetachShader(m_RendererID, m_ShaderIDMap[ShaderType::VertexShader]);
			glDetachShader(m_RendererID, m_ShaderIDMap[ShaderType::FragmentShader]);

			// TEMPORARY: Clearing out the entries from the map
			m_ShaderIDMap.erase(ShaderType::VertexShader);
			m_ShaderIDMap.erase(ShaderType::FragmentShader);

			return true;
		}
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}
}