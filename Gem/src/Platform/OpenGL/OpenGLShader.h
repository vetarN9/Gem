#pragma once

#include "Core/Renderer/Shader/Shader.h"
#include <glm/glm.hpp>

typedef unsigned int GLenum;

namespace Gem
{

	class OpenGLShader : public Shader
	{
		uint32_t m_RendererID;

		std::string ReadFile(const std::string& path);
		std::unordered_map<GLenum, std::string> Parse(const std::string& src);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSrcs);

	public:
		OpenGLShader(const std::string& path);
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		void UploadUniformInt(const std::string& name, int scalar);

		void UploadUniformFloat(const std::string& name, float scalar);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& vector2);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& vector3);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& vector4);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix3);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix4);
	};

}