#pragma once

#include "Ghost/Input.h"
#include "Ghost/Events/Event.h"

namespace Ghost {
	class WindowsInput : public Input {
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsKeyDownImpl(int keycode) override;
		virtual bool IsKeyUpImpl(int keycode) override;

		virtual bool IsMouseButtonPressedImpl(int button) override;

		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	private:
		std::unordered_map<int, int> m_keyPressMap;
	};
}