#include "Entity.h"

namespace mira
{
	Entity::Entity()
	{

	}

	Entity::~Entity()
	{

	}

	void Entity::AttachToScene(entt::registry& scene)
	{
		m_entity = scene.create();

		messages::PrintMessage("Attached new entity[id:" + std::to_string((unsigned long long)m_entity) + "] to scene", "", MessageTypes::api_core_info, false);
	}

	void Entity::Delete(entt::registry& scene)
	{
		scene.destroy(m_entity);

		messages::PrintMessage("Deleted entity[id:" + std::to_string((unsigned long long)m_entity) + "] from scene", "", MessageTypes::api_core_info, false);
	}

	entt::entity Entity::Get()
	{
		return m_entity;
	}

}