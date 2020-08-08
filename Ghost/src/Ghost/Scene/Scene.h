#pragma once

#include "entt.hpp"

#include "Ghost/Core/Timestep.h"

namespace Ghost {
	class Scene {
	public:
		Scene();
		~Scene();

		entt::entity CreateEntity();

		// TEMP
		entt::registry& Reg() { return m_Registry; }

		void OnUpdate(Timestep ts);
	private:
		entt::registry m_Registry;
	};
}