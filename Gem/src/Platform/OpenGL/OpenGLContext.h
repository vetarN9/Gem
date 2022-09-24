#pragma once

#include "Core/Renderer/Renderer/RenderContext.h"

struct GLFWwindow;

namespace Gem
{

	class OpenGLContext : public RenderContext
	{
		GLFWwindow* m_WindowHandle;

	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	};

}