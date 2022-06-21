#include "gempch.h"
#include "Shader.h"

#include "Core/Renderer/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Gem
{

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::none:
				GEM_CORE_ASSERT(false, "A RendererAPI must be selected!");
				return nullptr;

			case RendererAPI::API::OpenGL:
				return new OpenGLShader(vertexSrc, fragmentSrc);

			default:
				GEM_CORE_ASSERT(false, "Unknown RendererAPI!");
				return nullptr;
		}
	}

}