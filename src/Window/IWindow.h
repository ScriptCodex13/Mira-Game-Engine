#pragma once
#ifndef IWINDOW_H
#define IWINDOW_H

#include "../Event/Event.h"
#include "../Event/ApplicationEvent.h"
#include "WindowSettings.h"
#include "../Layer/InputMap.h"

#include <Zap.h>
#include <Graphics.h>
#include <magic_enum.hpp>
#include <algorithm>

namespace mira
{
	class IWindow
	{
	public:
		IWindow() {};
		~IWindow() {};

		virtual void Init() {};
		virtual Event GetEvent() { return Event(); };
		virtual void Update(Event event) {};
		virtual void Delete() {};

		Inputmap inputmap;
	};

	class ZapWindow : public IWindow
	{
	public:
		ZapWindow();
		~ZapWindow();

		void Init() override;
		Event GetEvent() override;
		void Update(Event event) override;
		void Delete() override;

		std::unique_ptr<zap::Window> i_window;
		std::string lastIconPath;
	};
}

#endif