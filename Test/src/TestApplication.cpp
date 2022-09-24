#include <Gem.h>
#include <Core/Application/EntryPoint.h>

#include "Test2D.h"

class Test : public Gem::Application
{
public:
	Test()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Test2D());
	}

	~Test()
	{

	}
};

Gem::Application* Gem::CreateApplication()
{
	return new Test();
}