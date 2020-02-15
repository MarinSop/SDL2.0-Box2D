#pragma once
#include "SDL.h"
#include "box2d/box2d.h"
#include "Player.h"
#include "GraphicBody.h"
#include "MyContactListener.h"
#include "Map.h"
#include "SDL_image.h"
class Game
{
public:
	Game(SDL_Renderer* renderer);
	~Game();

	void update(SDL_Window* window);
	void render(SDL_Renderer* renderer);

	bool isRunning;

private:

	b2World* _world;
	b2Vec2 _gravity = b2Vec2(0.0f,2.0f);

	Map* _map;
	Player* _player;
	MyContactListener* _contactListener;
	void EventHandler(SDL_Window* window);
};

