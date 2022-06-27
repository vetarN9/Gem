#include "gempch.h"

#include "Renderer2D.h"

#include "Core/Renderer/Buffer/VertexArray.h"
#include "Core/Renderer/shader/shader.h"
#include "Core/Renderer/Renderer/RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Gem
{

	struct Data
	{
		Ref<VertexArray> quadVertexArray;
		Ref<Shader> shader;
		Ref<Shader> texture;
	};

	static Data* s_Data;

	void Renderer2D::Init()
	{
		s_Data = new Data();
		s_Data->quadVertexArray = VertexArray::Create();

		float vertices[4 * 5] = {
			-0.5f, -0.5f,  0.0f,  0.0f,  0.0f,
			 0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.0f,  1.0f,  1.0f,
			-0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		};

		Ref<VertexBuffer> squareVertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

		squareVertexBuffer->SetBufferLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" }
		});

		s_Data->quadVertexArray->AddVertexBuffer(squareVertexBuffer);

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> squareIndexBuffer = 
			IndexBuffer::Create(indices, (sizeof(indices) / sizeof(uint32_t)));
		s_Data->quadVertexArray->SetIndexBuffer(squareIndexBuffer);

		s_Data->shader = Shader::Create("Assets/Shaders/FlatColor.glsl");
		s_Data->texture = Shader::Create("Assets/Shaders/Texture.glsl");
		s_Data->texture->Bind();
		s_Data->texture->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Data->shader->Bind();
		s_Data->shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		s_Data->texture->Bind();
		s_Data->texture->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ pos.x, pos.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color)
	{
		s_Data->shader->Bind();
		s_Data->shader->SetFloat4("u_Color", color);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
		s_Data->shader->SetMat4("u_Transform", transform);

		s_Data->quadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->quadVertexArray);
	}


	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		DrawQuad({ pos.x, pos.y, 0.0f }, size, texture);
	}

	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		s_Data->texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->texture->SetMat4("u_Transform", transform);

		texture->Bind();

		s_Data->quadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->quadVertexArray);
	}

	void Renderer2D::DrawQuadRotated(const glm::vec2& pos, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		DrawQuadRotated({ pos.x, pos.y, 0.0f }, size, rotation, color);
	}

	void Renderer2D::DrawQuadRotated(const glm::vec3& pos, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		s_Data->shader->Bind();
		s_Data->shader->SetFloat4("u_Color", color);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * 
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_Data->shader->SetMat4("u_Transform", transform);

		s_Data->quadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->quadVertexArray);
	}

}