#pragma once

#include "Ghost/Core/Base.h"
#include "Ghost/Core/Log.h"
#include "Ghost/Scene/Scene.h"
#include "Ghost/Scene/Entity.h"

namespace Ghost {
	class SceneHierarchyPanel {
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& scene);

		void SetContext(const Ref<Scene>& scene);

		void OnImGuiRender();
	private:
		void DrawEntityNode(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};
}
