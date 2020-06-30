#include "gtpch.h"
#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Ghost/Log.h"

namespace Ghost {
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1200, 720);
		if (e.IsInCategory(EventCategoryApplication)) {
			GT_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput)) {
			GT_TRACE(e);
		}

		while (true);
	}
}