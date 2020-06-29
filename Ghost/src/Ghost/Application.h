#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Ghost {
	class GHOST_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// TO BE defined in client
	Application* CreateApplication();
}