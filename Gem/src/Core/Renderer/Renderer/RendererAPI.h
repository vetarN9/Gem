#pragma once

#include <glm/glm.hpp>

#include "Core/Renderer/Buffer/VertexArray.h"

namespace Gem
{

	class RendererAPI
	{

	public:
		enum class API
		{
			none = 0,
			OpenGL = 1
		};

	private:
		static API s_API;

	public:
		virtual void Init() = 0;

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

		inline static API GetAPI() { return s_API; }
	};

}