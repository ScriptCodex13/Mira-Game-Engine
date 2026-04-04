#include "Scene.h"

namespace mira
{
	Scene::Scene()
	{

	}
	Scene::~Scene()
	{

	}

	entt::registry& Scene::Get()
	{
		return m_registry;
	}
}