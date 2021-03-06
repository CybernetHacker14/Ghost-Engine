#pragma once

#include "Ghost/Core/Base.h"
#include "Ghost/Core/Window.h"

#include "Ghost/Core/LayerStack.h"
#include "Ghost/Events/Event.h"
#include "Ghost/Events/ApplicationEvent.h"

#include "Ghost/Core/Timestep.h"

#include "Ghost/ImGui/ImGuiLayer.h"

int main(int argc, char** argv);

namespace Ghost
{
	struct ApplicationCommandLineArgs {
		int Count = 0;
		char** Args = nullptr;
		const char* operator[](int index) const {
			GT_CORE_ASSERT(index < Count);
			return Args[index];
		}
	};

	class Application {
	public:
		Application(const std::string& name = "Ghost App", ApplicationCommandLineArgs args =
			ApplicationCommandLineArgs());
		virtual ~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		Window& GetWindow() { return *m_Window; }

		void Close();

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		static Application& Get() { return *s_Instance; }

		ApplicationCommandLineArgs GetCommandLineArgs() const { return m_CommandLineArgs; }
	private:
		void Run();
		bool OnWindowClosed(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		ApplicationCommandLineArgs m_CommandLineArgs;
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;
		bool m_Minimized = false;

		LayerStack m_layerStack;

		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	// TO BE defined in client
	Application* CreateApplication(ApplicationCommandLineArgs args);
}
