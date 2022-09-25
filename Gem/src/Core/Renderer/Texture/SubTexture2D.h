#pragma once

#include "Core/Renderer/Texture/Texture.h"

#include <glm/glm.hpp>


namespace Gem 
{

	class SubTexture2D
	{
		Ref<Texture2D> m_Texture;
		glm::vec2 m_TexCoords[4];

	public:
		SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max);

		static Ref<SubTexture2D> CreateFromPosition(const Ref<Texture2D>& texture, const glm::vec2& pixelPos, const glm::vec2& spriteSize);

		const Ref<Texture2D> GetTexture() const { return m_Texture; }
		const glm::vec2* GetTexCoords() const { return m_TexCoords; }
	};

}