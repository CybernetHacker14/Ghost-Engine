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
	Ghost::Ref<Ghost::Framebuffer> m_Framebuffer;

	Ghost::Ref<Ghost::Texture2D> m_Texture;
};