#pragma once

#include <Gem.h>

class Test2D : public Gem::Layer
{
	Gem::OrthographicCameraController m_CameraController;

	// Temp
	Gem::Ref<Gem::VertexArray> m_SquareVertexArray;
	Gem::Ref<Gem::Shader> m_FlatColorShader;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

public:
	Test2D();
	virtual ~Test2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Gem::Timestep timestep) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Gem::Event& event) override;

};