#pragma once

#include "Core/Window/Window.h"

#include "Core/Events/ApplicationEvent.h"
#include "Core/Events/KeyEvent.h"
#include "Core/Events/MouseEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"
#include "Core/Renderer/Renderer/RenderContext.h"

#include <GLFW/glfw3.h>

namespace Gem
{

	class WindowsWindow : public Window
	{
		GLFWwindow* m_Window;
		Scope<RenderContext> m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
			EventCallbackFunc EventCallback;
		};

		WindowData m_Data;

		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline void SetEventCallback(const EventCallbackFunc& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return m_Window; }
	};

}