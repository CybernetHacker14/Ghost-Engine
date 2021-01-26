#pragma once

#include "entt.hpp"

#include "Ghost/Core/Timestep.h"
#include "Ghost/Renderer/EditorCamera.h"
#include "Ghost/Renderer/Framebuffer.h"

namespace Ghost {
	class Entity;

	class Scene {
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());
		void DestroyEntity(Entity entity);

		void OnUpdateRuntime(Timestep ts);
		void OnUpdateEditor(Timestep ts, EditorCamera& camera);
		void OnViewportResize(uint32_t width, uint32_t height);

		void DrawIDBuffer(Ref<Framebuffer> target, EditorCamera& camera);
		int Pixel(int x, int y);

		Entity GetPrimaryCameraEntity();
	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);
	private:
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;
	};
}
