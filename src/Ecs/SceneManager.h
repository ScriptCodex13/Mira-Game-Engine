#pragma once
#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <entt.hpp>
#include <unordered_map>
#include <Zap.h>
#include <memory>
#include <random>

#include "Scene.h"
#include "Components.h"

inline uint64_t GenerateID()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<uint64_t> dist(0, mt.max());

	return dist(mt);
}

namespace mira
{
	class SceneManager
	{
	public:
		SceneManager();
		~SceneManager();

		void NewScene(uint64_t& return_id);
		void LoadScene(uint64_t id);
		void UnloadScene(uint64_t id);
		void DeleteScene(uint64_t id);

		void Update();

		entt::entity RegisterEntity(uint64_t id);
		entt::registry& GetNativeRegistry(uint64_t id);

		std::shared_ptr<Scene> GetScene(uint64_t id);

	private:
		std::vector<uint64_t> active_scenes;
		std::unordered_map<uint64_t, std::shared_ptr<Scene>> scenes;

		glm::mat4 m_projection = glm::mat4(1.0f);
		glm::mat4 m_view = glm::mat4(1.0f);
	};
}

#endif