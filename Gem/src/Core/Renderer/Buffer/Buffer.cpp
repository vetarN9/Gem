#include "gempch.h"
#include "Buffer.h"

#include "Core/Renderer/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Gem
{

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::none:
				GEM_CORE_ASSERT(false, "A RendererAPI must be selected!"); 
				return nullptr;

			case RendererAPI::API::OpenGL:
				return std::make_shared <OpenGLVertexBuffer>(vertices, size);

			default:
				GEM_CORE_ASSERT(false, "Unknown RendererAPI!");
				return nullptr;
		}
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::none:
				GEM_CORE_ASSERT(false, "A RendererAPI must be selected!");
				return nullptr;

			case RendererAPI::API::OpenGL:
				return new OpenGLIndexBuffer(indices, size);

			default:
				GEM_CORE_ASSERT(false, "Unknown RendererAPI!");
				return nullptr;
		}
	}

}