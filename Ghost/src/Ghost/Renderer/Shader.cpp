#include "gtpch.h"
#include "Shader.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Ghost {
	Shader* Shader::Create()
	{
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:
			{
				GT_CORE_ASSERT(false, "RendererAPI::None is currently not supported");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
			{
				return new OpenGLShader();
			}

			GT_CORE_ASSERT(false, "Unknown RendererAPI");
			return nullptr;
		}
	}
}