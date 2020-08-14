#pragma once

#include "Ghost/Core/PlatformDetection.h"

#ifdef GT_PLATFORM_WINDOWS
#ifndef NOMINMAX
#define NOMINMAX
#endif // !NOMINMAX

#endif // GT_PLATFORM_WINDOWS

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Ghost/Core/Log.h"

#include "Ghost/Debug/Instrumentor.h"

#ifdef GT_PLATFORM_WINDOWS
#include <Windows.h>
#endif // GT_PLATFORM_WINDOWS
