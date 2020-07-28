#pragma once

#include <memory>

#ifdef GT_PLATFORM_WINDOWS
#if GT_DYNAMIC_PLATFORM
#ifdef GT_BUILD_DLL
#define GHOST_API __declspec(dllexport)
#else
#define GHOST_API __declspec(dllimport)
#endif // GT_BUILD_DLL
#else
#define GHOST_API
#endif
#else
#error Ghost only supports Windows!
#endif // GT_PLATFORM_WINDOWS

#ifdef GT_DEBUG
#define GT_ENABLE_ASSERTS
#endif // GT_DEBUG

#ifdef GT_ENABLE_ASSERTS
#define GT_ASSERT(x, ...) { if(!(x)) { GT_ERROR("Assetion Failed: {0}",__VA_ARGS__); __debugbreak(); } }
#define GT_CORE_ASSERT(x, ...) { if(!(x)) { GT_CORE_ERROR("Assertion Failed: {0}",__VA_ARGS__); __debugbreak(); } }
#else
#define GT_ASSERT(x, ...)
#define GT_CORE_ASSERT(x, ...)
#endif // GT_ENABLE_ASSERTS

#define BIT(x) (1 << x)

#define GT_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Ghost {
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}