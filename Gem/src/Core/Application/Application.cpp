#include "gempch.h"
#include "Application.h"

#include "Core/Log/Log.h"
#include "Core/Input/Input.h"

#include "Core/Renderer/Renderer/Renderer.h"

#include <GLFW/glfw3.h>

namespace Gem
{

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		GEM_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(GEM_BIND_EVENT_FUNC(Application::OnEvent));
		m_Window->SetVSync(false);

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	void Application::Run()
	{
		while (m_Running)
		{
			float currentTime = (float)glfwGetTime();
			Timestep timestep = currentTime - m_LastFrameTime;
			m_LastFrameTime = currentTime;

			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(timestep);
			}

			m_ImGuiLayer->Begin();
			{
				for (Layer* layer : m_LayerStack)
					layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowClosedEvent>(GEM_BIND_EVENT_FUNC(Application::OnWindowClosed));
		dispatcher.Dispatch<WindowResizedEvent>(GEM_BIND_EVENT_FUNC(Application::OnWindowResized));

		// Loop through the LayerStack backwards until 
		// a layer handles the event.
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(event);
			if (event.m_Handled)
				break;
		}
	}

	bool Application::OnWindowClosed(WindowClosedEvent& event)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResized(WindowResizedEvent& event)
	{
		if (event.GetWidth() == 0 || event.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;

		Renderer::OnWindowResized(event.GetWidth(), event.GetHeight());

		return false;
	}

}