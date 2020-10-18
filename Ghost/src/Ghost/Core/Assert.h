#pragma once

#include "Ghost/Core/Base.h"
#include "Ghost/Core/Log.h"
#include <filesystem>

#ifdef GT_ENABLE_ASSERTS

// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define GT_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { GT##type##ERROR(msg, __VA_ARGS__); GT_DEBUGBREAK(); } }
#define GT_INTERNAL_ASSERT_WITH_MSG(type, check, ...) GT_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define GT_INTERNAL_ASSERT_NO_MSG(type, check) GT_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", GT_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define GT_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define GT_INTERNAL_ASSERT_GET_MACRO(...) GT_EXPAND_MACRO( GT_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, GT_INTERNAL_ASSERT_WITH_MSG, GT_INTERNAL_ASSERT_NO_MSG) )

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define GT_ASSERT(...) GT_EXPAND_MACRO( GT_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define GT_CORE_ASSERT(...) GT_EXPAND_MACRO( GT_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
#define GT_ASSERT(...)
#define GT_CORE_ASSERT(...)
#endif
