#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CameraController(1600.0f / 900.0f)
{
}

void Sandbox2D::OnAttach()
{
	m_SquareVA = Ghost::VertexArray::Create();

	float squareVertices[3 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	Ghost::Ref<Ghost::VertexBuffer> squareVB;
	squareVB = Ghost::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
	squareVB->SetLayout({
		{Ghost::ShaderDataType::Float3, "a_Position"}
		});

	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
	Ghost::Ref<Ghost::IndexBuffer> squareIB;
	squareIB = Ghost::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
	m_SquareVA->SetIndexBuffer(squareIB);

	m_FlatColorShader = Ghost::Shader::Create();
	m_FlatColorShader->Compile("assets/shaders/FlatColor.glsl");
	m_FlatColorShader->Link();
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Ghost::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Ghost::RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f,1 });
	Ghost::RenderCommand::Clear();

	Ghost::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<Ghost::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<Ghost::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

	Ghost::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Ghost::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Ghost::Event& e)
{
	m_CameraController.OnEvent(e);
}