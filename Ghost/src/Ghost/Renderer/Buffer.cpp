#include "gtpch.h"
#include "Ghost/Renderer/Buffer.h"

#include "Ghost/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Ghost {
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:
			{
				GT_CORE_ASSERT(false, "RendererAPI::None is currently not supported");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
			{
				return CreateRef<OpenGLVertexBuffer>(vertices, size);
			}

			GT_CORE_ASSERT(false, "Unknown RendererAPI");
			return nullptr;
		}
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size) {
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
			{
				GT_CORE_ASSERT(false, "RendererAPI::None is currently not supported");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
			{
				return CreateRef<OpenGLIndexBuffer>(indices, size);
			}

			GT_CORE_ASSERT(false, "Unknown RendererAPI");
			return nullptr;
		}
	}
}