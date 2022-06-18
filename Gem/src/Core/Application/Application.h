#pragma once

#pragma once

#include "Core/Events/ApplicationEvent.h"
#include "Core/Core.h"
#include "Core/Events/Event.h"
#include "Core/Layer/LayerStack.h"
#include "Core/Log/Log.h"
#include "Core/Window/Window.h"
#include "Core/Debug/ImGui/ImGuiLayer.h"

namespace Gem
{

	class Application
	{
		static Application* s_Instance;

		bool OnWindowClosed(WindowClosedEvent& e);
		bool m_Running = true;
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;


	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	};

	Application* CreateApplication();

}


