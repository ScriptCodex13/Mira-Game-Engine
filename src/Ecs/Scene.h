#pragma once
#ifndef SCENE_H
#define SCENE_H

#include <entt.hpp>

namespace mira
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		entt::registry& Get();

	private:
		entt::registry m_registry;
	};
}

#endif