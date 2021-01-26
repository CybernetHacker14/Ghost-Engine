#pragma once

#include "Ghost/Core/Base.h"

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace Ghost {
	class Log
	{
	public:
		static void Init();

		static Ref<spdlog::logger>& GetCoreLogger() { return  s_CoreLogger; }
		static Ref<spdlog::logger>& GetClientLogger() { return  s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define GT_CORE_TRACE(...)     ::Ghost::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define GT_CORE_INFO(...)      ::Ghost::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GT_CORE_WARN(...)      ::Ghost::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GT_CORE_ERROR(...)     ::Ghost::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GT_CORE_CRITICAL(...)     ::Ghost::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define GT_TRACE(...)   ::Ghost::Log::GetClientLogger()->trace(__VA_ARGS__)
#define GT_INFO(...)    ::Ghost::Log::GetClientLogger()->info(__VA_ARGS__)
#define GT_WARN(...)    ::Ghost::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GT_ERROR(...)   ::Ghost::Log::GetClientLogger()->error(__VA_ARGS__)
#define GT_CRITICAL(...)   ::Ghost::Log::GetClientLogger()->critical(__VA_ARGS__)
