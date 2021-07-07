#pragma once

#include <filesystem>

#include "Ghost/Renderer/Texture.h"

namespace Ghost
{
	class ContentBrowserPanel {
	public:
		ContentBrowserPanel();

		void OnImGuiRender();
	private:
		std::filesystem::path m_CurrentDirectory;
		Ref<Texture2D> m_DirectoryIcon;
		Ref<Texture2D> m_FileIcon;
	};
}
