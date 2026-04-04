#include "Application.h"

namespace mira
{
	Application::Application()
	{
		zap::Init(3, 3);
		
		// Configure window settings here

		window = std::make_shared<ZapWindow>();
		zap::InitGlad();

		window_layer = std::make_shared<WindowLayer>(window);
		layer_stack.AttachLayer(window_layer);
	}
	Application::~Application()
	{
		layer_stack.DetachLayer(window_layer);
		zap::Delete();
	}

	void Application::Run()
	{
		while(layer_stack.application_close == false) layer_stack.Update();
	}
}