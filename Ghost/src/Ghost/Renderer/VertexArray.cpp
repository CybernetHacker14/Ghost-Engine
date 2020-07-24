#include "gtpch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Ghost {
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:
			{
				GT_CORE_ASSERT(false, "RendererAPI::None currently not supported");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
			{
				return new OpenGLVertexArray();
			}
		}

		GT_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}