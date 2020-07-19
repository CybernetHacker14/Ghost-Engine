#include "gtpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Ghost {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		GT_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		GT_CORE_ASSERT(status, "Failed to initialize Glad!");

		GT_CORE_INFO("Vendor          : {0}", glGetString(GL_VENDOR));
		GT_CORE_INFO("Hardware        : {0}", glGetString(GL_RENDERER));
		GT_CORE_INFO("OpenGL Version  : {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}