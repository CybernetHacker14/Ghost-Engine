#include <Ghost.h>
#include <Ghost/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Ghost
{
	class GhostEditor : public Application {
	public:
		GhostEditor(ApplicationCommandLineArgs args)
			:Application("Ghost Engine", args) {
			PushLayer(new EditorLayer());
		}

		~GhostEditor() {}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args) {
		return new GhostEditor(args); // reference using external in EntryPoint.h
	}
}
