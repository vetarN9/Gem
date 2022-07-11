#include "gempch.h"

#include "Renderer2D.h"

#include "Core/Renderer/Buffer/VertexArray.h"
#include "Core/Renderer/shader/shader.h"
#include "Core/Renderer/Renderer/RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Gem
{
	struct QuadVertex
	{
		glm::vec3 pos;
		glm::vec4 color;
		glm::vec2 texCoord;
	};

	struct Data
	{
		const uint32_t maxQuads = 10000;
		const uint32_t maxVertices = maxQuads * 4;
		const uint32_t maxIndices = maxQuads * 6;

		Ref<VertexArray> quadVertexArray;
		Ref<VertexBuffer> quadVertexBuffer;
		Ref<Shader> texture;
		Ref<Texture2D> whiteTexture;

		uint32_t indexCount = 0;
		QuadVertex* quadVertexBufferBase = nullptr;
		QuadVertex* quadVertexBufferPtr = nullptr;
	};

	static Data s_Data;

	void Renderer2D::Init()
	{
		s_Data.quadVertexArray = VertexArray::Create();

		// Create the quadVertexBuffer and add it to the vertexArray.
		s_Data.quadVertexBuffer = VertexBuffer::Create(s_Data.maxVertices * sizeof(QuadVertex));

		s_Data.quadVertexBuffer->SetBufferLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float2, "a_TexCoord" }
		});

		s_Data.quadVertexArray->AddVertexBuffer(s_Data.quadVertexBuffer);

		s_Data.quadVertexBufferBase = new QuadVertex[s_Data.maxVertices];

		uint32_t* quadIndices = new uint32_t[s_Data.maxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.maxIndices; i += 6) 
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> quadIndexBuffer = IndexBuffer::Create(quadIndices, s_Data.maxIndices);
		s_Data.quadVertexArray->SetIndexBuffer(quadIndexBuffer);
		delete[] quadIndices;


		s_Data.whiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data.whiteTexture->SetData(&whiteTextureData, sizeof(whiteTextureData));

		s_Data.texture = Shader::Create("Assets/Shaders/Texture.glsl");
		s_Data.texture->Bind();
		s_Data.texture->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{

	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Data.texture->Bind();
		s_Data.texture->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		s_Data.indexCount = 0;
		s_Data.quadVertexBufferPtr = s_Data.quadVertexBufferBase;
	}

	void Renderer2D::EndScene()
	{
		uint32_t dataSize = (uint8_t*)s_Data.quadVertexBufferPtr - (uint8_t*)s_Data.quadVertexBufferBase;
		s_Data.quadVertexBuffer->SetData(s_Data.quadVertexBufferBase, dataSize);
		Flush();
	}

	void Renderer2D::Flush()
	{
		RenderCommand::DrawIndexed(s_Data.quadVertexArray, s_Data.indexCount);
	}

	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuadRotated({ pos.x, pos.y, 0.0f }, size, 0.0f, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color)
	{
		// Bottom left
		s_Data.quadVertexBufferPtr->pos = pos;
		s_Data.quadVertexBufferPtr->color = color;
		s_Data.quadVertexBufferPtr->texCoord = { 0.0f, 0.0f };
		s_Data.quadVertexBufferPtr++;

		// Bottom right
		s_Data.quadVertexBufferPtr->pos = { pos.x + size.x, pos.y, 0.0f };
		s_Data.quadVertexBufferPtr->color = color;
		s_Data.quadVertexBufferPtr->texCoord = { 1.0f, 0.0f };
		s_Data.quadVertexBufferPtr++;

		// Top right
		s_Data.quadVertexBufferPtr->pos = { pos.x + size.x, pos.y + size.y, 0.0f };
		s_Data.quadVertexBufferPtr->color = color;
		s_Data.quadVertexBufferPtr->texCoord = { 1.0f, 1.0f };
		s_Data.quadVertexBufferPtr++;

		// Top left
		s_Data.quadVertexBufferPtr->pos = { pos.x, pos.y + size.y, 0.0f };
		s_Data.quadVertexBufferPtr->color = color;
		s_Data.quadVertexBufferPtr->texCoord = { 0.0f, 1.0f };
		s_Data.quadVertexBufferPtr++;

		s_Data.indexCount += 6;

		/*s_Data.whiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data.texture->SetMat4("u_Transform", transform);

		s_Data.quadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.quadVertexArray);*/
	}


	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		DrawQuadRotated({ pos.x, pos.y, 0.0f }, size, 0.0f, texture);
	}

	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		DrawQuadRotated(pos, size, 0.0f, texture, 1.0f, glm::vec4(1.0f));
	}

	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture2D>& texture, const float tiling)
	{
		DrawQuadRotated(pos, size, 0.0f, texture, tiling, glm::vec4(1.0f));
	}

	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture2D>& texture, const float tiling, const glm::vec4& tint)
	{
		DrawQuadRotated(pos, size, 0.0f, texture, tiling, tint);
	}

	void Renderer2D::DrawQuadRotated(const glm::vec2& pos, const glm::vec2& size, const float rotation, const glm::vec4& color)
	{
		DrawQuadRotated({ pos.x, pos.y, 0.0f }, size, rotation, color);
	}

	void Renderer2D::DrawQuadRotated(const glm::vec3& pos, const glm::vec2& size, const float rotation, const glm::vec4& color)
	{
		s_Data.texture->SetFloat4("u_Color", color);
		s_Data.whiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * 
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_Data.texture->SetMat4("u_Transform", transform);

		s_Data.quadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.quadVertexArray);
	}

	void Renderer2D::DrawQuadRotated(const glm::vec2& pos, const glm::vec2& size, const float rotation, const Ref<Texture2D>& texture)
	{
		DrawQuadRotated({ pos.x, pos.y, 0.0f }, size, rotation, texture, 1.0f, glm::vec4(1.0f));
	}

	void Renderer2D::DrawQuadRotated(const glm::vec3& pos, const glm::vec2& size, const float rotation, const Ref<Texture2D>& texture)
	{
		DrawQuadRotated(pos, size, rotation, texture, 1.0f, glm::vec4(1.0f));
	}

	void Renderer2D::DrawQuadRotated(const glm::vec3& pos, const glm::vec2& size, const float rotation, const Ref<Texture2D>& texture, const float tiling)
	{
		DrawQuadRotated(pos, size, rotation, texture, tiling, glm::vec4(1.0f));
	}

	void Renderer2D::DrawQuadRotated(const glm::vec3& pos, const glm::vec2& size, const float rotation, const Ref<Texture2D>& texture, const float tiling, const glm::vec4& tint)
	{
		s_Data.texture->SetFloat4("u_Color", tint);
		s_Data.texture->SetFloat("u_Tiling", tiling);
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_Data.texture->SetMat4("u_Transform", transform);

		s_Data.quadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.quadVertexArray);
	}

}