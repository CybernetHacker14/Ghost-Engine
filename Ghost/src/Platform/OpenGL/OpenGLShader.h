#pragma once

#include "Ghost/Renderer/Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Ghost {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader();
		virtual ~OpenGLShader();

		virtual bool Compile(const std::string& source, const ShaderType type) override;
		virtual bool Link() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const override;

	private:
		uint32_t m_RendererID;
		std::unordered_map<ShaderType, uint32_t> m_ShaderIDMap;
	};
}