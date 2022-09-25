#pragma once

#include "Core/Renderer/Camera/OrthographicCamera.h"
#include "Core/Renderer/Texture/Texture.h"
#include "Core/Renderer/Texture/SubTexture2D.h"

namespace Gem
{

	class Renderer2D
	{
		static void NewBatch();

		static void DrawQuadBatched(const glm::mat4 transform, const Ref<Texture2D>& texture, const glm::vec2* texCoords, float tilingFactor, const glm::vec4& tint);

	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		static void Flush();

		static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tint = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tint = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, float tilingFactor = 1.0f, const glm::vec4& tint = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, float tilingFactor = 1.0f, const glm::vec4& tint = glm::vec4(1.0f));

		static void DrawQuadRotated(const glm::vec2& pos, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void DrawQuadRotated(const glm::vec3& pos, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void DrawQuadRotated(const glm::vec2& pos, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tint = glm::vec4(1.0f));
		static void DrawQuadRotated(const glm::vec3& pos, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tint = glm::vec4(1.0f));
		static void DrawQuadRotated(const glm::vec2& pos, const glm::vec2& size, float rotation, const Ref<SubTexture2D>& subTexture, float tilingFactor = 1.0f, const glm::vec4& tint = glm::vec4(1.0f));
		static void DrawQuadRotated(const glm::vec3& pos, const glm::vec2& size, float rotation, const Ref<SubTexture2D>& subTexture, float tilingFactor = 1.0f, const glm::vec4& tint = glm::vec4(1.0f));
		
		// Stats
		struct Statistics
		{
			uint32_t drawCalls = 0;
			uint32_t quadCount = 0;

			uint32_t GetTotalVertexCount() { return quadCount * 4; }
			uint32_t GetTotalIndexCount() { return quadCount * 6; }
		};
		static void ResetStats();
		static Statistics GetStats();
	};

}