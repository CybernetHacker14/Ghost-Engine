#pragma once

#include "Core.h"
#include "Window.h"

#include "Ghost/LayerStack.h"
#include "Ghost/Events/Event.h"
#include "Ghost/Events/ApplicationEvent.h"

#include "Ghost/ImGui/ImGuiLayer.h"

#include "Ghost/Renderer/Buffer.h"
#include "Ghost/Renderer/Shader.h"

namespace Ghost {
	class GHOST_API Application
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

		unsigned int m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	private:
		static Application* s_Instance;
	};

	// TO BE defined in client
	Application* CreateApplication();
}