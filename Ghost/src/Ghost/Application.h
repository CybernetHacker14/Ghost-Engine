#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/Event.h"

namespace Ghost {
	class GHOST_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// TO BE defined in client
	Application* CreateApplication();
}