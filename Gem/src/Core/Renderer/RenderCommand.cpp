#include "gempch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Gem
{

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}