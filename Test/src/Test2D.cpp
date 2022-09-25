#include "Test2D.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

Test2D::Test2D()
	: Layer("Test2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Test2D::OnAttach()
{
	m_Checkerboard = Gem::Texture2D::Create("Assets/Textures/Checkerboard.png");
	m_SpriteSheet = Gem::Texture2D::Create("Assets/Textures/RPGpack_sheet_2X.png");
	float spriteSize = 128.0f;
	m_SubTexture = Gem::SubTexture2D::CreateFromPosition(m_SpriteSheet, { 2*spriteSize, 1*spriteSize }, { spriteSize, 2*spriteSize });
}

void Test2D::OnDetach()
{
}

void Test2D::OnUpdate(Gem::Timestep timestep)
{
	m_CameraController.OnUpdate(timestep);

	Gem::Renderer2D::ResetStats();

	Gem::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Gem::RenderCommand::Clear();

	static float rotation = 0.0f;
	rotation += timestep * 50.0f;

	//Gem::Renderer2D::BeginScene(m_CameraController.GetCamera());
	//{
	//	Gem::Renderer2D::DrawQuadRotated({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
	//	Gem::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	//	Gem::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	//	Gem::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_Checkerboard, 10.0f);
	//	Gem::Renderer2D::DrawQuadRotated({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_Checkerboard, 20.0f);

	//}
	//Gem::Renderer2D::EndScene();

	//Gem::Renderer2D::BeginScene(m_CameraController.GetCamera());
	//{
	//	for (float y = -5.0f; y < 5.0f; y += 0.5f)
	//	{
	//		for (float x = -5.0f; x < 5.0f; x += 0.5f)
	//		{
	//			glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
	//			Gem::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
	//		}
	//	}
	//}

	Gem::Renderer2D::BeginScene(m_CameraController.GetCamera());
	{
		Gem::Renderer2D::DrawQuad({ 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f }, m_SpriteSheet);
		Gem::Renderer2D::DrawQuad({ 0.0f, -1.0f, 0.0f }, { 1.0f, 2.0f }, m_SubTexture);
	}

	Gem::Renderer2D::EndScene();
}

void Test2D::OnImGuiRender()
{
	ImGui::Begin("Stats");
	{
		auto stats = Gem::Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.drawCalls);
		ImGui::Text("Quads: %d", stats.quadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
	}
	ImGui::End();
}

void Test2D::OnEvent(Gem::Event& event)
{
	m_CameraController.OnEvent(event);
}
