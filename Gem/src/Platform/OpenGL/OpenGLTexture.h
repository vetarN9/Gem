#pragma once

#include "Core/Renderer/Texture/Texture.h"

namespace Gem
{

	class OpenGLTexture2D : public Texture2D
	{
		std::string m_Path;
		uint32_t m_Width, m_Height, m_RendererID;

	public:
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }

		virtual void Bind(uint32_t slot = 0) const override;
	};

}