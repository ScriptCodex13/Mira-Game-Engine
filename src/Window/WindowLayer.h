#pragma once 
#ifndef WINDOW_LAYER_H
#define WINDOW_LAYER_H

#include "../Layer/ILayer.h"
#include "IWindow.h"

#include <memory>

namespace mira
{
	class WindowLayer : public ILayer
	{
	public:
		WindowLayer(std::shared_ptr<IWindow> window) : m_window(window) {};
		~WindowLayer() {};

		void OnAttach() override { m_window->Init(); };
		void OnDetach() override { m_window->Delete(); };
		void OnUpdate(Event event) { m_window->Update(event); };
		Event OnEvent() override { return m_window->GetEvent(); }

	private:
		std::shared_ptr<IWindow> m_window;
	};
}

#endif