#include "gempch.h"

#include "Core/Renderer/Shader/Shader.h"

#include "Core/Renderer/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Gem
{

	Ref<Shader> Shader::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::none:
				GEM_CORE_ASSERT(false, "A RendererAPI must be selected!");
				return nullptr;

			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGLShader>(path);

			default:
				GEM_CORE_ASSERT(false, "Unknown RendererAPI!");
				return nullptr;
		}
	}

	Ref<Shader> Shader::Create(const std::string&  name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::none:
				GEM_CORE_ASSERT(false, "A RendererAPI must be selected!");
				return nullptr;

			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);

			default:
				GEM_CORE_ASSERT(false, "Unknown RendererAPI!");
				return nullptr;
		}
	}

	//------------------ SHADER LIBRARY ------------------

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		GEM_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end(), "Given shader already exist!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}


	Ref<Shader> ShaderLibrary::Load(const std::string& path)
	{
		auto shader = Shader::Create(path);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& path)
	{
		auto shader = Shader::Create(path);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		GEM_CORE_ASSERT(m_Shaders.find(name) != m_Shaders.end(), "Given shader not found!");
		return m_Shaders[name];
	}

}