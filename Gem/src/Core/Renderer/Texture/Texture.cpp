#include "gempch.h"

#include "Core/Renderer/Texture/Texture.h"

#include "Core/Renderer/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Gem
{
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::none:
				GEM_CORE_ASSERT(false, "A RendererAPI must be selected!");
				return nullptr;

			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGLTexture2D>(path);

			default:
				GEM_CORE_ASSERT(false, "Unknown RendererAPI!");
				return nullptr;
		}
	}

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::none:
			GEM_CORE_ASSERT(false, "A RendererAPI must be selected!");
			return nullptr;

		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLTexture2D>(width, height);

		default:
			GEM_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}

}