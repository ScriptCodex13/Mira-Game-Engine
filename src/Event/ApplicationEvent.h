#pragma once 
#ifndef APPLICATION_EVENT_H
#define APPLICATION_EVENT_H

#include <Zap.h>

namespace mira
{
	enum ApplicationEvent
	{
		WINDOWCLOSE,
		WINDOWFOCUS,
		WINDOWNOTFOCUS,
		TERMINATEAPPLICATION
	};
}

#endif