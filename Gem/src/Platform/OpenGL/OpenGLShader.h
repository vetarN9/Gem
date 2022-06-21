#pragma once

#include "Core/Renderer/Shader/Shader.h"

#include <glm/glm.hpp>

namespace Gem
{

	class OpenGLShader : public Shader
	{
		uint32_t m_RendererID;

	public:
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