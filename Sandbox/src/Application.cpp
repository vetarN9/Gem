#include <Gem.h>

class ExampleLayer : public Gem::Layer
{
public:
	ExampleLayer()
		: Layer("Example"){ }

	void OnUpdate() override
	{
		//GEM_INFO("ExampleLayer::Update");
		if (Gem::Input::IsKeyPressed(GEM_KEY_H))
		{
			GEM_INFO("H Was pressed!");
		}
	}

	void OnEvent(Gem::Event& event) override
	{
		//GEM_TRACE("{0}", event);
	}
};

class Sandbox : public Gem::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Gem::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Gem::Application* Gem::CreateApplication()
{
	return new Sandbox();
}