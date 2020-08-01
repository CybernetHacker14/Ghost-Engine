#pragma once

#include <memory>

#ifdef _WIN32
#ifdef _WIN64
#define GT_PLATFORM_WINDOWS
#else
#error "x86 builds are not supported!"
#endif // _WIN64
#elif defined(__APPLE__) || defined (__MACH__)
#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR == 1
#error "iOS simulator is not supported!"
#elif TARGET_OS_IPHONE == 1
#define GT_PLATFORM_IOS
#error "iOS is not supported!"
#elif TARGET_OS_MAC == 1
#define GT_PLATFORM_MACOS
#error "MacOS is not supported!"
#else
#error "Unknown Apple platform!"
#endif
#elif defined(__ANDROID__)
#define GT_PLATFORM_LINUX
#error "Linux is not supported!"
#else
#error "Unknown platform!"
#endif // _WIN32

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

	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}