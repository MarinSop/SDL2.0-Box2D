#pragma once
#include "SDL.h"
#include "box2d/box2d.h"
#include "Player.h"
#include "GraphicBody.h"
#include "MyContactListener.h"
#include "Map.h"
#include "SDL_image.h"
#include "MouseControls.h"
class Game
{
public:
	Game(SDL_Renderer* renderer);
	~Game();

	void update(SDL_Window* window,SDL_Renderer* renderer);
	void render(SDL_Renderer* renderer);

	bool isRunning;

private:

	b2World* _world;
	b2Vec2 _gravity = b2Vec2(0.0f,0.5f);

	bool hold = false;
	int _currentLevel = 1;

	Map* _map;
	Player* _player;
	MyContactListener* _contactListener;
	MouseControls* _mouseControls;

	void reset();
	void nextLevel(SDL_Renderer* renderer);
	void EventHandler(SDL_Window* window);
};

