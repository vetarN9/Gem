#pragma once

#include "Core/Renderer/Camera/OrthographicCamera.h"
#include "Core/Renderer/Texture/Texture.h"

namespace Gem
{

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color);

		static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<Texture2D>& texture);
		static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture2D>& texture);

		static void DrawQuadRotated(const glm::vec2& pos, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void DrawQuadRotated(const glm::vec3& pos, const glm::vec2& size, float rotation, const glm::vec4& color);
	};

}