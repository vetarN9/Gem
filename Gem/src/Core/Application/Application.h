#pragma once

#include "Core/Core.h"

#include "Core/Window/Window.h"
#include "Core/Layer/LayerStack.h"
#include "Core/Events/ApplicationEvent.h"

#include "Core/Timer/Timestep.h"

#include "Core/Debug/ImGui/ImGuiLayer.h"

namespace Gem
{

	class Application
	{
		static Application* s_Instance;

		bool OnWindowClosed(WindowClosedEvent& event);
		bool OnWindowResized(WindowResizedEvent& event);
		bool m_Running = true;
		bool m_Minimized = false;

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;

		float m_LastFrameTime = 0.0f;

	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	};

	Application* CreateApplication();

}


