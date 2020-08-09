#include "gtpch.h"
#include "Ghost/Scene/Entity.h"

namespace Ghost {
	Entity::Entity(entt::entity handle, Scene* scene)
		:m_EntityHandle(handle), m_Scene(scene)
	{
	}
}