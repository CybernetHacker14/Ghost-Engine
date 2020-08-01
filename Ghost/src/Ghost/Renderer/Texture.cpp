#include "gtpch.h"
#include "Ghost/Renderer/Texture.h"

#include "Ghost/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Ghost {
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:
			{
				GT_CORE_ASSERT(false, "RendererAPI::None currently not supported");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
			{
				return CreateRef<OpenGLTexture2D>(width, height);
			}
		}
	}

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
				return CreateRef<OpenGLTexture2D>(path);
			}
		}

		GT_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}