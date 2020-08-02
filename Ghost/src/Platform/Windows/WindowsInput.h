#pragma once

#include "Ghost/Core/Input.h"
#include "Ghost/Events/Event.h"

namespace Ghost {
	class WindowsInput : public Input {
	protected:
		virtual bool IsKeyPressedImpl(KeyCode keycode) override;
		virtual bool IsKeyDownImpl(KeyCode keycode) override;
		virtual bool IsKeyUpImpl(KeyCode keycode) override;

		virtual bool IsMouseButtonPressedImpl(MouseCode button) override;

		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	private:
		std::unordered_map<KeyCode, int> m_keyPressMap;
	};
}