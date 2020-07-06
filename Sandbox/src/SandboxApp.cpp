#include <Ghost.h>

class ExampleLayer : public Ghost::Layer {
public:
	ExampleLayer()
		:Layer("Example") {
	}

	void OnUpdate() override {
		GT_INFO("ExampleLayer::Update");
	}

	void OnEvent(Ghost::Event& event) override {
		GT_TRACE("{0}", event);
	}
};

class Sandbox : public Ghost::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {
	}
};

Ghost::Application* Ghost::CreateApplication() {
	return new Sandbox(); // reference using extern in EntryPoint.h
}