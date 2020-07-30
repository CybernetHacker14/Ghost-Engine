#include <Ghost.h>
#include <Ghost/Core/EntryPoint.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui/imgui.h"

#include "Sandbox2D.h"

class ExampleLayer : public Ghost::Layer {
public:
	ExampleLayer()
		:Layer("Example"), m_CameraController(1600.0f / 900.0f)
	{
		m_VertexArray = Ghost::VertexArray::Create();
		m_BGVertexArray = Ghost::VertexArray::Create();

		float vertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Ghost::Ref<Ghost::VertexBuffer> vertexBuffer;

		vertexBuffer = Ghost::VertexBuffer::Create(vertices, sizeof(vertices));

		Ghost::BufferLayout layout = {
			{Ghost::ShaderDataType::Float3, "a_Position"},
			{Ghost::ShaderDataType::Float2, "a_TexCoord"}
		};

		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);
		m_BGVertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };

		Ghost::Ref<Ghost::IndexBuffer> indexBuffer;

		indexBuffer = Ghost::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(indexBuffer);
		m_BGVertexArray->SetIndexBuffer(indexBuffer);

		#pragma region Flat Color Shader

		m_FlatColorShader = Ghost::Shader::Create();

		std::string flatColorVertexShaderSrc = R"(
			#version 460 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position + 0.5;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position,1.0);
			}
		)";

		m_FlatColorShader->Compile("FlatColor", flatColorVertexShaderSrc, Ghost::ShaderType::VertexShader);

		std::string flatColorFragmentShaderSrc = R"(
			#version 460 core

			layout(location = 0) out vec4 color;

			uniform vec4 u_Color;

			in vec3 v_Position;

			void main()
			{
				color = u_Color;
			}
		)";

		m_FlatColorShader->Compile("FlatColor", flatColorFragmentShaderSrc, Ghost::ShaderType::FragmentShader);

		m_FlatColorShader->Link();

		#pragma endregion

		#pragma region Texture Shader

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
		textureShader->Link();

		#pragma endregion

		m_Texture = Ghost::Texture2D::Create("assets/textures/test_texture.png");

		std::dynamic_pointer_cast<Ghost::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Ghost::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Ghost::Timestep ts) override {
		// Update

		m_CameraController.OnUpdate(ts);

		// Render
		Ghost::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Ghost::RenderCommand::Clear();

		Ghost::Renderer::BeginScene(m_CameraController.GetCamera());

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		for (int x = 0; x < 10; x++) {
			for (int y = 0; y < 10; y++) {
				std::dynamic_pointer_cast<Ghost::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_Color2);

				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

				Ghost::Renderer::Submit(m_FlatColorShader, m_VertexArray, transform);
			}
		}

		std::dynamic_pointer_cast<Ghost::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Ghost::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_Color1);
		Ghost::Renderer::Submit(m_FlatColorShader, m_BGVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		/*m_Texture->Bind();
		Ghost::Renderer::Submit(m_ShaderLibrary.Get("Texture"), m_VertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));*/

		Ghost::Renderer::EndScene();
	}

	void OnImGuiRender() override {
		ImGui::Begin("Color Editor");
		ImGui::ColorEdit4("Color 1", glm::value_ptr(m_Color1));
		ImGui::ColorEdit4("Color 2", glm::value_ptr(m_Color2));
		ImGui::End();
	}

	void OnEvent(Ghost::Event& e) override {
		m_CameraController.OnEvent(e);
	}
private:
	Ghost::ShaderLibrary m_ShaderLibrary;

	Ghost::Ref<Ghost::Shader> m_FlatColorShader;
	Ghost::Ref<Ghost::VertexArray> m_VertexArray, m_BGVertexArray;

	Ghost::Ref<Ghost::Texture2D> m_Texture;

	Ghost::OrthographicCameraController m_CameraController;

	glm::vec4 m_Color1 = { 0.8f, 0.2f, 0.2f, 0.3f };
	glm::vec4 m_Color2 = { 0.2f, 0.8f, 0.2f, 1.0f };
};

