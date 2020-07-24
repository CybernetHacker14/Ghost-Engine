#pragma once

#include "Ghost/Renderer/RendererAPI.h"

namespace Ghost {
	class OpenGLRendererAPI : public RendererAPI {
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}