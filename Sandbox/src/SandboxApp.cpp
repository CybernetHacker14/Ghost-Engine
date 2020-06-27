#include <Ghost.h>

class Sandbox : public Ghost::Application {
public:
	Sandbox() {
	}

	~Sandbox() {
	}
};

Ghost::Application* Ghost::CreateApplication() {
	return new Sandbox(); // reference using extern in EntryPoint.h
}