#include "gtpch.h"
#include "Ghost/ImGui/ImGuiConsole.h"

#include "imgui.h"

namespace Ghost {
	uint32_t ImGuiConsole::s_LogMessageCount = 0;
	std::vector<Message> ImGuiConsole::s_MessageBuffer(0);

	void ImGuiConsole::Draw()
	{
		if (ImGui::Button("Clear", { 50.0f, 20.0f })) {
			Clear();
		}

		for (uint32_t i = 0; i < ImGuiConsole::s_LogMessageCount; i++) {
			if (s_MessageBuffer.at(i).m_MessageLevel == Message::Level::Info) {
				ImGui::TextColored({ 1.0f, 1.0f, 1.0f, 1.0f }, s_MessageBuffer.at(i).m_MessageData.c_str());
				ImGui::Separator();
				continue;
			}
			if (s_MessageBuffer.at(i).m_MessageLevel == Message::Level::Warn) {
				ImGui::TextColored({ 1.0f, 1.0f, 0.0f, 1.0f }, s_MessageBuffer.at(i).m_MessageData.c_str());
				ImGui::Separator();
				continue;
			}
			if (s_MessageBuffer.at(i).m_MessageLevel == Message::Level::Error) {
				ImGui::TextColored({ 1.0f, 0.0f, 0.0f, 1.0f }, s_MessageBuffer.at(i).m_MessageData.c_str());
				ImGui::Separator();
				continue;
			}
		}
	}

	void ImGuiConsole::Clear()
	{
		s_LogMessageCount = 0;
		s_MessageBuffer.clear();
	}
}