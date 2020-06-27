#pragma once

#ifdef GT_PLATFORM_WINDOWS

extern Ghost::Application* Ghost::CreateApplication();

int main(int argc, char** argv) {
	auto app = Ghost::CreateApplication();
	app->Run();
	delete app;
}

#endif