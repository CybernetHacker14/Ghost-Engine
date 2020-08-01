#include "gtpch.h"
#include "Ghost/Core/Input.h"

#ifdef GT_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsInput.h"
#endif // GT_PLATFORM_WINDOWS

namespace Ghost {
	Scope<Input> Input::s_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
		#ifdef GT_PLATFORM_WINDOWS
		return CreateScope<WindowsInput>();
		#else
		GT_CORE_ASSERT(false, "Unknown Platform!");
		return nullptr;
		#endif // GT_PLATFORM_WINDOWS
	}
}