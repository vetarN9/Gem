#pragma once

namespace Gem
{

	class Shader
	{
		uint32_t m_RendererID;

	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void UnBind() const;
	};

}