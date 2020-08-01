#include "gtpch.h"
#include "Ghost/Core/Window.h"

#ifdef GT_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif // GT_PLATFORM_WINDOWS

namespace Ghost {
	Scope<Window> Window::Create(const WindowProps& props) {
		#ifdef GT_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
		#else
		GT_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
		#endif // GT_PLATFORM_WINDOWS
	}
}