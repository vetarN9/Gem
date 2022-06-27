#include "Test2D.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"
#include <glm/gtc/type_ptr.hpp>

Test2D::Test2D()
	: Layer("Test2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Test2D::OnAttach()
{
	m_SquareVertexArray = Gem::VertexArray::Create();

	float vertices[4 * 3] = {
		-0.5f, -0.5f,  0.0f,
		 0.5f, -0.5f,  0.0f,
		 0.5f,  0.5f,  0.0f,
		-0.5f,  0.5f,  0.0f
	};

	Gem::Ref<Gem::VertexBuffer> squareVertexBuffer;
	squareVertexBuffer = Gem::VertexBuffer::Create(vertices, sizeof(vertices));

	squareVertexBuffer->SetBufferLayout({
			{ Gem::ShaderDataType::Float3, "a_Position" },
		});
	m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

	uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
	Gem::Ref<Gem::IndexBuffer> squareIndexBuffer;
	squareIndexBuffer.reset(Gem::IndexBuffer::Create(indices, (sizeof(indices) / sizeof(uint32_t))));
	m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

	m_FlatColorShader = Gem::Shader::Create("Assets/Shaders/FlatColor.glsl");
}

void Test2D::OnDetach()
{
}

void Test2D::OnUpdate(Gem::Timestep timestep)
{
	m_CameraController.OnUpdate(timestep);

	Gem::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Gem::RenderCommand::Clear();

	Gem::Renderer::BeginScene(m_CameraController.GetCamera());
	{
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Gem::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Gem::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

		Gem::Renderer::Submit(m_FlatColorShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
	}
	Gem::Renderer::EndScene();
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
