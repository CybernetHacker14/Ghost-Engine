#include "gtpch.h"
#include "Ghost/Renderer/UniformBuffer.h"

#include "Ghost/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLUniformBuffer.h"

namespace Ghost
{
	Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding) {
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				GT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				return nullptr;

			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGLUniformBuffer>(size, binding);
		}

		GT_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}
