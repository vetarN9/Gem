#pragma once

#ifdef GEM_PLATFORM_WINDOWS
#else
	#error GEM ONLY SUPPORTS WINDOWS AT THE MOMENT!
#endif GEM_PLATFORM_WINDOWS

#ifdef GEM_DEBUG
	#ifdef GEM_ENABLE_ASSERTS
		#define GEML_ASSERT(x, ...) { if(!(x)) {GEM_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
		#define GEM_CORE_ASSERT(x, ...) { if(!(x)) {GEM_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#else
		#define GEM_ASSERT(x, ...)
		#define GEM_CORE_ASSERT(x, ...)
	#endif // GEM_ENABLE_ASSERTS

	#ifdef GEM_ENABLE_VERIFY
		#define GEM_VERIFY(x, ...) { if(!(x)) {GEM_ERROR("Verification Failed: {0}", __VA_ARGS__); __debugbreak(); } }
		#define GEM_CORE_VERIFY(x, ...) { if(!(x)) {GEM_CORE_ERROR("Verification Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#else
		#define GEM_VERIFY(x, ...) x
		#define GEM_CORE_VERIFY(x, ...) x
	#endif // GEM_ENABLE_VERIFY
#endif // GEM_DEBUG


#define BIT_SHIFT(x) (1 << x)

#define GEM_BIND_EVENT_FUNC(func) std::bind(&func, this, std::placeholders::_1)