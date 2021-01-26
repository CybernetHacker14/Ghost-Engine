#include "gtpch.h"

#include "Ghost/Core/Application.h"
#include "Ghost/Core/Input.h"
#include "Ghost/Core/Log.h"
#include "Ghost/Renderer/Renderer.h"

#include <GLFW/glfw3.h>

namespace Ghost {
	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string& name)
	{
		GT_PROFILE_FUNCTION();

		GT_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Window::Create(WindowProps(name));
		m_Window->SetEventCallback(GT_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		GT_PROFILE_FUNCTION();

		Renderer::Shutdown();
	}

	void Application::PushLayer(Layer* layer)
	{
		GT_PROFILE_FUNCTION();

		m_layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		GT_PROFILE_FUNCTION();

		m_layerStack.PushLayerOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::Close()
	{
		m_Running = false;
	}

	void Application::OnEvent(Event& e)
	{
		GT_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(GT_BIND_EVENT_FN(Application::OnWindowClosed));
		dispatcher.Dispatch<WindowResizeEvent>(GT_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_layerStack.rbegin(); it != m_layerStack.rend(); ++it) {
			if (e.handled) {
				break;
			}
			(*it)->OnEvent(e);
		}
	}

	void Application::Run()
	{
		GT_PROFILE_FUNCTION();

		while (m_Running) {
			GT_PROFILE_SCOPE("RunLoop");

			float time = (float)glfwGetTime(); // Platform::GetTime() - Platform based implementation and abstraction
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized) {
				{
					GT_PROFILE_SCOPE("LayerStack OnUpdate");

					for (Layer* layer : m_layerStack)
						layer->OnUpdate(timestep);
				}

				m_ImGuiLayer->Begin();
				{
					GT_PROFILE_SCOPE("LayerStack OnImGuiRender");

					for (Layer* layer : m_layerStack)
						layer->OnImGuiRender();
				}
				m_ImGuiLayer->End();
			}

			Input::OnUpdate();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		GT_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0) {
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
}
