#include "Test2D.h"

#include "imgui/imgui.h"
#include <glm/gtc/type_ptr.hpp>

template<typename Func>
class Timer
{
	const char* m_Name;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTime;
	bool m_Stopped;
	Func m_Func;

public:
	Timer(const char* name, Func&& func)
		:m_Name(name), m_Func(func), m_Stopped(false)
	{
		m_StartTime = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		if (!m_Stopped)
			Stop();
	}

	void Stop()
	{
		auto endTime = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTime).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTime).time_since_epoch().count();

		m_Stopped = true;

		float duration = (end - start) * 0.001f;
		m_Func({ m_Name, duration });
	}
};

#define PROFILE_SCOPE(name) Timer timer##__Line__(name, [&](ProfileResult profileResult) { m_ProfileResult.push_back(profileResult); })

Test2D::Test2D()
	: Layer("Test2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Test2D::OnAttach()
{
	m_Texture = Gem::Texture2D::Create("Assets/Textures/Checkerboard.png");
}

void Test2D::OnDetach()
{
}

void Test2D::OnUpdate(Gem::Timestep timestep)
{
	PROFILE_SCOPE("Test2D::OnUpdate");

	{
		PROFILE_SCOPE("m_CameraController.OnUpdate");
		m_CameraController.OnUpdate(timestep);
	}

	Gem::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Gem::RenderCommand::Clear();

	Gem::Renderer2D::BeginScene(m_CameraController.GetCamera());
	{
		PROFILE_SCOPE("Draw quads");
		Gem::Renderer2D::DrawQuad({ -1.0f, 1.0f, 1.0f }, { 0.5f, 1.0f }, { 0.8f, 0.2f, 0.7f, 1.0f });
		Gem::Renderer2D::DrawQuad({ 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f }, { 0.3f, 0.7f, 0.6f, 1.0f });
		//Gem::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.5f }, { 100.0f, 100.0f }, m_Texture, 50, glm::vec4(1.0f, 1.0f, 1.0f, 0.2f));
		//Gem::Renderer2D::DrawQuadRotated({ -1.0f, -1.0f }, { 0.5f, 0.5f }, 22, m_Texture);
	}
	Gem::Renderer2D::EndScene();
}

void Test2D::OnImGuiRender()
{
	ImGui::Begin("Sliders");
	{
		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

		for (auto& result : m_ProfileResult)
		{
			char label[50];
			strcpy_s(label, "%.3fms ");
			strcat_s(label, result.name);
			ImGui::Text(label, result.time);
		}
		m_ProfileResult.clear();
	}
	ImGui::End();
}

void Test2D::OnEvent(Gem::Event& event)
{
	m_CameraController.OnEvent(event);
}
