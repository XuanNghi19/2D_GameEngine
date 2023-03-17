#ifndef Game_h
#define Game_h
#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <vector>

class ColliderComponent;

class Game
{
public:
	Game();
	~Game();
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void hadelEvents();
	void update();
	void render();
	void clean();
	bool runing();

	static void AddTile(int id, int x, int y);
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static std::vector<ColliderComponent*> colliders;

private:
	int cnt = 0;
	bool isRuning;
	SDL_Window* window;
};
#endif

