#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H

#include "./Layer/LayerStack.h"
#include "./Window/WindowLayer.h"
#include "./Ecs/SceneManager.h"

#include <Zap.h>
#include <memory>

namespace mira
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	public:
		std::shared_ptr<IWindow> window;

	public:
		LayerStack layer_stack = LayerStack();
		SceneManager scene_manager = SceneManager();

		std::shared_ptr<WindowLayer> window_layer;

	};

	Application* CreateApplication();
}

#endif