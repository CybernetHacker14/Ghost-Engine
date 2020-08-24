#pragma once

#include "Ghost/Core/Base.h"

namespace Ghost {
	class Message {
	public:
		enum class Level : int8_t {
			Info = 0,
			Warn = 1,
			Error = 2
		};
	public:
		Message() = default;
		Message(const std::string& message, Level level = Level::Info)
			:m_MessageData(message), m_MessageLevel(level)
		{}

	public:
		std::string m_MessageData;
		Level m_MessageLevel;
	};

	class ImGuiConsole
	{
	public:
		ImGuiConsole() = default;

		static void Draw();

		template <typename... Args>
		static void Log(const std::string& data, Args&&... args);

		template <typename... Args>
		static void LogWarning(const std::string& data, Args&&... args);

		template <typename... Args>
		static void LogError(const std::string& data, Args&&... args);

	private:
		static void Clear();

		template <typename... Args>
		static std::string Format(const std::string& fmt, Args&&... args);

	private:
		static std::vector<Message> s_MessageBuffer;
		static uint32_t s_LogMessageCount;
	};

	template<typename ...Args>
	inline std::string ImGuiConsole::Format(const std::string& fmt, Args && ...args)
	{
		size_t size = snprintf(nullptr, 0, fmt.c_str(), args...);
		std::string buffer;
		buffer.reserve(size + 1);
		buffer.resize(size);
		snprintf(&buffer[0], size + 1, fmt.c_str(), args...);
		return buffer;
	}

	// Logging Implementations
	template<typename ...Args>
	inline void ImGuiConsole::Log(const std::string& data, Args && ...args)
	{
		s_MessageBuffer.push_back({ ImGuiConsole::Format(data, args...) });
		s_LogMessageCount++;
	}

	template<typename ...Args>
	inline void ImGuiConsole::LogWarning(const std::string& data, Args && ...args)
	{
		s_MessageBuffer.push_back({ ImGuiConsole::Format(data, args...), Message::Level::Warn });
		s_LogMessageCount++;
	}

	template<typename ...Args>
	inline void ImGuiConsole::LogError(const std::string& data, Args && ...args)
	{
		s_MessageBuffer.push_back({ ImGuiConsole::Format(data, args...), Message::Level::Error });
		s_LogMessageCount++;
	}
}