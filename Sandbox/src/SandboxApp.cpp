#include <Ghost.h>

#include "imgui/imgui.h"

class ExampleLayer : public Ghost::Layer {
public:
	ExampleLayer()
		:Layer("Example") {
	}

	void OnUpdate() override {
		bool state1 = Ghost::Input::IsKeyDown(GT_KEY_0);
		bool state2 = Ghost::Input::IsKeyUp(GT_KEY_0);

		if (state1) {
			GT_WARN("0 Key Down");
		}

		if (state2) {
			GT_WARN("0 Key Up");
		}
	}

	void OnImGuiRender() override {
		ImGui::Begin("SandBox");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(Ghost::Event& event) override {
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