#include <Gem.h>

class ExampleLayer : public Gem::Layer
{
	std::shared_ptr<Gem::Shader> m_Shader;
	std::shared_ptr <Gem::VertexArray> m_VertexArray;

	std::shared_ptr<Gem::Shader> m_Shader2;
	std::shared_ptr <Gem::VertexArray> m_SquareVertexArray;

	Gem::OrthographicCamera m_OrthoCamera;

public:
	ExampleLayer()
		: Layer("Example"), m_OrthoCamera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		m_VertexArray.reset(Gem::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.7f, 0.0f, 0.7f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 0.7f, 0.1f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.7f, 0.7f, 0.0f, 1.0f
		};

		std::shared_ptr<Gem::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Gem::VertexBuffer::Create(vertices, sizeof(vertices)));

		Gem::BufferLayout layout = {
			{ Gem::ShaderDataType::Float3, "a_Position" },
			{ Gem::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetBufferLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Gem::IndexBuffer> indexBuffer;
		indexBuffer.reset(Gem::IndexBuffer::Create(indices, (sizeof(indices) / sizeof(uint32_t))));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVertexArray.reset(Gem::VertexArray::Create());

		float vertices2[4 * 3] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<Gem::VertexBuffer> squareVertexBuffer;
		squareVertexBuffer.reset(Gem::VertexBuffer::Create(vertices2, sizeof(vertices2)));

		squareVertexBuffer->SetBufferLayout({
			{ Gem::ShaderDataType::Float3, "a_Position" }
		});
		m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

		uint32_t indices2[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Gem::IndexBuffer> squareIndexBuffer;
		squareIndexBuffer.reset(Gem::IndexBuffer::Create(indices2, (sizeof(indices2) / sizeof(uint32_t))));
		m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

		m_Shader.reset(new Gem::Shader(vertexSrc, fragmentSrc));

		std::string vertexSrc2 = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc2 = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.4, 0.7, 1.0);
			}
		)";

		m_Shader2.reset(new Gem::Shader(vertexSrc2, fragmentSrc2));
	}

	void OnUpdate() override
	{
		Gem::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Gem::RenderCommand::Clear();

		m_OrthoCamera.SetPosition({ 0.3f, 0.1f, 0.0f });
		m_OrthoCamera.SetRotation(45.0f);

		Gem::Renderer::BeginScene(m_OrthoCamera);
		{
			Gem::Renderer::Submit(m_Shader2, m_SquareVertexArray);
			Gem::Renderer::Submit(m_Shader, m_VertexArray);

			Gem::Renderer::EndScene();
		}
	}

	virtual void OnImGuiRender() override
	{

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