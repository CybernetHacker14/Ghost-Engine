#pragma once

#include "Ghost/Core/Core.h"
#include "Ghost/Core/Layer.h"
#include "Ghost/Events/ApplicationEvent.h"
#include "Ghost/Events/KeyEvent.h"
#include "Ghost/Events/MouseEvent.h"

namespace Ghost {
	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}