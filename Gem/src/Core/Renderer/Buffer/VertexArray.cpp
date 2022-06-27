#include "gempch.h"
#include "VertexArray.h"

#include "Core/Renderer/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Gem
{

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::none:
				GEM_CORE_ASSERT(false, "A RendererAPI must be selected!");
				return nullptr;

			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLVertexArray>();

			default:
				GEM_CORE_ASSERT(false, "Unknown RendererAPI!");
				return nullptr;
		}
	}

}