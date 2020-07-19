#pragma once

#include "Ghost/Renderer/GraphicsContext.h"

struct GLFWwindow;  // Forward Declaration

namespace Ghost {
	class OpenGLContext : public GraphicsContext {
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}