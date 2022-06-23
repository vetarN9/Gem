#include <Gem.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui/imgui.h"

class ExampleLayer : public Gem::Layer
{
	Gem::ShaderLibrary m_ShaderLibrary;
	Gem::Ref<Gem::Shader> m_Shader;
	Gem::Ref<Gem::VertexArray> m_VertexArray;

	Gem::Ref<Gem::Shader> m_Shader2;
	Gem::Ref<Gem::VertexArray> m_SquareVertexArray;

	Gem::Ref<Gem::Texture2D> m_Texture, m_Texture2;

	Gem::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f)
	{
		m_VertexArray.reset(Gem::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.7f, 0.0f, 0.7f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 0.7f, 0.1f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.7f, 0.7f, 0.0f, 1.0f
		};

		Gem::Ref<Gem::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Gem::VertexBuffer::Create(vertices, sizeof(vertices)));

		Gem::BufferLayout layout = {
			{ Gem::ShaderDataType::Float3, "a_Position" },
			{ Gem::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetBufferLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Gem::Ref<Gem::IndexBuffer> indexBuffer;
		indexBuffer.reset(Gem::IndexBuffer::Create(indices, (sizeof(indices) / sizeof(uint32_t))));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVertexArray.reset(Gem::VertexArray::Create());

		float vertices2[4 * 5] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Gem::Ref<Gem::VertexBuffer> squareVertexBuffer;
		squareVertexBuffer.reset(Gem::VertexBuffer::Create(vertices2, sizeof(vertices2)));

		squareVertexBuffer->SetBufferLayout({
			{ Gem::ShaderDataType::Float3, "a_Position" },
			{ Gem::ShaderDataType::Float2, "a_TexCoord" }
		});
		m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

		uint32_t indices2[6] = { 0, 1, 2, 2, 3, 0 };
		Gem::Ref<Gem::IndexBuffer> squareIndexBuffer;
		squareIndexBuffer.reset(Gem::IndexBuffer::Create(indices2, (sizeof(indices2) / sizeof(uint32_t))));
		m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position*0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader = Gem::Shader::Create("triangle", vertexSrc, fragmentSrc);

		std::string vertexSrc2 = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc2 = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_Shader2 = Gem::Shader::Create("square", vertexSrc2, fragmentSrc2);

		auto textureShader = m_ShaderLibrary.Load("Assets/Shaders/Texture.glsl");

		m_Texture = Gem::Texture2D::Create("Assets/Textures/Checkerboard.png");
		m_Texture2 = Gem::Texture2D::Create("Assets/Textures/Alena.png");

		std::dynamic_pointer_cast<Gem::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Gem::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Gem::Timestep timestep) override
	{
		m_CameraController.OnUpdate(timestep);

		Gem::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Gem::RenderCommand::Clear();


		Gem::Renderer::BeginScene(m_CameraController.GetCamera());
		{
			glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

			std::dynamic_pointer_cast<Gem::OpenGLShader>(m_Shader2)->Bind();
			std::dynamic_pointer_cast<Gem::OpenGLShader>(m_Shader2)->UploadUniformFloat3("u_Color", m_SquareColor);

			for (int x = 0; x < 20; x++) 
			{
				for (int y = 0; y < 20; y++)
				{
					glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
					glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
					Gem::Renderer::Submit(m_Shader2, m_SquareVertexArray, transform);
				}
			}

			auto textureShader = m_ShaderLibrary.Get("Texture");

			m_Texture->Bind();
			Gem::Renderer::Submit(textureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

			m_Texture2->Bind();
			Gem::Renderer::Submit(textureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

			//Gem::Renderer::Submit(m_Shader, m_VertexArray);

			Gem::Renderer::EndScene();
		}
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Sliders");
		{
			ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
			ImGui::End();
		}

	}

	void OnEvent(Gem::Event& event) override
	{
		m_CameraController.OnEvent(event);
	}
};

class Sandbox : public Gem::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Gem::Application* Gem::CreateApplication()
{
	return new Sandbox();
}