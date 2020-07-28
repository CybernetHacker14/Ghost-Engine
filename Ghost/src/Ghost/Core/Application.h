#pragma once

#include "Ghost/Core/Core.h"
#include "Ghost/Core/Window.h"

#include "Ghost/Core/LayerStack.h"
#include "Ghost/Events/Event.h"
#include "Ghost/Events/ApplicationEvent.h"

#include "Ghost/Core/Timestep.h"

#include "Ghost/ImGui/ImGuiLayer.h"

namespace Ghost {
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClosed(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;
		bool m_Minimized = false;

		LayerStack m_layerStack;

		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	// TO BE defined in client
	Application* CreateApplication();
}