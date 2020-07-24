#pragma once

#include "Core.h"
#include "Window.h"

#include "Ghost/LayerStack.h"
#include "Ghost/Events/Event.h"
#include "Ghost/Events/ApplicationEvent.h"

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

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_layerStack;
	private:
		static Application* s_Instance;
	};

	// TO BE defined in client
	Application* CreateApplication();
}