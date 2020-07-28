#include "gtpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Ghost {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}