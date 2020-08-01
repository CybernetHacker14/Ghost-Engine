#include "gtpch.h"

#include <fstream>
#include <glad/glad.h>

#include "Platform/OpenGL/OpenGLShader.h"

namespace Ghost {
	static ShaderType GLEnumToShaderType(const GLenum& type) {
		if (type == GL_VERTEX_SHADER)
			return ShaderType::VertexShader;
		if (type == GL_FRAGMENT_SHADER)
			return ShaderType::FragmentShader;

		GT_CORE_ASSERT(false, "Unknown Shader type!");
		return ShaderType::None;
	}

	static GLenum StringToGLEnum(const std::string& type) {
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;

		GT_CORE_ASSERT(false, "Unknown Shader type!");
		return 0;
	}

	OpenGLShader::OpenGLShader()
	{
		GT_PROFILE_FUNCTION();

		m_RendererID = glCreateProgram();
	}

	OpenGLShader::~OpenGLShader()
	{
		GT_PROFILE_FUNCTION();

		glDeleteProgram(m_RendererID);
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		GT_PROFILE_FUNCTION();

		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in) {
			in.seekg(0, std::ios::end);
			size_t size = in.tellg();
			if (size != -1) {
				result.resize(size);
				in.seekg(0, std::ios::beg);
				in.read(&result[0], size);
				in.close();
			}
			else {
				GT_CORE_ERROR("Could not read from file '{0}'", filepath);
			}
		}
		else {
			GT_CORE_ASSERT("Could not open file at '{0}'", filepath);
		}

		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		GT_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			GT_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			GT_CORE_ASSERT(StringToGLEnum(type), "Invalid shader type specified");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);

			GT_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
			pos = source.find(typeToken, nextLinePos);

			shaderSources[StringToGLEnum(type)] =
				(pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
		}

		return shaderSources;
	}

	bool OpenGLShader::Compile(const std::string& filepath)
	{
		GT_PROFILE_FUNCTION();

		std::string source = ReadFile(filepath);
		std::unordered_map<GLenum, std::string> shaderSources = PreProcess(source);

		GT_CORE_ASSERT(shaderSources.size() <= 2, "We only support 2 shaders for now");

		GLuint shaderID = 0;
		const GLchar* sourceCStr;
		GLint isCompiled = 0;

		for (auto&& [key, value] : shaderSources) {
			GLenum type = key;
			const std::string& source = value;

			sourceCStr = source.c_str();

			shaderID = glCreateShader(type);

			glShaderSource(shaderID, 1, &sourceCStr, nullptr);
			glCompileShader(shaderID);
			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);

			if (isCompiled == GL_FALSE) {
				glDeleteShader(shaderID);
				GT_CORE_FATAL("Shader compilation failure!");
				GT_CORE_ASSERT(false, "Shader could not be compiled");
				return false;
			}
			else {
				glAttachShader(m_RendererID, shaderID);
				m_ShaderIDMap[GLEnumToShaderType(type)] = shaderID;
			}
		}

		if (isCompiled == GL_FALSE) {
			return false;
		}
		else {
			// Extract name from filepath
			auto lastSlash = filepath.find_last_of("/\\");
			lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
			auto lastDot = filepath.rfind('.');
			auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
			m_Name = filepath.substr(lastSlash, count);
			return false;
		}
	}

	bool OpenGLShader::Compile(const std::string& name, const std::string& source, const ShaderType type)
	{
		GT_PROFILE_FUNCTION();

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
					m_Name = name;
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
					m_Name = name;
					return true;
				}
			}
		}
	}

	bool OpenGLShader::Link()
	{
		GT_PROFILE_FUNCTION();

		glLinkProgram(m_RendererID);

		GLint isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)&isLinked);

		if (isLinked == GL_FALSE) {
			// Delete Program
			glDeleteProgram(m_RendererID);
			// Delete Shaders

			for (auto& it : m_ShaderIDMap) {
				glDetachShader(m_RendererID, it.second);
				glDeleteShader(it.second);
			}

			m_ShaderIDMap.clear();

			GT_CORE_FATAL("Shader link failure!");
			GT_CORE_ASSERT(false, "Shader program couldn't be linked");
			return false;
		}
		else {
			// Automated Cleanup

			for (auto& it : m_ShaderIDMap) {
				glDetachShader(m_RendererID, it.second);
				glDeleteShader(it.second);
			}

			m_ShaderIDMap.clear();

			return true;
		}
	}

	void OpenGLShader::Bind() const
	{
		GT_PROFILE_FUNCTION();

		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		GT_PROFILE_FUNCTION();

		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		GT_PROFILE_FUNCTION();

		UploadUniformInt(name, value);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		GT_PROFILE_FUNCTION();

		UploadUniformFloat3(name, value);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		GT_PROFILE_FUNCTION();

		UploadUniformFloat4(name, value);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		GT_PROFILE_FUNCTION();

		UploadUniformMat4(name, value);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& values)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, values.x, values.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& values)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, values.x, values.y, values.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& values)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, values.r, values.g, values.b, values.a);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}