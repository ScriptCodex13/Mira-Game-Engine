#include "LayerStack.h"

namespace mira
{
	LayerStack::LayerStack()
	{

	}

	LayerStack::~LayerStack()
	{

	}

	void LayerStack::AttachLayer(std::shared_ptr<ILayer> layer)
	{
		layers.push_back(layer);
		layers[layers.size() - 1]->OnAttach();
		messages::PrintMessage("Attached new layer", "", MessageTypes::api_core_info, false);
	}

	void LayerStack::DetachLayer(std::shared_ptr<ILayer> layer) 
	{
		for(int i = 0; i < layers.size(); i++)
		{
			if(layers[i] == layer)
			{
				layers[i]->OnDetach();
				layers.erase(layers.begin() + i);
				messages::PrintMessage("Detached layer", "", MessageTypes::api_core_info, false);
			}
		}
	};

	void LayerStack::Update()
	{
		for (auto i : layers)
		{
			i->OnUpdate(i_current_event);

			if(i->event_consumed) i_current_event = Event(); // Reset Event

			i_current_event = i->OnEvent();

			if (i_current_event.type == APPLICATION && i_current_event.event == TERMINATEAPPLICATION)
				application_close = true;
		}
	}
}