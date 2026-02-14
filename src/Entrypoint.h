#pragma once 
#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "Application.h"

int main()
{
	auto application = mira::CreateApplication();
	application->Run();
	delete application;
}

#endif