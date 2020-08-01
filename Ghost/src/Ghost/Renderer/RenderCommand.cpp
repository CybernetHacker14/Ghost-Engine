#include "gtpch.h"
#include "Ghost/Renderer/RenderCommand.h"

namespace Ghost {
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}