#pragma once

#include "Ghost.h"

class Sandbox2D : public Ghost::Layer {
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Ghost::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Ghost::Event& e) override;

private:
	Ghost::OrthographicCameraController m_CameraController;

	// Temp
	Ghost::Ref<Ghost::VertexArray> m_SquareVA;
	Ghost::Ref<Ghost::Shader> m_FlatColorShader;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};