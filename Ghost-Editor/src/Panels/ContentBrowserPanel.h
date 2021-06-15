#pragma once

#include <filesystem>

namespace Ghost
{
	class ContentBrowserPanel {
	public:
		ContentBrowserPanel();

		void OnImGuiRender();
	private:
		std::filesystem::path m_CurrentDirectory;
	};
}
