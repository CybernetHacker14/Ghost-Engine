#include <Ghost.h>

class ExampleLayer : public Ghost::Layer {
public:
	ExampleLayer()
		:Layer("Example") {
	}

	void OnUpdate() override {
	}

	void OnEvent(Ghost::Event& event) override {
	}
};

class Sandbox : public Ghost::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new Ghost::ImGuiLayer());
	}

	~Sandbox() {
	}
};

Ghost::Application* Ghost::CreateApplication() {
	return new Sandbox(); // reference using extern in EntryPoint.h
}