class SplashScreen : public Ghost::Layer {
public:
	SplashScreen()
		:Layer("Splash"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		#pragma region Background

		m_BackgroundVA = Ghost::VertexArray::Create();

		float sqB = ((float)glm::sqrt(3.0f)) * 0.25f;

		float backgroundVertices[3 * 6] = {
			 0.0f,   0.5f ,  0.0f, // 0
			 -sqB,   0.25f,  0.0f, // 1
			 -sqB,  -0.25f,  0.0f, // 2
			 0.0f,  -0.5f ,  0.0f, // 3
			  sqB,  -0.25f,  0.0f, // 4
			  sqB,   0.25f,  0.0f  // 5
		};

		Ghost::Ref<Ghost::VertexBuffer> backgroundVB;

		backgroundVB = Ghost::VertexBuffer::Create(backgroundVertices, sizeof(backgroundVertices));

		Ghost::BufferLayout backgroundLayout = {
			{Ghost::ShaderDataType::Float3, "a_Position"}
		};

		backgroundVB->SetLayout(backgroundLayout);

		m_BackgroundVA->AddVertexBuffer(backgroundVB);

		uint32_t backgroundIndices[3 * 4] = {
			0, 1, 2,
			2, 3, 4,
			4, 5, 0,
			0, 2, 4
		};

		Ghost::Ref<Ghost::IndexBuffer> backgroundIB;

		backgroundIB = Ghost::IndexBuffer::Create(backgroundIndices, sizeof(backgroundIndices) / sizeof(uint32_t));

		m_BackgroundVA->SetIndexBuffer(backgroundIB);

		#pragma endregion

		#pragma region Foreground

		m_ForegroundVA = Ghost::VertexArray::Create();

		float sqF1 = ((float)glm::sqrt(3.0f)) * 0.2f;
		float sqF2 = ((float)glm::sqrt(3.0f)) * 0.1F;

		float foregroundVertices[3 * 15] = {
			 0.0f,    0.4f,  0.0f, // 0
			-sqF1,    0.2f,  0.0f, // 1
			-sqF1,   -0.2f,  0.0f, // 2
			 0.0f,   -0.4f,  0.0f, // 3
			 sqF1,   -0.2f,  0.0f, // 4
			 sqF1,    0.0f,  0.0f, // 5
			 0.0f,    0.0f,  0.0f, // 6
			 0.0f,   -0.1f,  0.0f, // 7
			 sqF2,   -0.1f,  0.0f, // 8
			 0.0f,   -0.2f,  0.0f, // 9
			-sqF2,   -0.1f,  0.0f, // 10
			-sqF2,    0.1f,  0.0f, // 11
			 0.0f,    0.2f,  0.0f, // 12
			 sqF2,    0.1f,  0.0f, // 13
			 sqF1,    0.2f,  0.0f  // 14
		};

		Ghost::Ref<Ghost::VertexBuffer> foregroundVB;

		foregroundVB = Ghost::VertexBuffer::Create(foregroundVertices, sizeof(foregroundVertices));

		Ghost::BufferLayout foregroundLayout = {
			{Ghost::ShaderDataType::Float3, "a_Position"}
		};

		foregroundVB->SetLayout(foregroundLayout);

		m_ForegroundVA->AddVertexBuffer(foregroundVB);

		uint32_t foregroundIndices[3 * 13] = {
			14, 0, 13,
			13, 0, 12,
			1, 0, 12,
			12, 11, 1,
			2, 1, 11,
			11, 10, 2,
			3, 2, 10,
			10, 9, 3,
			3, 9, 8,
			8, 4, 3,
			4, 8, 5,
			6, 5, 8,
			8, 7, 6
		};

		Ghost::Ref<Ghost::IndexBuffer> foregroundIB;

		foregroundIB = Ghost::IndexBuffer::Create(foregroundIndices, sizeof(foregroundIndices) / sizeof(uint32_t));

		m_ForegroundVA->SetIndexBuffer(foregroundIB);

		#pragma endregion

		#pragma region Flat Color Shader

		m_FlatColorShader = Ghost::Shader::Create();

		std::string flatColorVertexShaderSrc = R"(
			#version 460 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position + 0.5;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position,1.0);
			}
		)";

		m_FlatColorShader->Compile("FlatColor", flatColorVertexShaderSrc, Ghost::ShaderType::VertexShader);

		std::string flatColorFragmentShaderSrc = R"(
			#version 460 core

			layout(location = 0) out vec4 color;

			uniform vec4 u_Color;

			in vec3 v_Position;

			void main()
			{
				color = u_Color;
			}
		)";

		m_FlatColorShader->Compile("FlatColor", flatColorFragmentShaderSrc, Ghost::ShaderType::FragmentShader);

		m_FlatColorShader->Link();

		#pragma endregion
	}

	void OnUpdate(Ghost::Timestep ts) override {
		Ghost::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Ghost::RenderCommand::Clear();

		Ghost::Renderer::BeginScene(m_Camera);

		std::dynamic_pointer_cast<Ghost::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Ghost::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_BackgroundColor);

		Ghost::Renderer::Submit(m_FlatColorShader, m_BackgroundVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		std::dynamic_pointer_cast<Ghost::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Ghost::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_ForegroundColor);

		Ghost::Renderer::Submit(m_FlatColorShader, m_ForegroundVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		Ghost::Renderer::EndScene();
	}

	void OnImGuiRender() override {
		ImGui::Begin("Console");
		ImGui::Text("Welcome to Ghost Engine");
		ImGui::End();
	}

	void OnEvent(Ghost::Event& event) override {
	}
private:
	Ghost::Ref<Ghost::Shader> m_FlatColorShader;
	Ghost::Ref<Ghost::VertexArray> m_BackgroundVA, m_ForegroundVA;

	Ghost::OrthographicCamera m_Camera;

	glm::vec4 m_BackgroundColor = { 0.2f, 0.2f, 0.2f, 1.0f };
	glm::vec4 m_ForegroundColor = { 0.4f, 0.4f, 0.4f, 1.0f };
};

class Sandbox : public Ghost::Application {
public:
	Sandbox() {
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox() {
	}
};

Ghost::Application* Ghost::CreateApplication() {
	return new Sandbox(); // reference using extern in EntryPoint.h
}