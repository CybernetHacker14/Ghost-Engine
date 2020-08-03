#include "Sandbox2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CameraController(1600.0f / 900.0f)
{
}

void Sandbox2D::OnAttach()
{
	GT_PROFILE_FUNCTION();

	m_Texture = Ghost::Texture2D::Create("assets/textures/crate2_diffuse.png");
}

void Sandbox2D::OnDetach()
{
	GT_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Ghost::Timestep ts)
{
	GT_PROFILE_FUNCTION();

	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Ghost::RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f,1 });
	Ghost::RenderCommand::Clear();

	Ghost::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Ghost::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Ghost::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	//Ghost::Renderer2D::DrawRotatedQuad({ -0.5f, -0.5f }, { 0.2f, 0.2f }, glm::radians(-25.0f), { 0.2f, 0.8f, 0.2f, 1.0f });
	Ghost::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 5.0f, 5.0f }, m_Texture);
	Ghost::Renderer2D::DrawQuad({ -5.0f, 0.0f, -0.1f }, { 3.0f, 3.0f }, m_Texture);

	//Ghost::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f, -0.1f }, { 5.0f, 5.0f }, glm::radians(30.0f), m_Texture);

	Ghost::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	GT_PROFILE_FUNCTION();
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Ghost::Event& e)
{
	m_CameraController.OnEvent(e);
}