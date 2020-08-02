#pragma once

#include "Ghost/Core/Core.h"
#include "Ghost/Core/KeyCodes.h"
#include "Ghost/Core/MouseCodes.h"

namespace Ghost {
	class Input {
	public:
		inline static bool IsKeyPressed(KeyCode keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		inline static bool IsKeyDown(KeyCode keycode) { return s_Instance->IsKeyDownImpl(keycode); }
		inline static bool IsKeyUp(KeyCode keycode) { return s_Instance->IsKeyUpImpl(keycode); }

		inline static bool IsMouseButtonPressed(MouseCode button) { return s_Instance->IsMouseButtonPressedImpl(button); }

		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

		static Scope<Input> Create();
	protected:
		virtual bool IsKeyPressedImpl(KeyCode keycode) = 0;
		virtual bool IsKeyDownImpl(KeyCode keycode) = 0;
		virtual bool IsKeyUpImpl(KeyCode keycode) = 0;

		virtual bool IsMouseButtonPressedImpl(MouseCode button) = 0;

		virtual std::pair<float, float>GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	private:
		static Scope<Input> s_Instance;
	};
}