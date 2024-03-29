#pragma once

#include "Core/Renderer/Shader/Shader.h"
#include <glm/glm.hpp>

typedef unsigned int GLenum;

namespace Gem
{

	class OpenGLShader : public Shader
	{
		std::string m_Name;
		uint32_t m_RendererID;

		std::string ReadFile(const std::string& path);
		std::unordered_map<GLenum, std::string> Parse(const std::string& src);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSrcs);

	public:
		OpenGLShader(const std::string& path);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override;

		virtual void SetFloat(const std::string& name, float value) override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& vector3) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& vector4) override;

		virtual void SetMat4(const std::string& name, const glm::mat4& matrix4) override;

		virtual const std::string& GetName() const override { return m_Name; }

		void UploadUniformInt(const std::string& name, int scalar);
		void UploadUniformIntArray(const std::string& name, int* values, uint32_t count);

		void UploadUniformFloat(const std::string& name, float scalar);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& vector2);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& vector3);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& vector4);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix3);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix4);
	};

}