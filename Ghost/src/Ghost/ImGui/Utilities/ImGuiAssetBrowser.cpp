#include "gtpch.h"
#include "Ghost/ImGui/Utilities/ImGuiAssetBrowser.h"
#include "Ghost/Fonts/IconsFontAwesome5Pro.h"

#include "imgui.h"

namespace Ghost {
	std::filesystem::path ImGuiAssetBrowser::m_AssetDirectoryPath("assets");
	std::filesystem::path ImGuiAssetBrowser::m_CurrentRightPanelDirectoryPath(ImGuiAssetBrowser::m_AssetDirectoryPath);

	void ImGuiAssetBrowser::Init()
	{
	}

	void ImGuiAssetBrowser::Draw()
	{
		ImGui::Columns(2, "Project", true);

		// Outer tree based project panel (Unity's left panel)
		DrawLeftProjectPanel();

		ImGui::NextColumn();

		// Folder content viewer (Unity's right panel)
		DrawRightProjectPanel();
	}

	bool ImGuiAssetBrowser::IsDirectory(const std::filesystem::path& path)
	{
		return std::filesystem::is_directory(path);
	}

	bool ImGuiAssetBrowser::IsDirectoryEmpty(const std::filesystem::path& path)
	{
		return IsDirectory(path) && std::filesystem::is_empty(path);
	}

	bool ImGuiAssetBrowser::HasSubDirectory(const std::filesystem::path& path)
	{
		bool value = false;
		for (const auto& entry : std::filesystem::directory_iterator(path)) {
			if (IsDirectory(entry.path())) {
				value = true;
				break;
			}
		}

		return value;
	}

	void ImGuiAssetBrowser::DrawLeftProjectPanel()
	{
		bool opened = ImGui::TreeNodeEx("leftProjectPanelAssets", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow, ICON_FA_FOLDER" assets");

		if (ImGui::IsItemClicked()) {
			m_CurrentRightPanelDirectoryPath = m_AssetDirectoryPath;
		}

		if (opened) {
			DrawRecursive(m_AssetDirectoryPath);
			ImGui::TreePop();
		}
	}

	void ImGuiAssetBrowser::DrawRightProjectPanel()
	{
		DrawRightFilePathHeader(m_CurrentRightPanelDirectoryPath);

		const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
		ImGui::BeginChild("RightProjectPanelVisor", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar);

		ImGui::Separator();

		std::string name, treeName;
		for (const auto& entry : std::filesystem::directory_iterator(m_CurrentRightPanelDirectoryPath)) {
			name = entry.path().filename().string();
			if (IsDirectory(entry.path())) {
				if (!IsDirectoryEmpty(entry.path())) {
					treeName = ICON_FA_FOLDER + std::string(" ") + name;
				}
				else {
					treeName = ICON_FA_FOLDER_MINUS + std::string(" ") + name;
				}

				if (ImGui::TreeNodeEx(name.c_str(), ImGuiTreeNodeFlags_Leaf, treeName.c_str())) {
					if (ImGui::IsItemClicked()) {
						m_CurrentRightPanelDirectoryPath = entry.path();
					}
					ImGui::TreePop();
				}
			}
			else {
				AssetFileType fileType = GetFileType(entry.path());
				switch (fileType) {
					case AssetFileType::PNG:
					{
						treeName = std::string(ICON_FA_PHOTO_VIDEO) + std::string(" ") + name;
						if (ImGui::TreeNodeEx(name.c_str(), ImGuiTreeNodeFlags_Leaf, treeName.c_str())) {
							ImGui::TreePop();
						}
						break;
					}
					case AssetFileType::GLSL:
					{
						treeName = std::string(ICON_FA_CIRCLE) + std::string(" ") + name;
						if (ImGui::TreeNodeEx(name.c_str(), ImGuiTreeNodeFlags_Leaf, treeName.c_str())) {
							ImGui::TreePop();
						}
						break;
					}
					case AssetFileType::TTF:
					{
						treeName = std::string(ICON_FA_FONT) + std::string(" ") + name;
						if (ImGui::TreeNodeEx(name.c_str(), ImGuiTreeNodeFlags_Leaf, treeName.c_str())) {
							ImGui::TreePop();
						}
						break;
					}
					case AssetFileType::SCENE:
					{
						treeName = std::string(ICON_FA_ARCHIVE) + std::string(" ") + name;
						if (ImGui::TreeNodeEx(name.c_str(), ImGuiTreeNodeFlags_Leaf, treeName.c_str())) {
							ImGui::TreePop();
						}
						break;
					}
				}
			}
		}

		ImGui::EndChild();
	}

	void ImGuiAssetBrowser::DrawRecursive(const std::filesystem::path& path)
	{
		for (const auto& entry : std::filesystem::directory_iterator(path)) {
			if (!IsDirectory(entry.path())) {
				continue;
			}

			std::string name = entry.path().filename().string();
			std::string treeName;

			if (!IsDirectoryEmpty(entry.path())) {
				treeName = ICON_FA_FOLDER + std::string(" ") + name;

				if (!HasSubDirectory(entry.path())) {
					bool opened = ImGui::TreeNodeEx(name.c_str(), ImGuiTreeNodeFlags_Leaf, treeName.c_str());

					if (ImGui::IsItemClicked()) {
						m_CurrentRightPanelDirectoryPath = entry.path();
					}

					DrawRecursive(entry.path());
					ImGui::TreePop();
				}
				else {
					bool opened = ImGui::TreeNodeEx(name.c_str(), ImGuiTreeNodeFlags_OpenOnArrow, treeName.c_str());

					if (ImGui::IsItemClicked()) {
						m_CurrentRightPanelDirectoryPath = entry.path();
					}

					if (opened) {
						DrawRecursive(entry.path());
						ImGui::TreePop();
					}
				}
			}
			else {
				treeName = ICON_FA_FOLDER_MINUS + std::string(" ") + name;
				ImGui::TreeNodeEx(name.c_str(), ImGuiTreeNodeFlags_Leaf, treeName.c_str());
				if (ImGui::IsItemClicked()) {
					m_CurrentRightPanelDirectoryPath = entry.path();
				}
				ImGui::TreePop();
			}
		}
	}

	void ImGuiAssetBrowser::DrawRightFilePathHeader(const std::filesystem::path& path)
	{
		std::stringstream stream(path.string());
		std::string pathSegment;
		std::vector<std::string> pathSegmentList;

		char separator = (char)std::filesystem::path::preferred_separator;

		while (std::getline(stream, pathSegment, separator)) {
			pathSegmentList.push_back(pathSegment);
		}

		std::string cumulativePath;

		for (const auto& entry : pathSegmentList) {
			cumulativePath += entry + separator;

			if (ImGui::Button(entry.c_str())) {
				m_CurrentRightPanelDirectoryPath = cumulativePath;
			}

			ImGui::SameLine();
			ImGui::Text(">");
			ImGui::SameLine();
		}
		ImGui::NewLine();
	}

	AssetFileType ImGuiAssetBrowser::GetFileType(const std::filesystem::path& path)
	{
		auto& it = m_FileExtensionMap.find(path.filename().extension().string());
		if (it == m_FileExtensionMap.end()) {
			return AssetFileType::NONE;
		}
		else {
			return it->second;
		}
	}
}
