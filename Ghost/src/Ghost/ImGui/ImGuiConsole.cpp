#include "gtpch.h"
#include "Ghost/ImGui/ImGuiConsole.h"

#include "imgui.h"

namespace Ghost {
	void ImGuiConsole::Init()
	{
		GT_CORE_WARN("ImGui Console Init");
	}

	void ImGuiConsole::Draw()
	{
		ImVec4 color = { 1.0f, 0.0f, 0.0f, 1.0f };
		ImGui::TextColored(color, "Drawing");
	}

	void ImGuiConsole::Log(const char* data, ...)
	{
	}
}