#include "gtpch.h"
#include "Ghost/Renderer/GraphicsContext.h"

#include "Ghost/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Ghost {
	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:
			{
				GT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
			{
				return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
			}

			GT_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}
}