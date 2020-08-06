#include "Sandbox2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
	Ghost::Renderer2D::ResetStats();
	Ghost::RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f,1 });
	Ghost::RenderCommand::Clear();

	{
		static float rotation = 30.0f;
		rotation += 1.0f;

		Ghost::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Ghost::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Ghost::Renderer2D::DrawRotatedQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, glm::radians(-25.0f), { 0.2f, 0.3f, 0.8f, 1.0f });
		Ghost::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 5.0f, 5.0f }, m_Texture);
		Ghost::Renderer2D::DrawRotatedQuad({ -5.0f, 0.0f, 0.1f }, { 3.0f, 3.0f }, glm::radians(rotation), m_Texture);

		Ghost::Renderer2D::EndScene();
	}

	{
		Ghost::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f) {
			for (float x = -5.0f; x < 5.0f; x += 0.5f) {
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f,(y + 5.0f) / 10.0f,0.7f };
				Ghost::Renderer2D::DrawQuad({ x,y }, { 0.45f,0.45f }, color);
			}
		}
		Ghost::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	GT_PROFILE_FUNCTION();
	ImGui::Begin("Settings");
	auto stats = Ghost::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats :");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
	ImGui::End();
}

void Sandbox2D::OnEvent(Ghost::Event& e)
{
	m_CameraController.OnEvent(e);
}