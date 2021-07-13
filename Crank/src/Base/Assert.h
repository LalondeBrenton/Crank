#pragma once

#include <filesystem>

#ifdef CGE_ENABLE_ASSERTS

	// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
	// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
	#define CGE_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { CGE##type##ERROR(msg, __VA_ARGS__); CGE_DEBUGBREAK(); } }
	#define CGE_INTERNAL_ASSERT_WITH_MSG(type, check, ...) CGE_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define CGE_INTERNAL_ASSERT_NO_MSG(type, check) CGE_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", CGE_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

	#define CGE_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define CGE_INTERNAL_ASSERT_GET_MACRO(...) CGE_EXPAND_MACRO( CGE_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, CGE_INTERNAL_ASSERT_WITH_MSG, CGE_INTERNAL_ASSERT_NO_MSG) )

	// Currently accepts at least the condition and one additional parameter (the message) being optional
	#define CGE_ASSERT(...) CGE_EXPAND_MACRO( CGE_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
	#define CGE_CORE_ASSERT(...) CGE_EXPAND_MACRO( CGE_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
	#define CGE_ASSERT(...)
	#define CGE_CORE_ASSERT(...)
#endif