#include "gtpch.h"
#include "WindowsInput.h"

#include "Ghost/Core/Core.h"
#include "Ghost/Core/Application.h"
#include "Ghost/Events/MouseEvent.h"
#include "Ghost/Events/KeyEvent.h"

#include <GLFW/glfw3.h>

namespace Ghost {
	Scope<Input> Input::s_Instance = CreateScope<WindowsInput>();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsKeyDownImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		if (m_keyPressMap.find(keycode) != m_keyPressMap.end()) {
			if (m_keyPressMap[keycode] == state) {
				return false;
			}
			else {
				m_keyPressMap[keycode] = state;
				return state == GLFW_PRESS;
			}
		}
		else {
			m_keyPressMap[keycode] = state;
			return false;
		}
	}

	bool WindowsInput::IsKeyUpImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		if (m_keyPressMap.find(keycode) != m_keyPressMap.end()) {
			if (m_keyPressMap[keycode] == state) {
				return false;
			}
			else {
				m_keyPressMap[keycode] = state;
				return state == GLFW_RELEASE;
			}
		}
		else {
			m_keyPressMap[keycode] = state;
			return false;
		}
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button) {
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)xpos,(float)ypos };
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return y;
	}
}