#pragma once

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