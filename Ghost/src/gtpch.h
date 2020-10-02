#pragma once

#include "Ghost/Core/PlatformDetection.h"

#ifdef GT_PLATFORM_WINDOWS
#ifndef NOMINMAX
// See github.com/skypjack/entt/wiki/Frequently-Asked-Questions#warning-c4003-the-min-the-max-and-the-macro
#define NOMINMAX
#endif // !NOMINMAX

#endif // GT_PLATFORM_WINDOWS

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <filesystem>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Ghost/Core/Base.h"

#include "Ghost/Core/Log.h"
#include "Ghost/ImGui/Utilities/ImGuiConsole.h"

#include "Ghost/Debug/Instrumentor.h"

#ifdef GT_PLATFORM_WINDOWS
#include <Windows.h>
#endif // GT_PLATFORM_WINDOWS
