#include "gtpch.h"
#include "Texture.h"

#include "Ghost/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Ghost {
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:
			{
				GT_CORE_ASSERT(false, "RendererAPI::None currently not supported");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
			{
				return std::make_shared<OpenGLTexture2D>(path);
			}
		}

		GT_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}