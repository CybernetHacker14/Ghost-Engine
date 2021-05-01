#include <Ghost.h>
#include <Ghost/Core/EntryPoint.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui/imgui.h"

#include "Sandbox2D.h"

class Sandbox : public Ghost::Application {
public:
	Sandbox(Ghost::ApplicationCommandLineArgs args)
		: Application("Sandbox", args) {
		//PushLayer(new ExampleLayer());
	}

	~Sandbox() {}
};

Ghost::Application* Ghost::CreateApplication(ApplicationCommandLineArgs args) {
	return new Sandbox(args); // reference using extern in EntryPoint.h
}
