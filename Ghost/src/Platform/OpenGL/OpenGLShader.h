#pragma once

#include "Ghost/Renderer/Shader.h"

namespace Ghost {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader();
		virtual ~OpenGLShader();

		virtual bool Compile(const std::string& source, const ShaderType type);
		virtual bool Link();

		virtual void Bind() const;
		virtual void Unbind() const;

	private:
		uint32_t m_RendererID;
		std::unordered_map<ShaderType, uint32_t> m_ShaderIDMap;
	};
}