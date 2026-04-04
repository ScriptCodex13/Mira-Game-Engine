#ifndef SCENE_LAYER_H
#define SCENE_LAYER_H

#include "SceneManager.h"

#include "../Layer/ILayer.h"

namespace mira
{
	class ECSLayer : public ILayer
	{
	public:
		ECSLayer() { sc_manager = SceneManager(); };
		~ECSLayer() {};

		void OnAttach()override {};
		void OnDetach()override {};
		void OnUpdate(Event event)override {};
		Event OnEvent()override { return Event(); };

	private:
		SceneManager sc_manager;
	};
}

#endif