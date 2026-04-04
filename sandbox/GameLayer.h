#pragma once
#ifndef GAME_LAYER_H
#define GAME_LAYER_H

#include "Mira-Export.h"

class GameLayer : public mira::ILayer
{
public:
	GameLayer(mira::SceneManager& sc_manager); // the scene and the asset manager... are passed in here
	~GameLayer();

	void OnAttach()override;
	void OnDetach()override;
	void OnUpdate(mira::Event event)override;
	mira::Event OnEvent()override;

private:
	// ref

	mira::SceneManager& scene_manager;

	//

private:
	// Put your vars here
	mira::Entity player = mira::Entity();
	uint64_t main_scene;

	const char* vertex_shader_source =
		R"glsl(
		#version 330 core

		layout(location = 0) in vec3 vertices;

		uniform mat4 model;

		void main()
		{
			gl_Position = model * vec4(vertices, 1.0);
		}
)glsl";

	const char* fragment_shader_source =
		R"glsl(
		#version 330 core

		out vec4 frag_color;

		void main()
		{
			frag_color = vec4(1.0, 0.0, 0.0, 1.0);
		}
)glsl";

	//
};

#endif