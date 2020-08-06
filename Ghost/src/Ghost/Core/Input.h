#pragma once

#include "Ghost/Core/Base.h"
#include "Ghost/Core/KeyCodes.h"
#include "Ghost/Core/MouseCodes.h"

namespace Ghost {
	class Input {
	public:
		static bool IsKeyPressed(KeyCode keycode);

		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}