#pragma once
#include "Ghost/Core/Base.h"

#ifdef GT_PLATFORM_WINDOWS

extern Ghost::Application* Ghost::CreateApplication();

extern "C" {
	__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

int main(int argc, char** argv) {
	Ghost::Log::Init();

	GT_PROFILE_BEGIN_SESSION("Startup", "GhostProfile-Startup.json");
	auto app = Ghost::CreateApplication();
	GT_PROFILE_END_SESSION();

	GT_PROFILE_BEGIN_SESSION("Runtime", "GhostProfile-Runtime.json");
	app->Run();
	GT_PROFILE_END_SESSION();

	GT_PROFILE_BEGIN_SESSION("Shutdown", "GhostProfile-Shutdown.json");
	delete app;
	GT_PROFILE_END_SESSION();
}

#endif
