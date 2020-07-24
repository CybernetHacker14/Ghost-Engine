#include <Ghost.h>

#include "imgui/imgui.h"

class ExampleLayer : public Ghost::Layer {
public:
	ExampleLayer()
		:Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f),
		m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Ghost::VertexArray::Create());

		float vertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		std::shared_ptr<Ghost::VertexBuffer> vertexBuffer;

		vertexBuffer.reset(Ghost::VertexBuffer::Create(vertices, sizeof(vertices)));

		Ghost::BufferLayout layout = {
			{Ghost::ShaderDataType::Float3, "a_Position"}
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };

		std::shared_ptr<Ghost::IndexBuffer> indexBuffer;

		indexBuffer.reset(Ghost::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_Shader.reset(Ghost::Shader::Create());

		std::string vertexSrc = R"(
			#version 460 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position + 0.5;
				gl_Position = u_ViewProjection * vec4(a_Position,1.0);
			}
		)";

		m_Shader->Compile(vertexSrc, Ghost::ShaderType::VertexShader);

		std::string fragmentSrc = R"(
			#version 460 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(v_Position, 1.0);
			}
		)";

		m_Shader->Compile(fragmentSrc, Ghost::ShaderType::FragmentShader);

		m_Shader->Link();
	}

	void OnUpdate() override {
		if (Ghost::Input::IsKeyPressed(GT_KEY_LEFT)) {
			m_CameraPosition.x -= m_CameraMoveSpeed;
		}
		else if (Ghost::Input::IsKeyPressed(GT_KEY_RIGHT)) {
			m_CameraPosition.x += m_CameraMoveSpeed;
		}

		if (Ghost::Input::IsKeyPressed(GT_KEY_UP)) {
			m_CameraPosition.y += m_CameraMoveSpeed;
		}
		else if (Ghost::Input::IsKeyPressed(GT_KEY_DOWN)) {
			m_CameraPosition.y -= m_CameraMoveSpeed;
		}

		if (Ghost::Input::IsKeyPressed(GT_KEY_A)) {
			m_CameraRotation += m_CameraRotateSpeed;
		}
		else if (Ghost::Input::IsKeyPressed(GT_KEY_D)) {
			m_CameraRotation -= m_CameraRotateSpeed;
		}

		if (Ghost::Input::IsKeyDown(GT_KEY_0)) {
			m_CameraPosition = { 0,0,0 };
		}

		Ghost::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Ghost::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Ghost::Renderer::BeginScene(m_Camera);

		Ghost::Renderer::Submit(m_Shader, m_VertexArray);

		Ghost::Renderer::EndScene();

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
	}

	void OnEvent(Ghost::Event& event) override {
	}
private:
	std::shared_ptr<Ghost::Shader> m_Shader;
	std::shared_ptr<Ghost::VertexArray> m_VertexArray;

	Ghost::OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 0.05f;

	float m_CameraRotation = 0;
	float m_CameraRotateSpeed = 2.0f;
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