#pragma once 
#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "Application.h"

int Startup()
{
	auto application = mira::CreateApplication();
	application->Run();
	delete application;

	return 0;
}

#ifdef _WIN32
#include <Windows.h>
#ifdef ZAP_CONSOLE_APPLICATION
int main() { return Startup(); }
#elif defined ZAP_WINDOW_ONLY_APPLICATION
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) { return Startup(); }
#endif
#else
int main() { return Startup(); }
#endif


#endif