#pragma once

#include "Core/Renderer/RenderingContext.h"

struct GLFWwindow;

namespace Gem
{

	class OpenGLContext : public RenderingContext
	{
		GLFWwindow* m_WindowHandle;

	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	};

}