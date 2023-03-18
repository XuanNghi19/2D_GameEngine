#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "ECS/Collision.h"
#include "Vector2D.h"

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

enum groupLabels : std::size_t
{
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders,
};

Game::Game()
{}
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen == true)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialised..." << std::endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "window ccreate!" << std::endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}
		isRuning = true;
	}
	else
	{
		isRuning = false;
	}
	map = new Map();

	// ecs implementation

	Map::LoadMap("assets/p16x16.map", 16, 16);

	player.addComponent<TransformComponent>(0.0f , 0.0f, 33, 49, 2);
	player.addComponent<SpriteComponent>("assets/mage.png");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	wall.addComponent<TransformComponent>(300.0f, 300.0f, 29, 29, 3);
	wall.addComponent<SpriteComponent>("assets/wall.png");
	wall.addComponent<ColliderComponent>("wall");
	wall.addGroup(groupMap);

}

void Game::hadelEvents()
{

	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRuning = false;
	default:
		break;
	}
}

void Game::update()
{
	manager.refresh();
	manager.update();

	for (auto cc : colliders)
	{
		Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
	}
}

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));

void Game::render()
{
	SDL_RenderClear(renderer);
	// this is where we would add stuff to render
	for (auto& t : tiles)
	{
		t->draw();
	}
	for (auto& p : players)
	{
		p->draw();
	}
	for (auto& e : enemies)
	{
		e->draw();
	}

	SDL_RenderPresent(renderer);

}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned!" << std::endl;
}

void Game::AddTile(int id, int x, int y)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, 32, 32, id);
	tile.addGroup(groupMap);
}

bool Game::runing()
{
	return isRuning;
}
Game::~Game()
{}