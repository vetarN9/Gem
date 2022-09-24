#include "gempch.h"

#include "Core/Renderer/Renderer/Renderer2D.h"

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
		float texIndex;
		float tilingFactor;
	};

	struct Data
	{
		const uint32_t maxQuads = 10000;
		const uint32_t maxVertices = maxQuads * 4;
		const uint32_t maxIndices = maxQuads * 6;
		static const uint32_t maxTextureSlots = 32;

		Ref<VertexArray> quadVertexArray;
		Ref<VertexBuffer> quadVertexBuffer;
		Ref<Shader> textureShader;
		Ref<Texture2D> whiteTexture;

		uint32_t quadIndexCount = 0;
		QuadVertex* quadVertexBufferBase = nullptr;
		QuadVertex* quadVertexBufferPtr = nullptr;

		std::array<Ref<Texture2D>, maxTextureSlots> textureSlots;
		uint32_t textureSlotIndex = 1;
	};

	static Data s_Data;

	void Renderer2D::Init()
	{
		s_Data.quadVertexArray = VertexArray::Create();

		s_Data.quadVertexBuffer = VertexBuffer::Create(s_Data.maxVertices * sizeof(QuadVertex));

		s_Data.quadVertexBuffer->SetBufferLayout({
			{ ShaderDataType::Float3,	"a_Position" },
			{ ShaderDataType::Float4,	"a_Color" },
			{ ShaderDataType::Float2,	"a_TexCoord" },
			{ ShaderDataType::Float,	"a_TexIndex" },
			{ ShaderDataType::Float,	"a_TilingFactor" }
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
		s_Data.whiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		int32_t samplers[s_Data.maxTextureSlots];
		for (uint32_t i = 0; i < s_Data.maxTextureSlots; i++)
			samplers[i] = i;

		s_Data.textureShader = Shader::Create("Assets/Shaders/Texture.glsl");
		s_Data.textureShader->Bind();
		s_Data.textureShader->SetIntArray("u_Textures", samplers, s_Data.maxTextureSlots);

		// Set all texture slots to 0
		s_Data.textureSlots[0] = s_Data.whiteTexture;
	}

	void Renderer2D::Shutdown()
	{
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Data.textureShader->Bind();
		s_Data.textureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		s_Data.quadIndexCount = 0;
		s_Data.quadVertexBufferPtr = s_Data.quadVertexBufferBase;

		s_Data.textureSlotIndex = 1;
	}

	void Renderer2D::EndScene()
	{
		uint32_t dataSize = (uint8_t*)s_Data.quadVertexBufferPtr - (uint8_t*)s_Data.quadVertexBufferBase;
		s_Data.quadVertexBuffer->SetData(s_Data.quadVertexBufferBase, dataSize);

		Flush();
	}

	void Renderer2D::Flush()
	{
		for (uint32_t i = 0; i < s_Data.textureSlotIndex; i++)
			s_Data.textureSlots[i]->Bind(i);

		RenderCommand::DrawIndexed(s_Data.quadVertexArray, s_Data.quadIndexCount);
	}

	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ pos.x, pos.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color)
	{
		const float texIndex = 0.0f; // White Texture
		const float tilingFactor = 1.0f;

		// Bottom left
		s_Data.quadVertexBufferPtr->pos = pos;
		s_Data.quadVertexBufferPtr->color = color;
		s_Data.quadVertexBufferPtr->texCoord = { 0.0f, 0.0f };
		s_Data.quadVertexBufferPtr->texIndex = texIndex;
		s_Data.quadVertexBufferPtr->tilingFactor = tilingFactor;
		s_Data.quadVertexBufferPtr++;
		
		// Bottom right
		s_Data.quadVertexBufferPtr->pos = { pos.x + size.x, pos.y, 0.0f };
		s_Data.quadVertexBufferPtr->color = color;
		s_Data.quadVertexBufferPtr->texCoord = { 1.0f, 0.0f };
		s_Data.quadVertexBufferPtr->texIndex = texIndex;
		s_Data.quadVertexBufferPtr->tilingFactor = tilingFactor;
		s_Data.quadVertexBufferPtr++;
			   
		// Top right
		s_Data.quadVertexBufferPtr->pos = { pos.x + size.x, pos.y + size.y, 0.0f };
		s_Data.quadVertexBufferPtr->color = color;
		s_Data.quadVertexBufferPtr->texCoord = { 1.0f, 1.0f };
		s_Data.quadVertexBufferPtr->texIndex = texIndex;
		s_Data.quadVertexBufferPtr->tilingFactor = tilingFactor;
		s_Data.quadVertexBufferPtr++;
			 
		// Top left
		s_Data.quadVertexBufferPtr->pos = { pos.x, pos.y + size.y, 0.0f };
		s_Data.quadVertexBufferPtr->color = color;
		s_Data.quadVertexBufferPtr->texCoord = { 0.0f, 1.0f };
		s_Data.quadVertexBufferPtr->texIndex = texIndex;
		s_Data.quadVertexBufferPtr->tilingFactor = tilingFactor;
		s_Data.quadVertexBufferPtr++;
			   
		s_Data.quadIndexCount += 6;
	}


	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tint)
	{
		DrawQuad({ pos.x, pos.y, 0.0f }, size, texture, tilingFactor, tint);
	}

	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tint)
	{
		constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < s_Data.textureSlotIndex; i++)
		{
			if (*s_Data.textureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)s_Data.textureSlotIndex;
			s_Data.textureSlots[s_Data.textureSlotIndex] = texture;
			s_Data.textureSlotIndex++;
		}

		s_Data.quadVertexBufferPtr->pos = pos;
		s_Data.quadVertexBufferPtr->color = color;
		s_Data.quadVertexBufferPtr->texCoord = { 0.0f, 0.0f };
		s_Data.quadVertexBufferPtr->texIndex = textureIndex;
		s_Data.quadVertexBufferPtr->tilingFactor = tilingFactor;
		s_Data.quadVertexBufferPtr++;

		s_Data.quadVertexBufferPtr->pos = { pos.x + size.x, pos.y, 0.0f };
		s_Data.quadVertexBufferPtr->color = color;
		s_Data.quadVertexBufferPtr->texCoord = { 1.0f, 0.0f };
		s_Data.quadVertexBufferPtr->texIndex = textureIndex;
		s_Data.quadVertexBufferPtr->tilingFactor = tilingFactor;
		s_Data.quadVertexBufferPtr++;

		s_Data.quadVertexBufferPtr->pos = { pos.x + size.x, pos.y + size.y, 0.0f };
		s_Data.quadVertexBufferPtr->color = color;
		s_Data.quadVertexBufferPtr->texCoord = { 1.0f, 1.0f };
		s_Data.quadVertexBufferPtr->texIndex = textureIndex;
		s_Data.quadVertexBufferPtr->tilingFactor = tilingFactor;
		s_Data.quadVertexBufferPtr++;

		s_Data.quadVertexBufferPtr->pos = { pos.x, pos.y + size.y, 0.0f };
		s_Data.quadVertexBufferPtr->color = color;
		s_Data.quadVertexBufferPtr->texCoord = { 0.0f, 1.0f };
		s_Data.quadVertexBufferPtr->texIndex = textureIndex;
		s_Data.quadVertexBufferPtr->tilingFactor = tilingFactor;
		s_Data.quadVertexBufferPtr++;

		s_Data.quadIndexCount += 6;

		/*s_Data.textureShader->SetFloat4("u_Color", tint);
		s_Data.textureShader->SetFloat("u_TilingFactor", tilingFactor);
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * 
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data.textureShader->SetMat4("u_Transform", transform);

		s_Data.quadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.quadVertexArray);*/
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& pos, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		DrawRotatedQuad({ pos.x, pos.y, 0.0f }, size, rotation, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& pos, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		s_Data.textureShader->SetFloat4("u_Color", color);
		s_Data.textureShader->SetFloat("u_TilingFactor", 1.0f);
		s_Data.whiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data.textureShader->SetMat4("u_Transform", transform);
		s_Data.quadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.quadVertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& pos, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tint)
	{
		DrawRotatedQuad({ pos.x, pos.y, 0.0f }, size, rotation, texture, tilingFactor, tint);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& pos, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tint)
	{
		s_Data.textureShader->SetFloat4("u_Color", tint);
		s_Data.textureShader->SetFloat("u_TilingFactor", tilingFactor);
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data.textureShader->SetMat4("u_Transform", transform);

		s_Data.quadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.quadVertexArray);
	}
}