#include "gempch.h"

#include "Core/Renderer/Texture/SubTexture2D.h"

namespace Gem
{
	SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max)
		: m_Texture(texture)
	{
		m_TexCoords[0] = { min.x, min.y };
		m_TexCoords[1] = { max.x, min.y };
		m_TexCoords[2] = { max.x, max.y };
		m_TexCoords[3] = { min.x, max.y };
	}

	Ref<SubTexture2D> SubTexture2D::CreateFromPosition(const Ref<Texture2D>& texture, const glm::vec2& pixelPos, const glm::vec2& spriteSize)
	{
		glm::vec2 min = { pixelPos.x / texture->GetWidth(), pixelPos.y / texture->GetHeight() };
		glm::vec2 max = { (pixelPos.x + spriteSize.x) / texture->GetWidth(), (pixelPos.y + spriteSize.y) / texture->GetHeight() };
		return CreateRef<SubTexture2D>(texture, min, max);

	}
}