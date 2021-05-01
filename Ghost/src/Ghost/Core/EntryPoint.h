#pragma once
#include "Ghost/Core/Base.h"
#include "Ghost/Core/Application.h"

#ifdef GT_PLATFORM_WINDOWS

extern Ghost::Application* Ghost::CreateApplication(ApplicationCommandLineArgs args);

extern "C" {
	__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

int main(int argc, char** argv) {
	Ghost::Log::Init();

	GT_PROFILE_BEGIN_SESSION("Startup", "GhostProfile-Startup.json");
	auto app = Ghost::CreateApplication({ argc, argv });
	GT_PROFILE_END_SESSION();

	GT_PROFILE_BEGIN_SESSION("Runtime", "GhostProfile-Runtime.json");
	app->Run();
	GT_PROFILE_END_SESSION();

	GT_PROFILE_BEGIN_SESSION("Shutdown", "GhostProfile-Shutdown.json");
	delete app;
	GT_PROFILE_END_SESSION();
}

#endif
