#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H

namespace mira
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApplication();
}

#endif