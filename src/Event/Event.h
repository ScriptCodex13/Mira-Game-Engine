#pragma once
#ifndef EVENT_H
#define EVENT_H

#include "../Layer/InputMap.h"

#include <Zap.h>
#include <unordered_map>

namespace mira
{
	enum EventTypes
	{
		NONE = -1,
		APPLICATION,
		WINDOW,
		KEY_PRESS,
		KEY_RELEASE,
	};

	enum WindowEvents
	{
		VSYNC_ENABLE,
		VSYNC_DISABLE,
		WINDOWMAXIMZE,
		WINDOWMINIMIZE,
	};

	struct Event
	{
		int event = -1;
		int type = NONE;
		std::unordered_map<int, int> inputmap;
	};
}

#endif