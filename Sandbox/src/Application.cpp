#include <Gem.h>

#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui/imgui.h"

class ExampleLayer : public Gem::Layer
{
	Gem::Ref<Gem::Shader> m_Shader;
	Gem::Ref<Gem::VertexArray> m_VertexArray;

	Gem::Ref<Gem::Shader> m_Shader2, m_TextureShader;
	Gem::Ref<Gem::VertexArray> m_SquareVertexArray;

	Gem::Ref<Gem::Texture2D> m_Texture;

	Gem::OrthographicCamera m_OrthoCamera;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 5.0f;
	float m_CameraRotation = 0.0f;

	glm::vec3 m_SquarePos;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

public:
	ExampleLayer()
		: Layer("Example"), m_OrthoCamera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f), m_SquarePos(0.0f)
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

		m_Shader.reset(Gem::Shader::Create(vertexSrc, fragmentSrc));

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

		m_Shader2.reset(Gem::Shader::Create(vertexSrc2, fragmentSrc2));

		std::string textureShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string textureShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		m_TextureShader.reset(Gem::Shader::Create(textureShaderVertexSrc, textureShaderFragmentSrc));

		m_Texture = Gem::Texture2D::Create("Assets/Textures/Checkerboard.png");

		std::dynamic_pointer_cast<Gem::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Gem::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Gem::Timestep timestep) override
	{
		if (Gem::Input::IsKeyPressed(GEM_KEY_R)) 
		{
			m_CameraPosition.x = 0.0f;
			m_CameraPosition.y = 0.0f;
			m_CameraRotation = 0.0f;
		}

		if (Gem::Input::IsKeyPressed(GEM_KEY_LEFT) && Gem::Input::IsKeyPressed(GEM_KEY_LEFT_SHIFT))
			m_CameraRotation += m_CameraSpeed * 60 * timestep;
		else if (Gem::Input::IsKeyPressed(GEM_KEY_LEFT))
			m_CameraPosition.x -= m_CameraSpeed * timestep;

		if (Gem::Input::IsKeyPressed(GEM_KEY_RIGHT) && Gem::Input::IsKeyPressed(GEM_KEY_LEFT_SHIFT))
			m_CameraRotation -= m_CameraSpeed * 60 * timestep;
		else if (Gem::Input::IsKeyPressed(GEM_KEY_RIGHT))
			m_CameraPosition.x += m_CameraSpeed * timestep;

		if (Gem::Input::IsKeyPressed(GEM_KEY_UP))
			m_CameraPosition.y += m_CameraSpeed * timestep;
		if (Gem::Input::IsKeyPressed(GEM_KEY_DOWN))
			m_CameraPosition.y -= m_CameraSpeed * timestep;

		Gem::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Gem::RenderCommand::Clear();

		m_OrthoCamera.SetPosition(m_CameraPosition);
		m_OrthoCamera.SetRotation(m_CameraRotation);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		Gem::Renderer::BeginScene(m_OrthoCamera);
		{
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

			m_Texture->Bind();
			Gem::Renderer::Submit(m_TextureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

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