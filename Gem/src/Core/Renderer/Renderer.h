#pragma once

namespace Gem
{

	enum class RendererAPI
	{
		none = 0,
		OpenGL = 1
	};

	class Renderer
	{
		static RendererAPI s_RendererAPI;

	public:
		inline static RendererAPI CurrentAPI() { return s_RendererAPI; }
	};

}