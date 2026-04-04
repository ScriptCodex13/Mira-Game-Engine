#pragma once
#ifndef LAYERSTACK_H
#define LAYERSTACK_H

#include <vector>
#include <memory>
#include <Zap.h>

#include "ILayer.h"
#include "../Event/Event.h"
#include "../Event/ApplicationEvent.h"
#include "InputMap.h"

namespace mira
{
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void AttachLayer(std::shared_ptr<ILayer> layer);
		void DetachLayer(std::shared_ptr<ILayer> layer);
		void Update();

		bool application_close = false;
		std::vector<std::shared_ptr<ILayer>> layers;
		Event i_current_event;
	};
}

#endif