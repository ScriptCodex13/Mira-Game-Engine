#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <entt.hpp>
#include <Zap.h>
#include <string>
#include <utility>

namespace mira
{
	class Entity
	{
	public:
		Entity();
		~Entity();

		void AttachToScene(entt::registry& scene);
		void Delete(entt::registry& scene);
		entt::entity Get();

		template<typename T, typename... A> void AttachComponent(entt::registry& scene, A&&... args)
		{ 
			scene.emplace_or_replace<T>(m_entity, std::forward<A>(args)...);
			messages::PrintMessage("Attached component to entity: " + std::to_string((unsigned long long)m_entity), "", MessageTypes::api_core_info, false);
		};

		template<typename T> void DetachComponent(entt::registry& scene) 
		{ 
			messages::PrintMessage("Detached component from entity: " + std::to_string((unsigned long long)m_entity), "", MessageTypes::api_core_info, false);
			scene.remove<T>(m_entity);
		}; // Also deletes it

		template<typename... T> auto& GetComponent(entt::registry& scene)
		{
			return scene.get<T...>(m_entity);
		}

		template<typename T> bool HasComponent(entt::registry& scene)
		{
			if (auto view = scene.view<T>()) return true;
			
			return false;
		};

	public:

		entt::entity m_entity;
	};
}

#endif