#include "gtpch.h"
#include "Ghost/Renderer/Framebuffer.h"
#include "Ghost/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Ghost {
	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
		{
			GT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		}
		case RendererAPI::API::OpenGL:
		{
			return CreateRef<OpenGLFramebuffer>(spec);
		}
		}

		GT_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
