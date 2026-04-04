#pragma once
#ifndef ILAYER_H
#define ILAYER_H

#include "../Event/Event.h"

#include <unordered_map>

namespace mira
{
	class ILayer
	{
	public:
		ILayer() {};
		~ILayer() {};

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate(Event event) {};
		virtual Event OnEvent() { return Event(); };

		bool event_consumed = false;
	};
}

#endif