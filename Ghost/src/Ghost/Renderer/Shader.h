#pragma once

#include <string>

namespace Ghost {
	enum class ShaderType {
		None = 0, VertexShader = 1, FragmentShader = 2
	};

	class Shader {
	public:
		virtual ~Shader() {}

		virtual bool Compile(const std::string& source, const ShaderType type) = 0;
		virtual bool Link() = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(); // Creates an empty shader
	};
}