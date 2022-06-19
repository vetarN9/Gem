#pragma once

#include "Core/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Gem
{

	class Log
	{
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	};

}

// Macros for core logs
#define GEM_CORE_TRACE(...)   ::Gem::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define GEM_CORE_INFO(...)    ::Gem::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GEM_CORE_WARN(...)    ::Gem::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GEM_CORE_ERROR(...)   ::Gem::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GEM_CORE_FATAL(...)   ::Gem::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Macros for client logs
#define GEM_TRACE(...)        ::Gem::Log::GetClientLogger()->trace(__VA_ARGS__)
#define GEM_INFO(...)         ::Gem::Log::GetClientLogger()->info(__VA_ARGS__)
#define GEM_WARN(...)         ::Gem::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GEM_ERROR(...)        ::Gem::Log::GetClientLogger()->error(__VA_ARGS__)
#define GEM_FATAL(...)        ::Gem::Log::GetClientLogger()->critical(__VA_ARGS__)