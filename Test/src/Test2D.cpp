#include "Test2D.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

Test2D::Test2D()
	: Layer("Test2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Test2D::OnAttach()
{
	m_Texture = Gem::Texture2D::Create("Assets/Textures/Checkerboard2.png");
}

void Test2D::OnDetach()
{
}

void Test2D::OnUpdate(Gem::Timestep timestep)
{
	m_CameraController.OnUpdate(timestep);

	Gem::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Gem::RenderCommand::Clear();

	Gem::Renderer2D::BeginScene(m_CameraController.GetCamera());
	{
		Gem::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Gem::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Gem::Renderer2D::DrawQuad({ -5.0f, -5.0f, -0.1f }, { 10.0f, 10.0f }, m_Texture, 10.0f);
		Gem::Renderer2D::DrawQuad({ -0.5f, -0.5f, 0.0f }, { 1.0f, 1.0f }, m_Texture, 20.0f);

	}
	Gem::Renderer2D::EndScene();
}

void Test2D::OnImGuiRender()
{
	ImGui::Begin("Sliders");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Test2D::OnEvent(Gem::Event& event)
{
	m_CameraController.OnEvent(event);
}
