#include "gtpch.h"
#include "Ghost/Renderer/VertexArray.h"

#include "Ghost/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Ghost {
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:
			{
				GT_CORE_ASSERT(false, "RendererAPI::None currently not supported");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
			{
				return CreateRef<OpenGLVertexArray>();
			}
		}

		GT_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}