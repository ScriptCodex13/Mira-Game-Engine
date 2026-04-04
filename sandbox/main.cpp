#include <Entrypoint.h>
#include <Mira-Export.h>

#include "GameLayer.h"

class Game : public mira::Application
{
public:
	Game()
	{
		layer_stack.AttachLayer(game_layer);
	};

	~Game()
	{
		layer_stack.DetachLayer(game_layer);
	};

public:
	std::shared_ptr<GameLayer> game_layer = std::make_shared<GameLayer>(scene_manager);
};

mira::Application* mira::CreateApplication()
{
	return new Game();
}