#pragma once

#include "Core/Renderer/Buffer/Buffer.h"

namespace Gem
{

	class OpenGLVertexBuffer : public VertexBuffer
	{
		uint32_t m_RendererID;
		BufferLayout m_BufferLayout;

	public:
		OpenGLVertexBuffer(uint32_t size);
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const BufferLayout& GetBufferLayout() const override { return m_BufferLayout; }
		virtual void SetBufferLayout(const BufferLayout& bufferLayout) override { m_BufferLayout = bufferLayout; }

		virtual void SetData(const void* data, uint32_t size) override;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
		uint32_t m_RendererID;
		uint32_t m_Count;
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t size);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual uint32_t GetCount() const { return m_Count; }
	};

}