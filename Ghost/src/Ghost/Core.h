#pragma once

#ifdef GT_PLATFORM_WINDOWS
#ifdef GT_BUILD_DLL
#define GHOST_API __declspec(dllexport)
#else
#define GHOST_API __declspec(dllimport)
#endif // GT_BUILD_DLL
#else
#error Ghost only supports Windows!
#endif // GT_PLATFORM_WINDOWS

#define BIT(x) (1 << x)