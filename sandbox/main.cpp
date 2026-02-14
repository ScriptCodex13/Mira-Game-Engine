#include <Mira.h>

class Game : public mira::Application
{
public:
	Game()
	{

	};

	~Game()
	{

	};
};

mira::Application* mira::CreateApplication()
{
	return new Game();
}