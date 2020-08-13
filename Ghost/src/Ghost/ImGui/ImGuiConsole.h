#pragma once

#include "Ghost/Core/Base.h"

namespace Ghost {
	class ImGuiConsole
	{
	public:
		ImGuiConsole() = default;

		static void Init();
		static void Draw();
		static void Log(const char* data, ...);
	};
}