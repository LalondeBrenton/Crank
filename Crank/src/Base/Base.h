#pragma once

#include <memory>

#ifdef BUILD_DLL
	#define CGE_API __declspec(dllexport)
#elif BUILD_LIB
	#define CGE_API __declspec(dllimport)
#else
	#define CGE_API
#endif

#ifdef CGE_DEBUG
	#define CGE_ENABLE_ASSERTS
	#if defined(CGE_PLATFORM_WINDOWS)
		#define CGE_DEBUGBREAK() __debugbreak()
	#elif defined(CGE_PLATFORM_LINUX)
		#include <signal.h>
		#define CGE_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
#else
	#define CGE_DEBUGBREAK()
#endif

#define CGE_EXPAND_MACRO(x) x
#define CGE_STRINGIFY_MACRO(x) #x

#define CGE_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#define BIT(x) (1 << x)

namespace Crank
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

#include "Log.h"
#include "Assert.h"