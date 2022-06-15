#pragma once

#pragma once

#include "Core/Core.h"
#include "Core/Events/Event.h"
#include "Core/Events/ApplicationEvent.h"
#include "Core/Log/Log.h"
#include "Core/Window/Window.h"
#include "Core/Layer/LayerStack.h"

#define BIND_EVENT_FUNC(x) std::bind(&x, this, std::placeholders::_1)

namespace Gem
{

	class GEM_API Application
	{
		static Application* s_Instance;

		bool OnWindowClosed(WindowClosedEvent& e);
		bool m_Running = true;
		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;


	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWIndow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	};

	Application* CreateApplication();

}


