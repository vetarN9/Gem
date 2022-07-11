#pragma once

#include "Core/Renderer/Texture/Texture.h"

#include <glad/glad.h>

namespace Gem
{

	class OpenGLTexture2D : public Texture2D
	{
		std::string m_Path;
		uint32_t m_Width, m_Height, m_RendererID;
		GLenum m_InternalFormat, m_DataFormat;

	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }

		virtual void SetData(void* data, uint32_t size) override;

		virtual void Bind(uint32_t slot = 0) const override;
	};

}