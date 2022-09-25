#include "Test2D.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

Test2D::Test2D()
	: Layer("Test2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Test2D::OnAttach()
{
	
	m_ChessPieces = Gem::Texture2D::Create("Assets/Textures/Pieces.png");

	glm::vec2 spriteSize = { 426.66f, 426.5f };
	m_BlackKing = Gem::SubTexture2D::CreateFromPosition(m_ChessPieces, { 0, 0 }, { spriteSize.x, spriteSize.y });
	m_WhiteKing = Gem::SubTexture2D::CreateFromPosition(m_ChessPieces, { 0, spriteSize.y }, { spriteSize.x, spriteSize.y });
	m_BlackQueen = Gem::SubTexture2D::CreateFromPosition(m_ChessPieces, { spriteSize.x, 0 }, { spriteSize.x, spriteSize.y });
	m_WhiteQueen = Gem::SubTexture2D::CreateFromPosition(m_ChessPieces, { spriteSize.x, spriteSize.y }, { spriteSize.x, spriteSize.y });

	m_CameraController.SetZoom(5.0f);
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

	glm::vec4 lightColor = { 0.8f, 0.7f, 0.5f, 1.0f };
	glm::vec4 darkColor = { 0.55f, 0.29f, 0.0f, 1.0f };

	Gem::Renderer2D::BeginScene(m_CameraController.GetCamera());
	{
		for (size_t file = 0; file < 8; file++)
		{
			for (size_t rank = 0; rank < 8; rank++)
			{
				bool isLightSquare = ((file + rank) % 2) != 0;

				glm::vec4 color = isLightSquare ? lightColor : darkColor;
				glm::vec2 pos = { -3.5f + file, -3.5f + rank };

				Gem::Renderer2D::DrawQuad(pos, { 1.0f, 1.0f }, color);
			}
		}

		Gem::Renderer2D::DrawQuad({ -0.5f, -3.5f, 1.0f }, { 1.0f, 1.0f }, m_WhiteQueen);
		Gem::Renderer2D::DrawQuad({ 0.5f, -3.5f, 1.0f }, { 1.0f, 1.0f }, m_WhiteKing);

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
