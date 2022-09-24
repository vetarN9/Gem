#include "gempch.h"

#include "Core/Renderer/Renderer/RenderCommand.h"

namespace Gem
{

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}