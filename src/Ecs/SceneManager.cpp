#include "SceneManager.h"

namespace mira
{
	SceneManager::SceneManager()
	{
		
	}

	SceneManager::~SceneManager()
	{

	}

	void SceneManager::NewScene(uint64_t& return_id)
	{
		return_id = GenerateID();

		scenes[return_id] = std::make_shared<Scene>();
	}

	void SceneManager::LoadScene(uint64_t id)
	{
		if(scenes.count(id) < 1)
		{
			messages::PrintMessage("Could not load scene. Scene with id " + std::to_string(id) + " not found", "", MessageTypes::error, false);
			return;
		}

		active_scenes.push_back(id);
	}

	void SceneManager::UnloadScene(uint64_t id)
	{
		if (scenes.count(id) < 1)
		{
			messages::PrintMessage("Could not unload scene. Scene with id " + std::to_string(id) + " not found", "", MessageTypes::error, false);
			return;
		}

		if (active_scenes.empty()) return;

		for(int i = 0; i < active_scenes.size(); i++)
		{
			if(active_scenes[i] == id)
			{
				active_scenes.erase(active_scenes.begin() + i);
			}
		}
	}

	void SceneManager::DeleteScene(uint64_t id)
	{
		if (scenes.count(id) < 1)
		{
			messages::PrintMessage("Could delete scene. Scene with id " + std::to_string(id) + " not found", "", MessageTypes::error, false);
		
			return;
		}

		scenes.erase(id);
		
		if (active_scenes.empty()) return;

		for (int i = 0; i < active_scenes.size(); i++)
		{
			if (active_scenes[i] == id)
			{
				active_scenes.erase(active_scenes.begin() + i);
			}
		}
	}

	void SceneManager::Update()
	{
		for (uint64_t sc : active_scenes)
		{
			if (auto view = scenes[sc]->Get().view<Camera3D>())
			{
				for (auto entity : view)
				{
					auto& camera = view.get<Camera3D>(entity);

					m_view = camera.m_view;
					m_projection = camera.m_projection;
				}
			}
			
			if (auto view = scenes[sc]->Get().view<Camera2D>())
			{
				for (auto entity : view)
				{
					auto& camera = view.get<Camera2D>(entity);

					m_view = camera.m_view;
					m_projection = camera.m_projection;
				}
			}

			if (auto view = scenes[sc]->Get().view<Mesh3D>())
			{
				for (auto entity : view)
				{
					auto& mesh = view.get<Mesh3D>(entity);

					if (scenes[sc]->Get().any_of<Transform>(entity))
					{
						auto view_transform = scenes[sc]->Get().view<Transform>();
						auto& transform = view_transform.get<Transform>(entity);

						mesh.SetTransform(transform.transform);
					}
					
					mesh.SetCamera(m_view, m_projection);

					mesh.Update();
				}
			}

			if (auto view = scenes[sc]->Get().view<Sprite2D>())
			{
				for (auto entity : view)
				{
					auto& sprite = view.get<Sprite2D>(entity);

					if (scenes[sc]->Get().any_of<Transform>(entity))
					{
						auto view_transform = scenes[sc]->Get().view<Transform>();
						auto& transform = view_transform.get<Transform>(entity);

						sprite.SetTransform(transform.transform);
					}
					
					sprite.SetCamera(m_view, m_projection);
					
					if (scenes[sc]->Get().any_of<Texture>(entity))
					{
						auto view_texture = scenes[sc]->Get().view<Texture>();
						auto& texture = view_texture.get<Texture>(entity);

						sprite.Update(texture);
					}
				}
			}
			
			
			/*if (scenes.count(sc) < 1)
			{ 
				auto view = scenes[sc]->Get().view<Mesh>();

				for(auto entity : view)
				{
					auto& mesh = view.get<Mesh>(entity);

					mesh.Update();
				}
			}
			else // Erase if scene doesn't exist but active scene id
			{
				for (int i = 0; i < active_scenes.size(); i++)
				{
					if (active_scenes[i] == sc)
					{
						active_scenes.erase(active_scenes.begin() + i);
					}
				}
			}*/
		}
	}

	std::shared_ptr<Scene> SceneManager::GetScene(uint64_t id)
	{
		if (scenes.count(id) < 1)
		{
			messages::PrintMessage("Could find scene with id " + std::to_string(id), "", MessageTypes::error, false);

			return nullptr;
		}

		return scenes[id];
	}

	entt::entity SceneManager::RegisterEntity(uint64_t id)
	{
		if (scenes.count(id) < 1)
		{
			messages::PrintMessage("Scene with id " + std::to_string(id) + " not found", "", MessageTypes::error, false);

			return entt::entity();
		}

		return scenes[id]->Get().create();
	}

	entt::registry& SceneManager::GetNativeRegistry(uint64_t id)
	{
		if (scenes.count(id) < 1)
		{
			messages::PrintMessage("Scene with id " + std::to_string(id) + " not found", "", MessageTypes::error, false);

			return entt::registry();
		}

		return (entt::registry&)scenes[id]->Get();
	}
}