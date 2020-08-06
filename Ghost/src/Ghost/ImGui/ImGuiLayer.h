#pragma once

#include "Ghost/Core/Base.h"
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
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }
	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};
}