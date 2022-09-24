#pragma once

#include <memory>

#ifdef GEM_PLATFORM_WINDOWS
#else
	#error GEM ONLY SUPPORTS WINDOWS AT THE MOMENT!
#endif GEM_PLATFORM_WINDOWS

#ifdef GEM_DEBUG
	#define GEML_ASSERT(x, ...) { if(!(x)) {GEM_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define GEM_CORE_ASSERT(x, ...) { if(!(x)) {GEM_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	
	#define GEM_VERIFY(x, ...) { if(!(x)) {GEM_ERROR("Verification Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define GEM_CORE_VERIFY(x, ...) { if(!(x)) {GEM_CORE_ERROR("Verification Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define GEM_ASSERT(x, ...)
	#define GEM_CORE_ASSERT(x, ...)
	
	#define GEM_VERIFY(x, ...) x
	#define GEM_CORE_VERIFY(x, ...) x
#endif // GEM_DEBUG

#define GEM_BIND_EVENT_FUNC(func) std::bind(&func, this, std::placeholders::_1)

namespace Gem
{

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}