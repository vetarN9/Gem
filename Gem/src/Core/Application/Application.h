#pragma once

#include "Core/Core.h"

#include "Core/Window/Window.h"
#include "Core/Layer/LayerStack.h"
#include "Core/Events/Event.h"
#include "Core/Events/ApplicationEvent.h"

#include "Core/Debug/ImGui/ImGuiLayer.h"

#include "Core/Renderer/Buffer/Buffer.h"
#include "Core/Renderer/Buffer/BufferLayout.h"
#include "Core/Renderer/Buffer/VertexArray.h"
#include "Core/Renderer/Shader/Shader.h"
#include "Core/Renderer/Camera/OrthographicCamera.h"

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

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr <VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_Shader2;
		std::shared_ptr <VertexArray> m_SquareVertexArray;

		OrthographicCamera m_OrthoCamera;

	public:
		Application();
		virtual ~Application() = default;

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	};

	Application* CreateApplication();

}


