#pragma once

#include "Ghost/Renderer/Shader.h"

namespace Ghost {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader();
		virtual ~OpenGLShader();

		virtual bool Compile(const std::string& source, const ShaderType type) override;
		virtual bool Link() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

	private:
		uint32_t m_RendererID;
		std::unordered_map<ShaderType, uint32_t> m_ShaderIDMap;
	};
}