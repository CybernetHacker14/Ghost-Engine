#pragma once

#ifdef GT_PLATFORM_WINDOWS

extern Ghost::Application* Ghost::CreateApplication();

int main(int argc, char** argv) {
	Ghost::Log::Init();
	char greeting[] = "CybernetHacker14";
	GT_CORE_WARN("Core Logging Initialized!");
	GT_INFO("Client Logging Initialized!");
	GT_TRACE("Hello User {0}", greeting);

	auto app = Ghost::CreateApplication();
	app->Run();
	delete app;
}

#endif