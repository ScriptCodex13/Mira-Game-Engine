#pragma once
#ifndef WINDOW_SETTINGS_H
#define WINDOW_SETTINGS_H

#include <string>

namespace window_settings
{
	inline unsigned int width = 1920;
	inline unsigned int height = 1080; 
	inline unsigned int viewport_x = width;  // Viewport
	inline unsigned int viewport_y = height; // Viewport
	inline float aspect_ratio = (float)width / (float)height;
	inline std::string title = "Mira Game";
	inline std::string icon_path = "";
}

namespace mira 
{
	inline float delta = 1.0f;
}

#endif