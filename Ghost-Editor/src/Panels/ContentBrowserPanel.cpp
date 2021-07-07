#include "gtpch.h"
#include "ContentBrowserPanel.h"

#include <imgui/imgui.h>

namespace Ghost
{
	// Once we have projects, change this
	static const std::filesystem::path s_Assetpath = "assets";

	ContentBrowserPanel::ContentBrowserPanel()
		:m_CurrentDirectory(s_Assetpath) {
		m_DirectoryIcon = Texture2D::Create("Resources/Icons/ContentBrowser/FolderIcon.png");
		m_FileIcon = Texture2D::Create("Resources/Icons/ContentBrowser/DocumentIcon.png");
	}

	void ContentBrowserPanel::OnImGuiRender() {
		ImGui::Begin("Content Browser");

		if (m_CurrentDirectory != std::filesystem::path(s_Assetpath))
		{
			if (ImGui::Button("<-"))
			{
				m_CurrentDirectory = m_CurrentDirectory.parent_path();
			}
		}

		static float padding = 16.0f;
		static float thumbnailSize = 75.0f;

		float cellSize = thumbnailSize + padding;

		float panelWidth = ImGui::GetContentRegionAvail().x;
		int columnCount = (int)(panelWidth / cellSize);

		columnCount = columnCount < 1 ? 1 : columnCount;

		ImGui::Columns(columnCount, 0, false);

		for (auto& directoryEntry : std::filesystem::directory_iterator(m_CurrentDirectory))
		{
			const auto& path = directoryEntry.path();
			auto relativePath = std::filesystem::relative(path, s_Assetpath);
			std::string filenameString = relativePath.filename().string();

			Ref<Texture2D> icon = directoryEntry.is_directory() ? m_DirectoryIcon : m_FileIcon;

			ImGui::ImageButton((ImTextureID)icon->GetRendererID(),
				{ thumbnailSize, thumbnailSize }, { 0 , 1 }, { 1, 0 });

			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				if (directoryEntry.is_directory())
				{
					m_CurrentDirectory /= path.filename();
				}
			}

			float textWidth = ImGui::CalcTextSize(filenameString.c_str()).x;
			if (textWidth > thumbnailSize)
			{
				ImGui::TextWrapped(filenameString.c_str());
			}
			else
			{
				ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ((thumbnailSize - textWidth) / 2) + (padding / 4));
				ImGui::Text(filenameString.c_str());
			}

			ImGui::NextColumn();
		}

		ImGui::Columns(1);

		/*ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 512);
		ImGui::SliderFloat("Padding", &padding, 0, 32);*/
		// TODO: status bar
		ImGui::End();
	}
}
