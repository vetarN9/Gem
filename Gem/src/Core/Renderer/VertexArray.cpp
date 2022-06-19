#include "gempch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Gem
{

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::CurrentAPI())
		{
			case RendererAPI::none:
				GEM_CORE_ASSERT(false, "A RendererAPI must be selected!");
				return nullptr;

			case RendererAPI::OpenGL:
				return new OpenGLVertexArray();

			default:
				GEM_CORE_ASSERT(false, "Unknown RendererAPI!");
				return nullptr;
		}
	}

}