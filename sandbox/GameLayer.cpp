#include "GameLayer.h"

//Put your code here

inline std::vector<float> vertices
{
	-0.4f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f,
	 0.4f, -0.5f, 0.0f
};

inline std::vector<unsigned int> indices
{
	0, 1, 2
};


GameLayer::GameLayer(mira::SceneManager& sc_manager) : scene_manager(sc_manager)
{
	scene_manager.NewScene(main_scene);
	scene_manager.LoadScene(main_scene);

	player.AttachToScene(scene_manager.GetNativeRegistry(main_scene));


	player.AttachComponent<mira::Mesh3D>(scene_manager.GetNativeRegistry(main_scene), vertices, indices);

	auto& mesh = player.GetComponent<mira::Mesh3D>(scene_manager.GetNativeRegistry(main_scene));

	mesh.SetAttribPointer(0, 3, 3, 0);
	mesh.SetShader(vertex_shader_source, fragment_shader_source);

	mesh.Enable(true);

	mesh.ModelMatrixLocation("model");
}

GameLayer::~GameLayer()
{
	player.Delete(scene_manager.GetNativeRegistry(main_scene));
}

void GameLayer::OnAttach() // Called on layer attach
{
	
}

void GameLayer::OnDetach() // Called on layer detach
{

}

void GameLayer::OnUpdate(mira::Event event) // called every layerstack update
{
	scene_manager.Update();
}

mira::Event GameLayer::OnEvent()
{
	mira::Event event;

	event.type = mira::EventTypes::WINDOW;
	event.event = mira::WindowEvents::VSYNC_ENABLE;

	return event; // resets/consumes the event
}

//