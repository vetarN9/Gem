#include "gempch.h"
#include "Core/Renderer/Renderer/RenderContext.h"

#include "Core/Renderer/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Gem
{

	Scope<RenderContext> RenderContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::none:    GEM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		GEM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}