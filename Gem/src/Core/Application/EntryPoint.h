#pragma once

#include "Core/Core.h"

#ifdef GEM_PLATFORM_WINDOWS

extern Gem::Application* Gem::CreateApplication();

int main(int argc, char* argv[])
{
	Gem::Log::Init();
	GEM_CORE_INFO("Initialized Log");

	auto app = Gem::CreateApplication();
	app->Run();
	delete app;
}
#endif // GEM_PLATFORM_WINDOWS