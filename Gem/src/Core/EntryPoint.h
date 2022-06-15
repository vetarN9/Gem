#pragma once

#ifdef GEM_PLATFORM_WINDOWS

extern Gem::Application* Gem::CreateApplication();

int main(int argc, char* argv[])
{
	Gem::Log::Init();
	GEM_CORE_WARN("Initialized Log");
	int a = 2;
	GEM_INFO("Hello int = {0}", a);

	auto app = Gem::CreateApplication();
	app->Run();
	delete app;
}
#endif // GEM_PLATFORM_WINDOWS