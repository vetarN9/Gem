#pragma once

namespace Gem
{

	class RenderContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

		static Scope<RenderContext> Create(void* window);
	};

}